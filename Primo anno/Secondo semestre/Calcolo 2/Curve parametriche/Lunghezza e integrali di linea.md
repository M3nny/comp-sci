Possiamo misurare la lunghezza di una curva tramite la sua **poligonale** $l(\mathcal{P})$ la quale rappresenta la curva rettificata.
![[Poligonale.svg]]
Per ottenere la _poligonale_ dobbiamo prendere tanti punti della curva e collegarli in sequenza, infine la lunghezza di quest'ultima è data da dalla somma dei suoi segmenti:
$$l(\mathcal{P})=\sum^n_{i=1}||r(t_i)-r(t_i-1)||$$
La lunghezza della poligonale è minore di quella della curva effettiva $l(\mathcal{P})<l(\gamma)$

$\gamma$ si dice **rettificabile** se $\text{sup}_{\mathcal{P}}\space l(\mathcal{P}) < +\infty$ dove $\mathcal{P}$ è una porzione qualsiasi di partizione di $[a,b]$. In tal caso la lunghezza di $\gamma$ $l(\gamma)$ vale $l(\gamma)=\text{sup}_{\mathcal{P}}\space l(\mathcal{P})$.

>[!Lunghezza di una curva]
>Se prendiamo una parametrizzazione regolare della curva $r:[a,b]\to\mathbb{R}^m$ , allora la curva $\gamma$ è **rettificabile** e la sua lunghezza è data da:
>$$l(\gamma)=\int^b_a||r'(t)||dt$$
>

>[!Tip]
>È possibile trovare integrali complessi del tipo:
>$$\int\sqrt{1+t^2}dt=\frac{1}{2}\ln(t+\sqrt{t^2+1})+\frac{1}{2}t\sqrt{t^2+1}+c$$


### Riparametrizzazione
Due parametrizzazioni sono legate se esiste una funzione che le lega.
Avendo $r_1:[a,b]\to\mathbb{R}^m$ e $r_2:[c,d]\to\mathbb{R}^m$, data una funzione di classe $\mathcal{C}^1[c,d]$ e crescente, allora $r_1(s)=r_2(t(s))$ ovvero $r_2$ è riparametrizzazione di $r_1$.

_N.B._
La lunghezza di $\gamma$ è invariante per le riparametrizzazioni, quindi
$$\int^b_a||r_1'(t)||dt=\int^d_c||r_2'(s)||ds$$

