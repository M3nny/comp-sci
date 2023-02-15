Data la funzione $f: A\subseteq \mathbb{R} \to \mathbb{R}$
- Se $x_0$ è di accumulazione per $A$ diremo che $f$ è **continua** in $x_0$ se $\lim\limits_{x\to x_0}f(x)=f(x_0)$
- Se $x_0$ è un punto isolato in $A$, diremo che $f$ è continua anche in $x_0$
- Diremo che $f$ è continua in generale se è continua in ogni punto del dominio $A$.

Un altro modo per verificare la continuità di una funzione è quello di verificare se esiste il limite sinistro e destro($\lim\limits_{x\to x_0^-}f(x)=\ell\ \in \mathbb{R}$  e $\lim\limits_{x\to x_0^+}f(x)=r \in \mathbb{R}$) allora $f$ è continua se e solo se $\ell = r = f(x_0)$.

>[!Example]
>Se consideriamo la [[Funzioni elementari#Potenza con esponente intero negativo|funzione]] $y=\frac{1}{x}$ possiamo dire che è continua, perchè nel suo dominio $D=\mathbb{R} \setminus \{0\}$ rispetta la definizione di funzione continua.
>
>---
>Se consideriamo la [[Funzioni elementari#Funzione segno|funzione]]: $\begin{cases}+1 \space &\text{ se } x>0;\\0 &\text{ se } x=0;\\-1 \space &\text{ se }x<0.\end{cases}$
>Non è continua perchè in $x_0 = 0$ che fa parte del suo dominio la funzione è definita a tratti.
>
>---
>Invece considerando: $\begin{cases}+1 \space &\text{ se } x>0;\\-1 &\text{ se } x<0.\end{cases}$
>Otterremo $D=\mathbb{R}\setminus \{0\}$ e quindi è continua perchè a differenza della funzione precedente lo zero non fa parte della funzione.

## Operazioni tra funzioni continue
Date due funzioni $f,g: A\to \mathbb{R}$, allora le seguenti funzioni saranno anch'esse continue:
$$h=f+g;\quad h=f\cdot g;\quad h=\frac{f}{g};\quad h=|f|$$
Mentre per l'operazione di composizione $h= f \circ g \to h(x)=f(g(x))$ è continua se$f$ e $g$ sono continue.

- Se $\lim\limits_{x\to x_0} g(x)=\ell$ e $\ell \notin A$ (dominio di $f$) ma $\ell$ è di accumulazione per $A$ allora possiamo considerare il cambio di variabili $t=g(x)$ e il limite diventa: $\lim\limits_{x\to x_0}f(g(x))=\lim\limits_{t\to \ell}f(t)$.

In breve: <mark>se la funzione non è definita per tratti allora è continua</mark>.

>[!Example]
>- $y=sin(cos(x))$ è continua perchè è una composizione di funzioni continue;
>- $y=ln(\frac{1}{x})$ è continua per lo stesso motivo

## Continuità della funzione inversa
Se $f$ è strettamente monotona e definita in un intervallo $I$ allora $f^{-1}$ è una funzione continua.
- **Nota**: non vale per tutte le funzioni

## Continuità delle funzioni elementari
Le funzioni elementari continue sono:
$$y=x^a; \quad y=a^x; \quad y=ln_a(x); \quad y=sin(x); \quad y=tan(x)$$
$$y=arcsin(x);\quad y=arctan(x)$$
Inoltre il valore assoluto è continuo.

Le funzioni a tratti possono non essere continue, per questo bisogna controllare il punto di giunzione.
Se facciamo il calcolo del limite su una funzione continua sappiamo che è uguale a trovare il punto nella funzione:
$$\text{se } f \text{ è continua in }x_0 \text{ allora} \lim\limits_{x\to x_0}f(x)=f(x_0)$$

## Teoremi fondamentali sulle funzioni continue

>[!Teorema]
>**Zeri di una funzione continua - teorema di Bolzano**:
>Siano $a<b$ e $f: [a,b]\to \mathbb{R}$ una funzione continua dove $f(a)\cdot f(b)<0$ ovvero che $f(a)$ e $f(b)$ abbiano segno opposto;
>Allora esiste almeno un punto $c$ di $[a,b]$ tale che $f(c)=0$.
>Praticamente la funzione dovrà passare per l'asse delle x.
>
>---
>**Teorema dei valori intermedi**:
>Sia $f: [a,b] \to \mathbb{R}$ continua;
>Allora $Im(f)$ è un intervallo, dove $f$ assume tutti i valori in quell'intervallo.
>
>---
>**Teorema di Weierstrass**:
>Sia $f$ continua in un insieme chiuso limitato;
>Allora $f$ ha un massimo ed un minimo in quel insieme.
>$\rightarrow$ $A$ chiuso e limitato, $f$ continua su $A$ allora $\exists c,d \in A$ tali che:
>$$f(c)=\max\limits_{x\in A}f(x); \quad f(d)=\min\limits_{x\in A}(fx)$$

>[!Example]
>- $f(x)=x^3+x^2+x+1$
>**Mostrare che l'equazione $x^3+x^2+x+1=0$ ha almeno uno zero in $\mathbb{R}$**
>- $f$ è continua e definita su tutto $\mathbb{R}$.
>$$\lim\limits_{x\to +\infty} = +\infty \implies \exists b\in \mathbb{R} \text{ per cui }f(b)>0$$
>$$\lim\limits_{x\to -\infty} = -\infty \implies \exists a\in \mathbb{R} \text{ per cui }f(a)<0$$
>In $[a,b]$ $f$ è continua e $f(a) \cdot f(b) < 0$
>$\rightarrow$ per teorema degli zeri $\exists c \in [a,b]|f(c)=0$.


