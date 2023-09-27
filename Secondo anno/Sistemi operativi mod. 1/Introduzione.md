Quando parliamo di **sistema operativo** parliamo di _software che controlla l'hardware_, ovvero un gestore di risorse, dove ogni programma richiede uno _spazio_ ed un _tempo_ in cui allocare risorse.

Interfacciandosi <u>verso l'alto</u>, l'utente vede una macchina astratta, mentre quando il _S.O._ si interfaccia <u>verso il basso</u> ci sono le risorse, le quali devono essere gestite al meglio.

Prevede due **modalità di esecuzione** per il processore:
- **User mode**: per eseguire le applicazioni utente
- **Kernel mode**: è la modalità in cui viene eseguito il SO (prevalentemente)

---
## Storia

### I gen.
Non esistono SO, la programmazione avviene in linguaggio macchina o cablando circuiti.
### II gen.
Nasce assembly e fortran assieme alle schede perforate, in questo periodo con la **monoprogrammazione** è possibile eseguire un _job_ per volta.

Con i primi SO **batch** potevano essere eseguiti dei job consecutivamente senza ulteriore intervento.

La memoria conteneva sempre il SO ed un eventuale compilatore il quale veniva poi sostituito dal programma in esecuzione dopo aver finito di compilare.
### III gen.
Nasce la _multiprogrammazione_ consentendo di gestire una <u>pool di job</u>, ciò significa che un job può usare la CPU mentre altri job usano altre risorse.
Per questo nascono anche:
- **Spooling**: cambio di job durante operazioni di I/O da parte dell'utente
- **Scheduling**: basato su un sistema di divisione del tempo in quanti chiamato _time sharing_ dove ogni job ha un tempo limite per essere eseguito prima di passare al prossimo job 

Compaiono _mainframe_ e _minicomputer_ assieme a linguaggi di alto livello come _C_, oltre ai primi terminali interattivi e l'introduzione della [[Mapping#Principio di funzionamento|memoria virtuale]].
Nascono inoltre i primi sistemi **real time** dove una risposta è data entro un più o meno _breve_ lasso di tempo.

Viene stabilito lo standard **POSIX** per rendere compatibili varie versioni di shell per le chiamate di sistema.

Comincia lo sviluppo di internet (TCP/IP).
### IV gen.
Nascono **personal computer** e **workstation** assieme alle prime **GUI** e si diffonde il modello **client/server** il quale poi porta a **sistemi paralleli** (più unità di elaborazione che hanno risorse condivise) e **sistemi distribuiti** (diverse unità di elaborazione complete cooperanti tramite linee di comunicazione) i quali usano linguaggi sempre più astratti e che supportano il _multithreading_ e _oggetti_.

Nasce il **World Wide Web** e con esso il **middleware** il quale serve a collegare applicazione di vari **servizi web**.

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

Una CPU può essere **multithreading** ovvero è in grado di supportare a livello hardware più thread e/o può anche essere **multiprocessore** ovvero possiede più core.

#### Memoria
Oltre a registri, cache e RAM abbiamo anche:
- **ROM** (Read Only Memory): la quale non è volatile, è veloce, economica e programmata solo dal costruttore
- **EEPROM** (Electrical Erasable ROM): la quale si differenzia dalla ROM in quanto è riscrivibile
- **CMOS** (Complementary Metal-Oxide Semiconductor): è volatile è viene usato spesso per memorizzare data e ora

Vari elementi possono interfacciarsi con il SO tramite **driver** i quali sono diversi per ogni SO che supporta, possono essere installati tramite:
- Inserzione manuale e riavviando
- In un file del SO e riavviando
- Plug and play

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

---
## Tipi di S.O.
- **Embedded**: gestiscono bene dispositivi con un numero limitato di risorse (elettrodomestici)
- **Mainframe**: garantiscono grandi capacità di I/O per sistemi centralizzati
- **Server**: gestiscono molteplici utenti connessi simultaneamente
- **Multiprocessore**: forniscono comunicazione e coerenza nella gestione dei processi paralleli
- **PC**: fornisce multiprogrammazione per un utente
- **Palmari (PDA)**: come android e iOS gestiscono molti sensori e app
- **Real-time**: gestiscono task con scadenze brevi (sistemi di controllo)