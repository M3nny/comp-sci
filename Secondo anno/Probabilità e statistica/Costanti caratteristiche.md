Le **costanti caratteristiche** sintetizzano informazioni sulla distribuzione di probabilità di una v.a.
### Valore atteso
Il **valore atteso** ($\mathbb{E}$xpected value) rappresenta la media (o centro di massa) di una v.a. ed è dato dalla somma dei valori di $X$ moltiplicati per la loro probabilità (o peso).
$$\boxed{\mathbb{E}[X]=\sum_ix_ip_i\quad\text{(X v.a. discreta)}}$$
$$\boxed{\mathbb{E}[X]=\int_\mathbb{R}xf(x)dx\quad\text{(X v.a. continua)}}$$

>[!Example]
>Usando la solita urna con $X$ che è una **v.a. discreta**:
>$$P_X(x)=\begin{cases}\frac{2}{7}&\text{se }x=1,2,3\\\frac{1}{7}&\text{se }x=4\\0&\text{altrimenti}\end{cases}$$
>$$\mathbb{E}[X]=1\frac{2}{7}+2\frac{2}{7}+3\frac{2}{7}+4\frac{1}{7}=\frac{16}{7}$$
>---
>Sia $X$ una **v.a. continua** con densità $f(x)=2e^{-2x}1_{(0,+\infty)}(x)$
>con questa notazione si indicano gli estremi dell'integrale, in quanto la probabilità compresa tra gli estremi sarà uguale a $1$, fuori sarà uguale a $0$.
>$$\mathbb{E}[X]=\int_0^{+\infty}2xe^{-2x}dx=\frac{1}{2}$$

**Proprietà del valore atteso**:
- $\mathbb{E}[a]=a$ (con $a$ costante)
- $\mathbb{E}[aX+b]=a\mathbb{E}[X]+b$ (con $a,b$ costanti)

>Da cui possiamo arrivare che $\mathbb{E}[X-\mathbb{E}[X]]=0$, ovvero il valore atteso della deviazione (o errore) di $X$ dal suo valore atteso è uguale a $0$ perchè le deviazioni positive e negative si bilanciano.
### Varianza
Dato che nel calcolare l'errore dovrei usare il valore assoluto per evitare valori negativi, il quale rende la funzione non differenziabile (è scomodo) si usa l'**errore quadratico medio** per il calcolo della **varianza**:
$$\boxed{Var[X]=\sum_i(x_i^2p_i)-[\mathbb{E}[X]]^2\quad\text{(X v.a. discreta)}}$$
$$\boxed{Var[X]=\int_\mathbb{R}x^2f(x)dx-[\mathbb{E}[X]]^2\quad\text{(X v.a. continua)}}$$
>[!Example]
>Usando la solita urna dove $X$ è una **v.a. discreta** e il valore atteso calcolato prima:
>$$P_X(x)=\begin{cases}\frac{2}{7}&\text{se }x=1,2,3\\\frac{1}{7}&\text{se }x=4\\0&\text{altrimenti}\end{cases}$$
>$$Var[X]=1^2\frac{2}{7}+2^2\frac{2}{7}+3^2\frac{2}{7}+4^2\frac{1}{7}-\left(\frac{16}{7}\right)^2$$
>---
>Usando la solita $X$ rappresentate una **v.a. continua** con densità $f(x)=2e^{-2x}1_{(0,+\infty)}(x)$ e valore atteso calcolato prima:
>$$Var[X]=\int_0^{+\infty}2x^2e^{-2x}dx-\left(\frac{1}{2}\right)^2$$
>

essendo la varianza l'errore quadratico medio, ovvero $(x-\mathbb{E}[X])^2$, si può scrivere come segue:
$$Var[X]=\mathbb{E}[X^2]-[\mathbb{E}[X]]^2$$
**Proprietà della varianza**:
- $Var[a]=0$ (con $a$ costante)
- $Var[aX+b]=a^2Var[X]$ (con $a,b$ costanti)

Altri modi per valutare la varianza sono: la **deviazione standard** la quale rappresenta lo _scarto quadratico medio_ della v.a. ed il **coefficiente di variazione**  il quale viene usato per _confrontare le dispersioni di più v.a._, questo perchè valuta la dispersione indipendentemente dall'unità di misura (e.g. la d.s. di un campione di redditi espressi in euro è diversa dalla stessa ma con redditi espressi in lire, mentre il coefficiente di variazione no).
$$\text{Deviazione standard}\quad\sigma^2=\sqrt{Var[X]}$$
$$\text{Coefficiente di variazione}\quad\sigma^*=\frac{\sigma^2}{|\mathbb{E}[X]|}=\frac{\sqrt{Var[X]}}{|\mathbb{E}[X]|}$$
### Moda
La **moda** di una v.a. indica il punto (o punti) con più massa (o densità).
Si dice **multimodale** se esistono più massimi locali, mentre si dice **senza moda** per una funzione costante.
### Mediana
A differenza della media, la **mediana** si situa dove la **probabilità è pari alla sua sinistra e alla sua destra**.

Per una v.a. **discreta** la mediana rappresenta il centro del gradino con il valore corrispondente ad essa, mentre per una v.a. continua la mediana è l'unico valore per cui la probabilità cumulata ($F$) fino a quel punto vale $\frac{1}{2}$.
### Quantili
I quantili ($\alpha$) sono **indici di posizione** i quali **generalizzano il concetto di mediana**, infatti la mediana è il quantile di livello $\frac{1}{2}$.
- **Percentili**: quantili di livello $\frac{k}{100}$ con $k=1,...,99$
- **Decili**: quantili di livello $\frac{k}{10}$ con $k=1,...,9$
- **Quartili**: quantili di livello $0.25, 0.5 \text{ (mediana)}, 0.75$ 

![[Moda Mediana Media.svg]]