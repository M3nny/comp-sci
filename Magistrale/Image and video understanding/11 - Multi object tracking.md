**Object tracking** consists in _following the identity of one or more objects_ across a video sequence (not just detecting them frame by frame).

It _builds on object detection_ but adds the temporal dimension, so that we must know that "object $A$ in frame 1" is the same object as "object $A$ in frame 2," even as it moves, changes appearance, gets occluded, or overlaps with others.

In brief, object tracking is:
- Detection
- Trajectory estimation (where has it been, where is it going)

### Single target tracking
We now list three representative deep learning approaches, each solving "given an object in frame 1, find it in frame 2".

**GOTURN**
Takes a _cropped search region_ from the current frame and the _target's appearance from the previous frame_, runs both through parallel convolutional branches, concatenates the features, and passes them through FC layers that directly _regress the bounding box coordinates_ of the new location.

![[GOTURN.png|500]]

This was one of the first trackers to treat tracking as pure regression rather than classification/search, making it _extremely fast_ (100 FPS), but it _doesn't handle re-detection well after full occlusion_ since it only looks locally around the previous position.

**Cycle consistency**
A self-supervised idea that _track a patch forward in time then backward_, then if it does not end up where it started, that's an error signal, so no manual labels are needed.
>This is a way to learn correspondence/tracking features without costly tracking annotations.

![[Cycle consistency.png|600]]

**Recurrent YOLO (ROLO)**
Combines YOLO detections with an LSTM that carries a hidden state across frames, letting the tracker use temporal memory rather than only the previous frame.
![[ROLO.png|500]]

### Multiple object tracking
The main **multiple object tracking (MOT)** challenges are:
- Occlusions
- Similar-looking objects
- Varying object crowding
- Camera motion
- Objects entering/leaving the scene (initialization and termination)

The **tracking-by-detection** paradigm (dominant MOT framework) runs first an object detector on every frame independently, then solve a _data association_ problem, that is: link detections across frames into consistent trajectories.
>This decouples "where are objects" from "which detection belongs to which identity".

There two types of tracking:
- **Online tracking**: decisions made causally, frame-by-frame, using only past and current information, this is necessary for real-time applications (robotics, autonomous driving)
- **Offline tracking**: the whole video is available at once, so association can be solved globally (as an optimization problem), giving better accuracy at the cost of latency

The **online tracking pipeline** works as follows:
1. Detect objects
2. Predict where existing tracks should be (motion model, e.g. [Kalman filter](https://en.wikipedia.org/wiki/Kalman_filter))
3. Compute a cost between predicted tracks and new detections
4. Solve an assignment problem (_bipartite matching_) to match tracks to detection (e.g. [Hungarian algorithm](https://en.wikipedia.org/wiki/Hungarian_algorithm))
	- Define distances between boxes (e.g. IoU)
	- Solve the unique matching (e.g. with Hungarian algorithm)
	- Solutions are the unique assignments that minimize the total cost
5. Update matched tracks (start new tracks for unmatched detections, and terminate tracks with no matches)

The solutions to point (4.) also called **bipartite-matching** are given by the unique assignments that minimize the total cost.
![[Hungarian algorithm.png|300]]

**Tracktor**
A minimalist but influential approach that reuses an _object detector's regression head_ itself as the tracker: take a track's box from frame $t$, feed it into the detector at frame $t+1$ as a region proposal, and let the detector's bounding-box regression "push" it to the new object location.
>No separate motion model or appearance network is trained.
![[Tracktor.png|500]]
- _Pros_: simple, no MOT-specific training data needed, strong baseline performance
- _Cons_: fails under fast motion (regression can't jump far), struggles with re-identifying objects after occlusion (no long-term appearance memory), and needs a re-identification (ReID) module bolted on to recover from track loss

### Deep similarity learning
Since Tracktor and similar methods struggle with re-identification, we are now going to see how to learn **embeddings** where the same object (even in different frames/poses) maps to nearby points, and different objects map far apart.
>This is the basis of appearance-based ReID.

- **Similarity learning**: learn a function that measure how similar two objects are
- **Deep metric learning**: learn a distance function over objects
>Low similarity score leads to large distance.

Given two objects $A$, $B$ and a threshold $\tau$, if $d(A,B)>\tau$ then $A\neq B$.

**ReID** works by having a database (gallery) from which we compute the distance between a query image and database images, then retrieve the $k$-nearest neighbors.

In order to _learn similarity_, **DeepFace** introduced the **siamese network** which is composed by two identical branches (shared weights) that each embed an image, trained so that embeddings of the same identity are close together.
>Originally developed for face verification, now also used for ReID in tracking.

![[Siamese network.png|500]]
Practically speaking, we use the same network to obtain an _encoding of the images_, $f(A)$ and $f(B)$ respectively, then we have to compare these encodings.

We can do this by using a distance function:
$$f(A,B)=||f(A)-f(B)||^2$$
Then **training** consists in learning the parameter such that:
- _Positive pair_: $A$ and $B$ depict the same person, $d(A,B)$ is small
$$\mathcal L(A,B)=||f(A)-f(B)||^2$$
- _Negative pair_: $A$ and $B$ depict a different person, $d(A,B)$ is large
$$\mathcal L(A,B)=\max(0,\underbrace{m^2}_\text{margin}-||f(A)-f(B)||^2)$$
Combining these two losses, we get the **contrastive loss**, which expects pairs of images with a binary label ($y^*=1$ positive pair, $y^*=0$ negative pair), pulling positive pairs together and pushing negative pairs apart by some _margin_:
$$\mathcal L(A,B)=\underbrace{y^*}_\text{Positive pair}||f(A)-f(B)||^2+\underbrace{(1-y^*)}_\text{Negative pair}\max(0,m^2-||f(A)-f(B)||^2)$$

Another loss function that can be used for this task is **triplet loss** which trains on triplets (anchor, positive, negative) simultaneously, optimizing so the anchor is closer to the positive than to the negative by a margin.
>Generally considered more effective than pairwise contrastive loss because it directly optimizes relative distances.

![[Triplet loss.png|500]]

### MOT with graphs
We can reframe MOT as **graph learning** using a [[06 - Graph neural networks#Message passing GNN|message passing CNN]].

Given a _graph_ $G=(V,E)$, its _initial embeddings_ $h_{(i,j)}^{(0)},(i,j)\in E$, $h_i^{(0)},in\in E$ and _node embeddings_ after $l$ steps: $h_i^{(l)},i\in V$.
The **goal** is to encode contextual graph information in node embeddings by iteratively combining neighboring nodes' features.
![[Graph learning.png]]
At every iteration, every node receives features from its neighboring nodes.
These features are then aggregated with an **order invariant operation** and combined with the current features with a learnable function.

This (classic message passing) is suited for learning **node embeddings**, but if we wanted to focus also on **edge embeddings** we would use a more general framework, by using **two update rules**:

_Node-to-edge_: update each edge's embedding using its two connected nodes
$$h_{(i,j)}^{(l)} = \mathcal{N}_e \left( \left[ h_i^{(l-1)}, h_{(i,j)}^{(l-1)}, h_j^{(l-1)} \right] \right)$$
- $\mathcal{N}_e$: learnable function (e.g. MLP) with shared weights across the entire graph
- $h_i^{(l-1)}$: embedding of node $i$ in the previous message passing step
- $h_{(i,j)}^{(l-1)}$: embedding of edge $(i,j)$ in the previous message passing step
- $h_j^{(l-1)}$: embedding of node $j$ in the previous message passing step

_Edge-to-node_: update each node's embedding by aggregating over its incident edges
After a round of edge updates, each edge embedding contains information about its pair of incident nodes, then edge embeddings are used to update nodes
$$m_i^{(l)} = \Phi \left( \left\{ h_{(i,j)}^{(l)} \right\}_{j \in N_i} \right)\qquad h_i^{(l)} = \mathcal{N}_v \left( \left[ m_i^{(l)}, h_i^{(l-1)} \right] \right)$$
- $\Phi$: order invariant operation (e.g. sum)
- $N_i$: neighbors of node $i$
- $\mathcal{N}_v$: learnable function (e.g. MLP) with shared weights across the entire graph

![[MOT two update rules.png|600]]
>[!Tip]
>The aggregation provides each node embedding with contextual information about its neighbors.

The **main goal** is obtaining node and edge embedding that contain context information encoding graph topology and neighbor's feature information.
After repeating the node and edge updates for $l$ steps, each node (resp. edge) embedding contains information about all nodes (resp. edge) at distance $l$ (resp. $l-1$).
>We can think of iterations as layers in a CNN.

This matters for tracking because in MOT, the natural graph is **detections as nodes** and **potential associations as edges**, so we specifically want the _edges_ (not just nodes) to carry rich, learned information about "should these two detections be linked?".

**MOT with MPN** consists in:
1. Building a graph over all detections in a time window
2. Encode node features (appearance) and edge features (e.g. spatial/temporal distance)
3. Run several rounds of message passing to refine edge embeddings
4. Classify each edge as "same identity" or "different identity"

![[MOT with MPN.png|800]]

This directly solves data association end-to-end with a learned graph neural network rather than hand-crafted affinity + Hungarian matching.

### The SUSHI approach
**Short-term association** (e.g. Tracktor/frame-to-frame) is good at handling nearby frames but drifts over long occlusions, and **long-term association** (e.g. MPN over a whole clip) handles occlusions well but is computationally expensive to run over long videos.

**SUSHI (Strong and Unified Scalable HIerarchical)** object tracker builds a _hierarchy of tracking graphs_.

It _solves short-term association first_ (local, cheap), then merges resulting short tracklets into a coarser graph and _solve association again at a longer time-scale_, repeating hierarchically.

This _gets long-term robustness_ without the full cost of one giant graph, and it's trained as a single _unified model_ rather than separate short/long-term modules (unlike earlier "hybrid multi-level trackers").
![[Sushi1.png|500]]
![[Sushi2.png|500]]

### Evaluation criterias
For each frame we can compute a set of **measures**:
- Perform matching between predictions and ground truth
- False Positives
- False Negatives
- IDsw: identity switches

At each frame, the tracker's predicted trajectories are matched to ground-truth (GT) trajectories (using the same bipartite matching).
An **ID switch** is counted whenever a _ground-truth track that was previously matched to one predicted ID gets matched to a different predicted ID_ in a later frame.

The overall **MOTA (Multi-object tracking accuracy)** is defined as:
$$\text{MOTA}=1-\frac{\sum_t(FN_t+FP_t+IDSW_t)}{\sum_tGT_t}$$
