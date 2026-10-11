A **text classifier** assigns one label from a predefined set $Y$ to an input text: $f(t) = y$, where $y \in Y$.

**Next-token prediction** is also classification, where the context is the input and every vocabulary token is a class.

**Supervised learning pipeline**:
- _Data_: $D = \{(t^{(i)}, y^{(i)})\}_{i=1}^{N}$, with human-provided labels
- _Training_: learn parameters $\theta$ by minimizing prediction error
- _Inference_: apply the learned model to unseen text
- _Execution_: raw text $t \to$ vector $x = \varphi(t) \to P_\theta(y=k \mid x) \to \hat y = \arg\max_k P_\theta(y=k\mid x)$

### Representing Text

|               | Sparse lexical                        | Dense learned                            |
| ------------- | ------------------------------------- | ---------------------------------------- |
| **Vector**    | $x \in \mathbb{R}^{\lvert V\rvert}$   | $h \in \mathbb{R}^{d}$                   |
| **Source**    | Bag-of-words / TF-IDF / n-gram counts | Neural encoder                           |
| **Dimension** | Very high (10,000+)                   | Low ($\approx$ 300)                      |
| **Values**    | Mostly zeros                          | Mostly nonzero                           |
| **Strength**  | Interpretable weights                 | Captures context and semantic similarity |

Logistic regression works on either: $P(y=1\mid t) = \sigma(w^\top \varphi(t) + b)$.

**Feature extraction for sparse classifiers**
We define $x = \varphi(d) = [x_1, \dots, x_n]$ as a fixed-length vector, each $x_i$ measures one property.

The model designer defines $\varphi$, then _the model learns the weights_.

A _feature_ can be a lexical token (e.g. "excellent"), lexicon-based (e.g. number of positive words), or surface from the presence of a certain token or some other document level metdata (e.g. document lenght).

Values are _encoded_ using binary presence (i.e. 1HE), raw count, or [[06 - Vector space model#Weighting schemes|TF-IDF]].

**TF-IDF**
- $\text{TF}(t,d)$ = count of $t$ in $d$ (local prominence)
- $\text{DF}(t)$ = number of documents containing $t$ (repeats within one document don’t count)
- $\text{TF-IDF}(t,d) = \text{TF}(t,d) \times \text{IDF}(t)$, with $\text{IDF}(t) = \ln(N/\text{DF})$

TF-IDF _emphasizes terms that characterize a document_ and _suppresses corpus-wide common terms_.

**Normalization and scaling**
- _L2 normalization_: $x' = x/\lVert x\rVert_2$ removes document-length effects
- _Log scaling_ instead reduces the dominance of single large counts

 _Scaling methods_:
- Standardization: $x' = (x-\mu)/\sigma$
- Min-max: $x' = (x-\min)/(\max-\min)$
- Log: $x' = \log(1+x)$, which suits skewed counts and handles zeros safely
>Binary features usually stay unchanged.

### Binary logistic regression
**Linear score (logit)**
$$z = w^\top x + b = w_1x_1 + \dots + w_dx_d + b$$
$w_ix_i > 0$ raises evidence for class 1, $w_ix_i < 0$ lowers it, $x_i = 0$ contributes nothing, $b$ is the baseline score
>Dimensionality $d$ is set by the feature extractor; $x_i$ and $w_i$ are strictly aligned.

**Sigmoid**
$$\sigma(z) = \frac{1}{1+e^{-z}}$$
Maps $(-\infty,\infty) \to (0,1)$, is monotonic, has asymptotes at 0 and 1, and is smooth and differentiable.

### Maximum likelihood and cross-entropy
**Bernoulli likelihood** of the observed label:  
$$P(Y=y\mid x) = \hat p^{\,y}(1-\hat p)^{1-y}$$
>The exponents select $\hat p$ when $y=1$ and $1-\hat p$ when $y=0$.

**Log-likelihood** of one sample:  
$$\log P(y\mid x;\theta) = y\log\hat p + (1-y)\log(1-\hat p)$$
**Full training set**:
$$LL(\theta) = \sum_i \left[y^{(i)}\log\hat p^{(i)} + (1-y^{(i)})\log(1-\hat p^{(i)})\right]$$

**Binary cross-entropy (BCE) loss**:
$$\mathcal{L} = -\frac{1}{N}LL(\theta)$$
Maximizing conditional log-likelihood is equivalent to minimizing BCE.

**Loss behavior**

| $\hat p$ | Loss if $y=1$ | Loss if $y=0$ |
| -------- | ------------- | ------------- |
| 0.10     | 2.303         | 0.105         |
| 0.50     | 0.693         | 0.693         |
| 0.90     | 0.105         | 2.303         |

Confident and correct gives loss near 0, while uncertain ($\hat p=0.5$) gives 0.693, confident and wrong gives unbounded growing loss.
>The log turns a product of probabilities into a tractable sum.

**Vectorization**
For a batch $X \in \mathbb{R}^{B\times d}$, $w\in\mathbb{R}^{d\times1}$, scalar $b$:  
$$z = Xw + b, \qquad \hat p = \sigma(z)$$
Shapes: $[B\times d]\cdot[d\times1] \to [B\times1]$, _the bias is broadcast to every row_.

**Gradients**
For sigmoid + BCE, the derivative with respect to the logit simplifies to  
$$\frac{\partial L}{\partial z} = e = \hat p - y$$

**Single-example SGD step:**  
$$w \leftarrow w - \eta\, e^{(i)} x^{(i)}, \qquad b \leftarrow b - \eta\, e^{(i)}$$
_Learning rate $\eta$_: too small gives slow progress, and too large causes overshooting and instability.
>Decaying schedules help fine-grained convergence. Initializing $w=0,\ b=0$ is valid for logistic regression because there are no hidden-unit symmetry issues.

**Training paradigms**:

| Method        | Batch size | Gradient                | Cost                |
| ------------- | ---------- | ----------------------- | ------------------- |
| Full-batch GD | $B=N$      | Exact                   | Expensive update    |
| SGD           | $B=1$      | Highly variable         | Very cheap          |
| Mini-batch GD | $1<B<N$    | Lower variance than SGD | Efficient, parallel |

An **epoch** is one pass over all training examples, and data are shuffled each epoch. In deep learning, "SGD" often means mini-batch SGD.

**Vectorized mini-batch updates:**  
$$e = \hat p - y \in \mathbb{R}^{B\times1},\quad g_w = \tfrac1B X^\top e\ [d\times1],\quad g_b = \tfrac1B \mathbf 1_B^\top e = \text{mean}(e)$$ $$w \leftarrow w - \eta g_w,\qquad b\leftarrow b-\eta g_b$$
Averaging keeps gradient magnitude independent of batch size.

### Multiclass Logistic Regression and Softmax
**$K$ mutually exclusive classes** use $K$ parallel linear units:
$$z = Wx + b \in \mathbb{R}^K,\quad W\in\mathbb{R}^{K\times d},\ b\in\mathbb{R}^K$$
With each row holding the class scores for one sample.

| |Binary|Multiclass|
|---|---|---|
|Output|1 logit|$K$ logits|
|Normalization|Sigmoid, giving $p(y=1)$|Softmax, giving a distribution|
|Boundaries|One|Multiple linear boundaries|

**Softmax**
$$\hat p_k = \frac{\exp(z_k)}{\sum_j \exp(z_j)}$$
- Probabilities are _strictly positive_ and sum to 1
- _Monotonic_: a larger logit gives a larger probability
- _Depends only on differences_

### Evaluation metrics
**Confusion matrix**

| Metric    | Formula                     | Question it answers                                 |
| --------- | --------------------------- | --------------------------------------------------- |
| Accuracy  | $\frac{TP+TN}{TP+TN+FP+FN}$ | How often is the model right overall?               |
| Precision | $\frac{TP}{TP+FP}$          | When it predicts positive, how often is it correct? |
| Recall    | $\frac{TP}{TP+FN}$          | How many actual positives are found?                |
| F1        | $\frac{2PR}{P+R}$           | Balance of precision and recall                     |

**Multiclass averaging** (one-vs-all per class):
- _Macro_: equal weight per class
- _Micro_ pool all decisions
- _Weighted_ weight by class support

