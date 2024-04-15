Estrae un vertice alla volta e ogni volta rilassa gli archi uscenti da quel vertice (il primo estratto è la sorgente).

Viene utilizzata una coda di priorità $Q$ (che contiene i vertici da estrarre) con chiave $d$.

Per cui i vertici estratti sono dati da: $S=V\setminus Q$.

```
Dijkstra(G, w, s)
	INIT_SS(G, s)
	Q = V[G]
	S = ∅
	while Q != ∅
		u = extractMin(Q)
		S = S U {u}
		for each v in Adj[u]
			relax((u, v), w(u, v))
	return (d, G_π)
```

### Complessità
**Complessità** (con **heap binario**):
l'inizializzazione ha costo lineare, il ciclo `while` esegue $n$ iterazioni, e l'operazione `extractMin` avrà costo logaritmico, il `for-each` eseguirà [[Grado#Grafi orientati|out-deg]] volte l'operazione di `relax` che avrà costo logaritmico in quanto dovrà
eventualmente ri-bilanciare l'heap binario.
$$T(n,m)=\underbrace{n}_\text{Init}+\underbrace{n\log n}_\text{Extract}+\underbrace{m\log n}_\text{Relax}=O(m\log n)$$

**Complessità** (con **array lineare**):
in questo caso l'operazione di `relax` è più rapida, infatti è semplicemente un assegnamento, a scapito però di una `extractMin` più lenta dato che bisognerà cercare l'elemento più piccolo in tutto l'array.
$$T(n,m)=\underbrace{n}_\text{Init}+\underbrace{n^2}_\text{Extract}+\underbrace{1\cdot m}_\text{Relax}=O(n^2)$$

**Osservazioni**:
- Grafo **sparso**: $m\simeq n$
- Grafo **denso**: $m\simeq n^2$

| $G$\Implementazione |    Heap     | Array lineare |
| :-----------------: | :---------: | :-----------: |
|     **Sparso**      |  $n\log n$  |     $n^2$     |
|      **Denso**      | $n^2\log n$ |     $n^2$     |

