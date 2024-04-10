Il problema dei **cammini minimi** riguarda i **grafi orientati**.
>Tuttavia possiamo vedere due nodi collegati da un arco non orientato, come due nodi collegati da due archi orientati. 

Indichiamo con $\mathscr{C}(u,v)$ l'insieme di [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Cammini|cammini]] che partono da $u$ e arrivano in $v$,
la **lunghezza di un cammino** è data da:
$$w(p)=\sum_{i=1}^qw(x_{i-1},x_i)$$

La **distanza** tra $u$ e $v$ è data da:
$$\delta(u,v)=
\begin{cases}
\min w(p)&\text{se }\mathscr{C}(u,v)\neq\emptyset\\
+\infty&\text{se }\mathscr{C}(u,v)=\emptyset\\
-\infty&\text{se }\mathscr{C}(u,v)\neq\emptyset \text{ ed } \exists\text{ ciclo negativo raggiungibile da sorgente}
\end{cases}$$

![[Ciclo negativo.svg]]

Nell'esempio soprastante abbiamo un **ciclo negativo**, si verifica quando la somma dei pesi degli archi che lo compongono è negativa, questo rende indeterminato (o meglio, $-\infty$) il valore minimo in quanto, ci potrebbero fare infiniti cicli per abbassare il costo del cammino.

Nella componente connessa di destra però, viene usato $+\infty$ dato che quei nodi **non sono raggiungibili dalla sorgente**.

Da notare anche che la sorgente è sempre pari a $0$, tranne quando compare in un ciclo negativo, infatti se la sorgente fosse presente nella componente connessa di destra, essa avrebbe valore $-\infty$.

### Tipi di problemi
Di seguito sono riportati i quattro tipi di problemi riguardanti i cammini minimi:

| Sorgenti \ Destinazioni | Singola                            | Multipla                                               |
| ----------------------- | ---------------------------------- | ------------------------------------------------------ |
| **Singola**             | in: $(u,v)$<br>out: $\delta(u,v)$  | in: $s\in V$<br>out: $\delta(s,v)\space\forall v\in V$ |
| **Multipla**            | in: $d\in V$<br>out: $\delta(u,d)$ | in: $G$<br>out: $\delta(u,v)\space\forall (u,v)\in V$  |
**Algoritmi**:
- **Dijkstra** e **Bellman-Ford**: sorgente singola - destinazioni multiple
- **Floyd-Warshall**: sorgente multipla - destinazioni multiple

**Osservazioni**:
- Sorgente multipla - destinazione singola può essere risolto invertendo la direzione degli archi del grafo per poi applicare un algoritmo per ss - dm
- Sorgente singola - destinazione singola comunque dovrà esplorare tutto il grafo, quindi la sua complessità non risulta essere migliore di quelle degli algoritmi con ss - dm

#### Proprietà dei cammini minimi
I sotto-cammini di cammini minimi sono anch'essi minimi.

**Dimostrazione** (per assurdo): ipotizziamo che esista un altro sotto-cammino (all'interno di un cammino minimo) il cui peso è minore di quello scelto per arrivare da $x$ a $y$, questo renderebbe il cammino che comprende il sotto-cammino **non minimo**, il che è assurdo, perchè per ipotesi avevamo un cammino minimo in partenza.

---
#### Strutture dati
In questo tipo di problema, vengono impiegate dagli algoritmi risolutivi, le seguenti strutture dati:
1. $d[u]$: stima della distanza tra $s$ e $v$ ($\delta(s,v)$)
2. $\pi[u]$: predecessore

#### Funzioni ausiliarie

**Inizializzazione**:
```
INIT_SS(G)
	for each u in V[G]
		d[u] = +∞
		π[u] = NIL
	d[s] = 0
```

pone a $+\infty$ tutte le distanze dei nodi, tranne il nodo sorgente a cui verrà assegnato il valore $0$, inoltre viene posto a $\text{NIL}$ il valore di tutti i predecessori.

**Aggiornamento (Relax)**:
```
Relax((u, v), w(u,v))
	if d[v] > d[u] + w(u, v)
		d[v] = d[u] + w(u, v)
		π[v] = u
```

![[Relax grafo.svg]]
L'operazione di `relax` serve ad aggiornare le strutture dati quando viene trovato un cammino con peso minore rispetto a quello conosciuto (inizialmente $+\infty$).
Inizializzazione infatti, $d[u]$ rappresenta una stima del peso del cammino.

>`relax` comunque cambierà al massimo il valore del vertice con arco entrante, e ne diminuirà sempre la sua distanza (se entra nell'else).

Alla fine degli algoritmi ci aspettiamo che: $\forall v\in V,\space d[v]=\delta(s,v)$.

