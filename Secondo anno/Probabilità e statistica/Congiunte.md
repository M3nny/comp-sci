Si è spesso interessati a formulare affermazioni di tipo probabilistico rispetto a **due o più variabili aleatorie contemporaneamente**.
Vengono chiamate **distribuzioni bivariate** le coppie di v.a. $(X,Y)$, **multivariate** i vettori di v.a. $(X_1, ... , X_n)$.

>In questo corso le congiunte che vedremo saranno tutte dello stesso tipo, non verranno mischiate discrete e continue.

### Funzione di ripartizione congiunta
La f.r. congiunta della coppia di v.a. $(X,Y)$ è una funzione $F:\mathbb{R}^2\to[0,1]$ tale che:
$$F(x,y)=\mathbb{P}[X\leq x,Y\leq y],\quad\forall(x,y)\in\mathbb{R}^2$$
dalla funzione di ripartizione possiamo ricavare facilmente le f.r. delle singole v.a. $X$ e $Y$, infatti:
$$F_X(x)=\lim_{y\to\infty}F(x,y)$$
$$F_Y(y)=\lim_{x\to\infty}F(x,y)$$
La f.r. congiunta di $(X,Y)$ contiene quindi anche l'informazione riguardante le distribuzioni di probabilità singole di $X$ e $Y$, ovvero le **distribuzioni marginali**, che si ottengono quindi sommando rispetto a tutti i valori possibili dell'altra variabile.
>Il viceversa non è vero.

La funzione di probabilità congiunta e le marginali possono essere rappresentate all'interno di una **tabella a due entrate**.

>[!Example]
>Un programma consiste di due moduli che hanno rispettivamente $X$ e $Y$ numero di errori che hanno distribuzione congiunta:
>$p(0,0)=p(0,1)=p(1,0)=0.2$
>$p(1,1)=p(1,2)=p(1,3)=0.1$
>$p(0,2)=p(0,3)=0.05$
>
>|   $X$    |  $0$   |  $1$   |  $2$   |  $3$   | $p_X(x)$ |
>|:--------:|:------:|:------:|:------:|:------:|:--------:|
>|   $0$    | $0.20$ | $0.20$ | $0.05$ | $0.05$ |  $0.5$   |
>|   $1$    | $0.20$ | $0.10$ | $0.10$ | $0.10$ |  $0.5$   |
>| $p_Y(y)$ | $0.40$ | $0.30$ | $0.15$ | $0.15$ |   $1$    |
>
>Probabilità che non ci siano errori nel primo modulo:
>$$\mathbb{P}[X=0]=\sum_{y=0}^3p(0,y)=0.20+0.20+0.05+0.05=0.5$$
>Probabilità che nel primo modulo ci siano meno errori che nel secondo modulo:
>$$
>\begin{flalign}
>\mathbb{P}[X&<Y]=1-\mathbb{P}[X\geq Y]\\
>&=1-\mathbb{P}[X=0,Y=0]-\mathbb{P}[X=1,Y=0]-\mathbb{P}[X=1,Y=1]\\
>&=1-(0.2+0.2+0.1)=0.5
>\end{flalign}
>$$


### Funzioni congiuntamente continue
$X$ e $Y$ sono **congiuntamente continue** se esiste una funzione $f:\mathbb{R}^2\to\mathbb{R}$ integrabile e tale che:
1. $f(x,y)\geq 0,\quad\forall(x,y)\in\mathbb{R}^2$
2. $\int\int_{\mathbb{R}^2}f(x,y)dxdy=1$
$f$ è la **funzione di densità congiunta** di $(X,Y)$ e si usa per calcolare probabilità riguardanti le due v.a. in questione.

Sia $(X,Y)$ una distribuzione continua bivariata con densità $f(x,y)$.
![[Area congiunte.svg]]
$$\begin{flalign}
\mathbb{P}[(X,Y)\in C]&=\int\int_Cf(x,y)dxdy\\
&=\mathbb{P}[a_1\leq x\leq a_2, b_1\leq y\leq b_2]=\int_{a_1}^{a_2}\int_{b_1}^{b_2}f(x,y)dydx
\end{flalign}
$$

>[!Example]
>Trovare il valore di $k$ che rende la seguente funzione, una funzione di densità:
>$$f(x,y)=kxy\space 1_{\{(x,y)\in[0,1]^2\}}$$
>
>$$\begin{flalign}
>&\int_0^1\int_0^1kxy\space dydx=1\\
>&k\int_0^1x\int_0^1y\space dydx=1\\
>&k\int_0^1x\frac{1}{2}dx=\frac{k}{2}\int_0^1x\space dx=1\\
>&\frac{k}{4}=1\implies k=4
>\end{flalign}$$
>
>Calcolare $\mathbb{P}[X>Y]$.
>![[Ripartizione congiunte.svg|300]]
>
>$$\begin{flalign}
>\mathbb{P}[X>Y]&=\int_0^1\int_0^x4xy\space dydx\\
>&=\int_0^1 4x[\frac{y^2}{2}]_0^x\space dx\\
>&=\int_0^1 4x\cdot\frac{x^2}{2}\space dx\\
>&=\int_0^1 2x^3\space dx = \frac{1}{2}
>\end{flalign}$$



