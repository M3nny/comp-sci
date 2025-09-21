Un **firewall** è un oggetto che protegge un sistema connesso ad una rete da attacchi intenzionali.

Una prima suddivisione può essere fatta fra:
- **Firewall hardware**: ha le dimensioni di un server rack (1U) e possiede un proprio sistema operativo
- **Firewall software**: gestisce l'hardware di un calcolatore sottostante come se fosse un firewall poggiando su un sistema operativo pre-esistente

>[!Info]
>Nell'ambito dei firewall, la dicitura "schede di rete" è un modo per identificare reti diverse.

Una **DMZ (DeMilitarized Zone)** ospita i server proteggendoli da attacchi esterni ed interni, infatti possono esistere due firewall che la proteggono (DMZ-OUT e DMZ-IN).

Un firewall è un **ponte** tra due o più reti che <u>verifica il traffico che lo attraversa</u>, esso accetta o scarta il traffico in base a delle policy di sicurezza.
- Verifica i pacchetti in transito (**IP filtering**)
- Può effettuare il mascheramento degli indirizzi interni (**NAT**)
- Blocca pacchetti pericolosi o non ammessi dalle policy di sicurezza

Cosa permette?
- **Controllo dei servizi**: decide a quali servizi si può accedere sia in uscita che in entrata
- **Controllo della direzione**: permette di decidere se le richieste di alcuni servizi possono essere avviate e inoltrare
- **Controllo utente**: regola l'accesso ad un servizio in base all'utente che ha effettuato la richiesta
- **Controllo del comportamento**: permette di controllare come sono utilizzati certi servizi

#### Politiche di default
<u>Tutto ciò che non è espressamente permesso è vietato.</u>

In questo caso il firewall blocca tutto il traffico e ogni servizio abilitato deve essere configurato.
Ciò garantisce maggiore sicurezza, ma è più difficile da gestire.

<u>Tutto ciò che non è espressamente vietato è permesso.</u>

Il firewall inoltra tutto il traffico e ciascun servizio dannoso deve essere disabilitato.
Ciò fornisce minore sicurezza, e tuttavia non è più facile da gestire rispetto alla controparte.

>[!Attention]
>Il firewall è un mero applicatore di regole, quindi è valido quanto le regole che applica.
>
>Se ci sono intrusioni nella rete che non passano per il firewall, esso non potrà fare nulla.

### Tipologie
La **tipologia** di firewall non coincide con la politica con cui è configurato.
- **Livello rete** o **Packet filtering**: ha il compito di bloccare o inoltrare i pacchetti leggendo gli header IP secondo regole definite a priori
- **Livello applicativo** o **Circuit/Application Gateway**: filtra il traffico a livello di trasporto e applicazioni leggendo gli header TCP/UDP, non deve essere installato a monte della rete protetta a differenza dell'altra tipologia

#### Application gateway
Un esempio di firewall a livello applicativo è un **proxy server**, ovvero media il traffico tra rete esterna ed interna regolando l'accesso ai servizi tramite ACL.
Essi sono indipendenti tra loro e non accedono al disco ad eccezione della lettura del file di configurazione, inoltre vengono eseguiti come utenti non privilegiati.
>Possono essere concentrati sull'host che funge da firewall.

#### Packet filter
Le regole di filtraggio di un firewall **packet filter** si basano sul valore dei campi contenuti nell'header IP e TCP/UDP, tra cui:
- Indirizzo e porta del mittente e destinatario
- Protocollo di trasporto
- Flag `SYN`, `ACK` nell'header TCP

Questa tipologia di firewall si suddivide ulteriormente in due categorie.

**Stateless**
Osserva il traffico sulla rete e blocca i pacchetti sulla base degli indirizzi del mittente e del destinatario.
Non tiene conto del modello di traffico o flusso dei dati, un pacchetto SMTP in arrivo sulla porta 80 viene fatto passare se la porta 80 è aperta, questo è chiamato _Malformed Packet Attack_.

**Stateful**
Possono sapere in che stato è una connessione TCP, ovvero aperta, sincronizzata, inoltre possono dire se la MTU è cambiata o se i pacchetti sono frammentati.

Permette di generare dinamicamente le regole per il prossimo pacchetto nella _sessione di conversazione_.
Se un pacchetto soddisfa la regola dinamica viene lasciato passare, altrimenti vengono applicate quelle statiche.

---
## IPtables
È un sistema di firewall implementato a livello kernel, consente di implementare firewall sia di rete e sia locali, le sue regole devono essere inserite in un contesto ben preciso che prende il nome di **chain**.

Esistono delle **chain di default**:
- **INPUT** (Filter): lavora sui pacchetti in entrata
- **OUTPUT** (Filter e Nat): lavora sui pacchetti in uscita
- **FORWARD** (Filter): lavora sui pacchetti in entrata diretti verso un altro host, in pratica agisce come un router
- **PREROUTING** (Nat): lavora sui pacchetti in entrata ai quali vengono già applicate regole prima di essere instradati
- **POSTROUTING**(Nat): lavora sui pacchetti in uscita, ma solamente dopo che è stato deciso il loro instradamento

Ogni chain fa parte di una **tabella**:
- **Filter**: regole per il filtraggio dei pacchetti
- **Nat**: regole per l'instradamento dei pacchetti
- **Mangle**: usata per modificare le opzioni dei pacchetti

```bash
# visualizza le regole in utilizzo
iptables -L

# visualizza le regole della tabella filer
iptables -t filter -L

# visualizza le regole della tabella nat
iptables -t nat -L

# visualizza le regole della chain INPUT
iptables -L INPUT
```

Prima di scrivere le regole di un nuovo firewall è bene eliminare quelle vecchie.
```bash
# cancella le regole dalla tabella di default (filter)
iptables -F

# cancella le catene definite dall'utente
iptable -X

# azzera i contatori
iptables -Z

# cancella le regole dalla tabella nat
iptables -t nat -F
```

Creiamo un esempio in cui blocchiamo tutto in ingresso e poi facciamo passare solo ssh (porta 22).
```bash
# rifiuta tutti i pacchetti in input
# -P definisce la politica per la catena
iptables -P INPUT DROP

# abilita sempre l'accesso al server stesso
# -j indica cosa fare del pacchetto
# -i indica l'interfaccia di rete da cui arriva la richiesta
iptables -A INPUT -i lo -j ACCEPT

# inserisce la regola alla fine della catena tramite -A (Append)
# -p indica il protocollo
# --dport indica la porta di destinazione
iptables -A INPUT -p tcp --dport 22 -j ACCEPT 
```

### Statefulness
Questo è un firewall stateless ed al momento del suo avvio, tutte le connessioni pre-esistenti vengono troncate, per evitare questo problema sfruttiamo la **statefulness** di ip tables aggiungendo una regola all'inizio della catena.
```bash
iptables -P INPUT DROP
iptables -A INPUT -i lo -j ACCEPT

# -I permette di inserire una regola in una determinata posizione
iptables -I INPUT 1 -m state --state ESTABLISHED,RELATED -j ACCEPT

# è necessario garantire la persistenza delle connessioni ssh
iptables -A INPUT -p tcp --dport 22 -m state --state NEW -j ACCEPT
```

Il modulo **conntrack**, facente parte del kernel, gestisce le connessioni classificandole in vari stati, ovvero:
- **New**: il pacchetto in arrivo non fa parte di nessun flusso o socket pre-esistente ed è presente la flag tcp `SYN=ON`
- **Established**: il pacchetto in arrivo fa parte di un flusso o di un socket pre-esistente tracciato dal modulo _contrack_ e possiede almeno una flag tcp attivata (`SYN`, `ACK`, `RST`), dopo aver stabilito la connessione la flag `SYN` deve essere disabilitata affinchè lo stato sia established
- **Related**: il pacchetto in arrivo non fa parte di nessun flusso o socket, ma è atteso poichè un socket lo prevede (e.g. dati sulla porta 20 quando vi è una connessione FTP sulla 21)
- **Invalid**: nessuno degli stati precedenti è applicabile al pacchetto, capita quando arrivano pacchetti inaspettati dalle regole di _conntrack_

Iptables inserisce le regole in sequenza (a partire da 1) ed esegue la prima che rispetta i requisiti senza preoccuparsi di quello che c'è dopo.
```bash
# cancella la terza regola nella catena INPUT
iptables -D INPUT 3

# -I sovrascrive la (eventuale) regola in una determinata posizone
iptables -I INPUT 3 -p tcp --dport 80 -j DROP
```

È sempre necessario definire anche una regola per la catena OUTPUT per la gestione di un firewall stateful, altrimenti iptables non è in grado di tenere traccia delle connessioni.
```bash
# manteniamo persistenti le connessioni in uscita
iptables -A OUTPUT -m state --state NEW,RELATED,ESTABLISHED -j ACCEPT
```

Possiamo distinguere tre scenari a seconda del percorso dei pacchetti:
1. Pacchetti destinati al sistema locale
2. Pacchetti in uscita dal sistema locale
3. Pacchetti che attraversano il firewall

### Firewall classico
Un firewall di rete classico permette di filtrare il traffico esterno prima che raggiunga dei server in una DMZ.
Possiede almeno due interfacce di rete, ovvero una esposta verso internet ed una sulla DMZ, che costituisce il default gateway.

Può agire in due modi:
- **Routing** fra rete esterna e DMZ con IP pubblici (della rete interna)
- **Natting** fra rete esterna e DMZ con IP privati (della rete interna) ed eventualmente riconvertiti in un indirizzo pubblico da firewall

In entrambi i casi va attivato l'**IP forwarding** scrivendo $1$ all'interno del file `/proc/sys/net/ipv4/ip_forward`.
```bash
echo 1 > /proc/sys/net/ipv4/ip_forward
```

Definite le regole di INPUT a protezione del firewall, si va a gestire ciò che passa per esso tramite la catena FORWARD.
```bash
$IPTABLES -P FORWARD DROP
# web
$IPTABLES -A FORWARD -d 1.2.3.4 -i eth0 -p tcp --dport 80 -j ACCEPT
# web
$IPTABLES -A FORWARD -d 1.2.3.4 -i eth0 -p tcp --dport 443 -j ACCEPT

# stateful
$IPTABLES -A FORWARD -m state --state RELATED,ESTABLISHED -j ACCEPT
```

>[!Example]
>**Scrivere una regola di iptables che blocchi in input l'accesso fpt alla rete 157.138.22.0**
>```bash
>iptables -A INPUT -p tcp --dport 21 -s 157.138.22.0/24 -j DROP
>```
>
>**Data la politica `iptables -P INPUT -j DROP`, realizzare delle regole iptables che permettano l’accesso a http e https per un web server**
>```bash
>iptables -A input -p tcp --dport 80 -j ACCEPT
>iptables -A input -p tcp --dport 443 -j ACCEPT
>```
>---
>**Supporre di essere amministratore di un firewall la cui politica di default sulla catena di FORWARD è: `iptables -P FORWARD DROP`.**
>**Accettare per la macchina 192.168.1.11 le connessioni ssh**
>```bash
>iptables -A FORWARD -d 192.168.1.11 -i eth0 -p tcp --dport 22 -j ACCEPT
>```
>
>**Accettare per la macchina 192.168.1.141 le connessioni http, https.**
>```bash
>iptables -A FORWARD -d 192.168.1.141 -i eth0 -p tcp --dport 80 -j ACCEPT
>iptables -A FORWARD -d 192.168.1.141 -i eth0 -p tcp --dport 443 -j ACCEPT
>```
>
>**Accettare per la macchina 192.168.1.110 le connessioni ftp solo dalla rete 192.168.100.0.**
>```bash
>iptables -A FORWARD -d 192.168.1.110 -i eth0 -s 192.168.100.0/255.255.255.0 -p tcp --dport 21 -j ACCEPT
>
>iptables -A FORWARD -d 192.168.1.110 -i eth0 -s 192.168.100.0/255.255.255.0 -p tcp --dport 20 -j ACCEPT
>```

### Tabella mangle
Viene utilizzata soltanto quando le opzioni dei pacchetti devono essere modificate al volo in quanto consente la modifica di vari header IP o TCP di un pacchetto.

Utile per alterare il **TOS (Throughput Of Service)**, ad esempio per ridurre la latenza di pacchetti DNS:
```bash
iptables -t mangle -A OUTPUT -p udp --dport 53 -j TOS --set-tos Minimize-Delay
```

### NAT
Il [[IPv4#Network Address Translation (NAT)|NAT]] (Network Address Translation) modifica l'IP sorgente o destinazione di un pacchetto.

Oltre a consentire l'esistenza di ip privati e pubblici, viene anche utilizzato per reindirizzare il traffico su un unico IP oppure per inoltrare il traffico con una determinata porta verso un altro host.

- **SNAT (Source NAT)**: avviene sempre dopo che il pacchetto ha subito il routing, un esempio è il _masquerading_ che trasforma tutti gli IP sorgenti di una rete locale in un unico IP con cui sono inviati
- **DNAT (Destination NAT)**: avviene prima che il pacchetto subisca il routing, ad esempio il port-forwarding

```bash
# cambia l'indirizzo sorgente in 1.2.3.4 o 4.3.2.1
# con porta 8000 o 8100
iptables -t nat -A POSTROUTING -p tcp -o ens33 -j SNAT --to 1.2.3.4-4.3.2.1:8000-8100
```

Per gli IP dinamici come le connessioni domestiche non è possibile specificare un IP in cui i pacchetti verranno mappati (dato che cambia), si utilizza quindi il **masquerading**, il quale utilizzerà l'indirizzo dell'interfaccia da cui il pacchetto uscirà.
```bash
# maschera qualsiasi cosa che esce da fb0
iptables -t nat -A POSTROUTING -o fb0 -j MASQUERADE
```


È possibile cambiare l'indirizzo di destinazione (in entrata) con il DNAT.
```bash
# cambia l'indirizzo di destinazione in 192.168.1.100
# con porta 8000 o 8100
iptables -t nat -A PREROUTING -p tcp -i eth1 -j DNAT --to 192.168.1.100:8000-8100
```

Volendo si può sfruttare il DNAT per **reindirizzare** dei pacchetti in entrata su una porta verso un proxy.
```bash
iptables -t nat -A PREROUTING -i eth1 -p tcp \ --dport 80 -j REDIRECT --to-port 3128
```
