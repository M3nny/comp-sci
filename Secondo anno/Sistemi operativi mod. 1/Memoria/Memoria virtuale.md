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

In particolare <u>la traduzione vera e propria viene effettuata nella tabella di gerarchia più bassa</u>, mentre nelle tabelle di livello più alto teniamo i puntatori verso le altre tabelle di livello inferiore,**memorizzando così in RAM solo l'ultima tabella**.
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
- **Random**: sostituisce una pagina scelta a caso
- **FIFO**: sostituisce la pagina che è più vecchia (potrebbe essere molto usata comunque)
- **Least Frequently Used (LRU)**: sostituisce la pagina che non viene riferita da più tempo
- **Not Frequently Used (NFU)**: sostituisce la pagina che non è stata recentemente riferita tramite dei contatori di riferimenti recenti (se sono state tutte riferite, si sostituisce una pagina che non è stata modificata), periodicamente i riferimenti si possono resettare.