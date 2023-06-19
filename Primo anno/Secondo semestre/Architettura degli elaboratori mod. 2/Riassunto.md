## Cache diretta vs associativa
![[Organizzazione gerarchia.png]]
$$\text{N°blocks}=\frac{\text{Byte di dati}}{\text{Block size}}\quad \text{oppure}\quad 2^{\text{index}}$$
$$\text{Block size}=\frac{\text{Byte di dati}}{\text{N°blocks}}\quad \text{oppure}\quad 2^{\text{offset}}$$

- **Diretta**: $Linee = N°Blocks$

- **Associativa**: $Linee = \frac{N°blocks}{N°ways}$

$$\text{Index}  = \log_2(\text{Linee})$$
$$\text{Offset}=\log_2(\text{Block size})$$
$$\text{Tag}=\text{Address size} - \text{Index} - \text{Offset}$$

---
## Pipeline
**Senza forwarding**: ogni istruzione deve avere i dati pronti su ID, con register file ottimizzato nello stesso ciclo di clock vengono eseguiti sia WB dell'istruzione precedente sia ID di quella che aspetta il risultato, se non fosse ottimizzato, allora l'istruzione che aspetta il risultato dovrebbe ri-eseguire ID al ciclo di clock successivo alla WB

**Forwarding**:
- Branch: produce il dato da scrivere al 2° ciclo (ID)
- R-type: producono il dato da scrivere al 3° ciclo (EXE)
- Load: calcola l'indirizzo al 3° ciclo (EXE) produce il dato da scrivere al 4° (MEM)
- Store: calcola l'indirizzo al 3° ciclo (EXE) memorizza al 4° (MEM)

- $N°cicli = \text{cicli per istruzione} \cdot \text{quante volte viene ripetuto l'eventuale ciclo}$
- $IC = \text{n°di istruzioni} \cdot \text{quante volte viene ripetuto il ciclo}$
$$CPI=\frac{N°cicli}{IC}$$
$$Speedup = \frac{N°cicli (maggiore)}{N°cicli (minore)}$$


## Domande
-  **Fare un esempio di località spaziale e temporale. L'aumento della dimensione del blocco su che tipo di località potrebbe impattare? E l'aumento del livello di associatività?**
	Un esempio di località spaziale è dato dall’accesso sequenziale agli elementi di un array, mentre un esempio di località temporale è il contatore di un ciclo.
	L'aumento della dimensione del blocco può impattare positivamente sulla località spaziale in quanto verranno caricati in cache più dati alla volta, mentre l'aumento del livello di associatività riducendo i conflitti fa si che un dato che ci servirà in futuro non venga subito sovrascritto quindi impatta la località temporale.
	
- **Descrivere le differenze tra bus sincroni ed asincroni.**
	Per bus sincroni si intendono bus veloci con frequenza di clock uguale tra tutti gli elementi connessi, inoltre sono corti (per evitare il clock skew) e solitamente proprietari, mentre quelli asincroni usano varie frequenze di clock per i vari elementi connessi, per questo si usa un protocollo di handshaking (servono più linee) per cominciare a comunicare, inoltre si definiscono standard ad esempio PCIe.
	
-  **Che problematiche comportano le eccezioni in una CPU con pipeline?**
	Occorre annullare tutte le istruzioni entrate nella pipeline prima dell'eccezione (problematico se la pipeline è profonda), occorre modificare lo stadio EXE in modo che possa mettere in stallo la CPU, inoltre possono avvenire multiple issue le quali devono essere gestite da un sistema di priorità di gestione delle eccezioni.

##### 31-05-2022

- **Discutere i vantaggi principali della memoria virtuale.**
	La memoria virtuale da l'idea di avere a disposizione più memoria di quanta è effettivamente disponibile sfruttando dispositivi di memoria più bassi come hdd (swapping), inoltre grazie alla traduzione da indirizzo virtuale a fisico c'è una protezione degli accessi la quale assegna ad ogni indirizzo virtuale un indirizzo fisico differente (in generale ci sono più indirizzi virtuali che fisici), inoltre con questo meccanismo un programma può essere caricato ovunque in memoria, senza doverci preoccupare di ricompilarlo per un'area di memoria specifica.
- **Che problematiche comporta l'utilizzo del DMA con indirizzi fisici anzichè virtuali?**
	Comporta tutte le problematiche che avrebbe un sistema senza indirizzi virtuali, ovvero: mancanza di protezione degli accessi e difficoltà nell'implementazione del paging.
	
- **Cosa si intende con static e dynamic multiple-issue?**
	Parliamo di multiple-issue quando vogliamo creare una pipeline in cui vengono inserite più istruzioni alla volta. 
	Nell'approccio statico è il compilatore a raggruppare le istruzioni ed inserirle contemporaneamente nella pipeline (evitando hazards).
	Nell'approccio dinamico è la CPU a decidere ad ogni ciclo di clock quante istruzioni inserire nella pipeline, si parla quindi di CPU superscalari.

##### 23-06-2022

- **Si descriva cosa si intende per structural, data e control hazards.**
	Lo structural hazard si riferisce ad una limitazione hardware che non consente certe combinazioni di istruzioni nello stesso ciclo di clock (e.g. register file non ottimizzato) portando quindi ad un rallentamento nel sistema, per data hazard ci riferiamo a istruzioni consecutive dipendenti tra loro che possono causare problemi nell'accesso ai dati (e.g. dipendenze raw,war,waw), mentre per control hazard ci riferiamo all'incertezza di quale istruzione verrà caricata nella pipeline dopo un branch, per questo è opportuno implementare un buon predittore del branch per evitare di annullare molteplici istruzioni entrate nella pipeline a causa di una errata speculazione sul esito del branch.
	
- **Spiegare la differenza tra polling e interrupt driven IO.**
	Nel polling è la CPU che controlla periodicamente il dispositivo per vedere se deve trasferire dati (utile quando il dispositivo deve trasferire molto spesso come il applicazioni real time), mentre nell'interrupt driven IO è il dispositivo a generare un interrupt quando vuole comunicare (utile per dispositivi che trasmettono poco spesso).
- **Si descrivano vantaggi e svantaggi delle politiche write through e write back.**
	Nella politica write through ogni scrittura in cache (sw) comporta una scrittura al livello inferiore (RAM) questo comporta che ogni blocco può essere rimpiazzato senza problemi, ma le scritture sono molto lente.
	Nella politica write back solo quando in blocco deve essere rimpiazzato (collisione di lw) viene scritto nella memoria inferiore questo comporta che in assenza di conflitti non ci sia un overhead ma la sostituzione di un blocco in conflitto è più lenta e complessa.

##### 14-09-2022

- **Si spieghi il concetto di località spaziale e in che modo questo viene sfruttato nelle memorie cache.**
	Per località spaziale si intende il concetto per cui è meglio ad accedere ad aree di memoria contigue quando possibile in quanto il dato che si vuole elaborare potrebbe già essere presente in cache da un precedente load.
- **Descrivere, fornendo almeno un esempio, cosa si intende per interruzioni ed eccezioni.**
	Per eccezioni e interruzioni intendiamo un cambiamento del flusso delle istruzioni, per quanto riguarda le eccezioni, esse sono causate da un programma ad esempio potrebbe essere lanciata un'eccezione se un particolare input non è corretto, mentre le interruzioni sono dovute ad elementi esterni ad esempio un dispositivo che crea un interrupt perchè vuole comunicare.
- **Per quali tipi di periferiche il DMA è particolarmente efficace?**
	Per periferiche che comunicano molti dati di continuo come schede di rete.

##### Marta
- **Il Page Fault viene solitamente trattato come un’eccezione, coinvolgendo il Sistema Operativo. Discutere e motivare la scelta.**
	Il sistema operativo viene coinvolto per passare da user mode a supervisor mode oppure per saltare alla routine di gestione dell'eccezione.
	
- **Perchè il CPI ideale in un’architettura pipeline come quella vista a lezione è 1? Quali sono le cause per le quali il CPI reale risulta maggiore dell’ideale?**
	Perchè dopo che la pipeline è piena, dopo ogni ciclo di clock verrebbe idealmente completata una istruzione, a volte a causa degli stalli non è del tutto vero, per cui il CPI potrebbe essere maggiore di quello ideale.
- **Il TLB miss può dar luogo ad un cache miss? Motivare.**
	No, un TLB miss è già il "corrispettivo cache miss" per quanto riguarda la RAM, quindi possiamo dire che se avviene un TLB miss, è già avvenuto un cache miss, quando avviene un TLB miss, la pagina viene cercata in RAM e caricata nella TLB 
- **In che modo l’aumento del miss penalty della cache impatta sul CPI? L’aumento del ciclo di clock è legato al miss penalty?**
	I CPI potrebbero aumentare a causa di un grande tempo di attesa dovuto da un elevato miss penalty, mentre i cicli di clock non sono influenzati dal miss penalty.
	
- **I singoli core dei moderni microprocessori multicore sono superscalari e eseguono le istruzioni out-of-order. Commentare.**
	La CPU decide ad ogni ciclo di clock quante istruzioni inserire nella pipeline (multiple issue dinamico) e nella soluzione out-of-order la CPU può cambiare l'ordine di esecuzione delle istruzioni prima di raggrupparle e scrivere i risultati in ordine (in-order commit)
- **Un cache miss può dar luogo ad un page fault miss? Motivare.**
	Si indirettamente, in quanto dopo aver cercato un valore in cache e non averlo trovato si va a cercare in TLB, se non è presente si va a cercare nella page table dove se non è presente neanche genererà un page fault miss.
- **Perchè è necessaria la TLB nella traduzione da indirizzo virtuale a fisico?**
	Questa soluzione hardware è necessaria per aumentare il numero di accessi in RAM in quanto una page table potrebbe essere molto grande in RAM, con la TLB vengono conservate le ultime page table così se dovessero essere richieste in un breve lasso di tempo sarebbero già pronte (nella TLB sono presenti solo pagine valide, se in RAM un pagina viene invalidata, verrà invalidata anche nella TLB) 
- **Per invocare una funzione sarebbe sufficiente l’istruzione b (Branch)? Commentare.**
	No, bisogna una bl la qualche salva il PC+4 corrente nel link register (x30) ed alla fine della funzione il PC viene ripristinato in modo da eseguire la prossima istruzione.
- **Dal punto di vista della banda reale di un dispositivo di I/O, perchè conviene usare blocchi grandi, sempre che la l’applicazione specifica lo permetta? Esemplificare.**
	Si conviene sempre dato che aumenta la banda diminuendo le operazioni di comunicazione I/O.
- **Qual è il compito dell’assemblatore e del linker per generare un file eseguibile? A grandi linee, cosa sono le librerie statiche (SLL) e dinamiche (DLL)?**
	L'assemblatore traduce il codice assembly in codice macchina, il linker unisce i file oggetto creati dall'assemblatore e permette di usare funzioni e librerie condivise tra i file. Le librerie statiche sono pezzi di codice che vengono incorporati nel file che le richiama al momento di linking, mentre quelle dinamiche vengono chiamate dal sistema operativo durante l'esecuzione del programma.
- **Perchè la predizione dei salti condizionati è importante, e come viene realizzata nelle CPU moderne?**
	è importante predire l'esito corretto di un branch in quanto si possono caricare le istruzioni in anticipo nella pipeline, se l'esito previsto dovesse però essere sbagliato, le istruzioni entrate nella pipeline riguardanti il branch previsto (sbagliato) dovrebbero essere annullate generando così branch penalty.
	Possiamo prevedere l'esito di un branch in due modi principalmente: statico in cui prediciamo sempre il caso taken oppure not taken (50% di possibilità di fare giusto, ma anche di sbagliare) oppure dinamico dove teniamo traccia degli esiti passati dei branch e prediciamo il prossimo branch con queste informazioni. 
