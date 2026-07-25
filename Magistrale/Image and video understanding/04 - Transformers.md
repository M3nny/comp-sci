RNNs are unrolled left-to-right, which bakes in a **linear locality** assumption, which means that _nearby words are assumed to interact more_, this becomes a problem when two distant words need $O(\text{sequence length})$ steps to interact.

**Linear interaction distance**
This makes _long-distance dependencies hard to learn_ (i.e. [[03 - Sequential models#Backpropagation through time|exploding/vanishing gradient]]) and forces the model to route information through many intermediate layers, even when the linear order isn't actually the right way to think about a sentence's structure.

**Lack of parallelizability**
Forward and backward passes in an RNN require $O(\text{sequence length})$ sequential, unparallelizable steps (can't compute the hidden state at position $5$  without first computing positions $1-4$), this limits training on large datasets.

### Self-attention
Attention treats each word's representation as a **query** to access and incorporate information from a set of **values**.

We've already seen [[03 - Sequential models#Additive attention|attention from the decoder to the encoder]], now we'll think about **attention within a single sentence**:
- The number of unparallelizable operations stays constant regardless of sequence length
- Maximum interaction distance is $O(1)$, every word can directly attend to every other word in a single layer

![[Attention within a sentence.png|500]]

We can think of attention as a **fuzzy version of a lookup table**.
A normal lookup table has keys mapped to values, and a query matches exactly one key, whilst in attention, a _query matches all keys softly_ (weights between $0$ and $1$), and the output is the weighted sum of all values.
![[Fuzzy lookup.png|400]]

Attention operates on:
- **Queries**: $q_1,...,q_T$, $q_i\in\mathbb R^d$
- **Keys**: $k_1,...,k_T$, $k_i\in\mathbb R^d$
- **Values**: $v_1,...,v_T$, $v_i\in\mathbb R^d$

In **self-attention** these are _drawn from the same source_, and the dot-product self-attention operation is described as:
$$\underbrace{e_{ij}=q_i^Tk_j}_\text{Key-query affinities}\quad \underbrace{\alpha_{ij}=\frac{\exp(e_{ij})}{\sum_{j'}\exp(e_{ij'})}}_\text{Attention weights from affinities (softmax)}\quad\underbrace{\text{output}_i=\sum_j\alpha_{ij}v_j}_\text{Outputs as weighted sum of values}$$

For example, let $x_{1:n}$ be a sequence of words in vocabulary $V$.
For each $w_i$, let $x_i=Ew_i$, where $E\in\mathbb R^{d\times |V|}$ is an _embedding matrix_.
1. **Transform** each word embedding with weight matrices $Q,K,V$ (each $\in\mathbb R^{d\times d})$
$$q_i=Q_{x_i}\quad k_i=Kx_i\quad v_i=Vx_i$$
2. **Compute pairwise similarities** between keys and queries and normalize with softmax
$$e_{ij}=q_i^Tk_j\qquad\alpha_{ij}=\frac{\exp(e_{ij})}{\sum_{j'}\exp(e_{ij'})}$$
3. **Compute the output** for each word as a weighted sum of values
$$o_i=\sum_j\alpha_{ij}v_i$$

![[Self-attention example.png]]

The output is given by the sum of the multiplications: $[2.0,7.0,1.5]$.

**Self-attention works on sets**, this means that it has many applications:
- image -> set (object detection / bounding boxes)
- set -> set (point clouds → bounding boxes, vehicle trajectory prediction)
- sequence -> sequence (translation, DALL-E-style conditional generation)
- sequence -> set (event localization/duration)
- image -> vector (Vision Transformer, ViT)
- sequence -> vector (e.g., movie review classification)

>[!Attention]
>Self-attention is not a drop-in replacement for recurrence (without applying a few fixes to it).

### Positional encoding
Self-attention is an operation on sets, **it has no inherent notion of order**.

The solution is to add **positional encodings** to the inputs before the first layer, so by considering $p_i\in\mathbb R^d$ ($i\in\{i,...,T\}$) as the _sequence index_ represented by a vector, we proceed as follows:
$$v_i=\tilde v_i+p_i\quad q_i=\tilde q_i+p_i\quad k_i=\tilde k_i+p_i$$
>Concatenation is possible instead of addition, but addition is what's typically done in practice.

There are two approaches to construction $p_i$, the first one is by using **sinusoidal position representations** (fixed, non-learned), it consists in concatenating sine/cosine functions of varying frequencies:
$$p_i=\begin{pmatrix}\sin(i/10000^{2\cdot 1/d}\\\cos(i/10000^{2\cdot 1/d}\\\vdots\\\sin(i/10000^{2\cdot \frac{d}{2}/d}\\\cos(i/10000^{2\cdot \frac{d}{2}/d}\end{pmatrix}$$
$i$ refers to the $i$-th dimension of the feature, $10,000$ is a user defined constant and $d$ is the dimension of the embedding space.

There are a few reason that justify this particular form:
- **Periodicity**: sine and cosine repeat, and this periodicity is useful for the later attention computation
- **Constrained values**: sine/cosine outputs are always in $[-1,1]$, so magnitudes stay controlled regardless of position
- **Extrapolation for long sequences**: the formula is fully deterministic (no learned parameters) and periodic, so in principle it could apply cleanly to sequences longer than any seen in training

Periodicity suggests absolute position may not matter much, and it seems like it should extrapolate, but _in practice extrapolation doesn't actually work well_, and being non-learnable is a real limitation.
![[Sinusoidal position representation.png|500]]

An alternative to this is to use **learned absolute position representations** by making every $p_i$ a learnable parameter, so learn a matrix $p\in\mathbb R^{d\times T}$ and let each $p_i$ be a column of that matrix.

This is _fully flexible_ since each position gets to be learned to fit the data, but we _can't extrapolate at all_ (outside $1,...,T$).
>Despite this limitation, this is what most systems actually use.

### Non linearities
Stacking self-attention layers on their own just re-averages value vectors over and over, there's no elementwise nonlinearity, so **depth alone doesn't buy us anything extra** (can't do deep learning with the current structure).

The solution is to **add a feed-forward network** after each self-attention block, applied independently to each position's output vector:
$$m_i=MLP(\text{output}_i)=W_2\cdot ReLU(W_1\times\text{output}_i+b_1)+b_2$$
![[FFN applied to self-attention block.png|400]]

The intuition is that the **FF network processes the result of attention**.

### Masking the future
To use self-attention in **decoders**, we need to ensure we can't peek at the future (e.g. in language modeling, where predicting token $i$ shouldn't have access to tokens $>i$).

Rather than inefficiently changing the set of keys/queries at every timestep, **mask out future positions** all at once by setting their attention scores to $-\infty$ before the softmax:
$$e_{ij}=\begin{cases}q_i^Tk_j,&j<i\\-\infty,&j\geq i\end{cases}$$
Since $\exp(\infty)=0$, softmax automatically zeroes out attention to future tokens.

### The transformer
The transformer is an **encoder-decoder** model that uses attention and has **no recurrence at all**, today it's used for essentially all of NLP (and well-beyond).
![[Transformer model architecture.png|300]]

#### Encoder
1. _Input embedding_: converts each token into a vector
2. _Positional embedding_: added to give the model order information
3. _Multi-head attention_:

Instead of one set of $Q,K,V$ matrices, use several, the motivation is that for word $i$, plain self-attention looks where $x_i^TQ^TKx_j$ is large, but **we might want to attend to different $j$ for different reasons simultaneously** (e.g. one head tracking entities and another tracking syntax).

Concretely a sentence gets split into $h$ heads, each with $Q_\ell,K_\ell,V_\ell\in\mathbb R^{d\times d/h}$, eahc head computes its own attention independently yielding:
$$\text{output}_\ell=softmax(XQ_\ell K_\ell^TX^T)XV_\ell$$
and all head outputs are concatenated and mixed with a final matrix $Y\in\mathbb R^{d\times d}$:
$$\text{output}=[\text{output}_1;...;\text{output}_h]Y$$
This costs about the **same total compute** as single-head attention over the full dimension, the heads just split $d$ into smaller chunks rather than adding extra work.
![[Magistrale/Image and video understanding/Images/Multi-head attention.png|500]]

4. _Scaled dot-product attention_: a refinement to stabilize training, since as dimensionality $d$ grows, raw dot products $q^Tk$ tend to get large in magnitude, which pushes softmax inputs into a regime with very small gradients

The fix it to divide the attention scores by $\sqrt{d/h}$ to stop the scores from becoming to large just as a function of $d/h$ (the dimensionality divided by the number of heads):
$$\text{output}_\ell=softmax\left(\frac{XQ_\ell K_\ell^TX^T}{\sqrt{d/h}}\right)\cdot XV_\ell$$

![[Multi-head attention summary.png|700]]

Now that we've replaced self-attention multi-head self-attention, we'll go through two **optimization tricks** that end up being:
- _Residual connections_: instead of each layer fully replacing its input $(X^{(i)}=Layer(X^{(i-1)})$) add the input back: $X^{(i)}=X^{(i-1)}+Layer(X^{(i-1)})$, so the layer only needs to learn the "residual" (the change from before), this is believed to make the loss landscape considerably smoother, which eases training
- _Layer normalization_: helps models train faster, by cutting down uninformative variation in hidden vector values

In this case we normalize each individual vector $x\in\mathbb R^d$ to zero mean, unit standard deviation, then apply a learned elementwise gain $\gamma$ and bias $\beta$ (these can technically be omitted), thus yielding:
$$\text{output}=\frac{x-\mu}{\sqrt\sigma+\epsilon}\cdot\gamma+\beta$$
>In most transformer diagrams, these are often written together as "Add & Norm".

![[Detailed transformer encoder.png|500]]

#### Decoder
The decoder is structurally similar to the encoder, but with two attention sub-blocks per layer instead of one.
![[Detailed transformer decoder.png|500]]

- **Masked multi-head self-attention**: attends only over previously generated decoder tokens, now extended to multiple heads simultaneously (each with its own score matrix)
- **Multi-head cross-attention**: this is where the decoder looks at the encoder's output, unlinke self-attention, keys and values come from the encoder's output (treated like a memory store: $k_i=Kh_i,v_i=Vh_i$ where $h_i$ are encoder outputs), while queries come from the decoder ($q_i=Qz_i$)

In matrix form:
$$\text{output}=softmax(ZQ(HK)^T)\times HV$$
giving $T\times  T$ matrix of decoder-to-encoder attention scores.

Each decoder block also has its own residual and layer norm around each sub-layer, plus a feed-forward layer, mirroring the encoder.
>Compared to previous seq2seq models, transformers require less training compute and are more efficient.

### Drawbacks
Computing all pairs of interactions means our **computation grows quadratically** with the sequence length, for recurrent models, it grew only linearly.

There are other **positional encodings** methods worth exploring, other than absolute indices:
- Relative linear position attention
- Dependency syntax-based position

