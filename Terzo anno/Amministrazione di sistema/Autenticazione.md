Per **autenticazione** si intende identificare un utente, mentre per **autorizzazione** si intende capire quali azioni esso può svolgere.

I sistemi Unix utilizzavano il contenuto del file `/etc/passwd` per entrambi gli scopi, ora le password (criptate) sono salvate in `/etc/shadow`, il quale non è pubblicamente leggibile.
>La lista dei gruppi del sistema e dei relativi GID è contenuta in `/etc/group`.

Ciò comporta una scarsa elasticità, ad ogni modifica dello standard dei file era necessario modificare anche i programmi che li gestivano.

Per ovviare a questa situazione sono nati sistemi che tramite **componenti modulari** aggiungono meccanismi di autenticazione e gestione di informazioni sugli utenti senza modificare i programmi che ne fanno uso:
- **NSS (Name Service Switch)**: per la gestione delle informazioni sugli utenti
- **PAM (Pluggable Authentication Modules)**: per i meccanismi di autenticazione

### NSS
NSS fornisce i dati dei system database (tra cui `passwd`e `group`), le fonti dati possono essere molto variegate (e.g. mysql).

Dei **moduli** di terze parti si occupano di tradurre richieste e risposte da/a database affinchè possano essere effettuate sulla fonte prescelta, come ad esempio una directory LDAP o un database SQL. 

Il file di configurazione è `/etc/nsswitch.conf`:
```
passwd:         files systemd
group:          files systemd
shadow:         files systemd
gshadow:        files systemd

hosts:          files dns
networks:       files

protocols:      db files
```

La semantica è: _informazione_: _dove ricavarla_.

NSS in pratica fornisce delle funzioni che fanno da interfaccia tra le applicazioni e i sistemi di autenticazione per la gestione delle informazioni utente.

### PAM
Il sistema PAM fornisce i servizi di autenticazione ad applicazioni e servizi, i **task** di autenticazione sono divisi in quattro **management group**:
- **Account**: verifica dei requisiti che l'account deve rispettare
- **Auth**: autentica l'utente e acquisisce le credenziali necessarie
- **Password**: aggiorna e modifica le informazioni di autenticazione
- **Sessione**: gestisce le attività che devono essere svolte ad inizio e fine sessione, ad esempio avviare e terminare una sessione `ssh-agent`

La configurazione si trova nei file in `/etc/pam.d/`, ma volendo (sconsigliato) si potrebbe tenerla tutta all'interno di `/etc/pam.conf`.

Le configurazioni di default in `/etc/pam.d/common-*` devono essere importate nei file che modificano il comportamento standard.

Ad oggi quasi tutti i sistemi che necessitano di **autenticazione centralizzata** si basano su **LDAP** per la gestione degli utenti e dei loro permessi, solitamente è accoppiato con **Kerberos** per la gestione degli accessi e delle password.

### NIS e RPC
Tempo fa veniva usato **NIS (Network Information Services)** ma era insicuro in quanto viaggiava tutto in chiaro, diventando root di un client era possibile accedere al database NIS il quale raggruppava i file `passwd`, `group` e `shadow` dei client iscritti al dominio NIS.
>Ora non viene più usato.

Esso era un sistema client/server basato su **RPC (Remote Procedure Call)**, ovvero attivazione a distanza di una procedura, inoltre l'esecuzione locale di tale procedura deve essere uguale all'esecuzione remota.
>Questo paradigma è adatto per il **calcolo distribuito**.

### LDAP
Una directory può essere rappresentata da un albero detto **DIT (Directory Information Tree)**.

**LDAP (Lightweight Directory Access Protocol)** è un protocollo per l'interrogazione e manipolazione di directory basato su client/server, viene utilizzato in situazioni in cui le letture sono molte, ma le scritture sono relativamente rare.
>Viene solitamente usato con il daemon **nscd** per migliorare la performance, esso gestisce la cache di rete.

In un DIT, i **nodi** rappresentano delle suddivisioni, mentre le **foglie** sono i dati veri e propri.

Ogni nodo (entry) dell'albero ha un nome univoco tra nodi fratelli, viene chiamato **RDN (Relative Distinguished Name)**, mentre il percorso completo dalla radice al nodo in questione viene chiamato **DN (Distinguished Name)** ed è univoco all'interno del DIT.

I nodi volendo possono indicare dei riferimenti ad altre parti del DIT, o addirittura a DIT di altri server LDAP (**referral**).

![[DIT.png]]
Il DN dell'utente con username "mrossi" è:
```
DN: uid=mrossi,ou=People,ou=Tecnici,I=Lecce,o=INFN,c=IT
```
oppure:
```
mrossi@people.tecnici.lecce.infn.it
```

L'accesso alla directory LDAP può essere **anonimo** o **autenticato**. la fonte dei dati di autenticazione può essere interna o esterna al DIT.

LDAP è spesso usato come **plugin di NSS** per fornire informazioni sugli utenti e gruppi ad un insieme di elaboratori, inoltre può essere anche usato tramite PAM per l'autenticazione, facendo verificare al sistema locale se la password cifrata presente nel DIT corrisponde a quella immessa dall'utente.

### Kerberos
**Kerberos** è un sistema per l'autenticazione distribuita, esso si affida ad un numero limitato di nodi fidati (**KDC**) che fanno da arbitro richiedendo prove dell'avvenuta identificazione e autenticazione delle parti.

I sistemi che usano la stessa infrastruttura basata su kerberos formano un **realm** ben identificato da un nome di dominio.

Il protocollo è formato da tre attori principali:
- **Client**
- **Application server**
- **Key Distribution Center (KDC)**, noto anche come **Authentication Server (AS)**, può essere integrato nell'application server

![[Kerberos.png]]

- **AS_REQ**: richiesta iniziale di autenticazione in chiaro del client, contiene:
	- Credenziali di chi chiede l'accesso e del servizio a cui si vuole accedere
	- IP a cui avere accesso
	- Periodo di validità della richiesta

- **AS_REP**: risposta dell'AS a AS_REQ, contiene:
	- **TGT (Ticket-Granting Ticket)** criptato con con la chiave segreta del **TGS**
	- Periodo di validità del TGT
	- Chiave di sessione criptata con la chiave segreta del client richiedente
	- Identificativo del client ed il suo IP

- **TGS_REQ**: richiesta del client al **TGS (Ticket Granting Server)** per un **ticket di servizio (TS)**, contiene:
	- TFT ottenuto dal messaggio precedente
	- Identificativo del servizio richiesto
	- Autenticatore generato dal client e criptato con la chiave di sessione

- **TGS_REP**: risposta del TGS a TGS_REQ, contiene:
	- TS criptato con la chiave segreta del servizio
	- Una chiave di sessione di servizio generata dal TGS e criptata con la precedente chiave di sessione generata dall'AS

- **AP_REQ**: richiesta che il client manda ad un application server per accedere ad un servizio, contiene:
	- TS ottenuto da TGS_REP
	- Autenticatore generato dal client, ma questa volta criptato con la chiave di sessione del servizio generata da TGS

- **AP_REP**: risposta che l'application server invia al client per provare di essere veramente il server che il client si aspetta, viene inviato solo quando è necessaria la mutua autenticazione

Esiste un modulo PAM che consente l'autenticazione di un utente attraverso le sue credenziali kerberos.

### Active directory
Un **dominio** è un insieme di server, workstation e utenti che operano dentro lo stesso ambiente e condividono le stesse regole e permessi.

In Windows una **Active Directory (AD)** è un database LDAP integrato nei server Windows e consente di gestire in modo centralizzato varie risorse, tra cui: utenti, gruppi, stampanti, cartelle condivise.

Possiamo vederla come un **contenitore di oggetti** organizzati in una gerarchia ad albero, essa utilizza kerberos per la gestione degli accessi.

Per creare una active directory è necessario aggiungere il ruolo **dominio active directory**.
