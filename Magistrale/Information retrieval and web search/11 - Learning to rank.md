The purpose of a **ranking system** is to check how relevant is a document $d$ to a query $q$.
Normally we have a framework with three parts:
- _Query representation_
- _Document representation_
- _Query-document representation_

![[Ranking system.png|500]]

Which are all fed into an **aggregation function** that outputs relevance scores $s(q,d)$.
We can imagine this as: encode the query, encode the document, compare them and score the match.

### Bag of words (BOW) ranking
Classical IR simplifies the previous framework by **representing both query and documents as sparse vectors**, each dimension corresponds to a word in the dictionary, and the value is roughly how often that word appears.
>There's no query-document interaction feature.

The aggregation function is something like [[06 - Vector space model#Vector space scoring|cosine similarity]], the issue with BOW is that it only cares about whether a word appears  and how often, **without understanding its meaning**.

### Learning to rank (LtR) pipeline
Search engines use a **two-stage pipeline**:
- **Base ranker**: fast and cheap retrieval step that returns a large set of candidate documents
- **Re-ranker**: a LtR model that re-ranks those candidates more carefully

![[LtR pipeline.png|500]]

This enables higher speeds since the **model inference cost is a hard constraint** in production systems, which directly impacts throughput.

LtR treats **ranking as a machine learning problem**, where we provide a training set of queries paired with documents and their relevance labels (e.g. $0$ is irrelevant and $4$ is perfectly relevant), then the model learns a sorting function from this data.

The goal is to **get the ranking right**, not to predict the exact numeric label.

LtR models rely on **hand-crafted feature vectors** describing each (query, document) pair, these fall into three categories:
- **Query-only features**: properties of the query itself, regardless of the document (e.g. query length, query type)
- **Query-independent features**: properties of the document that don't change per query (e.g. PageRank, URL length)
- **Query-dependent features**: this is the most important category, and tells how well the document matches this specific query (e.g. cosine similarity, click count for that query-URL pair)

Another important feature may be the **minimum query window size** which is the shortest text span in the document containing all the query words, this directly expresses a relevance signal.

### LtR approaches
**Pointwise**
Each document is scored independently, it is essentially a _regression or classification problem_ ("how relevant is this document?").

It ignores the ranking structure, it doesn't or care where in the result list a document will land.

**Pairwise**
Instead of absolute scores, the model learns _relative preferences_ ("document $A$ is better than document $B$ for query $q$").

This is a _binary classification problem_, a famous example is _RankNet_.

Still imperfect because _all pairs are treated equally_ (i.e. doesn't consider the graded relevance assigned to documents), but a pair at rank $1$ vs $2$ matters more for user experience than a pair at rank $900$ vs $901$.

**Listwise**
The model looks at the _whole ranked list at once_ and tries to optimize a ranking metric like NDCG@K directly.

This is the most principled approach but also the hardest, because [[08 - Evaluation metrics#NDCG Normalized DCG|NDCG]] depends on the sort order of scores, and _sort is not a continuous differentiable function_, so standard gradient descent can't be applied directly.

### BM25F
**BM25** is a classic BOW **ranking function** with two free parameters ($b, k$)

**BM25F** extends it to handle **multi-field documents** (e.g. web page that has: a title, URL, body text, ...), where each field deserves different weight.
$$\text{BM25F}(d,q)=\sum_t\text{IDF}_t\tau(F_t)\quad F_t+\sum_s\frac{w_s\cdot f_{t,s}}{1-b_s+b_s\cdot l_s/L_s}$$
- $w_s$: weight of field $s$
- $f_{t,s}$: frequency of term $t$ in field $s$
- $l_s$: length of field $s$ (of document $d$)
- $b_s$: determines the importance of $l_s$
- $L_s$: average length of field $s$ in the collection

BM25F has $2S + 1$ parameters where $S$ is the number of fields.
These parameters are **hard to set by hand**, which is where LtR comes in: we can fine-tune the parameters using a LtR model, optimizing them to maximize a metric like NDCG@10 on labeled training data.

The problem is that NDCG@K <u>cannot be directly optimized with gradient descent</u> (same issue from the listwise LtR).

A workaround is to use a [[06 - Ranking#Discounted Cumulative Gain at Rank|pairwise proxy loss]] (e.g. cross-entropy) or better approximations like [[06 - Ranking#LambdaMart algorithm|LambdaMART]], which approximates the NDCG gradient.

### Neural IR
So far we've seen:
- **BOW**: fast and practical, but blind to meaning, uses hand-crafted functions
- **LtR**: requires hand-crafted features

**Neural IR** tries to learn the features automatically (i.e. self-supervised) from raw text, with the goal of capturing semantic meaning beyond exact term matching.

A **Language Model (LM)** is an ML model that _predicts upcoming words_, formally, the probability of a sentence is decomposed using the **chain rule of probability**:
$$P(w_{1:n})=\prod_{k=1}^nP(w_k|w_{1:k-1})$$
That is: the probability of a sentence is the product of each word's probability given all the preceding words.
>LMs can also predict words in positions other than just the next one (given some context window).

#### N-gram models (pre-LLM approximation)
Computing $P(w_k|\text{ all previous words})$ is infeasible for long texts, since there are too many possible histories.
The classical solution is the **Markov approximation** which only looks at the last $N-1$ words:
$$P(w_{1:n})\approx\prod_{k=1}^nP(w_k|w_{k-1})$$
which approximates each word's probability using only the preceding word.

Probabilities are estimated by **Maximum Likelihood Estimation (MLE)** which consists into counting how often the bigram $(w_{n-1},w_n)$ appears relative to all bigrams starting with $w_{n-1}$:
$$P(w_n|w_{n-1})=\frac{C(w_{n-1}w_n)}{\sum_wC(w_{n-1}w)}$$
>[!Info]
>This was the standard before deep learning took over.

### Word representations
To use words in ML models, we need to encode them as vectors.
The naive approach is [[Feature selection & engineering#One-hot encoding|one-hot encoding]], the problem is that vocabulary-sized vectors are enormous, and the encoding captures **no similarity**.

The solution is then to **learn dense vectors** where semantically similar words have similar vectors.

The theoretical foundation is **distributed semantics**: a word's meaning is captured by the words that appear near it.
>"Car", "engine", "drive", "road" should have similar vectors.

### Word2Vec
Even though there are many words, the actual **number of distinct topics we talk about is low**, most of the information in a word's co-occurrence pattern can be captured in a **compact dense vector** without making them as large as the vocabulary size.

A **word's meaning** isn't stored in a single dimension, but spread across many dimensions simultaneously, in this way word similarity can be measured through standard vector operations.

The **Word2Vec** algorithm is what made neural word embeddings practical, it works as follows:
- We have a large corpus
- Every word in the vocabulary is represented by a vector
- We slide a window across the text, and at each position $t$, there is a _center word_ $c$ and _context words_ $o$ (surrounding words withing the window)
- The model learns vectors by trying to maximize $P(o|c)$, which is the probability of seeing each context word given center word

This is the **skip-gram** variant of Word2Vec, there is also the reverse which is called **CBOW (Continuous Bag of Words)**, which predicts the center word given the context.
>Skip-gram is preferred for learning quality embeddings.
![[Word2Vec.png|500]]

The model is simultaneously trying to assign high probability to all context words (given "into" in the example above), the window slides through the entire corpus, generating millions of such pairs automatically **without human labels needed**, this is what makes it **self-supervised**.

Word2Vec **trains a language model** (predicting context words), but the language model itself is **not the goal**, what we actually want are the **weights of the hidden layer**, those will become the word embeddings.

>[!Tip]
>The network learns to predict context words well only if it encodes meaningful word similarity into its weights, so <u>optimizing prediction quality forces the weights to become good embeddings</u>.

#### Word2Vec model
The neural network has the following structure:
- **Input**: one-hot vector of size $|L|$ (vocabulary size) representing the center word
- **Output**: vector of size $|L|$ giving, for every word in the vocabulary, the probability it's a nearby word of the input

The goal of Word2Vec is to find the parameter set $\theta$ that maximizes the probability of all observed (center, context) pairs across the entire corpus:
$$\arg\max_\theta\prod_{t=1}^T\prod_{\stackrel{-m\leq j\leq m}{j\neq0}}P(w_{t+j}|w_t;\theta)$$
- The outer product runs over all $T$ possible windows in the corpus
- The inner product runs over all context positions within the window of size $m$ (excluding $j=0$, which is the center word itself)
- $\theta$ represents all model parameters

Maximizing the probability is equivalent to minimizing the negative log-likelihood, that is, **cross-entropy loss**:
$$J(\theta)=-\frac{1}{T}\sum_{t=1}^T\sum_{\stackrel{-m\leq j\leq m}{j\neq0}}\log P(w_{t+j}|w_t;\theta)$$
>The minus sign turns maximization into minimization, and the $1/T$ normalizes by corpus size.

in order to compute $P(w_{t+j}|w_t;\theta)$ we will use two vectors per word $w$:
- $v_w$: when $w$ is a center word
- $u_w$: when $w$ is a center word

Then the probability of context word $o$ given center word $c$ is:
$$P(o|c)=\frac{\exp(u_o^Tv_c)}{\sum_{w\in V}\exp(u_w^Tv_c)}$$
This is a [[Layers#Funzioni di attivazione|softmax]] over the vocabulary, where the numerator measures the **similarity** between the center word and a context word vector, normalized across all words.

The neural network has **three layers**:
- **Input layer**: one-hot vector of size $|L|$
- **Hidden layer**: no activation function, just linear projection
- **Output layer**: $|L|$ neurons with _softmax_ activation, producing a probability over the whole vocabulary

A **forward pass** of the Word2Vec model looks like this:
![[Word2Vec forward pass.png|500]]
- $|L|$: vocabulary size
- $k$: embedding dimension (size of word vectors)
- $c$: one-hot vector for center word
- $V$: weight matrix (center word embeddings)
- $v^c$: the embedding of the center word (a single row of $V$)
- $U$: weight matrix (context word embeddings)
- $o$: resulting score vector over all vocabulary words
- $o'$: final output after softmax (a probability distribution)
- $u^o$: single row of $U$ (the context window for one word)

1. $c^T\times V=v^c$: multiply the one-hot vector by the center-word matrix $V$ to select the embedding of the center word
2. $v^c\times U^T=o$: multiply the center embedding against the context matrix $U$ to get raw similarity scores with every vocabulary word (this is what we ultimately want)
3. Softmax -> $o'$: normalize the scores into a probability distribution

All model parameters are stacked into **one long vector** $\theta$ of dimension $2\times d\times |L|$, which contains:
- All $v^c$ vectors (center embeddings for every word)
- All $u^o$ vectors (context embeddings for every word)

Note that every word has two vectors, and the reason for this is that, having **two embeddings** per word is convenient, since a word may appear as both a center word and a context word at the same time.

The update rule is the [[01 - Neural networks#Back-propagation|mini-batch gradient descent]] algorithm over a windows $t$ of the corpus:
$$\theta^{new}=\theta^{old}-\alpha\nabla_\theta J_t(\theta)$$

#### Optimizations
Word2Vec deals with many words making training expensive, to address this we can use some technique.

**Subsampling of frequent words**
Common words like "the," "a," "of" appear in almost every context but carry little meaningful information.
Word2Vec randomly discards some training examples involving frequent words, this speeds up training and improves quality by reducing the noise from meaningless co-occurrences.

**Negative Sampling**
The full softmax over the entire vocabulary is expensive (requires summing over all $|L|$ words for every training example), this technique sampling replaces this with the following task:

For each real (center, context) pair, randomly sample a few "negative" pairs (center, random word) and train the model to distinguish real pairs from fake ones.
This turns a $|L|$-class classification problem into a small binary classification problem, significantly reducing computation.

#### Word2Vec embeddings
At the end, words with similar contexts end up with similar vectors, and the model learns **synonyms** (e.g. "intelligent" and "smart") and **related concepts** (e.g. "engine" and "car").
![[Word2Vec embeddings.png|500]]

The analogy "king is to queen as man is to woman" should be encoded as:
$$\overrightarrow{king}-\overrightarrow{queen}=\overrightarrow{man}-\overrightarrow{woman}$$

### From word vectors to neural IR
Word embeddings give us a way out of the vocabulary mismatch problem.
Instead of exact term matching, now we compare **dense vector representations** of queries and documents.

Now, that we've solved the vocabulary mismatch problem, we still have to rank the retrieved results, for this there were initially two main _architectural families used for ranking_.

**Representation-based models**
Independently encode the query and each document into a single dense vector, then compute similarity between them.
Documents can be precomputed and indexed offline, making this suitable for _first-stage retrieval_ using _Approximate k-Nearest-Neighbor (AkNN)_ search.
>Fast but potentially less accurate.
![[Representation based models.png|500]]

**Interaction-based models**
Instead of reducing each side to one vector, these models explicitly <u>compute all pairwise similarities between query terms and document terms</u>, producing a _similarity matrix_ that captures term interactions.
It is then processed (e.g. with CNNs or RNNs) to produce a relevance score, this is more powerful, but _nothing can be precomputed_ since the query and document must be processed jointly, so these are used as _second-stage re-rankers_ on a smaller candidate set.
![[Interaction based models.png|500]]

### BERT
**BERT (Bidirectional Encoder Representations from Transformers)** is a large transformer-based language model that changed everything in IR.

Unlike Word2Vec (which gives each word a single fixed vector), BERT produces **contextualized representations**, the same word gets different vectors depending on its surrounding context.

The underlying architecture, is the [Transformer](https://en.wikipedia.org/wiki/Transformer_(deep_learning)).