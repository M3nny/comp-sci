In questa sezione andiamo a risolvere **problemi lineari** del tipo:
$$\min\limits_{a_i^T\geq b_i} c^Tx$$

Per risolvere [[Problemi convessi|problemi convessi]] complessi, è possibile approcciarli partendo da un intorno locale convesso, trovarne la soluzione ottima, e poi spostarsi verso tale direzione e considerare un altro sottoinsieme convesso, nello stesso modo trasformiamo i _problemi convessi_ in problemi lineari facili da trattare, in fine si tiene conto di tutte le soluzioni dei problemi lineari per trovare una soluzione ottima al problema originale.

>Indicheremo con $n$ il **numero di variabili** e con $m$ il **numero di vincoli**.

### Semispazi e iperpiani
Data la [[Definizioni generali#Funzioni lineari e affini|funzione lineare]] $f(x)=A^Tx$, con $A\in\mathbb{R}^n$, l'insieme di punti che soddisfa
$$A^Tx\geq b\quad b\in\mathbb{R}$$
si dice **semispazio**.

Se $f(x)$ soddisfa la seguente uguaglianza:
$$A^Tx=b\quad b\in\mathbb{R}$$
si dice **iperpiano**.
>Può essere scomposto in due disuguaglianze.

Le notazioni $A^Tx\geq b$ e $A^Tx=b$ in cui $A$ è un vettore e $b$ uno scalare indicano in modo riassuntivo che tale relazione vale per ogni componente del vettore.

>[!Example]
>$$\begin{align}
>\min 3x_1+5x_2\\
>2x_1-x_2\geq 5\\
>-x_1-x_2\leq 3\\
>x_2=4
>\end{align}$$
>
>Utilizziamo la disuguaglianza "$\geq$" ovunque:
>$$\begin{align}
>\min 3x_1+5x_2\\
>2x_1-x_2\geq 5\\
>x_1+x_2\geq -3\\
>x_2\geq 4\\
>-x_2\geq -4
>\end{align}$$
>
>Riassumiamo i vincoli come:
>$$A=\begin{pmatrix}2&-1\\1&1\\0&1\\-1&0\end{pmatrix}\in\mathbb{R}^{4\times 2}\quad b=\begin{pmatrix}5\\-3\\4\\-4\end{pmatrix}\in\mathbb{R}^4$$

---
## Poliedri
Definiamo come **poliedro** l'intersezione di un numero _finito_ di _semispazi_ e _iperpiani_.

Semispazi e iperpiani sono **convessi**, per cui anche **un poliedro è convesso** in quanto intersezione di insiemi convessi.

Possiamo scrivere un poliedro nella seguente forma:
$$P=\{x\in\mathbb{R}^n:Ax\geq b\}$$

Un **poliedro limitato** viene detto **politopo**.

Di seguito vediamo alcuni esempi di poliedri.
![[Poliedri.svg]]

- **Semispazi** e **iperpiani** sono poliedri
- L'insieme di **soluzioni di un problema lineare** è un poliedro
- L'**insieme $\mathbb{R}^n$** è un poliedro in quanto può essere scritto come segue
$$P=\{x\in\mathbb{R}^n:0^Tx\geq 0\}\equiv\mathbb{R}^n$$
- Una **retta** è un poliedro, lo stesso vale per un **segmento** in quanto può essere rappresentato come una retta intersecata con due semispazi

### Gradiente della funzione obiettivo
Dato il seguente problema di ottimizzazione:
$$\min\limits_{Ax\geq b}c^Tx$$
Il gradiente $\nabla f(x)=c$ della funzione obiettivo è **ortogonale** alle [[Problemi convessi#Curva di livello|curve di livello]] di $f(x)$ ed è **orientato nel verso crescente** di $f(x)$.
![[Poliedro curve di livello.svg|500]]

**Dimostrazione (ortogonalità)**
Le curve di livello di $f(x)$, rappresentanti un [[Rette e piani#Fasci di rette|fascio di rette improprio]], sono date dagli iperpiani definiti come:
$$c^Tx=\gamma\quad\text{ con }\gamma\in\mathbb{R}$$
Consideriamo ora i due punti $\bar x,\bar y\in\mathbb{R}^n$ appartenenti alla stessa curva di livello $\gamma$:
$$c^T\bar x=c^T\bar y=\gamma$$

Possiamo scriverli come:
$$c^T\bar x=c^T\bar y\implies c^T\bar x-c^T\bar y=0\implies c^T(\bar x-\bar y)=0$$
per cui il vettore $c$ è _ortogonale_ rispetto a $(\bar x-\bar y)$, in quanto il [[Definizioni generali#Prodotto scalare|prodotto scalare standard]] ottenuto è nullo.

**Dimostrazione (direzione crescente)**
Siano ora $\bar x,\hat y\in\mathbb{R}^n$ due punti appartenenti rispettivamente alle curve di livello $\bar\gamma,\hat\gamma$, con $\hat\gamma>\bar\gamma$, possiamo scriverli come:
$$c^T\bar x=\bar\gamma\quad c^T\hat y=\hat\gamma\quad \hat\gamma>\bar\gamma$$
otteniamo sottraendo dalla seconda uguaglianza la prima:
$$c^T\hat y-c^T\bar x=\underbrace{\hat\gamma-\bar\gamma}_{>0}\implies c^T(\hat y-\bar x)>0$$
Il prodotto scalare ottenuto può essere [[Definizioni generali#Relazione tra norma e prodotto scalare|riscritto]] come:
$$\underbrace{||c||_2\cdot||\hat y-\bar x||_2}_{>0}\cdot\cos(\widehat{\bar x\hat y})>0$$
Poichè il prodotto tra nome dovrà essere positivo, spetta a $\cos(\widehat{\bar x\hat y})$ essere positivo per far valere la disuguaglianza, per cui l'angolo formato da $c(\hat y-\bar x)$ dovrà essere nell'intervallo $[0°,90°[$, quindi $c$ è orientato nel verso crescente della funzione obiettivo.

Sapendo quindi che $c$ è orientato nel verso crescente della funzione obiettivo, possiamo utilizzare la direzione $-c$ per trovare una soluzione al problema di minimizzazione.

#### Problema di minimizzazione
Supponiamo di voler risolvere il seguente problema di ottimizzazione:
$$\begin{align}
\min\space& x_1+x_2\\
&x_1\geq0\\
&x_2\geq 0
\end{align}$$
Possiamo riassumerlo, indicando:
- $c$: **coefficienti della funzione obiettivo**, ovvero il suo _gradiente_ in questo caso dato che la funzione è lineare
- $A$: **coefficienti dei vincoli**
- $b$: **termini noti**
$$c=\begin{pmatrix}1\\1\end{pmatrix}\in\mathbb{R}^2\quad
A=\begin{pmatrix}1&0\\0&1\end{pmatrix}\in\mathbb{R}^{2\times2}\quad
b=\begin{pmatrix}0\\0\end{pmatrix}\in\mathbb{R}^2$$

![[Poliedri 2.svg]]

Per trovare il punto che minimizza la funzione obiettivo dobbiamo seguire la direzione indicata da $-c$.

Nel primo disegno la soluzione è **unica**, ed è rappresentata dal punto $x=0$, mentre nel secondo disegno con un vincolo aggiuntivo ($x_1+x_2>1$), le soluzioni saranno **infinite**, ovvero tutte quelle indicate dai punti presenti all'interno del segmento segnato.
>Nel caso questo fosse un problema di massimizzazione, allora non ammetterebbe soluzioni.

>[!Attention] Riduzione del poliedro
>Con l'aggiunta di nuovi vincoli, e quindi sfaccettature del poliedro, si riducono i punti ammissibili, per cui a parità di funzione obiettivo, non si potrà ottenere una soluzione migliore con l'aggiunta di nuovi vincoli.

### Vertici
Sia $v\in P$, un punto **interno al poliedro $P$**.
Il punto $v$ si dice **vertice** del poliedro se **non esistono** $u,z\in P$ con $u\neq z$ tali che $v\in[u,z]$, ovvero $v$ non deve essere compreso all'interno di un segmento costituito da due punti interni a $P$.
>Ogni punto non presente nei margini del poliedro non potrà mai essere un vertice.

Notare come la presenza o meno di vertici non definisca il numero o presenza di soluzioni.
![[Poliedri 3.svg]]

**Proposizione**
Sia $n$ il numero di variabili, $v\in P$ è un vertice del poliedro $P$ se:
1. Esistono almeno $n$ **vincoli attivi** in $v$.

Dato un vincolo del tipo $a^Tx\geq b$, esso viene definito come **vincolo attivo** se è soddisfatto per l'uguaglianza $a^Tv=b$, dove $v$ è un punto.

2. Esattamente $n$ vincoli attivi in $v$ sono [[Definizioni generali#Indipendenza lineare|linearmente indipendenti]].

Questa condizione è necessaria per evitare che vincoli uguali vengano ripetuti per far valere il primo punto.

- Se il numero di vincoli è minore del numero di variabili ($m<n$), allora **non ci sono vertici**
- Il **numero massimo di vertici** è dato dal [[Probabilità elementare#Combinazioni|coefficiente binomiale]] $\binom{m}{n}=\frac{m!}{n!(m-n)!}$

>[!Attention] Numero massimo di vertici
>Vengono considerati anche i punti generati dall'intersezione dei vincoli al di fuori del poliedro, tali punto non saranno vertici in quanto non interni al poliedro.

![[Vincoli attivi.svg]]

In questo caso la retta $r_1$ rappresenta un _vincolo attivo_ su $u$ e $v$, ma non su $w$, notare come esistano $n=2$ (siamo in $\mathbb{R}^2$) vincoli attivi linearmente indipendenti in $v$, esso infatti è un vertice.

>[!Example]
>Trovare i vertici del seguente poliedro (se esistono).
>$$P:\begin{cases}
>(\mathrm{I})~x_1\geq 0\\
>(\mathrm{II})~x_2\geq 0\\
>(\mathrm{III})~x_2+2x_1\geq 4
>\end{cases}$$
>Notiamo che il numero di variabili è $n=2$ ed il numero di vincoli è $m=3$, per cui al massimo possono esistere $\binom{3}{2}=3$ vertici.
>
>1. Consideriamo i vincoli $(\mathrm{I})-(\mathrm{II})$
>$$\begin{cases}
>x_1=0\\
>x_2=0
>\end{cases}$$
>Il sistema sarà vero per i seguenti valori di $x_1$ e $x_2$, rappresentati nel vettore colonna $z=\binom{0}{0}$.
>Notiamo inoltre che i vettori dei coefficienti $a_1=\binom{1}{0}$ e $a_2=\binom{0}{1}$ sono linearmente indipendenti.
>>In questo caso è facile vederlo, ma altrimenti si procede verificando se $\det\begin{pmatrix}a_1&\vdots&...&\vdots&a_n\end{pmatrix}\neq 0$.
>
>Sostituiamo $z$ nelle altre disuguaglianze per verificare se i vincoli in questione formano un vertice.
>Nella terza disuguaglianza otteniamo $0\geq 4$, per cui questo non potrà essere un vertice.
>
>2. Consideriamo i vincoli $(\mathrm{I})-(\mathrm{III})$
>$$\begin{cases}
>x_1=0\\
>x_2+2x_1=4
>\end{cases}\implies z=\begin{pmatrix}0\\4\end{pmatrix}$$
>I vettori dei coefficienti sono linearmente indipendenti, e le disequazioni sono rispettate sostituendo $z$, per cui questo è un vertice.
>
>3. Consideriamo i vincoli $(\mathrm{II})-(\mathrm{III})$
>$$\begin{cases}
>x_2=0\\
>x_2+2x_1=4
>\end{cases}\implies z=\begin{pmatrix}2\\0\end{pmatrix}$$
>I vettori dei coefficienti sono linearmente indipendenti, ma le disequazioni non sono rispettate sostituendo $z$, infatti nella terza otteniamo $2\geq 4$ per cui questo non è un vertice.

## Teorema fondamentale della PL
Una **retta è contenuta** all'interno di un poliedro se ogni punto della retta è interno al poliedro, un politopo infatti non potrà mai contenere una retta.
>Anche poliedri non limitati potrebbero non contenere rette.

Dato un problema di programmazione lineare di _minimizzazione_, si supponga che il poliedro $P=\{x\in\mathbb{R}^n:Ax\geq b\}$ con $A\in\mathbb{R}^{m\times n}$ <u>non contenga rette</u>, allora potrà verificarsi _uno_ dei seguenti tre scenari:
1. $P=\emptyset$, il problema non ammette soluzioni
2. La funzione $f(x)=c^Tx$ è illimitata _inferiormente_ (o superiormente se il problema è di massimizzazione) sul poliedro ammissibile $P$
3. Esiste almeno una soluzione e questa si trova su uno dei vertici del poliedro ammissibile $P$
>L'ipotesi per cui il poliedro non deve contenere rette è importante perchè assicura che $P$ contenga almeno un vertice, rendendo possibile il terzo punto.

Per evitare di imporre l'ipotesi per cui il poliedro non debba contenere rette, trasformiamo i vincoli del seguente problema di minimizzazione:
$$\min_{Ax\geq b}c^Tx\quad x\in\mathbb{R}^n\quad A\in\mathbb{R}^{m\times n}\quad b\in\mathbb{R}^m$$

Sfruttando il fatto che possiamo trasformare una disuguaglianza di maggioranza in una uguaglianza sottraendo un numero positivo al membro di sinistra, ed essendo che ogni numero può essere espresso come la differenza tra due numeri interi, definiamo $x$ come segue:
$$x=\begin{pmatrix}x_1\\\vdots\\x_n\end{pmatrix}=\begin{pmatrix}x_1^+\\\vdots\\x^+_n\end{pmatrix}-\begin{pmatrix}x_1^-\\\vdots\\x_n^-\end{pmatrix}$$
ridefiniamo quindi i vincoli nel seguente modo:
$$\begin{align}
Ax\geq b&\leftrightsquigarrow
\begin{cases}a_i^Tx\geq b_i\\i=1,...,m\end{cases}\leftrightsquigarrow
\begin{cases}a_i^Tx-y_i=b_i\\y_i\geq0\\i=1,...,m\end{cases}\leftrightsquigarrow
\begin{cases}a_i^T(x^+-x^-)-y_i=b_i\\y_i\geq0\\x^+,x^-\geq0\\i=1,...,m\end{cases}\\ &\leftrightsquigarrow
\begin{cases}Ax^+-Ax^--I_my=b\\\begin{pmatrix}x^+\\x^-\\y\end{pmatrix}\geq0\end{cases}
\end{align}$$

dove l'utilizzo della [[Primo anno/Primo semestre/Algebra lineare/Matrici#Identità|matrice identità]] riassume la seguente scrittura:
$$\begin{aligned}
a_1^Tx+\\
\vdots\\
a_m^Tx+
\end{aligned}
\begin{pmatrix}y_1&&\\&\ddots&\\&&y_m\end{pmatrix}
\begin{aligned}&=b_1\\&\vdots\\&=b_m\end{aligned}
$$

In questo modo abbiamo ottenuto più vincoli, infatti ora lavoriamo su uno spazio dimensionale più alto, ovvero:
$$\tilde A=(A-A-I_m)\in\mathbb{R}^{m \times(2n+m)}\quad\tilde b=b\in\mathbb{R}^m$$
la soluzione al problema sarà data da $x^*=(x^+)^*-(x^-)^*$. 

Ora però il poliedro è definito soltanto tramite **valori positivi**, per cui esso sarà interamente compreso nel primo quadrante degli assi cartesiani, per cui è **impossibile che esso contenga una retta**.

Con la forma finale ottenuta dalla matrice $\tilde A\in\mathbb{R}^{\tilde m\times\tilde n}$ ed il vettore $\tilde b\in\mathbb{R}^\tilde m$ con $\tilde m=m$ e $\tilde n=2n+m$, diremo che il poliedro $\tilde P=\{z\in\mathbb{R}^\tilde n:\tilde Az=\tilde b,z\geq 0\}$ è in **forma standard**.

### Teorema fondamentale della PL (standard)
Dato un problema di programmazione lineare con poliedro in forma standard, sono possibili solo i seguenti tre casi:
1. $\tilde P=\emptyset$, il problema non ammette soluzioni
2. La funzione $f(x)=\tilde c^Tx$ è illimitata _inferiormente_ (o superiormente se il problema è di massimizzazione) sul poliedro ammissibile $\tilde P$
3. Esiste almeno una soluzione e questa si trova su uno dei vertici del poliedro ammissibile $\tilde P$

