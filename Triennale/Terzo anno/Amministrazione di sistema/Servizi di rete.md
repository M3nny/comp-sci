La combinazione tra [[IPv4|IP]], [[TCP|protocollo di trasporto]] e [[TCP#UDP|porta]] prende il nome di **socket**.

Per **aprire una connessione** tra due socket:
- Il server deve aprire una connessione passiva su una porta
- Il client deve richiedere una porta per connettersi all'host remoto

Per avviare e spegnere **manualmente** i servizi si utilizzano i comandi `service` e `systemctl`:
```bash
service ssh [start|stop|status|restart]
systemctl [start|stop|status|restart] ssh
```

Nei vecchi sistemi Unix-like si utilizzava direttamente lo script `/etc/init.d`:
```bash
/etc/init.d/ssh [start|stop|status|restart]
```

### Operazioni periodiche
Nei sistemi Unix **cron** viene utilizzato per lanciare periodicamente dei comandi specificando anche l'utente con cui debbano essere eseguiti, la sua configurazione si trova in `/etc/crontab` e nei file `/etc/cron.*`.

Esiste anche `/etc/cron.d` che contiene script che vengono eseguiti a discrezione di chi li ha creati.

Da `/etc/crontab` possiamo vedere come dei task periodici vengono eseguiti:
![[Cron.png]]


Per operazioni programmate una tantum si può usare `at`:
```bash
at 6 am sep 9
```

### Servizi di base
Nei sistemi Unix, il daemon **inetd** era il modo più semplice per mettere in opera un servizio, esso rimaneva in ascolto sulle porte configurate, e quando riceveva una richiesta lanciava il programma desiderato e reindirizzava stdin, stdout e stderr sulla rete.
>Esistono varie implementazioni di questo daemon.

In combinazione a inetd, viene utilizzato **tcpd** il quale accetta o rifiuta le richieste in entrata secondo delle semplici regole definite in `/etc/hosts.allow` e `/etc/hosts.deny`.

Di solito si blocca tutto in `/etc/hosts.deny` e si aprono solo i servizi necessari in `/etc/hosts.allow`.
```bash
# /etc/hosts.deny
ALL: ALL

# /etc/hosts.allow
sshd: <ip>
```

### NTP
All'interno di un sistema distribuito è fondamentale che client e server abbiano tutti la stessa ora, il **Network Time Protocol (NTP)** ci permette di effettuare la sincronizzazione della data e ora.

Client e server si sincronizzeranno con dei **time server** i quali sono collegati a dispositivi di misurazione del tempo (o ad altri server NTP).
I dispositivi di misurazione diretta (e.g. orologio atomico) vengono detti **strato 0**, mentre i server NTP direttamente collegati vengono detti **strato 1** discorso analogo per server NTP collegati ad altri server NTP, fino allo **strato n**.

Per configurare NTP basta specificare il server NTP di riferimento in `/etc/ntp.conf`.

Esistono anche comandi come `rdate` i quali sincronizzano l'ora con un server che abbia a disposizione il servizio **time**, mentre `hwclock` gestisce il clock hardware del pc.

In Windows è necessario attivare questo servizio manualmente modificando una chiave di registro tramite GUI.

### DHCP
Lo strumento principale per fornire la **configurazione di rete** ai client che ne fanno richiesta è il protocollo [[Ethernet#DHCP|DHCP]].

È anche possibile assegnare ad un host con un determinato [[Ethernet#MAC|MAC]] sempre lo stesso IP.

Il funzionamento in breve è:
1. Il client invia in broadcast un pacchetto **DHCP DISCOVER**
2. Il server DHCP controlla il MAC del client e gli invia **DHCP OFFER**
3. Se il client accetta, invia **DHCP REQUEST**
4. Il server risponderà con **DHCP ACK**

Per la configurazione del server si modifica il file `/etc/dhcp/dhcp.conf`.

In Windows, sempre attraverso GUI, è possibile attivare il servizio e specificare quale rete viene servita dal DHCP server, il range di indirizzi assegnabili e attraverso quale connessione fornire il servizio.

### DNS
Il [[DNS]] consente di assegnare un nome simbolico ad un IP, per farlo è necessario gestire una tabella di corrispondenza.

Possiede una **duplice gerarchica**:
- Della struttura del nome di dominio
- Dei server che forniscono i dati relativi

La gerarchia dei DNS parte dai **root name server** e si realizza tramite **deleghe** sulle **zone**.

Una **zona DNS** è una parte dello spazio dei nomi costituita da un dominio e i suoi sottodomini.

La **gestione di una zona** è delegata dalla zona superiore, ad esempio nella zona `.it`, vi sarà una delega per la zona `unive.it`, e in `unive.it` vi sarà una delega per la zona `dais.unive.it`.

Ogni zona è replicata su più server, vi sono più **record NS** che specificano quali server siano **autoritativi** per tale zona.

Per ottenere la risoluzione di un nome è necessario partire dal root DNS ed interrogare **ricorsivamente** i DNS responsabili per una certa zona, finchè non arriviamo al server responsabile per il nome interessato.
>Le risoluzioni vengono messe in cache.

È possibile anche convertire un indirizzo IP ad i suoi nomi di dominio associati tramite [[DNS#Reverse DNS|reverse lookup]], per farlo però è necessario che il DNS associato possegga un **ptr record** per consentire la query inversa.

Vediamo di seguito i **tipi di record** che sono forniti da un server DNS:
- **SOA (Start Of Authority)**: fornisce un numero seriale che identifica la data di modifica del record, email del responsabile, ed il TTL per il quale un altro server DNS può ritenere valida l'informazione ricevuta
- **NS**: definisce i DNS responsabili per le [[DNS#Query ricorsive e iterative|query iterative]] riguardanti la zona
- **MX**: definisce gli hostname dei server di posta in entrata responsabili per il dominio
- **A**: traduzione nome $\to$ IPv4
- **AAAA**: traduzione nome $\to$ IPv6
- **CNAME**: alias per un host del tipo alias $\to$ nome
- **TXT**: associa stringhe arbitrarie ad un nome del tipo nome $\to$ stringa
- **SRV**: associa informazioni strutturate al nome di un servizio del tipo
	servizio.protocollo $\to$ priorità | peso | porta | nome host
- **PTR**: traduzione IP $\to$ nome

Il DNS può essere configurato modificando il file `/etc/hosts` specificando le coppie ip-nome.

Esistono varie **categorie** di server DNS:
- **Master**: contiene la copia principale del database DNS e propaga agli altri le modifiche
- **Slave**: possiede una replica di master, in caso di necessità può fungere da primario
- **Caching**: tiene una cache delle informazioni

È anche possibile usare **bind** in sistemi Unix per configurare il DNS, una direttiva particolare è `$ORIGIN`, ad esempio consideriamo un file di configurazione all'interno di `/etc/bind`:
```
$ORIGIN example.com.
@ IN NS ns1.example.com
@ IN NS ns2.example.com.
```

Esso effettuerà una sostituzione dei nomi che non sono FQDN durante l'elaborazione del file di zona.
>È importante specificare `.` alla fine di un nome.

La presenza di `@` trasforma la precedente configurazione in:
```
example.com. IN NS ns1.example.com.example.com. # sbagliato
example.com. IN NS ns2.example.com
```

In Windows invece esiste un **ruolo DNS** da installare, e la configurazione del DNS avviene sempre attraverso GUI, i file generati saranno simili a quelli creati con regole di _bind_.

Oltre al sistema DNS si può trovare anche:
- **WINS**: Windows Internet Naming Service
- **NetBIOS**: Network Basic Input Output System
- **NetBEUI**: NetBIOS Extended User Interface
