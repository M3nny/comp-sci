Un **albero radicato** è una coppia $T=(N,A)$ dove:
- $N$ è un insieme finito di nodi fra cui si distingue un nodo $r$ detto **radice**
- $A\subseteq N\times N$: è un insieme di coppie di nodi, detti **archi**

In un albero, ogni nodo $v$ (eccetto la radice) ha **esattamente un padre** $u$ tale che l'arco $(u,v)\in A$.
Un nodo può avere $0$ o più figli $v$ tali che $(u, v)\in A$.
## Caratteristiche di un albero
- **Grado**: numero di figli di un nodo
- **Foglia (o nodo esterno)**: un nodo senza figli
- **Nodo interno**: nodo non foglia
- **Fratelli**: nodi che hanno lo stesso padre
- **Cammino**: sequenza di nodi da nodo $u$ a nodo $u'$ compresi collegati da archi discendenti
- **Lunghezza del cammino**: numero di archi nel cammino (o numero di nodi - 1)
>c'è sempre un cammino di lunghezza $0$ da $u$ a $u$.

- **Antenato**: un nodo qualsiasi $y$ in un cammino dalla radice $r$ a $x$ è detto _antenato_ di $x$
- **Discendente**: se $y$ è antenato di $x$ allora $x$ è discendente di $y$ 
>Ogni nodo è antenato e discendente di sè stesso.
- **Antenato/discendente proprio**: se $y$ è antenato di $x$ e $x\neq y$, allora $y$ è antenato proprio di $x$, discorso analogo per i discendenti propri

- **Sottoalbero**: con radice nel nodo $x$ è l'albero formato dai discendenti di $x$ (incluso), dove $x$ è la radice
- **Profondità di un nodo**: lunghezza del cammino dalla radice al nodo $x$
- **Livello di un albero**: costituito da tutti i nodi che stanno alla stessa profondità
- **Altezza di un nodo**: lunghezza del più lungo cammino che scende dal nodo $x$ ad una foglia
- **Altezza di un albero**: altezza della sua radice

![[Albero esempio.png]]
>L'**altezza** di $3$ è $3$ mentre tutte le foglie hanno altezza pari a $0$, i **discendenti** di $12$ sono $12,1$, i suoi **antenati** sono $12,3,7$, la **profondità** di $1$ è $3$.

## Alberi binari
Sono definiti in modo ricorsivo:
- Un albero vuoto è un albero binario
- Un albero costituito da un nodo radice e da altri due sottoalberi binari (sinistro e destro) è un albero binario

Un albero $k$-ario è un albero, dove ogni ramo ha al massimo $k$ figli, un albero binario è un albero $k$-ario con $k=2$.
Un albero è $k$-ario **completo** se:
- Tutte le foglie hanno la stessa profondità
- Tutti i nodi interni hanno esattamente $k$ figli (hanno grado $k$)

>[!Example]
>Trovare il numero di foglie e nodi interni di un albero $k$-ario completo di altezza $h$.
>Per logica le foglie sono $k^h$, lo dimostriamo per induzione su $h$.
>- **Caso base**: $h=0$
>	l'albero ha solo la radice, che è anche l'unica foglia: $k^0=1$
>**Caso induttivo**: assumiamo vera l'ipotesi per cui $\text{foglie}(h)=k^h$ e lo dimostriamo per $h+1$.
>Sfruttando l'ipotesi induttiva e sapendo che in un albero completo ogni nodo ha $k$ figli: $k^h\cdot k=k^{k+1}$ quindi $\text{foglie}(h+1)=k^{h+1}$.
>
>Per calcolare i nodi interni invece:
>$$\sum_{i=0}^{h-1}k^i=\frac{k^{(h-1)+1}-1}{k-1}=\frac{k^h-1}{k-1},\quad k\neq 1$$
>---
>Se volessimo trovare l'altezza di un albero $k$-ario completo con $n$ foglie:
>$$n=k^h\implies\log_kn=h$$
## Tipo albero
- **Dati**: un insieme di nodi $v$ (di tipo Node) ed un insieme di archi
- **Operazioni**:
	- `padre(Tree P, Node v) -> Node or {NIL}`
		**Pre**: $v\in P$
		**Post**: restituisce il padre del nodo $v$, oppure NIL
	- `figli(Tree P, Node v) -> List of Nodes`
		**Pre**: $v\in P$
		**Post**: restituisce una lista contenente i figli del nodo $v$
