Un elemento all'interno di una matrice $A$ si indica come $a_{ij}$ dove $i$ è la riga e $j$ è la colonna.
$$

A = \begin{bmatrix}

a_{11} & a_{12} & ... & a_{1j} \\

a_{21} & a_{22} & ... & a_{2j} \\

\vdots & \vdots & \ddots & \vdots \\

a_{i1} & a_{i2} & ... & a_{ij} \\

\end{bmatrix}

$$

Se una matrice è **quadrata**, può essere:
- Simmetrica se $a_{ij} = a_{ji}$
$$\begin{bmatrix} 3&-2&4\\-2&6&2\\4&2&3 \end{bmatrix}$$
- Diagonale se $a_{ij}=0$ per $i\neq j$:
$$\begin{bmatrix} x&0&0\\0&x&0\\0&0&x\end{bmatrix}$$
- Identica se $a_{ii} = 1$ ed il resto è a $0$:
$$\begin{bmatrix} 1&0&0\\0&1&0\\0&0&1\end{bmatrix}$$
- Triangolare (sup/inf):
$$\begin{bmatrix} x&0&0\\x&x&0\\x&x&x\end{bmatrix} \quad \text{oppure}\quad \begin{bmatrix} x&x&x\\0&x&x\\0&0&x\end{bmatrix}$$