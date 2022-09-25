# Elementi di topologia
- Diciamo che $b \in \mathbb{R}$ è un **maggiorante** di $A$ se $x \leq b \space \forall x \in A$
	- Per maggiorante si intende un numero che è maggiore o uguale a tutti gli altri elementi dell'insieme, se esiste, allora l'insieme in questione è **limitato superiormente**, mentre il suo **estremo superiore** è il suo <u>maggiorante più piccolo</u>.

>[!Example]
>$C = \{ x \in \mathbb{R} | -2 < x < 10 \}$
>
>Non possiede nè massimo nè minimo
>
>**maggioranti** = $\forall x \in C \geq 10$
>**sup(C)** = $10$
>**minoranti** = $\forall x \in C \leq -2$
>**inf(B)** = $-2$

- Diciamo che $a \in \mathbb{R}$ è un **minorante** di $A$ se $a \leq x \space \forall x \in A$ 
	- Analogamente si intende per minorante un numero che è più piccolo o uguale a tutti gli altri elementi dell'insieme, se esiste, allora l'insieme in questione è **limitato inferiormente**, mentre il suo **estremo inferiore** è il suo <u>minorante più grande</u>.

>[!Example]
>$C = \{ x \in Q | x \leq 2 \}$
>
>Il massimo ed il minimo in questo caso, sono gli estremi dato che:
>$$-\sqrt{2}\leq x \leq \sqrt{2}$$
>
>**maggioranti** = $\forall x \in C \geq \sqrt{2}$
>**sup(C)** = $\sqrt{2}$
>**minoranti**: $\forall x \in C \leq -\sqrt{2}$
>**inf(C)** = $- \sqrt{2}$

## Proprietà
- Se un insieme è **superiormente limitato** esiste almeno un maggiorante, dove $sup(A) \in \mathbb{R}$ è **unico**, e dove togliendo una quantità minore della lunghezza dell'insieme troveremo un punto all'interno dell'intervallo dell'insieme ovvero:
$$L=sup(A) \iff L \geq a \forall a \quad \land \forall \epsilon>0 \space \exists a\in A | a>L-\epsilon$$


![[SupA.svg]]
- Nel caso in cui l'insieme fosse **superiormente illimitato** allora $sup(A)=+\infty$  e nel caso fosse **inferiormente illimitato**, allora $inf(A)=-\infty$

# Intervalli
- Un insieme $I$ più piccolo di $\mathbb{R}$ è un intervallo se esiste un punto $z$ compreso tra due punti qualsiasi $x,y$ appartenenti a $I$ tale che $z$ appartenga ad $I$, ovvero:
	- $I \leq \mathbb{R}$ è un intervallo se   $\forall x,y \in I$   con   $x \leq y$   e   $\forall z \space x \leq z \leq y$ 
![[Intervallo.svg]]
**nota**: se $a = b$, allora $[a,b] = {a}$, e $[a,b[ = ]a,b] = [a,b[ = \emptyset$


## Palle circolari
Definiamo palla circolare (aperta) l'intervallo $B$ avente **centro** $x_0$ e **raggio** $\delta > 0$ in cui $B$ ha come **estremo inferiore** $x_0 - \delta$ ed **estremo superiore** $x_0+\delta$: $$B(x_0,\delta)=]x_0-\delta, x_0+\delta[$$
![[Palla_Circolare.svg]]
- Un punto $x_0$ si dice **interno** a $B$ se $x_0 \in B$ ed esiste $\delta > 0$ tale che $B(x_0,\delta)\subset B$, ed il relativo insieme di questi punti si indica con $\mathring{B}$.
- Un punto $x_0$ si dice **esterno** a $B$ se $x_0$ è interno a $B^c=\mathbb{R} \setminus A$.
- Un punto $x_0$ si dice di **frontiera** per $B$ se $x_0$ non è ne interno, ne esterno a $B$, ed il relativo insieme di questi punti si indica con $\mathcal{F}(A)$.
- La palla circolare vista in precedenza è chiamata anche: **intorno circolare** di $x_0$, dove l'intervallo $]x_0-\delta,x_0[$ è l'intorno di **sinistra** e $]x_0,x_0+\delta[$ è l'intorno di **destra**.

## Insiemi aperti e insiemi chiusi
- $A$ si dice **aperto** se $A=\mathring{A}$
- $A$ si dice **chiuso** se $A^c$ è un insieme aperto

### Proprietà degli insiemi aperti
1. Se $A,B$ sono aperti, allora $A \cup B\space \land \space A\cap B$ sono aperti.
2. L'**unione** di <u>infiniti</u> intervalli aperti è un insieme aperto.
3. L'**intersezione** di <u>infiniti</u> intervalli aperti <u>non è sempre</u> un insieme aperto.

### Proprietà degli insiemi chiusi
1. Se $A,B$ sono chiusi, allora $A\cup B\space \land \space A\cap B$ sono chiusi.
2. L'**unione** di <u>infiniti</u> intervalli chiusi <u>non è sempre</u> un insieme chiuso.
3. L'**intersezione** di infiniti intervalli chiusi è un insieme chiuso.

## Teorema di Cantor
>[!Teorema]
>Considerata una successione $\{I_n\}_{n\in \mathbb{N}}$ di intervalli <u>chiusi e limitati</u> tali che $I_{n+1}\subseteq I_n$, allora esiste almeno un numero reale $c \in \mathbb{R}$ comune a tutti gli intervalli:
>$$c\in \bigcap^{+\infty}_{n=1}I_n$$
>Se poi l'ampiezza degli intervalli diventa arbitrariamente piccola al crescere di $n$, allora tale numero $c$ è unico:
>$$\{c\}=\bigcap^{+\infty}_{n=1}I_n$$

>[!Example]
>Trovare l'insieme di:
>$$\bigcup^{+\infty}_{N=1}[1- \frac{1}{n}, \quad 1+\frac{1}{n} ]$$
>$$n_1 = [0,2]$$
>$$n_2 = [\frac{1}{2},\frac{3}{2}]$$
>$$n_3 = [\frac{2}{3}, \frac{4}{3}]$$
>![[Es_Cantor.svg]]
>Notiamo che tutti gli intervalli sono contenuti in $[0,2]$, quindi l'unione di essi, è uguale a:
>$$\bigcup^{+\infty}_{N=1}[1- \frac{1}{n}, \quad 1+\frac{1}{n} ] = [0,2]$$