Questo algoritmo utilizza la [[Approccio dinamico|programmazione dinamica]], funziona con pesi negativi (ma non con cicli negativi), e prende in input una [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Matrice di adiacenza|matrice di adiacenza]]  $W$ di dimensioni $n\times n$, dove l'elemento $w_{ij}\in W$ rappresenta il peso dell'arco dal nodo $i$ al nodo $j$, in particolare i nodi sono **etichettati** da $1$ a $n$.

$$W_{i,j}=
\begin{cases}0&\text{se }i=j\\
w(i,j)&\text{se }i\neq j\text{ e }(i,j)\in E\\
+\infty&\text{se }i\neq j\text{ e }(i,j)\notin E
\end{cases}$$
Ad ogni iterazione l'algoritmo **crea** una matrice delle distanze $D$, anch'essa di dimensioni $n\times n$ e con elementi $d_{ij}$.
>Nell'ultima matrice prodotta varrà: $d_{i,j}=\delta(i,j)$.

```
Floyd-Warshall(W)
	n = rows(W)
	D^(0) = W
	for k = 1,...,n
		for i = 1,...,n
			for j = 1,...,n
				d^(k) [i][j] =
				min(d^(k-1) [i][j], d^(k-1) [i][k] + d^(k-1) [k][j])
	return D^(n)
```

### Complessità
$$T(n)=\Theta(n^3)$$

### Correttezza
Consideriamo i nodi $i,j,k\in V$, definiamo $\mathscr{D}_{ij}^k$ come l'insieme di cammini **semplici** da $i$ a $j$ che possiedono vertici **intermedi** $\leq k$:
$$\mathscr{D}_{i,j}^{(k)}=\{p\space|\space p\text{ è un cammino semplice da }i\text{ a }j \text{ con vertici intermedi}\leq k\}$$

dove per **nodi intermedi** si intendono i nodi presenti nel cammino da $i$ a $j$ con $i$ e $j$ esclusi.
>Questi dovranno essere $\leq k$ nella nostra definizione, tuttavia all'interno di $\mathscr{D}$ compariranno i cammini semplici interi compresi i nodi $i$ e $j$.

![[Nodi intermedi.svg]]
- $\mathscr{D}_{2,7}^{(1)}=\mathscr{D}_{2,7}^{(2)}=\mathscr{D}_{2,7}^{(3)}=\emptyset$
- $\mathscr{D}_{2,7}^{(4)}=\{<2,1,4,3,7>\}$
- $\mathscr{D}_{2,7}^{(5)}=\{<2,1,4,3,7>,<2,5,3,7>\}$

**Nota**: l'insieme $\mathscr{D}^{(k)}$ conterrà anche tutti i cammini di $\mathscr{D}^{(k-1)}$, abbiamo quindi che:
$$\forall k\quad\mathscr{D}_{i,j}^{(k-1)}\subseteq\mathscr{D}_{i,j}^{(k)}$$
e quando $k=n$, si avrà: $\mathscr{D}_{i,j}^{(k)}=\mathscr{D}_{i,j}$.

Quello che vogliamo calcolare con questo algoritmo è il peso del cammino minimo tra $i$ e $j$, cioè:
$$\delta(i,j)=\min_{p\in\mathscr{D}_{i,j}} w(p)$$

definiamo ora $d_{i,j}^(k)$ come il peso del cammino minimo tra $i$ e $j$ dove i valori dei vertici intermedi hanno valore $\leq k$, cioè:
$$d(i,j)=\min_{p\in\mathscr{D}_{i,j}} w(p)$$
dato che siamo riusciti a dimostrare che per $k=n$ vale che $\mathscr{D}_{i,j}^k=\mathscr{D}_{i,j}$, allora è anche vero che $\delta(i,j)=d_{i,j}^{(n)}$, che è l'elemento $i,j$-esimo dell'ultima matrice risultato prodotta.

