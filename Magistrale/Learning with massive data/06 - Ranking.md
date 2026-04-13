The **ranking problem** consists in maximizing the user-perceived quality of the result set $u$.
Formally speaking, given a query $q\in\mathcal Q$ and a dynamic collection of documents $\mathcal D$, we have to find an ordered $k$-subset that maximizes the **utility function**:
$$u:\mathcal Q\times\mathcal D^k\to\mathbb R$$

In this type of problem we are dealing with a _dataset_, _representation function_, _hypothesis class_, _loss_ and _metrics_.

### Labeling
When dealing with **labeling** there are two approaches:
- **Explicit labels**: human annotators rate document-query pairs, which is expensive, but clean, the problem arises when a new ranking function returns documents that are not yet annotated or the human annotators have to deal with private documents
- **Implicit labels**: the system observes what users actually click on, which cheap bu noisy, the big problem here is _position bias_ for which users click on the first result simply because it's at the top, not because it's the best one, which poisons the training data

In order to **represent a document** mathematically, we assume that there is a function $\phi$ that takes an object and returns a vector in $\mathbb R^n$ as its representation (e.g. TF-IDF for texts).
With the document we may include several signals, such as: PageRank, number of clicks, time spent on page.

### Metrics
We **predict the relevance** label $y\in\mathcal Y$ of a document $x\in\mathbb R^n$ using a linear function $f(x)=w^Tx+b$, then we **learn the parameters** of $f$ by minimizing the [[02 - Statistical learning theory#The ERM principle|empirical error]] on a set of $m$ training samples:
$$w^*,b^*=\arg\min_{w,b}\frac{1}{m}\sum_{i=1}^m\ell(f(x_i),y_i)$$
Depending on the **loss function** that we use, we may encounter some issues:
- **Binary classification loss**: being ranked 2nd instead of 1st count as a full error, but that's not actually a bad ranking
- **Regression loss (MSE)**: we are penalizing the absolute score difference from the label, but ranking only cares about relative order, for this reason we could have a large MSE yet a perfect ordering, or viceversa
![[Ideal ranking.png|400]]

**Kendall's correlation** $\tau$ applied to ranking counts how many pairs of documents are in the correct relative order.
$$\tau=\frac{2}{n(n-1)}\sum_{i<j}sign(y_i-y_j)sign(f_i-f_j)$$
The problem is that it treats a swap between position 1 and 2 identically to a swap between positions 99 and 100, but users almost never look past the first few results, so <u>errors at the top are far mode damaging than errors at the bottom</u>.
![[Kendall correlation applied to ranking.png|400]]

### Discounted Cumulative Gain at Rank
This metric, also abbreviated as $DCG@k$ **captures the user behavior**, and the key ideas are:
- **Gain**: higher relevance documents contribute exponentially more, so a highly relevant document at rank 1 is worth a lot more than a marginally relevant one
- **Discount**: the logarithmic discount means results lower in the list matter less, which reflects how users actually browse

$$DCG@k=\sum_{r\leq k}Gain(y_{\pi r})\times Discount(r)$$
$$Gain(y)=2^y-1\qquad\qquad Discount(r)=\frac{1}{\log_2(r+1)}$$
Where $\pi_r$ maps from rank $r$ to the corresponding document id $i$.
![[DCG.png|400]]

Normalizing by dividing by the **ideal DCG** (the best possible ordering), so the score is always between $0$ and $1$, gives us **NDCG**.

The problem with **rank-based metrics** such as Kendall's $\tau$ and NDCG, is that they depend on documents sorted order, so if we change a document's score slightly without changing its rank, the gradient is exactly $0$, and there is no learning signal, whilst if the rank does change, then the function jumps discontinuously, and in this case the gradient is undefined, and we are not able to perform the gradient descent.

In order to solve the differentiability issue, we can use a **proxy loss function** which should behave similarly to NDCG.
![[Proxy loss.png|300]]

Given a set of ranking samples $\Psi=\{(q_j,d_j,y_j)\}^N_{j=1}$, the **RankNet loss** (proxy) is:
$$\mathcal L(f)=\frac{1}{N}\sum_{(q,d,y)\in\Psi}\sum_{i,j\text{ s.t. }y_i>y_j}\log(1+e^{-(f_i-f_j)})$$
>Where $f_i=f(d_i)$.

For every pairs of documents where document $i$ should rank above $j$, it penalizes the model when $f_i<f_j$, using a [[Regressione lineare#Regressione logistica|logistic function]], which is **differentiable**.

But there's an issue, minimizing RankNet loss and maximizing NDCG are _not well correlated_ in practice, the loss goes down but NDCG plateaus or even drops.

### Gradient boosting decision trees
A [[Decision trees|regression decision tree]] works by partitioning the feature space through a series of yes/no tests at each node, it is built greedily, and at each node we find the split which reduces the prediction error the most, the score is then used to order documents.
>Decision trees are _train-efficient_.

A single tree usually is weak, the idea then is to build a [[Ensemble methods#Boosting|boosting ensemble]], where we train sequentially many trees.
At each step, the training data points that were previously misclassified are given higher weight (or probability), so the next tree focuses more on correcting those errors.

$$
\begin{aligned}
\textbf{Gradient Boosting} \\[6pt]
F &\leftarrow 0 \\[6pt]
\textbf{for } m = 1 \textbf{ to } M \textbf{ do} \\[4pt]
\quad r_i &\leftarrow \text{pseudo-residual for } i = 1, \dots, N \\[4pt]
\quad \mathcal{R} &\leftarrow \{(x_i, r_i)\}_{i=1}^N \\[4pt]
\quad T_m &\leftarrow \text{Train regression model on } \mathcal{R} \\[4pt]
\quad F &\leftarrow F + \nu T_m \\[6pt]
\textbf{end for}
\end{aligned}
$$

Informally speaking:
- **Initialize** the model $F\leftarrow 0$
- **Loop** over $M$ trees
	- For each data point $i$, compute how wrong the model is, these are called **residuals** $r_i$, in general they are gradients of the loss function (hence gradient boosting), in practice they indicate what the model still needs to learn
	- **Create a new dataset** $\mathcal R$ with the original input features $x_i$ with residuals $r_i$ as targets (we are now training on errors instead of original labels)
	- **Train a new regression tree** $T_m$ on $\mathcal R$ which learns how much correction should it add
	- **Update the model by adding the new tree to the ensemble** and weight it with a learning rate to avoid overfitting (which is a general boosting issue)

A more precise view of boosting is to see the model as an **additive function**:
$$
F(d) = \sum_{i=1}^{M} f_i(d)
$$

Each function $f_i$ (a tree) is added sequentially and represents a **step in function space**.

At each iteration, we choose $f_i$ to follow the **steepest descent direction**:
$$
f_i(d) = -g_i(d)
$$

where the gradient is:
$$
g_i(d) = \left[\frac{\partial \ell(f(d), y)}{\partial f(d)}\right]_{f=\sum_{j<i} f_j}
$$
### LambdaMart algorithm
LambdaMart is an algorithm that uses gradient boosting and adds smarts gradients on top of it in order to make it work for ranking.

Our original problem was that NDCG is not differentiable, for this reason we introduces RankNet as a first workaround, which defined a **pairwise loss** for pairs $(i,j)$:
$$\ell_{ij} = \log(1 + e^{-(f_i - f_j)})$$
But it treats all swaps equally, this is not aligned with NDCG.

The key idea of LambdaMart is that instead of defining a proper loss, it directly defines the gradients that it wishes it had, these are called **lambdas**:
$$\lambda_{ij} =  
-\frac{1}{1 + e^{(f_i - f_j)}} \cdot |\Delta NDCG|$$
Which is the **RankNet gradient scaled by importance of the swap** ($\Delta NDCG$).

Then, since boosting needs one gradient per data point, and not per pair, LambdaMart aggregates:
$$g_i =  
\sum_{j: y_i > y_j} \lambda_{ij}  
-  
\sum_{j: y_i < y_j} \lambda_{ji}$$
in this way we have one value $g_i$ per document, which is what boosting expects.

Pairs whose swap would hurt NDCG a lot get a large gradient, while pairs deep in the list whose swap barely matters get a tiny gradient.
>In practice LambdaMart creates the gradients to be fed into the boosting algorithm.

### Decision tables
Decision trees are not cache friendly, since a node can test a different feature depending on which path it took.

A **symmetric decision tree** is the halfway step: it enforces that every node at the same level uses the same split feature regardless of which path led there.

A **decision table** takes this approach a step further, since now every document goes through the exact same sequence of tests, we can compress the whole tree into two compact arrays:
- A list of which features to test
- A list of the cut thresholds for each feature

For any document, we evaluate each test and get a boolean result.
Concatenating these gives a binary string, which we can use directly as an index into a **lookup table of predictions**.

>[!Tip] Decision trees vs decision tables
>A standard tree can test any feature at any node, giving it more flexibility.
>However, the level-wise constraint also acts as a regularizer, making decision tables _less prone to overfitting_, which often compensates in practice.

### Backfitting
A further improvement to decision trees (and decision tables) is **backfitting** which **tries to solve the greedily built splits**.

It consists in revisiting and re-optimizing earlier greedy choices, and it has three variants:
- **Cyclic**: loop through all the cuts in order and re-optimize each one while holding the other fixed
- **Random**: randomly pick a cut to re-optimize each iteration
- **Greedy**: at each iteration, evaluate all possible cuts and pick whichever one gives the largest error reduction if re-optimized 

>[!Important]
>Backfitting is not nudging the existing cut slightly, it is fully re-optimizing it from a blank slate, which means we might end up testing a completely different feature at that level.

