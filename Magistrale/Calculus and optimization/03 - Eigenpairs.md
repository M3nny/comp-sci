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

## Eigenvectors and eigenvalues
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
>We have to compute the pairs $(\lambda_i,v_i)$ s.t. $Av_i=\lambda_iv_i$ with $v_i\neq0$ and being $v_i=(v_{i1}\space v_{i2})^T$.
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

In the previous example we used the following equation:
$$\det(A-\lambda I)=0$$
this is defined as the **secular (or characteristic)** equation associated to the matrix $A$, the values $\lambda$ that solve it, are the _eigenvalues_ of the matrix $A$.

**Proposition**
Let be given the matrix $A\in\mathbb{R}^{n\times n}$, then the next properties hold:
- If $(\lambda, v)$ is an eigenpair of $A$, then $(\lambda^k,v)$ is an eigenpair of $A^k$, for any integer $k\geq 1$
	When $k=1$ then $A^1v=\lambda^1v$, being $(\lambda,v)$ an eigenpair of $A$, and assuming that for any positive integer $k$ it is:
	$$A^{k-1}v=\lambda^{k-1}v,\quad v\neq 0$$
	we prove the result for index $k$, and indeed we have:
	$$A^kv=A(A^{k-1}v)=A(\lambda^{k-1}v)=\lambda^{k-1}Av=\lambda^kv$$
	
- If $A$ is _nonsingular_ ($\det\neq0$) and $(\lambda,v)$ is an eigenpair of $A$, then $(\lambda^{-1},v)$ is an eigenpair of $A^{-1}$, for any integer $k\geq 1$
	We have that $Av=\lambda v$, and since $A$ is nonsingular, <u>it does not admit any zero eigenvalue</u>, hence $\lambda\neq0$ and multiplying (on the left) the expression $Av=\lambda v$ by $A^{-1}$ we obtain:
	$$\cancel{A^{-1}}\cancel Av=\lambda A^{-1}v\implies v=\lambda A^{-1}\implies\frac{1}{\lambda}v=A^{-1}v$$

### Multiplicity
Let $A\in\mathbb{R}^{n\times n}$ and let $\lambda$ be an eigenvalue of $A$, we define the **algebraic multiplicity** of $\lambda$ $am(\lambda)$ and the **geometric multiplicity** of $\lambda$ $gm(\lambda)$ according to the following:
- $am(\lambda)$ is the multiplicity of $\lambda$ as a root of the secular equation
- $gm(\lambda)$ is the [[02 - Basics of linear algebra#Rank-nullity theorem|nullity]] of the matrix $A-\lambda I$

Note that it is always true that:
$$1\leq gm(\lambda)\leq am(\lambda)$$

## Diagonal matrices
Given the square matrix $A\in\mathbb{R}^{n\times n}$, we say that $A$ is **diagonalizable (or generalizable)** in $\mathbb{R}$ if there exists a nonsingular matrix $C\in\mathbb{R}^{n\times n}$, s.t. the matrix $C^{-1}AC$ has all real entries and is diagonal.

The matrix $A$ is diagonalizable in $\mathbb{R}$ iff:
1. $A$ has only real eigenvalues
2. $am(\lambda)=gm(\lambda)$ for every eigenvalue $\lambda$ of $A$

Generally it is digonalizable (not strictly on $\mathbb{R}$) if the second point holds.

>[!Tip] Eigenvalues and determinant
>- The product of eigenvalues is equal to the determinant of the matrix
>- The [[Triennale/Primo anno/Primo semestre/Algebra lineare/Matrici#Traccia|trace of a matrix]] is equal to the sum of the eigenvalues


>[!Tip] Block diagonal matrix and Binet's theorem
>It is possible to easily calculate the determinant of matrices in the following form:
>$$A=\begin{pmatrix}A_1&0&0\\0&A_2&0\\0&0&A_3\end{pmatrix}$$
>where $A_1$ are square matrices.
>
>Its determinant can be computed as follows:
>$$\det(A)=\prod_{i=1}^n \det(A_i)$$
>
>For example:
>$$
>A =
>\begin{bmatrix}
>1 & 2 & 0 \\
>2 & 1 & 0 \\
>0 & 0 & -4
>\end{bmatrix}
>=
>\begin{bmatrix}
>\begin{array}{cc|c}
>1 & 2 & 0 \\
>2 & 1 & 0 \\ \hline
>0 & 0 & -4
>\end{array}
>\end{bmatrix}
>=
>\begin{bmatrix}
>B & 0 \\
>0 & C
>\end{bmatrix},
>\quad
>B =
>\begin{bmatrix}
>1 & 2 \\
>2 & 1
>\end{bmatrix}, \;
>C = [-4]
>$$
>$$\det(A)=\det(B)\det(C)=-3(-4)=12$$

Once a matrix is in its diagonalized form, it is possible to **compute its powers** easily, in fact:
$$A^{n}=PD^nP^{-1}$$
where $D^n$ is just the eigenvalues raised to the $n$-th power on the diagonal.

### Symmetric matrices
If the square matrix $A\in\mathbb{R}^{n\times n}$ is **symmetric** (i.e. $A=A^T$), then:
- All its eigenvalues are real
- $A$ is diagonalizable with $C^{-1}AC$, where $C=(\frac{v_1}{||v_1||_2}\vdots\dotsi\vdots\frac{v_n}{||v_n||_2})$
- Its eigenvectors are orthogonal
- $V^{-1}=V^T$

Considering the real eigenvalues of a symmetric matrix:
- If every eigenvalue is _positive_, then $A$ is a _positive definite_ ($A\succ 0$) matrix
- If the eigenvalues are all _nonnegative_, then $A$ is a _positive semi-definite_ ($A\succeq 0$) matrix
- If the eigenvalues have an unspecified sign, then $A$ is an _indefinite_ matrix

>[!Example] Diagonal matrix representation
>We'll now show how to represent a diagonalized matrix using as a reference a symmetric matrix in order to also show its easier diagonalization procedure.
>$$A=\begin{pmatrix}2&1\\1&2\end{pmatrix}$$
>It is possible to represent a diagonalized matrix as:
>$$A=PDP^{-1}$$
>Where:
>- $P$: matrix of eigenvectors
>- $D$: diagonal matrix of eigenvalues
>
> We find the eigenvalues with:
> $$\det\begin{pmatrix}2-\lambda&1\\1&2-\lambda\end{pmatrix}=(2-\lambda)^2-1=0$$
> $$\lambda_1=3\quad\lambda_2=1$$
> 
> We find the eigenvectors:
> $$v_1=\begin{pmatrix}1\\1\end{pmatrix}\quad v_2=\begin{pmatrix}1\\-1\end{pmatrix}$$
> Now we can form $P$, $D$ and $P^{-1}$:
>$$P=\begin{pmatrix}1&1\\1&-1\end{pmatrix}\quad
>D=\begin{pmatrix}3&0\\0&1\end{pmatrix}\quad
>$$
>---
>**General approach**
>Now we compute $P^{-1}$:
>$$\det(P)=-2\quad P^{-1}=\frac{1}{-2}\begin{pmatrix}-1&-1\\-1&1\end{pmatrix}=\begin{pmatrix}1/2&1/2\\1/2&-1/2\end{pmatrix}$$
>Now we have all the elements to represent $A$ in its diagonalized form, in order to show that this is correct, we compute $D$, starting by computing $AP$:
>$$AP=\begin{pmatrix}2&1\\1&2\end{pmatrix}\begin{pmatrix}1&1\\1&-1\end{pmatrix}\quad=\begin{pmatrix}3&1\\3&-1\end{pmatrix}$$
>And finally we can retrieve $D$ from the diagonalized form showing that the calculations were correct:
>$$D=P^{-1}AP=\begin{pmatrix}1/2&1/2\\1/2&-1/2\end{pmatrix}\begin{pmatrix}3&1\\3&-1\end{pmatrix}=\begin{pmatrix}3&0\\0&1\end{pmatrix}$$
>
>---
>**Symmetric matrix approach**
>Since $A$ is symmetric, its eigenvectors are orthogonal, by normalizing them with $\frac{v}{||v||_2}$ we can get an orthonormal set of eigenvectors, this mean that $P$ becomes an orthogonal matrix where $P^{-1}=P^T$, this is useful because it allows to skip the computation of $P^{-1}$, in fact we can represent the diagonalized matrix as:
>$$A=PDP^T$$
>
>Let's compute the normalized vectors:
>$$u_1=\frac{v_1}{||v_1||_2}=\frac{1}{\sqrt2}\begin{pmatrix}1\\1\end{pmatrix}\quad u_2=\frac{v_2}{||v_2||_2}=\frac{1}{\sqrt2}\begin{pmatrix}1\\-11\end{pmatrix}$$
>$$P=(u_1\space u_2)=\begin{pmatrix}1/\sqrt2&1/\sqrt2\\1/\sqrt2&-1/\sqrt2\end{pmatrix}$$
>Now we can demonstrate that the steps were correct by retrieving $D$ (we omit the computation of $P^T A$ to keep it short)
>$$D=P^TAP=\begin{pmatrix}3/\sqrt2&3/\sqrt2\\1/\sqrt2&-1/\sqrt2\end{pmatrix}\begin{pmatrix}1/\sqrt2&1/\sqrt2\\1/\sqrt2&-1/\sqrt2\end{pmatrix}=\begin{pmatrix}3&0\\0&1\end{pmatrix}$$


