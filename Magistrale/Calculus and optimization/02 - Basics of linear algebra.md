Before going forward we recall a bit of linear algebra concepts.

### Change of basis
Considering a [[Magistrale/Calculus and optimization/00 - Introduction#Linear and affine functions|linear function]] $f:\mathbb{R}^n\to\mathbb{R}^m$, we can write it as:
$$f(x)=f(x_1e_1+...+x_ne_n)=x_1f(e_1)+...+x_nf(e_n)$$
where $e_i$ is the $i$-th unit vector of the **standard basis** in $\mathbb{R}^n$:
$$e_i=\begin{pmatrix}0\\\vdots\\1\\\vdots\\0\end{pmatrix}\leftarrow i\text{-th}\quad i=1,...,n$$
and $f(e_i)$ is the vector obtained transforming $e_i$ by $f$.

Now we introduce the following notation:
$$A=\left[f(e_1)\vdots\dotsi\vdots f(e_n)\right]\in\mathbb{R}^{m\times n}$$
an recalling that we can rewrite the points $x,y\in\mathbb{R}^n$ as:
$$X=(x_1,...,x_n)^T\qquad Y=(y_1,...,y_n)^T$$

We can rewrite the previous linear function as:
$$y=f(x)\iff Y=AX$$
which states the strong relation between linear functions and matrices.

Now, there could be different basis in the same vectorial space, thinking about $\mathbb{R}^2$ we can imagine each point described by a vector, that represents the horizontal movement respect to the origin and the vertical movement to reach the defined point.

Another basis, is just a different set of "movements" that have to be made from the origin in order to reach a point, for example we could also move diagonally.

In order to represent a point in our basis into another basis we can apply a linear combination to our vector, for doing so we need a **change-of-basis matrix** that is retrieved by joining the new basis vectors.

Let $B=\{e_1,e_2,e_3\}$ be the **old basis** (in this case, the standard basis):
$$e_1=\begin{pmatrix}1\\0\\0\end{pmatrix},e_2=\begin{pmatrix}0\\1\\0\end{pmatrix},e_3=\begin{pmatrix}0\\0\\1\end{pmatrix}$$
Let $C=\{c_1,c_2,c_3\}$ be the **new basis**:
$$e_1=\begin{pmatrix}1\\1\\0\end{pmatrix},e_2=\begin{pmatrix}0\\1\\1\end{pmatrix},e_3=\begin{pmatrix}1\\0\\1\end{pmatrix}$$
The **change-of-basis matrix** is defined as:
$$P_{C\to B}=\begin{pmatrix}1&0&1\\1&1&0\\0&1&1\end{pmatrix}$$
This basis converts coordinates <u>from the new basis to the old basis</u>:
$$[x]_B=P_{C\to B}[x]_C$$

But if we compute its [[Triennale/Primo anno/Primo semestre/Algebra lineare/Matrici#Matrici inverse|inverse]], we can go <u>from the old basis to the new basis</u>:
$$P_{B\to C}=\frac{1}{2}\begin{pmatrix}1&1&-1\\-1&1&1\\1&-1&1\end{pmatrix}$$
For example if we have the vector $[x]_B=(2,1,3)^T$ in the old (standard) basis, we can convert it to the new basis in this way:
$$[x]_C=P_{B\to C}[x]_B=\frac{1}{2}\begin{pmatrix}1&1&-1\\-1&1&1\\1&-1&1\end{pmatrix}\begin{pmatrix}2\\1\\3\end{pmatrix}=\begin{pmatrix}0\\1\\2\end{pmatrix}$$
#### Rank-nullity theorem
Given the matrix $A\in\mathbb{R}^{m\times n}$ we say that:
- $R[A]$ is the **range** of $A$, that is the set of all possible linear combinations of the columns of $A$, it can be expressed as: $R[A]=\{y\in\mathbb{R}^m:\exists x\in\mathbb{R}^n s.t. y=Ax\}$
- $N[A]$ is the **null space (or kernel)** of $A$ and it represents every vector that is zeroed by $A$, that is the solutions for $Ax=0$, so $N[A]=\{x\in\mathbb{R}^n:Ax=0\}$

The **rank-nullity theorem** states that given a matrix $A\in\mathbb{R}^{m\times n}$, we have that:
$$\dim{R[A]}+\dim N[A]=rank(A)+nullity(A)=n$$
that is, the sum of dimensions of the vector spaces $R[A]$ and $N[A]$ is constant, and is equal to the second dimension of $A$ (i.e. $n$).

The intuition is that every direction in the domain either contributes to the range (i.e. produces a nonzero output), or gets zeroed (i.e. belongs to the null space).

