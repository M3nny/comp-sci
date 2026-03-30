We want to store a set $S$ of $m$ integers from the universe $\{0,...,n-1\}$ using close to the IT lower bound of $\log\binom{n}{m}$ bits, while still supporting fast queries.

The **Elias-Fano (EF)** data structure achieves:
- **Space**: $\log\binom{n}{m}+O(m)$ bits
- **Access**: $O(1)$
- **Membership, predecessor and successor**: $O(\log m)$

Compared to [[03 - Zero-order bitvectors#Zero-order compressed bitvectors|RRR]], the EF data structure uses $O(m)$ extra bits instead of $o(n)$, which makes it **better for sparse or dense sets** where $o(n)$ would dominate.
The trade-off is **slower queries** ($O(\log m)$ instead of $O(1)$).

### The core idea
Each integer in $S$ can be written in binary using $\log n$ bits.
The idea is to **split every integer** in two parts:
- A _prefix_ of $\log n$ bits
- A _suffix_ of $\log(n)-\log(m)=\log(n/m)$ bits

Let's for example consider$S=\{0,5,8,12,14,17,20,31\}$, that has $n=32$ and $m=8$:
- $\log n=5$
- $\log(n/m)=2$

$$
\begin{array}{c|c|c}
x \in S & \text{prefix of } x_2 & EF_1 = \text{suffix of } x_2 \\
\hline
0 & 000 & 00 \\
5 & 001 & 01 \\
8 & 010 & 00 \\
12 & 011 & 00 \\
14 & 011 & 10 \\
17 & 100 & 01 \\
20 & 101 & 00 \\
31 & 111 & 11 \\
\end{array}
$$

The **prefixes**, being the top bits of a sorted list, are **non-decreasing**, and that structure can be exploited for compression.

The **suffixes** are stored [[03 - Zero-order bitvectors#Bit-packing|bit-packed]] in a plain array, and considering that there are $m$ elements and each suffix occupies $\log(n/m)$ bits, this takes exactly $m\log(n/m)$ bits of space, and access to the $i$-th suffix is $O(1)$ as we've seen.

The **prefixes** are non-decreasing numbers in $[0,m)$, instead of storing them directly, the idea is to:

1. Compute the **differences** between consecutive prefixes
2. Encode each difference in **unary**, that is, write as many $0$s as the represented decimal number, followed by a $1$
$$
\begin{array}{c|c|c}
x \in S & \text{prefix of } x_2 & EF_1 = \text{suffix of } x_2 \\
\hline
0 & 0\to 1 & 00 \\
5 & 1\to 01 & 01 \\
8 & 1\to 01 & 00 \\
12 & 1\to 01 & 00 \\
14 & 0\to 1 & 10 \\
17 & 1\to 01 & 01 \\
20 & 1\to 01 & 00 \\
31 & 2\to 001 & 11 \\
\end{array}
$$
3. Concatenate all the unary codes

The **Elias-Fano data structure is given by the pair** $(EF_1, EF_2)$:
- $EF_1=00\space01\space00\space00\space10\space01\space00\space11$
- $EF_2=1\space01\space01\space01\space1\space01\space01\space001$
$$
\begin{array}{c|c|c|c}
x \in S & \text{prefix of } (x)_2 & EF_2 = \text{difference } \delta_i \text{ in unary} & EF_1 = \text{suffix of } (x)_2 \\
\hline
0 & 000 & 1 & 00 \\
5 & 001 & 01 & 01 \\
8 & 010 & 01 & 00 \\
12 & 011 & 01 & 00 \\
14 & 011 & 1 & 10 \\
17 & 100 & 01 & 01 \\
20 & 101 & 01 & 00 \\
31 & 111 & 001 & 11 \\
\end{array}
$$

There are $m$ **ones** (one per integer in $S$) and **the number of zeros equals the sum of all differences**, which **also equals to the largest prefix** (that is $\leq m-1$).

Hence, $EF_2$ occupies $o(2m)$ bits, so $RRR(EF_2)\leq2m+o(m)$ bits.

We conclude that the Elias-Fano data structure uses in total at most:
$$m\log(n/m)+2m+o(m)=\log\binom{n}{m}+O(m)$$
>$EF_1$ bit-packed for $O(1)$ access, $EF_2$ unary stored with RRR for $O(1)$ rank/select.

### Queries
**Access** involves retrieving the $i$-th integer:
1. Since $EF_1$ is fixed length, just jump to position $i$ directly, the $4$th suffix (0-indexed) is $10$
2. Get the prefix from $EF_2$, which is given by the number of $0$s before the $i$-th $1$ in $EF_2$, that is:
$$\text{prefix}=EF_2.rank_0(EF_2.select_1(4))=3$$
and since both $rank$ and $select$ are $O(1)$ on RRR, this operation is $O(1)$ overall

3. Concatenate prefix + suffix: $011+10=01110=14$

Since all $m$ integers can be accessed in $O(1)$ and are stored in sorted order, we can use [[Dizionari#Search|binary search]] over them in $O(\log m)$ steps in order to compute the membership, predecessor and successor queries.

>[!Tip] Elias-Fano in practice
>The Elias-Fano data structure is one of the most successful "theoretical-to practical" stories in the field of compressed data structures.
>
>Its the gold standard for representing the [[01 - Boolean model#Inverted index|inverted lists]] in modern, high performance search engines.

