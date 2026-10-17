In this chapter we're going to introduce the **four postulates of quantum mechanics**, they tell us how to _represent a system_, _how it changes_, _how to read information_ out of it, and _how to combine systems_.

On its own quantum mechanics doesn’t tell us what laws a physical system must
obey, but it does **provide a mathematical and conceptual framework** for the development of such laws.

>[!Attention]
>The postulates of quantum mechanics were derived after a long process of trial and (mostly) error, which involved a _considerable amount of guessing and fumbling_ by the originators of the theory.

---
#### Dirac notation
The symbol $\vert{}\psi\rangle$ is called a **ket** (derived from the second half of the word "bracket"), it represents a _columnar vector_.

In a standard single-qubit system, the _computational basis states_ are written as:
$$\vert{}0\rangle = \begin{bmatrix} 1 \\ 0 \end{bmatrix}$$
An arbitrary superposition state is written as a linear combination: $\vert{}\psi\rangle = a\vert{}0\rangle + b\vert{}1\rangle$, where $a$ and $b$ are complex probability amplitudes.

The counterpart to the ket is the **bra** $\langle\psi\vert{}$, which represents a _row vector_ (specifically, the conjugate transpose of a ket).

Combining a bra and a ket forms a **braket** $\langle\phi\vert{}\psi\rangle$, which computes the _inner product_ (or dot product) between two quantum states.
>Geometrically, this scalar value tells us the "overlap" or _probability amplitude correlation between the two states_.

**Quantum gates** are represented as _matrices that act on state vectors_, and multi-qubit systems use tensor products to combine spaces.

- An **operator $U$ acting on a state** is written using juxtaposition: $U\vert{}\psi\rangle$
- **Multi-qubit states are combined** using the tensor product ($\otimes$), often shorthand-written as $\vert{}0\rangle \otimes \vert{}1\rangle = \vert{}01\rangle$
- The **outer product** $\vert{}\psi\rangle\langle\phi\vert{}$ creates a matrix operator rather than a scalar

#### Complex conjugate
Recall that a [[Numeri Complessi|complex number]] is just a number with two parts: a **real part** and an **imaginary part**, usually written as:
$$z=a+bi$$
- $a$ is the regular real number part
- $b$ is the coefficient of **$i$**, where $i$ is the "imaginary unit" defined as $i = \sqrt{-1}$ (meaning $i^2 = -1$)

The **complex conjugate** is a simple operation that involves _flipping the sign of the imaginary part_, it is usually denoted with an asterisk $*$, for example:
- If $z = 3 + 4i$, then its complex conjugate is $z^* = 3 - 4i$
- If $z = 5 - 2i$, then its complex conjugate is $z^* = 5 + 2i$
- If a number has no imaginary part (e.g., $7$), it is just $7 + 0i$, so its conjugate is still just $7$

##### Dagger (conjugate transpose / Hermitian adjoint)
The **dagger** symbol $\dagger$, is shorthand for two operations combined into one:
1. Transpose
2. Complex conjugate

So, for any matrix or vector $A$:
$$A^\dagger = (A^T)^*$$
For a ket vector, it is equal to turning it into a row vector, for example, if $\vert{}\psi\rangle = \begin{bmatrix} a \\ b \end{bmatrix}$, then its dagger is the bra $\langle\psi\vert{} = \begin{bmatrix} a^* & b^* \end{bmatrix}$.



---

### Postulate 1: state space
The first postulate of quantum mechanics sets up the arena in which quantum mechanics takes place, the arena is our familiar friend from linear algebra, Hilbert space.

>[!Cite] Postulate 1
>A closed system is described by a **unit vector** (the _state vector_) in a complex vector space with an inner product (a _Hilbert space_).

The simplest example is the **qubit**, whose space is 2-dimensional, with orthonormal basis $|0\rangle, |1\rangle$, any state is:
$$|\psi\rangle = a|0\rangle + b|1\rangle, \quad a,b\in\mathbb{C}$$
$$\text{Normalization condition: }\langle\psi|\psi\rangle = 1 \iff |a|^2+|b|^2=1$$
$|0\rangle,|1\rangle$ are the analogue of the bit values 0 and 1, the difference is that a qubit can also be in a **superposition** $a|0\rangle+b|1\rangle$, where we can’t say it is "definitely 0" or "definitely 1".

$a$ and $b$ are called **amplitudes**, for example, $\frac{|0\rangle-|1\rangle}{\sqrt2}$ has amplitude $1/\sqrt2$ on $|0\rangle$ and $-1/\sqrt2$ on $|1\rangle$.

It is possible to think of it as a length-2 vector of numbers (even complex ones) with Euclidean norm 1.
>The $|a|^2$ and $|b|^2$ will become probabilities in Postulate 3.

### Postulate 2: Evolution
How does the state, $\vert\psi\rangle$, of a quantum mechanical system change with time? The following postulate gives a prescription for the description of such state changes.

>[!Cite] Postulate 2
>The **evolution of a closed** system (one_ not interacting with anything else_) is a **unitary transformation**:
>$$|\psi'\rangle = U|\psi\rangle$$

A unitary transformation _preserves vector length_, so the _normalization condition_ is kept, and it is _reversible_.

**Quantum gates** are unitary matrices, that is: matrices that satisfy $U^\dagger U=I$ (where $I$ is the identity matrix), for example:
- **$X$ (bit flip / quantum NOT)**: $|0\rangle\leftrightarrow|1\rangle$
- **$Z$ (phase flip)**: leaves $|0\rangle$ alone and sends $|1\rangle\to-|1\rangle$. The extra $-1$ is a _phase factor_.
- **$H$ (Hadamard)**: $H|0\rangle=\frac{|0\rangle+|1\rangle}{\sqrt2}$, $H|1\rangle=\frac{|0\rangle-|1\rangle}{\sqrt2}$, with matrix $H=\frac1{\sqrt2}\begin{bmatrix}1&1\\1&-1\end{bmatrix}$, it turns a basis state into an equal superposition

#### Schrödinger equation
Instead of jumping from state to state instantly via a gate, quantum systems can also _evolve smoothly over continuous time_.

The **continuous-time** version of the second postulate is given by the **Schrödinger equation**:
$$i\hbar\frac{d|\psi\rangle}{dt}=H|\psi\rangle$$
- $H$ is a Hermitian matrix ($H=H^\dagger$) encoding the system’s energy and dynamics. $\hbar$ is a constant, usually set to 1
- Its solution is $|\psi(t_2)\rangle = U(t_1,t_2)|\psi(t_1)\rangle$ with $U=\exp\!\big[\tfrac{-iH(t_2-t_1)}{\hbar}\big]$

### Postulate 3: Quantum measurement
We postulated that closed quantum systems evolve according to unitary evolution, closed systems don't interact with the rest of the world, so far so good, but there must also be times where another external physical system **observes the system** in order to find out what is going on inside the system.

An **interaction** makes the system no longer closed, and thus _not necessarily subject to unitary evolution_, so to explain what happens when this is done, we introduce the third postulate, which provides a means for describing the effects of measurements on quantum systems.

>[!Cite] Postulate 3
>A measurement is a set of **measurement operators** $\{M_m\}$, one per possible outcome $m$.
>
>If the state of the quantum system is $|\psi\rangle$ immediately before the measurement then the **probability that result $m$ occurs** is defined by the **Born rule**:
>$$p(m)=\langle\psi|M_m^\dagger M_m|\psi\rangle$$
>
>The **state of the system after the measurement** is:
>$$\dfrac{M_m|\psi\rangle}{\sqrt{\langle\psi|M_m^\dagger M_m|\psi\rangle}}$$
>
>The measurement operators **satisfy the completeness equation**, which guarantees the probabilities sum to 1:
>$$\sum_m M_m^\dagger M_m=I$$

**Measuring a qubit**
$M_0=|0\rangle\langle0|$:
$$M_0 = \begin{bmatrix} 1 \\ 0 \end{bmatrix} \begin{bmatrix} 1 & 0 \end{bmatrix}= \begin{bmatrix} 1 & 0 \\ 0 & 0 \end{bmatrix}$$

$M_1=|1\rangle\langle1|$:
$$M_0 = \begin{bmatrix} 0 \\ 1 \end{bmatrix} \begin{bmatrix} 0 & 1 \end{bmatrix}= \begin{bmatrix} 0 & 0 \\ 0 & 1 \end{bmatrix}$$


Suppose the state being measured is $|\psi\rangle=a|0\rangle+b|1\rangle$, then the probability of obtaining measurement 0 is:
$$p(0)=\langle\psi| M_0^\dagger M_0|\psi\rangle=\langle\psi|M_0|\psi\rangle=|a|^2$$
Similarly, the probability of obtaining the measurement outcome 1 is $p(1)=|b|^2$.

The _state after measurement_ in the two cases is therefore:
$$\frac{M_0|\psi\rangle}{|a|}=\frac{a}{|a|}|0\rangle=|0\rangle$$$$\frac{M_1|\psi\rangle}{|b|}=\frac{b}{|b|}|1\rangle=|1\rangle$$
**Measuring collapses the superposition** to the outcome we saw.

#### Distinguishing quantum states
We're going to explain distinguishing quantum states using a communication between Alice and Bob.

**Perfect distinguishability**
Alice picks a state from an _orthonormal set_ (like $\vert{}0\rangle$ and $\vert{}1\rangle$) and hands it to Bob.
>"Orthonormal" means the states are completely independent and perpendicular to each other (like the X-axis and Y-axis on a graph).

_Bob can't fail decoding_ because the states don't overlap, Bob can design a tool using projectors $M_i = \vert{}\psi_i\rangle\langle\psi_i\vert{}$ for each state.

If Alice hands him state $i$, the probability of Bob measuring that exact result is $p(i) = \langle\psi_i\vert{}M_i\vert{}\psi_i\rangle = 1$ (100% certainty).

_There is no ambiguity_, so Bob can always identify the state with zero errors.

**Imperfect distinguishability**
Alice picks from a _set of overlapping (non-orthogonal) states_ (for example, $\vert{}0\rangle$ and a superposition state like $\frac{\vert{}0\rangle + \vert{}1\rangle}{\sqrt{2}}$) and gives one to Bob.
>"Non-orthogonal" means the states overlap, we can imagine two vectors pointing in directions that are close to each other, sharing a diagonal angle rather than being at a clean 90-degree right angle.

_Errors are unavoidable_:
- Any non-orthogonal state (let's call it $\vert{}\psi_2\rangle$) can be mathematically split into two parts: one part that is completely perpendicular to $\vert{}\psi_1\rangle$, and another part that is _parallel_ (overlapping) with $\vert{}\psi_1\rangle$
- Because $\vert{}\psi_2\rangle$ shares a parallel component with $\vert{}\psi_1\rangle$, whenever Bob tries to measure to see if it's $\vert{}\psi_1\rangle$, there is a  _non-zero chance_ that he will accidentally get a positive result, even if Alice actually sent $\vert{}\psi_2\rangle$
- Because of this unavoidable overlap, Bob will _always make mistakes sometimes_ when trying to guess which state he was given

>[!Info] Consequences for cryptography
>Since an attacker cannot look at non-orthogonal quantum states without disturbing them and making errors, any attempt from the attacker to intercept a secret quantum message will automatically introduce detectable flaws.

#### Projective measurements
The following represent highly structured subset of general measurements that we will encounter frequently during the course.

**The observable and spectral decomposition**
- Projective measurements are defined by an _observable_ $M$, which is a Hermitian matrix
- Any Hermitian matrix can be written via its _spectral decomposition_ as $M = \sum_m m P_m$
- The possible numerical outcomes of your measurement correspond directly to the _eigenvalues_ ($m$) of this observable
- The operators $P_m$ are _orthogonal projectors_ that project the state onto the specific eigenspace associated with eigenvalue $m$

**Probabilities and post-measurement states**
- The probability of getting a specific outcome $m$ when measuring a state $\vert{}\psi\rangle$ is given by $p(m) = \langle\psi\vert{}P_m\vert{}\psi\rangle$
- Immediately after the measurement yields outcome $m$, the system's state collapses and updates to $\frac{P_m\vert{}\psi\rangle}{\sqrt{p(m)}}$

**Repeatability**
- A defining feature of projective measurements is _repeatability_
- If we perform a projective measurement and obtain an outcome $m$, performing the exact same measurement a second time immediately after will yield outcome $m$ with 100% certainty without changing the state further

**Averages, spread, and the uncertainty principle**
- The _average (expected) value_ of an observable across many runs is calculated as $\mathbb{E}(M) = \sum_m m\,p(m) = \langle\psi\vert{}M\vert{}\psi\rangle$
	This average value is often written compactly as $\langle M \rangle$

- The _standard deviation_ (representing the spread or variance of the results) is calculated as $[\Delta M]^2 = \langle M^2 \rangle - \langle M \rangle^2$

- The _Heisenberg uncertainty principle_ establishes a mathematical lower bound on the product of the standard deviations of two non-commuting observables $C$ and $D$.
	This principle is expressed as $\Delta(C)\Delta(D) \ge \frac{\vert{}\langle\psi\vert{}[C,D]\vert{}\psi\rangle\vert{}}{2}$, where $[C,D] = CD - DC$ is the commutator.

The uncertainty principle does _not_ mean that measuring $C$ physically "disturbs" $D$, instead, it describes an intrinsic statistical property: if we prepare many identical copies of $\vert{}\psi\rangle$ and measure $C$ on some and $D$ on others, their respective result spreads must obey this inequality.

**Measuring qubits**
The Pauli-$Z$ operator has eigenvalues $\pm 1$ and eigenvectors $\vert{}0\rangle$ and $\vert{}1\rangle$, and measuring $Z$ on an equal superposition state like $\frac{\vert{}0\rangle + \vert{}1\rangle}{\sqrt{2}}$ yields $+1$ or $-1$ with a probability of $1/2$ each.

_Spin along axis $\vec{v}$_: for any 3D unit vector $\vec{v} = (v_1, v_2, v_3)$, the observable $\vec{v}\cdot\vec{\sigma} = v_1 X + v_2 Y + v_3 Z$ has eigenvalues $\pm 1$.
>The corresponding projectors for this observable are given by $P_\pm = \frac{I \pm \vec{v}\cdot\vec{\sigma}}{2}$.

>[!Tip] Basis Phrasings
>When we refer to: "measure in the basis $\vert{}m\rangle$," it simply means performing a projective measurement using the orthogonal projectors $P_m = \vert{}m\rangle\langle m\vert{}$.

#### POVM measurements
**POVM** stands for **Positive Operator-Valued Measure**.
It is a mathematical framework used when we only care about the **probabilities of measurement outcomes**, and we don't care about (or preserve) the state of the system after the measurement is finished.
>This frequently happens when a measurement is performed only once at the very end of an experiment.

Instead of tracking individual measurement operators $M_m$, we _combine them into a single set of operators_ called **POVM elements**, denoted as $E_m$:
$$E_m \equiv M_m^\dagger M_m$$
For a **valid POVM**:
- Each operator $E_m$ must be _positive_ (semi-definite).
- They must _satisfy the completeness relation_: $\sum_m E_m = I$ (meaning total probabilities sum to 1).

The probability of getting outcome $m$ is calculated simply as $p(m) = \langle\psi\vert{}E_m\vert{}\psi\rangle$, conversely, _any_ set of positive operators that sum to the identity matrix $I$ _forms a valid POVM_, because we can always define $M_m = \sqrt{E_m}$.
>For standard projective measurements, the POVM elements are just the projectors themselves ($E_m = P_m$).


>[!Example] Unambiguous discrimination
>A classic application of POVMs is **unambiguous state discrimination**, where we want to identify an unknown state without ever making a mistake, even if it means sometimes getting an inconclusive result.
>
>Imagine Alice sends Bob a qubit chosen from one of two non-orthogonal states:
>- $\vert{}\psi_1\rangle = \vert{}0\rangle$
>- $\vert{}\psi_2\rangle = \frac{\vert{}0\rangle + \vert{}1\rangle}{\sqrt{2}}$
>
>Because these states overlap (they are non-orthogonal), standard quantum mechanics says Bob _cannot distinguish them with 100% accuracy_ all the time. However, Bob can use a clever **3-outcome POVM** ($\{E_1, E_2, E_3\}$) to play it safe:
>1. **Outcome $E_1$**: built proportional to $\vert{}1\rangle\langle1\vert{}$, this operator is mathematically constructed so that $\langle\psi_1\vert{}E_1\vert{}\psi_1\rangle = 0$. This means _it never fires if Alice sent $\vert{}0\rangle$_, so if Bob measures $E_1$, he knows with _100% certainty_ that Alice sent $\vert{}\psi_2\rangle$
>2. **Outcome $E_2$**: built proportional to $\vert{}-\rangle\langle-\vert{}$ (where $\vert{}-\rangle = \frac{\vert{}0\rangle - \vert{}1\rangle}{\sqrt{2}}$), this operator never fires if Alice sent $\vert{}\psi_2\rangle$, if Bob measures $E_2$, he knows with _100% certainty_ that Alice sent $\vert{}\psi_1\rangle$.  
>3. **Outcome $E_3$ ($E_3 = I - E_1 - E_2$)**: this is the _inconclusive_ outcome. Bob learns nothing about which state was sent.
>
>**The Trade-off**: Bob never misidentifies a state (zero error rate), but he pays the price that sometimes the measurement yields $E_3$, giving him no information.

#### Phase
In quantum mechanics, **phase** refers to an angle or multiplier attached to quantum states, depending on how it is applied, phase falls into two distinct categories.

**Global phase**
Affects the entire state vector uniformly by multiplying it by a complex number of magnitude 1, written as $e^{i\theta}$.

When we calculate the probability of any measurement outcome, the global phase factor appears as both $e^{-i\theta}$ and $e^{i\theta}$ right next to each other, multiplying to $1$ ($e^{-i\theta}e^{i\theta} = 1$).

So, because measurement statistics remain completely unchanged, global phases are _physically invisible and can be safely ignored_.

**Relative phase**
Occurs when phase factors differ across individual amplitudes within a superposition rather than affecting the whole state equally.

Looking at these two states:
$$\frac{\vert{}0\rangle + \vert{}1\rangle}{\sqrt{2}} \quad \text{vs.} \quad \frac{\vert{}0\rangle - \vert{}1\rangle}{\sqrt{2}}$$
The $\vert{}0\rangle$ amplitude is positive in both, but the $\vert{}1\rangle$ amplitude has a relative phase difference of $-1$ (or $e^{i\pi}$) in the second state.

Unlike global phase, relative phase is _basis-dependent_ and _physically observable_.
Changing the relative sign _alters how quantum states interfere with one another during circuit operations_, yielding entirely different measurement outcomes if measured in a different basis (such as the X-basis).

### Postulate 4: Composite systems
Suppose we are interested in a **composite** quantum system _made up of two (or more) distinct physical systems_.

How should we **describe states of the composite system**?

The following postulate describes _how the state space of a composite system is built up from the state spaces of the component systems_.

>[!Cite] Postulate 4
>The state space of a composite physical system is the **tensor product** of the state spaces of the component physical systems.
>
>Moreover, if we have systems numbered $1$ through $n$, and system number $i$ is prepared in the state $|\psi_i\rangle$, then the joint state of the total system is:
>$$|\psi_1\rangle\otimes\dotsi\otimes|\psi_n\rangle$$

Why is the tensor product the mathematical structure used to describe the state space of a composite physical system?

At one level, we can simply **accept it as a basic postulate**, not reducible to something more elementary, and move on.
>And that's what we're going to do.

