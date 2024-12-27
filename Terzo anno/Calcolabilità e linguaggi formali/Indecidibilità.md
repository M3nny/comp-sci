Prima di dimostrare l'esistenza di linguaggi non decidibili andiamo per passi a capire come funzione la tecnica di **diagonalizzazione di Cantor**.

#### Funzioni biettive
Sia $f:A\to B$ una funzione:
- $f$ è **iniettiva** sse $x\neq y\implies f(x)\neq f(y)$
- $f$ è **suriettiva** sse $\forall y\in B\space\exists x\in A: f(x)=y$
- $f$ è **biettiva** sse essa è sia _iniettiva_ che _suriettiva_

Due insiemi $A$ e $B$ hanno la stessa **cardinalità** sse esiste una funzione $f:A\to B$ [[Cos'è una funzione#Iniettiva, suriettiva, biettiva|biettiva]].

Ad esempio l'insieme dei numeri naturali e l'insieme dei numeri naturali pari hanno la stessa cardinalità, possiamo infatti formulare la seguente biezione da $\mathbb{N}$ ai numeri naturali pari: $f(n)=2n$.

#### Insiemi numerabili
Un insieme si dice [[La cardinalità#Insiemi numerabili|numerabile]] sse è finito oppure ha la stessa _cardinalità_ di $\mathbb{N}$.

Ad esempio l'insieme dei numeri razionali positivi è numerabile, è possibile dimostrarlo creando una biezione da $\mathbb{N}$ a $\mathbb{Q}^+$, ovvero produrre una lista di razionali positivi tali che non vi siano ripetizioni e in cui tutti i razionali positivi siano rappresentati.

Per farlo creiamo una matrice $A$ in cui l'elemento $A_{ij}=\frac{i}{j}$ dove $i,j\in\mathbb{N}$, successivamente consideriamo solo le frazioni che producono numeri diversi prendendoli dalle diagonali.
![[Diagonalizzazione naturali a razionali.png|500]]

Dimostriamo ora che **$\mathbb{R}$ non è numerabile**.
Assumiamo per assurdo che $\mathbb{R}$ sia numerabile, allora dovrà esistere una biezione da $\mathbb{N}$ a $\mathbb{R}$, chiamiamola $f$.

| $n$      | $f(n)$               |
| -------- | -------------------- |
| $1$      | $3.\boxed14 ...$     |
| $2$      | $5.6\boxed23 ...$    |
| $3$      | $17.15\boxed2 ...$   |
| $4$      | $19.189\boxed27 ...$ |
| $\vdots$ | $...$                |

Andiamo a costruire un numero reale che _non_ occorre nel codominio di $f$ (parte destra della tabella), arrivando ad un assurdo.
Per farlo creiamo un numero il cui $i$-esimo decimale è diverso dal $i$-esimo decimale di $f(n)$, un possibile numero è formato come $0.5783 ...$, avendo quindi costruito un numero non presente nella tabella abbiamo dimostrato che $f$ non è suriettiva, quando dovrebbe esserlo in quanto funzione biettiva (per ipotesi assurda).

## Linguaggi non Turing-riconoscibili
Dimostriamo che **esistono dei linguaggi che non sono Turing-riconoscibili**, e che quindi di conseguenza esistono linguaggi non decidibili.

- <u>Dimostriamo che l'insieme delle MdT è numerabile</u>, osserviamo infatti che l'insieme delle stringhe costruite su un qualsiasi alfabeto $\Sigma$ finito è numerabile, ad esempio con $\Sigma=\{0,1\}$ possiamo creare la seguente biezione:

|    $1$     | $2$ | $3$ | $4$  | $5$  | $6$  | $7$  |  $8$  |
| :--------: | :-: | :-: | :--: | :--: | :--: | :--: | :---: |
| $\epsilon$ | $0$ | $1$ | $00$ | $01$ | $10$ | $11$ | $000$ |

Enumerando le stringhe per lunghezza crescente ci fornisce una biezione con $\mathbb{N}$, ed essendo qualsiasi MdT($Q,\Sigma,\Gamma,\delta,q_0,q_{accept},q_{reject}$) rappresentabile come stringa (in quanto l'informazione contenuta al suo interno è finita), possiamo dire che le MdT sono un sottinsieme delle stringhe e quindi sono numerabili.

- <u>Dimostriamo che l'insieme dei linguaggi non è numerabile</u>, prendiamo come esempio $L=\{0,00,01\}$, come visto precedentemente le stringhe sono numerabili, creiamo una codifica in cui il valore è $1$ se la stringa è presente nel linguaggio:


| Stringhe            | $\epsilon$ | $0$ | $1$ | $00$ | $01$ | $10$ | $11$ | $000$ |
| ------------------- | ---------- | --- | --- | ---- | ---- | ---- | ---- | ----- |
| **Codifica di $L$** | $0$        | $1$ | $0$ | $1$  | $1$  | $0$  | $0$  | $0$   |

Osserviamo che l'insieme delle stringhe binarie infinite non è numerabile, anche in questo caso lo si può dimostrare per _diagonalizzazione_ costruendo una stringa binaria infinita che non compare nella seguente tabella:

| $n$      | $f(n)$            |
| -------- | ----------------- |
| $1$      | $\boxed00110 ...$ |
| $2$      | $1\boxed1001 ...$ |
| $3$      | $01\boxed100 ...$ |
| $4$      | $100\boxed00 ...$ |
| $5$      | $1110\boxed0 ...$ |
| $\vdots$ | $...$             |

Costruiamo un numero con forma $10011 ...$, che sappiamo per certo che non sarà presente nella tabella, dimostrando così che l'insieme delle stringhe binarie infinite non è numerabile.

Essendo i linguaggi _non numerabili_ e le MdT _numerabili_, abbiamo dimostrato che esistono più linguaggi che MdT, per cui <u>dovranno esistere linguaggi non decidibili</u>.

### Accettazione - macchina di Turing
Determinare se una [[Macchina di Turing#Definizione di una macchina di Turing|macchina di Turing]] $M$ accetta una stringa $w$.
$$A_{TM}=\{<M,w>|M\text{ è una MdT e }w\in L(M)\}$$

Osserviamo che $A_{TM}$ **è Turing riconoscibile**, infatti possiamo costruire una MdT $N$ tale che $L(N)=A_{TM}$.
$N$ = su input $<M,w>$:
1. Simula $M$ su $w$
2. Ritorna il suo output

Questa macchina però _non è un decisore_ in quanto il primo passo potrebbe andare in loop se $M$ non termina.

<u>Dimostriamo che un decisore per</u> $A_{TM}$ <u>non esiste</u>.
Assumiamo per assurdo che $A_{TM}$ sia decidibile, allora dovrà esistere un decisore $H$ per $A_{TM}$:
$$H(<M,w>)=\begin{cases}accept&\text{se } M \text{ accetta }w\\reject&\text{altrimenti}\end{cases}$$

Usiamo $H$ per costruire un altro decisore $D$ definito come segue:
$D$ = su input $<M>$:
1. Simula $H$ su input $<M,<M>>$
2. Ritorna l'output invertito

Per cui possiamo vedere $D<M>$ come:
$$D(<M>)=\begin{cases}accept&\text{se } M \text{ non accetta }<M>\\reject&\text{altrimenti}\end{cases}$$
allora dalla definizioni soprastanti otteniamo:
$$D(<D>)=\begin{cases}accept&\text{se } D \text{ non accetta }<D>\\reject&\text{altrimenti}\end{cases}$$

Questo però è **assurdo** perchè $D$ eseguito su $<D>$ ritorna il contrario di quello che dovrebbe fare $D$ eseguito su $<D>$.

Per capire meglio come questo sia possibile mostriamo in forma matriciale l'esecuzione del decisore (assurdo) $H$ che opera su un input del tipo $<M_i, <M_i>>$, ovvero una MdT eseguita sulla sua rappresentazione in forma di stringa:

|          |  $<M_1>$  |  $<M_2>$  |  $<M_3>$  |  $<M_4>$  |  $...$   |  $<D>$   |
| :------: | :-------: | :-------: | :-------: | :-------: | :------: | :------: |
|  $M_1$   | $\boxed1$ |    $1$    |    $0$    |    $0$    |  $...$   | $\vdots$ |
|  $M_2$   |    $0$    | $\boxed1$ |    $0$    |    $1$    |  $...$   | $\vdots$ |
|  $M_3$   |    $0$    |    $0$    | $\boxed0$ |    $0$    |  $...$   | $\vdots$ |
|  $M_4$   |    $1$    |    $1$    |    $1$    | $\boxed1$ |  $...$   | $\vdots$ |
| $\vdots$ | $\vdots$  | $\vdots$  | $\vdots$  | $\vdots$  | $\ddots$ | $\vdots$ |
|   $D$    |    $0$    |    $0$    |    $1$    |    $0$    |  $...$   |   $?$    |

Nella tabella è possibile inserire anche una entry per il decisore $D$, il quale sappiamo comportarsi in maniera opposta all'input fornito, tuttavia quando incontrerà il suo stesso encoding $<D>$ non si può definire l'output in quanto esso dovrebbe essere l'opposto di se stesso, risultando in un assurdo.

### Linguaggi decidibili
**Teorema**
Un linguaggio $A$ è decidibile sse sia $A$, che $\bar A$ sono Turing-riconoscibili.

**Dimostrazione ($\Rightarrow$)**
Sia $A$ decidibile, allora $\bar A$ è decidibile in quanto la classe dei linguaggi decidibili è chiusa rispetto all'operazione di complemento, essendo la classe di linguaggi decidibili un sottoinsieme della classe dei linguaggi Turing-riconoscibili, essi saranno anche linguaggi Turing-riconoscibili.

**Dimostrazione ($\Leftarrow$)**
Siano $A$ e $\bar A$ Turing-riconoscibili, allora esistono delle MdT $M,N$ tali che $L(M)=A$ e $L(N)=\bar A$.

Costruiamo un _decisore_ $O$ tale che $L(O)=A$, per farlo non possiamo simulare sequenzialmente $M,N$ (o viceversa) su $w$, in quanto potrebbero andare in loop.

Utilizziamo quindi due nastri su cui vengono eseguiti alternando un passo d'esecuzione alla volta $M$ e $N$ su $w$, una delle due MdT dovrà obbligatoriamente accettare $w$.

$O$ = su input $w$:
1. Simula $M$ su $w$ per un passo di computazione sul primo nastro
	- Se $M$ accetta, allora accetta
	- Se $M$ rifiuta, allora rifiuta
2. Simula $N$ su $w$ per un passo di computazione sul secondo nastro
	- Se $N$ accetta, allora rifiuta
	- Se $N$ rifiuta, allora accetta
3. Ritorna al passo $1$

**Corollario**: $\bar A_{TM}$ non è Turing-riconoscibile.
Essendo $A_{TM}$ Turing-riconoscibile, vorrà dire che $\bar A_{TM}$ non è Turing-riconoscibile, se lo fosse, allora $A_{TM}$ sarebbe decidibile per il teorema appena visto, ma questo è assurdo.
>La classe dei linguaggi Turing-riconoscibili non è chiusa rispetto al complemento.
