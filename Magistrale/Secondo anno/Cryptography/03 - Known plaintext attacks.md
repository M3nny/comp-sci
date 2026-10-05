### Cryptoanalysis
- **Ciphertext-only attack**: the attacker is assumed to have access only to a set of ciphertexts
- **Known-plaintext attack**: the attacker knows some pairs $(x',y'),(x'',y''),...$ of plaintexts/ciphertexts
- **Chosen-plaintext attack**: attack model for cryptoanalysis which presumes that the attacker can ask and obtain the ciphertexts for given plaintexts
- **Chosen-ciphertext attack**: attack model for cryptoanalysis where the cryptoanalyst can gather information by obtaining the descriptions (plaintexts) of chosen ciphertexts

### Attacking the Hill cipher
Assume that the attacker has two plaintext and ciphertext messages:
- $(5,9)\to(19,4)$
- $(2,5)\to(24,11)$
- $m=2$

The challenge is, given $y$, to find the relative $x$ or the $k$.
It is clear that if $X^{-1}$ exists, then we can obtain $X^{-1}Y\mod26=X^{-1}XK\mod26$, from which $K=X^{-1}\mod 26$.

The Hill cipher is a **linear transformation** of a plaintext block into a cipher block.
The above attack shows that this kind of transformation is easy to break if enough pairs of plaintexts and ciphertexts are known.

Modern ciphers, in fact, always contain a **non-linear component** to _prevent this kind of attacks_.

>[!Example]
>We have: $Y=XK\mod26$ with $X=\begin{bmatrix}x_1^1&\dotsi& x_m^1\\\dotsi&\dotsi&\dotsi\\x_1^m&\dotsi&x_m^m\end{bmatrix}$ and $Y=\begin{bmatrix}y_1^1&\dotsi& y_m^1\\\dotsi&\dotsi&\dotsi\\y_1^m&\dotsi&y_m^m\end{bmatrix}$
>
>
>$$\begin{bmatrix}19&4\\24&11\end{bmatrix}=\begin{bmatrix}5&9\\2&5\end{bmatrix}K\mod26$$
>
>We want to reconstruct $K$, if $X^{-1}$ exists, then $K=X^{-1}Y\mod26$.
>$$\begin{align}
>X^{-1}&=det^{-1}(X)\begin{bmatrix}5&-9\\-2&5\end{bmatrix}\bmod26=det^{-1}(X)\begin{bmatrix}5&17\\24&5\end{bmatrix}\bmod26\\\\
>
>det(X)&=(5\cdot5-2\cdot9)\\
>&=7\\\\
>
>det^{-1}(X)&\text{ is an }a: 7\cdot a=1\bmod26\\
>a&=15
>\end{align}
>$$
>
>From which we derive $X^{-1}$:
>$$\begin{align}
>X^{-1}&=det^{-1}(X)\begin{bmatrix}5&17\\24&5\end{bmatrix}\mod26\\
>&=15\begin{bmatrix}5&17\\24&5\end{bmatrix}\mod26\\
>&=\begin{bmatrix}75&255\\360&75\end{bmatrix}\mod26\\
>&=\begin{bmatrix}23&21\\22&23\end{bmatrix}
>\end{align}$$
>
>Then we find $K$:
>$$\begin{align}
>K&=X^{-1}Y\mod26\\
>&=\begin{bmatrix}23&21\\22&23\end{bmatrix}\begin{bmatrix}19&4\\24&11\end{bmatrix}\mod26\\
>&=\begin{bmatrix}941&323\\970&341\end{bmatrix}\mod26\\
>&=\begin{bmatrix}5&11\\8&3\end{bmatrix}
>\end{align}$$

In previous examples we had to computer the determinant inverse by guessing (e.g. solving $7\cdot a\equiv1\mod26$ by testing numbers), this works for small numbers, but computers can' rely on guessing, especially for large numbers.

#### Greatest common divisor
A number $c$ has a multiplicative inverse modulo $d$ iff $c$ and $d$ share no common factors other than $1$, in other words:
$$\gcd(c,d)=1$$
If $\gcd(c,d)\neq1$, the matrix is not invertible, and the key/ciphertext cannot be decrypted.

To compute this efficiently we can use the **Euclidean algorithm**:
```python
def Euclid(c, d):
	while d != 0:
		tmp = C % d
		c = d
		d = tmp
	return c
```

>[!Example]
>`Euclid(15, 5)`
>- `d = 5 != 0`
>- `tmp = 15 % 5` // 0
>- `c=d` // 5
>- `d = tmp` // 0
>- `return 5`

The **extended euclidean algorithm** takes it one step further, while computing GCD, it tracks two extra coefficients: $e$ and $f$.
When $\gcd(c,d)=1$, the algorithm directly outputs $e\mod d$ which is the modular inverse $\det^{-1}(X)$.

```python
def EuclidExt(c,d):
	d0 = d
	e = 1
	f = 0
	while d != 0:
		q = c//d # integer division
		tmp = c - q*d # this is c % d
		c = d
		d = tmp
		tmp = e - q*f # new computation for the inverse
		e = f
		f = tmp
	if c == 1:
		return e % d0 # if gcd is 1 we have that e is the inverse
```

>[!Example]
>`EuclidExt(5, 17)`
>```
>d0=d=17;e=1;f=0;
q = 0, tmp = 5, c = 17, d = 5 tmp = 1, e = 0, f = 1
q = 3, tmp = 2, c = 5, d = 2 tmp = -3, e = 1, f = -3
q = 2, tmp = 1, c = 2, d = 1 tmp = 7, e = -3, f = 7
q = 2, tmp = 0, c = 1, d = 0 tmp = -17, e = 7, f = -17
e % d0 = 7
>```

