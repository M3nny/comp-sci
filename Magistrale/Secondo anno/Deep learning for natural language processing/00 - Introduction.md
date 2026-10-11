NLP is an **interdisciplinary field** bridging computer science, artificial intelligence, and linguistics to _enable machines to understand, interpret, and generate human language_.

**McLuhan** describes _media as an extension of human faculties_, in this case language models extend:
- Writing
- Interpretation
- Knowledge access
- Reasoning

They don't just transmit language, they take part in producing, organizing and evaluating it.
>This changes the speed of knowledge production, authorship and what people treat as credible.

### Why NLP is hard
- **Lexical ambiguity**: words have several meanings (e.g. bank as a financial institution or a river edge)
- **Syntactic ambiguity**: a sentence can be parsed in multiple ways (e.g. "I saw the man with the telescope")
- **Context dependence**: sarcasm, idioms, and cultural references require world knowledge beyond the text
- **Data sparsity**: English is resource-rich, but thousands of languages lack enough digitized corpora

### Core linguistic levels
Is it well formed (syntax)? What does it literally mean (semantics)? What does the speaker mean here (pragmatics)?

- **Syntax**: rules of word order and structure
- **Semantics**: literal meaning of words and how meanings combine
- **Pragmatics**: meaning that depends on context and speaker intent

### Evolution of NLP

| Era           | Period       | Key ideas                                                                    |
| ------------- | ------------ | ---------------------------------------------------------------------------- |
| Rule-based    | 1950-1980    | Hand-crafted rules, regular expressions, ELIZA, context-free grammars        |
| Statistical   | 1990–2010    | ML on large corpora: n-gram LM, TF-IDF, HMMs(POS tagging), SVM               |
| Deep learning | 2010         | Dense embeddings, RNNs/LSTMs addressing vanishing gradients                  |
| Transformers  | 2017–present | Self-attention, parallelization, massive scale, emergent zero-shot abilities |

**Milestones**:
- _2013_: word2vec gives dense embeddings
- _2014_: seq2seq encoder–decoder (RNN/LSTM)
- _2014–15_: attention lets the decoder select relevant encoder states, avoiding a single fixed-size vector
- _2015–16_: bidirectional RNN/LSTMs for tagging and parsing
  
- _2017_: the Transformer ("Attention Is All You Need").
	  Self-attention replaces recurrence, so each position attends directly to all others, this leads to parallel training, direct information flow between distant tokens without vanishing gradients, multi-head attention (several relationships and subspaces), and scalability to larger models and data.
  
- _2018_: contextual representations. ELMo shows a word’s representation should depend on its sentence (river bank $\neq$ investment bank), and BERT adds deep bidirectional Transformer pretraining plus fine-tuning
- _2018–20_: GPT, XLNet, RoBERTa, and T5 show pretraining transfers across tasks
- _2020_: GPT-3 shows in-context learning (zero-/few-shot prompting, no parameter updates)
  
- _2021–23_: instruction tuning and alignment (SFT, RLHF).
	  Foundation and open-weight models (PaLM, LLaMA, Falcon, Mistral) enable PEFT (e.g. LoRA), domain adaptation, and multilingual deployment.
- _2023–today_: retrieval-augmented systems, tool use, multimodality, reasoning, and agents

At the beginning of this chapter we gave an overlook of techniques used across the years, but how the "semantic" of the models has evolved?
1. **Static representations** (word2vec)
2. **Contextual representations** (ELMo, BERT)
3. **General pretrained models** (GPT, RoBERTa, XLNet, T5)
4. **Instruction-following systems** (instruction tuning and alignment)
5. **Reasoning and tool systems** (agentic AI)

### Classical NLP tasks
- **Pipeline steps**: tokenization, stemming/lemmatization, POS tagging, dependency parsing
- **Text classification**: sentiment analysis, spam detection
- **NER (sequence labeling)**: locates and classifies entities
- **Machine translation**: phrase-based statistical MT dominated the 2000s, then NMT with attention-guided seq2seq (encoder -> context vector -> decoder)
- **Summarization**: extractive (selects existing sentences, reliable but choppy) vs abstractive (generates new sentences, prone to _hallucination_, so it needs evaluation such as ROUGE and human oversight)
- **Question answering**: closed-book (relies on parametric knowledge, can be outdated) vs open-book _RAG_ (retrieve documents from an external database, then ground the LLM’s answer in them)
- **Conversational agents**: from intent classification with slot-filling to open-domain dialogue (ChatGPT-style) that keeps long context and handles topic switches
- **Multimodal NLP**: CLIP aligns text and images in one vector space, Whisper handles speech-to-text, and modern frontier models process text, audio, and vision in a single Transformer

### Agentic AI
An LLM acts as a reasoning engine to pursue complex goals over multiple steps. Traditional LLMs output text and stop, whereas **agents** plan, act in environments, observe results, and iterate, _using tools_.

The **core components** of this architecture are: models, reasoning, _memory and retrieval_, external tools, evaluation and safety.

The **cognitive architecture** involves _planning_ (chain-of-thought), _reflection_ (self-critique and correction), _memory_ (short-term context window and long-term vector databases).

### Ethics and safety
- **Bias and fairness**: models amplify _societal biases_ from their training data
- **Hallucination**: _confident false information_ is risky in medical, legal, and financial contexts
- **Alignment**: keeping capable models acting _in line with human values_ and avoiding harmful unintended goals (dual-use risks)