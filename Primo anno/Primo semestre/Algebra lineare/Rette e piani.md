La **forma parametrica** della retta viene definita come:
$$X=P+At$$
dove $P$ è un **punto**, $A$ un **vettore** ed il parametro $t$  è  uno **scalare** che assumerà tutti i valori tra $A$ e $P$ in modo da creare una retta.

La **forma cartesiana** della retta viene definita come:
$$ax+by=c$$
dove quando:
- $a=0$ è parallela all'asse $x$;
- $b=0$ è parallela all'asse $y$;
- $c=0$ passa per l'origine.

### Da parametrica a cartesiana
Riscriviamo l'equazione parametrica in questo modo, dove $p_0$ è l'ascissa del punto e $p_1$ è l'ordinata mentre $a_0$ e $a_1$ sono rispettivamente il primo ed il secondo elemento del vettore.
$$r:\begin{cases}
	      x=p_0+a_0t\\
	      y=p_1+a_1t
	\end{cases}
$$
Sarà poi possibile **passare alla forma cartesiana** _isolando_ $t$ e sostituendolo.
>[!Example]
>**Trovare la retta che passa per $c=(2,3)$ e parallela al vettore $\overrightarrow{OP} (-1,2)$**
>
>
>$$r=\begin{cases} x=2-t\\y=3+2t\end{cases} \quad \rightarrow \quad r=\begin{cases} t=2-x\\y=3+2(2-x)\end{cases}$$
>$$y=3+4-2x \quad \rightarrow \quad 2x+y-7=0$$
>
>---
>**Trovare la retta passante per i punti: $A=(1,2)$ e $B=(-1,3)$**
>In questo caso non abbiamo un vettore, per cui andiamo a calcolare il vettore applicato all'orgine (non è altro che un vettore parallelo ad $A$ e $B$) $\overrightarrow{AB}$
>- $\overrightarrow{AB} = B-A = (-2,1)$
>- Ora avendo un vettore parallelo ad una possibile retta tra $A$ e $B$ posso procedere come nell'esempio precedente, ovvero trovare la retta passante per $A$ o $B$ parallela al vettore appena trovato $\overrightarrow{AB}$
>
>Per farlo utilizzerò il punto $A$ (potrei usare anche il punto $B$).
>Quindi scrivo l'equazione parametrica della retta:
>$$r=\begin{cases} x=1-2t\\y=2+t\end{cases} \quad \rightarrow \quad r=\begin{cases} x=1-2(y-2)\\t=y-2\end{cases}$$
>
>$$x=-1-2y+4 \quad \rightarrow \quad x+2y=5$$

## Piano
Avendo uno spazio 3D ($\mathbb{R}^3$) l'equazione parametrica del piano passante per un punto e parallelo a due vettori viene definita come:
$$X=P+At+Bs$$
dove $P$ è un punto e $A$ e $B$ sono i vettori.

Mentre nella forma cartesiana il piano viene definito come:
$$ax+by+cz+d=0$$

Come similmente per la retta avremo che:
- $a=0$ è parallela all'asse $x$;
- $b=0$ è parallela all'asse $y$;
- $c=0$ è parallelo all'asse $z$;
- $d=0$ passa per l'origine.

Il funzionamento del piano è analogo a quello delle rette solo che questa volta al posto di avere un singolo vettore per fare le operazioni viste in precedenza, me ne serviranno due.
>[!Example]
>**Trova il piano passante per i seguenti 3 punti non allineati**:
> $P=(1,1,1)\space Q=(1,2,1)\space R=(5,0,7)$
>
>Scelgo arbitrariamente due vettori applicati all'origine: $\overrightarrow{PQ}$ e $\overrightarrow{PR}$
>- $Q-P=(0,1,0)$
>- $R-P=(4-1,6)$
>
>Ora scelgo arbitrariamente un punto da mettere nell'equazione parametrica: $P$
>$$\pi=\begin{cases} x=1+0t+4s\\y=1+t-1s\\z=1+0t+6s\end{cases} \quad \rightarrow \quad \pi=\begin{cases} x=1+4s\\y=1+t-s\\z=1+6s\end{cases}$$
>Mi ricavo (in questo caso dalla prima riga) $s \rightarrow s=\frac{x-1}{4}$
>Vado a sostituirlo su un'altra riga (terza in questo caso):
>$$z=1+6\cdot \frac{x-1}{4} \quad \rightarrow \quad 2z-3x = -1$$

### Piano passante per un punto e perpendicolare ad un vettore
Possiamo trovare l'equazione del piano passante per un punto $P=(1,0,2)$ e perpendicolare al vettore $\overrightarrow{v} = (1,1,1)$ con la seguente formula:
$$a(x-x_0)+b(y-y_0)+c(z-z_0)=0$$
quindi nel nostro caso:
$$1(x-1)+1(y-0)+1(z-2)=0 \quad \rightarrow \quad x+y-z-3=0$$

## Fasci di rette
Un fascio di rette può essere:
- **improprio** se le rette non ha un punto di intersezione comune (parallele)
- **proprio** se le rette hanno un centro $c$ comune a tutte le rette

Avendo due rette generatrici
- $r: ax+by+c$ 
- $s: a'x+b'y+c'$
possiamo trovare il fascio di rette tramite la seguente formula:
$$(ax+by+c)+k(a'x+b'y+c')=0$$
Troveremo tutte le rette tranne $s$, oppure per "ottenere" anche $s$ bisognerebbe che $k$ tendesse all'infinito, mentre per ottenere $r$ basta porre $k=0$.

>[!Example]
>**Trovare l'equazione di una retta passante per due punti $P=(1,1)$ e $Q=(2,5)$ con i fasci di rette**:
>Prendendo in considerazione $P$ troviamo due rette che passano per esso:
>- $y-x=0$
>- $x-1=0$
>$$(y-x)+k(x-1)=0$$
>Otteniamo il valore di $k$ sostituendo le sue coordinate alla formula:
>$$(5-2)+k(2-1)=0\rightarrow k=-3$$
>$$(5-2)-3(2-1)=0\rightarrow y=-4x+3=0$$

