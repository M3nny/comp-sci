Un algoritmo di **scheduling** decide quale processo viene eseguito ad un certo istante, esistono _varie caratteristiche_ che differenziano questo tipo di algoritmi.
## Caratteristiche
I **criteri** si basano su processi:
- **Processor-bound**: usa tutto il tempo di CPU disponibile
- **I/O bound**: genera richieste I/O velocemente e lascia la CPU libera
- **Batch**: richiedono lavoro da eseguire senza essere interrotti dall'utente
- **Interattivi**: richiedono frequenti input dall'utente

I **livelli** di scheduling si differenziano per l'importanza delle azioni eseguite in quel livello:
- **Alto**: determina quale job può iniziare lo scheduling
- **Intermedio**: determina che processi sospendere o mettere in stato ready
- **Basso**: assegna le priorità, esegue il dispatch e blocca i processi in caso di timeout

Un algoritmo di scheduling ha **due principali caratteristiche**:
- **Prelazione**:
	- I processi **con prelazione** possono essere rimossi dal processore (temporaneamente) prima che finiscano la loro esecuzione, importante in sistemi interattivi con molti input
	- I processi **senza prelazione** vengono eseguiti fino a che non finiscono il loro quanto di tempo o terminano, potrebbero anche bloccare processi più importanti
- **Priorità**:
	- **Statica**: non cambia nel tempo, per questo ha un basso overhead ed è facile da implementare
	- **Dinamica**: reattiva a cambiamenti, per questo ha un maggiore overhead il quale è giustificato dalla maggior capacità di agire
## Obbiettivi
In generale gli obbiettivi comuni a tutti gli algoritmi di scheduling sono:
- **Equità (fairness)**: ogni processo deve ricevere la CPU in modo equo
- **Predicibilità**: la politica dichiarata deve essere rispettata
- **Bilanciamento**: deve impegnare tutte le parti del sistema

Sistemi **Batch**:
	- **Throughput**: massimizzare il numero di processi serviti per unità di tempo
	- **Tempo di turnaround**: far evolvere e di seguito terminare il processo più velocemente possibile
	- **Utilizzo della CPU**: massimizzare l'uso della CPU

Sistemi **Interattivi**:
	- **Tempo di risposta**: deve essere breve
	- **Adeguatezza**: deve soddisfare le richieste e aspettative degli utenti

Sistemi **Real-time**:
	- **Rispettare le scadenze**
	- **Prevedibilità**: deve mantenere la qualità del servizio

---
### First-In-First-Out (FIFO)
L'algoritmo **FIFO** o **FCFS** (First-Come-First-Served) è il più **semplice** da realizzare in quanto è **senza prelazione**, dato che servirà sempre il primo processo ad arrivare è anche **fair** (se viene bloccato un processo dovrà poi rifare la coda).
Non è una scelta saggia però in quanto potrebbero esserci processi più importanti da servire, appunto non si usa quasi mai come algoritmo di scheduling principale.
### Shortest-Job-First (SJF)
Seleziona il **processo** (che secondo una stima) è **più vicino alla sua terminazione**, cosa che non è sempre facile da stimare, soprattutto se ci sono input da parte dell'utente.
Per i motivi sopra, questo algoritmo ha potenzialmente una **grande varianza**, ovvero la dispersione dei valori rispetto alla media del tempo d'attesa (che rispetto a FIFO è comunque minore) è alta.
Potrebbe causare **starvation** ai processi più lunghi.
### Shortest-Remaining-Time-First (SRT)
Questa è la versione **con prelazione** del _SJF_, la quale può causare una **varianza ancora più grande** dato che può avvenire la prelazione su un processo più lungo a favore di uno più corto, il che porta ancora a **più fenomeni di starving**, ed un **overhead significativo** dato che ci saranno ipoteticamente molte prelazioni (considerando che il processo in esecuzione finirà presto).
Teoricamente però ha un **ottimo tempo di attesa medio** migliore anche di _SJF_.
I problemi che aveva _SJF_ sulla stima dei tempi persiste.
### Round-Robin (RR)
È basato su _FIFO_, i processi però sono eseguiti per un **periodo di tempo limitato**, di seguito viene eseguita la **prelazione**.
L'obbiettivo è quello di **servire più processi "contemporaneamente"** possibile, in questo modo viene garantita la **fairness** dato che prima o poi un processo terminerà.
Bisogna fare **attenzione alla durata del quanto di tempo** da assegnare, il quale determinerà il costo dell'overhead dei context-switch.
### A Priorità
In questo algoritmo introduciamo $n$ **classi di priorità** (statica o dinamica) dove all'interno di ogni classe viene eseguito il _RR_.
I processi di classe più alta vengono eseguiti per primi, il che può portare a **starvation** dei processi di classe più bassa i quali non verranno mai eseguiti finchè esistono processi di classe più alta (risolvibile scegliendo dinamicamente che classe servire).
### Selfish Round-Robin
**Aumenta la priorità** con **l'età** del processo.
Esistono **due code**, all'inizio il processo viene inserito nella **coda di attesa** (holding), invecchiando, quando la sua priorità sarà uguale a quella dei processi pronti (attivi), allora entra nella **coda ready** dove verrà applicato il _RR_ (è quindi **fair**).
Possono anche esserci, volendo, diverse velocità di crescita della priorità.
### Highest-Response-Ratio-Next (HRRN)
**Migliora lo scheduling _SJF_** (ancora senza prelazione) implementando una **priorità dinamica** calcolata tramite: $\frac{\text{tempo di attesa + tempo di esecuzione}}{\text{tempo di esecuzione}}$, ovvero oltre a quanto tempo ci mette a finire, viene tenuto conto anche da quanto sta aspettando un processo, in questo modo si evita lo **starving** dei processi più lunghi.
### Code Multilivello con Feedback
Come osservato all'inizio, i processi possono essere di diversi tipi, e vorremo eseguire per primi i processi I/O bound mantenendo però la **fairness**.
Vengono implementate quindi $n$ **code**, ognuna con il proprio algoritmo di scheduling.
![[Code multilivello.png|600]]
All'inizio un processo **verrà inserito nella coda più alta**, se non termina nel quanto a sua disposizione in quella coda, **passa ad una più bassa**.
In questo modo <u>vengono serviti prima i processi corti tramite code <i>FIFO</i> e alla fine nella coda <i>RR</i></u> verranno eseguiti tutti i processi più lunghi.
Questo sistema porta con sè un **overhead** importante, il quale però **viene compensato** da una maggiore sensibilità ai cambiamenti.
### Fair Share (FSS)
**Controlla l'accesso degli utenti alle risorse** (un po' come schedulare gli utenti).
Esistono **gruppi utenti più importanti** i quali processi sono altrettanto importanti, questo scheduler decide **quanta potenza della CPU dedicare ad ogni gruppo**.
Se un gruppo di processi non arriva al suo obbiettivo in tempo, la **priorità del gruppo aumenta**, mantenendo così il principio di **fairness**.

## Scheduling per sistemi Real-Time
Finora abbiamo visto algoritmi che potevano andare meglio sia su sistemi _batch_ e sia su sistemi _interattivi_, i quali però sono ben diversi dai sistemi rigidi _real-time_, i quali si dividono in:
- **Soft real-time**: non garantisce che in vincoli temporali siano soddisfatti (e.g. streaming)
- **Hard real-time**: i vincoli temporali (periodici o asincroni) devono essere sempre soddisfatti, altrimenti potrebbero esserci conseguenze importanti (e.g. controllo del traffico aereo)



