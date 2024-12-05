## Costo fisso
Dato un problema generico di [[Programmazione lineare|programmazione lineare]]:
$$\begin{align}
\min_x&\space c^Tx\\
&x\in\mathcal{A}\\
&x\geq 0
\end{align}\quad x\in\mathbb{R}^n,\mathcal{A}\text{ è un poliedro}$$

introduciamo un **costo fisso** $P$ definito come segue:
$$\begin{cases}
\text{se }x_\hat i>0\text{ allora paghiamo un costo fisso }P>0\\
\text{se }x_\hat i=0\text{ allora NON paghiamo un costo fisso}
\end{cases}$$

![[Costo fisso e variabile.svg]]

$P$ nella pratica è il valore da pagare nel caso un servizio venisse attivato (anche di poco), mentre $c_\hat i$ è il coefficiente di $x_\hat i$ nella funzione obiettivo, il **costo variabile** infatti è indicato come $c_\hat ix_\hat i$.
>Notare la non linearità di tale funzione disegnata.

Per introdurre $P$ nel problema descritto sopra, **mantenendone la linearità**, inseriamo i seguenti vincoli:
$$\begin{align}
\min_{x,y}&\space c^Tx+yP\\
&x\in\mathcal{A}\\
&x\geq 0\\
&y\geq\frac{x_\hat i}{M},\quad M\gg 1\\
&y\in\{0,1\}
\end{align}$$

dove:
- $y$ è una variabile scelta (dal solutore) tra $0$ o $1$
- $M$ una costante molto maggiore di $x_\hat i$
- Se $y=0$ allora non verrà pagato il costo fisso, allora per definizione dei vincoli anche $x_\hat i=0$
- Se $y=1$ vengono attivati i costi fissi
>La linearità del modello è data dall'introduzione della variabile $y$.

>[!Attention] Non linearità
>Inserire nei vincoli operazioni non lineari come prodotto o quoziente tra variabili porterebbe il problema ad essere _non lineare_.

## Vincoli disgiuntivi
Dato il problema di programmazione lineare:
$$\begin{align}
\min_x&\space c^Tx\\
&x\in\mathcal{A}\\
&a_1^Tx\leq b_1\\
&a_2^Tx\leq b_2
\end{align}$$

Vogliamo imporre che **solo un vincolo** sia soddisfatto, per farlo aggiungiamo i seguenti vincoli:
$$\begin{align}
\min_{x,\alpha,\beta}&\space c^Tx\\
&x\in\mathcal{A}\\
&a_1^Tx\leq b_1+\alpha M\quad M\gg 1\\
&a_2^Tx\leq b_2+\beta M\\
&\alpha+\beta = 1\\
&\alpha,\beta\in\{0,1\}
\end{align}$$

Il solutore in questo modo sceglierà quale è il vincolo da far valere per minimizzare la funzione obiettivo.
- Se $\alpha=1$, il vincolo $a_1^Tx\leq b_1+\alpha M$ non verrà soddisfatto
- Se $\beta=1$, il vincolo $a_2^Tx\leq b_2+\beta M$ non verrà soddisfatto

Notare come la somma $\alpha+\beta$ deve essere pari a $1$, per cui un singolo vincolo potrà essere soddisfatto, in quanto $\alpha,\beta\in\{0,1\}$.

Generalizziamo lo stesso problema ad un caso con $m$ vincoli, dove _solo uno_ verrà soddisfatto:
$$\begin{align}
\min_{x,\alpha}&\space c^Tx\\
&x\in\mathcal{A}\\
&a_1^Tx\leq b_1+\alpha_1 M\quad M\gg 1\\
&\vdots\\
&a_m^Tx\leq b_m+\alpha_m M\\ 
&a_1+\dots+a_m=m-1\\
&\alpha_1,\dots,a_m\in\{0,1\}
\end{align}$$

Di seguito altre varianti del problema:
- **Solo $k$** vincoli soddisfatti: $a_1+\dots+a_m=m-k$
- **Al massimo 1** vincolo soddisfatto: $a_1+\dots+a_m\geq m-1$
- **Almeno 1** vincolo soddisfatto: $a_1+\dots+a_m\leq m-1$


