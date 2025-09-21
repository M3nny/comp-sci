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

---
### Parametro d'arco
Data una parametrizzazione regolare $r(t)$ con $t\in[a,b]$, il parametro d'arco è definito come:
$$s(t)=\int^t_a||r'(\tau) ||d\tau$$
dove $s(t)$ rappresenta la lunghezza di $\gamma$ tra due suoi punti $r(a)$ e $r(t)$.

Nel caso $r(a)$ fosse l'inizio della curva e $r(t)$ la sua fine, allora avremo trovato la lunghezza della curva intera.

- $s(t)$ è di **classe** $C^1$
- $s'(t) = ||r'(t)||$
- L'**immagine** $I(s) = [0, l(\gamma)]$
- La funzione $s(t)$ è strettamente crescente e quindi **invertibile**, la funzione inversa è data da $t=t(s)$ e si ha:
$$t'(s)=\frac{1}{s'}=\frac{1}{||r'||}$$


---
### Parametrizzazione naturale
Considerando la funzione inversa del parametro d'arco $t=t(s)$, la parametrizzazione naturale di $\gamma$ si ottiene tramite:
$$\tilde{r}(s)=r(t(s))$$
tra tutte le parametrizzazioni di un arco di curva $\gamma$, questa in particolare descrive un punto che si sposta lungo la traiettoria con velocità pari a $1$
$$||\tilde{r}(s)||=1$$

>[!Example]
>$$r(t)=(2t,5t-6),\quad t\in[0,1]$$
>- **Parametro d'arco**:
>$r'(t)=(2,5);\quad ||r'(t)||=\sqrt{29}$
>$$s(t)=\int^t_0\sqrt{29}d\tau = \sqrt{29}t$$

---
### Integrali di linea di prima specie
Possiamo immaginare che il risultato di un integrale di linea sia **una proprietà che cambia lungo la curva.**
Ad esempio potrebbe essere la massa in un certo punto di un filo.

Sia $r:[a,b]\to\mathbb{R}^m$ una parametrizzazione regolare con supporto $\gamma$ e sia $f$ una funzione a valori reali, $f: A\subset\mathbb{R}^m\to\mathbb{R}$ con $\gamma \in A$. 
Si dice **integrale di linea** di $f$ lungo $\gamma$ l'integrale:
$$\int_\gamma ds = \int^b_a f(r(t))\cdot||r'(t)||dt$$
l'integrale di linea è invariante per riparametrizzazioni regolari (non importa se la velocità scalare è lenta oppure no).

>[!Example]
>Consideriamo $f(x,y,z)=3x-y+z$ e sia $\gamma$ l'arco di curva descritto dalla parametrizzazione $r(t)=(3t,4t-1,t+5)$ per $t\in[0,1]$.
>Calcolare $\int_\gamma f\space ds$
>$$\int_\gamma (3x-y+z)ds=\int^1_0(9t-4t+1+t+5)\cdot||3,4,1||\space dt=$$
>$$=\int^1_0(6t+6)\sqrt{26}\space dt =$$
>$$=6\sqrt{26}\int^1_0t+1\space dt = 6\sqrt{26}\left[\frac{t^2}{2}+t\right]^1_0=$$
>$$=9\sqrt{26}$$

