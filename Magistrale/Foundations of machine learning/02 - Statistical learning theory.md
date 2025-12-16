Statistical Learning Theory (SLT) deals mainly with **supervised learning** problems, where the question of learning amounts to estimating a functional relationship between the input and the output spaces:
$$f:X\to Y$$
- $X$ is the input space
- $Y$ is the output space, typically in the range $\{-1,+1\}$

Such mapping $f$ is called a **classifier**, and in order to find it we use a **classification algorithm** which takes the training (labeled) data and outputs $f$.

In SLT there are the following assumptions:
- There exists a probability distribution $P$ on $X\times Y$
- The training samples are sampled independently from $P$

>In particular, $P$ is fixed and unknown at the time of learning.

In order to estimate how good a function $f$ is when used as a classifier, we use a **loss function** which measures the cost of miss-classifying an instance.
The simplest loss is the **0-1 loss**:
$$\ell(X,Y,F(X))=\begin{cases}1&\text{if }f(x)\neq Y\\0&\text{otherwise}\end{cases}$$
The **risk** of a function is defined as the average loss, and the best classifier is the one with the smallest risk $R(f)$:
$$R(f):=\mathbb E(\ell((X,Y,f(X)))$$

### The classification problem
The "best", but also impractical classifier is the **Bayes classifier**:
$$f_{Bayes}(x):=\begin{cases}1&\text{if }P(Y=1|X=x)\geq0.5\\-1&\text{otherwise}\end{cases}$$

In practice, it is impossible to compute it, since $P$ unknown to the learner.

We recall that the **Bayes' theorem** is defined as:
$$P(h|e)=\frac{P(e|h)P(h)}{P(e)}$$

But, not only it is impossible to compute the Bayes error, but also the risk of a function $f$ cannot be computed without knowing $P$.

### Nearest neighbor
Thomas Cover and Peter Hart showed that:
$$R(f_{Bayes})\leq R_\infty\leq 2R(f_{Bayes})$$
Where $R_\infty$ denotes the expected error rate of NN when the sample size tends to infinity.

#### Kernel rules
Instead of fixing the number of neighbors to classify a new point $x$, we might consider fixing a distance $h$ and taking a majority vote among the labels that fall within that distance.

We define the **kernel** (i.e. Parzen window) as follows:
$$K(\overline x)=\begin{cases}1&\text{if }||\overline x||\leq 1\\0&\text{otherwise}\end{cases}$$
and define the vote counts as:
$$v_n^0(\overline x)=\sum_{i=1}^nI_{\{y_i=0\}}K\left(\frac{\overline x-\overline x_i}{h}\right)$$
$$v_n^1(\overline x)=\sum_{i=1}^nI_{\{y_i=1\}}K\left(\frac{\overline x-\overline x_i}{h}\right)$$
then, assign $x$ to the class $0$ iff $v_n^0(x)\geq v_n^1(x)$.

### The ERM principle
Instead of looking for a function which minimizes the true risk $R(f)$, we try to find one which minimizes the _empirical risk_, which does not need to know the true distribution $P$:
$$R_{emp}(f)=\frac{1}{n}\sum_{i=1}^n\ell(X_i,Y_i,f(X_i))$$

Given training data $(X_1,Y_1),...,(X_n,Y_n)\in X\times Y$, a function space $\mathcal F$ and a loss function, we define the classifier $f_n$ as:
$$f_n:=\arg\min_{f\in\mathcal{F}}R_{emp}(f)$$
Which is in words, the model with the smallest empirical risk.
This is called **empirical risk minimization (ERM)**.

A fundamental result of SLT is that the set of rules in $\mathcal F$ cannot be too rich, where the richness of $\mathcal F$ is measured by its **VC dimension** (later discussed).

Ideally we want to make $R(f_n)-R(F_{Bayes})$ as small as possible, as $n\to\infty$, hence denoting by $f_\mathcal F$ the best classifier in $\mathcal F$, the difference can be decomposed as:
$$R(f_n)-R(f_{Bayes})=\underbrace{(R(f_n)-R(f_\mathcal{F}))}_{\text{Estimation error}}+\underbrace{(R(f_\mathcal{F})-R(f_{Bayes}))}_{\text{Approximation error}}$$
Which is in words: when using ERM, our classifier $f_n$ may be worse than the optimal Bayes classifier $f_{Bayes}$, hence the total gap in performance can be split in two sources of error:
- **Estimation error (variance)**: caused by finite data, even if $\mathcal F$ contains a perfect classifier, we may not find it because we only see $n$ samples, but as $n\to\infty$, this term should go to $0$
- **Approximation error (bias)**: caused by limitations of the model class $\mathcal F$, in practice if $\mathcal F$ cannot represent the Bayes solution because the models are too simple (e.g. linear model for non-linear problem), this term is always positive
![[Estimation and approximation error in ERM.png|400]]

#### Bias-variance trade-off
If we computed a linear fit for every data set, we would have an high **bias** imposed by us, since we are forcing the model to be linear and thus with limited expressiveness, this corresponds to the _approximation error_ in SLT.

On the other hand, if we fitted a polynomial of sufficiently high degree to any given data set, we would always be able to fit the data perfectly (too well, even the noise), hence we would get high variance since the model is not able to generalize, this corresponds to the _estimation error_ in SLT.
![[Bias variance dilemma.png|400]]


### The VC dimension
A set of instances from the input space is said to be **shattered** by a function class $\mathcal F$ if it can realize every possible labeling.

The **Vapnik–Chervonenkis (VC) dimension** of a function class $\mathcal F$, denoted $VC(\mathcal F)$, is the largest number of points that $\mathcal F$ can shatter.
In practice: the higher the VC dimension, the more expressive (richer) the class.

For every $f\in\mathcal F$ with probability at least $1-\delta$, we have this **fundamental result**:
$$R(f)\leq \underbrace{R_{emp}(f)}_{\text{Emprirical risk}}+\underbrace{\sqrt\frac{h(\log(2n/h)+1)-\log(\delta/4)}{n}}_{\text{VC confidence}}$$
where $h=VC(\mathcal F)$ and $n$ is the sample size.

This results:
- **Justifies the ERM**, since $R(f)\simeq R_{emp}(f)$ when the VC term is small, hence minimizing the empirical risk also approximately minimizes the true risk
- **Explains overfitting**: if $\mathcal F$ is too rich (i.e. large $h$), the empirical risk can be small, but the true risk may still be high
- **Formalizes the bias-variance trade-off**: the approximation error goes down with richer $\mathcal F$ and the estimation error goes up with richer $\mathcal F$

The inequality in other words says that the **generalization error**, is given by **training error + complexity penalty**.

#### Structural risk minimization
ERM takes only care of the estimation error (variance), but is not concerned with the approximation error (bias).

The optimal model is found by striking a balance between the empirical risk and the capacity of the function class $F$ (e.g. the VC dimension).

The basic idea of **Structural Risk Minimization (SRM)**:
1. Construct a nested structure for family of function classes $\mathcal F_1\subset \mathcal F_2\subset...$ with non-decreasing VC dimensions: $VC(\mathcal F_1)\leq VC(\mathcal F_2)$
2. For each class $\mathcal F_i$ find the solution $f_i$ that minimizes the empirical risk
3. Choose the function class $F_i$ and the solution $f_i$ that minimizes the risk bound (i.e. empirical risk + VC confidence)

In practice this method suggest to train models of different complexities, evaluate a trade-off between fit and complexity and choose the complexity that generalizes best.

>[!Important] Rethinking generalization
>Nowadays large and complex models seem to contradict the statistical learning theory, this is because, even if very complex, they still generalize well.
>As for to today we don't understand this phenomenon.


