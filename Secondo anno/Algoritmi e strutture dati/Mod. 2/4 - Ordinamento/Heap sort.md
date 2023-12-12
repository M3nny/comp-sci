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

