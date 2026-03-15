A **bitvector** is a string of $0$s and $1$s of length $n$, we are going to define the following operations on them:
- **Access**: $B[i]$ returns the $i$-th bit
- **Rank**: $B.rank_0(i)$ counts how many times the $0$s appear in $B[1,...,i]$
- **Select**: $B.select_0(i)$ finds the position of the $i$-th occurrence of bit $0$

>[!Example]
>Let $B=0010100$
>- $B[3]=1$
>- $B.rank_0(5)=3$
>- $B.select_1(2)=5$

The **characteristic bitvector** of a set $S\subseteq [n]$ with $|S|=m$ is the bitvector $B(S)\in\mathscr{B}_{n,m}$ such that $B[x]=1$ iff $x\in S$, for example:
$$S=\{1,2,3,4,5,6,7,8,9\}\implies B(S)=001001101$$

In other words: we are interested in bitvectors because any **integer set** $S$ can be represented as a bitvector $B$ where $B[x]=1$ iff $x\in S$.
Under this representation, _membership_, _predecessor_ and _successor_ on **sets** reduce directly to _access_, _rank_ and _select_ on **bitvectors**.

We will also see how we can reduce the operations of _count_, _locate_ and _extract_ on **strings**, to the previously mentioned bitvector operations.

### Zero-order compressed bitvectors
Our goal is to prove the following **theorem**:
There exists a data structure over **any bitvector** $B\in\mathscr B_{n,m}$ using $\log\binom{n}{m}+o(n)\leq nH_0+o(n)$ bits of space, and <u>supporting constant-time access, rank, select queries</u>.

Equivalently:
There exists a data structure over **any subset of size $m$ of $[n]$** using $\log\binom{n}{m}+o(n)$ bits of space, and supporting <u>constant-time membership, predecessor, and successor queries</u>.

Note that the $o(n)$ **overhead** term **can be much larger** than $\log\binom{n}{m}$, so this is bad on _very sparse or very dense sets_.
For example storing $m=10^3$ IP addresses from a universe of $n=2^{32}$, the IT lower bound is tiny, but the $o(n)$ overhead dominates.

We will name this bitvector which is capable of doing these operations as the **RRR bitvector**, named after Raman, Raman, and Rao.

### Model of computation
Before talking about data structures, the computation model needs to be fixed, for sure we don't want to use the [[Macchina di Turing|Turing machine]].

We are going to use the **Word RAM model** which is a theoretical model of computation that resembles what our computers can do.

It uses **words of $w=\Theta(\log n)$ bits** each, where $n$ is the input size (e.g. most computers nowadays use $w=64$ bits per word).

All **standard bitwise operations** are executed in **constant-time** (e.g. AND, OR, shifts, add, multiply, ...).

### Bit-packing
Can we store a bitvector of $n$ bits while supporting **access** in $O(1)$ time?
Using an array of integers ($32$n bits) or an array of booleans ($8$n bits) is wasteful, the right approach is **bit-packing**: pack all $n$ bits tightly into $n/w$ integers of $w$ bits each.

>[!Example]
>Suppose $w=4$ and $n=20$, then:
>- $B=1001\space0110\space1111\space0001\space1000$ 
>- $V=[9,6,15,1,8]$
>
>Space: $n+\Theta(w)=n+\Theta(\log n)$ bits.
>
>The term $\Theta(w)$ is necessary because we also need to store the address of $V$ in memory and its length, but this occupies a negligible size w.r.t the size $n$ of the bitvector.

In general $w$ does not divide $n$, so the last block could contain less than $w$ bits, in this case we pad $B$ with $0$s until its length is a multiple of $w$.

**Theorem** (packed bitvector):
$B\in\{0,1\}^n$ can be stored in $n+\Theta(\log n)$ bits so that any subsequence $B[i,...,i+\ell-1]$ of length $l\leq \log n$ can be extracted (and packed in one word) in $O(1)$ time.

---
### Compressing the bitvector
Our next goal is to compress $B\in\{0,1\}^n$ in $nH_0+o(n)$ bits.

Let $B$ be our bitvector, we choose a **block size** $b=\left\lceil\frac{\log_2(n)}{2}\right\rceil=\Theta(n)$, and divide $B$ in blocks of $b$ bits each.
We call these blocks $B-1,...,B_{n/b}$ (again, we assume for simplicity that $b$ divides $n$).

Then we define the **class of a block** with the number of $1$s in the block.

We are going to store in a **table** $T$ all possible bitvectors of length $b$: $T[k]=\mathscr B_{b,k}$, then we'll encode each block of $B$ as a variable-length pointer inside $T$.


Let take as an example $B=010101001110000011111$.
With $n=21$ we get $b=b=\left\lceil\frac{\log_2(21)}{2}\right\rceil=3$ hence we have $21/3=7$ blocks.
$$\begin{array}{ccccccc}
B_1&B_2&B_3&B_4&B_5&B_6&B_7\\
010&101&001&110&000&011&111
\end{array}$$
$$\begin{array}{ccccccc}
C_1&C_2&C_3&C_4&C_5&C_6&C_7\\
1&2&1&2&0&2&3
\end{array}$$
We need $\lceil\log_2(b+1)\rceil$ _bits to represent each integer of the array_ $C$ (we have to represent numbers that go from $0$ to $b$), then by substituting $b$, we get $O(\log\log n)$.

_In order to pack $C$ we need $n/b\cdot\log(b+1)$ bits_, which is:
$$\frac{n}{b}\cdot\log(b+1)=\frac{n}{\log^2n/2}\cdot O(\log\log n)=n\cdot\frac{\log\log n}{\log n}\implies 0\text{ as }n\to\infty\implies o(n)$$

Continuing the previous example, we build the lookup table $T$:

|                         |  0  |  1  |  2  |
| :---------------------: | :-: | :-: | :-: |
| $\mathscr B_{3,0}\to$ 0 | 000 |     |     |
| $\mathscr B_{3,1}\to$ 1 | 001 | 010 | 100 |
| $\mathscr B_{3,2}\to$ 2 | 011 | 101 | 110 |
| $\mathscr B_{3,3}\to$ 3 | 111 |     |     |

The **space taken by** $T$ considering that:
- It has $b+1$ rows
- $\leq2^b$ columns
- Each cell has $b$ bits
Is equal to:
$$O(b^2\cdot 2^b)=O((\log n)^2\cdot\sqrt n)=o(n)\text{ bits}$$

We define the **offset** of a block as the column in $T$ where that block appears:
$$\begin{array}{ccccccc}
O_1&O_2&O_3&O_4&O_5&O_6&O_7\\
1&1&0&2&0&0&0
\end{array}$$

Notice how $C$ contains row numbers in $T$, whilst $O$ contains column numbers in $T$, the third block ($001$) for example, has class $1$ and offset $0$, meaning that $T[1,0]=001$, hence this means that $C,O,T$ are a **lossless encoding of $B$**.

How many bits do we need to encode an offset of class (i.e. row) $k$?
- Row $2$ has $3$ nonempty columns, so we need enough bits to encode $3$ distinct values, then we need $2$ bits
- Row $0$ has $1$ nonempty column, so we need $0$ bits to encode $1$ value

The space taken by the offset of a class is equal to:
$$\log|\mathscr B_{b,k}|=\log\binom{b}{k}$$
so, by summing up the bit-sizes of every offset, we obtain that **the offset $O$ can be packed in**:
$$\sum_{j=1}^{n/b}\log_2\binom{b}{C[j]}\text{ bits}$$

**Theorem**:
Our variable -length encoding of $O_1,...,O_{n/b}$ uses $nH_0+o(n)$ bits.
$O_i$ is store using $\lceil\log_2\binom{b}{C_i}\rceil$ bits, and summing over all offsets, we obtain:
$$\begin{align}
\sum_{j=1}^{n/b}\left\lceil\log_2\binom{b}{C_i}\right\rceil&\leq\sum_{i=1}^{n/b}\left(\log_2\binom{b}{C_i}+1\right)\\
&=\sum_{i=1}^{n/b}\left(\log_2\binom{b}{C_i}\right)+n/b\\
&=\left(\log_2\prod_{i=1}^{n/b}\binom{b}{C_i}\right)+n/b
\end{align}$$

We use the fact that $\binom{x}{y}\cdot\binom{z}{k}\leq\binom{x+z}{y+k}$, then $\prod_{i=1}^{n/b}\binom{b}{C_i}\leq\binom{b+\dotsi b}{C_1+\dotsi C_{n/b}}=\binom{n}{m}$, where $m$ is the number of bits equal to $1$ in $B$.

And recalling that $\log_2\binom{n}{m}\leq nH_0$m we finally obtain that the number of bits is:
$$nH_0+n/b=nH_0+O(n/\log n)=nH_0+o(n)$$

Observe that in $O$ we concatenate **variable-length** codes, whilst the values in $C$ which are **fixed-length** are sufficient to reconstruct the lengths of codes in $O$, we conclude that $(n,C,T,O)$ is indeed an **invertible encoding** of $B$.

### Supporting access in constant-time
Given any block index $t$, we can look up $C[t]$ and $O[t]$, then retrieve $T[C[t]][O[t]]$ to get the full block back.

Array $C$ and table $T$ are stored using a **fixed-length encoding**, for each fo their entries, so easy to access in $O(1)$ time (by the bit-packing theorem).

Let's see how to access any $O[i]$, which is **variable-length** in $O(1)$ time using just $o(n)$ extra bits.

The offsets in $O$ are stored as a _flat bitstring with no separators_ (e.g. $encoded(O)=01100$), there is not way to know where $O[6]$ starts without knowing where all previous offsets end.

The naive fix is to store the starting positions of every offset, since there are $n/b$ offsets, and each position needs $\log_2 n$ bits, we need the following extra bits:
$$\frac{n}{b}\cdot\log n=\frac{n}{\log b}\cdot \log n=\Theta(n)$$
bu that's too much, since we only want it to occupy only $o(n)$ bits, for this reason we use a **2-level solution**.

**Level 1: macroblocks**
First, we group every $b$ consecutive blocks, together into a **macroblock**, and since $b=O(\log n)$, each macroblock contains $O(\log n)$ blocks.
The total _number of macroblocks_ is given by:
$$\frac{n/b}{b}=\frac{n}{b^2}=\frac{n}{\log^2n}\text{ bits}$$
then, for each macroblock, we store its **absolute starting position** in the encoded offset string, and since each position needs $O(\log n)$ bits, the **total space occupied** is:
$$\frac{n}{\log^2n}\cdot O(\log n)=O\left(\frac{n}{\log n}\right)=o(n)\text{ bits}$$

**Level 2: relative positions within a macroblock**
Each offset uses at most $\log \binom{b}{C_j}\leq b$ bits, so a full macroblock uses at most $b^2$ bits.
Therefore each relative position fits in $\lceil\log b^2\rceil=2\log b=O(\log\log n)$ bits.
Since there are $n/b$ relative positions in total, the occupied space is:
$$\frac{n}{b}\cdot O(\log\log n)=n\cdot \frac{\log\log n}{\log n}=o(n)\text{ bits}$$

$$\begin{array}{l|ccc|ccc|c}
 & O_1 & O_2 & O_3 & O_4 & O_5 & O_6 & O_7 \\ \hline
\text{encoded offsets} & 01 & 10 & 00 & 10 &  & 00 &  \\
\text{starting position of macroblock} & 1 &  &  & 7 &  &  & 11 \\
\text{relative starting position of offset inside macroblock} & 1 & 3 & 5 & 1 & 3 & 3 & 1
\end{array}$$

### Supporting rank in constant-time
The **rank** operation is solved with the same two-level sampling idea, plus a **3D precomputed rank table** $R$, where $R[class][offset][i]=rank_1(i)$ within that block.

Since $T$ already enumerates all possible blocks, $R$ can be built on top of $T$.
This table also fits in $o(n)$ bits.
It works as follows:
1. Look up the precomputed rank up to the start of $i$'s macroblock
2. Add the precomputed rank up to the start of $i$'s block within the macroblock
3. Add the rank within the block itself using $R$
>Every step is $O(1)$.

$$\begin{array}{l|ccc|ccc|c}
 & B_1 & B_2 & B_3 & B_4 & B_5 & B_6 & B_7 \\ \hline
\text{blocks} & 010 & 101 & 001 & 110 & 000 & 011 & 111 \\
\text{absolute rank before macroblock} & 0 &  &  & 4 &  &  & 8 \\
\text{relative rank inside macroblock} & 0 & 1 & 3 & 0 & 2 & 2 & 0
\end{array}$$

### Compressing multiple bitvectors
A final observation is that, the **compression is local**, each block is encoded independently of all others.

This means if you concatenate multiple bitvectors and compress the result, the total space is bounded by the sum of their individual entropies, plus small overhead terms.
>This locality property will be re-discussed for the FM-index.

