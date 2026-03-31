In the field of **vectorial databases**, when a user submits a query, we also convert it into a vector and need to find the stored item whose vector is closest to the query, by using the **nearest neighbor search**.

Formally, let $\mathcal X=\{x_n\}^N_{n=1}$ be a set of $N$ $D$-dimensional vectors where each $x_n\in\mathbb{R}^D$.
Given a query $y\in\mathbb{R}^D$, find the vector $x_{n^*}\in\mathcal X$ that is closest to the query $y$:
$$n^*=\arg\min_{n\in\{1,...,N\}}||y-x_n||_2^2$$

Now, **comparing the query to every item** one by one has a time complexity of $O(DN)$, which is way too **slow** for large datasets.

### Approximate nearest neighbor
Instead of finding the exact nearest neighbor, we relax the requirement, that is: find a vector $\hat x$ whose **distance to the query is at most $(1+\epsilon)$ times the true minimum distance**, for some small $\epsilon>0$.
$$||y-\hat x||_2^2\leq(1+\epsilon)\cdot||y-x_n||_2^2$$
The idea is to use a **compact, approximate representation of the data**.
>Notice that we do not compute the true minimum distance during inference, it is just a theoretical guarantee that has to be respected for the algorithm to work.

### Product quantization
Product quantization (PQ) achieves compression through **vector quantization**, which means mapping high-dimensional vectors to small integer codes.

Let's consider a vector $x\in\mathbb R^D$ as a concatenation of $M$ subvectors of dimension $D/M$:
$$x=[x^1,...,x^M]$$
where the $m$-th subvector is $x^m\in\mathbb R^{D/M}$ for $m=1,...,M$.

The idea is to **map each subvector into a small integer identifier**.

After splitting the vectors into $M$ subvectors, each of size $M$, we take the first $M$ dimensions elements from each subvector, and run the [[03 - Clustering#K-means|K-means]] algorithm over them, with $k=M$.

For example, say we have $5$ vectors in our dataset, each with $D=4$ dimensions, and we split them into $M=2$ subvectors:

| Vector | Subvector 1 (dims 1–2) | Subvector 2 (dims 3–4) |
| :----: | :--------------------: | :--------------------: |
| $x_1$  |      $[1.1, 2.0]$      |      $[8.9, 9.1]$      |
| $x_2$  |      $[1.3, 1.8]$      |      $[8.7, 9.3]$      |
| $x_3$  |      $[5.0, 5.1]$      |      $[1.2, 1.0]$      |
| $x_4$  |      $[5.2, 4.9]$      |      $[1.0, 1.3]$      |
| $x_5$  |      $[1.0, 2.2]$      |      $[9.0, 8.8]$      |

then we take $i$-th subvector (first one in this case) and run K-means on it:
- _Cluster 0_: $[1.1,2.0], [1.3,1.8], [1.0,2.2]$ -> _centroid_ $\approx[1.1, 2.0]$
- _Cluster 1_: $[5.0,5.1], [5.2,4.9]$ -> _centroid_ $\approx[5.1, 5.0]$
repeating it for the second subvector, we get:
- _Cluster 0_: $[8.9,9.1], [8.7,9.3], [9.0,8.8]$ -> _centroid_ $\approx[8.9, 9.1]$
- _Cluster 1_: $[1.2,1.0], [1.0,1.3]$ -> _centroid_ $\approx[1.1, 1.2]$

Taking into consideration the first subvector: these two centroids are the **sub-codewords** $c_1^1$ and $c_2^1$ for subspace $1$, and together they form the **sub-codebook** $\mathcal C^1=\{c_k^1\}^K_{k=1}=\{c_1^1=[1.1, 2.0], c_2^1=[5.1, 5.0]\}$.
Whilst for the second subvector we get: $\mathcal C^2=\{c_k^2\}^K_{k=2}=\{c_1^2=[8.9,9.1], c_2^2=[1.1, 1.2]\}$.

The process gets repeated for each subvectors, hence **every sub-codebook is built independently**.

A **sub-encoder** $i^m$ takes the subvector $x^m$ and returns the identifier of the closest centroid (sub-codeword):
$$i^m(x^m)=\arg\min_{k\in\{1,...,K\}}||x^m-c_k^m||_2^2$$
the **encoding of a data point** $x$ (the **PQ code**) is the tuple of sub-encoders outputs:
$$i(x)=[i^1(x^1),...,i^M(x^M)]$$

Continuing with our example, we then proceed by encoding every vector by replacing each subvector with the index of its nearest centroid

| Vector | Subvector 1  | Nearest in $C^1$ | Subvector 2  | Nearest in $C^2$ | PQ code  |
| :----: | :----------: | :--------------: | :----------: | :--------------: | :------: |
| $x_1$  | $[1.1, 2.0]$ |       $0$        | $[8.9, 9.1]$ |       $0$        | $[0, 0]$ |
| $x_2$  | $[1.3, 1.8]$ |       $0$        | $[8.7, 9.3]$ |       $0$        | $[0, 0]$ |
| $x_3$  | $[5.0, 5.1]$ |       $1$        | $[1.2, 1.0]$ |       $1$        | $[1, 1]$ |
| $x_4$  | $[5.2, 4.9]$ |       $1$        | $[1.0, 1.3]$ |       $1$        | $[1, 1]$ |
| $x_5$  | $[1.0, 2.2]$ |       $0$        | $[9.0, 8.8]$ |       $0$        | $[0, 0]$ |

The **codebook is built once during training**, then during inference, the vectors are reconstructed by looking up the indexes and concatenating them, for example we would have after looking up the index in $C^k$ for $x_1$:
$$C^1[0]C^2[0]=[1.1, 2.0,8.9,9.1]$$
>Which in this example is equal to the original vector.

#### Encoding cost
Each sub-encoder scans $K$ centroids, costing $O(KD/M)$ per subspace, giving a total **encoding time of** $O(DK)$.

The **space cost of the encoding** is $M\log_2 K$ bits (typically $64$ or $128$ bits for the entire vector).

#### Quantization error
Replacing a vector with its nearest centroid introduces error.
The **total error** $e(x)$ is the **sum of squared distances** from each **subvector to its assigned centroid**. 
>K-means training directly minimizes this error.

Formally: we denote $i^{-1}$ the **inverse of the encoder**, that is, the decoder that maps back the PQ code ids  to the corresponding centroid in the sub-codebooks.

The error is measured w.r.t. the codebooks $\mathcal C=\{C^m\}_{m=1}^M$ and we call it **quantization error**:
$$e(x;C)=||x-i^{-1}(i(x))||_2^2=\sum_{m=1}^M\min_{k\in\{1,...,K\}}||x^m-c_k^m||_2^2$$

### Distance computation
Simply storing PQ codes does not help speed unless we can also compute distances efficiently without materializing the full vectors.

**Asymmetric distance computation (ADC)** handles this quite well:
Given a query $y\in\mathbb R^D$, and the PQ code $i(x_n)$ of a data point $x_n\in\mathcal X$:
1. For each sub-vector $y^m$, compute the distance between $y$ and all the $K$ centroids in all the $M$ sub-codebooks, which will result in a matrix $A\in\mathbb R^{M\times K}$, where $A(m,k)=||y^m-c_k^m||_2^2$
2. Given the PQ code $i(x_n)=[i^1,...,i^M]$, the approximate distance between $y$ and $x_n$ is given by:
$$||y-x_n||_2^2\approx\sum_{m=1}^M||y^m-c_{i^m}^m||_2^2=\sum_{m=1}^MA(m,i^m)$$
We use the PQ code ids $i^1,...,i^M$ to look up the distances in the matrix $A$, and since euclidean distance is addictive, we **sum up the precomputed distances**.


**Computational cost**:
- Computing $A$ (once per query) takes $O(MKD/M)=O(DK)$ time
- Computing the distance takes $O(M)$ lookups
- For $N$ vectors, the total cost is $O(DK+NM)$

It's called _asymmetric_ because the query is left as a full vector while only the database points are quantized, this gives better accuracy than quantizing both sides.

### Inverted file index with ADC
ADC still scans the entire dataset, which is too slow at scale, the **inverted file index with ADC (IVFADC)** introduce as **divide-and-conquer** layer on top.

**Indexing**:
- _Partition_ the dataset $\mathcal X$ into $J$ buckets $\mathcal X_1,...,\mathcal X_J$ and let $\mu_j\in\mathbb R^D$ be the representative vector of the $j$-th bucket (centroid)
- The _inverted index_ has $J$ initially empty _posting lists_, one for each bucket
- For each $x_n\in\mathcal X$:
	- Find the closest representative vector $\mu_j$
	- Store the PQ code of the residual $x_n-\mu_j$ in the postings list of the $j$-th bucket
>Residuals are smaller and encode the fine-grained deviation from the bucket center, giving better precision.

**Searching**, given a query $y\in\mathbb R^D$ is done by:
- **Coarse quantization**: find the closest representative vector $\mu_j$
- **Distance estimation**: use ADC between the residual $y-\mu_j$ and all the PQ codes in the $j$-th bucket

### Hierarchical navigable small worlds
**HNSW** is a completely different approach, which instead of quantization, it builds a **multi-layer graph** over the data.

The key idea comes from **"small world" networks**,  where any two nodes can be reached through a small number of hops.

Every node is a data point, **layer 0 (bottom layer) contains all nodes**, whilst higher layers contain progressively fewer nodes, this means that the **top layer is the sparsest**.
![[HNSW.png|500]]

**Insertion** of data point $q$:
1. _Randomly assign a maximum layer $l$ using a geometric distribution_ (higher layers are exponentially less likely)
$$l=\left\lfloor\frac{-\ln(\text{uniform}(0,1))}{\ln M}\right\rfloor$$
	- $M$: controls the average number of neighbors
	- $L_\max$: the highest layer currently existing in the graph
	
2. Starting from the top layer $L_\max$, _greedily traverse down_ to layer $l+1$ (the previous before the layer where insertions begin) by finding the nearest neighbor at each layer (used as the entry point for the next layer down), this happens by following the neighbors of the entry point of the current layer $E$, if one of its neighbor is closer to $q$, we move to that node and update $E$ to the new node, we repeat the process until we see that moving to a neighbor would move us far away from $q$  (this is the greedy part), hence we know that we are sitting on $E_\text{best}$
3. From layer $l$ down to $0$, we switch from a completely greedy behavior to a _beam search_, which is executed in each of these last layers:
	- Keep track of the nearest neighbors found so far in a priority queue $W$, called _the beam_ of size $ef>M$
	- Evaluate the neighbors of all nodes in $W$ (it is initially populated with $E_\text{best}$), if one of them is closer to $q$ than the furthest node currently in $W$, we add it and prune $W$ to maintain its size limit
	- Stop when we can no longer find any points to add to $W$ that improve the search
4. _Once we have the candidate set_ $W$ for the current layer:
	- Create bidirectional edges between $q$ and the $M$ best nodes in $W$
	- If any of those neighbors now exceeds the maximum allowed connections $M_\max$ remove their least useful edges (most distant ones to them)
	- The single closest element in $W$ serves as the entry point for the beam search in the next layer down

>[!Info] First entry point
>The first entry point at layer $L_\max$ is usually the first point being inserted into the graph, or another lucky point which was assigned to an higher layer and thus created a new layer with only himself inside.

**Search** is done with a greedy search from $L_\max$ down to layer $1$, then at layer $0$, _beam search_ is used, which will then return the one or $k$ nearest neighbors inside $W$.

|                      |                  IVFPQ                   |        HNSW         |
| :------------------: | :--------------------------------------: | :-----------------: |
|      **Memory**      |              More efficient              | Higher memory usage |
| **Index build time** |                  Faster                  |       Slower        |
|     **Accuracy**     |                   Good                   |       Better        |
|   **Query speed**    | Fast, great with batches (GPU optimized) |  Faster per query   |
| **Dynamic updates**  |                  Harder                  |   Better support    |

