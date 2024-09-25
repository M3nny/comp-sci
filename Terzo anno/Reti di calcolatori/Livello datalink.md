## Notazioni
Un **time-sequence diagram** descrive l'interazione tra due host comunicanti

![[Time sequence diagram.png]]

Indichiamo `DATA.req(bit-value)` come una system call per mandare bit, mentre `DATA.ind(bit-value)` una system call per ricevere bit.

I bit ricevuto possono essere **alterati** rispetto a quelli mandati originariamente, oppure potrebbero essere **ricevuti meno o più bit** del previsto a causa di un **disallineamento dei clock**.

Usiamo il **Manchester encoding** per tenere allineati i clock, al posto di mandare un segnale basso quando si inoltra uno $0$ ed un segnale alto quando si inoltra un $1$, è più conveniente muovere il segnale da basso ad alto per ogni simbolo.

## Livello datalink
La **Service Data Unit (SDU)** in questo livello è chiamata **frame**, e rappresenta una sequenza di bit che ha una lunghezza massima ed una particolare sintassi o struttura.

Abbiamo visto che i dispositivi si scambiano [[Livello fisico#Modulazione|segnali modulati]] e in certi casi il segnale portante è sempre attivo, per cui non si può semplicemente smettere di mandare segnali.

Dobbiamo quindi <u>codificare l'inizio e la fine di un frame</u>, per esempio possiamo usare la sequenza $111111$ per marchiare inizio e fine del frame, tuttavia il mittente deve assicurarsi che nella sua trasmissione tale sequenza non si presenti mai, altrimenti terminerebbe precocemente il frame.

Introduciamo il **bit stuffing**, ovvero l'inserimento di bit $0$ dopo ogni sequenza di $5$ bit posti a $1$, in questo modo si evita di terminare precocemente il frame.
Il ricevitore dopo aver ricevuto il marker iniziale rimuove i bit $0$ extra inseriti dal mittente dopo ogni sequenza di $5$ bit posti a $1$, finchè non riceve il vero marker finale che determina la fine del frame.

| Frame originale | Frame trasmesso                                     |
| --------------- | --------------------------------------------------- |
| $0111110$       | $01111110\space011111\space0\space01111110$         |
| $01111110$      | $01111110\space011111\space0\space10\space01111110$ |

Ciò porta a **overhead di protocollo**, ovvero dati extra che devono essere trasmessi per rendere la comunicazione possibile, tale overhead riduce il bit-rate disponibile dato dalle formule di Nyquist e Shannon.

>[!Attention]
>Più grande è il marker più overhead viene aggiunto, la probabilità di infilare $0$ per interrompere la sequenza che formerebbe il marker (anticipato) è minore, tuttavia se vengono trasmessi pochi bit il frame sarà composto in maggior parte dai marker.

Nelle reti moderne il _bit stuffing_ viene sostituito da un lungo **preambolo**, esso viene usato dal ricevitore per identificare l'inizio di un frame con una lunghezza determinata dall'**header** del frame, quindi non serve usare un marker alla fine, e di conseguenza il _bit stuffing_ non viene più usato.

### Aknowledging frames
Immaginando di avere un host $A$ che manda un video ad un altro host $B$, dove ogni frame rappresenta un secondo di video, se $B$ è troppo lento a processare il chunk il suo buffer comincerà a scartare frame prima o poi, sarebbe opportuno che il ricevitore comunicasse al mittente di trasmettere più lentamente, per questo utilizziamo i frame di **acknowledgment (ack)**.

Un _ack_ non trasporta dati, bensì informa soltanto se i dati precedenti sono stati ricevuti correttamente.
Un frame è quindi composto da un **header** composto da un bit: $0$ se il frame trasporta dati, $1$ per gli ack, e da un **payload** il quale rappresenta il contenuto dei dati effettivi oppure dell'ack.

Di seguito la **state machine** del mittente (sopra) e ricevitore (sotto), $D$ indica i dati, $C$ gli ack:

![[Datalink state machine.png]]

### Gestione degli errori
Per verificare la presenza di bit alterati nel frame possono essere usati vari metodi.

Un **bit di parità** aggiunto alla fine del frame indica se nel frame sono presenti un numero pari di bit posti a $1$ o meno, considerando la parità dei bit a $1$ si procede come segue: assumiamo che i dati siano $0011011$, il bit di parità aggiunto sarà $0$ dato che c'è un numero pari di bit a $1$, quindi i dati trasmessi saranno $00110110$ in questo modo è possibile capire se ci sono stati degli alteramenti ai bit.

>[!Attention]
>Questa tecnica non funziona se i bit alterati sono un numero pari oppure se il bit alterato è proprio il bit di parità.

Al livello **Internet Protocol (IP)** che vedremo più avanti viene usata la **internet checksum** che rappresenta un campo da $16$ bit per controllare se ci sono state alterazioni di bit.

>[!Example]
>Per praticità immaginiamo che la checksum sia formata da $4$ bit, e abbiamo in input i seguenti dati: $1100$ $0011$ $1010$ $1110$ $1001$.
>1. Computiamo la loro somma: $110000$
>2. Presenta un riporto, lo sommiamo ai $4$ least significant bits: $0000+11=0011$
>3. Eseguiamo il complemento a uno: $1100$
>
>La checksum ottenuta è $1100$.

>La checksum viene aggiunta nell'header dell'SDU.

Il ricevitore computerà la somma dei dati in arrivo (man mano che arrivano per massimizzare la performance), e se il risultato è composto da solo bit posti a $1$ il pacchetto sarà corretto.

>[!Example]
>Immaginiamo di ricevere: $\underbrace{1100}_\text{checksum}$ $1100$ $0011$ $1010$ $1110$ $1001$
>1. La somma sarà: $111100$
>2. Il riporto viene sommato ai $4$ LSB: $1100+11=1111$
>
>Avendo una sequenza di soli $1$ possiamo affermare che il pacchetto ricevuto è corretto.

Ora l'header è più grande ($16$ bit extra normalmente), inoltre i pacchetti devono essere allineati con i byte della checksum, ovvero dovrà avere un multiplo di $16$ byte, se ne possedesse meno bisognerà fare **padding**.

---
## Trasporto affidabile
È possibile **correggere errori** nei frame utilizzando dei **bit ridondanti**, ovvero si mandano molteplici volte lo stesso bit, $1$ potrebbe essere mappato a $111$.
Immaginando di ricevere $101$, possiamo assumere che il bit in origine fosse $111$, ci potrebbero essere casi come in $010$ dove il bit originale era $111$, quindi non è sempre una buona strategia, inoltre stiamo sprecando $2/3$ del bit-rate.

>[!Info]
>Come principio generale <u>si assume che reti funzionino ragionevolmente bene</u>, per cui la probabilità di errore è assunta essere bassa.
>Detto ciò non è conveniente investire molte risorse nel correggere/evitare errori, è più conveniente invece scartare i frame con errori e **richiedere la ritrasmissione**.

Dato che sappiamo come rilevare errori, possiamo adottare il seguente schema il quale utilizza un **timer** per re-inoltrare un frame, in assenza di ack dopo un certo lasso di tempo:
![[Ack exchange.png]]

Si pone un <u>problema quando è l'ack a non arrivare</u>, in questo caso il mittente re-inoltrerà lo stesso frame inviato precedentemente a causa del timer scaduto, <u>il ricevitore però non sa distinguere frame duplicati</u>.

Aggiungiamo all'header un **numero di sequenza** per distinguere i frame, l'implementazione più semplice involve l'alternarsi di un bit, questo schema è chiamato **Alternating Bit Protocol (ABT)**, all'interno di $D$ inseriamo anche il bit di sequenza:

**Mittente**:
![[Mittente ABP.png]]

**Ricevitore**:
![[Ricevitore ABP.png]]

Se ci aspettiamo un ack dopo ogni frame il _bottleneck_ sarà causato dal **Round Trip Time (RTT)**, ovvero il tempo di andata e ritorno dell'informazione, infatti più lungo è il link, più tempo ci vorrà per raggiungere l'altro host, questa è un'altra forma di **overhead di protocollo**.

### Go-back-n e Selective Repeat
Introduciamo il **pipelining**, ovvero l'invio di frame in _batch_, dobbiamo comunque evitare l'overflow di frame e l'affidabilità, risolviamo questi problemi tramite una **sliding window**; gli host si accorderanno su una dimensione $n$ della _sliding window_ da utilizzare, poi il mittente manderà $n$ frame e aspetterà l'ack del primo frame inoltrato, allora sposterà la finestra di una posizione.

Lo spazio per l'header è finito, per cui per non occupare tanto spazio utilizziamo una sliding window che utilizza l'operazione di modulo per ricominciare da capo, segue un esempio con sliding window di grandezza $\text{maxseq} = 3$:
![[Sliding window.png]]

**Mittente**:
- Mantiene un buffer che può contenere un'intera sliding window, i buffer sono mandati assieme quando il buffer è pieno, poi aspetta il primo ack, e avvia un timer
- Quando arriva un ack vengono rimossi tutti i frame acknowledged, l'ack è **cumulativo**, ricevere un `OK2` significa che anche i frame $0,1$ sono stati ricevuti, riavvia il timer solo se il buffer non è vuoto
- Se il timer scade, viene assunto che i frame non acknowledged presenti nel buffer sono stati persi, dunque li re-inoltra e riavvia il timer

**Ricevitore**:
- Accetta solo i frame che arrivano rispettando la sequenza
- Quando riceve un data frame ritorna un ack indicando l'ultimo frame della sequenza ricevuto, i frame che non rispettano la sequenza vengono scartati, questo tipo di ack è detto **cumulativo**

Lo spazio nell'header per la sequenza solitamente è pari a $2^n$, immaginiamo di avere una _sliding window_ larga $2^n$:
1. $A$ invia $2^n$ frame e poi aspetta l'ack
2. $B$ riceve tutti i frame ed inoltra gli ack, la sliding window ricomincerà subito da $0$ dato che possiede la grandezza massima, immaginiamo però che tutti gli ack vadano persi
3. $A$ andrà in timeout, allora re-inoltrerà tutti i frame
4. Dato che $B$ si aspetta i frame che cominciano da $0$, li prende come buoni quando in realtà sono già stati inoltrati precedentemente

Per evitare questo problema occorre usare una sliding window di dimensione massima $2^n-1$, ovvero `buffer.length() - 1`.

Go-back-n è facile da implementare in quanto necessità solo di due variabili da parte del ricevitore: `lastack` il quale indica l'ultimo numero di sequenza che è stato ricevuto, `next` per indicare il prossimo numero di sequenza previsto; il mittente invece usa tre variabili: `size(buffer)` che indica il numero di frame nel buffer, `seq` rappresenta l'ultimo numero di sequenza inoltrato, `unack` indica il numero di sequenza del primo frame non acknowledged ed un _timer_.

Le <u>performance di questo schema calano velocemente</u> con molte perdite di pacchetti per due ragioni: il <u>ricevitore non accetta frame che non rispettano la sequenza</u>, il <u>mittente ritrasmette tutti i frame unacknowledged</u>.

Con il **selective repeat** anche il ricevitore possiede un buffer, ed accetta tutti i frame che possono apparire nella _sliding window_ attuale (anche in disordine), in ogni ack il ricevitore riporta il <u>numero di sequenza prima dell'inizio dell'attuale sliding window</u> ed una <u>lista di frame arrivati in disordine</u>.

Ogni volta che il mittente invia un frame avvia un timer (quindi un timer per frame), quando riceve un ack per un determinato frame rimuove il suo timer, se un timer va in timeout rispedisce solo il frame corrispondente:
![[Selective repeat.png]]

La dimensione della finestra non deve essere obbligatoriamente uguale tra mittente e ricevitore, dovrebbe essere negoziabile così da adattarsi in base alle condizioni della rete.

Inoltre molto spesso la comunicazione è **bi-direzionale**, quando il ricevitore manderà dati al suo mittente potrà includere (**piggybacking**) assieme ai dati il messaggio di ack, evitando di mandare un frame esclusivamente per l'ack.
