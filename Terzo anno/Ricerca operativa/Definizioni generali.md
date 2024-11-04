## Spazi vettoriali
Uno **spazio vettoriale** è un insieme $V^n(K)$ di elementi (vettori) con **campo** $K$ che soddisfano $8+1$ proprietà, in cui i simboli $+,\oplus, \cdot, \bullet$ rappresentano quattro operazioni binarie arbitrarie.

0. $\forall u,v\in V^n(K),\quad u+v\in V^n(K)$
	**Chiusura** rispetto a l'operatore $+$, ovvero l'operatore applicato a due elementi dello stesso tipo ritorna un valore dello stesso tipo.
	
1. $\forall u,v,z\in V^n(K),\quad (u+v)+z = u+(v+z)$
	Proprietà **associativa**.
	
2. $\exists w\in V^n(K): \forall v\in V^n(K),\quad w+v = v$
	Elemento **neutro (o nullo)**.
	
3. $\forall v\in V^n(K),\quad\exists \overline{v}\in V^n(K): v+\overline{v}=w$
	Elemento **opposto (o inverso)**.
	
4. $\forall u,v\in V^n(K),\quad u+v=v+u$
	Proprietà **commutativa**.
	
5. $\forall a,b\in K, \forall v\in V^n(K), a \bullet v\in V^n(K),\quad (a\cdot b)\bullet v=a\bullet (b\bullet v)$
6. $\exists\sigma\in K:\forall v\in V^n(K),\quad \sigma\bullet v = v$
7. $\forall a,b\in K, \forall v\in V^n(K),\quad (a\oplus b)\bullet v=a\bullet v+b\bullet v$
8. $\forall a\in K, \forall u,v\in V^n(K),\quad a\bullet (u+v)=a\bullet u + a\bullet v$

>[!Example]
>**Dimostriamo come il prodotto tra due numeri negativi è positivo**.
>$$(-2)\cdot (-3)$$
>Il nostro spazio vettoriale avrà $n=1$, e sarà quindi rappresentato da $\mathbb{R}(\mathbb{R})$.
>$$\begin{flalign}(-2)[+3+(-3)]&=0\\&=(-2)\cdot(+3)+(-2)\cdot(-3)=0\\&=-6+(-2)\cdot(-3)=0\\&=6-6+(-2)\cdot(-3)=6\\&=(-2)\cdot(-3)=6\end{flalign}$$

### Indipendenza lineare
L'apice $n$ in $\mathbb{R}^n$ rappresenta la **dimensione** dello spazio vettoriale, ovvero il numero massimo di vettori _linearmente indipendenti_ usati per rappresentare lo spazio vettoriale.
>D'ora in poi $\mathbb{R}^n=\mathbb{R}^n(\mathbb{R})$

Nelle matrici è possibile trovare come pedice il numero di righe $n$ ed il numero di colonne $m$, la dimensione è data da $n\cdot m$ (e.g. $M_{n,m}(\mathbb{R})$).

Un vettore $z=z_1,...,z_m\in \mathbb{R}^n(\mathbb{R})$ si dice **linearmente indipendente** quando:
$$z=0\iff a_1=...=a_m=0$$
ovvero: il vettore è nullo sse la _combinazione lineare_ (una qualsiasi) avente coefficienti nulli ritorna un vettore nullo.

Ad esempio nella matrice $M_{2,3}(\mathbb{R})$ i vettori linearmente indipendenti sono:
$$
\begin{pmatrix}1&0&0\\0&0&0\end{pmatrix}
\begin{pmatrix}0&0&0\\1&0&0\end{pmatrix}
\begin{pmatrix}0&1&0\\0&0&0\end{pmatrix}
\begin{pmatrix}0&0&0\\0&1&0\end{pmatrix}
\begin{pmatrix}0&0&1\\0&0&0\end{pmatrix}
\begin{pmatrix}0&0&0\\0&0&1\end{pmatrix}
$$
infatti tramite le loro combinazioni è possibile qualsiasi tipo di matrice $M_{2,3}(\mathbb{R})$.

Dati gli $n$ vettori $v_1,...,v_n\in\mathbb{R}^n$, essi risultano _linearmente indipendenti_ (su $\mathbb{R}$) sse il determinante della matrice da essi formata è non nullo:
$$\left(v_1\space\vdots\space...\space\vdots\space v_n\right)\in\mathbb{R}^{n\times n}$$
dove la prima colonna è data da: $v_i^1=\begin{pmatrix}v_1^1\\\vdots\\v_n^1\end{pmatrix}$.

Per indicare le **funzioni continue** nell'intervallo $[a,b]$ usiamo la seguente notazione (nel nostro caso $a=-\infty, b=\infty$):
$$C^0[a,b]=\{\sin(x),\cos(x),...\}$$
>$C^0$ rappresenta le funzioni continue, $C^1$ le funzioni derivabili almeno una volta, dove la derivata è anch'essa continua (vedi [[Funzioni vettoriali#Continuità/Derivabilità/Integrabilità|continuità]]).

Per indicare i **polinomi ad una variabile** con grado massimo $n$ usiamo la seguente notazione: $P_n(x)$.

---
### Combinazioni lineari
Una **combinazione lineare** dati $z_1,...,z_m\in\mathbb{R}^n$ e $a_1,...,a_m\in\mathbb{R}$ è definita come:
$$z=a_1z_1+...+a_mz_m$$

Una **combinazione affine** è una _combinazione lineare_ in cui:
$$z=a_1z_1+...+a_mz_m\quad\text{con}\quad\sum_{i=1}^ma_i=1$$
geometricamente appare come una retta passante passante per due punti specifici dei vettori:
![[Combinazione affine.svg|250]]
in tre dimensioni crea un _piano_.

Una **combinazione conica** è una _combinazione lineare_ in cui:
$$z=a_1z_1+...+a_mz_m\quad\text{con}\quad a_i\geq 0,\space i=1,...,m$$
geometricamente appare come l'area della superficie infinita generata dai due vettori:
![[Combinazioni coniche.svg|400]]
in tre dimensioni è il volume di una piramide senza base.

Una **combinazione convessa** è allo stesso tempo una _combinazione affine_ ed una _combinazione conica_:
$$z=a_1z_1+...+a_mz_m\quad\text{con}\quad \sum_{i=1}^ma_i=1\quad\land \quad a_i\geq 0,\space i=1,...,m$$
geometricamente appare come un segmento delimitato da due punti specifici dei vettori:
![[Combinazione convessa.svg]]
in tre dimensioni è un taglio (base) di una piramide.
In questo caso la combinazione convessa $z$ dei vettori $z_1$ e $z_2$ si ottiene tramite la relazione: $z=a_1z_1+a_2z_2$, dove $a_1+a_2=1$ e $a_1,a_2\geq 0$.

---
### Prodotto scalare
Dato uno spazio vettoriale $V^n(K)$, il **prodotto scalare** (o interno) è una funzione indicata come $<\bullet,\bullet>$ e definita come segue:
$$V^n(K)\times V^n(K)\to \mathbb{R}$$

Possiede le seguenti proprietà:
1. $\forall v\in V^n(K),\quad<v,v>$ è $\geq 0$, mentre è pari a $0 \iff v=w$
	
	Il prodotto scalare di un vettore per se stesso è $\geq 0$, è uguale a $0$ sse il vettore rappresenta vettore nullo.
	
2. $\forall u,v,z\in V^n(K),\quad<u+v,z>=<u,z>+<v,z>$
	
	Proprietà _distributiva_, l'operatore $+$ viene utilizzato sia per la somma tra vettori e sia per la somma tra scalari.
	
3. $\forall u,v\in V^n(K),\quad<u,v>=<v,u>$
	Proprietà _commutativa_.

Il **prodotto scalare standard**, dati due vettori $u,v$ è definito come:
$$\forall u,v\in\mathbb{R}^n,<u,v>=u_1v_1+...u_n v_n$$
Due vettori $u,v$ si dicono **ortogonali** ($u\bot v$) sse il prodotto scalare standard $<u,v>$ è pari a $0$.
>Due vettori ortogonali sono linearmente indipendenti, non è detto viceversa.

---
### Norma
Dato uno spazio vettoriale $V^n(K)$, la **norma** di un vettore può essere vista come la lunghezza del vettore stesso, essa è indicata come $||\bullet||_*$, ed è definita come:
$$V^n(K)\to\mathbb{R}^+$$
Possiede le seguenti proprietà:
1. $\forall v\in V^n(K),\quad||v||_*\geq 0$, mentre è pari a $0\iff v=w$
	
	La norma è $\geq 0$, è uguale a $0$ sse il vettore rappresenta il vettore nullo.
	
2. $\forall v\in v^n(K),\forall\alpha\in\mathbb{R},\quad||\alpha\bullet v||_* =|\alpha|\cdot||v||_*$
	
	La norma del prodotto di uno scalare per un vettore è uguale al valore assoluto dello scalare per la norma del vettore.
	
1. $\forall u,v\in V^n(K),\quad||u+v||_*\leq||u||_*+||v||_*$
	La norma della somma di due vettori è minore della somma delle norme dei due vettori ([[Secondo anno/Algoritmi e strutture dati/Mod. 1/Cammini minimi/Introduzione#Disuguaglianza triangolare|disuguaglianza triangolare]])

>[!Info]
>La norma viene indicata con $*$ (star) come pedice in quanto esistono varie norme, ovvero diversi metodi di misura di una lunghezza (che danno risultati diversi).

**Norma euclidea**: $||v||_2=\sqrt{v_1^2+...+v_n^2}$
**Norma 1**: $||v||_1=|v_1|+...+|v_n|$
**Norma $\infty$**: $||v||_\infty=\max\limits_{1\leq i\leq n}|v_i|$

Di seguito le rappresentazioni geometriche per le norme pari a $1$:
![[Norme.png]]

>Notare come solo in quattro punti il loro risultato combacia.


>[!Tip] Angolo tra vettori
>Dati due vettori $u,v$, il loro **angolo interno** è dato da:
>$$\varphi=||u||_2\cdot||v||_2\cdot\cos\varphi$$

---
## Funzioni lineari e affini
Data la funzione $f:\mathbb{R}^n\to\mathbb{R}^m$, si dice che $f(x)$ è **lineare** in $\mathbb{R}^n$ se soddisfa le seguenti proprietà:
1. $f(x+y)=f(x)+f(y),\quad\forall x,y\in\mathbb{R}^n$
2. $f(\lambda x)=\lambda f(x),\quad\forall x\in\mathbb{R}^n$

Data la funzione $g:\mathbb{R}^n\to\mathbb{R}$, si dice che $g(x)$ è **affine** in $\mathbb{R}^n$ se esiste una funzione _lineare_ $f(x)\in\mathbb{R}^n$ ed una costante $c\in\mathbb{R}$ tali che:
$$g(x)=f(x)+c$$
>Anche se non è propriamente lineare, ha un andamento lineare.

>[!Example]
>La funzione $f(x)=2x-3$, non è lineare, bensì affine, infatti non rispetta entrambe le due proprietà:
>$$f(x+y)=2(x+y)-3=2x+2y-3=f(x)+2y$$

---
## Derivate direzionali
Considerando una funzione $f(x)\in C^1(\mathbb{R}^n)$, la **derivata direzionale** $D(f,d)$ lungo il **vettore direzione** $d\in\mathbb{R}^n$ è definita come:
$$D(f,d)\stackrel{\Delta}{=}\lim_{h\to 0}\frac{f(x+hd)-f(x)}{h}=\nabla f(x)^Td$$

Nel caso di normali derivate parziali rispetto agli assi:
$$d=\begin{pmatrix}0\\1\\\vdots\\0\end{pmatrix}$$
Dove l'$i$-esimo (unico) elemento con valore $1$ sarà l'asse in questione su cui calcolare il cambiamento della funzione, mentre per le derivate direzionali $d$ sarà **denso** in quanto sarà riempito da valori reali solitamente diversi da $0$.

---
## Teorema del valor medio
Prima di procedere ricordiamo alcune definizioni:
- [[Cos'è una derivata#Derivata|Derivata]] $f'(\overline{x})$: rappresenta l'inclinazione della funzione in un suo punto specifico
- [[Calcolo differenziale#Derivate parziali|Derivata parziale]] $\frac{\partial f(\overline{x})}{\partial x}$: indica l'inclinazione rispetto ad un punto ed asse specifico
- [[Calcolo differenziale#Calcolo della derivata parziale|Gradiente]] $\nabla f(\overline{x})$: è composto dalle derivate prime , e "riassume" la direzione della funzione rispetto a tutti gli assi
- [[Punti di massimo e minimo#Matrice Hessiana|Matrice Hessiana]] $\nabla^2 f(\overline{x})$: è composta dalle derivate seconde di una funzione in un punto specifico
>Il nome deriva dal fatto che stiamo valutando il cambiamento nella congiungente tra $x$ ed $y$, e quindi in mezzo ai due punti.

Possiamo vedere il **teorema del valor medio** come una funzione utilizzata per predire lo stato in un punto $y$ a partire dal punto $x$, con $x,y\in\mathbb{R}^n$:
$$f(y)=f(x)+\nabla f(x)^T(y-x)+o(||y-x||)$$
- $f(x)$ rappresenta lo "stato attuale" in $x$
- $\nabla f(x)^T$ indica l'andamento di $f(x)$ fino al momento attuale
- $(y-x)$ è usato per definire la geometria della differenza tra $x$ ed $y$
- $o(||y-x||)$ può essere considerato come una stima dell'errore, se i due punti $x,y$ dovessero essere vicini l'errore sarebbe quasi nullo ([[Infiniti e infinitesimi#Funzioni infinitesime|o-piccolo]])

Un'**altra formulazione** del teorema è la seguente:
$$f(y)=f(x)+\nabla f[x+\theta(y-x)]^T(y-x)\quad\theta\in[0,1]$$
- $f(x)$ è lo "stato attuale" in $x$
- $f[x+\theta(y-x)]^T$ è la stima del futuro stato lungo la congiungente tra $x$ ed $y$, dove _esiste almeno un_ $\theta$ compreso tra $0$ e $1$ per cui la formulazione è vera (in pratica abbiamo spostato l'incertezza da $o$ piccolo a $\theta$), $\theta$ tuttavia può essere anche essere al di fuori di quell'intervallo
- $(y-x)$ è usato per definire la geometria della differenza tra $x$ ed $y$

La rappresentazione geometrica del teorema del valor medio con $n=1$ è la seguente:
![[Valor medio.svg]]
Da notare come all'avvicinarsi di $y$ a $x$ $o(|y-x|)$ diventa sempre più piccolo fino a scomparire del tutto, infatti **per funzioni lineari** essendo che la retta tangente percorre tutta la funzione standogli accanto, **si potrà togliere la componente** $o(|y-x|)$ in quanto sarà sempre pari a $0$,
ottenendo quindi: $f(y)=f(x)+\nabla f(x)^T(y-x)$.

### Teorema del valor medio (secondo ordine)
Il teorema del valor medio di **secondo ordine** viene usato per valutare il **cambiamento del cambiamento** lungo la congiungente tra $x$ e $y$.

Le due formulazioni le possiamo riscrivere usando anche le derivate seconde come:

$$f(y)=f(x)+\nabla f(x)^T(y-x)+\frac{1}{2}(y-x)^T\nabla^2 f(x)(y-x)+o(||y-x||)^2$$
$$f(y)=f(x)+\nabla f(x)^T(y-x)+\frac{1}{2}(y-x)^T\nabla^2 f[x+\theta (y-x)](y-x)\quad \theta\in[0,1]$$
