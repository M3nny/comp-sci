I file sono raccolte di dati denominati e trattati come una unità, ed è compito dei file system proteggerli.
### Gerarchia dei dati
Le <u>informazioni sono organizzate a livelli</u>, il livello più alto, comprende pezzi di elementi più bassi, di seguito la gerarchia in ordine ascendente:
- **Byte**: 8 bit
- **Word**: gruppo di byte, la grandezza della word deciderà quale è il numero massimo rappresentabile
- **Caratteri**: mappano i byte in simboli (vedi [unicode](https://home.unicode.org/))
- **Field**: gruppo di caratteri
- **Record**: gruppo di field
- **File**: gruppo di record _collegati_

Il livello più alto rappresenta un **file system** (o un _database_), dove i suoi file sono memorizzati in **volumi**, fisici (singolo dispositivo di memoria) o logici (può comprendere più dispositivi di memoria).
- $1$ record fisico : $1$ record logico = **non bloccante**
- $1$ record fisico : $n$ record logici = **bloccante**

### Caratteristiche di un file
Le **operazioni** che si possono fare su un file sono: open, close, create, delete, copy, rename, read, write, append, seek, get/set attributes.
La **struttura** di un file può essere: una sequenza di byte, una sequenza di record, un albero.
Un file ha un **tipo** che può essere: file, directory, speciale (a caratteri o a blocchi).
Possono essere eseguiti principalmente due tipi di **accesso**:
- _Sequenziale_: legge i byte dall'inizio, può tornare anche indietro, ma non può saltare
- _Casuale_: legge i byte in qualsiasi ordine

Un file può avere vari **attributi** che contengono: creatore, flags, data creazione, data modifica, dimensione...

### Compiti di un file system
Un file system **organizza** e **gestisce l'accesso** ai dati, ed è responsabile per:
- Gestione dei file
- Gestione della memoria ausiliaria
- Integrità dei file
- Metodi di accesso
esso dovrebbe essere **indipendente** dal dispositivo, ovvero gli utenti devono essere in grado di riferirsi ai propri file grazie a **nomi simbolici** e non nomi di dispositivi fisici.

Deve fornire funzionalità di **backup e ripristino** e può anche fornire funzionalità di **crittografia**.

## Directories
Anche le **directories** come i file hanno analogamente i propri attributi e operazioni, ed hanno lo scopo di **organizzare** ed **individuare** rapidamente i file.
Senza directories, il file system (piatto) ne avrebbe solo una con dentro tutti i file, tutti con nomi diversi, e per cercare un file dovrebbe fare una **ricerca lineare**.

Mentre con l'introduzione di quest'ultime, si ha un file system **gerarchico** composto da:
- **Radice**: indica dove sul dispositivo inizia la directory principale, la quale punta alle varie directory
- **User directory**

I **nomi** in questo caso sono unici solo all'interno di una directory, ma non in tutto il file system, essi sono formati da **pathname**, i quali possono essere relativi o assoluti.
Allo stesso modo esistono i **link** per facilitare la **condivisione dei dati**, possono essere:
- **Soft link**: se specifica la logica di come arrivare al file dalla directory contenente il link
- **Hard link**: se specifica la posizione fisica del file sul dispositivo di memoria
#### Metadata
Sono informazioni che non possono essere modificata direttamente dagli utenti, molti FS creano un **super blocco** per memorizzare le informazioni critiche che proteggono l'integrità del file system stesso, esso contiene:
- Identificatore del file system
- Posizione di blocchi liberi
- Posizione della radice
- Tempo dell'ultima modifica
>Per evitare perdite di dati, il file system generalmente crea **copie ridondanti** del super blocco.

L'open di un file restituisce un **descrittore di file**, il quale verrà usato per accedere al file stesso.

### Mounting
Combina più file system in un **unico spazio dei nomi** così che possano essere riferiti da una singola root chiamata **punto di mount**.
Le directory saranno poi gestite attraverso **tabelle di mount**, le quali contengono informazioni sulla posizione dei punti di mount.
>Quando il FS nativo incontra un punto di mount, usa la tabella di mount per determinare il dispositivo ed il tipo di FS montato.
><u>Non possono essere creati hard link tra vari FS</u>.

## Organizzazione dei file
I file sono memorizzati su un disco **partizionato** con file system in ogni parte:
- **Master Boot Record (MBR)** rappresenta il settore 0 del disco, usato all'avvio
- **Blocco di boot**: contiene il primo blocco di una partizione, se eseguito carica il SO contenuto nella partizione

Gli **schemi di organizzazione** dei file includono i seguenti metodi:
- **Sequenziale**
- **Diretto**: per dispositivi ad accesso diretto
- **Indicizzato non sequenziale**: sequenze logiche tramite chiave
- **Partizionato**: subfile memorizzati in directory

Il problema di **allocazione e liberazione** dello spazio nel disco è simile al problema analogo per la memoria principale, generalmente ora si usano sistemi _non contigui_.
### Allocazione contigua
Alloca i dati dei file in **indirizzi contigui**, la dimensione è specificata dall'utente.
- **Vantaggi**:
	- Record logici fisicamente adiacenti
	- Semplice memorizzazione
	- Conveniente in caso di memorizzazione _statica_ (e.g. DVD)
- **Svantaggi**:
	- Frammentazione esterna
	- Scarse prestazioni
	- Il file potrebbe cresce e non starci più nel suo spazio, portando ad ulteriori operazioni per spostarlo
### Allocazione non contigua con liste collegate
Ogni riga della directory punta al **primo settore** di un file, il quale avrà:
- Un blocco di dati
- Un puntatore al blocco successivo del file 

creando così una lista collegata per ogni file, dove: si <u>elimina la frammentazione esterna</u>, ma può avvenire <u>frammentazione interna nell'ultimo blocco</u>.

Quando viene assegnato il blocco, il sistema alloca **blocchi di settori contigui** (_extent_).
La **ricerca** di un record deve essere **effettuata dall'inizio** e può essere lenta se i blocchi contenenti i record sono dispersi.
![[Allocazione non contigua con liste collegate.svg]]
La dimensione del blocco può essere:
- **Grande**: frammentazione interna, meno operazioni di I/O
- **Piccola**: più dispersione dei dati, più operazioni di I/O
### Allocazione non contigua tabellare
Ogni riga della directory indica il **primo blocco** di un file.
Vengono utilizzate **tabelle** (memorizzate in cache) che memorizzano i **puntatori ai blocchi** dei file.
Il numero di blocco attuale viene usato come indice nella tabella per trovare la posizione del blocco successivo (l'ultimo è null).
![[Allocazione non contigua tabellare.svg]]
La **dimensione della tabella** è data da: $\text{n° blocchi }\times\text{ spazio del blocco}$.
>Una implementazione popolare è il file system FAT  in windows.
### Allocazione non contigua indicizzata
Le righe della directory puntano ai **blocchi indice** del file.
Ogni file ha almeno un **blocco indice** (i-node in unix), dove ognuno di essi contiene un **elenco di puntatori** ai **blocchi di dati** dei file, oppure ad altri _blocchi indice_ (chaining).
![[Allocazione dei file non contigua indicizzata.svg]]
Solitamente i blocchi di indice risiedono vicino ai blocchi di dati per un rapido accesso, si sfrutta anche la cache.
>Una implementazione popolare è il file system NTFS in windows.

### Organizzazione delle directories
Immaginando una directory come una tabella dove **ogni entry è un file**, gli <u>attributi</u> di quest'ultimi sono <u>memorizzati nella stessa riga</u> in cui compare il loro nome, oppure sono puntati dal puntatore memorizzato nella stessa riga.

I nomi del file possono avere tre tipi di lunghezza:
- **Fissa**: possibile spreco di memoria
- **Variabile**: si termina il nome con un carattere speciale
- **Variabile con heap**: nella riga viene memorizzato un puntatore al nome completo presente nell'heap il quale terminerà con un carattere speciale.

### Gestione dello spazio
La dimensione dei blocchi solitamente è costante, però varia in base al dispositivo.
Ricordiamo che blocchi **grandi** implicano possibile spreco di spazio, mentre blocchi **piccoli** un possibile spreco di tempo.
L'amministratore può decidere delle **quote** da assegnare agli utenti, esse rappresentano una quantità massima di dati archiviabili.

Per gestire lo **spazio libero**, alcuni sistemi usano una **linked list** contente le posizioni dei blocchi liberi, i quali vengono assegnati a partire dall'inizio della lista e vengono aggiunti nuovi blocchi liberi alla fine.
Per evitare l'allocazione sparsa si può forzare il FS ad allocare in blocchi contigui.

Alternativamente si può usare una **bitmap**, la quale contiene un bit per ogni blocco in memoria (0-libero, 1-in uso), questo permette di determinare velocemente se blocchi contigui sono disponibili, ma per trovare un blocco libero si deve cercare sull'intera bitmap.
La tabella occupa meno spazio della linked list, in quanto ogni blocco è rappresentato da $1$ bit e non da un puntatore.

### Backup e recovery
Con **backup** si intende conservare **copie ridondanti**, mentre con **recovery** intendiamo il ripristino dei dati in caso di errore.
- **Backup fisico**: semplice duplicazione di dati a livello di bit
- **Backup logico**: memorizza i dati del FS e la sua struttura logica
	e.g. _Backup incrementali_: memorizzano solo i dati modificati rispetto al backup precedente.

### Integrità dei dati
Nei sistemi che non possono tollerare la perdita di dati si usano **RAID** e/o FS con **logging** (journaling).

Alcuni FS usano **transazioni atomiche**, le quali scrivono una intera modifica solo dopo che si è sicuri che sia stata effettuata senza errori, altrimenti si esegue un **rollback** e si porta il FS nell'ultimo stato persistente (ultimo **checkpoint**).

La **paginazione shadow** usa questo meccanismo scrivendo prima su un blocco libero, e poi se è andato tutto a buon fine, copia tutto nel blocco originale.

File systems come NTFS ext3, implementando il **log structured file system (LFS)** (o journaling FS) dove ogni operazione è una transazione atomica, inoltre sfruttando la _cache_ per memorizzare le posizioni dei metadata del file system, alcuni FS di questo tipo utilizzano un log per memorizzare i metadati.
I dati sono scritti nel registro sequenzialmente, quando esso si riempie è probabile che lo spazio libero del FS sia frammentato, risolvibile compattando i dati validi in una regione contigua alla fine del log.

>[!Tip] File servers e sistemi distribuiti
>Si possono gestire file remoti inoltrando richieste ad un **file server**, il quale è dedicato alla **risoluzione di riferimenti** ai file fra sistemi, il controllo centralizzato di quest'ultimi (possibile bottleneck).
>
>Usando un approccio **distribuito** si lascia che i sistemi comunichino direttamente tra loro usando **file system distribuiti** (e.g. NFS, AFS)

## Controllo degli accessi
Un file system deve garantire che il **dominio di protezione**, il quale rappresenta le operazioni possibili (Read-Write-Execute...) venga rispettato. 

Vediamo ora alcuni metodi per il controllo degli accessi:
- **Matrici di controllo degli accessi**:
	Si usa una **matrice degli accessi**, dove $mat_{i,j}$ indica se all'utente $i$  è consentito l'accesso al file $j$, $1$ se è consentito $0$ altrimenti. 
	Può essere inefficiente in sistemi con tanti file e tanti utenti.
- **Access Control List (ACL)**:
	I privilegi possono essere memorizzati in due modi:
		1. Ogni utente ha memorizzato i file a cui può accedere
		2. Ogni file ha memorizzato gli utenti che gli possono accedere
	Occupa meno spazio della matrice di controllo degli accessi, ma la ricerca potrebbe non essere efficiente.
- **Lista di capability**:
	Genera dei capabilities (token) che garantiscono l'accesso ad un soggetto che li possiede.
	Il dominio di protezione è l'insieme di capabilities di un soggetto.



