In this chapter we're going to discuss how can a computer capture the richness and graded nuance of meaning in a low-dimensional vector space.

There are two families of approaches to **meaning**:

|                | Symbolic (e.g. WordNet)                                              | Distributional (vector semantics)                                                             |
| -------------- | -------------------------------------------------------------------- | --------------------------------------------------------------------------------------------- |
| Representation | Discrete concepts (synsets) linked by explicit relations (e.g. is-a) | Dense continuous vectors learned from co-occurrence                                           |
| Strengths      | Explicit, interpretable relations, formal distinction of senses      | Learned automatically (self-supervised) from corpora, graded similarity as geometric distance |
| Limitations    | Needs massive manual curation; poor at graded similarity             | Merges all senses of a word into one vector, reproduces biases in the data                    |

There are various **design goals for a representation**, but no method satisfies all of them, so there are trade-offs:
- _Semantic similarity_: "cat" should be closer to "tiger" than to "table"
- _Contextual sensitivity_: distinguish "deposited money at the bank" from "the river bank", only contextualized models achieve this
- _Coverage and robustness_: meaningful vectors for rare, unseen or misspelled words (subword models help)
- _Scalability_: learn from billions of tokens and million-word vocabularies
- _Computational efficiency_: dense vectors of roughly 50 to 1000 dimensions, cheap to store and use

Before going forward we take a look at **lexical semantics**:
- _Lemma and senses_: a lemma is the dictionary form (e.g. go, goes, went -> go), senses are the distinct meanings of a lemma (e.g. bank as slope vs financial institution)
- _Synonymy_: pure synonymy is rare because of the <u>principle of contrast</u> (i.e. words nearly always differ in register, dialect or connotation)
- _Antonymy_: opposites along one dimension (hot/cold), which are hard for discrete lexicons to place
- _Meaning is graded, not binary_: SimLex-999 human ratings run from near-synonyms (e.g. vanish/disappear -> 9.80) through moderate overlap (e.g. belief/impression -> 5.95) and related-but-contrasting pairs (muscle/bone -> 3.65) down to nearly unrelated ones (hole/agreement -> 0.30)

### The Distributional Hypothesis
<u>Words occurring in similar contexts tend to have similar meanings</u>.
>This is the idea behind Wittgenstein's "the meaning of a word is its use in the language".

The **computational recipe** can be summarized as follows:
1. Observe the co-occurrence patterns of each target word
2. Build a representation (a distribution or a dense vector) from them
3. Compare words with a distance measure such as cosine
>Similar context distributions then give nearby points in a continuous semantic space.

### From discrete symbols to vectors

**Discrete identities**
In n-gram models and many classical systems, words are just arbitrary IDs (e.g. cat -> ID_412, tiger -> ID_719).

If we replace every word with a unique ID, consistently in training and test data, the model's behavior does not change.

**One-hot vectors**
A word is a vector in $\mathbb{R}^{|V|}$ with a 1 at its index and 0 elsewhere.
For two distinct words $i \neq j$:
$$w_i^\top w_j = \sum_k w_{i,k}\, w_{j,k} = 0 \quad\Rightarrow\quad \cos\theta = 0$$
So "motel" and "hotel" are exactly as unrelated as "motel" and "cat".

Dimensionality also grows linearly with the vocabulary (millions of dimensions), which means extreme sparsity and large memory costs, and the orthogonality blocks any statistical sharing between similar words.

**The word-context matrix**
Rows are target words, columns are context words, so $X$ has shape $|V_\text{target}| \times |V_\text{context}|$ (or $|V|\times|V|$ if the vocabularies are shared).

The entry $X_{ij}$ counts how often context word $j$ occurs near target word $i$.

>[!Example]
>With a window of $\pm2$ around the target "word" in "...models learn useful word representations quickly and...", the context words are "learn", "useful", "representations", "quickly", and each of their cells in the row for "word" is incremented by 1.

After the whole corpus is processed, row $x_i = [X_{i1}, \dots, X_{i|V_c|}]$ is the context profile of word $i$.

Words in similar contexts get similar rows, these vectors are high-dimensional and sparse.

#### Measuring similarity
**Dot product**
$$u \cdot v = \sum_k u_k v_k$$
It is high when two words share many contexts, but it is _biased by frequency_. 
Frequent words (e.g. the, and, is) co-occur with everything and have huge counts, so two frequent but unrelated words can score higher than two related rare words.

**Cosine similarity**
Divides out the vector lengths, keeping only direction:
$$\cos\theta = \frac{u\cdot v}{\lVert u\rVert\,\lVert v\rVert} = \frac{\sum_k u_k v_k}{\sqrt{\sum_k u_k^2}\;\sqrt{\sum_k v_k^2}}$$

- It projects all words onto the unit sphere, ignoring magnitude (frequency)
- Its range is $[-1, 1]$, and $[0, 1]$ for non-negative count vectors
- $\cos\theta = 1$ means identical context direction. $\cos\theta = 0$ means orthogonal (i.e. no shared contexts)

#### Problems with raw co-occurrence vectors
- **High dimensionality**: a 50,000-word vocabulary means 50,000-dimensional vectors, and a downstream linear layer needs a parameter per dimension
- **Sparsity and limited evidence**: most entries are zero, and rare words have few observed contexts, so their vectors are unreliable
- **Feature fragmentation** raw counts give frequent words longer vectors, and related contexts such as "car" and "automobile" sit on separate orthogonal dimensions

>We want shorter vectors that preserve contextual similarity.

### Sparse vs dense vectors

|Sparse count vector|Dense embedding|
|---|---|
|$x \in \mathbb{R}^{\lvert V\rvert}$, tens of thousands of dimensions|$e \in \mathbb{R}^{d}$, $d \ll \lvert V\rvert$ (typically 50 to 1000)|
|Mostly zeros|Mostly non-zero real numbers|
|Each dimension is interpretable (one context word)|Individual dimensions are not interpretable|
|Similarity via shared context counts|Similarity via distributed patterns|

There are two **routes to dense vectors**:
- **Dimensionality reduction (count-based)**: build a global co-occurrence matrix and factorize it, then it uses global statistics but is expensive for huge vocabularies
- **Prediction-based learning**: learn vectors directly by predicting context words, as in CBOW and skip-gram (i.e. [[11 - Learning to rank#Word2Vec|Word2Vec]]), it optimizes a local objective over a sliding window and avoids factorizing a giant matrix

### Word2Vec: CBOW and Skip-gram
Instead of counting contexts, we can predict them.

The embedding matrix falls out as a by-product of training a very small neural network, a word vector is a row of a weight matrix.

|                        | CBOW                                                | Skip-gram                                                          |
| ---------------------- | --------------------------------------------------- | ------------------------------------------------------------------ |
| Models                 | $P(w_t \mid C_t)$: context predicts the center word | $P(c \mid w_t)$: center word predicts each context word            |
| Context representation | Average of context vectors, so order is ignored     | Single center word                                                 |
| Training unit          | One prediction per center position (efficient)      | One example per (target, context) pair (more steps)                |
| Assumption             | none special                                        | Context predictions are conditionally independent given the target |
| Behavior               | Strong for frequent words                           | Better for infrequent words                                        |

Both learn **static embeddings**: one vector per word type, regardless of the sentence it appears in.

#### CBOW step by step
Let $V$ be the vocabulary size, $d$ the embedding dimension (typically 50 to 1000), $W \in \mathbb{R}^{|V|\times d}$ the input embedding matrix and $W' \in \mathbb{R}^{d\times|V|}$ the output matrix.

1. **Lookup**: retrieve embeddings of the context $C_t = \{w_{t-2}, w_{t-1}, w_{t+1}, w_{t+2}\}$
2. **Average**:  
    $$h_t = \frac{1}{|C_t|}\sum_{w\in C_t} v_w \in \mathbb{R}^d$$ This is the _bag-of-words assumption_: no order, no syntax, just a simple average.
3. **Scores (logits)**: $z_t = W'^\top h_t + b$, one raw score per vocabulary word
4. **Softmax:**  
    $$P(w_t \mid \text{context}) = \frac{\exp(z_{w_t})}{\sum_{j=1}^{|V|}\exp(z_j)}$$

**Maximize the likelihood** of the correct target word, equivalently **minimize the cross-entropy** (negative log-likelihood) over the whole sequence:
$$\mathcal{L} = -\sum_{t=1}^{T}\log P(w_t \mid \text{context}_t)$$

#### The softmax bottleneck and negative sampling
The softmax denominator sums over the entire vocabulary, so each training example costs $O(|V|)$, and with $|V| = 10^5$ to $10^6$ this is very expensive, and wasteful, because only one correct word matters.

The natural question is whether we really need to normalize over all words and the answer is no.

**Negative sampling**
We replace which word fits the context (multiclass) with "did this (context, word) pair come from the data?" (binary):
- **1 positive pair** (context, observed word) -> label 1
- **$k$ negative pairs** (context, randomly sampled word) -> label 0

Each pair is scored by a dot product and a sigmoid, and the model is trained with _binary cross-entropy_.

Only $k+1$ pairs are evaluated per step, so the cost drops from $O(|V|)$ to $O(k)$, with $k$ typically 5 to 20 and $k \ll |V|$.

For CBOW with negative sampling:
$$P(D=1 \mid w, \text{context}) = \sigma(v'_w \cdot h)$$
where $h$ is the averaged context vector and $v'_w$ is the output embedding of the candidate word.

>[!Attention]
>These binary outputs separate data from noise, they do not form a probability distribution over the vocabulary.


### Skip-gram with Negative Sampling (SGNS)
The **architecture** is defined as:
1. _Input_: one-hot vector of the center word
2. _Hidden layer_: a linear projection into embedding space
3. _Output_: softmax over the vocabulary to predict context words.
>SGNS replaces that output with the negative-sampling objective.

We keep **two matrices**, each word has two vectors, one per role:
- $W \in \mathbb{R}^{|V|\times d}$: input (center-word) embeddings, $v_w = W[w,:]$
- $W' \in \mathbb{R}^{d\times|V|}$: output (context-word) embeddings, $u_c = W'[:,c]$

Separate parameters let each role be optimized for its own function.
The score of a pair is $u_c^\top v_w$, and $P(\text{data pair}\mid w,c) = \sigma(u_c^\top v_w)$.
>After training, one usually keeps $e_w = v_w$, but we can use $u_w$ or the sum $v_w + u_w$.

**Objective**
For an observed pair $(w, c)$, sample $k$ noise words $n_1,\dots,n_k \sim P_n$:
$$J(w,c) = \log\sigma(u_c\cdot v_w) + \sum_{i=1}^{k}\log\sigma(-u_{n_i}\cdot v_w), \qquad \sigma(x) = \frac{1}{1+e^{-x}}$$
The loss to minimize is $L(w,c) = -J(w,c)$, and the corpus objective is $J_\text{corpus} = \sum_{(w,c)} J(w,c)$.

In words:
- _Positive term_: maximizing $\log\sigma(u_c\cdot v_w)$ pushes the dot product up for real co-occurrences
- _Negative term_: since $\sigma(-x) = 1-\sigma(x)$, maximizing $\log\sigma(-u_{n_i}\cdot v_w)$ pushes the dot product down for random pairs

**Noise distribution**
Negatives are sampled from a smoothed unigram distribution:
$$P_n(w) = \frac{\text{count}(w)^{3/4}}{\sum_x \text{count}(x)^{3/4}}$$
The exponent $3/4$ flattens the distribution, so frequent words dominate less and rare words are sampled more often.

---
### GloVe: unifying count-based and prediction-based

|Count-based (e.g. LSA/SVD)|Prediction-based (Word2Vec)|
|---|---|
|Factorizes global co-occurrence statistics|Learns iteratively from local windows|
|Stable, uses global statistics|Captures linear relational structure (analogies) very well|
|Weak on linear analogies; expensive for huge matrices|Does not directly exploit global statistics (re-processes local windows)|

**GloVe** learns dense vectors directly from global co-occurrence statistics while keeping the linear relational properties of Word2Vec.

### FastText: subword representations
Two **limitations of word-level embeddings** (e.g. Word2Vec, GloVe) are:
- _Out-of-vocabulary_ unseen words have no vector
- _Morphological isolation_: related words (e.g. transform, untransformable) share no parameters, which wastes statistical power

**FastText** extends skip-gram by representing each word as a **bag of character n-grams**.

With boundary markers and $n=3$, the word `where` becomes `<wh, whe, her, ere, re>`, plus the whole word token `<where>`.

With $G_w$ the set of subwords of $w$:
$$v_w = \sum_{g\in G_w} z_g$$
where each $z_g$ is a learned vector.

- Related words _share subword parameters_, and an unseen word can be built from its known n-grams, which resolves OOV.
- Character n-grams are _not necessarily linguistic morphemes_, since the model does not explicitly split prefixes, roots or suffixes

### Relational regularities and analogies
Some relations appear as roughly consistent **vector offsets**:
$$v_\text{king} - v_\text{man} \approx v_\text{queen} - v_\text{woman} \;\Rightarrow\; v_\text{king} - v_\text{man} + v_\text{woman} \approx v_\text{queen}$$
>The offset reflects a mixture of corpus regularities, not a pure "royalty" or "gender" concept.

**Analogy search**
$$q = v_B - v_A + v_C, \qquad D^* = \arg\max_{d\in V\setminus\{A,B,C\}} \cos(v_d, q)$$
The inputs A, B, C are excluded because they typically lie closest to $q$.

There are some **caveats**:
- _Selection artifacts_: without exclusions, the nearest vector is often an input or a morphological variant (e.g. `cherry : red = potato : ?` may return potato/potatoes rather than brown)
- _Uneven performance_: works better for frequent words, morphological relations and geographic relations (countries/capitals), and worse for semantic and encyclopedic relations (it depends heavily on corpus, vocabulary and search procedure)
- _Simplified relations_: one vector per word collapses polysemy, and a fixed offset struggles with context-dependent or non-linear relations, analogies are a useful diagnostic, not a model of human reasoning

### Embeddings visualization and evaluation
It is possible to **visualize** embeddings using various techniques to reduce their dimensions to a visible space of 2-3 dimensions:

|             | PCA                                               | t-SNE                                                                                                                        |
| ----------- | ------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| Idea        | Linear directions of greatest variance            | Matches pairwise-similarity distributions in high and low dimension by minimizing KL divergence                              |
| Strengths   | Deterministic, fast, keeps broad linear structure | Preserves local neighborhoods better                                                                                         |
| Limitations | A 2D linear projection can lose local structure   | Depends on initialization and perplexity, distances between clusters and cluster sizes are hard to interpret and can mislead |

We can **evaluate** how good embeddings are based on _intrinsic_ and _extrinsic_ evaluation:

|          | Intrinsic                                        | Extrinsic                                                       |
| -------- | ------------------------------------------------ | --------------------------------------------------------------- |
| What     | Measures the embedding space directly            | Measures the effect on a downstream system                      |
| Examples | Word similarity and word analogies               | NER, sentiment classification, POS tagging, machine translation |
| Pros     | Fast, cheap, good for geometric analysis         | Measures real practical utility                                 |
| Cons     | Out of context, may not predict real performance | Expensive, hard to isolate embedding quality                    |

### Social bias in embeddings
Embeddings learn associations from their corpora, so they can **reproduce and even amplify stereotypes**.

- **Representational harm**: the model encodes demeaning stereotypes (e.g. `man : computer programmer = woman : homemaker`
- **Allocational harm**: a system distributes opportunities or resources unfairly (e.g. a resume screener scoring candidates differently because of gendered language)

**Limits of linear debiasing**
Removing the projection onto a single "gender direction" from neutral words often does not remove the bias since _gender-associated neighborhood structure_ and relative distances remain, so classifiers and clustering can still recover the original biased configuration.