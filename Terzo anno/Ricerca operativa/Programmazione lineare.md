In questa sezione andiamo a risolvere **problemi lineari** del tipo:
$$\begin{align}
\min c^Tx\\
a_i^T\geq b_i
\end{align}$$

Per risolvere [[Problemi convessi|problemi convessi]] complessi, è possibile approcciarli partendo da un intorno locale convesso, trovarne la soluzione ottima, e poi spostarsi verso tale direzione e considerare un altro sottoinsieme convesso, nello stesso modo trasformiamo i _problemi convessi_ in problemi lineari facili da trattare, in fine si tiene conto di tutte le soluzioni dei problemi lineari per trovare una soluzione ottima al problema originale.

## Semispazi e iperpiani
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

### Poliedri
Definiamo come **poliedro** l'intersezione di un numero _finito_ di _semispazi_ e _iperpiani_.

Semispazi e iperpiani sono **convessi**, per cui anche **un poliedro è convesso** in quanto intersezione di insiemi convessi.

Di seguito vediamo cosa può rappresentare un poliedro.
![[Poliedri.svg]]

- **Semispazi** e **iperpiani** sono poliedri
- L'insieme di **soluzioni di un problema lineare** è un poliedro
- L'**insieme $\mathbb{R}^n$** è un poliedro in quanto può essere scritto come segue
$$P=\{x\in\mathbb{R}^n:0^Tx\geq 0\}\equiv\mathbb{R}^n$$
- Una **retta** è un poliedro, lo stesso vale per un **segmento** in quanto può essere rappresentato come una retta intersecata con due semispazi

