Ipotizzando che nessun elemento abbia la stessa chiave, questa struttura dati dinamica consente di effettuare operazioni di inserimento, ricerca e cancellazione in **tempo costante**.

Ogni elemento ha una chiave $\in U=\{0,...,w-1\}$ dove $w$ corrisponde alla cardinalità di $U$.

![[Indirizzamento diretto.svg]]
Se nella tabella è presente l'elemento $x$ con chiave $k$, allora $T[k]$ contiene un puntatore a $x$, altrimenti se un elemento della tabella non è presente nel sottoinsieme $K$ contiene $NIL$.

```
directAccessSearch(T, k)
	return T[k]

directAccessInsert(T, x)
	T[x.key] = x

directAccessDelete(T, x)
	T[x.key] = NIL
```

Nonostante le operazioni sopra elencate siano costanti, la complessità spaziale è proporzionale a $w$ (non al numero di elementi memorizzati), portando ad un **grande spreco di memoria**.

## Tabelle hash
Lo spazio può essere ridotto al numero effettivo di chiavi presenti, al posto di usare tanta memoria quanti sono gli elementi dell'universo $U$, infatti al posto di memorizzare gli elementi con chiave $k$ nella cella $k$-esima, si usa una **funzione hash** $h$ e si memorizza l'elemento nella cella $h(k)$.
$$h:U\rightarrow\{0,...,m-1\}$$
Dove $m$ è la la dimensione della tabella hash che è generalmente molto più piccola di $|U|$ (dimensione di $U$).

![[Tabella hash.svg]]

Quando un elemento da inserire è mappato in una cella già occupata, si verifica una **collisione**.
- $|U|>m$: può succedere che ci siano delle collisioni
- $|K|>m$: è presente almeno una collisione ([pigeonhole principle](https://it.wikipedia.org/wiki/Principio_dei_cassetti))

Nell'imagine di sopra, la chiave $35$ viene mappata da $h$ nella posizione $5$ dell'array, la quale però contiene di già un puntatore ad una lista di elementi, dopo l'inserimento (in testa), sarà vero che $h(35)=h(15)=h(25)=5$.

Metodi per risolvere le collisioni:
- **Concatenamento** (doubly-linked list di collisioni)
- **Indirizzamento aperto**

>[!Attention]
>La complessità della funzione di **hashing** verrà sempre considerata **costante**.