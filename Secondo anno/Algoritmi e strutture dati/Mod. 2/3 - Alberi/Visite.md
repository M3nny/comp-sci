Visitare un albero significa esplorare tutti i suoi nodi, dove ogni nodo viene visitato al massimo una volta.
Per cui la complessità di una visita generica è:
$$T(n)=S(n)=O(n)$$
### Depth First Search (DFS)

L'idea è quella di usare lo **stack** per esplorare più a fondo possibile e poi ritornare su.
```
DFS(Node r)
	if  r!= NIL
		// visita r
		DFS(r.left)
		DFS(r.right)
```

Si può **dimostrare** che questa visita, dato che visita tutti i nodi ha complessità $\Theta(n)$.
$$T(n)=\begin{cases}c&\text{se }n=0\\T(k)+T(n-k-1)+d&\text{se }n>0\end{cases}$$
dove $T(k)$ è il numero di nodi del sottoalbero sinistro, mentre $T(n-k-1)$ è il numero di nodi del sottoalbero destro (togliamo dal totale dei nodi il sottoalbero sinistro e la radice da cui partiamo a visitare).

<u>Risolviamo con il metodo di sostituzione</u>: la complessità di questa funzione è lineare per ipotesi, quindi supponiamo che sia uguale alla funzione lineare più generica di tutte, ovvero $T(n)=an+b$ e lo dimostro per [[Il principio di induzione#Principio di induzione forte|induzione completa]] su $n$ nodi.
- **Caso base**: $T(0)=c$ ovvero una costante, proprio come $T(0)=a\cdot 0+b$ ponendo $b=c$
- **Passo induttivo**: assumiamo che per ogni $m<n$ vale che $T(m)=am+b$ e lo dimostro per $n$.
	$$\begin{flalign}
	T(n)&=T(k)+T(n-k-1)+d\text{ (per definizione)}\\
	&=ak+b+a(n-k-1)+b+d\text{ (per ipotesi induttiva)}\\
	&=an+2b-a+d
	\end{flalign}$$
	vogliamo quindi dimostrare che:
	$$an+2b-a+d=an+b\implies a=b+d$$
	dal caso baso abbiamo che $b=c$, quindi $a=c+d$, e sostituendo alla funzione generica otteniamo:
	$$T(n)=(c+d)n+c=\Theta(n)$$

#### Ordine di visita nella DFS
Esistono tre modi per eseguire la DFS:
![[DFS.svg]]
- **Pre-order**:
```
DFS(Node r)
if  r!= NIL
	// visita r
	DFS(r.left)
	DFS(r.right)
```
- **In-order**:
```
DFS(Node r)
if  r!= NIL
	DFS(r.left)
	// visita r
	DFS(r.right)
```
- **Post-order**:
```
DFS(Node r)
if  r!= NIL
	DFS(r.left)
	DFS(r.right)
	// visita r
```

### Breadth First Search (BFS)
In questa visita vengono visitati tutti i nodi sullo stesso livello prima di passare al prossimo.
```BFS(Node R)
	Queue C = newQueue()
	enqueue(C, r) // θ(1)
	while not queueEmpty(C)
		u = dequeue(C) // θ(1)
		if u != NIL
			// visita u
			enqueue(C, u.left)
			enqueue(C, u.right)
```
Anche questa visita avrà complessità:
$$T(n)=\Theta(n)$$
