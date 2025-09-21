Al giorno d'oggi nessuna CPU è implementata a **ciclo singolo**, questo perchè il periodo di un ciclo di clock dovrebbe essere tanto lungo quanto l'istruzione più lunga nella CPU e considerando le operazioni floating point che che richiedono _molto_ più tempo di una operazione come magari una beq quest'ultima CPU non è ottimale.

#### Suddivisione del datapath ([[CPU multiciclo#Sequenza passi (cicli) esecuzione|reference]])
1. Instruction Fetch (**IF**)
2. Instruction Decode & register file read (**ID**)
3. Execute (**EX**)
4. Accesso memoria (**MEM**)
5. Write Back (**WB**)

L'idea della **pipeline** sta nell'eseguire tutti i 5 passi della [[CPU multiciclo]] simultaneamente.

Da notare che ogni istruzione ci metterà sempre il solito tempo, solo che eseguendole contemporaneamente si avrà un **throughput maggiore** (n° di istruzioni completate in un certo lasso di tempo).

Con questo il **CPI** (Cicli Per Istruzione) si abbassa, esso sarà determinato dallo stadio più lento.

Il **tempo di esecuzione di ogni stadio** ($T_s$) è dato dal rapporto tra il **tempo di esecuzione sequenziale di ogni istruzione** ($T_{seq}$) ed il **numero di stadi** ($n$).
$$T_s=\frac{T_{seq}}{n}$$

Ogni stadio della pipeline completa la sua esecuzione in un tempo $T'$ quando è piena, viene considerata piena quando $n-1$ stadi sono pieni.
$T'$ è dato dal rapporto tra il periodo di clock della CPU a ciclo singolo ($T$) ed il numero di stadi ($n$).

$$T'=\frac{T}{n}$$
Possiamo calcolare lo **speedup** tramite:
$$\text{speedup} = \frac{n\cdot IC}{(n-1)+IC}$$ da notare che quando $IC$ è molto grande ($IC\to +\infty$) lo _speedup_ tende (ma non sarà mai) al numero di stadi della pipeline.
Ovvero più lunga la pipeline, migliore lo speedup.

Ci possono essere **dipendenze** tra le istruzioni che possono causare degli **stalli** per cui anche questo è un motivo che non permette allo speedup di essere uguale al numero di stadi.

_fine introduzione_.