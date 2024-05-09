Per **stallo o deadlock** si intende un insieme di processi o thread che si attendono tra di loro per un tempo indefinito.

##### Condizioni per lo stallo
- **Mutua esclusione**: se una risorsa può essere usata da tutti non si pone il problema
	Non è possibile evitare la mutua esclusione quando necessaria.

- **Possesso e attesa**: problematico se i thread richiedono risorse in modo incrementale
	Si potrebbe allocare direttamente tutte le risorse necessarie, però sarebbe inefficiente e potrebbe portare a _starvation_.

- **Assenza di preemption**: con la preemption non si verificano stalli
	Non tutte le risorse possono salvare il proprio stato per poi riesumarlo.

- **Attesa circolare**
	È possibile evitare l'attesa circolare tramite opportune strategie di allocazione delle risorse, come nel [[Problemi noti#Filosofo mancino|filosofo mancino]].

##### Gestione dello stallo da parte del sistema operativo
- **Prevenzione**: utilizza strategie che evitano in partenza stalli
- **Controllo**: l'assegnamento di risorse avviene solo se si è certi che non potrà generare uno stallo
- **Riconoscimento**: individua stalli e cerca di ripristinare uno stato precedente allo stallo
- **Nessuna azione**: lascia al programmatore la gestione dello stallo

## Controllo dello stallo
Per controllare a **run-time** lo stallo bisogna consentire l'assegnamento delle risorse solo nel caso in cui si è sicuri che non porteranno ad uno stallo.

Usiamo i **grafi di assegnazione** per controllare l'allocazione delle risorse del sistema utilizzando $3$ tipi di archi che collegano processi/thread a risorse:
```
P <----- R: La risorsa R è assegnata al processo P
P -----> R: Il processo P richiede la risorsa R
P - - -> R: Il processo P potrà richiedere in futuro la risorsa R
```

Un grafo di assegnazione è sicuro (privo di stalli) se:
1. C'è una sola istanza per risorsa: stallo $\iff$ $\exists$ ciclo nel grafo
2. Ci sono più istanze per risorsa: stallo $\implies$ $\exists$ ciclo nel grafo
	in questo caso bisogna fare ulteriori osservazioni.

##### Singola istanza per risorsa
![[Filosofi mancini.png]]
Il caso di $5$ filosofi mancini a cui è già stata assegnata la bacchetta di sinistra genererà un ciclo, per evitarlo basta mettere in attesa per un po' un filosofo, in questo modo verrà evitato lo stallo.

##### Multiple istanze per risorsa
Anche in presenza di cicli potrebbe _non_ esserci uno stallo, per esserne sicuri dobbiamo verificare la presenza di una **sequenza di processi sicura** tramite **l'algoritmo del banchiere**:
1. Cerca un processo che possa ottenere tutte le risorse necessarie (incluse quelle future) da quelle disponibili, <u>se non esiste non c'è alcuna sequenza sicura</u>
2. Rilascia tutte le risorse possedute dal processo, aggiungilo alla sequenza sicura e toglilo dal grafo
3. Se sono presenti ancora dei processi nel grafo vai al punto 1, altrimenti ritorna la sequenza sicura

Considerando il seguente grafo di assegnazione:
![[Sequenza sicura.png]]
Se viene assegnata una istanza di R1 a P1, otteniamo la sequenza sicura $<\text{P1,P2,P3}>$ in quanto P1 può ottenere R2, rilasciando le proprie risorse permette a P2 di ottenere R2, che a sua volta può rilasciare le risorse permettendo a P3 di ottenere R1 e R2.