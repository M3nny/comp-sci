Given the set $C\subseteq\mathbb{R}^n$, we'll say that it is **convex** if:
$$\alpha x+(1-\alpha)y\in C,\quad \forall x,y,\in C,\quad\forall\alpha\in[0,1]$$

That is, given **any** pair of point in the set $C$, the segment of points (convex combination) that connects them is inside of the set.
![[Insiemi convessi.svg|500]]

We also **assume** that the empty set $\emptyset$ is convex since it does not negate the definition of a convex set.

**Proposition**:
Given the convex sets $C_1,...,C_m$, then their **intersection**:
$$C=C_1\cap...\cap C_m$$
is also convex.

**Proof**:
we want to prove that the segment $[x,y]$ is inside the intersection of the sets, if this were true, then $x,y\in C_1$ which is convex, it follows that $[x,y]\subseteq C_1$, it is possible to make the same reasoning for each set.
Given that $[x,y]$ is contained in each set separately, then it is contained in the intersection, that is $[x,y]\subseteq C$.

### Convex functions
Given the function $f:\mathbb{R}^n\to\mathbb{R}$, and the convex set $C\subseteq\mathbb{R}^n$, $f$ is **convex on the set** $C$, if $\forall x,y,\in C$, the following property holds:
$$f[\alpha x+(1-\alpha)y]\leq \alpha f(x)+(1-\alpha)f(y)\quad\forall\alpha\in[0,1]$$

The function $f$ is said to be **strictly convex** on $C$ if the above inequality is strict (<).

An example of a strict convex function is the following:
![[Funzione convessa.svg|500]]

**Proposition**:
Given the function $f:\mathbb{R}^n\to\mathbb{R}$, and the convex set $C\subseteq\mathbb{R}^n$, if $f$ is convex on $C$, then, $-f(x)$ is concave on $C$.

**Proof**:
By the convexity of $f(x)$ we obtain:
$$f[\alpha x+(1-\alpha)y]\leq \alpha f(x)+(1-\alpha)f(y),\quad\forall x,y\in C,\quad \forall\alpha\in[0,1]$$
hence, multiplying by $-1$ both sides we obtain:
$$-f[\alpha x+(1-\alpha)y]\geq \alpha[-f(x)]+(1-\alpha)[-f(y)],\quad x,y\in C,\quad\forall\alpha\in[0,1]$$

which is the definition of concavity for the function $-f(x)$ on the set $C$.

**Proposition**: given the affine function $f:\mathbb{R}^n\to\mathbb{R}$, it follows that $f(x)$ is both concave and convex on $\mathbb{R}^n$.

#### Level set
Given the function $f(x)$ with $f:\mathbb{R}^n\to\mathbb{R}$, convex on $\mathbb{R}^n$, the **level set** (eventually empty) $\mathcal{L}_\gamma$ defined as:
$$\mathcal{L}_\gamma = \{x\in\mathbb{R}^n: f(x)\leq \gamma\}$$
is **convex** for each $\gamma\in\mathbb{R}$.
![[Insieme di livello.svg|400]]

#### Level curve
Given the function $f(x)$ with $f:\mathbb{R}^n\to\mathbb{R}$, and the real parameter $\gamma\in\mathbb{R}$, we define the **level curve** $c_\gamma$ of $f(x)$ as the set (possibly empty):
$$c_\gamma=\{x\in\mathbb{R}^n:f(x)=\gamma\}$$

### Combinations of convex functions
Given the convex set $C\subseteq\mathbb{R}^n$, let $f_i(x)$, $i=1,...,m$ be convex functions on $C$, and let be given the coefficients $\lambda_i\geq 0$, then the functions:
$$f(x)=\sum_{i=1}^m\lambda_i f_i(x)\quad\text{(sum of convex functions)}$$
$$f(x)=\max_{1\leq i\leq m}\{\lambda_if_i(x)\}\quad\text{(maximum of convex functions)}$$
are convex on $C$.

The second result is particularly useful when using a **penalty framework**, which involves the <u>transformation of a constrained problem into a unconstrained penalized problem</u>:
$$\begin{align}
\min\space& f(x)\\
&g(x)\leq 0
\end{align}
\Longrightarrow
\min f(x)+\sum_{i=1}^np\cdot\max[0,g_i(x)]\quad p_i\geq 0$$

#### Differentiability and convex functions
Given the non-empty set $C\subseteq\mathbb{R}^n$ and $f:\mathbb{R}^n\to\mathbb{R}$ that is _twice continuously differentiable_, then $f(x)$  is **convex** on $C$ iff $\forall x,y,\in C$, any of the following conditions is satisfied:
1. $f(y)\geq f(x)+\nabla f(x)^T (y-x)$
2. $[\nabla f(y) -\nabla f(x)]^T(y-x)\geq 0$ (rewriting of $1.$)
3. 3. $(y-x)^T \nabla^2 f(x)(y-x)\geq 0$

### Local minima also global in convex functions
Given the function $f(x)$ with $f:\mathbb{R}^n\to\mathbb{R}$ that is convex on $C\subseteq\mathbb{R}^n$.
Then **any local minimum** $x^*\in C$ for the problem $\min\limits_{x\in C} f(x)$ is also a **global minimum** for the same problem.

In addition, the **set of solutions** for that problem is **convex**.