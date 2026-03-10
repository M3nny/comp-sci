### Full text indexing
Given a text $T$ of length $n$, we want to build an index that supports three queries efficiently:
- $locate(P)$: find all positions where pattern $P$ occurs ($O(m+occ)$)
- $count(P)$: return how many times a pattern $P$ occurs in $T$ ($O(m)$)
- $extract(i,\ell)$: return a substring starting at position $i$ of length $\ell$ ($O(\ell)$

Where $m$ is the length of the pattern, $occ$ the number of occurrences and $\ell$ is the length of the substring to extract.
>These are the ideal query times, which is basically as fast as reading the output itself.

The **ideal space** goal is $n\cdot \log|\sum|$ bits. which is as close as possible to the IT lower bound, possibly less if $T$ is compressible enough.

In a **streaming scenario** we build an index on-the-fly as $T$ arrives, without ever storing $T$ in full (non-trivial).

### The suffix trie
Every substring of $T$ is a **prefix** of some **suffix** of $T$, so if we build a tree containing all suffixes of $T$, we can find any pattern by just navigating from the root.

Each leaf stores the starting position of the corresponding suffix, then:
- Every leaf stores a <u>pointer to the next leaf</u>
- Every node stores a <u>pointer to the leftmost/rightmost leaf below it</u>
- Every node stores the <u>number of leaves below it</u>
![[Suffix trie.png|300]]

The $locate(P)$ query navigates to the node, then follows the leaf chain, thus yielding a complexity of $O(m+occ)$.
The $count(P)$ query involves navigating the trie following $P$'s characters, then the count stored at the landing node is the answer, which is $O(m)$.

The **space complexity** is equal to $\Theta(n^2)$ since the total length of suffixes is $1+2+\dotsi+n$.

### The suffix tree
In order to solve the space problem, we can **compress all unary paths** (long chains with one child) by replacing each edge label with just two pointers into the original text. thus reducing the label storage from $O(length)$ to $O(1)$ per edge.

The result is the **suffix tree**, which has the _same query time of the suffix trie_, but now only _uses $O(n)$ words of space_.
![[Suffix tree.png|400]]

This is still impractical for large datasets, since for example the the human genome has $3.2$ billion letters on $\{A,C,G,T\}\approx 760MiB$, and a good suffix tree uses $\approx 8n$ words, this would occupy $8\cdot3.2\cdot10^9\approx 95GiB$ words.

### The suffix array
Notice how root-to-leaf paths (string suffixes) are sorted lexicographically, this integer array is called **suffix array (SA)**.

We don't need a trie or tree to answer those queries, we only need the text and its SA.
Since the SA is sorted, occurrences of a pattern $P$ form a _contiguous range_ in SA, and we find this range using **binary search** by comparing $P$ to suffixes of $T$ at each step.
![[Suffix array.png|300]]

It occupies $n\log n+n\log|\sum|$ bits total, and has the following performance:
- $locate(P)$: $O(m\log n+occ)$
- $count(P)$: $O(m\log n)$
- $extract(i\ell)$: $O(\ell)$

The suffix array **occupies way less space** than the other two approaches, **but it's slower**.
It still occupies an order of magnitude more than the text itself if we consider the human genome, which is an _incompressible_ text over alphabet of size $4$.
>On compressible texts, this gap is worse. 

|    Structure     |     Space      |    Count     |      Locate      |
| :--------------: | :------------: | :----------: | :--------------: |
| **Suffix Trie**  | $O(n^2)$ words |    $O(m)$    |    $O(m+occ)$    |
| **Suffix Tree**  |  $O(n)$ words  |    $O(m)$    |    $O(m+occ)$    |
| **Suffix Array** | $n\log n$ bits | $O(m\log n)$ | $O(m\log n+occ)$ |
