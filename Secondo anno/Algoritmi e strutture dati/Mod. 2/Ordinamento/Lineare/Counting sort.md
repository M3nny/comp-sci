Il limite inferiore per algoritmi di **confronto** è: $\Omega(n\log n)$, per dimostrarlo usiamo un **albero di decisione** rappresentante tutte le permutazioni degli elementi, dove ogni nodo (non foglia) ($x:y$) rappresenta il confronto tra l'elemento in posizione $x$ con quello in posizione $y$, mentre le foglie rappresentano le permutazioni.

![[Albero decisione.svg]]
Dato un qualsiasi algoritmo di confronto:
- $1$ albero di decisione per ogni $n$
- Il tempo di esecuzione (n° confronti) è dato dalla lunghezza di un cammino nell'albero
<u>Il caso peggiore avviene quando si considera l'altezza dell'albero</u>.

Vogliamo trovare un limite inferiore di tutti gli albero di decisione, dati $n$ elementi, esistono $n!$ permutazioni degli elementi, di conseguenza il numero di foglie è $\geq n!$
- $\geq$: perchè consideriamo anche gli algoritmi non ottimali
- $n!$: perchè ogni permutazione deve comparire almeno una volta

**Lemma**: un albero binario di altezza $h$ ha al massimo $2^h$ foglie ([[Cos'è un albero#Alberi binari|dimostrazione]]).
**Teorema**: qualsiasi algoritmo di ordinamento per confronto richiede $\Omega(n log n)$ confronti nel caso peggiore.

**Dimostrazione**: bisogna determinare l'altezza di un albero di decisione dove ogni permutazione appare come foglia. Si consideri un albero di decisione di altezza $h$ con $l$ foglie che corrisponde ad un ordinamento per confronto di $n$ elementi, allora:
$$n!\leq l\leq 2^h\implies h\geq \log_2 n!$$
Utilizzando [l'approssimazione di Stirling](https://it.wikipedia.org/wiki/Approssimazione_di_Stirling):
$$n!\simeq\sqrt{2\pi n}\cdot\underbrace{\left(\frac{n}{e}\right)^n}_{\text{Termine più grande}}\cdot\left(1+\Theta\left(\frac{1}{n}\right)\right)$$
si ottiene:
$$h\geq \log n!\geq \log\left(\frac{n}{e}\right)=n\log\left(\frac{n}{e}\right)=n(\log n-\underbrace{\log e}_{\Theta(1)})=\Omega(n\log n)$$
**Corollario**: [[Merge sort]] e [[Heap sort]] sono algoritmi di ordinamento per confronto asintoticamente ottimali.

---
## Counting sort

**Assunzione**: i numeri da ordinare sono interi in un intervallo limitato da $0$ a $k$, per qualche intero $k$.

```
countingSort(Array A, Array B, int k)
	Array C[0...k]
	
	for i = 0 to k
		C[i] = 0
	
	for j = 1 to n
		C[A[j]]++
	
	for i = 1 to k
		C[i] += C[i-1]
	
	for j = A.length down to 1
		B[C[A[j]]] = A[j]
		C[A[j]]--
```

![[Counting sample.svg]]
```c++
A: [3 0 2 3 2]

B: [0 0 0 0 0]
C: [1 1 3 5]

B: [0 0 2 0 0]
C: [1 1 2 5]

B: [0 0 2 0 3]
C: [1 1 2 4]

B: [0 2 2 0 3]
C: [1 1 1 4]

B: [0 2 2 0 3]
C: [0 1 1 4]

B: [0 2 2 3 3]
C: [0 1 1 3]
```

Cosa fanno i `for`:
1. Viene inizializzato l'array delle occorrenze
2. Vengono contate le occorrenze di un valore
3. Calcola le somme prefisse, ovvero somma ad ogni elemento di $C$, il numero di occorrenze dell'elemento precedente
4. Usa l'elemento in posizione $j$ come indice nell'array delle occorrenze, il quale contenuto sarà poi usato come indice nell'array risultato $B$, al quale verrà assegnato il valore dell'elemento in posizione $j$, viene poi decrementato il numero di occorrenze per quel valore nell'array delle occorrenze, in questo modo se ci sono più elementi uguali, verranno messi alla sinistra dell'ultimo elemento uguale inserito

Partendo dalla fine (nell'ultimo `for`) rende **stabile** l'algoritmo.

**Complessità**:
$T(n) = \Theta(k)+\Theta(n)+\Theta(k)+\Theta(n) = \Theta(k+n)$.
Se $k\leq n$, allora $T(n)=\Theta(n)$.

>[!Attention]
>Questo algoritmo non è vantaggioso se $k>n$.
>e.g. se la lunghezza è $n$, e $k=n^3$, la complessità sarà pari a $\Theta(n^3)$.

