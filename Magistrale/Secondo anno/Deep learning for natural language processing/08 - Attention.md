In a basic [[07 - Encoder-decoder model#Encoder-decoder models|encoder-decoder model]], the encoder produces one hidden state per input word, $h_1,\dots,h_n$, but only the last one is passed to the decoder ($s_0 = h_n$).
The whole input must be squeezed into one fixed vector, this is the **fixed-context bottleneck**: anything the decoder needs later must survive inside its recurrent state.

**Attention's idea**: keep all encoder states and let the decoder, at every output step, select the relevant ones and combine them into a step-specific context vector $r_t$.
The context always has the same dimensionality, but its content changes from step to step.

### Soft attention as a weighted reading
For each output word, the model assigns a weight to every input position and takes a weighted average of the encoder states:
$$r_t = \sum_{j=1}^{n} \alpha_{tj}\, h_j$$

### Additive attention
At each decoding step $t$:

**Compare** the previous decoder state $s_{t-1}$ with every encoder state $h_j$:
$$\text{features}_{tj} = \tanh(W_a s_{t-1} + U_a h_j + b_a)$$The same parameters are used for all encoder positions.

**Score**: a learned vector $w_{score}$ turns each feature vector into a scalar:
$$\text{score}_{tj} = w_{score}^\top\, \text{features}_{tj}$$
The vector $w_{score}$ learns which features matter. In the slide's example, with features $[0.8,0.1]$ and $[0.2,0.9]$, choosing $w=[2,0]$ gives scores $1.6$ and $0.4$, while $w=[0,2]$ gives $0.2$ and $1.8$, so the ranking flips.

**Normalize** with softmax over source positions:
$$\alpha_{tj} = \frac{\exp(\text{score}_{tj})}{\sum_{k=1}^{n}\exp(\text{score}_{tk})}, \qquad \sum_j \alpha_{tj}=1$$
Weights are positive and sum to one.
The softmax is over _source positions_, not the vocabulary, for padded batches, padding positions must be masked before the softmax.

**Build the context**: $r_t=\sum_j \alpha_{tj}h_j$.

**From context to next word**:
- State update: $s_t = \text{DecoderRNN}(s_{t-1}, \text{embed}(y_{t-1}), r_t)$
- Vocabulary scores: $z_t = W_s s_t + W_r r_t + b$
- Prediction: $p_t = \text{softmax}(z_t)$, and with greedy decoding $y_t = \arg\max p_t$, fed to the next step

**Training**: loss $L = -\sum_t \log P(y_t \mid y_{<t}, \text{input})$, encoder, decoder and attention are trained jointly by backpropagation, with no alignment labels needed.
>The RNNs still process sequences sequentially.

### Self-attention

#### Query, Key, Value
Each token plays three roles:
- **Query**: what this position is looking for
- **Key**: what makes it relevant to others (used for matching)
- **Value**: the information it contributes

Web-search analogy:
- Query = search request
- Key = page title
- Value = page content

In earlier encoder–decoder attention, the same vector served as both key and value, now they are separate learned views.

For a token vector $x_i$ (written as a row):
$$q_i = x_iW^Q,\quad k_i = x_iW^K,\quad v_i = x_iW^V$$
The same three matrices are shared across all positions. In matrix form, with $X\in\mathbb{R}^{n\times d}$ (tokens stacked as rows): $Q=XW^Q,\ K=XW^K,\ V=XW^V$.

#### Computing attention
1. **Scores** via dot products between a token's query and all keys, large dot product means strong compatibility
2. **Scaling**: $s_{ij} = \dfrac{q_i\cdot k_j}{\sqrt{d_k}}$. Without scaling, dot products grow with dimension, pushing softmax into saturated regions with tiny gradients, dividing by $\sqrt{d_k}$ keeps magnitudes manageable and stabilizes training
3. **Softmax** row-wise: $\alpha_{ij}=\dfrac{\exp(s_{ij})}{\sum_k \exp(s_{ik})}$, with an optional mask applied before it
4. **Weighted sum of values**: e.g. $h_3 = 0.18v_1+0.40v_2+0.08v_3+0.34v_4$

**Whole operation in matrix form:**
$$\text{Attention}(Q,K,V)=\text{softmax}\!\left(\frac{QK^\top}{\sqrt{d_k}}+M\right)V$$
where $M$ is an optional mask (0 for allowed positions, $-\infty$ for blocked ones).
Each row of the output $H=AV$ is the contextual vector of one token, and all tokens are _computed in parallel_.

**Contextual representations**: the output for "their" differs in "students opened their books", "companies published their results", and "trees lost their leaves".
>Unlike static embeddings, the representation adapts to context.

The **general model** is composed by four modular steps:
- _Compatibility_: $e=f(q,K)$
- _Distribution_: $a=g(e)$
- _Weighting_: $z_i=a_iv_i$
- _Aggregation_: $c=\sum_i z_i$

### Types of attention

|Type|Queries from|Keys/Values from|Visibility|
|---|---|---|---|
|**Cross-attention** (encoder–decoder)|decoder|encoder|decoder queries the source|
|**Bidirectional self-attention**|same sequence|same sequence|all positions (typical in encoders)|
|**Causal self-attention**|same sequence|same sequence|only current and previous positions (language models)|

- **Self vs cross** is defined by _where Q, K, V come from_.
- **Bidirectional vs causal** is defined by _which positions are visible_ (implemented via masking).

**Causal masking**: future scores are set to $-\infty$ before the softmax, so their weights become exactly 0 ($e^{-\infty}=0$).
The mask is a triangular matrix: 0 on and below the diagonal, $-\infty$ above, this enforces left-to-right, autoregressive generation.

### Why self-attention replaced recurrence
**Advantages**
- _Direct access_: any position can combine information from any other permitted position, with no single-vector bottleneck
- _Parallelism_: all positions are computed at once, while an RNN must compute $h_1$ before $h_2$ before $h_3$

**Costs**
- _Quadratic complexity_: the $n\times n$ attention matrix costs $O(n^2)$ memory
- _No built-in word order_: permutation-invariant
- _Interpretability limits_: attention weights show information flow but are not necessarily faithful explanations

Self-attention is **permutation-invariant**: without position signals, "dog bites man" and "man bites dog" yield the same set of pairwise comparisons (just reordered). 

The common fix is to add a positional embedding to each token embedding:
$$x_i = \text{token\_embedding}_i + \text{position\_embedding}_i$$
so the same word receives different vectors at different positions.

### Multi-head attention
A single head gives one attention distribution, that is: one weighted view of the sequence.
A token like "student" in "The student who submitted the assignment passed" may need several relationships at once (the verb, the clause, nearby modifiers).

**Multi-head attention** runs several attention operations in parallel, each with its own projections:
$$Q_r=XW^Q_r,\ K_r=XW^K_r,\ V_r=XW^V_r,\qquad \text{head}_r=\text{softmax}\!\left(\frac{Q_rK_r^\top}{\sqrt{d_k}}+M\right)V_r$$
Then the heads are concatenated and mixed:
$$H=\text{Concat}(\text{head}_1,\dots,\text{head}_h),\qquad \text{Output}=HW^O$$
**Shapes** (model dim 512, 8 heads, so $d_k=d_v=512/8=64$):
- Each head: $[n\times512]\times[512\times64]=[n\times64]$
- Attention weights per head: $[n\times n]$
- Concatenation: $[n\times(8\cdot64)]=[n\times512]$
- Output: $[n\times512]\times[512\times512]=[n\times512]$

Each head sees the _full input_ (not a slice of it) and learns its own projection.
>$W^O$ mixes information across heads and restores the model width.

### Applications and what heads learn
**Machine translation (cross-attention)**: attention builds a position-specific context at each decoding step, supporting flexible source–target alignment even when word order changes (e.g. "black cat" -> "gatto nero").

**What heads attend to (BERT analyses)**:
- _Positional_: previous, next or current token
- _Special tokens_: \[CLS\] and \[SEP\], acting like a global memory or "no-op"
- _Linguistic_: noun–determiner, verb–object, preposition–object, coreferent mentions
>Not every head has a clear linguistic function.

In GPT-2, attention patterns for coreference (e.g. "She"/"He" linked to occupations or names) suggest the model may encode gender bias.

**Specialization and redundancy**: some heads are specialized and interpretable, many are redundant, heads give capacity during training, but many are not needed at inference, which enables pruning.

##### Summary
- Attention scores queries against keys, normalizes with softmax, and uses the weights to average values
- Multi-head attention does this in several learned subspaces at once
- It supports generation, classification and contextual token representations
- Some heads correlate with positional or linguistic patterns, but many are redundant
- Attention weights describe internal information flow and are not causal explanations