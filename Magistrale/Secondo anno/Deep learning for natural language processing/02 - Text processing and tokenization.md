A **corpus** is a structured collection of documents, possibly with _metadata_ such as labels, authorship, timestamps, and linguistic tags.
>The pipeline is: raw text -> tokenizer -> units -> neural network.

**Tokens vs types**
- A _token_ is one word occurrence, counted by $N$
- A _type_ is one distinct word form, counted by $|V|$

It always holds that $|V| \le N$, for example: "the cat chased the dog", $N = 5$ and $|V| = 4$.

The **vocabulary** is the set of all distinct tokens the model can recognize:
$$V = \{t_1, \dots, t_{|V|}\}$$
It is the interface between language and the model: token (string) -> token ID (integer) -> token representation (vector).

**Tokenization decisions are not trivial**
- _Capitalization_: should “They” and “they” be the same?
- _Contractions_: is “can’t” one token, or “can” + “n’t”?
- _Multi-word expressions_: is “New York” one token or two?
- _Punctuation_: keep or strip the period?
>Different choices give very different token and vocabulary counts.

**Word boundaries are language-dependent**, since English uses spaces, but Chinese has none.

The vocabulary is fixed, so unseen words cannot be represented, this is called the **Out-of-vocabulary (OOV) problem**.

**Vocabulary size trade-off**: a larger $|V|$ gives larger embedding and output-projection matrices but shorter sequences, while a smaller $|V|$ gives the opposite.

### Heaps' law and vocabulary growth
$$|V(N)| = k\,N^{\beta}, \qquad 0 < \beta < 1$$
- $N$ is the number of **observed tokens** and $|V(N)|$ the number of **distinct types**
- $k$ is a **scale parameter** that sets the overall vocabulary size, so a larger $k$ means more lexical diversity
- $\beta$ is the **growth exponent**, because $\beta < 1$, growth is _sublinear_

Growth has two phases: _early on it is roughly linear_ ($\beta \approx 1$), while function words are being exhausted, _later it flattens_ ($\beta \approx 0.44$ in the slide’s illustration).
>Function words appear early, later growth comes from rare content words, names, technical terms, and spelling variants.

**Vocabulary growth never stops**, so models will always meet unseen words.
This motivates open-vocabulary **subword tokenization** (e.g. BPE).
>For example, an unseen word like “lower” can be split into the known pieces “low” + “er”.

### Morphology
A **morpheme** is the minimal unit carrying lexical meaning or grammatical function.
>For example, re- (prefix) + play (root) + -ed (suffix).


- **Roots** supply core meaning,  _affixes_ add meaning or grammatical function.
- **Inflection** expresses grammatical information without creating a new lexeme, and is highly predictable (cat+s -> plural, walk+ed -> past)
- **Derivation** creates a new word, often changing category (careful+ly: adjective -> adverb; happy+ness: adjective -> noun).
- **Morphological typology** is a spectrum from fewer to more morphemes per word:
    - _Analytic/isolating_: about one morpheme per word, with grammar carried by word order and function words (Vietnamese, Cantonese)
    - _Synthetic_: a root combined with several affixes (Russian, Turkish, Latin)
    - _Polysynthetic_: one word expresses a whole clause (Greenlandic, Koryak, Chukchi)
>Because "word" complexity varies this much across languages, _word-level tokenization is highly uneven_.

### Evolution of tokenization units

| Era                                  | Model(s)                          | Unit                               | OOV handling  |
| ------------------------------------ | --------------------------------- | ---------------------------------- | ------------- |
| Static word embeddings (2013–2016) | Word2Vec                          | Whole words, one fixed vector each | None          |
| Morphological subwords (2016–2018) | fastText                          | Character n-grams                  | Partial       |
| Data-driven subwords (2016–2019)   | WordPiece/BPE (BERT)              | Learned subword units              | Yes           |
| Probabilistic subwords (2018–2020) | SentencePiece (Unigram LM), XLM-R | Subwords chosen by likelihood      | Yes           |
| Byte-level (2019–present)          | GPT-3/4, LLaMA, BLOOM, Claude     | UTF-8 bytes (0–255)                | Full coverage |

**fastText**
- Each word is wrapped in boundary markers (`<playing>`), and its character n-grams are extracted (typically $n = 3$ to $6$)
- The word vector is the sum of its n-gram vectors: $\mathbf{v}_{w} = \sum_{g \in G_w} \mathbf{z}_g$
- Words like play, played, playing, and player share parameters. Unseen words still get meaningful vectors
- fastText still feeds whole words to the model and gives a _static_ representation
- Modern subword tokenizers instead give each subword its own ID and position in the sequence, and Transformers produce _contextual_ representations

**WordPiece (used in BERT)**
- It starts from small units and grows the vocabulary by adding entries that maximize corpus likelihood, using an association score rather than raw frequency:
$$\text{score}(a,b) = \frac{\text{freq}(ab)}{\text{freq}(a)\times \text{freq}(b)}$$
- A pair scores high if it co-occurs often and its parts rarely appear elsewhere. For example, “q+u” can beat “t+h” even though “t+h” is more frequent, because “q” almost always appears with “u”
- _Encoding is greedy_ longest-match-first, left to right: “playing” → `play` + `##ing`, the `##` marks a continuation inside a word. It does not replay merge rules
- If a word cannot be covered, classic BERT outputs `[UNK]`

**Unigram LM (used in SentencePiece, ALBERT)**
- Each token $t$ has a probability $P(t)$, with $\sum_t P(t) = 1$. A segmentation $s$ scores $P(s) = \prod_{t \in s} P(t)$
- The segmentation is unknown during training, so the string probability sums over all segmentations: $P(x) = \sum_{s} P(s)$
- _Training_ works as follows:
    1. Start with an oversized candidate vocabulary
    2. Run EM. The E-step estimates segmentation contributions with $P(s \mid x) = P(s)/P(x)$, and the M-step updates $P(t)$ from expected counts
    3. Prune the tokens whose removal hurts corpus likelihood least
    4. Repeat until the target size is reached, always keeping base characters to avoid OOV
- _Encoding_ picks $s^* = \arg\max_s P(s)$, evaluating whole paths through a segmentation lattice instead of making local irreversible choices

**BPE (Byte-Pair Encoding)**
- _Training_ is bottom-up:
    1. Start from characters or bytes, with word frequencies.
    2. Count all adjacent pairs.
    3. Merge the most frequent pair into a new symbol.
    4. Repeat until the target vocabulary size is reached.
- _Encoding_ is deterministic. It applies the learned merges in priority order and computes no new frequencies, "playing" → `play` + `ing`.
>Merges normally stay inside pre-tokenized word regions, Byte-level BPE starts from UTF-8 byte values 0–255.

|                    | WordPiece                           | BPE                               | Unigram LM                                      |
| ------------------ | ----------------------------------- | --------------------------------- | ----------------------------------------------- |
| **Initialization** | Small set of units                  | Small set of units                | Large candidate vocabulary                      |
| **Learning**       | Add units by likelihood/association | Merge most frequent adjacent pair | Estimate probabilities, prune low-impact tokens |
| **Stored**         | Vocabulary                          | Vocabulary + ranked merges        | Vocabulary + token probabilities                |
| **Encoding**       | Greedy longest-match                | Apply merges in priority order    | Best path through lattice                       |
| **Examples**       | BERT                                | GPT-2, RoBERTa                    | SentencePiece, ALBERT                           |
| **Scope**          | Local greedy choice                 | Hierarchical merges               | Global path score                               |

### Character encoding
**ASCII** covers English letters, digits, basic punctuation, and control codes.

A **code point** is a numeric Unicode identity, a **grapheme cluster** is what users perceive as one character, possibly several code points (e.g. U+0065 + U+0301 → é), and a _glyph_ is the visual shape chosen by the font engine.

**UTF-8** is a variable-length serialization of Unicode into 1–4 bytes, the _pipeline_ is:
UTF-8 -> code points -> grapheme clusters -> glyphs.

**Unicode normalization**
Visually identical text can have different code-point sequences, without normalization, string comparison, vocabulary entries, token counts, and search can fail.

