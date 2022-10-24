Sia data una funzione $f:A\subseteq \mathbb{R}$ e sia $x_0\in \mathbb{R}$ un [[Elementi di topologia di R#Punti isolati e di accumulazione|punto di accumulazione]] per $A$. Diremo che $l\in \mathbb{R}$ è il limite di $f$ per $x$ tendente a $x_0$:
$$\lim_{x\to x_0}f(x)=l$$
se fissato comunque un $\epsilon>0$ , è possibile in corrispondenza ad esso trovare un $\delta_\epsilon >0$ tale che :
$$\forall x \in A,\space x\neq x_0,\space \text{ tale che }|x-x_0|<\delta_\epsilon \text{ si abbia } |f(x)-l|<\epsilon$$

>[!Example]
>Data $f(x)=\frac{x^2-1}{x-1}$, verificare che $\lim\limits_{x\to 1}f(x)=2$.
>- Mostriamo che $\forall \epsilon >0 \space \exists \delta_\epsilon >0$:
>$$|x-1|<\delta_\epsilon \implies |f(x)-2|<\epsilon \text{ con } x\neq 1$$
>$$|f(x)-2|<\epsilon\iff |\frac{x^2-1}{x-1}-1|<\epsilon \iff |x+1-2|<\epsilon$$
>Quindi, basta porre $\delta_\epsilon =\epsilon$ e si ha $|x-1|<\delta_\epsilon \implies |f(x)-2|<\epsilon$.


>[!Teorema]
>**Teorema di unicità del limite**
>Siano $l_1 e l_2 \in \mathbb{R}$ e supponiamo: 
>$$\lim_{x\to x_0}f(x)=l_1 \quad \text{e}\quad \lim_{x\to x_0}f(x)=l_2$$
>allora si deve avere che $l_1=l_2$ ovvero se il limite esiste allora è <u>unico</u>.
>
>---
>**Teorema di permanenza di segno**:
>- Se una funzione ha limite positivo $\lim\limits_{x\to x_0}f(x)=l>0$ allora esiste un intorno $I_{x_0}$ per cui $f(x)>0 \space \forall x \in I_{x_0}$;
>- Se una funzione ha limite negativo $\lim\limits_{x\to x_0}f(x)=l<0$ allora esiste un intorno $I_{x_0}$ per cui $f(x)<0 \space \forall x \in I_{x_0}$

## Limiti infiniti
Fin ora abbiamo trattato **limiti  finiti** dove in $\lim\limits_{x\to x_0}f(x)=l$ abbiamo che $x_0\in \mathbb{R}$ e $l\in \mathbb{R}$; ora andremmo a vedere i limiti per cui $x_0$ e/o $l$ sono infiniti:
![[Limite infinito.svg]]
Vediamo che $]-\infty,b[$ è un [[Elementi di topologia di R#Palle circolari|interno]] di $-\infty$ mentre $[a,+\infty[$ è un interno di $+\infty$.

Quando abbiamo un limite con $x_0$ o $l$ che vale $\pm\infty$ non possiamo verificare il limite con $\epsilon - \delta$ ma dobbiamo considerare intorni di $\pm\infty$.

## Limite destro e sinistro
- L'**intorno sinistro** di $x_0$ si indica con $I^-_{x_0}$ ed esso non contiene $x_0$, può anche essere descritto come: $I^-_{x_0}=I_{x_0}\cap]-\infty,x_0[$
	- Scriveremo il limite tendete a $x_0$ da sinistra come: $\lim\limits_{x\to x^-_0}f(x)=l$
- L'**intorno destro** di $x_0$ si indica con $I^+_{x_0}$ ed esso non contiene $x_0$, può anche essere descritto come: $I^+_{x_0}=I_{x_0}\cap]x_0, +\infty[$
	- Scriveremo il limite tendete a $x_0$ da destra come: $\lim\limits_{x\to x^+_0}f(x)=l$

>[!Teoremi]
>$$\lim_{x\to x_0}f(x)=l$$
>$$\iff$$
>$$\lim_{x\to x^-_0}f(x)=l\quad \land \quad \lim_{x\to x^+_0}f(x)=l$$
>---
>
>**Teorema di limitatezza locale**:
>Se $\lim\limits_{x\to x_0}f(x)=l \in \mathbb{R}$ (limite finito) allora esiste un intorno di $x_0$ dove $f$ è limitata.
>
>---
>**Teorema del confronto**:
>Avendo tre funzioni $f,g,h$ che soddisfano le disuguaglianze:
>$$f(x)\leq g(x) \leq h(x)$$
>- $\lim\limits_{x\to x_0}f(x)=l\land \lim\limits_{x\to x_0}h(x)=l\implies \lim\limits_{x\to x_0}g(x)=l$
>- $\lim\limits_{x\to x_0}f(x)=+\infty \implies \lim\limits_{x\to x_0}g(x)=+\infty$
>- $\lim\limits_{x\to x_0}h(x)=-\infty \implies \lim\limits_{x\to x_0}g(x)=-\infty$

## Algebra dei limiti

Avendo due limiti generici
$$\lim_{x \to x_0} f(x) = \ell \quad \land \quad \lim_{x \to x_0} g(x) = \ell'$$
Vengono riassunte nella seguente tabella le principali operazioni con i limiti:
![[Operazioni_limiti.png|700]]


### Limite di funzioni monotone
Sia $f: A\subseteq \mathbb{R} \to \mathbb{R}$ una funzione monotona

Sia $\alpha=\text{sup}(A)$ con $\alpha$ diverso dal massimo di $A$ si avrà:
$$\lim\limits_{x\to \alpha}f(x)=\begin{cases}
	      \text{sup}(f(A)), & \text{ se $f$ è crescente };\\
	      \text{inf}(f(A)), & \text{ se $f$ è decrescente }.
	\end{cases}
$$
Sia $\beta = \text{inf}(A)$ con $\beta$ diverso dal minimo di $A$ si avrà:
$$\lim\limits_{x\to \beta}f(x)=\begin{cases}
	      \text{inf}(f(A)), & \text{ se $f$ è crescente };\\
	      \text{sup}(f(A)), & \text{ se $f$ è decrescente }.
	\end{cases}
$$
### Altri limiti
- **Il limite di funzioni periodiche non costanti non esiste**, per esempio notiamo: $\lim\limits_{x \to +\infty}sin(x) = \nexists$ questo accade perchè $sin(x)$ avrà valori che oscillano tra $-1$ e $1$ rendendo quindi il limite che tende verso infinito non unico.
	Da notare anche che una funzione del tipo: $\lim\limits_{x \to +\infty}cos(x) +x = +\infty$ questo perchè il valore assunto dal coseno sarà compreso tra $-1$ e $1$ anche in questo caso, ma sommandoci infinito sarà uguale a $+\infty$.

- $\lim\limits_{x\to x_0}|f(x)|=|l|$ anche con $l=\pm \infty$ 