RSA needs two big primes, the oldest algorithm for finding primes is the **Sieve of Eratosthenes**, which finds all primes $\le N$, and it works as follows:
1. List the numbers $2,\dots,N$
2. Take the smallest surviving number $p$ and remove all its multiples $2p,3p,\dots$
3. Repeat with the next surviving number

The numbers that survive are prime, because they are not a multiple of any smaller number.

>[!Example]
>$N=10$: $\{2,\dots,10\}\to$ remove multiples of 2 $\to\{3,5,7,9\}\to$ remove multiples of 3 $\to\{5,7\}$.
>
>Primes: $\{2,3,5,7\}$.

**Optimizations**
- Start removing multiples at $p^2$, because any $x\cdot p$ with $x<p$ was already removed when processing $x$
- Stop when $p>\sqrt N$

>[!Example]
>**Sieve(15)**
>- $N_s=3$
>- After $p=2$: $\{2,3,5,7,9,11,13,15\}$
>- After $p=3$ (removing 9, 12, 15): $\{2,3,5,7,11,13\}$
>
>**Sieve(22)**
>- $N_s=4$
>- After $p=2$: $\{2,3,5,7,9,11,13,15,17,19,21\}$
>- After $p=3$ (removing 9, 15, 21): $\{2,3,5,7,11,13,17,19\}$
>- The step $p=4$ is skipped because 4 is no longer in the sieve
>
>**Sieve(18)**
>- $N_s=4$
>- Same process gives $\{2,3,5,7,11,13,17\}$
>
>**Sieve(17)**
>- $N_s=4$
>- After $p=2$: $\{2,3,5,7,9,11,13,15,17\}$
>- After $p=3$: $\{2,3,5,7,11,13,17\}$
>- Result: $\{2,3,5,7,11,13,17\}$

The sieve is not used for RSA since it needs at least $N$ steps, for a 3072-bit prime, $N\approx 2^{3072}$, which is **impossible**.

Instead, _RSA picks random numbers and tests whether each is prime_ with a probabilistic primality test.

### Primality testing
**Miller-Rabin** is one of the most famous probabilistic primality tests.

It is a **NO-biased Monte Carlo** algorithm meaning that:
- Answer _false_ (composite): always correct
- Answer _true_ (prime): can be wrong, but the error probability is at most $\epsilon=\tfrac14$


Running it $r$ times (with independent random $a$) gives error $\le(\tfrac14)^r$, which falls exponentially, for $r=128$ the error is below $4^{-128}=2^{-256}$, which is negligible.
>Its complexity is $O(\log^3 n)$.


```python
def Prime(n):
    m = n-1
    k = 0
    while (m & 1 == 0):         # while m is even
        m = m >> 1
        k += 1                  # so that n-1 = 2^k * m, with m odd
    a = random.randrange(2, n)  # random a with 1 < a < n
    b = squareAndMultiply(a, m, n)   # b = a^m mod n
    if b == 1:
        return True
    for i in range(k):
        if b == n-1:
            return True
        b = b*b % n
    return False
```

In words:
- Write $n-1=2^k m$ with $m$ odd (the largest possible $k$)
- Pick a random $a$ and compute $b=a^m\bmod n$ (use square-and-multiply here otherwise large inputs are impossible)
- If $b=1$, answer `true`
- Otherwise square repeatedly, if $b$ ever equals $n-1$, answer `true`, if it never does, answer `false`

>[!Example]-
>
> **Prime(7)**
>
> $6=2^1\cdot3$, so $k=1$ and $m=3$.
>
> Choosing $a=2$:
>
> $b=2^3\bmod7=1$
>
> Since $b=1$, the test returns _true_.
>
> ---
>
> **Prime(9)**
>
> $8=2^3\cdot1$, so $k=3$ and $m=1$.
>
> Choosing $a=2$:
>
> $b=2^1\bmod9=2\neq1$
>
> The loop successively gives:
>
> $2\to4\to7\to4$
>
> It never reaches $n-1=8$, so the test returns _False_.
>
> This is correct because $9=3^2$.
>
> ---
>
> **Prime(5)**
>
> $4=2^2\cdot1$, so $k=2$ and $m=1$.
>
> Choosing $a=2$:
>
> $b=2^1\bmod5=2$
>
> At $i=0$, $b\neq n-1$, so we square:
>
> $b=2^2\bmod5=4$
>
> At $i=1$, $b=4=n-1$, so the test returns _True_.
>
> ---
>
> **Prime(10)**
>
> $9=2^0\cdot9$, so $k=0$ and $m=9$.
>
> Since $k=0$, the loop never runs, we only calculate:
>
> $b=a^9\bmod10$
>
> For every allowed base $a$, this is never equal to $1$, therefore, the test always returns _false_.
>
> ---
>
> **Prime(15)**
>
> $14=2^1\cdot7$, so $k=1$ and $m=7$.
>
> Choosing $a=2$:
>
> $b=2^7\bmod15=8\neq1$
>
> The loop squares $b$:
>
> $b=8^2\bmod15=4$
>
> Since $b\neq n-1=14$, the test returns _false_.
>
> This is correct because $15=3\cdot5$.
>
> **False positive**: only $a=14$ produces a false _true_, since:
>
> $14^7\equiv-1\equiv14\pmod{15}$
>
> Therefore, the probability of an incorrect result in a single run is:
>
> $P(\text{error})=\frac{1}{13}<\frac14$

**Proof that false answers are always correct**
Assume the algorithm returns false but $n$ is prime, then the algorithm passed through every branch, so:
- $a^m\not\equiv1 \pmod n$
- $a^{2^i m}\not\equiv n-1 \pmod n$ for $i=0,\dots,k-1$

Since $n$ is prime and $a<n$, Fermat/Euler gives $a^{n-1}=a^{2^k m}\equiv1\pmod n$.
So the chain of values is:
$$a^{m},\ a^{2m},\ a^{2^2m},\ \dots,\ a^{2^{k-1}m},\ a^{2^km}\equiv 1$$
where each value is the square of the previous one.

_Key fact_: if $n$ is prime, the only square roots of 1 mod $n$ are $1$ and $n-1$.** If $r^2\equiv1$, then $(r-1)(r+1)=zn$, since $n$ is prime it divides $r-1$ or $r+1$, so $r\equiv1$ or $r\equiv-1$.

Now let's argue backwards:
- The last value is 1, so $a^{2^{k-1}m}$ is a square root of 1, it is $\ne n-1$ by assumption, so it equals 1
- Repeating this for each earlier value, we get $a^m\equiv1$, which contradicts the assumption

<u>So a prime</u> $n$ <u>can never be answered false</u>.

**Why a composite $n$ may fool the test**
For composite $n$ there can be extra square roots of 1.
For example, $5^2=25\equiv1 \pmod 8$, so 5 is a square root of 1 mod 8 that is neither 1 nor 7.

### Generating RSA primes
The method is to generate random numbers of the needed size and test each with Miller-Rabin.

**How many attempts?**
About 1 in $\ln n$ numbers below $n$ is prime, if we consider a 512-bit prime (used for a 1024-bit modulus):
$$\ln n=\log_2 n\cdot\ln 2\approx 512\cdot0.7\approx 358$$
So on average about 358 attempts for a 512-bit prime.

**How many Miller-Rabin iterations?**
The $\tfrac14$ bound is pessimistic, a later paper showed the test is much more accurate.
>NIST suggests 7, 4 and 3 iterations for 512, 1024 and 1536-bit primes, giving an error of at most $2^{-100}$.

Taking in consideration **openssl**, if we use `openssl genrsa 1024` it prints:
- Dots (`.`) for candidate primes being tested
- A `+` for each successful Miller-Rabin iteration.
- `e is 65537 (0x10001)`, the fixed public exponent
- The private key in base64 (PEM) between `-----BEGIN RSA PRIVATE KEY-----` and `-----END RSA PRIVATE KEY-----`

```bash
openssl genrsa -verbose 1024

Generating RSA key with 1024 bits
..................................................++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
.........................................++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
e is 65537 (0x010001)
-----BEGIN PRIVATE KEY-----
MIICeAIBADANBgkqhkiG9w0BAQEFAASCAmIwggJeAgEAAoGBAL5qOvgUztCwyqDq
FDRtVA5/De8mxvL5IMjixa0IvmyQE1f8jrIEOY/1y7f9PQF+VfgqEhr1356seseN
E3wZlp9OzFaFAH7w+3xp1//8tTqt1EjPHZHwxwRduw7s/PdJQRaSSmx0zpK0fXeY
uvJpkeMidQHjL+sASR2DxxUliwOFAgMBAAECgYBvQjjkfZv+Ol6bOUrG+16S/dAR
fbHfhIuQdViVazeAzYpP7eUexPMxV6hKADDmL4Bh+YsMr7+SwisXcCoDaBwmRTXi
bh+ikDhqZlAzo83Y79NlWHcHmIh/MA6rz1bScf9WOD5xd/8Rpd/D+hN26mso000b
BuUMYyyfzqkWRUCufQJBAOXxf8jhTB5QwX0tMUEjF+9juBKtiw278hNTwufetMdR
tQSrJ/P4jGG2tCdGbuCAhxbm/fBaHZmGogvGJ+pYyVsCQQDT/goOzGjw/CBNVtjk
8WBML5Anx+eaRe/1O9mgukM5Xh8cYdadN9wUUB0kDngyrFmMZqFSBs29qWmd+8XV
IByfAkEAtwpT50t49VThgUydPbW60uQ1XiDpZShsXfg6WatNirC/ARVh+3KqBQqU
RANsNaf6YT/FezOxBkpG6kp18bV1qwJBAJWBJIC5Qg0qEnHYnNAhNqOkK4sSnVCc
oBUYJ2wF0GEF8vTmPx/ThD9DHLoQBk7eY6zzuDOMHs7ySk0jgarDocsCQQCTEtRl
xu/U3XZEW3CQB2gSVznaBmnBqGCuS8K3YL02fgverSuH3qAy2MarNrZKWTnNMoLa
NSVtoMzdit5H7V9v
-----END PRIVATE KEY-----
```

