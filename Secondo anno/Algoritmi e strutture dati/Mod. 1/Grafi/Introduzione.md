Un **grafo** è una rappresentazione del concetto matematico di relazione.
Viene indicato come:
$$G=(\underbrace{V}_{\text{Vertici | Vertices }}, \overbrace{E}^{\text{Archi | Edges}})$$
dove $V$ è un insieme di vertici, ed $E$ è un insieme di archi.
### Grafi orientati
In questo tipo di grafo, gli <u>archi sono orientati</u> e $E\subseteq V\times V =V^2$, ovvero $|E|=|V|^2=n^2$ è un insieme di coppie ordinate di nodi.
- $V=\{1,2,3,4\}$
- $E=\{(1,2),(1,4),(2,2),(2,3),(3,1),(3,4),(4,2),(4,3)\}$
![[Grafo orientato.svg]]
### Grafi non orientati
In questo tipo di grafo, gli <u>archi non sono orientati</u>, inoltre valgono le seguenti proprietà:
- **Simmetria**: $(i,j)\in E\iff(j,i)\in E\quad\forall i,j\in V$
	Se c'è $(0,1)$, allora c'è anche $(1,0)$ e viceversa.
- **Non riflessività**: $\forall i\in V,(i,i)\notin E$ 
	Non esistono **cappi** (e.g. $(1,1)$)

inoltre dato $G=(V,E)$ si ha $E\subseteq \binom{V}{2}$, questo prende il significato di "tutti gli insiemi di $2$ elementi costruiti su $V$".
e.g. $V=\{1,2,3\}\implies \binom{V}{2}=\{\{1,2\},\{1,3\},\{2,3\}\}$.

Viene usato il simbolo del [[Probabilità elementare#Combinazioni|coefficiente binomiale]] in quanto:
$$\left|\binom{V}{2}\right|=\binom{|V|}{2}=\binom{n}{2}=\frac{n(n-1)}{2}$$
