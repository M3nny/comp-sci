Given an objective function $F:\mathbb R^D\to\mathbb R$, we want to find a vector $x^*\in\mathbb R^D$ that minimizes $f(x)$:
$$x^*=\arg\min_{x\in\mathbb R^D}f(x)$$
As we've seen in other courses, we are interested in minimizing the error of our predictions, and this is formulated as minimizing a loss function in order to find the best parameters $x^*$.

Given a **user** $u\in U$ and **item** $i\in I$, we want to **learn a model** $g:U\times I\to\mathbb R$ which **predicts the user rating** for item $i$.

We can measure the error w.r.t. the **true rating** $R_{ui}$ with the loss $L$ defined with the Root Mean Squared Error (RMSE) over a set of known ratings:
$$L(g)=\sqrt{\frac{1}{|S|}\sum_{(u,i)\in S}(R_{ui}-g(u,i))^2}$$
>$S=\{(u,i)\in U\times I|R_{ui} \text{ is known}\}$.

The prediction of a model **depends on its parameters**, for this reason we can rewrite this machine learning task as:
$$\theta^*=\arg\min_{\theta\in\Theta}L(g(\cdot;\theta))=\arg\min_{\theta\in\Theta}\sqrt{\frac{1}{|S|}\sum_{(u,i)\in S}(R_{ui}-g(u,i;\theta))^2}$$
where $\Theta$ is the **set of all possible parameters** of the model.

### UV-decomposition
We assume that the true rating $R_{ui}$ can be approximated by the **dot product** of the **user vector** $u\in\mathbb R^k$ and **item vector** $v\in\mathbb R^k$, where $k$ is the **latent dimension** of the model.

We can see the _latent dimension_ as the $k$ hidden factors (not directly observed) that explain preferences.
In the case of movies recommendations, these hidden factors may represent popularity, amount of action, amount of romance.

The difference with the **features** of an instance in a dataset, is that the latent factors are not explicitly defined, but are learned implicitly from data, hence they are not directly interpretable.

The dot product then "measures" the **agreement** between the user's interests and the item's characteristics.
From this we retrieve the **rating matrix** $R\in\mathbb R^{|U|\times|I|}$:
$$R\approx UV$$
The original minimization goal then shifts to finding $U$ and $V$ that minimize RMSE:
$$U,V=\arg\min_{U,V}\sqrt{\frac{1}{|S|}\sum_{(u,i)\in S}(R_{ui}-U_u\cdot V_{:i})^2}=\arg\min_{U,V}\sum_{(u,i)\in S}(R_{ui}-U_u\cdot V_{:i})^2$$


We recall that the minimum is where the gradient is equal to $0$, that is, a **stationary point**, which may also indicate a local minimum and not a global one.

For a generic $u_{rs}$ to be optimized, we have:
$$\frac{\partial L}{\partial u_{rs}}=\frac{\partial}{\partial u_{rs}}\sum_j(R_{rj}-U_{r:}\cdot V_{:j})$$

The **full procedure** is:
- Initialize $U$ and $V$ with random values
- Repeat until convergence:
	- For each $u_{rs}$: set $u_{rs}$ s.t. $\partial L/\partial u_{rs}=0$, by using the previous update rule
	- For each $v_{rs}$: set $v_{rs}$ s.t. $\partial L/\partial v_{rs}=0$, by using the previous update rule

With large $k$ the error gets smaller, but on unseen data it increases, whilst smaller $k$ forces  the model to cluster users and items, to compress information and to capture patterns.
>Overall, larger $k$ increases the risk of overfitting.

### Support vector machines
Given a set of data points $D=\{(x_i,y_i)^n_{i=1}\}$, where $x_i\in\mathbb R^d$ and $y_i\in\{-1,1\}$ we want to find a function $g:\mathbb R^d\to\{-1,1\}$ that minimizes the number of missclassifications.

In the simple example of linear binary classifiers:
$$g(x;w,b)=sign(w\cdot x+b)=\begin{cases}+1&\text{if }w\cdot x+b>0\\-1&\text{if }w\cdot x+b<0\end{cases}$$
where $w\in\mathbb R^d$ and $b\in\mathbb R$.

The **Support Vector Machine (SVM)** is a linear classifier that maximizes the margin between the data points and the decision boundary:
- **Margin** ($\gamma$): distance between the decision boundary and the closest data points
- **Support vectors**: data points at distance $\gamma$ from the decision boundary
>The larger the margin, the smaller the missclassification risk on unseen data.

We want to solve the following optimization problem:
$$\begin{align}\max \gamma\\ y_i(w\cdot x_i+b)\geq\gamma\end{align}$$
and after applying [[03 - Support vector machines|regularization]] (canonical form) we have:
$$\begin{align}\max \frac{1}{||w||_2}\\ y_i(w\cdot x_i+b)\geq\gamma\end{align}$$

Since it is not always possible to find a linear separator, we introduce a **penalty** depending on the value distance from the margin:
- $0$ if $y_i(w\cdot x_i+b)\geq1$
- $1-y_i(w\cdot x_i+b)$ otherwise
>The penalty is $\max(0,1-y_i(w\cdot x_i+b))$.

The final formulation, which aims at **minimizing penalties** is:
$$\min\frac{1}{2}||w||_2^2+C\sum_i\max(0,1-y_i(w\cdot x_i+b))$$
The norm is elevated to the power of $2$ just to simplify derivatives, and $C$ is a hyperparameter that controls the trade-off between margin maximization and missclassification penalty.

We can then **update the parameters using the gradient descent**:
- Do small steps in the direction of the negative gradient
- Repeat until convergence
- Small steps (learning rate) provide better convergence

### Gradient descent strategies
**Batch gradient descent**
Computed after processing the whole dataset, provides smooth convergence, but is slow.

**Stochastic gradient descent**
The gradient is computed after processing each single data point, then the parameters are updated, this povides nooisy convergence, but is fast on massive datasets.

**Mini-batch gradient descent**
Data is partitioned in mini-batches and the gradient is computed over these mini-batches, then parameters are updated.
This is a middle way between the previous two approaches.

![[Gradient descent.png]]


We can further improve this approach by using second derivatives or by adding [[01 - Neural networks#Learning rate and momentum|momentum]].