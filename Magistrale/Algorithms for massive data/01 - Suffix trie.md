### Full text indexing
Given a text $T$ of length $n$, we want to build an index that supports three queries efficiently:
- `count(P)`: return how many times a pattern $P$ occurs in $T$
- `locate(P)`: find all positions where pattern $P$ occurs
- `extract(i, l)`: return a substring starting at position $i$ of length $\ell$

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

The `count(P)` query involves navigating the trie following $P$'s characters, then the count stored at the landing node $u$ is the answer, which is $O(m)$.
>`count(a)=3`.

The `locate(P)` query navigates to the node $u$ matching $P$, then goes to its leftmost leaf and then follows the leaves chain that are under the subtree with root $u$, thus yielding a complexity of $O(m+occ)$.
>`locate(a)=3,4,1`.

The `extract(i, l)` query is done by locating the leaf position corresponding to $i$, then from the root node pointing to that leaf, advance for $\ell$ steps and store its characters.
>`extract(3,2)=aa`.

The **space complexity** is equal to $\Theta(n^2)$ since the total length of suffixes is $1+2+\dotsi+n$.

### The suffix tree
In order to solve the space problem, we can **compress all unary paths** (long chains with one child) by replacing each edge label with just two pointers **into the original text** $T$, thus reducing the label storage from $O(length)$ to $O(1)$ per edge.

The result is the **suffix tree**, which has the **same query time of the suffix trie**, but now only **uses $O(2n)=O(n)$ words of space** (text + data structure).
![[Suffix tree.png|400]]

The **queries work in the same way** as the previous suffix trie, but this time we look at $T$ for the references.

This is still impractical for large datasets, since for example the the human genome has $3.2$ billion letters on $\{A,C,G,T\}\approx 760MiB$, and a good suffix tree uses $\approx 8n$ words, this would occupy $8\cdot3.2\cdot10^9\approx 95GiB$ words.

### The suffix array
Notice how root-to-leaf paths (string suffixes) are **sorted lexicographically**, this integer array is called **suffix array (SA)**.

**We don't need a trie or tree to answer those queries**, we only need the text and its SA.
Since the SA is sorted, **occurrences of a pattern $P$ form a contiguous range** in SA, and we find this range using **binary search** by comparing $P$ to suffixes of $T$ at each step.
![[Suffix array.png|300]]

Since we store $n$ suffixes and for each one of them we store an integer which is large at most $\log n$ bits, we need $n\log n$ for the SA, and then since we need to also store the original text, we also occupy additional $n\log|\Sigma|$ bits, hence this **occupies a total of $n\log n+n\log|\Sigma|$ bits**.

`count(a)`: do a binary search until we find a suffix that starts with $a$ (index: $2$), but we don't stop here, we keep going with the binary search discard the rightmost part of the search until we get to the first occurring $a$ (index: $1$), then we do another binary search from the first index that we found ($2$) which discards the leftmost part of the search, until we get to the last occurring pattern starting with $a$ (index: $3$). Then we compute `lastIndex - firstIndex + 1`, which gives us the result $3$.

`locate(a)`: proceed in the same way as the `count` query, but this time, after storing the indexes, de-reference them in order to return the positions where the pattern $a$ occurs, that is $SA[1]=3$, $SA[2]=4$ and $SA[3]=1$.

`extract(3,2)`: we ignore the SA (which is only used as an index) and go look directly in $T=abaab\$$ and take the substring at position $3$ with length $2$.

The time complexities are:
- `count(P)`: the binary search cost is given by $O(m\log n)$
- `locate(P)`: sum the `count` cost + de-referencing every occurrence, which results in $O(m\log n+occ)$ 
- `extract(i,l)`: simply lookup in the original text $O(\ell)$

The suffix array **occupies way less space** than the other two approaches, **but it's slower**.
It still occupies an order of magnitude more than the text itself if we consider the human genome, which is an _incompressible_ text over alphabet of size $4$.
>On compressible texts, this gap is worse. 

|    Structure     |       Space        |    Count     |      Locate      | Extract   |
| :--------------: | :----------------: | :----------: | :--------------: | --------- |
| **Suffix Trie**  |   $O(n^2)$ words   |    $O(m)$    |    $O(m+occ)$    | $O(\ell)$ |
| **Suffix Tree**  |    $O(n)$ words    |    $O(m)$    |    $O(m+occ)$    | $O(\ell)$ |
| **Suffix Array** | $O(n\log n$) bits* | $O(m\log n)$ | $O(m\log n+occ)$ | $O(\ell)$ |
