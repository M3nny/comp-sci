We know how to perform rank, select and access (RSA) queries efficiently on bitvectors, the problem is figuring out how to do this on general strings with larger alphabets.

A **wavelet tree** solves this by decomposing a general string into multiple smaller bitvectors.

It represents a **balanced binary tree** with a height of $O(\log\sigma)$, where $\sigma$ is the size of the alphabet.
It has **exactly $\sigma$ leaves**, one per character in the alphabet, and **inside every node we store a bitvector**.

### Building a wavelet tree
Let's see how it is built with an example using $S$=`FACE BAKE CAFE`.

**Step 1: Encode the alphabet**
Assign a binary code to each character in the alphabet using $\lceil\log\sigma\rceil=3$ bits.
![[WT encode alphabet.png|100]]

**Step 2: read vertically**
Stack the binary encodings of each character vertically.
![[WT stack encodings.png|200]]

**Step 3: build the root**
The root of the tree stores the top row of those bits, which is defined as level 1.
>The text is only shown for clarity, it is not being stored.

![[WT build root.png|200]]

**Step 4: split and repeat**
To build the next level, we look at the bits in the root.
Characters that had a $0$ in the first level go to the left branch, and characters that had a $1$ go to the right branch.
This logic gets repeated untile we reach the leaves, which represent the individual characters.
![[WT split.png|500]]

### WT Space
There are $n$ bits in each of the $\log\sigma$ levels, hence **in the nodes there are $n\log\sigma$ bits**.

But we also need to account for the **topology of the tree**, which considering that in a binary tree with $\sigma$ leaves there are $\sigma-1$ nodes, it results to have $2\sigma-1=O(\sigma)$ nodes, and each pointer used to locate them uses $\log n$ bits, hence the **topology size is $O(\sigma\log n)$ bits**.

The **space occupied by the leaves** is $\sigma\log \sigma$ bits, since there are $\sigma$ characters and each of them occupies at least $\log\sigma$ bits, it is also trivially true that $\sigma\log\sigma\leq\sigma\log n$.

Hence if we **store the bitvectors using RRR** we occupy a **total space of**:
$$\underbrace{n\log\sigma}_{\text{bitvectors}}+\underbrace{o(n\log\sigma)}_{\text{RRR overhead}}+\underbrace{O(\sigma\log n)}_{\text{topolgy + leaves}}\text{ bits}$$
if we assume for simplicity $\sigma=o(n/\log n)$, then the space is:
$$n\log\sigma+o(n\log\sigma)\text{ bits}$$

### Zero-order compression
We **claim** that using RRR on the bitvectors, **the space is actually $nH_0(S)+o(n\log \sigma)$ bits**.
This is because zero-order compression of the bitvectors "propagates" to **zero-order compression of the string**.

We prove this by induction on the height $h$ of the WT.
**Base case**: $h=1$
The string is a RRR bitvector, hence the claim is true since RRR achieves zero-order compression.

**Inductive step**:
the claim is true for height $h\geq1$ (strings $S_0,S_1$ over alphabets of size $\sigma\leq2^h$), let's prove it for $h+1$.

Let:
- $S\in\Sigma$ be the string of length $n$ represented by this WT of height $h+1$
- $\sigma=|\Sigma|$
- $N_0,N_1$ be the number of $0$s and $1$s in the root ($n=N_0+N_1$) and we define $|S_0|=N_0$ and $|S_1|=N_1$.

Let's partition the alphabet $\Sigma$ of $S$ as $\Sigma=\Sigma_0\cup\Sigma_1$:
![[WT inductive step.png|500]]
Characters in $\Sigma_0$ are those whose encoding starts with $0$ (the $0$s in the root), same similar with $\Sigma_1$.

We stress the fact that $S_0$ is over the alphabet $\Sigma_0$ and $S_1$ is over $\Sigma_1$, and that both $S$ and $S_0$ have $n_c$ occurrences of $c$ (same for $S_1$).

Then, inductively, **the subtree $S_0$ (similar for $S_1$) is compressed to this space**:
$$N_0 \cdot \underbrace{\left( \sum_{c \in \Sigma_0} \frac{n_c}{N_0} \log \frac{N_0}{n_c} \right)}_{H_0(S_0)} + o(\underbrace{h}_{(\log\sigma)-1} \cdot N_0)$$
and **the root, compressed with RRR, instead takes this number of bits**:
$$n \cdot \left( \sum_{b \in \{0,1\}} \frac{N_b}{n} \log \frac{n}{N_b} \right) + o(n)$$
adding up the quantities, we get:
$$\begin{align}
\underbrace{\left[\cancel{N_0} \cdot \left( \sum_{c \in \Sigma_0} \frac{n_c}{\cancel{N_0}} \log \frac{N_0}{n_c} \right) + o(h \cdot N_0)\right]}_{S_0} + 

\underbrace{\left[\cancel{N_1} \cdot \left( \sum_{c \in \Sigma_1} \frac{n_c}{\cancel{N_1}} \log \frac{N_1}{n_c} \right) + o(h \cdot N_1)\right]}_{S_1} + 

\underbrace{\left[\cancel{n} \cdot \left( \sum_{b \in \{0,1\}} \frac{N_b}{\cancel{n}} \log \frac{n}{N_b} \right) + o(n)\right]}_{\text{Root}}
\end{align}$$

by omitting $o$ terms and expanding the summation of the root, we are left with:
$$\sum_{c \in \Sigma_0} n_c \log \frac{N_0}{n_c} + \sum_{c \in \Sigma_1} n_c \log \frac{N_1}{n_c} + N_0 \log \frac{n}{N_0} + N_1 \log \frac{n}{N_1}$$
- $N_0=\sum\limits_{c\in\Sigma_0}n_c$
- $N_1=\sum\limits_{c\in\Sigma_1}n_c$
$$\sum_{c \in \Sigma_0} n_c \log \frac{N_0}{n_c} + \boxed{\sum_{c \in \Sigma_1} n_c \log \frac{N_1}{n_c}} + \sum_{c\in\Sigma_0}n_c \log \frac{n}{N_0} + \boxed{\sum_{c\in\Sigma_1}n_c \log \frac{n}{N_1}}$$
$$\begin{align}
\sum_{c \in \Sigma_0} n_c \log \left( \frac{N_0}{n_c} \cdot \frac{n}{N_0} \right) + \boxed{\sum_{c \in \Sigma_1} n_c \log \left( \frac{N_1}{n_c} \cdot \frac{n}{N_1} \right)} &=\\
&= \sum_{c \in \Sigma_0} n_c \log \frac{n}{n_c} + \sum_{c \in \Sigma_1} n_c \log \frac{n}{n_c}\\
&=\sum_{c\in\Sigma} n_c\log\frac{n}{n_c}\\
&=nH_0
\end{align}$$

**Theorem**
The wavelet tree of string $S\in\Sigma^n$, stored using RRR bitvectors in the nodes, uses:
$$nH_0(S)+o(n\log\sigma)\text{ bits}$$
>Assuming $\sigma=|\Sigma|=o(n/\log n)$.

### Access queries
To **access** a character at a specific index, we start at the root and navigate down to a leaf, by using $rank_0$ or $rank_1$ queries on bitvectors to calculate exactly where the target element gets pushed in the next level down.

For example let's **access** $S[6]$:
- $rank_0(6)=4$
- $rank_1(4)=2$
- $B$
![[WT access.png|500]]
The complexity is equal to $O(\log\sigma)$ which is the height traversal.

The **rank** query is done by retrieving the binary encoding (that we computed initially) of the character in which we are interested in, then follow in the same way as we did for access by using the $rank$ operator, but with the difference that this time we branch based on the current digit of the character.

For example let's compute $rank_C(13)$ recalling that $C=011$:
- $rank_0(13)=8$
- $rank_1(8)=3$
- $rank_1(3)=2$
![[WT rank.png|500]]

The **select** query is done with recursion, the result is accumulated on the unwinding process from leaf to root.
For example, with $select_C(2)$ with $C=010$:
1. Follow $C$'s bits from the root and reach $C$'s leaf and unwind
2. At level 3 we have $j=2$ trivially, we pass it up
3. At level 2 (`101`) the bit of $C$ is `1` lets call it $b$, hence we do $select_b(j)=select_1(2)=3$ hence $j=3$ and we pass it up
4. At level 1 (`01010010`) we proceed with $select_1(3)=7$
5. At the root (`10010001100011`) we conclude that $select_0(7)=11$, which is what we wanted to know, that is, the secondo position in which $C$ appears

### Final result
We've seen that any string $S\in\Sigma^n$ can be stored in $nH_0+o(n\log n)+O(\sigma\log n)$ bits, and that RSA queries take $O(\log \sigma)$ time.
>If $\sigma=O(1)$, then the space simplifies to $nH_0+o(n)$ and queries are solved in $O(1)$.

Like in the case of bitvectors, we can prove **that the WT of the concatenation**
**of strings reaches the zero-order entropies of those strings**.

**Theorem**
Let $WT\_size(S)$ be the bit-size of $WT(S)$, and let $S_i\in\Sigma^{n_i}$ for $i=1,...,t$ be $t$ strings of total length $n=\sum\limits_{i=1}^tn_i$, then:
$$WT\_size(S_1,...,S_t)\leq\left(\sum_{i=1}^tn_iH_0(S_i)\right)+o(\log\sigma)+O(t\sigma\log n)$$
The intuition is that each node gets partitioned in at most $t=3$ parts, each corresponding to one of the strings.
![[WT concatenation of strings.png|500]]
$O(\sigma)$ nodes, $O(t\cdot\sigma)$ parts, $O(t\cdot\sigma\cdot\log n)$ bits for the RRR blocks crossing the boundaries.
