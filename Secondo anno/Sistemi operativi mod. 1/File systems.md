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

### Caratteristiche di un file
Le **operazioni** che si possono fare su un file sono: open, close, create, delete, copy, rename, read, write, append, seek, get/set attributes.
La **struttura** di un file può essere: una sequenza di bye, una sequenza di record, un albero.
Un file ha un **tipo** che può essere: file, directory, speciale (a caratteri o a blocchi).
Possono essere eseguiti principalmente due tipi di **accesso**:
- _Sequenziale_: legge i bytes dall'inizio, può tornare anche indietro, ma non può saltare
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

La dimensione del blocco può essere:
- **Grande**: frammentazione interna, meno operazioni di I/O
- **Piccola**: più dispersione dei dati, più operazioni di I/O
### Allocazione non contigua tabellare
Ogni riga della directory indica il **primo blocco** di un file.
Vengono utilizzate **tabelle** (memorizzate in cache) che memorizzano i **puntatori ai blocchi** dei file.
Il numero di blocco attuale viene usato come indice nella tabella per trovare la posizione del blocco successivo (l'ultimo è null).

La **dimensione della tabella** è data da: $\text{n° blocchi }\times\text{ spazio del blocco}$.
>Una implementazione popolare è il file system FAT  in windows.
### Allocazione non contigua indicizzata
Le righe della directory puntano ai **blocchi indice** del file.  
Ogni file ha almeno un **blocco indice**(i-node in unix), dove ognuno di essi contiene un **elenco di puntatori** ai **blocchi di dati** dei file, oppure ad altri _blocchi indice_ (chaining).

Solitamente i blocchi di indice risiedono vicino ai blocchi di dati per un rapido accesso, si sfrutta anche la cache.
>Una implementazione popolare è il file system NTFS in windows.

### Organizzazione delle directories
Immaginando una directory come una tabella dove **ogni entry è un file**, gli <u>attributi</u> di quest'ultimi sono <u>memorizzati nella stessa riga</u> in cui compare il loro nome, oppure sono puntati dal puntatore memorizzato nella stessa riga.

I nomi del file possono avere tre tipi di lunghezza:
- **Fissa**: possibile spreco di memoria
- **Variabile**: si termina il nome con un carattere speciale
- **Variabile con heap**: nella riga viene memorizzato un puntatore al nome completo presente nell'heap il quale terminerà con un carattere speciale.

### Condivisione di file
