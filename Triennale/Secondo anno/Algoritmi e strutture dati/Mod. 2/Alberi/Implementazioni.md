### Implementazione con array
Prevede l'utilizzo di un array contenente coppie (**info, parent**), contenenti l'informazione del nodo e l'indice del suo nodo padre.
Sia $T=(N, A)$ un albero di $n$ nodi numerati da $0$ a $n-1$ rappresentabile come segue:
![[Albero binario.png|400]]
Il relativo array è:

|  P.info  | a   | b   | c   | d   | e   | f   | g   | h   | i   |
|:--------:| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| P.parent | -1  | 0   | 0   | 0   | 1   | 1   | 3   | 6   | 6   |
|  Indice  | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |

- $\text{P[v].info}$ è l'informazione
- $\text{P[v].parent}==u\iff\exists (u,v)\in A$
- Se $v$ è la radice $\text{P[v].parent == -1}$
- $\text{P.length}$ rappresenta il numero di nodi nell'albero

La complessità spaziale è:
$$S(n)=\Theta(n)$$
#### Padre
```
padre (Tree P, Node v)
	if P.[v].parent == -1
		return NIL
	else
		return P[v].parent
```
Semplicemente ritorna `NIL` se è la radice (non ha padre) altrimenti ritorna il padre.
##### Complessità
Eseguiamo solo assegnamenti, quindi la complessità è:
$$T(n)=\Theta(1)$$
#### Figli
```
figli (Tree P, Node v)
	l = creaLista()
	for i = 0 to P.length - 1
		if P[i].parent == v
			inserisci i in l
	return l
```
Creiamo una lista `l` per contenere i figli, poi vediamo se l'elemento dell'array ha come padre `v` e in quel caso lo inseriamo nella lista dei figli.
##### Complessità
Dobbiamo scorrere tutta la lista per vedere se esistono figli di `v`, quindi la complessità è (ipotizzando che l'inserimento sia costante):
$$T(n)=\Theta(n)$$

---
### Implementazione con vettore posizionale
Supponiamo di avere un albero $k$-ario completo con $k\geq 2$, dove $P$ è un vettore di dimensione $n$ dove `P[v]` contiene l'informazione del nodo `v`, e `P[0]` contiene l'informazione della radice.
![[Albero k-ario.svg]]
Vettore $P$:

| a   | b   | c   | d   | e   | f   | g   | h   | i   | l   | m   | n   | o   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  | 11  | 12  |

- L'$i$-esimo figlio è in posizione $k\cdot v+1+i$
- Il padre di un nodo $f$ diverso dalla radice è in posizione $\frac{f-1}{k}$
	e.g. il padre di $\text{i}$ è $\frac{8-1}{3}=2$
- $\text{P.length}$ contiene il numero di nodi
- $\text{P.K}$ contiene il grado di tutti i nodi
La complessità spaziale è:
$$S(n)=\Theta(n)$$
#### Padre
```
padre (Tree P, Node v)
	if v == 0 // radice
		return NIL
	else
		return (v-1)/P.K
```
##### Complessità
$$T(n)=\Theta(1)$$
#### Figli
```
figli (Tree P, Node v)
	l = creaLista()
	if (v * P.K + 1) >= P.length // non ha figli
		return l
	else
		for i = 0 to P.K - 1
			inserisci (v * P.K + 1 + i) in l
		return l
```
##### Complessità
Nel caso peggiore dobbiamo scorrere $K$ elementi, nel caso migliore il figlio non esiste.
$$T(n)=O(K)$$
Lo **svantaggio** di questa implementazione sono i costi di inserimento e cancellazione i quali portano allo spostamento di tanti elementi nel vettore.

---
### Implementazione con strutture collegate
Questa implementazione va bene per alberi generali, noi per semplicità considereremo alberi binari.
Supponendo un **albero binario**, ogni nodo $\text{x}$ avrà:
- $\text{x.Key}$: contiene l'informazione
- $\text{x.p}$: puntatore al padre
- $\text{x.left}$: puntatore al figlio sinistro
- $\text{x.right}$: puntatore al figlio destro
![[Albero con strutture collegate.svg]]
Lo spazio richiesto è:
$$S(n)=\Theta(n\cdot K)\quad\text{oppure}\quad S(n)=\Theta(n)\space\text{(se K è costante)}$$
#### Padre
```
padre (TreeP, Node v) // v è un puntatore
	return v.p
```
##### Complessità
$$T(n)=\Theta(1)$$
#### Figli
```
figli (Tree P, Node v) // cosiderando K=2
	l = creaLista()
	if v.left != NIL
		inserisci v.left in l
	if v.right != NIL
		inserisci v.right in l
	return l
```
Dato che dovrò accedere al massimo a $K$ puntatori, la complessità è:
$$T(n)=\Theta(1)$$
In questa implementazione lo **svantaggio** è il fatto di avere potenzialmente puntatori a tanti figli NIL.

### Implementazione con figlio sinistro - fratello destro
Ogni nodo $\text{x}$ possiede:
- $\text{x.Key}$: contiene l'informazione
- $\text{x.p}$: puntatore al padre
- $\text{x.left\_child}$: puntatore al figlio più a sinistra, se è NIL, allora $\text{x}$ è foglia
- $\text{x.right\_sib}$: puntatore al fratello subito a destra di $\text{x}$, se è NIL è il figlio più a destra del padre
![[Albero figlio sinistro fratello destro.svg]]
Lo spazio richiesto è uguale a quello dell'implementazione precedente.
#### Padre
```
padre (Tree P, Node v)
	return v.p
```
##### Complessità
$$T(n)=\Theta(1)$$
#### Figli
```
figli (Tree P, Node v)
	l = creaLista()
	iter = v.left_child
	while iter != NIL
		inserisci iter in l
		iter = iter->right_sib
	return l
```
##### Complessità
$$T(n)=\Theta(K)$$