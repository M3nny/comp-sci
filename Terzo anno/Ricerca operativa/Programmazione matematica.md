Un problema di **programmazione matematica** è un problema del tipo:
$$\stackrel{\min f(x)}{x\in C}\quad\text{oppure}\quad\stackrel{\max f(x)}{x\in C}$$
noi ci occuperemo di problemi per i quali $f:\mathbb{R}^n\to \mathbb{R}$, e $C\subseteq \mathbb{R}^n$.

I problemi di _programmazione matematica_ vengono identificati da:
- L'insieme delle **variabili** $x$ appartenenti ad uno spazio vettoriale di dimensione $n$
- La **funzione obiettivo** $f(x)$ da minimizzare o massimizzare
- Un insieme di **vincoli** del problema che devono essere soddisfatti, l'insieme dei valori che soddisfano i vincoli sono detti **soluzioni ammissibili**, e sono contenute all'interno di $C$ (**insieme ammissibile**)

Prima di risolvere il problema è necessario <u>capire se ammette soluzioni</u>, un ottimo modo per scoprirlo è utilizzare il [[Funzioni continue#Teoremi fondamentali sulle funzioni continue|teorema di Weierstrass]], il quale afferma:

Data la funzione $f(x)$ con $f:\mathbb{R}^n\to\mathbb{R}$, sia $f(x)$ [[Funzioni continue|continua]] sull'insieme $A\subset\mathbb{R}^n$ [[Limiti e continuità#Nozioni di topologia|chiuso e limitato]] (sia superiormente che inferiormente), quindi **compatto**, allora $f(x)$ ammette minimo e massimo globale su $A$.

>[!Attention]
>Il teorema di Weierstrass **non** è necessario e sufficiente per definire se una funzione ammette minimo e massimo globale, la funzione potrebbe ammettere un minimo e massimo anche non rispettando il teorema.

## Minimi/massimi - locali/globali
Dato l'insieme $C\subseteq \mathbb{R}^n$ e la funzione $f:\mathbb{R}^n\to\mathbb{R}$, indichiamo un punto $x^*\in C$ ed un intorno $I(x^*,\rho)\stackrel{\Delta}{=}\{x\in\mathbb{R}^n, ||x-x^*||_* \leq \rho\}$.

$x^*$ è **minimo locale** se:
$$f(x^*)\leq f(x),\quad\forall x\in I(x^*,\rho)\cap C$$
Nel caso $f(x^*) < f(x)$ si otterrebbe un **minimo locale stretto**, o nel caso valesse $\forall x\in C$ si avrebbe un **minimo globale**, se entrambe le precedenti affermazioni si verificassero, allora si otterrebbe un **minimo globale unico**.

$x^*$ è **massimo locale** se:
$$f(x^*)\geq f(x),\quad\forall x\in I(x^*,\rho)\cap C$$
Nel caso $f(x^*) > f(x)$ si otterrebbe un **massimo locale stretto**, o nel caso valesse $\forall x\in C$ si avrebbe un **massimo globale**, se entrambe le precedenti affermazioni si verificassero, allora si otterrebbe un **massimo globale unico**.
![[Massimi e minimi.svg]]

---
### Problema lineare
Un’industria possiede $3$ **fabbriche** $F1, F2, F3$ e $2$ **magazzini** $M1, M2$.
Nelle fabbriche durante il mese corrente si producono due tipi di prodotti $P1$ e $P2$, che vanno trasportati nei _magazzini_.
Nella seguente tabella riassumiamo i **tempi unitari** (in ore/unità) ed i **costi unitari** (in euro/unità) di produzione di $P1$ e $P2$, in ciascuna fabbrica:
![[Tabella problema lineare.png]]

In ciascuna fabbrica, è possibile far lavorare gli impianti per un numero di ore massimo pari a $2200$ ore per $F1$, $930$ ore per $F2$ e $1600$ ore per $F3$. Infine i $2$ magazzini richiedono rispettivamente un numero minimo di unità di prodotto pari a:

|       | $M1$   | $M2$   |
| ----- | ------ | ------ |
| $P_1$ | $1100$ | $1900$ |
| $P_2$ | $1650$ | $1300$ |

ed i **costi di trasporto** (euro/unità) dalle fabbriche ai magazzini, sono riassunti nella seguente tabella:

|      | $F1$   | $F2$   | $F3$   |
| ---- | ------ | ------ | ------ |
| $M1$ | $0.90$ | $0.88$ | $1.03$ |
| $M2$ | $0.99$ | $1.10$ | $0.85$ |

Scegliamo le **variabili**:
$x_{ijk}$ = numero dei prodotto $P_i$ nella fabbrica $F_j$ ed inviati al magazzino $M_k$.
Abbiamo $i=1,2$, $j=1,2,3$, $k=1,2$, per cui $12$ variabili.

La **funzione obiettivo** è definita come il valore minimo tra la somma dei costi produzione di ed i costi di trasporto:
$$\min
\left[\begin{flalign}
&\left(7.2\sum_{k=1}^2x_{11k}+6.3\sum_{k=1}^2+x_{12k}+5.2\sum_{k=1}^2x_{13k}\right)+\\
&\left(9.2\sum_{k=1}^2x_{21k}+7.3\sum_{k=1}^2x_{22k}+6.6\sum_{k=1}^2x_{23k}\right)+\\
&\left(0.90\sum_{i=1}^2x_{i11}+0.88\sum_{i=1}^2x_{i21}+1.03\sum_{i=1}^2x_{i31}\right)+\\
&\left(0.99\sum_{i=1}^2x_{i12}+1.10\sum_{i=1}^2x_{i22}+0.85\sum_{i=1}^2x_{i32}\right)
\end{flalign}\right]$$

Imponiamo poi i seguenti **vincoli** relativi ai _tempi di produzione_:
$$\begin{flalign}
0.72\sum_{k=1}^2x_{11k}+0.81\sum_{k=1}^2x_{21k}&\leq2200\\
0.63\sum_{k=1}^2x_{12k}+0.68\sum_{k=1}^2x_{22k}&\leq930\\
0.5\sum_{k=1}^2x_{13k}+0.67\sum_{k=1}^2x_{23k}&\leq1600\\
\end{flalign}$$

ed alle _richieste di unità di prodotto_:
$$\begin{flalign}
\sum_{j=1}^3x_{1j1}\geq1100\\
\sum_{j=1}^3x_{2j1}\geq1650\\
\sum_{j=1}^3x_{1j2}\geq1900\\
\sum_{j=1}^3x_{2j2}\geq1300
\end{flalign}$$

$$\underbrace{x_{ijk}\geq 0}_\text{vincolo di non-negatività}\quad \underbrace{\forall i,j,k\text{ intere}}_\text{vincolo di interezza}$$
