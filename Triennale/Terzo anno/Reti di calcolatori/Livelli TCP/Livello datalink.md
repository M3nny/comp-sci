## Notazioni
Un **time-sequence diagram** descrive l'interazione tra due host comunicanti

![[Time sequence diagram.png]]

Indichiamo `DATA.req(bit-value)` come una system call per mandare bit, mentre `DATA.ind(bit-value)` una system call per ricevere bit.

I bit ricevuto possono essere **alterati** rispetto a quelli mandati originariamente, oppure potrebbero essere **ricevuti meno o più bit** del previsto a causa di un **disallineamento dei clock**.

Usiamo il **Manchester encoding** per tenere allineati i clock, al posto di mandare un segnale basso quando si inoltra uno $0$ ed un segnale alto quando si inoltra un $1$, è più conveniente muovere il segnale da basso ad alto per ogni simbolo.

## Livello datalink
La **Service Data Unit (SDU)** in questo livello è chiamata **frame**, e rappresenta una sequenza di bit che ha una lunghezza massima ed una particolare sintassi o struttura.

Abbiamo visto che i dispositivi si scambiano [[Livello fisico#Modulazione|segnali modulati]] e in certi casi il segnale portante è sempre attivo, per cui non si può semplicemente smettere di mandare segnali.

Dobbiamo quindi <u>codificare l'inizio e la fine di un frame</u>, per esempio possiamo usare la sequenza $01111110$ per marchiare inizio e fine del frame, tuttavia il mittente deve assicurarsi che nella sua trasmissione tale sequenza non si presenti mai, altrimenti terminerebbe precocemente il frame.

Introduciamo il **bit stuffing**, ovvero l'inserimento di bit $0$ dopo ogni sequenza di $5$ bit posti a $1$ (a causa del marker composto da sei $1$), in questo modo si evita di terminare precocemente il frame.
Il ricevitore dopo aver ricevuto il marker iniziale rimuove i bit $0$ extra inseriti dal mittente dopo ogni sequenza di $5$ bit posti a $1$, finchè non riceve il vero marker finale che determina la fine del frame.

| Frame originale | Frame trasmesso                                                  |
| --------------- | ---------------------------------------------------------------- |
| $0111110$       | $01111110\space011111\space\boldsymbol{0}\space0\space01111110$  |
| $01111110$      | $01111110\space011111\space\boldsymbol{0}\space10\space01111110$ |

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
Introduciamo il **pipelining**, ovvero l'invio di frame in _batch_, dobbiamo comunque evitare l'overflow di frame e assicurare l'affidabilità, risolviamo questi problemi tramite una **sliding window**; gli host si accorderanno su una dimensione $n$ della _sliding window_ da utilizzare, poi il mittente manderà $n$ frame e aspetterà l'ack del primo frame inoltrato, allora sposterà la finestra di una posizione.

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

Go-back-n è facile da implementare in quanto necessità solo di due variabili da parte del ricevitore: `lastAck` il quale indica l'ultimo numero di sequenza che è stato ricevuto, `next` per indicare il prossimo numero di sequenza previsto; il mittente invece usa tre variabili: `size(buffer)` che indica il numero di frame nel buffer, `seq` rappresenta l'ultimo numero di sequenza inoltrato, `unack` indica il numero di sequenza del primo frame non acknowledged ed un _timer_.

Le <u>performance di questo schema calano velocemente</u> con molte perdite di pacchetti per due ragioni: il <u>ricevitore non accetta frame che non rispettano la sequenza</u>, il <u>mittente ritrasmette tutti i frame unacknowledged</u>.

Con il **selective repeat** anche il ricevitore possiede un buffer, ed accetta tutti i frame che possono apparire nella _sliding window_ attuale (anche in disordine), in ogni ack il ricevitore riporta il <u>numero di sequenza prima dell'inizio dell'attuale sliding window</u> ed una <u>lista di frame arrivati in disordine</u>.

Ogni volta che il mittente invia un frame avvia un timer (quindi un timer per frame), quando riceve un ack per un determinato frame rimuove il suo timer, se un timer va in timeout rispedisce solo il frame corrispondente:
![[Selective repeat.png]]

La dimensione della finestra non deve essere obbligatoriamente uguale tra mittente e ricevitore, dovrebbe essere negoziabile così da adattarsi in base alle condizioni della rete.

Inoltre molto spesso la comunicazione è **bi-direzionale**, quando il ricevitore manderà dati al suo mittente potrà includere (**piggybacking**) assieme ai dati il messaggio di ack, evitando di mandare un frame esclusivamente per l'ack.

---
## Topologie di rete

Una rete **full mesh** costituisce un grafo [[Tipologie#Grafo completo|completamente connesso]].

| Vantaggi                               | Svantaggi                                  |
| -------------------------------------- | ------------------------------------------ |
| Ogni comunicazione ha un link dedicato | Possiede $\frac{n(n-1)}{2}$ link           |
| Resiste al fallimento di link          | Possiede $n-1$ interfacce di rete per host |

Una rete a **bus** è rappresentata da un singolo link che passa attraverso tutti gli host.

| Vantaggi        | Svantaggi                                                             |
| --------------- | --------------------------------------------------------------------- |
| Molto economica | Non scalabile                                                         |
|                 | Non è robusta, se il bus si rompe la rete viene spezzata in due parti |

Una rete ad **anello** è simile ad una rete a _bus_, ma in questo caso gli host saranno collegati ad un link ad anello, il quale nel caso di rottura in un punto potrebbe far ancora comunicare tutti gli host.

| Vantaggi               | Svantaggi     |
| ---------------------- | ------------- |
| Un link più affidabile | Non scalabile |

Una rete a **stella** è costituita da un **centro stella** verso il quale tutti gli host sono connessi.

| Vantaggi                                     | Svantaggi                                             |
| -------------------------------------------- | ----------------------------------------------------- |
| Un link per host, in totale $n-1$            | Se il centro stella si rompe la rete non funziona più |
| Gestione migliore a causa del centro stella  |                                                       |
| Quasi resistente a malfunzionamenti dei link |                                                       |

Una rete ad **albero** estende il concetto della _rete a stella_, infatti al posto di avere un _centro stella_ (radice dell'albero), anche i suoi figli potranno fare da centro stella per i nipoti.

| Vantaggi                          | Svantaggi                                   |
| --------------------------------- | ------------------------------------------- |
| Un link per host, in totale $n-1$ | Se un link si rompe, la rete viene spezzata |

Quando una comunicazione deve attraversare molteplici link viene chiamata **multi-hop**, in questo tipo di comunicazione il **bottleneck** risiede nel link con meno capacità nel cammino.
![[Bottleneck.png]]

Se $H1$ e $H2$ comunicano con $H4$ contemporaneamente il loro bit-rate sarà limitato a $500Mb/s$ perchè condividono lo stesso link.
>In una rete gerarchica (e.g. ad _albero_) la capacità del link deve aumentare con l'avvicinarsi alla radice.

## Media access
Condividere dei **media** in una rete a _stella_ non causa collisioni in quanto i moderni cavi ethernet usano due percorsi separati per inviare e ricevere.
In una rete a _bus_ questo però è un problema dato che i segnali potrebbero sovrapporsi e quindi verranno scartati, si dovrà implementare uno scheduling di frame per evitare collisioni.

Una **rete wireless** è organizzata come una rete a _stella_, ma fisicamente si comporta come una rete a _bus_, il ricevitore possiede una singola radio, se due host comunicano allo stesso tempo c'è una collisione.

### Divisione della frequenza
È possibile usare una [[Livello fisico#Modulazione|frequenza]] diversa per ogni comunicazione così da evitare collisioni.
Il **Wi-Fi** opera su diverse frequenze chiamate **canali**, esso cercherà il canale non usato da altre reti wi-fi così lo spazio fisico potrà essere condiviso da più reti, una radio può usare un solo canale alla volta però, quindi gli host collegati ad un **Access Point (AP)** dovranno usare la stessa frequenza, e quindi schedulare i propri messaggi.

#### TDMA
In un **Time-Division Multiple Access (TDMA)** se la rete ha $m$ terminali, il tempo viene suddiviso in $m$ slot di lunghezza fissa, con uno **slot** assegnato ad un terminale, gli slot vengono dunque iterati, ed ogni terminale potrà trasmettere al frame $i$.
![[TDMA.png]]

Quando tutti i terminali hanno qualcosa da trasmettere, la rete funziona a piena capacità, diciamo quindi che è **saturata**, se però solo un terminale vuole comunicare, comunque dovrà aspettare il momento del suo frame $i$.
>Funziona bene nel caso peggiore, ma male nel caso medio.

>[!Example]
>**Considera un sistema TDMA dove il bit-rate è $b=100Mb/s$, ci sono $n=5$ terminali, e ad ognuno è assegnato uno slot di dimensione $s=1ms$**.
>
>- Il numero massimo di dati trasmessi per slot è:
>$s\cdot b=10^8\cdot 10^{-3}=10^5=100kb$.
>- Il numero massimo di dati trasmessi da un terminale in un secondo è:
>Un slot ha dimensione $1ms$, in un secondo ci sono $1000/5=200$ slot per terminale, il bit-rate in un secondo per terminale è $10^5\cdot 200=2\cdot 10^7=20Mb/s$.
>- Immaginando che un terminale voglia mandare $250kb$, il tempo che impiega è il seguente:
>Ogni $5ms$ può inoltrare $100kb$, quindi ci vorranno $2.5$ slot, nel caso peggiore ci metterà $15.5ms$, in quello migliore $10.5ms$.

#### Random Access
In questo sistema i terminali cercano di trasmettere e se avviene una collisione, essa viene rilevata ed il frame viene inviato di nuovo.

**ALOHA** è il primo sistema di questo tipo, noi utilizzeremo la sua versione "slotted" dove ogni terminale deve essere sincronizzato ed il tempo è diviso in slot: **S-ALOHA**.

La differenza con il _TDMA_ è che ogni terminale può trasmettere in qualsiasi slot.

Quando viene ricevuto una SDU dal layer superiore si aspetta il prossimo slot e poi si trasmette, indichiamo con $q_a$ la probabilità che un terminale abbia qualcosa da trasmettere, se un altro terminale vuole trasmettere nello stesso slot entrano entrambi nello stato **backlogged**, ritrasmetteranno nel prossimo slot con probabilità $q_b>q_a$, un terminale ritorna nel suo stato normale una volta che ha trasmesso con successo, se un terminale riceve un nuovo frame da inviare mentre è _backlogged_ lo scarta.
>$q_a$ dipende dal traffico in entrata, mentre $q_b$ è un parametro della rete.

![[S-ALOHA.png]]

Sia $G$ il carico del sistema (numero medio di frame da trasmettere per slot) e $P_S$ la probabilità di trasmettere correttamente un frame, si ha:
$$P_S=G\cdot e^{-G}$$
>S-ALOHA ha una **capacità massima** di $\frac{G}{e}$ con $m$ terminali.

![[Throughput S-ALOHA.png]]

Notiamo che con pochi frame da spedire la rete funziona bene, con molti (anche relativamente pochi) osserviamo il **collasso della congestione**, ovvero la performance del sistema diminuisce vertiginosamente con l'aumentare del carico.
>Nei sistemi TDMA con un alto carico si avranno meno risorse, ma non collasserà mai a differenza dei sistemi S-ALOHA.

>[!Example]
>![[Esercizio datalink.png]]
>I link dello stesso colore condividono lo stesso sistema:
>- Rosso: TDMA con frequenza da $20MHz$ a $8$ canali con $3$ slot
>- Blu: S-ALOHA con frequenza da $20MHz$ a $16$ canali
>- Verde: S-ALOHA con frequenza da $5MHz$ a $8$ canali
>- Nero: link dedicati che non fanno da bottleneck
>
>Si assumano link perfetti (usare [[Livello fisico#Teorema di Nyquist|Nyquist]]).
>
>**Assumere che $C1$ con un constant bit-rate (CBR) di $40Mb/s$ sia l'unico terminale a generare traffico verso internet. Riesce a trasmettere tutto il suo traffico?**
>La capacità della rete rossa è $C_r=2\cdot 20\cdot \log_2(8)=120Mb/s$, ma TDMA fornisce $1/3$ della capacità ad ogni rete ($R1,R2,R3$) mentre la capacità della rete blu è $C_b=2\cdot 20\cdot\log_2(16)=160Mb/s$ e dato che c'è un solo terminale esso può sfruttare tutta la capacità di S-ALOHA, quindi **si** $C1$ riesce ad inviare tutto il traffico se è l'unico a trasmettere.
>
>**Assieme a $C1$ ora anche $C2-C20$ inoltrano un CBR di $1Mb/s$ verso $R2$. Riescono a trasmettere tutto il traffico?**
>La massima capacità di S-ALOHA nella rete blu è $\frac{C_b}{e}=\frac{160}{e}\simeq 59Mb/s$, il traffico totale $C1-C20$ è dato da $40Mb/s+19Mb/s$, per cui **si**, la rete riesce a trasmettere tutto il traffico.
>
>**Situazione analoga alla precedente, ma ora $C2-C20$ inviano traffico a internet.**
>Il traffico aggregato nel link $R2-R1$ è di $59Mb/s$ che è più della capacità effettiva del TDMA ($40Mb/s$), per cui **no**, il link rosso è un bottleneck.
>
>**Ora $C1$ è l'unico a generare traffico nella rete, in particolare ha un CBR di $40Mb/s$ e vuole inoltrarlo verso $C'1$. Riesce ad inoltrare tutto il traffico?**
>Riuscirà ad arrivare fino a $R3$ senza problemi, ma poi si deve attraversare il link verde che usa un sistema S-ALOHA, con capacità ideale $C_g=2\cdot 5\log_2(8)=30Mb/s$ la quale verrà sfruttata tutta (essendo $C1$ l'unico terminale a generare traffico), tuttavia non basta per far passare il traffico di $C1$, quindi **no**, non riesce a far passare il traffico, dato che $R3-C'1$ crea un bottleneck.
>
>**$C1$ genera un CBR di $3Mb/s$ verso $C'1$, mentre $C'2-C'20$ generano $1.42 Mb/s$ vero internet. Quale è la velocità di comunicazione massima da $C1$ a $C'1$?**
>La rete verde ha una capacità effettiva $C_g=\frac{30}{e}\simeq 11Mb/s$, il carico di $R3$ è pari a $1.42\cdot 19 + 3=30Mb/s$, però solo $11Mb/s$ saranno consegnati, quindi la rete verde è il bottleneck.
>
>**Situazione analoga alla precedente, ma ora $R4$ genera $30Mb/s$ verso internet. Riesce $R4$ ad inoltrate tutto il suo traffico?**
>La rete verde riesce a trasportare $11Mb/s$, mentre la rete rossa $40Mb/s$, dato che ci saranno anche i frame di $C1$ e $C'2-C'20$ essa sarà a pieno carico, per cui nel link $R3-R1$ passeranno $11+30=42Mb/s$, il che crea un bottleneck, quindi **no**, non riuscirà ad inoltrare tutto il traffico senza perdere frame.
>
>**Situazione analoga alla precedente, ma ora $C'2-C'20$ generano $3Mb/s$ al posto di $1.42$. Riesce $R4$ ad inoltrare tutto il suo traffico?**
>Il carico totale su della rete verde è pari a $3\cdot 19+3=60Mb/s$, per cui la rete è al doppio della sua capacità ($G=2$), la sua efficienza sarà pari $2\cdot e^{-2}=0.27$, quindi il traffico in uscita dalla rete verde è di $30\cdot 0.27=8Mb/s$, sommando il traffico di $R4$ si avrà un traffico di $38Mb/s$ in $R3-R1$, quindi **si** $R4$ grazie al collasso della rete verde riuscirà a consegnare il suo traffico.

>Il livello datalink non è affidabile, può scartare molti frame, per cui i livelli superiori dovranno tenerlo in considerazione e cercare di compensare.