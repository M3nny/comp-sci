Most real-world data such as: video, text, time series and audio has **order that carries meaning**, which a plain feedforward/CNN can't exploit since it treats each input independently.

A **sequence model** is based on a _feedback loop_, this motivates a model whose current output depends on both the current input and a running summary of everything seen before (i.e. _recurrent connection_).

These types of model are used to:
- Deal with **variable length sequences**
- Maintain **sequence order**
- Keep track of **long-term dependencies**
- **Share parameters** across the sequence

These **Recurrent Neural Networks (RNNs)** have multiple use cases.
![[RNN in-out.png|600]]
- **One-to-one**: ordinary image classification (no sequence at all)
- **One-to-many**: image captioning (image in, sequence of words out)
- **Many-to-one**: sentiment analysis (sequence of words in, single class out)
- **Many-to-many (delayed)**: machine translation (a whole input sequence read before output starts)
- **Many-to-many (synced)**: action/event recognition (a label produced at every input frame)

### Recurrent neural networks
Ignoring (for simplicity) any classification/regression layers on top of the RNN's output, we can represent the basic version of a RNN as follows:

![[RNN internals.png|500]]

The **output** will then be produced by some function $F(h_t)$ which can be:
- Linear layer
- MLP
- Another RNN layer
- Whatever can be used to compute a loss $C_t$ at each step $t$

$$A_t=\theta_cA_{t-1}+\theta_xx_t\qquad h_t=\theta_hA_t$$
- $A_{t-1}$: hidden state at time $t-1$
- $x_t$: input at time $t$
- $\theta_{c,x,h}$: network parameters, $x$ stands for input, $c$ stands for cell state, $h$ stands for output

Note that the **network parameters are not depending on $t$**, this is to account for variable length sequences.

The same **weight matrices are reused** at every timestep, this is what lets the networks handle variable-length sequences and keeps the parameter count independent of sequence length.

**Unrolling** means drawing the recursion as a chain across time so the dependencies are explicit: $h_1$ depends on $x_1$ and the initial state, then $h_2$ depends on $h_1$ (hence indirectly on $x_1$) and $x_2$, and so on.
>Then $h_t$ ends up depending on every input up to time $t$.

>[!Tip]
>During training it's simple to decide a **maximum length** $t$.

![[RNN unrolling.png|500]]

Note that $A$ is always the same, since we use the same function/parameters at each time step.

### Multi-layer RNNs
RNNs are already "deep" across time, but **stacking** multiple RNN layers on top of each other makes them _deep in a second dimension_ too, with lower layers learning low-level features and higher layers more abstract ones.

High-performing RNNs are **usually multi-layer** (but aren’t as deep as convolutional or feed-forward networks), going past $2-3$ layers gives _diminishing returns_ without _residual connections_.

### Backpropagation through time
Let's take as an example the following unrolled RNN which is **processing a sequence** during its training phase:

![[RNN training.png|500]]

The loss is computed at each timestep and because the same weight matrix is reused at every step, its gradient is a **sum of contributions from every timestep**, which is both what makes RNNs able to learn temporal patterns and the root of the next problem.

The unrolled graph is a DAG computation graph where we can run **backpropagation**, this is historically called **backpropagation through time (BPTT)**.

![[RNN training-1.png|400]]
![[RNN training-2.png|400]]
![[RNN training-3.png|400]]

During the **forward pass**, the RNN processes the sequence word by word, and at each timestep $t$ it updates its hidden state $h_t$ using the current input $w_t$ and the previous hidden state $h_{t-1}$.
At every step, the network attempts to predict the next word in the sequence, the **loss** is computed at every step as a negative log-likelihood such as:
$$-\log p(like|w_2,w_2)$$
The **total loss** for the sequence is simply the sum of the losses at each individual timestep.

To train the network we need to **update the shared hidden-state** weight matrix $W_{hh}$ by computing the gradient of the total loss with respect to $W_{hh}$.

Since the loss at the final timestep depends on all previous hidden states, the **error must flow backward** through the unrolled network.

We compute how a change in a previous hidden state affects the current hidden state, for a single step back in time, the partial derivative is heavily dependent on the weight matrix itself:
$$\frac{\partial h_t}{\partial h_{t-1}}\approx W_{hh}$$
The issue arises when we look at how gradients flow across multiple timesteps, so to compute the gradient of the loss at timestep $t$ with respect to a hidden state $k$ in the past ($h_{t-k}$), we must chain the local gradients together.

Because the weight matrix $W_{hh}$ is shared across all timestep, propagating the gradient $k$ steps backward requires multiplying by $W_{hh}$ repeatedly:
$$\frac{\partial h_t}{\partial h_{t-k}}=[W_{hh}]^k$$
This **repeated multiplication** by the same matrix is what causes the RNN to **struggle with long-term dependencies**:
- _Vanishing gradients_: if the eigenvalues of $W_{hh}$ are less than $1$, multiplying them by themselves $k$ times will cause the gradient to shrink toward zero, thus "forgetting" distant past inputs
- _Exploding gradients_: if the eigenvalues are greater than $1$, the gradient will grow exponentially, causing the training process to become highly unstable

### Fixing long-term dependencies
In order to solve the _vanishing/exploding gradient_ issue, there are a few options, between them we have:
- **Gradient clipping**: if the gradient's norm exceeds a threshold $c$, rescale the gradient down to norm $c$ (direction preserved, magnitude capped), this is cheap and effective against exploding gradients, but doesn't touch vanishing gradient
- **Truncated BPTT**: rather than backpropagating through an entire (possibly very long) sequence, the sequence is processed in chunks, the hidden state is still carried forward across chunk boundaries, but gradients are only backpropagated within a limited window, this bounds compute/memory and somewhat limits vanishing gradients, at the cost of not learning dependencies longer than the truncation window

### Long short-term memory networks
LSTM networks were created with the following **objectives** in mind:
- Addressing the challenge of **long-term dependencies** encountered by recurrent RNNs caused by the vanishing gradient issue
- Distinguishing themselves from traditional feedforward neural networks through the **incorporation of feedback connections**
- **Preserving valuable information from prior data** within a sequence to facilitate the analysis of new data points
- Demonstrating remarkable proficiency in **handling data sequences** like text, speech, and general time-series data

The classic RNN cell:
![[RNN cell.png|500]]
gets transformed to:
![[LSTM cell.svg|500]]

LSTM maintains **two running states** instead of one:
- **Cell state**: long-term memory, changes slowly
- **Hidden state**: short-term memory, can change more abruptly at each step, and is recomputed from scratch each time

The **output** of an LSTM cell depends on:
- _Cell state_
- _Hidden state_
- _Input data_

LSTM cell introduces **three gates** that regulate the amount of long-term and short-term memories allowed to flow:
- _Forget gate_: how much of the long-term memory will be remembered
- _Input gate_: how we update the long-term memory
- _Output gate_: updates the short-term memory

The cell state has a nearly **uninterupted path across time steps** involving only elementwise multiplication/addition (not repeated multiplications through a squashing nonlinearity).
This **reduces vanishing gradients** since it will propagate over many steps largerly unattenuated.

The **structural reason** why LSTMs handle longer dependencies is that:
- In the LSTM cell $c$ changes slowly: $c_t$ is $c_{t-1}$ added by something
- In the RNN cell $c$ changes faster: $h_t$ and $h_{t-1}$ can be very different

### Recurrent sequential models in computer vision
The LSTM cell can be expanded in the domain of computer vision.

- **ConvLSTM**: the internal matrix multiplications are replaced with convolutions, so it can process spatial data (e.g. video frames) while still maintaining a memory over time (used for video prediction)
- **Caption generation**: the classic CNN+RNN "Show and Tell" architecture, a CNN encodes an image into a feature vector, which seeds an RNN/LSTM decoder that generates a caption word by word (like the earlier "image captioning" one-to-many pattern, now with a real CNN encoder)
- **Instance segmentation**: a recurrent architecture that outputs object masks sequentially, one instance at a time, rather than all at once, showing that recurrence is useful beyond purely temporal data

### Sequence-to-sequence
The core idea is to use two RNNs (often LSTMs) in an **encoder-decoder** setup to convert one sequence into another, where the two sequences can have different, variable lengths and no obvious $1:1$ alignment between positions.

Before this, **machine translation** presented a challenge to vanilla deep learning, since input and output are sequences, with variable lengths, and also the output length may not coincide with the input length, and there is no obvious correspondence between positions in the input and in the output.

This seq2seq setup can be used for machine translation, question answering, dialogue system, summarization and code generation.
![[Seq2seq.png|500]]

1. Input sentence gets `<sos>`/`<eos>` tokens appended, each word passed through an **embedding layer**, then into the encoder RNN
2. At each step, the **encoder combines the current word's embedding with the previous hidden state** to produce a new hidden state, after the last input word, the final hidden state becomes the **context vector**: a fixed-length summary of the whole source sentence
3. **Decoding starts** by feeding `<sos>` into the decoder RNN, initialized with the context vector as its starting hidden state
4. At each **decoding step**, the current hidden state passes through a linear layer + softmax to produce a probability distribution over the vocabulary, the predicted word is typically fed back in as the next input, looping until `<eos>`
5. **Training minimizes cross-entropy** between predicted and actual target sentences, backpropagated through both decoder and encoder

>[!Attention]
>Encode and decoder embedding layers have **separate parameters**, even though both operate on words.

### Additive attention
Compressing an entire source sentence into one fixed-length context vector is a **bottleneck**, it becomes especially damaging for long sentences (especially those that are longer than the sentences in the training corpus), since the model has no way to "look back" at specific parts of the input while decoding.

Rather than using only the final encoder hidden state, **keep all encoder hidden states** around, and at each decoding step, learn to weight them by relevance.
![[Encoder-decoder additive attention.png|600]]


In order to **decide which states are more or less useful** for every prediction at every time step of the decoder, we use a neural network to learn which hidden encoder states to attend to and by how much.

1. **Alignment model**: a small feedforward NN scores how well the decoder's previous hidden state matches each encoder hidden state
2. **Softmax**: turns those scores into attention weights $\alpha$ (summing to $1$), this can be viewed as a probability distribution over source positions
3. **Context vector**: weighted sum of all encoder hidden states, using those weights, so it changes at every decoding step, rather than being fixed once

The decoder consumes this per-step context vector (concatenated with its own state) to produce the next output word, then the whole process repeats for the next word.

![[Attention mechanism.png|500]]

**Attention is great**:
- It's useful to allow decoder to focus on certain parts of the source
- Allows the decoder to look directly at source (thus bypassing the bottleneck)
- Provides shortcut to faraway states
- Provides some _interpretability_: by inspecting attention distribution, we can see what the decoder was focusing on, and we get a (soft) _alignment_ for free since we never explicitly trained an alignment system, the network just learned alignment by itself
>Attention can be used in many architectures.

>[!Tip] General definition of attention
>Given a set of vector _values_, and a vector _query_, **attention** is a technique to compute a weighted sum of the values, dependent on the query.
>
>We sometimes say that the _query attends to the values_.
>>In the se2seq + attention model, each decoder hidden state (query) attends to all the encoder hidden states (values).

The weighted sum is a **selective summary** of the information contained in the values, where the query determines which values to focus on.
Attention is a way to obtain a **fixes-size representation of an arbitrary set of representations** (the values), dependent on some other representation (the query).

