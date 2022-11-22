#### Circuito sequenziale sincrono
È composto da:
1. **Circuiti combinatori**, i quali generano:
	- I valori in output;
	- I valori da memorizzare negli elementi di memoria.
2. **Elementi di memoria clockati**:
	- Sono registri realizzati tramite flip-flop (_falling edge triggered_) che mantengono lo **stato** del circuito e possono essere letti/scritti nello stesso periodo di clock.

Abbiamo due principali tipi di circuito:
- **Mealy**: l'output dipende dall'_input_ e dallo _stato_ del circuito;
- **Moore**: l'output dipende solo dallo stato del circuito.

## Register file
La parte operativa della CPU, chiamata **datapath**, contiene oltre all'ALU, alcuni registri che memorizzano gli operandi delle istruzioni aritmetico/logiche.

Ogni registro è formato da $n$ flip-flop, dove le _word_ saranno lunghe $n$ bit.
> Una word è lunga 32 bit nel MIPS.

Più registri organizzati assieme, formano il **register file**:
- Sul MIPS contiene 32 registri (32x32=1024 flip-flop);
- Permette la lettura di 2 registri e la scrittura su 1 registro.

Nel datapath, il clock non va subito dai flip-flop, ma viene messo in AND con un segnale di controllo **write**, il quale determina se il valore D debba essere memorizzato nel registro.

#### Lettura nel register file
Per leggere abbiamo bisogno di 2 multiplexer, poi il register file ci tornerà sempre una coppia di registri.

#### Scrittura nel register file
Per leggere utilizziamo un decoder per decodificare il segnale write, il quale è in AND con l'output del decoder.
Se **write** non è affermato non sarà possibile memorizzare nel register file.

>[!Tip] lettura/scrittura nello stesso ciclo di clock
>Se un register file viene acceduto sia in lettura e scrittura durante lo stesso ciclo di clock, dato che la scrittura avviene sul fronte di discesa allora il valore ritornato dalla lettura sarà il valore memorizzato nel ciclo di clock precedente.

## Memoria principale
La dimensione del register file è piccola, per questo utilizziamo la **memoria principale (RAM)**, così possiamo caricare in memoria programmi.

Caratteristiche della RAM:
- Meno veloce dei registri ma più capiente;
- È chiamata Random Access Memory perchè i tempi di accesso sono indipendenti dall'indirizzo della cella a cui si vuole accedere.

### SRAM
È molto veloce e per la sua realizzazione vengono usati dei **latch**, con essa vengono realizzate le _cache_.

È realizzata come matrice di latch $H\times W$:
- $W$ larghezza (numero di latch per ogni cella);
- $H$ altezza (numero di celle indirizzabili);
- Indirizzo di memoria formato da $\log_2H$ bit.

==A differenza del register file, non è possibile leggere e scrivere contemporaneamente.==

==Non possiamo realizzare una _SRAM_ come un register file, in quanto servirebbero molti decoder o multiplexer nel caso avessimo un numero elevato di celle in memoria.==

Per evitarlo utilizziamo una **linea di bit condivisa**, dove il collegamento ad essa avviene tramite un **sistema di buffer a 3 strati**:
![[Triplo buffer.png|300]]
- Il buffer ha 2 ingressi (il dato ed un segnale enable) ed una uscita;
- L'uscita viene impedita se Enable non è affermato.

Per risolvere il problema del grande decoder, utilizziamo una **SRAM a due livelli**: 
- Usiamo **un decoder più piccolo** ed **una batteria di piccoli multiplexer**, in questo modo gli indirizzi vengono divisi in due parti.

### DRAM
È più capiente della SRAM, ma più lenta.
Utilizza dei condensatori per mantenere i dati in memoria, è necessario però **refreshare** i condensatori ogni $x$ ms, questo perchè i condensatori tengono i dati in memoria solo per un periodo limitato di tempo.
Il _refresh_ avviene leggendo e riscrivendo i valori appena letti.

![[DRAM.png|400]]
Come nella SRAM, anche in questo caso gli indirizzi vengono divisi in 2 parti:
- La parte **alta** dell'indirizzo (riga) ha effetto sul **decoder**;
- La parte **bassa** dell'indirizzo (colonna) ha effetto sul **multiplexer**.

## SSRAM e SDRAM
Abbiamo visto che per diminuire la complessità del decoder è opportuno suddividere gli indirizzi in 2 parti:
- parte alta per la riga;
- parte bassa per la colonna.

>Da notare che celle consecutive hanno indirizzi che differiscono solo per la parte bassa dell'indirizzo.

La **Synchronous** SRAM e DRAM permettono di aumentare la banda sfruttando questa proprietà.

È possibile specificare che vogliamo trasferire dalla memoria un **burst** di dati (sequenza di celle consecutive), la riga su cui far avvenire il _burst_ è selezionata <u>una volta per tutte</u> tramite **decoder**, poi la memoria fornirà una cella del _burst_ a ogni ciclo del clock.
Questo meccanismo **migliora la banda di trasferimento** perchè il costo del decoder viene pagato una sola volta.
