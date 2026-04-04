In this chapter we are going to figure out how to **speed up count queries** when using [[07 - Burrows-Wheeler transform|BWT]], that is **backward search**.

### Backward search
Let's consider the following BWT matrix:
![[FM backward search.png|400]]

We have the range $[5,9]$ of string `ab`, and want to find the range of string `aab`.
In the BWT those `a` that we are interested in are precisely all the `a` that are followed by `ab`, hence they are all occurrences of our initial range, plus those `a`.

We find those `a`'s via [[07 - Burrows-Wheeler transform#The LF property|LF mapping]], in fact we can see that by looking at the $L$ column, the range is $[3,4]$.

The algorithm is:
1. Start from the range $[1,18]$ of the empty string `""`
2. Search the characters of our pattern $P$ right to left (backwards)
3. At the end, we'll have the range $[\ell,r]$

From which:
- $count(P)=r-\ell+1$
- $locate(P)=SA[\ell,...,r]$

In the **naive implementation**, when extending the current range $[i,j]$, with a character $a$, the range could contain _many_ $a$'s in the BWT, potentially $\Theta(n)$ (all of them), and we don't want to apply LF to each one individually.

In fact we don't need to, it is enough to **apply LF only to the first and last $a$ in the current range**.
This is because LF mapping preserves order within a character class, hence the entire block of $a$'s in the current range maps to a contiguous block in $F$, for this we only need the the endpoints to define the new range.

Now we are left with two problems:
- **Sub-problem 1**: find the rank of the first and last $a$ in the current range $[i,j]$.
	This is due to the fact that we need to know which occurrence of $a$ in $BWT$ we are dealing with.
	
	This is exactly a rank query on the $BWT$ string, for example, in order to retrieve the first and last `a` in $BWT[4,13]$:
	-  $BWT.rank_a(i-1)=BWT.rank_a(4-1)=2$
	- $BWT.rank_a(j)=BWT.rank_a(13)=5$
	
	Both are computed in $O(\log\sigma)$ with the [[06 - Wavelet trees|wavelet tree]].

- **Sub-problem 2**: compute the LF mapping
	To find where the $k$-th $a$ in $BWT$ lands in $F$, we use a precomputed array $C$, where $C[c]$ equals to the position in $F$ of the first occurrence of character $c$, minus $1$ (due to the $\$$ sign).
	
	So $C[\$]=0$, $C[a]=1$, $C[b]=9$, in this way we know that the $k$-th $a$ in $BWT$ maps to row $C[a]+k$..
	
	This additional array $C$ takes $\Theta(\sigma\log n)$ bits of space and answers LF in $O(1)$ time.

Putting it all together, the algorithm is:
```
m = |P|
l = 1
r = |S|
for i=m down to 1 do:
	c = P[i]
	l = C[c] + BWT.rank_c(l-1) + 1
	r = C[c] + BWT.rank_c(r)
return r - l - 1
```

Each step costs $O(\log\sigma)$, which is dominated by the rank query, and since there are $m$ characters in the pattern, the total time for counting is $O(m\log\sigma)$.

### The FM-index
Combining everything, the [[06 - Wavelet trees|wavelet tree]] on the [[07 - Burrows-Wheeler transform|BWT]] for space and rank queries, the $C$ array for [[07 - Burrows-Wheeler transform#The LF property|LF mapping]], the [[05 - Compressed suffix array#Locate query|sampling of SA]] and $SA^{-1}$ for locate/extract queries, gives the **FM-index**.

The **one difference from the CSA** is that $\psi[i]$ on the FM-index takes $O(\log\sigma)$ per step (whereas it was $O(1)$ per step in the CSA).
This means that we need to sample SA more frequently, specifically, sampling one out of every: $T=\frac{(\log n)^{1+\epsilon}}{\log\sigma}$ values of $SA$ and $SA^{-1}$ gives:
- The sampling takes $o(n\log\sigma)$ bits
- Each locate call walks at most $T$ steps of $\psi$, each costing $O(\log\sigma)$, so the cost per occurrence is $O((\log n)^{1+\epsilon})$

The **FM-index theorem**:
By choosing any constants $\epsilon>0$ and $a<1$, let $k=\lfloor\max\{0,a\log_\sigma n-1\}\rfloor$.
The FM-index uses $nH_k+o(n\log\sigma)+\Theta(\sigma\log n)$ bits of space, and supports:
- $count(P)$ queries in time $O(m\log\sigma)$
- $locate(P)$ queries in time $O(m\log\sigma+occ\cdot(\log n)^{1+\epsilon})$
- $extract(i,\ell)$ queries in time $O((\log n)^{1+\epsilon}+\ell\log\sigma)$

If $\sigma=O(1)$, the FM-index uses $nH_k+o(n)$ bits of space and supports:
- $count(P)$ queries in time $O(m)$
- $locate(p)$ queries in time $O(m+occ\cdot(\log n)^{1+\epsilon})$
- $extract(i,\ell)$ queries in time $O((\log n)^{1+\epsilon}+\ell)$

The FM-index **achieves both compressed space and optimal counting speed simultaneously**.
