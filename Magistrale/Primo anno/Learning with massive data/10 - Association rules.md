The goal here is to discover **hidden relationships** between items in large datasets, for example in _market-basket analysis_ where we want to know which products customers tend to buy together.

Association rules express **co-occurrence**, **not causation**, for example, the rule `{Bread} -> {Milk}` doesn't mean that purchasing bread will cause milk purchases, it just means that the two appear together frequently.

- **Itemset**: any collection of items (e.g. `{Milk, Bread, Coke}`), a $k$-itemset has exactly $k$ items
- **Support count ($\sigma$)**: how many transactions contain the itemset, for example `σ({Milk, Bread, Coke}) = 2` means it appears in $2$ transactions
- **Support (supp)**: fraction of all transactions containing the itemset, in the previous example it would have been `2/N` where `N` is the total number of transactions
- **Frequent itemset**: one whose support meets or exceeds a minimum threshold $s$ we can define
- **Association rule**: a rule of the form `X -> Y` evaluated with three metrics:
	- _Support_: how often $X$ and $Y$ appear together
	- _Confidence_: between transactions containing $X$, what fraction also contains $Y$?
	- _Interest_: confidence minus the baseline support of $Y$, this tells us whether the rule is genuinely interesting or just reflects how common $Y$ is overall, a positive interest means $Y$ appears more often when $X$ is present than it normally would

### Two step association rules mining
**Brute forcing** in order to find all association rules **does not work**, since for $n$ items we generate $2^{n-1}$ item sets, which will generate even more association rules, and usually there are thousands of items.

The smart approach decouples the problem into two phases:
1. **Frequent itemset generation**: find all itemsets meeting the support threshold
2. **Rule generation**: for each frequent itemset $I$, generate every rule of the form $A\to(I\setminus A)$ for every subset $A$. Since support is already known, we just need to check confidence. All rules from the same itemset share the same support but can differ in confidence

Frequent itemset generation is the most expensive task.

### The Apriori algorithm
If an itemset is frequent, **all of its subsets must also be frequent**, conversely, if an itemset is infrequent, **all of its supersets must also be infrequent**.

This is called **anti-monotonicity of support**, that is, adding more items can never increase support, only decrease or maintain it.
This lets us prune a huge parte of the search space: once we find that `{AB}` is infrequent, we never need to check `{ABC}`, `{ABD}`, `{ABCDE}`, ...
![[Apriori prune.png|500]]

The algorithm iterates level by level through the itemset lattice:
1. Scan the dataset to find all frequent single items $L_1$
2. Generate candidate pairs $C_2$ from $L_1$, then scan to find frequent pairs $L_2$
3. Generate candidate triples $C_3$ from $L_2$, then scan to fin frequent triples $L_3$
4. Repeat until no frequent itemsets are found

There are three ways to generate the candidates $C_k$:
- **Brute force**: combine all items into all possible $k$-length sets
- **Merge $L_{k-1}$, with $L_1$**: take each known frequent $(k-1)$-itemset and append each frequent single item, this is more efficient than the previous method, but sill generates some unnecessary candidates, for example, we'd generate `{ABD}` even if `{BD}` alone is infrequent, hence violating Apriori
- **Merge $L_{k-1}$ with itself**: merge two $(k-1)$-itemsets only if they share the same first $k-2$ items (same prefix), for example `{ABC}` and `{ABD}` share prefix `{AB}` will generate `{ABCD}`, then apply a pruning step, where for each generated candidate, verify that all its $(k-1)$-subsets are in $L_{k-1}$, if any subset is missing, discard the candidate immediately

### Counting pairs efficiently
Pairs ($2$-itemsets) are a bottleneck because there are so many of them, hence there are two approaches for counting them:
- **Matrix approach**: keep a triangular matrix where entry $[i,j]$ counts occurrences of pairs $\{i,j\}$, this is simple but requires $O(n^2)$ memory, which is infeasible for thousands of items
- **Triples approach**: store only `(item_i, item_j, count)` triples for pairs that actually appear, saves memory when most pairs are rare, but hash table lookup is needed per pair. In practice can use more memory than the matrix if many pairs exist

### PCY (Park-Chen-Yu) algorithm
PCY is a clever enhancement that uses otherwise wasted memory during the first Apriori pass.
The observation is that in the first pass we're only counting individual items, leaving most memory idle.

**Pass 1**
Count item frequencies as usual, but also _hash every pair_ `{i,j}` to a bucket in a hash table and increment that bucket's count.
We're not storing which pairs went to each bucket, just the total count per bucket.

**Pass 2**
Convert the hash table into a _compact bitmap_ ($1$ bit per bucket: $1$ = frequent, $0$ = infrequent).
A pair `{i,j}` is now only counted as a candidate if _both_ $i$ and $j$ are frequent individually and the pair hashes to a frequent bucket, fewer candidates equals to less memory needed for counts.
>Hash collisions mean a bucket's count is an _overestimate_, but an infrequent bucket is a guaranteed filter (the pair can't be frequent).

**PCY Multistage**
Adds a _third pass_ using the bitmap from pass $1$ as a pre filter, build a second, more refined hash table in pass $2$, then by pass $3$ we need far fewer candidates.
Each extra pass improves filtering quality.
![[PCY multistage.png|400]]

**PCY Multihash**
Achieves similar benefits _without extra passes_ by using two independent hash tables simultaneously in pass $1$.
We get two bitmaps for the price of one pass, at the cost of each hash table being smaller (more collisions).
![[PCY multihash.png|300]]

### Limited pass algorithms
Every Apriori iteration requires a **full scan of the dataset**, which is **expensive** for truly massive data, for this reason we introduce two other algorithms.

#### SON algorithm (Savasere-Omiecinski-Navathe)
The idea is to **split the dataset into chunks**, then run Apriori cheaply on each chunk (using a scaled-down support threshold of $p\times s$, where $p$ is the chunk's fraction of the full dataset), then verify the union of all discovered candidates against the full dataset in one final pass.

**Correctness guarantee**:
If an itemset is globally frequent, it _must be frequent in at least one chunk_, so we can't miss any truly frequent itemset (no false negatives).
We may have false positives (candidates that aren't globally frequent), but those are filtered in the second pass.

#### Toivonen's algorithm
More probabilistic, but it can finish in just two passes if lucky.
1. Take a **small random sample**, then run Apriori on it with a slightly lower support threshold (to reduce risk of missing globally frequent itemsets)
2. Compute the **negative border**, that is, _itemsets that are infrequent in the sample_, but all of _whose immediate subsets are frequent_, these are the "edge cases" to watch out for
3. **Scan the full dataset once** to compute actual support for both the sample-frequent itemsets and the negative border
4. If none of the negative border items turned out to be globally frequent:
	- We have our answer
	- Otherwise if any negative border item is frequent, the sample was unrepresentative, hence we have to restart with a new sample

The **negative border acts as a safety net**: if our sample missed a frequent itemset, it will show up in the negative border, alerting us to restart rather than returning a wrong answer.

