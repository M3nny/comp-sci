Non sempre tutte le feature di un dataset sono utili, scartare feature irrilevanti potrebbe far aumentare l'accuracy del modello assieme alla sua performance.

Un set di feature più piccolo <u>riduce il rischio di correlazione casuale</u>, e <u>riduce l'errore di generalizzazione</u> del modello.

L'algoritmo che ci assicura di trovare la miglior combinazione di features è quello che prova tutte le combinazione, tuttavia per dataset di modeste dimensione è già impraticabile in quanto dovrà considerare $2^d$ sottoinsiemi, dove $d$ è il numero totale di features.
Utilizziamo quindi tre approcci in particolare per selezionare le features rilevanti.

## Filter
Questo approccio seleziona le feature ancora prima eseguire un modello qualsiasi, il metodo di **filtering** può essere completamente indipendente dal futuro modello, ad esempio si possono rimuovere le features con **bassa correlazione** rispetto alla label, oppure rimuovere features che sono altamente correlate tra loro (ridondanti).
## Wrapper
In questo approccio le feature sono selezionate in base alla loro **contribuzione**, ovvero quanto migliora l'accuracy dell'algoritmo usando o meno la feature in questione.

Distinguiamo due metodi:
- **Sequential forward selection**: si fa crescere un insieme di feature inizialmente vuoto
- **Sequential backward selection**: si parte con l'insieme contenente tutte le features e si vanno a togliere man mano feature meno rilevanti

L'algoritmo si ferma quando un criterio di stop è raggiunto (e.g. numero desiderato di features, il miglioramento del modello è piccolo).

Questo è un algoritmo [[Algoritmi greedy|greedy]], tuttavia è sempre meglio che considerare tutte le combinazioni.

## Embedded on feature importance
Con **importanza delle features** ci riferiamo ad uno **score** che un modello ha assegnato ad una feature, dove tale score è proporzionale alla contribuzione della feature nel modello allenato.

In un [[Decision trees|albero decisionale]] è facile computare la contribuzione, essa rappresenta la riduzione di errore durante la selezione del miglior split.
>Tale errore può essere accumulato per i vari split nei vari alberi in una [[Ensemble methods#Random forest|random forest]].

>[!Info] Feature importance in sklearn
>In sklearn l'importanza delle features è calcolata sulla base dell'impurità (e.g. [[Decision trees#Information gain (entropy)|entropia]], [[Decision trees#Gini index|Gini]]), per poi essere normalizzate così da avere somma pari a $1$.

Con questo approccio viene quindi sfruttata la conoscenza che un modello ha acquisito durante il training, per questo esso deve essere "aperto" e deve esporre l'importanza che esso ha dato alle features.

Questo approccio può essere eseguito con qualsiasi modello, solitamente però si usa un modello veloce da allenare per selezionare le features, poi il modello effettivo che verrà utilizzato per fare predizioni reali potrebbe essere molto complicato (per questo non può essere lui a fare questo lavoro iterativo di feature selection).

### Eliminazione ricorsiva
Con questo approccio **eliminiamo** dopo ogni allenamento una o più **features** con **bassa importanza**.

Se abbiamo due (o più)  feature simili la loro importanza sarebbe spalmata, eliminando man mano le features meno importanti si cerca di eliminare una delle feature simili facendo aumentare l'importanza dell'altra.

---
## Preelaborazione dei dati
Vediamo di seguito alcune strategie per affrontare problemi comuni nei dataset.

>[!Attention]
>Prima di effettuare qualsiasi modifica il dataset va diviso in **train** e **test**, lo stesso preprocessing dovrà essere applicato per entrambi i subset.

- **Features categoriche binarie**
	Vanno mappate le categorie in $0$ e $1$.

- **Features categoriche k-arie**
	Viene utilizzato il _one-hot-encoding_, ovvero per ogni categoria viene creata una nuova colonna con valori binari per indicare se tale istanza appartiene a tale categoria.

- **Features con valori unici**
	Sono features che non apportano espressività al modello e dovrebbero essere eliminate.

- **Valori mancanti**
	I valori mancanti vengono sostituiti con la moda/media dei valori di tale feature, e viene aggiunta una nuova feature binaria che indica se tale valore è "vero" oppure è il risultato della moda/media (inizialmente mancava).

>Nota che la moda/media usata per sostituire i valori nel training set viene salvata, e sarà poi usata anche per sostituire i valori nel test set, altrimenti in un test set con una sola istanza non sarebbe possibile applicare moda/media a valori assenti.

