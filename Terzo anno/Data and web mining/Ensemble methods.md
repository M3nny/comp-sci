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

## Bias, varianza e rumore
L'errore di un modello può essere decomposto in:
- **Bias**: indica l'espressività del modello
- **Varianza**: indica il cambiamento delle predizioni in base al training set scelto
- **Rumore**: errori nel dataset come label errate o feature sbagliate (non può essere rimosso)

Nella regressione con errore MSE, l'errore è dato proprio da:
$$Error(M)=Bias^2+Variance+Noise$$

>Il bagging abbassa la varianza, mentre il boosting abbassa il bias.

Più un modello è complesso (e quindi espressivo), più è a rischio di varianza, ma avrà un basso bias, al contrario i modelli poco espressivi come i _weak learners_ hanno una bassa varianza ma un alto bias.

![[Overfitting vs underfitting.png]]