In previous chapters we've dealt with estimating how many times a **single specific element** appears in a data stream, in this chapter we're going to estimate **aggregate statistics** over all frequencies at once, called **frequency moments**.

Given a stream of $m$ elements drawn from a universe $[n]=\{1,2,...,n\}$, let $f_x$ denote the number of times element $x$ appears, the **$k$-th frequency moment** is:
$$F_k=\sum_{x\in[n]}f_x^k$$
This is just the sum of all individual frequencies each raised to the power of $k$.

- $F_0$: with the convention that $0^0=0$, $F_0=\sum_{x:f_x>0}1$ which is simply the _number of distinct elements_ in the stream
- $F_1$: each frequency is raised to the power $1$, so $F_1=\sum f_x=m$, the total length of the stream, this is trivial and requires just counting elements as they arrive using $O(\log m)$ bits, we could also do it in $O(\log\log m)$ bits using the [[18 - Misra-Gries#Morris approximate counting|Morris algorithm]]
- $F_2$: useful in dimensionality reduction

### Counting distinct elements
Before working through the implementation of data structures, we introduce the problem with real use cases.

Suppose that we want to know **how many different users have viewed a video**, simply counting views won't work since the same user might watch a video multiple times, instead we have to count distinct IPs.

This is hard since it can be proved that for an exact answer we need to store the entire set of elements seen so far, usually we can approximate it.

Other applications include:
- **DoS detection**: the attack causes a sudden spike in the number of distinct (sender IP, receiver IP) pairs passing through a hub, monitoring this count can trigger an alert
- **Worm spreading rate**: to estimate how fast a network worm is spreading, filter all packets that contain the worm's code and count distinct sender IPs, more infected machines mean more distinct senders

### Naive solutions
**Bitvector**
Allocate a bit array of size $n$ (one bit per possible element), when element $x$ arrives, set bit $x$ to $1$, then at the end, count the $1$s.
This uses exactly $n$ bits and gives the exact answer, but only works well when the universe $n$ is small.

**Hash table**
Maintain a dynamic data structure that stores only the distinct elements seen so far. When a new element arrives, insert it if not already present.
At the end, return the size of the set, the space is proportional to $d$ (the true number of distinct elements), which is good if few distinct elements appear but bad if $d$ is large.

**MinHash**
Recalling that MinHash is used to estimate the Jaccard similarity between sets, here the two sets are the stream's distinct elements and the full universe $[n]$, since $d=J(stream,[n])\cdot n$, MinHash can estimate $d$ but only within an addictive error of $\pm\epsilon\cdot n$, which is bad if $d\ll n$ (we want a relative error guarantee)

**Uniform random sampling does not work**, since if we just sample elements from the stream, we're more likely to pick elements that appear many times, and rare elements gets sampled with very low probability.

### Flajolet-Martin algorithm
The **Flajolet-Martin (FC)** algorithm was inspired by the [[18 - Misra-Gries#Morris approximate counting|Morris algorithm]] and later inspired [HyperLogLog](https://en.wikipedia.org/wiki/HyperLogLog) which is used today by many companies.
>We're going to see an "idealized" version which is easier to analyze.

The intuition is to draw $d$ elements $x_1<x_2,...,x_d$ uniformly at random from $[n]$, if we repeat this with a larger $d$, the smallest element $x_1$ **will become smaller** (on expectation), this means that $d$ can be expressed as a function of $x_1$.

The sketch reduces to storing only $x_1$.
If the stream contains **repeated elements**, the minimum $x_1$ is _not affected_, and if the elements are **not uniform** in $[n]$ we can _randomize them via hashing_.

```
initialization():
	h = uniform function from [n] to reals in [0, 1] // only idealized
	y = 1

new_stream_element(x):
	y = min(y, h(x))

estimate_distinct():
	return 1/y - 1
```

Why does this work?
The $d$ distinct values $\{y_1<...<y_d\}=\{h(x_1),...,h(x_m)\}$ are **uniformly spread** in $[0,1]$.
On average, they divide the interval into $d+1$ equal pieces of width $1/(d+1)$, so $E[y_1]=1/(d+1)$, which means $d=1/E[y_1]=1$.

![[FM spread.png|400]]

>[!Example]
>Stream: $3,1,5,3,1,1,1,3,5,7,1,3$
>![[FM example.png|500]]
>
>- $d=4$
>
>The estimate is the minimum hash value that appears for the values in the stream (i.e. $3\to0.125$), then we do $1/0.125-1=7$.

### FM analysis
Let $y_1<y_2<...<y_d$ be the $d$ distinct values in $\{h(x_1),...,h(x_m)\}$, then:
$$E[y_1]=1/(d+1)$$
$$\begin{align}
E[y_1]&=\\
&=\int_0^1 P(y_1\geq\lambda)d\lambda\quad\text{Alternative definition of mean}\\
&=\int_0^1 P(\forall x_i:h(x_i)\geq\lambda)d\lambda\quad\text{Because }y_1\leq h(x_i)\forall i\in[m]\\
&=\int_0^1 (1-\lambda)^dd\lambda\quad\text{Because each }h(x_i)\text{ is uniform and there are just }d\text{ distinct }h(x_i)\\
&=-\frac{(1-\lambda)^{d+1}}{d+1}\Bigg|_0^1\\
&=1/(d+1)
\end{align}$$

The algorithm returns $\hat d=1/y_1-1$ as an estimate of $d$, we know that $d=1/E[y_1]-1$, but $E[1/y_1]\neq E[y_1]$, so the estimator is **biased**.

The fix is that if $y_1$ has a **small variance**, then $1/y_1$ will also not fluctuate much, one can also prove that $Var[y_1]\leq E[y_1]^2$.

This allows us to apply the [[09 - Concentration bounds#The mean-median trick|mean-median trick]]: for any desired error $\epsilon$ and failure probability $\delta$, if we build $O(\epsilon^{-2}\log (1/\delta))$ independent instances of the FM sketch then we can probably compute a RV $y'$ such that:
$$P\left(\left|y'-\frac{1}{d+1}\right|>\frac{\epsilon}{d+1}\right)\leq\delta$$
The estimate of $d$ that we output is $\hat d=1/y'-1$.

It is possible to show that $\hat d=1/y'-1$ is a $(1\pm4\epsilon)$-approximation of $d$.

**Theorem**
Choose any desired error $\epsilon$ and failure probability $\delta$, by running $O(\epsilon^{-2}\log(1/\delta))$ independent instances of the FM sketch, we can return an estimator $\hat d$ such that:
$$P(|\hat d-d|>\epsilon\cdot d)\leq\delta$$
Where $d$ is the number of distinct elements in the stream.

#### Issues with the idealized FM algorithm
**Real numbers are infinite**
A hash outputting a real in $[0,1]$ can't be stored exactly, the fix is to approximate reals with fraction.
Map integers $h':[n]\to[q]$ and use $h(x)=h'(x)/q$, for large enough $q$, the induced error is negligible.

**A dully-uniform hash over $[n]$ requires too much space**
Storing a lookup table for all $n$ values takes $O(n)$ space, the fix is to use pairwise independence which is a weaker and cheaper condition (and it suffices).

### Bottom-k algorithm
Instead of keeping only the single minimum hash $y_1$, in this algorithm we **keep the $k$ smallest hash values**, and since $y_k\approx k/(d+1)$ estimating $d$ from $y_k/k$ has a **smaller variance** than estimating from $y_1$ alone.
$$y_k=\sum_{i=2}^k(y_i-y_{i-1})$$
![[FM spread.png|400]]
Intuitively, $y_k$ is a sum of $k$ independent gaps, each with mean $1/(d+1)$, so averaging $k$ terms reduces variance by a factor of $k$ (like the [[09 - Concentration bounds#Boosted Chebyshev's bound|boosted Chebyshev's trick]]).

```
initialization():
	h = pairwise independent function from [n] to reals in [0,1]
	k = ceil(24*epsilon**-2)
	s = {}

new_stream_element(x):
	insert h(x) into S
	if (|S| > k): remove max(S) from S

estimate_distinct():
	if |S| < k:
		return |S|
	else:
		return k/max(S)
```

>[!Example]
>Stream: $3,1,5,3,1,1,1,3,5,7,1,3$
>![[FM example.png|500]]
>
>- $d=4$
>
>The final state, considering $k=3$ is: $S=\{0.125,0.183,0.745\}$, $|S|=k=3$, then since $|S|=k$:
>$$\hat d=\frac{k}{\max(S)}=\frac{3}{0.745}\approx4.03$$
>
>Which is way closer to the real $d$.

**Theorem**
For any desired error $0<\epsilon\leq1/2$ and failure probability $\delta>0$, we can aggregate $O(\log(1/\delta))$ independent instances of the bottom-k algorithm into a sketch of size:
$$O(\epsilon^2\log(1/\delta))\text{ words}$$
which allows us computing an estimator $\hat d$ such that:
$$P(|\hat d-d|>\epsilon\cdot d)\leq\delta$$

### LogLog algorithm
Real companies use descendant of the **LogLog** algorithm.

```
initialization():
	h = pairwise independent function from [n] to 64-bits integers
	L = 0

new_stream_element(x):
	L = max{L, leadin_zeros(h(x)}

estimate_distinct():
	return 0.783 * 2^L
```

>[!Example]
>Stream: $3,1,5,3,1,1,1,3,5,7,1,3$
>![[LogLog example.png|500]]
>
>- $d=4$
>
>Estimate the leading zeros for each relevant element:
>- $1\to1$
>- $3\to2$
>- $5\to2$
>- $7\to0$
>
>Final $L=2$.
>
>Estimate $\hat d=0.783\cdot2^L=0.783\cdot2^2\approx3.13$.
>>Less accurate than bottom k, but uses only a single integer $L$.


The intuition why this works is that in a stream of **random binary hash values**:
- $1/2$ of the values will start in $0$
- $1/4$ will start in $00$
- $1/8$ will start in $000$
- $...$

Therefore, if the "rarest" event we see is a hash starting in $L$ zeros, it is statistically likely that we've seen approximately $2^L$ elements.

The correction factor $\approx 0.783$ is needed because this simplistic intuition tends to over-estimate the real count.

**Another intuition connected to out idealized FM**:
- Our idealized algorithm returns $1/y-1$ where $y\in[0,1]$
- To simulate a number in $[0,1]$, we can draw integers in $[0,2^N)$ and divide them by $2^N$
- Then, $y=h(x_i)/2^N$, where $h(x_i)\in[0,2^N)$ is the smallest hash we have seen, and:
$$1/y-1\approx1/y=2^N/h(x_i)$$
- But the smallest hash we have seen is also the one with the largest number $L$ of leading zeros, so:
$$h(x_i)\approx2^{N-L}$$
- Hence, our estimate is $2^N/h(x_i)\approx2^{N-L}=2^L$
- The correction factor $\approx 0.783$ serves to turn those approximations signs $\approx$ into equalities (in expectation)

**Space complexity**
The algorithm only needs to store $L$, since $d\approx2^L$, we have $L\approx\log_2d$, which takes $\log\log d$ bits, this is _doubly logarithmic_ in $d$.

>[!Tip] Hashing
>While Flajolet and Martin assumed a fully-uniform hash function, it can be shown that **pairwise independence is sufficient**.

|     **Algorithm**     |    **Sketch size**     |            **Output estimate**             |                        **Hash function**                        |
| :-------------------: | :--------------------: | :----------------------------------------: | :-------------------------------------------------------------: |
|      _Bitvector_      |        $n$ bits        |                    $d$                     |                          deterministic                          |
| _Self-balancing tree_ |      $O(d)$ words      |                    $d$                     |                          deterministic                          |
|       _MinHash_       |   $O(\log n)$ bits*    | $d \pm \epsilon \cdot n$ w.p. $1 - \delta$ | Approx. Min-Wise ind. $+O(\epsilon^{-2} \log(1/\delta))$ words* |
|    _Idealized FM_     |   $O(\log n)$ bits*    | $d \pm \epsilon \cdot d$ w.p. $1 - \delta$ |                     Uniform $+O(n)$ words*                      |
|     _Bottom-$k$_      |   $O(\log n)$ bits*    | $d \pm \epsilon \cdot d$ w.p. $1 - \delta$ |               Pairwise independent $+O(1)$ words*               |
|       _LogLog_        | $O(\log \log d)$ bits* | $d \pm \epsilon \cdot d$ w.p. $1 - \delta$ |               Pairwise independent $+O(1)$ words*               |
>* Assuming constant $\epsilon$, $\delta$; otherwise multiply sketch size by $O(\epsilon^{-2} \log(1/\delta))$.

