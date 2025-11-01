Given the linear function $f:\mathbb{R}^n\to\mathbb{R}^m$ and the matrix $A^{m\times n}$ associated with $f(x)$, which has $n$ columns to match the input space, and $m$ rows to match the output space:
-  $f(x)$ is **injective** (one-to-one) if $rank(A)=n$
	This means that the columns are linearly independent, and that $\ker=0$, this implies that $f(x)=0\iff x=0$, therefore if $f(x_1)=f(x_2)$, then $f(x_1-x_2)=0$, so $x_1-x_2=0$, meaning that $x_1=x_2$, this shows that for different inputs we get different outputs unless the input is the same.
- $f(x)$ is **onto (surjective)** if $rank(A)=m$
	This means that the rows are linearly independent and thus the columns span all of $\mathbb{R}^m$, that is, every vector of $\mathbb{R}^m$ can be written as a linear combination of the columns, so every output is actually achieved by some input.

### Linear transformations
A **homomorphism** is a structure-preserving map between two algebraic structures.
Considering $f:V\to W$, it is a homomorphism if:
- $f(x+y)=f(x)+f(y)$
- $f(c\cdot x)=c\cdot f(x)$, $c\in\mathbb{R}$

By the definition of [[Magistrale/Calculus and optimization/00 - Introduction#Linear and affine functions|linear functions]], we can state that every linear function is an homomorphism.

An **endomorphism** is a _homomorphism_ where the domain and codomain are the same space, for example the linear function $f:V\to V$.

And **automorphism** is an _endomorphism_ that is also **bijective** (injective and onto).

### Eigenvectors and eigenvalues
Let the linear function $f:V^n(K)\to V^n(K)$ be an endomorphism, then in case:
$$f(v)=\lambda v,\quad\lambda\in K,\quad v\neq 0_V$$
we say that:
- $v$ is an **eigenvector** of the linear function $f$
- $\lambda$ is an **eigenvalue** of the linear function $f$
>$0_V$ is the null vector of the space $V^n(K)$.

In words, an eigenvector is a special vector that does not change direction when the linear transformation is applied to it, and thus it only gets scaled.

The equation above states that when applying $f$ to $v$, we get the same vector $v$, just multiplied for some scalar $\lambda$.
So $v$ is a special direction that $f$ only scales by a factor of $\lambda$.

This is the same case for matrices, so let's consider the matrix $A\in\mathbb{R}^{n\times n}$, then if:
$$Av=\lambda v,\quad\lambda\in K,\quad v\neq0_V$$
we say that $v$ is an eigenvector of $A$ and $\lambda$ and eigenvalue of $A$.

>[!Example]
>Find the eigenvectors and eigenvalues of the matrix.
>$$A=\begin{pmatrix}3&6\\1&2\end{pmatrix}$$
>We have to computer the pairs $(\lambda_i,v_i)$ s.t. $Av_i=\lambda_iv_i$ with $v_i\neq0$ and being $v_i=(v_{i1}\space v_{i2})^T$.
>
>$$\begin{pmatrix}3&6\\1&2\end{pmatrix}\begin{pmatrix}v_{i1}\\v_{i2}\end{pmatrix}=\lambda_i\begin{pmatrix}v_{i1}\\v_{i2}\end{pmatrix}$$
>which yields:
>$$\begin{cases}(3-\lambda_i)v_{i1}=-6v_{i2}\\v_{i1}=(\lambda_i-2)v_{i2}\end{cases}\implies \lambda_i^2-5\lambda_i=0$$
>Which admits the solutions (_eigenvalues_) $\lambda_1=0$ and $\lambda_2=5$.
>Then by first setting $\lambda_1=0$ we obtain the _eigenvector_:
>$$v_1=p_1\begin{pmatrix}-6\\3\end{pmatrix},\quad p_1\in\mathbb{R}$$
>while by setting $\lambda_2=5$ we obtain the _eigenvector_:
>$$v_2=p_2\begin{pmatrix}3\\1\end{pmatrix},\quad p_2\in\mathbb{R}$$
>
>---
>Now we just want to compute the eigenvalues of the matrix, but this time we'll use another approach.
>If $\lambda$ is an eigenvalue, then there's a direction $v$ where $Av=\lambda v$, this means $(A-\lambda I)v=Av-\lambda v=0$.
>$$A=\begin{pmatrix}1&0&0\\0&1&2\\0&2&1\end{pmatrix}$$
>
>We want $\det(A-\lambda I)=0$ in order to get non-zero solutions for $v$, we do this because if the matrix is singular ($\det=0$) it means that it can send some non-zero vectors to zero, and then we can retrieve the values $\lambda$.
>$$0=\det(A-\lambda I)=(1-\lambda)\begin{vmatrix}1-\lambda&2\\2&1-\lambda\end{vmatrix}=(1-\lambda)(\lambda^2-2\lambda-3)$$
>which has the $n=3$ solutions:
>$$\begin{cases}\lambda_1=1\\\lambda_2=-1\\\lambda_3=3\end{cases}$$

