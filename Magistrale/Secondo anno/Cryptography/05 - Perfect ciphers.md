The **conditional probability of a plaintext** w.r.t. a ciphertext is related to the security of the cipher, it is a measure of how likely is a plaintext once a ciphertext is observed (which is what the attacker is usually interested to know).

Recall the [[04 - Stream ciphers#Perfect ciphers|conditional probability of a ciphertext]], we can invert it using the [[Probabilità condizionata#Teorema di Bayes|Bayes theorem]]:
$$p_P(x|y)=\frac{p_P(x)p_C(y|x)}{p_C(y)}$$
>[!Example]
>$P=\{a,b\}$, $K=\{k_1,k_2\}$, $C=\{1,2,3\}$.
>Encryption is defined by the following table:
>$$\begin{array}{c\|cc\|} E & a & b \\ \hline k1 & 1 & 2 \\ k2 & 2 & 3 \\ \hline \end{array}$$
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

**Theorem**
Let $p_C(y)>0$ for all $y$, a cipher is perfect only if $|K|\geq|P|$.
That is: the number of keys is at least the same number as the number of plaintexts.

**Proof**
For Bayes' theorem, assume that the cipher is perfect, so $p_P(x|y)=p_P(x)$ for all $x$ in $P$ and $y$ in $C$, that implies $p_C(y|x)=p_C(y)$ for all $x$ in $P$ and $y$ in $C$.

As an assumption $p_C(y)>0$.
If we fix $x$, we obtain that for each $y4, $p_C(y|x)=p_C(y)>0$, meaning that there exists _at least on_ key $k$ such that $E_k(x)=y$ (otherwise $p_C(y|x)=0$).

_All such keys are different_ since $E_k$ is a function and we have fixed $x$, and $x$ cannot be mapped to two different ciphertexts by the same key.

Thus, we have at least one key for each ciphertext, that is: $|K|\geq|C|$.

Since for any cipher (not necessarily perfect), $E_k$ injects the set of plaintexts into the set of ciphertexts, we also have that $|C|\geq|P|$, thus $|K|\geq|C|\geq|P|$, which leads us to $|K|\geq|P|$.

