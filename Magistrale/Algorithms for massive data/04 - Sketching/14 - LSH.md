So far we tried to avoid collisions when hashing various elements, now we want the opposite.

The goal of **Locality Sensitive Hashing (LSH)** is to design a hash function $h$ such that:
$$\mathbb P[h(x)=h(y)]\text{ increases as }d(x,y)\text{ decreases}$$
In other words, similar things should **hash to the same bucket**, and dissimilar things should hash to different buckets.

Suppose having a dataset $A$ of $m$ objects and want to _find all pairs that are similar_ (small distance), if we compare every pair, that's $O(m^2)$ distance computations, which is infeasible for large datasets.

LSH solves this by comparing elements that end up in the same hash bucket, **similar elements are likely to land in the same bucket**, so you find most similar pairs while examining only a tiny fraction of all possible pairs.

### Ideal vs the achievable
Fixing a threshold distance $t$, we'd want:
$$h(x)=h(y)\iff d(x,y)\leq t$$
So, everything closer than $t$ collides, and everything farther doesn't.

We won't be able to achieve this, but we can **approximate** it, intuitively: the closer we want this function to be to a perfect step function, the more hash functions we will need to employ (more space and time).

### Sensitive families
The most informative description of a LSH is a plot comparing collision probability vs distance.
![[LSH sensitivity.png|400]]
However that's too informative, so we'll just say what happens in **two points** on the curve (close to the step).

A hash family $\mathscr H$ is $(d_1,d_2,p_1,p_2)$-sensitive if, for a uniformly-drawn $g\in\mathscr H$ we have that:
- If $d(x,y)\leq d_1$, then $\mathbb P(g(x)=g(y))\geq p_1$: close objects collide with high probability
- If $d(x,y)\geq d_2$, then $\mathbb P(g(x)=g(y))\leq p_2$: far objects collide with low probability
>The image above is $(0.48,0.6,0.75,0.12)$-sensitive.

The two distances $d_1<d_2$ define a **transition zone**, we are free to choose the two points, but ideally:
- $d_1\approx d_2$: a sharp function as close as possible to a step function
- $p_1\approx 1$: guaranteed to find similar items
- $p_2\approx 0$: almost no false positives

### Constructing a primitive LSH
We start from a very simple function, then we're going to apply **two transformations** to make it _resemble_ a step function, this is achieved by combining several **distance-sensitive hash functions**.

We recall that [[13 - MinHash#Jaccard similarity and MinHash|MinHash]] is a distance-relative hash:
$$\mathbb P[\hat h(A)=\hat h(B)]=J(A,B)=1-d_j(A,B)$$
![[Collision probability MinHash.png|400]]

But alone it is a bad approximation of a step function.

### AND construction
Take $r$ independent hash functions $h_1,...,h_2$ from a $(d_1,d_2,p_1,p_2)$-sensitive family $\mathscr H$, and define:
$$h^{AND}(x)=(h_1(x),...,h_r(x))$$
Two elements **collide** under $h^{AND}$ only **if all $r$ individual hashes agree** simultaneously.

So, if the original per-function collision probability is $\mathbb P(h(x)=h(y))=p$:
$$\mathbb P[h^{AND}(x)=h^{AND}(y)]=p^r$$
Since $p\in[0,1]$, raising to the power $r$ **makes high probabilities stay high**, and **crushes low probabilities toward $0$**.
Hence $h^{AND}$ is a $(d_1,d_2,p_1^r,p_2^r)$-sensitive family.

In the case of **Jaccard distance** (with MinHash):
- $\mathbb{P}(\hat{h}(A) = \hat{h}(B)) = 1 - d_J(A, B)$
- $\mathbb{P}(\hat{h}^{AND}(A) = \hat{h}^{AND}(B)) = (1 - d_J(A, B))^r$
![[AND construction Jaccard.png|400]]

### OR construction
Take $b$ independent hash functions and declare a collision **if at least one of the $b$ hashes agrees**:
$$h^{OR}(x)\equiv h^{OR}(y)\iff h_i(x)=h_i(y)\text{ for some }i\in[b]$$
The new collision probability is:
$$\mathbb P[h^{OR}(x)\equiv h^{OR}(y)]=1-(1-p)^b$$
This works because the probability that none of the $b$ hashes agree is $(1-p)^b$, so at least one agrees with probability $1-(1-p)^b$.
Hence $h^{OR}$ is a $(d_1,d_2,1-(1-p_1)^b, 1-(1-p_2)^b)$-sensitive family.

>[!Tip] Implementation detail
>From a **practical point of view**, we build $b$ separate hash tables $H_1,...,H_b$, each element $x$ is inserted into bucket $H_i[h_i(x)]$ for each $i$, then two elements collide under the OR rule if they share a bucket in _any_ of the $b$ tables.


### AND+OR construction
Combine both approaches, first AND (concatenate $r$ hashes), then OR (use $b$ such AND-groups):
$$h^{AND+OR}(x):\text{ collide if any of the }b\text{ AND-groups agrees fully}$$
The new collision probability is:
$$\mathbb P[h^{AND+OR}(x)\equiv h^{AND+OR}(y)]=1-(1-p^r)^b$$
Hence $h^{AND+OR}$ is a $(d_1,d_2,1-(1-p_1^r)^b, 1-(1-p_2^r)^b)$-sensitive family.

For Jaccard distance, substituting $p=1-d_J(A,B)$:
$$\mathbb P[\hat h^{AND+OR}(A)\equiv\hat h^{AND+OR}(B)]=1-(1-(1-d_J(A,B))^r)^b$$
which gets us much closer to a step function.
![[AND+OR construction Jaccard.png|400]]
- $r$ **controls the position of the step**, that is, the threshold $t$ at which the transition happens
- $b$ **controls the steepness of the step**, that is, for larger $b$ we get sharper transition and better separation, but more space since we need $b$ hash tables

### Choosing parameters $r$ and $b$
Given a desired threshold distance $t$ (the center of the step):
1. Choose $b$ as large as our space budget allows, it directly trades space for quality
2. Derive $r$ from $b$ and $t$ using the observation that the step center is where the curve equals $1/2$:
$$r=\left\lfloor\frac{\ln(1-2^{-1/b})}{\ln(1-t)}\right\rfloor$$

>[!Example]
>We want to find sets with Jaccard distance at most $0.9$ (threshold $t=0.9$):
>- Choose $b=10^5$ (chosen arbitrarily for larger sharpness)
>- The formula gives $r=5$
>- Result is a $(0.85,0.95,0.99949,0.03076)$-sensitive function
>
>Objects at distance $\leq 0.85$ collide $99.9\%$ of the time, whilst objects at distance $\geq 0.95\%$ collide only $3\%$ of the time.

### Nearest Neighbor Search (NNS)
Given a dataset $A=\{x_1,...,x_m\}$ and a distance threshold $D$, we're going to build a data structure so that later, given any new query point $x$, we can quickly find some $x_i\in A$ with $d(x_1,x)\leq D$.

Since each $x_i$ could be an high dimensional vector, computing the distance between all other vectors is infeasible, hence we **approximate** it by finding a point within distance $D$ with high probability, if one exists, while examining only a small fraction of $A$.

>[!Example] Document plagiarism detection
>Pre-process $m$ documents (each represented as a set of tokens).
>Given a new document $x$, find a document $x_i$ in the database with $d_J(x,x_i)\leq0.7$, specifically, we want:
>- If a document with $d_J(x,x_i)\leq0.4$ exists, find it with probability $\geq0.999$
>- No guarantees for documents in the "gray zone" $d_J\in[0.4,0.7]$
>- At most $0.7\%$ of the database triggers false positives
>
>With $d_1=0.4$, $d_2=0.7$, threshold $t=0.5$, $b=1200$, $r=10$, this gives a $(0.4,0.7,0.999,0.007)$-sensitive function.

The data structure has two components:

**The MinHash array $M$**
For each document $x_i$, compute and store its MinHash $\hat h(x_i)$, this is a compact sketch that lets us estimate $d_J$ between any two documents quickly without the original data.

**The $b$ hash tables $H_1,...,H_b$**
For each of the $b$ hash groups $j\in[b]$, we compute:
$$\hat h_j^{AND}(x_i)=(\hat h_{1,j}(x_i),...,\hat h_{r,j}(x_i))$$
This is a tuple of $r$ MinHash values, and to save space, instead of storing this $r$-tuple directly in the hash table, we apply an additional collision-free hash $h'$ to it first, getting a single integer, then we insert the index $i$ into the bucket $H_j[h'(\hat h_j^{AND}(x_i))]$.

Without the extra $h'$, each hash table entry is an $r$-tuple of integers, and we end up occupying $O(b\cdot r\cdot m)$ total space, with $h'$, each bucket key is a single integer which occupies $O(b\cdot m)$ total space.

Space summary:
- Array $M$: $O(m)$ words
- $b$ hash tables: $O(b\cdot m)$ words
- Total: $O(b\cdot m)$ words

The **query algorithm** works as follows:
1. Compute MinHash $\hat h(x)$
2. For each of the $b$ hash tables $j\in[b]$: compute $h'(\hat h_j^{AND}(x))$ and look up bucket $H_j[h'(\hat h_j^{AND}(x))]$, this will give us the indices of all database elements that "collide" with $x$ in hash table $j$
3. For each candidate $x_i$ found in any bucket: use the stored MinHash $M[i]$ to estimate $d_J(x,x_i)$, then if the estimate is $\leq0.7$, return $i$

The time take is: $O(b\cdot r\cdot|x|)$ to compute all hash values, plus the time to check candidates.

Some candidates retrieved from the hash tables will be **false positives**, that is, elements that collided with $x$ by chance despite being far from it ($d_J>0.7$).

In the worst case, all $m$ elements are potential false positives, but the LSH guarantees that only $p_2=0.7\%$ of them will collide, so at most $0.0007\cdot m$ false positives need to be checked.

**Guarantee summary**:
- If $\exists x_i$ with $d_J(x_i,x)\leq0.4$: found with probability $\geq0.999$
- False positives at most $0.7\%$ of $A$
- Space: $O(b\cdot m)$
- No guarantees for elements in the "gray zone" $d_J\in[0.4,0.7]$

