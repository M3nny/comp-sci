### Uniforme
La v.a. $X$ è una **distribuzione uniforme** se la sua densità è costante nell'intervallo $(a,b)$ e nulla al di fuori di esso.
$$X\sim U(a,b)$$
- $f(x)=\frac{1}{b-a},\space x\in(a,b)$
- $F(x)=\frac{x-a}{b-a},\space x\in(a,b)$
- $\mathbb{E}[X]=\frac{a+b}{2}$
- $Var[X]=\frac{(b-a)^2}{12}$
---
### Normale (o gaussiana)
La v.a. $X$ è una **distribuzione normale** se presenta una forma a campana, con media $\micro$ e varianza $\sigma^2$.
$$X\sim N(\micro,\sigma^2)$$
- $f(x)=\frac{1}{\sigma\sqrt{2\pi}}e^{-\frac{1}{2}(\frac{x-\micro}{\sigma})^2}$
- $\mathbb{E}[X]=\micro$
- $Var[X]=\sigma^2$

la v.a. $Z\sim N(0,1)$ viene anche chiamata **normale standard** e si può arrivare alla forma standard da quella normale come segue:
$$X\sim N(\micro,\sigma^2)\implies Z=\frac{X-\micro}{\sigma}\sim N(0,1)$$
con versione standardizzata è possibile calcolare la funzione di ripartizione ($\Phi$) attraverso la [tavola della distribuzione normale standard](https://www.sjsu.edu/faculty/gerstman/EpiInfo/z-table.htm).

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
>\end{flalign}$$

---
### Distribuzione gamma
La v.a. $X$ con **distribuzione gamma** ha parametri $\alpha>0$ e $\lambda>0$, dove $\alpha$ è il numero di eventi che si stanno osservando, e $\lambda$ è il tempo di attesa medio ad ogni evento.
$$X\sim \text{Ga}(\alpha,\lambda)$$
- $f(x)=\begin{cases}\frac{\lambda^\alpha}{\Gamma(\alpha)}x^{\alpha-1}e^{-\lambda x}&x\in(0,\infty)\\0&\text{altrimenti}\end{cases}$
	dove $\Gamma(\alpha)=\int_0^\infty x^{\alpha-1}e^{-x}dx$ è la funzione gamma.
- $\mathbb{E}[X]=\frac{\alpha}{\lambda}$
- $Var[X]=\frac{\alpha}{\lambda^2}$

La funzione di ripartizione si può calcolare quando $\alpha$ è intero, questo perchè possiamo riscrivere $\Gamma$ come un fattoriale: $\Gamma(\alpha)=\int_0^\infty x^{\alpha-1}e^{-x}dx=(\alpha-1)!$

---
### Distribuzione esponenziale
Viene chiamata così la distribuzione gamma con $\alpha=1$, essa viene usata per modellare tempi di attesa e lunghezze.
$$X\sim \text{Exp}(\lambda)$$
- $f(x)=\begin{cases}\lambda e^{-\lambda x}&x\in(0,\infty)\\0&\text{altrimenti}\end{cases}$
- $F(x)=\begin{cases}0&x<0\\1-e^{-\lambda x}&x\geq 0\end{cases}$
- $\mathbb{E}[X]=\frac{1}{\lambda}$
- $Var[X]=\frac{1}{\lambda^2}$

Questa è l'unica distribuzione continua con **mancanza di memoria** (come la geometrica per le discrete), la proprietà può essere descritta come:
$$\begin{flalign}
\mathbb{P}[X>t+s|X>t]&=\frac{\mathbb{P}[X>t+s]}{\mathbb{P}[X>t]}\\
&=\mathbb{P}[X>s]
\end{flalign}
$$
tenendo conto che $\mathbb{P}[X>x]=e^{-\lambda x}$ con $x>0$.

>[!Example]
>In un ora viene installato un software in circa 30 pc.
>Assumendo che il tempo di installazione su ogni pc esegua una distribuzione esponenziale, calcolare la probabilità che si impieghi più di 5 minuti per installare il software nel prossimo pc.
>
>$X$ = tempo di attesa in ore $\sim Exp(30)$ (30 pc in media)
>$$\mathbb{P}[X>5/60]=\mathbb{P}[X>1/12]=e^{-30/12}$$
>
>$x$ = tempo di attesa in minuti $\sim Exp(1/2)$
>$$\mathbb{P}[X>5]=e^{-5/2}$$

---
### Processo di Poisson
Ricordando che:
- $\text{Po}(\lambda)$ modella il numero di arrivi in una unità di tempo
- $\text{Exp}(\lambda)$ modella il tempo d'attesa per un arrivo

Con il processo di Poisson colleghiamo una v.a. continua con una v.a. discreta, ovvero il tempo al numero degli arrivi, si indica come:
$$X_t\sim \mathcal{P}(\lambda\cdot t)$$
Si usa per contare il numero di manifestazioni di un fenomeno di interesse in un qualsiasi intervallo di tempo di ampiezza $t$, quando il numero medio delle manifestazioni dipende solo dall'ampiezza dell'intervallo considerato.
- $X_t$ = numero di eventi in un intervallo di tempo $t$
- $\lambda$ = numero medio di eventi nell'unità di tempo

>La differenza tra $\text{Po}(\lambda)$ e $\mathcal{P}(\lambda\cdot t)$ è che la prima ha una finestra di tempo fissa, mentre la seconda ha una finestra di tempo dinamica.

Il processo di Poisson è in relazione con la distribuzione esponenziale in quanto c'è una v.a. esponenziale che misura il tempo fra due manifestazioni successive del fenomeno in questione.

>[!Example]
>Il numero di messaggi in arrivo alla casella di posta elettronica segue un processo di Poisson nel tempo, con una media di $12$ messaggi ogni $10$ minuti.
>
>Scegliamo il minuto come unità di misura.
>- $\lambda = \frac{12}{10}$
>- $X_t = \text{Po}(\frac{12}{10}t)$
>
>$$\mathbb{P}[\text{più di 20 messaggi in 30 min}]=\mathbb{P}[X_{30}>20]=1-\mathbb{P}[X_{30}\leq 20]$$
>con $X_{30}\sim\text{Po}(\frac{12}{10}30)=\text{Po}(36)$
>
>Una volta calcolato il parametro $\lambda$ si possono risolvere i problemi o con la distribuzione di Poisson o con la distribuzione esponenziale.
>
>$$
>\begin{flalign}
>&\mathbb{P}[\text{nessun messaggio in 15 min}]=\\
>&=\mathbb{P}[X_{15}=0]=\frac{(\frac{12}{10}\cdot 15)^0}{0!}\cdot e^{-\frac{12}{10}15}=e^{-18}\\
>&=\mathbb{P}[T>15]=e^{-\frac{12}{10}\cdot 15}=e^{-18}
>\end{flalign}
>$$
>dove $T\sim\text{Exp}(\frac{12}{10})$ misura il tempo che passa fra l'arrivo di due messaggi consecutivi.





