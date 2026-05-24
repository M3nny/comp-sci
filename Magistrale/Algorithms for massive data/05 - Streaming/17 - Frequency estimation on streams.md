In this chapter we're going to see how to **estimate the frequency** of a particular value without storing the whole stream.

Given a stream $x_1,...,x_m$ where each element $x_i$ is drawn from an universe $[n]=\{1,...,n\}$, for any query value $y$, we want to estimate $f_y$, which is the number of times $y$ appears in the stream.

### Sampling
The simplest approach is **random sampling**, where instead of processing every element, we _randomly draw a small subset of $q$ elements_ from the stream and count how often $y$ appears in that sample, then scale the result up to estimate the full stream frequency.

The estimate is:
$$\tilde f_y=\frac{m}{q}\cdot(\text{number of times }y\text{ appears in the sample})$$
>[!Example]
>- Stream = $[4, 5, 2, 4, 1, 3, 4, 5, 1, 5, 1, 1, 4, 3]$ ($m=14$)
>- Uniform sample of size $q=5$: $2, 4, 1, 1, 3$
>
>The real frequency $f_4=4$ and the estimate is $\tilde f_4=\frac{14}{5}\cdot 1=2.8$

Each sampled element has a probability $f_y/m$ of being equal to $y$ (it's a Bernoulli random variable), and by linearity of expectation, the expected count of $y$ in the sample is $(q/m)\cdot f_y$, so after scaling, $E[\tilde f_y]=f_y$, in other words, **the estimator is unbiased** (correct on average).
$$\tilde f_y=\frac{m}{q}\sum_{i=1}^q(x'_i=y)$$
$$E\left[\sum_{i=1}^q(x_i'=y)\right]=(q/m)\cdot f_y\implies E[\tilde f_y]=f_y$$

To bound how far off the estimate can be, we can apply the [[09 - Concentration bounds#Chernoff-Hoeffding|Chernoff-Hoeffding inequality]].
$$\begin{align}
\mathbb P(|\tilde f_y-f_y|\geq\epsilon\cdot m)&=\\
&=\mathbb P((q/m)|\tilde f_y-f_y|\geq\epsilon\cdot q)\\
&=\mathbb P\left(\left|\sum_{j=1}^q(x'_j=y)-E\left[\sum_{j=1}^q(x'_j=y)\right]\right|\geq\epsilon\cdot q\right)\\
&\leq 2e^{-(\epsilon\cdot q)^2/(2q)}\\
&=2e^{-\epsilon^2 q/2}
\end{align}$$

Setting this failure probability equal to $\delta$ and solving for $q$ gives the required sample size:
$$q=\lceil2\epsilon^{-2}\ln(2/\delta)\rceil\in\Theta(\epsilon^{-2}\log(1/\delta))$$

**Theorem**
By sampling $q=\lceil2\epsilon^{-2}\ln(2/\delta)\rceil\in\Theta(\epsilon^{-2}\log(1/\delta))$ elements uniformly at random, we can estimate any frequency $f_y$ with additive error $\epsilon\cdot m$ and failure probability $\delta$.

In other words, for any $y\in[1,n]$ our estimator $\tilde f_y$ satisfies:
$$\mathbb P(|\tilde f_y-f_y|\geq\epsilon\cdot m)\leq\delta)$$
>[!Important]
>The **error is additive** $f_y\pm\epsilon m$, not multiplicative $f_y(1\pm\epsilon)$.
>In particular, this estimate is bad if $f_y$ is very small compared to $m$.

The fundamental problem is that since the sketch size scales as $\epsilon^{-2}$, to keep the sketch small we're forced to pick a large $\epsilon$, which makes the additive error large too.
The **minimum achievable additive error** with this technique is roughly $\sqrt m$.

### Count-Min sketch
The **Count-Min Sketch (CMS)** is an improvement from the sampling strategy:
- Space: $O(\epsilon^{-1}\log(1/\delta))$
- One-sided error: the estimate $\tilde f_y$ always satisfies $\tilde f_y\geq f_y$, we never undercount the frequency, we may overcount it due to hash collisions, but the true frequency will always be a lower bound on the estimate

The CMS is a $t\times s$ **matrix of integers**, where $t$ is the number of rows and $s$ is the number of columns.
Each row $i$ is associated with its own independent **universal hash function** $h_i:[n]\to[s]$, and all entries start at $0$.

![[CMS base.png|500]]

>[!Note]- Universal hash function
>A **universal hash function** is a hash function chosen at random from a family where any two distinct keys collide with probability at most $1/s$.
>This controlled collision probability is what will make the analysis work.

**Insert**
```
insert(x):
	for all i = 1, ..., t
		CM[i, h_i(x)] = CM[i, h_i(x)] + 1
```

When an element $x$ arrives, we increment one cell per row, the cell in the column where $x$ hashes.
>This is like a [[12 - Counting Bloom filters|counting bloom filter]] but without an overflow check, and for a different problem.

By inserting the following sequence: $1,3,4,3,3,1,5,1,5,8,8,8,1,2$
![[CMS insert.png|500]]

**Estimate frequency**
```
estimate_frequency(x):
	return min{CM[i, h_i(x)]: i in [t]}
```

To estimate $f_x$, we look up $x$'s hashed cell in each row and _return the minimum across all rows_.

Each cell $CM[i,h_i(x)]$ counts all occurrences of $x$ plus all occurrences of any other element $y$ that happens to hash to the same column (collisions), so every cell is $\geq f_x$ (hence the one-sided error).
_The minimum selects the row with the fewest collisions_, giving the best (lowest) estimate.

#### Analysis
**Expectation bound on a single row**
For a single row $i$, the expected value of $CM[i,h_i(x)]$ is:
$$\begin{align}
E[CM[i,h_i(x)]]&=E\left[\underbrace{f_x}_{\text{Occurences of }x}+\underbrace{\sum_{y\neq x}f_y\cdot(h_i(x)=h_i(y))}_{\text{Frequencies of elements }y\text{ that collide with }x}\right]\\
&=f_x+\sum_{y\neq x}f_y\cdot E[(h_i(x)=h_i(y))]
\end{align}$$
>$(h_i(x)=h_i(y))$ is the Bernullian R.V. indicating whether the two hashes collide.

Recalling that $h$ is universal we can rewrite the expected value of the Bernullian RV using the fact that: $\mathbb P(h_i(x)=h_i(y))\leq 1/s$:
$$\begin{align}
f_x+\sum_{y\neq x}f_y\cdot E[(h_i(x)=h_i(y))]&=\\
&\leq f_x+\sum_{y\neq x}f_y\cdot (1/s)\\
&\leq f_x+(1/s)\sum_{y\neq x}f_y\\
&\leq f_x+m/s
\end{align}$$
To sum up:
$$f_x\leq E[CM[i,h_i(x)]]\leq f_x+m/s$$
By choosing a larger $s$ (more columns), we can make the expected error $m/s$ smaller.
But this is just an expectation, we still have to control $CM[i,h_i(x)]$.

**From expectation to a probabilistic bound**
[[09 - Concentration bounds#Markov's bound|Markov's inequality]] says: if a non-negative RV $Z$ has mean $\mu$, then $\mathbb P(Z\geq 2\mu)\leq1/2$, and by applying this to the excess $CM[i,h_i(x)]-f_x$ whose mean is at most $m/s$:
$$\mathbb P(CM[i,h_i(x)]\geq f_x+2m/s)\leq 1/2$$
So each row independently has at most a $1/2$ probability of exceeding error $2m/s$.

**Amplification via multiple rows**
Since each row fails independently with probability $\leq 1/2$, the probability that all $t$ rows fail is at most $(1/2)^t=2^{-t}$, so with probability $\geq 1-2^{-t}$, at least one row has a good estimate, and the minimum will find it.

**Setting the parameters**
Choosing:
- $s=2/\epsilon$ (columns) the _error per row_ is $2m/s=\epsilon\cdot m$
- $t=\log(1/\delta)$ (rows) the _failure probability_ is $2^{-t}=\delta$

**Theorem**
The CMS uses $2\epsilon^{-1}\log(1/\delta)$ words of space and, for any $x\in[n]$ returns an estimate $\tilde f_x$ such that:
- $\tilde f_x\geq x$
- $\mathbb P(\tilde f_x\leq f_x+\epsilon\cdot m)\geq 1-\delta$

_Updates and queries both run in $O(\log(1/\delta))$ time_ (one hash lookup per row).

The key takeaway is that if we allow the CMS to use $O(m/k)$ space, the additive error is $k$.
>Space and error trade off linearly.

### Conservative updates
A simple improvement over the standard CMS uses **conservative updates** which instead of incrementing all $t$ cells $CM[i,h_i(x)]$, it increments only the cell(s) with the smallest current value.

This avoids inflating cells unnecessarily, and in practice it reduces the error, however this introduces dependencies between rows that make formal analysis much more difficult.

### Range queries
So far we asked ourselves "how many times does value $y$ appear?", now the question becomes "how many stream elements fall in the range $[i,j]$?".

The idea is to build $\log_2n+1$ separate count-min sketches, one for each "level" fo a hierarchy of **dyadic intervals**, which are intervals whose length is a power of $2$, aligned to that power, they form a natural hierarchy like a segment three or a binary tree over $[n]$.

For $n=16$, we build $5$ CMS structures, and each element $x$ in the stream is inserted into all $\log n+1$ CMS structures.

Any arbitrary range $[i,j]$ can be decomposed into **at most $2\cdot\log_2 n$ dyadic intervals** from the hierarchy.

To answer a query for range $[i,j]$:
1. Decompose $[i,j]$ into at most $2\cdot \log_2 n$ dyadic intervals
2. Query each relevant CMS for the frequency of that dyadic interval
3. Sum the results

Example with interval $[6,13]$:
![[CMS range query.png|600]]

**Failure probability**
_Naive approach (union bound)_: combining up to $2\log n$ queries each with failure probability $\delta$ gives overall failure probability $\leq 2\delta\log n$.

A _better approach_: the CMS at different levels are independent of each other, so within a single level, we may issue at most $2$ queries, and if the hash functions are _pairwise independent_ (not just universal), those two queries within the same level are also independent, then with pairwise independence, the overall failure probability becomes:
$$\delta'\leq1-(1-\delta)^{2\log n}$$
Which is a much tighter bound than $2\delta\log n$ for small $\delta$.
