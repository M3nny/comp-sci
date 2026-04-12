We will design randomized algorithms to **estimate** statistics on **data streams**, where the output will be a [[Variabili casuali|random variable]] and usually the [[Congiunte#Valore atteso|expected value]] is equal to the value we want to estimate.

As a first **example** we could consider a stream $x_1,...,x_m$ and estimate $f_x$ which indicates how many times a specific value $x$ appears in that stream.

The naive approach would be to store every element, but instead we add an element to our list $S$ with probability $1/1000$, then when asked how many times an element appeared in the stream, we could answer by retrieving how many times it appeared in $S$ and multiply that number by $1000$.

In this way we store $1/1000$ of the elements and have an estimate of the result.

If we run this program many times, **we _should_ see the expected value** to be the effective real value.

However, if we run the randomized algorithm just once, then its output $X$ is typically not equal to $E[X]$, for this reason we use **concentration bounds** which bound the probability that $|X-E[X]|$ exceeds some desired threshold.

We'll now see three bounds, from the weakest (Markov), to the stronger (Chernoff-Hoeffding).
Each one of them will require **assumptions on the Random Variable (RV)**, and usually with more assumption, comes a stronger bound.

---
### Markov's bound
**Assumption**: $X\geq 0$

**Theorem**
Let $X\geq 0$ be a non-negative RV, then for any $a\geq 0$ it holds:
$$\mathbb P(X\geq a)\leq E[X]/a$$

**Proof**
$$\begin{align}
E[X]&=\sum_{x\geq0}x\cdot\mathbb P(X=x)&\text{Definition of } E[X]\\
&\geq\sum_{x\geq a}a\cdot\mathbb P(X=x)\\
&=a\cdot\sum_{x\geq a}\mathbb P(X=x)\\
&=a\cdot\mathbb P(X\geq a)
\end{align}$$

>[!Example]
>Flip $100$ fair coins, let $X_i=0$ if the $i$-th coin is tail, $X_i=1$ if head.
>
>Let $X=\sum_{i=1}^{100}X_i$ be the number of heads, then $E[X]=\sum_{i=1}^{100}E[X_i]=\sum_{i=1}^{100}0.5=50$
>
>Applying Markov, we get $\mathbb P(X\geq 80)\leq E[X]/80=50/80=0.625$.
>
>Which is quite a useless upper bound, since the probability $\mathbb P(X\geq80)$ is in reality very small ($0.00\space...$).

### Chebyshev's bound
**Assumption**: we know $Var[X]$

**Theorem**
For any $k\geq 0$ it holds:
$$\mathbb P(|X-E[X]|\geq k)\leq Var[X]/k^2$$

**Proof**
$$\begin{align}
\mathbb P(|X-E[X]|\geq k) &=\mathbb P((X-E[X])^2\geq k^2)&\text{Square both sides}\\
&\leq E[(X-E[X])^2]/k^2&\text{Markov on the non-negative RV: }(X-E[X])^2\\
&=Var[X]/k^2&\text{By the definition of Var}
\end{align}$$

>[!Example]
> Using the same example:
> - $E[X]=50$
> - $Var[X]=\sum_{i=1}^{100}Var[X_i]=\sum_{i=1}^{100}0.5(1-0.5)=25$
> 
>The variance is retrieved from the [[Distribuzioni discrete#Bernoulli|variance of a bernoullian]], which is $p(1-p)$.
>
>Applying Chebyshev: $\mathbb P(X\geq 80)=0.5\cdot\mathbb P(|X-E[X]|\geq30)\leq0.5\cdot Var[X]/30^2\approx0.01389$.
>>$|X-E[X]|\geq 30$ iff either $X\geq 80$ or $X\leq 20$, and these two disjoint events are equaly-likely to happen since $X$ follows a symmetric binomial distribution.
>
>The bound is much more accurate than Markov.

### Boosted Chebyshev's bound
To improve our estimate, we can sample it multiple times and take the **average**.

**Theorem**
Let $X$ be a RV of which we know $Var[X]$, then fix $k>0$ and an integer $s\geq1$ and let $X_1,...,X_s$ be pairwise independent RV distributed as $X$.
Let $\hat X=\frac{1}{s}\sum_{i=1}^sX_i$, then:
$$\mathbb P(|\hat X-E[X]\geq k)\leq\frac{Var[X]}{s\cdot k^2}$$

The result is better than Chebyshev by a factor of $s$,.

This trick will be useful for other algorithms, that is, if we run the algorithm $s$ times and take the average of the results, then we boost the probability of success by a factor of $s$.

>[!Example]
>Using the same example, if we flip $100$ coins for $10$ times and take the average of the number of heads that we see in the $10$ rounds.
>
>Then the probability that the average exceeds $80$ is $1/10$ of what we obtained with Chebyshev: $\approx0.01389/10 = 0.001389$.

### Chernoff-Hoeffding
**Assumption**
The RV $Y=\sum_{i=1}^nY_i$ is the sum of $n$ independent and identically-distributed (i.i.d.) Bernoullian RV $Y_i$.

**Theorem**
If $Y$ is the sum of $n$ i.i.d. Bernoullian RV, then for any $t\geq 0$:
- $\mathbb P(Y\geq E[Y]+t)\leq e^{\frac{-t^2}{2n}}$
- $\mathbb P(Y\leq E[Y]-t)\leq e^\frac{-t^2}{2n}$
- $\mathbb P(|Y-E[Y]|\geq t)\leq 2e^\frac{-t^2}{2n}$

>[!Example]
>Using the same example, we have that $E[x]=50$, and by applying Chernoff-Hoeffding: $\mathbb P(X\geq 80)=\mathbb P(X\geq E[X]+30)\leq e^\frac{-30^2}{200}\approx 0.0111$.
>
>Which is better than Chebyshev.

---
### The mean-median trick
The technique that we are going to discuss, also know as the **mm-trick** works under a **strong assumption**: $Var[X]=O(E[X]^2)$, that is, the variance must not be too large.

**Theorem**
Let $X$ be a RV such that $Var[X]=O(E[X]^2)$ and choose parameters $\epsilon>0$ (**error rate**) and $\delta>0$ (**failure probability**).

Let $t=\Theta(\log(1/\delta))$ and $s=\Theta(\epsilon^{-2})$, then draw $st=\Theta(\epsilon^{-2}\log(1/\delta))$ i.i.d. realizations $X_{i,j}$ of $X$ (which is a matrix).

Let $\hat X_j=\frac{1}{s}\sum_{i=1}^sX_{i,j}$ be the **mean** of the $j$-th column and $Y=median(\hat X_1,...,\hat X_t)$ be the **median** of those means.
![[MM-trick.png]]

Then:
$$\mathbb P(|Y-E[X]|\geq \epsilon\cdot E[X])\leq\delta$$

In other words, we can have **arbitrary precision $\epsilon$ and failure probability $\delta$**, the price to pay is to repeat $st=\Theta(\epsilon^{-2}\log(1/\delta))$ times our randomized algorithm.

#### Mean trick proof
Let $c$ be the smallest constant such that $Var[X]\leq c\cdot E[X]^2$.
We begin by choosing enough rows such that the following holds:
$$\mathbb P(|\hat X_j-E[X]|\geq\epsilon\cdot E[X])\leq1/3$$
In other words, the mean of any column exceeds relative error $\epsilon$ with constant probability ($1/3$).

In order to obtain this, we can use **boosted Chebyshev's bound** and set $k=\epsilon\cdot E[X]$.
$$\begin{align}
\mathbb P(|\hat X-E[X]\geq k)&\leq\frac{Var[X]}{s\cdot k^2}\\
&\leq\frac{cE[X]^2}{s(\epsilon\cdot E[X])^2}\\
&=cs^{-1}\epsilon^{-2}\\
&=1/3\iff s=3c\epsilon^{-2}=\Theta(\epsilon^{-2})
\end{align}$$

#### Median trick proof
Now that our matrix has $s=\Theta(\epsilon^{-2})$ rows, then the mean $\hat X_j$ of each column exceeds relative error $\epsilon$ with probability at most $1/3$.

The next step is to show that the median of $\hat X_j$ exceeds relative error $\epsilon$ with probability at most $\delta$, if we have $t=\Theta(\log(1/\delta))$ columns.

**Claim**
Let $Y=median(\hat X_1,...,\hat X_t)$ be the median of $t=72\ln(1/\delta)$ i.i.d. RV $\hat X_j$ such that:
$$\mathbb P(|\hat X_j-E[X]|\geq\epsilon\cdot E[X])\leq1/3$$
then:
$$\mathbb P(|\hat X_j-E[X]|\geq\epsilon\cdot E[X])\leq\delta$$

**Proof**
Let $Y=median(\hat X_1,...,\hat X_t)=\hat X_q$ without loss of generality:
$$\hat X_1<\hat X_2<...<\hat X_q<...<\hat X_t$$
If $Y=\hat X_q$ "_fails_" because it is too large ($\hat X_q\geq E[X]+\epsilon\cdot E[X])$, then these $\geq t/2$ random variables "fail" as well.
>The case where it fails because it is too small has to be accounted since it is symmetric.

Let $\mathbb 1_j=1$ if $\hat X_j$ "fails", and $\mathbb 1_j=0$ otherwise, then $\mathbb 1_j$ is a Bernoullian RV distributed as $Be(1/3)$, then note that $Y=\hat X_q$ "fails" iff $Z=\sum\limits_{j=1}^t\mathbb 1_j\geq t/2$.

Now we apply **Chernoff-Hoeffding** to $Z$.
Notice that $E[Z]=t\cdot\frac{1}{3}$, so we can rewrite the failure condition:
$$Z\geq\frac{t}{2}=E[Z]+\frac{t}{6}$$

This is a deviation of $\frac{t}{6}$ above the mean, and since $Z$ is a sum of $t$ independent Bernoullian RV, Chernoff-Hoeffding applies with parameter $t_{param}=\frac{t}{6}$:
$$\mathbb{P}\left(Z\geq E[Z]+\frac{t}{6}\right)\leq e^{-\frac{(t/6)^2}{2t}}=e^{-\frac{t^2/36}{2t}}=e^{-t/72}$$

We need this probability to be at most $\delta$:
$$e^{-t/72}\leq\delta\iff t\geq72\ln(1/\delta)\implies t=\Theta(\log(1/\delta))$$

which is exactly the claim.

>[!Summary]
>The proof combines two tricks:
>- **Mean trick**: $s=\Theta(\epsilon^{-2})$ rows make each column mean fail with probability $\leq 1/3$
>- **Median trick**: $t=\Theta(\log(1/\delta))$ columns make the median fail with probability $\leq\delta$, because getting more than $t/2$ bad columns out of $t$ (when each is bad with prob $\leq 1/3$) is a large deviation that Chernoff kills exponentially fast.

The final intuition is that the mean reduces variance and the median amplifies the signal.
Together they give **arbitrary** $\epsilon$ and $\delta$ at the cost of $\Theta(\epsilon^{-2}\log(1/\delta))$ samples.
