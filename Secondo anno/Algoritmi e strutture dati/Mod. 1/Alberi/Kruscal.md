L'algoritmo di **Kruskal** parte con un insieme vuoto di archi $A$ e poi aggiunge ad esso un arco a patto che non crei un ciclo, gli archi sono estratti in modo crescente.
```
Kruskal(G, w)
	A = ∅
	
	for each v in V[G]
		makeSet(v)
		
	sort(E[G])
	
	for each (u, v) in E[G]
		if findSet(u) != findSet(v)
			union(u, v)
			A = A U {(u, v)}
			
	return A
```

**Correttezza**: garantita dal [[Minimum Spanning Tree#Teorema fondamentale degli MST|teorema fondamentale degli MST]] in quanto inizialmente l'insieme $A$ è vuoto (appartiene ad ogni $MST$) e successivamente gli archi inseriti vengono considerati da quello con peso minore, considerando quindi sempre gli archi leggeri (finchè non finisce l'algoritmo).

>L'algoritmo potrebbe finire anche quando $|A|=n-1$
>senza dover necessariamente controllare tutti gli archi, tanto una volta che $|A|=n-1$, tutti gli `if` successivi falliranno.

**Complessità**:
- `1° for each`: $|V|=n$ iterazioni
- `sort`: $|E|\log (m)=m\log(m)$
- `2° for each`: $m$ iterazioni
- `findSet` e `union`: $\log(m)$
$$T(n,m)=O(n+2m\log(m))=O(m\log(m))$$

**Esecuzione formale dell'algoritmo**:
![[Exec Kruskal.svg|300]]


| Step | A                               | Insiemi                             | Arco    |
| ---- | ------------------------------- | ----------------------------------- | ------- |
| $0$  | $\emptyset$                     | $\{a\}, \{b\}, \{c\}, \{d\}, \{e\}$ | $(b,d)$ |
| $1$  | $\{(b,d)\}$                     | $\{a\}, \{b,c\}, \{d\}, \{e\}$      | $(b,c)$ |
| $2$  | $\{(b,d),(b,c)\}$               | $\{a\}, \{b,c,d\}, \{e\}$           | $(a,e)$ |
| $3$  | $\{(b,d),(b,c)\}$               | $\{a,e\}, \{b,c,d\}$                | $(c,d)$ |
| $4$  | $\{(b,d),(b,c), (a,e)\}$        | $\{a,e\}, \{b,c,d\}$                | $(b,e)$ |
| $5$  | $\{(b,d),(b,c), (a,e)\}$        | $\{a,b,c,d,e\}$                     | $(e,d)$ |
| $6$  | $\{(b,d),(b,c), (a,e), (b,e)\}$ | $\{a,b,c,d,e\}$                     | $(a,b)$ |
| $7$  | $\{(b,d),(b,c), (a,e), (b,e)\}$ | $\{a,b,c,d,e\}$                     | $/$     |
