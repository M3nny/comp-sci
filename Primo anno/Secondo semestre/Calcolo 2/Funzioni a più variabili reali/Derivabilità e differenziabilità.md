Estendiamo il concetto di [[Cos'è una derivata|derivata]] a funzioni di più variabili.
Sia $f:A\subseteq\mathbb{R}^2\to\mathbb{R}$ con $A$ insieme aperto. Se il seguente limite esiste finito, allora esso definisce la **derivata parziale** di $f$ rispetto a $x$ calcolata nel punto $(x_0, y_0)$:
$$\frac{\delta f}{\delta x}(x_0,y_0)=\lim_{h\to 0}\left(\frac{f(x_0+h,y_0)-f(x_0,y_0)}{h}\right)$$
analogamente la **derivata parziale** rispetto a $y$ è:
$$\frac{\delta f}{\delta y}(x_0,y_0)=\lim_{k\to 0}\left(\frac{f(x_0,y_0+k)-f(x_0,y_0)}{k}\right)$$

Se anche solo una delle derivate parziali è uguale a $\pm\infty$ in un punto allora non esiste la derivata in quel punto.

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
