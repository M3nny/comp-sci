Let $f:\mathbb{R}^n\to\mathbb{R}^m$, with $f\in C^1(\mathbb{R}^n)$, then we say that the matrix:
$$\nabla f(x)=\left[\nabla f_1(x)\vdots\dotsi\vdots\nabla f_m(x)\right]\in\mathbb{R}^{n\times m}$$

is the **gradient matrix** associated to $f(x)$, where the $i$-th column is the gradient of the corresponding entry $f_i(x)$ of the vector $f(x)$.

We also define the matrix:
$$J(x)=[\nabla f(x)]^T\in\mathbb{R}^{m\times n}$$
as the **jacobian** of $f(x)$.

>[!Note] Matrices types
>- **Gradient**: applies to scalar functions, it represents the vector of first-order partial derivatives
>- **Gradient matrix**: applies to vector functions, each column represents the gradient of each component
>- **Jacobian**: applies to vector functions, it is the transpose of the gradient matrix
>- **Hessian**: applies to scalar functions, it represents the matrix of second-order partial derivatives

### Chain rule 1
Let $f:\mathbb{R}^n\to\mathbb{R}^m$ and $g:\mathbb{R}^m\to\mathbb{R}^\ell$, then we can define a **composite function** $h:\mathbb{R}^n\to\mathbb{R}^\ell$, such that:
$$h(x)=g[f(x)]$$
If both $f$ and $g$ are continuous functions, then also $h$ will be a continuous function, so:
$$\nabla h(x)=\nabla f(x)\nabla g[f(x)]\in\mathbb{R}^{n\times\ell}$$

### Chain rule 2
Let be given the functions $x_i:\mathbb{R}\to\mathbb{R}$ ($i=1,...,n$) with $x_i(t)\in C^1(\mathbb{R})$, $t\in \mathcal S$.
Considering also the function $f:\mathbb{R}^n\to\mathbb{R}$ with $f\in C^1(\mathbb{R}^n)$.
Being $F(t)=f[x_1(t),...,x_n(t)]$, then $F(t)$ admits derivative in any open subset of $\mathcal S$, and we have:
$$F'(t)=\frac{\partial f(x)}{\partial x_1}\cdot x_1'(t)+\dotsi+\frac{\partial f(x)}{\partial x_n}\cdot x_n'(t)$$

This is also knows as the **multivariable chain rule** and it measure the change in $F$ with respect to the change of $t$.

It sums the products of how much $f$ changes when $x_i$ changes by how fast $x_i$ changes in $t$.

