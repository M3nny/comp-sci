Si avrà una lista per ogni cella, contenente gli elementi che sono associati alla stessa cella, oppure $NIL$ se non è stato mappato nessun elemento in quella cella.

### Inserimento
```
chainedHashInsert(T, x)
	inserisce x in testa alla lista T[h(x.key)]
```
$$T(n) = O(1)$$
- Si suppone che l'elemento da inserire non sia presente nella lista, altrimenti bisognerebbe cercare se esiste prima procedere con l'inserimento, in tal caso il costo dell'operazione diventa pari al costo di ricerca.

### Ricerca
```
chainedHashSearch(T, k)
	ricerca un elemento con chiave k nella lista T[h(k)]
```
Il tempo di esecuzione nel caso peggiore è lineare, ovvero proporzionale alla lunghezza della lista `T[h(k)]`.

### Cancellazione
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