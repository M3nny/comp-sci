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

