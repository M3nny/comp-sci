Usiamo le **distribuzioni note** per ricavare delle _costanti caratteristiche_ con formule note.

### Uniforme
La v.a. $X$ è una **distribuzione uniforme** se assume un numero finito di valori $n$, **tutti con probabilità uguale**.
$$X\sim \text{U}\{x_1,...,x_n\}$$
- $\mathbb{P}[X=x]=\frac{1}{n}$
- $\mathbb{E}[X]=\frac{x_1+x_n}{2}$
- $Var[X]=\frac{n^2-1}{12}$

---
### Ipergeometrica
La v.a. $X$ è una **distribuzione ipergeometrica** se conta il numero di successi su $n$ estrazioni **senza reinserimento** da una popolazione di $N$ elementi, dei quali $K$ sono considerati successo (rispettando le seguenti [[Probabilità elementare#Popolazioni e sottopopolazioni|condizioni]])
$$X\sim \text{Ig}(N, K, n)$$
- $\mathbb{P}[X=x]=\frac{\binom{K}{k}\binom{N-K}{n-k}}{\binom{N}{n}}$
- $\mathbb{E}[X]=n\frac{K}{N}$
- $Var[X]=n\cdot\frac{K}{N}\cdot\frac{N-K}{N}\cdot\frac{N-n}{N-1}$
	Dove $\frac{K}{N}$ sono i _successi_, $\frac{N-K}{N}$ sono gli _insuccessi_ e $\frac{N-n}{N-1}$ è la **formula di correzione**, dovuta al fatto che dopo ogni estrazione si cambiano i valori all'interno dell'insieme di estrazione, ciò implica che la varianza è sempre meno col passare delle estrazioni.

>[!Example]
>Un software ha $12$ programmi, $5$ dei quali necessitano di un upgrade.
>Se vengono scelti a caso $4$ programmi per un test:
>
>Quale è la probabilità che _almeno_ $2$ di essi siano da aggiornare?
>Sia $X$ la v.a. che conta il numero di programmi da aggiornare fra i $4$ scelti.
>$$\begin{flalign}
>\mathbb{P}[X\geq 2]&= 1-\mathbb{P}[X\leq 1]\\
>&=1-\mathbb{P}[X=0]-\mathbb{P}[X=1]\\
>&=1-\frac{\binom{5}{0}\binom{12-5}{4-0}}{\binom{12}{4}}-\frac{\binom{5}{1}\binom{12-5}{4-1}}{\binom{12}{4}}
>\end{flalign}$$
>
>Quale è il numero medio di programmi da aggiornare fra i $4$ scelti?
>$$\mathbb{E}[X]=4\frac{5}{12}=\frac{5}{3}$$

---
### Bernoulli
Viene chiamata **prova bernoulliana** un esperimento i cui possibili risultati possono essere classificati come _successo_, con probabilità $p$, o _insuccesso_, con probabilità $1-p$.

La v.a. $X$ è una **distribuzione di Bernoulli** se $X=1$ rappresenta un _successo_, e $X=0$ rappresenta un _insuccesso_.
$$X\sim \text{Ber}(p)$$
- $\mathbb{P}[X=x]=p^x(1-p)^{1-x}\space1_{\{0,1\}}(x)=\begin{cases}1-p&\text{se }x=0\\p&\text{se }x=1\\0&\text{altrimenti}\end{cases}$
- $\mathbb{E}[X]=p$
- $Var[X]=p(1-p)$

---
### Binomiale
La v.a. $X$ è una **distribuzione binomiale** se conta il numero di _successi_ ottenuti nelle $n$ prove **con reinserimento** da una popolazione di $N$ elementi, dei quali $K$ sono considerati _successo_.
$$X\sim\text{Bin}(n,p)$$
- $\mathbb{P}[X=x]=\binom{n}{x}p^x(1-p)^{n-x}$, con $x=0,...,n$
- $\mathbb{E}[X]=np$
- $Var[X]=np(1-p)$

>[!Example]
>Si pensa che il $20\%$ dei siti possa contenere la parola cercata.
>Qual è la probabilità che $5$ dei primi $10$ siti visitati contengano la parola cercata?
>$$\mathbb{P}[X=5]=\binom{10}{5}0.2^5(1-0.2)^{10-5}=0.0264$$

---
### Poisson
La v.a. $X$ è una **distribuzione di Poisson** se rappresenta un **conteggio** di cui non conosco con esattezza $n$.

In particolare si usa quando si vuole contare qualcosa all'interno di un intervallo (e.g. periodo di tempo, lunghezza...).

Si indica con $\lambda$ il conteggio, e con $k$ l'intervallo in cui succede il conteggio.
$$X\sim\text{Po}(\lambda)$$
- $\mathbb{P}[X=k]=\frac{\lambda^k}{k!}e^{-\lambda}$ con $k\in\mathbb{N}$
- $\mathbb{E}[X]=\lambda$
- $Var[X]=\lambda$

>[!Example]
>Arrivano in media $10$ email ogni $30$ minuti in una casella di posta elettronica.
>Quale è la probabilità che nella prossima mezz'ora arrivino _al massimo_ $3$ messaggi?
>$$\begin{flalign}\mathbb{P}[X\leq 3]&=\mathbb{P}[X=0]+\mathbb{P}[X=1]+\mathbb{P}[X=2]+\mathbb{P}[X=3]\\
>&=\frac{10^0}{0!}e^{-10}+\frac{10^1}{1!}e^{-10}+\frac{10^2}{2!}e^{-10}+\frac{10^3}{3!}e^{-10}\\&=0.0103\end{flalign}$$

è possibile **approssimare la binomiale** utilizzando questa distribuzione, nel caso in cui $n\geq 100$ e $p\leq 0.05$ (per la binomiale):
$$\lim_{\substack{n\to\infty\\p\to 0\\np\to\lambda}}\binom{n}{k}p^k(1-p)^{n-k}= \frac{\lambda^k}{k!}e^{-\lambda}$$
questa approssimazione è anche nota come **legge degli eventi rari**, in quanto si va a sperimentare la distribuzione dei successi, quando sono presenti _molti esperimenti_ ($n\to\infty$), ma la probabilità di successo è _molto piccola_ ($p\to 0$).
>Si sostitusice $\lambda$ con $n\cdot\lambda$ (se $n\geq 100$ e $p\leq 0.05$)

>[!Example]
>Una fabbrica fornisce il $3\%$ dei chip acquistati da un produttore di telefoni.
>Quale è la probabilità che su $100$ chip, ve ne siano _al massimo_ $3$ provenienti da quella fabbrica?
>
>Usando la binomiale:
>$$\mathbb{P}[X\leq 3]=\sum_{k=0}^3\binom{100}{k}0.003^k0.97^{100-k}=0.64724921$$
>Usando la Poisson:
>$$\sum_{k=0}^3\frac{3^k}{k!}e^{-3}=0.64723189$$

---
### Geometrica
 La v.a. $X$ ha una **distribuzione geometrica** se conta il numero di ripetizioni indipendenti necessarie per osservare il primo successo in un esperimento binario.
$$X\sim\text{Geo}(p)$$
- $\mathbb{P}[X=x]=(1-p)^{x-1}p$
- $\mathbb{E}[X]=\frac{1}{p}$
- $Var[X]=\frac{1-p}{p^2}$

Questa è l'unica distribuzione discreta che possiede la proprietà di **mancanza di memoria**, ovvero: sebbene sono state eseguite $n$ prove con insuccessi, la probabilità che la prossima prova sia un successo è uguale alla probabilità di successo della prima prova.
La proprietà può essere descritta come:
$$\mathbb{P}[X>m+n|X>m]=\frac{\mathbb{P}[X>m+n]}{\mathbb{P}[X>m]}=\mathbb{P}[X>n]$$
tenendo conto che $\mathbb{P}[X>k]=(1-p)^k$

>[!Example]
>Sia $X$ la v.a. che conta il numero di pagine da visitare per trovare per la prima volta la parola cercata, con $X\sim\text{Geo}(0.2)$.
>
>Quale è la probabilità che si debbano visitare $15$ pagine prima di trovare per la prima volta la parola cercata: 
>$$\mathbb{P}[X=15]=0.2\cdot (1-0.2)^{15-1}=0.0088$$
>
>Quale è la probabilità che si debbano visitare più di $10$ pagine sapendo che ne sono già state visitate $4$?
>$$\mathbb{P}[X>10|x>4]=\mathbb{P}[x>10-4=6]=(1-0.2)^6=0.2621$$
