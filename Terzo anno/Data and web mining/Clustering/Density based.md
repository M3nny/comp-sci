Il **clustering basato sulla densità** affronta il problema degli outliers e dei punti di rumore.

Questo tipo di clustering si basa su **criteri di cluster locali**, le caratteristiche principali sono:
- La possibilità di scoprire cluster di qualsiasi forma
- Gestione del rumore
- Un solo scan
- Necessità di parametri di densità e condizioni di terminazione

## DBSCAN
L'idea dietro al **Density-Based Spatial Clustering of applications with Noise (DBSCAN)**  è quella di:
- Identificare oggetti in regioni dense
- Unire le regioni dense vicine in un cluster
- Scartare gli oggetti in regioni sparse (punti di rumore)

**Quando è che un punto è considerato all'interno di una regione densa?**
Un oggetto $p$ nel dataset $\cal D$ è detto **core point** se esistono almeno $MinPts$ punti entro un certa distanza $\epsilon$, formalmente definiamo il **neighborhood** di $p$ come:
$$N_\epsilon(p)=\{q\in D | dist(p,q)\leq\epsilon\}$$
un oggetto $p$ è quindi un _core point_ se $|N_\epsilon(p)|\geq MinPts$.
![[Core point.png]]

**Quali punti dovrebbero appartenere allo stesso cluster di $p$?**
Un punto $q$ è detto **direttamente densamente-raggiungibile** da $p$ se:
- $p$ è un _core point_
- $q\in N_\epsilon(p)$

Sfruttando il concetto di transitività, possiamo dire che un punto $q$ è detto **densamente-raggiungibile** da $p$ se esiste una catena di punti $p_1,...,p_n$ con $p_1=p$ e $p_n=q$ tali che $p_{i+1}$ è **direttamente densamente-raggiungibile** da $p_i$.
![[Density-reachable.png]]

Notare come la **raggiungibilità di densità** non sia simmetrica, ciò potrebbe causare situazioni in cui alcuni punti sono raggiungibili da $o$, ma non direttamente raggiungibili tra loro.

Diciamo che un punto $s$ è **densamente-connesso** a $r$ se esiste un punto $o$ tale che $s$ è **densamente-raggiungibile** da $o$, e $r$ è **densamente-raggiungibile** da $o$.
![[Density-connected.png]]


I punti definiti come **densamente-connessi formano i cluster**, gli altri vengono scartati.
![[Clustering comparison.png]]

**Algoritmo**
1. Crea un insieme vuoto di cluster $C$ e marca tutti i punti come non visitati e non rumorosi
2. Per ogni punto $p$:
	- Se non è già stato visitato, viene marcato come visitato
		- Se $|N_\epsilon(p)| < MinPts$ marca $p$ come punto rumoroso
		3. Altrimenti comincia la creazione di un nuovo cluster a partire da $p$
			- Usa una coda $Q$ per visitare i punti vicini $N_\epsilon$
			- Aggiunge core point che soddisfano $|N_\epsilon|\geq MinPts$ al cluster e alla coda
			- Aggiunge al cluster anche i punti densamente-connessi rimuovendo l'etichetta di rumore se necessario
		4. Quando non ci sono più punti da visitare nel vicinato aggiungi il cluster locale all'insieme $C$

#### Recap sugli algoritmi di clustering

|               | K-means                                                                                                            | Gerarchico                                                              | Density based                                                                                        |
| ------------- | ------------------------------------------------------------------------------------------------------------------ | ----------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------- |
| **Vantaggi**  | Veloce.<br>                                                                                                        | Fornisce differenti misure per configurazioni di clustering diverse<br> | Gestisce i punti di rumore esplicitamente.<br><br>Gestisce cluster di dimensione e forma arbitraria. |
| **Svantaggi** | Sensibile agli outliers.<br><br>Assume cluster globulari.<br><br>Funziona meglio con cluster di dimensioni simili. | Lento.<br><br>Sensibile agli outlier e punti di rumore.                 | È difficile trovare gli iperparametri corretti.                                                      |

## Valutazione dei cluster
La valutazione dei cluster ci consente di stabilire la bontà dei cluster generati.

### Valutazione intrinseca
Normalmente non abbiamo alcuna verità fondata o etichetta per i dati, per cui ci concentriamo sull'analisi interna al processo di clustering.

Un cluster è considerato buono se gli <u>oggetti dello stesso cluster sono vicini</u> ed <u>il cluster più vicino è distante</u>.

Per ogni oggetto $o_i$ all'interno del cluster $C_h$ definiamo le seguenti misure.
**Similarità intra-classe** (vogliamo che sia piccola):
$$a(o_i)=\frac{\sum\limits_{a_j\in C_h,i\neq j}dist(o_i,o_j)}{|C_h|-1}$$

**Similarità inter-classe** (vogliamo che sia grande) viene calcolato questo valore considerando tutti i $k$ cluster e ritornando il valore minimo trovato:
$$b(o_i)=\min\limits_{C_k\neq C_h}\left\{\frac{\sum\limits_{a_j\in C_k}dist(o_i,o_j)}{|C_k|}\right\}$$

Combiniamo queste due similarità per ottenere il **coefficiente silhouette**, esso è definito per $o_i$ come:
$$s(o_i)=\frac{b(o_i)-a(o_i)}{\max\{a(o_i),b(o_i)\}}$$

il suo valore è compreso tra $-1$ e $1$, più alto è il valore, migliore è il cluster.

Uno **score di qualità** dei cluster è dato dalla media dei coefficienti di silhouette di ogni oggetto.

### Valutazione estrinseca
Questo tipo di valutazione si basa su verità fondate le quali possono derivare da etichettature preesistenti, dataset piccoli o dati sintetici.

Essendo nel caso ideale definiamo:
- $C(o_i)$: id del cluster fornito dall'algoritmo di clustering per l'oggetto $o_i$
- $L(o_i)$: cluster reale dell'oggetto $o_i$

Possiamo costruire la seguente tabella di contingenza.

|                   | Stesso cluster                                                                    | Cluster diverso                                                                      |
| ----------------- | --------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| **Stessa label**  | **True Positives**<br>$TP=\|\{o_i,o_j\|C(o_i)=C(o_j)\land L(o_i)=L(o_j)\}\|$      | **False Negatives**<br>$FN=\|\{o_i,o_j\|C(o_i)\neq C(o_j)\land L(o_i)=L(o_j)\}\|$    |
| **Label diversa** | **False Positives**<br>$FP=\|\{o_i,o_j\|C(o_i)=C(o_j)\land L(o_i)\neq L(o_j)\}\|$ | **True Negatives**<br>$TN=\|\{o_i,o_j\|C(o_i)\neq C(o_j)\land L(o_i)\neq L(o_j)\}\|$ |

Sulla base della tabella di contingenza precedente vengono solitamente usate due statistiche:
$$\text{Rand Statistic}=\frac{TP+TN}{TP+FP+TN+FN}$$
$$\text{Jaccard Coefficient}=\frac{TP}{TP+FP+FN}$$

- **Rand statistics**: misura il numero di coppie per le quali è stato assegnato un cluster corretto
- **Jaccard coefficient**: non tiene conto dei True Negatives (TN)

