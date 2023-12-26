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
$$\boxed{T(n)=a\cdot T\left(\frac{n}{b}\right)+f(n)}$$
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
>**Caso 3**: $f(n)$ occupa più tempo di $g(n)$, devo verificare se esiste un $\epsilon>0$ per cui $f(n)=\Omega(n^{\frac{1}{2}+\epsilon})$, questa condizione è verificata ponendo $\epsilon=\frac{1}{2}$ in quanto ottengo $f(n)=\Omega(n)$.
>Devo anche verificare la condizione ausiliaria, ovvero vedere se esiste $0<c<1$ per $n$ suff. grande per cui $a\cdot f(\frac{n}{b})\leq c\cdot f(n)$:
>$$3\cdot\frac{n}{9}\leq c\cdot n\quad\implies\quad\frac{1}{3}\leq c$$
>Scelgo $c=\frac{1}{3}$ verificando così la condizione ausiliaria.
>La complessità dell'algoritmo è quindi:
>$$T(n)=\Theta(n)$$

---
## Dimostrazione
La dimostrazione è divisa in due parti:
1. Trasformazione della formula ricorsiva ad esplicita
2. Dimostrazione dei tre casi

#### Parte 1
Usiamo l'albero delle ricorsioni per esplicitare la formula:
![[Albero delle ricorsioni teorema master.svg]]
All'inizio il problema sarà di dimensione $n$, i suoi $a$ nodi figli risolveranno una parte <u>più piccola</u> di esso, di dimensione $\frac{n}{b}$, lo stesso vale per tutti gli altri nodi.
- I nodi presenti al livello $i$ sono: $a^i$
- La dimensione di ogni problema a livello $i$: $\frac{n}{b^i}$
- Al livello $0$ il tempo impiegato è $f(n)$, al livello $i$: $f(\frac{n}{b^i})$

Il **tempo di esecuzione** sarà pari al tempo complessivo per risolvere tutte le chiamate nei vari livelli, ovvero:
$$T(n)=\sum_{i=0}^\text{n° di livelli}a^if\left(\frac{n}{b^i}\right)$$
esplicitando ancora si ottiene:
$$\begin{cases}a\cdot T(\frac{n}{b})+f(n)&n\geq 2\\c&n=1\end{cases}$$
le <u>chiamate ricorsive finiranno</u> quando $\frac{n}{b^i}=1$, isolando $i$ otteniamo:
$$i=\log_b n$$

Il **numero di foglie** è pari a:
$$n_\text{foglie}=a^{\log_bn}=a^{\log_ba\cdot\log_an}=(a^{\log_an})^{\log_ba}=n^{\log_ba}=n^d$$
Il **numero di nodi** è pari a:
$$n_\text{nodi}=\sum_{i=0}^{\log_bn}a^i\overset{\text{progressione geometrica}}{=}\frac{a^{\log_bn+1}-1}{a-1}=\frac{a\cdot a^{\log_bn}-1}{a-1}=\frac{a\cdot n^d-1}{a-1}=\Theta(n^d)$$
#### Parte 2
Dimostriamo ogni caso.
##### Caso 1
Per ipotesi sappiamo che $\exists\epsilon>0:f(n)=O(n^{d-\epsilon})$, applichiamola alla formula della complessità totale del livello $i$-esimo.
$$\begin{flalign}
a^i\cdot f(\frac{n}{b^i})&=a^i\cdot O((\frac{n}{b})^{d-\epsilon})\space\text{per ipotesi}\\
&=O(a^i\cdot(\frac{n}{b^i})^{d-\epsilon})\\
&=O(a^i\cdot(\frac{n^{d-\epsilon}}{(b^i)^{d-\epsilon}}))\\
&=O(a^i\cdot\frac{n^{d-\epsilon}}{(b^i)^d(b^i)^{-\epsilon}})\\
&=O(a^i\cdot\frac{n^{d-\epsilon}}{(b^d)^i(b^i)^{-\epsilon}})\space\text{dato }d=\log_ba,\space (b^d)^i=a^i\text{ possiamo semplificare}\\
&=O(\frac{n^{d-\epsilon}}{(b^i)^{-\epsilon}})\\
&=O((b^i)^\epsilon\cdot n^{d-\epsilon})\\
&=O((b^\epsilon)^i\cdot n^{d-\epsilon})
\end{flalign}$$

Per trovare la complessità totale, calcoliamo la sommatoria dei livelli usando il risultato appena trovato.
$$\begin{flalign}
T(n)&=\sum_{i=0}^{\log_bn}a^i\cdot f(\frac{n}{b^i})=\sum_{i=0}^{\log_bn}O((b^\epsilon)^i\cdot n^{n-\epsilon})\\
&=O((n^{d-\epsilon})\cdot\sum_{i=0}^{\log_bn}(b^\epsilon)^i)\\
&=O(n^{d-\epsilon}\cdot\frac{(b^\epsilon)^{\log_bn+1}-1}{b^\epsilon-1})\space\text{sfruttando la progressione geometrica}\\
&=O(n^{d-\epsilon}\cdot\frac{b^\epsilon\cdot(b^\epsilon)^{\log_bn}-1}{b^\epsilon-1})\\
&=O(n^{d-\epsilon}\cdot\frac{b^\epsilon\cdot(b^{\log_bn})^\epsilon-1}{b^\epsilon-1})\\
&=O(n^{d-\epsilon}\cdot\frac{b^\epsilon\cdot n^\epsilon-1}{b^\epsilon-1})\\
&=O(n^{d-\epsilon}\cdot n^\epsilon)\space\text{togliendo le costanti}\\
&=O(n^d)
\end{flalign}$$
Per quanto riguarda $T(n)=\Omega(n^d)$, questo risulta vero dato che l'algoritmo deve passare tutti i $n^d$ nodi foglia, quindi:
$$T(n)=\Theta(n)$$
##### Caso 2
Dall'ipotesi sappiamo che $f(n)=\Theta(n^d)\implies T(n)=\Theta(n^d\log n)$, applichiamola alla formula della complessità totale del livello $i$-esimo.

$$\begin{flalign}
a^i\cdot f(\frac{n}{b^i})&=a^i\cdot\Theta((\frac{n}{b^i})^d)\space\text{per ipotesi}\\
&=\Theta(a^i\cdot\frac{n^d}{(b^i)^d})\\
&=\Theta(a^i\cdot\frac{n^d}{(b^d)^i})\space\text{dato }d=\log_ba,\space (b^d)^i=a^i\text{ possiamo semplificare}\\
&=\Theta(n^d)
\end{flalign}$$
Calcoliamo la complessità totale.
$$\begin{flalign}
T(n)&=\sum_{i=0}^{\log_bn}a^if(\frac{n}{b^i})=\sum_{i=0}^{\log_bn}\Theta(n^d)=\Theta(\sum_{i=0}^{\log_bn}n^d)\\
&=\Theta(n^d(\log_bn+1))\\
&=\Theta(n^d\log_bn)\space\text{togliendo le costanti}
\end{flalign}$$
##### Caso 3
Dall'ipotesi otteniamo due condizioni, ovvero che $\exists\epsilon>0:f(n)=\Omega(n^{d+\epsilon})$ e che $\exists 0<c<1$ per $n$ suff. grande. $a\cdot f(\frac{n}{b})\leq c\cdot f(n)$.

Dato che il tempo di split e merge occupa la maggior parte del tempo, otteniamo che:
$$\forall i\geq 0:\space a^if(\frac{n}{b^i})\leq c^if(n)$$
Calcoliamo la complessità totale.
$$\begin{flalign}
T(n)&=\sum_{i=0}^{\log_bn}a^i\cdot f(\frac{n}{b^i})\\
&\leq\sum_{i=0}^{\log_bn}c^i\cdot f(n)=f(n)\sum_{i=0}^{\log_bn}c^i\\
&\leq f(n)\sum_{i=0}^{\infty}c^i=f(n)\frac{1}{1-c}\space\text{sfruttando la serie geometrica}\\
&\leq f(n)\space\text{togliendo le costanti}
\end{flalign}$$
Abbiamo quindi che $T(n)=O(f(n))$, per quanto riguarda $T(n)=\Omega(f(n))$ sappiamo che è sicuramente vero, perchè:
$$T(n)=a\cdot T(\frac{n}{b})+f(n)$$
dove $a\cdot T(\frac{n}{b})\geq 0$, quindi sicuramente $T(n)\geq f(n)$, quindi:
$$T(n)=\Theta(f(n))$$
