In this section we deal with the solution of the following general nonlinear programming problem:
$$\min_{x\in X}f(x)\quad(\spadesuit)$$
where the feasible set $X\subseteq\mathbb{R}^n$ is explicitly defined throughout a finite number of equalities and/or inequalities, such as:
$$X:\begin{cases}h_j(x)=0&j=1,...,p\\g_i(x)\leq 0&i=1,...,m\end{cases}$$
Observe that this problem has a very general structure, and we do not assume convexity/concavity for $f(x)$ or any of the constraints functions.

In this regard, note that if the problem was convex, there are efficient methods in the literature called _feasible direction methods_.

Most of the optimization methods proposed in the literature, typically can guarantee to detect _stationary points_ (which may not be a minima), that is, points which satisfy the **first order optimality conditions**.

Before going forward, we report some definitions.

Given the problem above and the point $x^*\in X$, we define the set $I(x^*)$ of the **active constraints** at $x^*$, as the set of indices of the constraints which satisfy:
$$I(x^*)=\{j:h_j(x^*)=0,\quad j=1,...,p\}\cup\{i:g_i(x^*)=0,\quad i=1,...,m\}$$
In words, $I(x^*)$ represents the geometric boundaries of the feasible set that pass through $x^*$.

Now, always referring to $(\spadesuit)$, we introduce _additional variables_ $\lambda_0\in\mathbb R,\lambda\in\mathbb R^p$ and $\mu\in\mathbb R^m$ and we define the **Lagrangian function** $\mathcal L(x,\lambda_0,\lambda,\mu)$ as:
$$\mathcal L(x,\lambda_0,\lambda,\mu)=\lambda_0 f(x)+h(x)^T\lambda +g(x)^T\mu$$
where $\lambda=(\lambda_1,...,\lambda_p)^T$ and $\mu=(\mu_i,...,\mu_m)^T$.

These additional variables are called **Lagrange multipliers**:
- The scalar $\lambda_0$ is associated with the objective function $f(x)$
- The vector $\lambda$ contains one multiplier for each equality constraint $h_j(x)=0$
- The vector $\mu$ contains one multiplier for each inequality constraint $g_i(x)\leq 0$

Using these multipliers, we build a single _Lagrangian function_, which combines the objective function and all the constraints into one expression, by taking a weighted sum of them.
>In essence, we reformulate the original optimization problem as a single function whose behavior captures both the goal of minimizing $f(x)$ and the influence of the constraints.

**Observation**
If from the constraints in $(\spadesuit)$ we remove those constraints which are not active at the solution $x^*$, then the solution will not change, thus it is expected that just the active constraints at the solution will play a relevant role in the optimality conditions for $(\spadesuit)$.

---
### Fritz-John optimality conditions
Given the problem ($\spadesuit$), let $f:\mathbb R^n\to \mathbb R$, $h:\mathbb R^n\to\mathbb R^p$ and $g:\mathbb R^n\to\mathbb R^m$, with $f(x)$, $h(x)$ and $g(x)$ continuously differentiable in an open set containing $X$.
Let $x^*$ be a local minimum of $f(x)$ on the set $X$, then there exists a vector $(\lambda_0^*,\lambda^*,\mu^*)\in\mathbb R\times\mathbb R^p\times\mathbb R^m$ such that:
$$\begin{align}
\lambda_0^*\nabla f(x^*)+\sum_{j=1}^p\lambda_j^*\nabla h_j(x^*)+\sum_{i=1}^m\mu_i^*\nabla g_i(x^*)=0\quad(1)\\
h_j(x^*)=0,\quad j=1,...,p\quad(2)\\
g_i(x^*)\leq 0,\quad i=1,...,m\quad(3)\\
\mu_i^*g_i(x^*)=0,\quad i=1,..., m\quad(4)\\
(\lambda_0^*,\lambda^*,\mu^*)\neq 0\quad(5)\\
(\lambda_0^*,\mu^*)\geq 0\quad(6)
\end{align}$$
We call $(\lambda_0^*,\lambda^*,\mu^*)$ the **vector of generalized Lagrange multipliers**, while we call $(x,\lambda_0^*,\lambda^*,\mu^*)$ a **Fritz-John** point.

In $(1)$ we define the **gradient condition**, which is a weighted combination of all gradients equal to zero, it is possible to see that $\lambda_0^*$ _might be zero_, this implies that the gradient of the objective function in $(1)$ may not appear in the optimality conditions, this is problematic, since changing the objective function would always lead to the same solution.

To ensure $\lambda_0^*\neq 0$ we can impose additional requirements, called **constraint qualifications conditions**, and among many others, the following three are well known.
1. **Linear Independence Constraint Qualification (LICQ)**
	_Condition_: the gradients of the active constraints at $x^*$ are linearly independent
	$$\{\nabla h_j(x^*), \nabla g_i(x^*) \space|\space j,i \in I(x^*)\}\quad\text{linearly independent}$$
	This works because if the gradients are independent and $\lambda_0^*=0$, then the equation $(1)$ implies all $\lambda_j^*=0$ and $\mu_i^*=0$ for active constraints, contradicting $(5)$

2. **Mangasarian-Fromowitz Constraint Qualification (MFCQ)**
	_Conditions_ (weaker than LICQ):
	- The gradients $\{\nabla h_j(x^*)\}$ of equality constraints are linearly independent
	- There exists a vector $d\in\mathbb R^n$ such that:
		- $\nabla g_i(x^*)^Td<0\quad\forall i\in I(x^*)$
		- $\nabla h_j(x^*)^Td=0\quad\forall j=1,...,p$
	
	In words it says that there's a direction that points strictly into the feasible region.

3. **Linearity (or affinity) of Equality constraints and Concavity of Inequality constraints (LECI)**
	It is equal to say that for any $\alpha\in[0,1]$ and for any $x,y\in X$:
	- $h_j(x)=c_j^Tx\quad c_j\in\mathbb R^n\quad \forall j=1,...,p$
	- $g_i[\alpha x+(1-\alpha)y]\geq\alpha g_i(x)+(1-\alpha)g_i(y)\quad\forall i\in I(x^*)$
	
	This essentially says the feasible region is convex.

>[!Important] Fritz-John conditions are only necessary
>The Fritz-John conditions alone are **necessary but not sufficient** because they allow $\lambda_0^*=0$.
>By imposing constraint qualifications, we ensure $\lambda_0^*\neq0$.

### Karush-Kuhn-Tucker optimality conditions
Given the general optimization problem $(\spadesuit)$, let $f:\mathbb R^n\to \mathbb R$, $h:\mathbb R^n\to\mathbb R^p$ and $g:\mathbb R^n\to\mathbb R^m$, with $f(x)$, $h(x)$ and $g(x)$ continuously differentiable in an open set containing $X$.
Let $x^*$ be a local minimum of $f(x)$ on $X$. If **any** of the above _constraint qualification conditions_ is satisfied at $x^*$, then there exists a vector $(\lambda^*,\mu^*)\in\mathbb R^p\times\mathbb R^m$ such that:
$$\begin{align}
(\diamondsuit)\\
\nabla f(x^*)+\sum_{j=1}^p\lambda_j^*\nabla h_j(x^*)+\sum_{i=1}^m\mu_i^*\nabla g_i(x^*)=0\quad(1)\\
h_j(x^*)=0,\quad j=1,...,p\quad(2)\\
g_i(x^*)\leq 0,\quad i=1,...,m\quad(3)\\
\mu_i^*g_i(x^*)=0,\quad i=1,..., m\quad(4)\\
\mu^*\geq0\quad(5)
\end{align}$$

Compared to the Fritz-John optimality conditions, now the constraint qualification ensures $\lambda_o^*\neq0$, now the gradient of the objective function definitively appears in the conditions.

In particular, if LICQ is satisfied at $x^*$, then there exists a **unique vector** of generalized Lagrange multipliers $(\lambda^*,\mu^*)\in\mathbb R^p\times\mathbb R^m$ satisfying the above conditions.
The vector $(x^*,\lambda^*,\mu^*)$ is a so called **Karush-Kuhn-Tucker point**.

Now we discuss a proposition that gives **sufficient optimality conditions**, that means, if these conditions hold, we can guarantee that $x^*$ is a local (and global) minimum.

Given the general optimization problem $(\spadesuit)$, let $f:\mathbb R^n\to \mathbb R$, $h:\mathbb R^n\to\mathbb R^p$ and $g:\mathbb R^n\to\mathbb R^m$, with $f(x)$, $h(x)$ and $g(x)$ continuously differentiable in an open set containing $X$.
Let $f(x)$ be _convex_ on $X$, $g_i(x)$ be _convex_ on $X$, $i=1,...,m$ and let $h_j(x)$ be _linear (affine)_ $j=1,...,p$. If there exists vectors $\lambda^*\in\mathbb R^p$ and $\mu^*\in\mathbb R^m$ such that the conditions $(\diamondsuit)$ at $x^*$ hold.

Then $x^*$ is a local (and global) minimum of $(\spadesuit)$.
In particular, if $f(x)$ is also _strictly convex_ on $X$, then $x^*$ is the unique local (global) minimum of $(\spadesuit)$.
