Il quicksort è un algoritmo basato sulla tecnica **divide et impera**.

Sia $A[p...r]$ l'array da ordinare, e inizialmente $p=1$ e $r=A.length$:
1. Partiziona l'array $A[p ... r]$ in due sottoarray $A[p ... q-1]$ e $A[q+1 ... r]$ (eventualmente vuoti) dove $q$ non è compreso in nessuno dei due, tali che ogni elemento di $A[p ... q-1]\leq A[q]\leq A[q+1 ... r]$. L'indice $q$ è risultato di questa proceduta di partizionamento, e l'elemento $A[q]$ è chiamato pivot
2. Ordina i due sottoarray $A[p ... q-1]$ e $A[q+1 ... r]$ chiamando ricorsivamente quicksort. Risolve direttamente il problema se è sufficientemente piccolo (0 o 1 elementi)
3. Non c'è un vero è proprio passaggio di combinazione dei risultati, in quanto i sottoarray sono già ordinati sul posto

```
quicksort(array A, int p, int r)
	if p < r
		q = partition(A, p, r) // ritorna pivot
		quicksort(A, p, q-1)
		quicksort(A, q+1, r)

partition(array A, int p, int r) -> int
	x = A[r]
	i = p - 1
	
	for j = p to r - 1
		if A[j] <= x
		i = i + 1
		scambia A[i] e A[j]
	
	scambia A[i+1] e A[r]
	return i + 1
```

![[Quicksort animation.gif]]
