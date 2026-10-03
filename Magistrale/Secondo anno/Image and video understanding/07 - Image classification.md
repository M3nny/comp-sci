Image classification consists in **assigning a label** to an image, many other vision tasks (e.g. detection, segmentation, captioning) are built on top of it.

**Challenges** that appear in this task are:
- _Viewpoint variation_: the exact same object looks completely different in pixel space from another angle
- _Illumination_: lighting changes pixel values drastically
- _Deformation_: non-rigid objects can bend into many poses
- _Occlusion_: only part of the object may be visible
- _Background clutter_: object can blend into a busy background
- _Intra-class variation_: huge visual diversity within one category

A classifier can't be hand-coded with simple rules for these variations, this is why data-driven learned approaches are necessary.

### CNN building blocks
We recall from the [[02 - CNN recap|CNN chapter]] the main building blocks of a CNN:
- **Convolution layer**: a small filter slides across the input volume, computing dot products, producing an activation/feature map, multiple filters produce multiple output channels (depth)
- **Pooling layer**: downsamples spatially (e.g. max-pool), reducing resolution and parameter count while adding translation robustness

The **typical architecture pattern** is to stack `[CONV -> RELU] x N -> POOL` blocks a few times, then flatten into `[FC -> RELU] x M -> Softmax`.

#### Normalization layers
Normalization layers improve training and optimization algorithms, allowing higher learning rates (faster convergence).

**Batch normalization**
If layer inputs aren't zero-centered (or consistently scaled) optimization becomes hard (needs large biases and widely varying weights).

BatchNorm normalizes each activation dimension to zero-mean across the mini-batch, then applies a learnable scale $\gamma$ and $\beta$ so the network can undo the normalization if that's actually better for a given layer.

Sine batch statistics only exist when we have a batch, at test time (often single-sample inference), BatchNorm instead uses a running average of mean/variance accumulated during training.

**Layer normalization**
Normalizes across the feature dimension per single sample instead of across the batch, most useful when the batch size is small or variable (e.g. RNNs and generally sequential models)

**Instance normalization**
Normalizes per-channel, per-sample.

**Group normalization**
Splits channels into groups and normalizes within each group, this is a middle ground between layer and instance norm.

The main advantage is that BatchNorm's accuracy degrades badly at small batch sizes, while GroupNorm's performance stays stable regardless of batch size.

![[Normalization layers.png]]

**1x1 convolutions**
Technically it is just a convolution with $1\times 1$ spatial extent, but its real purpose is to project the channel/depth dimension up or down (mixing information across channels) cheaply, while leaving spatial dimensions untouched.

### CNN case studies
**LeNet**
This is the historical starting point, it had a few conv/pool layers followed by fully-connected layers.
$$[\text{CONV-POOL-CONV-POOL-FC-FC}]$$

**AlexNet** ($7$ layers)
This is the network that kicked off deep learning in vision.
$$[\text{CONV1-POOL1-NORM1-CONV2-POOL2-NORM2-CONV3...5-POOL3-FC5...8}]$$

Conv1 used $11\times 11$ filters at stride $4$ whilst later conv filters are smaller with a smaller stride (conv2 is $5\times 5$ and the others are $3\times 3$).

It was split across two GPUs (each with half the feature maps), because of hardware limits (not a deliberate architectural choice).

This was the first major use of ReLU, and had heavy data augmentation.

**VGGNet** ($16-19$ layers)
VGG replaces AlexNet's large filters with a deep stack of small $3\times 3$ convolutions.

Stacking three $3\times 3$ convs gives the same effective receptive fields as one $7\times 7$ conv, but with fewer parameters and more non-linearities in between.
![[Stacked convs.png|500]]

This leads to a deeper and more expressive network for a similar or lower parameter budget.
![[AlexNet vs VGGNet.png|400]]

**GoogLeNet** ($22$ layers)
Built around a repeated _inception module_, instead of choosing one filter size, run $1\times 1$, $3\times 3$, $5\times 5$ convolutions and a pooling branch in parallel and concatenate their outputs (network withing a network, stacked repeatedly).
![[Naive inception module.png|500]]

The _naive inception module_ is computationally explosive because concatenating many large filters at full input depth blows up the channel count, layer over layer.
![[Inception module issue.png|600]]


The fix is to use a _bottleneck_ by inserting $1\times 1$ convolutions before the expensive $3\times3$/$5\times 5$ convs (and after the pooling branch) to compress the channel depth first.
>This is the practical payoff of the $1\times1$ convolution concept covered earlier.

![[Inception module with dimension reduction.png|500]]
![[Fixed inception module.png|500]]

GoogLeNet replace the final expensive fully-connected layers with _global average pooling_ (spatially averaging each feature map down to one value) before a single FC layer, this leads to a big parameter count saving.

It also includes two _auxiliary classifier branches_ through the network during training, so that early/mid layers can receive gradient from the main classification loss and the auxiliary classification loss, thus giving the network a more direct learning signal and preventing the vanishing gradient issue.
>These branches compute the prediction using the features learned up to that point.

![[GoogLeNet.png]]

**ResNet** ($152$ layers)
Simply stacking more layers on a plain CNN eventually makes training error worse, this is the _degradation problem_, and it's caused by difficulty in very deep plain networks.

The fix is to add _residual (skip) connections_ so that each block learns a residual function $F(x)$ and the block output is $F(x)+x$, letting gradients flow directly through the shortcut, thus making deeper networks trainable.
![[Residual block.png]]

For deep variants of the architecture (e.g. $152$ layers), ResNet uses _bottleneck blocks_ ($1\times1\to3\times3\to1\times1$) to keep compute manageable, using the same trick from GoogLeNet.
![[Bottleneck residual block.png|400]]

### Weight initialization
Initializing all weights to the same constant (e.g. zero) makes every neuron in a layer compute identical outputs and gradients, so the network never breaks symmetry.

**Random initialization** solves that, but naive small-random-init causes activations to shrink toward zero in deep networks, while too-large random init causes saturation.

**Xavier initialization** addresses this by scaling the initial weight variance based on the number of inputs (fan-in), keeping activation variance roughly stable layer to layer.
Xavier is derived _assuming a linear/tanh-like activation_, it's not perfectly matched to ReLU networks.

**He initialization** (an adjustment for ReLU) is the usual companion to Xavier in modern practice.

### Transfer learning
We don't actually need a lot of data to use CNNs, because we can reuse a network already trained on some dataset (e.g. ImageNet).

The standard strategy is to _freeze every layer except the last few ones_, and then train these latter layers on our own dataset, this is **transfer learning**, and the number and type of layers that we re-initialize and train depends on how the original model was trained and what are we fine-tuning it to.
![[Transfer learning.png|500]]


|             |          Similar dataset           |                                          Different dataset                                           |
| :---------: | :--------------------------------: | :--------------------------------------------------------------------------------------------------: |
| **Little data** | Use linear classifier on top layer |          Trickier, try features from earlier/more generic layers rather than the final ones          |
| **Lot of data** |       Fine-tune a few layers       | Fine-tune through most or all of the network, initialized from pretrained weights rather than random |

Pre-training + fine-tuning is the standard practice, not training from scratch.
