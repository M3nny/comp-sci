Esegue $n-1$ iterazioni, e per ognuna di esse esegue `Relax` su tutti gli archi del grafo.

>Rispetto a Dijkstra, può essere eseguito anche su grafi che hanno archi con pesi negativi, ma comunque non con _cicli_ negativi.

Utilizza le stesse strutture dati di [[Dijkstra]], però usa un approccio di "brute force".

```
Bellman-Ford(G, w, s)
	Init_SS(G, s)
	
	for i = 1 to |V[G]| - 1
		for each (u, v) in E[G]
			Relax((u, v), w(u,v))
	
	for each(u, v) in E[G]
		if d[v] > d[u] + w(u, v)
			return false
	return true
```

### Complessità
L'inizializzazione ha costo lineare, la **prima parte** dell'algoritmo (che è l'algoritmo in sè) scorre tutti gli $n-1$ nodi e per ognuno di essi ne rilassa gli archi, la **seconda parte** consiste in un "sanity check" per controllare se ci sono stati cicli negativi, ed in quel caso ritorna `false` per segnalare che il risultato computato non è affidabile (l'algoritmo non funziona con cicli negativi).
$$T(n,m)=\underbrace{n}_\text{Init}+\underbrace{(n-1)\cdot m}_\text{Prima parte}+\underbrace{m}_\text{Seconda parte}=O(n\cdot m)$$

### Correttezza
Sia $G=(V,E)$ un grafo orientato pesato con $w:E\to\mathbb{R}$, con sorgente $s\in V$,
alla fine dell'algoritmo se in $G$ _non_ ci sono cicli negativi raggiungibili da $s$ si avrà:
- $d[u]=\delta(s, u)\space\forall u\in V$
- $G_\pi$ è un albero di cammini minimi
- L'algoritmo restituisce `true`

Se $G$ contiene cicli negativi raggiungibili da $s$, allora alla fine dell'algoritmo:
- L'algoritmo restituisce `false`

Dimostrazione del **primo punto**:
$$\forall u\in V,\space\delta(s, u)=\begin{cases}+\infty\\\in\mathbb{R}\\-\infty\end{cases}$$
ignoriamo il caso in cui otteniamo $+\infty$ in quanto quel vertice non essendo raggiungibile da $s$ avrebbe $d[u]=\delta(s,u)$ subito dopo `INIT_SS`, ed il caso in cui otteniamo $-\infty$ in quanto abbiamo detto che non ci sono cicli negativi raggiungibili da $s$ (per cui $s$ non può essere all'interno di un ciclo negativo).

se $s\in\mathbb{R}$ esiste un cammino minimo tra $s$ e $u$, sia $p$ un **cammino minimo semplice** (senza cicli) tra $s$ e $u$ (potrebbero esistere anche cammini minimi non semplici se il ciclo ha costo pari a $0$, tuttavia è possibile togliere questo ciclo così da ottenere sempre un cammino minimo semplice).

questo cammino potrà avere fino a $n-1$ archi in totale (nel caso attraversasse tutti i vertici), poichè <u>i sottocammini di camminimi minimi sono anch'essi minimi</u> possiamo applicare la [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Cammini minimi/Introduzione#Proprietà della convergenza|proprietà della convergenza]] tante volte quante sono le iterazioni dell'algoritmo, generando così, un "effetto domino":
- Subito dopo l'inizializzazione sarà vero che $d[s]=0=\delta(s,s)$
- Viene eseguito `Relax` su tutti gli archi
- Alla prossima iterazione la _proprietà della convergenza_ risulta essere verificata

alla fine di tutte le iterazioni, sarà vero per tutti i nodi che $d[i]=\delta(s,i)$.

Dimostrazione del **terzo punto**:
se alla fine l'algoritmo restituisce `true`, allora dovrà valere che:
$$\forall(u,v)\in E,\quad d[v]\leq d[u]+w(u,v)$$
la [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Cammini minimi/Introduzione#Disuguaglianza triangolare|disuguaglianza triangolare]] afferma: $\delta(s,v)\leq\delta(s,u)+w(u,v)$, ma avendo dimostrato il _primo punto_, possiamo sostituire le stime delle distanze alle distanze reali, ovvero $d[u]=\delta(s,u)$:
$$\delta(s,v)\leq\delta(s,u)+w(u,v)\implies d[v]\leq d[v]+w(u,v)$$
che è quello che volevamo dimostrare.

