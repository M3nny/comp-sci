In a standard [[11 - Bloom filters|Bloom filter]], bits never go back to $0$ once they have been set because we don't know how many elements $x\in S$ affected that bit.

If we wanted to delete element $x$, we'd want to set $BF[h_i(x)]$ back to $0$ for each $i$.
But we can't safely do this, those bits might have been set to $1$ by other elements too.

Resetting them would corrupt information about elements that are still in the set, causing **false negatives** (saying something isn't in $S$ when it actually is).
There is no safe way to "undo" a single insertion when multiple elements may share a position.

### Replacing bits with counters
Instead of a bitvector, we could use an **array of small integers** (counters), such that when inserting $x$, we **increment** the relevant counters rather than setting bits to $1$, then when we delete $x$, we **decrement** them.

This introduces a few challenges:
- **Overflow and underflow of a counter**: this is easily fixed by clamping values with `min()` and `max()`
- **False negatives**: when an overflow happens it gets clamped and we lose the real count on how many elements mapped to that counter, potentially causing a false negative when querying a still-present element

The **Counting Bloom Filter (CBF)** uses more space than a standard BF (because of integers instead of bits), and introduces a _small false negative probability_ $\mathbb P(FN)>0$.

The data structure mirrors the [[11 - Bloom filters#Construction|partitioned Bloom filter]] exactly, with bits replaced by integers.

An array of $M$ integers, each using $t$ bits, so each counter can hold values in $[0,2^t)$, this occupies a total space of $M\cdot t$ bits.
The array is split into $k$ equal blocks, and each of $k$ hash functions $h_i$ maps elements into the $i$-th block.
>$M$, $k$, and $t$ will be **tuned** based on the desired $\mathbb P(FP)$ and $\mathbb P(FN)$.

We'll introduce the various methods with the following example, considering $t=2$, so that every $CBF[i]$ can hold numbers in $[0,4)$:
![[Partitioned bloom filter.png|500]]

### Insertion
We increment each of the $k$ counters, and the `min()` prevents an overflow from happening.
```
Insert(x):
	for i = 1 to k:
	    CBF[h_i(x)] = min(CBF[h_i(x)] + 1, 2^t − 1)
```

![[CBF insertion.png|500]]

### Membership
The logic is identical to the [[11 - Bloom filters#Membership|classical Bloom filter membership]], but this time instead of checking for $1$s, we just check for positives.
```
Membership(x):
	return CBF[h_1(x)] > 0 AND CBF[h_2(x)] > 0 AND ... AND CBF[h_k(x)] > 0
```

### Delete
We decrement each of the $k$ counters, and the `max()` prevents an underflow from happening.
```
Delete(x):
	for i = 1 to k:
	    CBF[h_i(x)] = max(CBF[h_i(x)] − 1, 0)
```

![[CBF delete.png|500]]

### Computing the FP probability
The [[11 - Bloom filters#Computing the FP probability|FP analysis on classical Bloom filters]] applies directly since the behavior is the same as if each $CBF[i]$ was a boolean.
$$\mathbb P(FP)=(1/2)^{M/m}\ln2$$
So:
- $k=\log_2(1/\delta)$
- $M=mk\log_2e=O(m\log(1/\delta))$

### Computing the FN probability
$x\in S$ is a **false negative** only if some counter $CBF[h_j(x)]$ overflowed at some point, causing it to eventually hit $0$ despite $x$ still being in $S$, therefore:
$$\mathbb P(x\text{ is a }FN)\leq\mathbb P(\exists j:CBF[h_j(x)]\text{ overflows})$$

**Overflow probability for a single position $i$**
Fix any counter position $i$, only one hash function $h_j$ can affect it (due to partitioning), then position $i$ overflows if at least $T=2^t$ of the $m$ inserted elements hash to position $i$ under $h_j$.

Each element hashes to position $i$ independently with probability $k/M$, so the positions hit by $h_j$ during insertion are i.i.d. uniform random variables $i_1,...,i_m$ in the block of size $M/k$.

**Fixing $T$ elements that all land on position $i$**
For fixed indices $j_1,...,j_T$, the probability that all $T$ of them hash to position $i$ is:
$$\mathbb P(i_{j_1}=\dotsi=i_{j_T}=1)=\prod_{p=1}^T\mathbb P(i_{j_p}=1)=\left(\frac{k}{M}\right)^T$$
since the i.i.d. variables are independent and each hits position ii i with probability $k/M$.

**Union bound over all choices of $T$ elements**
An overflow means _some_ set of $T$ elements all land on $i$, there are $\binom{m}{T}$ ways to choose which $T$ elements cause it, so by the union bound:
$$\mathbb P(CBF[i]\text{ overflows})\leq\binom{m}{T}\cdot\left(\frac{k}{M}\right)^T$$

**Simplifying the binomial bound**
We are going to use the following useful upper bound for the binomial coefficient:
$$\frac{m}{T} \le \left(\frac{em}{T}\right)^T$$
so:
$$\mathbb{P}(\mathrm{CBF}[i]\text{ overflows}) \le \left(\frac{em}{T}\right)^T \cdot \left(\frac{k}{M}\right)^T \le \left(\frac{emk}{TM}\right)^T$$
now we substitute the optimal $M=mk\log_2e$ derived from the FP analysis:
$$\mathbb{P}(\mathrm{CBF}[i]\ \text{overflows}) \le \left(\frac{emk}{T \cdot mk \log_2 e}\right)^T
= \left(\frac{e}{T \log_2 e}\right)^T
= \left(\frac{e \ln 2}{T}\right)^T$$

**Simplification**
We can assume $t\geq 2$ (i.e. $T=2^t\geq 4$), otherwise $t=1$ means we're using a single bit per counter, which is just a standard Bloom filter with no delete.

For $T\geq 4$, one can verify that $\frac{e\ln 2}{T}\leq\frac{1}{2}$, so:
$$\mathbb P(CBF[i]\text{ overflows})\leq \left(\frac{1}{2}\right)^T=\left(\frac{1}{2}\right)^{2^t}$$
This is _doubly-exponential decay_ in $t$, adding one extra bit to each counter squares the exponent in the probability bound, making overflow vanishingly rare extremely quickly.

**FN probability for element $x$**
Since $x$ has $k$ hash positions $h_1(x),...,h_k(x)$, we apply the union bound overall $k$ of them:
$$\mathbb{P}(x \text{ is a FN}) \le \mathbb{P}(\exists j : \mathrm{CBF}[h_j(x)] \text{ overflows}) \leq k \cdot \left(\frac{1}{2}\right)^{2^t}$$

**Deriving $t$ from the desired $\gamma$**
Set the bound equal to the target FN probability $\gamma$ and solve, recalling that $k=\log_2(1/\delta)$:
$$k \cdot \left(\frac{1}{2}\right)^{2^t} = \gamma  
\implies  
2^t = \log_2\!\left(\frac{k}{\gamma}\right)  
\implies  
t = \log_2 \log_2\!\left(\frac{\log_2(1/\delta)}{\gamma}\right)$$

### Final result
A counting Bloom filter for at most $m$ elements, with desired FP probability $\delta$ and FN probability $\gamma$, built using $k = log_2(1/\delta)$ hash functions:
- Uses $O(m\log(1/\delta)\log\log\left(\frac{\log(1\delta)}{\gamma}\right))$ bits of **space**
- Supports insert and delete in $O(\log(1/\delta))$ **time**
- Supports **membership** in $O(\log(1/\delta))$ time with $\mathbb P(FP)\leq\delta$ and $\mathbb P(FN)\leq \gamma$

