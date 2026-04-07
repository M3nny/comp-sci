So far we've seen [[01 - Boolean model|boolean models]], that is documents either match or don't, which is good for experts, but not for most users.

Boolean queries often result in either too few or too many results.

### Ranked retrieval models
In **ranked retrieval** the system reorders the top documents in the collection for a given query, which is defined in **natural language**.

In this case having a big number of documents returned is not an issue since we just **return the top-k results**, but for this we need a way of assigning a score to a query-document pair.

A commonly used **measure of overlap** of two sets is the **Jaccard coefficient**:
$$jaccard(A,B)=|A\cap B|\setminus|A\cup B|$$
where $jaccard(A,A)=1$ and $jaccard(A,B)=0$ if $A\cap B=0$.

Now, since this is a measure of overlap between sets, it does not take into consideration the **term frequency**, which is also useful, since:
- The more frequent the query in the document, the higher the score
- Rare terms are more informative than frequent terms

We could recall the idea of **term-document count matrices**, where we consider the **number of occurrences** of a term $t$ in a document $d$, this is the definition of **term frequency**, noted as $tf_{t,d}$.

| Term \ document | Antony and Cleopatra | Julius Caesar | The Tempest | Hamlet | Othello | Macbeth |
| :-------------: | :------------------: | :-----------: | :---------: | :----: | :-----: | :-----: |
|     Antony      |         157          |      73       |      0      |   0    |    0    |    0    |
|     Brutus      |          4           |      157      |      0      |   1    |    0    |    0    |
|     Caesar      |         232          |      227      |      0      |   2    |    1    |    1    |
|    Calpurnia    |          0           |      10       |      0      |   0    |    0    |    0    |
|    Cleopatra    |          57          |       0       |      0      |   0    |    0    |    0    |
|      mercy      |          2           |       0       |      3      |   5    |    5    |    1    |
|     worser      |          2           |       0       |      1      |   1    |    1    |    0    |

A count vector, also called **bag of words** representation, does not consider the ordering of words in a document.

### Scoring documents
A little bit of notation before going forward:
- $cf_t$ (**collection frequency**): the number of occurrences of term $t$ in the whole document collection
- $df_t$ (**document frequency**): total number of documents that contain term $t$ in the corpus
- $tf_{t,d}$ (**term frequency**): total number of occurrences of term $t$ in a document $d$

We want to use $tf_{t,d}$, but we don't want a document with $10$ occurrences of the term to be $10\times$ more relevant, **relevance should not increase linearly with term frequency**.

We introduce then the **log-frequency weight** and the **score** for a document-query pair, which is the sum over terms $t$ in both $q$ and $d$:
$$w_{t,d}=\begin{cases}1+\log_{10}tf_{t,d}&\text{if }tf_{t,d}>0\\0&\text{otherwise}\end{cases}$$
$$Score_{qd}=\sum_{t\in q\cap d}(1+\log tf_{t,d})$$
>The score is $0$ for document $d$ if none of the query terms $q$ is present in $d$.

We would like **higher weights** for words characterized by a large $df_t$, but **even higher for globally rare terms**, which are characterized by a very small $df_t$.

Let's introduce the **inverse document frequency (idf)** of $t$ as:
$$idf_t=\log_{10}(N/df_t)$$
![[Idf.png|400]]
>The logarithm is used to dampen the effect of $df_t$.

>[!Important] The immutability of $idf_t$ 
>The $idf_t$ value **does not change for different documents**, because it only depends on the occurrences of term $t$ in the corpus.

$idf_t$ can **produce a ranking** of the matching documents for queries with at least two terms (if all docs to be ranked do not contain all query terms).
It **makes rare occurrences contribute more** to the final ranking.

### Weighting schemes
Terms that **appear often in a document** ($tf_{t,d}$) should **get high weights**, whilst terms that **appear in many documents** ($df_t$) should **get low weights**.

To express this mathematically we use the **product** of the term's weight and its $idf$ weight:
$$tf.idf_{t,d}=w_{t,d}\times idf_t$$
- Increases with the number of occurrences within a document
- Increases with the rarity of the term in the collection

>This is the best known weighting scheme in information retrieval.


Let's use this collection as an example:

|   Term    | Doc1 | Doc2 | Doc3 | $\mathrm{df}_t$ | $\mathrm{idf}_t$ |
| :-------: | :--: | :--: | :--: | :-------------: | :--------------: |
|    car    | $27$ | $4$  | $24$ |    $18,165$     |      $1.65$      |
|   auto    | $3$  | $33$ | $0$  |     $6,723$     |      $2.08$      |
| insurance | $0$  | $33$ | $29$ |    $19,241$     |      $1.62$      |
|   best    | $14$ | $0$  | $17$ |    $25,235$     |      $1.50$      |

>[!Example ]
>The $idf$ calculations are:
>$$
>\mathrm{idf}_{car} = \log \left(\frac{806,791}{18,165}\right) \approx 1.65
>\quad
>\mathrm{idf}_{auto} = \log \left(\frac{806,791}{6,723}\right) \approx 2.08
>$$
>
>$$
>\mathrm{idf}_{insurance} = \log \left(\frac{806,791}{19,241}\right) \approx 1.62
>\quad
>\mathrm{idf}_{insurance} = \log \left(\frac{806,791}{25,235}\right) \approx 1.5
>$$
>
>TF-IDF weights for Doc1 using an alternative formula: $\log(1+tf_{t,d})$:
>$$  
\begin{aligned}  
\text{car} &= 1.45 \times 1.65 = 2.39 \\  
\text{auto} &= 0.48 \times 2.08 = 1.2543 \\  
\text{insurance} &= 0 \\  
\text{best} &= 1.15 \times 1.5 = 1.764  
\end{aligned}  
>$$
>
>The **score** is defined as $Score(q,d)=tf.idf_{t,d}$.
>$$  
\text{Doc1}: 1.45 \cdot 1.65 + 0.48 \cdot 2.08 + 1.15 \cdot 1.5 = 1.23  
>$$
>$$  
\text{Doc2}:0.60 \cdot 1.65 + 1.52 \cdot 2.08 + 1.52 \cdot 1.62 = 6.61  
>$$ 
>$$  
\text{Doc3}:1.38 \cdot 1.65 + 1.46 \cdot 1.62 + 1.23 \cdot 1.5 = 6.48  
>$$
>
>Ranked list of docs: $\text{[Doc2, Doc3, Doc1]}$.

In this way each document is represented by a real-valued vector of $tf.idf$ weights $\in\mathbb R^{|V|}$, where $V$ is the vocabulary of the collection.

In other words, we have a $|V|$-dimensional vector space, where **vocabulary terms are axes of the space**, which can get big when applied in the context of web search engines.
>Although the vectors are very sparse, many entries are zero.

### Vector space scoring
The key idea is to also **represent queries as vectors** in the space.

Measuring **similarity** between vectors using **euclidean distance** is a **bad idea**.
Take for example a document $d$ and append it to itself in order to create $d'$, the euclidean distance between these two can be large even if _semantically equal_.

![[Euclidean distance vs angle.png|300]]

The euclidean distance between $q$ and $d_2$ is large although the distribution of terms in query $q$ and document $d_2$ are very similar.

We can rank documents in one the following (equal) ways:
- **Decreasing order of the angle** between query and document (angle = distance)
- **Increasing order of the cosine** between query and document (cosine = similarity)

We recall that the cosine is defined as as the dot product over the L2 norm, this is because dividing a vector by its L2 norm makes it a **unit vector**, so the initial example with one document appended to itself results to be identical to the original vector with this length-normalization.
Also, **long and short documents have now comparable weights**.
![[Cosine with normalized length.png|400]]
$$\cos(\theta)=\frac{A\cdot B}{||A||\cdot||B||}$$
