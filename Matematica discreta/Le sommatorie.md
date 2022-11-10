La sommatoria:
$$\sum^n_{k=1}a_k$$
Ha come **indice $k$** (con $k \in \mathbb{N}$) e **termine generico $a_k$**.
- La somma con indice $\emptyset$ è sempre $0$;
- Una somma si dice equivalente ad un'altra quando producono lo stesso risultato anche se hanno una struttura diversa.

>[!Leggi delle sommatorie]
>
>### Legge associativa
$$\sum_{k\in K}(a_k+b_k)=\sum_{k\in K}a_k + \sum_{k\in K}b_k$$
>### Legge distributiva
$$\sum_{k\in K}c\cdot a_k = c\cdot\sum_{k\in K}a_k$$
>### Legge commutativa
$$\sum_{k\in K} a_k = \sum_{p(k)\in K}a_{p(k)}$$

## Fondere e spezzare sommatorie
Con $1\leq m \leq n$:
$$\text{Fondere}\quad\sum^m_{k=1}a_k+\sum^n_{k=m}a_k=a_m+\sum^n_{k=1}a_k$$
$$\text{Spezzare}\quad\sum^n_{k=1}a_k=\sum^m_{k=1}a_k+\sum^n_{k=m+1}a_k$$
## Somma multipla
Definiamo così una somma che come **termine generico ha una somma**.
- Gli indici possono essere dipendenti oppure indipendenti.
- Le parentesi interni si possono omettere:
$$\sum_{i\in I}\sum_{j\in J}\sum_{k\in K}a(i,j,k)$$
## Scambio degli indici
Quando gli indici sono _indipendenti_ possono essere scambiati semplicemente:
$$\sum_{i\in I}\sum_{j\in J}a_{ij}=\sum_{j\in J}\sum_{I\in I}a_{ij}$$
>[!Tip] Somme notevoli
>$$\sum^n_{i=1}i=\frac{n(n+1)}{2}$$
>$$\sum^n_{i = 1} i^2 = \frac{n(n+1)(2n+1)}{6}$$
>$$\sum^n_{i = 0} a^i = \frac{a^{n+1}-1}{a-1},\quad \text{con }a > 1$$
