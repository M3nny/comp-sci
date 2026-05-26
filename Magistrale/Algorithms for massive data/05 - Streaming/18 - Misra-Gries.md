**Misgra-Gries (MG) sketch** is **fully-deterministic** (with no randomness at all), and has the opposite one-sided error from [[17 - Count-Min sketch#Count-Min sketch|CMS]], that is, it _never over-estimates_, but may under-estimate by up to $\epsilon\cdot m$.

MG maintains a **hash table** with at most $s$ entries, where each entry maps an element $x$ to an estimated frequency $\tilde f_x$ (like a "VIP list" of elements that have appeared a lot), and elements not in the table are assumed to have frequency $0$.

**Insert**
```
insert(x):
	if x in MS:
		MS[x]++
	else:
		MS.add({(x ,1)})
	
	if (|MS} = s):
		for y in MS:
			MS[y]--
		
	for y in MS:
		if MS[y] = 0:
			MS.delete({(y, 0)})
```
In words it is:
1. If $x$ is already in the table, increment its count by $1$, if $x$ is new, add it with count $1$
2. If the table now has exactly $s$ entries (it's full), decrement every entry's count by $1$, then remove any entry whose count has dropped to $0$

```
estimate_frequency(x):
	if x in MS:
		retun MG[x]
	else:
		return 0
```

>[!Example]
>Stream: $17,5,17,81,5,17$
>- See 17 -> $MG = \{(17,1)\}$
>- See 5 -> $MG = \{(17,1), (5,1)\}$
>- See 17 -> $MG = \{(17,2), (5,1)\}$
>- See 81 -> $MG = \{(17,2), (5,1), (81,1)\}$, now the table is full ($s=3$)
>    - **Decrement all**: every count drops by $1$ → $\{(17,1), (5,0), (81,0)\}$ -> remove zeros -> $MG = \{(17,1)\}$
>- See 5 -> $MG = \{(17,1), (5,1)\}$
>- See 17 -> $MG = \{(17,2), (5,1)\}$
>
>Estimates:
>- $ef(17)=2$
>- $ef(5)=1$
>- $ef(81)=0$
>- $ef(42=0)$

In the previous example with $m=6$ and $m/s=2$, the guarantee $f_x-m/s\leq\tilde f_x\leq f_x$ holds for every case.

Why it **never over-estimates** ($\tilde f_x\leq f_x$)?
A counter for $x$ is only ever incremented when $x$ actually appears in the stream, so $MG[x]$ counts a subset of the true occurrences.

Why the **under-estimate is bounded** ($\tilde f_x\geq f_x-m/s$)?
We can imagine expanding the table into a multiset $MG'$ where element $x$ appears $\tilde f_x$ times, this multiset is always a sub-multiset of the stream (since we only add copies when the element is seen).
Each "decrement all" event removes exactly $s$ copies from $MG'$ since $|MG'|\leq m$, this can happen at most $m/s$ times, therefore, each individual counter can be decremented at most $m/s$ times total, proving the lower bound.

**Choosing the parameter $s$**
Set $s=\lceil\epsilon^{-1}\rceil$, then the error bound becomes $f_x-\epsilon\cdot m\leq\tilde f_x\leq f_x$, and the space is $O(\epsilon^{-1})$ words.

**Time complexity**
- _Frequency query_: with a hash it is $O(1)$, with a deterministic self-balancing tree (e.g. AVL) it is $O(\log\epsilon^{-1})$
- _Insert_: we scan the whole table to decrement, so it is $O(\epsilon^{-1})$, but by using nested doubly-linked lists and a hash map, inserts can be done in $O(1)$

**Theorem**
For any $\epsilon>0$ and stream length $m$, MG uses $O(\epsilon^{-1})$ words, and for any element $x$ gives an estimate satisfying $f_x-\epsilon\cdot m\leq \tilde f_x\leq f_x$, both insert and query run in $O(1)$ expected time.
>If we want additive error at most $k$, use $O(m/k)$ space.

|     Technique      |          Space (words)           |                $\mathbb P$ (under-estimate)                |                              $\mathbb P$ (over-estimate)                              |
| :----------------: | :------------------------------: | :--------------------------------------------------------: | :-----------------------------------------------------------------------------------: |
|      Sampling      | $O(\epsilon^{-2}\log(1/\delta))$ | $\mathbb P(\|\tilde f_x-f_x\|>\epsilon\cdot m)\leq \delta$ | $\mathbb P(\|\tilde f_x-f_x\|>\epsilon\cdot m)\leq \delta$ (same error on both sides) |
|  Count-Min sketch  | $O(\epsilon^{-1}\log(1/\delta))$ |               $\mathbb P(\tilde f_x< f_x)=0$               |                 $\mathbb P(\tilde f_x>f_x+\epsilon\cdot m)\leq\delta$                 |
| Misra-Gries sketch |        $O(\epsilon^{-1})$        |       $\mathbb P(\tilde f_x<f_x-\epsilon\cdot m)=0$        |                             $\mathbb P(\tilde f_x>f_x)=0$                             |

### Drawbacks of MG compared to CMS
Even though MG looks superior on the comparison table (same space, no over-estimation, deterministic), it has many weaknesses:
- **Not linear**: CMS satisfies `CMS(stream1 + stream2) = CMS(stream1) + CMS(stream2)` (we can merge sketches by just adding the matrices). MG does not have this property, which matters a lot in distributed or parallel settings
- **Not hardware-friendly**: CMS is just a matrix of integers, which is easy to implement in custom hardware, but MG requires a dynamic hash table/linked-list structure
- **Deletions not supported**: MG can't handle a stream where elements are removed, only inserted

MG uses less space than CMS, but it uses pointers, CMS on the other hand is a matrix of counters.
We stored both using words, but actually **counters are more amenable to compression**.

After all, CMS is already approximated, at this point we could **approximate the counters** as well, in this way we could fit more columns in CMS for the same memory budget, which would improve accuracy.

### Morris approximate counting
Robert Morris was working with machine that had limited memory, and he had to deal with numbers in the order of $10^9$ whilst having the register size of only $1$ byte.
Exact counting was impossible, and his idea was to count approximately using exponentially fewer bits.

Instead of storing the number $y$ directly (which takes $\log_2 y$ bits), **store the exponent** $x$ such that $2^x\approx y$ (which takes only $\log\log y$ bits).
- If $y$ is a power of $2$, store $x=\log_2 y$ exactly, which has zero error
- If not, store $x=\lceil\log_{1+\epsilon}y\rceil$, this takes $\log\log y+O(\epsilon^{-1})$ bits and gives $(1+\epsilon)^x$ as the estimate

The problem is that this **only works for a fixed value** $y$, but we're on a stream where the count $y$ keeps growing.

**Morris' algorithm**
- `initialization()`: set register $X=0$
- `increment()`: with probability $2^{-X}$, do $X++$ (otherwise do nothing)
- `estimate()`: return $2^X-1$

The intuition is that $X$ is the exponent in our approximate representation, and instead of trying to update the exponent precisely on each increment, we do it randomly with the right probability so that, on average, the estimate stays correct.

When $X$ is small, $2^{-X}$ is close to $1$, so we increment almost every time (exact counting for small numbers), and when $X$ is large, we only increment occasionally.

#### Unbiasedness
**Lemma**: after $m$ calls to `increment()`, the expected value of the estimate equals the true count:
$$E[2^X-1]=m$$

Let $X_i$ be the register after $i$ calls to `increment()`, we prove it by induction on $i$:
- **Base case** ($i=0$): $X_0=0$, and the estimate is $2^{X_0}-1=0=i$ which is correct
- **Inductive step**: assume $E[2^{X_i}]=i+1$, we want to show $E[2^{X_{i+1}}]=i+2$

Using the law of total expectation (conditioning on $X_i=j$):
$$E[2^{X_{i+1}}]=\sum_{j=0}^\infty P(X_i=j)\cdot E[2^{X_{i+1}}|X_i=j]$$


Given $X_i=j$, the next step either increments (probability $2^{-j}$, giving $X_{i+1}=j+1$) or doesn't (probability $1-2^{-j}$, giving $X_{i+1}=j$), so:
$$E[2^{X_{i+1}}|X_i=j]=2^{-j}\cdot 2^{j-1}+(1-2^{-j})\cdot 2^j=2^j+1$$
Substituting back:
$$\begin{align}
E[2^{X_{i+1}}]&=\sum_{j=0}^\infty P(X_i=j)\cdot E[2^{X_{i+1}}|X_i=j]\\
&=\sum_{j=0}^\infty P(X_i=j)\cdot(2^j+1)\\
&=E[2^{X_i}]+1\\
&=(i+1)+1\\
&=i+2
\end{align}$$
So $E[2^X-1]=m$, proving that the estimator is unbiased.

#### Variance bound
**Lemma**: $\text{Var}[2^X-1]\leq m^2/2$

This is the bound needed to apply the [[09 - Concentration bounds#The mean-median trick|mean-median trick]], if variance is $O(m^2)$ and the mean is $m$, then running $O(\epsilon^{-2}\log(1/\delta))$ independent parallel instances and taking the median of means gives a $(1\pm\epsilon)$-approximation with failure probability $\leq\delta$.

#### Final result
Since $E[2^X-1]=m$, the register $X$ typically has value around $\log_2 m$, so storing $X$ takes only $O(\log\log m)$ bits on average (compared to $O(\log m)$ bits for an exact counter).

**Final theorem**
By running $O(\epsilon^{-2}\log(1/\delta))$ independent Morris instances and combining via mean+median, we use in total:
$$O(\epsilon^{-2}\log(1/\delta)\cdot\log\log m)$$
expected bits of space, and with probability $\geq 1-\delta$ the estimate $\hat Y$ satisfies:
$$P(|\hat Y-m|\geq m\cdot\epsilon)\leq \delta$$
In practice, using just $1$ byte we can count medium-size numbers with decent precision (enough for CMS).
