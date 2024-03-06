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

#### Caratterizzazione della sottostruttura ottima
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
