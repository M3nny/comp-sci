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