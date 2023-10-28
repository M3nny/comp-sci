Uno spazio campionario **non** è detto che sia **numerico**, per questo usiamo **variabili casuali** (o aleatorie), le quali rappresentano una funzione $X:\Omega\to\mathbb{R}$ dove $X$ è una funzione che assume valori numerici in base all'esito dell'evento.

Diciamo che $X(\Omega)$ è il **supporto** di $X$, inoltre abbiamo mappato ogni elemento di $\Omega$ ad un numero appartenente ad $\mathbb{R}$, rendendo di fatto $\Omega$ un sottoinsieme di $\mathbb{R}$.

![[Riduzione X(Omega).svg]]
Dobbiamo ora assegnare le probabilità ai nuovi eventi del nuovo spazio campionario vedendo prima se lo **spazio campionario indotto** è numerabile oppure no.
## $X(\Omega)$ è **numerabile**:
Usiamo una **variabile aleatoria discreta** $X$ la quale assume valori in un [[La cardinalità#Insiemi numerabili|insieme finito]].
>[!Example]
>Immaginiamo di avere un bersaglio, dove il cerchio rosso da $20$ punti, sia $A$ l'evento "il lancio cade nel rosso" possiamo mappare: $A=[X=20]$, per cui $\mathbb{P}[A]=\mathbb{P}[X=20]$.

La somma delle probabilità degli eventi mappati è $1$, in quanto sono tutte partizioni di $\Omega$.

La probabilità $\mathbb{P}(x)=\mathbb{P}[X=x]$ viene chiamata **funzione di probabilità (o massa)** dove i valori supportano la probabilità (massa) degli elementi di $X$.

>[!Example]
>Considerando il solito esempio con 4 palline bianche numerate da 1 a 4 e 3 nere numerate da 1 a 3.
>Sia $X$ il numero estratto dall'urna.
>$$X\in\{1,2,3,4\}=X(\Omega)\subset\mathbb{R}$$
>$$\mathbb[X=1]=\frac{2}{7},\quad\mathbb{P}[X=2]=\frac{2}{7},\quad\mathbb{P}[X=3]=\frac{2}{7},\quad\mathbb{P}[X=4]=\frac{1}{7}$$
>$$P_X(x)=\begin{cases}\frac{2}{7}&\text{se }x=1,2,3\\\frac{1}{7}&\text{se }x=4\\0&\text{altrimenti}\end{cases}$$
>![[Probabilità di massa.png|500]]
>

>[!Attention]
>Posso avere due variabili casuali diverse con la stessa funzione di probabilità.
>Considerando il lancio di una moneta:
>- $X$ = numero di croci $X(\Omega)=\{0,1\}$
>- $Y$ = numero di teste$Y(\Omega)=\{0,1\}$
>$$\mathbb{P}_x(1)=\mathbb{P}[X=1]=\frac{1}{2}=\mathbb{P}[Y=1]=\mathbb{P}_y(1)=\mathbb{P}[X=0]=\mathbb{P}[Y=0]$$
## $X(\Omega)$ <u>non è</u> numerabile
Una **variabile aleatoria continua** $X$ assume valori in un sottoinsieme di $\mathbb{R}$ non numerabile.
La probabilità di assumere un valore nell'insieme non numerabile $A$ è:
$$\mathbb{P}[X\in A]=\int_Af(x)dx$$
dove $f(x)$ è la **funzione di densità**.
![[Funzione di densità.svg]]
>[!Example]
>Sia $X$ una variabile aleatoria con densità:
>$$f(x)=2e^{-2x}$$
>considerando l'evento $A=[1,2]$:
>$$\mathbb{P}[X\in A]=\mathbb{P}[X\in[1,2]]=\int_1^22e^{-2x}dx=e^{-2}-e^{-e^4}$$

>[!Attention]
>Per considerare la probabilità di un singolo elemento non numerabile, bisogna eseguire l'integrale $\int_a^af(x)dx$ il quale risulterà essere $0$ in quanto, il trapezoide rappresentante quel elemento avrà una base infinitamente piccola.
