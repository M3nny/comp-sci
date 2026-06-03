Before talking about **second order frequency moments** we introduce another algorithm to estimate the number of times a specific element $y$ has appeared using a sketch.

### Count sketch
Take a hash function $h:[n]\to\{-1,+1\}$ that is pairwise independent (it maps each element randomly to either $-1$ or $+1$ and the values for any two distinct elements are independent of each other).

Two key facts follow from pairwise independence:
- $E[h(x)]=0$ for any $x$ (equal chance of $-1$ or $+1$)
- $E[h(x)\cdot h(y)]=1$ if $x=y$, and $=0$ if $x\neq y$ (different elements are independent, so their product averages to zero)

This second fact is particularly important, in fact multiplying two hash values cancels out noise from unrelated elements.

```
initialization():
	// Fourse-wise for technical reasons
	h = four-wise independent hash function from [n] to {-1, +1}
	z = 0

new_stream_element(x):
	z += h(x)

estimate_frequency(y):
	return z * h(y)
```

This works because after seeing the whole stream, $z=\sum_{x_i}h(x_i)$.
When we compute $z\cdot h(y)$, each stream element $x_i$ contributes $h(x_i)\cdot h(y)$, this equals $h(y)^2=1$, and if $x_i\neq y$, the expected value is $0$, so on average $z\cdot h(y)$ equals exactly $f_y$.

The estimator is **unbiased** for $f_y$:
$$\begin{align}
E[z \cdot h(y)] &= E\left[\left(\sum_{i=1}^{m} h(x_i)\right) \cdot h(y)\right]\\
&= E\left[\sum_{x_i = y} h(x_i)h(y) \;+\; \sum_{x_i \ne y} h(x_i)h(y)\right]\\
&=\sum_{x_i = y} E[h(x_i)h(y)] \;+\; \sum_{x_i \ne y} E[h(x_i)h(y)]\\
&=\sum_{x_i = y} 1 \;+\; \sum_{x_i \ne y} 0\\
&=f_y
\end{align}$$

**Theorem (by repetition, we skip the analysis)**
Using $O(\epsilon^{-2}\log(1/\delta))$ words of memory, count sketch returns $f_y\pm\epsilon||f||_2$ with probability at least $1-\delta$, where $||f||_2=\sqrt{\sum_xf_x^2}$ is the euclidean norm of the frequency vector.

>[!Note]
>The [[17 - Count-Min sketch#Count-Min sketch|Count-Min Sketch]] is smaller by a factor $\epsilon^{-1}$ but returns $f_y\pm\epsilon\cdot m$.


### Tug-of-war sketch
The same idea of the count sketch can be applied to estimate:
$$F_2=\sum_xf_x^2$$
Which is literally the sum of squares of all frequencies, and it is also called **surprise number** because:
- If all elements appear equally often, $F_2$ is small (frequencies are balanced, nothing is surprising)
- If some elements are very rare and others very common, $F_2$ is large
>It reflects how much frequencies are _unbalanced_.

```
initialization():
	// Fourse-wise for technical reasons
	h = four-wise independent hash function from [n] to {-1, +1}
	z = 0

new_stream_element(x):
	z += h(x)
	

estimate_second_order_moment(y):
	return z^2
```

ToW is **unbiased**:
$$
\begin{align}
E[z^2] &= E\left[\left(\sum_{i=1}^{m} h(x_i)\right)^2\right] \\
&= E\left[\left(\sum_{x \in [n]} f_x \cdot h(x)\right)^2\right] \\
&= E\left[\sum_{x \in [n]} \left(f_x^2 \cdot h(x)^2\right) + \sum_{x \neq y} \left(2f_x f_y \cdot h(x) \cdot h(y)\right)\right] \\
&= \sum_{x \in [n]} f_x^2 \cdot E[h(x)^2] + \sum_{x \neq y} 2f_x f_y \cdot E[h(x) \cdot h(y)] \\
&= \sum_{x \in [n]} f_x^2 \cdot 1 + \sum_{x \neq y} 2f_x f_y \cdot 0 \\
&= F_2
\end{align}
$$

**Theorem**
$Var[z^2]\leq 3F_2^2=3E[z^2]^2$.
A sketch of the proof is:
$$
\begin{align}
Var[z^2] &= E[(z^2)^2] - E[z^2]^2 \leq E[z^4] \\
&\leq F_4 + 6 \sum_{a < b \in [1,n]} f_a^2 f_b^2 \\
&\leq 3F_2^2 - 2F_4 \\
&\leq 3F_2^2 = O(E[z^2]^2)
\end{align}
$$

The proof uses _four-wise independence_: when expanding $E[z^4]$, terms involving any element an odd number of times vanish (by 4-wise independence).
Only terms where all elements appear an even number of times survive, yielding a manageable bound.

The important note here is that four-wise independence (not just pairwise) is needed for the variance calculation.

**Theorem**
Now, since $z^2$ is unbiased for $F_2$ and $Var[z^2]=O(E[z^2]^2)$, we use the mean+median trick, which gives us:
For any chosen $\epsilon,\delta>0$, ToW uses $O(\epsilon^{-2}\log(1/\delta))$ words of space and returns an estimator $z^2$ such that:
$$\mathbb P(|z^2-F_2|>\epsilon\cdot F_2)<\delta$$

### Dimensionality reduction
$F_2$ is the _squared euclidean norm_ of a vector, this connection lets us use the ToW idea to build a dimensionality-reduction map.

Given two vectors $x,y\in\mathbb R^n$ in a high dimensional space, we want to fin a linear map $M$ (a matrix) that compresses them to a much lower dimensional space $\mathbb R^{O(\epsilon^{-2})}$, while approximately preserving their euclidean distance:
$$||Mx-My||_2\approx(1\pm\epsilon)\cdot||x-y||_2$$
![[Dimensionality reduction.png|500]]

In other words, with constant probability (which can be amplified by repetition), the linear operator $M$ **preserves the euclidean distance** $\ell_2$ with distortion factor $\epsilon$.
$$\ell_2=||x-y||_2=\sqrt{\sum_{i=1}^n(x_i-y_i)^2}$$

This is useful because instead of comparing high-dimensional vectors at cost $O(n)$ per comparison, we can compress once and then compare in $O(\epsilon^{-2})$ time, independent of $n$.

Note that $||x||_2^2=\sum_ix_i^2$, which is $F_2$ of the vector $x$ (treating each coordinate as a "frequency").
Also, since $M$ will be a **linear** map, $||Mx-My||_2=||M(x-y)||_2$, so we only need to estimate the squared norm of a single vector.

The ToW sketch computes $z=\sum_ix_i\cdot h(i)$, which is exactly the **dot product** of a random $\pm1$ vector with $x$.
In matrix form, this is $z=M\cdot x$ where $M$ is a single-row matrix with $\pm1$ entries.

>[!Example]
>- $n=3$
>- $h=[-1,+1,-1]$
>- $x=[3.14,2.71,1.61]$
>$$z=\underbrace{[-1,+1,-1]}_{M}\cdot\underbrace{\begin{bmatrix}3.14\\2.71\\1.61\end{bmatrix}}_{x}=-2.04$$
>

**Mapping to $\mathbb R^1$**:
If $M$ is a single row drawn uniformly from $\{-1,+1\}^n$, then:
$$\mathbb E[||Mx||_2^2]=\mathbb E[z^2]=F_2=||x||_2^2$$
So a single random row preserves squared norm _on expectation_.

However, from the previous example we have $Mx=-2.04$, so $||Mx||^2\approx4.16$ vs $||x||^2\approx19.79$.
>A single row gives a terrible approximation in practice.


**Using $s$ rows**
Build $M$ as an $s\times n$ matrix, where each row is an independent random $\pm1/\sqrt s$ vector.
The $1/\sqrt s$ scaling ensures the expectation stays correct:
$$||Mx||_2^2=\frac{1}{s}\sum_{i=1}^sz_i^2$$
is the average of $s$ independent ToW outputs.

>[!Example]
>- $n=3$
>- $s=2$
>- $h=[-1,+1,-1]$
>- $x=[3.14,2.71,1.61]$
>$$M\cdot x=\frac{1}{\sqrt 2}\begin{bmatrix}-1,+1,-1\\+1,+1,-1\end{bmatrix}\cdot\begin{bmatrix}3.14\\2.71\\1.61\end{bmatrix}\approx\begin{bmatrix}-1.44\\3\end{bmatrix}$$

This is a much better approximation, since $||M\cdot x||_2^2=(-1.44)^2+3^2\approx11.07$ and $||x||_2^2=19.79$.

**Theorem**
If $M$ is drawn uniformly from $\{-1/\sqrt s,+1/\sqrt s\}^{s\times n}$ with $s=\lceil9\epsilon^{-2}\rceil$, then with probability at least $2/3$:
$$||Mx-My||_2=(1\pm\epsilon)\cdot||x-y||_2$$
The sketch of the proof is that:
each row gives one independent ToW estimate (scaled by $1/\sqrt s$), and $||Mx||_2^2$ is their average, by applying Chebyshev's inequality with $Var[z_1]\leq 3E[z_1]^2$ and solving for $s$, we get $s=9\epsilon^{-2}$.

To **boost the success probability** to $1-\delta$, there are two approaches:
- _Median trick_: run $O(\log(1/\delta))$ independent instances and take the median, the downside is that the result is no longer a linear map (medians aren't linear)
- _More rows_:; multiply the number of rows by $\Theta(\log(1/\delta))$, this works by concentration bounds and preserves linearity

### Achlioptas transform
The full theorem of dimensionality reduction, combining $\epsilon$ and $\delta$.

**Theorem**
For $x,y\in\mathbb R^n$ and any $\epsilon,\delta>0$, there exists $s\in O(\epsilon^{-2}\log(1/\delta))$ such that, if $M$ is drawn uniformly from $\{-1/\sqrt s,+1/\sqrt s\}^{s\times n}$, then with probability at least $1-\delta$:
$$||Mx-My||_2=(1\pm\epsilon)\cdot||x-y||_2$$
In short: $M:\mathbb R^n\to\mathbb R^{\Theta(\epsilon^{-2}\log(1/\delta))}$ is a **random projection** (linear map) that approximately preserves euclidean distance, and the output dimension doesn't depend on $n$ at all.
