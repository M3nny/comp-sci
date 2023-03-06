Una curva parametrica si trova sotto la forma di funzione a valori vettoriali.
$$\begin{split} f\colon &\mathbb{R} \to \mathbb{R}^2\newline &t \mapsto (x(t), y(t)) \end{split}$$


Vediamo ad esempio:
$$\begin{split} f\colon &\mathbb{R} \to \mathbb{R}^2\newline &t \mapsto (t^2-t, 2t-1) \end{split}$$

![[Curva parametrica.png|350]]


Indichiamo con delle frecce il **verso di percorrenza**, il quale va dal tempo $t$ più basso a quello più alto.

Otteniamo **l'equazione cartesiana del supporto** mettendo a sistema $x(t)$ e $y(t)$
$$\begin{cases}x=t^2+t\\y=2t-1\end{cases}\quad\Rightarrow\quad\begin{cases}x=\left(\frac{y+1}{2}\right)^2+\frac{y+1}{2}\\t=\frac{y+1}{2}\end{cases}\quad\Rightarrow\quad\begin{cases}x=\frac{1}{4}y^2+y+\frac{3}{4}\\t=\frac{y+1}{2}\end{cases}$$

- Nel caso la funzione fosse stata $f: [-1,1]\to\mathbb{R}^2$ allora avremo ottenuto un **arco di parabola** che va da $t_{-1}$ a $t_1$

Quello disegnato fin'ora tuttavia non è il grafico di $f$, bensì la traiettoria della sua curva parametrica.
Il grafico di $f$ è dato da (dominio $\cdot$ codominio), lo troviamo quindi in forma:
$$G(f)={(t,x,y)\in\mathbb{R}\times\mathbb{R}^2}:x=x(t)\land y=y(t)\quad\text{ovvero}\quad(t,x(t),y(t))\in\mathbb{R}^3$$
>[!Tip]
>$$\text{Circonferenza}$$
>Si presenta come $(x-x_0)^2+(y-y_0)^2=r^2$
>- Centro: $(x_0,y_0)$
>- Raggio: $r$
>$$\text{Elisse}$$
>Si presenta come: $\frac{(x-x_0)^2}{a^2}+\frac{(y-y_0)^2}{b^2}=1$
>- Centro: $(x_0,y_0)$
>- Semiasse orizzontale: $a$
>- Semiasse verticale: $b$
>
>Quando a sistema ho una funzione trigonometrica con argomento $t$ è consigliabile non isolare $t$.

>[!Definizione (Limite per funzioni a valori vettoriali)]
>Sia $I\subset\mathbb{R}$ intervallo e $r:I\to\mathbb{R}^m$ una funzione a valori vettoriali.
>Sia $t_0\in I$ si dice che:
>$$\lim_{t\to t_0}r(t)=s,\quad (s\in\mathbb{R})$$
>se vale
>$$\lim_{t\to t_0}||r(t)-s||=0$$
>Equivale al limite componente per componente cioè:
>$$\lim_{t\to t_0}r(t)=s\iff\lim_{t\to t_0}r_i(t)=s_i\quad \forall i = 1,...,m$$

### Continuità/Derivabilità/Integrabilità
Una funzione a valori vettoriali $r(t)=r_1(t),...,r_m(t))$ è continua/derivabile/integrabile sse tutte le sue componenti lo sono.

Una funzione a valori vettoriali $r(t)$ è di classe $n$ sse tutte le sue componenti sono di classe $n$:
$$r(t)\in \mathcal{C}^n(I)\quad\text{sse}\quad r_i(t)\in\mathcal{C}^n(I)$$

### Arco di curva
Sia $I\subset\mathbb{R}$ un intervallo e $r:I\to\mathbb{R}^m$ una funzione continua allora si dice _arco di curva o cammino_.

Indicando con $\gamma$ la curva:
- $r(t)$ costituisce una **parametrizzazione della curva** di $\gamma$ 
- $r'(t)$ rappresenta la **velocità istantanea** del punto (vettore tangente a $\gamma$)
- $v(t)=||r'(t)||\quad v(t)\in\mathbb{R}$ è la **velocità scalare**
	- Se e solo se $r'(t)=0$ allora $v(t)=0$ e $r'(t)$ non può rappresentare la direzione tangente.
- $r''(t)$ rappresenta l'**accelerazione istantanea**

### Curve chiuse, semplici e piane
Sia $r: I = [a,b]\to\mathbb{R}^m$ una curva parametrica indicata con $\gamma$
1. $\gamma$ è **chiusa** se $r(a)=r(b)$ ovvero se l'inizio è uguale alla fine
2. $\gamma$ è **semplice** se "non si interseca" (tranne nel punto iniziale e finale)
3. $\gamma$ è **piana** se il supporto si trova su un piano.

![[Curve semplici chiuse.svg]]
