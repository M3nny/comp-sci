Durante l'**analisi del linguaggio naturale** spetta a noi scegliere le features del testo, di seguito vediamo vari modi per interpretarlo.

## Set of words
Creiamo un insieme contenente tutte le parole presenti nel testo.

Prima di eseguire questa operazione è utile **normalizzarlo** (e.g. porre tutti i caratteri in lowercase), in questo modo parole con lo stesso significato ma scritte in modo diverso vengano rappresentate solo una volta all'interno dell'insieme.

L'**insieme delle features** è quindi formato dal **lexicon**, ogni parola sarà associata ad una feature binaria la quale indicherà la sua presenza o meno nel testo in questione.
```python
lexicon = set.union(*X_train_words) # * unpack iterable
```

Il metodo `fit` di [CountVectorizer](https://scikit-learn.org/1.5/modules/generated/sklearn.feature_extraction.text.CountVectorizer.html) con parametro `binary=True` impara il vocabolario dei testi presenti nel dataset, `transform` converte un testo in input in una **sparse matrix**, la quale indica per ogni parola (inclusa nel vocabolario imparato) se era presente o meno.

Ad esempio prendendo in considerazione i testi seguenti:
```python
X_train = [
    "I love my cat",
    "NaTuRaL   language processing!",
    "my cat does not understand my language",
]
```

applicare `fit_transform(X_train)` produrrà questa matrice:
![[Sparse matrix set of words.png]]

>Utilizziamo la _presenza_ (o meno) delle parole per allenare un modello.

## Bag of words
Funzione come un _set of words_, ma in questo caso teniamo in considerazione anche la frequenza di ogni parola, verrà quindi usato _CountVectorizer_, ma con il parametro `binary=False`.
![[Sparse matrix bag of words.png]]

>Utilizziamo la _frequenza_ delle parole per allenare un modello.

## TF-IDF
L'approccio **Term-Frequency e Inverse Document Frequency** ci consente di identificare le parole più generiche e di valutarle con uno score più basso.

La **term frequency** $tf(t)$ indica il numero di occorrenze di un termine.

La **inverse document frequency** approssima la _specificità_ di un termine all'interno di una data collezione di documenti definita come:
$$idf(t)=\ln\frac{N_{docs}}{df(t)}$$

Infine il peso di un termine è definito come $tf(d)\cdot idf(t)$.
![[Sparse matrix TF-IDF.png]]

>Utilizziamo la _frequenza inversa_ delle parole per allenare un modello.

#### Ulteriore text processing
Delle fasi tipiche per la **normalizzazione del testo** sono:
- **Stemming**: prevede la rimozione di prefissi e suffissi
	(e.g. `being -> be, was -> was`)
- **Lemming**: identifica l'origine di una parola
	(e.g. `being -> be, was -> be`)


---
## Naive Bayes
Ricordiamo che il [[Probabilità condizionata#Teorema di Bayes|teorema di Bayes]] è formulato come:
$$P(Y|X)=\frac{P(X|Y)P(Y)}{P(X)}$$

nell'ambito del machine learning, la questione diventa trovare $P(y|X)$, o in presenza di multiple classi $C_1,...,C_m$:
$$\arg\max_{C_i} P(C_i|X)$$
ovvero trovare l'indice della classe con probabilità di più alta di essere corretta.

Per rendere la computazione fattibile assumiamo che che le features siano [[Congiunte#Congiunte indipendenti|indipendenti]] tra loro, per cui:
$$P(X|C_i)=\prod_{j=1}^n P(x_j|C_i)$$
la predizione finale quindi (considerando il teorema di Bayes) è:
$$\arg\max_{C_i}P(C_i|X)=\left(\prod_{j=1}^n P(x_j|C_i)\right)\frac{P(C_i)}{P(X)}$$

In questo modo $P(x_j,C_i)$ può essere pre-computato dal dataset in due modi:
- **Multinomial Naive Bayes**: se la feature $f_j$ è **categorica**, allora $P(x_j|C_i)$ è il numero di istanze nel dataset di classe $C_i$ per cui la $j$-esima feature ha gli stessi valori di $X$, diviso per $|C_i|$, ovvero:
$$P(x_j|C_i)=\frac{\#\text{istanze di classe }C_i\text{ con }x_j=X}{|C_i|}$$

- **Gaussian Naive Bayes**: se la feature $f_j$ è **numerica**, allora assumiamo che essa abbia una [[Distribuzioni continue#Normale (o gaussiana)|distribuzione gaussiana]], per cui dopo aver calcolato la media $\mu$ e la deviazione standard $\sigma$ limitate alle istanze di classe $C_i$ otteniamo:
$$P(x_j|C_i)=\frac{1}{\sigma\sqrt{2\pi}}e^{-\frac{1}{2}\left(\frac{x_j-\mu}{\sigma}\right)^2}$$

I **classificatori bayesiani** sono classificatori statistici, predicono la probabilità di appartenenza ad una classe, essi <u>assumono che l'effetto del valore di un attributo di una data classe sia indipendente dai valori degli altri attributi</u>.

### Correzione di Laplace
Nel caso in cui durante la produttoria si abbia $P(x_j|C_i)=0$ il prodotto verrebbe completamente azzerato anche se i segnali provenienti dalle altre features erano forti.

La **correzione di Laplace** evita questo problema assumendo di osservare un'istanza aggiuntiva per ogni valore di feature:
$$P(x_j|C_i)=\frac{N_{ij}+1}{N_i+v}$$

- $N_{ij}$: $\#$istanze di classe $C_i$ con valore della $j$-esima feature uguale a $x_j$
- $N_i$: $\#$istanze di classe $C_i$
- $v$: $\#$valori unici per la feature $j$ nell'intero dataset

#### Considerazioni su naive Bayes
Nel caso in cui alcuni valori fossero **assenti** durante la fase di **training** si può semplicemente ignorare tale istanza, durante la fase di **testing** si può assumere che $P(x_j|C_i)$ sia uguale per ogni $C_i$.

La **complessità computazionale** è bassa.
Per evitare problemi di calcolo con numeri _floating point_ (e.g. [[Numeri razionali#Virgola mobile (floating point)|underflow]]) i quali possono portare a probabilità scorrette, si utilizza la somma dei logaritmi:
$$\log(P(C_i|X))=\prod_{i=1}^n\sum_{j=1}^m\log(P(x_j|C_i))$$

- È robusto a punti di rumore e ad attributi irrilevanti
- Gestisce valori mancanti
- L'assunzione di indipendenza potrebbe non valere per alcuni attributi
- Estremamente veloce in fase di training e testing, inoltre è facilmente interpretabile e possiede pochi parametri da gestire

