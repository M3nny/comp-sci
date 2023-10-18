I thread sono nati per **aumentare la concorrenza e prestazioni** del SO in quanto il thread è più "leggero" di un processo e si ottiene un migliore sfruttamento se sono I/O bound, ovvero se il suo _bottleneck_ si trova nelle operazioni di I/O, non di CPU.

I thread **condividono** con il proprio processo:
- Spazio di indirizzamento
- File aperti

ma <u>NON</u> condividono:
- Registri
- Stack
- Maschere dei segnali

I thread sono definiti "leggeri" in quanto la loro **creazione** non richiede l'inizializzazione delle risorse condivise riducendo di conseguenza anche l'overhead di **terminazione**.

Un processo **raggruppa risorse**, mentre i thread gli **eseguono** il programma che usa quelle risorse.

Il **ciclo di vita di un thread** è analogo al [[Processi#Ciclo di vita di un processo|ciclo di vita di un processo]] con l'aggiunta di due stati: **waiting** quando è bloccato da un evento di un altro thread e **sleeping** quando è bloccato per un tempo prefissato.
Anche per quanto riguarda le operazioni possibili abbiamo due aggiunte:
- **Cancellazione**: indica che un thread dovrebbe essere cancellato, ma non è detto che lo sarà, inoltre i thread possono disabilitare o mascherare i segnali di cancellazione (eccetto la _abort_)
- **Join**: il thread primario che esegue una _join_ con altri thread, rimarrà in attesa finche quest'ultimi non avranno terminato la loro esecuzione

Lo standard **POSIX** definisce anche uno standard nei sistemi unix su come devono essere eseguite le chiamate di sistema riguardanti i Pthread (package di thread).

---
## Modelli di thread
Esistono tre modelli di threading, ognuno con i propri vantaggi e svantaggi.
### Livello utente (molti-a-uno)
![[Thread livello utente.png|600]]
Non possono accedere direttamente al kernel, in quanto creati da librerie a tempo di esecuzione.
Il SO associa tutti i thread di un processo ad un **unico contesto di esecuzione**.
**Vantaggi**:
- Scheduling a livello utente per ottimizzare le prestazioni
- Si evita il cambio di contesto grazie alla sincronizzazione a livello utente
- Permette di eseguire thread (virtuali) anche se la CPU internamente non ne è in grado garantendo così maggiore **portabilità**
**Svantaggi**:
Dato che è visto come un singolo contesto di esecuzione dal kernel, un thread bloccato (e.g. I/O) blocca tutto il processo <u>diminuendo la performance</u>, inoltre <u>non può essere schedulato da più core in una sola volta</u>.
### Livello kernel (uno-a-uno)
![[Thread livello kernel.png|600]]
**Ogni thread viene mappato al proprio contesto di esecuzione**, per questo è la scelta migliore per applicazioni multithread.
**Vantaggi**:
- Aumento della scalabilità, interattività e throughput
- Il kernel oltre la tabella dei processi ha anche la tabella dei thread
- Un thread bloccato può non bloccare tutto il processo
**Svantaggi**:
Ci sono <u>overhead dovuti al cambio di contesti</u> e <u>ridotta portabilità</u>, in quanto le API sono specifiche per ogni SO.
### Ibridi (molti-a-molti)
![[Thread ibridi.png|600]]
Questa implementazione mette assieme i vantaggi dei due modelli precedenti.
- Il numero di thread a livello utente non deve non deve per forza rispecchiare il numero di contesti di esecuzione. 
- Può ridurre l'overhead tramite il **thread pooling**
- Grazie ai **worker threads**, i thread di livello kernel sono _persistenti_ migliorando così le prestazioni quando i thread vengono creati e distrutti molto spesso

Permette l'**utilizzo dello scheduler a livello utente** per imitare le funzionalità di livello kernel tramite processori virtuali, rendendo così questo modello portabile anche su sistemi multiprocessori.

---
## Thread in Linux e Windows
In **Linux** viene allocato lo stesso descrittore sia per processi e sia per thread, infatti si chiamano **task** senza fare distinzione.
Si generano dei task tramite `fork()`, mentre se si vogliono specificare risorse da condividere con il task figlio si usa `clone()`.

In **Windows** i processi contengono i programmi, gli handle (riferimenti ad oggetti) ed i thread con cui condividono le risorse.
Può raggruppare processi in **job** ed i thread possono creare **fiber** i quali vengono eseguiti nel contesto del thread che lo crea, garantendo così un vantaggio nel cambio di contesto a livello utente.
>Un thread può diventare fiber, e la relazione tra thread e fiber è molti-a-molti.

Anche Windows fornisce ad ogni processo un **pool di thread** (coda di task da eseguire) composto da **thread worker** (livello kernel) i quali eseguono funzioni previste dal thread utente, questo meccanismo evita la creazione/distruzione continua di thread.
>I thread in attesa non possono essere riassegnati ad un altro task da eseguire.
