Le dipendenze RAW sono molto frequenti nel nostro tipo di CPU, anche usando un buon compilatore per diminuire il numero di nop avremmo comunque perdita di prestazioni.

Vediamo ora vari problemi che si possono verificare e come risolverli:

## Forwarding
Si nota che **non serve aspettare che l'istruzione precedente venga completata**, in quanto il valore nella maggior parte delle volte è già disponibile a partire dallo step EXE, viene poi portato avanti fino alla fine dell'istruzione:
- EX/MEM $\to$ MEM/WB

![[Forwarding.png]]

**Non è possibile eseguire il forwarding da una lw** in quanto produce il valore da memorizzare durante lo stadio MEM non EXE, le istruzioni _R-type_ ed i _branch_ seguenti che dipendono dal valore salvato dalla _lw_ hanno bisogno del valore corretto durante il loro stadio EXE, per cui **lo stallo è inevitabile** bisogna aggiungere delle _nop_.


### Control hazards
Quando si presenta una istruzione di branch, non possiamo eseguire l'istruzione successiva in parallelo in quanto l'esito del branch è sconosciuto.

e.g.   
```armasm
beq $1, $2, 40
or $7, $8, $9
```

Possibili soluzioni:
- **Inserire 3 _nop_ dopo ogni istruzione branch**.
- **Assumere sempre not taken il branch**: in questo modo le 3 istruzioni successive sono già entrate nella pipeline, nel caso fosse taken le istruzioni già entrate nella pipeline non hanno comunque il tempo necessario per apportare modifiche a registri/memoria, quindi bisogna sostituirle con delle nop prima che arrivino allo stage MEM o WB (similmente alla prima soluzione abbiamo perso 3 cicli di clock)
- **Anticipare il calcolo del PC con hardware nuovo**: invece di usare l'ALU per il confronto possiamo usare una nuova unità hardware (veloce) formata da 2 XOR $\to$ 1 OR. Possiamo quindi eseguire il confronto nello stage ID (durante la lettura dei registri) in questo modo anche se fosse taken, ci sarà solo un'altra istruzione entrata nella pipeline (da annullare).

Questa ultima soluzione è chiamata anche **delayed branch**, ed è questo il motivo per cui l'istruzione dopo il branch viene sempre eseguita (che entra nel delay slot lungo 1 su MIPS).
**Sarà il compilatore a decidere come annullare l'istruzione** dopo il branch nel caso taken.

### Problema con il forwarding
Confrontando i registri nello stage ID implica che il loro valore deve essere corretto a partire dal secondo ciclo.
Dobbiamo quindi aggiungere:
- 1 _nop_ dopo una _R-type_ (produce il risultato alla fine di EXE)
- 2 _nop_ dopo una _lw_ (produce il risultato alla fine di MEM)

![[Forwarding problem.svg]]

## Recap
| **Tipo** | **Calcola**                        | **Al ciclo n°** | **Ha bisogno di**                       |
| -------- | ---------------------------------- | --------------- | --------------------------------------- |
| _Branch_ | dato da scrivere nel PC            | 2 (ID)               | input corretti al comparatore           |
| _R-type_ | dato da scrivere nel register file | 3 (EXE)             | input corretti nell'ALU                 |
|          |                                    |                 |                                         |
| _sw_     | indirizzo                          | 3 (EXE)               | input corretto nell'ALU                 |
| _sw_     | dato da scrivere in memoria        | 4 (MEM)               | input corretto da memorizzare           |
|          |                                    |                 |                                         |
| _lw_     | indirizzo                          | 3 (EXE)              | input corretto nell'ALU                 |
| _lw_     | dato da scrivere nel register file | 4 (MEM)               | input corretto in ingresso alla memoria |
