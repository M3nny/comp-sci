Un problema di **programmazione matematica** è un problema del tipo:
$$\stackrel{\min f(x)}{x\in C}\quad\text{oppure}\quad\stackrel{\max f(x)}{x\in C}$$
noi ci occuperemo di problemi per i quali $f:\mathbb{R}^n\to \mathbb{R}$, e $C\subseteq \mathbb{R}^n$.

I problemi di _programmazione matematica_ vengono identificati da:
- L'insieme delle **variabili** $x$ appartenenti ad uno spazio vettoriale di dimensione $n$
- La **funzione obiettivo** $f(x)$ da minimizzare o massimizzare
- Un insieme di **vincoli** del problema che devono essere soddisfatti, l'insieme dei valori che soddisfano i vincoli sono detti **soluzioni ammissibili**, e sono contenute all'interno di $C$

Prima di risolvere il problema è necessario capire se ammette soluzioni, un ottimo modo per scoprirlo è utilizzare il [[Funzioni continue#Teoremi fondamentali sulle funzioni continue|teorema di Weierstrass]], il quale afferma:

Data la funzione $f(x)$ con $f:\mathbb{R}^n\to\mathbb{R}$, sia $f(x)$ [[Funzioni continue|continua]] sull'insieme $A\subset\mathbb{R}^n$ [[Limiti e continuità#Nozioni di topologia|chiuso e limitato]] (sia superiormente che inferiormente), allora $f(x)$ ammette minimo e massimo globale su $A$.


