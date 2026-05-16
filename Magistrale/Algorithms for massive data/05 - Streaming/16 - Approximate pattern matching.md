The **Hamming distance** between two strings of the same length is the number of positions where they differ:
$$HD(A,b)=\sum_{i=1}^n(A[i]\neq B[i])$$
This chapter's goal is to compute $HD(A,B)$ exactly w.h.p., provided that $HD(A,B)\leq k$ for some fixed parameter $k$.

Note that the **normalized HD** $\frac{HD(A,B)}{n}\in[0,1]$, whilst $HD(A,B)$ is an integer.

### Sketch for HD
We want to **reduce Hamming distance to exact matching** by splitting both input strings into interleaved subsequences and checking each pair.

$A_{i,d}$ is the subsequence of $A$ formed by taking every $d$-th character starting at position $i$:
$$A_{i,d}=A[i]\cdot A[i+d]\cdot A[i+2d]\dotsi$$
So with $d=2$ we split $A$ into two subsequences: the characters at odd positions, and those at even positions.

The **key property** is that if there is exactly one mismatch at position $j$ between $A$ and $B$, then that mismatch lands in exactly one of the $d$ subsequences (the one that "owns" position j).
So $A_{i,2} \neq B_{i,2}$ for exactly one value of $i$, and all other pairs are equal, hence counting mismatching pairs gives us $HD(A,B)$ exactly.

This **fails with two or more mismatches**.
For example, let's take `A = abRacaDabra` and `B = abBacaAabra` with $HD=2$.

With $d=2$ both mismatches land in the same subsequence $A_{1,2}$ because the distance between them $7-3=4$ is divisible by $d=2$, the result is that we get only one mismatching pair, but $1\neq HD=2$.
$$\underbrace{\begin{rcases}A_{1,2}=\text{arcdba}\\B_{1,2}=\text{abcaba}\end{rcases}\neq\qquad\begin{rcases}A_{2,2}=\text{baaar}\\B_{2,2}=\text{baaar}\end{rcases}=}_\text{1 mismatch}$$

>[!Note]
>When $d$ divides the distance between two mismatches, they both fall into the same subsequence, hiding one of them.
>The number of mismatching pairs undercounts the true $HD$.

The fix is to use $d=3$, now $3$ does not divide $4$, so the two mismatches land in different subsequences, and counting gives $HD=2$ correctly.

When building the sketch of $A$ we don't know where the mismatches will be ($B$ isn't seen yet), so **we can't pick the right $d$ in advance**.

The solution is to **use all primes** up to the $\log n$-th prime, the key mathematical fact is that **any integer distance $|j-i|\leq n$ has at most $\log_2n$ distinct prime divisors**.

So, if we **try all primes** in the set $P=\{2,3,5,7,11,...,\log n-th\text{ prime}\}$, _at least one of them is guaranteed not to divide the distance_ between any pair of mismatches.
That "good" $d$ will correctly separate all mismatches into distinct subsequences.

The **sketch** of $A$ is:
$$sketch(A)=(\kappa(A_{1,d}),\kappa(A_{2,d}),...,\kappa(A_{d,d}))_{d\in P}$$
For each prime $d$ in $P$, store the [[10 - Hashing#Polynomial hashing|polynomial hash]] of each of the $d$ subsequences.
The total number of hashes is the sum of the first $\log n$ primes (where $n$ is the length of each string), which is $O(\log^2n\cdot\log\log n)$ words.

We can explain the previous result by counting the total number of hashes stored:
$$\sum_{d\in P}d=2+3+5+7+11+\dotsi+p_{\log n}$$
where $p_{\log n}$ is the $\log n$-th prime, and by the prime number theorem, the $k$-th prime is approximately $k\cdot\ln k$, so the $\log n$-th prime is roughly $\log n\cdot \log\log n$, the sum of the first $\log n$ primes is then approximately:
$$\sum_{k=1}^{\log n}k\cdot\ln k\approx\frac{(\log n)^2}{2}\cdot\log\log n=O(\log^2n\cdot\log\log n)$$

For $k=1$ the **algorithm** is:
1. For each $d\in P$, count $c_d$ = number of indices $i$ where $\kappa (A_{i,d})\neq\kappa(B_{i,d})$
2. Let $c=\max\{c^d:d\in P\}$
3. If $c\leq 1$, return $c$, otherwise return "$HD>1$"

Why does it work:
- $HD=0$: all hashes match for every $d$, so $c=0$
- $HD=1$: exactly one subsequence mismatches for every $d$, so $c=1$
- $HD>1$: there exists some $d\in P$ that doesn't divide any mismatch-distance, so for that $d$ the mismatches are separated and $c>1$

All three cases are distinguishable correctly w.h.p.
>w.h.p comes from the polynomial hashing, there's a small chance of a false hash collision.

>[!Example]
>Let's use $n=8$, $k=1$, $P=\{2.3\}$ (first two primes, since $\log_28=3$).
>Strings: $A=\text{abracada}$, $B=\text{abrecada}$ (one mismatch at position $4$).
>
>**Build the sketch of $A$** for each $d\in P$:
>- $A_{1,2}=\text{arcd}$
>- $A_{2,2}=\text{bcaa}$
>- $A_{1,3}=\text{aaa}$
>- $A_{2,3}=\text{bca}$
>- $A_{3,3}=\text{rc}$
>The sketch is composed by hashing each one of these, so $5$ hashes.
>
>**Build the sketch of $B$** in the same way:
>- $B_{1,2}=\text{arcd}$
>- $B_{2,2}=\text{beaa}$ $\leftarrow$ mismatch
>- $B_{1,3}=\text{aea}$ $\leftarrow$ mismatch
>- $B_{2,3}=\text{bca}$
>- $B_{3,2}=\text{rc}$
>  
> Now we count the mismatching pairs for each $d$.
> - $c_2=1$
> - $c_3=1$
> 
> Now we take the maximum count of mismatches:
> - $c=\max(c_2,c_3)=\max(1,1)=1=HD$
>   
>The max across all $d$ is what saves us: even if some primes are "bad" for a particular pair of mismatches, at least one prime in $P$ is guaranteed to be "good" and correctly separate them, and that good $d$ contributes the highest count.

### Turning the sketch into a streaming algorithm
We have to use this sketch on a stream, where pattern arrives first, then text character by character.

The **idea** is that when a new text character $x_j$ arrives, the sub-streams $x_{i,d}$ are updated, but only one character in each sub-stream changes, so instead of rerunning everything:
1. **Copy the stream** $|P|=\log n$ times (one copy per prime $d$)
2. **Sub-divide each copy**: for prim $d$, split the copy further into $d$ sub-streams $x_{i,d}$ (one per residue class), each character goes to exactly one sub-stream per copy
3. **Run P&P on each sub-stream pair** (text sub-stream vs pattern sub-stream): there are at most $d$ P&P instances per prime $d$
![[Approximate pattern matching 1.png|600]]
The character $\text b$ arrives:
![[Approximate pattern matching 2.png|600]]

There are at most $d$ P&P instances per prime, summed over all primes in $P$:
- Number of primes: $\log n$
- Largest prime $\approx O(\log n\cdot\log\log n)$
- Total P&P instances $\approx O(\log n\cdot \log\log n)$ per stream copy $\times\log n$ copies = $O(\log^2n\cdot \log\log n)$

When character $x_j$ arrives, it **goes to exactly one sub-stream per copy** ($\log n$ copies), so only $\log n$ sub-stream P&P instances are actually updated per character, the others are untouched.

Each P&P runs in $O(\log n)$ time, so **total delay** is $O(\log^2 n)$.

The **space** is given by: $O(\log n)$ copies $\times$ $O(\log n\log\log n)$ sub-streams $\times$ $O(\log n)$ space per P&P = $O(\log^4n\cdot\log^2\log n)$ words.

**Theorem ($k=1$)**: after each text character $x_j$ ($j\geq n)$, the algorithm correctly reports whether $HD(y,x_{j-n+1}... x_j)$ is $0$, $1$ or $>1$, with $O(\log^4n\cdot\log^2\log\log n)$ space and $O(\log ^2n)$ delay w.h.p.

>[!tldr] Multiple mismatches
>Up until now we distinguished three outcomes: $HD=0$, $HD=1$ and $HD>1$ this comes from the fact that "at least one good $d$ separates all mismatches" is a guarantee when there's only one mismatch .
>
>But with **multiple mismatches**, the guarantee weakens.
>For a specific pair of mismatches at distance $z$ apart, we need a prime that doesn't divide $z$, and the set $P$ was chosen to be the first $\log n$ primes, just enough to guarantee that for any single distance $z\leq n$, at least one prime in $P$ doesn't divide it.
>
>But "at least one good prime for each pair" is a **much harder condition** when there are $k^2$ pairs, each with their own distance.
>We need a **prime that simultaneously avoids dividing all of those distances at once**, the first $\log n$ primes aren't enough to guarantee this anymore.

### Generalization to $k\geq 1$
With $k$ mismatches, there are up to $t\leq k^2$ pairs of mismatches, where each pairs has a distance $z_i\leq n$.
We need a prime $d$ that doesn't divide any of these distances, a prime "fails" if it divides at least one $z_i$.

The product of all mismatch-pair distances is:
$$\prod_{i=1}^tz_i\leq n^{k^2}$$
This product has at most $\log_2(n^{k^2})=k^2\log n$ distinct prime divisors.

The **solution** is to extend $P$ to include all primes up to the $(k^2\log n)$-th prime, but also restrict to primes $\geq k$ (so that $d\geq k$ ensures each mismatch foes to a separate bucket), formally we have:
$$P=\{2,3,5,7,...,(k^2\log n)\text{-th prime}\}\cap\{k,...,n\}$$
For at least one $d\in P$, no mismatch pair has its distance divisible by $d$, so all mismatches land in separate subsequences.
The count of mismatching sub-stream pairs equals $HD$ exactly.

This gives us the **same streaming algorithm** as before, scaled up in $k$.

**Theorem (general $k$)**: for a stream with pattern length $n$ and parameter $k$, after each text character $x_j$, the algorithm either reports $HD(y,x_{j-n+1}...x_j)\leq k$ exactly, or reports "$>k$", using:
- $\tilde O(k^6)$ words of **space**
- $\tilde O(k^2)$ **delay**
- Correct w.h.p.
>The $\tilde O$ notation means "ignoring factors that are polynomial in $\log n$".

### Generalization to edit distance
The **edit distance** $ED(A,B)$ is the minimum number of single-character insertions, deletions, or substitutions needed to transform $A$ into $B$ (not just substitutions).

Unlike Hamming distance, the two strings can have **different lengths**, and mismatches can "shift" due to gaps, so we can't just compare position by position.

>[!Example]
>$$ED(saturday, sunday) = 3$$
>Delete `a` and `t` from "saturday", and substitute `r` -> `n`.

The idea is to **reduce the edit distance to Hamming distance** by suing a randomized synchronization trick.

Sketch for $ED(A)$:
```
Sketch_ED(A):
	A' = ""
	i = 1
	while i <= n:
	    A'.append(A[i])
	    if h(A[i], |A'|) = true: i++ // advance in A
	    // otherwise, stay on A[i] and append it again next step
	return Sketch_HD(A')
```

Here $h(character, position)$ is a uniform random hash function that returns true of false with equal probability $1/2$.
The key property is that $h$ is **deterministic given its inputs**, so if $A$ and $B$ share the same character at the same "stretched" position, they both move or both stay together.

The **intuition** is that the function $h$ randomly decides whether to "advance" to the next character of $A$, or repeat the current one, this stretches $A$ into a longer string $A'$. the same process applied to $B$ gives $B'$.
If there's an insertion or deletion (an "edit") between $A$ and $B$, the random stretching hash a chance of "absorbing" it, making $A'$ and $B'$ line up at that position as if it weren't there.

>[!Example]
>Take $A=saturday$ and $B=sunday$ ($ED=3$).
>
>The process runs in parallel on $A$ and $B$, when both are tat the same character (like '$s$'), the same input to $h$ fives the same output, they advance or stay together.
>When they diverge (like $A$ is at '$a$' and $B$ is at '$u$' after the first '$s$'), the inputs $h$ differ, so outputs are independent, each with probability $1/2$.
>
>A "lucky event" occurs when $A$ advances $(h=true)$ while $B$ stays ($h=false$), or viceversa, this effectively skips over a deletion/insertion, re-synchronizing $A'$ and $B'$, each such event has probability $1/2\times1/2=1/4$.
>
>With $k=3$ edits, we need $3$ such lucky events to fully synchronize, the probability is $(1/4)^3=4^{-k}$.
>
>After full synchronization $A'$ and $B'$ have the same length, and their Hamming distance equals the edit distance (the remaining mismatches are substitutions), so $HD(A',B')=ED(A,B)$ when synchronization succeeds.

**Claim 1**: $A'$ is not too long
$|A'|=\Theta(|A|)$ w.h.p. since at every step we advance with probability $1/2$, so the number of steps follows a binomial distribution.

**Claim 2**: if we repeat the sketch $t=\Theta(4^k\cdot\log n)$ independent times, at least one repetition will have $HD(A'_i,B'_i)=ED(A,B)$ w.h.p. and taking the minimum across all repetitions gives us the correct answer:
$$ED(A,B)=\min_i HD(A'_i,B'_i)$$

Each trial succeeds with probability $4^{-k}$, running $t=\Theta(4^k\log n)$ trials makes the probability that none succeed drop to:
$$(1-4^{-k})^t\leq e^{-t/4^k}\leq n^{-c}$$
which is negligibly small.

Each of the $t=\Theta(4^k\log n)$ repetitions uses a Hamming distance sketch of size $\tilde O(k^2)$, the **total space** is given by:
$$\text{Space}=\tilde O(4^k\cdot k^2)\text{ words}$$

**Theorem**: there exists a sketch for edit distance of size $\tilde O(4^k\cdot k^2)$ that computes $ED(A,B)$ exactly w.h.p. (if $ED\leq k$), or detects $ED>k$.

