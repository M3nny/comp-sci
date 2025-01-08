Una buona norma per **evitare l'overfitting** in una rete neurale è controllare se il numero di parametri sia minore del numero di istanze di training, tuttavia questo limita l'espressività del modello, per cui vedremo di seguito delle tecniche per ridurre l'overfitting pur mantenendo un numero elevato di parametri.

L'utilizzo del **validation set è obbligatorio** per controllare se una rete neurale è in overfitting.
![[NN overfitting.png]]

Nei grafici sopra è possibile notare come il modello continui a migliorare nel training set, ma diventa peggiore nel validation set, ciò può essere causato da diversi motivi:
- Il modello è **troppo complesso** e non ci sono abbastanza dati per eseguire un fine-tuning dei parametri
- Il validation set è **troppo diverso** dal training set

### Data augmentation
Se non è possibile semplificare il modello, sarà necessario **aumentare i dati**, in certi domini possiamo generare **dati sintetici** a partire da dati pre-esistenti (e.g. ruotare, alterare immagini), questo processo è chiamato **data augmentation**.
![[NN data augmentation.png]]
>Stesso modello allenato su ulteriori dati sintetici.

### Dropout
Nel caso in cui il processo di _data augmentation_ non fosse abbastanza, si utilizza il **dropout**, il quale rappresenta una **matrice binaria** la quale viene moltiplicata elemento per elemento con l'output del layer, in questo modo i neuroni moltiplicati per $0$ vengono "momentaneamente disabilitati" <u>non contribuendo nè al forward pass nè alla backpropagation</u>.
>È possibile specificare una probabilità di annullamento di un output.

In questo modo il modello non dipenderà troppo da specifici neuroni, in quanto essi impareranno indipendentemente dagli altri, migliorando di conseguenza la capacità di **generalizzazione** della rete neurale.
![[NN dropout.png]]
>Stesso modello allenato utilizzando anche il dropout.

---
### Transfer learning
Non sempre è necessario allenare una rete neurale da zero, molto spesso ne esistono di già allenate per task specifici, le quali possono subire un processo di fine-tuning per essere adattate a nuovi task, ciò è definito **transfer learning**.

---
### Deep learning workflow
1. **Selezionare una misura di qualità**, può usare un obiettivo personale oppure una formulazione matematica
2. **Utilizzare sempre un validation set**, e se necessario un ulteriore development set
3. **Preparare i dati** in modo che abbiano una forma del tipo $\text{osservazioni}\times\text{features}$, trasformare le features categoriche, riempire i valori mancanti e utilizzare il tipo `float`
4. Trovare una **baseline banale** (e.g. predire la classe più numerosa)
5. Trovare una **baseline migliore** (e.g. regressione lineare)
6. **Definire la rete neurale**, ovvero bisognerà trovare la _funzione di perdita_ che più si addice al problema, impostare le _funzioni di attivazione_ e configurare l'_ottimizzatore_
7. **Eseguire l'overfitting della rete neurale**, ovvero aggiungere layer, neuroni e aumentare le epoche, in questo modo avremo un buono score nel training set
8. **Risolvere l'overfitting**, ora che la rete è abbastanza potente possiamo aggiungere il dropout, dati sintetici e semplificare la rete il più possibile
9. Se necessario **iterare dal punto 7**, se il validation set viene utilizzato molteplici volte per trovare i migliori iperparametri, con buona probabilità è possibile che si stia eseguendo un overfitting del validation set, in questo caso è utile considerare l'utilizzo di un ulteriore **development set**
10. **Prendere la versione migliore del modello** e ri-addestrarlo su tutti i dati a disposizione

