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

