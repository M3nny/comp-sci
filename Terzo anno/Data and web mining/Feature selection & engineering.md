## Feature selection
Non sempre tutte le feature di un dataset sono utili, scartare feature irrilevanti potrebbe far aumentare l'accuracy del modello assieme alla sua performance.

Un set di feature più piccolo <u>riduce il rischio di correlazione casuale</u>, e <u>riduce l'errore di generalizzazione</u> del modello.

L'algoritmo che ci assicura di trovare la miglior combinazione di features è quello che prova tutte le combinazione, tuttavia per dataset di modeste dimensione è già impraticabile in quanto dovrà considerare $2^d$ sottoinsiemi, dove $d$ è il numero totale di features.
Utilizziamo quindi tre approcci in particolare per selezionare le features rilevanti.

### Filter
Questo approccio seleziona le feature ancora prima eseguire un modello qualsiasi, il metodo di **filtering** può essere completamente indipendente dal futuro modello, ad esempio si possono rimuovere le features con **bassa correlazione** rispetto alla label, oppure rimuovere features che sono altamente correlate tra loro (ridondanti).
### Wrapper
In questo approccio le feature sono selezionate in base alla loro **contribuzione**, ovvero quanto migliora l'accuracy dell'algoritmo usando o meno la feature in questione.

Distinguiamo due metodi:
- **Sequential forward selection**: si fa crescere un insieme di feature inizialmente vuoto
- **Sequential backward selection**: si parte con l'insieme contenente tutte le features e si vanno a togliere man mano feature meno rilevanti

L'algoritmo si ferma quando un criterio di stop è raggiunto (e.g. numero desiderato di features, il miglioramento del modello è piccolo).

Questo è un algoritmo [[Algoritmi greedy|greedy]], tuttavia è sempre meglio che considerare tutte le combinazioni.

### Embedded on feature importance
Con **importanza delle features** ci riferiamo ad uno **score** che un modello ha assegnato ad una feature, dove tale score è proporzionale alla contribuzione della feature nel modello allenato.

In un [[Decision trees|albero decisionale]] è facile computare la contribuzione, essa rappresenta la riduzione di errore durante la selezione del miglior split.
>Tale errore può essere accumulato per i vari split nei vari alberi in una [[Ensemble methods#Random forest|random forest]].

>[!Info] Feature importance in sklearn
>In sklearn l'importanza delle features è calcolata sulla base dell'impurità (e.g. [[Decision trees#Information gain (entropy)|entropia]], [[Decision trees#Gini index|Gini]]), per poi essere normalizzate così da avere somma pari a $1$.

Con questo approccio viene quindi sfruttata la conoscenza che un modello ha acquisito durante il training, per questo esso deve essere "aperto" e deve esporre l'importanza che esso ha dato alle features.

Questo approccio può essere eseguito con qualsiasi modello, solitamente però si usa un modello veloce da allenare per selezionare le features, poi il modello effettivo che verrà utilizzato per fare predizioni reali potrebbe essere molto complicato (per questo non può essere lui a fare questo lavoro iterativo di feature selection).

#### Eliminazione ricorsiva
Con questo approccio **eliminiamo** dopo ogni allenamento una o più **features** con **bassa importanza**.

Se abbiamo due (o più)  feature simili la loro importanza sarebbe spalmata, eliminando man mano le features meno importanti si cerca di eliminare una delle feature simili facendo aumentare l'importanza dell'altra.

---
## Feature engineering
Vediamo di seguito alcune strategie per affrontare problemi comuni nei dataset.

>[!Attention]
>Prima di effettuare qualsiasi modifica il dataset va diviso in **train** e **test**, lo stesso preprocessing dovrà essere applicato per entrambi i subset.

- **Features categoriche binarie**
	Vanno mappate le categorie in $0$ e $1$.

- **Features categoriche k-arie**
	Viene utilizzato il **one-hot-encoding (1HE)**, ovvero per ogni categoria viene creata una nuova colonna con valori binari per indicare se tale istanza appartiene a tale categoria.

- **Features con valori unici**
	Sono features che non apportano espressività al modello e dovrebbero essere eliminate.

- **Valori mancanti**
	I valori mancanti vengono sostituiti con la moda/media dei valori di tale feature, e viene aggiunta una nuova feature binaria che indica se tale valore è "vero" oppure è il risultato della moda/media (inizialmente mancava).

>Nota che la moda/media usata per sostituire i valori nel training set viene salvata, e sarà poi usata anche per sostituire i valori nel test set, altrimenti in un test set con una sola istanza non sarebbe possibile applicare moda/media a valori assenti.

### One-hot encoding
Con il 1HE, abbiamo detto che per ogni categoria viene creata una nuova colonna binaria per rappresentarla, ad esempio:

| Color  |
| :----: |
|  Red   |
| Green  |
| Yellow |
| Green  |

diventerà:

| Red | Green | Yellow |
| :-: | :---: | :----: |
|  1  |   0   |   0    |
|  0  |   1   |   0    |
|  0  |   0   |   1    |
|  0  |   1   |   0    |

Con questo tipo di encoding <u>il numero di colonne potrebbe esplodere</u> causando problemi di performance durante il training.

Se i valori categorici (discreti) dovessero essere molti, allora si potrebbe utilizzare il 1HE solo per i $k$ valori più frequenti, un modo per applicare questa strategia è rimpiazzare i valori meno frequenti con "other" e poi applicare il 1HE.

#### Baseline
È buona norma includere nelle analisi una **baseline**, ovvero l'accuratezza di un modello banale, ad esempio predicendo sempre la classe più numerosa.

### Misure di accuratezza
L'**accuratezza** è identificata come la frazione di istanze correttamente classificate.

Specialmente con dati non bilanciati l'accuratezza potrebbe non essere la misura migliore, per cui possiamo utilizzare misure differenti per ogni classe, vediamo di seguito misure comuni:

$$\text{Precision}=\frac{\#\text{ istanze correttamente classificate come }c}{\#\text{ istanze predette come classe }c}$$

$$\text{Recall}=\frac{\#\text{ istanze correttamente classificate come }c}{\#\text{ istanze con label effettiva }c}$$

$$\text{F-measure}=\frac{2\times\text{Precision}\times\text{Recall}}{\text{Precision+Recall}}$$

$$F_\beta\text{ weighted F-measure}=\frac{(1+\beta^2)\times\text{Precision}\times\text{Recall}}{\beta^2\times\text{Precision+Recall}}$$

Nell'$F_\beta\text{ weighted F-measure}$ stiamo considerando $\text{recall}$, $\beta$ volte più importante di $\text{precision}$.

Per qualsiasi tipo di misura siamo interessati alla **media**, esistono due metodi principali per calcolarla:
- **Macro**: le statistiche sono calcolate indipendentemente per ogni classe e poi la loro media viene estratta
	macro-recall ad esempio, è la media dei valori di recall misurata per ogni singola classe.

- **Weighted**: come _macro_, ma pesata sulla dimensione della classe (support)
	Le classi con più istanze hanno un impatto più grande sulla misurazione finale.

La **matrice di confusione** restituisce una tabella rappresentante l'accuratezza di classificazione per ogni classe.
Le righe rappresentano i valori effettivi, mentre le colonne rappresentano i valori predetti.

Da questo [dataset](http://archive.ics.uci.edu/dataset/102/thyroid+disease) utilizzando un decision tree, otteniamo la seguente _confusion matrix_:
![[Confusion matrix.png]]

### Cost-sensitive learning
Un'opzione interessante da utilizzare quando posti davanti ad un dataset con classi sovrarappresentate, che quindi "nascondono" le altre classi, è quella di utilizzare un sistema di **pesi**.

L'idea è quella di dare un peso diverso alla ricompensa/penalità derivata dalla classificazione durante il training, e quindi non un semplice $\pm1$.

Molti modelli di sklearn (e.g. [DecisionTreeClassifier](https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeClassifier.html)) supportano un dizionario di pesi come parametro aggiuntivo al modello, si vuole quindi andare a dare un peso maggiore alle classi sottorappresentate, ed un peso minore alle classi che compaiono più spesso.

---
## Valutare un classificatore binario
Valutare la bontà di un modello di classificazione binaria è molto più semplice di valutarne uno multi-classe.

Il modello durante la fase di inferenza ritornerà due probabilità, ovvero una per la prima classe ed un'altra per la seconda, la predizione del modello sarà data secondo un **threshold**, solitamente se la probabilità di una classe è $>0.5$, allora si predice tale classe.

|                  |              |                 | Predicted Label |
| ---------------- | ------------ | --------------- | --------------- |
|                  |              | **Negative**    | **Positive**    |
| **Actual Label** | **Negative** | True Negatives  | False Positives |
|                  | **Positive** | False Negatives | True Positives  |

Alcune misure interessanti sono:
$$\text{True Negative Rate}=\frac{\#\text{ True Negatives}}{\#\text{ Total Negatives}}$$
Il $\text{True Negative Rate}$, detto anche **specificità**, è importante in casi in cui si vuole essere sicuri del risultato della predizione (e.g. frode/non frode).

$$\text{True Positive Rate}=\frac{\#\text{ True Positives}}{\#\text{ Total Positives}}$$
Il $\text{True Positive Rate}$ è la stessa cosa del **recall**.

$$\text{False Positive Rate}=\frac{\#\text{ False Positives}}{\#\text{ Total Negatives}}$$

### ROC curves
Le **Receiver Operating Characteristic (ROC) curves**, di un modello mostrano il **trade-off** tra il _true positive rate_ (TPR) ed il _false positive rate_ (FPR).

Solitamente si può tollerare un FPR più largo per ottenere un TPR più alto (i.e. una recall più alta).

Ricordando che il classificatore binario solitamente utilizza un _threshold_ pari a $0.5$ per predire la classe, la _ROC curve_ è un grafico del TPR e FPR a confronto, dove ogni punto corrisponde alla coppia $(FPR,TPR)$ per un threshold diverso.
>Con threshold pari a $1$, FPR va a $0$, mentre se è pari a $0$, TPR va a $1$.

Il concetto di **Area Under the Curve (AUC)** è semplicemente l'area sottostante la ROC curve, ovvero un valore che misura la capacità del modello di distinguere tra le due classi.
- $AUC=1$: perfetta separazione tra le classi
- $AUC=0.5$: prestazioni casuali

L'AUC può essere visto come la probabilità che il modello assegni un punteggi più alto ad un esempio positivo rispetto ad un negativo.
![[ROC AUC.png]]