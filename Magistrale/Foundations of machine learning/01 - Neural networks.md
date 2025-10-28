From a **DARPA neural network study** in 1989, we can highlight the following statements:
- Neural networks are adaptive, or trainable
- Neural networks are naturally massively parallel

While this is true, it is also important to highlight that neural networks are not the only trainable data structure, the second point also suggests that the networks should be able to make decisions at **high-speed** and be **fault tolerant**, this is because if a neuron "dies" there are many other that will carry information.

The true potential behind this data structure, is given by the enormous number of **connections** between neurons.

The **transmission of a signal in the cerebral cortex** is a complex process, that can be simplified as it follows:
- The cellular body performs a "weighted sum" of the incoming signals
- If the result exceeds a certain threshold, then it produces an "action potential" which is sent down the axon (the neuron has "fired"), otherwise it remains in a rest state
- A chemical reaction then will provoke the diffusion of an electrical signal to other neurons

The **synaptic efficacy** is the amount of current that enters in the next neuron, compared to the action potential of the pre-synaptic neuron.
>Learning involves modifying the synaptic efficacy.

Synapses can **excite** in order to favor the generation of action potential in the post-synaptic neuron, or **inhibit** in order to hinder the generation of action potential.

### The McCulloch and Pitts Model
The McCulloch and Pitts (MP) neuron is modeled as a binary threshold unit, it "fires" if the **net input** $\sum\limits_{j}w_jI_j$ reaches (or exceeds) the **threshold** (bias) $T$:
$$y=g\left(\sum_j w_jI_j-T\right)$$
If the neuron is firing, then its output $y$ is $1$, otherwise it is $0$.:
$$g(x)=\begin{cases}
0&\text{if } x<0\\
1&\text{if } x\geq 0
\end{cases}$$
![[MP neuron.png|500]]

Weights $w_{ij}$ represent the strength of the synapse between neuron $j$ and neuron $i$.

By properly combining MP neurons it is possible to simulate the behavior of any boolean circuit, follows _not_, _and_, _or_:
![[MP neuron logic gates.png|500]]

The idea behind ml-related tasks is that the objects that are received as inputs can be represented as **points** in a **geometric space**.

In a **classification task**, the inputs are the features values, while the outputs are the class labels.

We can get rid of the _threshold_ (bias) associated with each neuron, by treating it like a weight with a clamped input (e.g. $1$), in doing so it can be adaptively adjusted during training.
$$w_1x_1+w_2x_2+b\stackrel{\text{becomes}}{\Longrightarrow}w_0(1)+w_1x_1+w_2x_2$$

### The Perceptron
The perceptron is a network consisting of one layer of M&P neurons connected in a feedforward way, that can classify things into two parts.
![[Perceptron.png|500]]

**Variables and parameters**:
- $x(n)$ = $(m+1)\times 1$ input vector
- $w(n)$ = $(m+1)\times 1$ weight vector
- $b$ = bias
- $y(n)$ = actual output
- $d(n)$ = desired output
- $\eta$ = learning-rate

**Algorithm**:
1. Set the weight vector to $0$
2. For each time step $n$:
	2. Present the algorithm with an input vector and the corresponding desired class label
	3. Compute the actual response with the [[Funzioni elementari#Funzione segno|signum function]] $y(n)=\text{sgn}[w^T(n)x(n)]$
	4. Update the weight vector: $w(n+1)=w(n)+\eta[d(n)-y(n)]x(n)$
	5. Increment time step $n$

![[Perceptron training with no bias.gif|300]]

It has been shown that perceptrons can only solve **linearly separable** problems (i.e. the decision regions can be separated by a hyperplane).

**Rosenblatt's Perceptron Convergence Theorem**
If the training set is linearly separable, the perceptron learning algorithm always converges to a consistent hypothesis after a finite number of epochs, for any $\eta>0$.

If it is not linearly separable, after a certain number of epochs the weights start oscillating.

### Multi-layer feedforward networks
People already knew at the time that by adding hidden layers we could train more complex networks, the point is that there wasn't such an algorithm for training these kind of models.

In a feedforward neural networks there are no cycles, and in order to learn the right weights for the task we use the **backpropagation** method that uses the **gradient descent**.

We may use different **activation functions** in order to say how much a neuron is "active" and contributes to the weighted sum.

### Supervised learning
Supervised learning algorithms require the presence of a "teacher" who provides the right answers to the input questions.

This means that we need a **training set** of the form:
$$\mathscr{L}=\{(x^1,y^1),...,(x^N,y^N)\}$$
- $x^\mu$: is the input vector
- $y^\mu$ is the desired output vector
>$\mu=1,...,N$

The training phase consists of determining a configuration of weights $w$ so that the network's output is as close as possible to the desired output, for all the samples in the training set.

This corresponds to minimizing a **loss function** such as the mean squared error (MSE):
$$MSE(w)=\frac{1}{2}\sum_\mu||y^\mu-O^\mu(w)||^2$$
- $O^\mu(w)$: the output vector for the $\mu$-th input sample, as a function of the current network weights $w$

