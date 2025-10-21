### Vectorial spaces
A **vectorial space** is a set $V^n(K)$ of elements (vectors) with **field** $K$ that satisfies the following properties:
$$\begin{align}
&0.\quad x+y\in V^n(K)\qquad a\bullet x\in V^n(K)&\text{closure with respect to addition and product}\\
\hline
&1.\quad \exists w\in V^n(K):x+w=x&\text{neutral element}\\
&2.\quad \exists\bar x\in V^n(K):x+\bar x=w&\text{inverse element}\\
&3.\quad x+y=y+z&\text{commutative property}\\
&4.\quad (x+y)+z=x+(y+z)&\text{associative property}\\
\hline
&5.\quad \exists\sigma\in K:\sigma\bullet x=x&\text{neutral element}\\
&6.\quad (a\odot b)\bullet x=a\bullet(b\bullet x)&\text{associative property}\\
&7.\quad (x+y)\bullet a=a\bullet x+a\bullet y&\text{distributive property}\\
&8.\quad (a\oplus b)\bullet x=a\bullet x+b\bullet x&\text{distributive property}
\end{align}$$

---
### Linear independence
A vector $z=z_1,...,z_m\in \mathbb{R}^n(\mathbb{R})$ is **linearly independent** when:
$$z=0\iff a_1=...=a_m=0$$
We can also check the independence by forming a matrix with the given vectors and calculate its **determinant**, if it is different from the null element ($0$), then they are independent.

---
### Linear combinations
Given $z_1,...,z_m\in\mathbb{R}^n$ and $a_1,...,a_m\in\mathbb{R}$, a **linear combination** is defined as:
$$z=a_1z_1+...+a_mz_m$$

An **affine combination** is a _linear combination_ where:
$$z=a_1z_1+...+a_mz_m\quad\text{with}\quad\sum_{i=1}^ma_i=1$$
![[Combinazione affine.svg|250]]

A **conical combination** is a _linear combination_ where:
$$z=a_1z_1+...+a_mz_m\quad\text{with}\quad a_i\geq 0,\space i=1,...,m$$
![[Combinazioni coniche.svg|300]]

A **convex combination** is both an _affine combination_ and a _conical combination_:
$$z=a_1z_1+...+a_mz_m\quad\text{with}\quad \sum_{i=1}^ma_i=1\quad\land \quad a_i\geq 0,\space i=1,...,m$$
![[Combinazione convessa.svg|300]]

---
### Inner product
Given a vectorial space $V^n(K)$, the **inner product** (or scalar), is a function defined as:
$$V^n(K)\times V^n(K)\to \mathbb{R}$$
It has the following properties:
1. $\forall v\in V^n(K),\quad<v,v>\geq 0$, with $<v,v> =0\iff v=0$
2. $\forall u,v,z\in V^n(K),\quad<u+v,z>=<u,z>+<v,z>$
3. $\forall u,v\in V^n(K),\quad<u,v>=<v,u>$

The **standard inner product** is defined as:
$$\forall u,v\in\mathbb{R}^n,<u,v>=u_1v_1+...u_n v_n$$
If its result is equal to $0$, then $u,v$ are **orthogonal** ($u\bot v$).
>Two orthogonal vectors are linearly independent, but the reverse is not necessarily true.

---
### Norm
Given a vectorial space $V^n(K)$, the **norm** of a vector can be imagined as the length of the vector, and it is defined as:
$$V^n(K)\to\mathbb{R}^+$$
>$\mathbb{R}^+$ indicates positive real numbers ($0$ excluded).

It has the following properties:
1. $\forall v\in V^n(K),\quad||v||\geq 0$, with $||v||=0\iff v=0$
2. $\forall v\in v^n(K),\forall\alpha\in\mathbb{R},\quad||\alpha\bullet v|| =|\alpha|\cdot||v||$
3. $\forall u,v\in V^n(K),\quad||u+v||\leq||u||+||v||$

**Euclidean norm**: $||v||_2=\sqrt{v_1^2+...+v_n^2}$
**Norm 1**: $||v||_1=|v_1|+...+|v_n|$
**Norm $\infty$**: $||v||_\infty=\max\limits_{1\leq i\leq n}|v_i|$
![[Norme.png|400]]

---
### Linear and affine functions
Given the function $f:\mathbb{R}^n\to\mathbb{R}^m$, $f(x)$ is **linear** in $\mathbb{R}^n$ if it satisfies the following properties:
1. $f(x+y)=f(x)+f(y),\quad\forall x,y\in\mathbb{R}^n$
2. $f(\lambda x)=\lambda f(x),\quad\forall x\in\mathbb{R}^n$

Given the function $g:\mathbb{R}^n\to\mathbb{R}$, $g(x)$ is **affine** in $\mathbb{R}^n$ if there exists a _linear function_ $f(x)\in\mathbb{R}^n$ and a vector $\overline c\in\mathbb{R}$ such that:
$$g(x)=f(x)+\overline c$$

---
### Directional derivatives
Considering a function $f(x)\in C^1(\mathbb{R}^n)$, the **directional derivative** $D(f,d)$, along the **directional vector** $d\in\mathbb{R}^n$ is defined as:
$$D(f,d)\stackrel{\Delta}{=}\lim_{h\to 0}\frac{f(x+hd)-f(x)}{h}=\nabla f(x)^Td$$

---
### Mean value theorem
We can imagine the **mean value theorem** as a function used to predict the state in a point $y$ starting from the point $x$, with $x,y\in\mathbb{R}^n$:
$$f(y)=f(x)+\nabla f(x)^T(y-x)+o(||y-x||)$$

we can also formulate the theorem as:
$$f(y)=f(x)+\nabla f[x+\theta(y-x)]^T(y-x)\quad\theta\in[0,1]$$
where in this case there _must exist at least_ a $\theta$ between $0$ and $1$.

The geometric representation of the theorem is depicted as it follows:
![[Valor medio.svg]]

#### Mean value theorem (second order)
In this case we are interested in the **change of change** along the conjunctive between $x$ and $y$.

The two formulations can be written as:
$$f(y)=f(x)+\nabla f(x)^T(y-x)+\frac{1}{2}(y-x)^T\nabla^2 f(x)(y-x)+o(||y-x||)^2$$
$$f(y)=f(x)+\nabla f(x)^T(y-x)+\frac{1}{2}(y-x)^T\nabla^2 f[x+\theta (y-x)](y-x)\quad \theta\in[0,1]$$

---
### Minima/maxima - local/global
From the [[Funzioni continue#Teoremi fondamentali sulle funzioni continue|Weierstrass theorem]]:
given the function $f(x)$ with $f:\mathbb{R}^n\to\mathbb{R}^n$, let $f(x)$ continuous over the set $A\subset\mathbb{R}^n$, which is closed and limited (i.e. compact), then $f(x)$ admits a global minima and maxima on $A$.
>A function might  admit a minima and maxima even if the theorem is violated, but we are sure they exists if the theorem is valid.


Given the set $C\subseteq\mathbb{R}^n$ and the function $f:\mathbb{R}^n\to\mathbb{R}$, let $x^*\in C$ and $I(x^*,\rho)\stackrel{\Delta}{=}\{x\in\mathbb{R}^n, ||x-x^*||_* \leq \rho\}$.

$x^*$ is a **local minima** if:
$$f(x^*)\leq f(x),\quad\forall x\in I(x^*,\rho)\cap C$$
and in the case that $f(x^*) < f(x)$, we would have a **strict local minima**, or in the case that property is applicable $\forall x\in C$, then we would have a **global minima**, if both previous statements hold at the same time, we would then have a **unique global minima**.

Same thing applies for the **local maxima**:
$$f(x^*)\geq f(x),\quad\forall x\in I(x^*,\rho)\cap C$$
![[Massimi e minimi.svg|500]]

