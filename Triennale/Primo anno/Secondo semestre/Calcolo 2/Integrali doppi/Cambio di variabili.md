Quando abbiamo un dominio non semplice, ovvero quando non ci sono linee orizzontali/verticali che intersecano entrambe le funzioni, e vediamo che sono usate delle circonferenze, possiamo passare alle **coordinate polari** applicando la trasformazione $T$ per cui:
$$\begin{cases}x=\rho\cos(\theta)\\y=\rho\sin(\theta)\end{cases}$$
dove:
- $\rho$ è la lunghezza del raggio.
- $\theta$ è dove è compresa la circonferenza nell'asse $y$.

In questo modo passiamo da una circonferenza ad un rettangolo.

![[Cambio variabili.svg|700]]

La formula per calcolare l'integrale dopo la trasformazione è il risultato di calcoli tratti dalla **matrice Jacobiana** e concetti di **diffeomorfismo**:
$$\int\int_Df(x,y)\space dxdy\quad = \quad \int\int_{D'}f(\rho\cos(\theta),\rho\sin(\theta))\cdot\rho\space d\rho d\theta$$

## Baricentro
Dato un dominio di cui è possibile trovare l'area, il **baricentro** è il punto di coordinate $(x_C, y_C)$ le quali sono date da:
$$x_C=\frac{\int\int_Dx\space dxdy}{A_D},\quad y_C=\frac{\int\int_Dy\space dxdy}{A_D}$$
dove $A_D$ è l'area di $D$ calcolata tramite come:
$$A_D=\int\int_D1\space dxdy$$

>[!Example]
>Dato il seguente grafico determinare l'area della superficie.
>- Gli angoli sono angoli fondamentali
>- Le curve sono circonferenze con centro $(0,0)$
>![[Es integrale doppio.svg|300]]
>$D=D_1\cup D_2$
>$$D_1'=\{(\rho,\theta)\in\mathbb{R}^2: 0\leq\rho\leq 2,\space \frac{\pi}{4}\leq\theta\leq\frac{\pi}{2}\}$$
>$$D_2'=\{(\rho,\theta)\in\mathbb{R}^2: 1\leq\rho\leq 3,\space 0\leq\theta\leq\frac{\pi}{4}\}$$
>
>Area $D_1$
>$$\int\int_{D_1}dxdy=\int_0^2\int_\frac{\pi}{4}^\frac{\pi}{2}1\cdot\rho\space d\rho d\theta =$$
>$$=\int_0^2\rho\space d\rho\cdot\int_\frac{\pi}{4}^\frac{\pi}{2}d\theta = \left[\frac{\rho^2}{2}\right]_0^2\cdot\left[\theta\right]_\frac{\pi}{4}^\frac{\pi}{2}=$$
>$$=\frac{\pi}{2}$$
>
>Area $D_2$
>$$\int_1^3\int_0^\frac{\pi}{4}1\cdot\rho\space d\rho d\theta=$$
>$$=\left[\frac{\rho^2}{2}\right]_1^3\cdot\left[\theta\right]_0^\frac{\pi}{4}=$$
>$$=\pi$$
>
>Area totale $D=\frac{\pi}{2}+\pi = \frac{3}{2}\pi$
>Con $D$ ora è possibile trovare il baricentro, ma dato che è diviso in due, per trovare $x_C$ dovremmo fare:
>$$x_C=\int\int_{D_1}x\space dxdy+\int\int_{D_2}x\space dxdy$$
>e poi bisognerà dividere il risultato per l'area trovata precedentemente.
>I passaggi sono analoghi per trovare $y_C$, basta sostituire $y$ a $x$ nell'equazione $x_C$ e procedere allo stesso modo.
