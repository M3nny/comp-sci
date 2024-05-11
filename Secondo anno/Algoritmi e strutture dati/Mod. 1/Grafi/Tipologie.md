### Grafo pesato
È possibile aggiungere delle informazioni sui vertici e/o archi di un grafo, questa informazione $W:E\to\mathbb{R}$ viene chiamata **peso**, rappresenta un numero reale, il quale significato dipende dalla realtà di riferimento.
- $G=(V,E,W)$ rappresenta un grafo pesato sui vertici o sugli archi
- $G=(V,E,W_1,W_2)$ rappresenta un grafo pesato sui vertici e sugli archi.

---
### Sottografo
Dato un grafo $G=(V,E)$, un **sottografo** $G'=(V',E')$ è definito come:
$$\begin{cases}V'\subseteq V\\E'\boldsymbol\subseteq E\cap V'\times V'\end{cases}$$
ovvero: i vertici sono un sottoinsieme di quelli originali, e gli archi presenti sono **al massimo** archi che collegano i vertici del sottografo.
![[Sottografi.svg]]

### Sottografo indotto
Dato un grafo $G=(V,E)$, un **sottografo indotto** $G[V']=(V',E')$ è definito come:
$$\begin{cases}V'\subseteq V\\E'\boldsymbol= E\cap V'\times V'\end{cases}$$
a differenza dei sottografi, gli archi presenti sono **tutti** quelli riguardanti solo e soltanto i vertici coinvolti.

Considerando il grafo originale precedente:
![[Sottografo indotto.svg]]

---
#### Grafo vuoto
Indicato da $E_n$, indica un grafo con $0$ archi.
#### Grafo completo
Indicato da $K_n$, indica un grafo con il numero massimo di archi:
- $n^2$ archi se orientato
- $\frac{n(n-1)}{2}$ se non orientato
vedi [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Cardinalità degli archi|cardinalità degli archi]].
#### Grafo complemento
Indicato con $\overline{G}=(V,\overline{E})$, si ha $(u,v)\in E\iff (u,v)\in \overline{E}$, praticamente in $\overline{G}$ ci sono gli stessi nodi di $G$, ma ci sono solo gli archi non presenti in $G$, risulta essere vero quindi:
- $G$ è completo $\iff$ $\overline{G}$ è vuoto
- $G=K_n\iff \overline{G}=E_n$ 
![[Grafo complemento.svg]]

#### Grafo bipartito
Si dice tale se gli archi di un insieme di nodi vanno solo a nodi dell'altro insieme, inoltre se ogni nodo del primo insieme è connesso ad ogni altro nodo dell'altro insieme e viceversa, viene chiamato **bipartito completo**
![[Grafo bipartito completo.svg]]
>Nel caso di grafo non orientato bipartito completo, esistono $n_1\times n_2$ archi.

---
#### Grafo aciclico
Non presenta [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Cammini|cicli]].
#### Grafo Connesso
Presi due nodi distinti qualsiasi, esiste un cammino che li collega.
#### Albero libero
È un grafo [[Tipologie#Grafo aciclico|aciclico]] e [[Tipologie#Grafo Connesso|connesso]], questo garantisce le seguenti due proprietà:
	1. $m=n-1$
	2. Il cammino che collega due vertici è unico

#### Foresta
Insieme di [[Tipologie#Albero libero|alberi]] disgiunti.
#### Albero radicato
[[Cos'è un albero|Questo tipo di albero]] impone che ci sia una radice, ciò genera una gerarchia.
