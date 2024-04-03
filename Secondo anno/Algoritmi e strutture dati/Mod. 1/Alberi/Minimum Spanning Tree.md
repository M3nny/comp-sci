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

### Fatto cruciale degli MST
Un **taglio** rappresenta una suddivisione del grafo originale in $S$ e $V/S$.

Una volta effettuato un taglio, esiste sempre almeno un arco che lo attraversa in quanto il grafo è _connesso_.

L'arco con peso minimo che attraversa il _taglio_ viene chiamato **arco leggero**.

>[!Info] Fatto cruciale degli MST - I
>Il **fatto cruciale degli MST** afferma che: se $(u,v)$ è un arco leggero che attraversa un taglio qualsiasi, allora questo arco appartiene ad un $MST$.

**Dimostrazione - cuci e taglia**:
Sia $T$ un $MST$ di $G$, consideriamo $(u,v)\in T$ come l'arco leggero di un taglio:
1. $(u,v)\in T$, la condizione è verificata in partenza
2. $(u,v)\notin T$, procediamo come segue:
	- **Cuci**: aggiungo l'arco $T'=T\cup \{(u,v)\}$, in questo modo si creerà un ciclo in quanto sarà presente un altro arco $(x,y)\in T$ che attraversa il taglio
	- **Taglia**: tolgo l'altro arco $T''=T'\setminus\{(x,y)\}$, ora $T''\in ST(G)$

Dimostrando che $W(T'')=W(T)$ validerebbe il _fatto cruciale_:
$$W(T'')=W(T)+\underbrace{w(u,v)-w(x,y)}_{\leq 0}\leq W(T)$$
ciò è sempre vero in quanto abbiamo aggiunto l'arco leggero a $T$, quindi:
$$W(T)\leq W(T'')\leq W(T)\implies W(T)=W(T'')$$
>Praticamente l'arco aggiunto e quello tolto hanno peso uguale.

>[!Info] Fatto cruciale degli MST - II
>Se invece $(u,v)$ fosse **l'unico arco leggero** che attraversa il taglio (non ce ne sono altri con peso uguale minimo), allora **per ogni** $T\in MST(G)$ si ha che $(u,v)\in T$ (ogni $MST$ possibile di $G$ possiede l'arco $(u,v)$).

**Dimostrazione per assurdo**: supponiamo che la tesi sia falsa e che quindi esista un $T\in MST(G)$ tale che $(u,v)\notin T$:
- **Cuci**: $T'=T\cup \{(u,v)\}$, si forma un ciclo
- **Taglia**: $T''=T'\setminus\{(x,y)\}$, ora $T''\in ST(G)$

$$W(T'')=W(T)+\underbrace{w(u,v)-w(x,y)}_{< 0}< W(T)$$
questa volta però $w(u,v)-w(x,y)<0$ in quanto $(u,v)$ è l'unico arco leggero (quindi con valore minimo) che attraversa il taglio.

Ciò ci farebbe concludere che $W(T'')<W(T)$, ma questo è assurdo perchè così facendo avrei trovato un $ST$ con peso minore rispetto a quello originale, ma non è possibile dato che per ipotesi $T$ era già un $MST$ in partenza.

>[!Info] Proprietà derivante dal fatto cruciale degli MST
>Dato un grafo non orientato pesato, sia $(u,v)\in E$ un arco di peso minimo, allora di conseguenza $\exists MST(G)$ tale che $(u,v)\in T$.
>
>>L'arco che pesa di meno in $G$ appartiene sicuramente ad un $MST$ costruitito su $G$.

La dimostrazione è la stessa fatta per la prima parte del fatto cruciale.

### Teorema fondamentale degli MST
Sia $G=(V,E)$ un **grafo non orientato connesso**, siano:
- $A\subseteq E$ un sottoinsieme di archi contenuto in qualche $MST$
- $(S,V\setminus S)$ un taglio di $G$ che **rispetta** $A$, ovvero nessun arco di $A$ attraversa il taglio
- $(u,v)\in E$ un arco leggero che attraversa il taglio

allora il **teorema fondamentale degli MST** afferma che _esiste_ un $MST(G)$ che contiene $A\cup\{(u,v)\}$, brevemente si dice che l'arco $(u,v)$ è **sicuro** per $A$.

**Dimostrazione - cuci e taglia**:
sia $T\in MST(G)$ tale che $A\subseteq T$, abbiamo due casi (come nel fatto cruciale):
1. $(u,v)\in T$, la condizione è verificata in partenza
2. $(u,v)\notin T$, procediamo come segue:
	- **Cuci**: aggiungo l'arco $T'=T\cup \{(u,v)\}$, in questo modo si creerà un ciclo in quanto sarà presente un altro arco $(x,y)\in T$ che attraversa il taglio
	- **Taglia**: tolgo l'altro arco $T''=T'\setminus\{(x,y)\}$, ora $T''\in ST(G)$

procedendo analogamente alla dimostrazione fatta per il fatto cruciale, abbiamo:
$$W(T)=W(T'')$$
abbiamo dimostrato che l'arco $(u,v)$ appartiene ad un $MST(G)$, ora però dobbiamo dimostrare anche che $A\cup\{(u,v)\}\subseteq T''$, ma questo è sempre vero in quanto ci è garantito dal secondo punto dell'ipotesi, ovvero:
- $A\subseteq T''$ perchè nessun arco in $A$ non attraversa il taglio
Inoltre $(u,v)\in T''$ per costruzione.

