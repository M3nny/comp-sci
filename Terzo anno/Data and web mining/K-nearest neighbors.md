# Introduzione
In questo corso lavoreremo con dati in forma tabellare, in particolare le righe definiscono un **oggetto**, mentre le colonne definiscono le sue **features**.

Possiamo definire un modello $M$ che prende in input un nuovo oggetto $x_i$ non presente nel dataset iniziale e ritorna una predizione $\hat y$ come:
$$M(x_i)\rightarrow \hat y$$

Un modello in questo campo può essere visto come una funzione che restituisce un output basandosi su una **conoscenza pregressa** acquisita da dati con lo stesso insieme di features.
Definiamo **supervised learning** l'apprendimento da un dataset che mette a disposizione le label $y$ di ogni record.
## Classificazione
Un task di **classificazione** consiste nell'assegnare una **label** appartenente ad un **insieme discreto** ad un oggetto passato in input.

Immaginiamo di avere un dataset di studenti laureati con features il voto ottenuto dai vari corsi universitari e con label $y$ indicante se hanno preso la lode o meno, vogliamo predire, date le features di uno studente (non presente nel dataset), la sua label di appartenenza, ovvero laureato con o senza lode.

Divideremo questo dataset in **training set** ($\sim70\%$) e **test set** ($\sim 30\%$).
>Le dimensioni dei set possono cambiare in base alla quantità di oggetti presenti nel dataset.

Per valutare la performance del modello allenato verrà usato il _test set_ (che contiene oggetti non presenti nel training set) assieme a delle **metriche** per valutarne l'**accuratezza** (percentuale di predizioni corrette effettuate nel test set).

>[!Tip] Selezione delle features
>Non sempre si avrà un dataset completo a disposizione, per questo sarà necessario definire delle features in grado di definire accuratamente un'istanza.

## Regressione
Un task di **regressione** consiste nel prevedere un valore numerico continuo.
La scelta della metrica di valutazione del modello è molto importante in quanto usare metriche come l'errore binario (assegna $0$ a predizioni sbagliate e $1$ a quelle giuste) non farebbe capire quanto il modello è accurato.

Avendo le seguenti predizioni dei modelli $M_1$ e $M_2$ ed il risultato atteso $y$ è possibile notare come $M_1$ risulti più accurato nel caso venisse usata una metrica che tiene conto dello scarto dal risultato atteso ($|y-\hat y|$) al posto di una metrica che considera solo se la predizione è completamente corretta.

| $M_1$                  | $M_2$                  | $y$   |
| ---------------------- | ---------------------- | ----- |
| $109$                  | $90$                   | $110$ |
| $99$                   | $90$                   | $100$ |
| $\text{Accuracy: 0\%}$ | $\text{Accuracy: 0\%}$ |       |

---
# K-nearest neighbors
I classificatori **nearest neighbors** sono definiti **lazy learners** in quanto non apprendono nulla durante la fase di training, ma si limitano solo ad eseguire una query su una base di dati (possibilmente indicizzata) durante la fase di inferenza.

La funzione del modello $M(x_i)$ infatti si limita ad eseguire una query su dati storici ed esegue una predizione in base alla somiglianza (e.g. [distanza euclidea](https://it.wikipedia.org/wiki/Distanza_euclidea)) del nuovo oggetto rispetto ai $K$ oggetti presenti nel dataset che più gli assomigliano.
#### Quale K scegliere
Solitamente è meglio scegliere un $K$ **dispari** in modo da non avere uguaglianze, tuttavia in caso di $K$ _pari_  e parità di vicini (e.g. $3$ blu $3$  verdi) si può procedere:
- Casualmente
- Considerando la classe con meno elementi globalmente (e.g. $90\%$ blu $10\%$ verdi), questo perchè sono rappresentato fortemente nei vicini in questione

Con $K$ **grande** oltre ad essere pesante in termini di computazione verrebbero preferite le classi con cardinalità maggiore (e.g. con $k=+\infty$ verrà sempre ritornata la classe più numerosa).

Con $K$ **piccolo** verrebbero valutati pochi oggetti storici presenti nel dataset, in questo modo si è più soggetti a punti di _rumore_.

Di seguito uno _scatter plot_ con _decision boundary_ avente $4$ classi differenti e $K=10$:
![[KNN.png]]
#### Normalizzazione delle features
Essendo che alcune metriche, come la distanza euclidea sono influenzate dalla scala di grandezza delle features, è necessario **normalizzare** le features tramite algoritmi appositi che fanno rientrare tutti i valori delle features in un range compreso tra $0$ e $1$ (e.g. [MinMaxScaler](https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.MinMaxScaler.html)).

Tuttavia <u>non va normalizzato l'intero dataset</u>, bensì si va a normalizzare _training set_ e _test set_ separatamente, altrimenti nella fase di training verrebbero rivelate informazioni del test set (**data leak**), rendendo poi il modello poco efficace in casi reali.