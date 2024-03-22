Un **grafo** è una rappresentazione del concetto matematico di relazione.
Viene indicato come:
$$G=(\underbrace{V}_{\text{Vertici | Vertices }}, \overbrace{E}^{\text{Archi | Edges}})$$
dove $V$ è un insieme di vertici, ed $E$ è un insieme di archi (coppie di nodi).

>D'ora in poi useremo questa notazione per la cardinalità di $V$ e $E$:
>$|V|=n$
>$|E|=m$

## Grafi orientati
In questo tipo di grafo, gli <u>archi sono orientati</u> e $E\subseteq V\times V =V^2$.
- $V=\{1,2,3,4\}$
- $E=\{(1,2),(1,4),(2,2),(2,3),(3,1),(3,4),(4,2),(4,3)\}$
![[Grafo orientato.svg]]
## Grafi non orientati
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
## Proprietà
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

Nel caso di un grafo **non orientato**, la matrice sarebbe [[Matrici#Matrice quadrata#Simmetrica|simmetrica]], ovvero $A^T=A$, inoltre la diagonale principale sarebbe pari a $0$ in quanto non ci sono cappi.

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
### Grafi pesati
È possibile aggiungere delle informazioni sui vertici e/o archi di un grafo, questa informazione $W:E\to\mathbb{R}$ viene chiamata **peso**, rappresentato un numero reale, il quale significato dipende dalla realtà di riferimento.
- $G=(V,E,W)$ rappresenta un grafo pesato sui vertici o sugli archi
- $G=(V,E,W_1,W_2)$ rappresenta un grafo pesato sui vertici e sugli archi.

---
### Sottografi
Dato un grafo $G=(V,E)$, un **sottografo** $G'=(V',E')$ è definito come:
$$\begin{cases}V'\subseteq V\\E'\boldsymbol\subseteq E\cap V'\times V'\end{cases}$$
ovvero: i vertici sono un sottoinsieme di quelli originali, e gli archi presenti sono **al massimo** archi che collegano i vertici del sottografo.
![[Sottografi.svg]]

### Sottografi indotti
Dato un grafo $G=(V,E)$, un **sottografo indotto** $G[V']=(V',E')$ è definito come:
$$\begin{cases}V'\subseteq V\\E'\boldsymbol= E\cap V'\times V'\end{cases}$$
a differenza dei sottografi, gli archi presenti sono **tutti** quelli riguardanti solo e soltanto i vertici coinvolti.

Considerando il grafo originale precedente:
![[Sottografo indotto.svg]]

---
### Cammini
Dato un grafo $G=(V,E)$ e due nodi $u,v\in E$, un **cammino** tra $u$ e $v$ è una sequenza di vertici $<x_0,...,x_q>\in V$, quindi:
$$\begin{cases}x_0=u\\x_q=v\\(x_i,x_{i+1})\in E&\forall i=0,...,q-1\end{cases}$$

la **lunghezza del cammino** rappresenta il <u>numero di archi del cammino</u>.
I cammini inoltre possono essere di due tipi:
- **Semplici**: una volta visitato un nodo, non si ritorna più su di esso
- **Non semplici**: un nodo viene visitato più volte

Un **ciclo** è una cammino dove $x_0=x_q$, inoltre per avere un ciclo in un grafo **non orientato**, ci devono essere almeno $3$ vertici.

Un grafo viene definito:
- **Aciclico (o foresta)** se non presenta cicli
- **Connesso**: se presi due qualsiasi nodi esiste un cammino che li collega
- **Albero libero**: se è _aciclico_ e _connesso_, questo garantisce le seguenti due proprietà:
	1. $m=n-1$
	2. Il cammino che collega due vertici è unico
- **Albero radicato**: questo tipo di [[Cos'è un albero|albero]] impone che ci sia una radice, questo genera una gerarchia

---
### Componente connessa
Dato un grafo $G=(V,E)$, una **componente connessa** di $G$ è un sottoinsieme di vertici $V'$ tale che:
- Il sottografo indotto $G[V']$ è connesso
- La componente connessa non deve appartenere ad un'altra più grande, ovvero $V'$ non è contenuto in nessun insieme di vertici che induca ad un sottografo connesso

Un esempio è il seguente grafo, il quale contiene $3$ componenti connesse:
![[Componenti connesse.svg]]
**Proprietà**: l'insieme delle componenti connesse di un grafo formano una [[Gli insiemi#Partizione|partizione]] di $V$.

---
### Grafi notevoli
- **Grafo vuoto**: indicato da $E_n$, indica un grafo con $0$ archi
- **Grafo completo**: indicato da $K_n$, indica un grafo con $n^2$ archi se orientato, $\frac{n(n-1)}{2}$ se non orientato
- **Grafo complemento**: indicato con $\overline{G}=(V,\overline{E})$, si ha $(u,v)\in E\iff (u,v)\in \overline{E}$, praticamente in $\overline{G}$ ci sono gli stessi nodi di $G$, ma ci sono solo gli archi non presenti in $G$, risulta essere vero quindi:
	- $G$ è completo $\iff$ $\overline{G}$ è vuoto
	- $G=K_n\iff \overline{G}=E_n$ 
![[Grafo complemento.svg]]
- **Grafo bipartito**: si dice tale se gli archi di un insieme di nodi vanno solo a nodi dell'altro insieme, inoltre se ogni nodo del primo insieme è connesso ad ogni altro nodo dell'altro insieme e viceversa, viene chiamato **bipartito completo**
![[Grafo bipartito completo.svg]]
>Nel caso di grafo non orientato bipartito completo, esistono $n_1\times n_2$ archi.

---
## Grado di un grafo
Dato un grafo non orientato $G=(V,E)$ con $u\in V$:
$$\underbrace{N(u)}_{\text{intorno di }u}=\{v\in V|(u,v)\in E\};\quad\underbrace{\deg(u)}_{\text{grado di }u}=|N(u)|;$$
ovvero: <u>il grado un nodo è pari alla cardinalità del suo</u> **intorno** ($N$).
![[Grado di un grafo.svg]]
<u>Non è possibile avere</u> $n$ <u>vertici con grado diverso</u>, in quanto $0\leq \deg(u)\leq n-1$, infatti dovrebbe esiste un nodo con grado $0$ ed uno con grado $n-1$, ma questo è assurdo perchè il primo indica che non è collegato con nessun'altro nodo, mentre il secondo indica che è collegato con tutti.

**Lemma (stretta di mano)** <u>vale solo per grafi non orientati</u>:
$$\sum_{u\in V}\deg(u)=2m$$
**Corollario (della stretta di mano)**: <u>Se</u> $G$ <u>è un grafo non orientato, allora il numero di vertici di grado dispari è pari.</u>
- **Dimostrazione**:
	Definiamo $P=\{u\in V|\deg(u)\text{ è pari}\}$ e  $D=\{u\in V|\deg(u)\text{ è dispari}\}$, dal lemma della stretta di mano otteniamo:
	$$\begin{flalign}
	2m&=\sum_{u\in V}\deg(u)\\
	&=\sum_{u\in P}\deg(u)+\sum_{u\in D}\deg(u)\\
	&=\sum_{u\in P}\underbrace{2\cdot f(u)}_{\text{grado di un numero pari}}+\sum_{u\in D}\underbrace{2\cdot f(u)+1}_{\text{grado di un numero dispari}}\\
	&=2\sum_{u\in P}f(u)+2\sum_{u\in D}f(u)+|D|\\
	&=2\sum_{u\in V}f(u)+|D|\\
	&\implies |D| = 2m-2\sum_{u\in V} f(u)=\underbrace{2(m-\sum_{u\in V}f(u))}_{\text{pari}}
	\end{flalign}
	$$

#### Grafo regolare
$G=(V,E)$ è $k$-**regolare**, se $\forall u\in V$, si ha $\deg(u)=k$, ovvero se tutti i nodi hanno lo stesso grado.

**Proprietà**:
- $2$-regolare $\implies$ $n=m$
- $3$-regolare $\implies$ $n$ è pari
- $4$-regolare $\implies$ $m$ è pari

### Deduzioni dalla matrice delle adiacenze
Data la **matrice di adiacenze** $A=a_{ij}$ con $i,j\in V$:
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
$$a_{ij}^{(2)}=\sum_{\ell=1}^n a_{i\ell}\cdot a_{\ell i}$$
tale prodotto è uguale a $1$ sse $a_{i\ell}=1$, cioè $(i,\ell)\in E$, e $a_{i\ell}=1$ e i due archi $(i,\ell)$ e $(\ell, i)$ rappresentano proprio un cammino di lunghezza $2$ che va da $i$ a $j$.

È possibile generalizzare questo concetto dicendo che: il prodotto di $k$ matrici di adiacenza $A^k$, ci da informazioni sul numero di cammini di lunghezza $k$ tra i nodi $i$ e $j$.
**Dimostrazione**:
Sia $A^k=\underbrace{A\times A\times ...\times A}_k=A^{k-1}\times A$ il prodotto di $k$ matrici di adiacenza per un certo grafo $G$

**Caso base**: $A^1=A$, infatti ci dice il numero di cammini di lunghezza $1$, ovvero gli archi tra $i$ e $j$
**Passo induttivo**: assumiamo che valga per $k-1$ e verifichiamolo per $k$, dato che $A^k=A^{k-1}\times A$ facciamo la stessa considerazione fatta nel caso $k=2$:
$$a_{ij}^{k}=\sum_{\ell=1}^n a_{i\ell}^{(k-1)}\cdot a_{\ell i}$$
dove $a_{i\ell}^{(k-1)}$ per ipotesi induttiva indica il numero di cammini di lunghezza $k-1$ tra $i$ e $\ell$, inoltre $a_{\ell, i}=1$ sse $(\ell, i)\in E$, e dunque la condizione è verificata.

Sulla diagonale principale inoltre sono rappresentati il **numero di cicli di lunghezza** $k$ che partono da $i$ ed arrivano a sè stesso, ma allo stesso tempo nei grafi <u>non orientati</u> rappresentano il **grado del nodo** $i$ (in caso di $A^2$) in quanto tutti gli archi di un nodo possono essere visti come un cammino di lunghezza $2$ dal nodo a sè stesso. 

### Grado nei grafi orientati
Il concetto di grado **cambia nei grafi orientati**, innanzitutto distinguiamo:
- **in-degree**: numero di archi entranti nel nodo
- **out-degree**: numero di archi uscenti dal nodo
$$\underbrace{\text{in-deg}(i)=\sum_{j=1}^na_{ji}}_\text{somma colonna i}\quad \underbrace{\text{out-deg}(i)=\sum_{j=1}^na_{ij}}_\text{somma riga i}$$
inoltre la somma degli archi entranti è uguale alla somma degli archi uscenti:
$$\sum_{i=1}^n\text{in-deg}(i)=\sum_{i=1}^n\text{out-deg}(i)=m$$

---
### Isomorfismo tra grafi
Dati $G_1=(V_1,E_1)$, $G_2=(V_2,E_2)$ e la funzione $\phi:V_1\to V_2$, essi rappresentano un **isomorfismo** (ovvero hanno la stessa forma) se:
1. $\phi$ è biunivoca
2. Deve preservare l'adiacenza: $(u,v)\in E_1\iff(\phi(u),\phi(v))\in E_2$

Seguono due grafi isomorfi:
![[Grafi isomorfi.svg]]
essi sono isomorfi perchè rappresentano la stessa relazione indipendentemente dal nome dei nodi, infatti esiste un vertice adiacente ad altri due, i quali non sono adiacenti tra loro, scriviamo quindi $G\simeq G'$.

La **degree-sequence** ($\text{deg-seq}(G)$) di un grafo è un vettore di $n$ elementi contenente i gradi dei vertici secondo un certo ordine (solitamente è crescente).

**Condizioni strettamente necessarie per l'isomorfismo**:
1. $G_1\simeq G_2\implies |V_1|=|V_2|$
2. $G_1\simeq G_2\implies |E_1| = |E_2|$, infatti deve valere anche $\deg(u)=\deg(\phi(u))\space\forall u\in V_1$
3. $G_1\simeq G_2\implies\text{deg-seq}(G_1)=\text{deg-seq}(G_2)$
4. $G_1\simeq G_2\implies$ $G_1$ e $G_2$ hanno lo stesso numero di _componenti connesse_

Di seguito sono rappresentati due grafi _non_ isomorfi, in quanto rispettano le prime tre condizioni, ma non l'ultima (4.):
![[Grafi non isomorfi.svg]]

**Dimostrazione isomorfismo tra due grafi**:
Siano $G_1$ e $G_2$ i seguenti grafi:
![[Grafi isomorfi pentagono.svg]]
e sia $\phi$ definita come segue:
$$\phi(1)=2\quad \phi(2)=4\quad \phi(3)=1\quad \phi(4)=3\quad \phi(5)=5$$
verifichiamo se $\phi$ rispetta le due condizioni:
1. $\phi$ mappa un solo vertice di $V_1$ ad uno solo di $G_2$ quindi è biunivoca
2. Le adiacenze sono rispettate:
	- $(1,2)\in E_1\to(\phi(1),\phi(2))=(2,4)\in E_2$
	- $(2,3)\in E_1\to(\phi(2),\phi(3))=(4,1)\in E_2$
	- $(3,4)\in E_1\to(\phi(3),\phi(4))=(1,3)\in E_2$
	- $(4,5)\in E_1\to(\phi(4),\phi(5))=(3,5)\in E_2$
	- $(5,1)\in E_1\to(\phi(5),\phi(1))=(5,2)\in E_2$

Verifichiamo se i due grafi rispettano le cinque condizioni:
1. $V_1=V_2=\{1,2,3,4,5\}$, quindi $|V_1|=|V_2|$
2. $|E_1|=|E_2|$
3. $\text{deg-seq}(G_1)[2,2,2,2,2]=\text{deg-seq}(G_2)[2,2,2,2,2]$
4. Entrambi hanno solo $1$ componente connessa

>Inoltre è possibile notare che $G_2$ è il grafo _complemento_ di $G_1$, quindi si può dire che $G_1$ è isomorfo al suo complemento $G_1\simeq \overline{G_1}$.

---
