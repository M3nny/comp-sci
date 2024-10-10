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
### Problema del knapsack
Il problema del knapsack (zaino) è un esempio di **programmazione lineare**.

Ci si pone il problema di riempiere uno zaino massimizzando l'utilità degli oggetti al suo interno e minimizzando il più possibile il volume interno occupato.
- $u_i$: utilità di portare l'oggetto $i$-esimo nello zaino
- $a_i$: volume dell'oggetto $i$-esimo
- $b$: volume dello zaino
- $x_i=\begin{cases}1&\text{se l'oggetto i-esimo è inserito nello zaino}\\0&\text{altrimenti}\end{cases}$

Formuliamo un **problema di massimizzazione** dell'utilità complessiva:
$$\max_x u_1x_1+...+u_nx_n$$
poniamo i seguenti **vincoli** ($C$):
$$a_1x_1+...+a_nx_n\leq b\quad\text{(vincolo lineare)}$$
$$x_i\in\{0,1\},\forall i=1,...,n\quad\text{(vincolo di interezza - inserisco oppure no)}$$
