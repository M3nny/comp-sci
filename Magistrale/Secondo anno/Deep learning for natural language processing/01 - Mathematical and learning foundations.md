**Tensor shapes** in NLP are:
- `[d]`: one token
- `[T, d]`: one sequence
- `[B, T, d]`: one mini-batch (usually processed by transformers)


**Vector operations**

| Operation              | Formula                                                                                                                     | Use case                                                                                                                                                 |
| ---------------------- | --------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| *Vector addition*        | $\mathbf{x}+\mathbf{y}=[x_1+y_1,\dots,x_n+y_n]^\top$                                                                        | Combines two displacements into one (e.g. composing representations)                                                                                     |
| *Scalar multiplication*  | $c\mathbf{x}=[cx_1,\dots,cx_n]^\top$                                                                                        | Changes magnitude and orientation: $c>0$ keeps direction, $c<0$ reverses it, $c=0$ gives $\mathbf{0}$                                                    |
| *Inner (dot) product*    | $\mathbf{x}\cdot\mathbf{y}=\sum_{i=1}^{n}x_i y_i\in\mathbb{R}$                                                              | Measures directional similarity as a single scalar                                                                                                       |
| *Outer product*          | $(\mathbf{x}\mathbf{y}^\top)_{ij}=x_i y_j,\quad \mathbf{x}\mathbf{y}^\top\in\mathbb{R}^{m\times n}$                         | Builds a matrix of all pairwise products of two vectors                                                                                                  |
| *Euclidean ($L_2$) norm* | $\lVert\mathbf{x}\rVert_2=\sqrt{\sum_{i=1}^{n}x_i^2}$                                                                       | Vector length (e.g. $(3,4)\Rightarrow 5$)                                                                                                                |
| *$L_2$ normalization*    | $\hat{\mathbf{x}}=\dfrac{\mathbf{x}}{\lVert\mathbf{x}\rVert_2},\quad \mathbf{x}=\lVert\mathbf{x}\rVert_2,\hat{\mathbf{x}}$  | Embeddings with length 1, so direction matters more than magnitude (e.g. $(3,4)\to(0.6,0.8)$)                                                            |
| *Cosine similarity*      | $\cos(\mathbf{u},\mathbf{v})=\dfrac{\mathbf{u}\cdot\mathbf{v}}{\lVert\mathbf{u}\rVert_2,\lVert\mathbf{v}\rVert_2}\in[-1,1]$ | Compares word and sentence embeddings, semantic search (query vs document), and recommenders. $1$ = same direction, $0$ = perpendicular, $-1$ = opposite |

**Matrix operations**

| Operation                  | Formula                                                                                                                                 | Use case                                                                                                                                                                                  |
| -------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| *Transpose*                  | $(A^\top)_{ij}=A_{ji},\quad A\in\mathbb{R}^{m\times n}\Rightarrow A^\top\in\mathbb{R}^{n\times m}$                                      | Aligns dimensions before multiplying (e.g. $XW^\top$)                                                                                                                                     |
| *Matrix–vector product*      | $\mathbf{y}=A\mathbf{x},\quad y_i=\text{row}_i(A)\cdot\mathbf{x},\quad \mathbb{R}^n\to\mathbb{R}^m$                                     | Each output feature is a weighted combination of all input features. $m>n$ expands, $m<n$ compresses                                                                                      |
| *Linear classifier*          | $\mathbf{z}=W\mathbf{x}+\mathbf{b},\quad W\in\mathbb{R}^{5\times 512}$                                                                  | Maps a 512-d document vector to 5 class logits (one row of $W$ per class). Predicted class is $\arg\max\mathbf{z}$                                                                        |
| *Softmax*                    | $\text{softmax}(\mathbf{z})_k=\dfrac{e^{z_k}}{\sum_j e^{z_j}}$                                                                          | Turns logits into probabilities without changing the class ranking                                                                                                                        |
| *Feed-forward network (FFN)* | $\mathbf{h}=\sigma(W_{\text{up}}\mathbf{x}+\mathbf{b}_{\text{up}}),\quad \mathbf{y}=W_{\text{down}}\mathbf{h}+\mathbf{b}_{\text{down}}$ | Transformer layer applied per token: $768\to3072\to768$ (4$\times$ expansion), allowing the residual connection $\mathbf{x}+\mathbf{y}$                                                   |
| *Matrix–matrix product*      | $(m\times n)\cdot(n\times p)\to(m\times p)$                                                                                             | Only defined if inner dimensions match. Applies one transformation to many vectors in parallel                                                                                            |
| *Batch linear layer*         | $Y=XW^\top+\mathbf{b},\quad X\in\mathbb{R}^{B\times d},\ Y\in\mathbb{R}^{B\times k}$                                                    | Scores a whole mini-batch at once (e.g. $32\times512$ docs $\to$ $32\times5$ scores $z_{ik}=\mathbf{x}_i\cdot\mathbf{w}_k+b_k$). Same pattern for Q/K/V projections and vocabulary logits |
| *Cross-entropy loss*         | $L=-\log\text{softmax}(\mathbf{z}_i)_{y}$                                                                                               | Training signal for classification: raises the gold class score (e.g. class 3) and lowers competing ones                                                                                  |

**Vector spaces and rank**

| Concept                      | Formula                                                                                                                                           | Use case                                                                                                                                                                        |
| ---------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| *Vector space / subspace*    | $\mathbf{u}+\mathbf{v}\in V,\ a\mathbf{v}\in V;\quad U\subseteq V \text{ needs } \mathbf{0}\in U,\ \mathbf{u}+\mathbf{w}\in U,\ a\mathbf{u}\in U$ | Formal setting for embeddings. A plane through the origin is a subspace, a plane missing the origin is not                                                                      |
| *Linear independence*        | $c_1\mathbf{v}_1+\dots+c_k\mathbf{v}_k=\mathbf{0}\ \Rightarrow\ c_1=\dots=c_k=0$                                                                  | Detects redundancy: a dependent representation adds no new linear information (e.g. $(1,2)$ and $(2,4)$)                                                                        |
| *Span*                       | $\text{Span}(\mathbf{v}_1,\dots,\mathbf{v}_k)=\left\{\sum_i c_i\mathbf{v}_i : c_i\in\mathbb{R}\right\}$                                           | All vectors you can build from a set. Only independent directions count (e.g. two independent vectors span $\mathbb{R}^2$)                                                      |
| *Range (column space)*       | $\text{Range}(A)={A\mathbf{x}:\mathbf{x}\in\mathbb{R}^n}=\text{Span}(\mathbf{a}_1,\dots,\mathbf{a}_n)$                                            | The outputs a matrix can actually produce, which may be smaller than the whole output space $\mathbb{R}^m$                                                                      |
| *Rank*                       | $\text{rank}(A)=\dim\text{Range}(A)\le\min(m,n)$                                                                                                  | Effective dimensionality of a transformation. Rank 0 is a point, 1 a line, 2 a plane. A large vocabulary does not imply high rank for $E\in\mathbb{R}^{\lvert V\rvert\times d}$ |
| *Rank in attention*          | $\text{rank}(QK^\top)\le d_k$                                                                                                                     | Head dimension limits the linear structure of raw attention scores                                                                                                              |
| *Low-rank adaptation (LoRA)* | $\Delta W=BA,\quad \text{rank}(\Delta W)\le r$                                                                                                    | Parameter-efficient fine-tuning: learns a small set of adaptation directions instead of updating the full weight matrix                                                         |

### Managing uncertainty
We define $\Omega$ as the **sample space**, $\omega$ as a **realized result**, an **event** $E\subseteq\Omega$.
Axioms are:
- $P(E)\geq 0$
- $P(\Omega)=1$

**Derived rules**:
- _Complement_: $P(A^c) = 1 - P(A)$
- _Monotonicity_: $A \subseteq B \implies P(A) \leq P(B)$
- _Intersection bound_: $P(A \cap B) \leq \min(P(A), P(B))$
- _Union bound:_ $P(A \cup B) \leq P(A) + P(B)$
- _Conditional probability_: $P(A \mid B) = \frac{P(A\cap B)}{P(B)}$
- _Independence_: $P(A\cap B)=P(A)P(B)$

**Random variables and distributions**
A _random variable_ $X:\Omega\to\mathbb{R}$ can be discrete (finite or countable values) or continuous.

_PMF_ $p_X(x)=P(X=x)$ for discrete variables, _PDF_ $f_X(x)=\dfrac{dF_X(x)}{dx}$ for continuous variables, where $P(X\in B)=\int_B f_X(x)\,dx$.

_CDF_ $F_X(x)=P(X\le x)$ applies to both, and $P(a<X\le b)=F_X(b)-F_X(a)$.

For a continuous variable, $P(X=x)=0$ even when $f_X(x)>0$, because $f_X$ is a density and not a probability.

- _Expected value_ $E[X]=\sum_x x\,p(x)$, a probability-weighted average (e.g. $p(0)=\tfrac{1}{3}$, $p(1)=\tfrac{2}{3}$ gives $E[X]=\tfrac{2}{3}$)
- _Variance_: $\mathrm{Var}(X)=E\big[(X-\mu)^2\big]=E[X^2]-(E[X])^2$.
	  It measures spread. Three variables with the same mean $0$ can have variances $0$, $1$, and $10{,}000$.

**Joint, marginal, conditional and Bayes**
_Joint PMF_ $p_{X,Y}(x,y)$ sums to $1$, _marginals_ come from summing out the other variable: $p_X(x)=\sum_y p_{X,Y}(x,y)$. 

- _Conditional distribution_: $p_{Y\mid X}(y\mid x)=\dfrac{p_{X,Y}(x,y)}{p_X(x)}$
- _Product rule_: $p_{X,Y}(x,y)=p_{Y\mid X}(y\mid x)\,p_X(x)$
- _Bayes' rule_: $p_{Y\mid X}(y\mid x)=\dfrac{p_{X\mid Y}(x\mid y)\,p_Y(y)}{p_X(x)}$

_Independence of random variables_: $p_{X,Y}(x,y)=p_X(x)\,p_Y(y)$, or equivalently $p_{Y\mid X}(y\mid x)=p_Y(y)$.

**Information theory**
- _Surprisal_: $I(x)=-\log_2 p(x)$. Rarer events carry more information: certain event $0$ bits, fair coin $1$ bit, $p=\tfrac{1}{8}$ gives $3$ bits, and surprisal goes to infinity as $p\to 0$
- _Entropy_: $H(p)=-\sum_x p(x)\log_2 p(x)$, the expected surprisal
- _Cross-entropy_: $H(p,q)=-\sum_x p(x)\log_2 q(x)$, the average surprisal of data from $p$ under model $q$
- _KL divergence_: $D_{\mathrm{KL}}(p\,\|\,q)=\sum_x p(x)\log_2\dfrac{p(x)}{q(x)}=H(p,q)-H(p)$
	It is $\ge 0$, equals $0$ iff $p=q$, and is _asymmetric_, so it is a divergence and not a distance.
