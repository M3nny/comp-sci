## Divide et impera
Con questo teorema siamo in grado di trovare la complessità degli algoritmi ricorsivi del tipo **divide et impera** (e.g. ricerca binaria, mergesort).

La complessità di un algoritmo di questo tipo è data da tre parti:
1. Tempo di _split_ ovvero la complessità nel dividere il problema in sottoproblemi
2. Tempo per la risoluzione dei sottoproblemi
3. Tempo di _merge_ delle soluzioni dei sottoproblemi

Considerando $a$ come il numero **costante** di sottoproblemi, $n$ la dimensione iniziale del problema e $\frac{n}{b}$ la dimensione dei sottoproblemi, si può riassumere come: 
$$\boxed{\begin{flalign}
T(n)=&T_\text{split}(n)+\\
&a\cdot T(\frac{n}{b})+\\
&T_\text{merge}(n)
\end{flalign}}$$
Dato che $T_\text{split}(n)$ e $T_\text{merge}(n)$ non sono funzioni ricorsive, possiamo considerarli come risultato di una funzione $f(n)$ la quale complessità dipenderà dalla dimensione del problema, quindi: $f(n)=T_\text{split}(n)+T_\text{merge}(n)$

La complessità ora risulta essere:
$$T(n)=a\cdot T\left(\frac{n}{b}\right)+f(n)$$
Le condizioni per la correttezza dell'algoritmo sono le seguenti:
1. $f(n)\geq 0$ per ogni $n$ sufficientemente grande
2. $a\geq 1,\quad a\in\mathbb{R}$
3. $b\geq 2,\quad b\in\mathbb{R}$

## Teorema master
Dato la variabile $d$, dove:
$$d=\log_ba$$
il teorema si divide in tre casi in base al confronto tra $f(n)$ e $a\cdot T(\frac{n}{b})$.

#### Caso 1
$$\exists\epsilon>0:f(n)=O(n^{d-\epsilon})\quad\implies\quad T(n)=\Theta(n^d)$$
Se $f(n)$ occupa meno tempo della parte ricorsiva, allora il tempo impiegato dall'algoritmo sarà pari al tempo impiegato dalla parte ricorsiva ($n^d$).
#### Caso 2
$$f(n)=\Theta(n^d)\quad\implies\quad T(n)=\Theta(n^d\log n)$$
Se $f(n)$ occupa lo stesso tempo della parte ricorsiva, allora la complessità dell'algoritmo sarà uguale al prodotto tra la parte ricorsiva e $\log n$.
#### Caso 3
$$\exists\epsilon>0:f(n)=\Omega(n^{d+\epsilon})$$
$$\text{e}$$
$$\exists\space0<c<1:\text{per }n\text{ suff. grande }a\cdot f\left(\frac{n}{b}\right)\leq c\cdot f(n)$$
$$\implies T(n)=\Theta(f(n))$$
Se $f(n)$ occupa più tempo della parte ricorsiva, allora il tempo impiegato dall'algoritmo sarà uguale a quello impiegato per $f(n)$.

>[!Example]
>Risolviamo gli stessi esempi risolti con il [[3 - Complessità di un algoritmo#Metodo dell'iterazione|metodo dell'iterazione]] + uno nuovo.
>$$T(n)=T\Big(\frac{n}{2}\Big)+c$$
>Posso usare il teorema master?
>- Posso esprimere la ricorrenza come $a\cdot T(\frac{n}{b})+f(n)$?
>	Si: $a=1$ $b=2$ $d=\log_21=0$ 
>- Valgono le tre condizioni?
>	$f(n)\geq 0$ (i.e. $c\geq 0$)? si
>	$a\geq 1$? si
>	$b\geq 2$? si
>
>$f(n)$ (i.e. $c$) come si colloca asintoticamente rispetto a $n^d$ (i.e. $n^0=1$)?
>**Caso 2**: si comportano similmente dato che sono entrambe costanti:
>$$T(n)=\Theta(\log n)$$
>---
>$$T(n)=9T\Big(\frac{n}{3}\Big)+n$$
>Si può risolvere con il teorema master.
>- $a=9$
>- $b=3$
>- $d=\log_39=2$
>- $f(n)=n$
>- $g(n)=n^2$
>**Caso 1**: $f(n)$ occupa meno tempo di $g(n)$, devo verificare anche se esiste un $\epsilon>0$ per cui $f(n)=O(n^{2-\epsilon})$
>Ponendo $\epsilon = 1$ la condizione è verificata dato che ottengo che $f(n)=O(n)$, quindi:
>$$T(n)=\Theta(n^2)$$
>---
>$$T(n)=3T\Big(\frac{n}{9}\Big)+n$$
>Si può risolvere con il teorema master.
>- $a=3$
>- $b=9$
>- $d=\frac{1}{2}$
>- $f(n)=n$
>- $g(n)=\sqrt{n}$
>**Caso 3**: $f(n)$ occupa più tempo di $g(n)$, devo verificare se esiste un $\epsilon>0$ per cui $f(n)=\Omega(n^{\frac{1}{2}}+\epsilon)$, questa condizione è verificata ponendo $\epsilon=\frac{1}{2}$ in quanto ottengo $f(n)=\Omega(n)$.
>Devo anche verificare la condizione ausiliaria, ovvero vedere se esiste $0<c<1$ per $n$ suff. grande per cui $a\cdot f(\frac{n}{b})\leq c\cdot f(n)$:
>$$3\cdot\frac{n}{9}\leq c\cdot n\quad\implies\quad\frac{1}{3}\leq c$$
>Scelgo $c=\frac{1}{3}$ verificando così la condizione ausiliaria.
>La complessità dell'algoritmo è quindi:
>$$T(n)=\Theta(n)$$
