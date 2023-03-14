>[!Quote]
>- Le memorie **lente** sono **grandi** ed **economiche**
>- Le memorie **veloci** sono **piccole** e **costose**

- **SRAM** (Static Random Access Memory): 
sono le memorie più veloci e non richiedono il refresh, però occupano un'area relativamente grande e consumano molta energia
- **DRAM** (Dynamic Random Access Memory): 
occupano un'area piccola e consumano meno energia, però sono più lente delle SRAM e necessitano di refresh (per questo sono dynamic).
Esistono due tipi di DRAM, le SDRAM (Syncrhonized DRAM) che usano il clock sincronizzato con la CPU e le DDR SDRAM (Double Data Rate SDRAM) che possono trasferire sia sul fronte di salita che di discesa del clock, raddoppiando la banda.

- **Memorie flash**: 
usate nelle SSD le quali usano i floating-gate transistors, non richiedono refresh e sono più lente delle memorie precedenti, però mantengono i dati memorizzati anche se non alimentate.
Un problema di queste memoria NAND è che si usurano nel tempo, quindi viene implementato il **wear leveling** che distribuisce le scritture in modo uniforme su tutta la memoria.

- **Hard disk**:
sono molto lenti ma estremamente capienti ed economici.

### Gerarchie di memoria
Usiamo tutti i tipi di memoria secondo una gerarchia.
Partendo dalla CPU avremmo memorie veloci perchè usate più spesso, mentre più ci allontaniamo da essa avremo memoria sempre più lente perchè meno usate.

### Principio di località
Un programma non accede a tutto il suo codice (o ai dati) con la stessa probabilità.

- **Località temporale**: quando si accede ad un certo dato, è probabile che verrà usato di nuovo entro breve (e.g. cicli).
- **Località spaziale**: quando si accede ad un certo dato, è probabile che verranno usati anche altri dati che hanno un indirizzo vicino a quello corrente (e.g. accessi sequenziali ad un array).

### Gerarchie di memoria
Può essere composta da più livelli, i dati sono sempre copiati tra due livelli adiacenti.
Indichiamo con **blocco** l'unità di informazione minima, quando la CPU richiede dei dati possiamo avere:
- **hit**: per indicare che il dato è stato trovato.
- **miss** per indicare che il dato non è stato trovato.

### Hit & miss

Indichiamo con **hit rate** la frazione di accessi alla memoria in cui ottengo un _hit_:
$$\frac{n_{hit}}{n_{accessi}}$$
mentre con **miss rate** indichiamo la frazione di accessi alla memoria in cui ottengo un _miss_:
$$\frac{n_{miss}}{n_{accessi}}$$
possiamo anche trovare il _miss rate_ tramite $1-\text{hit rate}$.

- **Hit time**: è il tempo di accesso al livello superiore della gerarchia (comprende anche l'overhead per stabilire se il tentativo porterà ad un hit o ad un miss).
- **Miss penalty**: è il tempo necessario a sostituire un blocco a livello superiore con un blocco preso a livello inferiore e passare i dati alla CPU.