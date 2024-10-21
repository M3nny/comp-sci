Gli **ensemble methods** utilizzano **weak learners**, ovvero modelli veloci ma poco espressivi (singolarmente) per poi **combinarli** assieme per aumentare l'accuracy.

Immaginiamo di avere tre diversi classificatori, ognuno con un _error rate_ pari a $\frac{1}{3}$, la probabilità che tutti diano una classificazione sbagliata è pari a $\left(\frac{1}{3}\right)^3=\frac{1}{27}$, mentre la probabilità che la maggior parte di loro sia sbagliata è:
$$3\left(2\cdot\frac{1}{3}\cdot\frac{2}{3}\right)+\frac{1}{27}=\frac{7}{27}\simeq 26\%$$

Quindi l'accuracy del classificatore singolo è pari a $100-33=67\%$, mentre l'accuracy della loro combinazione è $100-26=74\%$.
Un ensemble riesce ad ottenere un'accuracy alta anche se i weak learner non sono molto accurati.
>Ogni classificatore deve avere un'accuratezza migliore di una scelta casuale.

### Suddivisione del dataset e combinazione delle predizioni
È difficile creare ensemble methods utilizzando un solo dataset, in quanto si dovrebbe suddividere il dataset in $k$ gruppi, e con l'aumentare di $k$ i modelli impareranno poco a causa delle poche istanze per gruppo.
>Utilizzare il **sampling** è una soluzione migliore.

Per **combinare le predizioni** dei modelli si può procedere in due modi:
- Usare un sistema di **votazione** e considerare la predizione più scelta dai modelli per casi di **classificazione**
- Usa un sistema di **media** delle predizioni in caso di **regressione**

## Bagging
L'algoritmo di **bagging**, utilizza la **bootstrap aggregation** per combinare le predizioni dei $k$ modelli allenati su un **bootstrap sample** di un certo dataset di training.

Un **bootstrap sample** è creato utilizzando il **campionamento con sostituzione**, ovvero dopo aver scelto un'istanza da mettere nel campione, essa viene reinserita nel dataset (così da poter essere ripescata).
In questo modo ci si aspetta di avere campioni più grandi diversi tra loro (con intersezioni non banali).

L'algoritmo in pseudocodice è:
```
for i = 1,..., k
	crea un bootstrap sample D_i a partire da D
	crea un modello M_i su D_i
```

Successivamente la predizione per l'istanza $x$ è la combinazione di tutte le predizioni $M_i(x)$.

## Boosting
A differenza del bagging il quale probabilmente avrà modelli simili a causa del modo in cui sono creati, il **boosting** utilizza un approccio sequenziale e si basa sul modello costruito precedentemente, in particolare tenendo conto delle istanze problematiche.

Come nel bagging viene eseguito il **bootstrap sampling**, però in questo caso le istanze hanno un **peso associato**, il quale indica la percentuale di modelli che hanno fatto una predizione sbagliata per l'istanza in questione, più alto è il peso più probabilità ci sono che nel prossimo sampling tale istanza venga selezionata.

Inizialmente ogni istanza $x_j$ ha un peso $w_j=\frac{1}{N}$, dove $N$ è la dimensione del dataset.

Dopo aver allenato un nuovo modello $M_i$ su un sample $D_v$ misuriamo il suo _error rate_ sul dataset iniziale come:
$$error(M_i)=\frac{1}{N}\sum_{(x_j,y_j)\in D}w_j\cdot\mathbb{1}[M_i(x_j)\neq y_j]$$

dove $\mathbb{1}[condizione]=1$ se la $condizione$ è vera, $0$ altrimenti.

I modelli vengono pesati, utilizzando il peso $\alpha_i$ per il modello $M_i$:
$$\alpha_i=\frac{1}{2}\log\frac{1-error(M_i)}{error(M_i)}$$
la formula precedente è chiamata **log-odds** e mappa le probabilità di una predizione corretta in un numero reale.

La predizione finale dell'ensemble è data dalla classe con il voto di maggioranza pesato più grande.

**Aggiornamento dei pesi**
L'_error rate_ è usato per aggiornare i pesi di una istanza.
Se $x_j\in D$ è **correttamente** classificata, allora il suo peso è aggiornato come:
$$w_j=w_je^{-\alpha_i}$$
Se $x_j\in D$ è **erroneamente** classificata, allora il suo peso è aggiornato come:
$$w_j=w_je^{\alpha i}$$
Ciò diminuisce il peso delle istanze classificate correttamente e aumenta il peso delle istanze classificate erroneamente, così da includere nel sampling le istanze con pesi più alti per provare a correggere le predizioni.

>[!Attention]
>Il boosting è prone all'**overfitting** in quanto si concentra sulle istanze mal-classificate, includendo outliers e punti di rumore.

L'algoritmo in pseudocodice è:
```
Inizializza il peso w_j = 1/n per ogni istanza x_j
E = ∅
for i = 1 to k:
	ottieni D_i campionando D in base ai pesi w_j
	allena un modello M_i su D_i
	computa error(M_i) > 0.5
	if error(M_i) > 0.5:
		reset pesi w_j=1/n
		break
	computa l'importanza del modello α_i
	aggiorna i pesi delle istanze in D
	aggiungi αM_i all'ensemble finale E
return E
```
>Viene utilizzato $0.5$ immaginando di dover classificare $2$ classi diverse, quindi la probabilità di eseguire una predizione corretta è $0.5$.

### Bias, varianza e rumore
L'errore di un modello può essere decomposto in:
- **Bias**: indica l'espressività del modello
- **Varianza**: indica il cambiamento delle predizioni in base al training set scelto
- **Rumore**: errori nel dataset come label errate o feature sbagliate (non può essere rimosso)

Nella regressione con errore MSE, l'errore è dato proprio da:
$$Error(M)=Bias^2+Variance+Noise$$

>Il bagging abbassa la varianza, mentre il boosting abbassa il bias.

Più un modello è complesso (e quindi espressivo), più è a rischio di varianza, ma avrà un basso bias, al contrario i modelli poco espressivi come i _weak learners_ hanno una bassa varianza ma un alto bias.

![[Overfitting vs underfitting.png]]

---
## Random forest
Abbiamo visto che gli [[Decision trees|alberi decisionali]] molte foglie sono proni all'overfitting in quanto sono "troppo" espressivi (basso bias) e le predizioni cambiano tanto in base al training set, quindi hanno **alta varianza**.

Per diminuire la varianza possiamo usare l'algoritmo di **bagging**, tuttavia quest'ultimo è efficace quando i modelli sono indipendenti tra loro, in questo ci aiuta il **bootstrap sampling** per creare training set differenti, però alla fine i training set conterranno comunque istanze in comune risultando in modelli più o meno simili.

Introduciamo il concetto di **random input selection** all'algoritmo di creazione di nodi nuovi per gli alberi decisionali per creare modelli altamente espressivi (alberi totalmente cresciuti) e differenti (poco correlati) tra loro.

Al momento della creazione di un nodo non vengono posti dei vincoli su tutte le features, bensì solo in alcune scelte a caso:
```
for i = 1 to k:
	prendi un bootstrap sample D_i dal dataset D
	allena un albero completamente cresciuto M_i su D_i
		in ogni split seleziona solo F << d features casuali

RF = unione di tutti gli M_i alberi
return RF
```
>$<<$ vuol dire "molto meno di".
>Solitamente $F=\sqrt{d}$ oppure $F=\log_2(d)$.

Come gli altri metodi di ensemble la predizione alla fine sarà data per votazione usando la moda o media in base a task di classificazione/regressione.

>[!Tip] Performance delle random forest
>Gli alberi possono essere costruiti in parallelo aumentando la performance, inoltre anche il singolo albero è costruito più velocemente in quanto non si vanno a considerare tutte le features ad ogni split.

### Random forest per stimare la similarità
Abbiamo visto come i [[K-nearest neighbors]] stimano la similarità tra istanze utilizzando le features opportunamente scalate, possiamo utilizzare anche le random forest come stima di similarità senza dover scalare le features basandoci sulle label delle varie istanze.

Due istanze sono simili se seguono in percorso simile in un albero, si potrebbe quindi dire che sono simili se ricadono nella stessa foglia, per cui possiamo contare in quanti alberi della random forest le istanze in questione cadono nella stessa foglia.

La **similarità** è quindi data dalla frazione di foglie uguali raggiunte dalle istanze in questione durante l'attraversamento dell'albero.
>Esistono anche altre misure (e.g. potrebbero differenziarsi solo nell'ultimo split e sarebbero abbastanza simili comunque)

Questo metodo per stimare la similarità può essere applicato a qualsiasi foresta, quindi anche a bagging e boosting, però le random forest sono preferite perchè:
- È meglio del boosting perchè non pesa gli alberi
- È meglio del bagging perchè i suoi alberi sono più diversi

Vediamo di seguito la differenza tra distanza euclidea e distanza utilizzando la random forest:
![[Random forest distance.png]]

>$distance = 1-similarity$.

Il precedente non è un decision boundary, bensì rappresenta la distanza dall'origine che è posta al centro, la random forest ha imparato che quello che sta nella sezione di sinistra è meno distante da quello che sta nella sezione di destra.

### Random forest per trovare gli outliers
È difficile dare una definizione precisa di outlier, possiamo però definirli come un punto distante dalla distribuzione del nostro fenomeno, ciò può accadere per diversi motivi.

Utilizzando la similarità vista precedentemente possiamo formulare un **outlier score**:
$$out(o_i)=\frac{1}{\sum\limits_{o_j\in D} RF\_sim(o_i,o_j)^2}$$

Questa è un'operazione costosa in quanto per ogni istanza saranno necessarie $|D|^2$ computazioni di similarità.

### Random forest per trovare valori mancanti
Possiamo utilizzare la similarità anche per riempire i valori mancanti nel dataset.

Consideriamo una istanza $o_i\in D$ dove la feature $f$ è mancante, possiamo procedere come segue:
1. Rimpiazza i valori mancanti con la media delle altre istanze dove $f$ è presente, dove la media è pesata in base allo score di similarità di $(o_i,o_j)$

$$o_i[f]=\frac{\sum\limits_\stackrel{a_j\in D}{a_j[f]\neq NaN} a_j[f]\cdot RF\_sim(o_i,o_j)}{\sum\limits_\stackrel{a_j\in D}{a_j[f]\neq NaN} RF\_sim(o_i,o_j)}$$

2. Allena una nuova random forest sui dati modificati e computa nuovi score di similarità
3. Ripeti finchè non ci sono più miglioramenti

