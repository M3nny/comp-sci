We are going to put together previously seen compressed data structures in order to obtain a new data structure which stores both the text and its index in $nH_0+O(n)$ bits, which is basically the compressed size of the text, while still supporting fast queries.

### Suffix array summary
Let's recall how the [[01 - Suffix trie#The suffix array|suffix array]] works, suing $S=BANANA\$$ as an example.
$$
\begin{array}{rc ccccccc}
i & = & \color{gray}{1} & \color{gray}{2} & \color{gray}{3} & \color{gray}{4} & \color{gray}{5} & \color{gray}{6} & \color{gray}{7} \\
\hline
SA[i] & = & 7 & 6 & 4 & 2 & 1 & 5 & 3 \\
\hline
\text{sorted suffixes} & : & \$ & \mathrm{A} & \mathrm{A} & \mathrm{A} & \mathrm{B} & \mathrm{N} & \mathrm{N} \\
& & & \$ & \mathrm{N} & \mathrm{N} & \mathrm{A} & \mathrm{A} & \mathrm{A} \\
& & & & \mathrm{A} & \mathrm{A} & \mathrm{N} & \$ & \mathrm{N} \\
& & & & \$ & \mathrm{N} & \mathrm{A} & & \mathrm{A} \\
& & & & & \mathrm{A} & \mathrm{N} & & \$ \\
& & & & & \$ & \mathrm{A} & & \\
& & & & & & \$ & & \\
\end{array}
$$
The SA stores the starting positions of all suffixes in sorted _lexicographical order_, to find the **range** for a pattern like "AN" we use **binary search** since the suffixes are sorted.
1. We search for the first suffix in the array that is greater than or equal to "AN", in this case it is at $i=3$
2. We search for the last suffix that still starts with "AN", that is $i=4$
3. The range is $[3,4]$

<u>Observe that the SA and text are only needed to read the</u> $i$-th <u>suffix in sorted order</u>.

Suppose that we have a **black-box** that allows us to extract the $i$-th suffix without looking up the text, such that $SA[3]$ returns immediately $ANA\$$, let's build it as follows:

Build a string $F$ that contains the _first character of every suffix_, in sorted order, in our example: $F=\$AAABNN$

For sure $n\log\sigma$ bits are sufficient ($\sigma$ is the length of the alphabet), we can do better, that is mark in a RRR bitvector $FO$ the _first occurrence of every character_.

Then store just _one occurrence of every character_ in a vector $\Sigma$ of size $\sigma$.
$$\begin{array}{rc ccccccc}
i & = & 1 & 2 & 3 & 4 & 5 & 6 & 7 \\
\hline
\mathrm{F} & = & \$ & \mathrm{A} & \mathrm{A} & \mathrm{A} & \mathrm{B} & \mathrm{N} & \mathrm{N} \\
\hline
\mathrm{FO} & = & 1 & 1 & 0 & 0 & 1 & 1 & 0 \\
\Sigma & = & \$ & \mathrm{A} & \mathrm{B} & \mathrm{N} & & & \\
\end{array}$$
This occupies $\leq n+o(n)+\sigma\log\sigma=O(n)$ bits (assuming $\sigma\leq n/\log n$).

Now we can retrieve the **first character** of the $i$-th suffix using $F$, but what about other characters?

### The core idea
We introduce **a new function** $\psi[i]$ as:
given that the $i$-th suffix in sorted order starts at position $SA[i]$ in the text, $\psi[i]$ tells us the index in the sorted order of the suffix that starts at position $SA[i]+1$.
$$\psi[i]=SA^{-1}[SA[i]+1]$$
The intuition is that $\psi$ lets us move one step forward in the text while staying in the SA's sorted order.
$$\begin{array}{rc ccccccc}
i & = & 1 & 2 & 3 & 4 & 5 & \color{green}{6} & 7 \\
\hline
SA[i] & = & 7 & 6 & 4 & 2 & 1 & 5 & 3 \\
\hline
\psi[i] & = & - & 1 & \color{green}{6} & 7 & 4 & 2 & 3 \\
\hline
\mathrm{F} & = & \$ & \mathrm{A} & \mathrm{A} & \mathrm{A} & \mathrm{B} & \color{red}{\mathrm{N}} & \mathrm{N} \\
& & & \$ & \color{red}{\mathrm{N}} & \mathrm{N} & \mathrm{A} & \mathrm{A} & \mathrm{A} \\
& & & & \mathrm{A} & \mathrm{A} & \mathrm{N} & \$ & \mathrm{N} \\
& & & & \$ & \mathrm{N} & \mathrm{A} & & \mathrm{A} \\
& & & & & \mathrm{A} & \mathrm{N} & & \$ \\
& & & & & \$ & \mathrm{A} & & \\
& & & & & & \$ & & \\
\end{array}$$

The third suffix is given by:
$$\begin{array}{cccc}
F[3] & F[\psi[3]=6] & F[\psi[6]=2] & F[\psi[2]=1] \\
\downarrow & \downarrow & \downarrow & \downarrow \\
\mathrm{A} & \mathrm{N} & \mathrm{A} & \$
\end{array}$$
So by repeatedly applying $\psi$ and reading  from $F$, we can extract any suffix one character at a time in $O(1)$ per character, without needing the original text or SA.
>But then $count$ queries will take $O(m\log n)$ time, like with the SA.

### Compressing $\psi$
The function $\psi$ has a structure that we can exploit:
within the range of SA entries that share the same first character (e.g. all suffixes starting with 'A'), $\psi$ is **strictly increasing**.

This is because if two suffixes both start with 'A', they are sorted by their remaining characters.
Applying $\psi$ moves to the next position, and those next positions must also be sorted in the same relative order.

So $\psi$ can be split into $\sigma$ **sorted sub-arrays**, one per character, and each one fo them can be compressed with [[04 - Elias-Fano data structure|Elias-Fano]].

>[!Example]
>Considering the previous example, we have that:
>- $EF_A$ contains $(1,6,7)$
>- $EF_B$ contains $4$
>- $EF_N$ contains $(2,3)$

The **total space of all Elias-Fano structures** is $nH_0+O(n)$ bits:
$$\begin{aligned}
\sum_{c \in \Sigma} \text{bitsize}(EF(\psi_c)) &\le \sum_{c \in \Sigma} (n_c \log(n/n_c) + \Theta(n_c)) \\
&= \sum_{c \in \Sigma} (n_c \log(n/n_c)) + \Theta(n) \\
&= n \sum_{c \in \Sigma} ((n_c/n) \log(n/n_c)) + \Theta(n) \\
&= n H_0 + \Theta(n)
\end{aligned}$$

### Searching on the compressed $\psi$
To compute $\psi[i]$ in $O(1)$:
- **Identify Character:** use $FO.rank_1​(i)$ to find which block $i$ falls into. The character $c$ is determined by the symbol at that rank in the alphabet $\Sigma$.
- **Calculate Offset:** find the start of that character's block using $j=FO.select_1​(FO.rank_1(i))$. The relative offset within $ψ_c$ is $i−j+1$.
- **Access:** retrieve the value from the specific compressed Elias-Fano array: $\psi_c[\text{local\_index}]$.

All three steps are $O(1)$, so $\psi[i]$ is computed in $O(1)$ total, and this is what enables binary search to work character by character in $O(m\log n)$ time.

#### Count query
With compressed $\psi$ and $F$, binary search on the SA range of a pattern $P$ works as before: each binary search step extracts the next character of the $i$-th  suffix using $F$ and $\psi$, then compares it with $P$.

$O(m)$ characters extracted per binary search step, $O(\log n)$ steps, then the total is $O(m\log n)$, which is the same as the plain SA, but now in compressed space.

#### Locate query
To answer locate queries, we need $SA[i]$ (i.e. the actual text position), but storing the full SA takes $O(n\log n)$ bits.
The solution is then to **sample only $1$ out of every $\log n$ entries**.

The idea is to compute $SA[i]$ with a **sampled suffix array (SSA)**:
- Store $SA[i]$ only when $SA[i]$ is divisible by $\lceil\log n\rceil$ (or $SA[i]=n$)
- This gives $n/\log n$ sampled entries, using $n$ bits total ($n/\log n$ entries $\times$ $\log n$ bits each)
- Store a RRR bitvector $M$ marking which SA positions are sampled

**Computing $SA[i]$ for a non-sampled position**:
- Apply $\psi$ repeatedly: $SA[\psi[i]]=SA[i]+1$, so $SA[i]=SA[\psi[i]]-1$
- Keep applying $\psi$ until we hit a sampled position

Since samples are spaced $\log n$ apart in the text, we need at most $\log n$ applications of $\psi$.
Each $\psi$ application is $O(1)$, so in total: $O(\log n)$ per SA lookup.

>[!Example]
>Let's use the string $BANANA\$$ , since $\lceil\log n\rceil=3$, $SSA=\{7,6,3\}$.
>- $SA[3]=4$ which is not sampled
>- Apply $\psi$: $\psi[3]=6$, and $SA[6]=6$ which is sampled
>- We applied $\psi$ twice, so $SA[3]=SA[\psi^2[3]]-2=6-2=4$

Binary search is $O(m\log n)$, then each of the $occ$ occurrences costs $O(\log n)$ to retrieve, so the total is $O((m+occ)\log n)$.

#### Extract query
Extract queries use the same sampling trick, but with the inverse $SA^{-1}$ sampled instead of SA.

Given a text position $i$, we an apply $\psi$ at most $\log n$ times to reach a sample, then read $\ell$ characters using $\psi$, which costs $O(\log n+\ell)$.
