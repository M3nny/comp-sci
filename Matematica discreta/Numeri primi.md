- Un numero naturale $p>1$ si dice **primo** se i suoi divisori sono: $1$ e _se stesso_;
- Se $p>1$ non è primo, allora si dice **composto**;
- Per convenzione $1$ non è ne primo ne composto.

>Esistono diverse **congetture** che cercano di trovare un modo per elencare i numeri primi, non sono state verificate, ma sono state provate a computer con un numero limitato di casi, e quindi si dicono vere fino al quel caso verificato specifico, dato che non sono state dimostrate formalmente non saranno incluse in questo file.

>[!Teoremi]
>Ogni numero naturale $n\geq 2$ è esprimibile come prodotto di un numero finito di numeri primi.
>
>---
>Sia $p>1$un numero naturale. $p$ è primo se e solo se per ogni coppia di numeri naturali $a$ e $b$, se $p|ab$ allora $p|a$ oppure $p|b$

### Teorema fondamentale dell'aritmetica
Ogni numero naturale $n\geq 2$ è esprimibile in un'unico modo come prodotto di un numero finito di fattori primi.
>[!Example]
>- $100 = 2^2\cdot 5^2$
>- $150 = 2\cdot 3^2 \cdot 5$

## Il piccolo teorema di Fermat
Sia $p$ un numero primo e $a\in \mathbb{Z}$. Se $p\nmid a$ allora
$$a^{p-1}\equiv_p 1$$
## Teorema di Wilson
Se $p$ è un numero primo $(p>1)$ allora
$$(p-1)!\equiv_p -1$$
## La funzione di Eulero
È definita come:
$\phi(n) =$ numero di interi positivi $\leq n$ che sono relativamente primi con $n$.

Ovvero ritorna la quantità di numeri (precedenti al parametro) che sono relativamente primi per il parametro indicato.
>[!Example]
>- $\phi(7)=6$ perchè $1,2,3,4,5,6$ sono relativamente primi con $7$
>- $\phi(8)=4$ perchè $1,3,5,7$ sono relativamente primi con $8$
>- $\phi(14)=6$ perchè $1,3,5,9,11,13$ sono relativamente primi con $14$
