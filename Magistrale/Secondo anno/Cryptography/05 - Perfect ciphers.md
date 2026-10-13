The **conditional probability of a plaintext** w.r.t. a ciphertext is related to the security of the cipher, it is a measure of how likely is a plaintext once a ciphertext is observed (which is what the attacker is usually interested to know).

Recall the [[04 - Stream ciphers#Perfect ciphers|conditional probability of a ciphertext]], we can invert it using the [[Probabilità condizionata#Teorema di Bayes|Bayes theorem]]:
$$p_P(x|y)=\frac{p_P(x)p_C(y|x)}{p_C(y)}$$
>[!Example]
>$P=\{a,b\}$, $K=\{k_1,k_2\}$, $C=\{1,2,3\}$.
>Encryption is defined by the following table:
>$$\begin{array}{c|cc|} E & a & b \\ \hline k1 & 1 & 2 \\ k2 & 2 & 3 \\ \hline \end{array}$$
>
>Now, let $p_P(a)=3/4$, $p_P(b)=1/4$, $p_k(k_1)=p_k(k_2)=1/2$.
>
>We can now compute the probabilities of plaintexts $a$ and $b$ w.r.t. ciphertext $1$, we have $p_C(1|a)=1/2$ and $p_C(1|b)=0$, and we obtain:
>$$p_P(a|1)=\frac{p_P(a)p_C(1|a)}{p_C(1)}=\frac{3/4\cdot1/2}{3/8}=1$$
>$$p_P(b|1)=\frac{1/4\cdot0}{3/8}=0$$
>>When observing $1$ we are sure it is plaintext $a$, meaning that this cipher is _completely insecure_.

A cipher is **perfect** iff $p_P(x|y)=p_P(x)$ for all $x\in P$ and $y\in C$.
That means that there is some key that _maps any message to any ciphertext_ with _equal probability_.

>[!Example]
>We want to prove that the shift cipher with $p_K(k)=1/|K|=1/26$, that is: with keys picked at random for each letter of the plaintext is a perfect cipher.
>
>If we show that $p_C(y|x)=p_P(y)$ for every $x$ and $y$, then $p_P(x|y)=p_P(x)$ for every $x$ and $y$ so the cipher is perfect.
>
>$$p_C(y|x)=\sum_{k\in K,E_k(x)=y}p_K(k)=p_K(y-x\mod26)=\frac{1}{26}$$
>>Note that given $x$ and $y$ there exists a unique key $k$ that encrypts $x$ as $y$ and is $y-x\mod26$.
>
>$$p_P(x|y)=\frac{p_P(x)p_C(y|x)}{p_C(y)}=\frac{p_P(x)\frac{1}{26}}{\frac{1}{26}}=p_P(x)$$ 

In practice, if we change key, then encrypt a letter, the shift cipher becomes perfect, we now show that this strong requirement is indeed **necessary**, and we cannot hope to develop perfect ciphers without it.

**Theorem 1**
Let $p_C(y)>0$ for all $y$, a cipher is perfect only if $|K|\geq|P|$.
That is: the number of keys is at least the same number as the number of plaintexts.

**Proof**
For Bayes' theorem, assume that the cipher is perfect, so $p_P(x|y)=p_P(x)$ for all $x$ in $P$ and $y$ in $C$, that implies $p_C(y|x)=p_C(y)$ for all $x$ in $P$ and $y$ in $C$.

As an assumption $p_C(y)>0$.
If we fix $x$, we obtain that for each $y$, $p_C(y|x)=p_C(y)>0$, meaning that there exists _at least on_ key $k$ such that $E_k(x)=y$ (otherwise $p_C(y|x)=0$).

_All such keys are different_ since $E_k$ is a function and we have fixed $x$, and $x$ cannot be mapped to two different ciphertexts by the same key.

Thus, we have at least one key for each ciphertext, that is: $|K|\geq|C|$.

Since for any cipher (not necessarily perfect), $E_k$ injects the set of plaintexts into the set of ciphertexts, we also have that $|C|\geq|P|$, thus $|K|\geq|C|\geq|P|$, which leads us to $|K|\geq|P|$.

**Theorem 2**
Let $|P|=|C|=|K|$, a cipher is perfect iff:
1. $p_k(k)=\frac{1}{|K|}$ for all $k$ in $K$
2. For each $x$ in $P$ and $y$ in $C$, there exists exactly one key $k$ such that $E_k(x)=y$

The theorem states that for a cipher to be perfect (given that the size of $P$, $C$, $K$ is the same) keys should be picked at random for any encryption and each plaintext is mapped into each ciphertext through a unique key.

### One time pad
The **encryption** works as follows:
$$E_{(K_1,...,d_d)}(x_1,...,x_d)=(x_1\oplus k_1,...,x_d\oplus k_d)$$
where $\oplus$ is a bitwise xor operation.

This is a **perfect cipher** since set sizes are the same and we can apply the _second perfect cipher theorem_:
1. $p_K(k)=\frac{1}{|K|}$
2. Let $x$ in $P$ and $y$ in $C$, we have that the unique key giving $y$ from $x$ is computed as $x\oplus y$, that is $k_1=x_1\oplus y_1$, ..., $k_d=x_d\oplus y_d$
>We can conclude that the cipher is perfect.

Shannon theory on perfect ciphers shows that <u>they exist but require as many keys as the possible
plaintexts</u>, and keys need to be **picked at random** for each encryption.

### Composition of ciphers
A OTP cipher is hard to implement, modern ciphers are based on very **simple primitives** (e.g. xor, substitution), that are combined in a smart way in order to make the overall algorithm strong and hard to cryptoanalyze.

Note that combining simple ciphers _does not always improve security_, for example a composition of two shift ciphers, say shift by $k_1$, then by $k_2$, is equal to shifting by $k_1+k_2$.

**Composition**
We consider two ciphers $S^1=(P^1,C^1,K_1,E^1,D^1)$ and $S^2=(P^2,C^2,K_2,E^2,D^2)$.
>Let $P^1=C^1=P^2=C^2$, that we note as $P$ and $C$ in the following.

In this way, the output of one cipher is for sure a possible plaintext for the second cipher.

We can now define the composition as:
$$S^1\times S^2=(P,C,K_1\times K_2,E,D)$$
$$E_{(k_1,k_2)}(x)=E_{k_2}^2(E_{k_1}^1(x))\quad D_{(k_1,k_2)}(y)=D_{k_1}^1(D_{k_2}^2(y))$$

### Idempotent ciphers
When a repeated composition cipher is equivalent to itself with a different key, it is said to be **idempotent**, written $S\times S=S$.

In this case we know that iterating the cipher will be of no use to improve its security, and is thus necessary that the simple primitives it uses do not constitute an idempotent cipher.

It can be proved that if we have two **idempotent ciphers that commute**, such that $S^1\times S^2=S^2\times S^1$, then _their composition is also idempotent_.
