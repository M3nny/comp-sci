## Integrali impropri
Sia $f: [a, +\infty[ \to \mathbb{R}$ continua. Se esiste finito il limite
$$\lim_{t\to +\infty} \int_a^t f(x) dx$$
allora la funzione si dice integrabile in $[a,+\infty[$ ed **il risultato del limite si dice integrale improprio** indicato con:
$$\int_a^{+\infty} f(x) dx = \lim_{t\to +\infty} \int_a^t f(x) dx$$
Analogamente con $f: ]-\infty, b]\to \mathbb{R}$ continua, se esiste finito il limite, possiamo indicare l'integrale improprio con:
$$\int_{-\infty}^b f(x) dx = \lim_{t\to +\infty} \int_t^b f(x) dx$$

Inoltre se la funzione è continua in $\mathbb{R}$ possiamo valutare l'integrale improprio:
$$\int_{-\infty}^{+\infty} f(x)dx = \int_{\mathbb{R}} f(x)dx$$
>[!Example]
>Calcoliamo $\int_1^{+\infty} \frac{1}{x^2}dx$
>$$\int_1^t \frac{1}{x^2}dx = \left[ -\frac{1}{x}\right]_1^t = -\frac{1}{t}- \left(-\frac{1}{1}\right)$$
>$$\lim_{t\to +\infty} \int_1^t \frac{1}{x^2}dx = \lim_{t\to +\infty} \left( 1-\frac{1}{t}\right) = 1$$

>**Proposizione**
>Con $a>0$ avendo $\int_a^{+\infty} \frac{1}{x^p}dx$, **converge** se $p>1$, **diverge** se $p\leq 1$

>[!Teorema del confronto]
>Date $f(x) \geq g(x)\geq 0$ per $x\in [a, +\infty[$ allora
>- Se $\int_a^{+\infty}f(x)dx$ **converge**, allora $\int_a^{+\infty}g(x)dx$ **converge**
>- Se $\int_a^{+\infty}f(x)dx$ **diverge**, allora $\int_a^{+\infty}g(x)dx$ **diverge**

#### Funzioni con asintoti verticali
Sia $f:]a,b]\to \mathbb{R}$ continua, se esiste finito il suo limite, potremmo calcolare l'integrale improprio tramite:
$$\int_a^bf(x)dx=\lim_{t\to a^+}\int_t^bf(x)dx$$
oppure analogamente con $f: [a,b[ \to \mathbb{R}$:
$$\int_a^bf(x)dx=\lim_{t\to b^-}\int_a^tf(x)dx$$
>**Proposizione**
>Con $a>0$ avendo $\int_0^{a} \frac{1}{x^p}dx$, **converge** se $p<1$, **diverge** se $p\geq 1$

>[!Teorema del confronto]
>Date $f(x) \geq g(x)\geq 0$ per $x\in ]x_0, a]$
>- Se $\int_{x_0}^{a}f(x)dx$ **converge**, allora $\int_{x_0}^{a}g(x)dx$ **converge**
>- Se $\int_{x_0}^{a}f(x)dx$ **diverge**, allora $\int_{x_0}^{a}g(x)dx$ **diverge**

## Calcolo di aree
Per calcolare l'area compresa tra il grafico della funzione e l'asse $x$, dobbiamo calcolare l'integrale del valore assoluto di $f$:
$$A = \int_a^b|f(x)|dx$$
Usiamo il valore assoluto perchè nel caso un pezzo di area fosse sotto l'asse $x$ non va a diminuire il resto dell'area sopra l'asse, ma viene sommata anch'essa.

Se voglio calcolare l'area tra due funzioni, devo prima trovare quale sta sopra e poi sottrargli quella che sta sotto:
$$A=\int_a^b|f(x)-g(x)|dx$$
Nel caso di accavallassero le funzioni, devo trovare il punto $c$ in cui si incontrano e procedere come segue:
$$A= \int_a^cf(x)-g(x)dx+\int_c^bg(x)-f(x)dx$$
