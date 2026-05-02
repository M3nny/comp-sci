The goal from now on is to read a **stream** of integers $x_1,...,x_m\in[n]$ and create on-the-fly (online) a **data sketch** of the stream, which will typically use space proportional to:
$$polylog(n+m)=O\left((\log(n+m))^{O(1)}\right)$$
A **data sketch** is a function $f(x)$ applied to the data $x$ that satisfies several properties.

**Small size**
The sketch is _exponentially smaller_ than the original:
$$bitsize(f(x))\ll bitsize(x)$$
**Usefulness**
Despite being tiny, the sketch lets us estimate interesting properties of the original data, for example, if $x$ is a stream (multi-set):
- The number of distinct elements in $x$
- The frequency of any $y\in x$
- Some function of the frequencies of the elements in $x$

Because of the small size of the data structure, it is usually not possible to compute these properties _exactly_, instead we get an _$\epsilon$-approximation_ with probability $\geq1-\delta$, meaning the answer is within $\epsilon$ of the truth at least $1\delta$ fraction of the time.

**Dynamic**
The sketch can be updated efficiently when new data arrives, without needing to re-read the old data.

If we have sketches of two datasets $x_1$ and $x_2$ separately, we can compute the sketch of their union $x_1\cup x_2$ from just the two sketches, we don't need the original data.

**Similarity-preserving (optional but desirable)**
If two datasets $x_1$ and $x_2$ are "similar" by some measure, their sketches $f(x_1)$ and $f(x_2)$ are also similar, this is called a _locality-sensitive_ property and is extremely useful when we want to compare many datasets efficiently.

Sketches are usually constructed through randomization, this means that we apply one or more hash functions to the data and combine the results.

### Metrics
We will devise several sketches possessing the similarity-preserving property under several metrics.

A **metric** $d(x,y)$ is a function satisfying:
- **Identity**: $d(x,x)=0$
- **Symmetry**: $d(x,y)=d(y,x)$
- **Triangle inequality**: $d(x,z)\leq f(x,y)+d(y,z)$

### Jaccard similarity and MinHash
Given two sets $A$ and $B$, the **Jaccard similarity** measures how much they overlap:
$$J(A,B)=\frac{|A\cap B|}{|A\cup B|}$$
- $J(A,B)=0\iff A\cap B=\emptyset$
- $J(A,B)=1\iff A=B$

The **Jaccard distance** is a **metric** and is defined as:
$$d_j(A,B)=1-J(A,B)=1-\frac{|A\cap B|}{|A\cup B|}$$

**MinHash** was originally used in the AltaVista search engine to detect near-duplicate web page, today is also used by Google for the same reason, but also by other companies in order to check for similar things (e.g. genomes, recommendations, ...)

The core idea is to take a hash function $h:[n]\to[n]$ that is a **uniform random permutation** (a bijection that maps each element to a unique other element, chosen uniformly at random).

For a set $A\subseteq [n]$, the MinHash value is:
$$\hat h(A)=\min\{h(x):x\in A\}$$
That is, apply $h$ to every element of $A$, and take the _minimum_ output value.

This is remarkable since a set $A$ can have up to $n$ elements, each needing $\log n$ bits, so $A$ could take $O(n\log n)$ bits to store, but $\hat h(A)$ is just a single integer in $[n]$, needing only $\log n$ bits, this is an **exponential compression**.

|  $x$   |  1  |  2  |  3  |  4  |  5  |  6  |
| :----: | :-: | :-: | :-: | :-: | :-: | :-: |
| $h(x)$ |  5  |  3  |  1  |  2  |  4  |  6  |

With $A=\{4,2,6,1\}$:
- $h(A)=\{2,3,6,5\}$
- $\hat h(A)=2$

### Unbiased estimator
For two sets $A$ and $B$, and a random permutation $h$:
$$\mathbb P[\hat h(A)=\hat h(B)]=J(A,B)$$
The probability that $A$ and $B$ have the **same MinHash** value equals to their Jaccard similarity.

Let's define the following **Bernoullian indicator**:
$$\hat J(A,B)=\begin{cases}1&\text{if }\hat h(A)=\hat h(B)\\0&\text{otherwise} \end{cases}$$
the theorem says that $\mathbb E[\hat J(A,B)]=J(A,B)$, this is an **unbiased estimator**.

**Proof**
Let $N=|A\cup B|$, for each element $i\in A\cup B$, define the event $smallest(i)$ as "the element $i$ has the smallest hash value among all elements $A\cup B$".

Since $h$ is a permutation:
- Exactly one element will have the minimum hash
- By uniformity, each element $i\in A\cup B$ is equally likely to be the minimum: $\mathbb P(smallest(i))=1/N$

Now we apply the _law of total expectation_, conditioning on which element is the minimum:
$$\mathbb E[\hat J(A,B)]=\sum_{i\in A\cup B}\mathbb P(smallest(i))\cdot \mathbb E[\hat J(A,B)|smallest(i)]$$
Split the sum into two cases:
- $i\in A\cap B$ (the minimum element belongs to both sets), then $\hat h(A)=h(i)=\hat h(B)$, so $\hat J(A,B)=1$
- $i\in (A\cup B)\setminus(A\cap B)$ (the minimum element is in one set but not the other), then $\hat A()\neq\hat h(B)$, so $\hat J(A,B)=0$

Therefore:
$$\mathbb E[\hat J(A,B)]=\frac{1}{N}\sum_{i\in A\cap B}1=\frac{|A\cap B|}{N}=\frac{|A\cap B|}{|A\cup B|}=J(A,B)$$

### Reducing the variance
The estimator $\hat J(A,B)$ is either $0$ or $1$, which is a Bernoulli random variable, the true $J(A,B)$ is a fraction between $0$ and $1$, so a single trial gives a very noisy estimate.

This means that $\hat J(A,B)$ **alone is not a great estimator**, even if $E[\hat J (A,B)]=J(A,B)$.

When dealing with Bernoullian estimators, we don’t need the [[09 - Concentration bounds#The mean-median trick|mean-median trick]], we just apply [[09 - Concentration bounds#Chernoff-Hoeffding|Chernoff-Hoeffding]].

So, we use $k$ independent hash permutations $h_1,..,h_k$ and average their estimates:
$$J^+(A,B)=\frac{1}{k}\sum_{i=1}^k\hat J_{h_i}(A,B)$$
and by directly applying Chernoff-Hoeffding:
$$\mathbb P[|J^+(A,B)-J(A,B)|\geq\epsilon]\leq2e^{-\epsilon^2 k/2}$$
Setting this probability equal to $\delta$ and solving for $k$:
$$k=\frac{2\ln(2/\delta)}{\epsilon^2}=O(\epsilon^{-2}\log(1/\delta))$$
**Theorem**
Fix any desired absolute error $0<\epsilon\leq 1$ and failure probability $0<\delta\leq1$, the MinHash sketch:
- Uses $O(\epsilon^{-2}\log(1/\delta))$ words of space (one MinHash value per permutation)
- Computes $J^+(A,B)$ in the same time
- Satisfies $\mathbb P[|J^+(A,B)-J(A,B)|\geq\epsilon]\leq\delta$

**The problem with hash functions**
The whole proof assumed $h$ is a _uniform random permutation_ of $[n]$, but to specify a random permutation of $[n]$, we need $\log_2(n!)$ bits:
$$\log_2(n!)=O(n\log n)$$
For $n=2^{32}$ (IPv4 addresses), this is infeasible, so the sketch is useless if the hash function itself requires enormous storage.

### Min-wise independent permutations
The proof of the unbiased estimator did not actually require a full uniform permutation, it only used one property:

**Min-wise independent hashing**
A family of hash functions $\mathcal H$ (where each $h:[n]\to[0,M)$) is _min-wise independent_ if, for any subset $A\subseteq [n]$ and any $i\in A$:
$$\mathbb P[h(i)=\min_{j\in A}h(j)]=\frac{1}{|A|}$$
In words: when we draw a random $h$ from $\mathcal H$, every element of any set $A$ is equally likely to have the minimum hash value, and this is all we need for the MinHash proof.

For MinHash to work on any subset $A$, the family $|\mathcal H|$ must be a multiple of $|A|$ for every possible size of $A$ (so each element can get equal probability).
Since this must hold for sets of size $1,...,n$, we need $|\mathcal H|$ to be divisible by all of $1,...,n$, that is at least $lcm(1,...,n)$ (least common multiple).

By the _prime number theorem_, $lcm(1,...,n)=e^{n-o(n)}$, so:
$$\log_2|\mathcal H|=\Omega(n)$$
Any min-wise independent hash family requires at least $\Omega(n)$ bits to store, which is still bad for large $n!$.

Fortunately, a weakened version is sufficient and achievable cheaply.
A family $\mathcal{H}$ is **approximately min-wise independent** with error $\epsilon$ if:
$$\mathbb P[h(i)=\min h(A)]=\frac{1\pm\epsilon}{|A|}\quad\forall A\subseteq[n]\text{ and any desired }\epsilon>0$$
This can be achieved with only $O(\log(1/\epsilon))$ words of space.
