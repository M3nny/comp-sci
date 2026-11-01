Quantum parallelism alone is not useful, because measurement returns only one value.

**Interference** is what makes it useful: we arrange the amplitudes so that a _global property_ of a function $f$ shows up in the measurement result.

Deutsch's algorithm does this for 1 input bit, and Deutsch-Jozsa generalizes it to $n$ bits.

Before diving into the algorithm, we introduce a few concepts.

**The oracle $U_f$**
A function $f$ is a classical black box, to use it in a quantum circuit it must be reversible, so we use:
$$U_f: |x, y\rangle \to |x,\; y \oplus f(x)\rangle$$
The $x$ register is the _query_, the $y$ register is the _answer_, and $\oplus$ is addition mod 2. Evaluating $f$ means calling $U_f$ once.

**Hadamard transform on $n$ qubits**
Applying $H$ to each of $n$ qubits starting from $|0\rangle^{\otimes n}$ gives an equal superposition of all $2^n$ basis states, using only $n$ gates:
$$H^{\otimes n}|0\rangle^{\otimes n} = \frac{1}{\sqrt{2^n}}\sum_x |x\rangle$$
**Quantum parallelism**
Feeding that superposition into $U_f$ (with answer qubit $|0\rangle$) gives
$$\frac{1}{\sqrt{2^n}}\sum_x |x\rangle|f(x)\rangle$$
So $f$ seems to be evaluated on all inputs at once, with a single call.

**The catch** is that measuring this state yields just one pair $(x, f(x))$, which a classical computer gets just as easily, we need to _extract information about several values_ of $f$ at once, and that is where interference comes in.

### Deutsch's algorithm
Given a black box for $f:\{0,1\}\to\{0,1\}$, determine whether $f(0) = f(1)$ (constant) or $f(0) \neq f(1)$ (balanced), equivalently, compute $f(0)\oplus f(1)$.
- Classically: we need **2 evaluations** (compute $f(0)$ and $f(1)$)
- Quantum: **1 evaluation**
![[Deutsch's algorithm.png]]
>Both qubits go through $H$, then $U_f$, then $H$ on the first qubit only, then measure the first qubit.

Initially we have $|\psi_0\rangle = |01\rangle$, then **after the two Hadamards**:
$$|\psi_1\rangle = \left[\frac{|0\rangle + |1\rangle}{\sqrt{2}}\right]\left[\frac{|0\rangle - |1\rangle}{\sqrt{2}}\right]$$
If the answer qubit is in $\frac{|0\rangle - |1\rangle}{\sqrt{2}}$, then $U_f$ acts as:
$$U_f\left(|x\rangle\frac{|0\rangle - |1\rangle}{\sqrt{2}}\right) = (-1)^{f(x)}|x\rangle\frac{|0\rangle - |1\rangle}{\sqrt{2}}$$
This is because:
- If $f(x)=0$, then $y\oplus 0 = y$, so nothing changes
- If $f(x)=1$, then $U_f$ swaps $|0\rangle\leftrightarrow|1\rangle$ in the answer qubit, turning $|0\rangle - |1\rangle$ into $|1\rangle - |0\rangle = -(|0\rangle - |1\rangle)$

So the answer qubit stays unchanged and the value of $f(x)$ ends up as a _sign (phase) on the query qubit_.

**After $U_f$**
$$|\psi_2\rangle = \begin{cases} \pm\left[\dfrac{|0\rangle + |1\rangle}{\sqrt{2}}\right]\left[\dfrac{|0\rangle - |1\rangle}{\sqrt{2}}\right] & \text{if } f(0) = f(1) \\[3mm] \pm\left[\dfrac{|0\rangle - |1\rangle}{\sqrt{2}}\right]\left[\dfrac{|0\rangle - |1\rangle}{\sqrt{2}}\right] & \text{if } f(0) \neq f(1) \end{cases}$$
The two signs $(-1)^{f(0)}$ and $(-1)^{f(1)}$ are either equal (a global sign, constant case) or different (a relative sign, balanced case).
Only a relative sign changes the state of the first qubit from $|+\rangle$ to $|-\rangle$.

**After the final Hadamard on the first qubit** ($H|+\rangle = |0\rangle$, $H|-\rangle = |1\rangle$):
$$|\psi_3\rangle = \pm|f(0)\oplus f(1)\rangle\left[\frac{|0\rangle - |1\rangle}{\sqrt{2}}\right]$$
After **measuring the first qubit** we get $f(0)\oplus f(1)$ with certainty: $0$ means constant, $1$ means balanced.

One might think $|0\rangle|f(0)\rangle + |1\rangle|f(1)\rangle$ is like a classical machine that evaluates $f(0)$ or $f(1)$ with probability $\frac12$ each, but the difference is that **classically** the two alternatives _exclude each other forever_, whilst **quantum mechanically** they _interfere_ when recombined by the Hadamard gate, giving a global property of $f$ from a single call.

### Deutsch-Jozsa algorithm
Alice picks $x\in\{0,\dots,2^n-1\}$ and sends it to Bob, who computes $f(x)\in\{0,1\}$, Bob promises that $f$ is either:
- **Constant**: same output for all $x$
- **Balanced**: output $1$ for exactly half of the inputs and $0$ for the other half

Alice must decide which, with certainty, using as few queries as possible.

| Approach                     | Queries needed                                                                             |
| ---------------------------- | ------------------------------------------------------------------------------------------ |
| Best deterministic classical | $2^n/2 + 1$ (worst case: we see $2^n/2$ zeros in a row and still need one more to be sure) |
| Quantum (Deutsch-Jozsa)      | $1$                                                                                        |

![[Deutsch-Jozsa algorithm.png]]

The initial state is $|\psi_0\rangle = |0\rangle^{\otimes n}|1\rangle$, and **after Hadamards on all qubits**:
$$|\psi_1\rangle = \sum_{x\in\{0,1\}^n}\frac{|x\rangle}{\sqrt{2^n}}\left[\frac{|0\rangle - |1\rangle}{\sqrt{2}}\right]$$
>The query register is a uniform superposition of all inputs, and the answer qubit is in $|-\rangle$.

We then **apply** $U_f$:
$$|\psi_2\rangle = \sum_x\frac{(-1)^{f(x)}|x\rangle}{\sqrt{2^n}}\left[\frac{|0\rangle - |1\rangle}{\sqrt{2}}\right]$$

The values of $f$ are now stored in the _signs_ of the amplitudes, the answer qubit is unchanged and can be ignored from here on.

**Apply $H^{\otimes n}$ to the query register**
A useful formula, derived by checking $x=0$ and $x=1$ for a single qubit ($H|x\rangle = \sum_z(-1)^{xz}|z\rangle/\sqrt{2}$) and then extending to $n$ qubits:
$$H^{\otimes n}|x\rangle = \frac{1}{\sqrt{2^n}}\sum_z(-1)^{x\cdot z}|z\rangle$$
where $x\cdot z = x_1z_1 + \dots + x_nz_n \pmod 2$ is the bitwise inner product.

Applying it to $|\psi_2\rangle$:
$$|\psi_3\rangle = \sum_z\sum_x\frac{(-1)^{x\cdot z + f(x)}|z\rangle}{2^n}\left[\frac{|0\rangle - |1\rangle}{\sqrt{2}}\right]$$

**Measure the query register**
Look at the amplitude of $|0\rangle^{\otimes n}$ (that is, $z=0$, so $x\cdot z=0$):
$$\text{amplitude of } |0\rangle^{\otimes n} = \frac{1}{2^n}\sum_x(-1)^{f(x)}$$
- _$f$ constant_: every term has the same sign, so the amplitude is $\pm1$, since the state has unit length, all other amplitudes are $0$. we measure $|0\rangle^{\otimes n}$ with certainty
- _$f$ balanced_: half the terms are $+1$ and half are $-1$, so they cancel and the amplitude is $0$, we will never measure all zeros

The **decision rule** is measure the query register, the:
- All zeros -> constant
- Anything else -> balanced

>[!Info]
>Deutsch’s algorithm is the case $n=1$.

This is a **toy problem** and has _no known applications_, furthermore classical and quantum algorithms evaluate $f$ in quite different ways, so comparing query counts is not fair.

The algorithms still shows an important **template** used by many quantum algorithms:
1. _Superpose_ all inputs
2. _Evaluate_ the function once
3. _Encode_ its values as phases
4. Use _interference_ (a final transform) so that a useful global property shows up in the measurement

