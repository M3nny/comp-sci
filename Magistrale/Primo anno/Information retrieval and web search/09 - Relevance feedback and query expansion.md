User happiness/satisfaction can only be measured by **relevance to information needs**, not by relevance to queries, this is because a retrieve document may contain the query terms, but still not answer the information need.

We also have to consider the **vocabulary mismatch** problem, where for example, a document containing "plane" is retrieved, but not one containing "aircraft".

In order to solve this, in this chapter we are going to see two strategies:
- **Relevance feedback**: the user tells the system which returned documents were useful or not, and the system adjusts the query accordingly
- **Query expansion**: the system automatically adds synonyms or related terms to the query, without requiring user input
### Relevance feedback
**Interactive relevance feedback** improves initial retrieval results by telling the IR system which docs are relevant or not.

The basic idea is the following:
1. The _user_ issues a query
2. The _search engine_ returns a set of documents
3. The _user_ marks some docs as relevant, some as non-relevant
4. The _search engine_ computes a new query to represent the user information need
5. The _search engine_ runs the new query and returns new results (hoping to have a better recall)

#### Centroids
Recalling that [[06 - Vector space model#Vector space scoring|documents are represented as vectors]] we use the assumption that relevant docs will form a cluster, and non relevant docs will live in other clusters.

Before going forward, we give the definition of a **centroid** of a cluster:
$$\vec\mu(D)=\frac{1}{|D|}\sum_{d\in D}\vec v(d)$$
Where $D$ is a set of documents, and $\vec v(d)=\vec d$ is the normalized vector used to represent each document in $D$.

Intuitively, if we **average the vectors** of all documents a user marked as relevant, we get a point in space that represents what _relevant_ looks like for this query.

#### Rocchio algorithm
The **Rocchio algorithm** implements _relevance feedback in the vector space model_.
It aims to choose an **artificial query** maximizing:
$$\vec q_{opt}=\arg\max_{\vec q}[sim(\vec q,\mu(D_r))-sim(\vec q,\mu(D_{nr}))]$$
- $D_r$: set of known relevant docs
- $D_{nr}$: set of known nonrelevant docs

The ideal modified query should be as close as possible to the centroid of all relevant documents, and as far as possible from the centroid of all non-relevant documents.

Mathematically, this **optimal query** $\vec q_{opt}$​ should be the vector difference between those two centroids:
$$\vec q_{opt}=\frac{1}{|D_r|}\sum_{\vec d\in D_r}-\frac{1}{|D_{nr}|}\sum_{\vec d_j\in C_{nr}}\vec d_j$$
But **in practice we don't know** all relevant and non-relevant documents, we only have the small subset the user labeled, so the practical Rocchio formula is:
$$\vec q_m=\alpha\vec q_0\beta\frac{1}{|D_r|}\sum_{\vec d_j\in D_r}\vec d_j-\gamma\frac{1}{|D_{nr}|}\sum_{\vec d_j\in D_{nr}}\vec d_j$$
- $\vec q_0$: original query vector
- $\alpha,\beta,\gamma$: tunable weights

The new query moves toward the relevant documents and away from the non-relevant ones in the vector space.

**Positive feedback** (marking things relevant) is _more informative than negative feedback_.
>A common setting is $\beta = 0.75$ and $\gamma = 0.25$.

Many systems skip negative feedback entirely, treating unmarked documents as mildly non-relevant.

Despite its effectiveness, relevance feedback has many drawbacks:
- It's **computationally expensive**: the modified query has many more terms (denser vectors), making it slower to process
- **Users don't like doing it**
- The results become **harder to explain**: users often can't tell why a document appeared after feedback was applied

### Pseudo-relevance feedback
Since asking users for explicit feedback is unpopular, **pseudo-relevance feedback** automates it in the following way:
1. Run the original query and get a ranked list
2. Assume the top-$k$ documents are relevant
3. Apply Rocchio to modify the query
4. Re-run the modified query

This **works well on average**, but it has a known issue called **query drift**, that is, if those top-$k$ documents happen to be about something slightly off-topic, the modified query will drift further and further from the user's actual intent, especially if the process is repeated multiple times.

### Query expansion
Instead of learning from user feedback, the system [[02 - Document ingestion#Terms|expands the query by adding synonyms]] or related terms.

There are various **sources for related terms**, between them, we have the following.

**Query logs**
- _User session analysis_: if users who searched for a word end up searching for another one, that's a signal that the two are related (frequent sequential patterns)
- _Co-clicks_: if users searching for a word $v$ and users searching for $w$ both frequently click the same url, those queries are likely related (frequent co-occurring click pattern)

**Manual thesauri**
Curated databases of synonyms and related terms.

**Automatic (co-occurrence) thesauri**
Generated from the document collection itself by computing term-term similarities. The key idea is: words that appear in similar documents (or contexts) are likely similar in meaning.

### Distributional semantics and word embeddings
The _co-occurrence_ idea leads to **distributional semantics**, which is the principle that a word's meaning can be inferred from the words that appear around it.

Modern systems learn **dense low-dimensional vectors** called **word embeddings**.

These vectors are trained so that <u>words appearing in similar contexts end up with similar vector representations</u>, so for example, "car" and "automobile" end up close together in embedding space, even if they never directly co-occur.

This enables **Automatic Query Expansion (AQE)**:
1. For each term $t_i$ in the query, find its $k$ nearest neighbors in embedding space
2. Pool all candidate expansion terms across all query terms into a set $C$
3. For each candidate term, compute its average similarity to all original query terms
4. Select the top-$K$ highest-scoring candidates as expansion terms

This can also be **combined with pseudo-relevance feedback**: instead of using just the original query terms, we pull candidate expansion terms from the top-ranked retrieved documents.
