Come visto in [[Tipologie di memoria|passato]] abbiamo una gerarchia di memoria, dalla più piccola, veloce e costosa:
- **Cache**: memorizza una copia dei dati più usati per un accesso veloce
- **Principale**: memorizza solo dati e programmi necessari ai programmi in esecuzione
- **Secondaria**: memorizza dati e programmi non necessari al momento

Esistono varie **strategie** di gestione della memoria, tra cui quelle di:
- **Fetch**: decide _quando_ copiare i dati di un programma
- **Posizionamento**: decide _dove_ inserire i dati e programmi in memoria principale
- **Sostituzione**: decide _quali_ dati o programmi rimuovere dalla memoria principale per creare spazio

L'**allocazione** può essere:
- **Contigua**:
	Un programma deve essere memorizzato in un **unico** blocco di indirizzi contigui, anche se ha poco overhead, questo tipo di allocazione potrebbe non trovare un blocco contiguo grande abbastanza.
	
	Nei sistemi **mono utente** era il programmatore a dove gestire tutta la memoria, più avanti venne facilitato con sistemi come l'**IOCS** (I/O Control System).

	Con l'**overlay** è inoltre possibile imitare la _memoria virtuale_ dividendo il programma in sezioni e mettendo in memoria principale solo le sezioni attive, il che porta anche delle complicazioni come la modifica dei programmi oppure l'organizzazione degli overlay.
	
- **Non contigua**:
	Il programma è diviso in **segmenti** allocati in diverse parti della memoria, essendo più facile trovare buchi, ci possono stare più processi, il che compensa l'overhead di questa tecnica.

Usiamo dei **registri limite** (base/limite o basso/alto) per delimitare l'area di memoria accessibile da un programma, possono essere anche riallocati dinamicamente (impostati solo da istruzioni privilegiate).

Usiamo la **multiprogrammazione** (vedi [[Processi#Utilizzo della CPU|utilizzo della CPU]]) per evitare che un processo stia in attesa di I/O, bisogna quindi che più processi **risiedano** in memoria contemporaneamente.
### Multiprogrammazione a partizioni fisse
Ogni **processo attivo** riceve un blocco di **dimensioni fisse** della memoria, il che favorisce il passaggio da un processo all'altro fornendo un'illusione di **simultaneità**, a scapito però di una **maggiore richiesta di memoria** in quanto il processo potrebbe non utilizzarla tutta, oppure, ancora peggio, le partizioni fisse potrebbero essere troppo piccole per farci stare un processo.

Inizialmente se la partizione richiesta era occupata, il codice non poteva essere caricato in memoria, per questo sono nati i [[Primo anno/Secondo semestre/Architettura degli elaboratori mod. 2/Assembly/Introduzione|compilatori rilocanti]], i quali consentono l'esecuzione in qualsiasi area di memoria purchè sia grande abbastanza.

### Multiprogrammazione a partizioni variabili
Inizialmente i job vengono inseriti in **partizioni esattamente delle dimensioni necessarie**, quando un job finisce però avviene **frammentazione esterna** lasciando un buco, il quale potrebbe non essere abbastanza grande per un nuovo job.

Per contrastare la _frammentazione esterna_ si usa:
- **Coalescenza**: combina i buchi liberi adiacenti in un unico grande buco (spesso non è grande abbastanza)
- **Compattazione**: avvicina tutti gli spazi occupati, lasciando così un grande blocco di memoria libero, al costo di un **overhead significativo**.

### Multiprogrammazione con swapping di memoria
<u>Solo il processo in esecuzione è in memoria principale</u> consentendo di avere **spazio di crescita**, gli altri sono spostati temporaneamente in memoria secondaria per tenere più libera quella principale, al costo di avere <u>overhead significativi nel cambio di contesto</u>.

Una soluzione migliore è quella di mantenere in memoria più processi alla volta.

---
### Strategie di posizionamento
- **First-fit**: il processo è allocato nel <u>primo spazio libero di dimensioni sufficienti</u>, è semplice con basso overhead, però potrebbe occupare un blocco molto più grande del necessario
- **Best-fit**: il processo è allocato in un blocco che lo contiene appena, <u>lasciando la minor parte del blocco inutilizzata</u>, l'overhead sarà maggiore dato che dovrà scorrere tutti i blocchi alla ricerca del migliore
- **Worst-fit**: alloca il processo nel blocco più grande di tutti (sempre che possa contenere il processo), <u>lasciando la maggior parte del blocco inutilizzata</u>

### Gestione della memoria libera
- **Mappa di bit**: la memoria viene suddivisa in _unità di allocazione_, dove ad ognuna di esse viene assegnato un valore $0$ se è libera, $1$ se è occupata, per trovare uno spazio libero bisogna scorrere la mappa finchè non si trovano abbastanza $0$ da farci stare il processo in questione
- **Liste collegate**: si usa una lista con quattro campi, i quali indicano:
	1. Lo <u>spazio in questione è occupato oppure no</u>
	2. <u>Indirizzo di partenza</u> del blocco
	3. <u>Lunghezza</u> del blocco
	4. <u>Puntatore al prossimo elemento</u> della lista