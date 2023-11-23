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

#### Inserimento
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
#### Cancellazione
Prima di scrivere l'implementazione della funzione `Tree_delete()` dobbiamo tenere a mente la seguente **proprietà** degli alberi binari di ricerca:

Se un nodo $x$ in un albero binario di ricerca ha due figli, allora il suo successore non ha un figlio sx, ed il suo predecessore non ha un figlio dx.

**Dimostrazione**:
Sia $x$ un nodo con due figli, in una visita simmetrica, i nodi del sottoalbero sinistro vengono visitati prima di $x$, mentre quelli del sottoalbero destro vengono visitati dopo.
Quindi il predecessore di $x$ si troverà nel sottoalbero sinistro, mentre il successore nel sottoalbero destro.
Se $s$ è il successore di $x$, assumiamo per assurdo che $s$ abbia un figlio sinistro chiamato $y$. Allora $y$ viene visitato dopo $x$ perchè si trova nel sottoalbero destro, ma viene visitato prima di $s$ perchè si trova nel sottoalbero sinistro di $s$, questo è assurdo perchè $s$ non sarebbe più il successore di $x$, ma di $y$.
In modo analogo si può dimostrare che il predecessore non ha figlio destro.

Ritornando alla cancellazione, abbiamo tre casi di cancellazione di un nodo $z$:

![[Cancellazione albero binario di ricerca.svg]]

1. Se $\text{z}$ <u>non ha figli</u>, facciamo puntare suo padre $\text{z.p}$ a NIL. (e.g. $\text{z}=10$)
2. Se $\text{z}$ <u>ha solo un figlio</u>, facciamo puntare suo padre $\text{z.p}$ al figlio di $\text{z}$ (e.g. $\text{z}=18$)
3. Se $\text{z}$ <u>ha due figli</u>, facciamo in modo che il suo successore prenda il suo posto (e.g. $\text{z}=15$)

Per spostare dei sottoalberi usiamo la seguente funzione:
`Transplant(Tree T, Node u, Node v)`
- Pre: $u\in T$
- Post: sostituisce il sottoalbero con radice $u$ con il sottoalbero con radice $v$

```
Transplant(Tree T, Node u, Node v)
	if u.p == NIL
		T.root = v
	else
		if u == u.p.left  // u è figlio sx di suo padre
			u.p.left = v  // v diventa figlio sx del padre di u
		else              // u è figlio dx di suo padre
			u.p.right = v // v diventa figlio dx del padre di u
	if v != NIL
		v.p = u.p
```
**Complessità**: $O(1)$.

Vediamo ora come effettuare l'eliminazione di un nodo con la seguente funzione:
`Tree_delete(Tree T, Node z)`
- Pre: $z\in T$

```
Tree_delete(Tree T, Node z)
	if z.left == NIL
		Transplant(T, z, z.right)
	else
		if z.right == NIL
			Transplant(T, z, z.left)
		else
			y = Tree_minimum(z.right)
			if y.p != z
				Transplant(T, y, y.right)
				y.right = z.right
				z.right.p = y
			Transplant(T, z, y)
			y.left = z.left
			y.left.p = y
```
**Complessità**: $O(h)$ a causa di `Tree_minimum()`.

Il caso 1. e 2. sono gestititi nei primi due `if`, mentre nel caso $z$ abbia due figli, viene trovato il suo successore $y$ e nel caso $y$ <u>non</u> fosse figlio di $z$ viene fatta `Transplant(T, y, y.right)` ovvero viene spostato il sottoalbero destro di $y$ al posto di $y$, poi vengono sistemati i puntatori in modo tale che $z$ sia uguale a $y$ dove $y.right$ è uguale al sottoalbero destro di $z$ senza $y$ (perchè è stato trapiantato), poi ad $y$, ora che ha preso il posto di $z$ gli si aggiunge l'ex sottoalbero sinistro di $z$.

![[Cancellazione bst con due figli.svg]]
### Costruzione di alberi binari di ricerca
Le operazioni viste finora possono essere realizzata in tempo $O(h)$ in un bst di altezza $h$.
Se l'albero è bilanciato, $O(h)=O(\log n)$, altrimenti più è sbilanciato, più il tempo delle operazioni tenderà ad essere $O(n)$.

Possiamo usare il seguente algoritmo per creare un bst:
```
Arr A = [1, 2, 3, 4, 5]

buildBST(Arr A)
	t = newTree()
	for i = 1 to A.length
		u = creaNodo(A[i]) // u.Key = A[i]; u.left = u.right = nullptr;
		Tree_insert(t, u)
	return t
```
**Complessità**: essendo che l'array potrebbe avere valori tutti crescenti o tutti decrescenti ed essendo che la complessità dipende da `Tree_insert()`, avendo una potenziale altezza pari al numero di nodi (completamente sbilanciato), il tempo di esecuzione di `Tree_insert()` sarà $\Theta(n^2)$.
$$
\begin{flalign}
T(n)&=\sum_{i=0}^{n-1}(c+d\cdot i)\\
&=\sum_{i=0}^{n-1}c+\sum_{i=0}^{n-1}d\cdot i\\
&=c\cdot n+d\cdot\sum_{i=0}^{n-1}i\\
&=c\cdot n+d\left(\frac{(n-1)(n-1+1)}{2}\right)\\
&=c\cdot n+d\left(\frac{n(n-1)}{2}\right)=\Theta(n^2)
\end{flalign}
$$
Possiamo migliorare l'algoritmo partendo dal centro dell'array:
```
Arr A = [1, 2, 3, 4, 5]

buildBSTott(Arr A)
	t = newTree()
	t.root = buildBSTottAux(A, 1, A.length, NIL)
	return t

buildBSTottAux(Arr A, int inf, int sup, Node padre)
	if inf > sup
		return NIL
	else
		med = (inf + sup) / 2
		r = creaNodo(A[med])
		r.p = padre
		r.left = buildBSTottAux(A, inf, med-1, r)
		r.right = buildBSTottAux(A, med+1, sup, r)
		return r
```
- Pre: l'array in input deve essere ordinato

Sebbene i due algoritmi costruiti ricevono lo stesso array, l'albero creato è ben diverso, nel primo caso sarà completamente sbilanciato, mentre nel secondo è bilanciato con altezza $h=\Theta(\log n)$.

**Complessità**:
$$T(n)=\begin{cases}c&n=0\\2T(\frac{n}{2})+d&n>0\end{cases}$$
usando il teorema master:
- $a=2$
- $b=2$
- $f(n)=d$
- $g(n)=n^{\log_2 2}=n$
Verifichiamo di essere nel primo caso: $f(n)=O(n^{1-\epsilon})$, $\epsilon>0$
Se $\epsilon=1$ otteniamo $n^0=1$, quindi $T(n)=\Theta(n)$.
