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
- $P(k) \implies P(n+1) \space \forall n \geq k$ (**passo induttivo**).

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

## Funzioni ricorsive
Le funzioni ricorsive vengono utilizzare per esprimere facilmente una funzione.
Posso definire una funzione ricorsiva se essa non possiede catene discendenti infinite.

Per dimostrare che $P(x)$ è vera $\forall n \in \mathbb{N}$  basta dimostrare che:
- $P(0)$ è vera (**caso base**);
- $P(n-1) \implies P(n) \space \forall n > 0$ (**passo induttivo**).

>[!Example]
>$$f(n)=2$$
>Possiamo definirla in modo induttivo come segue:
>**caso base** $n=0$:
>$f(0)=2^0=1$
>**Passo induttivo** $n>0$:
>$f(n)=2^n=2^{n-1}\cdot 2$
>Possiamo riscriverla come:
>$$\begin{cases}
>1 & \text{se }n=0\\
>2\cdot f(n-1) & \text{se } n>0
>\end{cases}$$
>
>Dimostrare che la funzione $f(n)=2^n$ è "ben definita" (che fa quello che ci aspettiamo) per ogni numero naturale in $n$:
>**Caso base** $n=0$:
>$f(n)=1=2^0$
>**Ipotesi induttiva**:
>Assumiamo ben definita $f(n-1)=2^{n-1}$
>**Passo induttivo**:
>Dimostro che $f(n)=2^n$
>
>$$f(n)=2\cdot f(n-1) \text{ per definizione di f}$$
>$$=2\cdot 2^{n-1} \text{ per ipotesi induttiva}$$
>$$=2^n \text{ per le regole dell'algebra}$$


