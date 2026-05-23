Traditional word embeddings like [[11 - Learning to rank#Word2Vec|Word2Vec]] assign a **single fixed vector** to each word _regardless of context_, this creates problems with words that have multiple meanings.

**Contextualized embeddings** solve this by computing a word's representation dynamically, based on the _surrounding words_ in a given sentence.

Rather than using full words as vocabulary items, modern neural IR systems use **subword tokenizers** to keep vocabulary sizes manageable (e.g. [WordPiece](https://huggingface.co/learn/llm-course/chapter6/6), [Byte Pair Encoding](https://huggingface.co/learn/llm-course/chapter6/5).

### Deep Neural Networks for contextualization
DNNs take static word representations and **enrich them using information from surrounding words**.

For instance, deciding whether "bank" means a financial institution or a riverbank requires reading the whole sentence.

Before transformers, [[04 - Deep learning#Recurrent neural networks|RNNs]] were the standard tool for this, but since they process text sequentially left-to-right, this creates **two major problems**:
- _Each step depends on the previous one_, making parallelization impossible
- _Long-range dependencies_ (words far apart in a sentence) are very hard to maintain in a "hidden state", slowing both training and inference

### Transformers
Introduced in [Attention Is All You Need](https://arxiv.org/pdf/1706.03762), **transformers** replaced the sequential approach with a **self-attention mechanism**.

Instead of reading word by word, a transformer _looks at all words simultaneously_ and learns which ones to **pay attention to** when encoding any given word.
>In the sentence "I arrived at the bank after crossing the river," the model can immediately connect "bank" to "river" in a single step, regardless of distance.

Transformers consist of stacks of **encoders** (which read and understand input) and **decoders** (which generate output), this makes them well-suited for sequence-to-sequence tasks (e.g. machine translation, summarization, question answering, ...).

#### Self-attention
For each word, the model creates three vectors by multiplying its embedding by **three learned weight matrices**:
- **Query ($Q$)**: what this word is "looking for"
- **Key ($K$)**: what each word "advertises" about itself
- **Value ($V$)**: the actual content each word contributes

![[Scaled dot product attention.png|200]]

The attention score for a word is computed by taking its _query vector_ $Q$ and dotting it with all _key vectors_ $K$, these scores are scaled and passed through a [[Layers#Funzioni di attivazione|softmax]] to become probabilities (how much to attend to each word).
Finally, the _value vectors_ $V$ are weighted by these probabilities and summed to produce the word's new contextualized representation.
$$\text{Attention}(Q,K,V)=\text{softmax}\left(\frac{QK^T}{\sqrt{d_k}}\right)V$$
The dot products are scaled in order to avoid small gradients generated from the softmax function when the dot products grow large in magnitude.
>$d_k$ is the dimension of both $Q$ and $K$.

>[!Example]- Self-Attention in action
>![[Self-attention.png]]
>To encode "it" in the fifth encoder, part of the self-attention mechanism is focusing on "The Animal", this entails inserting a part of the representation "The Animal" into the encoding of "it".

#### Multi-head self-attention
Rather than running self-attention once, transformers run it in **parallel multiple times** (each called a "head"), each with its own $Q$/$K$/$V$ matrices.

This lets the model capture different kinds of relationships simultaneously, for example, one head might focus on syntactic relationships, another on semantic ones.

The results from all heads are concatenated and projected back to the original dimension.

![[Multi-head attention.png|200]]
$$\begin{align}
\text{MultiHead(Q,K,V)}&=\text{Concat}(\text{head}_1,...,\text{head}_h)W^O\\
&\text{where head}_i=\text{Attention}(QW_i^Q,KW_i^K,VW_i^V)
\end{align}$$


>[!Example]- Multi-head Self-Attention in action
>![[Multi-head self attention in action.png]]
>To encode "it", the orange attention is focusing most on "The animal", while the green one most on "tired", this entails mainly inserting a part of representation "The Animal" and "tired" into the encoding of "it".

#### The transformer pipeline
![[Transformer model architecture.png|300]]

$$\text{---------- Encoder ----------}$$
A single encoder layer (left block in the diagram) has the following workflow.

**Input Embedding + Positional Encoding**
The raw input tokens are first converted to embeddings, then positional encodings are added (element-wise sum $\oplus$).

This is the only place embeddings are computed, in stacked encoders above the first layer, the input is simply the output of the previous encoder.

**Multi-head Attention**
Every token attends to every other token in the input sequence simultaneously.
This is done in parallel $H$ times with different learned $Q$/$K$/$V$ matrices, allowing the model to capture different types of relationships at once.

The $H$ outputs are concatenated and linearly projected back to the model dimension.

**Add & Norm**
After the attention sub-layer, there is a  [residual connection](https://en.wikipedia.org/wiki/Residual_neural_network) (the "Add" part), the input to the sub-layer is added directly to its output, this helps gradients flow during training and prevents information loss.

Then _layer normalization_ is applied to stabilize training.

**Feed forward**
A simple fully connected network applied independently and identically to each position. It consists of two linear transformations with a [[Layers#Funzioni di attivazione|ReLU]] in between. Its role is to further transform the attention output (essentially adding non-linearity).

**Add & Norm**
The same residual and normalization pattern is applied after the feed-forward sub-layer.

**Repeat**
This block is repeated $N$ times, each layer refines the contextual representations produced by the layer below it.

The output of the final encoder is a sequence of rich, contextualized vectors, one per input token.

$$\text{---------- Decoder ----------}$$
The decoder (right block in the diagram) is more complex and has three sub-layers instead of two.

It also receives the encoder's final output as an additional input, and it has the following workflow.

**Output Embedding + Positional Encoding**
The decoder takes as input the tokens it has already generated (shifted right by one position since the first input is a special start-of-sequence token).

These are embedded and positional encodings are added (like in the encoder).

**Masked Multi-Head Attention**
This is self-attention over the decoder's own previously generated tokens.

The key difference from the encoder's attention is the _mask_, which sets future positions to $-\infty$ before the softmax, so they become $0$ after it.

This means when generating token at position $t$, the model can only attend to positions $[0,...,t−1]$, thus enforcing _autoregressive behavior_.

In other words, the decoder can only use what it has already produced, which is necessary because at inference time future tokens don't exist yet.

**Add & Norm**
Same pattern of the encoder.

**Multi-Head Attention (Encoder-Decoder Attention)**
This bridges the encoder and decoder.

The _keys and values come from the encoder's final output_, while the _queries come from the previous decoder sub-layer_, this allows each decoder position to attend over all positions of the input sequence.
>"Given what we've generated so far, which parts of the input should we focus on next?"

This is what allows the model to align output tokens with relevant input tokens (e.g. in translation, aligning an Italian word with its English counterpart).

**Add & Norm**
Same pattern of the encoder.

**Repeat**
This block is also repeated $N$ times.

$$\text{---------- Linear + Softmax ----------}$$
After the final decoder layer, a linear projection maps the decoder's output vector to a logits vector of size $|V|$ (vocabulary size).

Softmax converts these into a probability distribution over all possible next tokens, then the token with the highest probability is selected as the output for that time step.

>[!Attention] Fully parallel encoder
>The **encoder is fully parallel** since it processes all input at once, while the **decoder is sequential at inference time** since it must generate one token at a time.
>
>During training however, the decoder can also be parallelized because the ground-truth output is known in advance and can be fed all at once with appropriate masking.

### Pre-trained language models
The key innovation over the standard transformer is **pre-training**, which has a different meaning from the normal training step in other machine learning models.

In this case pre-training consists in training the transformer on a **massive general corpus** (e.g. common crawl) using a **self-supervised** objective, instead of directly training it on a specific task.

Self-supervised means that **labels are created automatically from the data** without human labels needed, the text itself provides supervision, for example when the model encounters a sentence like "the cat sat on the", the corpus contains the whole sentence, so the model now tries to guess "mat" without actually looking at the following (label) word.

![[Pre-traing fine-tune.png|500]]

**Fine-tuning** takes the pre-trained model and trains it further on a small task-specific 
dataset , this requires way less time than pre-training.
>This **transfer learning** approach means we don't need to train a powerful model from scratch for every new task.

In general we say that:
- **Few-shot learning**: fine-tuning with very little labeled data
- **Zero-shot learning**: means using a pre-trained model on a new task with no fine-tuning at all

### Generative Pre-Training models (GPT)
GPTs are a **decoder-only** transformer, this means that the encode is dropped, as well as the encoder-decoder sub-layer, hence they only have the masked multi-head self-attention and the feed forward sub-layer 
>The mask is the key, since it ensures that each token can only attend to previous tokens.

This means that it's a decoder in the sense that it **generates text autoregressively**, one token at a time, using only its own previous outputs.

>[!Info]
>The **context window** just gets fed in as the initial sequence, and the model keeps extending it.

### BERT
**Bidirectional encoder representations from transformers (BERT)** is an **encoder-only** transformer used for IR, it is _bidirectional_ in the sense that it looks at both left and right context simultaneously.

>[!Example]
>Given the sentence "The [MASK] didn't cross the street because it was too tired", BERT can use both the left context and the right context to predict the masked word "animal."
>> This only happens during pre-training.


BERT uses two self-supervised objectives during pre-training:
- **Masked Language Model (MLM)**: randomly mask $\approx 15\%$ of tokens in the input and train the model to predict them, this is sometimes called a _cloze task_
- **Next Sentence Prediction (NSP)**: given two sentences, predict whether the second one genuinely follows the first in the original document, this teaches the model inter-sentence relationships

After pre-training the **prediction head is removed** and it becomes a "read-only" model which **produces rich contextual embedding** vector that encodes the meaning of that token in the context of the whole sequence.
>These vectors are what get used for downstream tasks like relevance classification in IR.

BERT's input combines three types of embeddings added element-wise:
- **Token embeddings**: the representation of each WordPiece token
- **Segment embeddings**: indicate whether a token belongs to sentence $A$ or $B$
- **Position embeddings**: encode the position of each token in the sequence

**Reserved WordPiece tokens** are inserted into every input sequence before feeding them to the model, during training BERT learns what these positions mean and how to use them:
- `[CLS]`: placed at the start of the input, the effect is that by the final layer its output vector has "absorbed" information from the whole sequence
- `[SEP]`: placed at the end of a sentence
- `[PAD]`: used to pad shorter sequences to a uniform length within a batch (these tokens are masked so they don't contribute to the model's learning)

Since the prediction head gets removed after pre-training, BERT can be **fine-tuned** for many tasks by adding a small task-specific layer on top:
- **Single-input classification**: use the `[CLS]` token output vector in order to get a general feeling of the whole input and train a specific layer to distinguish sentiments for example
- **Two-input classification**: now we add another sentence after the `[SEP]` token, we can train a layer that can understand the relationship between these two sentences thanks to that token that separates them, and we can for example implement a model that detects if two sentences mean the same thing
- **Token labeling**: in this case we want to train a layer that labels each token of the input phrase (e.g. "person", "object", ...), since BERT outputs a rich vector for every token we can train a layer where we can distinguish between what token is what

### BERT as a re-ranker
One way to apply BERT to IR is as a **cross-encoder**, also called **monoBERT**, where a query and a document are concatenated as input:
$$\text{[CLS] }q_1,...q_m\text{ [SEP] }d_1,..., d_n\text{ [SEP]}$$

The `[CLS]` token's output embedding becomes a joint representation of the query-document pair, then we can add a small feed-forward layer on top of it produces a **relevance score**.

This is trained as a **binary classification task** (relevant vs not relevant) using cross-entropy loss on triples:
$$\text{(query, positive document, negative document)}$$

Cross-encoders are **computationally expensive** because the _query and document must be processed together_, we can't pre-compute document representations, therefore cross-encoders are used as a **second-stage re-ranker**, operating on a shortlist of candidates already retrieved by a faster first-stage system.

Because BERT is limited to an input size of $512$ tokens, long documents are split into **overlapping passages**, and each passage is scored independently alongside the query.
Then passage scores are _aggregated back to a document score_ using one of the many aggregation strategies, for example using the maximum score **MaxP** (where P stands for passage).

The dataset most commonly used for fine-tuning this setup is **MS MARCO**, a large IR dataset built from real search queries with labeled relevant passages.

### BERT for dense retrieval
Another use case is to use BERT as a **bi-encoder**, where instead of processing query and document together, two separate BERT instances independently encode them:
- $\phi(q)$ = Encoder(query) -> a single vector
- $\psi(d)$ = Encoder(document) -> a single vector
- $s(q, d)$ = $\phi(q)_{\text{[CLS}]}\cdot\psi(d)_{\text{[CLS]}}$

This is a [siamese network structure](https://en.wikipedia.org/wiki/Siamese_neural_network), meaning that two identical encoders share the same weights.
>Typically, the `[CLS]` token output is used as the representation, as noted in $s(q,d)$ above.

The advantage is that document embeddings can be **pre-computed and stored offline**, then at query time only the query needs to be encoded, then we search the index for the most similar document vectors, thus enabling **full-collection retrieval** (not just re-ranking).

>[!Info]
>Fine-tuning uses **contrastive loss**: for each query, the positive document's embedding is pulled closer to the query embedding, while negative documents' embeddings are pushed away.

These are even more expressive variants, such as:
- **Poly-encoders**: represent a document with the first $m$ output embeddings (not just `[CLS]`), computing similarity between the query vector and each of those m document vectors, then aggregating via softmax-weighted sum
- **ColBERT**: uses all output embeddings for both query and document, then the scoring uses _late interaction_, that is, for each query token, find the maximum similarity with any document token ($MaxSim$), then sum these $MaxSim$ values across all query tokens, this captures fine-grained token-level interactions while still allowing document pre-computation

### Dense retrieval architecture
We saw that it is possible to compute document embeddings offline, these will be stored in a vectorial database and at query time we have to find the top-k most similar documents, this is the **Maximum Inner Product (MIP)** search problem.

There are two main approaches to this:
- **Flat index**: compare the query vector against every document vector, exact but too slow for large collections (exhaustive search)
- **Approximate k-Nearest Neighbor**: accept a small loss in accuracy for a large gain in speed

The are many strategies for the latter approach:
- **Tree-based** (e.g. [ANNOY](https://github.com/spotify/annoy)): recursively partition the vector space into regions using random hyperplanes, then search only the most relevant partitions
- **Cluster-based** (e.g. [[04 - Approximate nearest neighbor search#Inverted file index with ADC|IVF]]): cluster document vectors using k-means, then for each cluster, store an inverted list of its document IDs, and at query time search only the closest $n$ cluster centroids (n-probe)
- **Hash-based** (e.g. [[14 - LSH|LSH]]): map vectors into hash buckets such that nearby vectors tend to land in the same bucket, then only compare within the same bucket
- **Graph-based** (e.g. [[04 - Approximate nearest neighbor search#Hierarchical navigable small worlds|HNSW]]): build a multi-layer graph where each node is a document vector and edges connect nearby ones, long-range edges are also added to create "small world" properties (short paths between any two nodes), search starts at the top (coarsest) layer and descends greedily to find the nearest neighbors at the bottom layer, with the number of nodes per layer decreasing exponentially

### Learned sparse retrieval
It is possible to combine the efficiency of [[01 - Boolean model#Inverted index|inverted indexs]] and the effectiveness of neural models.

The idea is to use neural networks to produce **sparse representations** (vectors that are mostly zero) so they can still be indexed in an inverted index, but the term weights are learned rather than hand-crafted.

There are three main approaches:
- **Document/query expansion**: use seq2seq models (e.g. transformers) to add relevant terms to a document or query that aren't literally present but are semantically relevant
- **Impact score learning**: transform a token's output embedding into a single scalar (its relevance weight in the document), this score is what gets stored in the inverted index
- **Sparse representation learning**: learn both expansion and impact scoring jointly end-to-end

