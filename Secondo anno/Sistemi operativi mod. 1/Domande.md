- **Indicare le due funzioni principali di un sistema operativo.**
	essere una macchina astratta per l'utente ed essere un gestore di risorse.

- **Descrivere i diversi tipi di sistema operativo e dare un esempio di applicazione per ciascuno.**
	- **Embedded**: gestiscono bene dispositivi con un numero limitato di risorse (elettrodomestici)
	- **Mainframe**: garantiscono grandi capacità di I/O per sistemi centralizzati
	- **Server**: gestiscono molteplici utenti connessi simultaneamente
	- **Multiprocessore**: forniscono comunicazione e coerenza nella gestione dei processi paralleli
	- **PC**: fornisce multiprogrammazione per un utente
	- **Palmari (PDA)**: come android e iOS gestiscono molti sensori e app
	- **Real-time**: gestiscono task con scadenze brevi (sistemi di controllo)
	- **Smart-card**: inseriti in piccoli chip con poca potenza di calcolo possono eseguire poche istruzioni

- **In cosa differiscono i sistemi timesharing e i sistemi multiprogrammazione?**
	Esistono più processi in entrambi i sistemi, multiprogrammazione è un termine generale, mentre timesharing sta ad indicare un metodo di scheduling nei sistemi di multiprogrammazione.

- **Cosa si intende per DMA, come viene utilizzato e che vantaggi può portare in un sistema operativo?**
	Il Direct Memory Access è un componente hardware che svincola la CPU dalle operazioni di I/O, rendendola libera ad altre operazioni.

- **Indicare i principali obbiettivi dei sistemi operativi e indicarne due che possono essere in contrasto.**
	efficienza, robustezza, scalabilità, estensibilità, portabilità, sicurezza, protezione, interattività, usabilità.
	Sicurezza ed efficienza potrebbero essere in contrasto dato che per avere sicurezza sarà necessario fare operazioni aggiuntive che potrebbero rallentare il sistema.

  - **Definire modalità utente e modalità nucleo in un sistema operativo e spiegarne l’utilizzo e la motivazione.**
	La CPU può essere in modalità utente per le applicazioni utente, mentre la modalità nucleo per le operazioni privilegiate e gestione hardware.
	I processi utente possono comunque richiedere di fare operazioni privilegiate tramite chiamate di sistema.

- **Indicare quale di queste istruzioni dovrebbe essere consentita solo in modalità nucleo: 
	a. Disabilitare gli interrupt
	b. Leggere il dispositivo che calcola l’ora corrente
	c. Impostare il dispositivo che calcola l’ora corrente
	d. Cambiare la mappa di memoria.**
	a, c tramite chiamata di sistema (quindi anche utente volendo), d.

- **In cosa differiscono i sistemi operativi con architettura monolitica e a microkernel?**
	Nel sistema monolitco tutte le risorse dentro al nucleo il che lo rende efficiente dato che queste si scambiano dati più velocemente.
	In un sistema microkernel ci sono poche risorse dentro al nucleo il che lo rende più modulare.

- **Perché è utile distinguere la politica di gestione e il meccanismo di attuazione delle funzioni di un sistema operativo? Dare esempi.**
	Perchè una politica può essere implementata con più meccanismi, ad esempio lo scheduling.

- **Se un processore usa una pipeline con quattro fasi e ogni fase impiega 1 ns per eseguire il proprio compito, il sistema quante istruzioni può eseguire per secondo? Spiegare in dettaglio la risposta.**
	A pipeline piena viene completata l'ultima fase di una istruzione ogni $1$ns (escludendo dipendenze che non influenzano tanto il totale), quindi $\frac{1s}{1ns}=10^9$ istruzioni al secondo.

- **Considerate un sistema con memoria cache, memoria principale (RAM) e disco e un sistema operativo con memoria virtuale che accede ad una parola nella cache in 2 ns, una parola nella RAM in 10 ns una parola nel disco in 10 ms. Se quando si cerca una parola la percentuale di successo nella cache è del 95% (Hit rate) e nella memoria principale (se la ricerca nella cache fallisce) è del 99% quanto è il tempo medio d’accesso a una parola?**
	$$Avg=\text{(Hit ratio * Cache access time) + ((Cache miss) * Page hit ratio * RAM access time) + ((Cache miss) * (Page fault) * Disk access time)}$$
	$$Avg=(0.95\cdot 2\cdot10^{-9})+(0.05\cdot0.99\cdot10\cdot10^{-9})+(0.05\cdot 0.01\cdot 10\cdot10^{-3})$$

- **Spiegare in cosa consiste e come viene usata un’istruzione trap nel sistema operativo.**
	è una chiamata di sistema che viene usata quando un processo vuole passare il controllo al SO oppure in caso di eccezioni.

- **Indicare in cosa differiscono i file speciali a blocchi e a caratteri?**
	I file speciali vengono usati in Unix per vedere e trattare dispositivi I/O come file, in particolare quelli a blocchi vengono usati per dispositivi a formati da blocchi (e.g. memorie), mentre quelli a caratteri per dispositivi che usano caratteri come I/O (e.g. stampanti).

---

- **Descrivere il meccanismo di gestione di interrupt in sistemi operativi. Dare un esempio**
	La CPU completa l'istruzione corrente, poi il processo esegue una funzione di gestione dell'interrupt, uno dei gestori di interrupt determina come rispondere, poi viene ripreso il processo interrotto o eseguito quello successivo.
	Un esempio è l'input da parte dell'utente.

- **Se in un sistema sono presenti in memoria sei programmi, che per la metà del tempo sono in attesa di un I/O, che percentuale di tempo di CPU viene sprecata?**
	$$T_{cpu}=1-p^n=1-0.5^6=0.98=98\%$$
	viene sprecato il $2\%$ del tempo.

- **L’uso della multiprogrammazione con esecuzione (pseudo) parallela permette spesso di abbreviare i tempi di esecuzione dei job rispetto all’esecuzione sequenziale. Considerare due job che iniziano insieme, ognuno dei quali richiede un tempo di CPU di 20 min, e di attesa della I/O per 50%: quanto tempo impiega il secondo per terminare se sono eseguiti in sequenza e quanto se eseguiti in parallelo?**
	In sequenza: $(20+10)\cdot2=60$ minuti
	In parallelo: le operazioni di I/O del primo processo sono in parallelo con l'esecuzione di 10 min del secondo processo $(20+20+10)=50$ minuti

- **In un sistema multiprogrammato con un sei programmi in memoria contemporaneamente, se ogni processo passi il 40% del tempo in attesa di un I/O, qual è l’utilizzo della CPU?**
	$$T_{cpu}=1-p^n=1-0.4^6=0.99$$

- **Assumendo di voler scaricare da Internet un file da 2 GB, disponibile in diversi siti mirror, ciascuno dei quali può inviarne una parte, assumendo che una richiesta specifichi i byte di inizio e di fine del file, indicate come si potrebbe utilizzare i thread per migliorare il tempo di download.**
	Si potrebbero avere più thread che prendono dati dalla rete, il thread principale, farà una join per aspettare che tutti i thread abbiano finito di scaricare la loro parte, per poi unire le parti di file scaricate in ordine tramite un algoritmo.

- **Discutere i vantaggi e limiti dell’implementazione dei thread nello spazio utente.**
	Come vantaggi abbiamo che può avvenire uno scheduling a livello utente, inoltre questa implementazione è "portabile" in quanto stiamo implementando dei thread virtuali i quali non richiedono hardware specifico (si possono eseguire più thread anche in macchine che a livello hardware non potrebbero), inoltre si eviterebbero context switch grazie alla sincronizzazione a livello utente.
	Come grande svantaggio abbiamo che se un thread è in attesa di I/O, l'intero contesto di esecuzione va in blocco e poi non può essere schedulato da più core sempre perchè ha un unico contesto di esecuzione.

- **Uno scheduler round-robin mantiene un elenco dei i processi eseguibili, dove ogni processo viene elencato una sola volta. Che cosa accadrebbe se un processo fosse elencato due volte? Indicare, in caso affermativo, una possibile motivazione, in caso negativo perché.**
	Se fosse elencato più volte significherebbe che sarebbe eseguito per più tempo rispetto agli altri processi, il che non è quello che promette questo tipo di politica, una possibile motivazione sarebbe appunto quella di dare più priorità ad un processo, ma allora staremo parlando di un altro algoritmo di scheduling non del RR.

- **Specificare come si può determinare quanto un processo è CPU-bound o I/O-bound analizzando il suo codice. È possibile determinarlo durante l’esecuzione?**
	Dal codice si può vedere quante richieste di input esegue se ne fa tante allora è I/O bound, mentre in esecuzione se la maggior parte del tempo il processo è bloccato, significa che è più I/O bound rispetto che CPU bound.

- **Spiegate la relazione e influenza reciproca fra la dimensione del quanto e il tempo necessario al cambio di contesto in un algoritmo di scheduling round-robin.**
	Bisogna fare attenzione al quanto di tempo da assegnare nella politica RR, dato che un quanto di tempo lungo implica meno cambi di contesto, ma vuol dire anche che un processo tiene per più tempo la CPU impedendo ad altri processi (magari brevi) di poter finire.
	Se un quanto è troppo corto avvengono tanti context switch portando quindi un grande overhead.

- **Considerando cinque job sono in attesa di esecuzione con richieste di tempo di esecuzione previsti di 9, 6, 3, 5 e X sec. In quale ordine dovrebbero essere eseguiti per minimizzare il tempo di risposta medio? (La risposta dipende da X).**
	Dovremmo eseguirli in tempo crescente così da finire per prima i processi corti ed ottenere un tempo di risposta breve, il processo con tempo X bisognerebbe inserirlo in mezzo agli altri sempre secondo l'ordine di grandezza, ma se non se ne conosce il tempo di esecuzione è meglio metterlo alla fine in quanto potrebbe essere potenzialmente molto alto.

- **Cinque lavori batch, A, B,C, D e E, arrivano al sistema contemporaneamente, con richiesta di esecuzione rispettivamente di 10, 6, 2, 4 e 8 min, priorità (assegnate dall’esterno) rispettivamente di 3, 5, 2, 1 e 4, dove 5 è la priorità massima e assumere che tutti i job siano CPU-bound. Determinare per ognuno dei seguenti algoritmi di scheduling il tempo medio di turnaround, senza considerare l’overhead dovuto al cambio di processo. 
	a. Round-robin
	b. Scheduling a priorità (senza prelazione)
	c. First-come first-served (eseguire nell’ordine 10, 6, 2, 4, 8).
	d. Shortest job first (senza prelazione)**
	a. I tempi si sommano da quello più lungo a quello più corto: $(10+18+24+28+30)/5=22 \text{ minuti}$
	b. $(6+14+24+26+30)/5=20 \text{ minuti}$
	c. $(10+16+18+22+30)/5=19.2 \text{ minuti}$
	d. $(2+6+12+20+30)/5=14 \text{ minuti}$

- **Assumere di usare un algoritmo di scheduling con aging con a = 1/2 per stimare i tempi di esecuzione. Se i precedenti quattro tempi di esecuzione, dal più vecchio al più recente, sono 40, 20, 40 e 15 ms, qual è la prossima previsione?**
	$\frac{1}{2}\cdot 40+\frac{1}{2}\cdot 20 =30$
	$\frac{1}{2}\cdot 30+\frac{1}{2}\cdot 40 = 35$
	$\frac{1}{2}\cdot 35+\frac{1}{2}\cdot 15 = 25$
	la prossima previsione del tempo di esecuzione sarà 25 ms.

