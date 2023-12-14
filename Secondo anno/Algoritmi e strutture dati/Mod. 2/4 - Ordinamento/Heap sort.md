Un **heap** è un albero binario quasi completo, ovvero, tutti i livelli sono completamente riempiti, tranne eventualmente l'ultimo livello, in cui tutte le foglie sono addossate a sinistra.

Un heap può essere memorizzato in un array $A$ con due attributi:
- $A.length$: numero di elementi nell'array
- $A.heapSize$: numero di elementi dell'heap memorizzati in $A$
>$A.heapSize\leq A.length$

La **radice** dell'heap è rappresentata dal **primo** elemento dell'array, mentre se $i$ è l'indice di un nodo, possiamo trovare i suoi nodi collegati tramite:
```
parent(Node i) -> Node
	return i/2

left(Node i) -> Node
	return 2 * i

right(Node i) -> Node
	return (2 * i) + 1
```

Esistono due tipi di heap:
- **Max-heap**: per ogni nodo diverso dalla radice, $A[parent(i)]\geq A[i]$
![[Max-heap.svg]]
- **Min-heap**: per ogni nodo diverso dalla radice, $A[parent(i)]\leq A[i]$

### Proprietà degli heap
**Lemma 1**: l'altezza di un heap di $n$ elementi è data da$\lfloor\log n\rfloor$.
- **Dimostrazione**: un heap è una albero quasi completo, se $h$ è la sua altezza, allora $n\leq\text{n° nodi albero completo}$, ovvero $\sum\limits_{i=0}^h2^i=\frac{2^{h+1}-1}{2-1}=2^{h+1}-1$, mentre l'albero con una sola foglia, ovvero $\sum\limits_{i=0}^{h-1}2^i+1=\frac{2^{h-1+1}}{2-1}+1=2^h$ ha un numero di nodi $\leq n$, dunque:
$$2^h\leq n\leq 2^{h+1}-1\implies2^h\leq n<2^{h+1}$$
dato che $h=\lfloor\log n\rfloor$, si ottiene:
$$n\leq\log n<h+1$$
**Lemma 2**: nell'array rappresentante l'heap di $n$ elementi, le foglie sono i nodi con indici $\lfloor\frac{n}{2}\rfloor+1,\lfloor\frac{n}{2}\rfloor+2,...,n$.

**Lemma 3**: ci sono al massimo $\left\lceil\frac{n}{2^{h+1}}\right\rceil$ nodi di altezza $h$ in una qualsiasi heap di $n$ elementi.

### Operazioni
`max_heapify(Heap A, Node i)`
- **Pre**: gli alberi binari con radice in $left(i)$ e $right(i)$ sono max-heap
- **Post**: l'albero radicato in $i$ è un max-heap
```
max_heapify(Heap A, Node i)
	l = left(i)
	r = right(i)
	if l <= A.heapSize and A[l] > A[i]
		max = l
	else
		max = i
	if r <= A.heapSize and A[r] > A[max]
		max = r
	if i != max
		scambia A[i] e A[max]
		max_heapify(A, max) // controllo per propagazione dell'eccezione
```

Questa funzione serve a verificare, e nel caso, correggere il nodo $i$ in modo tale che rispecchi le proprietà del max-heap, questo avviene scambiando il nodo $i$ con il suo nodo figlio con valore più alto, per poi andare a controllare se il nodo scambiato non causi a sua volta una eccezione.

**Complessità**: il tempo di esecuzione è $O(h)$, ma se viene chiamato sulla radice, dato che $h=\lfloor\log n\rfloor$, il suo tempo di esecuzione complessivo sarà $O(\log n)$.

Con un vettore qualsiasi è possibile creare un max-heap chiamando più volte `max_heapify`:
```
build_max_heap(Array A)
	A.heapSize = A.length
	for i = A.length/2 down to 1 // n/2 iterazioni
		max_heapify(A, i)
```
![[build_max_heap.svg]]
Il for parte da $A.length/2$ in quanto da questo indice in poi sono presenti tutte le foglie del heap per le quali sappiamo essere già verificata la proprietà di max-heap.

**Invariante**: ogni nodo da $i+1$ a $n$ è radice di un max-heap con $n=A.length$.
- **Conclusione**: quando il ciclo termina, $i=0$, ogni nodo $1, ..., n$ quindi è radice di un max-heap, in particolare anche il nodo $1$ è ora una radice di un max-heap, infatti rappresenta la radice dell'albero.

**Complessità**: sicuramente la complessità avrà limite superiore $O(n\log n)$ in quanto `max_heapify` viene chiamata $n$ volte, il limite stretto però, tenendo conto che l'albero ha molte foglie e `max_heapify` è $O(h)$ è il seguente:
$$\sum_{h=0}^{\lfloor\log n\rfloor} \underbrace{
\left\lceil\frac{n}{2^{h+1}}\right\rceil}_{\text{max n° di nodi con altezza h}} \cdot O(h)=O\left(n\sum_{h=0}^{\lfloor\log n\rfloor}\frac{h}{2^h}\right)$$
sfruttando una serie nota:
$$\sum_{h=0}^\infty hx^h=\frac{x}{(1-x)^2}\quad\text{per |x|<1}$$
ponendo $x=\frac{1}{2}$:
$$\sum_{n=0}^\infty\frac{h}{2^h}=\frac{1}{2}\cdot\frac{1}{1-\frac{1}{2}}=\frac{1}{2}\cdot 4=2$$
quindi si ottiene:
$$O\left(n\sum_{h=0}^{\lfloor\log n\rfloor}\frac{h}{2^h}\right)=O\left(n\sum_{h=0}^\infty \frac{h}{2^h}\right)=O(2n)=O(n)$$
il tempo di `build_max_heap` è quindi $O(n)$.

### Ordinamento
```
heapsort(array A)
	build_max_heap(A)
	for i = A.length down to 2
		scambia A[1] e A[i]
		A.heapSize--
		max_heapify(A, 1)
```

Dopo aver trasformato $A$ in un max-heap, partendo dalla fine si scambiano i valori $i$ con la radice dell'albero verificando poi se la nuova radice (in posizione $1$) rispetta le proprietà del max-heap (con dimensione ridotta), in questo modo ad ogni iterazione l'elemento più grande in $heapSize$ viene addossato alla fine dell'array e rimarrà intoccato fino alla fine dell'algoritmo.
Il for viene eseguito fino a $2$ in quanto l'ultimo elemento rimanente è obbligatoriamente il più piccolo di tutti gli altri.

**Invariante del ciclo**: il sottoarray $A[1 ... i]$ è un max-heap che contiene gli $i$ elementi più piccoli di $A[1 ... n]$ e il sottoarray $A[i+1 ... n]$ contiene gli $n-1$ elementi più grandi di $A[1 ... n]$ <u>ordinati</u>.
- **Conclusione**: quando il ciclo termina $i=1$, il sottoarray $A[1 ... 1]$ è un max-heap che contiene l'elemento più piccolo di $A[1 ... n]$, mentre $A[2 ... n]$ contiene gli $n-1$ elementi più grandi di $A[1 ... n]$ <u>ordinati</u>, nè risulta quindi che l'intero array è ordinato.
