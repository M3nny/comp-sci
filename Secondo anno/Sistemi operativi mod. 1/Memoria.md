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
	Il programma è diviso in **segmenti** allocati diverse parti della memoria, essendo più facile trovare buchi, ci possono stare più processi, il che compensa l'overhead di questa tecnica.

Usiamo dei **registri limite** (base/limite o basso/alto) per delimitare l'area di memoria accessibile da un programma, possono essere anche riallocati dinamicamente (impostati solo da istruzioni privilegiate).

Usiamo la **multiprogrammazione** (vedi [[Processi#Utilizzo della CPU|utilizzo della CPU]]) per evitare che un processo stia in attesa di I/O, bisogna quindi che più processi **risiedano** in memoria contemporaneamente.
## Multiprogrammazione a partizioni fisse
Ogni **processo attivo** riceve un blocco di **dimensioni fisse** della memoria, il che favorisce il passaggio da un processo all'altro fornendo un'illusione di **simultaneità**, a scapito però di una **maggiore richiesta di memoria** in quanto il processo potrebbe non utilizzarla tutta, oppure, ancora peggio, le partizioni fisse potrebbero essere troppo piccole per farci stare un processo.

Inizialmente se la partizione richiesta era occupata, il codice non poteva essere caricato in memoria, per questo sono nati i [[Primo anno/Secondo semestre/Architettura degli elaboratori mod. 2/Assembly/Introduzione|compilatori rilocanti]], i quali consentono l'esecuzione in qualsiasi area di memoria purchè sia grande abbastanza.
