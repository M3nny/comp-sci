CNNs can be used for **several tasks**.
![[CNN usage.png|600]]

### Why not a fully connected layer
We recall that a **fully connected layer** (FC) is just a layer where each of its neuron is connected to every neuron of the next layer.

If we wanted to process a tiny $5\times5\times1$ image with an FC layer of neurons, we would need $25$ weights per neuron, this becomes unfeasible for normal images that are $1920\times1080\times3$.

This won't work even when stacking multiple layers, since it is just **brute forcing**, there is not spatial relationship between pixels, and optimization becomes hard.

An **image is characterized by**:
- _Local structure_
- _Pattern_ that may repeat across the image
- _Distance pixels_ generally don't directly affect each other
- Data lives on a _regular grid_

So we better give the layer **explicit structure**, and reuse (share) the same weights across different spatial locations of the image, this **weight-sharing** idea is literally  the **convolution**.

### Convolution
Convolution can be applied to arbitrary shapes of data (even 1D), even though it is mostly used for 2D data (images).

A CNN pass works by passing a **kernel** upon the whole grid and thus creating a **feature map** with one "hidden neuron" computed per kernel position.
![[CNN pass.png|500]]
These kernels when applied to an image will create filters of the image itself (e.g. blur), but rather than hand-crafting kernels, the network can **learn the kernel weight** via backpropagation, and then the _filter that best extract useful features_ are discovered from data instead of designed by hand.

These kernels can be "reused" across the image to detect similar patterns wherever they occur, and this reuse (weight sharing) is what makes convolution **parameter efficient**.

A filter's depth **must always match the input's depth**, we don't independently choose filter depth.

At each spatial location, the filter computes one number via a dot product between the filter weights and the corresponding chunk of the image, plus a bias:
$$z_i=w^Tx_i+b$$
Applying **multiple filters** stacks multiple activation maps together, and each filter learns to detect something different.
>The _number of channels of the activation maps_ depends on the number of filters of the previous layer (initially it is just the image depth, which is usually $3$).

The general **output size** (without padding) for input $N\times N$, filter $F\times F$, stride $S$, is given by:
$$\text{output size}=\left(\frac{N-F}{S}+1\right)\times\left(\frac{N-F}{S}+1\right)$$
Note that **fractions are illegal**, so the stride/filter/input combinations must divide evenly, or padding must be added to fix it.
>Stride is defined by how much the kernel is moved every $S$-th spatial location.

**Padding** is justified by the fact that sizes shrink too quickly across layers, and corner/edge pixels get used in far fewer convolutions windows than central pixels (i.e. they're under-represented), the fix is to pad the input.
The general output size formula with padding $P$ becomes:
$$\text{output size}=\left(\lfloor\frac{N+2P-F}{S}\rfloor+1\right)\times\left(\lfloor\frac{N+2P-F}{S}\rfloor+1\right)$$

### Receptive fields
The receptive field is defined as the spatial extent of the input that a given output value is **connected to**, so a single $3\times 3$ filter means $1$ output pixel is connected to $9$ input pixels.

This effect stacks since and output unit two layers deep is influenced by many original pixel just by looking at only a bunch of them from the previous layer (sort of a compression of information).

**Stacking small filters** across many layers is a common design choice, it grows the effective receptive field without needing huge filters.

### ConvNET
A **ConvNET** is simply a **concatenation of conv layers and activation functions** stacked in sequence.
>Each stage narrows spatial dimensions while increasing depth.

Early layers tend to learn low-level features, middle layers learn mid-level features, and deeper layers learn high-level, semantically meaningful features.

While a conv layer performs _feature extraction_ (computing a feature response in a local region), a **pooling layer** performs _feature selection_ by picking out the strongest activation in a local region, and downsamples spatially in the process (depth is unchanged, only height/width shrink).

**Max pooling** takes the maximum value within each pooling window, whilst **average pooling** uses the same idea, but takes the mean instead of the max over each window.
