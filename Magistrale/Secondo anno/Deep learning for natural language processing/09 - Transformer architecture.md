An RNN processes tokens one after another, $h_t = f(x_t, h_{t-1})$, so each state must carry information forward.

A **transformer** layer instead _processes all positions at once_, and each token can directly retrieve information from any permitted position, the main consequence is that during training every position can be processed in parallel.
>The attention mask still blocks access to future tokens where needed.

### Overall architecture
The original model (Vaswani et al., 2017) is an **encoder–decoder**: the encoder represents the input, the decoder predicts the output.

1. **Input embeddings + positional encoding**: tokens become vectors that also carry position information
2. **Encoder stack** ($N$ layers): builds contextual representations of the source, every source position can attend to all other source positions
3. **Decoder embeddings + positional encoding**: same for the (right-shifted) target tokens
4. **Decoder stack** ($N$ layers): combines the target prefix with encoder information, masked self-attention prevents access to future target tokens
5. **Linear layer + softmax**: converts each decoder representation into vocabulary scores and then next-token probabilities

### Input representation and positional encoding
For the token at position $t$:
$$x_t = e_t + p_t, \qquad e_t, p_t \in \mathbb{R}^{d_{model}}$$
Self-attention has no built-in notion of order (it is permutation equivariant), so without $p_t$ it could not distinguish "the dog chased the cat" from "the cat chased the dog".

**Sinusoidal positional encoding** (original transformer, fixed and not learned):
$$p_t[2i] = \sin\!\left(\frac{t}{10000^{2i/d_{model}}}\right), \qquad p_t[2i+1] = \cos\!\left(\frac{t}{10000^{2i/d_{model}}}\right)$$

Each coordinate pair uses a different frequency: early dimensions (small $i$) oscillate rapidly with position, later ones change slowly, together they give every position a unique multi-scale "fingerprint".

**Why sine/cosine**
Periodicity at multiple scales; values bounded in $[-1,1]$; encodings can be computed for any position, even beyond training lengths, this allows longer inputs but does not guarantee good performance on them.

### Multi-head attention
One head gives one pattern of information retrieval, several heads learn several patterns in parallel, each in its own representation subspace.
$$\text{head}_r=\text{Attention}(XW^Q_r,\,XW^K_r,\,XW^V_r),\qquad \text{MHA}=\text{Concat}(\text{head}_1,\dots,\text{head}_h)\,W^O$$

Heads can pick up nearby context, long-distance dependencies, syntactic relations, or coreference, but the model assigns them no predefined roles.

### Position-wise feed-forward network (FFN)
$$\text{FFN}(h_t)=\text{ReLU}(h_tW_1+b_1)W_2+b_2$$
- **Expand**: $512\to2048$ (different learned feature combinations)
- **Activate**: ReLU element-wise. Without it, the two linear maps would collapse into a single affine map
- **Project back**: $2048\to512$, which keeps compatibility with the residual addition

The same FFN (shared parameters) is applied independently at every position, with no interaction across positions.
Each layer has its own FFN weights, in short: <u>attention exchanges information across positions; the FFN transforms features within each position</u>.

##### Why ReLU
$\text{ReLU}(z)=\max(0,z)$, tanh saturates for large $|z|$ (gradient $\to0$), while ReLU has gradient 1 for $z>0$.

**Limitations**
Sparse zero activations, "dying ReLU" (persistently negative inputs give zero gradient and learning stops), unbounded positive outputs, and the derivative at 0 is set to 0 by convention.

### Residual connections and layer normalization
**Residual connection**: $\text{Output}=h_t+\text{Sublayer}(h_t)$.
The vectors must have the same dimension (this is why sublayers return to $d_{model}$).  

**Benefits**:
- The sublayer supplements the input instead of replacing it
- Gradient flow: along the identity path the derivative is 1, so gradients bypass the sublayer and avoid vanishing in deep models
- Each sublayer can learn a small modification of its input

**Layer normalization** (per token, across its features):
$$\text{LayerNorm}(x)=\gamma\odot\frac{x-\mu}{\sqrt{\sigma^2+\varepsilon}}+\beta$$
Here $\mu,\sigma^2$ are the mean and variance over the features of one token, $\gamma,\beta$ are learnable scale and shift, and $\varepsilon$ avoids division by zero.

**Arrangements:**
- _Post-norm_ (original transformer): $y=\text{LayerNorm}(x+\text{Sublayer}(x))$
- _Pre-norm_ (common in modern LLMs): $y=x+\text{Sublayer}(\text{LayerNorm}(x))$, it generally makes very deep transformers easier to optimize

### The encoder
Initial representation $H^{(0)}=E_{source}+P$. Each layer (pre-norm variant):
$$A^\ell=H^\ell+\text{MHA}(\text{LayerNorm}(H^\ell)),\qquad H^{\ell+1}=A^\ell+\text{FFN}(\text{LayerNorm}(A^\ell))$$
Layers have the same structure but **different parameters**, and Q, K, V are recomputed from each layer's input.

Representations keep shape $[n\times d_{model}]$ throughout, there is no causal restriction (only padding is masked), the final output $H_{enc}$ is passed to the decoder's cross-attention.

### The decoder
**Input (teacher forcing and right shift)**: the decoder input is the target shifted right, starting with `<BOS>`, the prediction target is the next token:

|Pos|Decoder input|Target|
|---|---|---|
|1|`<BOS>`|Il|
|2|Il|gatto|
|3|gatto|dorme|
|4|dorme|`<EOS>`|

$S^{(0)}=E_{target}+P$.

**Each decoder layer** has three sublayers (pre-norm):
1. _Masked (causal) self-attention_: $A^{(\ell)}=S^{(\ell)}+\text{MaskedMHA}(\text{LayerNorm}(S^{(\ell)}))$, the causal mask $M$ is lower-triangular, with 0 for current and previous positions and $-\infty$ for future ones, for example, the position receiving "Il" sees `<BOS>` and "Il" and predicts "gatto"
2. _Cross-attention_: $B^{(\ell)}=A^{(\ell)}+\text{CrossMHA}(\text{LayerNorm}(A^{(\ell)}),H_{enc})$
    - Queries come from the decoder: $Q=SW^Q$
    - Keys and values come from the encoder: $K=H_{enc}W^K,\ V=H_{enc}W^V$
    - Attention matrix shape is $[m\times n]$ ($m$ target tokens, $n$ source tokens), padding in the source is masked
3. _FFN_: $S^{(\ell+1)}=B^{(\ell)}+\text{FFN}(\text{LayerNorm}(B^{(\ell)}))$

Each decoder layer has its own cross-attention parameters but consults the same $H_{enc}$

**Output layer**:
$$z_t=s_tW_{vocab}+b_{vocab},\qquad p_t=\text{softmax}(z_t)$$
where $W_{vocab}$ has shape $[d_{model}\times|V_{target}|]$.

### Training vs. generation
**Training**
One forward pass computes all position-wise predictions in parallel, using the gold target prefix (teacher forcing) and causal masking.

**Loss**
$L=\sum_t L_t$ with $L_t=-\ln p_t[y_t]$ (cross-entropy), in practice the loss is averaged over valid target tokens and padding is excluded.
Backpropagation combines the gradients from all token losses.

**Generation**
Select a token, append it to the decoder input, and repeat.
This is inherently sequential, because each token depends on the previous output.

### What depth does
Each layer builds on the previous one's contextual representations, and every layer can access the full permitted context.

For "bank" in "The bank approved the loan":
- **Early layers** encode token identity, position and nearby lexical patterns
- **Later layers** integrate the relation between bank, approved and loan, plus sentence-level grammar and evidence for the financial sense

>[!Info] Probing findings (BERT)
>Earlier layers tend to encode part of speech, phrase and dependency structure; later layers integrate semantic roles and coreference.
>>Entity information is more distributed.
>
>This is only an average tendency, not a rigid one-task-per-layer pipeline.
Probing shows what information is _recoverable_, not necessarily how the model _uses_ it.

### KV cache
During generation, keys and values of previous tokens don't change, so they are stored:
1. Compute for the new token: $q_t=h_tW^Q,\ k_t=h_tW^K,\ v_t=h_tW^V$
2. Append: $K_{cache}\leftarrow[K_{cache};k_t],\ V_{cache}\leftarrow[V_{cache};v_t]$
3. Attend: $\alpha_t=\text{softmax}\!\left(q_tK_{cache}^\top/\sqrt{d_k}\right)$, output $=\alpha_tV_{cache}$

- **Benefit**: avoids recomputing projections for earlier positions through all layers
- **Costs**: the new query still compares against all stored keys, and cache memory grows linearly with sequence length, in every layer

#### Computational bottlenecks
The attention score matrix is $T\times T$, so attention costs $O(T^2)$.

Main limitations:
- Quadratic attention cost in training
- Growing KV-cache memory in inference
- Sequential autoregressive generation
- Finite context window

These motivate research on _efficient attention_, longer-context models, and alternative sequence architectures.

##### Summary
1. **Why positional information?** Self-attention is order-agnostic, so word order must be injected explicitly
2. **Why is training parallel but generation sequential?** In training the full gold target is known (teacher forcing), and the causal mask enforces the prefix restriction, so all positions are predicted at once, while in generation, each token depends on the previously generated one
3. **Roles of attention vs FFN?** Attention mixes information across positions, the FFN transforms the features of each position independently
4. **What does the KV cache store?** The keys and values of all previously processed tokens (per layer)
5. **Why must residual inputs and outputs have the same dimension?** The addition $h+\text{Sublayer}(h)$ is element-wise, so both vectors need the same number of components (hence the FFN returns to $d_{model}$)

