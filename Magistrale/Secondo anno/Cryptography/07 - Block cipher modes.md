A **mode of operation** repeatedly applies a block cipher ($E$, $D$) so that plaintexts longer than one block can be encrypted, it works with _any block cipher_ (e.g. [[06 - AES#The AES cipher|AES]]).

### Electronic CodeBook mode (ECB)
Split $X$ into blocks $x_1..x_n$ and **encrypt each independently** with the same key.
- $y_i=E_k(x_i)$
- $x_i=D_k(y_i)$

**Pros**
- Very simple and fast, and blocks can be processed in parallel.

**Cons**
- It is like a _monoalphabetic cipher_, so equal plaintext blocks give equal ciphertext blocks. this allows building a _code-book_.
- Fixed message parts (e.g. "Dear Alice") reveal how some blocks are encrypted, and the same blocks can be recognised elsewhere.

There is _no integrity_, since an attacker can duplicate, swap or delete blocks, which duplicates, swaps or deletes the corresponding plaintext blocks.
Knowing the format, they could _produce a different but meaningful plaintext_.

### Cipher Block Chaining mode (CBC)
Each block is **XORed with the previous ciphertext block** before encryption.
The first block uses an **IV (Initialization Vector)**, which can be sent in clear but _must be random and change every time_.
- $y_i=E_k(x_i\oplus y_{i-1})$, with $y_0=IV$
- $x_i=D_k(y_i)\oplus y_{i-1}$

**Pros**
- The same plaintext block is never encrypted the same way, which prevents the code-book attack.
- _Integrity is improved_: swapping, duplicating or deleting blocks corrupts at least one plaintext block (e.g. changing $y_1$ propagates to the next block).

It is still not satisfactory, because the application might not notice the corruption (e.g. it may not check $y_1$), and integrity checking shouldn’t be left entirely to the application.

**Cons**
- XOR introduces a new weakness, flipping a bit in $y_i$ _flips the same bit in $x_{i+1}$_, while $x_i$ is corrupted.

### Output FeedBack mode (OFB)
OFB turns a block cipher into a [[04 - Stream ciphers|stream cipher]].

The block cipher generates a **key stream**, and encryption is just XOR of plaintext with that stream, this is like a [[05 - Perfect ciphers#One time pad|one-time pad]] with a generated key.
>The closer the stream is to random, the closer the cipher is to a perfect one.

**Key generation** is _independent of plaintext and ciphertext_, so the stream can be generated offline and used later.

**Decryption** is the same XOR: ciphertext $\oplus$ key stream gives the plaintext.
The key stream is the **CBC encryption of a zero plaintext**, so CBC implementations can be reused.

Plaintext units can be _smaller than the cipher block_.
>One 128-bit AES output can be split into $128/8=16$ keys of 8 bits, one per byte.


**Pros**
- Very efficient, since the key stream can be precomputed
- Good for streams of plaintext
- The stream comes from a block cipher, so it is very hard to predict


**Cons**
- It is a _synchronous stream cipher_: the key stream does not depend on the plaintext
- _Reusing the same IV with the same key_ gives the same key stream (one-time-pad-reuse attack), so the IV must change for every message under the same key $k$
- _No integrity_: an attacker can flip chosen plaintext bits by flipping the same bits in the ciphertext, and no decrypted block is corrupted, for this reason it should only be used when integrity doesn’t matter or is provided by other mechanisms

#### Counter mode (CTR)
A variation of OFB where the IV is a **random nonce plus a counter**.
The nonce can be sent in clear (it must change for each new stream), and the counter changes during stream generation.

### Cipher FeedBack mode (CFB)
Mitigates OFB's problems by making the key stream **depend on the previous ciphertext**.

To encrypt units smaller than a block (e.g. a byte), it uses a **shift register**. the register is shifted left by the ciphertext size (8 bits for a byte), and the previous ciphertext is copied into the rightmost bits.

In decryption, as in OFB, the key stream is generated and XORed with the ciphertexts.

**Pros**
- Better integrity than OFB, since if one ciphertext bit is modified, the next BSize/CSize plaintext units are corrupted (BSize is the cipher block size, CSize the unit size).
>With AES and 8-bit units that is $128/8=16$ corrupted decryptions, which is the number of left shifts needed for a ciphertext to leave the register.

**Cons**
- Slower than OFB, since each step needs the previous ciphertext, so _encryption can't be parallelized_
- On noisy channels (satellite, TV) a single-bit error corrupts the next BSize/CSize plaintext units completely

---
### More block ciphers
Besides AES there are other popular currently used ciphers.

#### DES (Data Encryption Standard)
Predecessor of AES, it is still used, and uses 64 bits blocks and **56 bits keys**, which is also its main problem, since the 56-bit key is vulnerable to modern parallel computers.

Its **structure** involves:
- 16 identical rounds
- Splitting the block in two 32-bit halves processed alternately 

This block splitting and alternate processing (criss-crossing) is the **Feistel scheme**, which works as:
1. _Expansion_ : from 32 to 48 bits
2. _Key mixing_: XOR with a round key extracted from the key by permutation and circular shifts
3. _S-boxes_: substitution and compression, from 8 blocks of 6 bits to 8 blocks of 4 bits (32 bits)
4. _Permutation_: P-box

Alternating S-box substitution with P-box and expansion permutations gives **confusion and diffusion** (Shannon):
- _Confusion_:  the output differs drastically from the input (e.g. via a non-linear table built from the key)
- _Diffusion_: changing one input character changes many output characters

#### IDEA (International Data Encryption Algorithm)
Proposed in 1990 as a **DES substitute** and still used in many applications.

It involves **no S-boxes**, so confusion and diffusion come from a combination of XOR, addition and multiplication modulo $2^{16}$.

#### Blowfish
**Blowfish** is very fast, compact and simple, with highly configurable security, and its key length is _variable up to 448 bits_, which gives a security/speed trade-off.

Like DES it is based on XOR and S-boxes, but the **S-boxes are key-dependent**, which means that they are computed with the cipher itself and the actual key.

This _makes brute force expensive_, because generating the S-boxes for each key takes 522 iterations of the algorithm.

#### RC2, RC5, RC6
- **RC2 (1987)**: vulnerable to a related-key attack using $2^{34}$ chosen plaintexts
- **RC5 (1994)**: uses _data-dependent rotation_
    - Extremely simple: each round is two XORs, two additions modulo and two rotations, the key expansion is complex
    - Highly configurable in rounds, key length and word length, giving a security/performance trade-off
- **RC6** (derived from RC5) was an AES finalist

#### 3DES
It is a **triple iteration of DES**, currently used in SSH and TLS/SSL, and in many commercial applications.

---
### Iterating ciphers
Iteration is one way to **strengthen a cipher**, all modern ciphers are built from rounds, and iterating a whole cipher (DES, AES) _increases the key length_.
>Three DES iterations with $(k_1,k_2,k_3)$ give 168 bits.

Iteration only makes sense if the cipher is [[05 - Perfect ciphers#Idempotent ciphers|not idempotent]].

#### DES is non-idempotent
We now show an informal argument on why modern block ciphers are very unlikely to be idempotent, using DES as an example.

DES has 64-bit blocks, so there are $2^{64}$ possible blocks, each key maps blocks to blocks injectively, since encryption must be invertible, so **each key is a permutation** of all blocks:
- There are $2^{64}!$ permutations, enormously more than the $2^{56}$ DES keys, keys select what looks like a random subset of $2^{56}$ permutations
- The probability that the composition of two such permutations is still in the subset is $2^{56}/2^{64}!$, which is negligible.

So two DES iterations are very unlikely to equal one DES under another key, and thus **DES is non-idempotent** (formal proofs also exist).

#### Meet-in-the-middle attack (on 2DES)
Considering 2DES (which has a key of $56\times 2=112$ bits), which is non-idempotent, is it really true that now, in order to break the cipher, we have to try all the possible key pairs?

No, we can exploit the so called **meet-in-the-middle attack**.

**Known-plaintext scenario**: the attacker has pairs $(X,Y),(X',Y'),\dots$ under the same key
1. Take one pair $(X,Y)$ and _decrypt $Y$ under all possible $k_2$_, then store each result $Z$ in a table indexed by $Z$, together with the key
2. _Encrypt $X$ under all possible $k_1$_ and look each result up in the table
3. On a match, test $(k_1,k_2)$ on all the other pairs, if every test succeeds, output it

**Cost**
Step 1 takes $2^{56}$ steps and builds a table of $2^{56}$ entries, step 2 takes at most $2^{56}$ steps, so in total $2^{56}+2^{56}=\mathbf{2^{57}}$ steps and $2^{56}$ space, versus $2^{112}$ for brute force.

A pair $(k_1,k_2)$ that works for $(X,Y)$ may not be the right one, so it must be tested on other pairs, this happens more often than expected, this leads to **false keys**.

**Assumption**: keys map plaintexts to ciphertexts uniformly, this holds for any good cipher, since a non-uniform mapping would make some plaintexts more likely given $Y$.

The **number of false keys** $\approx |K|/|C|=2^{112}/2^{64}=2^{48}$, but a false key also passes $(X',Y')$ with probability $1/2^{64}$, so false keys drop to $2^{48}/2^{64}=1/2^{16}$, then $1/2^{80}$ with one more pair, and so on.

>[!Attention]
>With 3 plaintext/ciphertext pairs the attack has a negligible chance of returning a false key.

>[!Info]
>- The **time cost is basically the same** as for a single DES, for this reason **2DES is never used**, and we use 3DES instead, with a 168-bit key $(k_1,k_2,k_3)$
>- Meet-in-the-middle still works on 3DES but only reduces the time cost to $2^{112}$, with a table of $2^{56}$ entries, the table is built by decrypting $Y$ under all $k_3$, then trying all pairs $(k_1,k_2)$

