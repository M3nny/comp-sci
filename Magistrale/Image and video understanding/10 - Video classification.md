A video is a **4D tensor** $(T\times3\times H\times W)$ which is far too large to feed into a network at full resolution/frame-rate.
A solution to this is to _train on short clips_ at low fps and low spatial resolution.

We're going to list increasingly sophisticated ways to get a CNN handle that extra time dimension.

**Single-frame classification**
Just an ordinary 2D CNN on individual frames and average the predictions, this is a simple baseline that ignores motion entirely.
![[Single-frame classification.png|500]]

**Late fusion**
Run an ordinary 2D CNN on several frames independently, then combine (average pool) the extracted features at the very end before classifying.
Motion information is barely used since fusion happens only after all spatial processing is done.
![[Late fusion.png|500]]

**Early fusion**
Stack the $T$ frames on the channel dimension right at the input, then run one 2D CNN.
This lets the very first conv layer look at pixel-level motion, but the network compresses time immediately, so it can't build up sophisticated temporal features.
![[Early fusion.png|500]]

**3D CNN**
Replace 2D convolution/pooling with 3D versions, so the kernel slides over height, width and time simultaneously, so motion is processed at every layer, not just first or last.
![[3D CNN.png|500]]

In practice a 2D conv kernel produces one output per frame independently, while a 3D conv kernel spans multiple frames at once, so its output already mixes information across time.
![[3D conv.png|500]]

### Optical flow
Given two consecutive frames, optical flow estimates the per-pixel 2D displacement vector from image $A$ to image $B$, it explicitly indicates the **perceived motion** (of pixel intensities), not necessarily the object's true 3D motion.
>A uniform rotating sphere with no texture shows no motion at all.

**Classical optical flow** (pre deep learning) was computed by hand-designed algorithms.

Given pixel at time $t$, we want to find nearby pixels of the same color at time $t+1$, **key assumptions** are:
- _Color/brightness constancy_: point at time $t$ looks same at time $t+1$
- _Small motion_: points fo not move very far

![[Optical flow.png|600]]


**FlowNet** was the first end-to-end supervised deep network for optical flow, and has two architecture variants.

**FlowNet-Simple**
Stack the two images channel-wise and feed into one CNN (mirrors the behavior of early fusion).
![[FlowNet-Simple.png|600]]

**FlowNet-Correlation**
Process each image with a separate CNN stream first, then explicitly compute a _correlation layer_ where, for each spatial location, multiply feature vectors from image $A$ against nearby locations in image $B$, producing a matching similarity score.

This gives the network an explicit mechanism for detecting where a "patch moved" rather than making it infer matching implicitly.
![[FlowNet-Correlation.png|600]]
![[FlowNet-Correlation2.png|600]]

An _upsampling module_ then produces the final dense flow field.
![[Upsampling module.png|600]]

### Modeling motion and time
**Two-Stream Networks** run two separate CNNs in parallel:
- _Spatial stream_: on raw RGB frames (appearance)
- _Temporal stream_: on pre-computed optical flow fields (motion)
![[Two-stream network.png|600]]
>These streams' predictions are then _fused_.

**Recurrent approaches to long-term structure**
Since CNNs only see a short clip, RNNs were added to model dependencies across an entire video.

_LRCN_
Run a CNN on each frame, then feed the sequence of CNN features into a RNN to aggregate information over time

_Recurrent convolutional networks_
Recalling [[03 - Sequential models#Multi-layer RNNs|Multi-layer RNNs]], we can use a similar structure to process videos, so instead of flattening CNN features before the RNN, we can use convolutional recurrent units that preserve spatial structure, keeping "where" information alongside "when".

|            Aspect            |                                Recurrent Neural Network (RNN)                                 |                                          1D Convolution (CNN)                                          |                                     Self-Attention                                      |
| :--------------------------: | :-------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------: |
|         **Works on**         |                                       Ordered sequences                                       |                                         Multidimensional grids                                         |                                     Sets of vectors                                     |
| **Long-sequence capability** | _Good_ at long sequences: after one RNN layer, hidden state ($h_T$) "sees" the whole sequence | _Bad_ at long sequences: need to stack many convolution layers for outputs to "see" the whole sequence | _Good_ at long sequences: after one self-attention layer, each output "sees" all inputs |
|     **Parallelization**      |               _Not parallelizable_: hidden states must be computed sequentially               |                       _Highly parallel_: each output can be computed in parallel                       |               _Highly parallel_: each output can be computed in parallel                |
|      **Main drawback**       |                              Sequential computation limits speed                              |                        Requires many layers to capture long-range dependencies                         |                                  Very memory intensive                                  |
| **Common video application** |                                  CNN + RNN, or recurrent CNN                                  |                                             3D convolution                                             |                        Transformer-based models (self-attention)                        |

**Non-local neural networks**
A self-attention mechanism for video is used, so instead of combining nearby pixels (as convolution does), a non-local block computes a _weighted sum over all space-time positions_ in the feature map, weighted by feature similarity.
![[Self-attention in videos.png|500]]

This lets the network directly _relate two frames far apart in time or space_.
>This is essentially the same mathematical idea as Transformer self-attention, applied to CNN feature maps.

This _nonlocal block_ can be applied into existing 3d CNN architectures and can be stacked as: 3D CNN -> nonlocal -> 3D CNN -> nonlocal-> 3D CNN -> prediction.

**I3D (Inflating 2D Networks to 3D)**
Rather than designing a 3D CNN from scratch, we can take a strong pretrained 2D CNN and _inflate_ its 2D $N\times N$ filters into 3D $N\times N\times N$ filters (by replicating weights along the new time axis).

This lets the 3D network start from powerful pretrained image features instead of training from random initialization on limited video data.
![[Inflated 2D network.svg|600]]

**Vision Transformers for Video**
This is one of the latest architectures which is a multiscale vision transformer that processes video tokens at progressively coarser resolutions (analogous to how CNNs downsample), rather than one flat token sequence like the original ViT.

### Pose estimation
Now we're dealing with "where are this object's joints", this can be very useful in the **AR** field.

**Articulated pose** is defined as localizing a set of keypoints (e.g. joints) on a deformable object.
In this case _articulated_ means the parts that can move somewhat independently, as opposed to _non-articulated_ objects whose pose is just a single rigid orientation.

The **general pipeline for pose detection** is:
1. Detect the object from the background
2. Find individual landmark locations
3. Holistically arrange landmarks into a consistent skeleton
4. Iteratively refine

![[Pose estimation.png|500]]

**Challenges** are similar to what we've already seen in other vision tasks, plus additional ones:
- Scale, lighting, occlusion, camera viewpoint
- Anatomically improbable configurations
- Associating the right keypoints to the right person
- Determining global orientation

#### Classical pose estimation
**Active Shape Models (ASM)**
Represent an object's boundary as a _set of control points_.

Across many training examples, _these points form a distribution_, then PCA finds the dominant "modes of deformation," giving a low-dimensional statistical model of plausible shapes.
![[Point model.png|500]]

_Training_ this model means iteratively moving points toward strong image edges while staying within the plausible-shape distribution.

The _weak point_ is that it only uses boundary evidence (little of the image is actually used), assumes a limited deformation model, doesn't guarantee convergence, errors compound across frames, and is highly sensitive to how it's initialized.

**Active Appearance Models (AAM)**
Same statistical/PCA framework as of the active shape model, but instead of just the boundary, it also models pixel _intensity_ (appearance) inside the shape, iteratively matching a synthesized appearance template to the image.

The _weak point_ is that it's still a rigid statistical/linear model, computationally expensive, still sensitive to initialization, and still assumes the whole object deforms holistically along shared principal components (can't handle parts moving independently).

**Deformable Parts Models (DPM)**
Abandons the holistic template in favor of independent parts connected by _"spring-like"_ constraints (a "pictorial structure" of root + parts), detected via [[09 - Object detection|HoG]] features at multiple scales.

The _weak point_ is that HoG features are hand-crafted, sensitive to viewpoint and object orientation, and don't handle occlusion, also, DPM was designed primarily for object detection, not pose per se.
![[DPM.png|600]]

**Real-Time Pose from a Single Depth Image**
Uses random forests over depth-image features for very fast per-pixel body-part classification, trained on large amounts of synthetic (rendered) training data, and was among the earliest large-scale uses of GPUs for this kind of pipeline.

We can highlight some **shared drawbacks** across all classical methods:
- Dependence on accurate initialization
- Iterative fitting with no convergence guarantee
- Poor occlusion handling
- Hand-crafted features
- Limited training data

### Deep-learning for pose estimation
**DeepPose**
This was the first DNN applied to pose estimation.

It directly regresses $(x, y)$ keypoint coordinates from a bounding-box-normalized image crop, trained with an L2 loss, using a _cascade of regressor networks_ (each stage predicts a correction/delta refining the previous stage's estimate, conceptually similar to [[06 - Ranking#Gradient boosting decision trees|boosting]]).

Its big contribution was showing that a _CNN can reason about the whole pose holistically_, even predicting occluded joints without any explicit geometric model.
![[DeepPose.png|600]]

A particular _downnote_ is that predicting a single exact $(x, y)$ point is arguably the wrong target, real keypoint locations have inherent annotation uncertainty, so a network is being asked to be over-precise about something that's genuinely ambiguous, _it would be better to predict a distribution_.

**Efficient Localization with CNNs**
Replaces direct coordinate regression with _heatmap prediction_.

The network outputs a 2D probability map per joint instead of a single coordinate, which _naturally represents uncertainty_ and is trained with a simple pixel-space MSE loss against a synthetic Gaussian "bump" at the true joint location.

Uses a coarse network followed by a fine-refinement network reusing coarse features, and _the whole pipeline is differentiable_, so it can be trained end-to-end.

>[!Info]
>Even this approach doesn't explicitly model the relationships/constraints between joints (e.g. that a wrist is connected to an elbow), each heatmap is still predicted somewhat independently.

#### Multi-persone pose estimation
So far we discusses about single-person pose estimation, for **multi-person pose** there are two main strategies: 
- **Top-down:** first detect/crop each person, then run single-person pose estimation on each crop
![[Top-down pose.png|600]]

- **Bottom-up:** detect all keypoints in the image at once, then solve the harder problem of associating keypoints to the correct individual person
![[Bottom-up pose.png|600]]

**Part Affinity Fields** is a _bottom-up_ method that has the network predict two things simultaneously:
1. _Per-joint heatmaps_ (as before)
2. _Part Affinity Fields_: vector fields encoding both the connection and direction between pairs of joints (e.g. elbow→wrist)

Because _both are predicted together_ in one forward pass through a multi-stage CNN, and a lightweight refinement/matching step resolves ambiguous associations, this allows multi-person pose estimation for an _arbitrary number of people in a single fast run_, without the need for a per-person cropping.
>Loss is a simple MSE across both the heatmap and affinity-field outputs.

