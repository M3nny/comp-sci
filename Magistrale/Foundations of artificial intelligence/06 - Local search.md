An approach to [[05 - Constraint satisfaction|constraint satisfaction]] problems is to turn them into an optimization problem, by defining an **objective function** that is positive and $0$ iff all constraints are satisfied.
>Recalling the n-queens game, we can define the function as the number of pairs of queens that are attacking each other.

In this case we move from a state to the other hoping to decrease (or increase, in case of maximization) the objective function.
This requires the _notion of adjacent state_ and a strategy to decide on which of the available states to move.

### Hill-climbing
The simplest approach would be to move to the adjacent state that optimizes the objective function, and terminate if adjacent states do not improve on current state.

With this approach <u>we can easily get stuck on a local minima</u>, for this reason we may want to use other strategies, such as:
- Restart with several initial condition
- Allow on occasion to make increasing (or decreasing) moves
- Introduce random jumps away from the neighborhood

### Simulated annealing
Simulated annealing is a probabilisti technique for approximating the global minimum (or maximum) of a given function $f$.

It exploits an heuristic that considers the neighboring state $s^*$ of the current state $s$, and probabilistically decides between moving the system to state $s^*$ or staying in $s$.

The probability is defined by $P(e,e^*,T)$, that depends on:
- $e=f(s)$ and $e^*=f(s^*)$, called **energies**
- A global time-varying parameter $T$ called **temperature**

When $T$ tends to $0$, $P(e,e^*,T)$ must also tend to $0$ if $e^*>e$, otherwise it will be positive.

For sufficiently small values of $T$, the system will increasingly favor safer moves, instead of trying to explore.

If $T$ decreases slowly enough, then this approach will find a global optimum with a probability approaching $1$.

### Local beam search
This is a variant of the hill-climbing algorithm, but instead of tracking only one state, we begin by tracking $k$ random states, and at each iteration, all the successors of all $k$ states are generated, from this larger pool, we check if there is a goal state, otherwise we select the $k$ best successors and repeat.

The idea is to avoid getting stuck on a local minima.

### Genetic algorithms
We start with $k$ randomly generated states, called **population**.
A state is a string over a finite alphabet (often $0$ and $1$).

The evaluation function, called **fitness function**, has higher values for better states.
The next generation of states is produced by **selection**, **crossover** and **mutation**.
- Individuals with higher fitness are more likely to be selected for reproduction
- Individuals selected for reproduction are placed in the mating pool
- When the mating pool is filled with $n$ copies of individuals, the descendants are created applying the genetic operators (i.e. mutation and crossover)

Let $f_i$ be the fitness value of individual $i$, the probability that $i$ is selected for reproduction is:
$$p_i=\frac{f_i}{\sum_kf_k}$$
For the **crossover** we select two parents, and a crossover point, the genotypes on the right part are swapped with probability $p_c$, generating two descendants.
![[Crossover.png]]

We simulate the **mutation** saying that with a _low_ probability $p_m$, one location fo the genotype is altered:
![[Mutation.png]]

---
## Search in a continuous space
Sometimes it is useful to **relax** the domain of the problem, from a discrete one to a continuous one.
>We already treated something simular in the [[Branch & Bound|branch & bound]] method.

A classic approach is to convert the assignment of a variable to a value in its domain, to a **probabilistic assignment**.

Assume the generic optimization function in the form:
$$\stackrel{\min f(x)}{x\in \Omega}$$
where $f$ is the objective function and $\Omega\in\mathbb{R}^n$ is the feasible set.

A point $x^*$ is said to be a **local minimum** over $\Omega$ if there is an $\epsilon>0$ such that $f(x)\geq f(x^*), \forall x\in\Omega$ within a distance $\epsilon$, while if we consider the strict inequality $f(x)>f(x)$, then $x$ is a **strict local minimum** of $f$ over $\Omega$.

We can say that it is a **global minimum** if $f(x)\geq f(x^*),\forall x\in\Omega$.

### Gradient descent
The gradient $\Delta f(x)$ according to our conventions, defined as a $n$-dimensional _row vector_, when there is not chance for ambiguity we will write $g_k$ for $g(x_k)=\nabla f(x_k)^T$, where in this case it is a _column vector_.

The method of steepest descent is defined by the iterative algorithm:
$$x_{k+1}=x_k-\alpha_kg_k$$
where $\alpha_k$ is a non-negative scalar minimizing $f(x_k-\alpha g_k)$.
In words, from the point of $x_k$ we search along the direction of the negative gradient $-g_k$ to a minimum point, this minimum point is taken to be $x_{k+1}$.

The **Newton's method** for optimization other than the gradient, uses the [[Punti di massimo e minimo#Matrice Hessiana|hessian matrix]] to get the curvature information.

The idea is that a smooth function $f(x)$ can be approximated near some point $x_k$ by a quadratic function, thus we can approximate $f$ by the truncated Taylor expansion:
$$f(x)\simeq f(x_k)+\nabla f(x_k)(x-x_k)+\frac{1}{2}(x-x_k)^TF(x_k)(x-x_k)$$
>Where $F$ is the hessian matrix.

The next iteration point is given by:
$$x_{k+1}=x_k-[F(x_k)]^{-1}\nabla f(x_k)^T$$
