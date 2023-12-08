L'insertion sort è un algoritmo basato sul **confronto** con tecnica **incrementale**, ovvero avendo $k$ elementi ordinati, vogliamo estendere questo insieme a $k+1$.
![[Insertion sample.svg]]
```
insertionSort(array A)
	for j = 2 to A.length // si parte a contare da 1
		key = A[j]
		i = j - 1
		while i > 0 and A[i] > key
			A[i+1] = A[i]
			i = i - 1
		A[i+1] = key
```
![[Insertion sort animation.gif]]
**Invariante del ciclo** (for):
Il sottoarray $A[1 ... j-1]$ è formato dagli elementi ordinati che originariamente erano in $A[1 ... j-1]$.

**Dimostrazione**:
- **Inizializzazione**: prima del ciclo il sottoarray $A[1 ... 1]$ è formato dagli elementi ordinati che erano in $A[1 ... 1]$
- **Conservazione**: dopo il for posizione correttamente l'elemento $j$ nella porzione già ordinata $A[1 ... j-1]$, formando così una porzione ordinata $A[1 ... j]$ e gli elementi che sono in tale porzione sono gli elementi originariamente in $A[1 ... j]$
- **Conclusione**: quando il ciclo termina il sottoarray degli elementi ordinati rappresenta l'intero array

>[!Ordinamento in loco]
>Un ordinamento si dice **in loco** quando un numero costante di elementi dell'array sono memorizzati fuori da quest'ultimo.

**Teorema**: l'insertion sort ordina in loco $n$ elementi eseguendo nel caso pessimo $\Theta(n^2)$ confronti.

**Dimostrazione**:
Il ciclo for viene eseguito $n-1$ volte, il numero totale di confronti è dato da:
$$\sum_{j=2}^nj-1=\sum_{k=1}^{n-1}k=\frac{(n-1)(n-1+1)}{2}=\frac{n(n-1)}{2}=\Theta(n^2)$$

| Caso migliore | Caso medio | Caso peggiore |
|:-------------:|:----------:|:-------------:|
|  $\Theta(n)$  |  $O(n^2)$  | $\Theta(n^2)$ |

**Vantaggi**:
- In loco
- Sensibile all'ordinamento: non esegue il ciclo interno se $j$ è già nel posto giusto
- Stabile: i numeri con lo stesso valore si presentano nell'array di output nello stesso modo in cui si presentano in input
**Svantaggio**:
- $\Theta(n^2)$ caso peggiore