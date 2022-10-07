# Operazioni tra funzioni

## Operazioni base
- **Somma**: 
	- $h=f+g$ tale che $h(x)=f(x)+g(x)$ con dominio: $D_h=D_f\cap D_g$ 
- **Prodotto**:
	- $h=f\cdot g$ tale che $h(x)=f(x)\cdot g(x)$ con dominio: $D_h=D_f\cap D_g$ 
- **Rapporto**:
	- $h=f/g$ tale che $h(x)=\frac{f(x)}{g(x)}$ con dominio: $D_h=\{x\in \mathbb{R}|(x\in D_f \cap D_g) \land (g(x) \neq 0\}$

## Funzione composta
$h=g\circ f$:
$$h(x)=(g\circ f)(x)=g(f(x))$$
con dominio: $D_h=\{x\in \mathbb{R}|(x\in D_f)\land (f(x)\in D_g)\}$
>[!Example]
>$f(x)=\sqrt{x} \quad g(x)=\sqrt{1-x}$
>$D_f=[0,+\infty[ \quad D_y=]-\infty ,1]$
>
>$h=g\circ f; \quad h(x)=(g\circ f)(x)=g(f(x))=g(\sqrt{x})=\sqrt{1-\sqrt{x}}$
>
>**Dominio**:
>$f(D) = \begin{cases} x\geq 0 \\ \sqrt{x} \leq 1\end{cases}$
>
>$D_h=[0,1]$

## Funzione inversa
Perchè una funzione sia invertibile, essa **deve essere biettiva**, la possiamo scrivere come:
$$f^{-1}:B \mapsto D$$
$$y \mapsto x = f^{-1}(y)$$
- $f^{-1}(B)=D$, l'immagine di $f^{-1}$ è uguale al dominio di $f$
- Due casi noti di funzione inversa sono le funzioni: $arcsin(x)$ e $arccos(x)$, le quali invertono le funzioni del seno e coseno, nell'esempio che segue vediamo il <u>seno</u> in rosso e la sua funzione inversa in blu; da notare anche che l'arcoseno agisce sulla restrizione del seno che ha intervallo $[-\frac{\pi}{2}, \frac{\pi}{2}]$.
![[Sin arcsin.png]]




