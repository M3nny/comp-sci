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

---
## Concatenamento
Si avrà una lista per ogni cella, contenente gli elementi che sono associati alla stessa cella, oppure $NIL$ se non è stato mappato nessun elemento in quella cella.

**Inserimento**:
```
chainedHashInsert(T, x)
	inserisce x in testa alla lista T[h(x.key)]
```
$$T(n) = O(1)$$
- Si suppone che l'elemento da inserire non sia presente nella lista, altrimenti bisognerebbe cercare se esiste prima procedere con l'inserimento, in tal caso il costo dell'operazione diventa pari al costo di ricerca.

**Ricerca**:
```
chainedHashSearch(T, k)
	ricerca un elemento con chiave k nella lista T[h(k)]
```
Il tempo di esecuzione nel caso peggiore è lineare, ovvero proporzionale alla lunghezza della lista `T[h(k)]`.

**Cancellazione**:
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

---
## Funzioni hash
Nella migliore delle ipotesi una funzione hash distribuisce le chiavi $k$ in modo uniforme ed indipendente nell'intervallo $0\leq k<1$.
$$h(k)=\lfloor k\cdot m\rfloor\quad\text{(H.U.I.)}$$
**Ipotesi**: le chiavi sono numeri naturali.
Questa ipotesi non è restrittiva in quanto ci si può riportare a numeri naturali tramite varie codifiche.

### Metodo della divisione
$$h(k)=k\text{ mod } m$$
In questo metodo il valore dell'hashing sarà dato dal resto della divisione tra la chiave e la dimensione della tabella hash.
- **Vantaggio**: facile da calcolare
- **Svantaggi**: rende la dimensione della tabella un <u>dato critico</u>

Sono da evitare alcuni valori per $m$, in particolare le potenze di $2$: se $m=2^p$, $h(k)$ rappresenta i $p$-bit meno significativi di $k$, così il valore hash dipenderà solo dagli ultimi bit, vorremmo che usasse tutti i bit della divisione, inoltre usando gli ultimi bit, essi si ripeteranno con più frequenza portando ad una distribuzione non uniforme.

Una buona scelta per $m$ è un numero primo non troppo vicino ad una potenza di $2$ o $10$.
>[!Example]
>Volendo memorizzare $2000$ elementi e prevedendo una media di $3$ collisioni, cerco un numero primo vicino a $\frac{n}{3}=\frac{2000}{3}\simeq 666.6$, scelgo arbitrariamente $701$, questo valore permette di distribuire in modo opportuno gli elementi nella tabella perchè $\frac{n}{3}\leq 701$.


### Metodo della moltiplicazione
$$h(k)=\lfloor m\cdot k\rfloor,\quad k\in[0,1[$$
L'idea è quella di trasformare $k$ in un numero $\in[0,1[$ per poi applicare la funzione hash:
1. Fisso una costante $A\in]0,1[$
2. Calcolo $k\cdot A$
3. Estraggo la parte frazionaria: $(k\cdot A)\text{ mod }1$

La funzione hash sarà quindi:
$$h(k)=\lfloor m\cdot((k\cdot A)\text{ mod }1)\rfloor$$
**Vantaggi**:
- La dimensione $m$ della tabella hash, non è un <u>valore critico</u>
- Funziona bene con tutti i valori di $A$
- L'informatico Donald Knuth ha osservato che l'algoritmo funziona bene con l'inverso del rapporto aureo: $A\simeq\frac{\sqrt{5}-1}{2}=0.618034$

#### Semplificare il calcolo
Sia $w$ la lunghezza di una [[Linguaggio macchina MIPS#Istruzioni e linguaggio macchina|word]] di memoria, assumiamo che $k$ entri in una singola word.
Scelgo un intero $q\in]0,2^w[$ e $m=2^p$, con $p\in]0,w]$.
Pongo $A=\frac{q}{2^w}<1$, il prodotto tra $k\cdot A$ diventerà:
$$k\cdot A=\frac{k\cdot q}{2^w}$$
![[Metodo della moltiplicazione semplificato.svg]]
Siamo interessati ai $p$ bit più significativi (quindi alla parte frazionaria) della word meno significativa del prodotto $k\cdot q$. (inizio della seconda word):
$$
\begin{flalign}
h(k)&=\lfloor m\cdot((k\cdot A)\text{ mod }1)\rfloor\\
&=\Big\lfloor \Big(2^p\cdot\Big(\frac{k\cdot q}{2^w}\Big)\Big)\text{ mod }1\Big\rfloor\\
&=((k\cdot q)\text{ mod }2^w)\gg(w-p)
\end{flalign}
$$
**Hashing universale (randomizzato)**: invece di avere una singola funzione hash $h$, si ha un insieme $\mathcal{H}$ di quest'ultime, all'inizio dell'esecuzione il programma ne sceglierà una casualmente.
Questo viene fatto per evitare possibili attacchi, dove, sapendo la funzione di hashing di partenza si vanno ad inserire valori che andranno mappati tutti in una singola cella, compromettendo la performance del programma.

---
## Indirizzamento aperto
Questo metodo non necessità di strutture dati ausiliarie, tutti gli elementi sono memorizzati nella tabella hash stessa, ogni cella contiene un elemento dell'insieme dinamico oppure `NIL`.

Per cercare un elemento con chiave $k$:
1. Calcolo $h(k)$ ed esamino il contenuto (**ispezione**)
2. Se la cella $h(k)$ contiene $k$ o `NIL`, la ricerca ha _successo_
3. La cella $h(k)$ potrebbe essere diversa da $k$ o `NIL`, allora calcoliamo l'indice di un'altra cella in base alla chiave $k$ ed al numero di ispezioni eseguite finora
4. Si continua la scansione della tabella finchè non si trova $k$ o `NIL` oppure ho eseguito $m$ ispezioni senza successo (_insuccesso_)

La funzione hash diventa:
$$h:U\times\underbrace{\{0,...,m-1\}}_\text{Numero di ispezione}\rightarrow\{0,...,m-1\}$$
$h(k,i)$ rappresenta la posizione della chiave $k$ dopo $i$ ispezioni fallite.

Si richiede che per ogni chiave, la sequenza di ispezioni: $<h(k,0),...,h(k,m-1)>$ sia una permutazione di $<0,...,m-1>$ in modo che ogni posizione della tabella hash possa essere considerata come possibile cella in cui inserire una nuova chiave mentre la tabella si riempie.

**Ipotesi**: per semplicità si assuma che gli elementi della tabella hash siano chiavi senza dati satellite, ovvero che contengano solo la chiave.

**Inserimento**:
- **Post**: restituisce l'indice della tabella ove ha memorizzato la chiave $k$ oppure segnala un errore se la tabella è piena
```
hashInsert(T, k)
	i = 0
	found = false
	repeat
		j = h(k, i)
		if T[j] == NIL
			T[j] = k
			found = true
		else
			i++
	until found or i == m
	if found
		return j
	else
		error "Overflow della tabella hash"
```

**Ricerca**:
- **Post**: restituisce $j$ se la cella $j$ contiene $k$, oppure restituisce `NIL` se la chiave $k$ si trova nella tabella $T$
```
hashSearch(T, k)
	i = 0
	found = false
	repeat
		j = h(k, i)
		if T[j] == k
			found = true
		else
			i++
	until found or T[j] == NIL or i== m
	if found
		return j
	else
		return NIL
```

