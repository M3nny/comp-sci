A **language model (LM)** assigns _probabilities to sequences of tokens_, and it also can:
- _Score whole sequences_: "the cat sat on the mat" gets a higher probability than "The cat sat on the democracy"
- _Predict the next token_: it outputs a distribution $P(w_i \mid w_1, \dots, w_{i-1})$ over the vocabulary
- _Generate text_: sample a token, append it to the context, and repeat

The **joint probability of a sequence** is:
$$P(W) = P(w_1, \dots, w_n)$$
The **chain rule** decomposes the joint probability into conditionals, _each conditioned on the full history_:

$$P(w_1,\dots,w_n) = \prod_{i=1}^{n} P(w_i \mid w_1,\dots,w_{i-1})$$
Full histories are _too sparse to estimate_, so the **Markov assumption** keeps only a _window_ of $n-1$ previous words:
- **Bigram** (first-order Markov): $P(w_i \mid w_1,\dots,w_{i-1}) \approx P(w_i \mid w_{i-1})$
- **Trigram** (second-order Markov): $P(w_i \mid w_1,\dots,w_{i-1}) \approx P(w_i \mid w_{i-2}, w_{i-1})$

### Parameter estimation with MLE
The [[02 - Point and interval estimation#Maximum likelihood estimator|MLE]] is the relative frequency of a continuation after a history $h$:
$$P_{\text{MLE}}(w \mid h) = \frac{C(h,w)}{C(h)}, \qquad C(h)=\sum_{w\in V} C(h,w), \qquad \sum_{w \in V} P_{\text{MLE}}(w\mid h)=1$$
>$C(h)$: total occurrences of history $h$.
>$C(h,w)$: occurrences of word $w$ after history $h$.

For _bigrams_:
$$P_{\text{MLE}}(w_i \mid w_{i-1}) = \dfrac{C(w_{i-1}, w_i)}{C(w_{i-1})}$$

>[!Example]
>If "natural language" occurs $100$ times, followed by "processing" $60$ times, "understanding" $25$ times and other words $15$ times, the probabilities are $0.60$, $0.25$ and $0.15$

### Preparing text for an n-gram model
The **preprocessing pipeline** works as follows:
1. _Segment_ sentences
2. _Normalize_ (case, Unicode, punctuation)
3. _Tokenize_
4. _Define a vocabulary_, mapping rare words to `<UNK>`
5. Add _boundary tokens_

An example of special tokens (depends on the tokenizer) could be:
- `<s>` marks the start of a sentence
- `</s>` marks the end and stops generation
- `<UNK>` stands for out-of-vocabulary words

>[!Example]
>"i like nlp" and "i like language":
>- $P(\text{i} \mid \texttt{<s>}) = 2/2 = 1.0$
>- $P(\text{nlp} \mid \text{like}) = P(\text{language} \mid \text{like}) = 1/2 = 0.5$
>- $P(\texttt{</s>} \mid \text{nlp}) = 1.0$
>
>>A trigram model needs two start tokens (`<s> <s>`) to provide a two-word history.

### Effects of increasing $n$

| Model   | Context | Typical behaviour                                 |
| ------- | ------- | ------------------------------------------------- |
| Unigram | 0 words | Right vocabulary, no coherent word order          |
| Bigram  | 1 word  | Locally plausible pairs                           |
| Trigram | 2 words | Recognizable phrases, local syntax                |
| 4-gram  | 3 words | Fluent local sequences, sometimes copied verbatim |

The **core trade-off** is that _more context improves local coherence_, but the number of possible _n-grams grows as $|V|^n$, so most are never observed_, this causes **sparsity and a risk of memorization**.

### Dependence on the corpus
Models learn the **style and vocabulary** of their training data,r this means that **performance drops** when the training distribution differs from the test distribution.

**Remedies** include training on legal documents, _QA pairs_, or relevant dialects, in addition **subword tokenization** (e.g. Jurafsky -> Jura + ##f + ##sky) _fixes vocabulary coverage only_, it _does not fix mismatches in topic_, genre, dialect or style.
>More context cannot compensate for a severe domain mismatch.

### Text generation
Using the **Shannon's sampling method** we can generate text as follows:
1. Start with `<s>`
2. Sample $w_1 \sim P(w \mid \texttt{<s>})$
3. Sample $w_2 \sim P(w \mid w_1)$
4. Repeat, sampling $w_i \sim P(w \mid w_{i-1})$ until `</s>` is generated

This lets us inspect what the model has actually learned about language structure.

### Evaluation
We can evaluate a model using two approaches:
- **Intrinsic**: measure the LM directly on a held-out test set, usually with perplexity (measures how well a LM predicts a sample of text), it is fast and automatic, but may not correlate perfectly with downstream performance
- **Extrinsic**: plug the LM into an application such as speech recognition or machine translation, it measures real impact, but is slow, expensive, and needs a full pipeline

Multiplying many small probabilities causes _numerical underflow_, so computation is done in log space:
$$\log P(w_1,\dots,w_T) = \sum_{i=1}^{T} \log P(w_i \mid h_i)$$

#### Cross-entropy and perplexity
With $q$ the model’s distribution:
$$\hat H(q) = -\frac{1}{T}\sum_{t=1}^{T} \log q(w_t \mid w_{<t}), \qquad PP(q) = e^{\hat H(q)} \;\; (\text{or } 2^{\hat H(q)})$$
**Perplexity** ($PP$) is the exponentiated average negative log-likelihood.
>Natural logs give cross-entropy in nats, and base-2 logs give bits.

_Lower perplexity is better_, it links directly to the cross-entropy training loss, an equivalent form is $PP(T) = P(T)^{-1/N}$, which can be read as the **effective branching factor**.

>[!Example]
>Vocabulary {red, blue, green}, test sequence “red red red red blue”):
>- Model A (uniform, 1/3 each): $PP = \left[(1/3)^5\right]^{-1/5} = 3.00$.
>- Model B ($P(\text{red})=0.8$, others 0.1): $PP = (0.8^4 \cdot 0.1)^{-1/5} \approx 1.89$.
>- Model B is less “surprised” because it concentrates probability on what actually occurs.
>
>>More context sharply lowers perplexity.

#### Out-of-vocabulary words
No training corpus can contain all words, unseen words at test time cause zero probabilities.

The **standard strategy** is to:
- Fix the vocabulary in advance (e.g. the top 50,000 words)
- Map every other word to `<UNK>` in both training and test data
- Estimate $P$(`<UNK>`) from counts like any other word

A modern alternative is _subword tokenization_ (BPE), which avoids OOVs entirely.

If $C(h,w)=0$, then $P_{\text{MLE}}(w\mid h)=0$, a single zero factor makes the whole sentence probability 0, so test-set perplexity becomes $\infty$.

An n-gram can be missing simply because the corpus is finite, not because it is ungrammatical, a solution for this problem is **smoothing** which takes probability mass from frequent events and redistributes it to unseen ones.

A standard smoothing strategy is the **add-one (Laplace)** which is defined as:
$$P_{\text{Lap}}(w_i \mid w_{i-1}) = \frac{C(w_{i-1},w_i)+1}{C(w_{i-1})+V}$$
Adding $V$ to the denominator keeps the distribution normalized.

>[!Example]
>$V=1446$: $P(\text{to}\mid\text{want})$ drops from $608/927 \approx 0.66$ to $609/(927+1446) \approx 0.26$.

Add-one _shifts far too much mass_ to unseen bigrams, this occurs because we add 1 to all of the 1.4 million unseen bigrams in the corpus, which accumulates massive
probability mass.

Instead of adding 1 we can add a **fractional hyperparameter $k$** (e.g. 0.5, 0.01):
$$P_{\text{add-}k}(w_i \mid w_{i-1}) = \frac{C(w_{i-1},w_i)+k}{C(w_{i-1})+kV}$$
It moves less mass than add-one, but it still performs poorly on web-scale text, and also, it _treats all unseen events equally_.

Sometimes we have no counts for a bigram, but we have **good unigram counts**, we should exploit this hierarchy.

We can use **lower-order n-grams**: the context–evidence trade-off is that low orders have _reliable counts but little context_, while high orders have _rich context but sparse counts_, for this reason we introduce two models:
- **Backoff**: use the trigram if it has counts, otherwise fall back to the bigram, then the unigram
- **Interpolation**: always mix all orders, interpolation generally outperforms backoff because it always uses lower-order information

Interpolation works as follows:
$$P_{\text{interp}}(w_i \mid w_{i-2},w_{i-1}) = \lambda_1 P(w_i \mid w_{i-2},w_{i-1}) + \lambda_2 P(w_i \mid w_{i-1}) + \lambda_3 P(w_i)$$
>With $\sum_j \lambda_j = 1$ and $\lambda_j \ge 0$.

The $\lambda$s are tuned on the dev dataset to _maximize likelihood_, in addition standard interpolation uses _one global weight per order_.

**Context-conditioned interpolation** uses weights $\lambda_k(h)$ that depend on how reliable each history is.

### Limitations and the move to neural LMs
The first limitation is due to **sparsity**, in fact parameters grow exponentially with $n$, so long-range context ($n>5$) is impractical, and also there is **no semantic similarity**, words are one-hot vectors (high-dimensional, orthogonal), so "cat" and "kitten" share no parameters.

The solution is to move to **neural LMs** (feedforward, recurrent, transformers) which represent words as _dense continuous vectors_ (e.g. $d=100$-$300$) in which similar words are close.
>This addresses both limits.

