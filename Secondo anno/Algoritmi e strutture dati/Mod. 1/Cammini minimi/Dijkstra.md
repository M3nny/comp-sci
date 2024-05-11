Estrae un vertice alla volta e ogni volta rilassa gli archi uscenti da quel vertice (il primo estratto è la sorgente).

Viene utilizzata una coda di priorità $Q$ (che contiene i vertici da estrarre)
con chiave $d$.

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


|    $G$\Implementazione    |    Heap     | Array lineare |
| :-----------------------: | :---------: | :-----------: |
| **Sparso** ($m\simeq n$)  |  $n\log n$  |     $n^2$     |
| **Denso** ($m\simeq n^2$) | $n^2\log n$ |     $n^2$     |

### Correttezza
Sia $G=(V,E)$ un grafo orientato pesato con $w:E\to\mathbb{R}$, con sorgente $s\in V$ e $\forall(u,v)\in E$ si ha $w(u,v)\geq 0$, allora alla fine dell'algoritmo si avrà:
- $d[u]=\delta(s,u)\space\forall u\in V$
- $G_\pi$ è un albero di cammini minimi

Dimostriamo solo il primo punto attraverso varie **osservazioni**:
supponiamo che **per assurdo** esista un vertice $u\in V$ che al momento dell'estrazione abbia $d[u]\neq\delta(s,u)$ e supponiamo che $u$ sia il primo vertice per cui questo accade.  

**Osservazioni**:
- $u\neq s$ in quanto $d[s]=0=\delta(s,s)$ e non può neanche valere $-\infty$ perchè per ipotesi non ci sono cicli negativi ($w(u,v)\geq 0$)
- Al momento dell'estrazione di $u$, $S\neq \emptyset$, perchè in $S$ (vertici estratti) ci sarà almeno la sorgente $s$
- $u$ raggiunge $s$, questo perchè se non lo fosse, si avrebbe $\delta(s,u)=+\infty=d[u]$ e non rispetterebbe l'ipotesi dell'assurdo in quanto sarebbe corretto


Identifichiamo $x$ come il vertice appena estratto e $y$ il vertice da estrarre nel cammino minimo tra $s$ e $u$:
![[Osservazione Dijkstra.svg]]

per il punto precedente infatti, esiste un cammino minimo $p$ tra $s$ e $u$, e $(x,y)$ è l'arco che attualmente attraversa il taglio, ovvero $x\in S$, $y\in Q$.

1. $d[x]=\delta(s,x)$ dato che il primo a violare la condizione abbiamo detto essere $u$
2. $d[y]=\delta(s,y)$ per la [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Cammini minimi/Introduzione#Proprietà della convergenza|proprietà della convergenza]] in quanto all'estrazione di $x$ applichiamo la `Relax` su $y$, ottenendo $d[y]=\delta(s,x)+w(x,y)=\delta(s,y)$
3. $d[u]\leq d[y]$ perchè ora stiamo per estrarre il nodo $u$, e sappiamo che l'algoritmo estrae prima il vertice avente campo $d$ più piccolo
4. $\delta(s,y)\leq \delta(s,u)$ perchè ci troviamo in un cammino minimo con pesi $\geq 0$
5. $\delta(s,u)\leq d[u]$ per la [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Cammini minimi/Introduzione#Proprietà del limite inferiore|proprietà del limite inferiore]]

Dovendo dimostrare quindi che $d[u]=\delta(s,u)$, possiamo scriverlo sotto la forma di disequazione:
$$\underbrace{\delta(s,u)\leq d[u]}_\text{vero per osservazione 5.}\leq\delta(s,u)$$
verificando entrambi i lati della disequazione:
$$\begin{flalign}
\delta(s,u)&\leq d[u]\quad\text{per oss. (5)}\\
&\leq d[y]\quad\text{per oss. (3)}\\
&=\delta(s,y)\quad\text{per oss. (2)}\\
&\leq\delta(s,u)\quad\text{per oss. (4)}
\end{flalign}$$

questo è assurdo perchè così abbiamo che $d[u]=\delta(s,u)$ anche se nell'ipotesi (dell'assurdo) avevamo detto che esisteva un vertice $u$ per cui $d[u]\neq\delta(s,u)$, verificando così la correttezza dell'algoritmo.

#### Archi con peso negativo
L'algoritmo non può essere applicato in caso di archi con peso negativo, anche se si eseguisse uno shift di tutti i pesi.

Ad esempio se è presente un singolo arco con peso negativo $-1$, si potrebbe aumentare il peso di tutti gli archi di $+1$ per poi eseguire l'algoritmo sul nuovo grafo, questo però potrebbe non ritornare l'insieme di archi che formano il cammino minimo corretto per il grafo originale.

Infatti una volta trovato il peso minimo bisognerà sottrarre la quantità aggiunta a tutti i pesi per ogni arco che compone il cammino minimo trovato, così da rispecchiare il peso del cammino originale, questo non funziona perchè la costante viene sommata a molti archi e quindi potrebbe far variare il vero cammino minimo del grafo originale.

![[Arco negativo Dijkstra.svg]]