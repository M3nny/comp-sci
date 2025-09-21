Un **filesystem distribuito (DFS)** permette la memorizzazione di risorse in dispositivi di archiviazione distribuiti in una rete, esso deve gestire i file in modo **concorrente**.

Un **file server** è un host che ospita un DFS offrendo dei servizi ai client che lo sfruttano, i client avranno installata un'interfaccia al file server che include delle operazioni che normalmente si fanno localmente.
>Deve comunque essere ridondato per sicurezza.

Invece di avere un dispositivo centralizzato per la memorizzazione, il sistema ne può avere molti ed **indipendenti**, le implementazioni di un DFS possono variare, tra cui:
- Il file server viene eseguito su un'unica macchina dedicata
- Il client accede simultaneamente a più file server
- La stessa macchina può ospitare sia file server che client

Un DFS deve essere **trasparente**, ovvero all'utente appare come un normale file system centralizzato, l'unica differenza che noterà sono le prestazioni (tempo impiegato per soddisfare una richiesta) di un DFS a confronto di quello nativo.
>Nei DFS si somma il ritardo dovuto alle comunicazioni di rete, oltre al tempo di accesso al disco.

I meccanismi per gestire la concorrenza possono essere inclusi nella realizzazione del DFS oppure resi disponibili da un protocollo parallelo.

---
### Implementazioni

**Network File System (NFS)**
È il primo DFS ad essere sviluppato, è molto usato, ora alla versione 4.

**CIFS/SMB**
DFS di Microsoft.

**AFS**
DFS molto scalabile che utilizza [[Autenticazione#Kerberos|Kerberos]] per eseguire autenticazioni, ed implementa liste per il controllo degli accessi alle singole cartelle per utenti e gruppi.

**Google FS**
DFS proprietario sviluppato da Google per proprio uso.

**Coda**
Presenta proprietà interessanti derivate da AFS e altre proprie, tra cui: elevate performance, replica, sicurezza, adattamento alle prestazioni della rete.

---
### Network File System (NFS)
È un modello per integrare filesystems locali differenti, <u>basato sull'idea che ogni host fornisce una vista unificata del proprio filesystem locale</u>.
>Può essere usato con computer eterogenei (sia software che hardware).

Usa un **remote access model**:
- I client non sanno realmente dove sono i file
- I server esportano ai client una serie di operazioni sui file
- Si accede direttamente ai file e alle directory sui file server

A differenza di altri sistemi che usano un **upload/download model**:
- Il client scarica il file in una cache locale
- Dopo aver fatto le modifiche il file viene caricato sul server
- Il server dovrebbe mantenere le versioni dei file
>Esempi di questo modello sono: git, svn e cvs.

È **indipendente dall'organizzazione**, ed esporta all'utente una visione simile a quella dei filesystem unix basandosi su file organizzati come sequenze di byte, inoltre utilizza **RPC** come protocollo sottostante.

#### Novità della versione 4.0
Dalla versione 4 supporta **server stateful**, ovvero è il server a mantenere lo stato delle operazioni correnti.

Vengono introdotte le **Compound Operations (CP)**, le quali comprendono più richieste di operazioni in una singola chiamata, in questo modo le chiamate RPC sono ridotte.

Le CP non sono transazioni, ovvero non avverrà un rollback in caso di errore, ma semplicemente non verranno eseguite le successive operazioni, per questo non conviene inviare operazioni non correlate tra loro tramite una CP.

Viene introdotto anche un nuovo approccio ai **wide area DFS** con sistemi di file locking, protocolli di cache consistency e procedure di callback.

Questa versione si basa su **TCP** (prima era UDP), inoltre presenta un sistema per il **riconoscimento dell'utente** tramite una stringa arbitraria e l'identità può essere provata tramite sistemi di autenticazione esterni come kerberos.

#### Configurazione
Il file di configurazione di NFS è `/etc/exports`, esso controlla quali file system sono esportati agli host remoti e ne specifica anche le opzioni, una entry di tale file è composta come segue:
```
<export> <host 1>(<options>) <host N>(<options>)
```

Ad esempio per esportare una directory e dare all'host `192.168.0.3` anche la capacità di scrittura (di default è solo lettura) si va ad inserire:
```
/exported/directory 192.168.0.3(rw)
```

Assumendo che il file server abbia indirizzo `192.168.0.1`, possiamo montare il filesystem condiviso da quest'ultimo sempre utilizzando **mount**:
```
sudo mount -t nfs 192.168.0.1:/exported/directory /mnt
```

Per montare il filesystem condiviso all'avvio però sarà necessario inserire il mount in `/etc/fstab` per effettuare un mount statico:
```
192.168.0.1:/exported/directory /mnt nfs defaults 0 0
```

Non è consigliabile tenere montato un file system remoto in modo permanente, per questo si utilizza **automount**, il quale monta il DFS solo in caso di necessità, e dopo un periodo di inattività viene smontato.
>Esso viene gestito dal **kernel**.

La **tabella di corrispondenza** tra percorso e locazione è mantenuta da un programma in user space chiamato **autofs**, le tabelle possono risiedere sul filesystem e sia provenire da fonti esterne come LDAP.

### Condivisione file Windows
In un **dominio active directory** vi sono due tipologie di cartelle condivise strettamente legate agli utenti, ovvero: i **profili** e le **home**.

I profili possono risiedere:
- **In locale**: le impostazioni utente ed i dati delle applicazioni non vengono trasportati su altri client nel caso l'utente cambi postazione
- **Sul server (roaming profiles)**: i profili vengono scaricati su tutti i client a cui un determinato utente si collega

>[!Attention]
>I **roaming profiles** <u>non coincidono</u> con le **home esportate**, infatti i profili vengono scaricati/caricati al login/logout, non sono live come in NFS.

### Common Internet File System (CIFS)
È un protocollo standard che permette la condivisione di file e risorse all'interno di una **LAN**, è una versione migliorata del protocollo di Microsoft **SMB (Server Message Block)**.

Tra le sue caratteristiche notiamo:
- Integrità e concorrenza
- Ottimizzazione per connessioni lente
- Sicurezza
- Performance e scalabilità
- Nomi file unicode
- Nomi file globali

### SAMBA
È un'implementazione di **CIFS** che gira su piattaforme unix-like, una volta configurato permette di interagire con i sistemi Microsoft, fornendo servizi di condivisione file e stampanti.

Tramite SAMBA è possibile <u>inserire una macchina Linux all'interno di un dominio Windows</u>, in particolare permette di configurare condivisioni via CIFS per le directory Unix scelte, le quali appariranno agli utenti Windows come normali cartelle.

Gli utenti Unix per accedere alle condivisioni possono procedere nello stesso modo visto per NFS, inoltre possono usare `smbclient` per leggere le directory condivise tramite una UI.

>[!Tip] Privilegi sovrapposti
>Ogni directory può avere differenti privilegi di accesso sovrapposti ai normali privilegi Unix.
>
>Le home directory ad esempio potrebbero essere solo in lettura per gli utenti Windows, mentre anche in scrittura per gli utenti Linux.

La configurazione di samba si ottiene modificando `/etc/smb.conf`.

Dalla **release 4**, samba si può integrare (anche se non completamente) con le **active directory** di Windows server.

È necessario proteggere il sistema da utenti che cercano di monopolizzare (volontariamente o non) lo **spazio di memorizzazione**, in quanto esso è una risorsa condivisa, per farlo viene introdotto il concetto di **quota**, il quale rappresenta un limite oltre al quale uno specifico utente non può più occupare spazio.
>Se un utente monopolizzasse tutto lo spazio gli altri non potrebbero più lavorare.

La quota può essere usata anche in locale, ma la sua applicazione naturale è nei DFS.

### Quota
In Linux il **sistema di quota** viene gestito dal kernel, mentre utility per la gestione sono presenti all'interno del pacchetto `quota`.
La quota, se presente, viene applicata anche i filesystem esportati.

La quota è espressa:
- **Sul numero di blocchi (spazio disco)**
- **Sugli inode / numero di file**

inoltre può essere:
- **Soft**: dopo aver raggiunto il limite si ottiene un warning
- **Hard**: dopo aver raggiunto il limite viene rifiutata ogni ulteriore richiesta di allocazione

Per la soft quota è possibile specificare un **grace period**, ovvero un periodo nel quale l'utente si può mantenere sopra la quota, se dopo tale periodo l'utente si trova ancora sopra la quota, si **trasforma in hard quota** rifiutando ogni ulteriore richiesta di allocazione oltre la quota massima.

È possibile abilitare la quota in `/etc/fstab` dove è definito il punto di mount del DFS nella sezione delle opzioni, e dopo aver rimontato tale filesystem è possibile usare: `sudo quotacheck -cug /directory` per creare un file utilizzato dallo strumento per la gestione della quota per tenere traccia dello spazio disco usato dall'utente.

Per **abilitare** la quota si utilizza `sudo quotaon /directory`, mentre per **gestirla** si utilizza `edquota`, `setquota` e `repquota`.

### Ceph
È una soluzione per soddisfare le esigenze di archiviazione distribuita, fornisce uno storage **affidabile e scalabile**, consente di separare i dati dallo storage fisico utilizzando livelli di astrazione software.

Il vantaggio principale è che fornisce interfacce per più tipi di storage all'interno di un singolo cluster, eliminando la necessità di più soluzioni di storage o qualsiasi hardware specializzato.

**CephFS** è un filesystem distribuito completo di funzionalità tra cui snapshot, quote e mirroring multi-cluster.
