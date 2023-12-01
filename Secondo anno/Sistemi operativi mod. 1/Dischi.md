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
