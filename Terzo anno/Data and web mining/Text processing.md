Durante l'**analisi del linguaggio naturale** spetta a noi scegliere le features del testo, di seguito vediamo vari modi per interpretarlo.

## Set of words
Creiamo un insieme contenente tutte le parole presenti nel testo.

Prima di eseguire questa operazione è utile **normalizzarlo** (e.g. porre tutti i caratteri in lowercase), in questo modo parole con lo stesso significato ma scritte in modo diverso verranno rappresentate solo una volta all'interno dell'insieme.

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

### Ulteriore text processing
Delle fasi tipiche per la **normalizzazione del testo** sono:
- **Stemming**: prevede la rimozione di prefissi e suffissi
	(e.g. `being -> be, was -> was`)
- **Lemming**: identifica l'origine di una parola
	(e.g. `being -> be, was -> be`)

