Quando parliamo di **sistema operativo** parliamo di _software che controlla l'hardware_, ovvero un gestore di risorse, dove ogni programma richiede uno _spazio_ ed un _tempo_ in cui allocare risorse.

Interfacciandosi <u>verso l'alto</u>, l'utente vede una macchina astratta, mentre quando il _S.O._ si interfaccia <u>verso il basso</u> ci sono le risorse, le quali devono essere gestite al meglio.

Prevede due **modalità di esecuzione** per il processore:
- **User mode**: per eseguire le applicazioni utente
- **Kernel mode**: è la modalità in cui viene eseguito il SO (prevalentemente), inoltre alcune volte il processore può anche accedere a istruzioni e risorse privilegiate per conto dei processi.

---
## Storia

### I gen.
Non esistono SO, la programmazione avviene in linguaggio macchina o cablando circuiti.
### II gen.
Nasce assembly e fortran assieme alle schede perforate, in questo periodo con la **monoprogrammazione** è possibile eseguire un _job_ per volta.

Con i primi SO **batch** potevano essere eseguiti dei job consecutivamente senza ulteriore intervento.

La memoria conteneva sempre il SO ed un eventuale compilatore il quale veniva poi sostituito dal programma in esecuzione dopo aver finito di compilare.
### III gen.
Nasce la **multiprogrammazione** consentendo di gestire una <u>pool di job</u>, ciò significa che un job può usare la CPU mentre altri job usano altre risorse.
Per questo nascono anche:
- **Spooling**: cambio di job durante operazioni di I/O da parte dell'utente
- **Scheduling**: basato su un sistema di divisione del tempo in quanti chiamato _time sharing_ dove ogni job ha un tempo limite per essere eseguito prima di passare al prossimo job 

Compaiono _mainframe_ e _minicomputer_ assieme a linguaggi di alto livello come _C_, oltre ai primi terminali interattivi e l'introduzione della [[Mapping#Principio di funzionamento|memoria virtuale]].
Nascono inoltre i primi sistemi **real time** dove una risposta è data entro un più o meno _breve_ lasso di tempo.

Viene stabilito lo standard **POSIX** per rendere compatibili varie versioni di shell per le chiamate di sistema.

Comincia lo sviluppo di internet (TCP/IP).
### IV gen.
Nascono **personal computer** e **workstation** assieme alle prime **GUI** e si diffonde il modello **client/server** il quale poi porta a **sistemi paralleli** (più unità di elaborazione che hanno risorse condivise) e **sistemi distribuiti** (diverse unità di elaborazione complete cooperanti tramite linee di comunicazione) i quali usano linguaggi sempre più astratti e che supportano il **multithreading** e **oggetti**.

Nasce il **World Wide Web** e con esso il _middleware_ il quale serve a collegare applicazione di vari _servizi web_.

### V gen.
Comincia lo sviluppo di tecnologia per dispositivi **mobili** i quali porteranno poi all'**IoT** supportato dal **cloud computing**.

---
## Componenti dei sistemi operativi
#### CPU
Contiene **registri** tra cui alcuni speciali:
- **PC**: Program Counter
- **SP**: Stack Pointer
- **PSW**: Program Status Word il quale contiene un descrittore dello stato dei programmi in esecuzione e della modalità in cui si trova il SO
- **Base & limit**: definiscono lo spazio di indirizzamento logico del programma, in modo da non sovrapporsi ad altri processi

Per quanto riguarda componenti software abbiamo:
- Processor scheduler
- Gestore della memoria, I/O, del file system e della IPC (Interprocess communication)

Una CPU può essere **multithreading** ovvero è in grado di supportare a livello hardware più thread e/o può anche essere **multiprocessore** ovvero possiede più core.
I **thread** sono componenti dei programmi eseguiti in modo indipendente che però usano uno _spazio condiviso_ con il processo padre ed altri suoi thread.

#### Memoria
Oltre a registri e RAM abbiamo anche:
- **ROM** (Read Only Memory): la quale non è volatile, è veloce, economica e programmata solo dal costruttore
- **EEPROM** (Electrical Erasable Programmable ROM): la quale si differenzia dalla ROM in quanto è riscrivibile
- **CMOS** (Complementary Metal-Oxide Semiconductor): è volatile è viene usato spesso per memorizzare data e ora

- **Caches**: mantengono copie di dati che saranno usati a breve, essendo veloci aumentano anche la velocità di esecuzione di un programma.
- **Buffers**: memoria temporanea usate per tenere i dati durante operazioni di I/O e per il coordinamento delle comunicazioni tra dispositivi di velocità diverse (supporta l'elaborazione asincrona)
- **Spooling**: permette di inviare richieste da una periferica senza aspettare che il dispositivo sia pronto a servire la richiesta
- **Memoria virtuale**: permette di eseguire richieste che esigono più memoria di quanta disponibile usando lo swapping

Vari elementi possono interfacciarsi con il SO tramite **driver** i quali sono diversi per ogni SO che supporta, possono essere installati tramite:
- Inserzione manuale e riavviando
- In un file del SO e riavviando
- **Plug and play**: consente ai SO di configurare hardware appena installato senza l'interazione dell'utente, per fare ciò l'hardware deve:
	- _Identificarsi_ univocamente
	- _Comunicare_ al SO le risorse ed i servizi che vuole
	- _Identificare il driver_

#### I/O
Vediamo tre modalità in cui possono essere eseguite le operazioni di input/output
- **Busy waiting**: attesa attiva fino alla fine delle operazioni di I/O
- **Interrupt**: il driver genera una interruzione e poi si selezione il corrispondente gestore dell'interruzione
- **DMA** (Direct Memory Access): svincola la CPU dal controllo delle operazioni di I/O

#### Bus
I bus sono formati da un insieme di **tracce** e **porte** (connettono due dispositivi).
Alcuni bus principali sono:
- **PCIe** (Peripheral Component Interconnect Express): connette la CPU ai dispositivi con bande di trasferimento diverse anche elevate
- **AGP** (Accelerated Graphic Port): per schede video
- **DMI** (Direct Media Interface): bus a banda larga pensato per evitare bottleneck nel connettere la parte superiore della scheda madre con la parte inferiore più lenta
- **SATA** (Serial Advanced Technology Attachment): per hdd e dischi ottici
- **USB** (Universal Serial Bus): connette dispositivi lenti senza dover riavviare
- **SCSI** (Small Computer System Interface): usato per fornire compatibilità tra dispositivi, oggi usato per server e workstations

### Tipi di S.O.
- **Embedded**: gestiscono bene dispositivi con un numero limitato di risorse (elettrodomestici)
- **Mainframe**: garantiscono grandi capacità di I/O per sistemi centralizzati
- **Server**: gestiscono molteplici utenti connessi simultaneamente
- **Multiprocessore**: forniscono comunicazione e coerenza nella gestione dei processi paralleli
- **PC**: fornisce multiprogrammazione per un utente
- **Palmari (PDA)**: come android e iOS gestiscono molti sensori e app
- **Real-time**: gestiscono task con scadenze brevi (sistemi di controllo)
- **Smart-card**: inseriti in piccoli chip con poca potenza di calcolo possono eseguire poche istruzioni

---
### Concetti base
Le architetture degli elaboratori racchiudono funzioni del SO in hardware per migliorare le prestazioni e garantire la **protezione**.

Infatti un processore:
- Impedisce ai processi di accedere a zone di memoria delimitate grazie a dei registri che vengono modificati solo in kernel mode
- Fornisce due modalità di esecuzione (user e kernel mode)
- Fornisce **privilegi minimi** ad ogni utente

A differenza di un _interrupt di I/O oppure periodici_, i quali vengono usati per evitare che un processo usi sempre la CPU per se stesso, le **eccezioni** sono degli interrupt in risposta agli _errori_.

Durante il **bootstrap** eseguito dal **BIOS** l'utente non può accedere a componenti hardware del computer, cosa che invece è concessa nel suo successore: **EFI** il quale è dotato di shell e anche dei driver.

Un **processo** è un _programma in esecuzione_ e possiede:
- Spazio di indirizzamento
- Descrittore che contiene informazioni riguardo al processo (e.g. è running oppure no)
- Un UID che indentifica l'utente che ha eseguito il processo
- Un PID che lo distingue da altri processi
Più processi possono comunicare tra loro tramite **pipe** ovvero uno pseudofile facente parte del **file system**

Una **chiamata di sistema** eseguita da un processo utente avviene tramite _TRAP_ la quale da il controllo al SO (passa in kernel mode) e al termine della chiamata il controllo passa alla prossima istruzione del processo utente (user mode).


### Architetture di S.O.
Le architetture supportano hardware e software eterogenei.

1. Nelle architetture **monolitiche** ogni componente fa parte del kernel e può comunicare direttamente con qualsiasi altra portando così ad una grande <u>efficienza</u> con il principale svantaggio di avere <u>difficoltà ad identificare eventuali fonti di errori</u>.

2. In quelle **a livelli** invece si ha l'<u>isolamento</u>, ovvero ogni livello comunica solo con quello sopra o sotto di lui, questo comporta che le richieste dei processi dovranno eventualmente attraversare vari livelli per cui il <u>throughput può essere minore rispetto alle architetture monolitiche</u>.

3. Un'architettura **microkernel** fornisce <u>servizi limitati</u> mantenendo un <u>elevato grado di modularità</u>.
