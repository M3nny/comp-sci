A **cryptosystem** (or cipher) can be defined as a quintuple $(P,C,K,E,D)$ where:
- $P$: set of plaintexts
- $C$: set of ciphertexts
- $K$: set of keys
- $E$: $k\times P\to C$ is the encryption function
- $D$: $k\times C\to P$ is the decryption function

Let $x\in P$, $y\in C$, $k\in K$, we will write $E_k(x)$ and $D_k(y)$ to denote $E(k,x)$ and $D(k,y)$, that is: the encryption and decryption under the key $k$ of $x$ and $y$, respectively.

We require that:
1. $D_k(E_k(x))=x$, that is: decrypting a ciphertext with the right key gives the original plaintext
2. Computing $k$ or $x$ given a ciphertext is **infeasible**

>[!Example] Caesar cipher
>If we use $k=3$:
>$$\text{BHV BRX PDGH LW}$$
>$$\text{YES YOU MADE IT}$$

**Kerckhoffs’ principle**: a cipher should remain secure even if the algorithm becomes public, so it is not the algorithm that needs to be hidden, it is its key.

### Shift cipher
We can consider Caesar cipher a **shift cipher** with $k=3$, we are going to generalize it.

If each letter is in the integer range $0$ to $25$, we have that $P=C=K=Z_{26}$:
- $E_k(x)=x+k\mod 26$
- $D_k(y)=y-k\mod 26$

This works sine if we decrypt the encrypted text with the above rules we get the original $x$, note also that $Z_{26}$ is a **group** under the _addition_ (not under the multiplication).

#### Groups
A **group** $<G,*>$ is a set $G$ together with a (closed) binary operation $*$ on $G$ such that:
- The operator is _associative_, that is: $(x*y)*z=x*(y*z)$ for all $x,y,z\in<G,*>$
- There is an element $e\in G$ such that $a*e=e*a=a$ for all $a\in G$, such element is the _identity element_
- For every $a\in G$, there is an element $b\in G$ such that $a*b=e$, this $b$ is said to be the _inverse_ of $a$ with respect to $*$. The inverse of $a$ is sometimes denoted as $a^{-1}$

The set $<Z,+>$, which is a set of integers under addition, forms a group,.
A group that is _commutative with an additive operator_ is said to be an **abelian group**.

The set $<Z,\cdot>$, which is the set of integers under multiplication, does not form a group, there is a multiplicative identity $1$, but there is no multiplicative inverse for every element in $Z$.

#### Attacks to shift ciphers
In order to find the key we can just **brute force** by trying all the possible 26 keys, since the problem is very small.

Kerckhoffs' principle does not hold in this case, since the algorithm is too weak, and if known, even if they key is not known, it can be exploited nevertheless.

### Substitution cipher
Instead of having a key represent a shift equal for every letter, in this case we use an arbitrary **mapping between letters**.

Now, computing $k$ or $x$ given a ciphertext $y$ is _infeasible_.
The key is a generic substitution (permutation), there are $26!$ permutations, which is approximately $4\times10^{26}>2^{88}$, which is very _hard to brute force_.

But, it is a **monoalphabetic cipher** which means that it maps a letter to the very same letter, thus preserving **statistics** of the plaintext and makes it possible to reconstruct the key by observing the statistics in the ciphertext.

### Statistical cryptoanalysis
Let's assume that we know the used cipher (e.g. a monoalphabetic substitution cipher) and the language used in the plaintext (e.g. Italian).

Given a ciphertext $C$, we can compute the frequency of the letters.

>[!Example] Analyzing the Italian vocabulary
>In Italian, letter $A$ will be the most frequent, and another fact is that the frequency of the letters $I$ and $L$ increases at the beginning of the sentences, while the vowels are used at the end of the words.
>
>Also, there are groups of letters that appear together often.

In order to decrypt this kind of cipher:
1. **Order** the letters of the ciphertext into decreasing frequencies
2. **Substitute** with letters in decreasing order as in the corresponding tables (depending on the language)
3. **Fix** words that look close to normal

### Polyalphabetic ciphers
With this technique, the same plain symbol is now not always mapped to the same encrypted symbol.

**Vigenére cipher**
Use a word as they key, for example "FLUTE", which has length $m=5$.
Split the plaintext in blocks of $m$ length, for each position of the block $[0,...,m-1]$ shift the letter position by the position associated to the current key index.
>[!Example]
>```
>THISISAVERYSECRETMESSAGE +
>FLUTEFLUTEFLUTEFLUTEFLUT =
>YSCLMXLPXVDDYVVJEGXWXLAX
>```

The number of possible keys is $26^m$, that is: all the possible sequence of letters of length $m$, for $m$ big enough this prevents brute force attacks.

The _histogram of the frequencies is flat_ (the flatness increases with the increase of the key length), so it does not help.
