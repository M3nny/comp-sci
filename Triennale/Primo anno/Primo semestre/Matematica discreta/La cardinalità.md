La [[Cardinalità e numerabilità#Cardinalità e numerabilità|cardinalità]] (già affrontata parzialmente in Calcolo 1) indicata con $|A|$ indica il numero di elementi all'intero dell'insieme $A$.

Due insiemi $A$ e $B$  <u>hanno la stessa cardinalità</u> (**equipollenti**/**equipotenti**) <u>se e solo se  esiste una funzione biettiva</u> $f: A\to B$.

- Trovare la cardinalità di un insieme consiste nel contare gli elementi al suo intero;
- **Non esiste** alcuna funzione [[Cos'è una funzione#Iniettiva, suriettiva, biettiva|iniettiva]] da $A$ a $B$ mentre <u>esistono</u> funzioni iniettive da $B$ ad $A$;
- **Esistono** funzioni [[Cos'è una funzione#Iniettiva, suriettiva, biettiva|suriettive]] da $A$ a $B$ mentre <u>non esiste</u> alcune funzione suriettiva da $B$ ad $A$.

## Insiemi infiniti
Due <u>insiemi infiniti hanno la stessa cardinalità se esiste una funzione iniettiva</u> da:
$$A\to B \space \land\space  B\to A$$
Possiamo notare quindi che l'insieme $P$ dei numeri pari ha la stessa cardinalità di $\mathbb{N}$
anche se $P\subset \mathbb{N}$ 

## Insiemi numerabili
Essendo la **cardinalità di insiemi infiniti** come $\mathbb{N}$ **un numero non naturale**, essa viene indicata con $\aleph_0$ 
$$|\mathbb{N}| = \aleph_0$$
Di conseguenza tutti gli insiemi equipollenti a $\mathbb{N}$ si dicono **numerabili**.

$$|\mathbb{N}|=|\mathbb{Z}|$$
$$|\mathbb{N}|=|\mathbb{Q}|$$
- Esiste però il caso di $|\mathbb{N}| < |\mathbb{R}|$ questo perchè esiste una funzione iniettiva da $\mathbb{N}\to \mathbb{R}$ ma **non** da $\mathbb{R} \to \mathbb{N}$;
- $\mathbb{R}$ infatti ha **due ordini di infinito**:
	1. L'insieme è infinito;
	2. Ogni numero reale ha una rappresentazione infinita.
	
	Questo lo porta a essere non numerabile per la sua **densità**, appunto tra un numero e l'altro ci sono infiniti numeri.

## Cardinalità del continuo
La cardinalità del continuo viene indicata con $\mathfrak{c}$.
Se $\aleph_0=|\mathbb{N}|$ e $\mathfrak{c}=|\mathbb{R}|$ abbiamo:
$$\aleph_0 < \mathfrak{c}$$
- Inoltre Cantor ha dimostrato che **la cardinalità di ogni insieme è strettamente minore di quella del suo insieme delle parti**:
$$|A|<|\mathcal{P}(A)|=2^{|A|}$$