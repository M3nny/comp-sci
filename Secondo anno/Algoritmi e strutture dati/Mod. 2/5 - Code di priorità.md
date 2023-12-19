Le **code di priorità** sono una struttura dati che serve a mantenere un insieme dinamico di elementi, dove ciascuno ha un valore associato detto **chiave** (o peso).

Esistono due tipi di code di priorità:
- **Massima priorità**
- **Minima priorità**
l'obiettivo è quello di rendere immediato l'accesso all'elemento con chiave massima o minima.
#### Operazioni su code di massima priorità
`insert(S, x)`
**Post**: inserisce l'elemento $x$ nell'insieme $S$, ovvero esegue $S = S\cup\{x\}$.

`maximum(S)`
**Post**: restituisce l'elemento di $S$ con la chiave più grande.

`extract_max(S)`
**Post**: restituisce ed elimina l'elemento di $S$ con la chiave più grande.

`increase_key(S, x, k)`
**Post**: aumenta il valore della chiave $x$ al nuovo valore $k$, che si suppone sia almeno pari al valore corrente della chiave di $x$, ovvero $k\geq$ chiave di $x$.

#### Operazioni su code di minima priorità
`insert(S, x)`
**Post**: inserisce l'elemento $x$ nell'insieme $S$, ovvero esegue $S = S\cup\{x\}$.

`minimum(S)`
**Post**: restituisce l'elemento di $S$ con la chiave più piccola.

`extract_min(S)`
**Post**: restituisce ed elimina l'elemento di $S$ con la chiave più piccola.

`decrease_key(S, x, k)`
**Post**: decrementa il valore della chiave $x$ al nuovo valore $k$, che si suppone sia al massimo pari al valore corrente della chiave di $x$, ovvero $k\leq$ chiave di $x$.

## Code di massima priorità usando max-heap

#### Maximum
```
heap_maximum(Heap A)
	if A.heapSize < 1
		exception "Heap underflow"
	else
		return A[1]
```
Per la definizione di [[Heap sort|max-heap]] l'elemento più grande è in prima posizione.
**Complessità**: $\Theta(1)$.

#### Extract max
```
heap_extract_max(Heap A)
	if A.heapSize < 1
		exception "Heap underflow"
	else
		max = A[1]
		A[1] = A[A.heapSize]
		A.heapSize--
		max_heapify(A, 1)
		return max
```
Sostituisce il massimo (primo elemento) con l'ultimo, così da mantenere un albero quasi completo (dalla definizione di heap) e poi viene eseguita una `max_heapify` sulla nuova radice per ripristinare la proprietà del max-heap.
**Complessità**: $O(\log n)$ a causa di `max_heapify`.

#### Increase
```
heap_increase_key(Heap A, Node i, Elem key)
	if key < A[i]
		exception "Nuova chiave più piccola di quella corrente"
	else
		A[i] = key
		while i > 1 and A[parent(i)] < A[i]
			scambia A[i] e A[parent(i)]
			i = parent(i)
```
Dopo aver assegnato correttamente il nuovo valore, viene controllato se il padre dell'elemento modificato possiede una chiave minore del figlio, in caso affermativo scambia il padre con il figlio per mantenere la proprietà del max-heap per poi iterare, eventualmente, fino alla radice.

**Invariante**: l'array $A[i ... A.heapSize]$ soddisfa la proprietà di max-heap tranne una possibile violazione in $A[i]$ (chiave modificata) in quanto potrebbe essere più grande di suo padre $A[parent(i)]$.
**Conclusione**: il ciclo termina quando:
- $i = 1$: poichè $i$ quando è uguale a $1$ rappresenta la radice, per cui non c'è alcuna eccezione
- $A[parent(i)]\geq A[i]$: l'unica violazione potrebbe essere in $i$, ma non è possibile a causa della guardia, la proprietà del max-heap è quindi verificata

**Complessità**: $O(h)=O(\log n)$ in quanto stiamo effettuando un cammino dal nodo $i$ fino potenzialmente la radice dell'albero, il che potrebbe percorrere l'intera altezza dell'albero.

#### Insert
```
max_heap_insert(Heap A, Elem key)
	A.heapSize++
	A[A.heapSize] = -∞
	heap_increase_key(A, A.heapSize, key)
```
La dimensione dell'heap viene aumentata per accogliere il nuovo elemento, il quale viene impostato a $-\infty$, in questo modo si è sicuri che manterrà la proprietà di max-heap.
Viene poi chiamata `heap_increase_key` così da assegnare il valore corretto all'ultimo elemento e muoverlo nella posizione corretta.
>Nel codice reale è possibile inserire $key$ al posto di $-\infty$.

**Complessità**: $O(\log n)$ a causa di `heap_increase_key`.

>[!Info]
>Un heap può svolgere ciascuna operazione delle code di priorità nel tempo $O(\log n)$, dove $n$ è il numero di elementi dell'insieme dinamico.
