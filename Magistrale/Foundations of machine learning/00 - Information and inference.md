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

**Classes of codes**
- **Nonsingular**: all codewords are distinct, the term might be misleading, but it means that we can revert the mapping since each symbol has a unique codeword (i.e. injective function)
- **Uniquely decodable**: any encoded string must have a unique decoding, this means that it is not possible to interpret a sequence of codewords as a wrong symbol
- **Instantaneous**: no codeword is a prefix of any other codeword, this means that without looking ahead of the sequence, we can instantly identify the symbol

|  X  | Singular | Nonsingular, but not uniquely decodable | Uniquely decodable, but no instantaneous | Instantaneous |
| :-: | :------: | :-------------------------------------: | :--------------------------------------: | :-----------: |
|  1  |    0     |                    0                    |                    10                    |       0       |
|  2  |    0     |                   010                   |                    00                    |      10       |
|  3  |    0     |                   01                    |                    11                    |      110      |
|  4  |    0     |                   10                    |                   110                    |      111      |

**Theorem**
Let $C$ be an instantaneous D-ary code for a random variable $X$ with range $\mathscr{X}$ and probability distribution $p(x)$, then:
$$L(C)\geq H_D(X)$$

In words, this means that the average length of any instantaneous code cannot be smaller than the entropy, but it can be equal to the entropy if $p(x)=D^{-l(x)}$ for all $x\in\mathscr{X}$, this would mean that the probability distribution of $X$ is **D-adic** (i.e. each of the probability is equal to $D^{-n}$ for some $n$).

>[!Info] D-adic distributions
>In the previous example, the distribution was D-adic, since each probability can be expressed as an exact power of $D$ (which was $2$), namely $2^{-1}, 2^{-2}, 2^{-3}, 2^{-3}$.

### Huffman coding
Huffman coding is a lossless data compression algorithm used to minimize the average number of bits required to represent symbols in a message.

More frequent symbols get shorter codes.
It works as follows:
1. Take the two least probable symbols in the alphabet, these two symbols will be given the longest codewords, which will have equal length, and differ only in the last digit
2. Combine these two symbols into a single symbol, and repeat
![[Huffman coding.png|500]]

**Optimality of Huffman codes**:
- Huffman codes are optimal and instantaneous
- If $C_{Huffman}$ is a Huffman D-ary code for a random variable $X$, then
$$H_D(X)\leq L(C_{Huffman})<H_D(X)+1$$
>If the distribution is not D-adic, we know that $H_D(X)< L(C_{Huffman})$.

This express how close are the Huffman codes to the theoretical lower boundary.

It is also important to highlight that as we increase the number of consecutive symbols, we get better and better codes, and Shannon's **source coding theorem** predicts that the expected codeword length ($L(C)$), will converge to the entropy of $X$ as we add more consecutive symbols to the Huffman encoding.

---
## Reliable communication through unreliable channels
A channel $\mathscr{C}$ is defined as a triplet:
$$\mathscr{C}=(\mathscr{X},p(y|x),\mathscr{Y})$$
Where:
- $\mathscr{X}$ is the input alphabet
- $\mathscr{Y}$ is the output alphabet
- $p(y|x)$ is the forward probability distribution (i.e. how the channel may distort the input)

The **capacity** of the channel $\mathscr{C}$ is defined as:
$$C=\max_{p(x)}I(X;Y)$$
>$\max_{p(x)}$ means we are choosing the best possible probability distribution of the input $X$ to maximize mutual information.

with:
$$0\leq C\leq\min\{\log|\mathscr{X}|,\log|\mathscr{Y}|\}$$
>$C=0$ when $X$ and $Y$ are independent.

>[!Tip] Shannon's max bandwidth theorem
>Note that if we consider a _Gaussian noise channel_, we get the [[Livello fisico#Teorema di Shannon|Shannon's theorem]].

A method to reduce errors in a channel is to use the repetition of symbols, for example we can map each symbols to 3 repetition of itself, so if the we receive $010$ we can decode it as $0$ anyway, the problem arises when the majority of bits are altered, but the probability of errors is reduced if we add more repetitions.

But the transmission rate also reduces if we add more symbols.

**Shannon's noisy channel coding theorem**
If we pick a transmission rate $R<C$, there exists a sequence of codes such that the probability of error goes to zero as the code length goes to infinity.
Conversely, if $R>C$, the probability of error cannot go to zero.

In other words, the channel capacity $C$ is the maximum rate at which you can send information **reliably**.

