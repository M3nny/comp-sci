Generalmente una funzione è crescente quando: $x_1 < x_2 \implies f(x_1)<f(x_2)$.
Vediamo ora questo concetto applicato a dei punti specifici.

- $f$ è **crescente** in $x_0$ se esiste un intorno $I_{x_0}$ per cui i punti compresi tra $[x_0 - \delta, I_{x_0}]$ sono minori di $x_0$ mentre i punti compresi tra $[x_0, x_0 + \delta]$ sono maggiori di $x_0$.
$$f(x)\leq f(x_0) \quad\forall x < x_0, \space x\in I_{x_0}$$$$f(x)\geq f(x_0) \quad \forall x > x_0, \space x\in I_{x_0}$$
- $f$ è **decrescente** in $x_0$ se esiste un intorno $I_{x_0}$ per cui i punti compresi tra $[x_0 - \delta, I_{x_0}]$ sono maggiori di $x_0$ mentre i punti compresi tra $[x_0, x_0 + \delta]$ sono minori di $x_0$.
$$f(x)\geq f(x_0) \quad\forall x < x_0, \space x\in I_{x_0}$$$$f(x)\leq f(x_0) \quad \forall x > x_0, \space x\in I_{x_0}$$
- $x_0$ è un **massimo** relativo per $f$ se considerato un intervallo $I_{x_0}$ abbiamo che $x_0$ è maggiore di tutti gli altri punti presenti nell'intervallo.
$$f(x_0)\geq f(x), \space \forall x \in I_{x_0}$$
- $x_0$ è un **minimo** relativo per $f$ se considerato un intervallo $I_{x_0}$ abbiamo che $x_0$ è minore di tutti gli altri punti presenti nell'intervallo.
$$f(x_0)\leq f(x), \space \forall x \in I_{x_0}$$

Grazie alle derivate è possibile trovare i punti in cui una funzione cresce e decresce.
Sia $f$ derivabile in un punto $x_0$:
- Se $f'(x_0) > 0$ allora $f$ è <u>strettamente crescente</u> in $x_0$;
- Se $f'(x_0) < 0$ allora $f$ è <u>strettamente decrescente</u> in $x_0$;
- Se $f$ è <u>crescente</u> in $x_0$ allora $f'(x_0) \geq 0$;
- Se $f$ è <u>decrescente</u> in $x_0$ allora $f'(x_0) \leq 0$.

## Punti stazionari
Considerando $f$ derivabile in $x_0$ e $x_0$ un punto interno al dominio:
Se $f'(x_0) = 0$ allora $x_0$ sarà un massimo o un minimo.
Inoltre se $f'(x_0) = 0$ e la funzione non è costante attorno a $x_0$ allora $x_0$ è detto **punto stazionario**.

Tipi di punti stazionari:
1. Se $f(x)$ **crescente** per $x<x_0$ e $f(x)$ **decrescente** per $x>x_0$ con $x\in I_{x_0}$ allora $x_0$ è un **massimo locale**;
2. Se $f(x)$ **decrescente** per $x<x_0$ e $f(x)$ **crescente** per $x>x_0$ con $x\in I_{x_0}$ allora $x_0$ è un **massimo minimo**;
3. Se $f(x)$ **crescente** per $x<x_0$ e $x>x_0$ allora $x_0$ è un **punto di flesso a tangente orizzontale**;
4. Se $f(x)$ **decrescente** per $x<x_0$ e $x>x_0$ allora $x_0$ è un **punto di flesso a tangente orizzontale**.