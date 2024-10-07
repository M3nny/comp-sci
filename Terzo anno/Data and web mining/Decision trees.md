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

Un albero di decisione può sempre arrivare a **$100\%$ di accuracy** nella fase di training in quanto facendolo raggiungere la sua profondità massima si avrà che ogni foglia rappresenta un'istanza riuscendo così a predire perfettamente $\hat y$ di qualsiasi record, ciò però non significa che nella fase di testing avrà un'accuracy alta, infatti si avrà un **supporto debole** in quanto la predizione avverrà considerando un solo record, quello che si vuole è avere **foglie che generalizzino** quanto possibile.

---
## Gain
Nella classificazione rappresentiamo l'**errore** $E$ come una frazione delle istanze classificate in modo errato.

Con un dataset $\cal D$, la miglior predizione è data da:
$$\mu = \arg\min_\mu Error(\mathcal{D},\mu)=\arg\min_\mu\frac{1}{|\mathcal{D}|}\sum_{(x,y)\in\mathcal{D}}E(y,\mu)$$
>Dove $E(y,\mu)$ è $0$ se $\mu=y$, mentre è $0$ altrimenti.

Dato un predicato $f\leq t$, definiamo il **gain** di uno split come la <u>riduzione dell'errore rispetto alla non suddivisione del nodo</u>:
$$Gain(f,t|{\cal D})=Error(\mathcal{D})-\left(\frac{|\mathcal{D}_L|}{|\mathcal{D}|}Error(\mathcal{D}_L) + \frac{|\mathcal{D}_R|}{|\mathcal{D}|}Error(\mathcal{D}_R)\right)$$

## Impurità del nodo
L'impurità del nodo è collegata all'errore, il quale può essere calcolato in vari modi.
>D'ora in poi indichiamo con $Error({\cal D})$ l'errore della migliore predizione $\mu$ per il dataset $\cal D$.

#### Classification error
Nel caso di classificazione, la miglior predizione $\mu$ è la label più frequente in $\cal D$, inoltre se definiamo con $p_i$ la frequenza della label $l_i\in\cal D$, l'errore totale nel dataset è dato da:
$$Error({\cal D})=1-\max_i p_i$$

>[!Example]
>Supponiamo di avere un dataset $|\mathcal{D}| = 800$, con $400$ istanze nella classe $0$ e altre $400$ nella classe $1$: $\mathcal{D}=(400,400)$.
>-  $Error(\mathcal{D})=1-\frac{1}{2}=0.5$
>- Assumere uno split $B=(f_2,t_2)$ che produce $\mathcal{D}_L=(200,400)$ e $\mathcal{D}_R=(200,000)$
>- $Gain(B|\mathcal{D})=0.5-\frac{600}{800}\cdot(1-\frac{2}{3})-\frac{200}{800}\cdot(1-1)=0.25$
>
>Lo split $B$ è un buono split in quanto produce una foglia **pura** (i.e. un set di istanze con una predizione che non deve essere ulteriormente processata).

#### Information gain (entropy)
L'errore di un dataset può essere misurato come l'**entropia** (i.e. misura di casualità) nella distribuzione delle label:
$$Error(\mathcal{D})=-\sum_i p_i\log_2(p_i)$$
Il gain in questo caso viene indicato come $InfoGain$.

>[!Example]
>Supponiamo di avere un dataset $|\mathcal{D}| = 800$, con $400$ istanze nella classe $0$ e altre $400$ nella classe $1$: $\mathcal{D}=(400,400)$.
>-  $Error(\mathcal{D})=-(\frac{1}{2}\log(\frac{1}{2})+\frac{1}{2}\log(\frac{1}{2}))=\log(2)=1$
>- Assumere uno split $B=(f_2,t_2)$ che produce $\mathcal{D}_L=(200,400)$ e $\mathcal{D}_R=(200,000)$
>- $InfoGain(B|\mathcal{D})=1-\left(\frac{600}{800}\cdot(-(\frac{1}{3}\log(\frac{1}{3})+\frac{2}{3}\log(\frac{2}{3})))+\frac{200}{800}\cdot(-(1\log(1)-0\log(0)))\right)\simeq 0.31$

#### Gain ratio
Per alberi di decisione k-ari l'$InfoGain$ favorisce split con partizioni più piccole, in quanto più propense ad essere pure, il $GainRatio$ normalizza l'information gain con $SplitInfo$:
$$SplitInfo(\mathcal{D}_i)=-\sum_{i=1}^k\frac{|\mathcal{D}_i|}{\mathcal{D}}\log\left(\frac{|\mathcal{D}_i|}{\mathcal{D}}\right)$$
$$Error(\mathcal{D})=GainRatio(\mathcal{D})=\frac{Info(\mathcal{D})}{SplitInfo(\mathcal{D})}$$

#### Gini index
**GINI** è una misura di dispersione statistica, l'errore in questo caso è misurato come:
$$Error(\mathcal{D})=Gini(\mathcal{D})=1-\sum_i p_i^2$$

>[!Example]
>Supponiamo di avere un dataset $|\mathcal{D}| = 800$, con $400$ istanze nella classe $0$ e altre $400$ nella classe $1$: $\mathcal{D}=(400,400)$.
>-  $Error(\mathcal{D})=1-\left((\frac{1}{2})^2+(\frac{1}{2})^2\right)$
>- Assumere uno split $B=(f_2,t_2)$ che produce $\mathcal{D}_L=(200,400)$ e $\mathcal{D}_R=(200,000)$
>- $Gain(B|\mathcal{D}) =  0.5 - \left(\frac{600}{800} \cdot ( 1 - (\frac{1}{3})^2 - (\frac{2}{3})^2) + \frac{200}{800} \cdot (1- (1)^2 - (0)^2)\right) \simeq 0.167$

#### Mean Squared Error (MSE)
Gli alberi decisionali possono essere utilizzati anche per task di **regressione**, l'errore e la predizione migliore però sono definiti diversamente, infatti la predizione migliore $\mu$ dovrebbe essere il valore medio delle label in $\cal D$:
$$\mu=\arg\min MSE(\mu,\mathcal{D})\quad\implies\quad\mu=\frac{1}{|\mathcal{D}|}\sum_{(x,y)\in\mathcal{D}} y$$
$$Error(\mathcal{D})=\frac{1}{|\mathcal{D}|}\sum_{(x,y)\in\mathcal{D}}(\mu-y)^2$$
$$Gain(f,t|\mathcal{D}) = Error({\cal D}) - \frac{|{\cal D}_L|}{|{\cal D}|} Error({\cal D}_L) - \frac{|{\cal D}_R|}{|{\cal D}|} Error({\cal D}_R)$$

---
### Iperparametri per decision tree
Tra i vari [iperparametri degli alberi decisionali](https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeClassifier.html) troviamo anche la **profondità massima** che può raggiungere l'albero, impostare un valore alto classificherà bene i valori noti, tuttavia non sarà tanto efficace su dati mai visti.
![[Decision tree max depth.png]]

Una digressione va fatta per il **numero massimo di foglie** applicato all'algoritmo di Hunt, infatti usare questo iperparametro come criterio di stop non è una buona idea se applicato a tale algoritmo dato che potrebbe venir generato un albero sbilanciato a sinistra a causa della creazione di figli sinistri come prima operazione.

Un algoritmo migliore (iterativo) potrebbe chiedersi se lo split migliore è quello di sinistra o quello di destra prima di creare un nuovo nodo.

---
## Overfitting
L'**overfitting** di un modello può avvenire per varie ragioni, tra cui:
1. **Bassa qualità dei dati**
	- Presenza di "rumore" nel dataset
	- Mancanza di campioni rappresentativi
2. **Modello troppo complesso**
	- Nel caso dei decision tree un modello complesso è dato da un albero _troppo_ profondo

### Validation set
Un modo per ridurre l'overfitting è quello di aggiungere un ulteriore divisione del dataset ed introdurre quindi un **validation set** per simulare ulteriori dati non visti.

La misura di performance sul _validation set_ (i.e. **errore di generalizzazione**) può essere usata per selezionare un modello finale.

Le proporzioni di split del dataset con il _validation set_ sono generalmente le seguenti:
$$60/20/20\quad\text{train/validation/test}$$
Il test set da una stima sull'accuratezza del modello, mentre il validation set viene usato per trovare gli iperparametri migliori del modello.
Solitamente dopo aver trovato la combinazione migliore di iperparametri si riallena il modello utilizzando il training set intero, ovvero $\text{train+validation}$.

### Pruning
A parità di _errore di generalizzazione_ si preferisce il modello più semplice, introduciamo quindi due metodi di pruning:
- **Pre-pruning**: criteri di stop anticipato (e.g. numero di foglie massimo)
- **Post-pruning**: dopo aver fatto crescere un albero, si vanno a rimuovere dei sotto alberi con una foglia

Il _post-pruning_ permette di prendere una decisione analizzando più nodi, infatti un sottoalbero viene sostituito con una foglia che rappresenta la moda/media delle predizioni in quel sottoalbero in base a classificazione/regressione, se l'errore di generalizzazione è minore o uguale a quello previsto precedentemente al pruning.

L'errore di un modello $\cal M$ (i.e. decision tree nel nostro caso) è definito come:
$$Error(\mathcal{D},\mathcal{M})=\frac{1}{|\mathcal{D}|}\sum_{(x,y)\in\mathcal{D}} E(y,\mathcal{M}(x))$$
mentre l'**errore di generalizzazione** può essere stimato tramite:
$$Error_{gen}(\mathcal{D}, \mathcal{M})=Error(\mathcal{D}, \mathcal{M})+\alpha\cdot Complexity(\mathcal{M})$$
>$\alpha$ è un iperparametro scelto a priori utilizzato per aggiustare la complessità del modello.

Un modo per misurare la complessità di un decision tree è il rapporto tra il numero di foglie e la dimensione del dataset $\cal D$:
$$Complexity(\mathcal{M})=\frac{\#\text{leaves in }|\mathcal{M}|}{|\mathcal{D}|}$$