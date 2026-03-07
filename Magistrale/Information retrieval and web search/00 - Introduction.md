**Information retrieval (IR)** is about _finding material_ of an _unstructured nature_ that satisfies an _information need_ from within _large digital collections_.

Already before the Web, this was a problem, but nowadays this field is many times associated with Web search.

### Web search engines
A Web search engine (WSE) is a software designed to search for information on the World Wide Web, by letting users enter **queries** (phrases), and the WSE returns a **ranked list of relevant websites**.

A WSE mainly consists of:
- **Crawler**: to collect web pages
- **Indexing system**: to organize pages for fast retrieval
- **Query processor**: to determine the relevance of pages to a given query, and rank them afterwards

The anatomy of a **Search Engine Result Page (SERP)** consists of:
- _User query_
- _Algorithmic search results_ with snippets
- _Related entity suggestions_
- _Featured descriptive snippet_ of the linked documents that best answer a query
- _People also ask (PAA)_ box
- AI overview, which uses _retrieval augmented generation (RAG)_ to read live search results
- Ads

### Generative AI and IR
Large Language Models (LLMs) are trained through **self-supervised learning** on a huge text corpora  to model the _probability distribution of a language_.

They generate responses token-by-token based on learned statistical patterns:
$$P(w_t|w_1,...,w_{t-1})$$
In principle at inference time, they do not need to query an external database of documents, but this may happen if the query requires real-time information, in this case the LLM may write a query for a search engine to retrieve top results.
>In this last case, the LLM works like a RAG.

IR systems then can operate in a pipeline that in some cases includes generative-AI, such as AI overview by Google.

Since **AI overviews** can _hallucinate_ when provided with irrelevant documents, and are also _expensive_, they are not used for too simple or too complex (risky) queries.
>In these two boundary cases, the classic ranked blue links take over.

The traditional **business model** of WSEs is **keyword-based advertising** where advertisers _bid on keywords_ and their revenue is based on pay-per-click (PPC).

### Difficulties in web search
Big data challenges are defined by the **4V's model**:
- Volume (amount of data)
- Velocity (speed of changes)
- Variety (range of data types and sources)
- Veracity (data integrity and trust)

IR systems have two main goals:
- **Effectiveness**: ML methods in order to enhance ranking
- **Efficiency**: pipelining and superscalar processor, parallel computing


And these two goals combined, determine also the _revenue_ of the search engine.
