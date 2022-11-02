Il principio di induzione è una tecnica di prova usata per fare dimostrazioni dove esistono infiniti elementi, ci riferiamo in particolare all'insieme $\mathbb{N}$.

Vogliamo dimostrare che $P(x)$ sia vera su $\mathbb{N}$, per farlo dobbiamo dimostrare che:
- $P(0)$ è vera (**caso base**);
- $P(n) \implies P(n+1) \space \forall n\geq 0$ (**passo induttivo**).

>[!Example]
>**Dimostrare che la somma dei numeri naturali da $0$ a $n$ con $n\geq 0$ è uguale a $\frac{n(n+1)}{2}$**:
>
>Dimostrazione per induzione su $n$:
>- **Caso base**: $0=\frac{0(0+1)}{2}$;
>- **Passo induttivo**: <u>Supponiamo</u> che $n\geq 0$ e che $S(n)=\frac{n(n+1)}{2}$ (_ipotesi induttiva_).
>	Ora dobbiamo dobbiamo dimostrare che $S(n+1) = \frac{(n+1)(n+2)}{2}$.
>	Per cui $S(n+1)=0+1+2+...+n+(n+1)=S(n)+(n+1)$ che equivale a dire (sostituendo $S(n)$ con _l'ipotesi induttiva_) che:
>	$$\frac{n(n+1)}{2}+(n+1)=(n+1)(\frac{n}{2}+1)=(n+1)(\frac{n+2}{2})=\frac{(n+1)(n+2)}{2}$$

## Principio di induzione forte
Il principio di induzione forte viene utilizzato per fare più ipotesi e andare meglio nella dimostrazione.

Per dimostrare $P(x)$ è vera per ogni numero naturale $x \geq k$ è sufficiente mostrare che:
- $P(k)$ è vera (**caso base**);
- $P(k) \implies P(n+1) \forall n \geq k$ (**passo induttivo**)

>[!Example]
>**Dimostrare che ogni numero naturale $n\geq 2$ è scomponibile in fattori primi**:
>
>Dimostrazione per induzione completa su $n$:
>- **Caso base** $n=2$:
>Poichè $2$ è un numero primo, $2$ è scomponibile in fattori primi.
>- **Ipotesi induttiva**:
>$\forall x: 2\leq x \leq n$, $x$ è scomponibile in fattori primi.
>- **Passo induttivo**: verifico che anche $n+1$ è divisibile in fattori primi
>Ci sono due possibilità:
>1. $n+1$ è un numero primo:
>	In questo caso una scomposizione in fattori primi di $n+1$ è data dal numero stesso.
>2. $n+1$ non è un numero primo, quindi esistono $y,z\in \mathbb{N}$ tali che $n+1=y\cdot z$ e $y,z\neq 1,n+1$
>
>Quindi $y$ e $z$ appartengono all'intervallo $[2,n]$ cioè:
>$$2\leq y \leq n \quad \text{e} \quad 2\leq z \leq n$$
>Per ipotesi induttiva sia $y$ che $z$ sono scomponibili in fattori primi, cioè:
>$$y=p_1\cdot \cdot \cdot p_r \text{ con } p_1 \cdot \cdot \cdot p_r\text{ numeri primi }$$
>$$y=q_1\cdot \cdot \cdot q_s \text{ con } q_1 \cdot \cdot \cdot q_s\text{ numeri primi }$$
>Quindi $n+1 = y \cdot z=(p_1\cdot \cdot  \cdot p_r)(q_1 \cdot \cdot \cdot q_s)$
>Cioè $n+1$ ammette una scomposizione in fattori primi.
>
