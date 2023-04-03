## Nozioni di topologia
Definiamo **intorno sferico** di centro $x_0$ e raggio $r$ l'insieme:
$$U_r(x_0)=\{x\in\mathbb{R}^n:||x-x_0||<r\}$$
![[Intorno sferico.svg|200]]
Un <u>punto</u> può essere (rispetto ad un insieme $E$):
- **Interno** se $x_0\in E$ e $\exists r >0$ tale che $U_r(x_0)\subset E$
- **Esterno** se $x_0\notin E$ e $\exists r >0$ tale che $U_r(x_0)\not\subset E$ 
- **Frontiera** se $x_0$ non è nè interno nè esterno ad $E$ $\forall r >0$ 

Esistono varie <u>componenti</u> di un insieme:
- **Parte interna** ($\mathring{E}$): è l'insieme dei punti interni ad $E$
- **Bordo** ($\partial E$): è l'insieme dei punti di frontiera di $E$
- **Chiusura** ($\overline{E}$): è l'insieme dei punti di $E$ compreso il bordo, ovvero $E\cup\partial E$
Da cui deduciamo: $\mathring{E}\subseteq E \subseteq \overline{E}$ e $\overline{E} = \mathring{E}\cup\partial E$

Un <u>insieme</u> può essere:
- **Aperto** se ogni suo punto è interno ($E=\mathring{E}$)
- **Chiuso** se il suo complementare è aperto ($E=\overline{E}$)
- **Nè chiuso nè aperto** 
Allo stesso tempo può anche essere:
- **Limitato** se esiste un _intorno circolare_ di centro $O$ che lo contiene (**illimitato** altrimenti)
- **Connesso** se esistono due punti che possono essere collegati senza uscire dall'insieme
![[Insiemi.svg]]
---

**Definizione di limite**:
>[!Limite di funzione usando le  successioni]
>Sia $f: A\subset \mathbb{R}^n\to\mathbb{R}$ e $x_0\in\mathbb{R}^n$ tale che $f$ è definita in almeno un intorno sferico di $x_0$ (al massimo $x_0$ escluso). Dato $L\in\mathbb{R}\cup\pm\infty$ diremo che:
>$$\lim_{x\to x_0}f(x)=L\quad\iff\quad\lim_{k\to\infty}f(x_k)=L$$
>per ogni successione $x_k$ che converge a $x_0$ con $x_k\neq 0$

>[!Limite di funzione usando gli intorni]
>Sia $f: A\subset \mathbb{R}^n\to\mathbb{R}$ e $x_0\in\mathbb{R}^n$ tale che $f$ è definita in almeno un intorno sferico di $x_0$ (al massimo $x_0$ escluso). Dato $L\in\mathbb{R}$ diremo che:
>$$\lim_{x\to x_0}f(x)=L\quad\iff\quad \forall\epsilon > 0 \space\exists\delta > 0$$
>$$\text{tale che}$$
>$$0<||x-x_0||<\delta \implies |f(x)-L|<\epsilon$$

### Verifica della continuità
$$f: A\subseteq \mathbb{R}^n\to\mathbb{R}$$
è **continua** in $x_0\in A$ se $\lim\limits_{x\to x_0}f(x)=f(x_0)$.

- È molto probabile che <u>non</u> sia continua se è definita a tratti (regioni diverse)
- Le funzioni elementari sono continue
- Somma/prodotto/rapporto/composizione di funzioni continue restituiscono funzioni continue.

>[!Example]
$$f:\mathbb{R}^2\to\mathbb{R}$$
>$$f(x,y)=\begin{cases}f_1=2x+3y+10&\text{se}\space (x-1)^2+(y-3)^2\geq 4\\f_2=x+4y+10&\text{se}\space (x-1)^2+(y-3)^2<4\end{cases}$$
>![[Es continuità.svg]]
>Se i due piani si toccano allora è continua, creiamo un sistema tra **frontiera** e $f_1=f_2$
>$$\begin{cases}(x-1)^2+(y-3)^2=4\\2x+3y+10=x+4y+10\end{cases}\quad\Rightarrow\quad\begin{cases}y^2-4y+3=0\\x=y\end{cases}$$
>Da cui ricaviamo $y_{1,2}=1,3$ e otteniamo che è continua nei punti
>$$P_1=(1,1)\quad P_2=(3,3)$$
>Quindi $f$ è continua in
>$$\{(x,y)\in\mathbb{R}^2:(x-1)^2+(y-3)^2<4\lor(x-1)^2+(y-3)^2>4\lor(1,1)\lor(3,3)\}$$

### Calcolo di limiti
In caso di forme indeterminate dobbiamo:
1. Trovare delle **sezioni** le quali devono dare risultato uguale (altrimenti non esiste il limite)
2. Usare il [[Definizione di un limite#Limite destro e sinistro|teorema del confronto]] per verificare il risultato delle _sezioni_

>[!Example]
>$$\lim_{(x,y)\to(0,0)}\left(\frac{y(x^2+3y^2)}{x^2+5y^2}+\cos(x+y)\right)$$
>Sostituendo vediamo che il primo addendo ($L_1$) è una forma indeterminata $\frac{0}{0}$ , mentre il secondo si risolve subito risultando quindi in $L_2=1$, andiamo risolvere la F.I. del primo addendo.
>
>**Sezione x=0** ($f(0,y)$):
>$$\lim_{y\to 0}(\frac{3y^3}{5y^2})=0$$
>**Sezione y=0** ($f(x,0)$):
>$$\lim_{x\to 0}(\frac{0}{x^2})=0$$
>Abbiamo provato con un paio di sezioni e abbiamo visto che sono uguali, quindi se $L_1$ esiste, sarà uguale a $0$.
>
>Usando la definizione di limite: $\lim\limits_{x\to x_0}f(x)=L\iff\lim\limits_{x\to x_0}|f(x)-L| = 0$
>Andiamo ad applicare il **teorema del confronto**:
>$$0\leq\left|\frac{y(x^2+3y^2)}{x^2+5y^2}\right|\leq |y|$$
>il confronto si basa sul fatto che $\frac{x^2+3y^2}{x^2+5y^2} \leq 1$ e quindi $y$ sarà sicuramente più grande di $y\cdot\frac{...}{...}$
>Deduciamo quindi che $L_1=0$
>$$L=L_1+L_2=0+1=1$$

#### Disuguaglianze utili per il confronto
- $2|ab|\leq a^2+b^2\quad\forall a,b\in\mathbb{R}^2$
- $\frac{a^2}{a^2+b^2}\leq 1\quad\forall a,b\in\mathbb{R}^2$
- $e^z\geq 1+z\quad\forall z\in\mathbb{R}^2$
- $\ln(z)\leq z-1\quad\forall z\geq0$
- $|\sin(z)|\leq|z|\quad\forall z\in\mathbb{R}^2$
- $|\sin(z)\leq1;\quad |\cos(z)|\leq 1\quad\forall z\in\mathbb{R}^2$
