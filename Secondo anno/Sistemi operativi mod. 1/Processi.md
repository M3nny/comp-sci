I processi consentono di eseguire attività simultanee, e nel farlo cambiano **stato** secondo il volere del sistema operativo.

![[Modello di processo.png]]
Nell'immagine è rappresentata la multiprogrammazione di quattro programmi, dove possiamo notare che i processi sono _indipendenti_ ed _un solo programma usa la CPU in ogni quanto di tempo_ per questo parliamo di **pseudo parallelismo**.

Un processo ha uno **spazio di indirizzamento** composto da tre regioni:
- **Testo**: memorizza il codice
- **Dati**: memorizza variabili e spazi di memoria allocata dinamicamente
- **Stack**: memorizza istruzioni e variabili locali per le chiamate di funzioni

Il **gestore di processi** è in grado far cambiare _stato_ a quest'ultimi, tra le azioni che può fare troviamo: creazione, distruzione, sospensione, ripresa, risveglio ma può anche modificare la **priorità** di un processo (si usano degli interi da -20 a 19).

I processi possono essere di due tipi principalmente:
- **Attivi**: solitamente collegati ad utenti
- **In background (deamons)**: non associati ad utenti, ma con funzioni specifiche

---
## Operazioni sui processi
### Creazione
La **creazione di processi** avviene in più occasioni:
- All'avvio
- Dopo una chiamata di sistema o richiesta di utente per la creazione di un processo
- Per servire attività di job in batch

In **Unix** usiamo l'istruzione `fork()` per creare un **clone** del processo chiamante il quale all'inizio condividerà le stesse risorse del processo padre fino alla prima istruzione di _write_ da parte di uno dei due.

In **Windows** usiamo `CreateProcess()` la quale crea un nuovo processo con **spazio separato** già dall'inizio.
### Chiusura
La **chiusura di processi** avviene anch'essa in più modi:
- Uscita normale (volontaria)
- Uscita per un errore (volontaria) oppure per un errore critico (non volontaria)
- Uscita forzata da un altro processo (non volontaria)

Rispettivamente in Unix e Windows usiamo `exit()` e `ExitProcess()` per le uscite normali, mentre per la terminazione forzata usiamo `kill()` e `TerminateProcess()`.

Quando un processo padre viene **distrutto** il SO può decidere se distruggere anche i suoi figli oppure consentire ai figli di evolvere indipendentemente.
Su Windows non esiste questo concetto di **gerarchia**, tutti i processi sono uguali (non discendono) però il padre ha un _handle_ per gestire il figlio, il quale può essere passato anche ad altri processi.
### Ciclo di vita di un processo
Un processo si sposta attraverso vari stati discreti, tra cui:
- **Running**: è in esecuzione
- **Ready**: il processo andrà in esecuzione quando il processore sarà disponibile, con il <u>dispatching</u> verrà assegnato al processore il primo processo della lista _ready_
- **Blocked**: è in attesa di qualche evento prima di poter evolvere
>Questi due ultimi stati hanno una lista ciascuno per tenere i riferimenti ai processi non in esecuzione.

Un processo può anche essere **sospeso** da se stesso oppure da un altro processo, fare ciò **rimuove in tempo indeterminato** il processo dalla contesa per il tempo sul processore.
>Utile per debugging e per rilevare minacce alla sicurezza.
>Inoltre può essere sospeso sia da ready, sia da blocked.

![[Ciclo di vita.png|600]]
Ovviamente un processo quando finirà la sua esecuzione in modo naturale, passerà da running a dead.

---
### Process Control Block
Il SO mantiene dei _puntatori_ ai **PCB** (Process Control Block) di ogni processo in una tabella che ne consente un _rapido accesso_.
Quando un processo termina, il SO lo rimuove dalla tabella e libera le risorse da esso utilizzate.

![[Process table.png]]
### Cambio di contesto
Un evento che può far cambiare lo stato di un processo da _running_ a _blocked_ è il **cambio di contesto**.
Il SO deve quindi **salvare** il contesto di esecuzione del processo _running_ nel suo PCB e caricare il contesto del processo _ready_ dal PCB.

### Utilizzo della CPU
L'utilizzo della CPU in funzione del grado di multiprogrammazione è dato dalla formula:
$$1-p^n$$
dove $n$ sono i processi in memoria e $p$ è la probabilità che un processo sia in attesa di I/O.
>[!Example]
>Trovare il numero di processi tale per cui quando la probabilità di I/O è pari al 30% la CPU sia usata al massimo per l'80%
>$$1-0.3^n<0.8\quad\implies\quad0.3^n>0.2\quad\implies\quad n\cdot\log(0.3)>\log(0.2)$$
>dato che $\log(0.3)$ è negativo il segno cambia
>$$n<\frac{\log(0.2)}{\log(0.3)}=1.3367$$

---
## Interrupts
Con questa tecnica il software è abilitato a **rispondere ai segnali hardware** con _basso overhead_.
Un **interrupt** può essere chiamato dal processo e quindi è **sincrono** con le operazioni del processo, oppure può essere **asincrono** se è chiamato da un evento esterno.

La **gestione dell'interrupt** avviene nel seguente modo:
1. CPU completa l'istruzione corrente, poi interrompe il processo corrente
2. Il processo esegue una funzione di gestione dell'interrupt del kernel
3. Uno dei **gestori di interrupt** (memorizzati in un _vettore di interrupt_) determina come rispondere
4. Finito il gestore di interrupt, viene ripreso il processo interrotto o viene eseguito il processo successivo

Possiamo gli _interrupt_ generati da dispositivi esterni alla CPU:
- Operazioni di I/O
- Fine di un quanto di un processo
- Comunicazione tra due processi (IPC)
mentre le **eccezioni** indicano che è avvenuto un guasto:
- Fault: e.g. segmentation fault
- Trap: e.g. overflow, breakpoint nel codice
- Abort: quando avvengono double-fault ovvero la CPU non riesce a gestire sequenzialmente una routine che gestisce un errore che a sua volta ha causato un errore
### Segnali
Sono interruzioni che notificano ad un processo l'**occorrenza di un evento**.
I processi possono (riguardo al segnale):
- **Ricevere**: specifica una routine
- **Ignorare**: viene eseguita una routine di default
- **Mascherare**: indica al SO di non consegnare segnali di quel tipo fino a che il mascheramento verso quel tipo di segnale è attivo, utile in processi critici che non vogliono essere interrotti
### Message passing
Possono essere **unidirezionali** o **bidirezionali**, possono essere:
- **Bloccanti**: se si richiede a chi riceve di notificare quando si è ricevuto il messaggio
- **Non bloccanti**: permette a chi invia di continuare con altre elaborazioni
L'implementazione comune è la **pipe**: una _regione di memoria_ che funge da buffer consentendo a più processi di scambiarsi dati.

>Nei **sistemi distribuiti** si usano tecniche di **acknowledgement** e **timeout** usando porte specifiche per capire con che servizio comunicare.

Un altro approccio è il **polling** il quale è poco efficiente in molti casi dato che la CPU deve richiedere ripetutamente lo stato di ogni dispositivo, è utile solo per dispositivi che comunicano molto.
