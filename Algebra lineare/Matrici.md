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
Considerando la matrice $A=(a_{ij})\space m\times n$, la **matrice trasposta** sarà $n\times m \space B=(b_{ji})$, praticamente le righe diventano colonne e viceversa.
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

---
## Matrici elementari
Sono definite per interpretare le mosse di Gauss e sono di tre tipi:
1. **Scambio di righe**;
2. **Moltiplicazione di una riga per uno scalare**;
3. **Combinazione lineare**, ovvero aggiungere ad una riga un'altra riga moltiplicata per uno scalare.
==Tutte le matrici elementari sono invertibili==.

---
## Determinante
Può essere calcolato se la matrice è quadrata, esso è un numero reale.
#### Matrice 2x2:
$$det(A)=(a_{11}\cdot a_{22})- (a_{12}\cdot a_{21})$$
- Se 2 colonne sono uguali, allora $det = 0$.
- Il determinante di una matrice Identica è $det = 1$.
- Due matrici sono linearmente indipendenti _se e solo se_ $det = 0$.

#### Matrice 3x3
Il determinante in questo caso va calcolato con la **regola di Sarrus**:
![[Sarrus.png]]
>[!Example]
>$$A = \begin{bmatrix}1&2&3\\1&1&-1\\2&0&5\end{bmatrix}$$
>$|A| = (1\cdot 1\cdot 5) + (2\cdot -1\cdot 2)+(3\cdot 1\cdot 0) - (2\cdot 1\cdot 3) - (0\cdot -1\cdot 1) - (5\cdot 1\cdot 2)$

## Minore di una matrice
Il **minore** di una matrice è dato dal determinante della sottomatrice ricavata togliendo l'intera riga e colonna appartenenti ad un elemento

>[!Example]
>$$A = \begin{bmatrix}1&3&2\\4&1&3\\2&5&2\end{bmatrix}$$
>Se voglio trovare il minore dell'elemento $a_{21}$ dovrò per prima cosa togliere la riga 2 e colonna 1, ottenendo la sottomatrice:
>$$\begin{bmatrix}3&2\\5&2\end{bmatrix}$$
>ora calcolo il determinante: $3\cdot 2 - 2\cdot 5 = -4$
>
>Per ottenere la **matrice dei minori**, dovrò fare questo passaggio per ogni elemento della matrice, ottenendo quindi:
>$$\text{matrice dei minori} = \begin{bmatrix}-13&2&18\\-4&-2&-1\\7&-5&-11 \end{bmatrix}$$

## Matrice dei cofattori
La **matrice dei cofattori**(o matrice dei complementi algebrici) si ricava procedendo per ogni elemento nel seguente modo: $\text{minore}(a)\cdot (-1)^{i+j}$ 
>[!Example]
>Continuando con la matrice dell'esempio precedente, il cofattore dell'elemento $a_{1,1}$ sarà: $-13\cdot (-1)^{1+1} = -13$.
>
>Procedendo in questo modo per ogni elemento otterremo:
>$$\begin{bmatrix}-13&-2&18\\4&-2&1\\7&5&-11 \end{bmatrix}$$

Posso inoltre calcolare il determinante della matrice sfruttando la matrice dei cofattori in questo modo:
$$det(A) = \sum_{j=1}^n a_{ij}\cdot C_{ij}$$

---
## Matrici inverse
Una matrice quadrata $A$ di ordine $n$ è detta invertibile se il prodotto $A\cdot A^{-1}$ restituisce una matrice identità di ordine $n$.

La posso calcolare solo se il $det(A) \neq 0$ tramite:
$$A^{-1} = \frac{1}{det(A)}\cdot C^T$$

## Matrici a scala
Sono matrici dove il primo valore non nullo di una riga si trova dopo il valore non nullo della riga precedente:
$$\begin{bmatrix} 0 & 1 & 5 & 0 & 3 & 1\\ 0 & 0 & 9 & 2 & 5 & 2\\ 0 & 0 & 0 & 0 & 5 & 6\\ 0 & 0 & 0 & 0 & 0 & 1 \end{bmatrix}$$

### Forma ridotta
In questo tipo particolare di matrice a scala:
- Il primo elemento non nullo di ogni riga deve essere $1$;
- Ci deve essere al massimo un $1$ per colonna e se presente non devono esserci altri numeri;
- Le colonne senza $1$ possono avere i valori che vogliono.
$$\begin{bmatrix} 1 & 0 & 0 & 0 & 0 & 7\\ 0 & 1 & 0 & 0 & 0 & 2\\ 0 & 0 & 0 & 1 & 0 & 6\\ 0 & 0 & 0 & 0 & 1 & 0\\ 0 & 0 & 0 & 0 & 0 & 0\ \end{bmatrix}$$

Per trasformare una matrice a scala in una matrice ridotta:
- Si prende la prima riga non nulla;
- Si divide la riga per il suo primo elemento a sinistra;
- Si procede per ogni riga.