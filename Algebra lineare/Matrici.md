Un elemento all'interno di una matrice $A$ si indica come $a_{ij}$ dove $i$ è la riga e $j$ è la colonna.
$$

A = \begin{bmatrix}

a_{11} & a_{12} & ... & a_{1j} \\

a_{21} & a_{22} & ... & a_{2j} \\

\vdots & \vdots & \ddots & \vdots \\

a_{i1} & a_{i2} & ... & a_{ij} \\

\end{bmatrix}

$$
- **vettore riga** di $A$: $A_i=\begin{bmatrix} a_{i1}, a_{i2}, ..., a_{ij}\end{bmatrix}$ è definito come una matrice $1 \times n$
- **vettore colonna** di $A: A_j=\begin{bmatrix} a_{1j}\\ a_{2j}\\ \vdots \\ a_{ij}\end{bmatrix}$  è definito come una matrice $n\times 1$
Chiamiamo poi un elemento $a_{ij}$ **termine o componente**.
>[!Example]
>$$\begin{bmatrix} 1 & 1 & -2\\ -1 & 4 & -5\end{bmatrix}$$
>Ha dimensione $2\times 3$ 
>Otteniamo inoltre 2 vettori riga e 3 vettori colonna.

Indichiamo con $O$ la **matrice zero**, ovvero con tutti gli elementi pari a $0$, dove: $O + A = A + O = A$ 

## Operazioni tra matrici

### Addizione
L'addizione tra matrici avviene solo se hanno la stessa dimensione, nel caso contrario si potrebbe procedere aggiungendo zeri a quella più piccola (padding).
>[!Example]
>$$A=\begin{bmatrix} 1 & -1 & 0\\ 2 & 3 & 4\end{bmatrix} \quad B=\begin{bmatrix} 5 & 1 & -1\\ 2 & 1 & -1\end{bmatrix}$$
>$$A+B=\begin{bmatrix} 6 & 0 & -1\\ 4 & 4 & 3\end{bmatrix}$$

### Trasposizione
Considerando la matrice $A=(a_{ij})\space m\times n$, la **matrice trasposta** sarà $n\times n \space B=(b_{ji})$ 
>[!Example]
>$$A=\begin{bmatrix}2 & 1 & 0\\1& 3 & 5\end{bmatrix} \quad A^t=\begin{bmatrix} 2 & 1\\1 & 3\\ 0&5\end{bmatrix}$$

Da notare che $(A^t)^t=A$ 

## Matrice quadrata
Una matrice è quadrata quando è di dimensioni $n\times n$ e il determinante è $\neq 0$.
Vediamo ora le operazioni che possiamo eseguire e i tipi di matrice quadrata:

### Simmetrica
Se $a_{ij} = a_{ji}$
$$\begin{bmatrix} 3&-2&4\\-2&6&2\\4&2&3 \end{bmatrix}$$
### Diagonale
Se $a_{ij}=0$ per $i\neq j$:
$$\begin{bmatrix} x&0&0\\0&x&0\\0&0&x\end{bmatrix}$$
### Identica
Se $a_{ii} = 1$ ed il resto è a $0$:
$$\begin{bmatrix} 1&0&0\\0&1&0\\0&0&1\end{bmatrix}$$
### Triangolare (sup/inf):
$$\begin{bmatrix} x&0&0\\x&x&0\\x&x&x\end{bmatrix} \quad \text{oppure}\quad \begin{bmatrix} x&x&x\\0&x&x\\0&0&x\end{bmatrix}$$
### Traccia
La traccia della matrice è la somma dei valori nella sua diagonale principale, può essere scritta come:
$$\sum_{i=1}^na_{ii}$$
### Prodotto
Se voglio fare il prodotto tra due matrici devo assicurarmi che le **colonne della prima siano uguali alle righe della seconda**.
Ad esempio si potrebbe fare il prodotto tra $A (m\times n)$ e $B(n\times s$).
Andremo poi ad ottenere dal prodotto, una matrice $m\times s$

Possiamo scrivere il prodotto tra due matrici come:

>[!Example]
>$$A=\begin{bmatrix} 2&1&5\\1&3&2 \end{bmatrix} \quad B=\begin{bmatrix} 3&4\\-1&2\\2&1 \end{bmatrix}$$
>Il prodotto $A\cdot B$ sarà di dimensioni $2\times 2$
>Procedo moltiplicando:
>- $1^a$ riga $1^a$ colonna;
>- $1^a$ riga $2^a$ colonna;
>- $2^a$ riga $1^a$ colonna;
>- $2^a$ riga $2^a$ colonna;
>
>Ottengo:
>$$A\cdot B=\begin{bmatrix} 15&15\\4&12 \end{bmatrix}$$

#### Proprietà del prodotto
- Il prodotto tra matrici è associativo: $A(BC)=(AB)C$;
- Ammette l'elemento neutro, ovvero la matrice identica $I$, quindi: $IA=AI=A$;
- Distributiva rispetto la somma: $A(B+C)=(AB)+(AC)$;
- Se $A$ e $B$ si possono moltiplicare, allora $(AB)^t=B^tA^t$.
>[!Attention]
>Il prodotto **non è** commutativo: $AB \neq BA$

## Vettori come matrici
I vettori posso essere suddivisi in:
- Matrici riga;
- Matrici colonna;

Il prodotto tra vettori deve sempre essere del tipo m.riga x m.colonna, dato che solo in questo caso si potrà avere il prodotto in quanto le colonne del primo sono uguali alle righe del secondo.

Nel caso dovessi avere due vettori colonna, per moltiplicarli dovrò prima fare la matrice trasposta.
>[!Example]
>a=v.colonna $nx1$
>b=v.colonna $nx1$
>Per moltiplicarli dovrò fare:
>$$a^t\cdot b$$
>Il quale risultato sarà **1 singolo valore**.
