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
## Limiti e continuità

>[!Limite di funzione usando le  successioni]
>Sia $f: A\subset \mathbb{R}^n\to\mathbb{R}$ e $x_0\in\mathbb{R}^n$ tale che $f$ è definita in almeno un intorno sferico di $x_0$ (al massimo $x_0$ escluso). Dato $L\in\mathbb{R}\cup\pm\infty$ diremo che:
>$$\lim_{x\to x_0}f(x)=L\quad\iff\quad\lim_{k\to\infty}f(x_k)=L$$
>per ogni successione $x_k$ che converge a $x_0$ con $x_k\neq 0$

>[!Limite di funzione usando gli intorni]
>Sia $f: A\subset \mathbb{R}^n\to\mathbb{R}$ e $x_0\in\mathbb{R}^n$ tale che $f$ è definita in almeno un intorno sferico di $x_0$ (al massimo $x_0$ escluso). Dato $L\in\mathbb{R}$ diremo che:
>$$\lim_{x\to x_0}f(x)=L\quad\iff\quad \forall\epsilon > 0 \space\exists\delta > 0$$
>$$\text{tale che}$$
>$$0<||x-x_0||<\delta \implies |f(x)-L|<\epsilon$$

