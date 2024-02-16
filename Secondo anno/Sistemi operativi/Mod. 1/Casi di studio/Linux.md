Il **nucleo** è **monolitico** con _componenti modulari_  e possiede sei principali sottosistemi:
- Gestione dei **processi**
- Interprocess **communication**
- Gestione della **memoria**
- Gestione del **file system**
- Gestione dei dispositivi **I/O**
- Gestione della **rete**

supporta molte piattaforme hardware, fornendo anche operazioni a basso livello diverse in base al tipo di architettura per sfruttarne i vantaggi, questo anche grazie al **porting**.

Oppure al posto di estendere il nucleo con il _porting_, è possibile **integrare** alcune funzionalità a richiesta, in quanto il modulo kernel è collegato dinamicamente al nucleo in fase di esecuzione.
- **Kmod** è un sottosistema che gestisce i moduli e le loro dipendenze senza l'intervento dell'utente.

## Gestione dei processi
Sia i processi che i thread sono **tasks**, i loro riferimenti sono mantenuti dal gestore di processi tramite una **lista circolare** ed una **tabella hash**.
La creazione di un task avviene assegnando un **PID** per identificare univocamente il task.

**Init** è il padre di tutti i task, da esso vengono chiamati:
- **Fork**: per creare task che condividono, fino alla prima scrittura di uno dei due, lo stesso spazio di indirizzi
- **Clone**: specifica quali strutture dati condividere con il nuovo task.
	- Se lo spazio di indirizzo è condiviso, crea un "thread" tradizionale
	- Se viene chiamato da un task del nucleo, crea un "thread" del nucleo
```c
pid = fork();
if (pid < 0) {
	// fork() ha fallito
	handle_error();
} else if (pid > 0) {
	// codice del padre
} else if (pid == 0) {
	// codice del figlio
}
```

### Scheduling dei processi
Esistono tre classi di thread:
- **Real-time FIFO**: massima priorità senza prelazione da parte di altri tipi
- **Real-time RR**
- **Time-sharing**

Ogni task è eseguito fino allo scadere del suo quanto di tempo oppure fino a quando si blocca.
Tutti i task sono nella coda **run** (multilivello con feedback), il **vettore di priorità** mantiene un puntatore ad ogni livello della coda, lo scheduler avvierà il task in testa alla lista nel livello più alto del vettore di priorità.

Per **evitare l'attesa infinita** ogni task è eseguito almeno una volta all'interno di una **epoca** (limite massimo di attesa per $n$ task nella coda run).
I task possono essere **active** o **expired**, quando viene raggiunto il tempo massimo per epoca, i task ad alta priorità vengono sospesi temporaneamente per far eseguire almeno una volta quelli a bassa priorità, poi quando sono tutti nello stato _expired_ (ogni task ha usato il suo quanto di tempo) vengono tutti portati allo stato _active_ per iniziare una nuova epoca.
>Più basso è il valore di affinità (nice), più alta è la priorità.

I <u>task I/O-bound sono eseguiti per primi</u> così da concludere in fretta dato che non usano tanta cpu.

Per quanto riguarda lo **scheduling multiprocessore**, ogni processore ha la sua coda di task indipendente con una cache locale, lo scheduler esegue il **bilanciamento dinamico del carico** controllando la quantità di dati contenuti all'interno delle cache.
>I task real-time possono essere creati solo da utenti con privilegi di root.

## Organizzazione della memoria
Viene usata esclusivamente la **paginazione**, con tre o quattro livelli di tabelle di pagina:
- Directory **globale** di pagina
- Directory **alta** di pagina
- Directory **intermedia** di pagina
- **Tabella delle pagine**
![[Indirizzo virtuale linux.png|600]]
La **memoria fisica** è divisa in tre zone:
- Memoria **DMA**: usata per supportare hardware vecchio senza DMA hardware
- Memoria **normale**: memorizza i dati utente e la maggior parte dei dati nucleo
- Memoria **alta**: memoria non mappata permanentemente dal nucleo e memoria per i task utente

Viene usato un **bounce buffer** per i dispositivi che non possono indirizzare la memoria alta, memorizzando temporaneamente nella zona DMA per l'I/O, i dati vengono poi copiati alla memoria alta dopo l'operazione di I/O.

### Allocazione
- **Allocatore di zona**:
	I task vengono allocati in memoria fisica a partire dalla memoria alta, scendendo di zona se non si trova posto.
	L'algoritmo **binary buddy** cerca un blocco di dimensioni corrette, se non esiste prende un blocco più grande e lo dimezza finchè non ci sta appena, poi nella deallocazione riunisce i blocchi liberi vicini.
- **Allocatore di slab**:
	Alloca memoria per strutture più piccole di una pagina.
- **Memory pool**:
	Regione di memoria garantita disponibile per task del nucleo o driver di periferica, indipendentemente dal carico di memoria, per evitare page fault critici.

### Sostituzione di pagine
<u>Solo le pagine degli utenti possono essere sostituite</u>, inoltre la paginazione avviene **a richiesta**.
Le pagine lette vengono subito inserite nella cache delle pagine e le pagine sporche sono scaricate su disco con cache write-back.

La sostituzione è eseguita indipendentemente per ogni zona, viene usato l'algoritmo di [[Memoria virtuale#Strategie di sostituzione|sostituzione ad orologio]].
Ogni zona ha due liste collegate:
- Lista **attiva**: pagine riferite recentemente (working set)
- Lista **inattiva**: pagine riferite meno di recente
la pagine riferite per la prima volta entrano nella lista inattiva, se vengono riferite un'altra volta in breve tempo, vengono inserite nella lista attiva, in questo modo non vengono sostituite (se possibile) le pagine riferite più volte recentemente.

### Swapping
Il demone swap del nucleo **kswapd**:
- Libera periodicamente le pagine sporche sul disco (swap out)
- Scambia le pagine dalla lista inattiva ad attiva

Non può liberare _immediatamente_ pagine libere se:
- La pagina è condivisa
- La pagina è modificata
- La pagina è _locked_ (in fase di I/O)

## File system
Grazie al **virtual file system** (VFS) è possibile supportare diversi file system, esso consente agli utenti di vedere tutti i file in un unico albero di directory.

<u>Tutte le richieste/operazioni relative ai file vengono prima inviate al VFS</u>, il quale fornisce un'interfaccia per l'accesso ai dati del file, determinando a quale file system corrisponde la richiesta e richiamando la routine del file system in questione che esegue le operazioni richieste.

Il VFS infatti **non implementa le operazioni**, ma **definisce delle operazioni** generiche e richiede che ogni file system fornisca un'implementazione per ogni operazione che il VFS supporta.

Il **VFS i-node** descrive la locazione di ogni file, directory o link.
Il **descrittore di file** contiene:
- Informazioni sul i-node a cui si accede
- Informazioni sulla posizione del file a cui si accede
- Flag che descrivono come accedere ai dati

Grazie alla **dentry** (directory entry) i descrittori di file sono mappati negli i-node.

| **Directory** |           **Contenuti**           |
|:-------------:|:---------------------------------:|
|      bin      |            eseguibili             |
|      dev      | file speciali per dispositivi I/O |
|      etc      |       file di sistema vari        |
|      lib      |             librerie              |
|      usr      |      directory degli utenti       |

Nel **superblocco VFS** sono contenute informazioni su un file system montato, esso viene caricato in RAM quando il file system viene montato.

| **Operazione VFS** |                                 **Uso**                                 |
|:------------------:|:-----------------------------------------------------------------------:|
|        read        |           copia i dati di un file in una locazione in memoria           |
|       write        |          scrive i dati di una locazione di memoria in un file           |
|        open        |                  trova l'i-node corrispettivo al file                   |
|      release       | rilascia l'i-node associato al file (solo se non ci sono open in corso) |
|       ioctl        |              esegue una azione specifica di un dispositivo              |
|       lookup       |  risolve un pathname in un i-node e ritorna una dentry corrispondente   |

#### EXT2fs
Nel **Extended File system 2**, per un meccanismo di sicurezza, di default 5% dei blocchi sono riservati per gli utenti con privilegi di root, in questo modo consente ai processi di root di continuare l'esecuzione.

Fornisce un **accesso rapido ai file piccoli**, ed è composto da **gruppi** di blocchi i quali cercano di memorizzare **dati correlati**, ogni gruppo contiene:
- **Superblocco**: contiene informazioni critiche dell'intero file system
- **Tabella degli i-node**: una riga per ogni i-node nel gruppo
- **Allocazione bitmap degli i-node**: traccia l'uso degli i-node del gruppo
- **bitmap di allocazione del blocco**: traccia l'uso dei blocchi del gruppo
- **Descrittore di gruppo**: contiene varie informazioni sul gruppo
- **Blocchi rimanenti**: memorizzano i dati dei file/directory

#### PROCfs
Il **process file system** è stato creato per fornire **informazioni in tempo reale** sullo stato del nucleo ed i processi di sistema.

Consente agli utenti di ottenere informazioni riguardo al sistema e all'hardware, esso esiste solo in RAM.
>Leggendo `/proc/devices` è possibile ottenere una lista dei dispositivi del sistema.

#### NFS
Il **Network File System** viene usato per avere un file system distribuito su più computer remoti.

## Drivers
I **device driver** sono una interfaccia software tra OS e dispositivo hardware, in genere sono implementati come moduli caricabili nel nucleo.

I dispositivi sono raggruppati in base alle loro funzioni simili e hanno **numeri di identificazione** per essere identificati dai driver, il primo numero è per identificare la classe di dispositivi, il secondo per identificare il dispositivo stesso.