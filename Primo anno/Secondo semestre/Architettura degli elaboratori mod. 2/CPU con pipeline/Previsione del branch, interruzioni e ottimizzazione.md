## Previsione del branch
Una prima soluzione potrebbe essere quella di assumere sempre **not taken** il branch, in questo modo se almeno la metà dei casi è _not taken_ gli stalli vengono dimezzati, il problema è che non funzione con pipeline profonde in quanto il **branch penalty** (n° di istruzioni da annullare) sarebbe molto significativo.

Con la **previsione dinamica** creiamo una _history table_ su cui tenere traccia gli esiti dei branch passati.
Possiamo quindi creare un automa **predittore** il quale (sulla base degli stati precedenti) esegue o meno il branch.

![[Predittore branch.svg]]
Per quanto buona possa essere una predizione comunque verrano commessi degli errori, per cui occorre l'**hazard detection unit** nello stadio ID la quale inserirà delle _nop_ nel caso ci fossero istruzioni da annullare già entrate nella pipeline.

---
## Eccezioni ed interruzioni
Il flusso delle istruzioni può cambiare anche a causa di:
- **Eccezioni**: causa del programma
- **Interruzioni**: causa esterna (I/O)

#### Gestione delle eccezioni
In caso di eccezione la CPU deve:
1. **Interrompere** l'esecuzione del programma corrente
2. **Salvare** lo stato di esecuzione del programma corrente nel EPC (Exception Program Counter)
3. **Trasferire** il controllo all'OS tramite un _salto_, quando l'OS avrà gestito il problema l'esecuzione potrà eventualmente riprendere.

Esistono due approcci per capire che tipo di eccezione si è verificata:
- **Registro speciale** (CAUSE in MIPS) che contiene un codice numerico corrispondente al tipo di eccezione (singolo entry point)
- **Vectorized interrupts**: l'indirizzo in cui si salta in caso di eccezione dipende da quest'ultima (multipli entry points)

Su MIPS la gestione delle eccezioni avviene nel seguente modo:
1. Individuare l'evento inatteso ed interromperlo
2. Salvare il PC nel EPC e la causa dell'eccezione nel registro CAUSE
3. Saltare ad una routine dell'OS che si trova all'indirizzo fisso 0xC0000000

>[!quote]
Mentre MIPS ha un approccio _minimale_ e salva solo il PC, lasciando all'OS il compito di salvare altro se necessario, altre CPU CISC eseguono un salvataggio _esteso_ di tutto lo stato prima di passare all'interrupt handler.
>
>(Su architetture CISC come x86, si parla solo di interrupt non eccezioni)

#### Eccezioni con Pipeline
A differenza dei branch i quali hanno _l'hazard detection unit_ nello stadio ID, le eccezioni aritmetiche vengono rilevate allo stadio EXE, dobbiamo quindi modificare il controllo della CPU nello stadio EXE in modo tale che possa inserire delle nop.

Un'altro problema è quello di eccezioni multiple in un ciclo di clock, risolvibile tramite un sistema di priorità delle istruzioni.

## Ottimizzazione del codice
1. Individuare le dipendenze **RAW**
2. Individuare le dipendenze **WAR**
3. In caso di branch, cercare di **non lasciare il delay slot vuoto**, sapendo che l'istruzione dopo un branch viene sempre eseguita, bisogna spostare un'istruzione da dentro il ciclo a subito dopo il ciclo senza alterare la semantica del programma, e quindi senza invertire la direzione delle dipendenze.
4. **Evidenziare in modo esplicito gli stalli** con delle nop
5. Sempre considerando la direzione delle dipendenze e semantica del programma, cercare di **spostare qualche istruzione al posto delle nop**

![[Ottimizzazione codice.svg]]
