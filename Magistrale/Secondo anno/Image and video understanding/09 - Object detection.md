A detector must output a **bounding box** $(x,y,w,h)$ per object and a **class label**.

One of the first approaches was to use **template matching + sliding window**, which consisted in sliding a fixed template over the image and score cross-correlation between template and each window, this has two major issues:
- Needs the whole object visible
- Only matches one specific instance, not a general class
- Unknown object scale makes this harder

The first widely used real-time detector was the **Viola-Jones face detector**, its feature are:
- _Integral image_: precompute a value for every pixel storing the sum of the pixel values above and to the left of the current evaluated pixel, in this way the pixel sum inside any rectangle is retrievable in $O(1)$ via $4$ corner lookups (sum is $A-B-C+D$)
![[Integral image.png|200]]
- _Haar-like features_: simple black-white rectangle patterns whose "value" is defined as the sum of white area - sum of black area, these approximate patterns like "eyes are darker than cheeks"
![[Haar-like features.png|500]]
- _AdaBoost_: selects the small subset of Haar features (out of the possible ones) that best separate faces from non-faces, combining many weak learners into one strong classifier
![[AdaBoost.png|500]]
- _Attentional cascade_: chains classifiers from cheap to expensive, rejecting obvious non-face early, this is what makes it fast at test time, this idea (cheap early rejection -> expensive late stage refinement) appears in many other two-stage detectors

**HOG (Histogram of Oriented Gradients)** computes image gradients in a dense grid of cells, which indicate the direction of greatest change of the image.
By averaging the gradient image over training samples, we get _shape information_, which let's use create a descriptor that exploits that.
![[HOG.png|500]]

The _pipeline_ to train a model of this type is:
1. Choose a training set of image that contain the object we want to detect
2. Choose a set of image that do NOT contain that object
3. Extract HOG feature on both sets
4. Train a SVM classifier on the two sets to detect whether a feature vector represents the object of interest or not

**Deformable Part Model (DPM)** was another model based on HOG, but represents an object as a root filter plus movable part filters (e.g. head, limbs), more robust to pose changes than a single rigid template.

Since sliding-window methods fire multiple overlapping detections on the sam object, **Non-maximum supression (NMS)** keeps only the highest scoring box per object and discards the rest:
- For each box $b_i$:
	- Compare it against every other box $b_j$:
		- if their overlap exceeds a threshold $\lambda_{nms}$ and $b_j$ scores higher, discard $b_j$

The overlap is measured through **Intersection over Union (IoU)**, also called Jaccard index:
$$J(A,B)=\frac{|A\cap B|}{|A\cup B|}$$
![[NMS.png|400]]

### Neural object detection
When classifying a **single object + localization**, we can use a CNN with two heads:
- _Classification head_: softmax over class scores
- _Box-regression head_: predicts $4$ numbers $(x,y,w,h)$, trained with L2 loss against ground-truth coordinates
>In this way we threat localization as a regression problem.

Training consists in:
1. Train the classification head first, freeze the layers
2. Train the regression head
3. At test time use both

![[Single object detection.png|500]]
With **multiple objects** the problem is that each image needs a different number of outputs, but standard networks have a fixed size output, so it can't just be classification + localization repeated naively.

We could **crop the image** into many overlapping windows, run each crop through a CNN classifier, but this would need a huge number of locations, scales and aspect ratios, making it computationally expensive.

We need a **generic class-agnostic** objectness measure that states how likely it is for an image region to contain an object, and then classify only those **regions of interest (RoI)**.

A few **methods to define a RoI** are:
- _Selective search_: find "blobby" image regions likely to contain objects using segmentation-style merging
- _Edge boxes_: score boxes by how many contour edges they fully enclose, boxes tightly wrapping an object's edges score higher
![[Edge boxes.png]]

### Families of object detectors
**One-stage detectors** directly extract features and then proceed the classic split classification + localization.

**Two-stage detectors** proceed by extracting the features, proposing objects and only then they proceed with classification + localization, but in this case the localization only refines the bounding box by computing $(\Delta x,\Delta y,\Delta w, \Delta h)$.

#### R-CNN
The **Region Based Convolutional Neural Network (R-CNN)** is a _two-stage detector_ that has the following pipeline:
1. Generate $\sim2$k region proposals (e.g. with selective search)
2. Warp each to $224\times224$ and run it independently through an ImageNet pretrained CNN
3. Classify each region's features with per-class SVMs
4. A separate box-regression module predicts small correction offsets $(\Delta x,\Delta y,\Delta w, \Delta h)$ to refine each proposal

![[R-CNN.png|500]]

This approach is slow, since there are $\sim2$k forward passes per image.

The **Fast R-CNN** version runs the CNN backbone once on the whole image to get a shared conv5 feature map, then crop features (not pixels) per region.
![[Fast R-CNN.png|300]]

Then it proceeds as follows:
1. **RoI pooling**: project each proposal onto the feature map, "snap" it to the nearest grid cells, then max-pool each cell, this produces a fixed-size feature vector, with the drawback of a slight spatial misalignment between the proposal and the sampled features
![[RoI pooling.png|400]]
>In green: project proposals onto features
>In blue: "snap" to grid cells

2. **RoI align**: samples feature values at regular sub-pixel points using _bilinear interpolation_, giving much more precisely aligned features 
![[RoI align.png|500]]
3. A shared per-region head then outputs class scores (linear + softmax) and box offsets (linear)

With this trick, the training time drops from 84h to 8.75h, the remaining problem is that runtime is now dominated by the external region-proposal step itself.

**Faster R-CNN** replaces the external proposal algorithm with a learned **Region Proposal Network (RPN)** that reuses the same backbone features, making the whole system trainable end-to-end and much faster.

A RPN uses **anchor boxes** which can be imagines as a fixed-size reference box centered at every location of the feature map, $K$ anchor boxes of different scales.aspect ratios are placed at each location, then a small conv head predicts, per anchor:
- A score indicating the probability of that anchor being an object
- Box-correction offsets which are a correction from the anchor to the ground-truth box
![[Anchor boxes.png|600]]


Faster R-CNN is jointly trained with 4 losses:
1. RPN classify object / not object
2. RPN regress box coordinates
3. Final classification score (object classes)
4. Final box coordinates

![[Faster R-CNN.png|400]]
**First stage** run once per image:
- Backbone network
- Region proposal network
**Second stage** run once per region:
- Crop features
- Predict object class
- Prediction bbox offset

### YOLO
**YOLO (You Only Look Once)** is a _one-stage detector_ that skips proposals entirely, its pipeline is:
1. Split image into an $S\times S$ grid
2. Each cell directly predicts, for each $B$ bounding boxes: $4$ coordinates + $1$ confidence (objectness) score, plus a set of class probabilities conditioned on "there is an object here" (e.g. $P(Car|Object)$)
3. Combine box predictions with class predictions, then apply NMS and a confidence threshold to get final detections

![[YOLO pipeline.svg|600]]

### SSD
**SSD (Single Shot MultiBox Detector)** uses a similar single-pass philosophy to YOLO but predicts boxes from _multiple feature-map scales_ (not just one grid resolution), giving better detection of small objects.

Now that we've seen both one-stage and two-stage detectors, we can list their **trade-offs**:
- _Two-stage:_ classification only runs on a small set of "interesting" foreground proposals ($\sim$ 1-2k), so background is already filtered and foreground/background class balance is manageable, the classifier can focus on information-rich regions
- _One-stage_: must densely evaluate $\sim$ 100k locations across the image, causing severe foreground/background imbalance, hard-negative mining helps but isn't sufficient on its own

### DETR
**DETR (DEtection TRansformer)** uses a convolutional backbone followed by a transformer encoder-decoder architecture.

Its **pipeline** works as follows:
1. A CNN backbone extracts 2D feature map from the image
2. Features are flattened into a sequence and combined with positional encodings, then fed into a _transformer encoder_
3. A _transformer decoder_ takes a small fixed number of learned "object queries" (positional embeddings) and cross-attends to the encoder output
4. Each decoder output embedding goes through a _shared feed-forward network_ (FFN) that predicts either (class, box) or a "no object" label, this removes the need for anchors, proposals, and NMS, since the fixed-size query set directly produces a de-duplicated detection set

![[DETR.png|400]]
>Very similar to Attention is All you need architecture, with just a few addition made to work for this particular problem.

---
### Instance segmentation
**Mask R-CNN** extends Faster R-CNN by adding a third, parallel branch to the per-region head, alongside classification and box-regression, a small FCN predicts a binary _segmentation mask_ for each detected object.

This is why RoI Align (not RoI Pooling) matters here: mask prediction needs pixel-accurate feature alignment, which the "snap to grid" of RoI Pooling would blur.

**DETR for panoptic segmentation** extends DETR by generating a binary mask in parallel for each detected object (via an added mask head), then merging all masks into a single _panoptic map_ using pixel-wise argmax (i.e. at each pixel, whichever object's mask scores highest "wins" that pixel).

### Evaluation
In order to evaluate detectors we use:
- $Precision = \frac{TP}{TP+FP}=\frac{\text{Good boxes detected}}{\text{All boxes that we detected}}$
- $Recall=\frac{TP}{TP+FN}=\frac{\text{Good boxes detected}}{\text{All ground truth boxes}}$

If IoU $>0.5$ then we have a **positive match**.

**Average precision (AP)** is the area under the precision-recall curve and the **mean Average precision (mAP)** is just AP average across all classes.

For example, let's say our method predicted $12$ boxes, where $6$ of them are true boxes present in the image, the precision-recall curve can be plotted as follows.

| Rank | True/False | Precision | Recall |
| :--: | :--------: | :-------: | :----: |
|  1   |     T      |   1.00    |  0.17  |
|  2   |     T      |   1.00    |  0.33  |
|  3   |     F      |   0.67    |  0.33  |
|  4   |     T      |   0.75    |  0.50  |
|  5   |     F      |   0.60    |  0.50  |
|  6   |     F      |   0.50    |  0.50  |
|  7   |     T      |   0.57    |  0.67  |
|  8   |     F      |   0.50    |  0.67  |
|  9   |     T      |   0.56    |  0.83  |
|  10  |     T      |   0.60    |  1.00  |
|  11  |     F      |   0.55    |  1.00  |
|  12  |     F      |   0.50    |  1.00  |

![[Precision-recall curve.png|500]]