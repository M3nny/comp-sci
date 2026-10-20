Starting with an example, let's assume an API should have a mean response time of 500 ms.

We sample requests and ask whether the data give _enough evidence_ that the true mean differs from 500 ms, this is a statistical decision problem because a different sample would give a different mean.

Let $D_n=(Y_1,\dots,Y_n)$ with $Y_i\stackrel{iid}{\sim}P_\theta$, in the example, $Y_i\stackrel{iid}{\sim}\mathcal N(\mu,\sigma^2)$ and the parameter of interest is $\mu$.
$$H_0:\mu=500\quad\text{versus}\quad H_1:\mu\neq 500$$
**Hypotheses** are _statements about the population_ (its parameters), _never about the observed sample_, the sample mean is simply what we observed.

There are various **types of alternatives**, and the direction is decided _before_ looking at the data:
- **Two-sided**: $H_0:\mu=\mu_0,\ H_1:\mu\neq\mu_0$
- **Upper (right) one-sided**: $H_0:\mu\le\mu_0,\ H_1:\mu>\mu_0$
- **Lower (left) one-sided**: $H_0:\mu\ge\mu_0,\ H_1:\mu<\mu_0$

Writing the hypothesis $H_0$ as an equality is often enough for calculations, because the boundary case $\mu=\mu_0$ is the "hardest to reject".
>The inequality form, states the real question more honestly, for example, if only slower latency matters, we would use the upper one-sided version.

### Test statistics and p-values
A **test statistic** is a function of the data, $T_n=t(D_n)$, designed so that unusual values under $H_0$ are evidence against $H_0$.

For example, let's use normal data with known $\sigma^2$, testing $H_0:\mu=\mu_0$.
We start with $T_n=\bar Y-\mu_0$, and under $H_0$, $\bar Y\sim\mathcal N(\mu_0,\sigma^2/n)$.

Dividing by the standard error $\sigma/\sqrt n$ gives a _standardized version_:
$$Z=\frac{\bar Y-\mu_0}{\sigma/\sqrt n}\ \sim\ \mathcal N(0,1)\quad\text{under }H_0 .$$
This is the **z-test**, in words, $Z$ measures how many standard errors the sample mean is from the hypothesized value.

The **distribution of $T_n$** when $H_0$ is true can be summarized as:

|Setting|Statistic|Null distribution|
|---|---|---|
|Normal mean, $\sigma$ known|$Z=(\bar Y-\mu_0)/(\sigma/\sqrt n)$|$\mathcal N(0,1)$|
|Normal mean, $\sigma$ unknown|$T=(\bar Y-\mu_0)/(S/\sqrt n)$|$t_{n-1}$|
|Normal variance|$(n-1)S^2/\sigma_0^2$|$\chi^2_{n-1}$|
|Ratio of two normal variances|$S_1^2/S_2^2$|$F_{n_1-1,\,n_2-1}$|

The **p-value** is the probability, if $H_0$ were true, of getting a test statistic at least as extreme as the one we observed:

| Alternative       | p-value                                                        |
| ----------------- | -------------------------------------------------------------- |
| right ($>$)       | $p=\mathbb P(T_n\ge t_{obs}\mid H_0)$                          |
| left ($<$)        | $p=\mathbb P(T_n\le t_{obs}\mid H_0)$                          |
| two-sided ($\ne$) | $p=\mathbb P(\lvert T_n\rvert\ge\lvert t_{obs}\rvert\mid H_0)$ |


A _small p-value_ means the observed statistic is far from where most of the probability sits under $H_0$, so the data is "surprising" if $H_0$ is true.

### Significance tests and critical regions
Let's now assume the following case: $H_0:\mu\le500$ vs $H_1:\mu>500$ (only slower latency matters).

**Rule 1 (p-value)**
Given $\alpha$, reject $H_0$ if $p\le\alpha$.

**Rule 2 (critical region)**
Equivalently, reject if the data fall in
$$\mathcal R=\{D_n:\ t(D_n)>c_\alpha\},\qquad \sup_{\theta\in\Theta_0}\mathbb P_\theta(D_n\in\mathcal R)\le\alpha .$$
In words, we choose the critical value $c_\alpha$ so that, in the worst case allowed by $H_0$, the probability of landing in the rejection region is at most $\alpha$.

#### Sided z-test
Let $Y\sim\mathcal N(\mu,\sigma^2)$ with $\sigma$ known.
$H_0:\mu=\mu_0$ vs $H_1:\mu>\mu_0$.
$$Z=\frac{\bar Y-\mu_0}{\sigma/\sqrt n},\qquad \text{reject if } Z>z_\alpha,\quad \mathbb P(Z>z_\alpha)=\alpha .$$
For $\alpha=0.05$, $z_\alpha=1.645$ (R: `qnorm(0.05, lower.tail=FALSE)`).

>[!Example]
>**Right-sided**
>Data $(514,557,492,531)$ ms, $\sigma=30$ known, $\mu_0=500$, $\alpha=0.05$.
>- $\bar y=523.5$, standard error $=30/\sqrt4=15$
>- $z_{obs}=\dfrac{523.5-500}{15}=1.567$
>- Critical value $1.645$, p-value $=\mathbb P(Z>1.567)=0.059$
>- Since $1.567<1.645$ (equivalently $0.059>0.05$): _do not reject $H_0$_
>![[Right-sided z-test.png|400]]
>
>**Left-sided**
>Data $(484,477,492,501)$, $H_0:\mu\ge500$, $H_1:\mu<500$.
>- $\bar y=488.5$
>- $z_{obs}=-0.767$
>- Critical value $-1.645$, p-value $=0.222$, so _do not reject_
>
>Here we reject if $z_{obs}<z_\alpha=-1.645$.
>
>![[Left-sided z-test.png|400]]

If departures in either direction are scientifically relevant, we can use the **two-sided version**:
$$\text{reject if } |Z|>z_{\alpha/2},\qquad p=2\times\mathbb P(Z\ge|z_{obs}|)=2\{1-\Phi(|z_{obs}|)\}.$$
The area $\alpha$ is split into two tails of $\alpha/2$ each. For $z_{obs}=2.33$, $p=0.0198$.
![[Two-sided z-test.png|400]]
#### The frequentist logic of testing
1. Specify $H_0$ and $H_1$
2. Choose $\alpha$ _before_ seeing the result
3. Build a statistic whose null distribution is known (exactly or approximately)
4. Define a rejection region with probability at most $\alpha$ under $H_0$
5. Observe the data and apply the rule

It is **asymmetric**, which means we only ever control the error of wrongly rejecting $H_0$, "Not rejecting" is not the same as proving $H_0$.

### Type 1 error, type 2 error and power
There are **two kinds of mistakes**:

|Decision \ Truth|$H_0$ true|$H_1$ true|
|---|---|---|
|Reject $H_0$|**Type I error** (false alarm), probability $\alpha$|Correct rejection, probability $1-\beta$|
|Do not reject $H_0$|Correct, probability $1-\alpha$|**Type II error** (missed detection), probability $\beta$|
$$\alpha=\sup_{\theta\in\Theta_0}\mathbb P_\theta(\text{reject }H_0),\qquad \beta(\theta)=\mathbb P_\theta(\text{do not reject }H_0),\ \theta\in\Theta_1,$$$$\pi(\theta)=\mathbb P_\theta(\text{reject }H_0)=1-\beta(\theta)\quad(\text{the power function}).$$

**Power** is the probability of detecting an effect that really exists, as a function of the true parameter value.

>[!Example]
>$\sigma=2$ ms, testing $\mu\le500$ vs $\mu>500$, where a true shift to $\mu=501$ is small but operationally relevant.
>
>Two questions: how often do we raise a false alarm when on target ($\alpha$), and how often do we detect the shift at $\mu=501$ (power)?
>
>![[Type 1 and 2 errors.png|400]]

**For fixed** $n$, _lowering_ $\alpha$ usually _raises_ $\beta$: demanding stronger evidence means fewer false alarms but also more missed real effects, while **increasing** $n$ _improves both_, because the two bell curves separate.

#### Power of the one-sided z-test
Reject when $Z=\frac{\bar Y-\mu_0}{\sigma/\sqrt n}>z_\alpha$.
If the true mean is $\mu>\mu_0$, the same statistic is no longer centered at 0:
$$Z^*\sim\mathcal N\!\left(\frac{\mu-\mu_0}{\sigma/\sqrt n},\,1\right).$$
Therefore:

$$\boxed{\pi(\mu)=\mathbb P(Z^*>z_\alpha)=1-\Phi\!\left(z_\alpha-\frac{\mu-\mu_0}{\sigma/\sqrt n}\right)}$$
In words: the quantity $\frac{\mu-\mu_0}{\sigma/\sqrt n}$ is the "signal-to-noise ratio", power grows with the effect size $\mu-\mu_0$, grows with $n$, and shrinks with the noise $\sigma$.

#### What influences a p-value?
- **Effect size**: bigger departures from $H_0$ give smaller p-values
- **Sample size**: larger $n$ gives smaller standard errors, so even a trivial 1 ms shift can become “significant” without being practically important
- **Noise**: more variability gives larger p-values
- **Test direction**: a pre-specified one-sided test puts all of $\alpha$ in one tail and is more powerful in that direction
- **Null value and null distribution**: the p-value is always calibrated against $H_0$
- **Assumptions and test choice**: changing the reference distribution or variance estimator changes the p-value

### Wald tests
Let's say a flaky CI test fails in $x=118$ of $n=200$ runs, is the failure probability really $0.5$?
$$Y_i=\begin{cases}1&\text{fails}\\0&\text{passes}\end{cases},\quad Y_i\stackrel{iid}{\sim}\mathrm{Bernoulli}(p),\qquad H_0:p=0.5\ \text{vs}\ H_1:p\ne0.5$$
The [[02 - Point and interval estimation#Maximum likelihood estimator|MLE]] is $\hat p=\frac1n\sum Y_i$ (the observed failure fraction), and for large $n$, MLEs are approximately normal around the true value.

If $\dfrac{\hat\theta-\theta}{\widehat{\mathrm{se}}(\hat\theta)}\xrightarrow{d}\mathcal N(0,1)$, then for $H_0:\theta=\theta_0$:
$$Z_W=\frac{\hat\theta-\theta_0}{\widehat{\mathrm{se}}(\hat\theta)}\xrightarrow{d}\mathcal N(0,1),\qquad\text{reject if }|Z_W|>z_{1-\alpha/2}.$$

Equivalently, $W=Z_W^2\xrightarrow{d}\chi^2_1$.

In words: we measure how many estimated standard errors the estimate is from the hypothesized value.

**Assumptions**: it is asymptotic (large-sample), not exact, it needs independent observations, a consistent and asymptotically normal estimator, and a true parameter not too close to problematic boundaries (e.g. $p$ near 0 or 1).

#### Wald vs Score
Both statistics have the same numerator and **differ only in which variance is used** in the denominator.
$\widehat{\mathrm{Var}}(\hat p)=\hat p(1-\hat p)/n$.
$$Z_S=\frac{\hat p-p_0}{\sqrt{p_0(1-p_0)/n}}\ \ (\text{Score / classic z-test: variance under }H_0)$$ $$Z_W=\frac{\hat p-p_0}{\sqrt{\hat p(1-\hat p)/n}}\ \ (\text{Wald: plugs in the estimate }\hat p)$$Both are asymptotically $\mathcal N(0,1)$ but _differ in finite samples_.

Recalling the flaky test ($\hat p=0.59$):

| Method | Statistic | p-value |
| ------ | --------- | ------- |
| Wald   | 2.5879    | 0.0097  |
| Score  | 2.5456    | 0.0109  |

>Both reject $p=0.5$ at 5%.

#### When Wald fails
The **normal approximation is poor** _when $np_0$ or $n(1-p_0)$ is small_ (both should be $\gtrsim5$–$10$).

For example: $n=10$ runs with 1 failure, $p_0=0.5$.
The Wald p-value is $2\times10^{-5}$ while the exact binomial test gives $0.0215$, the lesson is that Wald is not wrong, but its validity depends on asymptotics, and small or extreme samples violate them.

#### Test-confidence interval duality
For many procedures, a two-sided level-$\alpha$ test rejects $H_0:\theta=\theta_0$ exactly when the $(1-\alpha)$ confidence interval excludes $\theta_0$.

With known $\sigma$:
$$\bar Y\pm z_{1-\alpha/2}\frac{\sigma}{\sqrt n}.$$
A confidence interval is more informative than a p-value because it shows direction, magnitude, and precision ("between 495 and 530 ms" is more actionable than "$p=0.03$").

The duality holds only if the test and interval use the same model, standard error, sidedness and level.

### Classical parametric tests
Each test is valid only under stated assumptions, and those assumptions are part of the claim.

| Test               | Assumptions                                          | $H_0$                   | Null distribution       | R                         |
| ------------------ | ---------------------------------------------------- | ----------------------- | ----------------------- | ------------------------- |
| One-sample z       | iid, normal for exactness, $\sigma$ known            | $\mu=\mu_0$             | $\mathcal N(0,1)$       | manual                    |
| One-sample t       | iid normal, $\sigma$ unknown                         | $\mu=\mu_0$             | $t_{n-1}$               | `t.test`                  |
| Paired t           | independent pairs, differences iid normal            | $\mu_D=0$               | $t_{n-1}$               | `t.test(paired=TRUE)`     |
| Welch two-sample t | independent groups, normality helps in small samples | $\mu_1=\mu_2$           | approx. $t$             | `t.test`                  |
| Variance test      | iid normal                                           | $\sigma^2=\sigma_0^2$   | $\chi^2_{n-1}$          | manual                    |
| Two-variance F     | independent normal samples                           | $\sigma_1^2=\sigma_2^2$ | $F$                     | `var.test`                |
| Proportion test    | independent Bernoulli trials, large counts           | $p=p_0$                 | approx. normal/$\chi^2$ | `prop.test`, `binom.test` |
| Two-proportion     | same, two groups                                     | $p_1=p_2$               | approx. normal/$\chi^2$ | `prop.test`, `binom.test` |

#### One-sample t-test
Used when $\sigma$ is **unknown**: replace $\sigma$ by $S$, this makes the null distribution a Student-$t$ (which has heavier tails than the normal, reflecting the extra uncertainty).
$$T=\frac{\bar Y-\mu_0}{S/\sqrt n}\sim t_{n-1}\ \text{under }H_0,\qquad S^2=\frac1{n-1}\sum_{i=1}^n(Y_i-\bar Y)^2 .$$

#### Paired t-test
Use when the **same units are measured twice** (e.g. the same endpoints before and after enabling a cache).

The two samples are not independent, so we must keep the pairing, define the differences $D_i=X_i-Y_i$ and run a one-sample t-test on them:
$$H_0:\mu_D=0,\qquad T_n=\frac{\bar D-\mu_D}{s_D/\sqrt n}\ \sim_{H_0}\ t_{n-1}.$$

#### Two-sample t-test
Compares **means of two_independent groups**, the parameter is $\Delta=\mu_A-\mu_B$.

**Welch’s test** (no equal-variance assumption, which is R's default):
$$T_n=\frac{\bar X-\bar Y}{\sqrt{S_x^2/n_x+S_y^2/n_y}}\ \sim_{H_0}\ t_{df},$$
with degrees of freedom from the approximate Welch–Satterthwaite formula, for large samples $T_n\to Z$.

**Pooled Student t-test** (assumes $\sigma_x^2=\sigma_y^2$):
$$T=\frac{\bar X-\bar Y}{\sqrt{S_p^2(1/n_x+1/n_y)}}\sim t_{n_x+n_y-2},\qquad S_p^2=\frac{S_x^2(n_x-1)+S_y^2(n_y-1)}{n_x+n_y-2}.$$
$S_p^2$ is a weighted average of the two sample variances, in R, `t.test(x,y)` is Welch and `var.equal=TRUE` gives the pooled test.
>Welch is generally the safer default.

#### Test for a variance
Let's say we are dealing with network jitter, the expected variance is $\sigma_0^2=1$ ms². 
Useful because variability can worsen even if the mean doesn’t.
$$Q=\frac{(n-1)S^2}{\sigma_0^2}\sim\chi^2_{n-1}\ \text{under }H_0$$
The chi-square is asymmetric, so the two-sided p-value is:
$$p=2\times\min\{\Pr(\chi^2_{n-1}\le Q_{obs}),\ \Pr(\chi^2_{n-1}\ge Q_{obs})\}$$

#### Comparing two variances
Let's say we are comparing the latencies of Frankfurt vs Milan CDN latency: $n_1=9$, $n_2=8$. With $\rho=\sigma_1^2/\sigma_2^2$ and $H_0:\rho=1$:
$$F=\frac{S_1^2}{S_2^2}\sim F_{n_1-1,\,n_2-1}\text{ under }H_0$$
Observed: $s_F^2=0.139$, $s_M^2=0.900$, so $F_{obs}=0.154$, $p=0.017$.

Milan's latency is significantly more variable, the 95% CI for the variance ratio is $(0.032,\,0.702)$, which excludes 1.

#### Two proportions
Let's now say we are dealing with the failure rate of the flaky test on self-hosted vs cloud runners.
$X_k\sim\mathrm{Binomial}(n_k,p_k)$ independently, $\hat p_k=X_k/n_k$, and $H_0:p_1=p_2$.

Under $H_0$ both share a common $p$, estimated by the pooled proportion:
$$\hat p_{pool}=\frac{X_1+X_2}{n_1+n_2},\qquad Z=\frac{\hat p_1-\hat p_2}{\sqrt{\hat p_{pool}(1-\hat p_{pool})\left(\frac1{n_1}+\frac1{n_2}\right)}}\ \dot\sim\ \mathcal N(0,1),\qquad X^2=Z^2\ \dot\sim\ \chi^2_1$$

### Likelihood ratio (LR) tests
Instead of inventing a statistic, we ask "how much likelihood do we lose by forcing the parameter to obey $H_0$?"

**Likelihood** is the probability (density) of the observed data viewed as a function of the parameter.
$$\hat\theta_0=\arg\max_{\theta\in\Theta_0}L_n(\theta)\ (\text{best fit under }H_0),\qquad \hat\theta=\arg\max_{\theta\in\Theta}L_n(\theta)\ (\text{best fit overall})$$ $$\Lambda(D_n)=\frac{L_n(\hat\theta_0)}{L_n(\hat\theta)}\le 1$$
A small $\Lambda$ means $H_0$ fits much worse than the unrestricted model, which is evidence against $H_0$.

**Wilks’ theorem (asymptotic):**
$$LR=-2\log\Lambda=2\{\ell(\hat\theta)-\ell(\hat\theta_0)\}\xrightarrow{d}\chi^2_d,\qquad d=\dim(\Theta)-\dim(\Theta_0)$$
Here $d$ is the number of parameters that $H_0$ pins down.
It can fail for boundary parameters, non-identifiable models, small samples and other non-regular settings.

### Multiple testing
Assume we are screening $m=10{,}000$ genes, each tested at $\alpha=0.05$.
If no gene truly differs, the expected number of false discoveries is:
$$\mathbb E(V)\le m_0\alpha,\qquad m_0=m=10{,}000\ \Rightarrow\ \mathbb E(V)=500$$
We would get hundreds of "predictive features" from pure noise.
<u>Each individual test is valid, but the family of decisions is not under control.</u>

#### Family-wise error rate (FWER)
For $m$ independent true nulls, each tested at level $\alpha$:
$$\mathrm{FWER}=\mathbb P(V\ge1)=1-(1-\alpha)^m .$$
For $m=100$, $\alpha=0.05$: $1-0.95^{100}\approx0.994$. A figure shows this probability rising toward 1 as $m$ grows, even for $\alpha=0.01$ and $0.001$.

Before going forward we introduce some new notation.

|Symbol|Meaning|
|---|---|
|$m$|total number of hypotheses|
|$m_0$|number of true nulls|
|$V$|false positives (Type I errors)|
|$S$|true positives|
|$U$|true negatives|
|$W$|false negatives (Type II errors)|
|$R=V+S$|total rejections|

#### Controlling FWER
**Bonferroni**
Reject $H_{0j}$ if
$$p_j\le\frac\alpha m\quad\Longrightarrow\quad \mathrm{FWER}\le\alpha .$$
It needs no independence, it is simple and valid but _conservative_ when $m$ is large.

**Holm step-down**
Sort the p-values $p_{(1)}\le\dots\le p_{(m)}$ and compare:
$$p_{(j)}\le\frac{\alpha}{m+1-j}$$
Reject hypotheses in order until the first failure, then stop.
>Holm controls FWER, works under any dependence, and is uniformly more powerful than Bonferroni (so it is generally preferable).

Let's use for example ($m=5$, $p=0.006,\,0.918,\,0.012,\,0.601,\,0.045$):

| Test | $p$   | Bonferroni adj. | Holm adj. | BH adj. |
| ---- | ----- | --------------- | --------- | ------- |
| H1   | 0.006 | 0.030           | 0.030     | 0.030   |
| H2   | 0.918 | 1               | 1         | 0.918   |
| H3   | 0.012 | 0.060           | 0.048     | 0.030   |
| H4   | 0.601 | 1               | 1         | 0.751   |
| H5   | 0.045 | 0.225           | 0.135     | 0.075   |

Bonferroni rejects only H1, while Holm and BH reject H1 and H3.

#### False discovery rate (FDR)
**FWER avoids even one false positive**, which is _appropriate when $m$ is small_, mistakes are costly, and the analysis is confirmatory.

With thousands of tests, exploratory work may prefer to tolerate a small fraction of false discoveries:
$$\mathrm{FDP}=\frac VR\ (\text{false-discovery proportion}),\qquad \mathrm{FDR}=\mathbb E\!\left(\frac VR\right)\le q$$
Controlling FDR at $q$ means that, over repeated experiments, the _expected fraction of false discoveries among our rejections_ is at most $q$.

**Benjamini–Hochberg (BH)**
With sorted p-values:
$$L=\max\left\{j:\ p_{(j)}\le\frac{qj}{m}\right\},\qquad\text{reject all hypotheses with }p_j\le p_{(L)}$$
_BH looks for the largest $j$ that passes_, and then rejects everything up to it, which makes it less strict than Holm.
>Under independence it controls FDR at $\le q\,m_0/m\le q$, it also holds under certain positive dependence (PRDS), but not for arbitrary dependence, where Benjamini–Yekutieli is the more conservative alternative.

#### Simulation
Let's assume $m=1000$ genes, 30 controls vs 30 patients, and 50 genes truly shifted by $\delta=1.4$ and 950 are pure noise.

|Method|Rejected|False pos.|True pos.|FDP|
|---|---|---|---|---|
|Unadjusted|83|33|50|0.398|
|Bonferroni|41|0|41|0|
|Holm|41|0|41|0|
|BH|50|1|49|0.02|

- Unadjusted testing has $\sim$ 40% false discoveries
- Bonferroni/Holm are safe but miss 9 real signals
- BH keeps almost all signals with a tiny FDP

