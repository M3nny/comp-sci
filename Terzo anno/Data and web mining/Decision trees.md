Un **albero decisionale** è una sequenza di test sul dataset, dove i nodi intermedi vengono chiamati **predicati**, mentre le foglie rappresentano le **predizioni**.

Prendiamo in considerazione il seguente dataset:
![[Scatter plot decision tree.png]]

Un ottimo albero decisionale potrebbe essere il seguente:
![[Decision tree.svg]]

È possibile avere più di due figli per nodo, tuttavia non se ne trae nessun vantaggio in quanto un albero con nodo più figli può comunque essere espresso tramite un albero binario.
>Ogni predicato volendo può considerare multiple features.

L'**algoritmo di Hunt** è un algoritmo [[Algoritmi greedy|greedy]] ricorsivo che viene usato per creare un albero decisionale prendendo in considerazione il miglior split (se è possibile eseguire uno split) e le condizioni di stop:

>[!Tip] Hunt's algorithm
>**BuildTree**(${\cal D}$):
$\quad$*BestSplit*, *BestGain* = *None*
$\quad$**For each** feature $f$
$\quad$ **For each** threshold $t$
$\quad\quad$ *Gain* $\gets$ goodness of the split $(f \leq t)$
$\quad\quad$ **If** Gain>=BestGain:
$\quad\quad\quad$ *BestGain* $\gets$ *Gain*
$\quad\quad\quad$ BestSplit* $\gets$ $(f \leq t)$
**If** *BestGain*$=0$ or *other stopping criterion is met*:
$\quad$ $\mu \gets$ the best prediction for ${\cal D}$
$\quad$ **Return** $Leaf(\mu)$
Let $f$ and $t$ be those of BestSplit = $(f \leq t)$
${\cal D}_L \gets \{x \in {\cal D} ~|~ x_f\leq t\}$ *(Left Partition)*
$L \gets$  **BuildTree**(${\cal D}_L$) *(Left Child)*
${\cal D}_R \gets \{x \in {\cal D} ~|~ x_f > t\}$ *(Right Partition)*
$R \gets$  **BuildTree**(${\cal D}_R$) *(Right Child)*
**Return** $Node(L,R)$

Per **goodness** si intende la bontà della predizione con quello split applicato, mentre **gain** si riferisce alla _differenza_ della goodness con e senza lo split attualmente ispezionato.
$\cal{D}$ indica il dataset attuale, $D_L$ e $D_R$ le partizioni di sinistra e destra del dataset dopo lo split.

Una **foglia** viene creata quando il miglior _gain_ possibile è pari a $0$, oppure quando qualche altro criterio di stop viene soddisfatto (e.g. BestGain supera una certa soglia, si è raggiunta una certa profondità, ...).

Un albero di decisione può sempre arrivare a **$100\%$ di accuracy** nella fase di training in quanto facendolo raggiungere la sua profondità massima si avrà che ogni foglia rappresenta un'istanza riuscendo così a predire perfettamente $\hat y$ di qualsiasi record, ciò però non significa che nella fase di testing avrà un'accuracy alta, infatti si avrà un **supporto debole** in quanto la predizione avverrà considerando un solo record, quello che si vuole è: avere **foglie che generalizzino** quanto possibile.
