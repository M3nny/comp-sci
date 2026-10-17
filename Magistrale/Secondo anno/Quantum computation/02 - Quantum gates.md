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

