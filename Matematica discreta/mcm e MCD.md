## Minimo comune multiplo
Dati due interi $a$ e $b$, il minimo fra i loro multipli comuni è detto **minimo comune multiplo** ed è denotato come **mcm(a, b)**
>mcm(1, 6) = 6
>mcm(4, 6) = 12

## Massimo comun divisore
Dati due interi $a$ e $b$, il massimo fra i loro divisori comuni è detto **massimo comun divisore** ed è denotato con **MCD(a, b)**
>MCD(1, 6) = 1
>MCD(4, 6) = 2

Euclide definisce nel seguente modo l'algoritmo per calcolare l'MCD efficientemente:
1. Dividere il maggiore dei due numeri per il minore;
2. Rimpiazzare il maggiore con il minore;
3. Rimpiazzare il minore con il resto di tale divisione;
4. Ripetere finchè il resto non diventa zero.

## Teorema di Bezout
>[!Teorema di Bezout]
>Se $a,b \in \mathbb{N}^+$ e $d=MCD(a,b))$ allora esistono due interi $x$ e $y$ tali che:
$$d=ax+by$$

>**Identità di Bezout**: $MCD(a,b)=ax+by$

Se $a = 12$ e $b=8$, allora $MCD(12,8)=4$, valgono quindi le seguenti identità di Bezout:
- $4=12\cdot 1 +8\cdot(-1)$
- $4=12\cdot(-1)+8\cdot 2$

##### Lemma 
Con $a, b \in \mathbb{N}$ se $d$ divide sia $a$ che $b$, ed esistono due interi $x, y$ tali che $d=ax+by$, allora:
$$d=MCD(a,b)$$
##### Corollario
Due numeri naturali $a$ e $b$ sono coprimi se e solo se esistono due interi $x$ e $y$ tali che $ax+by=1$

### Teorema di Bezout generalizzato
Con $a,b,c \in \mathbb{N}$ e $d=MCD(a,b)$, l'equazione lineare $ax,by=c$ ammette soluzioni intere se e solo se $d|c$.

>[!Example]
>**Trovare una soluzione intera dell'equazione**: $240x+36y=12$
>
>Per prima cosa semplifico tutti i coefficienti, quindi divido per 12
>$$20x+3y=1 \quad \text{posso scriverlo come} \quad MCD(20,3)=1$$
>Dato che l'MCD è uguale a $1$, $20$ e $3$ sono coprimi, quindi l'equazione ammette soluzioni.
>---
>**Trovare una soluzione intera dell'equazione**: $6x+2y=5$
>$MCD(6,2)=2$ che è diverso da $5$ per cui secondo il teorema di di Bezout generalizzato non ammette soluzioni.

