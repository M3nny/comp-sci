## Permutazioni
- Le permutazioni (semplici) di un insieme di $n$ elementi distinti sono tutte le sequenze ordinate degli $n$ elementi.
- Se cambia l'ordine in compaiono gli elementi nelle sequenze allora le permutazioni si dicono diverse.

Il numero di permutazioni semplici di $n$ oggetti sono $n!$
$$P_n=n\cdot (n-1)\cdot (n-2) \cdot\cdot\cdot 2\cdot 1 = n!$$
>[!Example]
>Possibili anagrammi di CUORE
>5 modi di scrivere la prima lettera
>4 per la seconda
>...
>In totale ci sono $5! = 120$ possibili permutazioni.

## Combinazioni
Definiamo inoltre il numero di sottoinsiemi di $n$ elementi come $2^n$

Le combinazioni (semplici) di $n$ elementi a $k$ a $k$ sono tutti i possibili sottoinsiemi di $A$ aventi esattamente $k$ elementi, le possiamo trovare tramite:
$$\begin{pmatrix}n\\k\end{pmatrix} =\frac{n!}{k!(n-k)!}$$
- dove $n$ su $k$ è il coefficiente binomiale.

#### Proprietà
- $\begin{pmatrix}n\\k\end{pmatrix} = 0$ se $k>n$
- $\begin{pmatrix}n\\k\end{pmatrix} = \begin{pmatrix}n\\n-k\end{pmatrix}$
- $\begin{pmatrix}n\\n\end{pmatrix}=\begin{pmatrix}n\\0\end{pmatrix} = 1$
- $\begin{pmatrix}n\\1\end{pmatrix} = n$

## Disposizioni
Le disposizioni (semplici) di $n$ elementi a $k$ a $k$ sono tutti i possibili sottoinsiemi ordinati di $A$ aventi esattamente $k$ elementi diversi tra loro, anche le disposizioni come le permutazioni sono diverse tra loro se contengono elementi diversi oppure in ordine diverso.

Sono calcolabili tramite:
$$D_{n,k}=\frac{n!}{(n-k)!}$$

#### Proprietà
- $D_{n,0}=1$
- $D_{n,1}=n$
- $D_{n,n}=n!$ coincide con il numero di permutazioni
- $D_{n,m}=0$ per $m>n$
