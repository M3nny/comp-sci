### R basics
**Assignments** use `<-`:
```r
a <- 3.14
name <- "Brussels"
is_weekend <- FALSE
cat(a, name, is_weekend, "\n")
```

**Vectors** are created with `c()`:
```r
heights <- c(168, 175, 181, 172, 177)
```

The standard method `length()` is used to take the length of various objects such as strings and vectors.

**Common statistical methods** applied to a viable data structure are:
- `mean()`
- `median()`
- `sd()`
- `min() max()`
- `sum()`

Running `summary()` returns some of them:
```r
print(summary(heights))
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  168.0   172.0   175.0   174.6   177.0   181.0
```

#### Dataframes
**Dataframes** are tables where each row might use different types, but it has to have the same number of columns, and they can also be summarized.
```r
students <- data.frame(
	id = 1:6,
	group = c("A", "A", "B", "B", "B", "B"),
	score = c(12, 15, 11, 18, 16, 14),
	passed = c(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE)
)

summary(students)
```

We can _access_ a row with `dataframe[["row_name"]]` or `dataframe$row_name`, we can _filter rows_ with `students[students$group == "A"]`.

#### Functions
We can create **functions** with defaults like in Python.
```r
standardize <- function(x) {
	(x - mean(x)) / sd(x)
}
standardize(students$score)
```

#### Randomness and reproducibility
```r
set.seed(1)

sample(c("H", "T"), size = 10, replace = TRUE)
die <- sample(1:6, size = 1000, replace = TRUE)

table(die)
#> die
#> 1 2 3 4 5 6
#> 154 152 148 177 191 178
```

---
### Probability
A **random experiment** is a process whose _possible outcomes are known_, but whose _realized outcome is uncertain_.
We will use $\Omega$ as the **sample space** (set) of possible outcomes, and define an **event** as a subset of the sample space.
```r
Omega <- 1:6
A <- Omega[Omega %% 2 == 0]
B <- Omega[Omega >= 4]
```

**Set operations**:
- `union(A, B)`
- `intersect(A, B)`
- `setdiff(A, B)`

A probability satisfies:
$$0\leq P(A)\leq1\quad P(\Omega)=1$$
$$P(A^c)=1-P(A)$$
$$P(A\cup B)=P(A)+P(B)-P(A\cap B)$$
>If $A$ and $B$ are _disjoint_, then $P(A\cap B)=0$.

**Conditional probability**:
$$P(A|B)=\frac{P(A\cap B)}{P(B)},\quad P(B)>0$$
Events $A$ and $B$ are **independent** if:
$$P(A\cap B)=P(A)P(B)$$
As a consequence:
$$P(A|B)=P(A)$$
>Independence _is not_ the same as mutual exclusivity.

Let $B_1,...,B_k$ form a _partition of the sample space_, then:
$$P(A)=\sum_{i=1}^kP(A|B_i)P(B_i)$$
By the [[Probabilità condizionata#Teorema di Bayes|Bayes rule]] we can _reverse the conditioning direction_:
$$P(B_i|A)=\frac{P(A|B_i)P(B_i)}{P(A)}=\frac{P(A|B_i)P(B_i)}{\sum_jP(A|B_j)P(B_j)}$$
---
### Random variables
A **random variable** maps the outcome of a random experiment to a number $\in[0,1]$ called probability.

We're going to use upper-case letters such as $X$ for the random variable and a lower-case letter $x$ for a realized value.

We attach to the random variable some specific mathematical function $P(x)$ that gives for each $x\in X$ the probability that $X$ assumes the value $x$.
$$Pr(Z=z)$$
It has to satisfy $Pr(Z)\geq0$ and $\sum_{z\in Z}P(Z=z)=1$.

For example: toss three coins and let $X=\text{number of heads}$, its **support** is $S_X=\{0,1,2,3\}$.

A **discrete RV** has a _finite or countable support_ (e.g. number of heads), while a **continuous RV** takes values on _intervals of the real line_ (e.g. time, height).

#### PMF, PDF and CDF
For a _discrete RV_, the **probability mass function (PMF)** is:
$$p_X(x)=P(X=x)$$
For a _continuous RV_, the **probability density function (PDF)** is a continuous function $f_X(x)$, a well known function is the [[Distribuzioni continue#Normale (o gaussiana)|normal random variable]]:
$$f_X(x)=\frac{1}{\sqrt{2\pi\sigma^2}}\exp\left(-\frac{(x-\mu)^2}{2\sigma^2}\right),\quad X\sim\mathcal{N}(\mu,\sigma^2)$$
Interval probabilities are integrals of the density as follows:
$$\int_{-2}^1f_Z(u)du$$
For _either type_, the **cumulative distribution function (CDF)** is:
$$F_X(x)=P(X\leq x)$$

#### Expected value, variance and standard deviation
For a _discrete RV_ , the **expected value** $E(X)$ is the _probability-weighted average_ of its possible values.

It can also be interpreted as the _long-run average of $X$ over many repetitions_ of the same random experiment:
$$E(X)=\sum_xxP(X=x)=\mu$$
For a _continuous RV_, it has to be calculated using an integral in order to consider an infinite sum of values:
$$E(X)=\int_{S_X}xf(x)dx=\mu$$
The **variance** $Var(X)$ is the average difference between the expected values.
The general form can be calculated as:
$$Var(X)=E[(X-E(X))^2]=E(X^2)-[E(X)]^2$$
Specifically, for _discrete RV_:
$$E(X^2)=\sum_{x\in S_X}x^2P(X=x)$$
and for _continuous RV_:
$$E(X^2)=\int_{x\in S_X}x^2f(x)dx$$

Other quantities of interest are the **moments of a distribution**:
$$\mu_r=E(X^r)=\int_{x\in S_X}x^rf(x)dx$$
>The moment of order $r=1$ is the mean of $X$.

The **standard deviation** is simply:
$$SD(X)=\sqrt{Var(X)}$$
Some **important properties**:
- $E(aX+b)=aE(X)+b$
- $Var(aX+b)=a^2Var(X)$
- $E(X+Y)=E(X)+E(Y)$, $\forall X,Y$
- $Var(X+Y)=Var(X)=Var(Y)$, $\forall$ <u>independent</u> $X,Y$

### Empirical vs theoretical quantities
A **probability model** describes the _distribution of a random variable_.
A dataset is a collection of observed realizations from some data-generating process.

**Simulation** makes this distinction concrete, usually the **empirical mean and variances** are close to the theoretical values.
>As we increase the simulations, the empirical and theoretical values become closer.

---
### Common distributions
| Prefix | Meaning                | Typical question                              |
| ------ | ---------------------- | --------------------------------------------- |
| `d`    | density / mass         | Point probability (discrete) or density value |
| `p`    | cumulative probability | Compute $P(X \le x)$                          |
| `q`    | quantile               | Find $x$ from a cumulative probability        |
| `r`    | random generation      | Simulate values                               |

Example: $X=\text{number of heads in 10 fair tosses}$.
```r
# P(X = 6)
dbinom(6, size = 10, prob = 0.5)

# P(X <= 6)
pbinom(6, size = 10, prob = 0.5)

# 95th percentile
qbinom(0.95, size = 10, prob = 0.5)

# Simulate 12 observations
rbinom(12, size = 10, prob = 0.5)
```

A **normal random variable** is written as:
$$X\sim N(\mu,\sigma^2)$$
It is continuous, symmetric around $\mu$, and has:
$$E(X)\mu,\quad Var(X)=\sigma^2$$
We can define a **standard** normal RV as:
$$Z=\frac{X-\mu}{\sigma}$$
then $Z\sim N(0,1)$.

Example: $X\sim N(100,15^2)$.
```r
mu <- 100
sigma <- 15

# P(X <= 120)
pnorm(120, mean = mu, sd = sigma)

# P(X > 120)
pnorm(120, mean = mu, sd = sigma, lower.tail = FALSE)

# 95th percentile
qnorm(0.95, mean = mu, sd = sigma)
```

