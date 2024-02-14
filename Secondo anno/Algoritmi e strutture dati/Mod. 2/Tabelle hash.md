## Tabelle ad indirizzamento diretto
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
### Concatenamento
Si avrà una lista per ogni cella, contenente gli elementi che sono associati alla stessa cella, oppure $NIL$ se non è stato mappato nessun elemento in quella cella.

```
chainedHashInsert(T, x)
	inserisce x in testa alla lista T[h(x.key)]
```
$$T(n) = O(1)$$
- Si suppone che l'elemento da inserire non sia presente nella lista, altrimenti bisognerebbe cercare se esiste prima procedere con l'inserimento, in tal caso il costo dell'operazione diventa pari al costo di ricerca.

```
chainedHashSearch(T, k)
	ricerca un elemento con chiave k nella lista T[h(k)]
```
Il tempo di esecuzione nel caso peggiore è lineare, ovvero proporzionale alla lunghezza della lista `T[h(k)]`.

```
chainedHashDelete(T, x)
	cancella x dalla lista T[h(x.key)]
```
$$T(n)=O(1)$$
È costante perchè `x` rappresenta il puntatore all'elemento da cancellare e la lista è doppiamente linkata, altrimenti sarebbe lineare.

#### Analisi hashing con concatenamento
Vogliamo stimare il tempo di esecuzione della ricerca di un elemento con chiave $k$.
Sia $T$ una tabella hash con $m$ celle, dove sono stati memorizzati $n$ elementi.

Il **caso peggiore** si verifica quando tutti gli elementi sono mappati nella stessa cella, si avrà quindi una lista di lunghezza $n$.
$$T(n)=O(n)+\underbrace{O(1)}_\text{hash}$$
Il **caso medio** dipende da come la funzione hash distribuisce mediamente le chiavi fra le $m$ celle.

**Hashing Uniforme Indipendente (H.U.I.)** ([[Distribuzioni discrete#Uniforme|distribuzione]]): qualsiasi elemento ha la stessa probabilità di essere mandato in una qualsiasi delle $m$ celle indipendentemente dalle celle in cui sono mandati gli altri elementi.
$$\forall i\in[0,...,m-1]\quad Q(i)=\frac{1}{m}$$
$Q(i)$ rappresenta la probabilità che una chiave qualsiasi finisca nella cella $i$.

>[!Attention]
>Questa è una **proprietà ideale**, in realtà è una euristica, comunque le dimostrazioni verranno eseguite tenendo conto di questa proprietà.

Il **fattore di carico** di una tabella hash con $m$ celle e $n$ elementi memorizzati è dato dal seguente rapporto:
$$\text{Fattore di carico:}\quad\alpha=\frac{n}{m}=\frac{\text{\#chiavi nella tabella}}{\#\text{celle}}$$

**Osservazione**: quando $\alpha>1$ bisogna fare attenzione che non sia troppo grande, altrimenti le prestazioni sarebbero compromesse.

Sotto ipotesi di H.U.I. $n_j$ rappresenta la lunghezza della lista $T[j]$ , il valore medio di $n_j$ è dato da:
$$\frac{n_0,...,n_{m-1}}{m}=\frac{n}{m}=\alpha$$
quindi possiamo vedere il fattore di carico $\alpha$ anche come il numero medio di elementi in una lista (nel caso di hashing con concatenamento).

In una tabella hash che usa il concatenamento, una **ricerca senza successo** richiede un tempo $\Theta(1+\alpha)$ nel caso medio.
**Intuizione**:
- Calcolo $j=h(k)\rightarrow O(1)$
- Accedo a $T[j]\rightarrow O(1)$
- Scorro la lista $T[j]\rightarrow \Theta(\alpha)$
$$\text{Ricerca senza successo:}\quad T(n)=\Theta(1+\alpha)$$

Anche una **ricerca con successo** impiegherà un tempo $\Theta(1+\alpha)$ nel caso medio.
**Intuizione**:
- Calcolo $j=h(k)\rightarrow O(1)$
- Accedo a $T[j]\rightarrow O(1)$
- Scorro la lista $T[j]$ fino a trovare $k$ $\rightarrow \text{mediamente: }\Theta(\frac{\alpha}{2})$
$$\text{Ricerca con successo:}\quad T(n)=\Theta\Big(1+\frac{\alpha}{2}\Big)=\Theta(1+\alpha)$$
>$+1$ è dovuto al fatto che $\alpha$ potrebbe essere $<1$, però il costo è comunque almeno $1$ a causa del calcolo della funzione hash.

>[!Info] Perchè viene usato $\Theta$ e non $O$?
>Mettiamo $\Theta$ nelle complessità perchè stiamo valutando il tempo nel caso medio.

**Interpretazione**: nel caso medio il costo della ricerca è $\Theta(1+\alpha)$, se $n=O(m)$, il numero di celle è proporzionale al numero di elementi da memorizzare, quindi:
$$\alpha=\frac{n}{m}=\frac{O(m)}{m}=O(1)$$
ovvero: se ci sono tante celle quante sono le chiavi, allora ogni lista avrà un solo elemento rendendo la ricerca costante.
Per mantenere le prestazioni con $n$ elevato, bisognerà riallocare una tabella più grande e copiare gli elementi attuali nella nuova tabella (overhead significativo).
