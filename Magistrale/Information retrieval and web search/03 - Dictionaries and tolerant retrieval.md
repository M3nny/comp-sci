We've seen that **terms**, **document frequencies** and **pointers to each posting list** are used for the [[01 - Boolean model#Inverted index|inverted index]], and they are actually stored in a **dictionary**, in this chapter we are going to see how to store this data structure efficiently and how to quickly lookup elements.

### Dictionary data structures
A first approach is to use **hashtables**, in this case each vocabulary term is hashed to an integer, in this way the lookup time is $O(1)$, but it is not possible to prefix search with a wildcard (seen later), and if vocabulary keeps growing, we have to [[02 - Static organizations#Hash methods|rehash]] everything.

Another approach is to use a **binary tree** where each internal node represents a _binary test_, and its outcome determines one of the two sub-trees along which the search proceeds.
![[Binary tree.png|400]]

We could also use a [[03 - Dynamic organizations#B-trees|B-tree]] in order to generalize the binary tree approach.
In this case nodes can have more than two children, and since a range of child nodes is permitted, B-trees do not need re-balancing as often as binary trees.
![[B-tree.png|400]]

**Binary search trees** are **not good for spatial locality** since their nodes occupy only a fraction of any memory block, whilst in B-trees we can put multiple elements into each node/memory block.

B-trees were originally invented for storing data on disks, but nowadays they are also used as an in-memory data structure, since main memory is way slower than current processors, and thus **effective cache exploitation** is crucial.

In a B-tree of order $m$, each internal node has at most $m$ children, if a node has $n\leq m$ children, it contains $n-1$ keys.
We can choose $m$ so that the pointers to the $m$ children plus the $m-1$ elements **fill out a cache line at the highest level** of the memory hierarchy.
>Each **leaf node** stores at most $m$ elements, but it can even be a multiple of $m$.

![[B-tree elements.png|500]]

Trees, unlike hashtables, **require a standard ordering**, but we typically use **lexicographical order**.

They **solve the prefix problem** but are **slower** $O(\log M)$, and they have to be re-balanced (even if B-trees mitigate this).

### Wild-card queries
We want to find all docs matching `mon*`.
It is possible by retrieving all terms in range `mon <= word < moo`.

In case we wanted to find all docs matching `*mon`, we could maintain an additional **reverse B-tree** (which stores terms backwards) and then retrieve all words in range `nom <= word < non`.

>[!Example]
>Terms stored backwards.
>- sermon -> nomres
>- lemon -> nomel
>- demon -> nomed
>- salmon -> nomlas
>- backgammon -> nommagkcab

In order to handle queries with wildcards in the middle, such as `co*tion`, we could lookup `co*` and `*tion` in the two B-trees, and **intersect two term sets**, but this would be **expensive**.

The solution is to **transform wild-card queries** so that they occur always at the end.

### Permuterm index
Let's consider the term `hello`, we are going to **expand the dictionary/lexicon size**, as we store $n+1$ terms instead of $1$ (where $n$ is the length of the term), in practice we are going to rotate the word $n$ times, and make each rotation point to the original term.
>We mark the end of a rotation with the character `$`.

![[Permuterm.png|200]]
The idea is to insert `$` at the end, and rotate the term to have `*` at the end.
>For example: `h*e` first becomes `h*e$` and then `e$h*`.

Queries:
- `X` -> `X$`
- `*X` -> `X$*`
- `X*Y` -> `Y$X*`
- `X*` -> `$X*`
- `*X*` -> `X*`
- `X*Y*Z` -> `Z$X*` then filter out those who don't contain `Y`

### K-gram index
Enumerate all $k$-grams (sequence of $k$ chars) occurring in any term.

>[!Example]
>From `April is the cruelest month`, we get the $2$-grams:
>`$a,ap,pr,ri,il,l$,$i,is,s$,$t,th,he,e$,$c,cr,ru,ue,el,le,es,st,t$, $m,mo,on,nt,h$`

We then maintain a **second inverted index** from bigrams to dictionary terms that match each bigram.
>Also used for spelling correction.
![[Bigrams.png|400]]


To get terms matching `mon*`, we would run the query on the second inverted index as follows: `$m AND mo AND on`, but we would also enumerate `moon` which is wrong, hence we must post-filter these terms against the query and then lookup surviving elements in the term-document inverted index.

We can also manage queries with a wildcard in the middle, such as:
`mo*n` -> `$mo*n$` -> `$m AND mo AND n$`.

>[!Note]
>With $2$-grams, considering the leading and trailing `$`, we have a size per term equal to $(n+1)\cdot2$ chars:
>`$h, he, el, ll, lo, o$`
>
>With $3$-grams, considering the leading and trailing `$`, we have a size per term equal to $n\cdot 3$ chars:
>`$he, hel, ell, llo, lo$`

Wild-cards can result in expensive query execution, in fact full wildcard support (like in databases) is not available in major web search engines.

---
### Spelling correction
This technique can be used both when correcting documents being indexed and also when correcting user queries to retrieve "right" answers.

There are two main flavors:
- **Isolated words**: check each word on its own for misspelling
- **Context-sensitive**: look at surrounding words (e.g. I went form Padova to Venice)

Correction algorithms are tuned for specific use cases, for example OCR can confuse O and D often.

We can either:
- Directly retrieve documents indexed by the most likely correct spelling
- Return several suggested alternative queries with the correct spelling (_Did you mean ... ?_)

### Isolated word correction
The fundamental premise is that <u>there is a correct lexicon from which the correct spellings come </u>.

There are two choices for this:
- An hand-maintained dictionary
- The lexicon of the indexed corpus (may contain mis-spellings)

Given a lexicon and a character sequence $Q$, we have to return the words in the lexicon **closest** to $Q$.

So in principle, among alternative correct spellings for a mis-spelled query, we choose the "nearest" one, and if two correctly spelled queries are tied, we select the most common.

### Edit distance
Given two strings $S_1$ and $S_2$, the **edit distance** is defined as the minimum number of operations to convert one to the other.

**Operations** are typically at character level and are:
- Insert
- Delete
- Replace
- Transposition

>[!Example]
>The edit distance from `dof` to `dog` is $1$ replace operation.
>- From `cat` to `act` is $2$ replacements (or $1$ transposition)
>- From `cat` to `dog` is $3$ replacements

The edit distance is usually found by a [[Approccio dinamico|dynamic programming]] algorithm, and the time to compute the edit distance between two strings is $O(|S_1|\times|S_2|)$, where $|S_i|$ denotes the length of a string.

Defining $D(i,j)$ as the edit distance between the first $i$ characters of string $X$ and the first characters of string $Y$, the idea is:
- Compute $D(i,j)$ for small $i,j$
- Compute larger $D(i,j)$ based on previously computed smaller values
- Eventually, compute $D(i,j)$ $\forall i\in (0<i<n)$ and $j\in(0<j<m)$ and return $D(n,m)$

$$D(i,j)=\min\begin{cases}D(i-1,j)+1\\D(i,j-1)+1\\D(i-1,j-1)+\begin{cases}2&\text{if }X[i]\neq Y[j]\\0&\text{if }X[i]=Y[j]\end{cases}\end{cases}$$

We can compute a **weighted edit distance**, by weighting certain operations, for example `m` is more likely to be my-typed as `n` than as `q` in the qwerty keyboard, therefore replacing `m` by `n` is a _smaller edit distance_ than by `q`.
>This may be formulated as a probability model.

Given a misspelled word, we enumerate all correct words up to a present distance (**distance-based range query**):
- Show terms found to the user as suggestions
- Alternatively, run with the top-1 most likely correction

We **can't compute every edit distance** to every dictionary term, hence a few options are:
- _Restrict the search dictionary_ to terms beginning with the asme letter as the query string
- _Generate everything up to a small edit distance_ ($k=1,2,...$) and then intersect these candidates with terms in the index lexicon and keep those that actually exist (i.e. are full complete words)
- _Use the n-gram overlap_; correct and misspelled terms likely share many n-grams

#### N-gram overlap
When dealing with the latest option, **n-gram overlap** we can set a _threshold_ on the number of matching n-grams, in order to filter out terms where the number of matching n-grams is smaller than the threshold.

>[!Example]
>Suppose the text is `november` with trigrams: `nov, ove, vem, emb, mbe, ber`.
>The query is `december` with trigrams: `dec, ece, cem, emb, mbe, ber`.
>
>The overlap is equal to $3$, and if this is bigger than the threshold, then we can infer that december may be the misspelled term of november.

We can use the **Jaccard coefficient** to measure the set overlap, it is defined as:
$$J=|X\cap Y|\setminus|X\cup Y|$$
Equals $1$ when $X$ and $Y$ have the same elements, and $0$ when they are disjoint.
>In the previous example we may have had set the threshold set to $J=3/9=0.3$.

>[!Example]
>Considering the query `lord`, we want to identify words matching $2$ of its $3$ bigrams (`lo`, `or`, `rd`):
>![[Bigrams overlap.png|400]]
>We match `border` and `lore`, but `border` is implausible:
>- $J(lord. lore)=2/4$
>- $J(lord,border)=2/6$

### Context-sensitive correction
A naive idea is to **generate similar words** (with small edit distance) for each word in a phrase, then try combinations (one fix at a time).

>[!Example]
>Possible resulting phrases queries for `flew form heathrow`:
>- `flew from heathrow`
>- `fled form heathrow`
>- `flea form heathrow`
>
>Pick the one with the most search results (expensive).

Another technique which is more feasible, is to keep corrections that form **common word combinations**.

>[!Example]
>The phrase `flew form heathrow` is split into biwords (can be more):
>- `flew form`
>- `form heathrow`
>
>Now we check biwords frequencies, and for each of them we try small edits ($=1,2$) and modify one word at a time, for example: `flew form -> flew from, flew farm, ...`.
>
>Then we keep only frequent/valid biwords and combine the best corrections, so we end up having: `flew from heathrow`.

