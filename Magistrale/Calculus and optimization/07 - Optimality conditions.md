On this chapter we aim at giving analytical conditions which explicitly allow to identify solutions of the following general optimization problem (provided that it admits solutions):
$$\min_{x\in C} f(x)$$
Assuming that $f:\mathbb{R}^n\to\mathbb R$ and the feasible set $C\subseteq \mathbb R^n$ is convex and given the point $\overline x\in C$, we say that the vector (direction) $d=y-\overline x\in\mathbb R^n$, with $y\in\mathbb R^n$ and $y\neq\overline x$, is a **feasible direction** for $C$ in $\overline x$, if the point $x-\overline x+\alpha d$ belongs to $C$, for any $\alpha\in(0,\overline\alpha]$ with $\overline\alpha >0$.

### Descent direction
Considering the function $f:\mathbb R^n\to \mathbb R$, and the vector $d\in\mathbb R^n$, with $d\neq 0$, let $\overline x\in\mathbb R^n$, we say that $d$ is a **descent direction** for $f(x)$ at $\overline x$ if there exists a value $\overline\alpha>0$ such that:
$$f(\overline x+\alpha d)<f(\overline x),\quad\forall\alpha\in(0,\overline\alpha]$$
In other words: the direction $d$ is a descent direction for $f$ at $\overline x$ if in a small enough neighborhood of $\overline x$, along the direction $d$, the function $f(x)$ is _strictly decreasing_.

**Proof**
From the [[Magistrale/Calculus and optimization/00 - Introduction#Mean value theorem|mean value theorem]] , for $\alpha\in(0,1]$ (greater than $0$ otherwise we are still on the point $\overline x$) we get:
$$\begin{align}
f(\overline{x}+\alpha d)&=f(\overline{x})+\nabla f(\overline{x})^T(\alpha d)+o(||\alpha d||)\\
&= f(\overline{x})+\alpha\nabla f(\overline{x})^Td+o(||\alpha d||)\frac{||d||}{||d||}\\
\frac{f(\overline{x}+\alpha d)-f(\overline{x})}{\alpha}&=\nabla f(\overline{x})^Td+\frac{o(||\alpha d||)}{\alpha ||d||}||d||
\end{align}$$
By using the limit $\alpha\to0^+$ at both the sides of the latter equality we obtain:
$$\begin{align}
\lim_{\alpha\to0^+}\frac{f(\overline{x}+\alpha d) -f(\overline{x})}{\alpha}&=\nabla f(\overline{x})^T d+\lim_{\alpha\to0^+}\frac{o(||\alpha d||)}{\alpha||d||}||d||\\
&=\nabla f(\overline{x})^Td
\end{align}$$
With this we proved that the directional derivative along $d$ on $\overline x$ is given by the previous formulation, we still have to prove that $d$ is a descent direction for $f$ iff $\nabla f(\overline{x})^Td<0$.

($\Rightarrow$)
Since $d$ is a descent direction, then the difference $f(\overline{x}+\alpha d) -f(\overline{x})$ will be negative, being $\alpha>0$ the ratio will be negative, hence $\nabla f(\overline{x})^Td<0$.

($\Leftarrow$)
Since $\nabla f(\overline{x})^Td<0$, this implies that the right hand side is negative, and this implies that also the left hand side will be negative.
For the ratio to be negative, it must hold that $f(\overline{x}+\alpha d) -f(\overline{x})$ must be negative, since $\alpha$ is always positive due to the limit, that difference represents the definition of descent direction, proving that $d$ is in fact a descent direction.

### Necessary condition for a local minimum
Given the minimization problem above, a **necessary condition** such that the point $\overline x\in C$ is a _local minimum_ of $f(x)$ on $C$ is that:
$$\nabla f(\overline x)^T(x-\overline x)\geq 0,\quad\forall x\in C$$
**Proof**
If $\overline x$ is a local minimum, then it must not exists any admissible descent direction in $\overline x$, hence there only must exists directions such that:
$$\nabla f(\overline x)^Td\geq 0\quad\forall d\text{ feasbile for }C$$

Now, since $C$ is convex, given any point $x\in C$ with $x\neq\overline x$, the direction $d=x-\overline x$ will be feasible, hence as a consequence, if at $\overline x$ we cannot have any direction $d$ which is both feasible for $C$ and fo descent fo $f(x)$, then we must have $\nabla f(\overline x)^T(x-x^*)\geq 0$.

### Necessary and sufficient condition for a local minimum
Given the same minimization problem above, with $C\subseteq\mathbb R^n$ convex, let $f\in C^1$ in an open set containing $C$, and let $f(x)$ be convex on $C$.
A **necessary and sufficient condition** for the point $\overline x\in C$ to be a local minimum of $f(x)$ on $C$ is that:
$$\nabla f(\overline x)^T(x-\overline x)\geq 0\quad\forall x\in C$$
**Proof**
For the necessary condition ($\Rightarrow$) we already have the proof from the _necessary condition_.
Now we have to prove the opposite side ($\Leftarrow$) assuming that $\nabla f(\overline x)^T(x-\overline x)\geq 0$.

We know that a function is convex if holds the following [[01 - Convexity#Differentiability and convex functions|inequality]]:
$$f(y)\geq f(\overline x)+\underbrace{\nabla f(\overline x)^T(x-\overline x)}_{\geq 0\text{ from the hypothesis}}\quad\forall x,y\in C$$
Proving that $\overline x$ is both local and global minimum since we are considering a convex function.