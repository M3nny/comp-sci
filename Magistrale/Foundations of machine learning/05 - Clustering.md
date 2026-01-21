Given an edge-weighted graph $G$ (represented as a matrix), with the edges containing **pairwise similarities**, we want to partition the vertices of $G$ into maximally homogeneous groups, called **clusters**.
>Similarities are symmetric.

### K-means clustering
The k-means clustering algorithm works as follows:
1. Pick $K$ random points as **cluster centers**
2. Assign data points to the closest cluster center
3. Change the cluster center to the average of its assigned points
4. If points assignments did not change, stop, otherwise go to step 2

This algorithm is <u>guaranteed to converge in a finite number of steps</u>.
It minimizes the objective function representing the compactness of clusters:
$$\sum_{i\in\text{clusters}}\sum_{j\in{i}}||x_j-\mu_i||^2$$
where $\mu_i$ is the center of cluster $i$.


|   Pros    |                   Cons                   |
| :-------: | :--------------------------------------: |
|  Simple   |       Converges to a local minimum       |
| Efficient |             Need to pick $K$             |
|           | Sensitive to initialization and outliers |
|           |      Only finds spherical clusters       |

### MinCut clustering
MinCut tries to **partition a graph into two groups** $A$ and $B$ by cutting edges between them, the goal is to _minimize the total weight of cut edges_.

Given a weighted graph $G=(V,E,w)$ and a partition $(A,B)$ where $B=V\setminus A$, the cut is defined as:
$$cut(A,B)=\sum_{i\in A}\sum_{j\in B}w(i,j)$$
this sums up all edge weights between nodes in set $A$ and nodes in set $B$.

By minimizing the cut, we're cutting the weakest connections between groups.

The **critical problem** is that it tends to favor _highly unbalanced_ partitions, often just isolating single vertices or tiny groups.

This is due to the fact that the easiest way to minimize the cut is to separate one vertex (or a small group) from the rest, in fact this cuts very few edges.

### Normalized cut
Normalized cut (Ncut) fixes MinCut's problem by **normalizing the cut value** by the size of each partition, this prevents the algorithm from favoring tiny isolated clusters.
$$Ncut(A,B)=cut(A,B)\left(\frac{1}{vol(A)}+\frac{1}{vol(B)}\right)$$
- $vol(A)$: sum of all edge weights connected to nodes in $A$ (volume, or total degree of $A$)
- $vol(B)$: sum of all edge weights connected to nodes in $B$

This works because we penalize small clusters, forcing the algorithm to find more balanced and meaningful clusters.

The optimization problem can be re-formulated as:
$$Ncut(A,B)=\min_y\frac{y^T(D-W)y}{y^TDy}$$
- $y$: $n$-dimensional vector ($n$ being the number of nodes) where the $i$-th position is equal to $1$ if node $i\in A$, or$-1$ if $i\in B$
- $W$: the affinity/similarity matrix which measures similarities between nodes (the diagonal is equal to $0$ and the matrix is symmetric)
- $D$: degree (diagonal) matrix, the diagonal value $d_i$ is given by summing up the values vertically (or horizontally, since the matrix is symmetric) of $W$ in the $i$-th column

This is called a **Rayleigh quotient** and the optimization problem is [[Teoria della NP completezza#Classe NPC|NP-hard]] because $y$ must take discrete values ($1$ or $-1$).

Now the **key fact** is that:
$$f^TLf=f^T(D-W)y=\frac{1}{2}\sum_{i,j}w_{ij}(f_i-f_j)^2$$
where in our case $f=y$, and since if $i$ and $j$ are in the same cluster we get $(y_i-y_j)^2=0$ and if on different clusters we get: $(y_i-y_j)^2=4$:
$$y^T(D-W)y-\frac{1}{2}\sum_{\stackrel{i\in A}{j\in B}}w_{ij}\cdot4=2\sum_{\stackrel{i\in A}{j\in B}}w_{ij}=2\cdot cut(A,B)$$
>This highlights how the numerator of our minimization problem is strictly related to the cut itself, we just transformed it.

As regard to the denominator, it encodes the volume information through node degrees, ensuring that the optimization considers cluster size measured by total connectivity, not just node count.

We can **relax** the problem by setting $y\in\mathbb R$, and then we can transform the problem in the following mathematically equivalent version, which is easier to solve using standard eigenvalue techniques:
$$\begin{align}
\min_y y^T(D-W)y\\
y^TDy=1
\end{align}$$

This becomes a **generalized eigenvalue problem**:
$$\underbrace{(D-W)}_{\text{Laplacian}}y=\lambda Dy$$

Partitions are built using the **2-way Ncut**:
1. Build the affinity matrix $W$ and degree matrix $D$
2. Solve the eigenvalue problem $(D-W)y=\lambda Dy$
3. Take the eigenvector corresponding to the second eigenvalue, this is because the smallest eigenvalue of Laplacians is always $0$ and is trivial
4. Use this eigenvector to split the graph in two parts:
	- Sort nodes by their eigenvector value
	- Choose a splitting point (e.g. median)
	- Nodes above the splitting point go to $A$, below go to $B$



#### More than two clusters

**Recursive two-way cuts**
1. Given the weighted graph $G=(V,E,w)$, compute $W$ and $D$
2. Solve $(D-W)y=\lambda Dy$ for the eigenvector with the second smallest eigenvalue
3. Use this eigenvector to bipartition the graph
4. Verify that the Ncut value is below a prespecified threshold
	- If Ncut is too high, the split is not meaningful (don't subdivide further)
5. Recursively apply the same process to each resulting partition and stop when subdivisions are no longer stable or meaningful

This is computationallu wasteful since we don't use information given by other eigenvalues.

**Use first $k$ eigenvectors**
1. Compute $W$ and $D$
2. Solve the eigenvalue problem to get the first $k$ eigenvectors
3. Stack these $k$ eigenvectors to form a $n\times k$ matrix
4. Apply k-means clustering to these $n$ row vectors in $k$-dimensional space

Each eigenvector encodes partitioning information at different scales, together they provide a **spectral embedding** of the graph, now clusters are more separable when represented in this way, hence k-means can easily find clusters.

We can choose $k$ such that eigenvalues $\lambda_1,...,\lambda_k$ are very small, but $\lambda_{k+1}$ is relatively large.

This works because small eigenvalues indicate well-separated clusters, and a large gap, called **eigengap** between $\lambda_k$ and $\lambda_{k+1}$ suggests that $k$ is the natural number of clusters, and adding more does not reveal meaningful structure.