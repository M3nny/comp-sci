I **miglioramenti delle prestazioni** della memoria secondaria aumentano in modo significativo le prestazioni dell'intero sistema, le soluzioni possono essere sia software che hardware.

## Comunicazione con I/O
Vediamo i due principali tipi di [[Controller|controller]], da non confondere con il metodo di gestione dell IO.
#### Mappato in memoria
**Vantaggi**:
- Scritto con linguaggi ad alto livello, i registri sono semplici variabili
- Controllo degli indirizzi semplice
- Le istruzioni possono riferirsi direttamente ai registri di controllo
**Svantaggi**:
- Non è possibile usare la cache
- Con bus separati alcuni dispositivi I/O potrebbero non vedere alcuni indirizzi spediti sul bus, è possibile usare un singolo bus, oppure un doppio bus
![[Comunicazione IO mappato in memoria.png|600]]
#### DMA
Il controllore DMA ha accesso diretto alla memoria ed ha **molti registri** utili per capire dove e quanto trasferire, è anche possibile usare più registri di controllo per **trasferimenti multipli**.
![[Comunicazione IO DMA.png|600]]

### Tipi di software per I/O
Il software per la gestione degli IO è **indipendente** dal dispositivo, esso gestisce il metodo di gestione dell'IO, i buffer ed i dispositivi dedicati e condivisi da più processi.

Nel [[Controller#Programmed IO (Polling)|polling]] il buffer è nello spazio utente, nell'[[Controller#Interrupt-driven IO|interrupt driven IO]] è nel kernel, mentre il [[Controller#Direct Memory Access (DMA)|DMA]] ha accesso diretto.

---
## Caratteristiche dei dischi a testina mobile
Un hard disk possiede:
- **Piatti**
- **Tracce**: cerchi di raggio differente con centro il perno dell'hard disk
- **Settori**: archi di tracce
- **Cilindri**: gruppi verticali di tracce
- **Testine mobili** impilate che si muovono contemporaneamente
![[Schema hard disk.png|500]]
Indici di prestazione:
- **Tempo di ricerca (seek)**: tempo impiegato dalla testina per spostarsi su un altro cilindro
- **Latenza rotazionale**: ritardo dovuto alla velocita di rotazione del disco
- **Tempo di trasmissione**: tempo di lettura dei settori

I dischi moderni usano un **indirizzamento logico** dei blocchi per evitare di considerare la geometrica del disco.

Grazie al **cylinder skew**, per ogni traccia, il primo settore è spostato rispetto all'ultimo della traccia precedente per migliorare le prestazioni.

Viene usato l'**interleaving** per evitare che la testina sorpassi un settore necessario subito dopo quello che si sta elaborando a causa della CPU che deve ancora finire di leggere il primo settore.
Quindi al posto di avere dei settori in ordine (0-1-2-3...), con un _singolo interleaving_ si avrà (0-10-1-11...), se non basta si può usare un interleaving più alto, come e.g. quello doppio (0-10-20-1-11-21...).

Quando un hdd viene **formattato**, viene definito il blocco di avvio, directory principale e file system.

### RAID (Redundant Array of Inexpensive Disks)
Vengono usati i **RAID** (visti dal sistema come **singola unità disco**) per aumentare l'**affidabilità** attraverso la gestione di molte copie di dati su più dischi in modo parallelo.

Un livello di RAID può avere **striping** per aumentare il throughput usando diversi dischi in parallelo, **mirroring** se ci sono dischi che contengono dati copiati e blocchi di parità per verificare che i dati non siano corrotti.


## Scheduling del disco
Gli algoritmi di scheduling del disco cercano di minimizzare il **tempo di risposta** medio e aumentare il **throughput**

- **First Come First Served (FCFS)**:
	tratta le richieste nell'ordine in cui arrivano.
	
	Sebbene è equo, con basso overhead e evita l'attesa infinita, ogni richiesta potrebbe richiedere di leggere in parti diverse del disco, portando così ad un modello di seek casuale.

- **Shortest Seek Time First (SSTF)**:
	soddisfa la richiesta che opera sul settore più vicino alla testina in quel momento.
	
	Il throughput è molto alto, ma non è equo e c'è possibilità di attesa infinita, inaccettabile per sistemi interattivi.

- **SCAN**:
	simile a SSTF con la differenza che non cambia direzione finchè non raggiunge il limite del disco.
	
	Non è equo (tracce centrali favorite), l'attesa infinita è ancora possibile, ma diminuisce la varianza dei tempi di risposta.

- **C-SCAN**:
	come SCAN, solo che si muove solo verso una direzione e alla fine di una scansione verso l'interno salta al cilindro più esterno.
	
	Riduce ancora di più la varianza.

- **FSCAN**:
	soddisfa gruppi batch di richieste congelando periodicamente le richieste al disco finchè non ha finito di servire quelle nell'attuale batch con algoritmo SCAN.
	
	Elimina l'attesa infinita e riduce la varianza rispetto a SCAN.

- **N-Step SCAN**:
	come FSCAN, solo che in questo caso serve le prime $n$ richieste.
	
	Elimina l'attesa infinita e riduce la varianza rispetto a SCAN.

- **LOOK**:
	migliora SCAN cambiando direzione quando in quel momento non ci sono più richieste nella direzione percorsa.
	
	Throughput elevato dato che si evitano operazioni di ricerca inutili.

- **C-LOOK**:
	combina LOOK e C-SCAN, quando non ci sono più richieste nell'attraversamento verso l'interno, salta verso l'esterno e ricomincia.
	
	Minor varianza rispetto a LOOK a scapito del throughput.

Gli algoritmi più moderni ottimizzano anche il **tempo di rotazione**.
- **Shortest Latency Time First (SLTF)**:
	serve le richieste con la minima latenza di rotazione.

	Facile da implementare, raggiunge prestazioni quasi ottimali per la latenza rotazionale.

- **Shortest Positioning Time First (SPTF)**:
	serve le richieste con il minimo tempo di posizionamento, il quale è dato dalla somma di tempo di ricerca e latenza di rotazione.
	
	Throughput elevato ma può causare attesa infinita, inoltre richiede la conoscenza delle prestazioni del disco.

- **Shortest Access Time First (SATF)**:
	variante di SPTF che tiene conto anche del tempo di trasmissione
	
	Throughput elevato ma può causare attesa infinita, inoltre richiede la conoscenza delle prestazioni del disco.

> Sia SPTF e SATF possono implementare LOOK per migliorare le prestazioni.

### Considerazioni di sistema
Lo scheduling del disco è spesso utile ma non sempre:
- Poco utile in sistemi processor-bound
- L'overhead dello scheduling potrebbe ridurre le prestazioni
- Il modo in cui vengono organizzati i file potrebbe andare in contrasto con gli algoritmi di scheduling
- Le geometrie del disco potrebbero vanificare i vantaggi dello scheduling

La **buffer cache** può essere usata per memorizzare temporaneamente in RAM delle copie dei dati sul disco per accederci più velocemente, oppure per posticipare le scritture ad un momento in cui il disco sarà meno occupato.
Per garantire la coerenza del buffer vengono usati i meccanismi di [[Cache diretta#Politiche di coerenza|write-through]] o [[Cache diretta#Politiche di coerenza|write-back]].

**Gestione degli errori**:
Eventuali settori difettosi possono essere sostituiti da settori di riserva, inoltre per avere operazioni di lettura e scrittura stabile, assumendo di disporre di un RAID che ci consente di avere dati duplicati su almeno due dischi, se la lettura o scrittura non è corretta $n$ volte su un disco, viene usato il disco clone.

#### Ottimizzazioni
- **Deframmentazione**: operazione eseguita periodicamente per inserire i dati in settori contigui
- **Compressione**: i dati occupano meno spazio e migliora i tempi di trasferimento, bisogna tenere conto però dell'overhead di compressione/decompressione
- **Copie multiple**: in questo modo la testina può scegliere la copia più vicina da leggere, occupa più memoria ed un overhead in più
- **Accorpamento di record (blocking)**: leggere e scrivere più record come unico blocco di dati
- **Anticipazione del braccio del disco**: quando inattivo il braccio del disco può posizionarsi dove è maggiore la probabilità del prossimo accesso (o al centro)
