Un **Grafo** è composto da **Nodi**(o vertici) e **Archi**(o edges) e viene indicato come segue:
$$G=(V,E)$$
Dove $V$ è un insieme finito di nodi: $V=\{V_1,V_2,...,V_n\}$, 
mentre $E$ è un insieme finito di archi: $E = \{E_1,E_2,...,E_n\}$.

Indichiamo con **cammino** di un grafo una sequenza di nodi e possiamo andare a rappresentarlo in una **matrice di adiacenza** che segue la seguente proprietà:
$$A_{ij}=\begin{cases}
	1 & \text{se } (V_i,V_j)\in E\\
	0 & \text{altrimenti}
\end{cases}$$
>[!Example]
>Consideriamo il grafo:
>![[Grafo.svg]]
>Ha cardinalità $|V| = 5$, quindi voglio creare una matrice di adiacenza $5\times 5$
>
| **0** | **1** | 1   | 0   | 0   |  $\sum 2$   | 
| ----- | ----- | --- | --- | --- | --- |
| 1     | 0     | 1   | 1   | 0   |   $\sum 3$  |
| 1     | 1     | 0   | 1   | 0   |   $\sum 3$  |
| 0     | 1     | 1   | 0   | 1   |   $\sum 3$  |
| 0     | 0     | 0   | 1   | 0   |   $\sum 1$  |
>
>- La diagonale è $0$ perchè nessun nodo viene connesso a se stesso;
>- Individuiamo con **degree** ($\sum$) il numero di connessioni con altri nodi;
>- Se il grafo non è orientato come in questo caso, la matrice di adiacenza sarà simmetrica.

Posso calcolare il numero di cammini di lunghezza $x$ da $y$ a $z$ tramite le potenze:
$$A^x_{y,z}$$
Tenendo in considerazione l'esempio precedente, se volessi calcolare il numero di cammini di lunghezza $2$ dal nodo $1$ al nodo $4$ procederei così: $$A^2_{1,4} = 0+1+1+0+0=2$$
Vado così a moltiplicare m.riga $1$ con m.colonna $4$.
