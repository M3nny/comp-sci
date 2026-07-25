We're going to see four ideas for combining self-attention with vision, ending with the Vision Transformer (ViT).

### Add attention to existing CNNs
Take a standard CNN backbone and insert self-attention blocks between existing convolutional stages, rather than replacing convolution entirely.
![[Self-attention in CNN.png|500]]

Non-local blocks let a feature map at one spatial location attend to features at any other location in the image, **giving the network long-range dependencies** that convolution's local receptive field can't easily capture.

The model is still fundamentally a CNN, the attention i just a bolt-on module.

### Replace convolution with local attention
Instead of a convolution kernel doing a fixed inner product with its receptive field, use attention to compute the output.
![[Local attention.png|500]]

- **Query**: the center pixel of the receptive field is mapped to a query vector (dimension $D_Q$)
- **Key/Value**: every pixel within the receptive field (an $R\times R$ neighborhood) is mapped to a key and a value
- **Output**: computed via standard attention $softmax(QK^T)V$ instead of a fixed convolution kernel, so the "kernel weights" become data-dependent rather than fixed/learned-but-static

There are a lot of tricky implementation details, and empirically only marginally better than plain ResNets.

### Standard transformer directly on pixels
Treat an image as literally a sequence of pixel values (flatten $H\times W\times 3$ into a 1D sequence) and feed it straight into a vanilla transformer.
![[Transformer on pixels.png|500]]

Self-attention computes an $N\times N$ attention matrix, where $N$ is the sequence length, for an image $N=R^2$ (one token per pixel), so the attention matrix has $R^4$ elements, this is a **huge problem for memory occupancy**.

### Standard transformer on patches
Instead of one token per pixel, **chop the image into a grid of patches** (e.g. a photo split into a $3\times3$ grid of image crops) and treat each **patch** as one token.

This shrinks the sequence length from $R^2$ pixels to a much smaller number of patches, making the memory problem tractable, this directly leads to _vision transformers_.

---
### Vision transformers
A vision transformer converts image patches into inputs.
![[Vision transformer.svg]]

- **Patchify**: split the image into $N$ patches, each shaped $3\times16\times16$
- **Linear projection**: each flattened patch is projected to a $D$-dimensional embedding vector
- **Position embeddings**: a learned $D$-dimensional vector is added per position (since attention itself has no notion of order/location)
- **Classification token**: an extra learnable $D$-dim "CLS" token is added to the sequence (this trick is borrowed directly from [[12 - Transformers#BERT|BERT]]), it doesn't correspond to any image patch, it's just a slot the model learns to aggregate global information into
- **Transformer encoder**: a vanilla transformer
- **Classification head**: only the output corresponding to the CLS token is taken, linearly projected to $C$ class scores

Even tough ViT are advertised as **"convolution free", this isn't totally true**:
- The patch-extraction + linear projection step is mathematically identical to a single Conv2D layer with kernel size $p\times p$, stride $p$, mapping $3\to D$ channels
- The MLP blocks inside each transformer layer are applied identically and independently to each token, this is mathematically equivalent to a stack of $1\times 1$ convolutions

The accurate claim is: _ViT has no large-kernel, strided convolutions with spatial mixing beyond the initial patch split_, the actual "seeing across space" all happens through self-attention, not convolution.

### ViT results and data scaling
ViT's <u>performance advantage over CNNs only emerges at large pretraining data scale</u>.

With little data, its lack of built-in visual assumptions hurts it.
With enough data, it's able to learn better representations than CNN's baked-in assumptions allow, and do so more cheaply per unit of compute.

### Inductive bias
ViTs have much **less image-specific inductive bias than CNNs**.
In CNNs, locality and two-dimensional neighborhood structure are _baked into each layer throughout the whole model_.

In ViT, **only MLP layers are local**, while the **self-attention layers are global**.
The **two-dimensional neighborhood structure** is used very sparingly:
- _In the beginning of the model_ by cutting the image into patches
- _At fine-tuning time_ for adjusting the position embeddings for images of different resolution

Other than that, the **position embeddings** at initialization time **carry no information about the 2D positions of the patches** and all spatial relations between the patches have to be learned from scratch.

In practice, **a CNN is handed strong assumptions for free**, that is "nearby pixels are related", and "the same pattern can appear anywhere in the image" are baked into the conv operation itself.

**ViT has to learn spatial relationships purely from data**, that's why it needs so much pretraining to be competitive, and why it can eventually surpass CNNs once it has enough data to learn better relationships than the hand-coded con assumptions.