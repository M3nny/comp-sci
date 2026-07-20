We are interested in Computer Vision (CV) to **know what is where by looking**.

### History of computer vision
- **Hubel & Wiesel (1959)**: recorded from cat visual cortex neurons and discovered that individual neurons respond to specific oriented edges, and that cells are organized hierarchically (simple -> complex)
- **Larry Roberts (1963)**: extracted edges from photos of blocks to infer 3D structure
- **David Marr ('70s)**: _three levels of analysis_ for understanding any information-processing system:
	1. _Computational_: what problem is being solved and why
	2. _Algorithmic/representational_: what representations and processes are used
	3. _Implementational/physical_: how it's physically realized (e.g. in neurons or silicon).
- **Recognition via Parts / Generalized Cylinders (1973–79)**: modeled objects as assemblies of generic 3D primitive shapes rather than trying to model exact object geometry
- **Recognition via Edge Detection (1986-87)**: the _canny edge detector_ remains a standard algorithm, this era treated recognition as built up from detected edges/contours
- **AI Winters**: two periods (roughly following 1969 and the late 1980s/90s) when funding and enthusiasm for AI collapsed after early hype failed to deliver, partly triggered by Minsky & Papert's 1969 book showing perceptrons couldn't learn the XOR function
- **Recognition via Grouping (1990s), Normalized Cuts (1997)**: a graph-theoretic approach to image segmentation, grouping pixels via spectral clustering
- **Recognition via Matching (2000s) SIFT, David Lowe (1999)**: Scale-Invariant Feature Transform: hand-crafted local features robust to scale/rotation, used to match keypoints between images
- **Face Detection (2001)**: real-time face detection using a cascade of simple features boosted together
- **Caltech 101 (2004)**: an early benchmark image dataset
- **Histogram of Oriented Gradients**: a feature descriptor especially effective for pedestrian detection
- **PASCAL VOC (2007)**: a benchmark with competitions for classification detection (bounding boxes), segmentation (pixel-level labeling), and "person layout" (body-part boxes)
- **ImageNet (2009)**: large-scale dataset, which enabled the deep learning breakthrough a few years later
- **Deformable Part Model**: revived part-based modeling combining flexible spatial arrangements of parts with modern ML-trained features, the last major hand-engineered detector before deep learning took over
- **AlexNet (2012)**: CNN that dramatically won the ImageNet competition, marking deep learning's mainstream breakthrough in vision

#### Deep learning history in computer vision
- **Perceptron (1958)**: one of the earliest trainable learning algorithms, it's a linear classifier
- **Minsky & Papert (1969)**: their book proved perceptrons can't learn the XOR function (not linearly separable)
- **Neocognitron - Fukushima (1980)**: a direct conceptual ancestor of CNNs, though it lacked a practical training algorithm
- **Backpropagation - Rumelhart, Hinton & Williams (1985/86)**: popularized the algorithm for computing gradients through multi-layer networks, finally making it possible to train networks with hidden layers
- **LSTM - Hochreiter & Schmidhuber (1997)**: a recurrent architecture designed to learn long-range dependencies in sequential data
- **Convolutional Networks - LeCun et al. (1998)**: applied backprop to a Neocognitron-like architecture, learned to recognize handwritten digits
- **2000s "Deep Learning"**: deeper networks were explored, but the field wasn't mainstream yet and lacked large datasets, setting up AlexNet's 2012 breakthrough once ImageNet-scale data and GPU compute were available

### The modern era
Nowadays we have **vision transformers** (adapting the transformer architecture originally from NLP), **denoising diffusion processes**, **real-time 2D pose estimation**, **scene understanding** (which consists into interpreting relationships between multiple objects).
>The current frontier lies on **vision-language models**.

This evolving field also brings with itself some ethical concerns (e.g. surveilance).
### Biological inspiration
The "post 2012" philosophy is to **build features automatically from data**, learn a full **feature hierarchy** from raw pixels to classifier output, with each layer extracting features from the previous layer's output, all trained jointly end-to-end.

This takes inspiration from **biological vision** as biological analogues to mechanisms used in modern vision models (like attention mechanisms in Transformers).\\\

### What makes computer vision hard
There is an **infinite number of possible shapes**, hence there are multiple challenges when dealing with computer vision:
- **Viewpoint variation**: a shot from an unusual angle
- **Intraclass variability**: a lineup of very different dog breeds, all still "dogs"
- **Deformation**: an object may have multiple poses
- **Illumination**: an object's silhouette lit dramatically from one side
- **Background clutter**: an object nearly camouflaged against its background
- **Occlusion**: an object peeking out from under another object

Then there are **illusions** which are already hard for biological vision.
