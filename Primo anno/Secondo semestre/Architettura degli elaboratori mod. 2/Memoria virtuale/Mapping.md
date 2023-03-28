## Introduzione e motivazioni
Come la **cache** permette di accedere in modo veloce a dati acceduti di recente, allo stesso modo _la **RAM** può agire da cache per memoria di livello inferiore_ come hdd e ssd, questa tecnica è chiamata **memoria virtuale**.

Tutto questo per:
1. Condividere la RAM in modo sicuro tra più programmi in esecuzione.
2. Permettere ad un programma di usare più memoria della RAM realmente disponibile.

### Principio di funzionamento
I programmi sono compilati rispetto ad uno **spazio di indirizzamento virtuale**, per cui l'OS e la CPU dovranno tradurli in indirizzi fisici successivamente.

- I blocchi di memoria, chiamati **pagine** sono <u>mappati da indirizzi virtuali a indirizzi fisici</u>.
- La <u>CPU lavora su indirizzi virtuali</u>, dopo la traduzione <u>la memoria viene acceduta usando indirizzi fisici</u>. Questo significa che i puntatori come in C puntano ad un indirizzo virtuale.

### Vantaggi
1. **Illusione di avere più memoria fisica di quella disponibile**:
	Possono essere eseguiti contemporaneamente programmi che utilizzano più RAM di quella esistente, questo grazie alla **memoria swap** che consente di salvare i dati che normalmente risiedono nella RAM su un hdd o ssd, quando la RAM sarebbe altrimenti vuota.

2. **Protezione degli accessi**:
	Garanzia che gli spazi di indirizzamento virtuali di programmi diversi siano mappati su indirizzi fisici distinti, per evitare conflitti di memoria.

3. **Semplifica il caricamento dei programmi**:
	Un programma può essere caricato ovunque in memoria usando un suo spazio di indirizzamento virtuale, senza avere il bisogno di ricompilarlo per un'area di memoria specifica.

### Mapping
Gli _indirizzi virtuali_ e _fisici_ possiedono rispettivamente il loro **virtual page number** e **phisical page number** assieme ad un **page offset** (uguale per entrambi).

- <u>La funzione di mapping non è biunivoca</u>, ci sono più pagine virtuali di quelle fisiche.
- <u>Il numero di bit dell'offset determina la dimensione della pagina</u>:
$$\text{page offset} = \log_2(\text{page size})$$
la traduzione avviene tramite la **page table** (del programma associato ad essa) che risiede nella RAM, sarà poi il **page table register** a contenere l'indirizzo delle _page table_ e ad associare gli indirizzi virtuali a quelli fisici.

![[Mapping.png|500]]

---
### Page fault
Se una pagina non è presente in RAM e bisogna cercarla a livello inferiore, si avrà un **page fault** (analogo al cache miss), dove il **miss penalty è enorme**, quindi bisogna ridurre il più possibile i _page faults_.

1. Il mapping tra pagine virtuali e fisiche è completamente associativo
2. Viene usata la politica di rimpiazzo LRU
3. I page fault sono gestiti dall'OS.
4. Si usa solo la politica _write-back_ in quanto è molto costoso scrivere nella memoria al livello inferiore della RAM.

All'avvio di un processo vengono create sul disco le immagini delle pagine e dei dati, poi a richiesta le pagine saranno portate in memoria fisica quando avvengono dei page fault.

Oltre al **valid bit**, sono presenti anche i:
- **dirty bit** per indicare se una pagina è stata modificata e deve quindi essere ricopiata al livello inferiore quando viene rimpiazzata (write back)
- **reference bit** per vedere quanto tempo fa è stata usata la pagina (per la politica LRU).

### Translation Lookaside Buffer
Implementiamo un sistema di memoria virtuale **in hardware** per aumentare il numero di accessi alla RAM (dato che la page table può essere molto grande in RAM).

La memoria **TLB** (o _translation cache_) contiene le ultime page table riferite e la prima volta che una pagina viene riferita (e genera per forza un page fault) viene anche copiata nella TLB per velocizzare gli accessi successivi.
- La TLB **può avere vari livelli di associatività**
- La TLB **contiene solo entry valide** nella page table, se una pagina viene eliminata dalla memoria fisica, anche la relativa entry della TLB viene invaldiata.

### Integrare memoria virtuale, cache e TLB
Con questi meccanismi simil-cache, cosa fa la cache effettiva?

- **Physically addressed cache**: usa indirizzi fisici, prima di passare per la cache bisogna passare per la TLB ed in caso di TLB miss per la page table, inoltre più programmi possono usare lo stesso indirizzo virtuale (_niente aliasing_) contemporaneamente.
- **Virtually addressed cache**: usa indirizzi virtuali quindi non richiede l'accesso alla TLB (non genera TLB miss e page fault), ma esiste un possibile problema con la protezione dei dati in quanto programmi diversi potrebbero usare lo stesso indirizzo virtuale (_aliasing_).
- **Virtually indexed but physically tagged**: è un approccio ibrido dove l'INDEX della cache viene calcolato dall'indirizzo virtuale ma il TAG viene ottenuto dall'indirizzo fisico, in questo modo si evita l'_aliasing_.

### Tipologie di miss
- **Compulsory**: miss obbligatori la prima volta che dei blocchi vengono portati in memoria.
- **Capacity**: quando la cache non riesce a contenere tutti i blocchi, allora un blocco viene espulso e riammesso subito dopo.
- **Collisions**: avvengono se la cache non è completamente associativa e due blocchi sono in conflitto per una certa posizione.