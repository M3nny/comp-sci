**Deep learning** is a subset of machine learning that uses **multilayered neural networks** to simulate _complex decision making_ of the human brain.

**Natural Language Processing (NLP)** is an interdisciplinary subfield of computer science and artificial intelligence which focuses on <u>providing computers with the ability to process data encoded in natural language</u>.

NLP has its roots in the 1940s especially due to machine translations needs after WW2.
The **Turing test** introduced the task of the automated interpretation and generation of natural language.

>[!Note] Turing test
>A man, closed in a room, asks questions, trough a remote keyboard to a computer.
>If the man doesn't understands if on the other side of the room the answers are provided by a human or a computer, then we are in presence of a "intelligent computer".


![[NLP history.png|500]]

### Symbolic NLP
Up until the 1980s, most NLP systems were based on **complex sets of hand-written rules**.

The _premise of this technique_ can be summarized by the **Chinese room argument**: given a collection of rules (e.g. a Chinese phrasebook, with questions and matching answers), the computer emulates natural language understanding by applying those rules to the data it confronts.

The **Georgetown experiment** consisted in translating 70 sentences from English to Russian using six grammar rules and 250 lexical items, the authors then, claimed that withing 3-5 years, machine translation could well be a solved problem (it wasn't, funding collapsed).

**SHRDLU** and **ELIZA** were landmark 1960s programs:
- SHRDLU manipulated blocks in a simulated world via natural-language commands
- ELIZA simulated a psychotherapist using pattern matching

Then there was **HPSG** (Head-Driven Phrase Structure Grammar) which is a rule-based grammar formalism from the 1980s.

### Statistical NLP
In the late 1970s there was a revolution in NLP with the introduction of **machine learning algorithms**.
This was allowed by more compute power and moving away from the purely theoretical Chomskyan grammar toward _corpus-based learning_.

**IBM alignment models** pioneered statistical machine translation, trained on large _parallel corpora_, notably the bilingual proceedings of the Canadian parliament and the EU, which are legally required to be translated into all official languages, making them ideal training data.

**Statistical language modeling** introduces the core idea of a language model as something assigning probabilities to word sequences, for example:
$$P(\text{Colosseo}|\text{Rome})>P(\text{Colosseo}|\text{Paris})$$

### Neural NLP
In 2003 a **small neural probabilistic language model** (MLP) outperformed n-gram models (at the time the best statistical algorithms).

In 2010 a [[04 - Deep learning#Recurrent neural networks|recurrent neural network]] was applied to language modelling, later creating [[11 - Learning to rank#Word2Vec|Word2Vec]].

Then progression continues to **contextualized embeddings** (e.g. BERT) thanks to the **Transformer architecture**.

[On the Dangers of Stochastic Parrots](https://dl.acm.org/doi/epdf/10.1145/3442188.3445922) critiques large language models for fluently reproducing patterns without genuine understanding, which is a counterpoint to the neural-NLP triumphalism in these recent times.

### NLP as an empirical science
The evaluation of NLP models is **task-driven**.

The steps usually conducted to evaluate a model are:
1. Identify or create training data for the task
2. Select one or more benchmarks for the evaluation
3. Identify state-of-the-art models for the task
4. Compute metrics on the benchmarks
5. Compare the results

### NLP task taxonomy
**Text and speech processing** consist in _OCR_ (+ OCR post-correction), _speech recognition_ and _text-to-speech_.

The **NLP pipeline** is organized in the following way.

**Morphology**: word formation
_Lemmatization_ and _morphological segmentation_ (splitting words into morphemes, e.g. "unhappiness" -> un+happy+ness).

**Syntax**: how words combine
_Part of Speech (POS) tagging_ (labeling each word's grammatical category) and _syntactic parsing_ represented by its grammatical structure and defined by the relationships between"head" words and words, which modify those heads.

**Semantics**: meaning
_Lexical semantics_ (data-derived word meaning), _word sense disambiguation_ (based on context), _named entity recognition_ (e.g. "monday" -> "date"), _entity linking_ (association between entity and a knowledge base).

_Semantic role labeling_ which consists in who did what to whom, when, and where:
![[Semantic role labeling.png|400]]


Other tasks consist in:
- _Semantic parsing_: converts human language into a machine-readable form
- _Topic modeling_: discover hidden, abstract themes (topics) within a large collection of unstructured documents
- _Sentiment analysis_
- _Language identification_

**Higher-level applications** consist in:
- _Machine translation_
- _Text summarization_
- _Natural language generation_
- _Conversational agents_

### Framing NLP as a field
**NLP is more engineering-oriented**, whilst **computational linguistics** leans more toward using computation to study language scientifically.
>Though the line is blurry and the terms overlap heavily in practice.

The **goal of NLP** can be reframed as three processes:
- _Analysis_: language -> structured representation
- _Generation_: representation -> language
- _Acquisition_: learning the representations/algorithms from data

![[levels of linguistic representation.png|400]]
Deeper levels are harder and more **context-dependent**.

**NLP is hard** since there are _complex mappings between levels_, representation choice depends on application, noisy input, representations are theoretical constructs (not directly observable), and pervasive _ambiguity at every level_ (which we resolve easily via context, but computers struggle with).

**Pragmatics/Discourse** study how meaning depends on context beyond the sentence, and structure across multi-sentence/dialogue units.

This course will focus from morphology up to semantics.

### Learning paradigms
- **Supervised learning**: labeled $(X, Y)$ pairs
- **Self-supervised learning**: labels are auto-generated from raw text itself
- **Transfer learning**: pretrain self-supervised on huge data, then fine-tune on a small labeled dataset for a specific task
- **Prompt-based learning**: pretrain, then just prompt the model in natural language to perform a task with no further training, this is the paradigm behind modern LLM usage (few-shot/zero-shot prompting)

