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

---
### Strutture dati
In questo tipo di problema, vengono impiegate dagli algoritmi risolutivi, le seguenti strutture dati:
1. $d[u]$: stima della distanza tra $s$ e $v$
2. $\pi[u]$: predecessore

Denotiamo il **grafo dei predecessori**, il sottografo di $G$: $G_\pi=(V_\pi,E_\pi)$, esso dipende dal campo predecessore dei vertici di $G$, esso inoltre è un grafo che si evolve durante l'esecuzione dell'algoritmo (di ricerca del cammino minimo).
Lo possiamo definire come segue:
$$G_\pi=\begin{cases}
V_\pi=\{s\}\cup\{v\in V[G]\space|\space\pi[v]\neq\text{NIL}\}\\
E_\pi=\{(\pi[v],v)\in E\space|\space v\in V_\pi\setminus \{s\}\}
\end{cases}$$

![[Grafo dei predecessori.svg]]

Denotiamo l'**albero dei cammini minimi** il sottografo di $G$: $G'=(V',E')$  dove valgono le seguenti condizioni:
- $V'=\{v\in V\space|\space\delta(s,v)<+\infty\}$, ovvero i vertici del grafo sono raggiungibili dalla radice
- $G'$ forma una albero con radice $s$
- Per ogni vertice $v\in V'$, l'unico cammino tra $s$ e $v$ in $G'$ è un cammino minimo tra $s$ e $v$ in $G$

>Alla fine dell'algoritmo vogliamo che $G_\pi$ sia un _albero di cammini minimi_.

---
### Funzioni ausiliarie

#### Inizializzazione
```
INIT_SS(G)
	for each u in V[G]
		d[u] = +∞
		π[u] = NIL
	d[s] = 0
```

pone a $+\infty$ tutte le distanze dei nodi, tranne il nodo sorgente a cui verrà assegnato il valore $0$, inoltre viene posto a $\text{NIL}$ il valore di tutti i predecessori.

#### Relax (aggiornamento)
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

---
### Proprietà dei cammini minimi

##### Sottocammini minimi
<u>I sottocammini di cammini minimi sono anch'essi minimi</u>.

**Dimostrazione** (per assurdo): ipotizziamo che esista un altro sotto-cammino (all'interno di un cammino minimo) il cui peso è minore di quello scelto per arrivare da $x$ a $y$, questo renderebbe il cammino che comprende il sotto-cammino **non minimo**, il che è assurdo, perchè per ipotesi avevamo un cammino minimo in partenza.

##### Disuguaglianza triangolare
$$(u,v)\in E\implies \delta(s,v)\leq \delta(s,u)+w(u,v)$$

**Dimostrazione**:
Distinguiamo tre casi:
1. $\delta(s,u)=+\infty$
	ovvero non esiste un cammino tra $s$ e $u$, allora banalmente $+\infty\leq +\infty$
2. $\delta(s,u)=-\infty$
	ovvero esiste un ciclo negativo tra $s$ e $u$, allora banalmente $-\infty\leq -\infty$
3. $\delta(s,u)\in\mathbb{R}$
	ovvero esiste un cammino senza cicli negativi tra $s$ e $u$,
	sia $p$ il cammino da $s$ a $u$, se l'unico cammino tra $s$ e $v$ è dato da $p\cup(u,v)$, allora il costo di tale cammino è uguale a $w(p)+w(u,v)$.
	È possibile però che esistano altri cammini da $s$ a $v$ il cui costo può essere minore di $w(p)+w(u,v)$ e di conseguenza, quindi $\delta(s,u)+w(u,v)$ è il valore massimo per la distanza tra $s$ e $v$

##### Proprietà del limite inferiore
In qualsiasi algoritmo che:
1. Inizializza i dati con `INIT_SS`
2. Usa esclusivamente `Relax` per modificare la struttura dati $\pi$ (predecessori)
$$\delta(s,v)\leq d[v]$$

ovvero, per qualunque sequenza di `Relax` eseguita, la **vera distanza** tra
$s$ e $v$ ($\delta(s,v)$) costituirà sempre un limite inferiore per la stima della
distanza ($d[v]$) tra $s$ e $v$.
>Quando $\delta(s,v)=d[v]$, le `Relax` a venire non cambieranno più il valore di $d[v]$.

**Dimostrazione**:
Distinguiamo due situazioni in cui viene eseguita la `Relax`:
1. Subito dopo la `INIT_SS`
	- se $v\neq s$ si avrà $d[v]=+\infty$ dovuto all'inizializzazione che verifica la proprietà
	- se $v=s$ allora $\delta(s,s)=0$ se non ci sono cicli negativi, altrimenti se $s$ è all'interno di un ciclo negativo, si avrà $\delta(s,s)=-\infty$, e in entrambi i casi si ha $\delta(s,s)\leq 0=d[s]$
2. Supponiamo per _assurdo_ che $v$ sia il **primo** vertice per cui la la proprietà della `Relax` viene violata e quindi vada ad abbassare il valore di $d[v]$ tale che $d[v]<\delta(s,v)$, al termine dell'operazione si avrà:
$$\begin{flalign}
d[u]+w(u,v)&=d[v]\\
&<\delta(s,v)\quad\text{(per ipotesi)}\\
&\leq \delta(s,u)+w(u,v)\quad\text{(per disuguaglianza triangolare)}
\end{flalign}$$

quindi abbiamo che:
$$d[u]+\cancel{w(u,v)}\leq\delta(s,u)+\cancel{w(u,v)}\implies d[u]\leq \delta(s,u)$$
ma è assurdo perchè allora $v$ non sarebbe il primo vertice che infrange la proprietà, ma sarebbe $u$.

##### Proprietà della convergenza
In un **cammino minimo** per qualche coppia per vertici $u,v\in V$, supponiamo che dopo una serie di `Relax` si abbia $d[u]=\delta(s,u)$, allora `Relax((u,v),w(u,v))` farà in modo che $d[v]=\delta(s,v)$.

**Dimostrazione**:
$$\begin{flalign}
\delta(s,v)&\leq d[v]&\text{(proprietà limite inferiore)}\\
&\leq d[u]+w(u,v)&\text{(proprietà Relax)}\\
&=\delta(s,u)+w(u,v)&\text{(per ipotesi)}\\
&=\delta(s,v)&\text{(perchè siamo su un cammino minimo)}
\end{flalign}$$
