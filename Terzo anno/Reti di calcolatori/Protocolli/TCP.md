Il [[Livello di rete|livello di rete]] è **conectionless**, il suo servizio è far comunicare tra loro degli host identificati da IP.
## UDP
Lo **User Datagram Protocol (UDP)** fornisce un servizio di trasporto **connectionelss** sopra il livello di rete.

Il vantaggio è che consente a più applicazioni di un host di interagire con altre applicazioni di un altro host tramite un numero di porta.

Un **header** UDP contiene quattro campi da $16$ bit ciascuno:
- Porta sorgente
- Porta di destinazione
- Lunghezza
- Checksum

Dato che i numeri di porta sono definiti tramite $16$ bit, si potranno avere $2^{16}=65536-1=65535$ processi differenti associati ad una porta in un host.

Le porte hanno tre tipi di **range**.
- **Well-Known** ($0-1023$): usate per applicazioni server particolari, è necessario che abbiano permessi da amministratore
- **Registered** ($1024-49151$): usate non ufficialmente da alcuni servizi, è necessario chiedere a IETF nel caso un protocollo volesse usare una di queste porte
- **Dynamic** ($49152-65535$): assegnate dinamicamente ai processi client

Le applicazioni che sfruttano questo protocollo non hanno bisogno di mantenere uno stato della connessione, ne favoriscono applicazioni real time, e anche i DNS.

---
## TCP
Il **Transmission Control Protocol (TCP)** fornisce un servizio di trasporto **affidabile** e **connection-oriented** al di sopra del livello di rete.

L'**header** è formato come segue:
- $16$ bit per **porta sorgente** e di **destinazione**
- $32$ bit per **numero di sequenza** e **numero di ack**
- $4$ bit per **data offset** indica la dimensione dell'header

Al suo interno troviamo varie **flag**, tra cui:
- `SYN`: usata durante lo stabilimento della connessione
- `FIN`: usata durante la chiusura della connessione
- `RST`: chiude la connessione in caso di problemi
- `ACK`: indica il numero di ack è valido
- `window`: dimensione della receiving windows del mittente
- `checksum`: eseguita su tutto il segmento e alcuni campi dell'indirizzo IP

#### PSH e Urgent Pointer
Una applicazione ricevente [[Livello di trasporto#Trasporto dati affidabile|possiede un buffer]], i dati ricevuti quindi potrebbero non essere inoltrati subito all'applicazione, in alcuni casi questo approccio è **dannoso**.

Un segmento in entrata con flag `PSH` impostata farà svuotare immediatamente il buffer e manderà tutti i dati all'applicazione (rispettando i numeri di sequenza).

Mentre se possiede `URG`, il ricevitore dovrà passare subito quell'informazione all'applicazione ignorando i numeri di sequenza.
>`PSH`e `URG` non si usano più o sono poco usati.

#### Connection Set-Up
L'unica differenza con il [[Livello di trasporto#Three way handshake|3-way handshake]] è l'interpretazione dei numeri di `ACK`, infatti un `ACK=X+1` vuol dire che il ricevitore ha ricevuto tutti i dati fino a `X`, si aspetta ora `X+1`.
![[TCP connection set-up.png|700]]

Il TCP consente anche la <u>comunicazione tra host dello stesso tipo</u> (e.g. 2 server).
![[FSM TCP connection.png]]

Un campo importante è il **Maximum Segment Size (MSS)**, esso rappresenta il segmento di dimensione massima che un host può ricevere.
Solitamente viene impostato della dimensione del più grande frame ricevibile, in modo da evitare la frammentazione.

Per ogni connessione in atto, il TCP mantiene un **Transmission Control Block (TCB)**, il quale è un insieme di informazioni necessario per mantenere lo stato della connessione.

#### Connection release
Il TCP supporta due tipi di rilascio della connessione.

**Graceful release**
Accade tramite un segmento `FIN` con il numero di sequenza `x`, ovvero vuol dire che il mittente ha finito di mandare tutti i dati, l'ultimo byte valido è `x`.
Il ricevente sarà ancora in grado di richiedere dati persi prima di `x`, e aspetterà il `FIN` dal mittente.
>I segmenti `FIN` devono essere riconosciuti.

**Abrupt release**
Accade tramite un segmento `RST`, appena ricevuto o inoltrato, il TCB viene cancellato.
>Non si può rispondere ad un `RST` con un altro `RST` (per evitare il "ping-pong").

Inoltre il **Time Wait State** indica un tempo specificato dall'RFC, in cui un peer deve mantenere il TCB in memoria prima di poterlo cancellare definitivamente.
Questo è dovuto al fatto che un `ACK` rispetto all'ultimo `FIN` potrebbe essere perso e quindi deve essere ritrasmesso.

### Trasporto affidabile
Nel protocollo originale TCP utilizza [[Livello datalink#Go-back-n e Selective Repeat|Go-back-n + Selective Repeat]].

Il <u>TCB mantiene tutte le variabili</u> utilizzate per mantenere lo stato della connessione, vediamo di seguito il suo contenuto.

**Contenuti statici**
- **Indirizzi IP** dei due peer
- **Sending buffer**: memorizza i dati non ancora riconosciuti
- **Receiving buffer**: dati ricevuto dall'altro peer che però non sono ancora stati consegnati all'utente (esso potrebbe essere lento a processarli)

**Contenuti dinamici**
- **Stato corrente** della macchina a stati finiti (vedi sopra)
- **Maximum Segment Size (MSS)**
- `snd.nxt`: numero di sequenza del prossimo byte in uscita
- `snd.una`: numero di sequenza precedentemente inviato, ma non ancora riconosciuto
- `snd.wnd`: dimensione della _sliding window_ attuale
- `rcv.nxt`: numero di sequenza del prossimo byte che dovrebbe arrivare al ricevitore
- `rcv.wnd`: dimensione della _sliding windows_ attuale dichiarata dall'altro peer

Durante la fase di **invio**, il TCP:
- Controlla che il _sending buffer_ non contenga più dati di quelli dichiarati in `rcv.wnd`
- Controlla che si siano al massimo MSS byte piazzati nel payload del segmento
- Il numero di sequenza di questo segmento è impostato a `snd.nxt` e poi la variabile `snd.nxt` è incrementata
- Il numero di acknowledgement è impostato a `rcv.nxt` ed il campo _window_ del segmento è calcolato in base allo spazio libero rimanente nel _receiving buffer_
- I dati una volta inviati rimangono memorizzati in caso serva ritrasmetterli

Quando un segmento **arriva**, se la flag ACK è attiva:
- Imposta `rcv.wnd` al valore di _window_ del segmento ricevuto
- Compara l'acknowledgement number a `snd.una`
- I dati riconosciuti sono rimossi dal _sending buffer_ e `snd.una` viene aggiornato

Se nel ricevimento **il segmento contiene dei dati**, il ricevitore:
- Compara il numero di sequenza a `rcv.nxt`, se sono uguali, i dati volendo possono essere trasmessi all'utente, e `rcv.nxt` viene aggiornato
- Se è possibile inviare altri dati in sequenza presenti nel _receiving buffer_ all'utente si aggiorna `rcv.nxt` ancora
- Il payload del segmento è piazzato nel _receiving buffer_
- Manda l'ACK con la dimensione della _window_ aggiornata

---
### Quando inviare i dati
Volendo si potrebbero inviare i dati, non appena il _sending buffer_ non è più vuoto, tuttavia così si sprecherebbe capacità di rete.

Oppure si potrebbe aspettare di avere il _sending buffer_ almeno pieno quanto la dimensione di MSS, nel caso in cui però ci mettesse tanto a riempirsi, i dati al suo interno diventerebbero obsoleti ancora prima di essere inviati.

Un trade-off viene offerto dall'**algoritmo di Nagle**.
```
if len(data) >= MSS and rcv.wnd >= MSS:
	send one MSS-sized segment
else:
	if there are unacknowledged data:
		place data in buffer until acknowledgment has been received
	else:
		send one TCP segment containing at most rcv.wnd data
```

Questo algoritmo rende più probabile che segmenti grandi siano inoltrati, infatti delle misure effettuate su internet hanno mostrano che la maggior parte dei pacchetti sono lunghi quanto la MTU del link layer oppure sono di $0$ byte (ACK).
>Questo algoritmo non funzionerebbe bene nel caso di applicazioni real-time.

#### Window scale
Essendo che l'header TCP non può essere esteso, la dimensione della finestra non può essere aumentata, venne poi introdotta una nuova estensione del protocollo in cui viene specificato un **Window Scale Option**, questo campo è scambiato soltanto nei pacchetti `SYN` e `SYN-ACK` e contiene un numero $0\leq S\leq 14$.

La dimensione della finestra viene shiftata di $S$ bits, ovvero si avrà: $\text{rcv.wnd}\cdot2^S$.

#### Retransmission Time Out (RTO)
Idealmente l'RTO è poco più grande di un RTT (round trip time), quindi se entro un RTT non è arrivato l'ACK, bisogna ritrasmettere.

Il problema è venire a conoscenza dell'RTT, per farlo bisogna misurarlo, ciò porta ad altri due problemi:
- Misurare l'RTT in una connessione che perde pacchetti, rende anch'esso soggetto ad errori
- L'RTT cambia durante una connessione, per cui dobbiamo approssimarlo

Venne introdotta un'altra estensione del protocollo la quale aggiunge dei **timestamps**.
In ogni segmento TCP due timestamps vengono aggiunti, ovvero, quello corrente e l'ultimo ricevuto dall'altro peer, ciò ci consente di calcolare l'RTT dall'ultimo segmento ricevuto, non importa se esso è stato ritrasmesso o meno.

Abbiamo visto che i numeri di sequenza non devono ricominciare da capo prima del [[Livello di trasporto#Connection-oriented service|Maximum Segment Life]], i timestamps risolvono anche questo problema, infatti se un segmento è molto in ritardo, anche se il numero di sequenza ha ricominciato da capo (e quindi ci potrebbe essere una ambiguità), il timestamp rivelerà che il segmento è vecchio.

Assumiamo ora di essere a conoscenza del RTT, utilizziamo l'**algoritmo di Von Jacobson** per ottenere una **media mobile esponenziale** della sequenza di valori RTT.
>Se il ricevitore è congestionato, non può gestire molti pacchetti, per cui il mittente dovrà rallentare.

Il mittente potrebbe ricevere degli ACK con ordine diverso dal previsto, ad esempio potrebbe ricevere `seq=Y<X` quando aveva inoltrato `seq=X`, concluderà che il segmento è stato perso e dovrà ritrasmetterlo, tuttavia potrebbe essere che semplicemente l'altro ACK sta per arrivare.

La **ritrasmissione veloce** prevede che la ritrasmissione prima della scadenza del timer possa avvenire dopo aver ricevuto tre copie dello stesso ACK.
Quindi anche se il RTO non è scaduto, ma il mittente riceve tre copie dello stesso ACK, probabilmente il pacchetto è stato perso e dovrà ritrasmetterlo.

#### Delayed ACKs
La maggior parte delle volte la comunicazione è mono-direzionale, ovvero il ricevitore manderà in maggior parte solamente degli ACK, la strategia di **delayed ACKs** consente di mandare un ACK dopo un certo intervallo, e non uno per ogni segmento, in modo da riconoscere più segmenti alla volta.
>Non funziona bene con l'_algoritmo di Nagle_.

#### Selective ACKs
Il [[Livello datalink#Go-back-n e Selective Repeat|go-back-n]] non funziona bene quando ci sono grandi perdite, in quanto la finestra non si sposta, nel TCP il ricevitore può memorizzare dati fuori sequenza (potrà riconoscere solo quelli in sequenza però), con i **selective ACKs**, il ricevitore potrà riconosce i dati arrivati fuori sequenza purchè essi siano **contigui**.

Ad esempio gli ACK potrebbero contenere i seguenti intervalli:
$$[1100-1200],[1250-1500],[1800-1900]$$
L'ACK conterrà anche l'acknowledgement number, diciamo essere $850$, questo è interpretato dal mittente come: il ricevitore ha ricevuto correttamente tutti i byte prima di $850$, e gli intervalli indicati.
>Spetta al mittente decidere cosa fare.

---
## TCP performance
Nel protocollo [[Livello datalink#Go-back-n e Selective Repeat|go-back-n]] esistono due _window size_, quella del mittente ($swnd$) e quella del ricevitore ($rwnd$) i dati inoltrati saranno al massimo:
$$window=\min(swnd,rwnd)$$
- $rwnd$ è **ridotta** quando un segmento è inviato ma l'ACK deve ancora arrivare, questo perchè il mittente deve tenere nel buffer i dati non ancora riconosciuti
- $swnd$ è **ridotta** quando il segmento è arrivato correttamente ma non è stato raccolto dall'applicazione

Secondo l'**algoritmo di Nagle**, il mittente invierà tanti segmenti di dimensione MSS quanti $swnd$ consente (praticamente tutti assieme), diciamo che ciò accade nell'istante $t_0$.

Assumiamo che entrambi i peer abbiano una capacità elevata e che tutti i segmenti arrivino a destinazione, allora essi arriveranno all'istante $t_0+\frac{RTT}{2}$.
>$\frac{RTT}{2}$ è il tempo dell'andata di un segmento.

Il ricevitore poi invierà un ACK cumulativo, e all'istante $t_0+RTT$ il mittente riceverà gli ACK, svuoterà il buffer e ricomincerà.

Per cui ad ogni RTT al massimo $window$ dati sono inviati, il **massimo throughput** è dato da:
$$\max throughput=\frac{window}{RTT}$$
Questa formula è applicabile anche nel caso in cui la finestra venga ridotta, ad esempio se la finestra del ricevitore diminuisce perchè è lento, si avrà alla fine $window'<window$ con throughput $\frac{window'}{RTT}$.

### Congestione della rete
Assumiamo ora che ci sia una congestione nella rete, ciò non implica problemi di ricezione da parte del ricevitore, assumiamo quindi che riceva correttamente.

Una congestione è rilevata dal mittente come una **perdita di pacchetti**, infatti l'ACK cumulativo non gli consentirà di svuotare tutto il _sending buffer_, tuttavia la _receiver window_ non sarà ridotta.

Se un mittente ha sempre dati da inoltrare, potrebbe semplicemente inviare tutto il buffer di nuovo (contenente vecchi dati non riconosciuti e quelli nuovi).
>Ignoriamo per questo esempio la strategia di _ritrasmissione veloce_.

Per cui i dati inviati saranno sempre $\frac{window}{RTT}$ anche se i dati nuovi saranno mediamente $\frac{window}{2\cdot RTT}$ (a causa di metà buffer con dati vecchi non riconosciuti).
In questo modo però il router continuerà ad essere **congestionato**, dobbiamo trovare un modo per rilevare la congestione del router e ridurre $swin$.

Il problema della congestione nasce dal fatto che <u>il mittente dall'inizio della connessione invierà il massimo throughput possibile</u>, ovvero $\frac{window}{RTT}$, la dimensione della finestra dovrebbe essere inizialmente piccola e crescere nel tempo.

#### Congestion window
Introduciamo una **congestion window** $cwnd$ inizializzata ad un valore fisso:
$$cwnd_0=10\cdot MSS$$
>$cwnd_0$ indica il valore fisso di partenza.

ad ogni istante la dimensione della finestra sarà data da:
$$window=\min(swnd,rwnd,cwnd)$$
introduciamo anche il parametro **slow-start threshold** $sstrash$, inizializzato a qualche valore piccolo.

L'**algoritmo slow start** funziona come segue:
- Ad ogni $RTT$ se tutti i segmenti vengono riconosciuti, $cwnd=2\cdot cwnd$
- Se $cwnd>sstrash$, allora ad ogni $RTT$, $cwnd\mathrel{+}=MSS$

Esistono due eventi che sono interpretati come congestione:
- **Congestione mite**: $3$ ACK sono ricevuti con lo stesso numero di sequenza, viene provata una _ritrasmissione veloce_ la quale ha successo

$$\begin{align}
&cwnd'=cwnd\\
&cwnd=sstrash\\
&sstrash=\frac{cwnd'}{2}
\end{align}$$

- **Congestione grave**: la _ritrasmissione veloce_ va in timeout

$$\begin{align}
&cwnd'=cwnd\\
&cwnd=cwnd_0\\
&sstrash=\frac{cwnd'}{2}
\end{align}$$
![[TCP congestion.png]]

---
## Network sockets 
Un **socket** è un'interfaccia standard tra le applicazioni ed il livello di trasporto, definita da POSIX.

Le **famiglie** socket sono le seguenti:
- `AF_INET`: per gli indirizzi IPv4
- `AF_INET6`: per gli indirizzi IPv6
- `AF_UNIX`: per i messaggi tra processi

I **tipi** di socket sono i seguenti:
- `SOCK_STREAM`: per usare il TCP
- `SOCK_DGRAM`: per usare l'UDP

La **creazione** di un socket (in C) avviene tramite la funzione:
```c
int socket(int family, int type, int protocol)
```

La funzione ritorna un numero non-negativo intero simile ad un [[Linux#File system|file descriptor]].
