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
