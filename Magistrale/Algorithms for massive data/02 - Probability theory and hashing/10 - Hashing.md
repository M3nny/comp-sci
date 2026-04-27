Many algorithms <u>work beautifully when the input is random</u>.

For instance, if we have $m$ numbers drawn uniformly at random, we can sort them in expected linear time $O(m)$ using [bucket sort](https://en.wikipedia.org/wiki/Bucket_sort), which is something no known deterministic sorting algorithm can do.

The _problem_ is that **real-world inputs are not random**, they're deterministic data from a user or file, so how do we get the "randomness" that our algorithm needs?
The _solution_ is **hashing**, instead of hoping our input is random, we **make it look random** by applying a hash function.

We **randomly pick a function** $h$ from a set of functions $\mathscr H$ and replace our data $x_1,...,x_m$ with $h(x_1),...,h(x_m)$.
By carefully designing $\mathscr H$, we can guarantee that the hashed values have the statistical properties our algorithm needs.

>[!Info]
>The random choice of $h$ happens _once_ at the start of the algorithm, after that, $h$ is used throughout, hence the only randomized step is picking it.
>

### Hash functions
A hash function $h:U\to[0,M)$ maps elements from a universe $U$ (e.g. integers, strings) to a range of $M$ values, and the function is chosen uniformly at random from a finite family $\mathscr H$.

Three desirable properties for $\mathscr H$:
1. **Randomness**: $h(x_1), ..., h(x_m)$ should behave like independent uniform random numbers, the more functions in $\mathscr H$, the more random the output
2. **Speed**: computing $h(x)$ should be $O(1)$ for integers, or $O(|x|)$ if $x$ is a string/set
3. **Small space**: storing the description of $h$ should require as few bits as possible

To store $h$, we need $\log_2|\mathscr H|$ bits, the bigger $\mathscr H$ is, the more space we need, but also the more random the output as we previously discussed, this creates a fundamental tension.

For example $\mathscr H=\{ax^2+bx+c\mod M:a,b,c\in[0,M)\}$ requires storing just three coefficients,  costing $3\log_2M$ bits.

### Fully uniform hashing
A family of hash functions $\mathscr H$ is **uniform** (or  fully uniform) if, for any outputs $y_1,..., y_n$ we have that:
$$\mathbb P((h(x_1),...,h(x_n))=(y_1,...,y_n))=\frac{1}{M^n}$$
In other words, all hashed values are independent and uniformly distributed over $[0, M)$ maximum possible randomness.

The **only** uniform family is the set of all possible functions from $U$ to $[0,M)$, if we remove even one function from it, we break the uniformity (there exists an output tuple that has probability $0$ instead of $1/M^n$).

**Formal proof**
Let $\mathscr H'\neq\mathscr H=[0,M)^U$, then:
- Surely $|\mathscr H'|<|\mathscr H|$, because $\mathscr H'\subseteq [0,M)^U$ and $\mathscr H'\neq [0,M)^U$
- Hence, let $h$ be a function in $\mathscr H$ that does not belong to $\mathscr H'$
- Let $y_i=h(x_i)$, for all $x_i\in U$
- We conclude that for any $h'\in\mathscr H$ it must be $(h'(x_1),...,h'(x_n))\neq(y_1,...,y_n)$, hence, for a uniform $h'\in\mathscr H'$:
$$\mathbb P((h'(x_1),...,h'(x_n))=(y_1,...,y_n))=0\neq\frac{1}{M^n}$$
Implying that $\mathscr H'$ is not uniform.

Since the only uniform family is all functions $U\to[0,M)$, storing one such function requires $|U|\cdot\log_2M$ bits, we need to store a separate output value for every element in the universe.

>[!Example]
>If $U$ is the universe of IPv4 addresses ($|U|=2^{32}$) and $M=2$, storing a uniform hash function requires $2^{32}$ bits $\approx 512$ MiB, just to store the function.
>This is completely impractical.
>

In conclusion we can say that full uniformity is in **direct conflict with the small-space requirement**, since we can't have both.

### K-wise independent hashing
Since our input has only $m$ elements (and usually $m\ll|U|$), we don't need all outputs to be jointly uniform, we only need any $k$ of them to be jointly uniform.

**Definition**: $\mathscr H$ is $k$-wise independent if, for any $k$ distinct inputs $x_1,...,x_k\in U$ and nay outputs $y_1,...,y_k\in[0,M)$:
$$\mathbb P((h(x_1),...,h(x_n))=(y_1,...,y_n))=\frac{1}{M^k}$$
The $k$ outputs look like $k$ independent uniform draws, but we make no promise about larger subsets:
- $k=|U|$ recovers full uniformity
- $k=2$ (called **pairwise independence**) is enough for many applications

A concrete $k$-wise independent family is defined by the family of degree $k-1$ polynomials over a prime-power field:
$$\mathscr H=\left\{\sum_{i=0}^{k-1}a_ix^i\mod M:a_0,...,a_{k-1}\in[0,M)\right\}$$
This works when $m\geq n$ is a power of a prime (so that $\mathbb Z_M$ is a field, ensuring polynomial roots behave as expected).

**Proof for $k=2$**:
Given two distinct inputs $x_1,x_2\in[n]$ and any targets $y_1,y_2\in[0,M)$, we need to prove that:
$$\mathbb P(h(x_1)=y_1\land h(x_2)=y_2)=M^{-2}$$
By definition of $h$ we have that:
$$\mathbb P(h(x_1)=y_1\land h(x_2)=y_2)=\mathbb P(ax_1+b\equiv_M y_1\land ax_2\equiv y_2)$$
Solving the two equations system in the variables $a$ and $b$, and recalling that the random variables $a$ and $b$ are _independent_, this equals to:
$$\begin{align}&\mathbb P\left(a\equiv_M\frac{y_2-y_1}{x_2-x_1}\land b\equiv_M y_1-x_1\cdot\frac{y_2-y_1}{x_2-x_1}\right)=\\
&=\mathbb P\left(a\equiv_M\boxed{\frac{y_2-y_1}{x_2-x_1}}_{z_1}\right)\cdot\mathbb P\left(b\equiv_M \boxed{y_1-x_1\cdot\frac{y_2-y_1}{x_2-x_1}}_{z_2}\right)\end{align}$$
Now, remembering that $x_1\neq x_2$ and $x_1,x_2\in[n]$, moreover $M\geq n$, it follows that $x_1-x_2\not\equiv0$.
Then, since $M$ is the power of a prime number, the inverse of $x_1-x_2$ modulo $M$ exists (because $\mathbb Z_M$ is a field).

We conclude that, to the right-hand side of these equivalences, we have two numbers from $[0,M)$, let's call them $z_1$ and $z_2$.

$$\mathbb P(a\equiv_M z_1)\cdot\mathbb P(b\equiv_M z_2)=\frac{1}{M}\cdot\frac{1}{M}=M^{-2}$$
**Space and time**:
- Space: $k\log M$ bits (just store the $k$ coefficients)
- Time: $O(k)$ to evaluate $h(x)$
- Both are small when $k$ is a constant, which is a great tradeoff

### Universal hashing
Sometimes we only need a _weaker_ property than full pairwise independence.

**Definition**: $\mathscr H\subseteq[0,M)^U$ is a **universal** hash family iff for a uniform choice of $h\in\mathscr H$ and any two distinct $x_1,x_2\in U$:
$$\mathbb P(h(x_1)=h(x_2))\leq \frac{1}{M}$$
In other words: the probability that two distinct elements **collide** (map to the same value) is at most as large as it would be if $h$ were fully random.

**Theorem**: if $\mathscr H$ is pairwise independent, then $\mathscr H$ is universal.
**Proof**: choose uniformly $h\in\mathscr H$ and any two distinct $x_1,x_2\in U$.
$$\begin{align}
\mathbb P(h(x_1)=h(x_2))&=\\
&=\sum_{y\in[0,M)}\mathbb P(h(x_1)=h(x_2)\land h(x_2)=y)\quad\text{Law of total probability}\\
&=\sum_{y\in[0,M)}\mathbb P(h(x_1)=y\land h(x_2)=y)\\
&=\sum_{y\in[0,M)}M^{-2}\quad\text{By pairwise independence}\\
&=\frac{1}{M}
\end{align}$$

### Perfect hashing
A hash function $h$ is **perfect** on a set $A$ if it is injective on $A$, which means no two distinct elements of $A$ collide.

**Static case**
If $A$ is known in advance, we can construct a perfect hash that evaluates in $O(1)$ time and uses only $O(\log|A|)$ bits.
>This is a well-known result in the theory of data structures.

**Dynamic case**
In streaming applications, $A$ arrives element by element and is not known ahead of time, in this case, perfect hashing with a strict guarantee is too strong a requirement. Instead, we settle for a guarantee _with high probability (w.h.p.)_.

We say that an event holds **with high probability** with respect to some quantity $n$, if its probability is at least $1-n^{-c}$ for an arbitrary large constant $c$ of our choice.

>[!Example]
>With $n=10^6$ and $c=3$, the collision probability is $\leq10^{-18}$.

**Theorem (perfect hashing via universality)**: if $\mathscr H$ is a universal family of functions $h:[1:n]\to[0,M)$ and $M\geq n^{c+2}$, then a uniformly-chosen $h\in\mathscr H$ is perfect on any set $A\subseteq [1,n]$ with high probability.
In other words: the co-domain size $M$ doesn't need to be astronomically larger than the universe size $n$.

### Polynomial hashing
The previous hash families worked on integers, for _strings_, a different approach is needed.

**Definition**: fix a prime $q$ and choose a uniform random $z \in [0, q)$, for a string $x$ of length $n$ over an alphabet $\Sigma$ of integers, **Rabin's hash** (polynomial hashing) is:
$$k_{q,z}(x)=\left(\sum_{i=1}^nx[i]\cdot z^{n-i}\right)\mod q$$
Intuitively, the string's characters are treated as coefficients of a polynomial evaluated at the random point $z$.

>[!Example]
>With $q=7$, $z=4$, and $x = \text{hello} = (104, 101, 108, 108, 111)$ in ASCII:
>$$k = 104\cdot4^4 + 101\cdot4^3 + 108\cdot4^2 + 108·4 + 111 \mod 7 = 2$$

**Remarkable compositional properties**: these make polynomial hashing extremely useful in practice:
- **Append a character**: $k(x\cdot c) = k(x) \cdot z + c \mod q$, we can extend the hash by one character without re-hashing from scratch
- **Concatenate two strings**: $k(x\cdot y) = k(x) \cdot z^|y| + k(y) \mod q$, we can combine two hashes using only their lengths and hash values, not the original strings

This means we can _manipulate and compare strings using only their hashes_, enabling huge savings in time and space.

Additionally, polynomial hashing has a **small collision probability**.
**Theorem**: let $x,y\in\Sigma^n$ with $x\neq y$, then:
$$\mathbb P(k_{q,z}(x)=k_{q,z}(y))\leq \frac{n}{q}$$
**Proof**:
$$\begin{align}
\mathbb{P}\bigl(k_{q,z}(x) = k_{q,z}(y)\bigr)&=\\
&= \mathbb{P}\bigl(k_{q,z}(x) - k_{q,z}(y) \equiv_q 0\bigr)\\
&= \mathbb{P}\left(
\sum_{i=1}^{n} x[i] \cdot z^{n-i}
- \sum_{i=1}^{n} y[i] \cdot z^{n-i}
\equiv_q 0
\right)\\
&= \mathbb{P}\left(
\sum_{i=1}^{n} (x[i] - y[i]) \cdot z^{n-i}
\equiv_q 0
\right)\\
&\leq\frac{n}{q}
\end{align}$$
The difference $k(x) − k(y)$ is a nonzero polynomial of degree $n−1$ over $\mathbb Z_q$.
By the fundamental theorem of algebra over a field, it has at most $n−1$ roots, and since $z$ is chosen uniformly from $q$ values, the probability of hitting a root is at most:
$$\frac{(n−1)}{q} < \frac{n}{q}$$
Therefore:
$$\mathbb{P}\bigl(k_{q,z}(x) = k_{q,z}(y)\bigr)\leq\frac{n}{q}$$

This is slightly worse than universal (which would require $\leq 1/q$), but in practice it's negligible: with strings of length $n = 2^{32}$ and a $128$-bit prime $q$, the collision probability is $\approx 2^{32}/2^{128} = 2^{-96}$.

**Choosing $q$ for perfect hashing w.h.p.**: if we want the hash to be perfect (no collisions) w.h.p., choose $q \gg n^2$ (so that $n/q \ll 1/n$, and a union bound over all pairs gives failure probability $\ll 1$).

>[!Info]
>From now on, to simplify terminology, we will say:
>"$h$ is $k$-wise independent/uniform/perfect/polynomial hash function".
>
>Instead of:
>"$h$ is a function uniformly chosen from a $k$-wise independent/uniform/perfect/
>polynomial family $\mathscr H$ of hash functions".

