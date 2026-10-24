We recall that **language modeling** means estimating the distribution of the next token given the preceding context, where the _training target_ is the word that actually follows.

[[04 - N-gram language modeling|n-gram models]] estimate probabilities by **MLE**, using relative frequencies:
$$P(w_j \mid \text{history}) = \frac{C(\text{history}, w_j)}{C(\text{history})}$$
We recall also that this leads to **sparsity problems**:
1. _Zero probability_: if "students opened their $w_j$" never occurred in training, then $p = 0$
2. _Zero context_: if "students opened their" never occurred, the denominator is 0 and the estimate is undefined
3. _No parameter sharing_: "students opened their", "pupils opened their" and "scholars opened their" are treated as unrelated, learning about one tells the model nothing about the others

A partial fix to OOV was [[04 - N-gram language modeling#Out-of-vocabulary words|smoothing]], but we can do better.

The **motivation for neural models** is to share information across semantically similar contexts by using continuous, dense word representations (embeddings).

### Architecture of the neural probabilistic LM
The key idea is to **jointly learn** the word representations and the language model parameters from the same next-word prediction objective.

The architecture has the following three steps.

**Embedding lookup and concatenation**
A shared embedding matrix maps each vocabulary word to a dense trainable vector:
$$C \in \mathbb{R}^{|V| \times D}, \qquad e_i = C[w_i] \in \mathbb{R}^{D}$$
Each row of $C$ is one word's embedding, words are identified by integer IDs, so the lookup is just picking a row.

The _context embeddings are then concatenated_:
$$x_t = [e_{t-n+1}; \dots; e_{t-1}] \in \mathbb{R}^{(n-1)D}$$
>For a 4-gram model (3 context words, $D = 100$): $x_t \in \mathbb{R}^{300}$.

_Why concatenate rather than average?_
Concatenation preserves _word order_, for example "dog bites man" and "man bites dog" use the same word vectors but produce different $x_t$, averaging would make them identical (bag-of-words).
>The cost is that dimensionality grows linearly with the window size.

**Hidden layer**
$$h = \tanh(H x_t + b_1)$$

|Symbol|Shape|Meaning|
|---|---|---|
|$H$|$[M \times cD]$|weights combining context features into $M$ hidden units|
|$b_1$|$[M \times 1]$|hidden bias|
|$h$|$[M \times 1]$|hidden state|

**Output layer and softmax**
$$a = U h + W x_t + b_2, \qquad p = \text{softmax}(a)$$

| Symbol | Shape                        | Meaning                                         |
| ------ | ---------------------------- | ----------------------------------------------- |
| $U$    | $[\lvert V\rvert \times M]$  | maps hidden state to vocabulary scores          |
| $W$    | $[\lvert V\rvert \times cD]$ | optional direct connection from input to output |
| $b_2$  | $[\lvert V\rvert \times 1]$  | output bias                                     |
| $a$    | $[\lvert V\rvert \times 1]$  | logits (unnormalized scores)                    |
| $p$    | $[\lvert V\rvert \times 1]$  | next-word probabilities                         |

The _softmax_ function is defined as:
$$P(w_t = j \mid \text{context}) = \frac{\exp(a_j)}{\sum_{k=1}^{|V|} \exp(a_k)}$$
Its properties are:
- _Normalization_: outputs are positive and sum to 1
- _Monotonic ranking_: a higher logit always means a higher probability
- _Differentiable_: gradients flow end-to-end
- _Prediction_: pick the word with argmax (greedy decoding) or sample from the distribution

#### Tanh activation
$$\tanh(z) = \frac{e^z - e^{-z}}{e^z + e^{-z}}$$
It is applied **element-wise**, so the vector shape is preserved.

A **nonlinearity is needed** since without it, the two linear stages collapse into one:
$$U(Hx_t + b_1) + Wx_t + b_2 = (UH + W)x_t + Ub_1 + b_2$$
That is just a single linear map, so the hidden layer would add no expressive power. Tanh lets the network learn feature interactions beyond a linear transformation.

**Derivative and its drawback**:
$$\frac{d \tanh(z)}{dz} = 1 - \tanh^2(z)$$
- It is _maximal_ (equal to 1) at $z = 0$, where tanh is approximately linear
- In _saturated_ regions (large $|z|$), the derivative approaches 0, thus causing vanishing gradients and slows learning

### Training
All parameters $\theta = \{C, H, b_1, U, b_2, W\}$ are learned **jointly and end-to-end** by backpropagation from one objective.

The **loss function** is the _negative log-likelihood_ (multiclass cross-entropy):
$$J(\theta) = -\frac{1}{N}\sum_t \log P_\theta(w_t \mid \text{context}_t)$$

The **update rule** is simply the _gradient descent_:
$$\theta \leftarrow \theta - \eta \nabla_\theta L$$
where $\eta$ is the learning rate.

#### Backpropagation, step by step
Here we discuss the backpropagation for neural LMs step by step.

**Output error**
With $y$ the one-hot target vector:
$$\delta = \frac{\partial L}{\partial a} = p - y$$

The correct word’s logit gets a _negative gradient_ (raising it lowers the loss), and all other words get _positive gradients_ (lowering them lowers the loss).

Even though the loss only looks at the target word’s probability, softmax couples all outputs, so _every logit receives a gradient_.

**Output-layer parameter gradients** (outer products)
$$\frac{\partial L}{\partial U} = \delta\, h^\top, \qquad \frac{\partial L}{\partial W} = \delta\, x_t^\top, \qquad \frac{\partial L}{\partial b_2} = \delta$$
**Gradient passed to the hidden layer**
$$\frac{\partial L}{\partial h} = U^\top \delta$$
**Through tanh** (element-wise product $\odot$)
$$g = \frac{\partial L}{\partial z} = (U^\top \delta) \odot (1 - h^2)$$

For one hidden unit, $0.40 \times 0.75 = 0.30$, the factor $(1-h^2)$ scales down the incoming error.
>If a unit is saturated ($|h| \approx 1$), then $1 - h^2 \approx 0$ and the error signal nearly vanishes.

**Hidden-layer parameter gradients**
$$\frac{\partial L}{\partial H} = g\, x_t^\top, \qquad \frac{\partial L}{\partial b_1} = g$$
**Gradient to the embeddings**
Two paths combine at $x_t$, the hidden path and the direct path:
$$\frac{\partial L}{\partial x_t} = H^\top g + W^\top \delta$$

This vector is split into blocks matching the concatenation, $[\partial L/\partial e_1;\ \partial L/\partial e_2;\ \partial L/\partial e_3]$. 

Each block updates the corresponding row of $C$.
If a word appears more than once in the context, _its contributions accumulate_ in the same row.
>Only the rows of words actually in the context are updated at that step.

**Update**
Compute all gradients first, then update $C, H, U, b_1, b_2, W$ simultaneously.

##### Backpropagation enables generalization
this enables generalization because **the network is shared**, contexts like "the cat is" and "the dog is" lead to similar predictions, which _pulls $C[\text{cat}]$ and $C[\text{dog}]$ closer together_.

The model therefore learns both **how to represent words** and **how to use those representations**, and what it learns about one word transfers to similar words.
>This is the core idea behind modern word embeddings.

### Fixed-window neural LM vs n-gram
**Improvements over n-gram models**:
- _No sparsity problem_: unseen n-grams still get sensible probabilities because words live in a dense continuous space
- _Parameters scale as $O(n)$_: with context size, instead of exponentially, $O(\exp(n))$
- _Generalization_: similar words and contexts share statistical strength

**Remaining limitations**
- _The window is too small_ and can never be made large enough for long-range dependencies.
- _Enlarging the window enlarges $W$_ (and $H$), so parameters inflate
- _No weight sharing across positions_: each position uses different columns of the weight matrix, so what is learned about a word at one position is not reused at another

The main point is that we need an architecture that can **process inputs of any length**, which motivates recurrent and other flexible models.
