### Frequentist estimation framework
Let $Y$ be a RV with the following cumulative distribution function:
$$F_Y(y;\theta)=P_\theta(Y\leq y),\quad\theta\in\Theta$$
The _PDF_ describes _local density_, the _CDF_ gives the probability of _observing a value no larger than a threshold_.

The **model family** $\{F_Y(\cdot;\theta:\theta\in\Theta\}$ is assumed known, while the true parameter $\theta$ is fixed but unknown.
We observe an i.i.d. random sample:
$$D_n=(Y_1,...,Y_n),\quad Y_i\stackrel{i.i.d.}{\sim}P_\theta$$
whose observed realization is $d_n=(y_1,...,y_n)$.

**Frequentist principle**: randomness belongs to the sampling process, and therefore to statistics computed from the sample, $\theta$ is not random.

The statement $Y_i\stackrel{i.i.d.}{\sim}P_\theta$ contains three assumptions:
- Every $Y_i$ has distribution $P_\theta$
- The observations share the same parameter $\theta$
- The observations are mutually independent
>_These assumptions must come from the sampling design and scientific model_, they cannot be established merely by inspecting a histogram.

#### Why i.i.d. matters
Its assumptions make the math tractable.

1. **Identically distributed**
$$Y_i\sim P_Y(\theta)\quad\forall i$$
Every observation comes from the same distribution with the same parameter $\theta$ (e.g. 100 flips of the same coin, not 100 different coins), this is what lets us use one $\theta$ to describe the whole sample.

2. **Independent**
$$P_\theta(Y_1\in A_1|Y_2\in A_2,...,Y_n\in A_n)=P_\theta(Y_1\in A_1)$$
Knowing what happened to $Y_1,...,Y_n$ tells us nothing about $Y_1$, conditioning on the other observations doesn't change the probability.

This leads to the _joint probabilities becoming products_:
$$p_\theta(y_1,...,y_n)=p_\theta(y_1)\times\dotsi\times p_\theta(y_n)=\prod_{i=1}^np_\theta(y_i)$$
This is the probability (or density) of seeing the entire dataset $y_1,...,y_n$.
Since the observations are independent, we multiply the individual probabilities, and because they are identically distributed, every factor uses the _same function_ $p_\theta$.

>[!Example]
>Three coin flips with $P(heads)=\theta$:
>$$p_\theta(H,H,T)=\theta\cdot\theta\cdot(1-\theta)=\theta^2(1-\theta)$$

>[!Info]  MLE preview
>Later we'll find that in MLE, we treat the joint probability as a function of $\theta$ (the likelihood) and find that the $\theta$ that makes our observed data most probable.
>
>Without i.i.d. the joint distribution could be a complicated object with dependencies between observations, and we'd have to model all of them.
>
>With i.i.d. we only need the single-observation formula $p_\theta(y)$, and the product does the rest.

#### Point estimation vs interval estimation
A **point estimator** is a statistic applied to the random sample $D_n$:
$$\hat\theta_n=h(D_n)$$
Before the data is observed, $\hat\theta_n$ is random, after observing $d_n=(y_1,...,y_n)$, evaluating $h(d_n)$ gives a _numerical estimate_ of the fixed unknown parameter $\theta$.

An **interval estimator** is formed by a pair of statistics (a lower bound and an upper bound):
$$[L(D_n), U(D_n)]$$
where $L(D_n)$ and $U(D_n)$ are statistics.

The interval contains a series of values that are "plausible" for the parameter $\theta$.
The interval is random before sampling and _becomes fixed after the data is observed_.

| Object                               | Interpretation                     |
| ------------------------------------ | ---------------------------------- |
| $\theta$                             | fixed unknown population parameter |
| $D_n = (Y_1, \dots, Y_n)$            | random sample                      |
| $d_n = (y_1, \dots, y_n)$            | observed sample                    |
| $\hat{\theta}_n = h(D_n)$            | random estimator                   |
| $\hat{\theta}_{\text{obs}} = h(d_n)$ | observed estimate                  |
| $\mathcal{L}_\theta(\hat{\theta}_n)$ | (Law) sampling distribution        |

---
### Empirical distribution and plug-in estimation
Before observing the data, the **empirical distribution function (ECDF)** is the random function:
$$\widehat F_n(y)=\frac{1}{n}\sum_{i=1}^n1\{Y_i\leq y\}$$
- $\mathbf{1}\{Y_i \le y\}$ is an _indicator_: it equals 1 if $Y_i \le y$, and 0 otherwise
- Summing the indicators counts how many observations are $\le y$
- Dividing by $n$ turns the count into a proportion

After observing $d_n=(y_1,...,y_n)$, its realized value is:
$$\widehat F^{obs}_n(y)=\frac{1}{n}\sum_{i=1}^n1\{y_1\leq y\}=\frac{\#\{i:y_i\leq y\}}{n}$$
These are _different objects_: $\hat F_n$ is a statistic and therefore random, whereas $\hat F_n^{obs}$ is the deterministic step function computed from the observed data.

```r
latency_ms <- c(20,21,22,20,23,25,26,25,20,23,24,25,26,29)
plot(ecdf(latency_ms), verticals = TRUE, do.points = TRUE,
	main = "Empirical distribution function",
	xlab = "API latency (ms)", ylab = expression(hat(F)[n]*obs(y)),
	las = 1)
grid()
```

![[ECDF.png|659]]
>At any threshold $y$, `ecdf(latency_ms)(y)` is the observed proportion of requests with latency no greater than $y$.

For a fixed threshold $y$, each comparison $Y_i\leq y$ is the results of a Bernoulli random variable with success probability $p=F_Y(y)$, consequently:
$$E[\widehat F_n(y)]=F_Y(y),\quad Var[\widehat F_n(y)]=\frac{F_Y(y)(1-F_Y(y))}{n}$$
Thus the empirical CDF is unbiased pointwise, and its pointwise variance decreases at rate $1/n$.

Now, suppose the _target parameter_ $\theta$ (some number describing the population, such as mean, median, variance, ...) is computed from the true distribution $F_Y$ by some true $t$ (a "recipe" that takes a distribution and returns a number):
$$\theta=t(F_Y)$$
>[!Example]
>- If $t$ = "take the mean of the distribution," then $\theta$ is the population mean.
>- If $t$ = "take the median," then $\theta$ is the median.

#### The plug-in principle
Since we don't know the real $F_y$, but we have $\widehat F_n$, we use the **plug-in estimator** that replaces the unknown $F_Y$ by $\widehat F_n$:
$$\boxed{\hat\theta_n=t(\widehat F_n)}$$
>In words: "Whatever we'd compute from the true distribution, compute it from the empirical distribution instead."

The **population mean** is:
$$\mu=E[Y]=\int_{-\infty}^{+\infty}y f_Y(y)dy=\int_{-\infty}^{+\infty}ydF_Y(y)$$
Replacing $F_Y$ by $\widehat F_n$ and recalling that from the step plot each observation gets a jump of $1/n$, the integral becomes a sum:
$$\hat\mu_n=\int yd\widehat F_n(y)=\frac{1}{n}\sum_{i=1}^nY_i=\overline Y$$
As a result, the plug-in estimator of the population mean is the ordinary sample average $\overline Y$.
>That's the point: a familiar formula falls out of a general principle.

The **population variance** is:
$$\sigma^2=E[(Y-\mu)^2]$$
When $\mu$ is unknown, we can replace it by the plug-in estimator $\overline Y$, thus getting the _plug-in variance estimator_ (divide by $n$):
$$S_n^2=\frac{1}{n}\sum_{i=1}^n(Y_i-\overline Y)^2$$

There is a second version, dividing by $n-1$:
$$S^2=\frac{1}{n-1}\sum_{i=1}^n(Y_i-\overline Y)^2$$
this is the _unbiased sample variance_.

>[!Tip]
>Because $\overline Y$ is computed from the same data, so the data sit slightly closer to $\overline Y$ than to the true $\mu$, which makes $S_n^2$ a bit too small on average. Dividing by $n-1$ instead of $n$ corrects that exactly: $E[S^2]=\sigma^2$, while $E[S_n^2] = \frac{n-1}{n}\sigma^2$.

---
### Sampling distributions
If the input $D_n$ is random, the output $h(D_n)$ is random too, since different samples give different averages, in practice $\hat\theta_n=h(D_n)$ _changes from sample to sample_.

The **sampling distribution** is the distribution of these values over all the samples of size $n$ we could draw, it answers to "if we repeated the whole experiment many times, how would our estimate vary?".

|           | Distribution of $Y_i$                    | Sampling distribution of $\hat\theta_n$   |
|-----------|------------------------------------------|-------------------------------------------|
| Describes | individual observations                  | the estimate computed from a whole sample |
| Example   | spread of single latencies (20 to 29 ms) | spread of sample averages (much narrower) |

For some estimators (the mean of normal data), we can _derive the sampling distribution with math_, for others (a median, a complicated formula), it's too hard.
>In real life we also can't repeat the experiment thousands of times.

The trick is: pretend we know the population, simulate many samples from it, and look at the results, this is the **Monte Carlo** methods, which just means "use repeated random simulation", and it works as follows:
1. **Fix a population model and $\theta$**: choose a distribution and a true parameter (e.g. $Y \sim N(\mu,\ \sigma^2)$). now we know the truth
2. **Generate a new sample $D_n^{(r)}$ from $P(\theta)$**: simulate $n$ observations (the superscript $(r)$ is just a label, it means: "the $r$-th simulated sample")
3. **Compute $\hat\theta_n^{(r)}$**: apply our estimator to that sample (e.g. take its average)
4. **Repeat for $r = 1,\dots,R$**: do steps 2 and 3 a large number of times
5. **Inspect the empirical distribution of the $R$ estimates**: we now have many numbers $\hat\theta_n^{(1)},\dots,\hat\theta_n^{(R)}$, so we plot a histogram, that histogram approximates the sampling distribution

This is the first sample:![[First sample histogram.png|522]]after this, we find its mean, and do the same thing for other samples, ending up with the _sampling distribution of the sample mean_:
![[Sampling distribution.png|514]]
The simulated sampling distribution is centered near the true value.
>Its normal shape is exact here because the observations themselves are Gaussian.

If the data are i.i.d. normal, the sample mean is _exactly normal_, centered at the true mean $\mu$, with variance $\sigma^2/n$, so its standard error is $\mathrm{SE}(\overline Y)=\sigma/\sqrt n$, meaning averages get more precise as $n$ grows.

It is possible to demonstrate that the _simulation error decreases as_ the number of Monte Carlo _repetitions $R$ grows_.

#### Central limit theorem
The **Central Limit Theorem (CLT)** says that even if the data is _not normal_, the sample mean is still **approximately** normal when $n$ is large.

Take i.i.d. $Y_1,\dots,Y_n$ from any distribution with mean $\mu$ and finite variance $\sigma^2$, then:
$$\frac{\sqrt n\,(\overline Y-\mu)}{\sigma} \xrightarrow{d} \mathcal N(0,1) \quad \text{as } n\to\infty$$
- $\overline Y - \mu$: how far the sample mean is from the truth (the error)
- Dividing by $\sigma/\sqrt n$ (which is the same as multiplying by $\sqrt n/\sigma$) standardizes it (this is the same $Z = \frac{X-\mu}{\sigma}$ idea from earlier, applied to $\overline Y$, whose standard error is $\sigma/\sqrt n$)
- $\xrightarrow{d}$ means "converges in distribution": the shape of the distribution of the left side gets closer and closer to the standard normal curve

Undoing the standardization:
$$\overline Y \overset{\text{approx}}{\sim} \mathcal N\!\left(\mu,\ \frac{\sigma^2}{n}\right)$$
This is the same formula seen before, but now it's only **approximate**, and it works for non-normal data.

---
### Point estimators
So far we have defined an estimator $\hat\theta_n$ and a true value $\theta$, there are three characteristics that measure how good it is:
- **Bias**: is it aimed at the right spot?
- **Variance / SE**: how much does it scatter?
- **MSE**: how bad is it overall?

#### Bias
$$\text{Bias}_\theta(\hat\theta_n) = E_\theta[\hat\theta_n] - \theta$$
In words: average of the estimates over many repeated samples, minus the truth.

- Bias $=0$: darts are centered on the bullseye, so the estimator is **unbiased**
- Bias $\ne 0$: darts are systematically off to one side

#### Variance and standard error
$$\text{Var}_\theta(\hat\theta_n) = E_\theta\!\left[(\hat\theta_n - E_\theta[\hat\theta_n])^2\right]$$

In words: average squared distance of the estimate from its own average.
This is the **scatter of the darts**, no matter where they land.

If the estimator is unbiased, $E[\hat\theta_n]=\theta$, so this becomes $E[(\hat\theta_n-\theta)^2]$.

$$\text{SE}_\theta(\hat\theta_n) = \sqrt{\text{Var}_\theta(\hat\theta_n)}$$
The **standard error** is just the square root, so it's in the same units as $\theta$.

>[!Tip] Remarks
>- **Unbiased**: correct _on average_, any single estimate will still be off
>- **Several unbiased estimators can exist**: (e.g. for a mean, both $\overline Y$ and "just use $Y_1$" are unbiased, but $\overline Y$ has far smaller variance, so prefer the one with smaller variance)
>- **Transforming breaks unbiasedness**: if $\overline Y$ is unbiased for $\mu$, then $\overline Y^2$ is generally not unbiased for $\mu^2$ (same reason $S$ is biased for $\sigma$ even though $S^2$ is unbiased for $\sigma^2$)
>- **Bias correction:** if we know the bias is a fixed amount $b$ that doesn't depend on $\theta$, just subtract it: $\hat\theta_n - b$ is unbiased
>- **$\overline Y$ and $S^2$ are unbiased** for $\mu$ and $\sigma^2$ (this is why we divide by $n-1$)

|                            | What it is                                                                   |
|----------------------------|------------------------------------------------------------------------------|
| $\text{Var}(\hat\theta_n)$ | how much an estimator varies across samples                                  |
| $S^2$                      | an estimator of the population variance $\sigma^2$, computed from one sample |
>$S^2$ is a _tool_ for estimating spread of the data, $\text{Var}(\hat\theta_n)$ is the spread of _any estimate_ (including $S^2$ itself, or $\overline Y$) across repeated samples.

#### Mean squared error
$$\text{MSE}_\theta(\hat\theta_n) = E_\theta[(\hat\theta_n-\theta)^2]$$

In words: average squared distance from the truth.
>This combines both problems (off-center and scattered) in one number.

$$\text{MSE} = \text{Var} + \text{Bias}^2$$
Considering the darts analogy: total error = scatter + (how far the center is from the bullseye)$^2$.
If unbiased, the bias term vanishes and MSE = variance.

**Why it matters:** a slightly biased estimator with much lower variance can have a _smaller MSE_ than an unbiased one, showing that unbiased isn't automatically the best.

#### Consistency
Bias, variance, and MSE judge an estimator at one fixed sample size $n$.
**Consistency** asks a different question: _what happens as $n$ grows?_ Does the estimator eventually approach the truth?

**Weak consistency**
$$\hat\theta_n \xrightarrow{P} \theta \quad\Longleftrightarrow\quad \text{for every } \varepsilon>0,\ \ P_\theta(|\hat\theta_n-\theta|>\varepsilon)\to 0$$
Pick any tolerance $\varepsilon$, however tiny, the probability that our estimate misses the truth by more than $\varepsilon$ shrinks to $0$ as $n\to\infty$.
>With enough data, being far off becomes very unlikely.

**Strong consistency:**
$$P_\theta\!\left(\lim_{n\to\infty}\hat\theta_n=\theta\right)=1$$
Here we follow one infinite sequence of estimates $\hat\theta_1,\hat\theta_2,\dots$ as we keep adding data, and it converges to $\theta$ with probability $1$.
>This is a stronger statement: weak says "at each large $n$, a miss is unlikely," strong says "the whole sequence settles on $\theta$ and stays there."

>[!Important]
>If an estimator is unbiased (or its bias goes to $0$) **and** its variance tends to $0$, then it converges to the truth.

**Unbiasedness is not consistency**
Two estimators of the mean $\mu$:

| Estimator                                    | Bias | Variance                   | Consistent? |
| -------------------------------------------- | ---- | -------------------------- | ----------- |
| $\hat\mu_n = Y_1$ (ignore all but the first) | 0    | $\sigma^2$ (never shrinks) | **No**      |
| $\overline Y$                                | 0    | $\sigma^2/n\to 0$          | **Yes**     |

Both are unbiased, but $Y_1$ ignores the extra data, so a million observations are no better than one: it never concentrates around $\mu$, whilst $\overline Y$ uses everything, so its scatter disappears.

>[!Important]
>Unbiased only means "correct on average."
>Consistency also needs the scatter to vanish with more data (the reverse also happens: an estimator can be biased yet consistent, like $S_n^2$, whose bias $-\sigma^2/n\to0$).

#### Efficiency
Which estimator is better when several are available?

- **Both unbiased**: pick the one with _smaller variance_ (e.g. if $\text{Var}(\hat\theta_1)<\text{Var}(\hat\theta_2)$, then $\hat\theta_1$ is more efficient)
- **Some biased**: variance alone is misleading, so compare MSE $=\text{Var}+\text{Bias}^2$. _Smaller MSE_ wins.

---
### Maximum likelihood estimator
Earlier we saw that for i.i.d. data the joint probability factorizes into a product.
Now we flip the viewpoint and _use that product to find the best parameter_, this is the  **maximum likelihood estimation (MLE)**.

#### Likelihood: data fixed, parameter varies
$$L_n(\theta; d_n) = \prod_{i=1}^n p_Y(y_i;\theta)$$

We use the same formula as before but we ask different questions.

|          | Probability view                           | Likelihood view                                        |
| -------- | ------------------------------------------ | ------------------------------------------------------ |
| Fixed    | $\theta$                                   | the data $y_1,\dots,y_n$                               |
| Varies   | the data                                   | $\theta$                                               |
| Question | "How likely is this data, given $\theta$?" | "Which $\theta$ makes the data we saw most plausible?" |

$p_Y$ is the pmf (for discrete data) or density (for continuous data), after plugin-in our observed $y_i$'s, what's left is a function of $\theta$ only.


Three coin flips, observed H, H, T, with $\theta = P(\text{heads})$:
$$L(\theta) = \theta\cdot\theta\cdot(1-\theta) = \theta^2(1-\theta)$$

Trying with a few values:

| $\theta$ | $L(\theta)$ |
| -------- | ----------- |
| 0.3      | 0.063       |
| 0.5      | 0.125       |
| 0.667    | 0.148       |
| 0.9      | 0.081       |
The peak is at $\theta = 2/3$, which is exactly the observed fraction of heads. that peak is the **MLE**, which is defined as:
$$\hat\theta_{ML}(d_n) = \arg\max_{\theta\in\Theta} L_n(\theta; d_n)$$

>[!Attention]
>The likelihood is **not a probability distribution for $\theta$**.
>It does not integrate to $1$ over $\theta$, and $\theta$ is a fixed unknown number here, not a random variable.
>
>$L(\theta)=0.148$ does not mean "$\theta$ has a $14.8\%$ chance", it only lets us _compare_ parameter values: a higher $L$ means the data fit that $\theta$ better.

#### Log-likelihood
$$\ell_n(\theta; d_n) = \log L_n(\theta; d_n) = \sum_{i=1}^n \log p_Y(y_i;\theta)$$
**Why bother with the log notation?**

1. _Numerical problem (underflow)_: multiplying many probabilities of about $0.1$ gets us to a very low causing an underflow
2. _Algebra_: sums are much easier to differentiate than products (recall that $\prod \to \sum$ is the whole point)

Maximizing the log is legitimate since only the height of the curve changes, not where the peak is.

```r
curve(4*log(x)-201*x,0,0.04,ylab="log-Likelihood",xlab=expression(lambda))
abline(v=4/201,lty=2)
```
![[Log-likelihood.png|584]]

#### Interior maximum: score equation
The **score** is just the slope of the log-likelihood curve:
$$U_n(\theta) = \frac{\partial \ell_n(\theta)}{\partial\theta}$$

Picture $\ell_n(\theta)$ as a hill. At the top of the hill the slope is flat, so the slope is 0:

$$U_n(\hat\theta_{ML}) = 0 \qquad \text{(the score equation)}$$

**This only applies if** the peak is in the **interior** of the parameter space (not at an edge) and $\ell_n$ is differentiable there.

The score equation supplies **candidate points**, not an automatic solution: a slope of $0$ also happens at the bottom of a valley or on a flat spot, so solving $U_n=0$ only gives _candidate_ points, we must check each one.

**Second derivative test:**
$$\frac{\partial^2 \ell_n}{\partial\theta^2}\Big|_{\hat\theta_{ML}} < 0$$
A negative second derivative means the curve bends downward, so the flat point is a **peak**, this guarantees a _local_ maximum.

**Then we also need to:**
- Compare with the _boundaries_ of $\Theta$ (the max could be at an edge)
- Confirm the peak is the _global_ maximum, not just a local one

#### Bernoulli/Binomial MLE
Run $n$ tests: $Y_i=1$ if test $i$ fails, $0$ if it passes, $p$ is the unknown failure probability, and $S=\sum Y_i$ is the _number of failures_.

**Likelihood**
The number of failures $S$ is Binomial:
$$L_n(p) = \frac{n!}{S!(n-S)!}\,p^S(1-p)^{n-S}$$
**Drop the constant**
The fraction $\frac{n!}{S!(n-S)!}$ doesn't contain $p$, so it only scales the curve up or down without moving the peak, we can ignore it:
$$L_n(p) \propto p^S(1-p)^{n-S}$$
>($\propto$ means "proportional to.") This is the same as the coin example: $\theta^2(1-\theta)$ was $S=2$, $n=3$.

**Log**
$$\ell_n(p) = S\log p + (n-S)\log(1-p)$$
**Differentiate** (this is the score)
$$U_n(p) = \frac{S}{p} - \frac{n-S}{1-p}$$
**Set to 0 and solve**
$$\frac{S}{p} = \frac{n-S}{1-p} \;\Longrightarrow\; S(1-p) = p(n-S) \;\Longrightarrow\; S = np \;\Longrightarrow\; \hat p_{ML} = \frac{S}{n} = \overline Y$$

The MLE of the failure probability is the observed fraction of failures.
>$3$ failures in $20$ tests gives $\hat p = 0.15$.

**Check it is a maximum** (second derivative):
$$\ell_n''(p) = -\frac{S}{p^2} - \frac{n-S}{(1-p)^2}$$
If $0<S<n$, both terms are negative (squares are positive, so each fraction is positive, and there is a minus sign in front), so $\ell_n''<0$ everywhere: the curve always bends downward, which means a _single peak_, so the stationary point is the unique global maximum.

There are **two edge cases**:
- _$S=0$ (no failures at all)_: $\ell_n(p)=n\log(1-p)$, which keeps increasing as $p$ decreases, the best value is $p=0$, the boundary
- _$S=n$ (every test fails)_: $\ell_n(p)=n\log p$, which increases as $p$ grows, the best value is $p=1$, the other boundary

In both cases the score equation has **no solution inside** $(0,1)$, so the peak is at the edge.
This is exactly the situation we warned about earlier: the formula $\hat p=S/n$ still gives the right answer (0 or 1), but the _derivation_ via the score equation doesn't apply.
![[Binomial log-likelihood.png|493]]

>[!Tip] MLE with tiny samples
>Saying $p=0$ after seeing 0 failures in 10 tests is a bit extreme, since it claims failures are impossible.
>>That's a weakness of MLE with tiny samples.

#### Gaussian MLE
Same recipe as before (likelihood -> log -> differentiate -> set to $0$), now with _two parameters instead of one_.

**Likelihood**
Multiply the normal density over all $n$ observations, the constant $(2\pi\sigma^2)^{-1/2}$ appears $n$ times, giving the power $-n/2$, the exponentials multiply, so their exponents add up into a sum:
$$L_n(\mu,\sigma^2) = (2\pi\sigma^2)^{-n/2}\exp\left\{-\frac{1}{2\sigma^2}\sum_{i=1}^n (y_i-\mu)^2\right\}$$
**Log**
The log kills the exponential and turns the power into a multiplier:
$$\ell_n(\mu,\sigma^2) = -\frac n2\log(2\pi\sigma^2) - \frac{1}{2\sigma^2}\sum_{i=1}^n(y_i-\mu)^2$$
**Differentiate with respect to $\mu$**
Only the last term contains $\mu$:
$$\frac{\partial \ell_n}{\partial\mu} = \frac{1}{\sigma^2}\sum_{i=1}^n (y_i-\mu) = 0 \;\Longrightarrow\; \sum y_i = n\mu \;\Longrightarrow\; \hat\mu_{ML}=\overline Y$$
The MLE of the mean is the sample average
>Note that $\sigma^2$ cancels, so this answer doesn't depend on it.

**Differentiate with respect to $\sigma^2$**
Treat $\sigma^2$ as a single symbol $v$:
$$\frac{\partial \ell_n}{\partial v} = -\frac{n}{2v} + \frac{1}{2v^2}\sum_{i=1}^n(y_i-\mu)^2 = 0 \;\Longrightarrow\; v = \frac1n\sum_{i=1}^n (y_i-\mu)^2$$
Since $\mu$ is unknown, plug in its MLE $\overline Y$:
$$\hat\sigma^2_{ML} = \frac1n\sum_{i=1}^n (Y_i-\overline Y)^2$$
>This is the same as the plug-in estimator $S_n^2$ from earlier, dividing by $n$.


We have to **remark an observation about the bias**:
$$E(\hat\sigma^2_{ML}) = \frac{n-1}{n}\sigma^2$$
So the variance MLE is slightly too small on average (bias $=-\sigma^2/n$), exactly as we saw for $S_n^2$:
- _Likelihood_ asks "which $\sigma^2$ makes my data most plausible?" and the answer has denominator $n$
- _Unbiasedness_ asks "which formula is right on average?" and the answer has denominator $n-1$.
>They are two different goals, so they give two different formulas.
>For large $n$ the difference is negligible (the MLE is still consistent).

![[Gaussian log-likelihood for mean latency.png|500]]![[Gaussian log-likelihood for latency variability.png|524]]
#### Gamma MLE
Durations (task times, file-transfer times) are positive and right-skewed, which a normal curve fits poorly, the [[Distribuzioni continue#Distribuzione gamma|Gamma distribution]] is designed for this.

**Parameters** (shape–rate form):
- $\alpha$ = _shape_: controls the look of the curve,  $\alpha<1$ piles up near $0$, $\alpha=1$ is the exponential, larger $\alpha$ gives a more symmetric, concentrated bump
- $\beta$ = _rate_: controls the scale, larger $\beta$ means shorter durations
$$E(Y)=\frac\alpha\beta,\qquad \mathrm{Var}(Y)=\frac{\alpha}{\beta^2}$$

**Log-likelihood**
$$\ell_n(\alpha,\beta) = n\alpha\log\beta - n\log\Gamma(\alpha) + (\alpha-1)\sum\log y_i - \beta\sum y_i$$
This comes from the same steps: multiply the densities, take the log, so the product becomes a sum.
$\Gamma(\alpha)$ is the Gamma function, a generalization of the factorial that normalizes the density.

**Score for $\beta$** (differentiate and set to $0$):
$$\frac{n\alpha}{\beta} - \sum y_i = 0 \;\Longrightarrow\; \hat\beta = \frac{\hat\alpha}{\overline y}$$
Since $E(Y)=\alpha/\beta$, matching the mean $\overline y=\alpha/\beta$ gives $\beta=\alpha/\overline y$.

**Score for $\alpha$**, after substituting $\hat\beta$, we get:
$$\log\hat\alpha - \psi(\hat\alpha) = \log\overline y - \frac1n\sum\log y_i$$
where $\psi$ is the _digamma function_ (the derivative of $\log\Gamma$).
>The right side is a number we can compute from the data: log of the average minus the average of the logs.
>The left side is a function of $\hat\alpha$ alone.

There is **no closed form**, so we cannot isolate $\hat\alpha$ with algebra, so we solve it _numerically_: a computer searches for the $\alpha$ that makes both sides equal, then we get $\hat\beta=\hat\alpha/\overline y$.

---
### Fisher information and Cramér–Rao bound
We have the MLE, two natural questions follow: **how precise can any estimator possibly be**, and **how is the MLE distributed**?

#### Score and Fisher information
**Score (one observation):** the slope of the log-density, as seen previously, but now for a _random_ observation $Y$:
$$U(\theta) = \frac{\partial}{\partial\theta}\log p_Y(Y;\theta)$$
Since $Y$ is random, $U(\theta)$ is random too.

The **mean of the score is $0$** (under regularity conditions):
$$E_\theta[U(\theta)] = 0$$
At the **true** $\theta$, the log-likelihood slope is positive for some samples and negative for others, and these cancel on average.
>That is why the score equation $U=0$ works as an estimating equation: on average it is satisfied at the truth.

**Fisher information** is defines as:
$$I_1(\theta) = E_\theta[U(\theta)^2] = -E_\theta\!\left[\frac{\partial^2}{\partial\theta^2}\log p_Y(Y;\theta)\right]$$

_Two equivalent forms_, each with its own intuition:
- **$E[U^2]$ = variance of the score** (since its mean is 0): if the score fluctuates a lot, the data are very sensitive to $\theta$, so they carry a lot of information
- **$-E[\ell'']$ = average curvature**: a sharply peaked log-likelihood (large negative second derivative) means $\theta$ is pinned down precisely, whilst a flat one means many $\theta$ values fit about equally well

For $n$ i.i.d. observations, _information adds up_:
$$I_n(\theta) = n\,I_1(\theta)$$

>[!Example] Fisher information using Bernoulli
$\ell(p)=y\log p+(1-y)\log(1-p)$, so:
>$$  
>-\ell''(p) = \frac{y}{p^2}+\frac{1-y}{(1-p)^2}  
>\;\Rightarrow\;  
>I_1(p)=\frac1p+\frac1{1-p}=\frac{1}{p(1-p)}  
>$$
>>Information is largest when $p$ is near 0 or 1 and smallest at $p=0.5$.

#### Cramér–Rao lower bound
$$\mathrm{Var}_\theta(T_n)\ \ge\ \frac{1}{I_n(\theta)}$$
For **any unbiased estimator** $T_n$, the variance cannot go below $1/I_n(\theta)$.
- More information $\Rightarrow$ lower possible variance
- An unbiased estimator that _reaches the floor_ is called **efficient** (the best possible)

>[!Example]  Cramér–Rao using Bernoulli
For Bernoulli, $I_n(p)=\frac{n}{p(1-p)}$, so any unbiased estimator of $p$ has
>$$\mathrm{Var}\ge\frac{p(1-p)}{n}$$
>
>And $\overline Y$ has variance exactly $p(1-p)/n$. So $\overline Y$ hits the bound: it is efficient.

>[!Warning]
>- **Only for unbiased estimators**: a biased estimator can have variance below the bound (it may still have a larger MSE)
>- **Regularity conditions are required**: the Uniform$(0,\theta)$ model fails them because the support (the range where the density is nonzero) depends on $\theta$, so the bound need not hold there

#### Asymptotic normality of the MLE
$$\sqrt n\,(\hat\theta_{ML}-\theta)\xrightarrow{d}\mathcal N\!\left(0,\ I_1(\theta)^{-1}\right)$$

This is the MLE version of the CLT seen previously:
- $\hat\theta_{ML}-\theta$ is the error, scaled by $\sqrt n$ so that it doesn't shrink to $0$
- In the limit it is normal, centered at $0$ (no asymptotic bias), with variance $1/I_1(\theta)$

**Equivalent forms**:
$$\hat\theta_{ML}\overset{\text{approx}}{\sim}\mathcal N\!\left(\theta,\ I_n(\theta)^{-1}\right)$$
>Dividing the variance $1/I_1$ by $n$ gives $1/(nI_1)=1/I_n$

The standardized version:
$$\sqrt{nI_1(\theta)}\,(\hat\theta_{ML}-\theta)\xrightarrow{d}\mathcal N(0,1)$$

>The extraction dropped the square root over $nI_1(\theta)$ in the text, but it must be there to standardize correctly.

---
### Gaussian sampling distributions
