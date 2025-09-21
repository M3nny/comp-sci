### Asintoto verticale
Data una funzione $f: A \to \mathbb{R}$ ed un punto di accumulazione $x_0$, definiamo come asintoto verticale la retta $x=x_0$ se:
$$\lim_{x\to x_0^\pm}f(x)=\pm \infty$$
### Asintoto orizzontale
Data una funzione $f: A \to \mathbb{R}$ definiamo come asintoto orizzontale la retta $y=q$ se:
$$\lim_{x\to\pm\infty}f(x)=q$$
### Asintoto obliquo
Data una funzione $f: A \to \mathbb{R}$ definiamo come asintoto obliquo la retta $y=mx+q$ se:
$$\lim_{x\to\pm\infty}(f(x)-mx-q)=0$$

>[!Example] Esempio esame
>$$f(x)=\begin{cases} x^2\cdot \sin(\frac{1}{x}); &x\neq 0\\
>0; &x=0
>\end{cases}$$
>- **Continuità**: $\lim\limits_{x\to 0}f(x)=0$
>- **Derivabilità**: $f'(x)=2x\cdot \sin{\frac{1}{x}}+x^2\cdot \cos(\frac{1}{x})\cdot (-\frac{1}{x^2}) =$
> $$ = 2x\cdot \sin(\frac{1}{x})-\cos(\frac{1}{x})$$
> Andiamo a fare il limite che tende a $0$ per la derivata appena trovata:
> $$\lim_{x\to 0^+}f'(x)=\nexists$$
> Dato che non esiste (a causa dell'oscillazione del coseno di $\infty$) faccio il rapporto incrementale in $x_0=0$
> $$\lim_{x\to 0}\frac{f(x)-f(x_0)}{x-x_0}=\lim_{x\to 0}\frac{x^2\sin(\frac{1}{x})-0}{x-0}=0$$
> Quindi $f$ è derivabile in $x_0=0$, $f'(0)$ sarà quindi uguale a $0$.
> Ma $f'(x)$ non è una funzione continua perchè $\lim\limits_{x\to 0}f'(x)\neq f'(0)$
