Il quicksort è un algoritmo basato sulla tecnica **divide et impera**.

Sia $A[p...r]$ l'array da ordinare, e inizialmente $p=1$ e $r=A.length$:
1. Partiziona l'array $A[p ... r]$ in due sottoarray $A[p ... q-1]$ e $A[q+1 ... r]$ (eventualmente vuoti) dove $q$ non è compreso in nessuno dei due, tali che ogni elemento di $A[p ... q-1]\leq A[q]\leq A[q+1 ... r]$. L'indice $q$ è risultato di questa proceduta di partizionamento, e l'elemento $A[q]$ è chiamato pivot
2. Ordina i due sottoarray $A[p ... q-1]$ e $A[q+1 ... r]$ chiamando ricorsivamente quicksort. Risolve direttamente il problema se è sufficientemente piccolo (0 o 1 elementi)
3. Non c'è un vero è proprio passaggio di combinazione dei risultati, in quanto i sottoarray sono già ordinati sul posto

![[Quicksort sample.svg|450]]

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
**Invariante del ciclo**:
Ogni elemento in $A[p ... i]$ è minore o uguale al pivot ($x$), mentre ogni elemento $A[i+1 ... j-1]$ è strettamente maggiore del pivot.

- **Conclusione**: alla fine del ciclo, $j = r$, in questo modo l'invariante vale con gli elementi tra $i+1$ e $r-1$, in pratica ad ogni ciclo di for viene ingrandita una delle due porzioni finchè non ci sono più elementi appartenenti a $[?]$.

#### Analisi della complessità
Il tempo di esecuzione di `partition` è $\Theta(n)$ in quanto $n=r-p-1$.
Il tempo di esecuzione del `quicksort` è dato da:
$$\begin{cases}c&n\leq 1\\\underbrace{T(k)}_{\text{elementi }\leq x}+\underbrace{T(n-k-1)}_{n-(\text{elementi }\leq x)-\text{pivot}}+\Theta(n)&n>1\end{cases}$$
- **Caso peggiore**: una partizione contiene $n-1$ elementi, l'altra $0$.
$$\begin{flalign}
T(n)&=T(n-1)+\underbrace{T(0)}_{\Theta(1)}+\Theta(n)\\
&=T(n-1)+cn\\
&=T(n-2)+c(n-1)+cn\space\text{(per srotolamento)}\\
&=\sum_{i=1}^nci=c\sum_{i=1}^ni\\
&=c+\frac{n(n+1)}{2}\space\text{(per progressione aritmetica)}\\
&=\Theta(n^2)
\end{flalign}$$
Il tempo di esecuzione su partizioni fortemente sbilanciate (e.g. vettore già ordinato o crescente o decrescente) è quindi $\Theta(n^2)$.

- **Caso migliore**: due sottoproblemi di $\frac{n}{2}$ elementi e $\frac{n}{2}-1$ elementi ($-1$ così viene tolto il pivot).
$$T(n)=2T(\frac{n}{2})+\Theta(n)$$
Possiamo usare il teorema master:
- $f(n)=n$
- $n^{\log_b a}=n^{\log_2 2}=n$

Siamo nel secondo caso, $T(n)=\Theta(n\log n)$.

- **Caso medio**: supponiamo che l'algoritmo produca sempre una ripartizione proporzionale a $9:1$.
$$T(n)=T(\frac{n}{10})+T(\frac{9n}{10})+cn$$
tramite l'albero delle ricorsioni otteniamo:
![[Quicksort caso medio.svg|600]]

All'inizio la somma della complessità dei livelli è $cn$, ma ai livelli inferiori sarà $\leq cn$ in quanto alcuni cammini termineranno prima la ricorsione di altri, infatti la profondità del cammino sinistro (più corto) è $\log_{10}n$, mentre quella del cammino destro (più lungo) è $\log_{\frac{10}{9}}n$.

La ricorsione termina alla profondità $\log_{\frac{10}{9}}n=\Theta(\log n)$, dunque la complessità totale è data da:
$$T(n)\leq cn\cdot\log_{\frac{10}{9}}n=O(n\log n)$$
Generalizzando: qualsiasi proporzionalità costante $T(n)=T(\alpha n)+T((1-\alpha)n)+cn$ con $\alpha$ costante e $0<\alpha<1$ e $c>0$ costante produce un albero di ricorsione di profondità $\Theta(\log n)$, dove il costo di ogni livello è sempre $O(n)$, facendo risultare il tempo di esecuzione in $O(n\log n)$.

- **Altro caso medio**: supponiamo che si alternino partizioni buone ($L$) e pessime ($U$)
$$L(n)=2U(\frac{n}{2})+\Theta(n)\quad\text{(Lucky)}$$
$$U(n)=L(n-1)+\Theta(n)\quad\text{(Unlucky)}$$
sostituendo si ottiene:
$$\begin{flalign}
L(n)&=2(L(\frac{n}{2}-1)+\Theta(\frac{n}{2}))+\Theta(n)\\
&=2L(\frac{n}{2}-1)+2\Theta(\frac{n}{2})+\Theta(n)\\
&=2L(\frac{n}{2}-1)+\Theta(n)\\
&=\Theta(n\log n)
\end{flalign}$$

|   Caso migliore   |    Caso medio     | Caso peggiore |
|:-----------------:|:-----------------:|:-------------:|
| $\Theta(n\log n)$ | $\Theta(n\log n)$ |   $O(n^2)$    |

### Pivot casuale
Scegliere in modo casuale il pivot evita il caso peggiore.
Invece di sceglierlo sempre con la posizione $r$, cioè $A[r]$, scambiamo $A[r]$ con un elemento scelto a caso in $A[p ... r]$, questo ci assicura che il pivot $x$ avrà la stessa probabilità di essere uno qualsiasi degli $r-p+1$ elementi del sottoarray.

```
randomized_quicksort(array A, int p, int r)
	if p < r
		q = randomized_partition(A, p, r)
        randomized_quicksort(A, p, q-1)
        randomized_quicksort(A, q+1, r)

randomized_partition(Array A, int p, int r) -> int
    i = random(p, r)
    scambia A[i] e A[r]
    return partition(A, p, r) // partition normale
```
