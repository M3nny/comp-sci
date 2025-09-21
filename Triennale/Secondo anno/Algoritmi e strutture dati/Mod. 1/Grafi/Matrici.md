Data la [[Triennale/Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Matrice di adiacenza|matrice di adiacenza]] $A=a_{ij}$ con $i,j\in V$:
$$\deg(i)=\sum_{j=1}^na_{ij}$$ovvero: <u>il grado di un nodo è dato sommando le righe o le colonne del nodo relativo</u> (per grafo non orientato, in quanto la sua matrice è simmetrica).

Consideriamo il seguente grafo:
![[GNO rombo 4.svg]]
la sua matrice di adiacenza $A$ risulta essere:
$$A=\begin{bmatrix}0&1&1&1\\1&0&1&0\\
1&1&0&1\\1&0&1&0\end{bmatrix}$$
oltre a notare che la proprietà precedentemente elencata risulta essere vera, se calcoliamo $A^2=A\times A$, otteniamo:
$$A^2=\begin{bmatrix}0&1&1&1\\1&0&1&0\\
1&1&0&1\\1&0&1&0\end{bmatrix}\times\begin{bmatrix}0&1&1&1\\1&0&1&0\\
1&1&0&1\\1&0&1&0\end{bmatrix}=\begin{bmatrix}3&1&2&1\\1&2&1&2\\
2&1&3&1\\1&2&1&2\end{bmatrix}$$
e osserviamo che $a_{ii}^{(2)}$ indica il **grado del nodo** $i$, mentre gli altri elementi indicano il **numero di cammini di lunghezza** $2$ tra $i$ e $j$, formalmente si può scrivere come:
$$a_{ij}^{(2)}=\begin{cases}\deg(i)&\text{se }i=j\\\text{numero di cammini di lunghezza 2 tra i e j}&\text{se }i\neq j\end{cases}$$

1. Dimostriamo che $A_{ii}=\deg(i)$:
dato che $A\times B = C$, e $c_{ij}=\sum\limits_{k=1}^na_{ik}\cdot b_{kj}$, si ha:
$$a_{ii}^{(2)}=\sum_{k=1}^na_{ik}\cdot a_{ki}=\sum_{k=1}^na_{ik}\cdot a_{ik}=\sum_{k=1}^na^2_{ik}=\sum_{k=1}^na_{ik}=\deg(i)$$
dove $a_{ik}^2=a_{ik}$ in quanto **la matrice è binaria**.

2. Dimostriamo che $a_{ij}$ è uguale al numero di cammini di lunghezza $2$ tra $i$ e $j$ $\forall i\neq j$:
$$a_{ij}^{(2)}=\sum_{\ell=1}^n a_{i\ell}\cdot a_{\ell j}$$
tale prodotto è uguale a $1$ sse $a_{i\ell}=1$, e $a_{\ell j}=1$ e i due archi $(i,\ell)$ e $(\ell, j)$ rappresentano effettivamente un cammino di lunghezza $2$ che va da $i$ a $j$.

**Generalizzazione**:
È possibile generalizzare questo concetto dicendo che: il prodotto di $k$ matrici di adiacenza $A^k$, ci da informazioni sul numero di cammini di lunghezza $k$ tra i nodi $i$ e $j$.
**Dimostrazione**:
Sia $A^k=\underbrace{A\times A\times ...\times A}_k=A^{k-1}\times A$ il prodotto di $k$ matrici di adiacenza per un certo grafo $G$

**Caso base**: $A^1=A$, infatti ci dice il numero di cammini di lunghezza $1$, ovvero gli archi tra $i$ e $j$
**Passo induttivo**: assumiamo che valga per $k-1$ e verifichiamolo per $k$, dato che $A^k=A^{k-1}\times A$ facciamo la stessa considerazione fatta nel caso $k=2$:
$$a_{ij}^{k}=\sum_{\ell=1}^n a_{i\ell}^{(k-1)}\cdot a_{\ell j}$$
dove $a_{i\ell}^{(k-1)}$ per ipotesi induttiva indica il numero di cammini di lunghezza $k-1$ tra $i$ e $\ell$, inoltre $a_{\ell, j}=1$ sse $(\ell, i)\in E$, e dunque la condizione è verificata.

Sulla diagonale principale inoltre sono rappresentati il **numero di cicli di lunghezza** $k$ che partono da $i$ ed arrivano a sè stesso, ma allo stesso tempo nei grafi <u>non orientati</u> rappresentano il **grado del nodo** $i$ (in caso di $A^2$) in quanto tutti gli archi di un nodo possono essere visti come un cammino di lunghezza $2$ dal nodo a sè stesso. 

---
## Grafi triangoli
Dato $G=(V,E)$ _non orientato_, che rappresenta $K_3$, ovvero un grafo completo con $3$ nodi, lo chiamiamo anche $C_3$ per indicare un grafo a forma di cerchio con $3$ nodi oppure **triangolo**.

Se esiste un $a_{ij}\cdot a_{ij}^{(2)}\neq 0$, allora si ha che il grafo contiene un triangolo, in parole più semplici: se $a_{ij}$ e $a_{ij}^{(2)}$ sono diversi da $0$, allora è presente un triangolo nel grafo.

Riprendiamo il concetto di [[Triennale/Primo anno/Primo semestre/Algebra lineare/Matrici#Traccia|traccia]] ($tr$) della matrice e notiamo che ha le seguenti proprietà all'interno di una matrice delle adiacenze $A$ in un grafo _non orientato_:
1. $tr(A)$ = $0$
2. $tr(A^2)$ = somma dei gradi dei nodi = $2|E|=2m$ (per lemma della stretta di mano)
3. $tr(A^3)$ = $6\cdot(\text{n. triangoli in }G)$

Spiegazione del terzo punto:
banalmente abbiamo $tr(A^3)=\sum\limits_{i=1}^n a_{ii}^{(3)}$, dove $a_{ii}^{(3)}$ indica il numero di cammini di lunghezza $3$, ma sotto un'ottica diversa rappresenta anche $2\cdot(\text{n. triangoli in }G\text{ incidenti ad }i)$, segue esempio:
![[Grafo triangolo.svg]]
e quindi se questo vale per un nodo, con tre nodi avremo: $3$ vertici $\cdot$ $2$ rotazioni = $6$.
