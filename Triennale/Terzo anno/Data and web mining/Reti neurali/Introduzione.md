Un [neurone](https://it.wikipedia.org/wiki/Neurone) può essere semplificato come una "cosa" con:
- Molteplici input provenienti dai **dendriti**
- Un solo output trasmesso attraverso l'**assone**

Possiamo _imitare_ un neurone con una **funzione di attivazione** che riceve vari input e produce un output.

Possiamo collegare i neuroni artificiali tra loro per formare una **rete neurale**, ogni neurone quindi prenderà degli input ed inoltrerà l'output ad altri neuroni.

Ogni neurone **peserà in modo diverso gli input** in modo da fornire un output diverso agli altri neuroni.

## Processo di apprendimento
Il processo di apprendimento è il seguente:
1. Una istanza di training è presentata all'algoritmo di machine learning
2. L'algoritmo fornisce una predizione per tale istanza
3. La differenza tra la predizione e l'output desiderato è chiamata **perdita**
4. Utilizziamo l'errore per **aggiornare i pesi** dell'algoritmo
5. L'errore è pesato dal **learning rate**, un learning rate più basso consente di individuare con più precisione un minimo globale delle funzione di perdita, a scapito della velocità di allenamento
6. Ripeti dal primo punto per tutte le istanze
7. Ripeti dal primo punto molteplici volte

![[ANN learning process.png]]

Una iterazione di tutte le istanze è detta **epoca**.

## Discesa del gradiente
L'obiettivo del training è quello di trovare i pesi adatti per ogni neurone in modo da **minimizzare la funzione di perdita**.
Questa operazione è realizzata tramite la **discesa del gradiente**, la quale è una tecnica utilizzata per risolvere [[Problemi convessi|problemi convessi]].
![[Discesa del gradiente.png]]

Sia $J$ la **funzione di perdita**, vogliamo trovare i pesi $w$ che minimizzano l'errore, il processo iterativo della discesa del gradiente è definito come segue:
$$w_i^{t+1}=w_i^t-\eta\frac{\partial J}{\partial w_i^t}$$
- $w_i^{t}$: valore del parametro $w_i$ alla iterazione $t$
- $\eta$: fattore di scala il quale determina quanto grandi sono i passi effettuati lungo la direzione del gradiente, esso viene definito come **learning rate**
- $\frac{\partial J}{\partial w_i^t}$: gradiente della funzione di perdita $J$ rispetto al peso $w_i^t$

Notare come i pesi vengano aggiornati nella direzione opposta del gradiente, questo perchè vogliamo minimizzare la funzione di perdita, non aumentarla.
>Vedi [[Programmazione lineare#Gradiente della funzione obiettivo|gradiente della funzione obiettivo]].

Se l'aggiornamento dei pesi è computato dopo aver misurato la perdita $J$ su un **mini-batch** di istanze, e quindi non tutte le istanze di training, si parla di **mini-batch gradient descent**.

Un'_epoca_ consiste nel processare tutti i batch nel dataset, molteplici epoche vengono eseguite fino alla **convergenza** del modello.

L'implementazione di questo processo è noto come **back-propagation**.

Il **teorema di approssimazione universale** dice che una rete neurale con (anche) un singolo layer (nascosto) è in grado di approssimare qualsiasi funzione continua con un numero sufficiente di neuroni.

La **standardizzazione** (media = $0$, deviazione standard = $1$) o **normalizzazione** nell'intervallo $[0,1]$ è altamente raccomandata, in questo modo l'ottimizzatore convergerà più rapidamente ad una soluzione ottimale.

