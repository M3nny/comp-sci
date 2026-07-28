**Image captioning** takes an image as input and produces a natural-language sentence describing it.

This task seemed solved when the first **CNN + RNN** approaches were discovered:

Take a _CNN pretrained on ImageNet_, chop off the final classification layer and keep everything before it as a general-purpose image feature extractor.

Normally _RNN's hidden state update_ is $h_t=\tanh(W_{hh}h_{t-1}+W_{xh}x_t+b_h)$, to _inject image information_, a new term is added: $h_t=\tanh(W_{hh}h_{t-1}+W_{xh}x_t+W_{ih}v+b_h)$, where $v$ is the CNN's image feature vector and $W_{ih}$ is a new learned weight matrix.
>This effectively seeds the RNN's initial hidden state with visual information.

Starting from a `<START>` token, the RNN predicts a word, that word is fed back in as the next input, and this repeats until the model samples an `<END>` token, at which point generation stops.
>This is a standard autoregressive sequence generation, just conditioned on an image.

>[!Info]
>These models often latch onto spurious visual correlations rather than truly understanding scene content.

The key limitation of this architecture is that **all image information must be compressed into a single context vector** (the initial hidden state), which is fine for short captions, but a constraint for long descriptions, since a fixed-size vector has to encode everything the model might ever want to say.
![[CNN+RNN for image captioning.png|600]]

The fix (borrowed from machine translation) is to **compute a new context vector at every decoding step**, each one attending to different spatial regions of the image.

Instead of a single pooled feature vector, extract a _spatial feature grid_ from the CNN, specifically a $H\times W\times D$ tensor, giving one feature vector $z_{i,j}$ per spatial location.

At each decoder step $t$, compute _alignment scores_ $e_{t,i,j}=f_{att}(h_{t-1},z_{i,j})$ using a small MLP that scores how relevant each spatial location is, given the current hidden state.

Then we _normalize_ these scores with a softmax over all locations to get attention weights $\alpha_{t,i,j}$.
The _context vector_ is computed as a weighted sum $c_t=\sum_{i,j}\alpha_{t,i,j}\cdot z_{t,i,j}$.

The context vector is then fed into the decoder per-step along with the previous word and hidden state $y_t=g_v(y_{t-1},h_{t-1},c_t)$.

![[CNN+RNN+Attention for image captioning.png|600]]

This whole pipeline is **differentiable end-to-end** which means that the model learns where to look without ever being given explicit supervision on what to attend to.

There are **two attention versions**:
- _Soft attention_ (what's described above): smooth, differentiable weighted average, trainable directly by backprop
- _Hard attention_: forces the model to pick exactly one location, which is not differentiable and require reinforcement learning to train

![[Soft-hard attention.png]]
>Above: soft attention.
>Below: hard attention.

The final evolution **drops RNN entirely**, two changes happen in sequence:
- Replace the RNN decoder with a _transformer encoder-decoder_, the spatial CNN features become a sequence of tokens fed into a transformer encoder, whose outputs condition a transformer decoder that autoregressively generates caption words, keeping the same input/output shape as before, but self-attention replace recurrence
- A [[05 - Vision transformers|vision transformer]] is used by slicing the image directly into patches, then linearly embeds each patch and adds positional embeddings, and feeds the whole sequence into a standard transformer encode, thus _removing CNNs_ from the pipeline, treating image patches like word tokens

![[Transformers for image captioning.png|600]]

### CLIP
State-of-the-art computer vision systems are typically trained to predict a fixed set of predetermined object categories, which **restricts their generality** since new visual concepts require additional labeled data.

**CLIP's (Contrastive Language-Image Pre-training)** alternative is to _learn directly from raw text about images_, leveraging a much broader and more scalable source of supervision than manually labeled datasets.

The payoff is robust **zero-shot inference** and a shared multimodal embedding space.

**Contrastive Language-Image Pre-training** works as follows:
1. Start with a large set of `(image, text)` pairs
2. Pick an image encoder (ResNet or ViT) and a text encoder (transformer), and encoder a batch of $N$ images and $N$ texts into embeddings $I_1,...,I_N$ and $T_1,...,T_N$
3. Compute the full $N\times N$ matrix cosine similarities between every image embedding and every text embedding
4. Scale these similarities by a learned _temperature parameter_ $\tau$ and normalize each row/column into a probability distribution via softmax, the temperature will control how "peaked" or "soft" the distribution is

![[CLIP.png|500]]

The **training goal** is to maximize similarity on the diagonal (the true image-text pairs) while minimizing it on all off-diagonals entries (mismatched pairs).
This is a **symmetric cross-entropy loss**, computed once treating images as the anchor and once treating text as the anchor, then summed:
$$SKL=\underbrace{KL(q||p)}_{\text{e.g. }I_N\cdot T_1}+\underbrace{KL(p||q)}_{\text{e.g. }I_1\cdot T_N}$$
This is genuinely **self-supervised** at scale, since no manual class labels are needed, just naturally-occurring image-caption pairs from the web.

Once trained, CLIP can classify images into any set of categories without further training, this is how **zero-shot classification** works:
1. Encode the query image into the shared embedding space
2. Take the candidate class names and turn each into a natural sentence using a template like "a photo of a {class name}"
3. Encode each of these text prompts with the text encoder
4. Compute cosine similarity between the image embedding and every text embedding
5. Pick the highest-similarity match as the predicted class

![[CLIP zero-shot classification.png|500]]

This is why it's called "zero-shot", the model was _never explicitly trained to recognize "dog"_ as a discrete label, it just recognizes that the image embedding is closest to the embedding of the phrase "a photo of a dog."

Models trained on natural language supervision **generalize far better to novel image distributions** than models trained on a fixed label taxonomy, because CLIP never overfits to the narrow visual statistics of one benchmark's label set in the first place.
