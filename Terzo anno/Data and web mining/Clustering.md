Un **cluster** è una collezione di dati **simili** tra loro e **dissimili** rispetto ad altri.
Per **cluster analysis** intendiamo trovare similarità tra i dati secondo le loro caratteristiche per poi raggrupparli all'interno di vari _cluster_.

Il processo di _clustering_ appartiene alla famiglia dell'**unsupervised learning**, ovvero non esistono classi predefinite, è suo compito crearle.
>Questo metodo è utile per avere un'idea della distribuzione dei dati, oppure come uno step di preprocessing per altri algoritmi.

### Qualità di un metodo di clustering
Un buon metodo di clustering produrrà dei cluster di alta qualità con le seguenti caratteristiche:
- **Alta similarità interna**: coesione all'interno del cluster
- **Bassa similarità esterna**: distinzione tra cluster

La qualità dipende dalla **misura di somiglianza** utilizzata e dalla sua abilità di scoprire pattern tra i dati.

Misurare la qualità di un clustering è difficile in quanto le classi reali non sono conosciute e quindi non esiste un metodo di confronto per la bontà del clustering, inoltre misure di similarità potrebbero non essere sufficienti (e.g. [curse of dimensionality](https://en.wikipedia.org/wiki/Curse_of_dimensionality)).

### Considerazioni per cluster analysis
Il **partizionamento** può essere a **singolo livello** oppure **gerarchico**, i cluster possono essere **esclusivi** se non ammettono intersezioni, **non-esclusivi** altrimenti.
La _misura di somiglianza_ può essere basata sulla **distanza** (e.g. euclidea) oppure sulla **connettività** (e.g. densità).
Lo **spazio di clustering** può essere **full space** oppure può avere **subspaces** (usato con molte features solitamente).

L'algoritmo deve essere **scalabile**, deve saper **gestire vari tipi di dati** (e.g. numerici, categorici) e deve soddisfare eventuali **vincoli** posti dall'utente.

#### Vari approcci per il clustering
- **Partitioning**: vengono costruite varie partizioni e poi vengono valutate secondo qualche criterio
- **Hierarchical**: crea una decomposizione gerarchica dei dati utilizzando un certo criterio
- **Density-based**: basato su funzioni di connettività e densità
- **Grid-based**: basato su una struttura di granularità multilivello
- **Model-based**: si ipotizza un modello per ciascuno dei cluster e si cerca di trovare il miglior adattamento di tale modello agli altri
- **Frequent pattern-based**: basato sull'analisi di pattern frequenti
- **User-guided o constraint-based**: clustering basato su vincoli posti dall'utente o dall'applicazione specifica
- **Link-based**: gli oggetti sono solitamente collegati tra loro in vari modi

---
## K-means
L'algoritmo di clustering **K-means** rientra nella categoria di **partizionamento**.

Questo algoritmo vuole essere veloce, per cui come _misura di qualità_ utilizzeremo la [[Definizioni generali#Norma|norma-2]] (i.e. distanza euclidea).
Definiamo quindi il centro di un cluster e misuriamo le distanze rispetto ogni punto ed il corrispettivo centro:
$$E=\sum_{i=1}^k\sum_{p\in C_i}||p-c_i||_2^2$$

>Il che risulta nella _norma-1_.

Definiamo $E$ come **Sum of Squared Errors (SSE)**.

In questo approccio assumiamo di sapere in partenza il numero corretto di cluster, ovvero $k$.

Dato il numero $k$ di partizioni, l'algoritmo è implementato come segue:
1. Scegli $k$ punti casualmente come **centroidi**
2. Finchè i cluster continuano a cambiare (o cambiano poco):
	3. Assegna ogni istanza al cluster con il centroide più vicino
	4. Computa i nuovi centroidi della partizione attuale utilizzando la media dei punti che ne fanno parte

![[K-means.png]]

**Vantaggi**:
- È tra gli algoritmi di clustering più veloci
- Solitamente termina in un <b>ottimo <u>locale</u></b>
**Svantaggi**:
- È necessario conoscere $k$
- È sensibile a punti di rumore ed outliers

### K-means++
A differenza dell'algoritmo originale, **k-means++** aggiunge una strategia per la selezione dei centroidi di partenza.

L'idea è che i centroidi devono essere ben separati e devono coprire bene i dati.
L'algoritmo per la selezione iniziale dei centroidi è il seguente:
1. Seleziona il primo centroide casualmente
2. Ripeti per gli altri centroidi rimanenti
	3. Per ogni punto $x$ computa la distanza $d(x)$ rispetto al centroide più vicino
	4. Assegna ad ogni punto una probabilità proporzionale a $d(x)^2$
	5. Seleziona un nuovo centroide casualmente secondo le probabilità assegnate nel punto precedente


#### Elbow method
L'errore SSE nell'approccio k-means decrementa all'aumentare di $k$, ma vorremmo tenere un numero piccolo di $k$ solitamente.

Una pratica comune è smettere di incrementare $k$ se il vantaggio marginale è piccolo (i.e. fermarsi al gomito).
![[Elbow method.png]]

>Un buon candidato per $k$ è $4$.

>[!Attention] K-means è un euristica
>Dato $k$, trovare una partizione di $k$ cluster che ottimizza il criterio di partizionamento scelto è un problema [[Teoria della NP completezza#Classe NPC|NP-hard]], per cui si ricorre a delle euristiche come k-means, altrimenti per trovare un <b>ottimo <u>globale</u></b> bisognerebbe enumerare tutte le possibili partizioni, il che non è fattibile.

