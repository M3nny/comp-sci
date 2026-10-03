Graphs are used as the natural data structure for relationships between entities, and are pervasive across many fields.

This topic in machine learning is also referred to as **geometric deep learning**.

### Graphs recap
$V$ is the set of **nodes**, and $E\subseteq V\times V$ is the set of **edges**.

We've already seen various [[Tipologie|graph types]], here we also mention _multigraphs_ (multiple edges between the same pair of nodes) and _hypergraphs_ (an edge that connects more than $2$ nodes, thus grouping them around a shape like a circle).

Graphs can be **weighted** so that $w(i,j)=e_{ij}\to\mathbb R$.
Nodes and/or edges can be **attributed** so that $f...\in\mathbb R^d$ or $f^e...\in\mathbb R^{d_e}$.

A graph can be **represented** as:
- _Adjacency matrix $A$_: $n\times n$, an entry is $1$ if an edge exists
- _Degree matrix $D$_: diagonal matrix of each node's degree
- _Graph Laplacian_: $L=D-A$, mainly used for spectral graph theory, its eigenvectors underlie [[05 - Clustering#Normalized cut|spectral clustering]]

### Theoretical foundations
Graphs are **harder** than images, since images have a fixed number of neighbors with a fixed well-defined order, whilst graph neighborhoods have a variable number of neighbors with _no natural ordering_.

CNNs exploit two main properties: **locality** (nearby pixels relate more strongly than distant ones) and **translation invariance** (a pattern means the same thing regardless of where it appears, i.e. weight sharing), but on graphs _translation doesn't make sense_.

Let's start by _assuming we only have a set of nodes_ with no edges:
- **Stack node features into a matrix** $X$ ($n\times k$, where $x_i\in\mathbb R^k$ represents the features of node $i$, doing this imposes a node ordering that shouldn't matter to the model
- A **permutation matrix** $P$ reorders rows of $X$ (there are $n!$ possible permutations)
- **Permutation invariance**: $f(PX)=f(X)$ for any permutation $P$, so that the output doesn't depend on node order

One very generic form is the _deep sets_ model:
$$f(X)=\phi\left(\sum_i\psi(x_i)\right)$$
where we transform each node independently with $\psi$, then aggregate with a permutation-invariant pooling op (e.g. sum/max/min/avg) and then apply $\phi$.

**Permutation equivariance**: $f(PX)=Pf(X)$, needed when we want per-node outputs (e.g. node classification), since a fully invariant aggregator would destroy node identity


The **general blueprint** for _learning on sets_ is to apply a shared function $\psi$ to each node independently to get a latent $h_i$ stack into $H$ (equivariant), then optionally follow with a permutation-invariant aggregator $\oplus$ (e.g. sum/avg/max) for a set-level summary.
>This shared per-node transform + invariant pooling pattern is the template that every GNN architecture uses.

Let's _bring back the edges_:
- Now $E\subseteq V\times V$ is represented by an adjacency matrix $A$
- Permuting nodes now also permutes the edges: $A\to PAP^T$ (both rows and columns)

|                  | Sets          | Graphs                |
| ---------------- | ------------- | --------------------- |
| **Invariance**   | $f(PX)=f(X)$  | $f(PX,PAP^T)=f(X,A)$  |
| **Equivariance** | $f(PX)=Pf(X)$ | $f(PX,PAP^T)=Pf(X,A)$ |

We define $N_i$ as the **neighborhood** (set of nodes connected nodes to $i$) and also include $i\in N_i$ via a self-loop.
Accordingly, we can extract the _multiset of features in the neighborhood$X_{N_i}$_.

Now we can construct **permutation equivariant functions** $f(A,A)$, by appropriately applying the local function $g$ over all neighborhoods:
$$f(X,A)=\begin{bmatrix}\dotsi\space g(x_1,X_{N_1})\space\dotsi\\\dotsi\space g(x_2,X_{N_2})\space\dotsi\\\vdots\\\dotsi\space g(x_n,X_{N_n})\space\dotsi\end{bmatrix}$$
$g$ must itself be permutation-invariant over the neighbor set.

Visualized concretely, for node $b$, the function $g$ takes $b$'s own features and its neighbors' features $X_{N_b}$ and produces $b$'s new latent representation $h_b$.
![[Permutation equivariant function.png|600]]

>[!Tip] GNN layer
>This single idea, a shared permutation-invariant local function applied identically at every node, is what a **GNN layer** means, and every architecture covered later is just a different concrete choice of $g$.

GNNs can be used for:
- **Node-classification**
- **Edge-level predictions**
- **Graph-level predictions**
![[GNN tasks.png|600]]

Inside of a **GNN layer** there is:
- $f$: the GNN layer (equivariant function over the whole path)
- $g$: local, per neighborhood function

Almost every GNN layer falls into one of **three spatial flavors**, in increasing order of expressive power (and computational cost):
![[GNN layer flavors.png|700]]

### Convolutional GNN
The general form of a convolutional GNN is:
$$g(x_i,X_{N_i})=\phi\left(x_i,\bigoplus_{j\in N_i}c_{ij}\psi(x_j)\right)$$
- $\psi$: function applied independently to each neighbor's features
- $c_{ij}$: fixed importance coefficient (usually derived from $A$, not learned per-pair, typically the similarity)
- $\bigoplus$: aggregation (sum) over the neighborhood
- $\phi$: nonlinearity combining a node's own embedding with the aggregated neighbor embedding

Because weights are fixed rather than learned per-edge, these are cheap and scale well, and work best on **homophilous** graphs (where connected nodes tend to share labels/properties).

We then define:
- **Inputs**: node feature matrix $X$ ($N\times D$) and adjacency matrix $A$
- **Output**: node-level $Z$ ($N\times F$)
- **Next layer**: $H^{(l+1)}=f(H^{l},A)$, with $H^{(0)}=0$ and $H^{(L)}=Z$

- **Naive propagation rule**: $H^{(l+1)}=\sigma(AH^{(l)}W^{(l)})$
	- $AH$: sums each node's neighbors' embeddings ($A:n\times n$, $H:n\times d$)
	- $(AH)W$: transforms the aggregated embedding via learnable $W$ ($d\times k$)
	- $\sigma$: nonlinear activation

There are **two limitations**:
- Since $A$ has a _zero diagonal_, a node's own previous features are dropped from the aggregation, the fix is to _add self-loops_, so that $\hat A=A+I$
- $A$ is _unnormalized_, so multiplying by it rescales features by node degree (high-degree nodes blow up in magnitude), the fix is to _use a normalized version_


By combining these two fixes, we get the final GCN layer:
$$H^{(l+1)}=\sigma(\hat D^{-\frac{1}{2}}\hat A\hat D^{-\frac{1}{2}}H^{(l)}W^{(l)})$$
where $\hat A=A+I$ and $\hat D$ is the degree matrix of $\hat A$, and $\hat D^{-\frac{1}{2}}\hat A\hat D^{-\frac{1}{2}}$ normalizes $\hat A$.
![[GNN node classification.png|500]]
**Semi-supervised node classification** works by aggregating features from each neighborhood, then they are passed through a nonlinearity, and this is repeated across layers, after $t$ layers, each node's representation reflects information from up to $t$ hops away.
The cross-entropy loss is applied _only on the labeled subset of nodes_ (this is the "semi-supervised" part), most of the nodes are unlabeled, but they still contribute to feature propagation.

An MLP ignoring the graph structure performs far worse than GCN, thus showing that the _pairwise relational information genuinely helps_.

### Attentional GNN
The general form of an attentional GNN is:
$$g(x_i,X_{N_i})=\phi\left(x_i,\bigoplus_{j\in N_i}\alpha(x_i,x_j)\psi(x_j)\right)$$
same as the convolutional case, but $c_{ij}$ is replaced by a **learned, implicit attention weight** $\alpha_{ij}(x_i,x_j)$, where $\alpha$ is itself a learnable function.

Unlinke convolutional GNNs, attention can express _not just similarity_, but also **repulsion** effects between nodes.

This architecture is a middle ground in capacity/scale, _edges don't need to encode homophily_, we can still only compute one scalar weight per edge.

The attention score is built up in the following way:
1. **Linear transform** of node features: $Wx_i$ (with $W$ _shared_ across all node)
2. **Concatenate** the transformed features of node $i$ and neighbor $j$
3. Pass through a shared single-layer **feedforward** network (the attention mechanism $\alpha$)
4. Apply a **nonlinearity** (e.g. LeakyReLU)
5. **Softmax** over $i$'s actual neighbors (not the whole graph), this is what normalizes attention weights per-neighborhood
![[Attentional GNN.png|500]]

The **node embedding update** is given by a weighted sum (by $\alpha$) of the transformed neighbor features, passed through a nonlinearity.

To _stabilize training_, GAT runs $K$ independent attention heads in parallel.
In hidden layers, the $K$ resulting embeddings are **concatenated**, whilst in the final output layer they're **averaged** instead.
![[Multi-head GAT.png|500]]
>Different edge colors mean different attention scores.

### Message passing GNN
The general form of a message passing GNN is:
$$g(x_i,X_{N_i})=\phi\left(x_i,\bigoplus_{j\in N_i}\psi(x_i,x_j)\right)$$
Instead of a single scalar weight per edge, we now compute an arbitrary **vector message** $m_{ij}=\psi(x_i,x_j)$ sent across each edge.

In this case **two nodes genuinely collaborate** to encode the message, this is different from convolutional/attentional approaches, which just weight the neighbor's own features.

This is the **most generic** GNN layer, and also the most expressive, but flagged as potentially having **scalability issues** since a message must be computed for every edge (this scaled quadratically).
>This leads to learnability issues.

![[Neural message passing.png|600]]

Formally, **neural message passing** can be split in two phases:
1. **Message passing** (run for $T$ steps, $T$ is a hyperparameter)
	- Message function $M_t$ depends on node $v$'s and $w$'s embeddings plus the edge $e_{vw}$ connecting them
	- Aggregate all incoming messages from a node's neighbors, this gives the message $M_v^{t+1}$
	- Update function $U_t$ combines the node's current embedding with its incoming message to produce the new embedding $h_v^{t+1}$
	- $M$ and $U$ are both learnable functions
2. **Readout**: a function $R$ that operates over the final set of all node states to produce a single output (e.g. for whole-graph prediction), $R$ must be _permutation-invariant_

### Relational inductive biases
The ability to build new inferences from known building blocks should be a priority in machine learning, this is also called **combinatorial generalization**.

Each architecture brings its own structural assumptions, called **inductive biases**:
- _Fully connected layers_: very weak relational bias, every input can influence every output unit independently
- _Convolutional layers_: impose locality and translation invariance as biases
- _Recurrent layers_: impose sequentiality as a bias, giving time translation invariance
- _Graph networks_: impose an arbitrary relational structure (defined by the graph's edges), giving invariance to node and edge permutations

Standard deep learning has "no default" way to operate on **arbitrary relational structure**, graphs fill that gap.

>[!Example] Example of a graph structure task
>For example, when predicting the center of mass of an $n$-body solar system, where each planet has attributes (mass, position, velocity).
>The order in which we consider the planets shouldn't matter, since the answer only depends on aggregated quantities

