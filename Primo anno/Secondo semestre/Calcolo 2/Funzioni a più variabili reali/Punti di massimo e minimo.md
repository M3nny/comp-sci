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
>- $D_x = 2x$
>- $D_y = 6(y-1)$
>$$\begin{cases}2x=0\\6(y-1)=0\end{cases}\quad\Rightarrow\quad\begin{cases}x=0\\y=1\end{cases}$$
>Abbiamo ottenuto che $(x,y)=(0,1)$ è l'unico punto critico per $f$.
