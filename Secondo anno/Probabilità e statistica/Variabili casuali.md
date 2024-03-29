Uno spazio campionario **non** è detto che sia **numerico**, per questo usiamo **variabili casuali** (o aleatorie), le quali rappresentano una funzione $X:\Omega\to\mathbb{R}$ dove $X$ è una funzione che assume valori numerici in base all'esito dell'evento.

Diciamo che $X(\Omega)$ è il **supporto** di $X$, inoltre abbiamo mappato ogni elemento di $\Omega$ ad un numero appartenente ad $\mathbb{R}$, rendendo di fatto $\Omega$ un sottoinsieme di $\mathbb{R}$.

![[Riduzione X(Omega).svg]]
Dobbiamo ora assegnare le probabilità ai nuovi eventi del nuovo spazio campionario vedendo prima se lo **spazio campionario indotto** è numerabile oppure no.
## Funzione di massa
Quando $X(\Omega)$ è **numerabile** usiamo una **variabile aleatoria discreta** $X$ la quale assume valori in un [[La cardinalità#Insiemi numerabili|insieme finito]].
>[!Example]
>Immaginiamo di avere un bersaglio, dove il cerchio rosso da $20$ punti, sia $A$ l'evento "il lancio cade nel rosso" possiamo mappare: $A=[X=20]$, per cui $\mathbb{P}[A]=\mathbb{P}[X=20]$.

La somma delle probabilità degli eventi mappati è $1$, in quanto sono tutte partizioni di $\Omega$.

La probabilità $\mathbb{P}(x)=\mathbb{P}[X=x]$ viene chiamata **funzione di probabilità (o massa)** dove i valori supportano la probabilità (massa) degli elementi di $X$.
Una funzione si definisce tale se soddisfa le seguenti **proprietà**:
- $0\leq p_i\leq 1,\space\forall i$
- $\sum_ip_i=1$ 

>[!Example]
>Considerando il solito esempio con 4 palline bianche numerate da 1 a 4 e 3 nere numerate da 1 a 3.
>Sia $X$ il numero estratto dall'urna.
>$$X\in\{1,2,3,4\}=X(\Omega)\subset\mathbb{R}$$
>$$\mathbb[X=1]=\frac{2}{7},\quad\mathbb{P}[X=2]=\frac{2}{7},\quad\mathbb{P}[X=3]=\frac{2}{7},\quad\mathbb{P}[X=4]=\frac{1}{7}$$
>$$P_X(x)=\begin{cases}\frac{2}{7}&\text{se }x=1,2,3\\\frac{1}{7}&\text{se }x=4\\0&\text{altrimenti}\end{cases}$$
>![[Funzione di massa.png|450]]
>

>[!Attention]
>Posso avere due variabili casuali diverse con la stessa funzione di probabilità.
>Considerando il lancio di una moneta:
>- $X$ = numero di croci $X(\Omega)=\{0,1\}$
>- $Y$ = numero di teste$Y(\Omega)=\{0,1\}$
>$$\mathbb{P}_x(1)=\mathbb{P}[X=1]=\frac{1}{2}=\mathbb{P}[Y=1]=\mathbb{P}_y(1)=\mathbb{P}[X=0]=\mathbb{P}[Y=0]$$
## Funzione di densità
Quando $X(\Omega)$ **non è numerabile** usiamo una **variabile aleatoria continua** $X$ la quale assume valori in un sottoinsieme di $\mathbb{R}$ non numerabile.
La probabilità di assumere un valore nell'insieme non numerabile $A$ è:
$$\boxed{\mathbb{P}[X\in A]=\int_Af(x)dx}$$
dove $f(x)$ è la **funzione di densità**.
Una funzione si definisce tale se soddisfa le seguenti **proprietà**:
- $f(x)\geq 0,\space\forall x\in\mathbb{R}$
- $\int_\mathbb{R}f(x)dx=1$, ovvero l'area sottesa alla funzione è pari a $1$
![[Funzione di densità.svg]]
>[!Example]
>Determinare se la seguente funzione può essere la funzione di densità per una variabile casuale continua, ed in caso affermativo per quale valore di $K$.
>$$f(x)=\begin{cases}Kx&x\in(-1,1)\\0&\text{altrimenti}\end{cases}$$
>Ci stiamo chiedendo per quale valore di $K$ vale $\int_{-1}^1Kxdx=1$
>$$K\left[\frac{x^2}{2}\right]_{-1}^1=K\left[\frac{1}{2}-\frac{1}{2}\right]=0$$
>è impossibile per qualsiasi valore di $K$ che le proprietà di una funzione di densità siano verificate, quindi $f(x)$ non può essere una funzione di densità.

>[!Attention]
>Per considerare la probabilità di un singolo elemento non numerabile, bisogna eseguire l'integrale $\int_a^af(x)dx$ il quale risulterà essere $0$ in quanto, il trapezoide rappresentante quel elemento avrà una base infinitamente piccola.

## Funzione di ripartizione
Si dice **funzione di ripartizione** (o di distribuzione cumulativa) di una variabile aleatoria $X$ la funzione $F:\mathbb{R}\to[0,1]$ dove:
$$\boxed{F(x)=\mathbb{P}[X\leq x],\space\forall x\in\mathbb{R}}$$
rappresenta la probabilità cumulata fino al punto $x$ compreso, ovviamente la probabilità massima sarà $1$.
Una funzione si definisce tale se soddisfa le seguenti **proprietà**:
- $F$ è crescente in senso lato
- $F$ è continua a destra
- $\lim\limits_{x\to -\infty}F(x)=0$ e $\lim\limits_{x\to +\infty}F(x)=1$

#### Funzione di ripartizione di una v.a. discreta
Rappresenta una **funzione a tratti**, con salti in corrispondenza dei punti di massa $x_1,x_2,...$
$$\boxed{F(x)=\sum_{i:x_i\leq x}\mathbb{P}[X=x_i]=\sum_{i:x_i\leq x}p_i}$$
ovvero la probabilità nel punto di massa $x_i$ è data dalla somma dei punti di massa fino a $x_i$ compreso.
![[Funzione di ripartizione discreta.png|500]]
Dalla funzione di ripartizione si può risalire alla funzione di probabilità della variabile tramite:
$$\mathbb{P}[X=x]=F(x)-F(x^-)$$
dove $F(x)$ è il punto di cui voglio calcolare la probabilità e $F(x^-)$ è la probabilità cumulata fino al punto $x$ escluso.

#### Funzione di ripartizione di una v.a. continua
Rappresenta una **funzione continua** così definita:
$$\boxed{F(x)=\int_{-\infty}^xf(t)dt}$$
>[!Example]
>Avendo densità$f(x)=2e^{-2x}$, tenendo in considerazione che $x$ assumerà valori $>0$ si ha:
>$$F(x)=\int_0^x2e^{-2t}dt=[-e^{-2t}]_0^x=1-e^{-2x}$$
>![[Funzione di ripartizione continua.png|400]]

Dalla funzione di ripartizione si può risalire alla **densità** di probabilità della v.a. in tutti i punti in cui $F(x)$ è derivabile tramite:
$$f(x)=\frac{d}{dx}F(x)$$

