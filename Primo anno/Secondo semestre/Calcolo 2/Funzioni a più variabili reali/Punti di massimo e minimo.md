## Estremi di una funzione e punti critici
Sia $f:A\subseteq\mathbb{R}^n\to\mathbb{R}$ con $x_0\in A$
- $x_0$ è **massimo assoluto (o globale)** se $\forall x_1\in A\quad f(x_0)\geq f(x_1)$ 
- $x_0$ è **minimo assoluto** se $\forall x_1\in A\quad f(x_0)\leq f(x_1)$ 

- $x_0$ è **massimo relativo (o locale)** se esiste un intorno di $x_0$ ($U_r(x_0)$) per cui si ha che $f(x_0)\geq f(x_1)\quad \forall x_1\in U_r(x_0)\cap A$ 
- $x_0$ è **minimo relativo** se esiste un intorno di $x_0$ ($U_r(x_0)$) per cui si ha che $f(x_0)\leq f(x_1)\quad \forall x_1\in U_r(x_0)\cap A$ 

>Noi ci preoccuperemo dei massimi e minimi **non vincolati**, ovvero quelli interni al dominio, non quelli sul bordo (vincolati).

>[!Teorema di Weirstrass]
>Analogamente al teorema con una variabile:
>Sia $f: A\subseteq\mathbb{R}^n\to\mathbb{R}$; se $A$ è **chiuso, limitato** e $f$ è **continua**, allora $f$ ha massimo e minimo assoluti in $A$, cioè:
>$$\exists x_m, x_n\in A: f(x_m)\leq f(x)\leq f(x_n)\quad \forall x\in A$$
>- Se $A$ è **chiuso, limitato e connesso** allora:
>$$I(f)=[f(x_m), f(x_n)]$$ 
>ovvero: i punti che restituisce la funzione sono compresi tra il minimo ed il massimo.

### Punti critici (o stazionari)
Si dice punto critico $x_0 \in A$ se $\nabla f(x_0) = 0$, ovvero tutte le derivate parziali sono nulle in $x_0$.

>[!Teorema di Fermat]
>Se $x_0\in\mathring{A}$ è minimo o massimo locale di $f$ e $f$ è derivabile in $x_0$, allora $x_0$ è punto critico di $f$, cioè $\nabla f(x_0)=0$.
>


>[!Example]
>$f(x,y)=x^2+3(y-1)^2$
>Trovare i punti critici.
>
>- $D_x = 2x$
>- $D_y = 6(y-1)$
>$$\begin{cases}2x=0\\6(y-1)=0\end{cases}\quad\Rightarrow\quad\begin{cases}x=0\\y=1\end{cases}$$
>Abbiamo ottenuto che $(x,y)=(0,1)$ è l'unico punto critico per $f$.
>
>---
>$f(x,y)=x^2-y^3$
>Trovare i punti critici.
>
>- $D_x=2x$
>- $D_y = -3y^2$
>$$\begin{cases}2x=0\\-3y^2=0\end{cases}$$
>Abbiamo che $(x,y)=(0,0)$ è un punto critico, ma è un massimo o un minimo?
>In questo caso banale possiamo fare una sezione in $x=0$ e vedere che $f(0,y)=-y^3$  che ha la forma di $f(x)=x^3$ specchiato rispetto l'asse delle $y$.
>
>Vediamo che il punto $(0,0)$ non è nè massimo nè minimo, bensì un punto di sella

## Derivate di ordine superiore
Per vedere se un _punto critico_ è un massimo o un minimo, si vanno a studiare le derivate di ordine superiore (guardiamo la concavità).
### Derivate parziali seconde
Sia $f: A\subseteq\mathbb{R}^2\to\mathbb{R}$ con $A$ aperto ed $f$ derivabile (esistono $D_x$ e $D_y$).
Se $D_x$ è derivabile possiamo calcoalre le sue derivate parziali chiamate **seconde di $f$**.
$$\frac{\delta}{\delta x}\left(\frac{\delta f}{\delta x}\right)=\frac{\delta^2 f}{\delta x^2}; \quad\quad \frac{\delta}{\delta y}\left(\frac{\delta f}{\delta x}\right)=\frac{\delta^2 f}{\delta y\delta x}$$
$$\frac{\delta}{\delta x}\left(\frac{\delta f}{\delta y}\right)=\frac{\delta^2 f}{\delta x\delta y}; \quad\quad \frac{\delta}{\delta y}\left(\frac{\delta f}{\delta y}\right)=\frac{\delta^2 f}{\delta y^2}$$
è possibile usare la forma abbreviata:
$$f_{xx}\quad\quad f_{yx}$$
$$f_{xy}\quad\quad f_{yy}$$
#### Matrice Hessiana
Come il _gradiente_ è un vettore colonna che contiene le derivate parziali, la **matrice Hessiana** ($H_f(x)$) **contiene tutte le derivate seconde**.
$$H_f(x,y)=\begin{pmatrix}f_{xx}&f_{yx}\\f_{xy}&f_{yy}\end{pmatrix}$$
In $\mathbb{R}^2$ sarà grande $2\times 2$ in quanto ci sono $2$ variabili, se ce ne fossero state $n$, sarebbe stata $n\times n$.

Le **derivate miste** ovvero $f_{yx}$ e $f_{xy}$ saranno uguali in $\mathbb{R}^2$.

>[!Example]
>$f(x,y)=x^2e^x+\cos(x)\sin(y)+3y$
>Calcolare la matrice Hessiana e valutarla in $(0,\frac{\pi}{2})$ 
>- $D_x = 2xe^x+x^2e^x-\sin(x)\sin(x)$
>- $D_y=\cos(x)\cos(y)+3$
>
>Ora troviamo le derivate seconde derivando le precedenti due derivate sia per $x$ sia per $y$.
>- $D_{xx}=2e^x+2xe^x+2xe^x+x^2e^x-\cos(x)\sin(x)$
>- $D_{yx}=-\sin(x)\cos(y)$
>- $D_{xy}=-\sin(x)\cos(y)$
>- $D_{yy}=-\cos(x)\sin(y)$
>
>$$H_f(x,y)=\begin{pmatrix}2e^x+4xe^x+x^2e^x-\cos(x)\sin(x)&-\sin(x)\cos(y)\\-\sin(x)\cos(y)&-\cos(x)\sin(y)\end{pmatrix}$$
>$$H_f\left(0,\frac{\pi}{2}\right)=\begin{pmatrix}1&0\\0&-1\end{pmatrix}$$

- $f$ si dice $\mathcal{C}^1(A)$ (classe $\mathcal{C}^1$ in A) se $f$ è continua in $A$, derivabile, e le derivate parziali sono continue in $A$
- $f$ si dice $\mathcal{C}^2(A)$ se le derivate seconde esistono in $A$ e sono continue

Quindi riassumendo (indicando con $\mathcal{C}^0$ le funzioni almeno continue):
$$\mathcal{C}^0(A)\supseteq\mathcal{C}^1(A)\supseteq\mathcal{C}^2(A)\supseteq\mathcal{C}^\infty(A)$$
>[!Teorema di Schwarz]
>Le derivate parziali miste sono uguali in ogni punto del dominio se $f$ è $\mathcal{C}^2(A)$

### Formula di Taylor
Analogamente al [[Polinomio di Taylor#Definizione|polinomio di Taylor]] ad una variabile ($n=1$) dove c'è una retta che approssima bene la funzione vicino al punto, in $n=2$ sarà la parabola ad approssimare bene la funzione vicino al punto.

Se prima la _perturbazione_ era data da $(x_0+h)$, ora sarà data da $(x_0+h, y_0+k)$.
Quindi, indicando $x_0$ come un vettore rappresentante $x_0=(x_0,y_0)$, la formula è data da:
$$f(x_0+h,y_0+k)=$$
$$=f(x_0)+f_x(x_0)h+f_y(x_0)k+\frac{1}{2}(f_{xx}h^2+2f_{xy}hk+f_{yy}k^2)+o(h^2+k^2)$$
In forma compatta (**vettoriale**):
$$f(x_0+h,y_0+k)=$$
$$=f(x_0)\nabla f^T(x_0)\cdot\begin{pmatrix}h\\k\end{pmatrix}+\frac{1}{2}(hk)H_f(x_0)\begin{pmatrix}h\\k\end{pmatrix}+o(h^2+k^2)$$
sviluppata:
$$=f(x_0)\nabla f^T(x_0)\cdot\begin{pmatrix}h\\k\end{pmatrix}+\frac{1}{2}(hk)H_f(x_0)\begin{pmatrix}h\\k\end{pmatrix}+o(h^2+k^2)$$

**Riassumendo**:
Indicando con $x_0=(x_0,y_0)^T$ e $h=(h,k)^T$, la formula di Taylor si può scrivere come:
$$f(x_0+h)=f(x_0)+\nabla f^T(x_0)h+\frac{1}{2}h^T H_f(x_0)h + o(||h||^2)$$

## Studio della natura dei punti critici
Abbiamo visto che se $x_0$ è un _punto critico_ allora $\nabla f(x_0)=0$
La formula di Taylor per un punto critico diventa quindi:
$$f(x_0+h)=f(x_0)+\frac{1}{2}\cdot h^T H_f(x_0) h + o(||h||^2)$$
Se $H_f(x_0)$ non è una matrice nulla, il termine $h^TH_f(x_0)h$ è il termine rilevante per approssimare il grafico di $f$, chiamato **forma quadratica** $q(x,y)$
$$q(x,y)=(xy)H\begin{pmatrix}x\\y\end{pmatrix}$$
>[!Example]
>Esempi di forme quadratiche
>- $H = \begin{pmatrix}2&0\\0&3\end{pmatrix};\quad q(x,y)=(xy)\begin{pmatrix}2&0\\0&3\end{pmatrix}\begin{pmatrix}x\\y\end{pmatrix} = 2x^2+3y^2$
>$q$ è un **paraboloide ellittico** rivolto verso l'alto, il punto è un minimo.
>
>- $H = \begin{pmatrix}-2&0\\0&-3\end{pmatrix};\quad q(x,y)=(xy)\begin{pmatrix}-2&0\\0&-3\end{pmatrix}\begin{pmatrix}x\\y\end{pmatrix} = -2x^2-3y^2$
>$q$ è un **paraboloide ellittico** rivolto verso il basso, il punto è un massimo.
>
>- $H = \begin{pmatrix}1&0\\0&-3\end{pmatrix};\quad q(x,y)=(xy)\begin{pmatrix}1&0\\0&-3\end{pmatrix}\begin{pmatrix}x\\y\end{pmatrix} = x^2-3y^2$
>$q$ è un **parabolodide iperbolico**, quindi è un punto di sella (nè max nè min)
>
>- $H = \begin{pmatrix}1&0\\0&0\end{pmatrix};\quad q(x,y)=(xy)\begin{pmatrix}1&0\\0&0\end{pmatrix}\begin{pmatrix}x\\y\end{pmatrix} = x^2$
>$q$ è un **cilindro con profilo parabolico** ovvero una parabola lungo una direzione, non possiamo determinare un minimo in quanto abbiamo il minimo lungo tutta una direzione.

Ma non sempre abbiamo questi casi particolari, la matrice potrebbe essere degenere (ovvero potrebbe darci un'interpretazione delle precedenti ma storta), quindi dovremo usare gli [[Primo anno/Primo semestre/Algebra lineare/Riassunto#Autovettori|autovettori]] per capire come è ruotata $H$.

### Caratterizzazione dei punti critici
Possiamo scrivere la matrice Hessiana anche come:
$$H=U\Lambda U^T$$
dove $U$ rappresenta il vettore contenente le coordinate del punto critico e $\Lambda$ la matrice diagonale contenente gli **autovalori** (derivate seconde).
Classifichiamo come segue i punti critici:
1. $\lambda_i>0\space\forall i$ (tutti gli autovalori positivi): $H$ è una matrice simmetrica definita positiva, $q$ è un <u>paraboloide elittico rivolto verso l'alto</u>, quindi il punto critico è un **minimo**.
2. $\lambda_i<0\space\forall i$ (tutti gli autovalori negativi): $H$ si dice matrice definita negativa, $q$ è un <u>paraboloide elittico rivolto verso il basso</u>, quindi il punto critico è un **massimo**.
3. Ci sono autovalori con segno discorde: $H$ si dice indefinita e abbiamo un **punto di sella**.
4. $\lambda_i\geq 0\space\forall i$: $H$ è **semidefinita positiva**.
5. $\lambda_i\leq 0 \space\forall i$: $H$ è **semidefinita negativa**.

Gli [[Primo anno/Primo semestre/Algebra lineare/Riassunto#Autovettori|autovalori]] sono difficili da calcolare, ma a noi serve solo il segno, non il loro valore, sfruttando il fatto che lavoriamo in $n=2$ e che la matrice $H$ è simmetrica:
$$det(H)=\lambda_1\cdot\lambda_2$$
Per cui possiamo caratterizzare il punto critico in base al determinante tramite il **test della matrice Hessiana**:
- Se $det(H) < 0$ gli autovalori ($\lambda$) sono discordi ed il punto critico è un **punto di sella** (parabolodide iperbolico).
- Se $det(H) > 0$ dobbiamo distinguere il caso in cui $\lambda_1, \lambda_2$ sono entrambi negativi o entrambi positivi, per fare questo andiamo a vedere il segno di $a$ ($f_{xx}$) appartenente a $H=\begin{pmatrix}a&b\\b&d\end{pmatrix}$
	- Se $a>0$ allora $H$ è definita positiva, il punto critico è un **minimo**.
	- Se $a<0$ allora $H$ è definita negativa, il punto critico è un **massimo**.
	- Se $a=0$ $H$ è indefinita, il punto critico è un **punto di sella**.
- Se $det(H) = 0$ allora $H$ è semidefinita positiva o negativa o nulla, ma non possiamo usare il test della matrice Hessiana per caratterizzare questo punto critico.

>[!Example]
>$f(x,y)=x^2+2y^2-x^2y$
>$D=\mathbb{R}^2$
>Il test della matrice Hessiana e altri teoremi visti, funzionano solo se $f\in\mathcal{C}^2$, e in questo caso $f\in\mathcal{C}^\infty$ in quanto composizione di funzioni continue e derivabili infinite volte.
>1. Derivate prime:
>- $f_x = 2x-2xy$
>- $f_y=4y-x^2$
>2. Troviamo i punti critici:
>$$\begin{cases}2x-2xy=0\\4y-x^2=0\end{cases}\to\begin{cases}2x(y-1)=0\\4y-x^2=0\end{cases}$$
>Notiamo subito che un punto critico è $(x,y)=(0,0)$ ma non è l'unico, nella prima equazione $y$ annulla l'equazione per $y=1$, ma $x$ lo dobbiamo ancora valutare, andiamo quindi a sostituire $y=1$ all'interno della seconda equazione:
>$$\begin{cases}y=1\\4-x^2=0\end{cases}$$
>Otteniamo $P_1 = (0,0),\space P_2=(2,1)\space P_3=(-2,1)$
>3. Derivate seconde:
>- $f_{xx}=2-2y$
>- $f_{xy}=-2x$
>- $f_{yy}=4$
>$$H=\begin{pmatrix}2-2y&-2x\\-2x&4\end{pmatrix}$$
>4. Valuto i punti critici 
>- $H(0,0)=\begin{pmatrix}2&0\\0&4\end{pmatrix}$, $det(H)=8>0$, $P_1$ è un **minimo** (relativo).
>- $H(2,1)=\begin{pmatrix}0&-4\\-4&4\end{pmatrix}$, $det(H)=-16<0$, $P_2$ è un **punto di sella**.
>- $H(-2,1)=\begin{pmatrix}0&4\\4&4\end{pmatrix}$, $det(H)=-16<0$, $P_3$ è un **punto di sella**.
>![[Grafico esercizio.png|300]]
