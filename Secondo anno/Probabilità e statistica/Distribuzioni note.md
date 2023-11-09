Usiamo le **distribuzioni note** per ricavare delle _costanti caratteristiche_ con formule note.

### Distribuzione uniforme discreta
Si dice **distribuzione uniforme discreta** se una v.a. assume un numero finito di valori, **tutti con probabilità uguale**.
$$X\sim \text{U}\{x_1,...,x_n\}$$
Se è **simmetrica**, allora il valore atteso è dato da $\mathbb{E}[X]=\frac{x_1+x_2}{2}$, dove $x_1$ e $x_2$ sono rispettivamente il valore minimo e massimo.
Se **non è simmetrica** allora $\mathbb{E}[X]=\frac{1}{n}\sum\limits_{i=1}^n x_i$ e $Var[X]=\sum\limits_{i=1}^n x_i^2\cdot p_i$
### Distribuzione ipergeometrica
Sia $X$ la v.a. che conta il numero di successo su $n$ estrazioni **senza reinserimento** da una popolazione di $N$ elementi, dei quali $K$ sono considerati successo.
Per applicare queste formule, devono essere rispettate delle [[Probabilità elementare#Popolazioni e sottopopolazioni|condizioni]].

$X$ ha una **distribuzione ipergeometrica** di parametri $N, K, n$.
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

### Distribuzione di Bernoulli
Viene chiamata **prova bernoulliana** un esperimento i cui possibili risultati possono essere classificati come _successo_, con probabilità $p$, o _insuccesso_, con probabilità $1-p$.

Sia $X$ la v.a. che prende il valore $X=1$ quando l'esito è un _successo_, e $X=0$ quando è un _insuccesso_.

Si dice che $X$ ha una **distribuzione di Bernoulli** di parametro $p\in(0,1)$.
$$X\sim \text{Ber}(p)$$
- $\mathbb{P}[X=x]=p^x(1-p)^{1-x}\space1_{\{0,1\}}(x)=\begin{cases}1-p&\text{se }x=0\\p&\text{se }x=1\\0&\text{altrimenti}\end{cases}$
- $\mathbb{E}[X]=p$
- $Var[X]=p(1-p)$

### Distribuzione binomiale
Sia $X$ la v.a. che conta il numero di _successi_ ottenuti nelle $n$ prove.
Si dice che $X$ ha una **distribuzione binomiale** di parametri $n$ e $p\in(0,1)$.
$$X\sim\text{Bin}(n,p)$$
- $\mathbb{P}[X=x]=\binom{n}{x}p^x(1-p)^{n-x}$, con $x=0,...,n$
