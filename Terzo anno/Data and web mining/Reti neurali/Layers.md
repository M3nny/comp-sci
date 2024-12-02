Le reti neurali possono essere costruite concatenando vari **layer** di neuroni, aumentare il numero di layer e neuroni aumenta la potenza della rete neurale.
Differenziamo tre **categorie di layer**:
- **Layer di input**: primo layer della rete
- **Layer nascosto**: layer compreso tra l'_input layer_ e l'_output layer_, il numero di layer di una rete neurale è dato dal numero di layer nascosti, il numero dei suoi neuroni è arbitrario
- **Output layer**: ultimo layer della rete


La dimensione del **layer di input** dipende dalla dimensionalità dell'input (e.g. features in un dataframe), discorso analogo per il **layer di output** il quale dipenderà dalla dimensione dell'output (e.g. nella classificazione binaria avrà un layer composto da due neuroni).

I layer sono **densamente connessi** tra loro formando un [[Tipologie#Grafo bipartito|grafo bipartito completo]] ed ogni connessione possiede un peso, il processo di training consiste proprio nel trovare i pesi migliori per ogni connessione.

Esistono tre parametri principali nei **layer densi**, ovvero:
1. Numero di neuroni nel layer
2. Funzione di attivazione
3. Dimensione dell'input

### Funzioni di attivazione
Le funzioni di attivazione **determinano l'output di ogni neurone**, è importante che esse siano non-lineari in modo da poter permettere l'apprendimento di funzioni complesse.
![[Sigmoid.png]]

Possiamo utilizzare la **sigmoide** per la **classificazione binaria**, per qualsiasi input, l'output sarà compreso in $[0,1]$.
>Questa funzione "scarta" gli input molto grandi e molto piccoli.

In task di classificazione si vuole ottenere un vettore di probabilità che possieda somma pari a $1$, ma essendo gli output dei neuroni in qualche modo _scorrelato_, questo non accade, per questo solitamente si pone come ultimo layer la funzione **softmax** definita come segue:
$$\text{softmax}=\sigma(z_i)=\frac{e^{z_i}}{\sum\limits_{j=1}^Ke^{z_j}}\qquad z=(z_1,...,z_K)\in\mathbb{R}^K$$
A differenza della _sigmoide_ che agisce su ogni singolo neurone, la funzione _softmax_ agisce sul vettore risultante (ultimo layer) trasformando i valori in probabilità.
>La sigmoide può essere usata come ultima funzione di attivazione nel caso di classificazione binaria.

Nel caso di **task di regressione**, non è necessario porre una funzione di attivazione nell'ultimo layer.

Una funzione di attivazione molto efficace e famosa è la **ReLU (Rectified Linear Unit)**, ed è definita come:
$$ReLU(x)=x^+=\max(0,x)$$

![[Activation functions.png|600]]

### Funzioni di perdita
Le funzioni di perdita misurano l'errore tra la predizione e l'output atteso, esse dipendono dal task specifico.

#### Classificazione
Per la classificazione binaria sarà utile la **binary cross-entropy loss**, in questo task essendo che l'output sarà composto da due elementi, i quali indicano la probabilità che l'istanza in input sia di una classe o dell'altra, dovremmo quindi selezionare l'indice che massimizza la probabilità (nel vettore in output).

Per task di **classificazione multi-classe**, utilizziamo la **categorical cross-entropy loss**, la quale al posto di confrontare due probabilità, confronta due **distribuzioni di probabilità**.

#### Regressione
Per task di **regressione** le funzioni di perdita sono differenti, le più comuni sono:
- **MSE**: Mean Squared Error
- **MAE**: Mean Absolute Error
- **MAPE**: Mean Absolute Percentage Error
- **MSLE**: Mean Squared Logarithmic Error

### Ottimizzatori
Il compito dell'ottimizzatore è quello di trasformare il valore della funzione di perdita in un aggiornamento dei pesi.
- Grande perdita, grandi aggiornamenti
- Piccola perdita, piccoli aggiornamenti

Come visto precedentemente, il **learning rate** solitamente è basso in modo creare una curva di training più performante ed evitare di essere _greedy_.

Esistono vari ottimizzatori che adottano varie tecniche per minimizzare la funzione obiettivo (funzione di perdita), tra cui quella di partire con un learning rate alto per poi diminuirlo con l'avanzare delle epoche.
- **SGD (Stochastic Gradient Descent)**: aggiorna tutti i pesi in modo uniforme secondo la direzione opposta indicata dal gradiente
- **RMSprop (Root Mean Square propagation)**: a differenza dell'SGD, mantiene un learning rate specifico per ogni parametro
- **ADAM (Adaptive Moment Estimation)**: combina l'RMSprop con il concetto di [momentum](https://optimization.cbe.cornell.edu/index.php?title=Momentum) per arrivare alla convergenza più velocemente
>Eseguire il fine tuning degli ottimizzatori è l'ultimo passo da compiere.

#### Recap

| Tipologia del problema       | Attivazione dell'ultimo layer | Funzione di perdita        |
| ---------------------------- | ----------------------------- | -------------------------- |
| Classificazioe binaria       | `sigmoid`                     | `binary_crossentropy`      |
| Classificazione multi-classe | `softmax`                     | `categorical_crossentropy` |
| Regressione                  | _Nessuna_                     | `mse`                      |
