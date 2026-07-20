The motivating idea behind machine learning is that **hand-engineered features** are _time-consuming, brittle, and don't scale_.

**Deep Neural Networks (DNN)** learn _hierarchical features_ directly from data, they've become common nowadays because of _big data_, _better hardware and software_.

### The perceptron
The perceptron is the atomic unit of a neural network, a simplified model of a biological neuron.

Given inputs $x_1,...,x_m$ with weights $w_1,...,w_m$, the perceptron computes a weighted sum, then passes it through a **non-linear activation function** $g$.

Adding a **bias term** $w_0$ (with implicit input of $1$) allows the decision boundary to shift away from the origin, without it, the hyperplane is forced through zero, limiting what the model can represent, in vectorized form it is:
$$\hat y=g(w_0+X^TW)$$
**Activation functions** introduce _non-linearities_ into the network which give networks the expressive power to approximate complex functions.

![[Activation functions.png|400]]

![[Magistrale/Image and video understanding/Images/Perceptron.png|400]]

### Artificial neural networks
Stacking perceptron into layers gives a **single-layer neural network**, where every hidden unit connects to every input and every output unit (dense layer).

Stacking multiple hidden layers between input and output creates a **multi-layer perceptron (MLP)**:
![[MLP.png|500]]

The **universal approximation theorem** states that: a two-layer network with a finite number of hidden units can approximate _any_ continuous function on a bounded domain arbitrarily well.
>Such network exists, totally not easy to find.

Generalizing to $k$ layers we end up with **deep neural networks**, where each layer's activations depend on the previous layer's outputs passed through a non-linearity:
![[DNN.png|400]]
$$z_{k,i}=w_{0,i}^{(k)}+\sum_{j=1}^{d_{k-1}}g(z_{k-1,j})w_{j,i}^{(k)}$$

### Losses
The **loss** measures the cost of an incorrect prediction for a single example:
$$\mathcal L(\underbrace{f(x^{(i)};W)}_{\text{Predicted}},\underbrace{y^{(i)}}_{\text{Actual}})$$
The [[02 - Statistical learning theory#The ERM principle|empirical loss]], also called _objective function_ (or empirical risk) averages the loss over the entire dataset:
$$J(W)=\frac{1}{n}\sum_{i=1}^n\mathcal L(f(x^{(i)};W),y^{(i)})$$
- **Binary cross-entropy loss** used for for binary classification
- **Mean squared error**: used for regression problems with continuous outputs

### Training neural networks
The goal is to find the weights $W$ that minimize the loss:
$$W^*=\arg\min_WJ(W)$$
Since $J(W)$ is a function of all the weights $W=\{W^{(0)},W^{(1)},...\}$, and this loss surface is generally **non-convex**, finding the global minimum isn't guaranteed, hence we settle for a good local minima.

The **gradient descent algorithm** works as follows:
1. Initialize weights randomly from $\mathcal N(0,\sigma^2)$
2. Until convergence (stationary point):
	1. Compute gradient $\frac{\partial J(W)}{\partial W}$
	2. Update weights $W=W-\eta\frac{\partial J(W)}{\partial W}$
3. Return weights

The core mechanism is the **computational graph** and the **chain rule**:
![[Computational graph.png|500]]

![[NN in and out.png|400]]

This generalizes to any node $f$ in a computational graph: each node receives **activations** _flowing forward_ and **gradients** _flowing backward_, computes its own **local gradient**, and combines it with the incoming upstream gradient via the chain rule $\frac{\partial L}{\partial x}=\frac{\partial L}{\partial z}\cdot\frac{\partial z}{\partial x}$ to pass gradients further back.

This is exactly how **backpropagation** works in neural networks, and it's the algorithm that makes training deep networks _computationally tractable_.

Since training occurs on a highly non-convex loss surface, so the **learning rate** $\eta$ is critical:
- Too small: slow convergence
- Too large: overshoots the minimum

**Adaptive learning rates** algorithms can adapt $\eta$ based on the gradient magnitude, learning speed, or weight size (e.g. ADAM).
>See also: [[01 - Neural networks#Learning rate and momentum|learning rate and momentum]].

Full-batch gradient descent is computationally expensive, there are two alternatives:
- **Pure SGD**: pick a single random data point, compute its gradient, very cheap but noisy
- **Mini-batch SGD**: pick a batch of $B$ points and average their gradients, a middle ground that's more accurate gradient estimate and gives smoother convergence

**Regularization** is defined as a set of strategies to reduce the generalization gap while keeping training error low (i.e. constraining the optimization to discourage overly complex models)

Commonly used techniques include:
- **Data augmentation**: artificially expand the training set by applying label-preserving transformations (e.g. blur, grayscale, rotations)
- **Dropout**: during training, randomly zero out some activations (typically $\sim50\%$ of a layer), preventing the network from over-relying on any single neuron, forcing redundant, more robust representations
- **Early Stopping**: stop training once validation/test loss starts increasing while training loss keeps decreasing, this point is where the model transitions from underfitting to overfitting on unseen data

