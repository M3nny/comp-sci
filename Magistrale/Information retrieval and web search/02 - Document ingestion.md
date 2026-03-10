When documents enter a search system, they go trough three stages:
- A **tokenizer** splits raw text into individual words
- **Linguistic modules** normalize those words
- An **indexer** stores them in an [[01 - Boolean model#Inverted index|inverted index]]

Before even tokenizing, the system needs to answer some fundamental questions:
- _What format is the document in?_
	- This is a classification problem that is often solved with heuristics
- _What language is it in?_
- _What even counts as a document?_
	- Is an email with 5 attachments one document or 6? There is not universal answer, it depends on the application

### Tokenization
Tokenization is the process of splitting text into individual units, called **tokens**.
- "Finland's": do we keep the apostrophe or not?
- "Hewlet-Packard": one token or two?
- "San Francisco": a biword or two separate words?
- Numbers like "3/20/9" contain spaces or slashes that shouldn't be treated as separators

And language makes it harder, for example Japanese has no spaces between words, so the system must figure out word boundaries from context.

### Terms
A **term** is what actually gets stored in the index, it's a token after **normalization**.

>[!Example]
>- Word, WORD, word -> word
>- U.S.A, USA, usa -> USA

These mappings create **equivalence classes**, which are groups of tokens that all map to the same index term.
It is **crucial to normalize both** the indexed documents and the queries in exactly the same way.

One could think that removing the **commonest words** is a right move, but various queries need them (e.g. "flight to Venice), furthermore, good compression techniques use very little space for including them in the system.

We can handle **synonyms** by using _equivalence-class_ to index them under the same word, or we could use them to expand queries, for example, if a query contains "automobile", look under "car" as well.

### Stemming and lemmatization
Both of these techniques reduce words to a common base form to improve matching.

**Lemmatization** uses linguistic knowledge to find the true dictionary (e.g. "am", "are" become "be").

**Stemming** is a rule-based approach that just chops suffixes (e.g. "compressed", "compression" become "compress").

The most famous stemmer is **Porter's algorithm**, which applies five sequential phases of suffix-removal rules, always choosing the rule that matches the longest suffix, for example $(m>1)EMENT$ strips "ement" only if the remaining stem is long enough:
- "replacement" -> "replac"
- "cement" -> "cement"

Stemming **helps recall** (i.e. increases the number of results), but for some queries it **harms precision** (i.e. the quality of the results).

### Document ingestion in neural IR
Classical IR relies on exact term matching in the inverted index, whilst modern systems add a **neural reranker** on top:
1. The inverted index retrieves an initial set of candidate documents
2. A neural reranker (i.e. a deep learning model) re-scores them for relevance

These rerankers are **Learning to Rank (LtR)** models, they learn to output relevance scores for query-document pairs from training data, rather than relying on hand-crafted rules.

Neural models can't work with raw text, they need numbers, this requires a different kind of tokenization than classical IR.

**Byte Pair Encoding (BPE)**:
1. Start with individual characters as tokens
2. Iteratively merges the most frequent adjacent pair into a new token
3. Repeats until reaching a target vocabulary size
>Common words stay whole, rare words get split into subword pieces.

**WordPiece**:
1. Start with individual characters as tokens
2. Score all adjacent pairs, but unlike BPE which just counts frequency, WordPiece scores each possible merge using a likelihood formula that maximizes the prediction score of the language model
3. Merge the best pair and repeat until reaching a target vocabulary size

WordPiece tokenization follows a simple _greedy left-to-right_ rule:
- If the word is in the vocabulary, keep it whole, else take the longest prefix that is in the vocabulary, then mark the remainder with `##` and repeat

For example, "tokenization" becomes: `["token",  "##ization"]`.

#### Word embeddings
After tokenization, each token is mapped to a **dense vector** (list of floating point numbers), these are called **embeddings** or **word distributed representations**.

The key property is that words appearing in similar contexts get **similar** vectors.
Similarity is measured with dot products or Euclidean distance.
>The neural network only processes the embeddings at the end.

