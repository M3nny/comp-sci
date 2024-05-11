L'algoritmo di **Prim** a differenza di quello di [[Kruskal]] non usa tanti insiemi sparpagliati per poi unirli, ma fa crescere un albero, in particolare il nodo da cui si parte (il quale sarà la **radice** dell'albero) sarà il **predecessore** di tutti gli altri.

La struttura implicita di **predecessori** sarà un albero vero e proprio dove ogni vertice punta al suo padre, in questo modo sarà facile ricostruire il $MST$.
>Viene creato un albero radicato.

Per ogni vertice vengono mantenute due informazioni nell'algoritmo:
1. $Key[u]$: elemento della _coda di priorità_ (intero)
2. $\pi[u]$: predecessore (puntatore)

Viene usata una **coda con priorità** $Q\subseteq V[G]$ la quale implementata tramite **heap binario** e contiene i **vertici da estrarre**.
- $V\setminus Q$: vertici già estratti
- $Q$: vertici da estrarre
>Ad ogni step abbiamo un **taglio** del grafo.

$Key[u]$ rappresenta il **peso minore** tra tutti gli archi che attraversano il taglio e sono incidenti a quel vertice in particolare, se non c'è un arco incidente a quel vertice che attraversa il taglio, si avrà $Key[u]= \infty$.

Così facendo il **più piccolo valore nella coda di priorità** rappresenterà il **peso dell'arco leggero** che attraversa il taglio.

$\pi[u]$ ovvero il **predecessore**, è dato dal vertice collegato al nodo $u$ tramite l'arco con peso minore che attraversa il taglio ed è incidente a $u$, se non c'è un arco incidente a $u$, si avrà $\pi[u]=\text{NIL}$.

![[Exec Prim.svg|700]]

L'algoritmo estrae il nodo con chiave minore e poi aggiorna i valori delle strutture dati con il nuovo taglio.

Riassumendo:
1. **Inizializzazione**:
	- $Q=V[G]$
	- Ogni $Key[u]$ diversa dalla radice sarà $\infty$
	- $Key[r]=0$
	- Tutti i predecessori $\pi[u]$ saranno uguali a $\text{NIL}$
2. **Estrazione**: viene estratto il nodo con $Key$ minore (il peso rappresenta il peso dell'arco leggero del taglio attuale)
3. **Aggiornamento campi**: dato che il taglio è cambiato con l'estrazione del nodo, dovranno essere aggiornate le $Key$

```
Prim(G, w, r)
	Q = V[G]
	for each u in V[G]
		Key[u] = ∞
		π[u] = NIL
	Key[r] = 0
	
	while Q != ∅
		u = extractMin(Q)
		for each v in Adj[u]
			if v in Q and w(u, v) < Key[v]
				π[v] = u
				Key[v] = w(u, v)
	return A = {(v, π[v]) | v in V \ {r}}
```

**Osservazioni**: `Adj[u]` indica i vertici adiacenti al nodo estratto `u`, viene ritornato il valore:
$$\{(v,\pi[v])\space|\space v\in V\setminus Q\setminus {r}\}$$
più in particolare, in quanto $Q$ sarà vuoto:
$$\{(v,\pi[v])\space|\space v\in V\setminus {r}\}$$
perchè questo è il modo per ritornare gli archi che formano l'MST ad ogni passo (come $A$ nell'algoritmo di [[Kruskal]]), alla fine lo ritorniamo nella sua forma senza $Q$ in quanto esso sarà vuoto.

L'algoritmo è **corretto** per il [[Minimum Spanning Tree#Teorema fondamentale degli MST|teorema fondamentale degli MST]], in quanto prendiamo sempre un arco leggero.

**Complessità** (indicando il numero di nodi con $n$ e di archi $m$):
l'inizializzazione ha costo $n$, il `while` viene eseguito $n$ volte, però il numero di volte che viene eseguito il `for each` dipende dall'iterazione corrente, il `for each` infatti esso viene eseguito per ogni nodo $u$: $\deg(u)$ volte, per un totale di $\sum\limits_{i=1}^n\deg(u_i)$ iterazioni, che per il [[Grado#Lemma della stretta di mano|lemma della stretta di mano]] è pari a $2m$.
Da notare le operazioni fatte su heap binario come [[Code di priorità#Extract max|extract min]], oppure l'operazione `Key[v] = w(u, v)` che ha complessità $\log(n)$  in quanto $Key$ usa un heap binario, per cui ad ogni modifica bisogna verificare se la proprietà di heap binario vale per ogni nodo.
$$T(n,m)=\underbrace{n}_{\text{init}}+\underbrace{n\log(n)}_{\text{estrazione}}+\underbrace{m\log(n)}_{\text{aggiornamento}}=\space O(m\log(n))$$

**Esecuzione formale dell'algoritmo** (usando $a$ come radice):
![[Exec Prim 2.svg]]


| Nodo estratto | $a$          | $a$             | $b$          | $b$             | $c$          | $c$             | $d$          | $d$             | $e$          | $e$             |
| ------------- | ------------ | --------------- | ------------ | --------------- | ------------ | --------------- | ------------ | --------------- | ------------ | --------------- |
|               | $\pi$        | $Key$           | $\pi$        | $Key$           | $\pi$        | $Key$           | $\pi$        | $Key$           | $\pi$        | $Key$           |
| $a$           | $\text{NIL}$ | $\boldsymbol 0$ | $\text{NIL}$ | $\infty$        | $\text{NIL}$ | $\infty$        | $\text{NIL}$ | $\infty$        | $\text{NIL}$ | $\infty$        |
| $e$           | $\text{NIL}$ | $0$             | $a$          | $5$             | $\text{NIL}$ | $\infty$        | $a$          | $2$             | $a$          | $\boldsymbol 1$ |
| $d$           | $\text{NIL}$ | $0$             | $a$          | $5$             | $e$          | $3$             | $a$          | $\boldsymbol 2$ | $a$          | $1$             |
| $c$           | $\text{NIL}$ | $0$             | $a$          | $5$             | $e$          | $\boldsymbol 3$ | $a$          | $2$             | $a$          | $1$             |
| $b$           | $\text{NIL}$ | $0$             | $a$          | $\boldsymbol 5$ | $e$          | $3$             | $a$          | $2$             | $a$          | $1$             |
| $\emptyset$   | $\text{NIL}$ | $0$             | $a$          | $5$             | $e$          | $3$             | $a$          | $2$             | $a$          | $1$             |

$$\text{Nodi estratti: }a,e,d,c,b$$
$$\text{Archi: }(e\rightarrow a), (d\rightarrow a), (c\rightarrow e), (b\rightarrow a)$$
