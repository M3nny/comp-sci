Sono insiemi di equazioni, dove ogni equazione è definita come **iperpiano** (insieme dei punti le cui coordinate soddisfano l'equazione)
Le soluzioni possono essere ad esempio: $x,y,z$ se siamo in $\mathbb{R}^3$ oppure $x,y$ se siamo in $\mathbb{R}^2$.
Quando abbiamo sistemi a 2 variabili che formano delle rette, esse sono:
- **Parallele**: quando non esistono soluzioni $\Rightarrow \cos \alpha = \pm 1$;
- **Coincidenti**: quando ci sono infinite soluzioni $\Rightarrow \cos \alpha = 0$;
- **Non parallele**: quando c'è solo una soluzione $\Rightarrow \cos \alpha = < 1$.

## Metodo di eliminazione di Gauss
Per calcolare la soluzione del sistema trasformo il sistema lineare in uno equivalente che ci permette di ricavare più facilmente le variabili:

## Gauss e le matrici
Prima di vedere come applicare Gauss alle matrici, è bene far notare che un sistema può essere rappresentato come matrice:
$$\begin{cases}
	      3x+2y=5\\
	      x+4y=3
	\end{cases} \Rightarrow \begin{bmatrix}
	   3 & 2 & 5\\
	   1 & 4 & 3
	\end{bmatrix}
$$
Vediamo ora le operazioni che possiamo fare sulle matrici:

1. Scambiare le righe
$$\begin{bmatrix}
		3 & 2 & 5\\
		1 & 4 & 3
	\end{bmatrix} \Rightarrow \begin{bmatrix}
		1 & 4 & 3 & R_1\\
		3 & 2 & 5 & R_2
	\end{bmatrix}
$$
2. Moltiplicare le righe per uno scalare:
$$R_1 \cdot 3= \begin{bmatrix}
		3 & 12 & 9 & R_1\\
		3 & 2 & 5 & R_2
	\end{bmatrix}
$$
3. Sottrarre una riga ad un'altra
$$R_2 - R_1 = \begin{bmatrix}
		3 & 12 & 9 & R_1\\
		0 & -10 & -4 & R_2
	\end{bmatrix}
$$
4. Semplificare dividendo, in questo caso dividiamo $R_1$ per $3$ e $R_2$ per $2$:
$$\begin{bmatrix}
		1 & 4 & 3 & R_1\\
		0 & -5 & -2 & R_2
	\end{bmatrix}
$$
Per poi riscrivere il sistema:
$$\begin{cases}
	x+4y=3\\
	-5y=-2
\end{cases} \Rightarrow
\begin{cases}
	y=\frac{2}{5}\\
	x=\frac{7}{5}
\end{cases}
$$

## Sistemi lineari in $\mathbb{R}^3$
Esistono tre possibili soluzioni che possono venire fuori da questo tipo di sistema:
1. L'intersezione è un **piano**:
	Se i tre vettori sono <u>colineari</u> (stanno sulla stessa retta);
2. L'intersezione è una **retta**:
	Se i tre vettori <u>non sono colineari</u> ma si trovano sullo stesso piano che passa per l'origine.
3. L'intersezione è un **punto**:
	Se $a$ e $b$ non si trovano nella stessa retta, allora $c$ non si trova nel piano generato da $A$ e $B$.

>[!Example]
>**Risolvi il seguente sistema lineare**:
>$$\begin{cases} 
>	3x+2y+z=0\\
>	x+4y+3z=0\\
>	x+y+z=0
>\end{cases}$$
>Per capire che soluzione delle tre mi darà, devo prima vedere se i vettori sono colineari, quindi calcolo il coseno:
>$$\cos \alpha = \frac{A\cdot B}{||A||\cdot ||B||} = \frac{3\cdot 1+2\cdot 4 + 1\cdot 3}{\sqrt{14}\cdot \sqrt{26}}$$
>Il risultato sarà $<1$ perciò $A$ e $B$ non sono colineari.
>Controllo se $C$ appartiene al piano generato da $A$ e $B$
>Quindi devo verificare che $P+At+Bs = C$ per cui 
>$$t(3,2,1)+s(1,4,3)=(1,1,1) \Rightarrow \begin{cases}3t+s=1\\2t+4s=1\\1t+3s=1\end{cases}$$
>Risolvendolo arriviamo alla conclusione che $\frac{3}{5} = 1$ che ovviamente è falsa, per cui $C$ non appartiene al piano generato.


