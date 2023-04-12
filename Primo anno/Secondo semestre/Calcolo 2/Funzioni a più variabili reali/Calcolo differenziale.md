## Derivate parziali
Estendiamo il concetto di [[Cos'è una derivata|derivata]] a funzioni di più variabili.
Sia $f:A\subseteq\mathbb{R}^2\to\mathbb{R}$ con $A$ insieme aperto. Se il seguente limite esiste finito, allora esso definisce la **derivata parziale** di $f$ rispetto a $x$ calcolata nel punto $(x_0, y_0)$:
$$\frac{\delta f}{\delta x}(x_0,y_0)=\lim_{h\to 0}\left(\frac{f(x_0+h,y_0)-f(x_0,y_0)}{h}\right)$$
analogamente la **derivata parziale** rispetto a $y$ è:
$$\frac{\delta f}{\delta y}(x_0,y_0)=\lim_{k\to 0}\left(\frac{f(x_0,y_0+k)-f(x_0,y_0)}{k}\right)$$

Se anche solo una delle derivate parziali è uguale a $\pm\infty$ in un punto allora non esiste la derivata in quel punto.

>[!Definizione (Funzione derivabile)]
>Una funzione $f: A\subseteq \mathbb{R}^2\to\mathbb{R}$ si dice **derivabile** in $x_0$ se esistono tutte le derivate parziali in $x_0$.
>Si dice **derivabile** in $A$ se è derivabile in tutti i punti di $A$.
>- Funzioni con punti di discontinuità oppure definite per parti potrebbero avere punti di non derivabilità.
>- Nei punti di possibile non derivabilità bisogna usare la definizione con il limite.

![[Rapporto incrementale.svg|300]]
**Notazioni compatte**:
- $\delta_xf(x,y)$
- $f_x(x,y)$
- $D_x[f(x_0,y_0)]$

### Calcolo della derivata parziale
Per trovare la _derivata parziale_ senza passare per la definizione con il limite, si usano i metodi usati per le derivate di funzioni ad una variabile <u>trattando ogni variabile singolarmente e considerando le altre variabili presenti come coefficienti</u>.

Indichiamo con il **vettore gradiente** il vettore che ha per componenti le derivate parziali di $f$.
Segue la definizione di $\text{grad}\in\mathbb{R}^2$ 
$$\nabla f(x_0,y_0)=\left(\frac{\delta f}{\delta x}(x_0,y_0),\frac{\delta f}{\delta y}(x_0,y_0)\right)$$
**Notazioni compatte**:
- $Df(x_0,y_0)$
- $\text{grad}\space f(x_0,y_0)$

>[!Example]
>Trovare il gradiente della seguente funzione:
>$$f(x,y,z)=y\sin(xz)$$
>$D_x=z\cdot y\cos(xz)$
>$D_y=\sin(xz)$
>$D_z=x\cdot y\cos(xz)$
>$$\nabla f = \begin{pmatrix}z\cdot y\cos(xz)\\ \sin(xz)\\ x\cdot y\cos(xz)\end{pmatrix}$$
>---
>Sia $f(x,y) = y\sqrt{x}$. Calcolare (se esiste) $f_x(0,0)$.
>$$D_x(x,y)=\frac{y}{2\sqrt{x}}$$
>Quando $(x,y)\to(0,0)$ si ottiene una forma indeterminata $\frac{0}{0}$ dobbiamo quindi usare la definizione di derivata parziale:
>$$D_x(0,0)=\lim_{h\to 0}\frac{f(0+h,0)-f(0,0)}{h}=\lim_{h\to 0}\frac{0}{h} = 0$$
>Quindi in questo caso la derivata parziale rispetto a $x$ nell'origine vale $0$.


## Piano tangente e differenziabilità
Analogamente alla retta tangente in un punto indicante la derivata in un punto, estendiamo questo concetto alle funzioni a più variabili con la nozione del **piano tangente**.

L'equazione di un piano $T$  _non verticale_ in $\mathbb{R}^2$ è data da:
$$z=ax+by+c$$
per costruire il possibile **piano tangente** a nel punto $(x_0, y_0)$ bisogna applicare ad una equazione le condizioni per cui:
- $T(x_0,y_0)=f(x_0,y_0)$ 
- $a=D_x[T(x_0, y_0)] = D_x[f(x_0, y_0)]$
- $b=D_y[T(x_0, y_0)] = D_y[f(x_0, y_0)]$

otteniamo analogamente all'equazione della [[Algebra delle derivate#Retta tangente che passa per un punto|retta tangente per un punto]]:
$$T(x,y)=f(x_0,y_0) + D_x[f(x_0,y_0)](x-x_0)+D_y[f(x_0,y_0)](y-y_0)$$

>[!Definizione (Funzione differenziabile)]
>Una $f:A\subseteq\mathbb{R}^2\to\mathbb{R}$ è **differenziabile** in $(x_0,y_0)\in\mathring{A}$ se il piano tangente $T$ è _ben definito_ in $(x_0,y_0)$ e "approssima bene" la funzione $f$ in un intorno di $(x_0,y_0)$.
>- Se $f$ è differenziabile in un punto, allora è anche derivabile in quel punto.
>- Il piano tangente è ben definito ed esso è la miglior approssimazione lineare di $f$ attorno a quel punto.

>[!Teorema (Condizione sufficiente di differenziabilità)]
>**Differenziabile in $x_0$**:
>Sia $f:A\subseteq\mathbb{R}^2\to\mathbb{R}$ con $A$ aperto e $x_0\in A$. Se le derivate parziali esistono in un intorno di $x_0$ e sono continue in $x_0$, allora $f$ è differenziabile in $x_0$.
>
>**Differenziabile in $A$**:
>Se le derivate parziali esistono continue in tutto $A$, allora $f$ è differenziabile in $A$

>N.B. all'esame le funzioni saranno tutte differenziabili

>[!Example]
>Scrivere l'equazione del piano tangente in $(0,1)$
>$$f(x,y)=ye^x+x^2+2xy+y^3$$
>Il piano sarà dato da:
>$$T(x,y)=f(0,1)+D_x[f(0,1)](x-0)+D_y[f(0,1)](y-1)$$
>- $D_x = ye^x+2x+2y$
>- $D_y = e^x+2x+3y^2$
>$$T(x,y)= 2 + 3x + 4(y-1)$$

## Derivate direzionali
Data $f: A\subseteq\mathbb{R}^2\to\mathbb{R}$ con $A$ aperto, $x_0\in A$ e $v\in\mathbb{R}^n$ con $||v||=1$ (versore). 
Si dice **derivata direzionale** di $f$ rispetto al versore $v$ nel punto $x_0$ il limite (se esiste finito):
$$D_v(x_0)=\lim_{t\to 0}\frac{f(x_0+tv)-f(x_0)}{t}$$
- $f(x_0+tv)$ è il rapporto incrementale lungo la direzione di $v$
