A communication system can be abstracted as follows:
![[Communication system.png]]
There are three level of "information": **symbolic** (or syntactic), **semantic** (deals with meaning) and **pragmatic** (how context affects meaning).
>Classical information theory deals with the symbolic level.

## Measuring information
The **amount of information (i.e. surprise)** $I(E)$ provided by the event $E$ can be defined as a function of $P(E)$, the probability of $E$:
$$I(E)=f(P(E))$$

We define the following **axioms**:
1. $I(E)\geq 0$, $I(E)=0\iff P(E)=1$
	An event that is certain, gives no new information.
2. $\lim\limits_{P(E)\to0}I(E)=+\infty$
	A rare event gives more information when it happens, if it has probability near $0$, it would be infinitely surprising to see it happen.
3. $P(E_1)<P(E_2)\implies I(E_1)>I(E_2)$
	The rarer the event, the more information is obtained.

These axioms restrict the shape of $f(P(E))$, but not enough to determine it uniquely. we can further describe $I(E)$ with the following equation that has some desirable properties:
$$I(E)=\log\frac{1}{P(E)}=-\log P(E)$$

---
## Entropy
We don't necessarily have to know how the information source works, we can just understand its [[Distribuzioni continue|probabilistic distribution]], for this reason we identify the source as a  (discrete) [[Variabili casuali|random variable]] $X$, with probability distribution $P(x)$.

The **entropy** of $X$ is defined as the _average information produced by a source_:
$$H(X)=\mathbb{E}[I(X)]=\sum_{x\in\mathscr{X}}p(x) I(x)-\sum_{x\in\mathscr{X}}p(x)\log p(x)$$
where $\mathscr{X}$ is the symbols **alphabet** of the source.
>If we want to emphasize the logarithm base $b$, we can write $H_b(x)$.
>The measurement unit for base $2$ is called _bit_.
>We use the convention that $0\log0=0$.

**Properties of entropy**:
- We can express a base change as: $H_b(X)=(\log_ba)H_a(X)$
- $H(X)\geq0$, it is true that $H(X)=0$ only if the source is deterministic and always produces the same value
- $H(X)\leq \log|\mathscr{X}|$, means that the upper bound is the logarithm of the cardinality of the alphabet, and it reaches that upper bound only when every symbol of the alphabet has the same probability to appear (i.e. they have a [[Distribuzioni discrete#Uniforme|uniform distribution]])

For example if we toss a biased coin where $p$ represents the probability of heads, we have: $H(X)=-p\log p-(1-p)\log(1-p)$.

>[!Tip] Zero entropy
>Note that if the symbols alphabet contains only 1 symbol, then there is no entropy.

### Joint entropy
Let $X$ and $Y$ be two (discrete) random variables, then their **joint entropy** is defined as:
$$H(X,Y)=-\sum_x\sum_yp(x,y)\log p(x,y)$$
>See [[Congiunte#Congiunte indipendenti|joint probability]].

If the variables are:
- **Independent**: $H(X,Y)=H(X)+H(Y)$, the entropy is added
- **Dependent**: $H(X,Y)<H(X)+H(Y)$, since one variable provides some information about the other, the uncertainty is reduced

### Conditional entropy
Let $X$ and $Y$ be two (discrete) random variables, then the **conditional entropy** given the event $Y=y$, is defined as:
$$H(X|Y=y)=-\sum_xp(x|y)\log p(x|y)$$
while the conditional entropy of $X$ given $Y$ is:
$$H(X|Y)=-\sum_x\sum_yp(x,y)\log p(x|y)$$
>See [[Probabilità condizionata|conditional probability]].

If the variables are:
- **Independent**: $H(X|Y)=H(X)$
- **Dependent**: $H(X|Y)<H(X)$

>[!Example]
>Let $X=\{1,2,3,4,5,6\}$ and $Y=\{even, odd\}$.
>- $H(X|Y)\leq H(X)$, saying that the number is even or odd, reduces the surprise
>- $H(Y|X)=0$, saying the extracted number, gives no surprise on the result of $Y$ since we already know if it will be even or odd

#### Chain rule
We can <u>combine the conditional and joint probabilities</u> into a single equation:
$$\begin{align}
H(X,Y)&=H(X)+H(Y|X)\\
&=H(Y)+H(X|Y)
\end{align}$$
### The Kullback-Leiber divergence
Let $p$ and $q$ be two (discrete) probability distributions.
We can imagine them as two points belonging to the [standard simplex](https://en.wikipedia.org/wiki/Simplex) defined as:
$$\Delta=\left\{x\in\mathbb{R}^n:\sum_{i=1}^nx_i=1,x_i\geq0\right\}$$
The **Kullback-Leiber (KL) divergence (i.e. relative entropy)** between $p$ and $q$ is defined as:
$$D(p||q)=\sum_{i=1}^np_i\log\frac{p_i}{q_i}$$
It measures how different two probabilities distributions are, in particular, how much information is lost when we use $q$ to approximate $p$, for this reason it is used as a **statistical distance**.

While it measures how different two distributions are, and thus is distance, **it is not a metric** and does not satisfy [[Triennale/Secondo anno/Algoritmi e strutture dati/Mod. 1/Cammini minimi/Introduzione#Disuguaglianza triangolare|triangular inequality]].

Its key properties are:
- **Non-negativity (Gibbs' inequality)**: $D(p||q)\geq 0$ and $D(p||q)=0\iff p=q$
- **Asymmetry**: $D(p||q)\neq D(q||p)$
- **Convexity**: $D(p||q)$ is convex in the pair $(p,q)$
>This is a useful property, since it is used in the _cross-entropy loss_, and it ensures that we're not stuck in a bad local minima (from the KL term itself).

### Mutual information
Let $X$ and $Y$ be two (discrete) random variables, the **mutual information** between them, is defined as:
$$\begin{align}
I(X;Y)&=\sum_x\sum_yp(x,y)\log\frac{p(x,y)}{p(x)p(y)}\\
&=D(p(x,y)||p(x)p(y))
\end{align}$$
which provides a measure of mutual dependence between $X$ and $Y$.

Intuitively it measures <u>how much knowing one variable reduces the uncertainty about the other</u>.
- If $X$ and $Y$ are **independent**, then $p(x,y)=p(x)p(y)$, this produces $I(X;Y)=0$
- If $X$ and $Y$ are **dependent** then, $I(X;Y)>0$

It can also be written as:
$$\begin{align}
I(X;Y)&=H(X)-H(X|Y)\\
&=H(Y)-H(Y|X)
\end{align}$$
In other words $I(X;Y)$ measures the **amount of information that travels on a channel**, where $X$ represents the _input_, and $Y$ the _received message_, this tells us how much knowing $Y$ reduces our uncertainty about $X$.

So $I(X;Y)$ is the part of $X$'s uncertainty that was resolved by seeing $Y$, this is literally a measure of how much the receiver learns about the sender.
![[Mutual information.svg|500]]
- $I(X;Y)=I(Y;X)$
- $I(X;X)=H(X)$
- $I(X;Y)\geq0$, and $I(X;Y)=0\iff H(X,Y)=H(X)+H(Y)$
- $H(X|Y)\leq H(X)$, and $H(X|Y)=0\iff H(X,Y)=H(X)+H(Y)$
>It is equal to $0$ iff $X$ and $Y$ are independent.

---
## Source coding
A source code $C$ for a random variable $X$ with range $\mathscr{X}$ and probability $p(x)$ is a mapping:
$$C:\mathscr{X}\to\mathscr{D}^*$$
where $\mathscr{D}^*$ is the set of strings of symbols from a $d$-ary alphabet, where $|\mathscr{D}|=d$.
>See the [[Espressioni regolari|regular expression]] for $\mathscr{D}^*$.


$C(x)$ denotes the **codeword** associated to $x$ and $l(x)$ is its length.
The **average length** $L(C)$ of a code $C$ is defined as:
$$L(C)=\sum_{x\in\mathscr{X}}p(x)l(x)$$

>[!Example]
>- $P(X=1)=\frac{1}{2}$, codeword $C(1)=0$
>- $P(X=2)=\frac{1}{4}$, codeword $C(2)=10$
>- $P(X=3)=\frac{1}{8}$, codeword $C(3)=110$
>- $P(X=4)=\frac{1}{8}$, codeword $C(4)=111$
>$$L(C)=\frac{1}{2}\cdot1+ \frac{1}{4}\cdot2+ \frac{1}{8}\cdot3+ \frac{1}{8}\cdot3=1.75$$
>Note that $H(X)=1.75=L(C)$, therefore the code is optimal since $H(X)$ indicates the theoretical minimum average number of symbols needed per source symbol (seen later).

