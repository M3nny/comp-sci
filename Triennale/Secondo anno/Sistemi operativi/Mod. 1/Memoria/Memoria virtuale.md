Finora abbiamo visto **indirizzi fisici** ($R$) i quali rappresentano indirizzi nella RAM, ci riferiremo a **indirizzi virtuali** ($V$) (i quali sono più numerosi rispetto a quelli _fisici_), come indirizzi riferiti a processi.

La [[Mapping|memoria virtuale]] crea l'<u>illusione di avere più memoria a disposizione</u>, grazie alla **MMU (Memory Management Unit)**, la quale è una componente hardware dedicata alla **traduzione** di $R$ in $V$ scambiando porzioni di $V$ tra memoria principale, cache e memoria secondaria.

Il **mapping dei blocchi** indica quali regioni dello spazio di indirizzamento virtuale di un processo sono attualmente in RAM e dove si trovano.
>Gli indirizzi virtuali contigui visti dal programmatore potrebbero non corrispondere a indirizzi reali contigui.

## Mapping dei blocchi
La **traduzione di un blocco (virtuale)** di grandezza variabile ad un blocco fisico avviene come segue: 
un indirizzo virtuale sarà dato da $v=(b,d)$ dove $b$ è il numero del blocco e $d$ lo spostamento.
Considerando che ogni processo ha la sua **tabella della mappa dei blocchi** (memorizzata in RAM) che comincia dall'indirizzo reale $a$, la **traduzione** da un indirizzo virtuale a reale avviene nei seguenti passaggi:
![[Mapping dei blocchi.png|600]]
1. Si aggiunge ad $a$ il numero del blocco $b$ per individuare la riga nella tabella di mappa dei blocchi del processo
2. Ora abbiamo $b'$ il quale indica l'inizio del blocco $b$ in memoria principale
3. Si aggiunge lo spostamento (offset) $d$ a $b'$ per formare l'indirizzo reale $r$
## Paginazione
Vediamo **come disporre in memoria i page frame**.
A differenza dei blocchi visti precedentemente, le **pagine hanno dimensione fissa**.
In questo caso l'indirizzo virtuale è $v=(p,d)$ dove $p$ è il numero di pagina in memoria virtuale.
Un **page frame** è un blocco di RAM destinato a contenere pagine, inizia ad un indirizzo di memoria che è un multiplo della dimensione fissa della pagina ($p_s$).

La traduzione avviene nei seguenti passaggi:
![[Paginazione.png|500]]
1. Da $p$ ricavo attraverso una **tabella delle pagine** $p'$ (page frame)
2. Faccio $p'\cdot p_s + d$ per ottenere l'indirizzo reale di interesse

La **tabella delle pagine** quindi data una **pagina virtuale** restituisce un **page frame**.
>Ha tante righe quante sono le pagine virtuali del processo.

Ogni riga (**PTE: Page Table Entry**) contiene:
- **Bit di residenza** $r$: indica se l'indirizzo è presente in RAM o no
- **Page frame** e **indirizzo di memoria secondaria**
![[Page table entry.svg]]
Se $r=0$ il SO dovrà caricare in RAM l'indirizzo da $s$ (nel mentre blocca il processo e fa altro).

### Mapping diretto
Questa tecnica è simile al [[Memoria virtuale#Mapping dei blocchi|mapping dei blocchi]] di dimensione variabile, usando sempre la forma precedente di indirizzo virtuale si prosegue nel seguente modo:
![[Mapping diretto.png|500]]
1. Il **DAT (Dynamic Address Translation)** aggiunge l'indirizzo base della tabella delle pagine del processo $b$ a $p$
2. $b+p$ forma l'indirizzo di memoria principale della _PTE_ per la pagina $p$
3. Nella riga appena trovata nella _PTE_ troviamo $p'$ il quale è il page frame corrispondente, al quale viene concatenato lo spostamento $d$ per formare l'indirizzo reale

### Mapping associativo
Spesso non è possibile tenere in cache una tabella delle pagine grande, per questo **si posiziona la tabella delle pagine in una [[Cache associativa|cache associativa]]**, dove ogni posizione è cercata **contemporaneamente**.
![[Mapping associativo.png|500]]
1. $p$ è cercato in tutte le righe della cache associativa contemporaneamente
2. Nella riga appena trovata si estende $p'$ con l'offset $d$ per formare l'indirizzo reale

### Mapping diretto/associativo
Cerchiamo un **compromesso fra costo e prestazioni**.
Le _PTE_ sono prevalentemente nelle tabelle in _RAM_, però quelle più utilizzate di recente si trovano nella [[Mapping#Translation Lookaside Buffer|TLB]], che è una _cache associativa_ controllabile in parte dalla _MMU_ ed in parte dal SO.
![[Mapping diretto_associativo.png|600]]

1. Si prova l'approccio _associativo_ usando la TLB
2. Se $p$ non è stato trovato all'interno della TLB si procede con l'approccio diretto, usando quindi il meccanismo DAT

### Tabelle di pagine multilivello
Per evitare sprechi di memoria **teniamo in RAM solo le pagine usate** al momento.

In particolare <u>la traduzione vera e propria viene effettuata nella tabella di gerarchia più bassa</u>, mentre nelle tabelle di livello più alto teniamo i puntatori verso le altre tabelle di livello inferiore, **memorizzando così in RAM solo l'ultima tabella**.
![[Pagine multilivello.png|600]]
Il procedimento per la traduzione è lo stesso del _mapping diretto_ a differenza che si passa per più page table.
In questo caso $v=(p,t,d)$ dove $p$ è l'indice delle pagine di primo livello, $t$ l'indice delle pagine di secondo livello dal quale troveremo poi $p'$ al quale verrà aggiunto l'offset $d$.
Con $n$ livelli, l'indirizzo è dato da $v=(x_1,...,x_n, d)$.

### Tabella inversa delle pagine
La tabella **inversa** mappa un **indirizzo reale ad un indirizzo virtuale**, in questo modo la tabella avrà tante PTE quante le pagine fisiche in memoria (costante) ed inoltre sarà una sola per tutti i processi.
![[Tabella inversa delle pagine.png|600]]
Sebbene sono gli indirizzi fisici ad essere mappati in virtuali con questo metodo, la traduzione avviene comunque da virtuale a fisico.
1. Si esegue l'hashing di $p$ 
2. **Se non avviene una collisione** nell'hashing, si aggiunge a $p'$ (determinato dall'hashing) l'offset per ricavare l'indirizzo reale
3. **Se è avvenuta una collisione** si esegue il chaining, ovvero viene creata una lista di tutte le PTE che hanno lo stesso risultato di hashing uguale e si scorre finchè non viene trovato il frame number $p'$ cercato, distinto da altri valori presenti in ogni elemento della lista tra cui il PID (che è appunto presente in ogni PTE)

Dato che per la sua natura non si può ingrandire la tabella inversa delle pagine viene usata la **Hash Anchor Table** la quale è una tabella intermedia da cui si passa prima di andare alla inverted page table.
L'HAT solitamente è più grande della IPT per aumentare il range di valori possibili dati dall'hashing.

---
## Strategie di gestione della memoria
In un sistema multiprogrammato, condividere la memoria migliora la performance in quanto non ci sono dati duplicati per nulla, sempre se la pagina è condivisibile.
Un esempio è la tecnica **copy-on-write** effettuata dal `fork()` in linux.

### Strategie di fetch
Determina **quando caricare** le pagine o segmenti dalla memoria secondaria alla RAM.
- **A richiesta**: viene effettuato il fetch quando se ne ha bisogno (ovviamente si dovrà aspettare per ogni richiesta il tempo di trasferimento in RAM)
- **A previsione (prefetching)**: sfruttando la [[Tipologie di memoria#Principio di località|località spaziale e temporale]] si decide quanta memoria pre-allocare e quante pagine pre-caricare ogni volta e con quale politica, in modo che l'overhead non sia troppo alto
### Strategie di sostituzione
Determina **chi sostituire** in RAM quando la memoria è piena.
Si usa un **dirty bit** che è pari a $1$ se la pagina è stata modificata, $0$ altrimenti.
Esiste una tecnica di **flush** per scrivere sul disco le pagine modificate (come un _write-through_ periodico).

Per evitare i **page fault** usiamo le seguenti strategie di sostituzione:
- **Random**:
	sostituisce una pagina <u>scelta a caso</u>

- **FIFO**:
	sostituisce la pagina che è <u>più vecchia</u> (potrebbe essere molto usata comunque).

- **Least Recently Used (LRU)**:
	sostituisce la pagina che <u>non viene riferita da più tempo</u>.

- **Not Frequently Used (NFU)**:
	sostituisce la pagina che <u>non è stata recentemente riferita tramite dei contatori</u> di riferimenti recenti (se sono state tutte riferite, si sostituisce una pagina che non è stata modificata), periodicamente i riferimenti si possono resettare.

- **Not Recently Used (NRU)**:
	<u>approssima la NFU, usando i bit di riferimento e modifica</u>, cerca di sostituire prima una pagina non riferita e se non ne trova una, ne sostituisce una non modificata, periodicamente si possono azzerare i bit di riferimento.

- **Second chance**:
	è una variante FIFO che <u>esamina il bit di riferimento della pagina più vecchia, se è</u> $0$ <u>la sostituisce, altrimenti lo azzera e sposta la pagina in coda FIFO come nuovo arrivo</u>.

- **A orologio**:
	è una variante FIFO, con implementazione <u>simile a Second chance, solo che al posto di usare una lista lineare, ne usa una circolare</u>, dove c'è una lancetta (puntatore) che punta alla pagina più vecchia, quando si dovrà sostituire, se il suo bit di riferimento è $0$ la sostituisce, altrimenti lo azzera e la lancetta va al prossimo elemento.

- **Far**:
	viene costruito in grafo dove, i nodi sono le pagine e gli archi i riferimenti ad esse, <u>viene sostituita la pagina non referenziata più lontana da qualsiasi pagina riferita</u>.

#### Modello working set
Per eseguire un programma in modo efficiente, bisogna tenere in memoria principale le sue pagine più usate, altrimenti si accederebbe spesso alla memoria secondaria (thrashing).

Per fare ciò, si tiene in memoria un range di pagine referenziate negli ultimi secondi **sfruttando il principio di località**.
>La dimensione del working set aumenta con la dimensione del processo.

Un processo **può avere più working set**, quando smette di utilizzarne uno, quest'ultimo viene mantenuto temporaneamente in memoria, e <u>se bisogna sostituire delle pagine, verranno sostituite delle pagine che non fanno parte dei working set</u> del processo in esecuzione, tenendo a mente questo, vediamo altri metodi di sostituzione:

- **Clock e Working Set (WSClock)**:
	oltre ad avere una "seconda chance", in [questo algoritmo](https://cs.winona.edu/Francioni/cs405/wsclock.html), se il frame non è stato referenziato dall'ultima ispezione, ha una "terza chance" prima di essere rimosso, questo meccanismo è implementato controllando se il frame che si sta ispezionando fa parte dell'attuale working set, <u>una pagina viene sostituita solo se non è stata referenziata dall'ultima ispezione ed il tempo virtuale attuale è maggiore di quello dell'ultima ispezione del frame ispezionato</u>.

- **Page Fault Frequency (PFF)**:
	<u>basandosi sulla frequenza di page fault</u> del processo in questione ed il tempo trascorso tra i page fault (_interfault_), modifica il numero di pagine del working set in memoria, ovvero se fa tanti page fault, allora dovrà allargare il range del working set.

Le **pagine inattive**, tuttavia, possono essere **sostituite volontariamente** dal processo che non ne ha più bisogno (senza dover aspettare l'algoritmo di sostituzione), questa strategia può essere implementata nel compilatore e nel sistema operativo.

La dimensione della pagina, inoltre, può variare tra vari sistemi operativi:
- **Piccola**:
	- Può ridurre la memoria per contenere un working set
	- Maggior memoria per altri processi
	- Tabella delle pagine più grande
- **Grande**:
	- Ogni riga della TLB mappa una regione più ampia della memoria
	- Riduce il numero di operazioni per caricare un working set in memoria

#### Sostituzioni globali
Sono strategie applicate a tutti i processi, quindi ignorano le caratteristiche individuali di comportamento del processo.

- **Global LRU (gLRU)**:
	sostituisce la pagina che <u>non viene riferita da più tempo in tutto il sistema</u>.

- **SEQ**: 
	usa la <u>gLRU finchè non avvengono page fault in pagine contigue</u>, allora lì utilizza la MRU (Most Recently Used) che rimuove la pagina più usata di recente, questo per interrompere i page fault, considerando che verrà ricaricata a breve.

---
## Segmentazione
Un segmento è un **concetto logico**, non fisico (come le pagine), inoltre possono non essere della stessa dimensione e/o adiacenti.

>La traduzione dell'indirizzo con mapping diretto è analoga al [[Memoria virtuale#Mapping dei blocchi|mapping dei blocchi]], con l'unica differenza che al posto del block number si ha il segment number.

Ogni riga nella mappa dei segmenti contiene:
- $s$ inizia all'indirizzo $s'$ in memoria reale
- **Bit di residenza**
- **Lunghezza**: usata per evitare che un processo riferisca al di fuori del segmento
- **Bit di protezione**: controlla se il tipo di operazione è ammessa, altrimenti genera un'eccezione, i bit di protezione sono: R(read)-W(write)-E(execute)-A(append)

Durante un riferimento possono avvenire le seguenti eccezioni:
- **Missing segment fault**: il segmento non è in memoria
- **Overflow segment exception**: se l'offset supera la lunghezza del segmento
- **Segment protection exception**: se non è consentita l'operazione (R-W-E-A)

La **condivisione** con i segmenti può causare meno overhead rispetto a quella in un sistema con paginazione pura e con mapping diretto.

>[!Tip] Paginazione vs Segmentazione
>I sistemi con paginazione sono nati per avere un grande spazio di indirizzamento lineare senza dover comprare altra memoria.
>
>I sistemi con segmentazione permettono ai programmi ed i dati di essere suddivisi in spazi di indirizzamento logici indipendenti e per migliorare la condivisione e protezione 

## Paginazione + Segmentazione
Per sfruttare i vantaggi delle due tecniche: i segmenti possono occupare più pagine, e le pagine del segmento possono non essere in RAM contemporaneamente.

L'indirizzo virtuale viene implementato tramite una **tripla ordinata** formata dal numero del segmento, numero della pagina all'interno del segmento e displacement all'interno della pagina:
$$v=(s,p,d)$$
considerando la TLB contenuta in memoria associativa, la traduzione avviene come segue:
![[Mapping combinato.png|600]]
1. Si cerca in TLB la pagina $(s,p)$, se viene trovata, si concatena il page frame $p'$ a $d$ formando l'indirizzo reale
2. Se non viene trovata la pagina in TLB, il DAT aggiunge l'indirizzo base $b$ al numero del segmento $s$
3. $b+s$ forma l'indirizzo della riga della tabella dei segmenti, da quest'ultima ricaviamo l'indirizzo della tabella delle pagine $s'$
4. Il numero di pagina $p$ è aggiunto a $s'$ per individuare la PTE per la pagina $p$, dalla quale ricaviamo il numero di page frame $p'$
5. Si concatena $p'$ con lo spostamento $d$ per formare l'indirizzo reale

La **condivisione** in questo tipo di sistema avviene quando ogni processo ha una riga della tabella di mappa dei segmenti che punta alla stessa tabella delle pagine.

>Otteniamo una condivisione facilitata dalla paginazione ed un controllo degli accessi come nella segmentazione.