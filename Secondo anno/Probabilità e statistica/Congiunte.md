Si è spesso interessati a formulare affermazioni di tipo probabilistico rispetto a **due o più variabili aleatorie contemporaneamente**.
Vengono chiamate **distribuzioni bivariate** le coppie di v.a. $(X,Y)$, **multivariate** i vettori di v.a. $(X_1, ... , X_n)$.

>In questo corso le congiunte che vedremo saranno tutte dello stesso tipo, non verranno mischiate discrete e continue.

### Funzione di ripartizione congiunta
La f.r. congiunta della coppia di v.a. $(X,Y)$ è una funzione $F:\mathbb{R}^2\to[0,1]$ tale che:
$$F(x,y)=\mathbb{P}[X\leq x,Y\leq y],\quad\forall(x,y)\in\mathbb{R}^2$$
dalla funzione di ripartizione possiamo ricavare facilmente le f.r. delle singole v.a. $X$ e $Y$, infatti:
$$F_X(x)=\lim_{y\to\infty}F(x,y)$$
$$F_Y(y)=\lim_{x\to\infty}F(x,y)$$
La f.r. congiunta di $(X,Y)$ contiene quindi anche l'informazione riguardante le distribuzioni di probabilità singole di $X$ e $Y$, ovvero le **distribuzioni marginali**, che si ottengono quindi sommando rispetto a tutti i valori possibili dell'altra variabile.
>Il viceversa non è vero.

La funzione di probabilità congiunta e le marginali possono essere rappresentate all'interno di una **tabella a due entrate**.

>[!Example]
>Un programma consiste di due moduli che hanno rispettivamente $X$ e $Y$ numero di errori che hanno distribuzione congiunta:
>$p(0,0)=p(0,1)=p(1,0)=0.2$
>$p(1,1)=p(1,2)=p(1,3)=0.1$
>$p(0,2)=p(0,3)=0.05$
>
>|   $X/Y$    |  $0$   |  $1$   |  $2$   |  $3$   | $p_X(x)$ |
>|:--------:|:------:|:------:|:------:|:------:|:--------:|
>|   $0$    | $0.2$ | $0.2$ | $0.05$ | $0.05$ |  $0.5$   |
>|   $1$    | $0.2$ | $0.1$ | $0.1$ | $0.1$ |  $0.5$   |
>| $p_Y(y)$ | $0.4$ | $0.3$ | $0.15$ | $0.15$ |   $1$    |
>
>Probabilità che non ci siano errori nel primo modulo:
>$$\mathbb{P}[X=0]=\sum_{y=0}^3p(0,y)=0.20+0.20+0.05+0.05=0.5$$
>Probabilità che nel primo modulo ci siano meno errori che nel secondo modulo:
>$$
>\begin{flalign}
>\mathbb{P}[X&<Y]=1-\mathbb{P}[X\geq Y]\\
>&=1-\mathbb{P}[X=0,Y=0]-\mathbb{P}[X=1,Y=0]-\mathbb{P}[X=1,Y=1]\\
>&=1-(0.2+0.2+0.1)=0.5
>\end{flalign}
>$$
### Funzioni congiuntamente continue
$X$ e $Y$ sono **congiuntamente continue** se esiste una funzione $f:\mathbb{R}^2\to\mathbb{R}$ integrabile e tale che:
1. $f(x,y)\geq 0,\quad\forall(x,y)\in\mathbb{R}^2$
2. $\int\int_{\mathbb{R}^2}f(x,y)dxdy=1$
$f$ è la **funzione di densità congiunta** di $(X,Y)$ e si usa per calcolare probabilità riguardanti le due v.a. in questione.

Sia $(X,Y)$ una distribuzione continua bivariata con densità $f(x,y)$.
![[Area congiunte.svg]]
$$\begin{flalign}
\mathbb{P}[(X,Y)\in C]&=\int\int_Cf(x,y)dxdy\\
&=\mathbb{P}[a_1\leq x\leq a_2, b_1\leq y\leq b_2]=\int_{a_1}^{a_2}\int_{b_1}^{b_2}f(x,y)dydx
\end{flalign}
$$
Dalla **densità congiunta** si può ricavare la **f.r. congiunta**:
$$F(x,y)=\mathbb{P}[X\leq x, Y\leq y]=\int_{-\infty}^y\int_{-\infty}^xf(s,t)dsdt$$
dalla **f.r. congiunta** si può ricavare la **densità congiunta**:
$$f(x,y)=\frac{d^2F(x,y)}{dxdy}$$
dalla **densità congiunta** si possono ricavare le **funzioni di densità marginali**:
$$f_X(x)=\int_\mathbb{R}f(x,y)dy$$
$$f_Y(y)=\int_\mathbb{R}f(x,y)dx$$
>[!Example]
>Trovare il valore di $k$ che rende la seguente funzione, una funzione di densità:
>$$f(x,y)=kxy\space 1_{\{(x,y)\in[0,1]^2\}}$$
>
>$$\begin{flalign}
>&\int_0^1\int_0^1kxy\space dydx=1\\
>&k\int_0^1x\int_0^1y\space dydx=1\\
>&k\int_0^1x\frac{1}{2}dx=\frac{k}{2}\int_0^1x\space dx=1\\
>&\frac{k}{4}=1\implies k=4
>\end{flalign}$$
>
>Calcolare $\mathbb{P}[X>Y]$.
>![[Ripartizione congiunte.svg|300]]
>
>$$\begin{flalign}
>\mathbb{P}[X>Y]&=\int_0^1\int_0^x4xy\space dydx\\
>&=\int_0^1 4x[\frac{y^2}{2}]_0^x\space dx\\
>&=\int_0^1 4x\cdot\frac{x^2}{2}\space dx\\
>&=\int_0^1 2x^3\space dx = \frac{1}{2}
>\end{flalign}$$

### Congiunte indipendenti
Il concetto di [[Probabilità condizionata#Eventi indipendenti|indipendenza degli eventi]] si estende anche alle v.a.
Due v.a. sono **indipendenti** in modo generale quando:
$$\boxed{F(x,y)=F_X(x)\cdot F_Y(y)\quad\forall(x,y)}$$
è possibile verificarlo in un altro modo in base al tipo di v.a.:
- **Discrete**: $p(x,y)=p_X(x)p_Y(y)\quad\forall(x,y)$
- **Continue**: $f(x,y)=f_X(x)f_Y(y)\quad\forall(x,y)$

>[!Example]
>$$f(x,y)=\begin{cases}24xy&x,y\in(0,1),\space x+y\in(0,1)\\0&\text{altrimenti}\end{cases}$$
>$X$ e $Y$ sono indipendenti?
>Si può procedere in due modi:
>1. Trovare le marginali e vedere se $f(x,y)=f_X(x)f_Y(y)$
>2. Vedere dal grafico se conoscere $X$ o $Y$ dice qualcosa dell'altro
>![[Esempio indipendenza congiunte.svg]]
>Si, conoscere una v.a. ci dice qualcosa sull'altra in quanto, più alto è il valore di una v.a., più basso è il valore dell'altra, quindi $X$ e $Y$ <u>non sono</u> indipendenti.
>---
>Avendo la seguente distribuzione congiunta determinare se $X$ e $Y$ sono indipendenti.
>
>|   $X/Y$    |  $0$   |  $1$   |  $2$   |  $3$   | $p_X(x)$ |
>|:--------:|:------:|:------:|:------:|:------:|:--------:|
>|   $0$    | $0.2$ | $0.2$ | $0.05$ | $0.05$ |  $0.5$   |
>|   $1$    | $0.2$ | $0.1$ | $0.1$ | $0.1$ |  $0.5$   |
>| $p_Y(y)$ | $0.4$ | $0.3$ | $0.15$ | $0.15$ |   $1$    |
>
>Dato che siamo in presenza di una bivariata discreta, perchè $X$ e $Y$ siano indipendenti, deve valere $p(x,y)=p_X(x)p_Y(y)\quad\forall(x,y)$.
>- $p(0,0)=p_X(0)p_Y(0)\Rightarrow 0.2 = 0.5\cdot 0.4$
>- $p(0,1)=p_X(0)\cdot p_Y(1)\Rightarrow 0.2\neq 0.5\cdot 0.3$
>Abbiamo trovato dei valori per cui la condizione non è valida, quindi $X$ e $Y$ non sono indipendenti.
>
>>Sapendo in partenza che $X$ e $Y$ sono indipendenti, è possibile ricavare tutte le funzioni di probabilità congiunta dalle marginali attraverso i prodotti di ogni loro combinazione.  

### Congiunte condizionate
Anche in questo caso, il concetto di [[Probabilità condizionata|probabilità condizionata]] si estende alle v.a.
Siano $X$ e $Y$ due v.a. **discrete** con probabilità congiunta $p(x,y)$, la **funzione di probabilità condizionata** di $X$ dato $Y=y$ è:
$$p_{X|Y}(x|y)=\frac{p(x,y)}{p_Y(y)}\quad\forall y|p_Y(y)>0$$
analogamente, conoscendo $X=x$:
$$p_{Y|X}(y|x)=\frac{p(x,y)}{p_X(x)}\quad\forall x|p_X(x)>0$$
per le **v.a. continue** invece viene usata la **funzione di densità**:
$$f_{X|Y}(x|y)=\frac{f(x,y)}{f_Y(y)}\quad\forall y|f_Y(y)>0$$
$$f_{Y|X}(y|x)=\frac{f(x,y)}{f_X(x)}\quad\forall x|f_X(x)>0$$
da cui:
- $\mathbb{P}[X\in A|Y=y]=\int_Af_{X|Y}(x|y)dx$
- $\mathbb{P}[Y\in B|X=x]=\int_Bf_{Y|X}(y|x)dy$

>Due v.a. **discrete** sono indipendenti se:
>- $p_{X|Y}(x|y)=p_X(x)$ e $p_{Y|X}=p_Y(y)$
>
>Due v.a. **continue** sono indipendenti se:
>- $f_{X|Y}(x|y)=f_X(x)$ e $f_{Y|X}=f_Y(y)$

>[!Example]
>Avendo la seguente distribuzione congiunta:
>
|  $X/Y$   |  $0$  |  $1$  | $p_X(x)$ |
|:--------:|:-----:|:-----:|:--------:|
|   $0$    | $0.4$ | $0.2$ |  $0.6$   |
|   $1$    | $0.1$ | $0.3$ |  $0.4$   |
| $p_Y(y)$ | $0.5$ | $0.5$ |   $1$    |
>
>- $p_{X|Y}(0|1)=\frac{p(0,1)}{p_Y(1)}=\frac{0.2}{0.5}=0.4$
>- $p_{X|Y}(1|1)=\frac{p(1,1)}{p_Y(1)}=\frac{0.3}{0.5}=0.6$
>
>inoltre è possibile anche concludere che le variabili non sono indipendenti, in quanto $p_{X|Y}(0|1)\neq p_X(0)$.

### Valore atteso
Il valore atteso di una trasformazione $g(X,Y)$ è dato da:
$$\mathbb{E}[g(X,Y)]=\begin{cases}
\sum_y\sum_xg(x,y)p(x,y)&\text{caso discreto}\\
\int\int_{\mathbb{R}^2}g(x,y)f(x,y)dxdy&\text{caso continuo}
\end{cases}$$
Due conseguenze del precedente risultato sono:
1. $\mathbb{E}[X+Y]=\mathbb{E}[X]+\mathbb{E}[Y]$
	in generale: $\mathbb{E}[\sum\limits_{i=1}^n a_iX_i]=\sum\limits_{i=1}^n a_i\mathbb{E}[X_i]$.
2. Se $X$ e $Y$ sono **indipendenti**, allora: $\mathbb{E}[X\cdot Y]=\mathbb{E}[X]\cdot\mathbb{E}[Y]$

>[!Example]
>Avendo la seguente distribuzione congiunta rappresentate la distribuzione degli errori in due moduli di un programma:
>
>|   $X/Y$    |  $0$   |  $1$   |  $2$   |  $3$   | $p_X(x)$ |
>|:--------:|:------:|:------:|:------:|:------:|:--------:|
>|   $0$    | $0.2$ | $0.2$ | $0.05$ | $0.05$ |  $0.5$   |
>|   $1$    | $0.2$ | $0.1$ | $0.1$ | $0.1$ |  $0.5$   |
>| $p_Y(y)$ | $0.4$ | $0.3$ | $0.15$ | $0.15$ |   $1$    |
>
>quale è il numero atteso di errori nell'intero programma?
>- $\mathbb{E}[X]=0\cdot\sum\limits_{i=0}^3 X_i+1\cdot\sum\limits_{i=0}^3 X_i = 0+0.5 = 0.5$
>- $\mathbb{E}[Y]=0\cdot\sum\limits_{i=0}^1 Y_i+1\cdot\sum\limits_{i=0}^1 Y_i+2\cdot\sum\limits_{i=0}^1 Y_i+3\cdot\sum\limits_{i=0}^1 Y_i = 0+0.3+0.3+0.45 = 1.05$
>
>Il numero atteso di errori nel programma è dato da:
>$$\mathbb{P}[X+Y]=0.5+1.05=1.55$$

### Covarianza
Date due v.a. $X$ e $Y$, si definisce **covarianza** il valore atteso del prodotto delle loro distanze dalla media.
$$\boxed{\text{Cov}(X,Y)=\mathbb{E}[XY]-\mathbb{E}[X]\mathbb{E}[Y]}$$
Due v.a. si dicono **incorrelate** se $\text{Cov}[X,Y]=0$, se le due v.a. sono indipendenti allora $\text{Cov}[X,Y]=0$ (ma non è detto viceversa).

**Proprietà della covarianza**:
1. $\text{Cov}[X,Y]=\text{Cov}[Y,X]$
2. $\text{Cov}[X,X]=Var[X]$
3. $\text{Cov}[aX,Y]=a\text{Cov}[X,Y]$
4. $\text{Cov}[X,a]=0$
5. $\text{Cov}[\sum_i X_i,\sum_j Y_j] = \sum_i\sum_j\text{Cov}[X_i,Y_j]$
6. $\text{Cov}(aX,aX)=a^2\text{Cov}(X,X)$

Se le $X_i$ sono **a due a due indipendenti**, allora si ha:
- $\text{Cov}[X_i,X_j]=0$ per $i\neq j$
- $Var[\sum\limits_i X_i]=\sum\limits_i Var[X_i]$

### Correlazione
Una **correlazione** è una relazione tra due v.a. $X$ e $Y$ la quale indica una tendenza di una variabile a cambiare in funzione dell'altra, ed è definita come:
$$\boxed{\text{Cor}[X,Y]=\frac{\text{Cov}[X,Y]}{\sqrt{Var[X]\cdot Var[Y]}}\quad\text{con Var[X] e Var[Y]}\neq 0}$$
il valore generato sarà compreso tra $-1$ e $1$.
- Vicino a $-1$ si ha una forte relazione lineare con pendenza **negativa**
- Vicino a $1$ si ha una forte relazione lineare con pendenza **positiva**

![[Correlazione.svg]]

>[!Example]
>Tornando all'esempio del numero di errori nei due moduli di un programma.
>
>|   $X/Y$    |  $0$   |  $1$   |  $2$   |  $3$   | $p_X(x)$ |
>|:--------:|:------:|:------:|:------:|:------:|:--------:|
>|   $0$    | $0.2$ | $0.2$ | $0.05$ | $0.05$ |  $0.5$   |
>|   $1$    | $0.2$ | $0.1$ | $0.1$ | $0.1$ |  $0.5$   |
>| $p_Y(y)$ | $0.4$ | $0.3$ | $0.15$ | $0.15$ |   $1$    |
>
>$$\begin{flalign}
>\text{Cov}[X,Y]&=\mathbb{E}[XY]-\mathbb{E}[X]\mathbb{E}[Y]\\
>&=1\cdot 1\cdot 0.1+1\cdot 2\cdot 0.1+1\cdot 3\cdot0.1-0.5\cdot 1.05\\
>&=0.6-0.525=0.075
>\end{flalign}$$
>Dato che $Var[X]=0.5^2$ e $Var[Y]=1.0712^2$:
>$$\text{Cor}[X,Y]=\frac{0.075}{0.5\cdot 1.0712}=0.14$$

### Somma di v.a.
Sotto la condizione di **indipendenza** è facile trovare la distribuzione di due v.a.
- $\sum\limits_{i=0}^n\text{Bin}(1,p)=\text{Bin}(n, p)$
- $\sum\limits_{i=0}^n\text{Po}(\lambda_i)=\text{Po}(\sum\limits_{i=0}^n\lambda_i)$
- $\sum\limits_{i=0}^n\text{Exp}(\lambda)=\text{Ga}(n,\lambda)$
- $\sum\limits_{i=0}^n\text{N}(\micro_i,\sigma_i^2)=\text{N}(\sum\limits_{i=0}^n\micro_i,\sum\limits_{i=0}^n\sigma_i^2)$

### Media campionaria
Avendo $n$ variabili **indipendenti** e tutte con la stessa distribuzione (i.i.d.), dove ognuna ha: $\mathbb{E}[X_i]=\micro$ e $Var[X_i]=\sigma^2$, la media campionaria si calcola come:
$$\boxed{\overline{X}_n=\frac{\sum_i X_i}{n}}$$
- $\mathbb{E}[\overline{X}_n]=\micro$
- $Var[\overline{X}_n]=\frac{\sigma^2}{n}$

### Legge dei grandi numeri
Date $n$ v.a. i.i.d. con $\mathbb{E}[X_i]=\micro$ e $Var[X_i]=\sigma^2<\infty$, allora:
$$\boxed{\overline{X}_n\stackrel{p}{\to}\micro\quad\text{quando }n\to\infty}$$
ovvero la distribuzione di $\overline{X}_n$ si concentra attorno al valore atteso $\micro$.

>La LGM _forte_ dice che **quasi sicuramente** per $n$ grande i valori tendono al valore atteso.

### Teorema del limite centrale
Date $n$ v.a. i.i.d. con $\mathbb{E}[X_i]=\micro$ e $Var[X_i]=\sigma^2<\infty$, allora:
$$\boxed{\overline{X}_n\sim\text{N}(\micro,\frac{\sigma^2}{n})}$$
ovvero la distribuzione di $\overline{X}_n$ si avvicina ad una normale sebbene la distribuzione delle sue v.a. non è una normale.

>[!Example]
>Il numero di studenti iscritti a un corso di laurea segue una distribuzione di Poisson di media $100$. Se gli iscritti superano i $120$ bisogna sdoppiare i corsi. Qual è la probabilità che ciò accada?
>- $X\sim\text{Po}(100)$
>Si può vedere $X$ come la somma di $100$ v.a. $\text{Po}(1)$, la possiamo approssimare con la normale applicando la correzione per continuità:
>$$\begin{flalign}
>\mathbb{P}[X\geq 120]&=\mathbb{P}[X\geq 119.5]=\mathbb{P}[\sum_{i=1}^{100} X_i\geq 119.5]\\
>&=\mathbb{P}[Z\geq\frac{119.5-100}{\sqrt{100}}]\\
>&=1-\Phi(1.95)=0.0256
>\end{flalign}$$

