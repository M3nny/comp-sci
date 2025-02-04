Lo standard **Wi-Fi (IEEE 802.11)** descrive il layer fisico e datalink per le comunicazioni wireless all'intero di una LAN.

Il processo di standardizzazione delle varie versione del protocollo 802.11 è lento, per cui i produttori hanno creato la **Wi-Fi alliance**, la quale produce versioni dei nuovi standard in sviluppo "in anteprima" le quali contengono solo le features stabili ancora prima che il nuovo standard sia finito.

### Layer fisico
Le versioni più comuni del WI-Fi utilizzano:
- Bande di **frequenza** attorno ai $2.4$ o $5 GHz$
- **Bitrate** da $11-6700$ Mbps
- **Portata** attorno ai $50$ metri all'interno, mentre $300$ metri all'esterno

Il Wi-Fi normalmente opera su **frequenze senza licenza**, ovvero le **bande ISM (Industrial, Scientific and Medical)**.

Le bande ISM utilizzate sono principalmente due:
- $2.4 - 2.4835$ (conosciuta come banda a $2.4 GHz$)
- $5.17 - 5.33$ e $5.49-5.710$ (conosciuta come banda a $5 GHz$)

Le bande ISM _non sono_ solo usate dal Wi-Fi, soffrono quindi dall'interferenza di altri dispositivi, per questo motivo e altri motivi di sicurezza, la <u>potenza di trasmissione massima è limitata per legge</u>.

La banda usata dal Wi-Fi è divisa in **canali**, ovvero sotto-bande che possono operare quasi indipendentemente, per $2.4 GHz$ abbiamo $11$ canali, mentre per la $5GHz$ ne abbiamo $19$.
>I canali reali potrebbero essere di più tuttavia quelli usabili dipendono dal paese e dalle leggi.

Lo standard $802.11b/g$ prevedeva soltanto $3$ **canali completamente separati**, ciò permetteva di avere $3$ reti separate senza interferenze, nel caso ce ne fossero state di più, allora si causavano dei disturbi a vicenda.

Con gli standard successivi venne introdotta la possibilità di **aggregare i canali**, tuttavia, sebbene l'ampiezza di banda aumenti, aumentano anche i rischi di interferenza con le reti vicine.

### Layer datalink
Esistono tre **tipi di frame** nello standard 802.11:
- **Management frames**: non contengono traffico, vengono usati per gestire le comunicazioni
- **Control frames**: sono usati per gestire l'accesso ai canali
- **Data frames**: trasportano il traffico effettivo

Un **Basic Service Set (BSS)** è l'unita più piccola in grado di creare una rete Wi-Fi, noi ci concentriamo sul modello **"infrastrutturato"** che è il più comune.
Questo modello è composto da un AP e qualche stazione connessa, le stazioni non comunicano tra loro rendendo l'AP il **centro stella**.

Un BSS è **identificato da un BSSID** il quale è un numero da $48$ bit costruito utilizzando l'indirizzo MAC dell'AP.

Ogni AP può scegliere un **SSID (Service Set ID)**, il quale è un nome _"leggibile"_ per il BSS, configurabile dall'amministratore.

Molteplici BSS possono essere collegati tra loro usando un **DS (Distribution Service)**, il quale è un link tra vari AP che creano BSS individuali, parliamo quindi di un **Extended Service Set (ESS)**. 
>Solitamente il link è un cavo gigabit.

Ogni AP emette dei frame periodici, detti **beacon frames**, i quali contengono informazioni riguardanti al BSS, tra cui: BSSID, SSID.
Una stazione che vuole unirsi alla rete deve attraversare tre passi:
- **Scansione**
- **Autenticazione**: 
- **Associazione**

La _scansione_ può avvenire in **modo passivo** se ascolta tutti i canali in attesa di qualche frame da un beacon, oppure in **modo attivo** se manda una **probe-request** su tutti i canali, in modo da ottenere una risposta da tutti gli AP.

Mentre la fase di _autenticazione_ e _associazione_ viene eseguita una sola volta per creare un canale sicuro.

L'**header MAC** per i _data frame_ è formato dai seguenti campi:
- **Frame control**
- **Duration**
- **3 indirizzi**
- **Sequence control**
- **CRC**

I pacchetti IP sono incapsulati in un frame Wi-Fi utilizzando l'**header LLC**.

### Access control
L'obiettivo del MAC è coordinare l'accesso a media condivisi, quando si utilizza un media condiviso le stazioni non possono comunicare allo stesso istante, devono infatti **evitare le collisioni**.

Un modo semplice per evitare le collisioni è controllare se c'è qualcun altro che sta già trasmettendo, questo viene chiamato **carrier sensing**.
Il Wi-Fi utilizza un layer MAC del tipo **CSMA/CA (Carrier Sensing Multiple Access / Collision Avoidance)**.
>Lo stato di una canale può essere **inattivo, occupato o impegnato**.

L'obiettivo del datalink è anche quello di <u>massimizzare il tempo in cui il canale rimane impegnato</u>, tuttavia proprio perchè serve coordinarsi, non si raggiungerà mai la massima efficienza proprio perchè bisogna stare in attesa o mandare/ricevere segnali di controllo.

Esistono due modi in cui il layer datalink può funzionare:
- **Point Coordination Function (PCF)**: la coordinazione viene gestita da un singolo AP il quale manda ai terminali una schedule in cui possono inviare frame, questo modo implementa un [[Livello datalink#TDMA|TDMA centralizzato]]
- **Distribuited Coordination Function (DCF)**: implementa uno schema ad accesso casuale simile ad [[Livello datalink#Random Access|ALOHA]]

### Distribuited Coordination Function (DCF)
Come visto precedentemente un nodo che vuole trasmettere un frame deve prima rimanere in ascolto, se il canale è _inattivo_ aspetta un intervallo predefinito (dallo standard) chiamato **DIFS (DCF InterFrame Space)**.
Se il canale rimane inattivo per DIFS secondi, allora la stazione trasmette il frame.

La stazione ricevente all'arrivo del frame, ne computa la checksum, e poi se è corretta aspetta un altro intervallo di tempo detto **SIFS (Short-IFS)** per poi mandare un ACK.
![[DIFS e SIFS.png]]

Ogni frame nel suo header include un **NAV** il quale è un campo che indica quanto ci metterà il pacchetto ad arrivare a destinazione sommato al tempo del successivo ACK.
Gli altri terminali nel raggio di ricezione leggeranno il frame dell'header (anche se non è diretto a loro), in questo modo sapranno che non possono trasmettere per quel tempo.
>In pratica quando una stazione invia un frame si sta riservando un canale per del tempo.

![[NAV.png]]

1. T2 e T1 ricevono un frame al tempo $t_0$ e $t_1$, chiamiamo $\delta=t_1-t_0$
2. Al tempo $t_2$ DIFS è terminato per T2, quindi comincia a trasmettere
3. Al tempo $t_3$ anche T1 riceve il frame inviato da T2 (ne leggerà NAV), mentre T1 sta ancora aspettando il termine di DIFS, quindi per lui dopo $t_3$ il canale è ancora occupato
4. T1 legge il NAV dal frame inviato da T2 e ora sa che il canale sarà occupato fino a tempo $t_4$
5. Al tempo $t_4$ il canale è inattivo e T1 può trasmettere

Se $\delta$ dovesse essere troppo piccolo (minore del tempo di trasmissione), quando DIFS termina, T1 considererà il canale inattivo, per cui comincerà a trasmettere, viene così generata una **collisione sul ricevitore**, per cui R non invierà un messaggio di ACK, per cui T1 e T2 non ricevendo un ACK sapranno che il frame non è stato ricevuto correttamente.
![[Collision.png]]

In questo caso $\delta$ è minore del tempo di trasmissione.
1. $t_2$: DIFS è finito per T2, quindi comincia a trasmettere
2. $t_3$: DIFS è finito anche per T1, ma non ha ricevuto il frame da T2, quindi anche lui comincia a trasmettere in quanto considera il canale inattivo
3. $t_4$: T1 riceve il frame di T2, ma è troppo tardi, inoltre R comincia a ricevere il frame di T2 correttamente
4. $t_5$: R riceve anche il frame di T1, per cui avviene una _collisione_

![[3 transmitters collision.png]]
1. T2, T1 e T3 ricevono un frame rispettivamente a tempo $t_0,t_1,t_2$, T2 comincia a trasmettere per primo
2. T1 e T3 essendo vicini ricevono il frame propagato da T2 allo stesso momento $t_4$, aspettano poi il tempo NAV
3. T1 e T3 trasmettono assieme creando una collisione

In questo caso il problema non è più dato da $\delta$, ma dalla vicinanza delle due stazioni T1 e T3, il che è possibile in una rete LAN.

Per evitare di eseguire **invii sincronizzati**, ogni stazione introdurrà un ritardo casuale (diverso per ogni stazione) detto **backoff** prima di inoltrare un messaggio.
Se il canale diventa occupato durante il _backoff_, il timer si ferma e ricomincerà a decrementare (da dove era rimasto) quando il canale diventa inattivo, quando arriva a $0$ invierà il messaggio.

<u>Le collisioni possono ancora verificarsi</u> nel caso la differenza tra i timer casuali sia più piccola del tempo di trasmissione.
Incrementare il range di tempo casuale da aspettare diminuisce questa probabilità, tuttavia in una rete con molti terminali questa aumenta comunque.

Ad ogni fallimento il mittente sceglierà una **finestra di numeri casuali** possibili **più grande**.
Sia $[0,CW]$ l'intervallo di numeri casuali, $CW$ è aggiornato come segue ad ogni trasmissione fallita.
$$\begin{align}
CW_1&=CW_\min\\
CW_i&=2\cdot CW_{i-1}\\
CW_i&<CW_\max
\end{align}$$
>$CW_\min$ e $CW_\max$ sono parametri di sistema.

In questo modo al tentativo $i$, $CW_i=2^i\cdot CW$, per cui la probabilità che due timer casuali siano uguali diminuisce, questo è detto **binary exponential backoff**, e quando una trasmissione ha successo viene resettato ($CW=CW_\min$).
>Dopo un numero massimo di collisioni il mittente scarta il frame.

>[!Attention]
>Questo metodo diminuisce le collisioni ma spreca risorse.

### Meccanismo RTC/CTS
Nel caso in cui due terminali non fossero in grado di comunicare tra loro, allora la DCF non funzionerebbe in quanto non potrebbero capire se il canale è occupato.

Per risolvere il problema del **nodo nascosto**, una stazione prima di mandare un frame inoltra un **RTS (Request To Send)** la quale contiene un NAV, successivamente l'AP risponderà con un **CTS (Clear To Send)** nel caso fosse possibile trasmettere, dopo SIFS il CTS rimpiazza l'ACK.
>Il CTS contiene un NAV inviato a tutti i terminali.

In questo modo anche se qualche stazione non è in grado di raggiungere le altre, dovranno comunque comunicare con l'AP il quale invia il CTS.
![[CTS.png]]

L'handshake composto da RTS e CTS non viene sempre usato, ma solo nel caso in cui i dati da trasferire siano molti, altrimenti si ridurrebbe il bit-rate con tutte quelle attese e segnali di controllo.

#### Stima del bit-rate
È difficile capire quale è il massimo bit-rate reale, in quanto esso dipende su molteplici fattori, tra cui:
- La grandezza del canale
- Il SNR
- Il tempo in cui il canale è effettivamente usato

Quindi in generale non si può sapere in anticipo quale sarà il vero bit-rate.

