Le [[Terzo anno/Data and web mining/Reti neurali/Introduzione|reti neurali]] usate nel riconoscimento delle immagini utilizzano i **filtri di convoluzione**, i quali rappresentano una matrice di valori numerici applicata su un'altra matrice, nel nostro caso una matrice rappresentante i valori dei pixel.

Ogni valore appartenente al filtro rappresenta un **peso**, la **convoluzione** consiste nel far scorrere il filtro su tutta la matrice originale e per ogni regione calcolare una **somma pesata**, il quale risultato da origine ad un nuovo pixel chiamato **response**, appartenente ad una nuova matrice risultato.
![[Conv2D.png]]

La sintassi `Conv2D(32, (3, 3))` (vedi [keras](https://keras.io/api/layers/convolution_layers/convolution2d/)) sta ad indicare che vengono fatti scorrere $32$ filtri di dimensione $3\times 3$ sulla matrice originale, ognuno con pesi diversi che dovranno essere imparati in fase di training, solitamente ogni filtro impara a differenziare un pattern diverso nell'immagine.

Tutte le matrici risultanti saranno della stessa dimensione di quella originale.
Per quanto riguarda i **bordi della matrice** dove il filtro non può essere applicato (altrimenti "uscirebbe" dalla matrice originale) vengono utilizzate delle tecniche di **padding**, oppure vengono direttamente ignorati i bordi.

La convoluzione ha delle proprietà importanti, tra cui:
- I filtri sono **invarianti alla traslazione**, quindi se un filtro genera un pixel con elevata _response_, lo troverà anche con l'immagine traslata
- Le reti di convoluzione imparano **gerarchie spaziali di pattern**, possiamo immaginare che i layer più vicini all'output rappresentino pattern più complessi che sfruttano quelli imparati dai layer precedenti
>Possiamo pensare ai filtri come a dei rilevatori di pattern.

## Pooling layers
La somma pesata tramite filtri viene calcolata ovunque, anche se il pattern non è presente, risultando in molte _response_ con valori bassi, in genere infatti ci interessa il **valore massimo di una response** in una certa area.
![[MaxPooling2D.png]]

Il layer di **MaxPooling** seleziona la response più grande all'interno di un'area specificata, `MaxPooling2D((2, 2))` ad esempio genererà un output ogni quadrato $2\times 2$ che non si sovrappone con altri.

In questo modo riduciamo la quantità di dati generati dalle varie matrici di response e manteniamo solo le response elevate, scartando le altre.

### Flatten layer
Ad un certo punto dovremo far convergere i _pooling layer_ nelle $n$ possibili classificazioni dell'immagine, per cui l'output dell'ultimo pooling layer deve avere forma corretta per darlo in input alla funzione **softmax**.

Per farlo utilizziamo la funzione **flatten** utilizzata per trasformare una matrice multidimensionale in un vettore.
Aggiungiamo poi un layer **denso** seguito da una funzione di attivazione al quale poi seguirà un **ultimo layer denso** con funzione di attivazione _softmax_.

Con keras possiamo scrivere:
```python
model = Sequential([
	Input(shape=(img_x, img_y, 1)), # 1 channel (grayscale)
	
	Conv2D(32, (3, 3), activation="relu"),
	MaxPooling2D((2, 2)),
	
	Conv2D(64, (3, 3), activation="relu"),
	MaxPooling2D((2, 2)),
	
	Flatten(),
	Dense(64, activation="relu"),
	
	Dense(10, activation="softmax")
])
```

L'utilizzo dei layer densi alla fine, oltre ad essere necessari per utilizzare la funzione _softmax_, è importante in quanto essi sono connessi alla matrice risultante dai filtri di convoluzione ed i successivi max pooling, in questo modo avrà una "visuale" dell'immagine intera, in modo da rilevare dei pattern ed aggiornare i pesi in fase di backpropagation.

![[Convolutional NN.png]]

Il **numero di parametri** di un layer di convoluzione è dato da:
$$\#params=(\text{\#canali in ingresso}\cdot\text{dimensione kernel + bias})\cdot\text{\# numero di filtri}$$

In figura il primo layer ha $(1\cdot 25+1)\cdot 10=260$ parametri, mentre il secondo layer ha $(10\cdot 25+1)\cdot 20=5020$ parametri.

#### Effetto funnel
Quando una rete neurale possiede un'architettura con un numero decrescente di neuroni in ogni layer viene creato l'**effetto funnel (o imbuto)**, dove l'output del layer precedente deve essere **compresso** in un numero inferiore di nodi.

In questo modo il modello sintetizzerà le informazioni ricavate dai layer precedenti.

È importante sottolineare che i **layer nascosti** devono essere **sufficientemente grandi** per rappresentare una sintesi dell'informazione dei layer precedenti, ad esempio se un layer nascosto ha $n<N$ nodi, non avrà abbastanza capacità di rappresentazione.
>$N$: numero di classi.

### Filtri di convoluzione 1D
I filtri di convoluzione possono anche essere monodimensionali, utili ad esempio per l'**analisi di time series**.

Un filtro con lunghezza $3$ con pesi pari a $[\frac{1}{3},\frac{1}{3},\frac{1}{3}]$ rappresenta una **media mobile**.
![[Conv1D.png|350]]
