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

---
## Scheduling per sistemi Real-Time
Finora abbiamo visto algoritmi che potevano andare meglio sia su sistemi _batch_ e sia su sistemi _interattivi_, i quali però sono ben diversi dai sistemi rigidi _real-time_, i quali si dividono in:
- **Soft real-time**: non garantisce che in vincoli temporali siano soddisfatti (e.g. streaming)
- **Hard real-time**: i vincoli temporali (periodici o asincroni) devono essere sempre soddisfatti, altrimenti potrebbero esserci conseguenze importanti (e.g. controllo del traffico aereo)

Avendo $m$ eventi periodici dove l'evento $i$ avviene nel periodo $P_i$ e richiede $C_i$ secondi di CPU, si può gestire i carico solo se:
$$\sum_{i=1}^m\frac{C_i}{P_i}\leq 1$$
ovvero il sistema **è schedulabile** solo se tutti gli eventi richiedono al massimo $P_i$ secondi di CPU, dove il periodo $P_i$ può anche variare da evento ad evento (come i secondi $C_i$ richiesti).

### Deadline scheduling
I processi devono essere completati **entro un tempo stabilito**, dopo il quale il loro risultato diventa inutile.
**Difficile da implementare** in quanto bisogna conoscere i requisiti delle risorse in anticipo, comporta **notevole overhead** ed il servizio offerto agli altri processi potrebbe essere ridotto.
### Rate-Monotonic (RM)
**Aumenta la priorità del processo** monotonicamente con la frequenza con cui deve essere eseguito, l'algoritmo usato alla fine è il _RR_.
Favorisce quindi i processi periodici eseguiti spesso.
Può anche essere implementata una **deadline** per processi con scadenza diversa dal loro periodo.
### Earliest-Deadline-First (EDF)
Sceglie sempre il processo con la **scadenza più vicina**, anche pre-rilasciando il processo corrente, in questo modo si massimizza il throughput e si minimizza il tempo di attesa.
### Minimum-Laxity-First
Si comporta similmente ad _EDF_ con la differenza che **basa la priorità sulla lassità**, ovvero la differenza temporale tra deadline, tempo passato dallo stato di ready e tempo rimanente:
$$L=\text{Deadline}-\text{Tempo passato da ready}-\text{Tempo rimanente}$$
ovviamente servono tutte queste informazioni per poter schedulare correttamente.

---
## Scheduling di thread
Un processo conosce la rilevanza dei thread figli, per questo occorrerebbero algoritmi di scheduling parametrizzati, dove il **meccanismo** risiede nel **kernel** ed i parametri dovrebbero essere scelti dal processo padre, definendo quindi una **politica** a livello utente.
- **Scheduling a livello utente**:
	1. Il kernel preleva un processo
	2. Il processo preleva un proprio thread figlio

- **Scheduling a livello kernel**: il kernel preleva un thread di un processo
