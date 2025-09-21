Un **grafo** è una rappresentazione del concetto matematico di relazione.
Viene indicato come:
$$G=(\underbrace{V}_{\text{Vertici | Vertices }}, \overbrace{E}^{\text{Archi | Edges}})$$
dove $V$ è un insieme di vertici, ed $E$ è un insieme di archi (coppie di nodi).

>D'ora in poi useremo questa notazione per la cardinalità di $V$ e $E$:
>$|V|=n$
>$|E|=m$

### Grafi orientati
In questo tipo di grafo, gli <u>archi sono orientati</u> e $E\subseteq V\times V =V^2$.
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
- $V=\{1,2,3,4\}$
- $E=\{(1,2),(2,3),(3,1),(3,4)\}$
![[Grafo non orientato.svg]]
---
## Cardinalità degli archi
**Numero di archi**:
- Orientato: $|E|=|V|^2=n^2$
- Non orientato: $|E|=\left|\binom{V}{2}\right|=\frac{n(n-1)}{2}$

Un grafo si dice:
- **Sparso**: se $m\simeq n$, ovvero tanti archi quanti nodi
- **Denso**: se il numero di archi è massimo

#### Densità
La **densità** viene calcolata come segue:
$$\delta(G)=\frac{|E|}{(\text{max n° possibile di archi})}$$
per i **grafi orientati**:
$$\delta(G)=\frac{|E|}{|V|^2}=\frac{m}{n^2}$$
per i **grafi non orientati**:
$$\delta(G)=\frac{|E|}{|\binom{V}{2}|}=\frac{m}{\frac{n(n-1)}{2}}=\frac{2m}{n(n-1)}$$
in generale vale:
$$\underbrace{0}_{\text{Grafo vuoto}}\leq\delta(G)\leq\underbrace{1}_{\text{Grafo completo}}$$
Un **grafo vuoto** è _senza archi_, mentre un **grafo completo** ha il _numero massimo di archi_.

---
## Rappresentazione dei grafi
Possiamo rappresentare in memoria i grafi in tre modi principali:
1. Lista di adiacenza
2. Matrice di adiacenza
3. Matrice di incidenza

- **Adiacenza**: due nodi si dicono adiacenti se sono collegati da un arco
- **Incidenza**: un arco che collega due nodi è incidente ai due nodi

### Lista di adiacenza
Consiste in una **lista di liste** $n+m$.
Occupa **poco spazio**, però è **inefficiente**, viene usata per **grafi sparsi** che quindi hanno pochi archi rendendo le liste corte.
![[Lista di adiacenza.svg]]
Nel caso di un grafo **non orientato**, gli archi verranno memorizzati due volte (prima in un senso e poi nell'altro).

### Matrice di adiacenza
Consiste in una **matrice binaria quadrata** $n\times n$ che segue la seguente logica:
$$a_{ij}=\begin{cases}1&(i,j)\in E\\0&(i,j)\notin E\end{cases}$$
Anche in presenza di grafi sparsi occupa **tanto spazio** però è **efficiente** in quanto l'accesso è costante, quindi se ne trae vantaggio con **grafi densi**.
considerando il grafo precedente si ha:

| $i$ \ $j$ |  1  |  2  |  3  |  4  |
|:---------:|:---:|:---:|:---:|:---:|
|   **1**   |  0  |  1  |  1  |  1  |
|   **2**   |  0  |  1  |  1  |  0  |
|   **3**   |  0  |  1  |  0  |  1  |
|   **4**   |  1  |  0  |  0  |  0  |

Nel caso di un grafo **non orientato**, la matrice sarebbe [[Triennale/Primo anno/Primo semestre/Algebra lineare/Matrici#Matrice quadrata#Simmetrica|simmetrica]], ovvero $A^T=A$, inoltre la diagonale principale sarebbe pari a $0$ in quanto non ci sono cappi.

### Matrice di incidenza
Consiste in una **matrice a "3-vie"** $n\times m$ che segue la seguente logica:
$$a_{ij}=\begin{cases}-1&\text{arco uscente}\\0&\text{arco assente}\\1&\text{arco entrante}\end{cases}$$
Solitamente viene utilizzata questa rappresentazione quando non ci sono cappi.

considerando il seguente grafo:
![[Grafo per matrice incidenza.svg]]
la sua matrice di incidenza risulta essere:

| $i$ \ $j$ | (1,2) | (1,4) | (3,1) | (3,2) | (3,4) | (4,1) |
|:---------:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|   **1**   |  -1   |  -1   |   1   |   0   |   0   |   1   |
|   **2**   |   1   |   0   |   0   |   1   |   0   |   0   |
|   **3**   |   0   |   0   |  -1   |  -1   |  -1   |   0   |
|   **4**   |   0   |   1   |   0   |   0   |   1   |  -1   |

Nel caso di un **non orientato** si utilizzerà solo $1$ e $0$ per indicare i nodi coinvolti.

---
## Cammini
Dato un grafo $G=(V,E)$ e due nodi $u,v\in E$, un **cammino** tra $u$ e $v$ è una sequenza di vertici $<x_0,...,x_q>\in V$, quindi:
$$\begin{cases}x_0=u\\x_q=v\\(x_i,x_{i+1})\in E&\forall i=0,...,q-1\end{cases}$$

la **lunghezza del cammino** rappresenta il <u>numero di archi del cammino</u>.
I cammini inoltre possono essere di due tipi:
- **Semplici**: una volta visitato un nodo, non si ritorna più su di esso
- **Non semplici**: un nodo viene visitato più volte

Un **ciclo** è un cammino dove $x_0=x_q$, inoltre per avere un ciclo in un grafo **non orientato**, ci devono essere almeno $3$ vertici.
