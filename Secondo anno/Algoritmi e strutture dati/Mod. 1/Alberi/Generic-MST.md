L'algoritmo **Generic-MST** è un'**idea**, un **modello** su cui si basano algoritmi reali per la ricerca di un [[Minimum Spanning Tree#Albero di copertura minimo|MST]].
```
Generic-MST(G, w)
	A = emptySet
	while |A| < |V| - 1 // finchè non forma un MST
		trova un arco (u, v) sicuro per A
		A = A U {(u, v)}
	return A
```

### Strutture dati
Le strutture dati trattate, come le operazioni sono molto astratte in modo da poter esprimere gli algoritmi facilmente in pseudocodice.

Definiamo **rappresentante** di un insieme un elemento che compare solo in un insieme.

**Operatori**:
- $\text{makeSet(x)} \rightarrow \{x\}$: crea un set con un unico elemento `x`
- $\text{union(x, y)} \rightarrow S_X\cup S_y$: esegue l'unione degli insiemi aventi come rappresentanti $x$ e $y$
- $\text{findSet}\rightarrow y:x\in S_y$: dato $x$ ritorna il rappresentante dell'insieme che contiene $x$

**Strutture dati**:
- **Liste concatenate**: in testa è presente il _rappresentante_ dell'insieme e finisce con NIL
- **Heap binari** ([[Heap sort|heap]]): nella radice troviamo il _rappresentante_ dell'insieme, bisogna fare attenzione all'unione che potrebbe portare a violazioni delle proprietà degli heap (bisogna aggiustare l'heap quindi)

### Verifica della componenti connesse
Dato un grafo vogliamo un algoritmo che verifichi se si tratta di un'unica componente connessa, e nel caso non lo sia, ritorni le sue componenti connesse.
```
Connected_Components(G)
	for each v in V[G]
		makeSet(v)
	for each (u, v) in E[G]
		if findSet(u) != findSet(v)
			union(u, v)
```

1. Crea tanti insiemi singoletti quanti sono i nodi in $G$
2. Itera tutti gli archi in $G$, se gli estremi dell'arco appartengono ad insiemi differenti, unisce i due insiemi

![[Connected components.svg]]

| Step | Insiemi                               | Arco    |
| ---- | ------------------------------------- | ------- |
| $0$  | $\{1\},\{2\},\{3\},\{4\},\{5\},\{6\}$ |         |
| $1$  | $\{1,2\},\{3\},\{4\},\{5\},\{6\}$     | $(1,2)$ |
| $2$  | $\{1,2\},\{3\},\{4,5\},\{6\}$         | $(4,5)$ |
| $3$  | $\{1,2,3\}, \{4,5\},\{6\}$            | $(1,3)$ |
| $4$  | $\{1,2,3\}, \{4,5\},\{6\}$            | $(2,3)$ |
