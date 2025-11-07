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

---
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

---
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

---
### Multi-layer feedforward networks
People already knew at the time that by adding hidden layers we could train more complex networks, the point is that there wasn't such an algorithm for training these kind of models.

In a feedforward neural networks there are no cycles, and in order to learn the right weights for the task we use the **backpropagation** method that uses the **gradient descent**.

We may use different **activation functions** in order to say how much a neuron is "active" and contributes to the weighted sum.

---
## Supervised learning
Supervised learning algorithms require the presence of a "teacher" who provides the right answers to the input questions.

This means that we need a **training set** of the form:
$$\mathscr{L}=\{(x^1,y^1),...,(x^N,y^N)\}$$
- $x^\mu$: is the input vector for the $\mu$-sample
- $y^\mu$ is the desired output vector for the $\mu$-sample

The training phase consists of determining a configuration of weights $w$ so that the network's output is as close as possible to the desired output, for all the samples in the training set.

This corresponds to minimizing a **loss function** such as the mean squared error (MSE), which is here represented in a compact version using the norm:
$$MSE(w)=\frac{1}{2}\sum_\mu||y^\mu-O^\mu(w)||^2$$
- $O^\mu(w)$: the predicted output produced for input $x^\mu$ given weights $w$

### Back-propagation
To minimize the error function $E$ we can use the **gradient-descent** algorithm, which updates the weights in the following way:
$$w_{ij}=w_{ij}-\eta\frac{\partial E}{\partial w_{ij}}$$
in words: we subtract from the weight $w_{ij}$ the partial derivative of the error function $E$ with respect to that particular weight, this is because [[Programmazione lineare#Gradiente della funzione obiettivo|the derivative will always point to the growing direction]], whilst its opposite will be oriented in the descending direction.

The **error back propagation** algorithm consists in two stages:
- **Forward pass**: the input of the network is propagated layer after layer in forward direction
- **Backward pass**: the error made by the network is propagated backward, and weights are updated properly

It stops in three main cases:
1. $-\eta\nabla E(w)=0$ this indicates a _stationary point_, which means that the gradient has completely _vanished_ and we cannot move from that point by only following the gradient
2. After a certain number of epochs
3. Early stopping

![[Neural network notation.png|400]]

Given sample $\mu$, the unit $j$ receives a **net input**:
$$h_j^\mu=\sum_k w_{jk}x_k^\mu$$
- $w_{jk}$: the weight connecting unit $k$ to unit $j$
- $x_k^\mu$: $k$-th feature of the input vector for the sample $\mu$

In words: the weighted sum of all the inputs that the neuron $j$ receives from the previous layer for the sample $\mu$ (before applying the activation function).

And it produces as <u>output the weighted sum given as the input to the activation function</u> $g$:
$$V_j^\mu=g(h_j^\mu)$$

>[!Note] Chain rule
>We recall that if two functions $f$ and $g$ are both differentiable, and their composition is given by $F(x)=f(g(x))$, then $F$ is differentiable, and $F'$ is given by the product:
>$$F'(x)=f'(g(x))g'(x)$$

#### Weight update
We'll now analyze how the weight update is done considering the MSE as the loss function.
$$E=\frac{1}{2}\sum_\mu\sum_i(y_i^\mu-O_i^\mu)^2$$
**Updating hidden-to-output weights**

![[Hidden to output weight update.png|300]]
$$\Delta W_{ij}=\eta\sum_\mu\delta_i^\mu V_j^\mu\qquad \delta_i^\mu=(y_i^\mu-O_i^\mu)g'(h_i^\mu)$$
- $(y_i^\mu-O_i^\mu)$ is the difference between target and predicted value
- $g'(h_i^\mu)$ is the derivative of the activation function, which tells us how much the neuron's output changes with its input (it can be seen as a scaling factor)
- $V_j^\mu$ indicates how active was the hidden neuron, those who are more active have more responsibility on the predicted value

We sum over all training samples and multiply by the learning rate $\eta$ to get the weight change.

In this case the neurons have direct access to the error information, so the error signal $\delta_i^\mu$ is straightforward.

**Updating input-to-hidden weights**
![[Input to hidden weight update.png|300]]
$$\Delta w_{jk}=\eta\sum_\mu\hat\delta_j^\mu x_k^\mu\qquad \hat\delta_i^\mu=g'(h_j^\mu)\sum_i\delta_i^\mu W_{ij}$$

Since hidden neurons don't directly see the target output, we have to backpropagate the error from the output layer.

We weight each output neuron error signal $\delta_i^\mu$ by how strongly that hidden neuron connects to that output neuron ($W_{ij}$), and we sum over all the output neurons to get the total "blame" assigned to this hidden neuron, then we multiply by its sensitivity $g'(h_j^\mu)$.

Now that we have the error signal $\hat\delta_i^\mu$ for the hidden neuron, we multiply it by how active the input $x_k^\mu$ was and the learning rate $\eta$.

**Structural pattern of the formula**
Both formulas follow the same pattern, only that it is easier to calculate the weight update when we have direct access to the information (i.e. hidden to output).
$$\Delta(\text{weight})=\eta\sum_\mu(\text{error signal})\cdot(\text{input from previous layer})$$

When updating the weights from the last hidden layer to the output layer, we only consider one edge since, as previously stated, we have direct access to the error information.
```
Hidden Layer           Output Layer

    (j) --------W_ij------> (i) -----> Compare with target y_i and
                                       get the error directly
```

When updating the weights from the input layer or from any hidden layer to the following hidden layer we also have to weight the edges connected to the considered hidden layer in order to know how much influence it had on the final output's error.
```
Input Layer     Hidden Layer         Output Layer

   (k) ----w_jk----> (j) ----W_ij-------> (i) ------> error δ_i
                      |                    
                      |------W_ij'------> (i') -----> error δ_i'
                      |                    
                      |------W_ij''-----> (i'') ----> error δ_i''
```

We stress the fact that this algorithm uses only **locally available information**, this is a key element that **enables parallelism**.

There are two extremes to the gradient descent algorithm:
- **Off-line**: process and accumulate gradients from every sample, update weights once after seeing the entire dataset
	This is slow, but it represents the true direction of the steepest descent.
- **On-line** also called **Stochastic Gradient Descent (SGD)**: process and update weights after seeing one sample
	This is fast, good for streaming data and can escape local minima because of the noise, but it is not stable

The most common approach is a mix of both approaches, the so called **mini-batch** gradient descents consists in the processing of a small batch of samples and accumulating the gradients over the batch.

---
### Learning rate and momentum
The gradient descent may converge too slowly if  $\eta$ is too small, but oscillate if $\eta$ is too large.

A simple remedy to this problem is the **momentum**:
$$\Delta w_{pq}(t+1)=-\eta\frac{\partial E}{\partial w_{pq}}+\alpha\Delta w_{pq}(t)$$
in words: the weight update at time $t$ is given by the current gradient multiplied by the learning rate $\eta$, plus a fraction of the previous weight update, where $\alpha$ is the momentum term that usually is set to $\alpha=0.9$ and $\eta=0.5$.

![[Momentum.png|300]]
>Same learning rate, on the left there is no momentum.

Adding this **memory of past direction** helps to reduce oscillations and accelerating in consistent directions.

