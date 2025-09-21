In **Windows** (verrà trattato Windows 8) le applicazioni vengono eseguite all'interno delle **AppContainer**, delle sandbox che isolano il codice per motivi di sicurezza.
Le applicazioni potranno poi usare le API WinRT comunicanti con i **processi broker** per accedere ad altre risorse.

## Gestore degli oggetti
Un **oggetto** in windows rappresenta il **nome** di una **risorsa fisica o logica**, ed ogni istanza definisce gli attributi e le procedure di quest'ultimo.

Un oggetto solitamente ha un nome, ma i thread del nucleo possono anche aprire degli handle per un oggetto senza nome.

Un **oggetto rimane finchè non è cancellato** anche se non è usato da nessuno, per farlo è possibile togliere l'handle per cancellarlo dallo spazio dei nomi, o togliergli anche i puntatori per cancellarlo dalla memoria.

- **Pointer**: puntatore referenziato per contare i riferimenti
- **Handle**: specifica cosa un thread può fare con un oggetto, possono essere passati ad altri processi e anche essere duplicati

## Architettura di sistema
Il **kernel NTOS** è formato da due livelli:
- **Kernel**:
	scheduling, interrupt, servizi base, sincronizzazione dei thread
- **Esecutivo**:
	sotto al livello kernel di NTOS, si occupa di gestire oggetti, I/O, processi, memorie ed implementa il _registro di sistema_.

![[Architettura windows.png]]

L'**HAL** (Hardware Abstraction Layer) interagisce con l'hardware per astrarre le sue specifiche che differiscono tra sistemi con la stessa architettura.
L'**hypervisor** che sia trova al livello più basso schedula i processori virtuali su processori fisici.
Le librerie **DLL** sono moduli in modalità utente che i processi possono collegare in modo dinamico.

Il **registro di sistema** è un file speciale che memorizza i dati di configurazione (e.g. impostazioni, preferenze...) ed è accessibile a tutti i processi in modalità nucleo.

L'**ISR** (Interrupt Service Routine) si occupa della gestione delle interruzioni, le quali hanno vari livelli di priorità, dalla meno importante alla più importante:
- **Passivo**: nessun interrupt in fase di elaborazione
- **APC**: chiamate di procedura asincrona
- **DPC**: chiamate di procedura differite
- **ISR di dispositivo**: interrupt di una periferica
- **Critici**: debugger, clock, power failure, bus errors

## Gestione dei processi
Processi e thread sono entrambi oggetti.
Per descrivere i **processi** vengono usati dei blocchi:
- **PEB** (Process Environment Block): informazioni del processo disponibili ai thread utente, librerie DLL collegate al processo
- **KPROCESS**: usato al livello _kernel_, fornisce informazioni di scheduling e di sincronizzazione tra processi
- **EPROCESS**: usato dal livello _executive_, descrive un processo, contiene un _KPROCESS_ e punta ad un _PEB_

I blocchi usati per descrivere i **thread** si differenziano di poco, viene usato un **TEB**, ed esso è puntato da **KTHREAD**, inoltre utilizzano una memoria locale **TLS** (Thread Local Storage) per memorizzare dati locali (e.g. DLL), volendo può avere molti indici TLS.
>I thread che appartengono ad un processo condividono lo _spazio di indirizzamento virtuale_.
>Viene utilizzato un modello di threading [[Triennale/Secondo anno/Sistemi operativi/Mod. 1/Thread#Ibridi (molti-a-molti)|ibrido]].

**Creazione di processi**: padre e figlio sono indipendenti e possiedono un thread principale, però è possibile l'ereditarietà per attributi del figlio dal padre.
**Terminazione di processi**: avviene se tutti i suoi thread terminano oppure se l'utente che possiede il processo si disconnette, terminare il padre non comporta la terminazione del figlio.

I **jobs** sono gruppi di processi che vengono trattati come una singola _unità_, (e.g. tempo di CPU unificato) questo comporta che terminare un job, terminerà tutti i suoi processi.
>Un processo può far parte di un solo job.

I **fibers** sono schedulati dai thread che li creano ed eseguiti nello stesso contesto ("sono i thread dei thread"), anche loro usano una memoria locale **FLS** (Fiber Local Storage).

### Scheduling di thread
I thread sono schedulati senza considerare i processi, e hanno **32 livelli di priorità** (0 = priorità minima) dove ognuna ha una coda "ready" disciplinata dall'algoritmo **round-robin**.

- **Priorità 0-15**: thread dinamici
	aumentata quando un thread non viene eseguito da molto, non può diminuire oltre la priorità di base
- **Priorità 16-31**: thread in tempo reale

La **prelazione** può avvenire quando cambia la priorità del thread, entra in stato ready o esce dallo stato running.

## Organizzazione della memoria
Il **VMM** (Virtual Memory Manager) è un componente _executive_ responsabile della gestione della memoria, esso adotta strategie come:
- **[[Memoria virtuale#Strategie di gestione della memoria|Copy on write]]**
- **Lazy allocation**: alloca memoria solo quando necessario
- **[[Memoria virtuale#Strategie di fetch|Prefetching]]**

Vengono usate pagine a **dimensione fissa** mappate su [[Memoria virtuale#Tabelle di pagine multilivello|due livelli]].
Ogni riga di **PDE** (Page Directory Enter) indica una **tabella delle pagine**.

Gli stati della pagina degli indirizzi virtuali sono:
- **Non valida**: non è mappata in alcun oggetto
- **Riservata**: indirizzi che non saranno mai allocati dal gestore per altro
- **Committed**: è mappata su una pagina virtuale

Il VMM tratta un insieme di pagine contigue come una sola pagina, esse devono essere consecutive sia in memoria virtuale sia in memoria fisica.

### Allocazione
Esistono tre stadi di **allocazione della memoria**:
- **Reserve**: un processo riserva spazio nel proprio spazio di indirizzamento virtuale
- **Commit**: un processo è pronto a scrivere, VMM crea la tabella delle pagine e verifica la fattibilità dell'operazione
- **Access**: un processo è pronto ad accedere alla memoria, VMM scrive i dati in una pagina azzerata e aggiorna la tabella delle pagine

Nell'allocazione di memoria, sono vietate le richieste _must-succeed_ ed è possibile regolare l'I/O per rallentare il sistema ed essere più tollerante ai guasti (throttling).

| **Frame state** |                                   **Definizione**                                    |
|:---------------:|:------------------------------------------------------------------------------------:|
|      Valid      |                       La pagina corrisponde ad un working set                        |
|   Transition    |                   La pagina sta essendo trasferita al o dal disco                    |
|     Standby     |             Pagina appena rimossa dal suo working set, la PTE è invalid              |
|    Modified     | Pagina appena rimossa dal suo working set, non consistente con la versione nel disco |
|      Free       |                     Il page frame non contiene una pagina valida                     |
|     Zeroed      |                   Il page frame non fa parte di nessun working set                   |
|       Bad       |         Il page frame ha generato un errore hardware, non deve essere usato          |

Esiste una lista delle pagine per ogni frame state.
Il **VAD** (Virtual Address Descriptor) descrive l'intervallo di memoria virtuale allocata, i **gruppi di pagine** vengono chiamati **cluster** e fanno parte dello stesso file 

### Sostituzione di pagine
La sostituzione avviene secondo la [[Memoria virtuale#Strategie di sostituzione|LRU]], le pagine eliminate vengono messe in una lista di pagine _standby_ o _modified_.
Essendo che la memoria principale è divisa in due:
- **Page pool**: VMM può spostare queste pagine nel pagefile
- **Nonpaged pool**: VMM non sposta mai le pagine nel pagefile, in quanto questo segmento di memoria è usato per il codice di drivers, VMM, gestione di interrupt.
>Il codice in nonpaged pool, non può accedere alla page pool.

## File system
Comprende tre livelli di driver, ovvero i **volume drivers**: i quali sono a basso livello e interagiscono con l'hardware, i **file system drivers** (e.g. NTFS) ed i **file system filter divers** i quali eseguono funzioni di alto livello come la scansione dei virus.

### NTFS
NTFS è il file system nativo di windows, scala bene e comprende funzioni di compressione e crittografia e flussi di dati multipli.

Possiede una **MFT** (Master File Table) ed ogni file possiede una riga in essa, le informazioni dei file sono memorizzate come **attributi**, i quali possono essere **residenti** se sono memorizzati direttamente dentro la riga, **non residenti** se nella riga c'è solo l'intestazione ed i dati sono memorizzati nel disco.

Un **cluster** è la dimensione minima usata per memorizzare un file, se un file è più grande della dimensione di un cluster, ma più piccolo di due, verranno usati due cluster per memorizzarlo.
- **VCN** (Virtual Cluster Number): indica il cluster da cui parte un file
- **LCN** (Logical Cluster number): indica l'indirizzo del cluster sul quale è posizionato l'attributo
![[Clusters NTFS.png]]

Un file viene **cancellato** solo quando sono stati cancellati tutti i suoi hardlink.
Il **contenuto** di un file viene memorizzato in uno o più **data stream**:
- **Default** data stream: contenuti primari di file (e.g. testo, immagini)
- **Alternate** data stream: memorizza i metadati (e.g. autore, copyright)

I file sono **compressi** (se l'unità occupa più di 16 cluster da compresso, non viene memorizzato compresso), **crittografati** (crittografia eseguita in unità di compressione) e **sparsi**, ovvero grandi serie di bit zero sono memorizzati in blocchi (e.g. bitmap con grandi aree bianche).

