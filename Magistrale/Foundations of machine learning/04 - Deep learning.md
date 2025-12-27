After seeing the origins of machine learning methods, in this chapter we are going to explore the current most used methods: deep neural networks.

Deep learning systems benefit dramatically from large datasets, in fact, **performance improves with more data**.

Despite the idea of deep networks is quite old, it is successful now because:
- We have more data
- We have more computing power
- There are new ideas and techniques

The fundamental philosophy is to **learn a feature hierarchy**.

### Biology inspiration
Biological vision is hierarchically organized, it is possible to compare the inferotemporal cortex to how convolutional neural networks work in an abstract way.

![[Hierarchy of visual areas.png|400]]


|        CNN         |      Example      |    Visual Nervous System     |
| :----------------: | :---------------: | :--------------------------: |
|    Input image     |   Forest image    |    Photo-receptors retina    |
| Primitive features |  Oriented edges   | V1: simple and complex cells |
|    Object parts    | Bark, leaves, etc |    V4: different textures    |
|       Object       |       Trees       |    Inferotemporal cortex     |

As regard **receptive fields**, they represent the region of visual space where light stimuli evoke neuronal responses.

We also have a progression of cell types as follows:
- **Simple cells**: respond strongly to lines or edges at specific orientations
- **Complex cells**: respond to oriented features but with spatial invariance
- **Hypercomplex cells**: exhibit end-stopping behavior, allowing to move beyond edge detection and toward recognizing complex shapes

The key takeaway is that the visual system operates as a hierarchy of feature detectors, with increasing complexity at each level.

#### Neocognitron
The neocognitron, introduced in the 1980, was a neural network architecture inspired by biological vision for pattern recognition unaffected by shift in position.

---
### Convolution layer
The **convolution layer** in neural networks can be seen as a sliding filter (kernel) across an image, which is used to produce feature maps.

Between the hyperparameters of the convolution layer, we have:
- **Stride**: how many steps the filter moves at each position (by default is $1$)
- **Padding**: adding zeros around the input to maintain dimensional consistency between input and output
![[Stride and padding.png|400]]
>Stride and padding can be used to adjust the dimensionality of the data.

![[Image channels.png|400]]
Images are often in the RGB format, to encode the information of the **three color channels** we use one feature map per channel.

In the preprocessing phase various filters may be applied based on the task of the model, such as **mean/Gaussian** filters, used for smoothing the image edges.

**Learned features** are proved to be far more effective than the traditional computer vision hand-crafted features.

#### Convolutional neural networks architecture
Instead of having **fully-connected** layers, connecting every input to every output, it is preferable to use **locally-connected** layers with small receptive fields in order to reduce the number of trainable parameters.

So, instead of learning a separate set of weights for every pixel location (as in fully-connected layers), a CNN learns one filter (as seen in the previous paragraph) and slides it across the image, this is called **weight sharing**.

Weight sharing works under the assumption that, if one feature is useful to compute at some spatial position, then it should also be useful to compute at a different position.
>Multiple filters are learned automatically during training, each detecting different features.

![[Maxpool.png|400]]
**Max pooling** is a _downsampling_ operation that reduces the number of neurons resulting from filtering operations.
It works by creating a feature map that retains only the highest values in a certain area.

![[AlexNet.png|500]]
In 2012 **AlexNet** won the ImageNet challenge by creating a CNN with $8$ layers, applying convolutions in the first $6$ layers, and having $2$ fully connected layers at the end.

---
### Training techniques
In this section we are going to mention some well known methods used in machine learning.

- **Softmax**
	Layer used to convert output values into probabilities that sum $1$.
- **ReLU(Rectified Linear Unit)**
	Activation function that addresses the vanishing gradient problem of sigmoid activations.
	Sigmoids squash values between $(0,1)$, causing gradients to vanish when backpropagated to early layers, thus slowing learning, ReLU function which is defined as $f(x)=\max(0,x)$ does not have this problem.
- **Mini-batch stochastic gradient descent**
	Instead of updating the weight only after seeing the whole training set, the weights are updated after seeing only a batch of samples of the training set.
- **Dropout**
	Randomly sets some neurons of a specified layer to zero with a certain probability.
	Neurons which are dropped out do not contribute to the forward and backward pass, hence reducing complex co-adaptations of neurons, since a neuron cannot rely on the presence of a particular other neuron.   

The easiest and most common method to reduce overfitting on image data is to artificially enlarge the dataset using label-preserving transformations.
AlexNet uses two forms of this **data augmentation**:
- Image translations and horizontal reflections
- Altering the RGB channel intensities

A well trained CNN is an excellent **feature extractor**, in fact, we can "chop" the network at a desired layer and use the output as a feature representation to train another model on some other dataset.
>We can also take a pre-trained CNN and re-train it on a different dataset.

---
### Recurrent neural networks
Recurrent neural networks are used for sequential data processing, and unlinke feedforward neural networksm RNNs have:
- A hidden state that persists across time steps
- The ability to process variable length sequences
- Memory of previous inputs

![[Recurrent neural networks.png]]


| Type of network |                             Task                             |
| :-------------: | :----------------------------------------------------------: |
|   One to one    |                    Vanilla neural network                    |
|   One to many   |        Image captioning (image -> sequence of words)         |
|   Many to one   |  Sentiment classification (sequence of words -> sentiment)   |
|  Many to many   | Machine translation (sequence of words -> sequence of words) |
|  Many to many   |             Video classification on frame level              |

The algorithm used to learn is called **back-propagation through time (BPTT)**, and it unfolds the RNN through time and computes gradients.
![[BPTT.png|500]]
**Truncated BPTT** is a practical approximation that only backpropagates for a fixed number of time steps.

>[!Info] Combining CNN and RNN
>It is possible to combine CNNs and RNNs in order to generate image captions.
>The architecture uses a CNN to encode the image, then feeds this representation to an RNN that generates a sentence word by word.

