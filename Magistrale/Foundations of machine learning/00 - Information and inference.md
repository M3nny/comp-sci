A communication system can be abstracted as follows:
![[Communication system.png]]
There are three level of "information": **symbolic** (or syntactic), **semantic** (deals with meaning) and **pragmatic** (how context affects meaning).
>Classical information theory deals with the symbolic level.

### Measuring information
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

### Entropy
We don't necessarily have to know how the information source works, we can just understand its [[Distribuzioni continue|probabilistic distribution]], for this reason we identify the source as a  (discrete) [[Variabili casuali|random variable]] $X$, with probability distribution $P(x)$.

The **entropy** of $X$ is defined as the _average information produced by a source_:
$$H(X)=\mathbb{E}[I(X)]=\sum_{x\in\mathfrak{X}}p(x) I(x)-\sum_{x\in\mathfrak{X}}p(x)\log p(x)$$
where $\mathfrak{X}$ is the symbols **alphabet** of the source.
>If we want to emphasize the logarithm base $b$, we can write $H_b(x)$.
>The measurement unit for base $2$ is called _bit_.
>We use the convention that $0\log0=0$.

**Properties of entropy**:
- We can express a base change as: $H_b(X)=(\log_ba)H_a(X)$
- $H(X)\geq0$, it is true that $H(X)=0$ only if the source is deterministic and always produces the same value
- $H(X)\leq \log|\mathfrak{X}|$, means that the upper bound is the logarithm of the cardinality of the alphabet, and it reaches that upper bound only when every symbol of the alphabet has the same probability to appear (i.e. they have a [[Distribuzioni discrete#Uniforme|uniform distribution]])

For example if we toss a biased coin where $p$ represents the probability of heads, we have: $H(X)=-p\log p-(1-p)\log(1-p)$.

>[!Tip] 0 entropy
>Note that if the symbols alphabet contains only 1 symbol, then there is no entropy.

#### Joint entropy
Let $X$ and $Y$ be two (discrete) random variables, then their **joint entropy** is defined as:
$$H(X,Y)=-\sum_x\sum_yp(x,y)\log p(x,y)$$
>See [[Congiunte#Congiunte indipendenti|joint probability]].

If the variables are:
- **Independent**: $H(X,Y)=H(X)+H(Y)$, the entropy is added
- **Dependent**: $H(X,Y)<H(X)+H(Y)$, since one variable provides some information about the other, the uncertainty is reduced

#### Conditional entropy
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

##### Chain rule
We can <u>combine the conditional and joint probabilities</u> into a single equation:
$$\begin{align}
H(X,Y)&=H(X)+H(Y|X)\\
&=H(Y)+H(X|Y)
\end{align}$$

