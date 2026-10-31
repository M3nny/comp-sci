**RSA** is named after Rivest, Shamir and Adleman (1978), and it is a public-key cipher based on _prime numbers_.

It has not been broken, its security rests on the belief that **factoring** a large $n=pq$ into $p$ and $q$ is _infeasible_. without the factors, $\phi(n)$ cannot be computed and the private key cannot be found.

### Euler's function
$\phi(n)$ is the **number of integers in $\{1,\dots,n\}$ that are coprime** to $n$ (i.e. $\gcd(i,n)=1$).
>Their only common divisor is 1.

|$n$|1|2|3|4|5|6|7|
|---|---|---|---|---|---|---|---|
|$\phi(n)$|1|1|2|2|4|2|6|

- **If $n$ is prime**: $\phi(n)=n-1$, because a prime is coprime to every smaller positive number
	$\phi(7)=6$.
- **If $n=p_1\cdots p_k$ with distinct primes**: $\phi(n)=(p_1-1)\cdots(p_k-1)$
	 $\phi(15)=\phi(3)\phi(5)=2\cdot 4=8$, the coprime numbers are $1,2,4,7,8,11,13,14$.

**Proof** for $n=pq$ ($p\neq q$ prime)
The numbers below $n$ that are not coprime to $n$ are the multiples of $p$ (namely $p,2p,\dots,(q-1)p$, which is $q-1$ numbers) and the multiples of $q$ (namely $q,2q,\dots,(p-1)q$, which is $p-1$ numbers), hence:
$$\phi(n)=pq-1-(q-1)-(p-1)=pq-p-q+1=(p-1)(q-1)$$

### Key generation
1. Generate two distinct, **big primes** $p$ and $q$
2. Compute $n=pq$ and $\phi(n)=(p-1)(q-1)$
3. Choose $a$ with $a<\phi(n)$ and $\gcd(a,\phi(n))=1$
4. Compute the unique $b$ such that $a\cdot b \equiv 1 \pmod{\phi(n)}$ (i.e. $b=a^{-1} \bmod \phi(n)$), this is computed with the [[03 - Known plaintext attacks#Greatest common divisor|extended Euclidean algorithm]]

**Keys**
$$PK=(b,n),\qquad SK=(a,n),\qquad \mathcal C=\mathcal P=\mathbb Z_n$$

**Encryption and decryption**
$$E_{PK}(x)=x^{b}\bmod n,\qquad D_{SK}(y)=y^{a}\bmod n$$
>We denote the public exponent $b$ and the private one $a$.

**Why it works**
Since $ab\equiv 1 \pmod{\phi(n)}$, we can write $ab = 1+k\phi(n)$, and by Euler’s theorem, $x^{\phi(n)}\equiv 1 \pmod n$ when $\gcd(x,n)=1$, so:
$$(x^b)^a = x^{1+k\phi(n)} = x\cdot (x^{\phi(n)})^k \equiv x \pmod n$$
The same holds for all $x$ when $n=pq$, even if $x$ shares a factor with $n$.

**Why $\phi(n)$ must stay secret**
$n$ and $b$ are public, anyone who could compute $\phi(n)=(p-1)(q-1)$ could compute $a=b^{-1}\bmod\phi(n)$, computing $\phi(n)$ requires factoring $n$, which is infeasible for large $n$.

> [!example] RSA examples
> **Example 1**: $p=5$, $q=11$.
>
> - $p=5$, $q=11$ gives $n=55$ and $\phi(55)=4\cdot10=40$
> - Choose $a=23$ (coprime to 40), then $b=7$ from the extended Euclid above
> - $PK=(7,55)$, $SK=(23,55)$
> - **Encryption** of $x=2$: $2^7 = 128 \equiv 128-110 = 18 \pmod{55}$
> - **Decryption**: $18^{23}\bmod 55 = 2$
>
> ---
>
> **Example 2**: $p=11$, $q=13$.
>
> - $n=143$ and $\phi(143)=10\cdot12=120$
> - Choose $a=7$, since $\gcd(7,120)=1$
> - Find $b$ with $7b\equiv1 \pmod{120}$, we get $b=103$, because $7\cdot103=721=6\cdot120+1$
> - $PK=(103,143)$, $SK=(7,143)$
> - **Encryption** of $x=2$: $y=2^{103}\bmod 143$, using the Chinese Remainder Theorem:
>   - mod 11: $2^{10}\equiv1$, so $2^{103}\equiv2^3=8$
>   - mod 13: $2^{12}\equiv1$, so $2^{103}\equiv2^7=128\equiv11$
>   - The unique solution mod 143 is $y=\mathbf{63}$ (check: $63\equiv 8 \pmod{11}$ and $63\equiv 11 \pmod{13}$)
> - **Decryption:** $63^{7}\bmod 143$. mod 11: $8^7\equiv 2$. mod 13: $(-2)^7=-128\equiv 2$, so the result is $2$, the original plaintext

### Implementation issues
Secure RSA needs a modulus $n$ of **at least 1024 bits**, at this size, algorithms must be _polynomial in the bit-length $k$_, an algorithm that is linear in the _value_ of $n$ would take about $2^{1024}$ steps, which is impossible.

**Cost of basic operations on $k$-bit numbers**:

|Operation|Cost|
|---|---|
|Addition|$O(k)$|
|Multiplication|$O(k^2)$|
|Division|$O(k^2)$|
|Reduction mod $n$ (a division)|$O(k^2)$|

**The exponentiation problem**
Encryption and decryption both compute $x^e \bmod n$, the exponent can itself be about $k$ bits, so its value is up to about $2^k$.

Computing it as $e$ repeated multiplications would need roughly $k^2\cdot 2^k$ operations, which is $O(2^k)$.

That is as bad as brute-forcing the trap-door and is infeasible for $k\ge1024$, we therefore need a _smarter exponentiation algorithm_.

---
### Correctness of RSA
We want to show $D_{SK}(E_{PK}(x))=x$, to do so we are first going to prove **Euler's theorem**, which RSA correctness relies on.

**Euler’s theorem**: if $\gcd(a,n)=1$, then $a^{\phi(n)}\equiv 1 \pmod n$.

**Lemma 1**
If $x$ and $y$ are coprime to $n$, then $x\cdot y$ is coprime to $n$.

_Proof idea_
Every divisor of $xy$ is a product of divisors of $x$ and/or $y$, so a common divisor of $xy$ and $n$ greater than 1 would force $\gcd(x,n)>1$ or $\gcd(y,n)>1$, a contradiction.

_Example_
$x=7$, $y=3$, $n=55$, then $\gcd(21,55)=1$.

**Lemma 2**
If $x$ is coprime to $n$, then $x \bmod n$ is coprime to $n$.

_Proof idea_
Write $x\bmod n = x-kn$, suppose $d$ divides both $x\bmod n$ and $n$. Then $\frac{x \bmod n}{d}=\frac{x}{d}-k\frac{n}{d}$ is an integer, so $d$ also divides $x$. But $x$ and $n$ are coprime, so $d=1$.
- _Example:_ $x=57$, $n=55$. Then $57\bmod 55=2$ and $\gcd(2,55)=1$.

**Lemma 3**
If $a x\equiv a y \pmod n$ and $\gcd(a,n)=1$, then $x\equiv y \pmod n$.

_Proof idea_
$ax-ay=wn$ for some integer $w$, so $a(x-y)=wn$. Since $\gcd(a,n)=1$, $a$ must divide $w$, hence $x-y=tn$ for some integer $t$, i.e. $x\equiv y \pmod n$.

In words: we can "divide" both sides by $a$ modulo $n$, but only if $a$ is coprime to $n$.

>[!Example]
>**Counterexample when $\gcd(a,n)\neq1$**: $a=3$, $n=6$ (gcd is 3).
>Take $x=1$, $y=3$, then $3\cdot1\bmod6=3=3\cdot3\bmod6$, but $1\not\equiv3 \pmod 6$
>
>**Example when $\gcd(a,n)=1$**: $a=5$, $n=6$, $x=1$, $y=7$.
>Then $5\bmod 6=35\bmod 6=5$ and $1\equiv7\pmod6$, as the lemma predicts.


#### Proof of Euler's theorem
Let $S=(s_1,\dots,s_{\phi(n)})$ be the numbers less than $n$ that are coprime to $n$, then let:
$$R=(a s_1 \bmod n,\ \dots,\ a s_{\phi(n)} \bmod n)$$
**Step 1: $R\subseteq S$**
Each $s_i$ is coprime to $n$ and so is $a$, by Lemma 1, $a s_i$ is coprime to $n$. by Lemma 2, $a s_i \bmod n$ is also coprime to $n$, and it is less than $n$, so every element of $R$ is coprime to $n$ and below $n$, and therefore belongs to $S$.

**Step 2: the elements of $R$ are distinct**
Suppose $a s_i\equiv a s_j \pmod n$, by Lemma 3, $s_i\equiv s_j \pmod n$, which contradicts the $s_i$ being distinct numbers below $n$, so $R$ has $\phi(n)$ different elements, all inside $S$, which has $\phi(n)$ elements, hence $R=S$ as sets (multiplication by $a$ just permutes $S$).

**Step 3: multiply everything**
Since $R=S$, the two products are equal:
$$\prod_{i=1}^{\phi(n)} s_i \;\equiv\; \prod_{i=1}^{\phi(n)} a s_i \;=\; a^{\phi(n)}\prod_{i=1}^{\phi(n)} s_i \pmod n$$
The factor $a$ comes out of the product because $a s_i \bmod n = a s_i-k_i n$, and the terms $k_i n$ vanish when we reduce mod $n$.

**Step 4: cancel**
Each $s_i$ is coprime to $n$, applying Lemma 3 repeatedly (dividing by $s_1$, then $s_2$, and so on) gives:
$$1\equiv a^{\phi(n)} \pmod n$$

>[!Example]
>- **Not coprime**: $n=6$, $a=3$. Then $\phi(6)=2$ and $3^2\bmod 6=3\neq1$, the theorem needs $\gcd(a,n)=1$
>- **Coprime**: $n=6$, $a=5$. Then $5^2=25\equiv1 \pmod 6$

> [!example] RSA exercise: breaking a weak key
>Given $PK=(b,n)=(141,391)$, and the received ciphertext $y=306$.
>
> **Find the private key**
> - Factor $n$: $391=17\cdot23$
> - $\phi(391)=16\cdot22=352$
> - Solve $141\,a\equiv1 \pmod{352}$ with the extended Euclidean algorithm, this gives $a=5$, since $141\cdot5=705=2\cdot352+1$
> - $SK=(5,391)$
>
> **Decipher $y=306$**
> $$x = 306^{5}\bmod 391 = 17$$
>
> Check: $17^{141}\bmod 391=306$, this confirms the result.
>
> **Why is this not secure?**
> RSA's security depends on factoring $n$ being infeasible.
> Here $n=391$ is tiny and can be factored by hand, real RSA uses moduli of at least 1024 bits (now 2048 or more), where factoring is infeasible.


---
### Correctness of RSA
We want to show $D_{SK}(E_{PK}(x))=x$ for every $x<n$.

Since $ab\equiv1 \pmod{\phi(n)}$, we have $ab=k\,\phi(n)+1$ for some integer $k$, then:
$$D_{SK}(E_{PK}(x)) = (x^b \bmod n)^a \bmod n = x^{ab}\bmod n = \big(x^{\phi(n)}\big)^k\cdot x \bmod n$$

We must show this equals $x$, there are two cases

**Case 1: $\gcd(x,n)=1$**  
Euler's theorem gives $x^{\phi(n)}\equiv1 \pmod n$, hence $(x^{\phi(n)})^k\equiv1$ and the expression equals $x$.

**Case 2: $\gcd(x,n)>1$.** 
Since $x<n=pq$, the gcd is either $p$ or $q$, assume it is $p$ (the other case is identical). 

Then:
1. $x=j\cdot p$ for some $j$, and $\gcd(x,q)=1$ (because $x<n$ and $x$ is not a multiple of $q$)
2. By Euler’s theorem mod $q$: $x^{\phi(q)}\equiv1 \pmod q$
3. Since $\phi(n)=\phi(p)\phi(q)$, we get $x^{\phi(n)}=(x^{\phi(q)})^{\phi(p)}\equiv1 \pmod q$
4. Therefore $(x^{\phi(n)})^k\equiv1 \pmod q$, i.e. $(x^{\phi(n)})^k=wq+1$ for some integer $w$
5. Multiply by $x=jp$:
$$(x^{\phi(n)})^k\, x = (wq+1)\,jp = w\,j\,(pq)+jp = w\,j\,n + x \equiv x \pmod n$$

So in both cases $D_{SK}(E_{PK}(x))=x$, and **RSA is correct**.

**Numerical check**:
$p=3$, $q=11$, $PK=(3,33)$, $SK=(7,33)$, $x=2$.
Then $x^{ab}=2^{21}=2097152\equiv 2 \pmod{33}$.

### Efficient exponentiation
Encryption and decryption both compute $x^e \bmod n$, with $e$ as large as $n$ ($k$ bits, so $e\approx 2^k$).

Doing $e$ multiplications would cost about $k^2\cdot 2^k$ operations, which is $O(2^k)$, this is as bad as brute-forcing the trap-door and is infeasible for $k\ge1024$.

#### Square-and-multiply
Squaring repeatedly is much cheaper than multiplying repeatedly, for example, $x^8=((x^2)^2)^2$ takes only 3 multiplications instead of 7.

For exponents that are not powers of 2:
- If the exponent is **even**, halve it and square
- If it is **odd**, pull out one factor of $x$ (one extra multiplication), then continue
>Example: $x^{10}=(x^5)^2=((x^2)^2\cdot x)^2$.

Halving the exponent corresponds to reading its binary digits.
Start from the **most significant bit**, then at each step **square** the running result, and **multiply by $x$ only if the bit is 1**.

```python
def squareAndMultiply(x, e):
    r = 1
    b = bin(e)[2:]          # binary representation of e, removes the 0b
    for bit in b:           # for all bits of the exponent
        r = r * r           # we always square
        if bit == '1':
            r = r * x       # we multiply only if the bit is 1
    return r
```


**Example $2^{10}$** ($10=1010_2$):

|bit|square|multiply|$r$|
|---|---|---|---|
|1|$1\cdot1=1$|$\cdot2$|2|
|0|$2^2$|none|4|
|1|$4^2=16$|$\cdot2$|32|
|0|$32^2$|none|1024|

**Example $2^{13}$** ($13=1101_2$):

| bit | square | multiply | $r$  |
| --- | ------ | -------- | ---- |
| 1   | 1      | $\cdot2$ | 2    |
| 1   | 4      | $\cdot2$ | 8    |
| 0   | 64     | none     | 64   |
| 1   | 4096   | $\cdot2$ | 8192 |

**Complexity**
- There are $k$ iterations (one per bit of the exponent)
- Each iteration does at most two multiplications (plus a reduction mod $n$), each $O(k^2)$, in total: $O(k\cdot k^2)=O(k^3)$, which is _polynomial_
>For $k=1024$ this is about $10^9$ steps, which is efficient on modern machines.

