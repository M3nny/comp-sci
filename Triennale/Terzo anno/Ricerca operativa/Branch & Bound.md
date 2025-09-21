Il **B&B** è una tecnica iterativa utilizzata per la risoluzione di problemi di programmazione matematica con **variabili intere o miste**.
L'idea è quella di utilizzare un approccio [[Teorema master#Divide et impera|divide et impera]] per trovare una stima della soluzione di ogni sottoproblema.

Consideriamo il seguente problema di PLI:
$$\begin{aligned}
\min&\space c^Tx\\
&x\in Q_0\\
&x\in \mathbb{Z}^n
\end{aligned}
\quad\equiv\quad
\begin{aligned}
\min&\space c^Tx\\
&x\in S_0
\end{aligned}$$

Indichiamo con $Q_0$ un generico poliedro, mentre con $S_0=Q_0\cap\mathbb{Z}^n$ i **punti ammissibili con coordinate intere**.
![[Poliedro con coordinate intere.svg|400]]

Sia $x_0$ la soluzione di $\min\limits_{x\in Q_0}c^Tx$ e $\hat x_0$ la sol di $\min\limits_{x\in S_0}c^Tx$, si ha naturalmente:
$$f(\hat x_0)\geq f(x_0)$$
poichè $S_0\subseteq Q_0$, ovvero si avranno più punti a disposizione per minimizzare $f$, per cui la soluzione $\hat x_0$ avrà sempre un valore maggiore o uguale alla soluzione definita dal punto $x_0$.

Il metodo del B&B consiste nel **partizionare** (da cui branch) la regione ammissibile $S_0$ nei sottoproblemi $S_i,i\in\{1\dots,k\}$ in modo tale che:
$$S_0=\bigcup_{i=1}^kS_i\qquad S_i\cap S_j=\emptyset,\space\forall i\neq j$$
cercando (se necessario) una **stima per difetto** di una soluzione del sottoproblema $(P_i)$:
$$(P_i):\min\limits_{x\in S_i}c^Tx$$
>Il sottoproblema $(P_i)$ generato viene detto **aperto** e viene inserito in una lista.

Per calcolare una stima della soluzione di $(P_i)$ si deve calcolare un **bound** per $(P_i)$, tramite la risoluzione del problema di programmazione lineare $(PL_i)$ ad esso associato ottenuto tramite un **rilassamento lineare** dei vincoli, in pratica <u>vengono rimossi i vincoli di interezza</u>.
$$(PL_i):\min_{x\in Q_i} c^Tx$$

La soluzione di $(PL_i)$ sarà dunque migliore o al massimo uguale a quella di $(P_i)$ in quanto vengono rimossi dei vincoli.
L'algoritmo non usa direttamente le soluzione dei problemi $(PL_i)$, bensì le usa per suddividere lo spazio delle soluzioni per individuarne una intera ottima.

>[!Attention]
>Il metodo del B&B non risolve mai problemi con variabili intere.

### Algoritmo
1. Sia $\tilde x\in\mathbb{Z}^n$ l'**ottimo corrente (intero)**, nel caso non fosse possibile stimarlo si pone $\tilde x=+\infty$ (non noto)

2. Sia $\mathcal{L}$ la **lista dei problemi aperti** dei quali è ancora necessario trovare un possibile bound per la soluzione, essa viene inizializzata come:
$$\mathcal{L}=\{(P_0)\}$$

3. Si estrae da $\cal L$ il problema $(P_i)$ e se ne risolve il rilassamento $(PL_i)$:
	- Se $(PL_i)$ ha $x_i$ come **soluzione non migliore** di $\tilde x$, ovvero $c^T\tilde x\leq c^T x_i$, allora si **chiude** $(P_i)$
	
	- Se $(PL_i)$ **non contiene alcuna soluzione** $Q_i\equiv\emptyset$, allora si **chiude** $(P_i)$ (questo succede quando un problema è stato diviso in troppe parti)
	
	- Se $(PL_i)$ ha $x_i$ come **soluzione migliore** di $\tilde x$, ovvero $c^T\tilde x>c^Tx_i$, sono possibili due casi:
		- Se $x_i\in\mathbb{Z}^n$ (ovvero ha tutte le componenti intere), si **aggiorna** $\tilde x$, tramite $\tilde x\leftarrow x_i$ e si **chiude** $(P_i)$
		
		- Se $x_i\notin\mathbb{Z}^n$ (ovvero non ha tutte le componenti intere), si **partiziona** $(P_i)$ in due sottoproblemi $(P_{i+1})$ e $(P_{i+2})$ rimuovendo $(P_i)$ da $\cal L$
			
			Sia $x_i^j$ la $j$-esima componente non intera del vettore soluzione $x_i$, identifichiamo i due sottoproblemi come:
			$$(P_{i+1}):\begin{align}\min\space&c^Tx\\&x\in S_i\\&x^j\leq\lfloor x_i^j\rfloor\end{align}$$
			$$(P_{i+2}):\begin{align}\min\space&c^Tx\\&x\in S_i\\&x^j\geq\lceil x_i^j\rceil\end{align}$$

4. Se $\cal L$ risulta essere vuota, allora l'algoritmo termina identificando l'attuale $\tilde x$ come soluzione del problema di partenza, altrimenti si torna al punto $3$

>Nell'ultimo caso del punto $3$, se ci dovessero essere più componenti non intere se ne sceglie una arbitrariamente.

![[B&B.svg|500]]

Dato che la soluzione $x_i=\begin{pmatrix}2\\1.5\end{pmatrix}$ non ha tutte le componenti intere si cerca una soluzione aggiungendo i vincoli $x_i^2\leq 1$ e $x_i^2\geq 2$.

## Problema del knapsack binario
Il problema del knapsack (zaino) è un esempio di **programmazione lineare**.

Ci si pone il problema di riempiere uno zaino massimizzando l'utilità degli oggetti al suo interno e minimizzando il più possibile il volume interno occupato.
- $c_i$: **utilità** di portare l'oggetto $i$-esimo nello zaino
- $a_i$: **volume dell'oggetto** $i$-esimo
- $b$: **volume dello zaino**
- $x_i=\begin{cases}1&\text{se l'oggetto i-esimo è inserito nello zaino}\\0&\text{altrimenti}\end{cases}$

Formuliamo un **problema di massimizzazione** dell'utilità complessiva:
$$(P_0):\begin{align}
\max&\space c_1x_1+\dots+c_nx_n\\
&a_ix_1+\dots+a_nx_n\leq b\\
&x\in\{0,1\}^n
\end{align}$$
Dove $x\in\{0,1\}^n$ è un vincolo di interezza (inserisco oppure no).

La versione _rilassata_ del problema è la seguente:
$$(PL_0):\begin{align}
\max&\space c_1x_1+\dots+c_nx_n\\
&a_ix_1+\dots+a_nx_n\leq b\\
&0\leq x_i\leq 1\quad i=1,...,n
\end{align}$$

Per ottenere la soluzione di quest'ultimo procediamo come segue:
1. Se $c_i=0$, l'oggetto $i$-esimo non ha utilità, poniamo quindi:
	- $x_i=0$ se $a_i\geq 0$ (non portiamo l'oggetto se occupa volume)
	- $x_i=1$ se $a_i<0$ (portiamo l'oggetto se aumenta il volume disponibile)

2. Se $a_i=0$, l'oggetto $i-$esimo non influenza il volume, poniamo quindi:
	- $x_i=0$ se $c_i\leq 0$ (non porto l'oggetto se non è utile)
	- $x_i=1$ se $c_j>0$ (portiamo l'oggetto se è utile)

3. Se $c_i\neq0$ oppure $a_i\neq 0$:
	- Se $c_i<0$ e $a_i>0$: $x_i=0$ (l'oggetto occupa volume e non è utile)
	- Se $c_i>0$ e $a_i<0$: $x_i=1$ (l'oggetto è utile e aumenta il volume)
	- Se $c_i<0$ e $a_i<0$: $x_i=1-y_i$ con $y_i\in\{0,1\}$ (non è possibile determinare $x_i$ a priori, per cui aggiungiamo un vincolo disgiuntivo)
	- Se $c_i > 0$ e $a_i>0$: non si può determinare $x_i$

Per assegnare un valore alle variabili dove $c_1>0$ e $a_i>0$, si prosegue come segue.

Ottenuto il nuovo problema di PLI dove abbiamo assegnato un valore a $n-m$ variabili ($m\leq n$), si ordinano le restanti $m$ variabili non assegnate in base al rapporto $\frac{c_i}{a_i}$ **non crescente**:
$$\frac{c_i}{a_i}\geq\frac{c_2}{a_2}\geq\dots\frac{c_m}{a_m}$$

Si determina ora l'indice $h$ con $1\leq h\leq m$ il quale indica quali sono i migliori $h$ oggetti: 
$$\sum_{i=1}^h a_i\leq b\quad\sum_{i=1}^{h+1}a_i>b$$

Si sceglie infine:
$$\begin{cases}
x_i=1&i=1,...,h\\
x_{h+1}=\frac{b-\sum\limits_{i=1}^h a_i}{a_{h+1}}\\
x_i=0&i=h+2,...,m
\end{cases}$$

### Esempio di knapsack binario
$$(P_0):\begin{align}
\max&\space x_1+4x_2-x_3+2x_4+3x_5-x_6\\
&2x_1-x_2-x_3+2x_4+x_5-x_6\leq 2.5\\
&x\in\{0,1\}^6
\end{align}$$

Per ispezione visiva possiamo già assegnare i seguenti valori:
- $x_2=1$
- $x_3=1-y_3$
- $x_6=1-y_6$

Ottenendo il seguente problema:
$$\begin{align}
\max&\space x_1+y_3+2x_4+3x_5+y_6+2\\
&2x_1+y_3+2x_4+x_5+x_6\leq 5.5\\
&x_1,x_4,x_5,y_3,y_6\in\{0,1\}
\end{align}$$

La soluzione iniziale del problema si ottiene ponendo tutte le variabili a $0$ (tranne quelle a cui è già stato assegnato $1$), in questo caso la soluzione intera corrente è data da: $\hat x=(0,1,1,0,0,1)^T$, con $f(\hat x)=2$.
>Notare che $x_3$ è stata posta a $1$ a causa di $x_3=1-y_3$, discorso analogo per $x_6$.

Ordiniamo i rapporti dei coefficienti:
$$\begin{align}
x_5&&y_3&&x_4&&y_6&&x_1\\
\downarrow&&\downarrow&&\downarrow&&\downarrow&&\downarrow\\
\frac{3}{1}&\qquad\geq&\frac{1}{1}&\qquad\geq&\frac{2}{2}&\qquad\geq&\frac{1}{1}&\qquad\geq&\frac{1}{2}
\end{align}$$

Ottenendo così il problema $(P_1)$:
$$(P_1):\begin{align}
\max&\space 3x_5+y_3+2x_4+y_6+x_1+2\\
&x_5+y_3+2x_4+y_6+2x_1\leq 5.5\\
&x_1,x_4,x_5,y_3,y_6\in\{0,1\}
\end{align}$$
$$\mathcal{L}=\{(P_1)\}$$

Essendo $h=4$, risulta per la **soluzione rilassata** di $(P_1)$:
$$x_5^{(1)}=1\quad y_3^{(1)}=1\quad x_4^{(1)}=1\quad y_6^{(1)}=1\quad x_1^{(1)}=\frac{5.5-(1+1+2+1)}{2}=0.25$$

Ottenendo così:
- $x^{(1)}=(0.25, 1, 0, 1, 1, 0)^T$
- $f(x^{(1)})=0.25+4+0+2+3+0=9.25>f(\hat x)=2$

La soluzione ottenuta è migliore della soluzione migliore intera corrente, tuttavia non è composta da soli valori interi, per cui chiudiamo il problema $(P_1)$, ed eseguiamo un branching dove, in $(P_2)$ $x_1=0$, mentre in $(P_3)$ $x_1=1$.

$$(P_2):\begin{align}
\max&\space 3x_5+y_3+2x_4+y_6+2\\
&x_5+y_3+2x_4+y_6\leq 5.5\\
&x_4,x_5,y_3,y_6\in\{0,1\}
\end{align}$$

$$(P_3):\begin{align}
\max&\space 3x_5+y_3+2x_4+y_6+3\\
&x_5+y_3+2x_4+y_6\leq 3.5\\
&x_4,x_5,y_3,y_6\in\{0,1\}
\end{align}$$
$$\mathcal{L}=\{(P_2),(P_3)\}$$

Estraiamo il problema $(P_2)$, notiamo che $h=4$, infatti possiamo porre tutte le variabili ad $1$ (tenendo conto di eventuali $x_i=1-y_i$), la **soluzione rilassata** di $(P_2)$ è data da:
- $x^{(2)}=(0,1,0,1,1,0)^T$
- $f(x^{(2)})=4+2+3=9>f(\hat x)=2$

Essendo tutte le componenti di $x^{(2)}$ intere, ed essendo che la soluzione è migliore di quella intera attuale, possiamo utilizzare questa soluzione come soluzione intera ottimale attuale, per cui $\hat x=x^{(2)}$.

Chiudiamo il problema $(P_2)$, inoltre non è necessario alcun branching dato che abbiamo trovato una soluzione intera migliore di quella precedente.

Estraiamo ora il problema $(P_3)$, notiamo che $h=2$, in questo caso non possiamo porre tutte le componenti ad $1$, otterremo infatti la componente $h+1$ con un valore decimale.

La **soluzione rilassata** di $(P_3)$ è data da:
- $x^{(3)}=(1,1,0,0.75,1,1)^T$
- $f(x^{(3)})=1+4+1.5+3-1=8.5<f(\hat x)=9$

La soluzione non è migliore di quella intera attuale, per cui possiamo chiudere il problema.

Essendo che la lista di problemi $\cal L$ è vuota, siamo giunti alla fine del problema di partenza, e abbiamo la seguente soluzione ottima:
$$x^*=(0,1,0,1,1,0)^T\quad f(x^*)=9$$
