Una strategia per implementare il **clustering gerarchico** può essere l'utilizzo di una **matrice di distanza/similarità**, immaginando di avere una matrice di distanza $D$, l'elemento $D[i,j]$ indica la distanza tra l'oggetto $i$ e l'oggetto $j$.
>Questo metodo non richiede la conoscenza del numero di cluster in partenza.

## Clustering gerarchico agglomerativo
Il clustering gerarchico **agglomerativo** (HAC) utilizza un approccio [[Approccio dinamico#Top-down o Bottom-up?|bottom-up]], ovvero inizialmente ogni oggetto rappresenta un cluster, essi sono poi uniti finchè un singolo cluster non diventa la radice della gerarchia.
![[Clustering gerarchico agglomerativo.png]]

>[!Tip] HAC algorithm
>// _Inizializza ogni punto come un cluster_
>**for** $i=1\ldots |{\cal D}|$:
>$\quad$ $C_i = \{o_i\}$
>
>// _Insieme di cluster_
>$\cal C = \bigcup\limits_i \{C_i\}$ 
>
>// _Loop di aggregazione_
>**while** $|{\cal C}|>1$:
>$\quad$ // _Trova la coppia di cluster più vicina_
>$\quad$ $C_i, C_j = \arg\min\limits_{C_x, C_y} D(C_x, C_y)$
>$\quad$ // _Rimpiazza_ $C_i$ _e_ $C_j$ _con la loro unione_
>
>$\quad$ $C_{new} = C_i\cup C_j$
>$\quad$ ${\cal C} = (({\cal C} \setminus \{C_i\}) \setminus \{C_j\}) \cup \{C_{new}\}$

Gli elementi iniziali in $D$ rappresentano la distanza tra l'oggetto $i$ e $j$

Quando si sta unendo $C_i$ con $C_j$ (con $i<j$):
- La riga e colonna corrispondente al cluster $C_j$ vengono invalidate ponendole a $+\infty$
- La riga e colonna corrispondente al cluster $C_i$ sono usate per il nuovo cluster $C_{new}$, ovvero $D[i,k]=sim(C_{new}, C_k)$ e $D[k,i]=sim(C_k,C_{new})$

>Se la matrice è di **similarità** (non di distanza), essa sarà simmetrica, quindi è possibile utilizzare solo la metà dello spazio.

I cluster possono anche terminare quando viene raggiunto un criterio di stop:
- $K$ cluster sono stati creati
- I cluster sono meno simili di un certo threshold

## Clustering gerarchico divisivo
Il clustering gerarchico **divisivo**, a differenza di quello _agglomerativo_, utilizza un approccio [[Approccio dinamico#Top-down o Bottom-up?|top-down]], ovvero inizialmente tutti gli oggetti fanno parte di un cluster il quale è ricorsivamente diviso in cluster più piccoli.

### Linkage measures
Di seguito sono elencate delle **misure di similarità** tra cluster tipiche.

|     Nome     |    Tipo di distanza    |                                   Definizione                                    |                                         Nota                                         |
| :----------: | :--------------------: | :------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------: |
|  **Single**  |    Distanza minima     |             $dist(C_i,C_j)=\min\limits_{x\in C_i,y\in C_j}dist(x,y)$             |                         Potrebbe sovrastimare la similarità                          |
| **Complete** |    Distanza massima    |             $dist(C_i,C_j)=\max\limits_{x\in C_i,y\in C_j}dist(x,y)$             |                         Potrebbe sottostimare la similarità                          |
| **Average**  |     Distanza media     | $dist(C_i,C_j)=\frac{1}{\|C_i\|\|C_j\|}\sum\limits_{x\in C_i,y\in C_j}dist(x,y)$ |                   È una via di mezzo tra le due misure precedenti                    |
| **Centroid** | Distanza tra centroidi |                          $dist(C_i,C_j)=dist(o_i,o_j)$                           |                      È molto veloce rispetto alle altre misure                       |
|   **Ward**   |           -            |                                        -                                         | Misura l'incremento della SSE rispetto ai centroidi quando vengono uniti due cluster |

![[Distance measures.png|600]]

**Algoritmo per single linkage**
```
M = matrice delle distanze (N x N)
V = lista di coppie (distanza - id colonna matrice)
for each i in M:
	Trova la distanza minore in V
	Aggiorna in M le distanze tra il nuovo cluster e gli altri
	Aggiorna le distanze memorizzate in V
```
$$O(n^2)+O(n\cdot 3n)=O(n^2)$$

È possibile osservare infine tramite un **dendrogramma** i raggruppamenti tra i vari cluster:
![[Dendrogramma.png]]
