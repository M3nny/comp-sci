La regressione lineare **individua una tendenza**, data una label $y$ da predire e delle features $x$ vogliamo trovare una relazione lineare che meglio si avvicina a tutte le istanze presenti nel dataset.
![[Regressione lineare.png|400]]

$$y=b_0+b_1x$$

L'**obiettivo** è quello di trovare i migliori coefficienti ($b$) per la retta.

L'**errore** è dato dalla somma delle distanze dalla previsione rispetto all'istanza reale (non viene usata la distanza perpendicolare alla retta), una delle funzioni possibili per calcolarlo è il **RMSE (Root Mean Squared Error)**:
$$RMSE(y_{true},y_{pred})=\sqrt{\frac{\sum_i(y_{true}[i]-y_{pred}[i])^2}{\#y_{true}}}$$

Prendiamo come esempio l'andamento del valore del BTC in base al giorno:
```python
BTC = [10923.63, 10679.14, 10621.66, 10804.00, ...]
```

in questo caso il **train** e **test** set non saranno scelti in modo casuale, bensì verrà estratto un giorno che divide passato (training) e futuro (test).

Tuttavia se il fenomeno che vogliamo modellare non è lineare, la regressione lineare non funzionerà bene.
![[Regressione lineare BTC.png|500]]

Possiamo dunque allenare una funzione più espressiva, come una parabola, o generalmente un <u>polinomio di grado maggiore</u> per rendere di conseguenza il modello più espressivo:
$$y=b_0+b_1x+b_2x^2$$
![[Regressione lineare BTC 2.png]]
In questo caso il modello funziona meglio.
È possibile notare che aumentando il grado del polinomio ci si avvicina sempre di più ai punti reali (nel training set), tuttavia aumentarlo troppo fino a mappare correttamente tutte le istanze del training set comporta un **overfit**, nel test set infatti il modello non saprà come comportarsi.

#### Scelta di features migliori
Finora abbiamo utilizzato il giorno singolo per allenare il modello, un'idea migliore è quella di trasformare il dataset considerando una **finestra temporale**, ad esempio prendiamo $4$ giorni e prediciamo il quinto, poi spostiamo la finestra avanti di uno per predire il sesto.
![[Regressione lineare BTC 3.png]]

>Il modello in questo caso si sta comportando come una specie di media mobile.

## Regressione logistica
La regressione lineare predice un valore continuo, nel caso si volesse capire se una istanza sta in una classe o in un'altra (**classificazione binaria**) è necessaria una probabilità che indichi la percentuale di "sicurezza" che ha tale istanza di stare nella classe $A$ piuttosto che $B$.

Sostituiamo una predizione lineare con range $]-\infty,+\infty[$ con una probabilità tramite la [sigmoide](https://en.wikipedia.org/wiki/Sigmoid_function):
$$\sigma(x)=\frac{1}{1+e^{-x}}$$

Sappiamo che la regressione lineare è nella forma di $z=w^Tx+b$, ma dobbiamo limitare $z$ nell'intervallo $[0,1]$ per interpretarlo come una probabilità, siamo quindi interessati in:
$$P(y=1|x)=\sigma(z)=\frac{1}{1+e^{-z}}$$
$$\frac{P(y=1|x)}{P(y=0|x)}=e^z\quad\implies\quad \ln\left(\frac{P(y=1|x)}{P(y=0|x)}\right)=z=w^Tx+b$$

La regressione logistica è una regressione lineare sul **log-odds**, ovvero il logaritmo del rapporto tra la probabilità di essere nella classe $A$ rispetto che nella classe $B$.
![[Regressione logistica.png]]

>L'indecisione tra le due classi è la funzione logistica, in $\mathbb{R}^3$ possiamo vederlo come un piano a forma di sigmoide in cui la salita rappresenta i punti di incertezza.

In un problema linearmente separabile (come quello rappresentato) esistono infinite rette in grado di separare le due classi, e la retta migliore è quella che lascia il margine maggiore tra le due classi.
>Avere poco margine tra le due classi aumenta il rischio di classificazioni errate.


## Support Vector Machine (SVM)
La SVM è una tecnica di **classificazione** che come obiettivo ha _massimizzare_ la generalizzazione del modello di classificazione.
![[SVM.png]]

Chiamiamo **margine** la distanza tra istanze di classi opposte più vicine tra loro lungo la direzione perpendicolare al decision boundary selezionato.
Le istanze che determinano il margine sono chiamate **support vectors**.

Le distanze sono misurate tramite la [[Definizioni generali#Norma|norma euclidea]], indichiamo con $d_s$ la distanza dell'istanza $x_s\in S$, più vicina a $w^Tx+b$, mentre con $d_c$ la distanza considerando l'istanza $s_c\in C$ più vicina a tale retta.
$$d_s=\frac{1}{||w||_2}\quad d_c=\frac{1}{||w||_2}\implies d=d_s+d_c=\frac{2}{||w||_2}$$

Sia $y_i\in\{-1,1\}$ la classe della $i$-esima istanza, il problema può essere formulato come:
$$\min \frac{||w||_2}{2}$$
$$y_i(w^Tx_i+b)\geq 1$$

Essendo la funzione obiettivo quadratica ed il vincolo lineare in $w$ e $b$, si tratta di un [[Problemi convessi|problema convesso]].

Nel caso il problema non fosse linearmente separabile sarà necessario introdurre variabili in grado di **rilassare il modello**, ovvero istanze della classe $B$ vengono classificate come appartenenti alla classe $B$ anche se sono nella regione delle istanze di classe $A$ definita dalla SVM.
>Vanno minimizzate anche tali variabili.

Un'altra opzione di fronte a problemi non linearmente separabili è quella di applicare un **kernel trick** ovvero applicare una trasformazione al dataset in modo da poterlo rappresentare in dimensioni aggiuntive e quindi dividere meglio le istanze di classi diverse.
![[Kernel trick.png]]

>[!Attention]
>Le support vector machines sono un buon modello, ma il problema diventa quasi **intrattabile** con dataset grandi a causa della loro scarsa scalabilità in termini di performance.

---
## K-fold cross validation
Abbiamo visto precedentemente l'importanza del [[Decision trees#Validation set|validation set]] per capire gli iperparametri migliori di un modello, tuttavia alcune istanze particolari nel training o validation set potrebbero agevolare oppure rendere più difficile l'apprendimento, portando a risultati poco affidabili in entrambi i casi.

Utilizziamo la **k-fold cross validation** per partizionare ulteriormente il dataset ed eseguire $k$ esperimenti (uno per partizione).
![[K-fold validation.png]]

>Bisogna sostituire il testing set (vedi immagine) con il validation set nel caso lo si usasse.

L'accuracy infine è data dalla media delle performance dei validation set (vedi [cross_validate](https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.cross_validate.html))

In generale i risultati sono biased in base alla scelta del validation set, ciò si nota molto con dataset non bilanciati, esistono due modi per scegliere le istanze di un **fold**:
- **Random**: prendendo $x$ istanze casuali
- **Stratified**: vengono prese $x$ istanze preservando la frequenza delle varie classi
