A **cluster** is a collection of data objects that are:
- _Similar_ to the objects inside the same cluster
- _Dissimilar_ to objects inside of other clusters

This is an **unsupervised learning** task with no predefined classes and unlabeled data, it is often used for grouping things based on a certain behavior, and it can also be used as a _preprocessing step_.

A good clustering produces **high intra-class similarity** and **low inter-class similarity**.
The fact is that in general the true clustering is **not known**, and similarity-based measures might not suffice.

The **quality** of a clustering algorithm depends on the ability to handle various cluster shapes, sizes and densities, other than dealing with outliers.
Other than this it should be computationally feasible and scalable.

Let the **centroid** of a cluster be the **mean** of the data points in the cluster.
We measure the quality of a cluster by the **sum of squared distances (SSD)** of the data points to the centroid.

Given a dataset $D$, with $n=|D|$ data points:
- Let $C_1,...,C_k$ be clusters of $D$, and let $c_i$ be the centroid of $C_i$
- Let $d(x,y)$ be the distance between data points $x$ and $y$, such as the euclidean distance $d(x,y)=\sqrt{\sum_j(x_j-y_j)^2}$

Then the quality of the clustering is given by:
$$SSD=\sum_{i=1}^k\sum_{x\in C_i}d(x,c_i)^2$$

### K-means
A lazy approach to design a clustering algorithm that minimizes SSD is the **k-means** algorithm:
1. Start with random centroids $c_1,...,c_k$
2. While the centroids keep changing (or change slightly):
	1. Assign each data point to the nearest centroid
	2. Compute the new centroids of the current partition by using the mean of the assigned data points, this will reduce the SSD

**Random initialization is a problem**, one might prefer the [[K-means#K-means++|k-means++]] method.
The algorithm converges to a **local optimum** since minimizing SSD is [[Teoria della NP completezza#Classe NPC|NP-hard]] for a general number of clusters.
Another defect is that it **only handles spherical clusters**.

We can choose $k$ based on the [[K-means#Elbow method|elbow method]] which is the $k$ value for which the error does not decrease significantly.

### K-means++
The **K-means++** algorithm works in the same way of the original algorithm, but it defines an algorithm for choosing the initial centroids in order to have them well separated and make them cover most of the data:
1. Pick the first centroid randomly
2. Repeat for the other $k-1$ centroids:
	1. For every data point $x$ compute the distance $d(x,c_j)$ w.r.t the nearest centroid
	2. Assign to each point a probability proportional to $d(x,c_j)^2$
	3. Pick a new centroid randomly based on the previously assigned probabilities

For any dataset, this algorithm variation guarantees that the **expected** $SSD$ is at most $8(\ln k+2)$ times the optimal $SSD$.

K-means is **efficient**, and its complexity is equal to $O(|D|\cdot k\cdot i)$, where $i$ is the number of iterations.

### Mini-batch K-means
The **mini-batch** version of the algorithm is used to handle big datasets, and works as follows:
1. Start with random centroids $c_1,...,c_k$
2. While the centroids keep changing (or change slightly):
	1. Grab a small random sample (mini-batch $M$) of $b$ points from the dataset (instead of using all the data)
	2. Assign each point in the mini-batch to its nearest centroid
	3. Update each centroid incrementally, one mini-batch at a time:
		1. Increment the count $v$ for the assigned centroid by $1$
		2. Compute a learning rate $\eta=\frac{1}{v}$ (this gets smaller as more points are seen)
		3. Nudge the centroid slightly toward the new point $x$ using $\eta$ as the step size
3. Once the centroids have settled, assign every point in the full dataset to its nearest centroid to produce the final clusters

The key difference is that centroids are updated on small random chunks of data rather than the full dataset.The centroids will converge to a **slightly less optimal** solution, but the **speed gain is usually worth it** for large datasets.

The complexity is $O(b\cdot k\cdot i)$ where $i$ is the number of iterations, and since $b<<|D|$ it is much faster than the original K-means.

Decreasing learning rate is what ensures **convergence**.

**The larger $b$ is, the better the quality** of the clustering, trivially, when $b=|D|$, it is equal to the original K-means.
>**The smaller $b$, the faster the algorithm**.

### Clustering Using REpresentatives (CURE)
The **CURE** clustering algorithm targets:
- Clusters of arbitrary shape
- Outliers
- Large datasets

It is a two-phase [[Gerarchico|hierarchical clustering]] algorithm, that first clusters a random sample of the data and then assigns the remaining points to the nearest found cluster.

**Step 1: random sampling**
Since clustering the full dataset is expensive, it draws a random sample of size $m$, and we want $m$ to be small (for speed), but large enough to ensure that every cluster is represented in the sample.
>This means that in the sample we want to grab at least some points from every cluster that exists in the data.

**Step 2: sample partitioning**
If the sample size $m$ is too large (in terms of memory), split it in $p$ equally sized partitions of size $m/p$, each designed to fit in main memory, but don't choose a $p$ that is too big, otherwise we cannot capture the shape of each cluster (that will be small).

Each partition is then clustered independently so that each group has $\frac{m}{pq}$ clusters and the total number of clusters is $m/q$.
- $q$ is a user defined parameter, and it can be considered as the average cluster size

The goal is that even though clusters may be split across partitions, each cluster is still represented by enough points.

**Step 3: hierarchical clustering of the partitions**
CURE uses a hierarchical bottom-up algorithm to cluster the partitions:
- Initially each data point is considered a cluster
- At each step, the two clusters that are closes to each other are merged
	- Each cluster is represented by a set of $c$ _representative points_
	- The distance between two clusters is defined  as the minimum distance between any two representative points
	- Merging is repeated until we have the desired number of clusters

Representative points are chosen to be well scattered:
- The first point is the point farthest from the cluster center
- Remaining points are farthest from all the previously chosen points
>Similar to K-means++ initialization.

Finally, each representative is nudged toward the cluster center (_shrinking_) by a factor of $\alpha\in[0,1]$.
This dampens the influence of outliers and prevents false merges between nearby clusters.

The larger $c$ the more expensive, the better the ability to model arbitrary shapes.
For smaller $\alpha$ representatives collapse to the center, hence leads to more spherical clusters, for larger $\alpha$ they stay in place, hence capturing arbitrary shapes.

**Step 4: merging partial clusters and outlier removal**
The previous step applied clustering locally to each partition, now we apply the same approach, but to partitions themselves.

```
Partition 1: [points] -> 5 partial clusters  |
Partition 2: [points] -> 5 partial clusters  |-> merge into final clusters
Partition 3: [points] -> 5 partial clusters  |
```

The $m/q$ partial clusters from step 2 are now merged into the final $k$ clusters using the same hierarchical approach.

Outlier removal happens here in two passes:
- When the number of clusters reaches $1/3$ of the number of data points
- Again near the end, when the cluster count is close to $k$

Outliers are identified as clusters with very few points ($\leq 2$), since by definition outliers are isolated and never absorbed into large clusters.

**Step 5: assigning remaining data points to clusters**
With the final $k$ clusters established (each with $c$ representative points), the rest of the dataset is scanned, and each point is assigned to whichever cluster has the nearest representative point.

The **complexity** is $O(m^2\log m)$, where $m$ is the dataset/sample size, but large values of $p$ and $q$ reduce the cost.

![[K-means vs CURE.png]]