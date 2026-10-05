**Block ciphers** are cryptosystems that reuse the same key to encrypt letters or blocks of the plaintext.

**Stream ciphers** are cryptosystems that use a stream of keys $z_1,...,z_n$ instead of a single one, so ideally the $i$-th letter of plaintext gets encrypted with $z_i$.
It does not matter if we encrypt a letter or a block, but that the key is always different.

The stream of key is usually derived starting from an **initial key $k$**, and it can also _depend on previous parts of the plaintext_, in general we say that:
$$z_i=f_i(k,x_1,...,x_{i-1})$$
>Note how block ciphers are an instance of stream ciphers where $z_i=k$ for all $i$.

A stream cipher is **periodic** if its key stream has the following form:
$$z_1,...,z_d,z_1,...,z_d,z_1,...$$
>That is: if it repeats after $d$ steps.

>[!Example]
>**Vigenére cipher** can be seen as a (synchronous) stream cipher acting on single letters and with a periodic key stream.
>
>We can formalize the cipher giving $(P,C,K,E,D)$ and defining the key stream $z_i$:
>- $P=C=K=Z_{26}$
>- $E_{z_i}=(x_i+z_i)\mod26$
>- $D_{z_i}(y_i)=(y_i-z_i)\mod26$
>- $z_i=k_{(i\mod m)}$

A stream cipher is **synchronous** if its keys stream does not depend on the plaintexts, that is: $z_i=f_i(k)$ for all $i$.
>The key stream can be generated starting from $k$ and independently on the plaintext.

In this way the key stream can be **generate offline (precomputed)** before the actual ciphertext is received.

An **asynchronous** stream cipher is defined as $z_i=f+i(k,x_1,...,x_{i-1})$, and in this case we need to decrypt and compute the keys stream at the same time, as a key can depend on previous plaintexts.

>[!Example]
>We can define an **autokey cipher** as an asynchronous stream cipher:
>- $P=C=K=Z_{26}$
>- $E_{z_i}(x_i)=(x_i+z_i)\mod26$
>- $D_{z_i}(y_i)=(y_i-z_i)\mod26$
>- $z_1=k$ and $z_i=x_{i-1}$ for $i\geq2$
>  
>  ```
>  k=5
>  13 4 19 22 14 17 10 18 4 2 20 17 8 19 24
>  18 17 23 15 10 5 1 2 22 6 22 11 25 1 17
>  ```

### Perfect ciphers
A **perfect cipher** is a cipher that can never be broken, even after an unlimited time.
>In reality they can be implemented, but they are _unpractical_.

A cipher system is said to offer **perfect secrecy** if, on seeing the ciphertext, the interceptor gets _not extra information_ about the plaintext than he had before the ciphertext was observed.

Given a plaintext and a key there exists a unique corresponding ciphertext.
- $p_p(x)$ is the probability of a plaintext $x$ to occur
- $p_K(k)$ is the probability of a certain key $k$ to be used as the encryption key

The two probability distributions $p_p(x)$ and $p_K(k)$ induce a probability distribution on the ciphertexts:
$$p_C(y)=\sum_{k\in K,\exists x: E_k(x)=y}p_K(k)p_P(D_k(y))$$
Given a ciphertext $y$ we look for all the keys that can give such a ciphertext from some plaintext $x$, we then sum the probability of all such keys times the probability of the corresponding plaintext.

>[!Example]
>$P=\{a,b\}$, $K=\{k_1,k_2\}$, $C=\{1,2,3\}$.
>Encryption is defined by the following table:
>$$\begin{array}{c\|cc\|} E & a & b \\ \hline k1 & 1 & 2 \\ k2 & 2 & 3 \\ \hline \end{array}$$
>
>Now, let $p_P(a)=3/4$, $p_P(b)=1/4$, $p_k(k_1)=p_k(k_2)=1/2$.
>Let's now compute $p_c(1)$:
>$$p_c(1)=p_k(k_1)p_P(D_k(1))=1/2\cdot3/4=3/8$$
>>Note that $k_1$ is the only key giving ciphertext $1$.

The **conditional probability of a ciphertext** $y$ w.r.t. a plaintext $x$ computes how likely is a certain $y$ once we fix $x$:
$$p_C(y|x)=\sum_{k\in K, E_k(x)=y}p_K(k)$$
>It is simply the sum of the probability of all keys giving $y$ from $x$.

>[!Example]
>The conditional probability of ciphertext $1$ w.r.t. the two plaintexts $a$ and $b$ is:
>$$p_C(1|a)=\sum_{k\in K, E_k(x)=y}p_K(k)=p_K(k1)=1/2$$
>$$p_C(1|b)=\sum_{k\in K, E_k(x)=y}p_K(k)=0$$
>>Note that $1$ can never be obtained from $b$.

