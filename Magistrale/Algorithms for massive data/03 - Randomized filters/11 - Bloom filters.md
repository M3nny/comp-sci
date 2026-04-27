Suppose that we have a large set $S$ stored somewhere slow (e.g. a hard disk), and we frequently receive membership queries: "is $x$ in $S$?" reading from disk every time is expensive.

A **filter** is a tiny, fast data structure you keep in memory that can answer "definitely not in $S$" instantly saving us the costly disk lookup in the common case.

A filter is a **randomized data structure** that encodes a set of $m$ elements drawn from a universe of size $n$.

Its defining features are:
- Supports _insert_ and _membership_ queries (and sometimes delete)
- Membership queries can fail but only in one direction it **may contain false positives**, but it **will never contain false negatives** this one-sided error model is what makes filters useful in practice
- The **false positive probability** $\delta$ is a parameter you set at construction time
- Filters use remarkably little space: $O(m \cdot log(1/\delta))$ bits, regardless of the universe size $n$, this breaks the information-theoretic lower bound for exact set membership

>[!Tip] Space reduction from accepting false positives
>Storing which $m$ elements out of a universe of n were inserted requires at least $\log_2(C(n, m)) \approx m\cdot\log(n/m)$ bits, which grows with $\log n$.
>A filter avoids this by accepting a small FP probability, **cutting the space down** to just $m\cdot\log(1/\delta)$ bits, which is independent of $n$.
>
>When $\delta$ is a small constant (e.g. $\delta=0.0001$), it occupies just $O(m)$ bits, regardless of how large the universe is, if we wanted high precision (e.g. $\delta=n^{-c}$), the filter uses $O(m\log n)$ bits and solves membership correctly with high probability.

### Partitioned bloom filters
We are going to present the **partitioned Bloom Filter** variant, which fixes a mathematical error present in the original paper and allows for a cleaner analysis.

Supported operations by a bloom filter are:
- **Insert(x)**: add $x$ to the set, can be called at most $m$ times
- **Membership(x)**: returns true if $x$ was inserted, possibly true even if it wasn't (false positive), but never false if $x$ was inserted (no false negatives)
- Does not support delete

At **construction time** we are going to specify the maximum set size $m$ and the desired false positive probability $\delta$, and as long as we insert at most $m$ elements, the FP probability is guaranteed to be $\leq\delta$.

>[!Attention]
>For the analysis, we are going to assume **fully uniform** hash functions.
>
>As established in [[10 - Hashing#Fully uniform hashing|fully uniform hashing]], these require impractical amounts of space. However, it has been proven that $O(1)$-wise independent hash functions work just as well in practice, so this is a simplification for the sake of clean math.

#### Construction
The data structure is a **bitvector** BF of length $M$ bits, initialized to all zeros, which is divided into $k$ equally-sized contiguous blocks, each of length $M/k$ bits.

There are $k$ independent fully-uniform hash functions $h_1,...,H_k$, where $h_i$ maps any element $x$ to an index within the $i$-th block specifically:
$$h_i:[n]\to\left[(i-1)\frac{M}{k},i\frac{M}{k}\right)$$
![[Partitioned bloom filter.png|500]]

This partitioning is what distinguishes this variant from the original Bloom filter (where all hash functions could write to any position, complicating the analysis).

#### Insertion
We compute all $k$ hash values and set those $k$ positions in the bitvector to $1$.
Previously-set bits stay $1$, nothing is ever reset to $0$.
```
Insert(x):
	for i = 1 to k:
		BF[h_i(x)] = 1
```

![[Bloom filter insertion.png|500]]

#### Membership
Membership works by checking all $k$ positions pointed to by the hash functions.
If **all** of them are $1$, report "yes", otherwise if **any** is $0$, report "no."
```
Membership(x):
	return BF[h_1(x)] AND BF[h_2(x)] AND ... AND BF[h_k(x)]
```

The **will never be false negatives** since when $x$ was inserted, we set all $k$ of its positions to $1$, and since bits never get flipped back to $0$, those positions will be $1$ when we query $x$ later.

**False positives may happen** when different elements are inserted and their hash positions overlap.
Bits set for element $y$ might accidentally cover all $k$ positions for element $z$, even though $z$ was never inserted.

### Computing the FP probability
We're now going to see what is $\mathbb P(FP)$ as a function of $M,k$ and $m$.

**Probability that a single bit is $1$**
Considering any position $i$ in block $j$, it can only be set by $h_j$ (since hash functions are partitioned).

A given inserted element $x_i$ sets position $i$ with probability $k/M$, since $h_j$ maps uniformly to $M/k$ positions in its block, so $\mathbb P(h_j(x_i)=i)=k/M$.
The probability that $x_i$ does not set position $i$ is: $1-k/M$.

Since all $m$ inserted elements act independently, the probability that none of them set position $i$ is:
$$\mathbb P(BF[i]=0)=(1-k/M)^m$$
**Asymptotic simplification**
We rewrite this probability as:
$$\begin{align}
(1-k/M)^m&=\left(\boxed{\left(1-\frac{1}{M/k}\right)^{M/k}}\right)^{mk/M}\\
&\to\lim_{x\to\infty}(1-1/x)^x=\boxed{e^{-1}}\qquad (x=M/k)\\
&=(e^{-1})^{mk/M}\\
&=e^{-mk/M}
\end{align}$$
Hence we can write:
$$\begin{align}
\mathbb P(BF[i]=1)&=1-\mathbb P(BF[i]=0)\\
&=1-e^{-mk/M}
\end{align}$$

**False positive probability**
Finally, an element $x\notin S$ is a false positive iff all $k$ of its hash positions happen to be $1$, and since the $k$ hash functions are independent and each bit is $1$ with the probability derived above we get:
$$\mathbb P(FP)=(1-e^{-mk/M})^k$$

#### Optimizing the parameters
We want to choose $M$ (total bits) and $k$ (number of hash functions) to minimize $\mathbb P(FP)$ for a given $m$ and desired false positive rate $\delta$.

It can be shown that this quantity is minimized for $k=(M/m)\ln 2$, and by replacing this value in the above probability, we obtain:
$$\mathbb P(FP)=(1/2)^{(M/m)\ln 2}$$
To conclude, we set $\mathbb P(FP)=\delta$ (our desired probability) and obtain:
- $k=\log_2(1/\delta)$
$$\begin{align}
M&=m\cdot\log_2(e)\cdot k\\
&=m\cdot\log_2e\cdot\log_2(1/\delta)\\
&=O(m\log(1/\delta))
\end{align}$$
In other words: both the number of hash functions (= **query time**) and **space** are proportional to $\log(1/\delta)$.

An **interesting structural observation** is that when the filter is at **full capacity** (exactly $m$ insertions), each bit is $0$ with probability $e^{(−mk/M)} = e^{(−\ln 2)} = 1/2$.

So at full capacity, **exactly half the bits are set on average**, the bitvector is a uniform random bitvector.

This is not a coincidence: **a uniform bitvector has maximum entropy**, meaning the filter has packed as much information as possible into its $M$ bits.
>The Bloom Filter is information-theoretically optimal in this sense.

#### Final result
A partitioned Bloom Filter for a set of at most $m$ elements, with desired false positive probability $0 < \delta < 1$:
- Uses $O(m \cdot \log(1/\delta))$ bits of **space**,
- Supports **insert** in $O(\log(1/\delta))$ time,
- Supports **membership** in $O(\log(1/\delta))$ time with false positive probability $\leq\delta$ and _zero false negatives_

