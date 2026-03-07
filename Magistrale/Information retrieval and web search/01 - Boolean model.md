Basic assumptions of information retrieval are:
- **Collection**: a set of documents (assumed to be static for now)
- **Goal**: retrieve documents with information that is relevant to the user information need and helps the user to complete a task

How good are the retrieved docs?
- **Precision**: fraction of retrieved docs that are _relevant_ to the user's information need
- **Recall**: fraction of _all relevant_ docs in collection that are retrieved


## Boolean retrieval model
We ask ourselves: "which plays of Shakespeare contain the following words?"
$$\text{Brutus}\land\text{Caesar}\land\neg\text{Calpurnia}$$
We could grep for Brutus and Caesar, then strip out lines containing Calpurnia, but this is not the answer since it is slow for large corpora and _not_ Calpurnia is not trivial, then other operations such as "find word X near Y" are not feasible.

We can build a **term-document incidence matrix**.
![[Term-document incidence matrix.png|500]]

now we have a binary vector for each term, and to answer the query we can do a bitwise AND:
$$\begin{align}
&110100&\land\\
&110111&\land\\
&101111&=\\
&100100
\end{align}$$
which returns us: "Antony and Cleopatra" and "Hamlet".

When we consider **bigger collections**, building such matrix is expensive and it will result also in a _sparse matrix_ with a very little percentage of $1$'s, for this reason we could record only the $1$ positions.

### Inverted index
For each term $t$, we store the list of all documents that contain it.
>The previous image involved an inverted index.

With inverted indexes we have an **item to collection** mapping, instead of a **collection to item**.
As an example we could imagine searching for "Caesar", we don't want to open each collection and check if it appears inside it, instead we want to directly get the collections that mention it.

On **disk** we write this type of index as a _continuous block_, and in **memory** we store it as a _linked list_ in order to handle insertions of documents.

The **first steps** of text processing are:
- **Tokenization**: character sequence into word tokens
- **Normalization**: lowercase, accents removal (e.g. U.S.A and USA should match)
- **Stemming**: use a common prefix for various forms (e.g. authorize, authorization should be authoriz )
- **Stop words**: we may omit very common words (e.g. the, a, to, of)

After these first steps, tokens are normalized, thus becoming **terms** of the dictionary, in this step we just read the documents and form the index, for this reason we may have duplicates.

Follows the sorted index by term and then by DocID:

| _**Term**_  | ambitious | be  | brutus | brutus | capitol | caesar | caesar | caesar |
| :---------: | :-------: | :-: | :----: | :----: | :-----: | :----: | :----: | :----: |
| _**DocID**_ |     2     |  2  |   1    |   2    |    1    |   1    |   2    |   2    |

Then multiple term entries in a single document are merged and we add the document **frequency**:

|      _**Term**_      | ambitious | be  | brutus | capitol | caesar |
| :------------------: | :-------: | :-: | :----: | :-----: | :----: |
|      _**Freq**_      |     1     |  1  |   2    |    1    |   2    |
| _**Postings lists**_ |     2     |  2  | 1 -> 2 |    1    | 1 -> 2 |

### Query processing
We want to process the following query:
$$\text{Brutus}\land\text{Caesar}$$
1. Locate "Brutus" and retrieve its posting list
2. Locate "Caesar" and retrieve its posting list
3. Merge the two postings in order to find the match

![[Merge in retrieval query.png]]

```python
p1 = [1, 4, 5, 8]
p2 = [2, 4, 5, 6, 7, 8, 10]

# nextGEQ(p1,p2[j]) returns the pointer of the first docId in list p1
# which is greater than or equal to p2[j]
def intersect(p1, p2):
	answer = []
	i = 0
	j = 0
	while i != len(p1) and j != len(p2):
		if p1[i] == p2[j]:
			answer.append(p1[i])
		i = i + 1
		j = j + 1
		elif p1[i] < p2[j]:
			i = nextGEQ(p1, p2[j])
		else:
			j = nextGEQ(p2, p1[i])
	return answer
```

The implementation of `nextGEQ`, most of the times uses **pointer skipping**.
![[Pointer skipping.png|500]]
Suppose that we've stepped through the lists until we process $8$ on each list, we match it and advance on both lists, then since $11$ is the smallest, we advance the second pointer, but since the _skip successor_ of $11$ on the lower list is $31$, which is still lower than $41$, we can skip ahead pas the block $\{17,21,31\}$.

A simple **heuristic** used to decide how to distribute skip pointers is, for postings of length $L$, use $\sqrt L$ evenly-spaced skip pointers.
Skip lists can be _combined with compression of blocks_ of the lists, in order to avoid decompressing skipped sub-blocks.

**Time complexity**: $O(len(x)+len(y))$, it can stop early if one list is shorter.

When computing an **OR query**, we cannot use these optimizations since we have to fully check both lists, hence its **time complexity** is given by $\Theta(len(x)+len(y))$.

#### Query optimizations
With AND queries is it possible to process them in order of **increasing frequency**.
![[AND query optimization.png|500]]

Even with OR queries we can use this type of optimization, since know that the max size output of and OR query between two disjoint sets is given by the sum of their frequency.

### Strengths and weaknesses
**Boolean retrieval fails** for natural language, since it is way more complex, but it excels in things like library catalogs.

| Strenghts                  | Weaknesses                                         |
| -------------------------- | -------------------------------------------------- |
| Precise                    | Users must learn boolean logic                     |
| Efficient for the computer | Boolean logic insufficient to capture the language |
|                            | No control over size of result                     |

### Positional indexes
We want to be able to answer queries such as "Stanford university" as a **phrase**, thus the sentence "I went to university at Stanford" should not be a match.

One fix would be to <u>index every consecutive pair of words</u>, but i would bloat the dictionary massively other than returning **false positives**.

>[!Example]
>"Stanford University is in Palo Alto. This is not the only university. Palo Alto also hosts Palo Alto University."
>
>The biwords indexed from this would include: "stanford university", "university palo", "palo alto", "alto this", "only university", "university palo" again, etc.
>
>Searching for the phrase **"stanford university palo alto"** leads the system to break it into:
>- "stanford university"
>- "university palo"
>- "palo alto"
>
>And since all three biwords are found, the document is returned as a match even if the full phrase does not appear.

A real solution would be to use **positional indexes** which also sore the where in the document each word appears, now we can verify that words appear adjacent or within $k$ words of each other (_proximity queries_), despite being 2-4 times larger than a basic index.

For extremely common phrases like "Barack Obama", it's wasteful to merge positional lists every time, a **combined strategy** caches those as biwords while using positional indexes for everything else.

### Structured vs unstructured data
Databases handle structured data with exact queries, whilst IR handles free-form text.

There are tools such as [Westlaw](https://legal.thomsonreuters.com/en/westlaw) which are still used nowadays by experts in order to get precise IR queries with boolean models, must most of the data is semi-structured, which led to tools like [Elasticsearch](https://www.elastic.co/elasticsearch) which handles structured (e.g. metadata) and unstructured (e.g. full-text search) content.
