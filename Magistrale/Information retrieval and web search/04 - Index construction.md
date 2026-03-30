Before talking about how we construct an index, we recall the [[Tipologie di memoria|memory hierarchy]].
Access to **DRAM** is much faster than accessing the disk, even more if the disk is an **HDD** which cannot transfer data during head seeks, **SSDs** solve this last issue, but are still slower than DRAM and caches.
>Spatial locality is essential to exploit memory hierarchies.

Nowadays servers have a lot of GBs allocated for the main memory, storage is anyways orders of magnitude larger, and having **many regular machines** is preferable instead of having a big fault-tolerant machine.

### Inverted index construction
We cannot construct an index in memory if we are dealing with large collections, for this reason we are required to use **out-of-core index construction** techniques.

We recall that to build an [[01 - Boolean model#Inverted index|inverted index]] we have to parse documents, then the inverted file is **sorted** by terms and then by `Doc#` (if the sorting algorithm is not stable).

It is not possible to store and sort a large corpus in memory, or better, [[Memoria virtuale|virtual memory]] would allow this, but with a lot of **page faults**.

It is not even possible to sort it on the disk either, since disk is slow.

#### Blocked Sort-Based Indexing (BSBI)
This algorithm applies sorting with fewer disk seeks, with an out-of-core technique which exploits spatial locality.

The algorithm can be thought as:
1. **Read** a block of documents, and in the meantime emit the triple(s) `(termID, docID, freq)`
2. **Sort** that block **in memory** using [[Quick sort|quicksort]]
3. **Write** the sorted block (called "run") to disk
4. **Repeat** until all documents are processed
5. **Merge** all sorted runs into one final index

The **merge step** is critical, a naive **binary merge** (i.e. combining pairs of runs repeatedly) is expensive because we keep re-writing larger and larger files to disk.

A better approach is to use a **multiway-merge**, where we read one small chunk from each run simultaneously into memory, and then output the globally smallest elements into an output buffer and flush when full, in this way we read  and write all data just once.

#### Single-Pass-In-Memory Indexing (SPIMI)
In the previous BSBI algorithm, we assumed that a global dictionary maintaining `term -> termID` mappings could fit into memory.
It was actually possible to avoid this mapping and just work with `(term, docID)` postings, but then the intermediate files become very large.

SPIMI sidesteps this issue:
1. Each block gets its own **local dictionary**
2. Postings are **appended** as the arrive rather than sorted upfront (faster)
3. When memory is filled, **flush the partial index** to disk and start fresh
4. After all blocks are written, **merge them** (with vocabulary reconciliation and docID remapping)

SPIMI is **generally faster and memory-efficient** than BSBI since it avoids the overhead of maintaining a global term mapping and defers sorting to the end of each block.

#### Distributed Indexing with MapReduce
For web-scale collections, we can distribute the work across multiple machines using the MapReduce procedure.

A **master** machine assigns each task to an idle machine from a pool.

**Map Phase (parsers)**:
Each machine reads a subset of documents and emits `(term, docID)` tuples, routing them to the right partition based on terms' first letters.

For example if we had three partitions: `a-f, g-p, q-z` we will route terms with first letter being `b` to the first partition.

**Reduce Phase (inverters)**:
Each inverter collects all pairs for its letter range and builds sorted postings lists.

![[Magistrale/Information retrieval and web search/Images/MapReduce.png|400]]

#### Dynamic indexing
Up until now we assumed that collections are **static**, but real search engines can't stop and rebuild the index every time a new page is crawled.

For this reason we have various solutions.

**Auxiliary indexes**:
New documents go into a small in-memory index, then searches query both indexes and merge results.

Periodically, the auxiliary index is _merged into the main one_, but this implies poor server performance during the merge.

Merging of the auxiliary index into the main index is _efficient if we keep a separate file for each postings list_.
Merging posting lists is the same as a simple list append, but this implies that we would need a lot of files (inefficient for the OS).

**Invalidation bit-vector**:
Deleted documents are flagged and filtered out of results without immediately rebuilding.

**Periodic full rebuild**:
Even if the large search engines now do dynamic indexing, they still fully rebuild the index periodically.

### Sharding in search engines
We've seen how [[02 - MongoDB#Sharding|sharding]] is used in distributed databases to distribute and partition data across multiple physical nodes.

In our indexing study case, we can split nodes in two principal ways.

**Document-based partitioning**:
- Each node holds a complete index for a subset of documents
- Every query hits every node, and results are merged
- Simple to build (SPIMI on each split), but expensive query time

**Term-based partitioning**:
- Each node holds the complete posting list for a subset of terms
- Queries only contact the nodes holding relevant items (faster)
- Multi-term queries require coordination, and nodes containing popular terms get hammered by traffic

To handle the last point we can:
- Increase the number of shards in case of a large index
- Increase the number of replicas in case of large traffic

