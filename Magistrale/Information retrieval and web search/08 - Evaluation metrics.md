We can measure a lot of things when using a SE (e.g. query latency), but none of these will tell us if the user was **happy with their search results**.

The most direct signals of user happiness include:
- **Click-through rate**: how often results get clicked (clickbaits may inflate this)
- **Post-search behavior**: did the user spend money, or return to the site?
- **Dwell time**: how long a user stays on a clicked result before returning to the results page, longer Swell time generally means the result was useful

But happiness is hard to measure directly, the field then settled on **relevance** as the standard proxy for happiness.

### The Cranfield paradigm
The framework for measuring relevance was pioneered by **Cyril Cleverdon** in the **Cranfield experiments** and remains the standard today.

It requires three things:
- A benchmark document collection
- A benchmark query suite
- Relevance judgments: for each query, each document is labeled as _relevant_ or _not relevant_, or given a _graded score_

The challenge is that if we have many documents and many queries, fully judging every combination would require a lot of judgments, which is impossible, so in practice only a subset of documents gets judged for each query.

### Getting relevance judgments
**Crowdsourcing** is an alternative to hiring expert assessors, it could provide useful signal, but the variance in judgments is very high since different workers often disagree on whether something is relevant.

**Test queries** must be chosen carefully sine random terms from the document collection don't make good queries, the best approach is to **sample from real query logs**.

### The standard evaluation infrastructure
**TREC (Text REtrieval Conference)** is the primary institution for building and maintaining IR evaluation benchmarks, its main goals are:
- Create large scale test collections
- Researching the best methods for evaluation
- Running annual evaluation campaigns

A TREC test collection has three parts: a document set, a set of topics (information needs) and relevance judgments.
A system's output on a test collection is called a **run**.

To make judging feasible, TREC uses a technique called **pooling**, which means taking the top results from many submitted runs into a pool, and judging only those.

<u>Relevance is always assessed relative to the user's information need</u>, not the literal query string, for example:
- Information need: "my swimming pool bottom is turning black and needs to be cleaned"
- Query submitted: "pool cleaner"

### Unranked measures
These are the foundational metrics, treating retrieval as a binary classification problem.

|                   |    Relevant    |  Non relevant  |
| :---------------: | :------------: | :------------: |
|   **Retrieved**   | True Positive  | False Positive |
| **Not retrieved** | False Negative | True Negative  |

$$\text{Precision (P)}=\frac{TP}{TP+FP}$$
Of everything returned, what fraction was actually relevant?

$$\text{Recall (R)}=\frac{TP}{TP+FN}$$
Of everything relevant that exists, what fraction did we find?

$$\text{Accuracy}=\frac{TP+TN}{N}$$
Generally not used in IR because datasets are heavily skewed (most documents are irrelevant), making accuracy misleading high.

The **F-measure** combines _precision_ ($P$) and _recall_ ($R$) into a single number using the **harmonic mean**:
$$F=\frac{2PR}{P+R}$$
The **harmonic mean** is chosen deliberately, it is always **less or equal than the arithmetic mean**, and when two values differ greatly, it <u>pulls strongly toward the lower value</u>.
This means a system can't "cheat" by having very high recall but near $0$ precision and still get a good F-score.

The **weighted F-measure** allows us to emphasize one metric over the other:
$$F_\beta=\frac{(\beta^2+1)PR}{\beta^2P+R}$$
- $\beta<1$: emphasizes precision
- $\beta>1$: emphasizes recall
- $\beta=1$: the standard F-measure

### Ranked measures
In practice, search engines return a **ranked list**, not just a set, hence the order matters enormously and rank-based measures account for this.

By varying $k$ (the number of documents retrieved), we can compute precision and recall at each cutoff and plot them against each other, and as $k$ increases, recall generally increases but precision fluctuates.

Since these curves are jagged, they're **interpolated**, so at any recall level $r$, the interpolated precision is defined as the _highest precision_ achieved at any recall level $r' \geq r$, this produces a smooth, monotonically decreasing curve.

The standard approach uses **11 fixed recall levels** and reports precision at each.
![[Precision-recall.png|400]]

#### MAP: Mean Average Precision
MAP avoids the need for interpolation entirely and is one of the most widely used single-number metric in research for binary relevance.

For a single query, **average precision (AP)** is computed by:
1. Finding the rank position of each relevant document returned ($K_1,...,K_r$)
2. Computing $Precision@K$ at each of those positions
3. Averaging those precision values

If relevant document is never retrieved, its precision contribution is $0$:
$$MAP(Q)=\frac{1}{|Q|}\sum_{j=1}^{|Q|}\frac{1}{m_j}\sum_{k=1}^{m_j}\text{Precision}(R_{jk})$$
$MAP@K$ is a truncated version used in web search and recommender systems, where only the top-$K$ results are considered, reflecting the reality that users only engage with a limited number of results.

MAP gives each query equal weight (macro-averaging), regardless of how many relevant documents exist for it.

#### Precision@K
For web search, full precision recall is impractical since the total number of relevant document is unknown, what matters instead is how good are the **top K** results.
$$P@K=\frac{\text{Number of relevant documents in the top K}}{K}$$

#### MRR: Mean Reciprocal Rank
MRR is designed for scenarios with only **one correct answer**, called _known-item search_ or _navigational queries_ (e.g., "Wikipedia homepage," "flight booking page").
>The user's effort is proportional to how far down the list they have to scroll to find it.

For each query, the **reciprocal rank** is equal to $1/\text{rank of the first relevant result}$.
MRR averages this across all queries:
$$MRR=\frac{1}{|Q|}\sum_{i=1}^{|Q|}\frac{1}{rank_i}$$
---
### Graded judgments
Binary relevant/not-relevant is often too coarse, in web search, results might be highly relevant, marginally relevant or completely irrelevant.

#### DCG: Discontinued Cumulative Gain
DCG operates on graded relevance scores and embeds two key ideas:
1. **Higher relevance = more gain**: a highly relevant doc contributes more than a marginally relevant one
2. **Lower rank = less value**: a relevant doc at position $10$ is worth less than the same doc at position $1$ (the user is less likely to see it)

The **discount factor** $1/\log(rank)$, so positions $1,2,3,4,...$ get discounts of $1,1,0.63,0.5$.
$$DCG_p=rel_1+\sum_{i=2}^p\frac{rel_i}{\log i}$$
An alternative formulation used by some web companies amplifies the importance of highly relevant documents:
$$DCG_p=\sum_{i=1}^p\frac{2^{rel_i}-1}{\log(1+i)}$$

#### NDCG: Normalized DCG
The problem with raw DCG is that different queries have different amounts of relevant material, making cross-query comparison unfair.

NDCG fixes this by dividing by the DCG of the **ideal ranking** (i.e. if all the most relevant documents had been placed at the top).
$$NDCG_p=\frac{DCG_p}{IDCG_p}$$
NDCG is always between $0$ and $1$, and equals $1$ only if the ranking is perfect.

---
### Using user clicks instead of human judgments
Human relevance judgments are expensive, inconsistent between assessors, decay over time as document collections change, and may not reflect real users.
**Clicks offer a scalable alternative**.

The **problem with raw click counts** is that there is a strong **position bias**, which means that results at the top get clicked more simply because they're at the top, regardless of quality.

For this reason we can use **relative comparisons**, so if a user clicks result $5$ but skipped results $2$, $3$, and $4$, it's reasonable to infer result $5$ was more useful than the previous ones.

#### Kendall Tau correlation
Given a set of pairwise preferences $P$ (ground truth), we can compare two rankings $A$ and $B$ by counting agreements and disagreements with $P$:
$$\tau=\frac{X-Y}{X+Y}$$
where we mark with $x$ the agreements and with $Y$ the disagreements, and $\tau$ ranges from $-1$ for perfect disagreement to $+1$ for perfect agreement.

#### Interleaved A/B testing
Rather than showing users entirely different systems, we can **interleave** two rankings into a single result list and see which ranking's documents get more clicks:
1. _Take rankings_ $A$ and $B$
2. _Interleave them_ (alternating, starting randomly with $A$ or $B$ to neutralize position bias)
3. _Remove duplicates_ (a document appearing in both rankings is shown once but credited to both)
4. _Count how many clicks_ go to $A$-originated results vs $B$-originated results
5. **The ranking with more clicks wins**

This is **more sensitive than full-page A/B testing** because both systems compete on the same page for the same user.

**Full-page A/B testing** diverts a small fraction of real traffic (e.g. $1\%$) to a new algorithm and compares downstream metrics like clicks, purchases, or dwell time across the two user groups.

#### Zero click problem
As search engines increasingly answer questions directly on the results page (e.g. "Mount Everest height" displays the actual height in the result page without requiring a click), **click-based evaluation breaks down**.

If no one needs to click, _clicks no longer measure satisfaction_.
>This is an active area of challenge for search engine evaluation.

