In this chapter we are going to discuss **how to find a function $y=y(x)$ that satisfies an equation $f(x,y)=0$ near a specific point $(\overline x,\overline y)$.**

The question is: can we write $y=y(x)$ such that when we plug it in, we get $f(x,y(x))=0$?.

Before addressing the possible computation of the function $y=y(x)$, we briefly describe _possible related drawbacks_ which can arise:
- The relation $f(x,y)=0$ might not be satisfied by a pair $(\overline x, \overline y)\in\mathbb{R}^2$, regardless of the choice of $(\overline x,\overline y)$, for example we could consider the following relation which is **never satisfied**: $f(x,y)=e^y+x^2=0$
- The relation $f(x,y)=0$ might be **trivially obtained** such in the following case: $f(x,y)=e^y-x^2=0$ which yields $y=y(x)=2\ln(|x|)$ for any $x\in\mathbb{R}\setminus0$
- The relation $f(x,y)=0$ **might possibly not be a function**, this means that we have multiple solutions, for example we could consider a circle $f(x,y)=x^2+y^2-1=0$

The key idea is that, even when we can't solve globally, we might be **able to solve locally** (in a small neighborhood).
![[Implicit function theorem.png|500]]

In the figure above we have:
- A curve $f(x,y)=0$
- A point $(\overline x, \overline y)$
- A rectangle around the point with dimensions $a,b,c,d>0$
- The function $y=y(x)$ is defined only in the neighborhood (i.e. rectangle in the figure) $I(\overline x,\overline y)=I_\overline x\times I_\overline y$ of the point $(\overline x, \overline y)$
$$I_\overline x=\{x\in\mathbb{R}:\overline x-a\leq x\leq\overline x+b\}\quad I_\overline y=\{y\in\mathbb{R}:\overline y-c\leq y\leq\overline y+d\}$$
$$I(\overline x,\overline y)=I_\overline x\times I_\overline y=\{(x,y)\in\mathbb{R}^2:\overline x-a\leq x\leq\overline x+b,\overline y-c\leq y\leq \overline y+d\}$$

Given the relation $f(x,y)=0$, with $f(\overline x,\overline y)=0$, and the set $I(\overline x,\overline y)$, we say that the **implicit function** $y=(x)$ _exists in a neighborhood_ of $(\overline x, \overline y)$ if:
$$f[x,y(x)]=0,\quad\forall x\in I_\overline x\land\forall y\in I_\overline y$$

### Dini's theorem
The implicit function theorem, also known as the Dini's theorem, states that given $f:A\to\mathbb R$ where $A\subseteq\mathbb R^2$, and $f$ is continuously differentiable in some open set $B\supseteq A$, and a point $(\overline x, \overline y)\in A$ where $f(\overline x,\overline y)=0$, suppose:
$$\frac{\partial f(\overline x,\overline y)}{\partial y}\neq0$$
Then, there exists a neighborhood $I(\overline x,\overline y)\subseteq A$ where the implicit function $y=y(x)$ is defined and satisfies:
1. $\overline y=y(\overline x)$ (the function passes through our point)
2. The first derivative $y'(x)$ of $y=y(x)$ is given , in any open subset of $I(\overline x,\overline y)$, by:
$$y'(x)=-\frac{\frac{\partial f(x,y(x))}{\partial x}}{\frac{\partial f(x,y(x))}{\partial y}},\quad\forall(x,y)\in \mathring{I}(\overline x,\overline y)$$

**Proof (simplified)**
The current proof assumes that the function $y=y(x)$ already exists in $I(\overline x,\overline y)$, then we only have to prove the second point.

1. We start with the fact that $f(x,y(x))=0$ which holds for any $x$ in $I_\overline x$
2. Given the previous point, then also the derivatives in both sides must be zero, in any open subset of $I_\overline x$, that is:
$$\frac{d}{dx}[f(x,y(x))]=0$$
3. By applying the [[05 - Chain rules#Chain rule 2|multivariable chain rule]] we obtain:
$$\frac{d}{dx}[f(x,y(x))]=\frac{\partial f(x,y(x))}{\partial y}\cdot y'(x)+\frac{\partial f(x,y(x))}{\partial x}=0\quad\forall x\in\mathring{I}_\overline x$$
	hence:
$$y'(x)=-\frac{\frac{\partial f(x,y(x))}{\partial x}}{\frac{\partial f(x,y(x))}{\partial y}},\quad\forall(x,y)\in\mathring{I}(\overline x,\overline y)$$
>[!Important] Internal interval
>The notation $\mathring I$ means the **interior** of $I$ (excluding the boundary points).
>This is because inside the interval the function $y=y(x)$ is smoothly defined by the implicit function theorem, whilst at the boundary it might not.

#### First extension to Dini's theorem
Let $f:A\to\mathbb R$ with $A\subseteq\mathbb R^{n+1}$, with
$$f(x_1,...,x_n,y)=0$$
and $f\in C^1(B)$, being $B$ an open set satisfying $B\supset A$.
Given the point $(\overline x_1,...,\overline x_n,\overline y)\in A$ s.t. $f(\overline x_1,...,\overline x_n,\overline y)=0$, suppose:
$$\frac{\partial f(\overline x_1,...,\overline x_n,\overline y)}{\partial y}\Bigg|_{(\overline x,\overline y)}\neq0$$
>This symbology means: evaluate at $(\overline x,\overline y)$ the derivative with respect to $y$.

Then, there exists a neighborhood $I(\overline x,\overline y)\subseteq A$, with $I(\overline x,\overline y)=I_\overline x\times I_\overline y$ and $I_\overline x=I_{\overline x_1}\times\dotsi\times I_{\overline x_n}$, where the implicit function $y=y(x_1,...,x_n)$ is defined and satisfies:
1. $\overline y=y(\overline x_1,...,\overline x_n)$
2. The partial derivatives $\partial y(x_1,...,x_n)/\partial x_i$, $i=1,...,n$ of $y=y(x)$ are given, in any open subset of $I(\overline x,\overline y)$, by
$$\frac{\partial y(x_1,...,x_n)}{\partial x_i}=-\frac{\frac{\partial f(x_1,...,x_n,y)}{\partial x_i}}{\frac{\partial f(x_1,...,x_n,y)}{\partial y}},\quad\forall(x,y)\in\mathring{I}(\overline x,\overline y)$$
In this case, instead of one derivative $y'(x)$, we now have $n$ partial derivatives showing how $y$ changes with respect to each $x_i$.

#### Second extension to Dini's theorem
Let $f:A\to\mathbb R^p$, $A\subseteq\mathbb R^{n+p}$, with
$$f_i(x_1,...,x_n;y_1,...,y_p)=0\quad i=1,...,p$$
and $f_i\in C^1(B)$, being $B$ an open set satisfying $B\supset A$.
Given the point $(\overline x_1,...,\overline x_n;\overline y_i,...,\overline y_p)$ s.t. $f_i(\overline x_1,...,\overline x_n;\overline y_i,...,\overline y_p)=0$, $i=1,...,p$, suppose
$$J_y(f)[\overline x_1,...,\overline x_n;\overline y_i,...,\overline y_p]=\begin{bmatrix}\frac{\partial f_1(\overline x_1,...,\overline x_n;\overline y_i,...,\overline y_p)}{\partial y_1}&\dotsi&\frac{\partial f_1(\overline x_1,...,\overline x_n;\overline y_i,...,\overline y_p)}{\partial y_p}\\\vdots&\vdots&\vdots\\\frac{\partial f_p(\overline x_1,...,\overline x_n;\overline y_i,...,\overline y_p)}{\partial y_1}&\dotsi&\frac{\partial f_p(\overline x_1,...,\overline x_n;\overline y_i,...,\overline y_p)}{\partial y_p}\end{bmatrix}$$
is nonsingular, where $J_y(f)[\overline x,\overline y]\in\mathbb R^{p\times p}$ is the Jacobian matrix of $f$, with respect uniquely to the subvector $y\in\mathbb R^p$.
Then there exists a neighborhood $I(\overline x,\overline y)\subseteq A$, with $I(\overline x,\overline y)=I_\overline x\times I_\overline y$ and $I_\overline x=I_{\overline x_1}\times\dotsi\times I_{\overline x_n}$, where the implicit function $y=y(x_1,...,x_n)$ is defined as satisfies:
1. $\overline y=y(\overline x_1,...,\overline x_n)$
2. $y\in C^1(I_x)$ and the Jacobian matrix $J(y)[x]$ satisfies
$$J(y)[x]=[J_y(f)[x;y]]^{-1}\cdot[J_x(f)[x;y]]\quad\forall (x,y)\in\mathring I(\overline x,\overline y)$$

The only difference is that there are more independent ($n$) and dependent ($p$) variables.


