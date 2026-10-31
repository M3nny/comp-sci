All the ciphers seen so far (Caesar, Vigenère, Hill, ...) use the **same key $k$** to encrypt and decrypt, for this reason they are called **symmetric-key ciphers**.

The sender and receiver must therefore _share the secret key in advance_, through a secure channel (e.g. meeting in person).

Without a trusted central key service, _every pair of users needs its own key_, and for $N$ users this gives:
$$\frac{N(N-1)}{2} = O(N^2)\ \text{keys}$$

### Asymmetric cryptography

The idea was proposed in 1976 by Whitfield Diffie and Martin Hellman, and it consists of each user $A$ having a **key pair**:
- A **public key $PK_A$**: published in a public directory and known to everybody, even attackers, which is used to _encrypt_
- A **private key $SK_A$**, known only to $A$, which is used to _decrypt_
>The two keys are mathematically related, but knowing $PK$ gives no practical way to find $SK$.

The **protocol** is then: $B$ sends $E_{PK_A}(M)$ to $A$, and $A$ recovers the message with $D_{SK_A}(E_{PK_A}(M)) = M$.

Only $N$ public keys and $N$ private keys ($2N$ keys in total), are needed, this is $O(N)$ instead of $O(N^2)$, and no secret has to be pre-shared.

#### Formal definition
An asymmetric cipher is a quintuple $(\mathcal P,\mathcal C,\mathcal K_S\times\mathcal K_P,E,D)$ with $E:\mathcal K_P\times\mathcal P\to\mathcal C$ and $D:\mathcal K_S\times\mathcal C\to\mathcal P$, such that:
1. **Generating a key pair** $(SK,PK)$ is computationally _easy_
2. Computing $y=E_{PK}(x)$ is _easy_
3. Computing $x=D_{SK}(y)$ is _easy_
4. **Correctness**: $D_{SK}(E_{PK}(x))=x$
5. Computing $SK$ from $PK$ and $y$ is **computationally infeasible**
6. Computing $D_{SK}(y)$ from $PK$ and $y$ **without $SK$** is **infeasible**

Items 1–3 say the cipher must be **practical to use**, item 4 says **decryption must work**. Items 5–6 say the cipher must stay _secure even though the public key is public_.

**The central challenge**: the keys must be related, otherwise decryption could never work, yet deriving $SK$ from $PK$ must still be infeasible.

This respects **secrecy** since only the holder of $SK_A$ can read messages sent to $A$, but there is **no authentication** since $PK_A$ is public, _anyone can send $A$ a message claiming to be $B$_.
>With symmetric keys this does not happen, because only $B$ knows the shared key.
>For this issue we also need **digital signatures**, which will be discussed later.

### One-way and trap-door functions
Asymmetric-key ciphers are strictly related to **one-way trap-door functions**.

A **one-way function** (injective and invertible): $y=f(x)$ is easy to compute, but $x=f^{-1}(y)$ is _infeasible_ to compute (which does not mean that the inverse doesn't exist).

A **one-way trap-door function** is a family $f_k$ where, given $k$, $y=f_k(x)$ is easy, but $f_k^{-1}(y)$ is _infeasible unless you know a secret trap-door $S(k)$_.
>With the trap-door, inversion becomes easy.

In **cryptography** the public key defines the function $f_k$ (encryption), and the private key is the trap-door (decryption).

### Merkle-Hellman knapsack cryptosystem
Even if this system was later **broken** (by Shamir in 1982), it is still useful because it clearly shows how a trap-door is built.

Given positive integers $s_1,\dots,s_n$ (the _sizes_) and a _target_ $T$, find a binary tuple $(x_1,\dots,x_n)$ such that:
$$\sum_{i=1}^{n} x_i s_i = T$$

>[!Example]
>Sizes $(4,6,3,8,1)$ and $T=11$ have two solutions:
>- $(0,0,1,1,0)$, since $3+8=11$
>- $(1,1,0,0,1)$, since $4+6+1=11$

The problem is [[Teoria della NP completezza#Classe NPC|NP-complete]] in general, so $f(x_1,\dots,x_n)=\sum x_i s_i$ is a **one-way function**, it is easy to compute, but inverting it (recovering the bits from the sum) is infeasible for large $n$.

**Super-increasing** means each element is larger than the sum of all previous ones:
$$s_i > \sum_{j=1}^{i-1} s_j \quad \text{for all } i>1$$
>For example $(1,3,5,10)$ is super-increasing, but $(1,3,5,9)$ is not, because $9 = 1+3+5$.

An **easy greedy algorithm** is to go from the biggest element down, so if $s_i \le T$, take it ($x_i=1$) and set $T \leftarrow T-s_i$, otherwise set $x_i=0$.
At the end, if $T=0$ a solution was found, otherwise there is none.

**The idea behind this greedy algorithm**: if $s_i\le T$, we must take it, because all smaller elements together sum to less than $s_i$ and could never reach $T$ without it.
>For $(1,3,5,10)$ the sum $5+3+1=9<10$.

Considering sizes $[1,3,5,10]$:

| Target | Result               |
| ------ | -------------------- |
| 11     | $[1,0,0,1]$ (10+1)   |
| 12     | $[\,]$ (no solution) |
| 13     | $[0,1,0,1]$ (10+3)   |
| 14     | $[1,1,0,1]$ (10+3+1) |

#### Key generation
1. Start from a super-increasing sequence $(s_1,\dots,s_n)$
2. Choose a _prime_ $p>\sum_{i=1}^n s_i$
3. Choose a random $a$ with $1<a<p$
4. Compute the disguised sequence $\hat s_i = a\,s_i \bmod p$ (in general this is _not super-increasing_, so it looks like a hard knapsack)
>$(1,2,5,12)$, $p=23$, $a=6$ gives $(6,12,7,3)$.

| |Value|
|---|---|
|**Private key (trap-door)**|$(s_1,\dots,s_n)$, $p$ and $a$, e.g. $(1,2,5,12)$, 23, 6|
|**Public key**|$(\hat s_1,\dots,\hat s_n)$, e.g. $(6,12,7,3)$|

#### Encryption
Convert the message to binary (ASCII) to get bits $x_1,\dots,x_n$, then compute:
$$E_{PK}(x_1,\dots,x_n)=\sum_{i=1}^{n} x_i\hat s_i$$
>Plaintext $(1,0,0,1)$ with public key $(6,12,7,3)$ gives $6+3=9$.

Without the trap-door, recovering the bits from 9 means solving a hard (apparently non-super-increasing) subset-sum problem.

#### Decryption
1. Compute $a^{-1} \bmod p$, the modular inverse of $a$
2. Compute $T = a^{-1}\,y \bmod p$
3. Solve the **super-increasing** problem $(s_1,\dots,s_n)$ with target $T$ using the greedy algorithm, the result is the plaintext

##### Worked example
Given super-increasing sequence $(2,7,11,21,42,89,180,354)$, $p=881$, $a=588$.
The sum of the sequence is $706<881$, so the conditions hold.

_Public key_: $\hat s_i = 588\,s_i \bmod 881$

| $s_i$ | $588\,s_i$ | mod 881 |
| ----- | ---------- | ------- |
| 2     | 1176       | 295     |
| 7     | 4116       | 592     |
| 11    | 6468       | 301     |
| 21    | 12348      | 14      |
| 42    | 24696      | 28      |
| 89    | 52332      | 353     |
| 180   | 105840     | 120     |
| 354   | 208152     | 236     |

_Public key_: $(295,\,592,\,301,\,14,\,28,\,353,\,120,\,236)$.

**Encrypting the letter "a"**
ASCII "a" = 97 = `01100001`, so $x=(0,1,1,0,0,0,0,1)$.
$$y = 592 + 301 + 236 = 1129$$
**Decrypting**
1. $a^{-1} \bmod 881 = 442$, because $588\cdot442 = 259{,}896 = 295\cdot881+1$
2. $T = 442\cdot1129 \bmod 881 = 442\cdot248 \bmod 881 = \mathbf{372}$, using $1129\equiv248$
3. Greedy on $(2,7,11,21,42,89,180,354)$ with $T=372$:
    - 354 fits, remainder 18
    - 180, 89, 42 and 21 don't fit
    - 11 fits, remainder 7
    - 7 fits, remainder 0
    - 2 is skipped

Result: $(0,1,1,0,0,0,0,1)=01100001=97=$ **"a"**.

