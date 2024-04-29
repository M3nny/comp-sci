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
Consideriamo i nodi $i,j,k\in V$, definiamo $\mathscr{D}_{ij}^{(k)}$ come l'insieme di cammini **semplici** da $i$ a $j$ che possiedono vertici **intermedi** $\leq k$:
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

definiamo ora $d_{i,j}^{(k)}$ come il peso del cammino minimo tra $i$ e $j$ dove i valori dei vertici intermedi hanno valore $\leq k$, cioè:
$$d(i,j)=\min_{p\in\mathscr{D}_{i,j}} w(p)$$
dato che siamo riusciti a dimostrare che per $k=n$ vale che $\mathscr{D}_{i,j}^{(k)}=\mathscr{D}_{i,j}$, allora è anche vero che $\delta(i,j)=d_{i,j}^{(n)}$, che è l'elemento $i,j$-esimo dell'ultima matrice risultato prodotta.

Per dimostrare la correttezza dell'algoritmo dobbiamo verificare la veridicità dell'uguaglianza all'interno dei cicli `for`, e per farlo ci avvaliamo del seguente **principio**:
	Sia $X$ un insieme, diviso in due partizioni $Y$ e $Z$, allora $\min X=\min\{\min Y,\min Z\}$.

ciò ci permette di applicare un algoritmo [[Teorema master#Divide et impera|divide et impera]] o, in questo caso di **programmazione dinamica** al problema dei cammini minimi.

![[Insieme cammini Floyd-Warshall.svg|500]]
dividiamo l'insieme dei cammini da $i$ a $j$ in due sottocammini:
- Quelli che passano per $k$
- Quelli che _non_ passano per $k$
poichè stiamo assumendo che **i cammini siano semplici**, non essendoci cicli siamo sicuri che $k$ non è compreso in nessuno dei due insiemi di sottocammini $\mathscr{D}_{i,k}^{(k-1)}$ e $\mathscr{D}_{k,j}^{(k-1)}$, e che tutti i vertici compresi in quei sottocammini abbiano valore $\leq k-1$.

Definiamo il seguente insieme:
$$\hat{\mathscr{D}}_{i,j}^{(k)}=\{p\space|\space p\in\mathscr{D}_{i,k}^{(k)} \text{ passanti per } k\}$$
quindi:
$$\mathscr{D}_{i,k}^{(k)}=\hat{\mathscr{D}}_{i,k}^{(k)}\cup\mathscr{D}_{i,k}^{(k-1)}$$
usando la definizione di $d_{i,j}^{(k)}$:
$$\begin{flalign}
d_{i,j}^{(k)}&=\min_{p\in\mathscr{D}_{i,j}^{(k)}}w(p)\\

&=\min \left\{\min_{p\in\hat{\mathscr{D}}_{i,j}^{(k)}} w(p),\min_{p\in\mathscr{D}_{i,j}^{(k-1)}} w(p)\right\}\\

&=\min \left\{\min_{p\in\mathscr{D}_{i,k}^{(k-1)}} w(p)+\min_{p\in\mathscr{D}_{k,j}^{(k-1)}} w(p),\space d_{i,j}^{(k-1)}\right\}\\
&=\min \left\{d_{i,k}^{(k-1)}+d_{k,j}^{(k-1)},\space d_{i,j}^{(k-1)}\right\}
\end{flalign}$$
verificando così l'uguaglianza all'intero dei cicli `for`.

### Ottimizzazione dello spazio
All'algoritmo servono solo _due matrici_:
- Quella che viene costruita nell'iterazione corrente
- Quella che viene costruita nell'iterazione precedente

È possibile limitare la complessità spaziale ad **una matrice** se valgono le seguenti condizioni:

##### Prima condizione
Se non esistono cicli negativi $\forall \ell=1,...,n$ tale che $d_{ii}^{(\ell)}=0\space\forall i=1,...,n$, ovvero se non esistono cicli negativi la diagonale principale sarà uguale a $0$.

**Dimostrazione** per induzione su $\ell$:
**Caso base**: per $\ell=0$ la condizione è verificata per definizione di $W$.
**Passo induttivo**: assumiamo per ipotesi induttiva che la proprietà valga fino a $\ell-1$ e lo dimostriamo per $\ell$.
$$d_{i,i}^{(\ell)}=\min\{\underbrace{d_{i,i}^{(\ell-1)}}_\text{=0 per ip. ind.},\space \underbrace{d_{i,\ell}^{(\ell-1)}+d_{\ell,i}^{(\ell-1)}}_{\geq 0\text{ perchè }\nexists\text{ cicli neg. }}\}=0$$
questo verifica la proprietà.
>Applicando l'algoritmo di **Floyd-Warshall** ad un grafo qualsiasi è possibile capire se ci sono cicli negativi verificando la presenza di valori negativi nella diagonale principale.

##### Seconda condizione
Presi due vertici $i,j\in V$ ed un ulteriore vertice $k\in V$, vale che:
$$\begin{cases}
d_{i,k}^{(k)}=d_{i,k}^{(k-1)}\\
d_{k,j}^{(k)}=d_{k,j}^{(k-1)}
\end{cases}$$
cioè la $k$-esima riga e la $k$-esima colonna restano inalterate tra la matrice $D^{(k)}$ e la matrice $D^{(k-1)}$.

**Dimostrazione** per definizione di $d_{i,k}^{(k)}$ sia ha che:
$$d_{i,k}^{(k)}=\min\{d_{i,k}^{(k-1)},d_{i,k}^{(k-1)}+d_{k,k}^{(k-1)}\}=d_{i,k}^{(k-1)}$$
questo perchè $d_{k,k}^{(k-1)}=0$ dato che si trova nella diagonale principale.

l'algoritmo riscritto risulterebbe essere:
```
Floyd-Warshall(W)
	n = rows(W)
	D = W
	for k = 1,...,n
		for i = 1,...,n
			for j = 1,...,n
				d[i][j] = min(d[i][j], d[i][k] + d[k][j])
	return D
```

La complessità temporale rimane invariata, ora però la **complessità spaziale** è quadratica: $S(n)=\Theta(n^2)$.

