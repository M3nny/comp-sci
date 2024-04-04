L'algoritmo di **Prim** a differenza di quello di [[Kruscal]] non usa tanti insiemi sparpagliati per poi unirli, ma fa crescere un albero, in particolare il nodo da cui si parte (il quale sarà la **radice** dell'albero) sarà il **predecessore** di tutti gli altri.

La struttura implicita di **predecessori** sarà un albero vero e proprio dove ogni vertice punta al suo padre, in questo modo sarà facile ricostruire il $MST$.
>Viene creato un albero radicato,

Per ogni vertice vengono mantenute due informazioni nell'algoritmo:
1. $Key[u]$: elemento della _coda di priorità_ (intero)
2. $\pi[u]$: predecessore (puntatore)

viene usata una **coda con priorità** $Q\subseteq V[G]$ la quale implementata tramite **heap binario** e contiene i **vertici da estrarre**.
- $V\setminus Q$: vertici già estratti
- $Q$: vertici da estrarre
>Ad ogni step abbiamo un **taglio** del grafo.

$Key[u]$ rappresenta il **peso minore** tra tutti gli archi che attraversano il taglio e sono incidenti a quel vertice in particolare, se non c'è un arco incidente a quel vertice che attraversa il taglio, si avrà $Key[u]= \infty$.

Così facendo il **più piccolo valore nella coda di priorità** rappresenterà il **peso dell'arco leggero** che attraversa il taglio.

$\pi[u]$ ovvero il **predecessore**, è dato dal vertice collegato al nodo $u$ tramite l'arco con peso minore che attraversa il taglio ed è incidente a $u$, se non c'è un arco incidente a $u$, si avrà $\pi[u]=\text{NIL}$.

![[Exec Prim.svg|700]]

L'algoritmo estrae il nodo con chiave minore e poi aggiorna le i valori delle strutture dati con il nuovo taglio.
