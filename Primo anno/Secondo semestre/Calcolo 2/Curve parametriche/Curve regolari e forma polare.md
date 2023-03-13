##### Ripasso su equazioni di rette parametriche
Un'[[Rette e piani#Da parametrica a cartesiana|equazione parametrica]] di una retta passante per un punto $x = (x_0, y_0)$ e direzione $v = (v_x, v_y)$ è data da:
$$\begin{cases}x=x_0+v_x(t-t_0)\\y=y_0+v_y(t-t_0)\end{cases}$$
Per passare alla **forma cartesiana** è sufficiente isolare $t$ e sostituire:
$$\begin{cases}t-t_0=\frac{x-x_0}{v_x}\\y=y_0+v_y(\frac{x-x_0}{v_x})\end{cases}$$


L'arco di una curva è **regolare** quando _il suo vettore velocità è continuo non si annulla mai_, e nel caso si annullasse in qualche punto si dice **regolare a tratti**.

- Se $r(t)$ è regolare allora $r'(t)$ definisce la direzione tangente a $\gamma$ 

Con la direzione tangente possiamo definire il **versore tangente** ($T(t)$), ovvero il vettore di lunghezza $1$ nella direzione di $r'(t)$:
$$T(t)=\frac{r'(t)}{||r'(t)||}$$

---
## Coordinate polari
Possiamo univocamente identificare un punto $P$ di coordiante $(x,y)$ tramite le coordinate polari indicate con $(\rho, \theta)$, dove:
- $\rho$ è la **distanza** di $P$ dall'origine.
- $\theta$ è **l'angolo** formato dal semiasse positivo delle ascisse ed il segmento $\overline{OP}$, con $0 \leq \theta < 2\pi$.
$$\begin{cases}x=\rho\cos(\theta)\\y=\rho\sin(\theta)\end{cases}$$
Può essere conveniente usare le coordinate polari per rappresentare alcune curve, come le **curve piane** come: $r(\theta):(x(\theta),y(\theta))$ con:
$$\begin{cases}x(\theta)=f(\theta)\cos(\theta)\\y(\theta)=f(\theta)\sin(\theta)\end{cases}\quad\theta\in [a,b]$$
le quali sono dette in **forma polare** e rappresentano un punto che ruota in senso **antiorario**, dove:
- $f(\theta)$ è la **distanza** del punto dall'origine.
- $\theta$ è l'angolo.

Il suo **vettore tangente** è dato da:
$$r'(\theta)=(f'\cos\theta-f\sin\theta,\space f'\sin\theta+f\cos\theta)$$
mentre la sua **velocità scalare** è data da:
$$||r'(\theta)||^2=(f')^2+f^2$$

#### Proprietà delle curve in forma polare
- $r(\theta)$ è **continua** _sse_ $f$ è continua in $[a,b]$ 
- $r(\theta)$ è **chiusa** _sse_ $f(a)=f(b)$ e $b-a=2k\pi$ con $k\in\mathbb{N}$ 
- $r(\theta)$ è **semplice** sse non esistono $\theta_1\in [a,b]$ e $\theta_2\in ]a,b[$ tali che $\theta_1=\theta_2+2k\pi$ e $f(\theta_1) = f(\theta_2)$ 

$r(\theta)$ non è regolare _sse_ $f'(\theta)=0$ e $f(\theta)=0$ (passa per l'origine), quindi **se non passa per l'origine è regolare**.

