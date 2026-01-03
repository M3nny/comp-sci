Given the general nonlinear function $f$, we first introduce some basics on numerical optimization with a focus on the solution of the following unconstrained optimization problem:
$$\min_{x\in\mathbb R^n}f(x)\quad(\spadesuit)$$
We are interested to understand what happens to the sequence $\{x_k\}$ with $x_k\in\mathbb R^n$ when $k$ increases, when $n=1$ we may have:
1. $x_k=\frac{1}{k}\in\mathbb R$: then we have $\lim\limits_{k\to\infty}\frac{1}{k}=0$ so that the sequence is _convergent_
2. $x_k=\frac{1}{3}\in\mathbb R$: the sequence contains the same value for every index, the we have $\lim\limits_{k\to\infty}\frac{1}{3}=\frac{1}{3}$ so that again the sequence is _convergent_
3. $x_k=(-1)^k\in\mathbb R$: the sequence contains only two values for all the indices ($-1$ or $1$), and we have that the limit $\lim\limits_{k\to\infty}(-1)^k$ does not exist, so it _does not converge_


We want to study the third case with reference to an infinite subsequence $\mathcal K$:
$$\{x_k\}_\mathcal K=\{x_k:k\in\mathcal K,\mathcal K\subseteq\{0,1,2,...\}\}\subseteq\{x_k\}$$

Choosing even/odd indices:
$$\mathcal K_1=\{0,2,4,6,...\}\quad\mathcal K_2=\{1,3,5,7,...\}$$
we have:
$$\lim_{k\in\mathcal K_1,k\to\infty}(-1)^k=+1\quad\lim_{k\in\mathcal K_2,k\to\infty}(-1)^k=-1$$
Thus, even if the original sequence $\{(-1)^k\}$ does not admit a limit, we can address the limits for the subsequences of even/odd numbers, furthermore we can say that $+1$ and $-1$ are **limit points** of the original sequence.

**Definition**
Given the sequence $\{x_k\}$ with $x_k\in\mathbb R^n$, we say that $\{x_k\}$ **converges to** $x^*\in\mathbb R^n$ (i.e. $\{x_k\}$ _admits the limit_) if:
$$\forall\epsilon,\exists k_\epsilon\geq0:\forall k>k_\epsilon\implies ||x_k-x^*||_2<\epsilon$$
In words: once the sequence gets close to $x^*$, it never leaves the neighborhood $\epsilon$.

**Definition**
Given the sequence $\{x_k\}$ with $x_k\in\mathbb R^n$, we say that $\{x_k\}$ **admits the limit point** (or **cluster point**) $\overline x\in\mathbb R^n$ if:
$$\forall\epsilon>0,\exists k_\epsilon\geq0:\exists k>k_\epsilon,\implies ||x_k-\overline x||_2<\epsilon$$
In words: the sequence keeps coming back close to $\overline x$, but it may also move far away again.

**Definition**
The sequence $\{x_k\}$ with $x_k\in\mathbb R^n$ $k=0,1,2,...$ is **convergent** iff:
$$\lim_{k\to\infty}\inf x_k=\lim_{k\to\infty}\sup x_k=\lim_{k\to\infty} x_k$$
- $\inf x_k$: smallest value the sequence can still approach from index $k$ onward
- $\sup x_k$: largest value the sequence can still approach from index $k$ onward

In words: this is a different viewpoint from the initial definition of convergence, it means that a sequence converges iff its long-term lower and upper bound collapse to the same number.

### Convergence to stationary points
We want to study convergence _regardless of the initial point_ $x_0$ of the sequence.

**Definition**
The sequence $\{x_k\}$ with $x_k\in\mathbb R^n$ $k=0,1,2,...$ is **globally convergent** to the point $\overline x$ if for any $x_0\in\mathbb R^n$ we have that at least one subsequence of $\{x_k\}$ converges to $\overline x$.

We distinguish among four different kinds of global convergence to stationary points, as follows ($\diamondsuit$):
1. **Finite convergence of** $\{x_k\}$: there exists a finite index $k^*<\infty$ such that $\nabla f(x_k^*)=0$
2. **Convergence of** $\{x_k\}$: we simply have that $\lim\limits_{k\to\infty}x_k=x^*$ with $\nabla f(x^*)=0$
3. **Convergence of** $\{\nabla f(x_k)\}$: we have that $\lim_{k\to\infty} ||\nabla f(x_k)||_2=0$
4. **The sequence $\{\nabla f(x_k)\}$ admits limit points**: we have that the condition $\lim\limits_{k\to\infty}\inf||\nabla f(x_k)||_2=0$ is fulfilled
>The first condition is the strongest, whilst the fourth is the weakest.

### Gradient methods
Assuming that $f\in C^1(\mathbb R^n)$ and starting from the point $x\in\mathbb R^n$, let us consider the scheme for generating the novel point $x_\alpha$:
$$x_\alpha=x-\alpha\nabla f(x),\quad\alpha\geq0$$
In words: the point $x_\alpha$ is taken by moving from the point $x\in\mathbb R^n$ along the direction $-\nabla f(x)$ with a steplength $\alpha\geq 0$.

By the [[Magistrale/Calculus and optimization/00 - Introduction#Mean value theorem|mean value theorem]] at $x$ we obtain:
$$\begin{align}
f[x-\alpha\nabla f(x)]&=f(x)+\nabla f(x)^T[x-\alpha\nabla f(x)-x]+o(||\alpha\nabla f(x)||)\\
&=f(x)-\alpha||\nabla f(x)||^2+o(||\alpha\nabla f(x)||)
\end{align}$$
so that if we take $\alpha$ sufficiently small, that is $\alpha||\nabla f(x)||^2>o(||\alpha\nabla f(x)||)$, then we obtain:
$$f[x-\alpha\nabla f(x)]<f(x)$$
>We recall that the gradient points uphill, and by going exactly the opposite direction, we always point downhill.

Using the above arguments, we can now define the following class of _iterative methods_ known in literature as **gradient methods** for $k=0,1,2,...$
$$x_{k+1}=x_k+\alpha_kd_k,\quad\nabla f(x_k)^Td_k<0$$
where $\alpha_k$ is chosen so that $f(x_k+1)< f(x_k)$.

In general if $D_k\in\mathbb R^{n\times n}$ is a positive definite matrix and $d_k=-D_k\nabla f(x_k)$, then we can consider the **generalized gradient methods**:
$$x_{k+1}=x_k-\alpha_kD_k\nabla f(x_k)$$
for which the direction $d_k$ satisfies (at any non-stationary point $x_k$):
$$\nabla f(x_k)^Td_k=-\nabla f(x_k)^TD_k\nabla f(x_k)<0$$
that is: $d_k$ is always a descent direction at $x_k$.

>[!Tip] Preconditioning matrix
>$D_k$ is the **preconditioning matrix** used to compute the direction $d_k$, it helps use choose a good direction.

Now we analyze some special cases of widely used gradient methods in literature:
- **Steepest Descent** $D_k=I$:
	We simply have $d_k=-\nabla f(x_k)$, and depending on the starting point $x_0$ and the shape of the level curves of the function, this method may be faster or it may suffer from the phenomenon known as _zigzagging_
	![[Steepest descent.png|500]]

- **Newton's method** $D_k=[\nabla^2 f(x_k)]^{-1}$:
	Differs from the steepest descent because it requires the function to be twice continuously differentiable in $\mathbb{R}^n$ and $\mathrm{II}$ order information.
	This method can be used as long as $\nabla^2 f(x_k)$ is _nonsingular_.
	
	When the sequence $\{x_k\}$ converges to $x^*$ and $\nabla^2 f(x^*)$ is positive definite, then $d_k = -[\nabla^2 f(x_k)]^{-1} \nabla f(x_k)$ is a descent direction at $x_k$ when $x_k$ is sufficiently close to $x^*$.
	
	Newton's method can be derived from the [[Magistrale/Calculus and optimization/00 - Introduction#Mean value theorem (second order)|second order mean value theorem]] at $x_k$. Setting $d = x - x_k$, we have:$$\varphi(d) = f(x_k + d) = f(x_k) + \nabla f(x_k)^T d + \frac{1}{2}d^T\nabla^2 f(x_k)d + o(||d||^2)$$
	
	Neglecting the term $o(||d||^2)$ and computing the stationary point of $\varphi(d)$ by solving $\nabla\varphi(d_k) = 0$, we obtain: $$\nabla\varphi(d_k) = \nabla f(x_k) + \nabla^2 f(x_k)d_k = 0$$
	
	which is satisfied iff: $$d_k = -[\nabla^2 f(x_k)]^{-1} \nabla f(x_k), \quad k = 0, 1, 2, \ldots$$
	
	Since $d_k = x_{k+1} - x_k$, the iteration of Newton's method is:$$x_{k+1} = x_k - \alpha_k [\nabla^2 f(x_k)]^{-1} \nabla f(x_k), \quad k = 0, 1, 2, \ldots$$
	
	Unlike the steepest descent, _Newton's method does not suffer from zigzagging_ because it can fruitfully exploit information from second order derivatives.
	![[Newton's method.png|400]]

- **Preconditioned Steepest Descent** $D_k\succ0$:
	In this case we consider the direction $d_k=-D_k\nabla f(x_k)$, where $D_k$ is _positive definite_, if well chosen, the preconditioner $D_k$ can make the method significantly faster than standard steepest descent.

#### Choosing the right steplength for gradient methods
Several choices for $\alpha_k$ may be adopted in the literature, depending on both the nature and the difficulty of the optimization problem in hand.

- **Minimization Rule**:
	Choose the steplength $\alpha_k$ such that: $$f(x_k+\alpha_kd_k)=\min_{\alpha>0}f(x_k+\alpha d_k)$$
	where by $\min$ we mean the "global minimum" along that direction, which is rather expensive.

- **Limited Minimization Rule**:
	Choose the steplength $\alpha_k$ such that: $$f(x_k+\alpha_kd_k)=\min_{\alpha\in[0,s]}f(x_k+\alpha d_k),\quad s>0$$
	in this case we want to find the global minimum along that direction, but constrained only to a specific interval, which is again expensive.

- **Armijo Rule**:
	Choose the steplength $\alpha_k$ so that setting the parameters $0<\beta<1$ and $s>0$ and writing: $$\alpha_k=\beta^{m_k} s,\quad m_k\text{ is a positive integer}$$
	- $s$ is the initial step size
	- $\beta$ is the reduction factor, this is how much we shrink the step size $s$ each time the Armijo condition fails
	
	Choosing $a_k$ corresponds to finding the _smallest value_ of $m_k$ which satisfies: $$f(x_k+\beta^{m_k}sd_k)\leq f(x_k)+\sigma\beta^{m_k}s\nabla f(x_k)^Td_k,\quad0<\sigma<1$$
	This rule is a like a "good enough" test for the steplength, we start with a step size, then we check if the function decreased by a reasonable amount, if yes we take that step, otherwise we cut the step in half and check again untile we get enough decrease.
	![[Armijo rule.png|400]]
	- $f(x_k+\alpha d_k)$: the actual function value as we move along the direction $d_k$ with different step sizes $\alpha$
	- $f(x_k)+\sigma\alpha\nabla f(x_k)^Td_k$: represents the reference line for the Armijo condition, it starts at $f(x_k)$ and has a slope that's a fraction ($\sigma$) of the initial slope
	- The regions $a$ and $b$: show where the actual function is below the straight reference line, any $\alpha$ value in these region satisfies the Armijo condition

- **Constant Stepsize**:
	Choose $\alpha_k=s$ for any $k$

- **Diminishing Stepsize**:
	Choose $\alpha_k$ so that: $$\lim_{k\to\infty}\alpha_k=0$$
	When paired with gradient methods, the global convergence of the overall algorithm might not be ensured in the general case.

### Issues on convergence
In order to monitor the progress of our iterative methods we need some reliable criteria, in particular we adopt the following ones:
- **Global convergence to stationary points**: the capability of the algorithm to generate a sequence of iterates $\{x_k\}$ such that one of the four conditions ($\diamondsuit$) is fulfilled, regardless of the choice of the starting point $x_0$
- **Rate of convergence**: provided that the algorithm is globally convergent to a stationary point $x^*$, we want to measure the speed at which it approaches the local solution $x^*$, for this purpose we can use one of the following indicators:
$$e(x_k)=||x_k-x^*||\quad\text{ or }\quad e(x_k)=|f(x_k)-f(x^*)|$$

**Definition**
Given the sequence (or subsequence) $\{x_k\}$ with $x_k\in\mathbb R^n$, $k=0,1,2,...$ such that $\{x_k\}$ converges to $x^*$, then we say that:
1. $\{x_k\}$ is **sublinearly convergent** to $x^*$ if:
	$$e(x_{k+1})\leq\beta e(x_k),\quad\beta_k>0$$
2. $\{x_k\}$ is **linearly convergent** to $x^*$ if:
	$$e(x_{k+1})\leq\beta e(x_k),\quad1>\beta_k>0$$
3. $\{x_k\}$ is **superlinearly convergent** to $x^*$ if:
	$$\lim_{k\to\infty}\sup\frac{e(x_{k+1})}{e(x_k)}=0$$

Before talking about the **gradient-related direction** we preliminary introduce some comments:
- In order to obtain the minimization of a function, it is natural to think about adopting a search direction related to the steepest descent $-\nabla f(x_k)$
- We want that the inner product $\nabla f(x_k)^T d_k$ remains eventually negative when the algorithm generates the convergent subsequence of points, that is:
	$$\lim_{k\to\infty}\sup\nabla f(x_k)^Td_k<0$$
- The search direction of a gradient method should be effective only in case we are not at a stationary point, that is in the case the condition $\nabla f(x_k)\neq 0$ is fulfilled
- We require that $||d_k||$ depends on $||\nabla f(x_k)||$ so that when $\{x_k\}\to x^*$ and $x^*$ is a stationary point (equivalently $||\nabla f(x_k)||\to0$), then also $||d_k||\to0$. This property avoids the algorithm to generate search direction when a stationary point has already been outreached

**Definition**
Given the sequence (or subsequence) $\{x_k\}$ with $x_k\in\mathbb R^n$, $k=0,1,2,...$ such that $\{x_k\}$ converges to the stationary point $x^*$, we say that the direction $d_k$, is **gradient-related** if for any $k$ there exists the parameters $a>0$, $b>0$, $p>0$ and $q>0$ (independent of $k$) such that:
1. $\nabla f(x_k)^Td_k\leq -a||\nabla f(x_k)||^p$
2. $||d_k||\leq b||\nabla f(x_k)||^q$

**Global Convergence of Gradient methods**
Consider the function $f:\mathbb R^n\to\mathbb R$ with $f\in C^1(\mathbb R^n)$, let us consider the gradient method of $k=0,1,2,...$
$$x_{k+1}=x_k+\alpha_kd_k$$
and assume that:
- $d_k$ is **gradient-related**
- The [[01 - Convexity#Level set|level set]] $\mathcal L_0=\{x\in\mathbb R^n: f(x)\leq f(x_0)\}$ is **closed** and **bounded**
- The steplength $\alpha_k$ is computed by using the _minimization rule_, or the _limited minimization rule_ or the _Armijo rule_

Then regardless of the choice of $x_0$, every _limit point_ of the sequence $\{x_k\}$ is a **stationary point**, that is:
$$\lim_{k\to\infty}||\nabla f(x_k)||=0$$

We remark that the latter definition <u>does not say that the entire sequence is convergent</u>, it rather states that both:
- All the subsequences of $\{x_k\}$ are convergent (possibly to different limit points)
- Any of the limit points is a stationary point


**Rate of Convergence of the Steepest Descent**
Consider the quadratic function:
$$f(x)=\frac{1}{2}x^TQx,\quad Q\succ0$$
and the gradient method (steepest descent):
$$x_{k+1}=x_k-\alpha_k\nabla f(x_k),\quad k=0,1,2,...$$
If $\alpha_k$ is chosen according with the minimization rule, then we have:
$$f(x_{k+1})\leq\left(\frac{\lambda_M(Q)-\lambda_m(Q)}{\lambda_M(Q)+\lambda_m(Q)}\right)f(x_k)\quad(\clubsuit)$$
where $\lambda_m(Q)$ is the smallest eigenvalue of $Q$ and $\lambda_M(Q)$ the biggest.

By the above formula, we can deduce the following results:
- If $\lambda_m(Q)=\lambda_M(Q)$ then the steepest descent method will converge in just one iteration to the stationary point $x^*=0$, being by ($\clubsuit$) $f(x_1)\leq0\cdot f(x_0)=0$
- The larger the difference $\lambda_M(Q)-\lambda_m(Q)$, the larger in general the ratio:
$$\frac{\lambda_M(Q)-\lambda_m(Q)}{\lambda_M(Q)+\lambda_m(Q)}$$
	meaning that in case $\lambda_M(Q)-\lambda_m(Q)$ is large, then the bound on $f(x_{k+1})$ is less significant in practical applications
- The formula $(\clubsuit)$ explains zigzagging of the steepest descent method

