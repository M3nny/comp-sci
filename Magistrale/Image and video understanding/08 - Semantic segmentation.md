Other than [[07 - Image classification|image classification]] other vision related tasks we have:
- **Semantic segmentation**: a label per pixel, but no notion of individual object instances
- **Object detection**: bounding boxes around individual instances, with labels
- **Instance segmentation**: pixel-level masks and instance separation

In _semantic segmentation_, training data consists of images paired with a dense label map (each pixel labeled with a category), and at test time, the network must output a same-resolution map of predicted classes for a new image.

### Sliding window
The first idea to semantic classification is to use a **sliding window**.
Take a **small patch around each pixel**, run it through a CNN and classify the _center pixel_ using that patch as context.

This has two major issues:
- **No global context**: a small patch alone can be ambiguous to classify
- **Extremely inefficient**: neighboring patches overlap heavily, and this approach recomputes convolutional features from scratch for each patch instead of reusing shared computation

### Fully convolutional
Instead of patches, we could run the whole image through a **stack of conv layers** (no pooling/striding) and predict all pixels at once via a final `argmax` over per-pixel class scores.

This solves the context problem but introduces a new one: _keeping every layer at full resolution_ is computationally expensive.
![[Semantic vanilla CNN.png]]

The practical compromise is to **downsample** spatial resolution in an "encoder" (via pooling/strided convolutions) to build up context and receptive field cheaply, then expand it back to full resolution in a "decoder" via **upsampling**.
>This pattern is widely used.

![[Downsample-upsample.png]]

The loss is typically per-pixel cross-entropy.

### Upsampling techniques
Downsampling is just a strided convolution and pooling layers, but how can we upsample?

There are various techniques, from the roughly non-learnable to the most learnable we have:
- **nearest neighbor unpooling**: each value is simply copied into a small block (e.g. $2\times 2$) in the output
- **Bed of nails**: each value is placed in one corner of its output block, with zeros elsewhere
![[Upsample1.png]]
- **Bilinear interpolation**: uses the two nearest points in $x$ and $y$ to build a linear approximation between the known values
![[Upsample2.png|400]]
- **Bicubic interpolation**: uses three nearest points to fit a cubic approximation (this is how images are normally resized)
![[Upsample3.png|400]]
- **Max unpooling**: pairs a downsampling (max pooling) layer with a corresponding upsampling layer later in the network, it remembers which position held the max value during pooling, and places the incoming value back at that exact position (zeros elsewhere), this preserves some spatial precision lost by pooling
![[Upsample4.png]]
- **Transposed convolution (deconvolution)**: this is the only learnable upsampling method

#### Transposed convolution
We recall that a stride-2 convolution takes $2$ input pizels worth of movement for every 1 output pixel, thus creating a resolution-reducing operation.
![[Learnable downsampling.png|500]]

**Transposed convolution** flips this ratio: the filter moves 2 pixels in the output for every 1 pixel step in the input.
Each input scales a copy of the filter, which gets pasted into the output at the appropriate location, and where these pasted copies overlap, values are summed.
![[Learnable upsampling.png|500]]

Concretely ($2\times 2$ input, $3\times3$ kernel, stride $2$): input value `a` weights the whole filter and writes it into one output region, input value `b` does the same into an overlapping region, wherever contributions overlap, they are added together.

The name _transposed convolution_ comes from linear algebra, where an ordinary convolution can be written as multiplying  a signal vector by a sparse matrix built from the filter $X$, and a transposed convolution multiplies by that same matrix's transpose $X^T$.

Follows a 1D transposed convolution:
![[Transposed 1D convolution.png|600]]

### Encoder-decoder fully convolutional networks
Classic classification CNNs (with fully-connected layers at the top) are _converted into fully convolutional nets_ by turning the FC layers into $1\times1$ convolutions, this lets a network trained for whole-image classification instead output a **spatial heatmap**.

**Naively upsampling** directly from the last, coarsest feature map ($32\times$ upsampling) _loses a lot of detail_.
The fix is **skip connections** from earlier, higher resolution layers, fused with the upsampled coarse prediction, in fact FCN-16 adds in `pool4` features, and FCN-8 further adds `pool3` features, each requiring progressively less upsampling and preserving finer detail.

**Training** is done **hierarchically**: first train using only the coarsest/high-level features, then fine-tune incorporating mid and low-level features.
![[Fully-conv network.png|600]]

### SegNet
This is an encoder-decoder architecture where:
- **Encoder**: standard conv + pooling
- **Decoder**: upsampling + trainable conv filter

The _upsampling_ step reuses the max-pooling indices recorded in the corresponding encoder layer (i.e. it uses the max-unpooling technique, and then refines with learnable convolutions).
![[SegNet.png]]

This is in contrast with a FCN decoder, since SegNet upsamples without learning (via indices) and then convolves with a trainable filter, whereas FCN learns the deconvolution itself and adds encoder feature maps directly, with no trainable decoder filters.

### U-Net
Originally designed for biomedical image segmentation, U-Net **generalizes the skip-connection** idea:
- **Contraction (encoder)**: each stage halves spatial resolution while doubling the number of feature channels
- **Expansion (decoder)**: each stage doubles resolution (via transposed convolution), while halving the channels

Skip connectors **concatenate** ("copy and crop") corresponding encoder feature maps directly into the decoder at each solution level, passing low-level spatial detail forward alongside high-level semantic information reconstructed at the top.
>This is called _symmetric encoder-decoder with concatenated skip connections_.

![[Symmetric encoder-decoder.png]]

### Transformer-based segmentation
**SETR (SEgmentation TRansformer)** motivates itself by naming two limitation of all the FCN-style approaches seen before:
- CNNs struggle to capture very_ long-range dependencies_
- The _maximum context_ any single neuron can use is capped by its receptive field

This type of architecture splits the image into patches, linearly projected + positional embedding, and passed through $24$ standard [[05 - Vision transformers|vision transformers]] layers, this gives every patch access to every other patch's information from the very first layer (i.e. global receptive field immediately).

### Datasets
Models are often pre-trained in the large [MS-COCO](https://cocodataset.org/#home) dataset, the nfine-tuned to the specific dataset.

**Evaluation metrics** include:
- _IoU_: for a given class $\frac{\text{Area of overlap}}{\text{Area of Union}}$ between predicted an ground-truth masks
- _mIoU_ (mean IoU): computes IoU per class, then average across all classes
- _Pixel accuracy_: the fraction of all pixels classified correctly

