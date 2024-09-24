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
