Le catene di Markov sono un modello in cui una successione di v.a. discrete con valori appartenenti ad un **insieme degli stati** sono legate dalla seguente dipendenza:
$$\boxed{P(X_{n+1}=j|X_n=i)=p_{ij}}$$
ovvero: il prossimo stato di una v.a. è dipendente solo da quello presente.
$P$ è la **matrice di transizione** ed i suoi elementi sono le **probabilità di transizione**.
$$P=\begin{pmatrix}
p_{11}&p_{12}&...&p_{1M}\\
p_{21}&p_{22}&...&p_{2M}\\
\vdots&\vdots&\ddots&\vdots\\
p_{M1}&p_{M2}&...&p_{MM}
\end{pmatrix}$$
Ogni **riga** rappresenta il **presente**, mentre le **colonne**, la probabilità di andare verso un altro stato (transizione verso un altro **futuro**).
- Tutte le righe sommano $1$.
>Lo stato iniziale viene indicato con $\pi^{(0)}$.

### Transizione a $n$ passi
Dalla matrice di transizione possiamo solo osservare il futuro prossimo, ma se volessimo effettuare più passi (e.g. 2) dovremmo usare $p_{ij}^{(2)}$ il quale è l'elemento $ij$ della matrice $P^2=P\cdot P$.
$$p_{ij}^{(2)}=P(X_2=j|X_0=i)=\begin{pmatrix}p_{i1}&...&p_{iM}\end{pmatrix}\begin{pmatrix}p_{1j}\\ \vdots\\p_{Mj}\end{pmatrix}$$
questa formula si può estendere a $n$ passi moltiplicando ancora per righe e colonne.

>[!Example]
>Nel mondo di Oz ci sono tre possibili situazioni metereologiche:
>$1$=pioggia, $2$=sole, $3$=neve.
>- Non ci sono mai due giorni consecutivi di sole
>- Se oggi c'è sole domani o piove o nevica con la stessa probabilità
>- Se nevica o piove, con probabilità $0.5$ domani rimane invariato altrimenti cambia a caso con probabilità $0.5$
>
>Se oggi c'è il sole, come sarà il tempo fra due giorni?
>$$S=\{1,2,3\}$$
>$$P=\begin{pmatrix}
>\frac{1}{2}&\frac{1}{4}&\frac{1}{4}\\
>\frac{1}{2}&0&\frac{1}{2}\\
>\frac{1}{4}&\frac{1}{4}&\frac{1}{2}
>\end{pmatrix}$$
>
>![[Catena di Markov.svg]]
>
>$$p_{21}^{(2)}=P(X_2=1|X_0=2)=
>\begin{pmatrix}\frac{1}{2}&0&\frac{1}{2}\end{pmatrix}
>\begin{pmatrix}\frac{1}{2}\\\frac{1}{2}\\\frac{1}{4}\end{pmatrix}=\frac{3}{8}$$
>$$p_{22}^{(2)}=P(X_2=2|X_0=2)=
>\begin{pmatrix}\frac{1}{2}&0&\frac{1}{2}\end{pmatrix}
>\begin{pmatrix}\frac{1}{4}\\0\\\frac{1}{4}\end{pmatrix}=\frac{1}{4}$$
>$$p_{23}^{(2)}=P(X_2=3|X_0=2)=
>\begin{pmatrix}\frac{1}{2}&0&\frac{1}{2}\end{pmatrix}
>\begin{pmatrix}\frac{1}{4}\\\frac{1}{2}\\\frac{1}{2}\end{pmatrix}=\frac{3}{8}$$

### Distribuzioni marginali
Le distribuzioni marginali si ottengono dalla probabilità iniziale della catena e dalla matrice di transizione a $n$ passi.
$$\boxed{\pi^{(n)}=\pi^{(0)}\cdot P^n}$$
>[!Example]
>Quale sarà la distribuzione del tempo fra due giorni tenendo conto che oggi c'è sole?
>Dato che oggi c'è sole, la probabilità dello stato "c'è sole" sarà pari a $1$, poi moltiplico per due volte la matrice di transizione dato che voglio sapere la distribuzione tra due giorni.
>
>$$
>\begin{flalign}\pi^{(2)}&=\pi^{(0)}\cdot P^2\\
>	&=\begin{pmatrix}0&1&0\end{pmatrix}
>	\begin{pmatrix}
>		\frac{1}{2}&\frac{1}{4}&\frac{1}{4}\\
>		\frac{1}{2}&0&\frac{1}{2}\\
>		\frac{1}{4}&\frac{1}{4}&\frac{1}{2}
>	\end{pmatrix}
>	\begin{pmatrix}
>		\frac{1}{2}&\frac{1}{4}&\frac{1}{4}\\
>		\frac{1}{2}&0&\frac{1}{2}\\
>		\frac{1}{4}&\frac{1}{4}&\frac{1}{2}
>	\end{pmatrix}\\
>	&=\begin{pmatrix}0&1&0\end{pmatrix}
>	\begin{pmatrix}
>		\frac{7}{16}&\frac{3}{16}&\frac{3}{8}\\
>		\frac{3}{8}&\frac{2}{8}&\frac{3}{8}\\
>		\frac{3}{8}&\frac{3}{16}&\frac{7}{16}
>	\end{pmatrix}\\
>	&=\begin{pmatrix}\frac{3}{8}&\frac{2}{8}&\frac{3}{8}\end{pmatrix}
>\end{flalign}
>$$

### Catene regolari
Una catena si dice **regolare** se esiste un $n$ per cui $P^n$ ha tutti elementi $>0$.
Ciò significa che dopo $n$ passi posso sempre raggiungere uno stato qualsiasi
(come nell'esempio di Oz con $P^2$ in cui non compaiono $0$).

Mentre è **irregolare** se non esistono $n$ passi per cui da uno stato posso raggiungerne un altro.

### Distribuzione stazionaria
La distribuzione stazionaria è una distribuzione di probabilità che si mantiene costante all'evolversi nel tempo della catena.

Se la distribuzione iniziale è la distribuzione stazionaria $\pi$, allora:
$$\pi P^n=\pi\quad\forall n$$
$$\sum_{i=1}^M\pi_i=1$$
e tutte le distribuzioni marginali della catena sono uguali a quest'ultima.

Per **trovare la distribuzione stazionaria** bisogna risolvere il sistema a $n$ equazioni, dove $n$ è il numero di stati, per cui $\sum\limits_{i=1}^M\pi_i=1$.
>[!Example]
>Trovare la distribuzione stazionaria data la seguente matrice di transizione:
>$$P=\begin{pmatrix}
>\frac{1}{2}&\frac{1}{4}&\frac{1}{4}\\
>\frac{1}{2}&0&\frac{1}{2}\\
>\frac{1}{4}&\frac{1}{4}&\frac{1}{2}
>\end{pmatrix}$$
>
>Dato che i valori sono tutti in forma di frazione, è meglio lavorare con degli interi moltiplicando gli elementi per $4$.
>$$\begin{cases}
>4\pi_1=2\pi_1+2\pi_2+\pi_3\\
>4\pi_2=\pi_1+\pi_3\\
>4\pi_3=\pi_1+2\pi_2+2\pi_3\\
>\pi_1+\pi_2+\pi_3=1
>\end{cases}=
>\begin{cases}
>\pi_3=2\pi_2\\
>\pi_1=2\pi_2\\
>\pi_1+\pi_2+\pi_3=1
>\end{cases}
>$$
>da come soluzione $\pi=(0.4,0.2,0.4)$.

### Random walk
Una random walk (o passeggiata aleatoria) è una catena di Markov con spazio degli stati $S=\mathbb{Z}$ che ad ogni istante di muove da in un verso con probabilità $p$ oppure il suo opposto con probabilità $1-p$.

Si possono aggiungere delle **barriere** che modificano il comportamento del sistema:
- **Non assorbenti**: una volta raggiunte, il sistema rimbalza allo stato precedente (catena regolare)
- **Assorbenti**: una volta raggiunte il sistema si ferma (catena non regolare)

![[Random walk.svg|500]]
