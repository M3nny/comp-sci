A **classical bit** is either 0 or 1, whilst a **qubit** has two basis states, written $|0\rangle$ and $|1\rangle$ (check [[00 - Postulates of quantum mechanics#Dirac notation|Dirac notation]]), but it can also be in a **superposition**:
$$|\psi\rangle = \alpha|0\rangle + \beta|1\rangle$$

We recall that $\alpha$ and $\beta$ are **amplitudes**, in practice:
$$|0\rangle = \begin{pmatrix}1\\0\end{pmatrix}\quad|1\rangle = \begin{pmatrix}0\\1\end{pmatrix}\quad|\psi\rangle = \begin{pmatrix}\alpha\\\beta\end{pmatrix}$$

### Measurement
We cannot read $\alpha$ and $\beta$ from a qubit, when we measure we get only $0$ or $1$:
- $P(0)=|\alpha|^2$
- $P(1)=|\beta|^2$

Probabilities sum up to $1$, so $|\alpha|^2+|\beta|^2=1$.

After a measurement, the **state collapses** (changes), which means that after we get result $0$, the qubit is now exactly $|0\rangle$, likewise with $1$.

In other words, the state is "hidden", but it has real consequences, _states can be manipulated_ so that the measurement outcomes depend on $\alpha$ and $\beta$, and that's where quantum computing comes in.

Take as an example the following state:
$$\frac{1}{\sqrt{2}}|0\rangle + \frac{1}{\sqrt{2}}|1\rangle$$
here $|\alpha|^2 = |\beta|^2 = \frac{1}{2}$, so measuring gives $0$ or $1$ with 50% probability each, this state is called $|+\rangle$ and will appear often.

>[!Tip]
>A qubit can be anywhere on a **continuum between $|0\rangle$ and $|1\rangle$**, until observed.
>
>This is not the same as "a coin that’s randomly heads or tails but we don’t know which", since in this case the superposition is a genuinely different state.

Qubits **can be built in several ways**, for example: photon polarization, nuclear spin in a magnetic field, or two energy levels of an electron in an atom.
![[Qubit represented by two electronic levels in an atom.png]]
>Shining light on the atom for the right amount of time flips $|0\rangle\leftrightarrow|1\rangle$, shining it for half that time puts it in $|+\rangle$.

### The Bloch sphere
Using $|\alpha|^2 + |\beta|^2 = 1$, any qubit state can be written as:
$$|\psi\rangle = \cos\frac{\theta}{2}|0\rangle + e^{i\varphi}\sin\frac{\theta}{2}|1\rangle$$
$\theta$ and $\varphi$ are **two angles**, so a single-qubit state is a point on the surface of the so called **Bloch sphere**:
- North pole = $|0\rangle$
- South pole = $|1\rangle$
- Other points = superposition
![[Bloch sphere.png]]
>This is a nice visualization for one qubit, but there is no simple generalization for multiple qubits.

There's an apparent paradox: there are **infinite points** on the sphere, so in principle we could store a huge text in the digits of $\theta$, but this isn't the case because measurement gives **only one bit** and _destroys the state_.

For example, if measuring $|+\rangle$ gives $0$, then the post-measurement state of the qubit will be $|0\rangle$, why does this type of collapse occur? **nobody knows**, this is one of the [[00 - Postulates of quantum mechanics|four postulates of quantum mechanics]].

So, in reality the extractable information per qubit is $1$ bit, yet nature seems to "keep track" of the continuous $\alpha$ and $\beta$ during _evolution_, understanding and exploiting this _hidden information_ is the central theme of quantum computing.

### Multiple qubits
Two qubits have four basis states: $|00\rangle, |01\rangle, |10\rangle, |11\rangle$, and a **general state** is:
$$|\psi\rangle = \alpha_{00}|00\rangle + \alpha_{01}|01\rangle + \alpha_{10}|10\rangle + \alpha_{11}|11\rangle$$
Measuring both qubits gives result $x$ with probability $|\alpha_x|^2$, and the state collapses to $|x\rangle$, **normalization** says that all four $|\alpha_x|^2$ sum to 1.

We can measure only a single bit if we want to, for example we can **measure the first bit** and get $0$ with probability $|\alpha_{00}|^2 + |\alpha_{01}|^2$, the state collapses to the part consistent with that result, and it is _re-normalized_ so it’s a valid unit vector again:
$$|\psi'\rangle = \frac{\alpha_{00}|00\rangle + \alpha_{01}|01\rangle}{\sqrt{|\alpha_{00}|^2 + |\alpha_{01}|^2}}$$
>Throw away the terms that don’t match, then rescale.

#### The Bell state
An important two qubit state is the **Bell state (or EPR pair)**:
$$\frac{|00\rangle + |11\rangle}{\sqrt{2}}$$
Upon measuring the the first qubit, one obtains two possible results: $0$ with probability $1/2$, leaving the post measurement state $|\varphi'\rangle=|00\rangle$, and $1$ with probability $1/2$, leaving $|\varphi'\rangle=|11\rangle$.
As a result, a measurement of <u>the second qubit always gives the same result as the measurement of the first qubit</u>, that is, the measurement outcomes are **correlated**.

>[!Info]
>Bell proved that **correlations** in this state (under other kinds of measurements) are **stronger than any classical system could produce**.
>
>This was the first hint that quantum mechanics _allows information processing beyond classical limits_.

For **$n$ qubits**, there are $2^n$ amplitudes, for $n = 500$, $2^{500}$ exceeds the estimated number of atoms in the universe.
No classical computer could store that, yet nature handles it with a few hundred atoms, this _enormous potential computational power_ is something we would very much like to take advantage of.

