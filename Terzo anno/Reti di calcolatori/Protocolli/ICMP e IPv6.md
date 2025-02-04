## ICMP
L'**Internet Control Message Protocol (ICMP)** è un protocollo di **segnalazione**, infatti esso <u>non trasporta informazioni utente</u>, ma consegna messaggi riguardanti errori e status della rete.
- IP dipende dall'ICMP per gestire gli errori
- ICMP utilizza l'IP per trasmettere i messaggi

Un pacchetto ICMP viene generato quando un altro pacchetto genera un **evento anomalo**.

l'**header** di un pacchetto ICMP è formato come segue:
- **Type & Code**: identificano il tipo di errore/evento
- **Checksum**

I <u>datagrammi contenenti ICMP sono trattati come tutti gli altri</u>, l'unica eccezione è che se un messaggio di errore ICMP genera un altro errore, allora non ci saranno ulteriori messaggi inviati per evitare una situazione di ping-pong.

L'ICMP viene **usato per testare le reti**, ad esempio:
- **Ping**: rappresenta una richiesta di tipo _echo_
- **Traceroute**: inoltra un pacchetto (non necessariamente ICMP) ad una destinazione con TTL=1, in questo modo al primo hop il router che riceve tale pacchetto risponderà con un `ICMP TTL exceeded` in questo modo è possibile conoscere l'indirizzo IP del primo hop, ripetere questo processo con TTL=1,2,3... consente di dare un'idea del numero di hop per arrivare a destinazione
>Gli host non sono obbligati a generare errori ICMP, quindi potrebbe non funzionare sempre questa tecnica.

---
## IPv6
Il numero di indirizzi [[IPv4]] diventò presto insufficiente, per cui nacque il [[IPv4#Network Address Translation (NAT)|NAT]] il quale doveva essere una soluzione temporanea, mentre **IPv6** la soluzione definitiva.

Sebbene il numero di host che utilizzano IPv6 stia aumentando, esso rimane **non retro-compatibile con IPv4**, questo rallenta il suo utilizzo su larga scala.
Inoltre non tutti gli ISP utilizzano IPv6, per cui se non si usasse IPv4 non si potrebbe comunicare con loro.

### Formato IPv6
Un indirizzo IPv6 è composto da $128$ **bit** in formato **esadecimale**:
$$\text{abcd:ef01:2345:6789:abcd:ef01:2345:6789}$$
nel caso fossero presenti blocchi di zeri, **possono essere compattati**:
$$\text{ff01:0:0:0:0:0:0:101}\Rightarrow\text{ff01::101}$$
come negli indirizzi IPv4, gli indirizzi hanno un prefisso di una certa lunghezza:
$$\text{2001:0db8::cd30:0:0:0/60}$$
Un IPv6 è diviso in tre parti:
- Un **prefisso di routing globale** che è assegnato all'ISP che possiede il blocco di indirizzi
- Un **subnet ID** che identifica il cliente di un ISP
- Un **interface ID** che identifica una interfaccia di un host tramite indirizzo MAC (grande $64$ bit), ciò vuol dire che i $2^{128}$ indirizzi IPv6 devono essere raggruppati in $2^{64}$ subnet

Data l'elevata quantità di indirizzi IPv6 disponibili, <u>non c'è più bisogno di ottimizzare l'assegnamento delle subnet</u>.

Esistono alcuni indirizzi IPv6 speciali:
- `fc00::/7:`: **Unique Local Unicast**, questi sono come gli indirizzi privati IPv4, tuttavia non ce ne è più bisogno, in questo caso vengono usati per creare reti locali per testare il protocollo
- `0:0:0:0:0:0:0:1:`: interfaccia di **loopback**
- `ff::/8:`: indirizzo **multicast**
- `fe80::/10:`: **Link Local Unicast**

### Header IPv6
L'**header** IPv6 ha dei campi interessanti come:
- **Next Header**: rimpiazza il tipo del protocollo di IPv4 (6=TCP)
- **Hop Limit**: rimpiazza il TTL
- Non è presenta la checksum
- Non c'è supporto per la frammentazione

Gli **header possono essere concatenati** tramite `next_header`, in questo modo IPv6 è estendibile, inoltre l'header puntato, avrà anch'esso il campo `next_header`.

### Assegnamento degli indirizzi
Ogni host può computare il suo **link local address** (detto anche Link Local Unicast) concatenando il prefisso `fe80::/64` con i $64$ bit dell'interfaccia (MAC), essi possono essere usati per far scambiare pacchetti tra host appartenenti alla stessa LAN.

Utilizzando come analogia gli indirizzi privati IPv4, un router non può inoltrare un pacchetto il quale ha come _source_ o _destination_ address un link local address.

Tralasciando gli indirizzi LLU, gli host dovrebbero ricevere indirizzi pubblici, dove l'**host id** sarà dato dall'indirizzo MAC.
Vengono usati due protocolli per **scoprire il prefisso della rete**:
- **SLAAC (StateLess Address Autoconfiguration)**: il router di rete periodicamente eseguirà un broadcast di un pacchetto SLAAC contenente vari parametri, tra cui il prefisso della rete
- **DHCPv6**: versione aggiornata del DHCP

#### IPSec
L'**IPSec** è un insieme di standard che implementano la crittografia e autenticazione sui pacchetti IP, venne introdotto già nell'IPv4 come feature opzionale, tuttavia per IPv6 è obbligatorio che tutti i router lo supportino.
>Non vuol dire che lo debbano usare sempre però.

#### Frammentazione
Con l'introduzione dell'IPv6 **viene rimossa la frammentazione "on path"**, questo per evitare di far sprecare risorse di calcolo ai router.

Il mittente al posto di frammentare i pacchetti, creerà dei pacchetti più piccoli da mandare.

#### ICMPv6
Come cambia il layer IP, anche il protocollo ICMP deve cambiare.
La maggior parte delle features rimane invariata, ma viene introdotto il codice **Packet Too Big**, questo sostituisce il codice **Fragmentation Needed** di ICMPv4.

In una rete del tipo:
$$A\stackrel{1500}{\longrightarrow}R1\stackrel{1400}{\longrightarrow}{R2}\stackrel{1200}{\longrightarrow}R3\stackrel{1500}{\longrightarrow}B$$
Se $A$ e $B$ si accordano sulla dimensione massima del pacchetto pari a $1460$ byte, nel tragitto $A\to B$ esso verrà frammentato in $R1$, verrà ritornato un errore specificando il pacchetto di dimensione massima inoltrabile da $R1$, poi succederà di nuovo in $R2$.

Dopo un ammontare necessario di fallimenti, la MTU viene stabilita.

---
## Intradomain Routing
Il **routing intradominio** viene utilizzato per gestire e suddividere reti grandi, un singolo dominio amministrativo dovrebbe avere un numero limitato di router che collegano le varie subnet (sull'ordine delle centinaia al massimo), il che rende la rete piccola abbastanza per usare il [[Livello di rete#Link-State routing|link-state routing]] il quale può reagire più velocemente ai fallimenti rispetto al protocollo di routing basato su [[Livello di rete#Distance vector routing|distance vector]].

Uno dei protocolli più usati è l'**Open Shortest Path First (OSPF)**, il quale segue i principi del _link-state routing_ con un paio di modifiche.

### Aree OSPF
Esistono due tipi di router per l'OSPF:
- **Router interni**: connessi solo ad altri router nella stessa area
- **Router di frontiera**: appartengono a più di un'area

Ogni OSPF possiede una singola **area zero (backbone)**, la quale contiene tutti i router di frontiera.
I router che non appartengono alla _backbone_ possono comunicare tra loro passando per quest'ultima.

All'interno di ogni area _non backbone_ i router **si scambiano pacchetti link-state** per stabilire la topologia della rete nell'area di appartenenza, inoltre ogni router conosce il percorso per arrivare alla backbone.

Il **routing inter-area** è effettuato scambiando _distance vectors_ tra i router di frontiera, questo aiuta a ridurre l'overhead causato dai pacchetti di link-state.
>OSPF può essere usato sia con IPv4 e sia con IPv6.

### Virtual Full Mesh
![[Virtual Full Mesh.png]]

In questa rete tutti i router sono collegati tra loro tramite uno switch, assumiamo che siano tutti nell'area $3$, e che $R1$ e $R4$ siano router di frontiera.
OSPF scambierà messaggi link-state e la topologia che verrà creata sarà una **full mesh**.

Ciò darà la falsa percezione che esista più di un cammino da un router all'altro.
Nel caso lo switch non funzionasse, un router proverà tutti gli altri cammini, finchè non si renderà conto che nessuno di essi funziona.

Per evitare che ciò accada OSPF consente di selezionare un router in particolare al quale verranno recapitati i link-state packets.

È possibile rilevare il malfunzionamento di un link nei seguenti modi:
- **Messaggi HELLO** con alta frequenza, andando così a creare molto traffico
- Il **link-layer notifica il layer di rete**, ma non è garantito da tutti i link layer
- Un **protocollo di heartbeat** dedicato può essere utilizzato per monitorare ogni link

