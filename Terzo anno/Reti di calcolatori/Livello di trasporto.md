Il [[Livello di rete|livello di rete]] offre un servizio **connectionless** e non affidabile, le applicazioni però hanno necessità che i dati arrivino correttamente senza nessun intoppo.

Il livello di **trasporto** deve garantire il **multiplexing**, ovvero deve distinguere i dati che appartengono a diverse coppie di client-server che comunicano nello stesso canale.

Le applicazioni non conoscono nulla dei pacchetti, però condividono un **buffer** con il livello di trasporto che contiene uno stream di dati, che verrà poi **segmentato** ed inoltrato al livello di rete.
>La SDU del livello di trasporto sono i **segmenti**.

## Connectionless service
Questo tipo di servizio offerto dal livello di trasporto offre soltanto _multiplexing_, normalmente è **stateless** e la consegna dei dati non è affidabile, però possiede _rilevamento di errori_ grazie un **checksum** contenuto nell'header.
>Utile per servizi in streaming.

Per distinguere le coppie di comunicazioni sullo stesso canale vengono utilizzate le **porte**, le quali vengono specificate nell'header (source-destination).

## Connection-oriented service
In questo caso la connessione è **stateful**, ovvero alcune variabili vengono utilizzate per tenere traccia dell'evoluzione della connessione, per questo prima di cominciare una comunicazione avviene un **preambolo** per impostare la connessione.

Il preambolo dovrebbe essere semplice come uno scambio di due pacchetti, però il livello di rete è inaffidabile, possiamo assegnare ad ogni segmento un id unico (incrementale), ma questo comporta che gli attori nella connessione mantengano una coda di id per ogni connessione attiva, il che non è fattibile.

Introduciamo il **Maximum Segment Life (MSL)**, ovvero il tempo massimo per cui un pacchetto può esistere nella rete.
>La specifica pone MSL a $2$ minuti.

Ogni transport layer possiede un **transport clock** che è incrementato col passare del tempo e ad ogni connessione, infatti ogni **Connection Request (CR)** richiede un **Initial Sequence Number (ISN)**, il destinatario poi includerà l'ISN nel **Connection Acknowldegement (CA)**.

Essendo che lo spazio nell'header è limitato, prima o poi l'ISN ricomincerà da capo, ed <u>è necessario che il modulo per l'ISN sia molto più grande rispetto al MSL</u>, altrimenti potrebbe ricominciare il suo conteggio ed il destinatario non sarebbe più in grado di distinguere se il pacchetto è nuovo oppure è lo stesso appena che ha da poco ricevuto.

Un ISN è sufficiente per ricostruire lo stream di segmenti dal client al server, tuttavia per avere una comunicazione bi-direzionale, <u>anche il server genererà un ISN da mandare al client</u>.

### Three way handshake
![[Three way handshake.png|700]]
1. La CR contiene il numero di porta ed un numero di sequenza (seq=x), il quale valore è estratto dal _transport clock_
2. Il server processa il segmento CR e crea uno stato per il tentativo di connessione
3. Il server ritorna un segmento CA che contiene un ack che conferma il ricevimento del segmento CR (ack=x) ed un numero di sequenza (seq=y)
4. Il client riceve CA, l'ack gli fa capire che il suo CR è stato consegnato con successo
5. La connessione è stabilita per il client ed i segmenti vengono numerati da seq=x
6. Prima di mandare altri segmenti l'entità che ha iniziato la connessione (la quale ha ricevuto il segmento CA) deve a sua volta mandare un altro CA
7. Il server dopo aver ricevuto il CA dal client considera la connessione stabilita, i segmenti inoltrati dall'entità remota cominciano da seq=y
>Questa è la base del modello utilizzato nel protocollo TCP.

## Trasporto dati affidabile
Una volta ottenuti i numeri di sequenza è possibile utilizzare [[Livello datalink#Gestione degli errori|checksum]], [[Livello datalink#Go-back-n e Selective Repeat|go-back-n e selective repeat]] per aumentare l'affidabilità, tuttavia ci sono alcune differenze nel livello di trasporto.

Il livello di trasporto riceve uno **stream di byte**, ed l numero di sequenza si riferisce alla posizione del byte nello stream, ciò significa che il ricevitore dovrà avere un **buffer** (anche con go-back-n), questo perchè <u>non si conosce in anticipo la quantità di dati che arriveranno</u> (i.e. non c'è una dimensione fissa come per i frame).

La chiamata `Data.ind()` non è più bloccante, il ricevitore può ricevere dati mentre l'applicazione li processa, tuttavia essa potrebbe essere lenta, quando questo succede il buffer è sovracaricato di dati, e dato che la chiamata non è bloccante gli ack verranno inoltrato subito, bisogna quindi cercare un modo per comunicare al mittente di rallentare senza però bloccare gli ack in uscita.

Il livello di trasporto consente di eseguire il _piggybacking_ della grandezza della **sliding window** all'interno degli ack, in pratica il mittente contiene due variabili: $swin$ per indicare la dimensione della **sending window**, e $rwin$ per indicare la dimensione della **receiving window**.
>Il numero di segmenti unacknowledged non può essere più grande di $\min(swin,rwin)$.

![[Sliding window swin rwin.png]]

Le finestre possono pure avere dimensione pari a $0$ nel caso il ricevitore sia completamente sovraccarico, allora in questo caso il mittente si ferma e aspetta un ack.

È necessario monitorare il parametro $capacity\cdot delay$, infatti quando i pacchetti viaggiano in una rete locale si avrà una alta capacità ed un basso delay, ciò non accade però su internet.

### Connection release
Una volta che il traffico è stato inviato bisogna **chiudere la connessione** rendendolo noto ad entrambe le entità comunicanti:
- **Graceful release**: entrambe le entità segnalano la chiusura della connessione e aspettano di ricevere gli ack reciproci
- **Abrupt release**: in caso un'entità dovesse chiudere la connessione immediatamente (e.g. si sta spegnendo) cercherà di inviare una richiesta di disconnessione, la quale potrebbe anche non arrivare (a differenza del _graceful release_)

>[!Example]
>**Assumere MSL=120s, e numeri di sequenza da 32 bit, quale è il massimo throughput $S$ per assicurare che nessun errore sia possibile?**
>$$S=\frac{2^{32}\cdot 8}{120}\simeq 286Mb/s$$
>
>**È possibile avere due o più comunicazioni contemporanee tra la stessa coppia di host?**
>Si, ogni connessione è identificata dall'indirizzo numerico degli endpoint e due numeri di porta (che saranno diversi).
>
>**Quanti elaboratori bisogna cambiare a livello di internet, se si vuole modificare il livello di trasporto o di rete?**
>Per modificare il livello di trasporto è solo necessario far concordare le due entità comunicanti senza toccare internet in quanto tale livello è utilizzato tra due endpoint, mentre per il livello di rete bisognerà cambiare tutti i router su internet.
