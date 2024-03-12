Il problema della **Longest Common Subsequence (LCS)** consiste nel trovare la massima sottosequenza comune dei caratteri presenti in due stringhe.

Ci riferiamo alla **edit distance** come numero di operazioni da fare ad una stringa per renderla uguale all'altra.

Considerando delle sequenze di basi azotate:
$S_1=ACTACCTG$
$S_2=ATCACC$ 
risultano avere una edit distance pari a $4$, infatti:
1. Si inserisce una $C$ in seconda posizione in $S_2$
2. Si cancella la $C$ presente dopo la prima $T$ in $S_2$
3. Aggiungo in coda $T$ a $S_2$
4. Aggiungo in coda $G$ a $S_2$

otteniamo che due possibili $LCS$ sono $ACACC, ATACC$.

Una **sottosequenza** non deve avere obbligatoriamente caratteri consecutivi, ma devono apparire in ordine strettamente crescente rispetto alle posizioni della stringa originale.

Una **sottostringa** a differenza di una _sottosequenza_ possiede caratteri in ordine consecutivo rispetto alla stringa originale.

**Osservazioni**:
- Non vi è obbligatoriamente una singola $LCS$ di due sequenze
	e.g. $X=AC$, $Y=CA$ otteniamo le seguenti lcs: $(A, C)\in LCS$
	indichiamo con $LCS(X,Y)$ l'insieme delle $LCS$ di $X$ e $Y$ 
- Un algoritmo di brute-force potrebbe generare tutte le sottosequenze di $X$ verificando se sono sottosequenze anche di $Y$ e tenere traccia della più lunga, tuttavia le sottosequenze di $X=x_1,...,x_m$ sono $2^m$ in quanto ogni carattere potrebbe essere scelto o meno, portando ad una complessità $T(n)=O(2^m)$

### Caratterizzazione della sottostruttura ottima
Data $X=x_1,...,x_m$ per $k\leq m$, indichiamo con $X^k$ il **prefisso** di lunghezza $k$ di $X$, $X^k=x_1,...,x_k$.

>[!Example]
>$$X=ACG$$
>$$X^0=\epsilon,\quad X^1=A,\quad X^2=AC,\quad X^3=ACG$$

>Esistono sempre $m+1$ prefissi, in quanto si considera la sottosequenza vuota.

Se si riduce il problema $LCS$ di $X$ e $Y$ al problema sui prefissi, potranno essere generati $O(m\cdot n)$ sottoproblemi, quindi si avrà un ordine **polinomiale**, non più esponenziale.

**Sottostruttura ottima per $LCS$**:
Siano $X=x_1,...,x_m$ e $Y=y_1,...,y_n$ due sequenze e sia $W=w_1,...,w_k\in LCS(X,Y)$, allora:
1. Se $x_m=y_n$ allora $w_k=x_m=y_n$ e $W^{k-1}\in LCS(X^{m-1}, X^{n-1})$
2. Se $x_m\neq y_n$
	_2.1_  Se $w_k\neq x_m$ allora $W\in LCS(X^{m-1},Y)$
	_2.2_  Se $w_k\neq y_m$ allora $W\in LCS(X,Y^{n-1})$

![[Sottostruttura LCS.svg]]
#### Soluzione ricorsiva per il valore della soluzione ottima
Dati $X=x_1,...,x_m$ e $Y=y_1,...,y_n$, indichiamo con $c[i,j]$ la lunghezza delle sottosequenze appartenenti a $LCS(X^i,Y^j)$, con $0\leq i\leq m$ e $0\leq j\leq n$.
$$c[i,j]=
\begin{cases}
0&\text{se }i=0\lor j=0\\
c[i-1,j-1]+1&\text{se }i,j>0\land x_i=y_j\\
\max(c[i-1,j],c[i,j-1])&\text{se }i,j>0\land x_i\neq y_j
\end{cases}
$$
Un ulteriore esempio è il seguente:
- $X=ABACA$
- $Y=ACDA$
Inizialmente si ha $c[5,4]$, notiamo che l'ultimo carattere è uguale quindi:
$c[5,4]=c[4,3]+1$, successivamente confrontiamo gli ultimi caratteri rimanenti, ovvero $C\neq D$, quindi eseguiamo il passo ricorsivo $\max(c[3,3], c[4,2])$.

### Bottom-up
Consideriamo le seguenti due matrici in pseudocodice $b[1,...,m][1,...,n]$ e $c[0,...,m][0,...,n]$ ed indicheremo gli indici `c[i][j]` e `b[i][j]` che contengono:
- $c[i,j]$ lunghezza delle $LCS(X^i,Y^j)$
- $b[i,j]$ informazioni utili a recuperare la soluzione:
	- $b[i,j]=\nwarrow$ se $x_i=y_j$, quindi $LCS(X^i,Y^j)$ si riduce a $LCS(X^{i-1},Y^{j-1})$
	- $b[i,j]=\uparrow$ se $x_i\neq y_j$, quindi $LCS(X^i,Y^j)$ si riduce a $LCS(X^{i-1},Y^j)$
	- $b[i,j]=\leftarrow$ se $x_i\neq y_j$, quindi $LCS(X^i,Y^j)$ si riduce a $LCS(X^i,Y^{j-1})$

```
LCS(X, Y)
	m = X.length
	n = Y.length
	
	for i = 0 to m // inizializza la prima colonna a 0
		c[i, 0] = 0
		
	for j = 0 to n // inizializza la prima riga a 0
		c[0, j] = 0
	
	for i = 0 to m
		for j = 1 to n
			if x[i] == Y[j]
				c[i, j] = c[i-1, j-1] + 1
				b[i, j] = ↖
			else if c[i-1, j] >= c[i, j-1]
				c[i, j] = c[i-1, j]
				b[i, j] = ↑
			else
				c[i, j] = c[i, j-1]
				b[i, j] = ←
	return b, c
```

Considerando le due stringhe: $X=AC$ e $Y=BA$ si otterranno le seguenti matrici $c$ e $b$, per comodità qui sotto appaiono sovrapposte, $c$ contiene le lunghezze delle $LCS$ e comprende la riga e colonna con la stringa vuota, mentre $b$ contiene i riferimenti (frecce) e non contiene la stringa vuota.

| $X$ \ $Y$  | $\epsilon$ |     $B$     |     $A$     |
|:----------:|:----------:|:-----------:|:-----------:|
| $\epsilon$ |    $0$     |     $0$     |     $0$     |
|    $B$     |    $0$     | $0\uparrow$ | $1\nwarrow$ |
|    $A$     |    $0$     | $0\uparrow$ | $1\uparrow$ |

La **complessità** è data dai due cicli for annidati:
$$T(n)=\Theta(m\cdot n)$$

Al momento nella cella $c[m, n]$ è presente la lunghezza della $LCS$, però non sappiamo ancora quali sono i caratteri a formarla, usiamo quindi la funzione `printLCS` la quale utilizza `printLCSaux` passando solo $X$ in quanto stiamo considerando solo i caratteri comuni (andava bene anche $Y$ adattato opportunamente).

```
printLCS(X, Y)
	b, c = LCS(X, Y)
	printLCSaux(X, b, X.length, Y.length)

printLCSaux(X, b, i, j)
	if i > 0 and j > 0
		if b[i, j] = ↖ // carattere comune alle due sottosequenze
			printLCSaux(X, b, i-1, j-1)
			print(X[i])
		else if b[i, j] == ↑
			printLCSaux(X, b, i-1, j)
		else
			printLCSaux(X, b, i, j-1)
```

Ad ogni iterazione (chiamata) o $i$ o $j$ (o entrambi) vengono diminuiti quindi la complessità di `printLCS` è data da:
$$T(n)=\Theta(m\cdot n)+O(m+n)=\Theta(m\cdot n)$$
è possibile **ottimizzare** l'algoritmo di stampa evitando di usare $b$ in quanto per determinare $c[i,j]$ vengono usati solo tre valori:
- $c[i-1,j-1]$
- $c[i-1,j]$
- $c[i,j-1]$
e confrontandoli, <u>facendo attenzione all'ordine</u>, è possibile capire come è stata ottenuta la sequenza ottima.

```
printLCSaux(X, b, i, j)
	if i > 0 and j > 0
		if c[i, j] == c[i-1 ,j]
			printLCSaux(x, c, i-1, j)
		else if c[i, j] == c[i, j-1]
			printLCSaux(x, c, i, j-1)
		else
			printLCSaux(x, c, i-1, j-1)
			print(X[i])
```

**Osservazione**: se sono interessato solo alla lunghezza della $LCS$, posso evitare di mantenere tutta la tabella $c$ dato che posso calcolare la riga $i+1$ utilizzando solo la riga $i$, si può dunque utilizzare come spazio (e.g. di un vettore), il minimo tra $m$ ed $n$ posizioni più uno spazio costante aggiuntivo. 
### Top-down
```
tdLCS(X, Y)
	m = X.length
	n = Y.length
	c[0...m, 0...n] = -1 // inizializzo a -1 la matrice (Theta(m*n))
	return tdLCSaux(X, Y, c, m, n)

tdLCSaux(X, Y, c, i, j)
	if c[i, j] == -1
		if i == 0 or j == 0
			c[i, j] = 0
		else if X[i] == Y[j]
			c[i, j] = tdLCSaux(X, Y, c, i-1, j-1) + 1
		else
			c[i, j] = max(tdLCSaux(X, Y, c, i-1, j), tdLCSaux(X, Y, c, i, j-1)
	return c[i, j]
```
