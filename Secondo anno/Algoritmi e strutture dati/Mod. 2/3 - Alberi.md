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

---
## Tipo albero
- **Dati**: un insieme di nodi $v$ (di tipo Node) ed un insieme di archi
- **Operazioni**:
	- `padre(Tree T, Node v) -> Node or {NIL}`
		**Pre**: $v\in T$
		**Post**: restituisce il padre del nodo $v$, oppure NIL
	- `figli(Tree T, Node v) -> List of Nodes`
		**Pre**: $v\in T$
		**Post**: restituisce una lista contenente i figli del nodo $v$

### Implementazione con array
Prevede l'utilizzo di un array contenente coppie (**info, parent**), contenenti l'informazione del nodo e l'indice del suo nodo padre.
Sia $T=(N, A)$ un albero di $n$ nodi numerati da $0$ a $n-1$ rappresentabile come segue:
![[Albero binario.png|400]]
Il relativo array è:

|  P.info  | a   | b   | c   | d   | e   | f   | g   | h   | i   |
|:--------:| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| P.parent | -1  | 0   | 0   | 0   | 1   | 1   | 3   | 6   | 6   |
|  Indice  | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |

- $\text{P[v].info}$ è l'informazione
- $\text{P[v].parent}==u\iff\exists (u,v)\in A$
- Se $v$ è la radice $\text{P[v].parent == -1}$
- $\text{P.length}$ rappresenta il numero di nodi nell'albero

La complessità spaziale è:
$$S(n)=\Theta(n)$$
#### Padre
```
padre (Tree T, Node v)
	if T.[v].parent == -1
		return NIL
	else
		return T[v].parent
```
Semplicemente ritorna `NIL` se è la radice (non ha padre) altrimenti ritorna il padre.
##### Complessità
Eseguiamo solo assegnamenti, quindi la complessità è:
$$T(n)=\Theta(n)$$
#### Figli
```
figli (Tree T, Node v)
	l = crealista()
	for i = 0 to T.length - 1
		if T[i].parent == v
			inserisci i in l
	return l
```
Creiamo una lista `l` per contenere i figli, poi vediamo se l'elemento dell'array ha come padre `v` e in quel caso lo inseriamo nella lista dei figli.
##### Complessità
Dobbiamo scorrere tutta la lista per vedere se esistono figli di `v`, quindi la complessità è (ipotizzando che l'inserimento sia costante):
$$T(n)=\Theta(n)$$
