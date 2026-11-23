In this chapter we're going to see how quantum computers **factor large numbers** exponentially faster than the best known classical algorithms.

The best classical method (i.e. [general number field sieve](https://en.wikipedia.org/wiki/General_number_field_sieve)) takes roughly $\exp(n^{1/3})=e^{n^{1/3}}$ steps for an $n$-bit number, while the quantum algorithm takes about $O(n^3)$.

>[!Info] The idea behind the Fourier transform
>Any sufficiently well-behaved signal can be represented as a combination of sinusoidal waves (sines and cosines) with different frequencies, amplitudes, and phases.
>
>The Fourier Transform changes the way we describe a signal: instead of looking at how it evolves in time, we look at its frequency components.
>
>**In other words**
>Imagine we have a complicated sound signal, such as a piece of music, when we listen to it, we hear a combination of many different notes.
>
>The Fourier transform allows us to take that complicated sound and identify the individual frequencies that compose it.

The core intuition is that the quantum Fourier transform (QFT) is a **frequency detector**, if we can put a quantum state into a "wave" whose frequency encodes the answer, the inverse QFT converts that wave into a state we can measure.

### The quantum Fourier transform
**Classical DFT** turns a vector $x_0,\dots,x_{N-1}$ into $y_0,\dots,y_{N-1}$:
$$y_k = \frac{1}{\sqrt N}\sum_{j} x_j\, e^{2\pi i jk/N}$$
>DFT = Discrete Fourier Transform.

**QFT** is the same transformation, but applied to the amplitudes of a quantum state:
$$|j\rangle \to \frac{1}{\sqrt N}\sum_k e^{2\pi ijk/N}|k\rangle$$
It is _unitary_, which is why it can be a quantum operation.

Now we introduce a key trick: the **product form**
Write $j$ in binary as $j_1 j_2\dots j_n$ and define $0.j_l j_{l+1}\dots j_m$ as a binary fraction, then the QFT output factorizes into one independent qubit state per qubit:
$$|j_1\dots j_n\rangle \to \frac{(|0\rangle + e^{2\pi i\,0.j_n}|1\rangle)(|0\rangle + e^{2\pi i\,0.j_{n-1}j_n}|1\rangle)\cdots(|0\rangle + e^{2\pi i\,0.j_1\dots j_n}|1\rangle)}{2^{n/2}}$$
>This is derived with elementary algebra, it matters because a product state can be built qubit by qubit with a small circuit.

The circuit for this is the following:
![[Circuit for the quantum Fourier transform.png]]
For each qubit, apply a Hadamard gate $H$, then **controlled-phase gates** $R_k$ that add one more bit of $j$ into the phase, $R_k$ is just "multiply $|1\rangle$ by $e^{2\pi i/2^k}$".
Finish with swaps to reverse the qubit order (not shown here), and because every gate is unitary, this also proves the QFT is unitary.

> [!info] Controlled-phase gates
>A **phase gate** leaves $|0\rangle$ unchanged and applies a phase $e^{i\phi}$ to $|1\rangle$:
> 
>$$
>P(\phi)=
>\begin{pmatrix}
>1&0\\
>0&e^{i\phi}
>\end{pmatrix}
>$$
> 
>A **controlled-phase gate** applies this phase only when _both qubits are in state $|1\rangle$_:
> 
>$$
>CP(\phi)=
>\begin{pmatrix}
>1&0&0&0\\
>0&1&0&0\\
>0&0&1&0\\
>0&0&0&e^{i\phi}
>\end{pmatrix}
>$$
> 
>Therefore, only $|11\rangle$ acquires a phase, the other (three) basis states remain unchanged.
> 
>**Key intuition**
>CNOT conditionally changes a qubit's bit value, whereas a controlled-phase gate conditionally changes its phase.
>QFT relies on these phase changes to encode information and produce quantum interference.

**Cost**:
- The circuit uses about $n(n+1)/2$ gates plus swaps, so it is $\Theta(n^2)$.
- The classical Fast Fourier Transform (FFT), which is used to efficiently compute the DFT on $2^n$ numbers is $\Theta(n2^n)$
- So the QFT is exponentially fewer operations

>[!Attention] QTF for processing real digitized sound
>This does not speed up classical Fourier transforms such as audio processing:
>- We can't read out the transformed amplitudes (measurement gives only one sample)
>- We can't efficiently load arbitrary classical data into amplitudes in the first place
>
>>The QFT is useful only inside cleverly designed algorithms.

### Phase estimation
We're given a unitary $U$ and an eigenvector $|u\rangle$ with $U|u\rangle = e^{2\pi i\varphi}|u\rangle$, the task is: estimate $\varphi$.
We get "black boxes" that prepare $|u\rangle$ and apply controlled-$U^{2^j}$, so this is a subroutine, not a complete algorithm.

**Procedure** (two registers: $t$ qubits starting at $|0\rangle$, and the register holding $|u\rangle$):
1. Apply Hadamards to the first register to get a uniform superposition over $|j\rangle$
2. Apply controlled-$U^{2^j}$ operations, since $U^j|u\rangle = e^{2\pi i\varphi j}|u\rangle$, each $|j\rangle$ picks up phase $e^{2\pi i\varphi j}$, the first register becomes $\frac{1}{2^{t/2}}\sum_k e^{2\pi i\varphi k}|k\rangle$, this is a  _"wave"_ of frequency $\varphi$

![[First stage of the phase estimation procedure.png|526]]

3. Apply the inverse QFT to the first register
4. Measure the first register to get an estimate of $\varphi$

**Why it works.**
- If $\varphi$ has an exact $t$-bit binary expansion, the state in step 2 equals the QFT product form, so the inverse QFT gives exactly $|\varphi_1\dots\varphi_t\rangle$ and we measure $\varphi$ with certainty
- Otherwise, a geometric-series calculation shows the measurement lands within $e$ of the best $t$-bit approximation with probability at least $1 - \frac{1}{2(e-1)}$
- To get $n$ bits of accuracy with success probability $\ge 1-\epsilon$, we can set
$$t = n + \left\lceil \log\left(2 + \tfrac{1}{2\epsilon}\right)\right\rceil$$
**If we can't prepare an eigenstate**, feed in an arbitrary $|\psi\rangle = \sum_u c_u|u\rangle$, then we'll measure the phase $\varphi_u$ of a _randomly chosen eigenvector_, with probability $|c_u|^2$.

**Cost**: $O(t^2)$ operations plus one call to the controlled-$U^j$ black box.

### Order-finding
For coprime $x < N$, the **order** of $x$ mod $N$ is the smallest $r > 0$ with $x^r \equiv 1 \pmod N$.
>The order of $5 \mod 21$ is $6$.
>No efficient classical algorithm is known.

**Setup**
Take the operator $U|y\rangle = |xy \bmod N\rangle$, its eigenstates are:
$$|u_s\rangle = \frac{1}{\sqrt r}\sum_{k=0}^{r-1} e^{-2\pi i sk/r}\,|x^k \bmod N\rangle,\qquad \text{eigenvalue } e^{2\pi i s/r}$$
So phase estimation gives $\varphi \approx s/r$, and from that we can recover $r$, then two obstacles arise:
1. **Implementing controlled-$U^{2^j}$**: this is done by modular exponentiation: repeated squaring to get $x^{2^j} \bmod N$, then multiplying the right ones together, the cost is $O(L^3)$ gates, where $L$ is the number of bits of $N$
2. **Preparing $|u_s\rangle$**: we can't, because that requires knowing $r$, the trick: $\frac{1}{\sqrt r}\sum_s |u_s\rangle = |1\rangle$, so just start the second register in $|1\rangle$, phase estimation then returns a random $s/r$, each $s$ equally likely, we set $t = 2L + 1 + \lceil\log(2+\frac{1}{2\epsilon})\rceil$ qubits

**Continued fractions**
We now have a decimal-like approximation of $s/r$ and need the fraction itself:
- If $|s/r - \varphi| \le \frac{1}{2r^2}$, then $s/r$ is a convergent of the continued fraction of $\varphi$
- The $2L+1$ bits of accuracy guarantee this condition
- The continued fraction algorithm is just repeated "split off the integer part, invert the remainder", like the Euclidean algorithm (e.g.: $31/13 = [2,2,1,1,2]$), it costs $O(L^3)$
- Check the candidate by testing whether $x^{r'} \equiv 1$

**Failure mode**
If $s$ and $r$ share a common factor, we get $r' = r/\gcd(s,r)$, a proper divisor of $r$, there are three fixes to this:
1. Repeat about $2\log N$ times (a random $s$ is often prime and so coprime to $r$)
2. Replace $x$ by $x^{r'}$ and iterate on the smaller order
3. The _best solution_ is to run twice, getting $r_1'$ and $r_2'$, and take the _least common multiple (lcm)_, this succeeds with probability $\ge 1/4$

**Total cost**: $O(L^3)$, dominated by modular exponentiation.

#### Factoring (reduction to order-finding)
The quantum part is only the order-finding step, the rest is classical:
1. If $N$ is even, return 2.
2. If $N = a^b$ for integers $a \ge 1$, $b \ge 2$ (a perfect power), return $a$ (an efficient classical test)
3. Pick a random $x$, if $\gcd(x,N) > 1$, return that gcd
4. Find the order $r$ of $x$ using the quantum subroutine
5. If $r$ is even and $x^{r/2} \not\equiv -1 \pmod N$, compute $\gcd(x^{r/2}\pm 1, N)$, one of them is a non-trivial factor

**Why step 5 works**
- If $y^2 \equiv 1 \pmod N$ with $y \ne \pm 1$, then $N$ divides $(y-1)(y+1)$ without dividing either factor, so the gcds reveal factors
- For random $x$, the order $r$ is even with $x^{r/2} \ne -1$ with probability at least $1 - 2^{-m}$ (where $m$ is the number of distinct prime factors of the odd composite $N$), so at least 1/2

> [!Example]
>$$N=15\quad x=7$$
>Powers of $7$ mod $15$ cycle: $1, 7, 4, 13, 1, \dots$, so $r = 4$.
>
>The phase estimation measurement gives one of $0, 512, 1024, 1536$ out of $2048$, each with probability about $1/4$, say $1536$.
>
>$1536/2048 = 3/4$, so $r = 4$.
>
>$7^2 = 49 \equiv 4 \not\equiv -1 \pmod{15}$, so $\gcd(4-1,15) = 3$ and $\gcd(4+1,15) = 5$, giving $15 = 3 \times 5$.


> [!Abstract] General applications (hidden subgroup problem)
>Not needed for factoring, but it shows that the same technique solves a whole family of problems.
>
> **The recipe** (same as order-finding):
> 1. Create a superposition over all inputs
> 2. Evaluate the function once
> 3. Rewrite the function value in the Fourier basis
> 4. Apply the inverse QFT and measure
> 5. Post-process classically (e.g. continued fractions)
>
>---
> **Period-finding**
> - Given $f(x+r)=f(x)$, find the period $r$
> - The states $|\hat f(\ell)\rangle$ (Fourier transform of $|f(x)\rangle$) play the role of the eigenvectors $|u_s\rangle$
> - Measurement gives a random $\ell/r$, and continued fractions recover $r$
> - Cost: one query to $f$ plus $O(L^2)$ other operations
> - Why it works: the Fourier transform is *shift-invariant*, shifting the input only changes phases, not magnitudes, so the measurement statistics don't depend on where the periodic pattern starts
> - Order-finding is the special case $f(k)=x^k \bmod N$
>
> **Discrete logarithm**
> - Given $a$ and $b=a^s$, find $s$
> - Use $f(x_1,x_2)=b^{x_1}a^{x_2}$, whose period is the 2-tuple $(\ell,-\ell s)$
> - Same recipe on two registers, then a *generalized* continued fractions step recovers $s$
> - Matters for cryptography: Diffie-Hellman and elliptic-curve schemes rely on this problem being hard
>
> **Hidden subgroup problem**
> - $f$ is defined on a group $G$ and is constant and distinct on the cosets of a hidden subgroup $K$, the goal is to find a generating set for $K$
> - $K$ is the generalized "hidden period"
> - Special cases: Deutsch, Simon, period-finding, order-finding, discrete log.
> - _Finite Abelian $G$_: solvable with polynomial in $\log|G|$ operations and one query
> - Subtlety: the measured $\ell$ may share factors with $|G|$, so plain continued fractions can fail, the fix is to decompose $G$ into cyclic groups of prime-power order and run phase estimation on each factor.

