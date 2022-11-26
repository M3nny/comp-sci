## Funzioni infinitesime
Una funzione si dice **infinitesima** in $x_0$ se $\lim\limits_{x\to x_0}f(x)=0$ 
Per cui due funzioni che sono entrambe _infinitesime_ in $x_0$ hanno lo **stesso ordine di infinitesimo** se esiste $l>0$ tale che:
$$\lim_{x\to x_0}\left|\frac{f(x)}{g(x)}\right|=l$$
$f=O(g)$   $f$ è 'o grande' di $g$

- $f$ ha ordine di **infinitesimo superiore** a $g$ se:
	$$\lim_{x\to x_0}\left|\frac{f(x)}{g(x)}\right|=0$$ $f=o(g)$   $f$ è 'o piccolo' di $g$ 

- $f$ ha ordine di **infinitesimo inferiore** a $g$ se:
	$$\lim_{x\to x_0}\left|\frac{f(x)}{g(x)}\right|=+\infty$$ $g=o(f)$   $g$ è 'o piccolo' di $f$ 

- Se il limite non esiste, $f$ e $g$ sono **infinitesimi non confrontabili**.

#### Principio di sostituzione degli infinitesimi
Siano $f_1, f_2, g_1, g_2$ infinitesimi simultanei (stesso ordine di infinitesimo) in $x_0$, allora:
$$\lim_{x\to x_0}\frac{f_1(x)+f_2(x)}{g_1(x)+g_2(x)}=\lim_{x\to x_0}\frac{f_1(x)}{g_1(x)}$$

## Funzioni infinite
Una funzione si dice **infinita** in $x_0$ se $\lim\limits_{x\to x_0}f(x)=\infty$ 
Per cui due funzioni che sono entrambe infinite in $x_0$ hanno lo **stesso ordine di infinito** se esiste $l>0$ tale che:
$$\lim_{x\to x_0}\left|\frac{f(x)}{g(x)}\right|=l$$
$f=O(g)$   $f$ è 'o grande' di $g$

- $f$ ha ordine di **infinito superiore** a $g$ se:
	$$\lim_{x\to x_0}\left|\frac{f(x)}{g(x)}\right|=\infty$$ $f=o(g)$   $f$ è 'o piccolo' di $g$ 

- $f$ ha ordine di **infinito inferiore** a $g$ se:
	$$\lim_{x\to x_0}\left|\frac{f(x)}{g(x)}\right|=0$$ $g=o(f)$   $g$ è 'o piccolo' di $f$ 

- Se il limite non esiste, $f$ e $g$ sono **infinitesimi non confrontabili**.

#### Principio di sostituzione degli infiniti
Siano $f_1, f_2, g_1, g_2$ infiniti simultanei (stesso ordine di infinito) in $x_0$, allora:
$$\lim_{x\to x_0}\frac{f_1(x)+f_2(x)}{g_1(x)+g_2(x)}=\lim_{x\to x_0}\frac{f_1(x)}{g_1(x)}$$
