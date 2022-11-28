Serve per risolvere forme indeterminate nei limiti, ci consente quindi di approssimare una funzione derivabile $n$ volte vicino ad un punto.

### Definizione
Sia una funzione derivabile $n$ volte in $x_0$, chiamiamo **Polinomio di Taylor** di ordine $n$ della funzione $f$ relativo al punto $x_0$ il seguente polinomio:
$$T_{n,x_0}=\frac{(x_0)}{0!)}+\frac{f'(x_0)}{1!}(x-x_0)+\frac{f''(x_0)}{2!}(x-x_0)^2+...=\frac{f^{(n)}(x_0)}{n!}(x-x_0)^n$$
- Quando $x_0 = 0$ e quindi si ottiene $T_{n,0}(x)$ viene anche chiamato **polinomio di McLaurin**.

>Polinomi di Taylor di ordine superiore forniscono un'approssimazione migliore della funzione $f$ attorno $x_0$.

>[!Example]
>Prendiamo in considerazione il polinomio di McLaurin sulla funzione $\sin(x)$
>$$T_{n,0}=0+\frac{1}{1!}x+\frac{0}{2!}x^2-\frac{1}{3!}x^3+\frac{0}{4!}x^4+\frac{1}{5!}x^5+...$$
![[Taylor.svg]]
Possiamo notare come al crescere del valore di $n$ nel polinomio di Taylor la funzione assomigli sempre di più a quella originale.

## Formula di Taylor-Peano
Serve per dare una stima dell'errore di approssimazione del polinomio di Taylor.

$$f:]a,b[\to \mathbb{R}; \quad x_0\in]a,b[$$
$f$ derivabile almeno $n-1$ volte in $]a,b[$ e derivabile almeno $n$ volte in $x_0$.
Possiamo scrivere la stima dell'errore come:
$$w_n(x)=f(x)-T_{n,x_0}(x)$$
$w_n(x)$ è **infinitesima** rispetto a $x-x_0)^n$ per $x\to x_0$ cioè:
$$\lim_{x\to x_0}\frac{w_n(x)}{(x-x_0)^n}=0$$
- Vicino a $x_0$ si ha "o piccolo":
	$$f(x)=T_{n,x_0}+o((x-x_0)^n)$$
	dove $o((x-x_0)^n)$ è il **resto in forma di Peano**.

## Formula di Taylor-Lagrange
Un'altro modo per trovare il resto associato al polinomio di Taylor è la formula di Taylor-Lagrange nel caso di funzioni derivabili $n+1$ volte.

$$f:]a,b[\to \mathbb{R}; \quad x_0\in ]a,b[$$
$f$ derivabile $n+1$ volte in $]a,b[$ e $f^{(n)}$ continua allora esiste un punto $c$ per cui:
$$f(x)=T_{n,x_0}(x)+\frac{f^{(n+1)}(c)}{(n+1)!}(x-x_0)^{n+1}$$
- Dove $\frac{f^{(n+1)}(c)}{(n+1)!}(x-x_0)^{n+1}$ è il **resto in forma di Lagrange**.

#### Sviluppi asintotici
Sviluppando un polinomio di Taylor come nell'esempio di sopra, si otterrà uno **sviluppo asintotico**.
