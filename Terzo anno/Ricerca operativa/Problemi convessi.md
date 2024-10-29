## Insiemi convessi
Dato l'insieme $C\subseteq \mathbb{R}^n$ diremo che esso è **convesso** se:
$$\alpha x+(1-\alpha)y\in C,\quad \forall x,y,\in C,\quad\forall\alpha\in[0,1]$$
>Con $\alpha=0,w=y$, mentre con $\alpha=1,w=x$.

Ovvero presa una **qualunque** coppia di punti nell'insieme $C$, il segmento di punti (combinazione convessa) che li congiunge è interno all'insieme stesso.
![[Insiemi convessi.svg]]

Notare che anche l'insieme $\mathbb{R}^n$ è convesso per $n\geq 1$, inoltre **assumiamo** che l'insieme vuoto ($\emptyset$) sia convesso in quanto non nega la definizione di insieme convesso.

Dati gli insiemi convessi $C_1,...,C_m$, allora l'**insieme intersezione** degli $m$ insiemi
$$C=C_1\cap...\cap C_m$$
è a sua volta convesso.
**Dimostrazione**: vogliamo dimostrare che il segmento $[x,y]$ è contenuto interamente nell'intersezione degli insiemi, se ciò fosse vero allora $x,y\in C_1$ il quale è convesso, segue che $[x,y]\subseteq C_1$, è possibile fare lo stesso ragionamento per ogni insieme. Dato che $[x,y]$ è contenuto in tutti gli insiemi separatamente allora esso è contenuto nell'intersezione, ovvero $[x,y]\subseteq C$.

>[!Example]
>Sia $C=\{x\in\mathbb{R}^2:x_1^2+x_2^2\leq1\}$ ovvero l'insieme compreso nella circonferenza di raggio $1$ e come centro l'origine, vogliamo vedere se $w_1^2+w_2^2\leq 1$.
>$$w_1^2 + w_2^2 = ||w||_2^2=||\alpha x+(1-\alpha)y||_2^2\leq ||\alpha x||_2+||1-\alpha y||_2=$$
>$$\underbrace{\alpha||x||_2}_{\leq 1} + \underbrace{(1-\alpha)||y||_2}_{\leq 1}\leq \alpha\cdot 1+(1-\alpha)\cdot 1=1$$
>
>Notare che nell'ultimo passaggio non si è usato il valore assoluto (vedi [[Definizioni generali#Norma|norma]]), in quanto $\alpha\in[0,1]$.
>Per qualsiasi punto abbiamo dimostrato che $w\in C$, $\forall\alpha\in[0,1]$.

## Funzioni convesse
Data la funzione $f:\mathbb{R}^n\to\mathbb{R}$, e l'insieme convesso $C\subseteq \mathbb{R}^n$, $f(x)$ si dice **convessa sull'insieme $C$**, se $\forall x,y\in C$ risulta verificata la seguente proprietà:
$$f[\alpha x+(1-\alpha)y]\leq \alpha f(x)+(1-\alpha)f(y)\quad\forall\alpha\in[0,1]$$

La funzione $f(x)$ si dice **strettamente convessa** su $C$ nel caso in cui la disuguaglianza precedente fosse stretta ($<$).

Segue la rappresentazione geometrica di una funzione strettamente convessa:
![[Funzione convessa.svg|700]]

>Un modo semplice per individuarle è immaginare tutti i possibili segmenti e vedere se tutta la funzione sta al di sotto del segmento in questione.

Nel caso la disuguaglianza precedente fosse stata di maggioranza ($\geq$), si sarebbe trattato di una funzione **concava in $C$**, mentre con il simbolo di maggioranza stretta ($>$) sarebbe **concava stretta**.

>[!Tip] Convessità e concavità rispetto ad un insieme convesso
>Le funzioni convesse/concave lo sono solo rispetto ad un insieme convesso, questo perchè l'unico modo per essere sicuri che $\forall\alpha\in[0,1]$ i punti del segmento siano dentro a $C$ è avere un insieme convesso.

**Proposizione**
Data la funzione $f:\mathbb{R}^n\to\mathbb{R}$, e l'insieme $C\subseteq\mathbb{R}^n$ convesso, se $f(x)$ è convessa su $C$ allora $-f(x)$ è concava su $C$.
**Dimostrazione**
Dalla convessità di $f(x)$ segue che:
$$f[\alpha x+(1-\alpha)y]\leq \alpha f(x)+(1-\alpha)f(y),\quad\forall x,y\in C,\quad \forall\alpha\in[0,1]$$
da cui moltiplicando per $-1$ si ottiene:
$$-f[\alpha x+(1-\alpha)y]\geq \alpha[-f(x)]+(1-\alpha)[-f(y)],\quad x,y\in C,\quad\forall\alpha\in[0,1]$$

Quindi se $x^*$ è una soluzione locale/globale di $\min {f(x)}_{x\in C}$ dove $f$ è convessa su $C$, allora analogamente $x^*$ è soluzione locale/globale di $\max -f(x)_{x\in C}$ dove $-f$ è concava su $C$.

**Proposizione**
Data la funzione $f:\mathbb{R}^n\to\mathbb{R}$ affine, segue che $f(x)$ è concava e convessa su $\mathbb{R}^n$.
**Dimostrazione**
Sia ha dalla definizione di [[Definizioni generali#Funzioni lineari e affini|funzione affine]] che $f(x)=f_L(x)+\overline{c}$, dove $f_L(x)$ è una funzione lineare, mentre $\overline{c}\in\mathbb{R}$, per cui prendendo una coppia qualsiasi di punti $x,y\in\mathbb{R}^n$ ed uno scalare $\alpha\in[0,1]$, si avrà:
$$\begin{flalign}
f[\alpha x+(1-\alpha)y]&= f_L[\alpha x+(1-\alpha)y]+\overline{c} = \alpha f_L(x)+(1-\alpha)f_L(y)+\overline{c}\\
&=\alpha f_L(x)+(1-\alpha)f(y)+\alpha\overline{c}+(1-\alpha)\overline{c}\\
&=\alpha[f_L(x)+\overline{c}]+(1-\alpha)[f_L(y)+\overline{c}]\\
&=\alpha f(x)+(1-\alpha)f(y)
\end{flalign}$$

Pertanto l'operatore di uguale può essere sostituito con le condizioni $\leq$ e $\geq$, verificando che $f$ è al contempo convessa e concava su $\mathbb{R}^n$.

### Insieme di livello
Nei problemi di ottimizzazione si ha un problema del tipo $\min f(x)$, con dei vincoli $A:\begin{cases}g_1(x)\leq b_1\\\vdots\\g_m(x)\leq b_m\end{cases}$, l'insieme dei vincoli è un'**intersezione** in quanto devono convivere tutti assieme, se gli insiemi singolarmente sono convessi allora anche la loro intersezione $A$ sarà convessa.

**Proposizione**
Data la funzione $f(x)$ con $f:\mathbb{R}^n\to\mathbb{R}$, sia $f(x)$ convessa su $\mathbb{R}^n$, allora l'**insieme di livello** (eventualmente vuoto) $\mathcal{L}_\gamma$ definito come:
$$\mathcal{L}_\gamma = \{x\in\mathbb{R}^n: f(x)\leq \gamma\}$$
è **convesso** per ogni $\gamma\in\mathbb{R}$.

Segue la rappresentazione grafica di un insieme di livello:
![[Insieme di livello.svg|700]]
>Nel caso $\gamma$ fosse un valore troppo basso, $\mathcal{L}_\gamma$ potrebbe essere vuoto.

**Dimostrazione**
Fissato $\gamma\in\mathbb{R}$ avremmo tre casi possibili:
1. $\mathcal{L}_\gamma=\emptyset$, e quindi è convesso
2. $|\mathcal{L}_\gamma|=1$, e quindi è un singleton, che per definizione è un insieme convesso
3. $|\mathcal{L}_\gamma|=\infty$, questo perchè non potrà mai contenere solo due punti dato che operiamo su $\mathbb{R}$, e quindi conterrà tutti i punti del segmento $[y,z]$

Nell'ultimo caso siano $y,z$ due punti distinti di $\mathcal{L}_\gamma$, si ha pertanto che $f(y)\leq \gamma$ e $f(z)\leq \gamma$, inoltre considerando un punto $w$ intermedio al segmento $[y,z]$ si ha:
$$w=\alpha y+(1-\alpha)z\quad \alpha\in[0,1]$$


Per la _convessità_ di $f(x)$ su $\mathbb{R}^n$ si ha:
$$f(w)=f[\alpha y+(1-\alpha)z]\leq \alpha \underbrace{f(y)}_{\leq\gamma}+(1-\alpha)\underbrace{f(z)}_{\leq\gamma}\underbrace{\leq}_{\text{maggiorazione: }\alpha\in[0,1]} \alpha\gamma +(1-\alpha)\gamma = \gamma$$

Si ha quindi che $w\in\mathcal{L}_\gamma$ per ogni $y,z\in\mathcal{L}_\gamma$, di conseguenza $\mathcal{L}_\gamma$ è convesso.

### Somma di funzioni convesse
Dato l'insieme convesso $C\subseteq\mathbb{R}^n$, siano $f_i(x)$, $i=1,...,m$ funzioni convesse su $C$, e siano dati i coefficienti $\lambda_i\geq 0$, allora la somma delle funzioni:
$$f(x)=\sum_{i=1}^m\lambda_i f_i(x)$$
è anch'essa convessa.
**Dimostrazione**
La dimostrazione è banalmente vera se $C=\emptyset$ oppure $|C|=1$, mentre se $|C|=\infty$, per ogni $x,y\in C$ e $\alpha\in[0,1]$, dalla convessità di $f_1(x),...,f_m(x)$ ed essendo $\lambda_i\geq 0$ con $i=1,...,m$ si avrà:
$$\begin{flalign}
f[\alpha x+(1-\alpha)y]&=\sum_{i=1}^m\lambda_i f_i[\alpha x+(1-\alpha)y]\leq \sum_{i=1}^m\lambda_i[\alpha f_i(x)+(1-\alpha) f_i(y)]\\
&=\alpha\underbrace{\sum_{i=1}^m \lambda_i f_i(x)}_{f(x)}+(1-\alpha)\underbrace{\sum_{i=1}^m\lambda_i f_i(y)}_{f(y)}=\alpha f(x)+(1-\alpha)f(y)
\end{flalign}$$

## Minimi locali anche globali in funzioni convesse
**Proposizione 1**
Data la funzione $f(x)$ con $f:\mathbb{R}^n\to\mathbb{R}$ e l'**insieme convesso** $C\subseteq\mathbb{R}^n$.
Sia $f(x)$ **convessa** su $C$, allora ogni punto di **minimo locale** $x^*\in C$ per il problema $\min\limits_{x\in C} f(x)$ è anche un punto di **minimo globale**.

Grazie a questo risultato, non dobbiamo più preoccuparci della soluzione fornita dal solutore, in quanto qualsiasi soluzione di qualsiasi solutore per questo problema sarà la soluzione migliore, nonchè un minimo globale.

**Dimostrazione**
Se $C=\emptyset$ non ammette soluzioni, se $|C|=1$ tale punto sarà la migliore soluzione, se invece $|C|=\infty$, sia $x^*$ un punto di minimo locale della $f(x)$ su $C$ e sia $y\in C$ un qualsiasi altro punto ammissibile:
![[Intorno nell'insieme convesso.svg]]

Introduciamo il segmento chiuso $[x^*, y]$ (contenuto in $C$ per via della convessità).
Essendo $x^*$ un minimo locale, esisterà un intorno $I(x^*, \rho)$ con $\rho>0$ tale che:
$$f(x^*)\leq f(x)\quad\forall x\in I(x^*,\rho)\cap [x^*,y]$$

Poichè deve esistere un punto $w\in[x^*,y]$, dentro all'intorno $I(x^*,\rho)$, dove $w\neq x^*$ esisterà un valore $\alpha$ per cui $w$ possa essere scritto nel seguente modo:
$$w=\alpha x^*+(1-\alpha)y\quad \alpha\in[0,1[$$

per la concavità di $f(x)$ su $C$ si ha:
$$f(w)=f[\alpha x^*+(1-\alpha)y]\leq \alpha f(x^*)+(1-\alpha)f(y)$$
$$f(x^*)\leq \alpha f(x^*)+(1-\alpha)f(y)\quad\implies\quad (1-\alpha)f(x^*)\leq (1-\alpha)f(y)\quad\forall y\in C$$

Essendo che $w\neq x^*$ e che quindi $\alpha\in[0,1[$, possiamo semplificare:
$$\cancel{(1-\alpha)}f(x^*)\leq \cancel{(1-\alpha)}f(y)\quad\implies\quad f(x^*)\leq f(y)\quad \forall y\in C$$

ovvero $x^*$ è anche un **minimo globale** di $f(x)$ su $C$.

**Proposizione 2**
Data la funzione $f(x)$ con $f:\mathbb{R}^n\to\mathbb{R}$, e l'insieme convesso $C\subseteq\mathbb{R}^n$, e sia $f(x)$ convessa su $C$, allora l'insieme delle soluzioni per il problema $\min\limits_{x\in C} f(x)$ formano un insieme convesso.

**Dimostrazione**
Se $C=\emptyset$ oppure $|C|=1$, allora per definizione è un insieme convesso, se invece $|C|=\infty$, siano $x^*$ e $y^*$ due punti di minimo locale della $f(x)$ su $C$, per la proposizione precedente saranno quindi anche minimi globali, pertanto dovrà risultare:
$$f(x^*)=f(y^*)=f_\min$$

ovvero $f(x^*)$ e $f(y^*)$ sono uguali, e identifichiamo tale valore (minimo globale) come $f_\min$.

Prendiamo un punto $w$ appartenente al segmento $[x^*,y^*]$, esiste un $\alpha\in[0,1]$ tale che $w=\alpha x^*+(1-\alpha)y^*$, per cui dalla convessità di $f(x)$ otteniamo:
$$\begin{flalign}
f(w)&=f[\alpha x^*+(1-\alpha)y^*]\leq \alpha f(x^*)+(1-\alpha)f(y^*)\\
&=\alpha f_\min +(1-\alpha) f_\min = f_\min
\end{flalign}$$

### Differenziabilità e funzioni convesse
Dato l'insieme convesso non vuoto $C\subseteq\mathbb{R}^n$ e sia $f:\mathbb{R}^n\to\mathbb{R}$ con $f\in \mathcal{C}^1(\mathbb{R}^n)$, allora $f(x)$ è _convessa_ su $C$ sse $\forall x,y,\in C$ è soddisfatta una qualsiasi delle seguenti condizioni:
1. $f(y)\geq f(x)+\nabla f(x)^T (y-x)$
2. $[\nabla f(y) -\nabla f(x)]^T(y-x)\geq 0$ (riscrittura di $1.$)

La rappresentazione geometrica è la seguente:
![[Differenziabilità e funzioni convesse.png]]

Nel caso $f\in \mathcal{C}^2(\mathbb{R}^n)$ ci si può avvalere anche della seguente condizione:
3. $(y-x)^T \nabla^2 f(x)(y-x)\geq 0$

