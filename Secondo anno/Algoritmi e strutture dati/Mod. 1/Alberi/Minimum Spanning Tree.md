Ricordiamo che un [[Tipologie#Albero libero|albero]] è:
$$\underbrace{\text{aciclico}}_{|E|\leq |V|-1}\quad\text{e}\quad\underbrace{\text{connesso}}_{|E|\geq |V|-1}$$
per cui: $|E|=|V|-1$.

Un albero è **fragile** in quanto aggiungendo un arco, esso diventerà ciclico, mentre togliendo un arco, esso diventerà disconnesso.

##### Teorema caratterizzante degli alberi
Se $G=(V,E)$ è **non connesso**, allora le seguenti affermazioni sono equivalenti (singolarmente sufficienti perchè $G$ sia un albero)
1. $G$ è un albero
2. Due vertici qualsiasi di $G$ sono connessi da un unico cammino
3. $G$ è connesso, ma se un arco qualsiasi è rimosso da $G$, allora il grafo risultante è disconnesso
4. $G$ è connesso e $|E|=|V|-1$
5. $G$ è aciclico e $|E|=|V|-1$
6. $G$ è aciclico ma se un arco qualsiasi viene aggiunto a $G$, il grafo diventa ciclico

### Albero di copertura minimo
Considerando un grafo $G=(V,E)$ **non orientato connesso**,
definiamo un **albero di copertura** (o **spanning tree**) un grafo composto da un sottoinsieme di archi $T\subseteq E$, ovvero $(V,T)$ tale che esso sia un **albero**.
>Su un grafo possono esistere più alberi di copertura.

Sia $G=(V,E,w)$ un grafo _non orientato connesso_ e [[Tipologie#Grafo pesato|pesato]] sugli archi.
L'**albero di copertura minimo** (o **Minimum Spanning Tree - MST**) di $G$ è un albero di copertura avente somma dei pesi sugli archi minima.

Il peso di ciascun arco è rappresentato tramite $w(u,v)$, e la somma dei pesi di un albero di copertura è definita come:
$$W(T)=\sum_{(u,v)\in T}w(u,v)$$

Un MST è detto tale se:
1. $T$ è un albero di copertura
2. $W(T)$ è il più piccolo tra tutti gli alberi di copertura

![[MST.svg|500]]

>Sappiamo sempre che un MST sarà composto da $|V|-1$ archi.

