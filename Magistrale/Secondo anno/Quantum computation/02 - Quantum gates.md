Changes occurring to a quantum state can be described using the language of **quantum computation**, which is built from **quantum circuits**, made of wires and **quantum gates**.

A single-qubit gate is a $2\times 2$ matrix and a two-qubit gate is a $4\times 4$ matrix, the only requirement is that _the matrix must be unitary_ (preserves the normalization of the state).

### Quantum NOT gate
A classical NOT swaps $0 \leftrightarrow 1$, the obvious quantum analogue swaps $|0\rangle \leftrightarrow |1\rangle$, but that alone doesn’t say what happens to superpositions.

The key fact is that **quantum gates act linearly**:
$$\alpha|0\rangle + \beta|1\rangle \;\longmapsto\; \alpha|1\rangle + \beta|0\rangle$$
this _linear behavior_ is a general property of quantum mechanics.

>[!Attention]
>Nonlinear behavior can lead to apparent paradoxes such as time travel, faster-than-light communication, and violations of the [second law of thermodynamics](https://en.wikipedia.org/wiki/Second_law_of_thermodynamics).

Because gates are linear, they can be written as **matrices**, the quantum NOT is called $X$:
$$X \equiv \begin{pmatrix} 0 & 1 \\ 1 & 0 \end{pmatrix}, \qquad X\begin{pmatrix}\alpha\\\beta\end{pmatrix} = \begin{pmatrix}\beta\\\alpha\end{pmatrix}$$
>The first column of a gate matrix is what the gate does to $|0\rangle$, and the second column is what it does to $|1\rangle$.

The **only constraint** to quantum gates is that the matrix used to represent it must be [[00 - Postulates of quantum mechanics#Postulate 2 Evolution|unitary]], for this reason, _any unitary matrix_ is a **valid quantum gate**.

Classically there is only one non-trivial single-bit gate (NOT), quantum mechanically there are **infinitely many** single-qubit gates.

#### Pauli gate
Leaves $|0\rangle$ alone and flips the sign of $|1\rangle$:
$$Z \equiv \begin{pmatrix} 1 & 0 \\ 0 & -1 \end{pmatrix}, \qquad Z|0\rangle = |0\rangle, \quad Z|1\rangle = -|1\rangle$$

#### Hadamard gate
$$H \equiv \frac{1}{\sqrt{2}}\begin{pmatrix} 1 & 1 \\ 1 & -1 \end{pmatrix}$$
- $H|0\rangle = \dfrac{|0\rangle + |1\rangle}{\sqrt{2}}$ (first column), "halfway" between $|0\rangle$ and $|1\rangle$
- $H|1\rangle = \dfrac{|0\rangle - |1\rangle}{\sqrt{2}}$ (second column), also "halfway"

It is loosely called a "square root of NOT", but it is not a NOT gate, in fact: $H^2 = I$, so applying $H$ twice does nothing.

![[Hadamard gate.png]]
Single-qubit gates correspond to **rotations and reflections of the [[01 - Qubits#The Bloch sphere|Bloch sphere]]**.
The Hadamard is a $90^\circ$ rotation about the $\hat{y}$ axis followed by a $180^\circ$ rotation about the $\hat{x}$ axis.

### Decomposing arbitrary single-qubit gates
There are **infinitely many single-qubit gates**, but they can all be built from a small set of building blocks, any $2\times 2$ unitary $U$ can be written as:
$$U = e^{i\alpha}\begin{pmatrix} e^{-i\beta/2} & 0 \\ 0 & e^{i\beta/2} \end{pmatrix}\begin{pmatrix} \cos\frac{\gamma}{2} & -\sin\frac{\gamma}{2} \\ \sin\frac{\gamma}{2} & \cos\frac{\gamma}{2} \end{pmatrix}\begin{pmatrix} e^{-i\delta/2} & 0 \\ 0 & e^{i\delta/2} \end{pmatrix}$$
with $\alpha, \beta, \gamma, \delta$ real, the pieces are:
- A global phase $e^{i\alpha}$ (unobservable)
- An ordinary rotation (the middle matrix)
- Two rotations about the $\hat{z}$ axis (the outer matrices)

We don’t need exact gates for every angle, good approximations built from a **finite set of fixed gates** are enough.

### Multiple-qubit gates
Classical multi-bit gates are: AND, OR, XOR, NAND, NOR, where **NAND is universal**, which means that any boolean function can be computed using NAND gates alone.

The **Controlled-NOT (CNOT) gate** takes two qubits and a target:
- If control $= 0$: target is left alone
- If control $= 1$: target is flipped
$$|00\rangle \to |00\rangle, \quad |01\rangle \to |01\rangle, \quad |10\rangle \to |11\rangle, \quad |11\rangle \to |10\rangle$$

We can see it as a **XOR generalization**: $|A, B\rangle \to |A, B \oplus A\rangle$.
>Where $\oplus$ is addition mod 2.

![[CNOT.png]]
Classical gates like NAND or XOR cannot be made unitary like NOT, this is because they are **irreversible**, from the output $A \oplus B$ we cannot recover $A$ and $B$, so information is lost, on the other side, unitary gates are always **invertible**, since the inverse of a unitary matrix is also unitary, so _classical logic must be redone in a reversible way_ for quantum computers.

#### Measurements in other bases
$|0\rangle, |1\rangle$ is just one possible basis, another is:
$$|+\rangle \equiv \frac{|0\rangle + |1\rangle}{\sqrt{2}}, \qquad |-\rangle \equiv \frac{|0\rangle - |1\rangle}{\sqrt{2}}$$

Any state can be rewritten in this basis:
$$|\psi\rangle = \alpha|0\rangle + \beta|1\rangle = \frac{\alpha + \beta}{\sqrt{2}}|+\rangle + \frac{\alpha - \beta}{\sqrt{2}}|-\rangle$$
Measuring in the $\{|+\rangle, |-\rangle\}$ basis gives:
- result "$+$" with probability $\dfrac{|\alpha + \beta|^2}{2}$, leaving the state $|+\rangle$
- result "$-$" with probability $\dfrac{|\alpha - \beta|^2}{2}$, leaving the state $|-\rangle$

For any **orthonormal** basis $\{|a\rangle, |b\rangle\}$, write $|\psi\rangle = \alpha|a\rangle + \beta|b\rangle$, then measuring in that basis gives $a$ with probability $|\alpha|^2$ and $b$ with probability $|\beta|^2$.
>Orthonormality is what guarantees $|\alpha|^2 + |\beta|^2 = 1$.

### Quantum circuits
Circuits are read **left to right**, each line is a **wire**, which may represent the _passage of time_ or a particle (e.g. a photon) moving through space, not necessarily a physical wire.

By convention the input is a computational basis state, usually all $|0\rangle$'s.

Let's see how to implement a **qubit swap** (recall that all additions are mod 2):
$$
\begin{aligned}
|a, b\rangle &\longrightarrow |a, a \oplus b\rangle\\
&\longrightarrow |a \oplus (a \oplus b), a \oplus b\rangle = |b, a \oplus b\rangle\\
&\longrightarrow |b, (a \oplus b) \oplus b\rangle = |b, a\rangle
\end{aligned}
$$
![[Qubit swap.png]]
>Circuit swapping two qubits, and an equivalent schematic symbol notation for this common circuit.

The main **differences from classical circuits** are:
- _No loops_: quantum circuits are acyclic
- _No FANIN_: merging wires with a bitwise OR is irreversible, so not unitary
- _No FANOUT_: copying a qubit is impossible

We introduce another _convention_ when representing quantum circuits.
For any unitary $U$ acting on $n$ qubits, the **controlled-$U$ gate** has one control qubit and $n$ target qubits:
- Control $= 0$: nothing happens
- Control $= 1$: $U$ is applied to the targets
>CNOT is the special case $U = X$.

![[Controlled-U gate.png]]
A **meter symbol** is used to represent _measurement_, it converts a qubit $\alpha|0\rangle + \beta|1\rangle$ into a **classical bit** $M$ (drawn as a double line), equal to $0$ with probability $|\alpha|^2$ and $1$ with probability $|\beta|^2$.
![[Measurement symbol.png]]

#### Can we copy qubits?
Consider the task of copying a classical bit, this may be done using a CNOT gate, which takes in the bit to copy (in some unknown state $x$) and a "scratchpad" bit initialized to zero:
![[Copying a bit.png]]
The output is two bits, both of which are in the same state $x$.

Suppose we try to copy a qubit in the unknown state $|\psi\rangle = a|0\rangle + b|1\rangle$ in the same manner by using a CNOT gate, the input state of the two qubits may be written as:
$$\big[a|0\rangle + b|1\rangle\big]|0\rangle = a|00\rangle + b|10\rangle$$
The function of CNOT is to negate the second qubit when the first qubit is $1$, and thus the output is simply $a|00\rangle + b|11\rangle$, but, have we successfully copied $|\psi\rangle$? That is, have we created the state $|\psi\rangle|\psi\rangle$?

In the case where $|\psi\rangle=|0\rangle$ or $|\psi\rangle=|1\rangle$, then yes, that is indeed what this circuit does, however, for a general state $|\psi\rangle$ we see that:
$$|\psi\rangle|\psi\rangle = a^2|00\rangle + ab|01\rangle + ab|10\rangle + b^2|11\rangle$$
We see that unless $ab=0$ the "copying circuit" above **does not copy** the quantum state input, it is in fact **impossible to make a copy** of an unknown state.

Intuition of the **no-cloning theorem** _via hidden-information_:
	Measure one qubit of $a|00\rangle + b|11\rangle$ and the other is completely determined (as seen in [[01 - Qubits#The Bell state|Bell state]]), so no more information about $a$ and $b$ can be extracted.
	A genuine copy would still carry the hidden information in the second qubit, but this is not the case, so a copy cannot have been made.

### Bell states from a circuit
A circuit with a _Hadamard on the first qubit followed by a CNOT_ creates the **Bell states**, for example:
$$|00\rangle \xrightarrow{H \text{ on 1st qubit}} \frac{(|0\rangle + |1\rangle)|0\rangle}{\sqrt{2}} \xrightarrow{\text{CNOT}} \frac{|00\rangle + |11\rangle}{\sqrt{2}}$$

$H$ puts the top qubit in superposition, that qubit then acts as the control, so the target flips only in the "1" branch.

The four outputs for the four basis inputs are the **Bell states** (also called EPR states or EPR pairs):
$$|\beta_{00}\rangle = \frac{|00\rangle + |11\rangle}{\sqrt{2}}, \qquad |\beta_{01}\rangle = \frac{|01\rangle + |10\rangle}{\sqrt{2}}$$ $$|\beta_{10}\rangle = \frac{|00\rangle - |11\rangle}{\sqrt{2}}, \qquad |\beta_{11}\rangle = \frac{|01\rangle - |10\rangle}{\sqrt{2}}$$
These four Bell states can be written in one formula:
$$|\beta_{xy}\rangle \equiv \frac{|0,y\rangle + (-1)^x|1,\bar{y}\rangle}{\sqrt{2}}$$
where $\bar{y}$ is the negation of $y$. Check with $x=0, y=0$: $\frac{|0,0\rangle + |1,1\rangle}{\sqrt{2}} = |\beta_{00}\rangle$.
![[Quantum circuit to create Bell states.png]]
### Quantum teleportation
**Quantum teleportation** moves an unknown qubit state from Alice to Bob using only a shared **EPR pair** and **two classical bits** of communication, combining everything seen so far.

The problem **setup** is the following:
- Alice and Bob once shared an EPR pair, and each kept one qubit, but now they live far apart
- Alice wants to send Bob an _unknown_ qubit $|\psi\rangle$
- She can only send _classical_ information

This is a **problem**, since:
- Alice doesn’t know $|\psi\rangle$, and she can't learn it from a single copy (measurement destroys it, and no-cloning forbids copying)
- Even if she knew it, describing (to Bob) a point in a continuous space would take infinitely many classical bits

The **idea of the solution** is:
1. Alice interacts $|\psi\rangle$ with her half of the EPR pair
2. She measures her two qubits and gets one of four classical results: $00, 01, 10, 11$
3. She sends those 2 classical bits to Bob
4. Bob applies one of four operations to his qubit and recovers $|\psi\rangle$

![[Quantum teleport.png]]
>Quantum circuit for teleporting a qubit.
>The two top lines represent Alice's system, while the bottom line is Bob's system. The meters represent measurement, and the double lines coming out of them carry classical bits (recall that single lines denote qubits).

The state to teleport is $|\psi\rangle = \alpha|0\rangle + \beta|1\rangle$ with unknown $\alpha, \beta$.

**Initial state**
$$|\psi_0\rangle = |\psi\rangle|\beta_{00}\rangle = \frac{1}{\sqrt{2}}\Big[\alpha|0\rangle(|00\rangle + |11\rangle) + \beta|1\rangle(|00\rangle + |11\rangle)\Big]$$

**Step 1**
Alice applies CNOT (control: her qubit $|\psi\rangle$, target: her half of the EPR pair), the CNOT flips the 2nd and 3rd or, more precisely, it flips Alice's second qubit whenever the first is $1$:
$$|\psi_1\rangle = \frac{1}{\sqrt{2}}\Big[\alpha|0\rangle(|00\rangle + |11\rangle) + \beta|1\rangle(|10\rangle + |01\rangle)\Big]$$
**Step 2**
Alice applies a Hadamard to her first qubit:
$$|\psi_2\rangle = \frac{1}{2}\Big[\alpha(|0\rangle + |1\rangle)(|00\rangle + |11\rangle) + \beta(|0\rangle - |1\rangle)(|10\rangle + |01\rangle)\Big]$$
**Step 3**
Regroup by Alice's two qubits:
$$|\psi_2\rangle = \frac{1}{2}\Big[|00\rangle(\alpha|0\rangle + \beta|1\rangle) + |01\rangle(\alpha|1\rangle + \beta|0\rangle) + |10\rangle(\alpha|0\rangle - \beta|1\rangle) + |11\rangle(\alpha|1\rangle - \beta|0\rangle)\Big]$$
Each term pairs one of Alice's four possible measurement outcomes with a state of Bob's qubit.

**Step 4**
Alice measures both her qubits, each outcome has probability $1/4$, and Bob's qubit collapses to:

| Alice's result | Bob's state $\lvert\psi_3\rangle$              | Fix needed          |
| -------------- | ---------------------------------------------- | ------------------- |
| $00$           | $\alpha\lvert 0\rangle + \beta\lvert 1\rangle$ | None                |
| $01$           | $\alpha\lvert 1\rangle + \beta\lvert 0\rangle$ | $X$                 |
| $10$           | $\alpha\lvert 0\rangle - \beta\lvert 1\rangle$ | $Z$                 |
| $11$           | $\alpha\lvert 1\rangle - \beta\lvert 0\rangle$ | $X$ first, then $Z$ |

**Step 5**
Bob corrects: after Alice sends the two bits $M_1M_2$, Bob applies
$$Z^{M_1} X^{M_2}$$
to his qubit.
>Recall that in matrix products, the rightmost operator acts first (so $X^{M_2}$ is applied before $Z^{M_1}$), even though circuit diagrams read left to right.

Bob ends up with exactly $|\psi\rangle$.

>[!Tip] Does teleportation break anything?
>**Is this faster-than-light communication?**
>No. Bob’s qubit is in one of four possible states, and he can't know which one without Alice’s classical message.
>That message travels at most at light speed, without it, teleportation conveys no information at all.
>
>**Doesn’t this copy $|\psi\rangle$, violating no-cloning?**
>No. After teleportation, only Bob's qubit is in state $|\psi\rangle$, Alice's original qubit has been measured and ends up in $|0\rangle$ or $|1\rangle$, the state was moved, not duplicated.

