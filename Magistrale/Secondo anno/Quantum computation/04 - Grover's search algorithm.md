We have an unordered collection of $N$ items and want to find one that satisfies some condition, classically we must check items one by one, leading to a $O(N)$ complexity.

Grover's algorithm needs only about $\sqrt{N}$ oracle calls, a **quadratic speedup**.
It works by repeatedly rotating the quantum state a small fixed angle toward the "winning" states until a measurement almost surely returns a solution.

The **problem setup** is the following:
- $N = 2^n$ items, each identified by an $n$-bit index $x \in \{0, \dots, N-1\}$
- There are $M$ solutions, with $1 \le M \le N$
- The problem is encoded by a function:
$$f(x) = \begin{cases} 1 & \text{if } x \text{ is a solution} \\ 0 & \text{otherwise} \end{cases}$$

So, we'll end up with $O(\sqrt{N/M})$ oracle calls, versus $O(N/M)$ classically.

### The oracle
The **oracle recognizes solutions**, even though it doesn’t tell us which ones they are.
>See [[Turing riducibilità#Turing-riducibilità|oracle in Turing reduction]].

The oracle $O$ is a _unitary_ acting as:
$$|x\rangle|q\rangle \xrightarrow{O} |x\rangle|q \oplus f(x)\rangle$$
where $|q\rangle$ is the _oracle qubit_, flipped only if $f(x)=1$. If we prepare $|q\rangle = \frac{|0\rangle - |1\rangle}{\sqrt{2}}$, this is the same **phase kickback** trick used in [[03 - Deutsch-Jozsa algorithm#Deutsch's algorithm|Deutsch-Jozsa algorithm]]:
$$|x\rangle\frac{|0\rangle - |1\rangle}{\sqrt{2}} \xrightarrow{O} (-1)^{f(x)}|x\rangle\frac{|0\rangle - |1\rangle}{\sqrt{2}}$$

The oracle qubit is unchanged throughout, so we drop it and write simply:
$$\boxed{|x\rangle \xrightarrow{O} (-1)^{f(x)}|x\rangle}$$
>We can refer to this as $U_f$.

The oracle **marks solutions by flipping their sign** (phase) and leaving everything else untouched.

>[!Example] Factoring numbers
>Given $m = p\cdot q$ (two primes), the oracle takes $|x\rangle$, tests whether $x$ divides $m$, and flips the oracle qubit if so.
>
>We can build this without knowing $p$ or $q$, classical search needs about $m^{1/2}$ trial divisions, Grover needs about $m^{1/4}$.
>
>Anyway, this is **not practical**, since better classical factoring algorithms exist, but it shows the **general pattern**: <u>any search-based classical algorithm can be sped up this way</u>.

### The procedure
The algorithm uses one $n$-qubit register (the oracle's workspace qubits are irrelevant to the analysis).

**Start in the uniform superposition**
Begin in $|0\rangle^{\otimes n}$ and apply $H^{\otimes n}$:
$$|\psi\rangle = \frac{1}{\sqrt{N}}\sum_{x=0}^{N-1}|x\rangle$$

**Repeat the Grover iteration $G$ about $R$ times**
Each iteration does four things:
1. Apply the oracle $O$
2. Apply $H^{\otimes n}$
3. Apply a conditional phase shift: $|0\rangle$ is unchanged, every other basis state gets a $-1$:
$$|x\rangle \to -(-1)^{\delta_{x0}}|x\rangle$$
4. Apply $H^{\otimes n}$

**Measure** the register, _with high probability_ we get a solution.

Steps 3-4-2 combined (in the order they act) form the **diffusion operator**:
$$H^{\otimes n}(2|0\rangle\langle 0| - I)H^{\otimes n} = 2|\psi\rangle\langle\psi| - I$$
The phase shift in step 3 is exactly $2|0\rangle\langle 0| - I$, so:
$$\boxed{G = (2|\psi\rangle\langle\psi| - I)\,O}$$

One oracle call, $2n$ Hadamard gates, and $O(n)$ gates for the phase shift, the **oracle call dominates**, so _we count algorithm cost in oracle calls_.

### Geometric picture (the heart of the algorithm)
We define two normalized states:$$|\alpha\rangle = \frac{1}{\sqrt{N-M}}\sum_{x:\,f(x)=0}|x\rangle \quad\text{(all non-solutions)}$$ $$|\beta\rangle = \frac{1}{\sqrt{M}}\sum_{x:\,f(x)=1}|x\rangle \quad\text{(all solutions)}$$

The starting state lives in the 2D plane spanned by them:
$$|\psi\rangle = \sqrt{\frac{N-M}{N}}\,|\alpha\rangle + \sqrt{\frac{M}{N}}\,|\beta\rangle$$
Define an angle $\theta$ by $\cos\frac{\theta}{2} = \sqrt{\frac{N-M}{N}}$, so that
$$|\psi\rangle = \cos\tfrac{\theta}{2}\,|\alpha\rangle + \sin\tfrac{\theta}{2}\,|\beta\rangle, \qquad \sin\tfrac{\theta}{2} = \sqrt{\tfrac{M}{N}}$$
So $|\psi\rangle$ starts at angle $\theta/2$ from $|\alpha\rangle$, nearly parallel to it when $M \ll N$.
We want to rotate it up to $|\beta\rangle$ (the vertical axis).

**Two reflections make a rotation**:
- The _oracle_ $O$ is a _reflection_ about $|\alpha\rangle$: $O(a|\alpha\rangle + b|\beta\rangle) = a|\alpha\rangle - b|\beta\rangle$. (Winners' sign flips, non-winners stays untouched)
- The _diffusion operator_ $2|\psi\rangle\langle\psi| - I$ is a _reflection_ about $|\psi\rangle$
- _Composing two reflections_ in a plane gives a _rotation by twice the angle between the two mirror lines_, the mirrors $|\alpha\rangle$ and $|\psi\rangle$ are $\theta/2$ apart, so $G$ rotates by $\theta$

Because the mirrors don't depend on the input, **$G$ rotates every state in the plane by the same angle $\theta$**, and nothing ever leaves the $|\alpha\rangle,|\beta\rangle$ plane.

The **action of a single Grover iteration** can be seen as:
![[Single Grover iteration.png|272]]

After $k$ iterations:
$$G^k|\psi\rangle = \cos\!\Big(\tfrac{2k+1}{2}\theta\Big)|\alpha\rangle + \sin\!\Big(\tfrac{2k+1}{2}\theta\Big)|\beta\rangle$$

In the $|\alpha\rangle,|\beta\rangle$ basis, $G$ is the ordinary rotation matrix:
$$G = \begin{pmatrix}\cos\theta & -\sin\theta \\ \sin\theta & \cos\theta\end{pmatrix}, \qquad \sin\theta = \frac{2\sqrt{M(N-M)}}{N}$$
>The formula for $\sin\theta$ follows from $\sin\theta = 2\sin\frac{\theta}{2}\cos\frac{\theta}{2}$.


### How many iterations?
The angle from $|\psi\rangle$ to $|\beta\rangle$ is $\frac{\pi}{2} - \frac{\theta}{2}$, so the number of rotations needed is
$$R = \frac{\frac{\pi}{2} - \frac{\theta}{2}}{\theta} \le \frac{\pi}{2\theta}$$
Since $\sin x \le x$, we **bound it**:
$$\sqrt{\frac{M}{N}} = \sin\frac{\theta}{2} \le \frac{\theta}{2} \;\Longrightarrow\; \theta \ge 2\sqrt{\frac{M}{N}}$$
Therefore:
$$\boxed{R \le \left\lceil\frac{\pi}{4}\sqrt{\frac{N}{M}}\right\rceil = O\!\left(\sqrt{\frac{N}{M}}\right)}$$
**Why it's fast**
$\theta$ behaves like $\Omega(\sqrt{M/N})$, so the "step size" is relatively large, and only about $\sqrt{N/M}$ steps are needed to cover the quarter circle.

**Rounding and success probability**
$R$ must be an integer, so we can't align exactly with $|\beta\rangle$, the worst remaining angle is $\theta/2$, so:
- Success probability at least $\frac{N-M}{N}$ (since $\cos^2\frac{\theta}{2} = \frac{N-M}{N}$), which is close to 1 when $M \ll N$
- In general the final state is within $\theta/2 \le \pi/4$ of $|\beta\rangle$, giving success probability _at least $1/2$_, for $M \ll N$ the error probability is at most $M/N$

>[!Important]
>$R$ **depends on the number of solutions** $M$ but **not on which items they are**.
>
>So we need to know $M$.

#### Summary of the algorithm ($M=1$)

| | |
|---|---|
|**Input**|Oracle $O$ with $f(x_0)=1$ for exactly one $x_0$, and $n+1$ qubits in $\lvert 0\rangle$|
|**Output**|$x_0$|
|**Runtime**|$O(\sqrt{2^n})$ operations; succeeds with probability $O(1)$|

| Step | State / action                                                                                                                                                                                 |
| ---- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1    | $\lvert 0\rangle^{\otimes n}\lvert 0\rangle$ (initial)                                                                                                                                         |
| 2    | Apply $H^{\otimes n}$ to the first $n$ qubits and $HX$ to the last: $\frac{1}{\sqrt{2^n}}\sum_x\lvert x\rangle\frac{\lvert 0\rangle - \lvert 1\rangle}{\sqrt 2}$                               |
| 3    | Apply $G = (2\lvert\psi\rangle\langle\psi\rvert - I)O$ about $R \approx \lceil\pi\sqrt{2^n}/4\rceil$ times, state $\approx \lvert x_0\rangle\frac{\lvert 0\rangle - \lvert 1\rangle}{\sqrt 2}$ |
| 4    | Measure the first $n$ qubits to get $x_0$                                                                                                                                                      |

---
### Optimality of Grover's search
No quantum algorithm can search $N$ unstructured items with fewer than $\Omega(\sqrt{N})$ oracle calls, and since Grover uses $O(\sqrt{N})$, it is **optimal**: the complexity is $\Theta(\sqrt{N})$.

#### The idea behind the proof
Consider any quantum algorithm: it alternates oracle calls with arbitrary unitaries.

Compare two runs:
- One with the real oracle (which marks the hidden solution $x$)
- One with no oracle at all

The proof asks: how far apart can these two runs get after $k$ oracle calls?
>Summed over all $N$ possible solutions, noted as the the quantity $D_k$.

Two facts squeeze $k$:
1. **Each oracle call can only change the state by a limited amount**, so the deviation grows slowly: at most $D_k \le 4k^2$
2. **To actually find $x$, the deviation must be large**: for the algorithm to identify the right answer among $N$ possibilities with probability at least $\frac12$, the final states for different $x$ must be distinguishable, which forces $D_k \ge cN$

Combining: $cN \le 4k^2$, so $k \ge \Omega(\sqrt{N})$.

**Intuition**
The _oracle leaks only a tiny bit of information per call_, and we need to accumulate enough information to tell $N$ candidates apart, quadratic growth in leaked deviation means we need $\sqrt{N}$ calls.

#### Consequences
**Quadratic speedup is the ceiling** for unstructured search: no $O(\log N)$ search exists

**NP-complete problems can't be cracked by naive quantum search**: if $O(\log N)$ search existed, searching all $2^{w(n)}$ possible witnesses would take only about $w(n)$ calls, solving NP-complete problems efficiently, this shows that approach is guaranteed to fail

Many researchers believe NP-complete problems have no exploitable structure, which would mean _BQP (Bounded-error Quantum Polynomial-time)_ does not contain them (it is unproven).

**Structure is what quantum computers exploit**, for example factoring has hidden structure (reduction to order-finding), which is why quantum computers solve it efficiently even though generic search can't be beaten.
