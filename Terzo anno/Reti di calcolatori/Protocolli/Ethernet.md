Il protocollo **ethernet** al giorno d'oggi viene usato su **cavi di rame intrecciati** e **cavi di fibra ottica**.

### Twisted pairs
I cavi **twisted pair** sono essenzialmente cavi di rame intrecciati tra loro, nè esistono di vari tipi in base alla **schermatura** fornita:
- **Unshielded**: non possiede la schermatura
- **Screened**: è presente una schermatura metallica che ricopre il cavo intero
- **Foiled**: ogni coppia di cavi è avvolta all'intero di un foglio di alluminio
![[Twisted pairs.png|600]]

Il servizio ethernet moderno assicura una stabilità buona riguardo alla consegna di frame senza bisogno di riordinarli.

## MAC
Un **indirizzo MAC identifica una NIC** al livello data link, esso è composto da $48$ bit:
- $23+1$ bit: un bit che identifica se il **tipo** è _unicast_ o _broadcast_ seguito dall'**identificativo dell'organizzazione (OUI)** che ha prodotto la NIC
- $24$ bit: per un'**identificato unico all'interno del produttore** della NIC

L'indirizzo MAC complessivo è **unico** e ha la seguente forma:
$$\text{f8:75:a4:6a:97:33}$$
>Il protocollo ethernet codifica gli indirizzi dal bit meno significativo.

Un MAC è **unicast** se il primo byte è pari, ovvero la seconda cifra a partire da sinistra è pari, l'indirizzo riportato sopra infatti è di unicast.
>Seconda cifra valida perchè sia unicast: $0,2,4,6,8,A,C,E$.

Abbiamo visto precedentemente che l'indirizzo MAC viene usato per assegnare indirizzi unici agli host [[ICMP e IPv6#IPv6|IPv6]], ma essi erano lunghi $64$ bit, questo perchè utilizzano un **formato esteso**.

L'**header** di un ethernet frame è il seguente:
- **Destination** e **source address**
- **Lunghezza** dell'header
- **Payload**
- **CRC checksum**

Alcune note sull'header:
- L'header comincia con l'indirizzo di destinazione così una NIC che lo riceve può capire subito se è interessata nel decodificarlo o meno
- Il CRC sta in coda a differenza dell'header IP, questo perchè la NIC può computare il CRC mentre riceve i dati per poi compararlo senza doverlo salvare in memoria

Ethernet è usato sopratutto con il protocollo IP, ma non necessariamente è l'unico protocollo con cui funziona, infatti un layer MAC deve includere un campo che specifichi il protocollo superiore.

Inizialmente esisteva il campo **EtherType** (al posto della lunghezza) che specificava il protocollo superiore, i frame infatti erano separati da un tempo di attesa al posto di specificare una lunghezza.

Per questo il livello datalink venne diviso in due nel modello **ISO/OSI**:
- **MAC (Media Access Control) layer**: specificava _EtherType_
- **LLC (Logical Link Control) layer**: specificava la lunghezza

Successivamente LLC divenne meno utile in quanto EtherType ospitava anche la lunghezza del frame, infatti ora ci riferiamo al livello datalink come come MAC, inoltre il campo ha preso il nome di _lunghezza_.

### Switch
Un singolo link può essere esteso per creare una rete tramite degli **switch** che collegano terminali tra loro.
![[Hub vs switch.png]]

Gli **hub** inizialmente avevo lo scopo degli switch, tuttavia sono stati rimpiazzati in quanto ripetevano semplicemente i segnali in ingresso verso tutte le altre porte.

Uno **switch** indirizza il traffico di una porta ad un'altra porta specifica, per farlo però <u>deve imparare su quale porta un certo frame deve essere inviato</u> per raggiungere la destinazione.

#### Backward learning
Nel caso semplice in cui nella rete sia presente solo uno swtich collegato a molteplici terminali, si utilizza l'algoritmo di **backward learning** per imparare verso dove indirizzare il traffico.

```python
# Arrivo del frame F sulla porta P a tempo T
# Table è definita come addr->[port, time]
# Ports è una lista di porte

src = F.SourceAddress
dst = F.DestinationAddress

# Aggiorna Table
if isUnicast(dst):
	if dst in Table:
		ForwardFrame(F, Table[dst][0])
		return

# Multicast, broadcast o destinazione sconosciuta
for o in Ports:
	if o!= P:
		ForwardFrame(F, o)
```

Periodicamente lo switch controlla la tabella e rimuove tutti gli indirizzi inattivi per un periodo di tempo, in questo modo si fa spazio per nuovi indirizzi MAC.

### Spanning Tree Protocol
Nel caso di una rete più complessa con switch a cascata è necessario implementare l'algoritmo distribuito **Spanning Tree Protocol (STP)** per evitare che si formino cicli.

Ethernet non provvede un campo TTL, per cui i frame sono consegnati, ma potrebbero viaggiare per tempo indefinito.
![[Switch loop.png]]

Inizialmente in questa rete l'host $A$ vuole mandare un frame a $C$, ma lo switch1 non sa su che porta inoltrarlo, per cui lo inoltra a tutte, faranno lo stesso gli altri switch, ad un certo punto il frame arriverà, ma delle copie di tale frame continueranno a rimbalzare tra i vari switch.

<u>Un loop a livello di switch blocca la rete</u>, inoltre è facile da creare ma difficile da fermare, tuttavia avere una rete ridondante è importante in quanto resiste ai guasti.

Si assume che ogni switch possieda un ID da $64$ bit, dove i primi $16$ sono scelti dall'amministratore, mentre gli altri $48$ sono determinati dal produttore.
L'algoritmo STP costruisce un albero che come radice possiede lo switch con ID più passo.

Uno **spanning tree** non è un [[Minimum Spanning Tree#Albero di copertura minimo|minimum spanning tree]], tuttavia possiede le proprietà degli [[Minimum Spanning Tree#Teorema caratterizzante degli alberi|alberi]], e quindi non possiede cicli.

Le porte degli switch che supportano lo STP possono essere in tre stati: **root, designated, blocked**.
>Le porte non inoltrano traffico finchè non ottengono uno stato.

Alla **convergenza** si ottiene:
- Lo switch di root ha tutte le porte come sullo stato _designated_
- Tutti gli altri switch hanno almeno una porta sullo stato _root_
- Tutte le altre porte sono _blocked_ o _designated_

Ogni switch periodicamente manda un frame di tipo **Bridge Protocol Data Unit (BPDU)** su tutte le porte.
Il frame contiene varie informazioni, tra cui: $<Root_{id}, Cost, Sender_{id}, p>$, ovvero:
- L'ID dello switch di root corrente
- Il costo del path alla root (distanza pesata sulla capacità del link)
- L'ID del nodo che ha generato il BPDU
- Il numero della porta verso la quale il BPDU è stato inoltrato
>I BPDU soon inoltrati ad un indirizzo multicast, ed inizialmente ogni switch utilizza il proprio ID come root, ed imposta il costo a $0$.

I BPDU possono essere comparati in modo lessicografico secondo l'ordine usato nella loro definizione, quindi se $Root_{id}<Root_{id}'$, allora $BPDU<BPDU'$.

#### Funzionamento di STP
Al ricevimento di un BPDU da $B$, $A$ calcola il **costo** $c$:
$$c=Cost+C_{AB}$$
dove $C_{AB}$ è il costo del link $A\to B$.

assieme al **root priority vector** memorizzato per ogni porta:
$$V_q=<Root_{id},c,Sender_{id},p,q>$$
dove $q$ è la porta da cui si è ricevuto il BPDU.

Se $V_q$ è più piccolo del proprio BPDU, allora:
- $A$ utilizzerà $B$ come switch di root
- La porta $q$ in $A$ assume stato di _root_
>$A$ è diventato un figlio di $B$ nell'albero.

Se il proprio BPDU è più piccolo del BPDU ricevuto dalla porta $q$:
- La porta $q$ assume il ruolo di _designated_ ($B$ è un figlio di $A$)
- Altrimenti $B$ è un potenziale fratello di $A$, quindi ci potrebbe essere un loop, per cui $q$ assume lo stato di _blocked_

| Stato della porta | Riceve BPDU | Manda BPDU | Gestisce frame |
| ----------------- | ----------- | ---------- | -------------- |
| **Blocked**       | Si          | No         | No             |
| **Root**          | Si          | No         | Si             |
| **Designated**    | Si          | Si         | Si             |

>I BPDU vengono inoltrati solo ai figli.

Questo processo viene sempre ripetuto, con lo switch di root che computa il suo BPDU e lo inoltra sulle porte _designated_.
Essendo che tutti i BPDU ricevuto possiedono un'**età**, se essa dovesse superare una certa soglia, lo switch capisce che la topologia è cambiata e che c'è un malfunzionamento, per cui l'algoritmo comincia da capo cercando una nuova root.

---
## ARP
Nel caso un host $A$ voglia comunicare con un host $B$, necessità di sapere oltre l'IP di $B$ anche il suo MAC, per scoprirlo si utilizza l'**Address Resolution Protocol (ARP)**.

Ogni host mantiene una **tabella ARP** la quale mappa un indirizzo IP con un indirizzo MAC.
Per cui quando un host vuole sapere il MAC di un altro host, manderà in broadcast un pacchetto ARP contenente le sue informazioni, ovvero il suo IP e MAC, ed una richiesta per l'IP di cui si vuole sapere il MAC, quando arriva a destinazione l'host risponderà con un pacchetto unicast diretto al MAC sorgente.

## DHCP
Quando un host esegue il boot ha bisogno di varie configurazioni, tra cui:
- Un indirizzo IP da usare
- L'indirizzo IP del router gateway
- L'indirizzo IP del server DNS

Il **Dynamic Host Configuration Protocol (DHCP)**, è utilizzato per configurare gli host al momento del loro avvio.
>Il protocollo è configurato da parte di un server che se interrogato fornisce una configurazione per il client.

All'avvio un nuovo host manda un **DHCP discover message** con destinazione il _limited broadcast_: $255.255.255.255$, dove il source address è $0.0.0.0$.
Nel messaggio il client include anche il MAC della sua NIC, successivamente quando il server risponderà (utilizzando l'IP di broadcast) **offrirà un indirizzo IP** specificando la subnet mask e la durata del prestito.

Il client poi inoltrerà una **DHCP request** (sempre in broadcast) che richiede l'IP offerto dal server specificando nel body l'IP del server che ha offerto l'IP, possono esserci vari server DHCP che mandano la stessa offerta (per garantire ridondanza), tuttavia ogni server controllerà il body del messaggio per decidere se processarlo o meno.

Il server infine risponderà con un **messaggio di acknowledgement** indirizzato all'IP richiesto dal client, assieme ad esso ribadirà la durata del prestito e specificherà quale è il default gateway ed il server DNS.

**Recap**
Se $192.168.1.1$ vuole comunicare con $1.2.3.4$ che è fuori dalla sua rete, esso procederà come segue:
1. Controlla che $1.2.3.4$ non fa parte della sua rete
2. L'indirizzo MAC di destinazione sarà quello del gateway (conosciuto tramite la configurazione ricevuta dal DHCP)
3. L'indirizzo MAC del gateway non è nella tabella ARP procederà con una ARP resolution
4. Una volta ricavato il MAC del gateway verrò inoltrato il frame al MAC del gateway utilizzando $1.2.3.4$ come indirizzo IP

