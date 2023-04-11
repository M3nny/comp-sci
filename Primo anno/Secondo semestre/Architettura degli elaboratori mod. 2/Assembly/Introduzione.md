Possiamo tradurre in linguaggio macchina i nostri programmi in due modi.

**Interpretazione**:
	Un interprete genera ed esegue codice macchina linea per linea, questo rende il programma <u>portabile</u> ma il programma deve essere interpretato ad ogni esecuzione, rendendolo più lento di conseguenza.

**Compilazione**:
	Il compilatore <u>traduce una volta</u> il linguaggio sorgente nel linguaggio target (oggetto) che tipicamente è codice macchina, ma potrebbe essere anche assembly il quale dovrà poi passare per l'assemblatore il quale esegue una sostituzione delle istruzioni 1:1 in linguaggio macchina, successivamente potrà essere eseguito quante volte si vuole anche senza il compilatore, il programma rimane però <u>non portabile</u> su altre ISA.
	Dopo che sono stati prodotti tutti i file oggetto necessari, avviene il [[Primo anno/Secondo semestre/Architettura degli elaboratori mod. 2/Assembly/Introduzione#Linking|linking]] tra essi ed eventuali librerie esterne per produrre il file eseguibile.

### Object files
Un object file nei sistemi UNIX (formato ELF) è strutturato come segue:
1. **Header**: descrive il contenuto del file
2. **Text segment**: contiene il codice macchina prodotto dall'assemblatore
3. **Data segment**: contiene i dati globali
4. **Relocation information**: identifica istruzioni e dati che dipendono da indirizzi assoluti
5. **Symbol table**: contiene i simboli (label) locali e globali (da esportare)
6. **Debug informations**: Informazioni aggiuntive (e.g. corrispondenza tra codice ad alto livello e codice macchina).

### Linker
Il file eseguibile prodotto dal **linker** è un file oggetto dove:
- Tutti i riferimenti a funzioni esterne sono stati risolti.
- I segmenti dei file oggetto sono concatenati.
- È noto l'indirizzo di caricamento.

### Loader
Quando eseguiamo un eseguibile, il **loader** carica il programma in memoria eseguendo le seguenti operazioni:

1. Legge l'header dell'eseguibile per determinare la dimensione dei segmenti text e data
2. Crea un nuovo spazio di indirizzamento per il programma che contiene i segmenti (i quali verrano poi copiati nello spazio appena creato) ed ulteriore memoria necessaria durante l'esecuzione
3. Copia i parametri passati da riga di comando nello stack
4. Inizializza i registri
5. Salta all'indirizzo definito nell'entry-point del header
6. Il programma comincia la sua esecuzione.
