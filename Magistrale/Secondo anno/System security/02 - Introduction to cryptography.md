A **cipher** is defined through two functions:
- _Encryption_: given a plaintext and a key $K1$ returns a ciphertext $E_{K1}(X)=Y$
- _Decryption_: given a ciphertext and a key $K2$ returns a plaintext $D_{K2}(Y)=X$

When $K1=K2$ we have a **symmetric** key cipher, when $K1\neq K2$ we have an **asymmetric** key cipher.
>It should be _infeasible_ to compute $X$ or $K2$ from $Y$ even knowing other pairs $(X_1,Y_1),...,(X_n,Y_n)$.

A **collision resistant hash function** $h$ is one for which it is infeasible to compute different $x_1,x_2$ such that $h(x_1)=h(x_2)$.

A **one-way hash function** $h$ is one for which, given a digest $z$ it is infeasible to compute a preimage $x'$ such that $h(x')=z$.

**Cryptographic vulnerabilities** include:
- _Vulnerabilities in applications_: can reveal keys or downgrade to less secure mechanisms
- _Insecurity of mechanism_: cypto mechanisms are not equally secure
- _Configuration and management_: the configuration and management of cryptographic systems is complex and error prone
- _Cryptoanalysis_: improvements in technology and cryptoanalysis require better crypto

**Heartbleed** is a vulnerability in OpenSSL, where an over-read allows for accessing process memory where server keys are stored, allowing to then mount a MITM attack and intercept the whole Web session.

### ECB weaknesses
When the data is bigger than the block size compute by the cryptographic function, we split the data in blocks, this procedure is called **ECB (Electronic CodeBook)**, for example AES-ECB.

In ECB blocks are **encrypted independently** under the same key, which leads to:
- Equal blocks are encrypted in the same way
- Swapping encrypted blocks also swaps plaintext blocks

If an attacker can _prepend arbitrary prefix_ to the plaintext they can bruteforce blocks byte after byte: AES uses 16 bytes blocks, if we prepend 15 known bytes and brute force the 16th and then iterate over all the bytes we have bruteforced all of them.
![[ECB attack 1.png|400]]![[ECB attack 2.png|400]]

### Stream cipher
A **stream cipher** uses a **CTR (counter mode)** using a _random nonce_ (called initialization vector) which is a unique, arbitrary number used only once in a cryptographic operation.

If the CTR has a configuration mistake and introduces a fixed nonce, we could break a ciphertext by knowing a pair of plaintext and its ciphertext.

```
ciphertext 1:
8f079a817d1dfa5bb2b1e069b0f4027abc65db6d130e6f3c154611d165d66b0a2342473479
0df0769cc3c4f4f289e784ac0cc5cab7e47c5c1a

ciphertext 2:
9f0a92807d33fb1ab7a9ad36e5cd4064a320da7a56122e21004c42c46d93214b28595b7776
12e46c9dc3c4eefedde88ee31c97c1b1e834135c

Leaked plaintext 1:
Dear Graham, I'll be happy to participate in the training
```

$P1, P2$ plaintexts and $C1, C2$ corresponding ciphertext.
Same nonce means same key $K$:
- $P1\oplus K=C1$
- $P2\oplus K=C2$

Thus:
- $P1\oplus P2=C1\oplus C2$ 
- $P2=P1\oplus C1\oplus C2$

