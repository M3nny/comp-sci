Un albero binario è **bilanciato** se $h=O(\log n)$.
![[Albero bilanciato.svg|400]]
Tutte le operazioni che vedremo, avranno complessità $O(h)$, mentre se l'albero sarà completamente sbilanciato si avrà una complessità lineare.

## Cos'è un albero binario di ricerca
Un albero è detto tale se soddisfa la **proprietà di ricerca**:
Sia $x$ un nodo di un albero binario di ricerca.

Se $y$ è un nodo nel sottoalbero sinistro di $x$, allora $y.Key\leq x.Key$, mentre se $y$ fa parte del sottoalbero destro di $x$ allora $y.Key\geq x.Key$.
![[Alberi binari di ricerca.svg]]
La proprietà di ricerca consente di **elencare in ordine crescente** (in senso lato) le chiavi di questo tipo di albero eseguendo una visita in ordine simmetrico (in-order).

## Operazioni su alberi di ricerca
Un nodo $x$, in questo tipo di albero, ha i seguenti campi:
- $x.Key$
- $x.p$ (puntatore al padre)
- $x.left$, $x.right$
L'albero inoltre possiede $T.root$ per conservare il puntatore alla radice dell'albero.

#### Ricerca
`Tree_search(Node x, Elem k) -> Node or Nil`
- Post: restituisce un nodo che contiene la chiave $K$ (se esiste)

```
Tree_search(Node x, Elem k)
	if x == NIL or x.Key == k
		return x
	else
		if k < x.Key
			return Tree_search(x.left, k)
		else
			return Tree_search(x.right, k)
```

```
Tree_search_iter(Node x, Elem k)
	while x != NIL and x.Key != k
		if k < x.key
			x = x.left
		else
			x = x.right
	return x
```

**Correttezza**: possiamo tagliare lo spazio di ricerca perchè la _proprietà di ricerca_, assicura che nel sottoalbero destro si trovano solo chiavi più grandi di $x.Key$, discorso analogo per il sottoalbero sinistro, quale conterrà solo chiavi più piccole di $x.Key$

**Complessità**:
I nodi incontrati durante la ricorsione formano un cammino verso il basso a partire dalla radice dell'albero, quindi il tempo di esecuzione sarà _al massimo_ l'altezza di quest'ultimo.
$$T(n)=O(h)$$
#### Minimo e massimo
`Tree_min/max(Node x) -> Node`
- Pre: $x\in T$
- Post: ritorna il nodo con chiave più piccola/grande nel sottoalbero di radice $x$

```
Tree_min(Node x)
	while x.left != NIL
		x = x.left
	return x
```

```
Tree_max(Node x)
	while x.right != NILL
		x = x.right
	return x
```
**Correttezza**: se un nodo $x$ non ha sottoalbero sinistro, vuol dire che è lui stesso la chiave minima, in quanto il sottoalbero destro conterrà solo valori uguali o maggiori a $x.Key$, discorso analogo nel caso in cui non abbia sottoalbero destro, dato che nel sottoalbero sinistro ci sono solo valori uguali o minori di $x.Key$, allora sarà proprio quest'ultimo il massimo.

**Complessità**: la sequenza dei nodi visitati forma una cammino che scende dalla radice, e che può avere lunghezza massima $h$.
$$T(n)=O(h)$$
#### Predecessore e successore
`Tree_successor/predecessor(Node x) -> Node`
- Pre: $x\in T$

Dato un nodo $x$ si vuole determinare il predecessore e  successore in una visita simmetrica.

Se tutte le chiavi sono distinte, il **successore** di $x$ è il nodo che contiene la più piccola chiave maggiore di $x.Key$.

![[Sucessore.svg|500]]

1. Se $x$ ha un figlio destro, il successore è il minimo del sottoalbero destro di $x$
2. Se $x$ non ha figli destri, il successore, se esiste (non esiste se $x$ è il massimo), è l'antenato più prossimo di $x$ il cui figlio sinistro è anche antenato di $x$. Per trovarlo si risale da $x$ verso la radice fino ad incontrare la prima svolta a destra.

```
Tree_successor(Node x)
	if x.right != NIL
		return Tree_min(x.right) // O(h)
	else
		y = x.p
		while y != NIL and x == y.right // O(h)
			x = y
			y = y.p
		return y
```
**Complessità**: in entrambi i casi viene fatto un cammino che visita al massimo un numero di elementi pari all'altezza dell'albero, nel caso dell'`if` da $x$ alla chiave minima, nel caso dell'`else` da $x$ alla radice.
$$T(n)=O(h)$$

Per trovare il **predecessore** le operazioni saranno invertite, ma si procede analogamente.
1. Se $x$ ha un figlio sinistro, il predecessore è il massimo del sottoalbero sinistro di $x$
2. Se $x$ non ha figli sinistri, il predecessore, se esiste (non esiste se $x$ è il minimo), è l'antenato più prossimo di $x$ il cui figlio destro è anche antenato di $x$. Per trovarlo si risale da $x$ verso la radice fino ad incontrare la prima svolta a sinistra.

```
Tree_predecessor(Node x)
	if x.left != NIL
		return Tree_max(x.left) // O(h)
	else
		y = x.p
		while y != NIL and x == y.left // O(h)
			x = y
			y = y.p
		return y
```
**Complessità**: analoga al successore, ovvero $O(h)$

#### Inserimento e cancellazione
`Tree_insert(Tree T, Node z)`
- Post: inserisce il nodo $z$ (già inizializzato) in $T$ mantenendo la proprietà di ricerca

```
Tree_insert(Tree T, Node z)
	y = NIL // padre di z
	x = T.root
	while x != NIL
		y = x
		if z.Key < x.Key
			x = x.left
		else
			x = x.right
	z.p = y // x sarà NIL alla fine del while
	if y == NIL // albero vuoto
		T.root = z
	else
		if z.Key < y.Key
			y.left = z
		else
			y.right = z
```
**Complessità**: il `while` verrà eseguito al massimo $h$ volte ($h$ = altezza dell'albero), mentre le altre operazioni sono costanti.
$$T(n)=O(h)$$
