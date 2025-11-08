Let's consider the _functions_:
$$x_i(t):\mathbb{R}\to\mathbb{R},\quad i=1,...,n$$
Each $x_i(t)$ gives the $i$-th coordinate of a point, depending on the parameter $t$, which runs over an interval $[a,b]\subset\mathbb{R}$.
>As $t$ changes, the point moves along a path.


By combining all those coordinate functions into one **vector function**:
$$x(t)=\begin{pmatrix}x_1(t)\\\vdots\\x_n(t)\end{pmatrix}\in\mathbb{R}^n$$
as $t$ changes it traces a path, called **curve** (not necessarily something that bends) in that space.

Unlike normal functions like $f(x)=x$, which cannot overlap with themselves, in this case we are describing each coordinate in the vector space with a specific function,
so in $\mathbb{R}^2$ we can describe a circle using a _vector function_ composed by two functions, that is:
$$x(t)=\begin{pmatrix}\cos(t)\\\sin(t)\end{pmatrix}\in\mathbb{R}^2$$

**Proposition**
Given the curve $x(t)$ of $\mathbb{R}^n$, for any $t\in[a,b]\subseteq\mathbb{R}$, we say that the curve $x(t)$ is **regular**, that is, smoothly traced without breaks or overlapping points, if it satisfies the following conditions:
1. $x_i(t)\in C^1([a,b])$, for any $i=1,...,n$, and for any $t\in[a,b]$
	The curve is differentiable, so it is smooth with no jumps.
2. $\sum\limits_{i=1}^{n}[x_i'(t)]^2\neq 0$, for any $t\in[a,b]$
	The point on the curve never stops moving (i.e. the derivatives are never simultaneously zero).
3. Given the couple $t_1,t_2\in[a,b]$, with $t_1\neq t_2$, we have $x(t_1)\neq x(t_2)$
	The curve never passes through the same point twice.

### Tangent to a curve
Considering the regular curve $C\in\mathbb{R}^n$, given by the point $x(t)\in\mathbb{R}^n$, for $t\in[a,b]$.
Then we say that the line $\ell'\in\mathbb{R}^n$, with the equations:
$$\ell':\frac{x_1-x_1(t)}{x'_1(t)}=\dotsi=\frac{x_n-x_n(t)}{x'_n(t)}$$
is the **tangent line** to the curve $C$.

It can be interpreted as $x(t)$ being the curve that passes through the point $x(t)$, while the velocity vector $x'(t)$ gives the direction in which the curve is moving at that point, so the tangent line, passes through $x(t)$ and has direction vector $x'(t)$.

We also define the **normal hyperplane** $\pi$ to the curve $C$ at $x(t)$ with the following equation:
$$\pi:[x_1-x_1(t)]\cdot x_1'(t)+\dotsi+[x_n-x_n(t)]\cdot x_n'(t)$$
it represents an $n-1$ dimensional flat surface that is perpendicular to some direction, here that direction is the tangent vector $x'(t)$.
![[Tangent and hyperplane to a curve.png|400]]
>The image is in $\mathbb{R}^3$, but represented in 2D for simplicity.


