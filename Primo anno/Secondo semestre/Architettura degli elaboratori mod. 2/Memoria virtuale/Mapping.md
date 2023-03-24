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