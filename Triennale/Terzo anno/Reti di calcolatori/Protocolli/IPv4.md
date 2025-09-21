Il [[Livello di rete|livello di rete]] non è affidabile in quanto si basa sui servizi offerti dal [[Livello datalink|livello datalink]], il quale può essere di due tipi:
- **Point-to-Point Protocol (PPP)**: nel quale i frame vanno da un solo host ad un altro singolo host, il suo obiettivo è quello di trasportare frame attraverso dispositivi fisici (e.g. ethernet, da cui PPPoE)
- **Local Area Network (LAN)**: dove tutti i dispositivi sono connessi tra loro e sono identificati tramite indirizzo MAC

## IPv4
Ogni host possiede almeno una **Network Interface Card (NIC)**, alla quale può essere assegnato un **indirizzo IP** rappresentante un numero a $32$ bit del tipo:
$$1.2.3.4=00000001\space00000010\space00000011\space00000100$$

Una rete è organizzata in **subnet** interconnesse dai router, le quali sono identificate da un gruppo di indirizzi nella forma $x.y.z.w/N$, dove $N$ viene usato per indicare il numero totale degli indirizzi presenti in tale subnet: $2^{32-N}$.

Un indirizzo IP è quindi diviso in un **prefisso** che identifica la subnet (**netid**), ed un **suffisso** che identifica la NIC di rete (**hostid**).
>Tutte le NIC della stessa subnet condividono lo stesso prefisso.

$$192.168.0.0/24=\underbrace{192.168.0.}_{24 \text{ bit di rete}}\underbrace{0}_{8\text{ bit di host}}$$
Al giorno d'oggi si utilizza la rappresentazione **classless**, ovvero $/N$ viene esplicitamente definito, in passato i prefissi si dividevano in sole tre classi:
- $A$: $/8$
- $B$: $/16$
- $C$: $/24$
>Con classless invece è ora possibile usare anche, ad esempio, $/30$ per definire $2$ bit di host.

### Indirizzi IP speciali
Idealmente ogni NIC al mondo dovrebbe possedere un IP unico (non possibile con IPv4), dove _netid_ è assegnato da IANA, e _hostid_ assegnato dall'amministratore locale.
Considerando che ogni subnet ha due **indirizzi speciali** riservati:
- **hostid**=$0$: indirizzo di rete
- **hostid**=$1\dots1$: indirizzo di broadcast
Ad esempio: $192.168.0.0/24$
- $192.168.0$: netid
- $192.168.0.0$: indirizzo di rete
- $192.168.0.255$: indirizzo di broadcast, usato per mandare pacchetti a tutti gli indirizzi della subnet
>Una NIC senza IP assegnato può fare un **broadcast limitato** a $255.255.255.255$.

Gli indirizzi che cominciano con $1110$, ovvero $224.0.0.0/24$ sono detti **indirizzi multicast** e sono usati da gruppi di host che vogliono comunicare, i più noti sono:
- $224.0.0.1$: tutti gli host nella subnet, router esclusi
- $224.0.0.2$: tutti i router

Vediamo di seguito degli **indirizzi IP speciali**:
- $0.0.0.0/8$: utilizzabile solo come indirizzo sorgente (e.g. quando si usa il DHCP)
- $127.0.0.0/8$: **interfaccia di loopback**, questo indirizzo assegnato ad ogni host, è un indirizzo locale all'host stesso, ed è usato per gestire le comunicazioni TCP/IP dei processi interni
- $10.0.0.0/8, 172.16.0.0/12, 192.168.0.0/16$: classi private non instradabili
- $169.254.0.0/16$: link-local, non instradabile, usato per NIC senza IP associato per consentirgli di comunicare

### Routers
- Un **router** possiede più NIC con ogni indirizzo appartenente a subnet diverse
- Ogni host possiede un **default router** al quale inoltrare pacchetti quando non sono indirizzati ad host nella stessa subnet

Quando un indirizzo IP viene configurato nella rete locale, viene aggiunta una entry nella **tabella di routing** assumendo che i pacchetti indirizzati ad un host appartenente alla subnet siano **direttamente raggiungibili**, mentre quelli indirizzati verso l'esterno devono avere un **gateway** specificato per raggiungere la destinazione.

#### Header IPv4
- **Version**: $4$ o $6$
- **IP Header Length**: lunghezza dell'header
- **DS**: usato per notificare una possibile congestione
- **Total length**: lunghezza complessiva del pacchetto
- **Identification**: per abbinare i frammenti
- **Flags**: don't fragment, more fragments
- **Fragment offset**: offset di un frammento nel pacchetto originale
- **TTL (Time To Live)**: decrementato ad ogni hop
- **Protocollo**: ICMP, TCP, UDP
- **Header chk**: checksum per i dati nell'header
- **Source & destination addresses**

### Frammentazione
Sappiamo che i datalink supportano MTU differenti, per cui un pacchetto più grande della MTU di una rete deve essere **frammentato** per poi essere riassemblato a destinazione.

Ogni frammento dello stesso pacchetto possiede:
- Lo stesso campo `identification`
- `total_length` = `fragment_length`, eccetto per l'ultimo frammento che potrebbe essere più piccolo
- `fragment_offset` inizialmente sarà a $0$, poi sarà spostato di volta in volta
- `more_fragments=1` eccetto per l'ultimo frammento

Ogni frammento diventa un pacchetto indipendente con un nuovo header IP grande $20$ byte.
>`identification` rimane uguale per tutti i pacchetti.

$$\text{Total length = 250, MTU = 120}$$
![[Frammentazione pacchetti.png]]

>Per farci stare sia il nuovo header IP e sia i dati del frammento, la dimensione di quest'ultimo dovrà essere decisa considerando la dimensione dell'header IP aggiuntivo.

I pacchetti contenenti i frammenti potrebbero pure prendere delle strade diverse per arrivare a destinazione, per ricomporre il pacchetto, alla fine verrà utilizzato `identification` assieme ai `fragment_offset` per ricomporlo in ordine corretto.

### Indirizzi pubblici e privati
Il numero totale di indirizzi IPv4 è $2^{32}$, inizialmente sembrava un numero accettabile, ma ora non lo è più, per quello è nata la versione **IPv6** composta da $2^{128}$ indirizzi, come soluzione a lungo termine.

Una soluzione a breve termine è stata quella di introdurre il **Network Address Translation (NAT)**.

Sono **riservate** tre classi (range) di indirizzi IP:
- $10.0.0.0 - 10.255.255.255\space(/8)$
- $172.16.0.0 - 172.31.255.255\space(/20)$
- $192.168.0.0 - 192.168.255.255\space(/16)$

Esse possono essere usate nelle rete locali senza doversi coordinare con altre reti, per questo motivo vengono dette **private**.
Un router di bordo non può inviare pacchetti da/a un indirizzo IP privato proprio perchè esso può essere ripetuto in ogni rete locale.

Esiste una **quarta classe privata**:
- $100.64.0.0 - 100.127.255.255\space(/10)$

Essa non è per definizione "usabile da tutti", in quanto viene usata dagli ISP nel caso in cui non disponessero di sufficienti indirizzi IP per servire i clienti.
>Nulla vieta di utilizzarla, tuttavia potrebbe creare problemi con l'ISP.

---
## Network Address Translation (NAT)
Il **NAT** è una tecnologia generica che viene usata per convertire un indirizzo pubblico in uno privato e viceversa, la più comune è il **Network Address Port Translation (NAPT)**.
>L'idea è che un router di frontiera esegua la conversione.

![[LAN.png]]

Nell'esempio di sopra il router ha due NIC, una con indirizzo privato, ed un'altra (collegata tramite cavo all'ISP) con indirizzo pubblico.

Il **traffico verso internet** apparirà provenire sempre da $1.2.3.4$, questo perchè il router cambierà la `source_address` di ogni pacchetto in uscita.

Al momento del ricevimento della risposta dal server il router cambierà il `destination_address` a quello dell'IP privato per inoltrarlo al dispositivo corretto che ha fatto la richiesta.

Una connessione a _livello di trasporto_ è identificata dalla seguente quintupla:
$$[sIP,dIP,SPort,dPort]$$
Per cui un router che implementa il NAT avrà una tabella come segue:

**In arrivo** alla NIC privata:

| Protocol | sIP           | dIP       | sPort   | dPort |
| -------- | ------------- | --------- | ------- | ----- |
| UDP      | $192.168.1.2$ | $8.8.8.8$ | $12909$ | $43$  |
| TCP      | $192.168.1.3$ | $4.3.2.1$ | $9823$  | $80$  |

**In uscita** dalla NIC pubblica:

| Protocol | sIP       | dIP       | sPort   | dPort |
| -------- | --------- | --------- | ------- | ----- |
| UDP      | $1.2.3.4$ | $8.8.8.8$ | $12909$ | $43$  |
| TCP      | $1.2.3.4$ | $4.3.2.1$ | $9823$  | $80$  |

Oltre al **mapping degli indirizzi**, il router eseguirà anche un **mapping delle porte** per evitare due righe con la stessa `sPort`.

Il NAT porta con se varie **problematiche**:
- Forza i router a **mantenere uno stato**, cosa per cui non sono stati progettati, infatti il NAT viene fatto da dispositivi di firewall
- Deve **rilevare inizio e fine della comunicazione** per eliminare righe nella NAT table, tuttavia questo non è facile con UDP oppure con TCP nel caso il segnale `RST` non venisse ricevuto in una situazione critica
- Può avere **problemi di memoria** con tante connessioni nella rete locale
- Un host dietro ad un NAT può aprire una connessione verso un host con indirizzo pubblico, ma non viceversa
- È anche colpa del NAT se **non è possibile avere la crittografia a livello di trasporto** (infatti si usa il [[TLS]] che è costruito al di sopra)

---
## Forwarding tables
Una **forwarding table** esegue il mapping da un indirizzo di rete ad una interfaccia esterna di un router.

Quando un pacchetto arriva, viene abbinato al contenuto nella tabella scegliendo l'interfaccia corrispondente al **prefisso di rete più lungo**.

Consideriamo la seguente forwarding table:

| Destination network | Destination network (bin)             | Out NIC |
| ------------------- | ------------------------------------- | ------- |
| $0.0.0.0/0$         | $00000000.00000000.00000000.00000000$ | $0$     |
| $124.156.12.0/24$   | $01111100.10011100.00001100.00000000$ | $1$     |
| $124.156.13.0/24$   | $01111100.10011100.00001101.00000000$ | $0$     |
| $124.156.13.128/26$ | $01111100.10011100.00001101.10000000$ | $2$     |
| $200.212.12.127/26$ | $11001000.11010100.00001100.01111111$ | $3$     |
| $200.212.12.64/28$  | $11001000.11010100.00001100.01000000$ | $4$     |

Di seguito alcuni mapping che rispettano la tabella di sopra:
- $124.156.12.12:1$
- $124.156.13.2:0$
- $124.156.13.129:2$
- $200.212.12.79:4$
- $124.156.12.35:0$
- $124.156.12.1:0$

>Nei router il matching è eseguito a livello hardware.

>[!Example]
>- **Con la subnet $1.2.1.0/24$ è possibile assegnare l'indirizzo $1.2.1.255$?**
>No, netid è $1.2.1$, per cui hostid sarà $255$ il quale corrisponde all'indirizzo di broadcast.
>
>- **Con la subnet $1.2.0.0/16$ è possibile assegnare l'indirizzo $1.2.1.0$?**
>Si, netid è $1.2$ per cui hostid sarà $0.0$ il quale è valido.
>
>- **Con la subnet $1.2.1.0/24$ è possibile assegnare l'indirizzo $1.2.1.0$?**
>No, netid è $1.2.0$ per cui hostid sarà $0$ il quale non è valido in quanto corrisponde all'intero indirizzo di rete (netid).
>
>---
>- **Quale è la lunghezza minima di netid per ottenere $15$ indirizzi IP a partire dalla subnet $1.2.0.0/16$?**
>Sono necessari $4$ bit per rappresentare $15$ indirizzi diversi, tuttavia ogni subnet contiene due indirizzi riservati, in questo caso sono $1.2.0.0$ per l'indirizzo di rete, e $1.2.0.15$ per l'indirizzo di broadcast.
>L'unico modo per avere $15$ indirizzi è quello di utilizzare $1.2.0.0/27$ il quale fornirà $30$ indirizzi ($1.2.0.0-1.2.0.31$ con hostid da $1$ a $30$), dei quali solo $15$ verranno poi usati.
>
>---
>**Una organizzazione possiede due subnet: $A$ possiede $14$ host, $B$ ne possiede $16$.
>ll provider ha il seguente indirizzo pubblico $1.2.0.0/16$.**
>Trovare:
>$1$. La network mask più piccola da affittare
>$2$. Dei possibili range di indirizzi
>$3$. La routing table del router connesso a internet (il quale è connesso ai 2 router di frontiera delle due subnet)
>
>$1$. Per $30+(2\cdot 2)=34$ IP è necessaria la netmask $/26$ la quale provvede $64$ indirizzi, ne verranno usati solo $30$
>$2$. Affitta $1.2.255.192/26$ e lo divide tra due subnet:
> - $1.2.255.192/27$, con range: $1.2.255.192/27-1.2.255.223/27$
> - $1.2.255.224/27$, con range: $1.2.255.224/27-1.2.255.255$
> Ovvero con $32$ indirizzi per subnet, dove il primo e ultimi indirizzo dei range non può essere usato, notare che in questo modo abbiamo sia indirizzi per gli host e anche per i router.
> 
> Ipotizzando che $A$ si connetta al router tramite $eth0$, $B$ tramite $eth1$, e che l'interfaccia d'uscita sia $eth2$, la forwarding table è la seguente:
> 
>| Destination network | Out NIC |
|---------------------|---------|
| $0.0.0.0/0$           | $eth0$    |
| $1.2.255.192/27$      | $eth1$    |
| $1.2.255.224/27$      | $eth2$    |
>
>>Volendo si potevano affittare due subnet differenti, con netmask $/28$ e $/27$.

