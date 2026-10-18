The **Advanced Encryption Standard (AES)** cipher is the composition of simple operations and contains a _non-linear component_ to avoid known-plaintexts attacks.

The composed operations gives a _non-idempotent cipher_ that is iterated for a fixed number of rounds.

AES works on the **Galois field** with $2^8$ elements noted $GF(2^8)$, intuitively, it is the set of all 8-bit digits with sum and multiplications performed by interpreting the bits as binary coefficients of polynomials.

>[!Example]
>$11010011\rightarrow x^7+x^6+x^4+x+1$
>$00111010\rightarrow x^5+x^4+x^3+x$

The **sum** of is just a _bit-wise XOR_ of the binary numbers.

>[!Example]
>$$11010011\oplus 00111010 = 11101001 = x^7+x^6+x^5+x^3+1$$

The **product** is done by multiplying the polynomials, then keeping only the coefficients that appear once, and **dividing** by the _irreducible polynomial_ (cannot be written as the product of two other polynomials), which in the case of AES it is:
$$\text{Irreducible polynomial }=x^8+x^4+x^3+x+1$$
and finally we take the **remainder**.
>The answer can be _checked_ asserting that: dividend = (quotient * divisor) + remainder.

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
>Then take the **remainder**, which gives $11000101$, this corresponds to $x^7+x^6+x^2+1$.

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

Now we focus on each one of them.

**AddRoundKey**
The round key is XORed with the state, byte by byte, and since it is its own inverse, the decryption uses the same operation.
![[AES AddRoundKey.png|279]]
**SubBytes**
Each byte goes through the fixed _S-box_, a $16\times16$ lookup table, the first hex digit picks the row and the second picks the column.

The S-box is built in two steps:
1. Take the _multiplicative inverse_ of the byte in $GF(2^8)$, this gives the non-linearity
2. Apply an _affine transformation_ to the bits $b_7...b_0$. This complicates algebraic attacks.
$$b_i = b_i \oplus b_{(i+4)\bmod 8}\oplus b_{(i+5)\bmod 8}\oplus b_{(i+6)\bmod 8}\oplus b_{(i+7)\bmod 8}\oplus c_i,\quad c = 01100011$$

The same transformation can be written as a matrix product plus the constant vector $c$.

![[AES SubBytes.png|374]]

**ShiftRows**
Row $r$ ($r=0..3$) is rotated _left by $r$ positions_ (circular).  
$$\begin{bmatrix}b_1&b_5&b_9&b_{13}\\b_2&b_6&b_{10}&b_{14}\\b_3&b_7&b_{11}&b_{15}\\b_4&b_8&b_{12}&b_{16}\end{bmatrix}\Rightarrow\begin{bmatrix}b_1&b_5&b_9&b_{13}\\b_6&b_{10}&b_{14}&b_2\\b_{11}&b_{15}&b_3&b_7\\b_{16}&b_4&b_8&b_{12}\end{bmatrix}$$
![[AES ShiftRow.png|406]]
**MixColumns**
Each column is multiplied (in $GF(2^8)$, with $\oplus$ as the sum) by a fixed matrix:  
$$\begin{bmatrix}2&3&1&1\\1&2&3&1\\1&1&2&3\\3&1&1&2\end{bmatrix}$$
For example, the first byte of each column is $2c_0\oplus3c_1\oplus c_2\oplus c_3$.

#### Key expansion
Keys are arrays of **4-byte words**, so a 128-bit key is 4 words.

The key is expanded into $4\cdot(N_r+1)$ words, which gives 4 words (one 128-bit round key) for each round plus the initial one.
>$N_r$ is 10, 12 or 14 for 128, 192 and 256-bit keys.

#### Complete pipeline
**Encryption**
```python
AddRoundKey(state, w[0,3])

for round in range(1, Nr):
    SubBytes(state)
    ShiftRows(state)
    MixColumns(state)
    AddRoundKey(state, w[round*4, round*4+3])
    
SubBytes(state)
ShiftRows(state)
AddRoundKey(state, w[Nr*4, Nr*4+3]) # last round: no MixColumns
```

**Decryption**
```python
AddRoundKey(state, dw[Nr*4, Nr*4+3])

for round in range(Nr-1, 0, -1):
    InvSubBytes(state)
    InvShiftRows(state)
    InvMixColumns(state)
    AddRoundKey(state, dw[round*4, round*4+3])
    
InvSubBytes(state)
InvShiftRows(state)
AddRoundKey(state, dw[0, 3])
```

Decryption applies the inverse operations in reverse order:
- _AddRoundKey_ is unchanged, since XOR is its own inverse
- _InvShiftRows_ shifts the rows to the right
- _InvSubBytes_ uses the inverse S-box table.
- _InvMixColumns_ multiplies by  
$$\begin{bmatrix}0e&0b&0d&09\\09&0e&0b&0d\\0d&09&0e&0b\\0b&0d&09&0e\end{bmatrix}$$

>[!Example]
>**Key**: "Thats my Kung Fu", **plaintext**: "Two One Nine Two".
>
>1. **ASCII -> hex**
>    - Plaintext: `54 77 6F 20 4F 6E 65 20 4E 69 6E 65 20 54 77 6F`
>    - Key: `54 68 61 74 73 20 6D 79 20 4B 75 6E 67 20 46 75`
>    - Both are written into matrices by columns.
>2. **AddRoundKey** (e.g. $69\oplus4B=22$):  
  >  `00 3C 6E 47 / 1F 4E 22 74 / 0E 08 1B 31 / 54 59 0B 1A`
>3. **SubBytes** (e.g. $6E$ → row 6, column E → $9F$):  
 >   `63 EB 9F A0 / C0 2F 93 92 / AB 30 AF C7 / 20 CB 2B A2`
>4. **ShiftRows**:  
 >   `63 EB 9F A0 / 2F 93 92 C0 / AF C7 AB 30 / A2 20 CB 2B`
>5. **MixColumns**:  
 >   `BA 84 E8 1B / 75 A4 8D 40 / F4 8D 06 7D / 7A 32 0E 5D`
>
> For example, $BA=(02\cdot63)\oplus(03\cdot2F)\oplus(01\cdot AF)\oplus(01\cdot A2)=11000110\oplus01110001\oplus10101111\oplus10100010=10111010$.
> 
>6. **AddRoundKey** with round key 1 (`E2 91 B1 D6 / 32 12 59 79 / FC 91 E4 A2 / F1 88 E6 93`) gives the _output of round 1_:  
>    `58 15 59 CD / 47 B6 D4 39 / 08 1C E2 DF / 8B BA E8 CE`

