Come negli [[Integrali definiti|integrali ad una variabile]] andavamo a trovare l'area sottesa alla funzione con la somma dei rettangoli (trapezoidi), ora calcoliamo il volume del solido tramite la somma dei parallelepipedi.

![[Integrale doppio.svg|400]]


Sia $f:[a.b]\times[c,d]\to\mathbb{R}$ (dominio rettangolare) e $f$ limitata, $f$ si dice integrabile nel dominio rettangolare se il valore più piccolo delle somme integrali superiori è uguale al valore più grande delle somme integrali inferiori.
- Se $f$ è continua allora $f$ è integrabile.

>[!Teorema di riduzione dell'integrale doppio]
>Sia $D=[a,b]\times[c,d]$ il dominio rettangolare e sia $f:D\to\mathbb{R}$ continua, allora:
>$$\int_a^b\left(\int_c^df(x,y)dy\right)dx=\int_c^d\left(\int_a^bf(x,y)dx\right)dy$$
>Ovvero fare integrare prima per $x$ e poi per $y$ o viceversa non cambia.
>
>>Potrebbe essere più laborioso però fare l'integrale prima di $x$ rispetto che di $y$, o viceversa.

## Funzioni a variabili separate
Se la funzione integranda è prodotto di due funzioni $g(x)h(y)$ allora l'integrale è dato dal prodotto degli integrali di $g$ e $h$:
$$\int_a^b\left(\int_c^dg(x)\cdot h(y)dy\right)dx=\left(\int_a^bg(x)dx\right)\cdot\left(\int_c^dh(y)dy\right)$$

>[!Example]
>$\int\int_De^{2x}\cos(3y)dxdy\quad D=[0,1]\times[0,\pi]$
>$$\int_0^1\left(\int_0^\pi e^{2x}\cos(3y)dy\right)dx$$
>Se integro prima per $y$ posso tirare fuori dal primo integrale $e^{2x}$ dato che è costante per $dy$.
>$$\int_0^1e^{2x}\left(\int_0^\pi\cos(3y)dy\right)dx$$
>Ottengo così:
>$$\left(\int_0^\pi\cos(3y)dy\right)\cdot\left(\int_0^1e^{2x}dx\right)=\left[\frac{1}{3}\sin(3y)\right]_0^\pi\cdot\left[\frac{e^{2x}}{2}\right]_0^1$$

## Insiemi semplici
- $y-$semplice: se $\exists_{g_1,g_2}:[a,b]\to\mathbb{R}$ tali che:
$$E=\{(x,y)\in\mathbb{R}^2:x\in[a,b],\space g_1(x)\leq y \leq g_2(x)\}$$


![[Y-semplice.svg]]
- $x-$semplice: se $\exists_{h_1,h_2}:[c,d]\to\mathbb{R}$ tali che:
$$E=\{(x,y)\in\mathbb{R}^2:x\in[c,d],\space h_1(x)\leq x \leq h_2(x)\}$$
![[X-semplice.svg]]
>Per capire come varia $x$ traccio una linea orizzontale tra $0$ e $1$, la retta deve intersecare le due funzioni $h_1,h_2$ la prima che incontra sarà $h_1$, discorso analogo per capire come varia $y$ in $y-$ semplice.

- $E$ si dice **regolare** se è unione finita di insiemi semplici.

>[!Teorema]
>Se $f:E\to\mathbb{R}^2$ è continua e finita, allora $f$ è integrabile sul dominio $\Omega$.

>[!Teorema di riduzione su domini semplici]
>Sia $f:\Omega\to\mathbb{R}^2$ continua
>- $\Omega$ è $x-semplice$; $y\in[c,d]$; $h_1(y)\leq x\leq h_2(y)$
>$$\int\int_\Omega f(x,y)dxdy=\int_c^d\left(\int_{h_1(y)}^{h_2(y)}f(x,y)dx\right)dy$$
>- $\Omega$ è $y-semplice$; $y\in[a,b]$; $g_1(y)\leq x\leq g_2(y)$
>$$\int\int_\Omega f(x,y)dxdy=\int_a^b\left(\int_{g_1(y)}^{g_2(y)}f(x,y)dy\right)dx$$

>[!Example]
>$\int\int_\Omega 2x\space dxdy\quad \Omega=\{(x,y)\in\mathbb{R}^2:x\geq 0,y\geq\frac{\sqrt{3}}{2},\frac{x^2}{4}+y^2\leq 1\}$
>![[Elisse esercizio.svg]]
>Abbiamo quindi che:
>$$\frac{\sqrt{3}}{2}\leq y \leq 1;\quad 0\leq x \leq \sqrt{4-4y^2}$$
>- Prendo la parte positiva dell'elissi perchè nel grafico è la parte positiva che ci interessa.
>
>Per trovare la parte evidenziata di area dovrò risolvere l'integrale:
>$$\int_{\frac{\sqrt{3}}{2}}^1\left(\int_0^{\sqrt{4-4y^2}}2x\space dx\right)dy$$
