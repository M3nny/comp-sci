Il merge sort è un algoritmo basato sulla tecnica **divide et impera**.

Sia $A[p...r]$ l'array da ordinare, e inizialmente $p=1$ e $r=A.length$:
1. Divide $A$ in due sottoarray: $A[p ... q]$ e $A[q+1 ... r]$, quindi $q=\frac{p+r}{2}$
2. Ordina i due sottoarray in modo ricorsivo utilizzando ancora il mergesort. Se il problema è sufficientemente piccolo (1 elemento), risolve direttamente
3. Fonde insieme i due sottoarray ordinati per generare un singolo vettore ordinato

![[Merge sample.svg]]

```
mergesort(array A, int p, int r)
	if p < r
		q = (p+r) / 2
		mergesort(A, p, q)
		mergesort(A, q+1, r)
		merge(A, p, q, r)

merge(array A, int p, int q, int r)
	n1 = q - p + 1
	n2 = r - q
	crea array L[1...n1+1] e R[1...n2+1]
	
	for i = 1 to n1
		L[i] = A[p+i-1]
	for j = 1 to n2
		R[j] = A[q+j]
		
	L[n1+1] = R[n2+1] = ∞ // elementi sentinella
	i = j = 1
	
	for k = p to r
		if L[i] <= R[j]
			A[k] = L[i]
			i++
		else
			A[k] = R[j]
			j++
```

Il `merge` fonde i due array in input in un unico array ordinato, per eseguirlo però:
- $p\leq q\leq r$
- I sottoarray $A[p ... q]$ e $A[q+1 ... r]$ sono ordinati, inoltre per le restrizioni poste su $p,q,r$ i due array non saranno mai vuoti
![[Merge sort animation.gif|300]]
**Invariante del ciclo** (ultimo for di `merge`):
Il sottoarray $A[p ... k-1]$ contiene ordinati i $k-p$ elementi più piccoli di $L[1 ... n1+1]$ e $R[1 ... n2+1]$, inoltre $L[i]$ e $R[j]$ sono i più piccoli elementi dei loro array che non sono stati ancora copiati in $A$.

- **Conclusione**: alla fine del ciclo $k=r+1$ e vale l'invariante, ovvero il sottoarray $A[p ... r+1-1]$ contiene ordinati i $r+1-p$ elementi più piccoli di $L[1 ... n1+1]$ e $R[1 ... n2+1]$, inoltre $L[i]$ e $R[j]$ sono i più grandi valori, cioè le sentinelle ($\infty$), il che significa che $A$ ora è ordinato e gli unici elementi che non sono stati copiati sono le sentinelle.

**Complessità**:
$$
\begin{flalign}
T_{\text{merge}}(n)&=\underbrace{q-p+1}_{n1}+\underbrace{r-q}_{n2}+\underbrace{r-p+1}_{\text{for per merge}}\\
&=\underbrace{r-p+1}_{n1+n2}+\underbrace{r-p+1}_{\text{for per merge}}\\
&=\Theta(n)+\Theta(n)\\
&=\Theta(n)
\end{flalign}
$$
Sapendo ora che la complessità di `merge` è $\Theta(n)$, la complessità totale è data da:
$$T_{\text{mergesort}}=\begin{cases}\Theta(1)&n\leq 1\\ 2T(\frac{n}{2})+\Theta(n)&n>1\end{cases}$$
Possiamo usare il teorema master:
- $f(n)=n$
- $n^{\log_ba}=n^{\log_22}=n$
Siamo nel secondo caso, per cui: $T(n)=\Theta(n\log n)$.

**Vantaggi**:
- $\Theta(n\log n)$
- Stabile
**Svantaggi**:
- Non in loco, ha bisogno di memoria aggiuntiva proporzionale al numero di elementi da ordinare
- Non è sensibile all'ordinamento

>L'algoritmo si può migliorare usando l'insertion sort quando il sottoarray è di piccole dimensioni.
