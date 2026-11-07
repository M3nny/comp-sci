The two models studied so far both rely on a **bounded local context**.

|             | Bengio neural LM                                                                                  | Word2Vec                                                                                |
| ----------- | ------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------- |
| Input       | The previous $n-1$ words                                                                          | Words in a window around the target                                                     |
| Limitations | Tokens outside the window cannot influence the prediction (a bigger window means more parameters) | Only local context is used, CBOW treats the context as a bag of words, so order is lost |

Both learn distributed word representations, but _neither models an evolving sequence**.

**The RNN idea**: replace the explicit window with a _hidden state_ $h_t$ that is updated as the sequence is read one token at a time:
$$h_t = f(x_t,\, h_{t-1})$$

Its **advantages** are:
- _Flexible context length_: in principle the whole preceding sequence can influence the current step
- _Shared parameters_: the same transformation is applied at every position
- _Persistent state_: $h_t$ is a compact summary of everything seen so far, $x_1,\dots,x_t \rightarrow h_t$

An RNN is defined by a **connection through time**, which means that the computation at step $t$ depends on an output from an earlier step, this can be viewed as the network's form of **memory**. 

### The vanilla RNN computation
$$h_t = \tanh(W_e x_t + W_h h_{t-1} + b_h)$$ $$z_t = W_2 h_t + b_y, \qquad \hat y_t = \text{softmax}(z_t)$$

| Parameter   | Connection                        | Role                                                                               |
| ----------- | --------------------------------- | ---------------------------------------------------------------------------------- |
| $W_e$       | input -> hidden                   | Transforms the current input $x_t$ (for a language model it is the word embedding) |
| $W_h$       | previous hidden -> current hidden | Carries information through time (the temporal component)                          |
| $W_2$       | hidden -> output                  | Produces the logits $z_t$                                                          |
| $b_h,\ b_y$ | biases                            |                                                                                    |

$\hat y_t$ is the **predicted** distribution over the vocabulary, and $y_t$ is reserved for the true one-hot **target**.

$h_0$ is usually a zero vector (empty memory), some models learn it as a parameter.

**Unrolling through time**
Drawing the network once per time step shows a chain $x_1\to h_1\to x_2\to h_2\to\dots$
The same $W_e, W_h, W_2$ are **reused at every step**, this gives:
- Natural handling of _variable-length sequences_
- The _same transformation_ at every position,
- _Position invariance_: a pattern is learned regardless of where in the sequence it occurs
- _Parameter count does not grow with sequence length_, unlike the fixed-window model, where it grows with the window

**In theory**, by recursion, $h_t = F_\theta(x_1,\dots,x_t,h_0)$: _any earlier position can influence_ the current prediction, with no explicit context limit.

**In practice**, the entire history is repeatedly compressed into a fixed-dimensional vector, _earlier information gets overwritten or distorted_, so the effective memory can be much shorter than the theoretical one.

>[!Example]
>"The _keys_ to the old wooden cabinet near the window _are_ missing."
>
>To predict _are_, the model must keep the plural number of _keys_ across several intervening singular nouns, learning this is hard for a vanilla RNN.

#### RNN language model
![[RNN language model.png|484]]
Using an RNN for language modeling consists in the following **pipeline**:
1. Words are mapped to _embeddings_ $c_1,\dots,c_4$
2. Hidden states are computed recursively, $h^{(t)} = f(W_h h^{(t-1)} + W_e c_t)$, starting from $h^{(0)}$
3. At each step, the hidden state gives an output distribution $\hat y = \text{softmax}(W_2 h^{(t)})$ over the next word (e.g. "books", "laptops" get high probability after "the students opened their").

At every step the model predicts the next token, and the negative log-likelihood of the correct token is the **loss**, for the sequence `Students -> opened -> their -> books` it is:
$$L_2 = -\log P(\text{opened}\mid\text{Students}),\quad L_3 = -\log P(\text{their}\mid\text{Students opened}),\quad L_4 = -\log P(\text{books}\mid\text{Students opened their})$$

Losses from different time steps are **added**:
$$L = -\sum_t \log P(x_{t+1}\mid x_{1:t})$$

### BackPropagation Through Time (BPTT)
Training treats the **unrolled RNN as a very deep network** whose _"layers" are time steps_.

The gradient travels backward through every intermediate state, and because parameters are shared, <u>gradients from all time steps are summed</u> for each shared matrix.

For two states $k$ steps apart, the gradient contains $k$ **chained factors**:
$$\frac{\partial h_t}{\partial h_{t-k}} = \frac{\partial h_t}{\partial h_{t-1}}\cdot\frac{\partial h_{t-1}}{\partial h_{t-2}}\cdots\frac{\partial h_{t-k+1}}{\partial h_{t-k}}$$

##### Vanishing gradients
If each factor has **magnitude below 1**, the signal shrinks exponentially:
$$0.5^1 = 0.5,\qquad 0.5^5\approx 0.031,\qquad 0.5^{20}\approx 10^{-6}$$
By the time the gradient reaches an early input it is too small **to produce a meaningful update**.

The consequence is that **short-range patterns are learned much more easily** than long-range ones, the network has access to the full sequence in theory but _cannot learn how distant information affects the output_.

##### Exploding gradients
If each factor has **magnitude above 1**, the gradient grows exponentially:
$$1.5^1 = 1.5,\qquad 1.5^5\approx 7.6,\qquad 1.5^{20}\approx 3{,}325$$
Updates become huge, **training is unstable**, the loss fluctuates wildly, and parameters can become `NaN`.

A fix to this is **gradient clipping** which _rescales the gradient_ when its global norm exceeds a threshold.
>It does not fix vanishing gradients or give the network better long-term memory.

### Gated RNNs
<u>Vanilla RNNs rewrite the entire hidden state at every step</u> and have little control over what to preserve, overwrite or forget.

**LSTMs** and **GRUs** add **gates**:
$$g_t = \sigma\!\big(W_{ge}\,x_t + W_{gh}\,h_{t-1} + b_g\big)\in(0,1)^d$$

The gate scales information element-wise, $g_t\odot h_{t-1}$:

|Gate value|Effect|
|---|---|
|0|Block / discard|
|0.5|Partially pass / regulate|
|1|Pass through / preserve|

**Gates are learned and differentiable**, which gives selective retention, selective updating, selective forgetting, and, importantly, **better gradient flow** for long-range dependencies.

#### GRU (Gated Recurrent Unit)
$$r_t = \sigma(W_{er}x_t + W_{hr}h_{t-1} + b_r)\quad\text{(reset gate)}$$
Controls **how much of the old state is used** to build the candidate, it is near 0 it suppresses the old state, near 1 it passes it through.
$$u_t = \sigma(W_{eu}x_t + W_{hu}h_{t-1} + b_u)\quad\text{(update gate)}$$
**Blends old state and candidate** per component, it is near 1 it mostly preserves the old value, near 0 it mostly uses the candidate.
$$\tilde h_t = \tanh\!\big(W_e x_t + W_h(r_t\odot h_{t-1}) + b_h\big)\quad\text{(candidate)}$$ $$h_t = u_t\odot h_{t-1} + (1-u_t)\odot\tilde h_t$$
>The GRU can keep some components untouched while updating others.


#### LSTM (Long Short-Term Memory)
This architecture presents two recurrent states:
- **Cell state $c_t$**: stored long-term information, carried through time with gated writing
- **Hidden state $h_t$**: a gated, transformed view of the memory, used for prediction and the next step

At each step there are three decisions:
- **Forget**: how much old memory stays
- **Write**: how much new information enters
- **Expose**: how much memory reaches the hidden state

$$f_t = \sigma(W_{ef}x_t + W_{hf}h_{t-1} + b_f)\quad\text{(forget gate)}$$ $$i_t = \sigma(W_{ei}x_t + W_{hi}h_{t-1} + b_i)\quad\text{(input gate)}$$ $$o_t = \sigma(W_{eo}x_t + W_{ho}h_{t-1} + b_o)\quad\text{(output gate)}$$ $$\tilde c_t = \tanh(W_{ec}x_t + W_{hc}h_{t-1} + b_c)\quad\text{(candidate memory)}$$ $$c_t = f_t\odot c_{t-1} + i_t\odot\tilde c_t$$ $$h_t = o_t\odot\tanh(c_t)$$

![[LSTM architecture.png|622]]

### Encoder-decoder models
Many tasks map one sequence to another of a **different length** (e.g. translation), doing this requires _two conceptually different operations_, so they are split into two roles:
$$\text{Input sequence}\ \rightarrow\ \textbf{Encoder}\ \rightarrow\ \text{Representation}\ \rightarrow\ \textbf{Decoder}\ \rightarrow\ \text{Output sequence}$$
- **Encoder**: reads and compresses the input $x_1,\dots,x_n$ into a representation
- **Decoder**: uses that representation to generate the target $y_1,\dots,y_m$ one token at a time

**How the decoder generates**
1. _Initialize from the encoder_: $s_0 = h_n$
2. _Update state_ from the previous state and the embedding of the previous token: $s_t = \text{DecoderRNN}\big(s_{t-1},\, e(y_{t-1})\big)$, the first input is the BOS (beginning-of-sequence) token
3. _Predict_: $z_t = W_o s_t + b_o$, $p_t = \text{softmax}(z_t)$, a token is selected from $p_t$ and fed to the next step, until EOS (end of sequence) or a length limit


**Training vs generation**:
- _Training_: the gold previous token is fed to the decoder
- _Generation_: the decoder's own previously generated token is fed
>The decoder's state evolves over time, while the encoder's stored states stay unchanged.


### The information bottleneck and the motivation for attention
In the original architecture the decoder sees the input **only through $h_n$**:
- An input of arbitrary length $x_1,\dots,x_n$ is _compressed_ into one fixed-size vector $h_n\in\mathbb R^d$
- $h_n$ _must hold the overall meaning_, important words and entities, word order and relations, and the details needed at every output step
- _Early tokens must survive many recurrent updates_ before reaching $h_n$, and the longer the input, the harder this gets

**Different output words need different source words**
A _standard encoder–decoder_ makes every decoding step retrieve this from the _same vector_, with no direct access to individual source states.

>[!Example]
>"The student who submitted the assignment yesterday passed the exam"
>Is translated to:
>
>"Lo studente che ha consegnato il compito ieri ha superato l’esame"
>
>"studente" needs "student", "compito" needs "assignment", and "ieri" needs "yesterday". 


An important observation is that the encoder already produces a state for each input position, $h_1,\dots,h_n$, but **all except $h_n$ are discarded**.

A **better mechanism** would:
1. Retain all encoder states
2. Identify the ones relevant to the current output
3. Combine them into a task-specific _context_ for the next prediction

That is **attention**, which can be seen as:
$$\text{current decoder state}\to\text{select relevant encoder states}\to\text{build a context for the next prediction}$$

Each output step gets **selective access to the whole encoded input**.

