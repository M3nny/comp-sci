In this chapter we focus on how to compress the index in order to **increase speed of data transfer** from disk to memory.
>Note that read and decompress is faster than read uncompressed data.

We can already differentiate between between **lossless compression** in which all information is preserved, and **lossy compression** in which we discard some information (e.g. stemming).

We cannot assume an upper bound on the term vocabulary, this is because we will discover that the vocabulary keeps growing with the collection size (e.g. unicode keeps adding symbols).

---
### Heaps' law
**Heaps' law** tells us how vocabulary grows with collection size:
$$M=kT^b$$
where $M$ is the vocabulary size,  and $T$ is the number of tokens in the collection (i.e. collection size).
>Typical values are $30\leq k\leq100$ and $b\approx0.5$.

It shows us that vocabulary **grows roughly as the square root of collection size**, meaning it never stops growing, it just slows down.

Heaps' law on [Reuters RCV1 corpus](https://dl.acm.org/doi/10.5555/1005332.1005345):
![[Heaps' law.png|400]]
Spelling errors **increase growth rate**, whilst stemming and case folding **reduce it**.

>[!Example]
>Looking at a collection of web pages, you find that there are $3000$ different terms in the first $10,000$ tokens and $30,000$ different terms in the first $1,000,000$ tokens.
>
>Assume that the search engine indexes a total of $20,000,000,000$ ($2 \cdot 10^{10}$) pages, containing $200$ tokens on average: $T = 200(2\cdot10^{10}) = 4 \cdot 10^{12} = (2\cdot10^6)^2$
>
>What is the size of the vocabulary of the indexed collection as predicted by the Heaps’ law, by considering $b\approx0.5$?
>$$M=6\cdot 10^7$$

### Zipf's law
**Zipf's law** describes term frequency distribution. thus impacting the size of the positional postings lists.

In natural language there are a **few very frequent terms** and **many rare terms**.

Assuming that **terms are ranked** from the most frequent to the least frequent:
- $t_i$ is the **term at rank $i$** in the collection
- $cf_i$ is the **collection frequency**, that is, the total number of times $t_i$ appears across the whole collection
- $df_i$ is the **document frequency**, that is, the number of documents containing $t_i$
- $tf_{i,d}$ is the **term frequency**, that is, how many times $t_i$ appears in a specific document $d$

**Zipf's law** states that if we rank all terms from most to least frequent, the collection frequency of the $i$-th ranked term is inversely proportional to its rank:
$$cf_i=\frac{K}{i}$$
where $K$ is a normalizing constant equal to $cf_1$ (i.e. the frequency of the most common term).

If the first most frequent term occurs $cf_1$ times, then the second occurs $cf_1/2$ times, and the third $cf_1/3$ times, and so on.
$$\log cf_i=\log K-\log i$$
this means that in a log-log plot of frequency vs rank, Zipf's law predicts a straight line with slope equal to $-1$.

![[Zipf's law.png|400]]

Zipf's laws is actually a special case of a more general **power law**:
$$p(i)\approx k\cdot i^{-\alpha}$$
where $\alpha=1$ for pure Zipf implementation.

This produces a **long tail** shape that shows that a few terms are extremely common, while the vast majority are very rare.
![[Long tail.png|500]]
This connects to the **Pareto 80/20** principle since $80\%$ of the terms contribute to only $20\%$ of the index (and viceversa).

---
### Compression
We want to keep the dictionary in memory, but some devices may have very little memory (e.g. mobile devices), hence compressing is important.

Original index table without optimizations:

| Terms | Frequency | Postings ptr. |
| ----- | --------- | ------------- |
| The   | 123.456   | ->            |

Here we list progressively better approaches.

**Fixed-width arrays**
Simple but wasteful, allocating fixed bytes per term wastes space on short words and can't handle long ones.

**Dictionary-as-a-string**
pack all the terms into one continuous string, then instead of storing the term itself, use a pointer to the point in the string where the term actually begins, its end is defined by the beginning of the next term pointer.

**Blocking**
Instead of a pointer per term, store one pointer per block of $k$ terms, plus a $1$-byte length prefix per term (which indicates the length of the term). In this way with $k=4$ we save $3$ pointers but add $4$ length bytes. This slightly slows down the lookup (linear scan within a block)
![[Blocking.png|600]]

Number of comparisons in binary search without and with blocking (assuming that each term is equally likely):
- Without blocking: $(1+2\cdot2+4\cdot3+4)/8\approx2.6$
- With blocking: $(1+2\cdot2+2\cdot3+2\cdot4+5)/8 = 3$

>[!Tip] Structuring the tree based on term frequency
>If the frequencies of the query terms were non-uniform, but known, we could have structured the tree in way that puts terms with high frequency near the root, in order to minimize comparisons.

**Front coding**
Exploit the fact that adjacent alphabetically sorted words often share prefixes.
Store only the difference from the shared prefix, for example:
- Original string: $\text{8automata8automate9automatic10automation}$
- Encoded string: $\text{8automat*a1}\diamondsuit \text{e2}\diamondsuit \text{ic3}\diamondsuit \text{ion}$

### Postings compression
**Postings lists are way larger** than the dictionary, so compression here matters most.

A **posting** for our purposes is a **docID**, since a frequent term like "the" has docIDs that are _close together_ (e.g. $1,2,3,...$) and for a rare term we have docIDs that are _spread far apart_ (e.g. $12000, 50538, ...$), instead of storing the actual docIDs, we **store the gap between them** in order to use less bit for common terms.

#### VB codes
This calls for **variable-length encoding**, in this case we are going to use **variable byte (VB) codes** which are _byte aligned_.

Since for a gap value $G$, we want to use close to the fewest bytes needed to hold $\log_2G$ bits, we **begin with one byte to store $G$** and dedicate $1$ bit in it to be a **continuation bit flag**, this is in case it cannot be stored in one byte and has to be continued in the next byte.
>VB-encoded postings are uniquely prefix-decodable, and no special marker is needed to separate codes.

>[!Example]
>Imagine having the following postings (docIDs) and their VB-encoding:
>- $824 \to 00000110\space10111000$
>- $829\to 1000010$
>- $215406\to 00001101\space 00001100\space10110001$
>
>Then they get stored as the byte concatenation:
>$$000001101011100010000101000011010000110010110001$$
>>There are also other methods used for alignment, not only byte-alignment as we've seen here.
>>For example we could also use word-alignment.

#### Gamma codes
A gamma code uses **bit-level** codes to represent each gap $G$ as:
- **Offset**: $G$ in binary with the leading $1$ removed (e.g. $13\to1101\to101$)
- **Length**: the length of the offset, encoded in _unary_, which is $n$ ones followed by a zero (e.g. for $13$ the length is $1110$)

The **gamma code** is the concatenation of _length_ and _offset_ (e.g. $13\to 1110\space101$).
>They are uniquely prefix-decodable.

The offset is encoded in $\lfloor\log_2 G\rfloor$ bits ($1$ less than the number of bits to represent $G$), and the length of the length is $\lfloor\log_2 G\rfloor+1$ bits (including the ending $0$), hence $G$ **is encoded using $2\lfloor\log_2 G\rfloor+1$ bits**.

**We cannot just store the binary translation** of the gaps, otherwise the would not be "prefix-free", for example $10$ ($2$) is also the start of $100$ ($4$).
Gamma codes fix this by adding a self-delimiting structure (the unary length prefix).

Since the length of the offset is produced with inefficient unary code, we can use instead **delta codes** which express the length of the gamma code as another gamma code:
$$\delta(G)=\gamma(\lfloor\log_2G\rfloor+1)+\text{offset}$$
So for $G=13$:
- Binary: $1101$
- Offset: $101$
- Length: $3$
- $\gamma(3)=101$ (since $3=11$, offset = $1$, unary length = $10$)
- Final $\delta(13)=101\space101$
>Delta encoding wins over large numbers.

The space occupied by delta codes is: $2\cdot\lfloor\log \lfloor\log G\rfloor\rfloor+1$.

>[!Attention]
>Machines have byte/word boundaries, hence operations that cross word boundaries are slower.
>VB codes are aligned and potentially more efficient.

|   $G$   | Bits needed | VB bytes | VB bits | $\gamma$ bits |  Winner  |
| :-----: | :---------: | :------: | :-----: | :-----------: | :------: |
|    5    |      3      |    1     |    8    |       5       | $\gamma$ |
|   127   |      7      |    1     |    8    |      13       |    VB    |
|   128   |      8      |    2     |   16    |      15       | $\gamma$ |
|   500   |      9      |    2     |   16    |      17       |    VB    |
| 16,000  |     14      |    2     |   16    |      27       |    VB    |
| 500,000 |     19      |    3     |   24    |      37       |    VB    |

For larger gaps VB wins because gamma's unary length component grows linearly, while VB adds a whole new byte every $7$ bits.

### References to information theory
Shannon showed that the **minimum expected message length** we can achieve with any binary prefix-free code is between $H(P)$ and $H(P)+1$, where $H(P)$ is the entropy:
$$H(P)=\sum_ip_i\log\frac{1}{p_i}$$
[[00 - Information and inference#Huffman coding|Huffman codes]] are optimal, but require traversing a tree or slow table lookups, and in our case we have an alphabet that is too large to apply this method.

The gamma codes are optimal w.r.t. $H(P)$ when the integers to be compressed conform to the following probability distribution:
$$Pr(n)=\frac{1}{2n^2}$$
This follows a ind of **power-law**, and it is skewed towards small values (a few large numbers).
>We remember that the power-law is defined as $Pr(n)\approx kn^{-\alpha}$.

