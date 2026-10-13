The **Advanced Encryption Standard (AES)** cipher is the composition of simple operations and contains a _non-linear component_ to avoid known-plaintexts attacks.

The composed operations give e _non-idempotent cipher_ that is iterated for a fixed number of rounds.

AES works on the **Galois field** with $2^8$ elements noted $GF(2^8)$, intuitively, it is the set of all 8-bit digits with sum and multiplications performed by interpreting the bits as binary coefficients of polynomials.

>[!Example]
>$11010011\rightarrow x^7+x^6+x^4+x+1$
>$00111010\rightarrow x^5+x^4+x^3+x$

The **sum** of is just a _bit-wise XOR_ of the binary numbers.

>[!Example]
>$$11010011\oplus 00111010 = 11101001 = x^7+x^6+x^5+x^3+1$$

The **product** is done by multiplying the polynomials, then keeping only the coefficients that appear once, and **dividing** by the _irreducible polynomial_ (cannot be written as the product of two other polynomials), which in the case of AES it is:
$$\text{Irreducible polynomial }=x^8+x^4+x^3+x+1$$
and finally we take the **reminder**.
>The answer can be _checked_ asserting that: dividend = (quotient * divisor) + reminder.

>[!Example]
>**Multiplication**
>
>$$
>\begin{aligned}
>&(x^{7} + x^{6} + x^{4} + x + 1) \times (x^{5} + x^{4} + x^{3} + x) \\
>&= x^{12} + x^{11} + x^{10} + x^{8} + x^{11} + x^{10} + x^{9} + x^{7} + x^{9} + x^{8} + x^{7} + x^{5} + x^{6} + x^{5} + x^{4} + x^{2} + x^{5} + x^{4} + x^{3} + x \\
>&= x^{12} + x^{6} + x^{5} + x^{3} + x^{2} + x
>\end{aligned}
>$$
>
>**Division** by the irreducible polynomial
>$$
>\begin{array}{r}
>1\ 0\ 0\ 0\ 0\ 0\ 1\ 1\ 0\ 1\ 1\ 1\ 0 \\
>\underline{1\ 0\ 0\ 0\ 1\ 1\ 0\ 1\ 1\phantom{0000}} \\
>1\ 1\ 1\ 0\ 1\ 1\ 1\ 1\ 0 \\
>\underline{1\ 0\ 0\ 0\ 1\ 1\ 0\ 1\ 1\phantom{0}} \\
>1\ 1\ 0\ 0\ 0\ 0\ 1\ 0\ 1
>\end{array}
>$$
>
>Then take the **reminder**, which gives $11000101$, this corresponds to $x^7+x^6+x^2+1$.

The **optimized multiplication** uses shifts and XORs:
1. _Initialize the result (`p`)_: start with a running total `p = 0`
- _Check the multiplier (`b`)_: look at the last (rightmost) bit of `b` (`b & 1`). If it is `1`, add the current value of `a` to our total `p` using an **XOR** operation (`p = p ^ a`). If it's `0`, skip this addition
- _Shift `b`_: move `b` one bit to the right (`b >>= 1`) so we can inspect the next bit in the next loop
- _Check overflow for `a`_: check if the leftmost (most significant) bit of `a` is `1` (`a & 0x80`). Save this check as `hbit`
- _Shift `a`_: shift `a` one bit to the left (`a <<= 1`) to multiply it by $x$
- _Reduce `a` (if needed)_: if `a` overflowed (meaning `hbit` was true), XOR `a` with the reduction polynomial constant (e.g., `0x11b`) to keep it within the proper field size
- _Return_: after checking all bits, return the final result `p`


>[!Example]
>AES Multiplication of $(x^{4}+x^{3}+1) \times (x^{5}+1)$
>$$\begin{array}{lll} a & b & p \\ 11001 & 100001 & 0 \text{ XOR } 11001 \\ 110010 & 10000  \\ 1100100 & 1000 \\ 11001000 & 100  \\ 110010000 & 10 \end{array}$$
>$$\begin{aligned} &110010000 \text{ XOR } 100011011 = 010001011 \\ &0100010110 \text{ (with bit } 1\text{)} \\ &100010110 \text{ XOR } 100011011 = 000001101 \text{ (with bit } 1\text{)}
>\end{aligned}$$
>Then $1101 \text{ XOR } 11001 = 10100$, which corresponds to $x^{4}+x^{2}$.

### The AES cipher
AES uses a **symmetric key** which is the same for both encryption and decryption, and it operates on $4\times 4$ matrices of bytes, which in total occupy $128$ bits, which is the block size.

**Plaintext bytes** $b_1,...,b_{16}$ are copied in the matrix by columns following this scheme:
$$
\begin{bmatrix}
b_1 & b_5 & b_9 & b_{13} \\
b_2 & b_6 & b_{10} & b_{14} \\
b_3 & b_7 & b_{11} & b_{15} \\
b_4 & b_8 & b_{12} & b_{16}
\end{bmatrix}
$$
Cipher keys have **lengths** of 128 (10 rounds), 192 (12 rounds) and 256 (14 rounds) bits.

A **round** is composed of different operations, all of which are invertible:
- _AddRoundKey_: bitwise XOR the block with a round key
- _SubBytes_: apply a fixed non-linear substitution box (S-box) byte-by-byte using hexadecimal row and column lookup
- _ShiftRows_: cyclically shifting rows of the state matrix to the left by $0,1,2,3$ positions respectively
- _MixColumns_: multiply the columns of the matrix by a fixed polynomial matrix
