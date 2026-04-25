In this chapter we're going to see how to speed up vector space ranking, and then put together a complete search system.

#### TAAT and DAAT
When dealing with a phrase query (with multiple terms), each term has its posting list composed by `(docID, Score)` pairs for every document containing that term.
There are two strategies for computing scores across these lists.

**Term-At-A-Time (TAAT)**
Process one query term completely before moving to the next, we accumulate partial scores per document in a big array, then at the end we sort the array and return the top-k results.

**Document-At-A-Time (DAAT)**
Process all query terms simultaneously, computing each document's full score before moving to the next document.

TAAT needs more memory since we keep accumulators for all documents that match nay term, whilst DAAT uses less memory (we can discard low-scoring documents early) and is much more efficient when we need to operate on boolean semantics.
>Modern search engines mostly use DAAT.

### Fast scoring
If we assume that each query term appears exactly once ($tf_{t,q}=1$), then the query weight $w_{t,q}$ is always $1$, this means that we **don't need to normalize the query vector** (since its a constant factor that does not change ranking order).

Score accumulation per document becomes a simple addition rather than a multiply and then add.

The **FastCosineScore (TAAT)** algorithm exploits this concept by looping over query terms, look up each posting list, add the document's tf-idf weight directly to its score accumulator, then normalize at the end by document length.

Now we return to the main point, TAAT is bad for boolean queries, in fact if we want to apply an AND query, we have to process every score anyway, and only then, filter documents.

![[TAAT.png]]

Other than this, TAAT has a lot of **cache misses** due to many accumulators to be incremented (which cause jumps in memory), and there is a **need to sort huge numbers of accumulators**.

We are now going to see how to pick off docs with K highest cosines without sorting the associated scores.

### Efficient Top-K selection
Let $J$ be the number of docs with nonzero cosines (much less than $N$ if query terms do not include stop words).

Rather than sorting all $J$ scored documents, we can build a [[Heap sort|max-heap]] (for TAAT) from the complete array of accumulators in $2J$ comparisons (similar to heap-sort).
Then extract the top $K$ in $K\log J$ steps, for $J=1M$ and $K=100$, this is $10\times$ faster than full sorting.

For DAAT we can use instead a **min-heap** of exactly $K$ candidates, and as we process each new document with score $s'$:
1. Check if $s'$ is greater than the heap's current minimum
2. If not, skip, otherwise remove the minimum and insert the new document
> In this way we never store more than $K$ documents at once.

### WAND scoring
WAND (Weak AND) is a DAAT method that avoids computing all $J$ scores by **pruning documents** that can't possibly be in top $K$.
>This is a basic idea which comes from [[Branch & Bound|branch & bound]].

We use an **upper bound (UB)** on how much any document in a posting list can contribute to the total score:
$$UB_t=idf_t\times\max_d(w_{t,d})$$
and maintain a **threshold** $\tau$ which indicates the minimum score currently in the min-heap (i.e. the worst of the best $K$ found so far).

The **pivoting mechanism**:
1. Sort query terms' current "fingers" (pointers) by their document ID
2. Accumulate upper bounds left to right untile the cumulative sum exceeds $\tau$
3. The document at that point is the _pivot_ (the first candidate worth investigating)
4. All documents before the pivot are _hopeless_ and skipped using `nextGEQ()`
5. If the pivot documemt actually appears in all relevant posting lists, compute its real score, otherwise advance fingers and pivot again

>[!Example]
>For the query "catcher in the rye" with threshold $6.8$, document $273$ (which only contains "catcher", $UB = 2.3$) is immediately hopeless and skipped.
>Document $589$ has a cumulative UB of $7.2 > 6.8$, so it becomes a candidate, but after computing its actual score, it turns out to be a **false positive** (real score $6.6 < 6.8$), so it doesn't enter the heap.
>![[Pivoting example 1.png|400]]
>![[Pivoting example 2.png|400]]

WAND is **safe**, it guarantees the true top-$K$, while computing far fewer full scores than naive DAAT.
>It works best for long queries and small $K$.

#### Block-max WAND
A further refinement on the previous algorithm.
WAND's global UB per posting list can be very loose (a single outlier document inflates the bound for the whole list, causing many false positives).

**Block-max** stores finer-grained upper bounds:
- Each posting list is split into blocks of $64-128$ documents IDs
- Each block stores its own local maximum impact store
- During pivoting, we can use the tighter block-level UB instead of the global list UB, skipping even more documents without decompressing them

---
### Unsafe approximate ranking
**Safe ranking** guarantees the true top-$K$.
**Unsafe (approximate) ranking** intentionally trades correctness for speed, we might miss a few true top-$K$ documents, returning near-optimal results instead.

This is acceptable in practice because ranking functions are already imperfect proxies for user satisfaction.
>A document ranked $11$th vs. $10$th makes little real-world difference.

The general approach is to build a smaller set $A$ of **contenders** ($K < |A| << N$), then return the top-$K$ from $A$.

There are several techniques for building $A$.

**Unsafe WAND**
Artificially inflate the threshold $\tau'=F\cdot \tau$ where $F\geq 1$.
This prunes more aggressively, skipping documents that might have made the cut under true WAND.

**Index elimination**
For queries like "catcher in the rye", terms like "in" and "the" have very low $idf$ and contribute almost nothing to scores.
We then simply _ignore their posting lists entirely_, this eliminates huge numbers of documents from consideration (since "the" appears in nearly every document).

**Soft AND / Docs containing many query terms**
Instead of scoring any document matching at least one query term, only score documents _matching several terms_ (e.g. at least 3 of 4).
This is a "soft AND", which means that documents matching only one or two terms are excluded from set $A$, drastically reducing computation.

**Champion lists**
At index-build time, for each term $t$, precompute the $r$ _documents with the highest $tf.idf$ weight_, called _champions_.
At query time, only score documents that appear in the champion list of at least one query term.
The value of $r$ is fixed at index build time and can vary per term (rare terms may include nearly their whole posting list).

### Static quality scores and authority
Relevance (cosine score) isn't enough, since a highly relevant but obscure document might rank below a well-known authoritative one.
The solution is to add a **query-independent quality score** $g(d)\in[0,1]$ to each document.

Examples of $g(d)$ may be:
- PageRank
- Number of citations
- Publication venue prestige

The combined score becomes:
$$\text{net-score}(q,d)=g(d)+\cos(q,d)$$
A key trick is to remap document IDs so that documents are **sorted by $g(d)$** ine very posting list (highest $g(d)$ = lowest ID).
This means traversing any posting list naturally encounters the most authoritative documents first, enabling **early termination**, this enables to stop early in time-constrained applications and still return high-quality results.

### Champion lists with $g(d)$, high/low lists and tiered indexes
The following ideas combine quality scores with champion lists.

**Champion lists in $g(d)$-ordering**
For each term, we maintain the $r$ documents with the highest $g(d)+tf.idf_{t,d}$ and then query time only considers these.

**High/Low lists**
Split each posting list into two tiers:
- _High list_ = champion list (top-scoring documents)
- _Low list_ = the rest

At query time, traverse only high lists first, if we get $\geq K$ results, stop, otherwise fall through to low lists.

**Tiered indexes**
Break the entire index into a hierarchy of sub-indexes ordered by document importance.
- Tier $1$ is _small_ but contains the most important documents
- Tier $3$ is _large_ but contains less important ones.

Queries are processed tier by tier, stopping as soon as enough results are found.
The same document can appear in multiple tiers (once per query term it's relevant to).

### Impact-ordered postings (TAAT variant)
Instead of ordering posting lists by document ID, order them by $w_{f,t,d}$ (the term's contribution to the document's score) highest first.
This makes only TAAT feasible (DAAT needs DocID ordering), but enables the following two unsafe optimizations.

**Early termination**
For each query term's posting list, stop after either a fixed number of documents $r$, or when the weight drops below a threshold.
Take the union of these partial lists and compute scores only for those documents.

**Idf-ordered terms**
Process query terms in order of _decreasing idf_ (most informative first).
After processing each term, check if scores have stabilized, and if adding the next (less informative) term changes nothing significantly, stop early.

### Document clustering and index pruning
An architectural approach: cluster documents offline by similarity (e.g. by content similarity or co-click likelihood).

Build a **separate smaller index for each cluster**, then a **federator** (coordinator node) selects the most relevant clusters based on query-cluster similarity, then searches only those.

This dramatically **reduces the search space**, though it introduces challenges in load balancing and cluster quality.

### Parametric/Field and zone indexes
Real documents aren't just bags of words, they have **structure**.

**Fields (parametric indexes)** are structured metadata with specific values, such as:
- Author name,
- Publication date
- Language

These are _stored in separate indexes_ and typically queried as conjunctions (e.g. "find documents authored by Shakespeare in 1601").

**Zones** are unstructured but labeled regions of a document, such as:
- Title
- Abstract
- References

These get their own inverted indexes, a zone query might be "find documents with 'merchant' in the title zone matching the query 'gentle rain'."

Zones can be encoded either in the dictionary (e.g. `william.title`, `william.abstract`) or in the postings (e.g. `2.author, 2.title`).

### Term proximity and aggregate scoring
Users prefer documents where query terms appear **close to each other**.

The smallest window $\omega$ containing all query terms is a useful proximity signal.
For example, for the query "strained mercy", the phrase "The quality of mercy is not strained" has $\omega = 4$ words.

$\omega$ **can be incorporated as yet another additive feature** in the final scoring function, alongside cosine similarity and $g(d)$.

How these signals are combined is either expert-tuned or, increasingly, **learned from data** using Machine-Learned Ranking (MLR).

### The complete search system
Putting it all together, a modern search engine pipeline looks like this.

**Offline (index building)**:
- Documents -> parsing and linguistic processing -> indexers
- Multiple index types are built: zone/field indexes, tiered positional inverted indexes, $k$-gram indexes (for spell correction), and structures for inexact top-$K$ retrieval
- A document cache stores parsed documents for snippet generation

**Online (query processing)**:
1. User query -> free-text query parser
2. Query goes to spell correction (optionally, only if the original query returns too few results)
3. Query hits the relevant indexes, retrieving candidate documents
4. Candidates pass to a _scoring and ranking module_, whose parameters are learned via MLR from a training set of query-document relevance judgments
5. Final results page is assembled (with snippets generated from the document cache)

![[Search system.png]]
