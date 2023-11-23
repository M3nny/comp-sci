### Uniforme
La v.a. $X$ è una **distribuzione uniforme** se la sua densità è costante nell'intervallo $(a,b)$ e nulla al di fuori di esso.
$$X\sim U(a,b)$$
- $f(x)=\frac{1}{b-a},\space x\in(a,b)$
- $F(x)=\frac{x-a}{b-a},\space x\in(a,b)$
- $\mathbb{E}[X]=\frac{a+b}{2}$
- $Var[X]=\frac{(b-a)^2}{12}$

### Normale (o gaussiana)
La v.a. $X$ è una **distribuzione normale** se presenta una forma a campana, con media $\micro$ e varianza $\sigma^2$.
$$X\sim N(\micro,\sigma^2)$$
- $f(x)=\frac{1}{\sigma\sqrt{2\pi}}e^{-\frac{1}{2}(\frac{x-\micro}{\sigma})^2}$
- $\mathbb{E}[X]=\micro$
- $Var[X]=\sigma^2$

la v.a. $Z\sim N(0,1)$ viene anche chiamata **normale standard** e si denota con $\Phi$, si può arrivare alla forma standard da quella normale come segue:
$$X\sim N(\micro,\sigma^2)\implies Z=\frac{X-\micro}{\sigma}\sim N(0,1)$$

>[!Example]
>Una macchina produce tubi di diametro $X$ (mm).
>Supponiamo che per contratto i tubi debbano essere di diametro $d$ mm con un margine di circa $\epsilon$ m.
>Calcolare la probabilità che un generico tubo sia difettoso (fuori specifica, non uniforme)
>Sia $p=\mathbb{P}[\text{"X è difettoso"}]$, allora:
>$$\begin{flalign}
>p&=\mathbb{P}[(X<d-\epsilon)\cup (d+\epsilon<X)]\\
>&=\mathbb{P}[X<d-\epsilon]+\mathbb{P}[d+\epsilon<X]\\
>&=\int_{-\infty}^{d-\epsilon}\frac{1}{\sigma\sqrt{2\pi}}e^{-\frac{1}{2}(\frac{x-\micro}{\sigma})^2}dx+\int_{d+\epsilon}^{+\infty}\frac{1}{\sigma\sqrt{2\pi}}e^{-\frac{1}{2}(\frac{x-\micro}{\sigma})^2}dx
>\end{flalign}$$

Quando $n$ è grande nella binomiale, si può usare la normale per approssimarla:
$$\text{Bin}(n,p)\approx N(np,np(1-p))$$
- L'approssimazione si usa quando: $np(1-p)\geq 10$

>[!Example]
>Un virus danneggia un file con probabilità $0.35$, indipendentemente dagli altri file.
>Il virus attacca una cartella con $2400$ file, quale è la probabilitàà che vengano danneggiati fra gli $800$ e gli $850$ file (inclusi).
>
>Sia $X$ la v.a. che conta il numero di file danneggiati su $2400$, usando la binomiale:
>$$\mathbb{P}[800\leq X\leq 850]=\sum_{k=800}^850\binom{2400}{k}0.35^k(1-0.35)^{2400-k}=0.632893$$
>
>Approssimando la binomiale con la normale:
>$$\micro=2400\cdot 0.35=840$$
>$$\sigma=\sqrt{2400\cdot 0.35\cdot (1-0.35)}=\sqrt{546}=23.36664$$
>
>Quando si approssima una distribuzione discreta con un'altra continua, si applica la **correzione per continuità**, che consiste nell'ampliare di $\frac{1}{2}$ si estremi dell'intervallo di integrazione, per cui:
>$$\begin{flalign}
>\mathbb{P}[800\leq X\leq 850]&=\mathbb{P}[799.5<X<850.5]\\
>&\approx\Phi\left(\frac{850.5-840}{23.36664}\right)-\Phi\left(\frac{799.5-840}{23.36664}\right)\\
>&\approx\Phi(0.4493586)-\Phi(-1.73324)=0.631887
>\end{flalign}
