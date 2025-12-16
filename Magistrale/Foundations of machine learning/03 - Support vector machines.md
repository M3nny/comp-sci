clSupport vector machines are part of the so called **kernel methods**.
Their job is to find a **margin** which maximizes the boundary from one class cluster to another.
The class instances which determine the margin are called **support vectors**, all other points can move freely since the solutions only depends on the SVs.
![[Magistrale/Foundations of machine learning/Images/SVM.png|400]]

Every hyperplane can be represented as:
$$f(x)=w^Tx+b$$
in order to avoid multiple representations of the same hyperplane such as $c(w^Tx+b)=0$, we choose a normalization, also called **canonical form** that is:
- $w^Tx+b=1$ for _positive_ support vectors
- $w^Tx+b=-1$ for _negative_ support vectors

Hence, in a binary classification problem, we would have for positive samples $w^Tx+b\geq1$ and for negative samples $w^Tx+b\leq-1$.

From a geometrical point of view, the distance from a point $x_0$ to the hyperplane $w^Tx+b=0$ is defined as:
$$\text{Distance}=\frac{|w^Tx_0+b|}{||w||}$$
and since we imposed the canonical form, we have (by computing the distance for the negative support vector):
$$\text{Margin}=\frac{|w^Tx_++b+1|}{||w||}=\frac{1+1}{||w||}=\frac{2}{||w||}$$
>The distance is the same everywhere since the hyperplanes are parallel.

![[Margin.png|400]]


>[!Tip] Mapping SVMs to real problems
>In real scenarios, when we train a SVM model, like the one from sklearn, we are actually training $n$ SVMs, that is, $1$ for each class.
>
>Each SVM will behave like this for the $k$ class:
>$$\begin{cases}w^Tx+b\geq1\implies\text{On this side, only k samples}\\ w^Tx+b\leq-1\implies\text{On this side, samples with class different from k}\end{cases}$$

### Learning SVMs
Learning the SVM can be formulated as an optimization problem:
$$\max_w\frac{2}{||w||}\text{ subject to }w^Tx_i+b\begin{matrix}\geq1\text{ if }y_i=1\\\leq-1\text{ if }y_i=-1\end{matrix}$$
where $y_i$ is the label of the sample.

This is a [[01 - Convexity#Convex functions|convex]] quadratic optimization problem subject to linear constraints, this ensures that there is a **unique minimum**.

>[!Info] Lagrangians and duality
>We want to find the maximum of:
>$$f(x,y)=1-x^2-y^2$$
>the solution is found among the points where the gradient vanishes:
>$$\nabla f=\begin{pmatrix}-2x\\-2y\end{pmatrix}$$
>which yields $x=0$ and $y=0$.
>
>In the case of constrained optimization with the following constraint:
>$$x+y-1=0$$
>we would have to define a new function, called **lagrangian** as follows:
>$$L(x,y,\lambda)=1-x^2-y^2+\lambda(x+y-1)$$
>where $\lambda\neq0$ is a **lagrangian multiplier** and look for points $(x,y,\lambda)$ where the gradient $\nabla L$ vanishes.
>$$\nabla L=\begin{pmatrix}-2x+\lambda\\-2y+\lambda\\x+y-1\end{pmatrix}$$
>which yields $x=y=\frac{1}{2}$.
>
> In the general case with:
> $$\max f(x)$$
> subject to:
> $$g_1(x)\geq0...g_m(x)\geq 0\quad\text{(m inequality constraints)}$$
> $$h_1(x)\geq0...h_m(x)\geq 0\quad\text{(p equality constraints)}$$
> 
> The lagrangian $L(x,\Lambda,M)$ is defined as follows:
> $$L(x,\Lambda,M)=f(x)+\sum_{i=1}^m\lambda_i g_i(x)+\sum_{j=1}^p\mu_j h_j(x)$$
> where $\Lambda=(\lambda_1,...,\lambda_m)^T$ and $M=(\mu_1,...,\mu_p)^T$ are vectors of Lagrange multipliers corresponding to inequality and equality constraints, respectively.
> 
> ---
> Let's now consider a minimization problem: $\min f(x)$ subject to $g_1(x)\geq0...g_m(x)\geq 0\quad\text{(m inequality constraints)}$ with optimal value $p^*$, and consider its Lagrangian:
> $$L(x,\Lambda)=f(x)-\sum_{i=1}^m\lambda_i g_i(x)$$
>The problem $P$ that we just defined is called **primal**, because now we are going to define its **dual function**:
>$$\phi(\Lambda)=\inf_x L(x,\Lambda)$$
>>$\inf$ is like $\min$ but admits $-\infty$ as a solution.
>
>It can be proven that $\phi(\Lambda)\leq p^*$, the intuition is that the penalty term ($-\sum$) is always non-positive for feasible points, so the Lagrangian underestimates the objective function.
>
>The problem $\max \phi(\Lambda)$ subject to $\Lambda\geq 0$ is called the **dual** of problem $P$.
>
>Given $p^*$ solution of the primal and $d^*$ solution of the dual:
>- **Weak duality**: $d^*\leq p^*$
>- **Strong duality**: if the function $f$ of the primal is convex (and so are all the constraints $-g_i$) then $p^*=d^*$
>
>$p^*-d^*$ is called the **duality gap**.
>
>>The dual problem is useful to find the best lower bound for optimization problems where the primal might be much harder.

Now let's go back to SVM training, we can reformulate the optimization problem as the following minimization problem:
$$\min\frac{1}{2}||w||^2\quad\text{subject to }y_i(w^Tx_i+b)\geq 1\quad i=1,...,N$$
To solve this constrained optimization problem, we introduce $N$ Lagrange multipliers $\lambda_i\geq 0$ (one for each constraint) giving the Lagrangian function:
$$L(w,b,\Lambda)=\frac{1}{2}||w||^2-\sum_{i=1}^N\lambda_i\left[y_i(w^Tx_i+b)-1\right]$$
It can be proved that:
$$\min_{w,b}\max_{\lambda\geq0}L(w,b,\Lambda)=\max_{\lambda\geq0}\min_{w,b}L(w,b,\Lambda)$$
where the left side is the primal problem, whilst the right side is the dual problem.
This equality holds because **SVMs satisfies strong duality**. 

Now we want to find the dual problem, and maximize the lower bound to be as near as possible as the original primal problem, in this case due to the strong duality, the solutions will be the same as the primal.

In order to do this, we want to minimize $L$ over $w$ and $b$, for this reason we are going to take the derivatives and set them to zero, and then substitute them into $L$.
Setting $\nabla L=0$ we obtain:
$$L'_w=w-\sum_{i=1}^N\lambda_iy_ix_i\quad L'_b=\sum_{i=1}^N\lambda_iy_i=0$$
Now, we substitute $w$ and $b$ to $L$, and considering that $b=0$, we only have to substitute $w=\sum_{i=1}^N\lambda_iy_ix_i$, hence we get the **dual problem** $L_D$:
$$\max L_D(\Lambda)=\sum_{i=1}^N\lambda_i-\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\lambda_i\lambda_jy_iy_jx_i^Tx_j$$
$$\text{ subject to}\underbrace{\sum_{i=1}^N\lambda_iy_i=0}_{\text{From eliminating }b}\quad\land\quad\lambda_i\geq0\forall i=1,...,N$$

Now, it is true that the dual problem has **many more variables** than the primal since:
- Variables of the primal: based on number of input features
- Variables of the dual: based on number of training samples

But the fact is that the solution that we're gonna get from the dual, is **sparse** which means that the vast majority of variables is going to be $0$.

>[!Tip] SVMs and the VC dimension
>A **theorem** from **Vapnik** tells us that the idea of maximizing the margin is equivalent to the notion of minimizing the [[02 - Statistical learning theory#The VC dimension|VC dimension]] of our SVM.

---
### SVM in real cases
In practice it is rare to have a linearly separable dataset, we distinguish two cases:
- **Non-intrinsic non-linearly separable**: if we remove some outlier, the dataset becomes linearly separable
- **Intrinsically non-linearly separable**: in this case we have to use the so called _kernel trick_

For solving the real localization problem, say, recognizing pedestrians in an image, we used a _sliding window_ approach which was a binary classifier that said if in that windows there was a pedestrian or not.

#### Managing outliers
If we are in the first case, it is possible to introduce **slack variables** ($\xi$) in order to deal with outliers, thus creating **soft margins**.
A slack variable is associated with each sample in the training set and that measures the **amount of violation** of the constraint.
![[Soft margins.png|500]]

The modified problem with slack variables introduced as a **penalty** can be defined as:
$$\min\frac{1}{2}||w||^2+\underbrace{C\sum_{i=1}^N\xi_i}_{\text{Penalty}}$$
$$\text{Subject to}\quad y_i(w^Tx_i+b)\geq1-\xi\quad\xi_i\geq0,i=1,...,N$$

$C$ is an _hyperparameter_:
- Small $C$: allows constraints to be easily ignored (large margin)
- Large $C$: makes constraints hard to ignore (narrow margin)
- $C=\infty$: hard margin (enforces the constraints)

#### Non-linearly separable dataset
Introducing slack variables does not always work, especially when the problem is intrinsically not linearly separable.

For example in the following image we can clearly see how the problem becomes linearly separable when we map it to polar coordinates:
![[Polar mapping.png|400]]

**Cover's theorem** roughly speaking states that: a complex pattern-classification problem cast in a high-dimensional space non-linearly is more likely to be linearly separable than in a low-dimensional space.

The power of SVMs resides in the fact that they can represent a robust and efficient implementation of the aforementioned theorem.
Nonlinear SVMs _operate in two stages_:
- Perform a (typically implicit) non-linear mapping of the feature vector onto a high-dimensional space
- Construct an optimal separating hyperplane in the high-dimensional space

How do we map the original problem into an higher dimension?
This is where the _dual_ of the original problem comes in, in fact we recall that it is represented as:
$$\max L_D(\Lambda)=\sum_{i=1}^N\lambda_i-\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\lambda_i\lambda_jy_iy_j\underbrace{x_i^Tx_j}_{\text{Feature vectors}}$$

We can notice that the optimization depends (regarding inputs) only on the dot product between points, so we don't need their exact coordinates or dimension.

So the problem of computing the mapping onto another dimension does not apply anymore, now we are simply interested in the dot product of the two vectors as if they were in an higher dimensional space, the function that computes this dot product in an higher dimensional space is called a **kernel** ($K$).
$$\max L_D(\Lambda)=\sum_{i=1}^N\lambda_i-\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N\lambda_i\lambda_jy_iy_jK(x_i^Tx_j)$$
Some popular kernels are:
- **Linear**: $K(x,y)=x^Ty$
- **Polynomial**: $K(x,y)=(1+x^Ty)^d$ for any $d>0$
- **Gaussian**: $K(x,y)=\exp\frac{-||x-y||^2}{2\sigma^2}$

---
### Multi-class problems
So far we discussed binary classification problems, but in the case of multiple classes we should use another approach.

Say for example that we have the classes: cat, dog, bird.
We could train a **one-vs-the-rest classifier** which practically speaking is $K-1$ binary classifiers in one, for each one of the we ask ourselves: is it class $A$ or not?
In the example stated above we would have:
- Cat or not?
- Dog or not?
- Bird if not one of the above

Another solution can be provided by the **one-vs-one** classifiers which train $\frac{K(K-1)}{2}$ binary classifiers, that is, one for every pair of classes:
- Cat vs Dog
- Cat vs Bird
- Dog vs Bird

>The typical approach is to train one-vs-the-rest classifiers and take the class with the most positive score during classification.
