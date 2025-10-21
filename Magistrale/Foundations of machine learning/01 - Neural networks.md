From a **DARPA neural network study** in 1989, we can highlight the following statements:
- Neural networks are adaptive, or trainable
- Neural networks are naturally massively parallel

While this is true, it is also important to highlight that neural networks are not the only trainable data structure, the second point also suggests that the networks should be able to make decisions at **high-speed** and be **fault tolerant**, this is because if a neuron "dies" there are many other that will carry information.

The true potential behind this data structure, is given by the enormous number of **connections** between neurons.

The **transmission of a signal in the cerebral cortex** is a complex process, that can be simplified as it follows:
- The cellular body performs a "weighted sum" of the incoming signals
- If the result exceeds a certain threshold, then it produces an "action potential" which is sent down the axon (the neuron has "fired"), otherwise it remains in a rest state
- A chemical reaction then will provoke the diffusion of an electrical signal to other neurons

The **synaptic efficacy** is the amount of current that enters in the next neuron, compared to the action potential of the pre-synaptic neuron.
>Learning involves modifying the synaptic efficacy.

Synapses can **excite** in order to favor the generation of action potential in the post-synaptic neuron, or **inhibit** in order to hinder the generation of action potential.

### The McCulloch and Pitts Model
The McCulloch and Pitts (MP) neuron is modeled as a binary threshold unit, it "fires" if the **net input** $\sum\limits_{j}w_jI_j$ reaches (or exceeds) the threshold (bias) $T$:
$$y=g\left(\sum_j w_jI_j-T\right)$$
If the neuron is firing, then its output $y$ is $1$, otherwise it is $0$.:
$$g(x)=\begin{cases}
0&\text{if } x<0\\
1&\text{if } x\geq 0
\end{cases}$$
![[MP neuron.png|500]]

Weights $w_{ij}$ represent the strength of the synapse between neuron $j$ and neuron $i$.

By properly combining MP neurons it is possible to simulate the behavior of any boolean circuit, follows _not_, _and_, _or_:
![[MP neuron logic gates.png|500]]
