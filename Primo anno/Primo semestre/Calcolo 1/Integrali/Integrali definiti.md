Data una funzione **continua e limitata**, gli integrali definiti servono per calcolare l'area sottesa ad una funzione.

### Funzioni positive e negative
- Se l'intervallo su cui vogliamo calcolare l'integrale è **negativo**, otterremo un'area negativa per cui dovremmo considerarla con il segno opposto.
- Se l'integrale che vogliamo calcolare invece ha una parte di intervallo positiva e una parte negativa dovremmo dividere l'integrale in più parti.

## Definizione
Una funzione si dice **integrabile** su $[a,b]$ se le somme tra integrali inferiori e superiori convergono allo stesso valore, tale valore è proprio l'integrale di $f$ in $[a,b]$ e viene indicato come:
$$\int^b_a f(x)\space dx$$
dove:
- l'intervallo $[a,b]$ è il dominio di integrazione;
- $f$ è la funzione integranda.

>[!Tip] Nota sugli estremi di integrazione
>- Se $b<a: \int^b_a f(x) \space dx = - \int^a_b f(x)\space dx$;
>- Se $a=b: \int^b_a f(x) \space dx = 0$.

## Proprietà degli integrali definiti
- Con $a<b$, la funzione è integrabile per ogni $a,b \in \mathbb{R}$ e si ha:
$$\int_a^b \alpha f(x)+ \beta g(x) dx = \alpha \int^b_a f(x)dx + \beta \int^b_a g(x)dx$$
- Se la funzione integranda è $\geq 0$ allora anche il risultato dell'integrale sarà $\geq 0$
- Con due funzioni integrande $f(x)$ e $g(x)$, se $f(x)\geq g(x)$ allora anche il risultato dell'integrale di $f(x)$ sarà $\geq$ il risultato dell'integrale di $g(x)$
- $|\int^b_a f(x)dx| \leq \int^b_a |f(x)|dx$
- $\forall c\in [a,b]$ si ha $\int^b_a f(x) dx = \int^c_a f(x)dx + \int_c^b f(x)dx$

#### Valor medio integrale
Sia $f: [a,b] \to \mathbb{R}$ integrabile, si chiama **valor medio integrale** la quantità:
$$\frac{\int_a^b f(x)dx}{b-a}$$

## Teorema fondamentale del calcolo integrale
$$\int^b_a f(x) dx = [F(x)]^b_a$$
>[!Example]
>$$\int_0^2 x^2 dx = \left[ \frac{x^3}{3} \right]_0^2 = \frac{2^3}{3}-\frac{0}{3} = \frac{8}{3}$$

