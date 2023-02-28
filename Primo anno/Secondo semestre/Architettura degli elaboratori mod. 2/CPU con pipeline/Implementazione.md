Introduciamo dei **registri intermedi** tra gli stadi in quanto non possiamo eseguire tutte le istruzioni in parallelo dato che necessitano dei valori calcolati nei cicli di clock precedenti.
Così facendo _le istruzioni passano da un registro intermedio al successivo fino al loro completamento_.

Dobbiamo considerare però il **problema delle dipendenze** tra istruzioni.
(e.g. con una lw quando eseguo il write-back è possibile che su write register ci sia il contenuto di una istruzione successiva che ha appena fatto IF/ID).

## Controllo
- **IF e ID devono essere sempre eseguiti** ad ogni ciclo di clock (non dipendono da altre istruzioni).
- **ID calcola i segnali di controllo anche per gli stadi successivi**, quest'ultimi _devono essere propagati_ in avanti assieme all'istruzione stessa ed il valore del PC.

![[Controllo pipeline.png|500]]

## Criticità (Hazard)
Quando una istruzione dipende dal risultato di una istruzione precedente si parla di **hazard**.
Quando si verifica questa situazione avviene uno **stallo** il quale implica che lo stadio che ha scoperto la criticità riesegua la stessa istruzione.
- Vengono introdotte delle **nop** (bolle d'aria) alle unità seguenti della pipeline, in questo modo si aspetta finchè la criticità non è risolta.

Parliamo invece di **structural hazards** quando una istruzione ha bisogno di una risorsa ancora occupata da una istruzione precedente.
La CPU MIPS è stata progettata per non avere questo tipo di problema, ma vediamo cosa succederebbe se usassimo una sola memoria per istruzioni e dati.

>[!Attention]
>Prestare attenzione alle richieste della consegna,
>il **register file ottimizzato** consente di leggere e scrivere un registro nello stesso ciclo di clock, in questo modo alcune dipendenze possono essere risolte prima.

### Data hazards
Sono criticità dovute a dati che vengono letti e scritti dalle istruzioni, la dipendenza sui dati tra coppie di istruzioni implica quindi un ordine di esecuzione non modificabile.

Ci sono 3 tipi di dipendenze sui dati:
- **RAW (Read After Write)**: 
Avviene quando _un'istruzione legge un registro scritto da una istruzione precedente_.
```armasm
add $s0, $t0, $t1 // write $s0
add $t2, $s0, $t3 // read $s0
```

![[Dipendenza RAW.png|500]]

- **WAW (Write After Write)**:
Avviene quando _un'istruzione scrive un registro da una istruzione precedente_.
```armasm
add $s1, $t0, $t1 // write $s1
sub $s1, $s2, $t3 // write $s1
```

- **WAR (Write After Read)**:
Avviene quando _un'istruzione scrive un registro letto da una istruzione precedente_.
```armasm
add $t0, $s1, $t1 // read $s1
sub $s1, $s2, $t3 // write $s1
```

Per quanto riguarda la _Read After Read_, non ci poniamo problemi in quanto legge e basta quindi non è una criticità.

>[!Tip]
>Le dipendenze WAW e WAR sono importanti solo se la CPU può eseguire le istruzioni out-of-order, ma nel nostro caso ci dobbiamo preoccupare solo delle dipendenze RAW dato che:
>- La lettura di un registro avviene allo stage 2 (ID)
>- La scrittura avviene allo stage 5 (WB)

L'**hazard detection unit** che esegue questi controlli è contenuta nello stadio ID, essa confronta i registri dell'istruzione corrente con quelli usati nelle istruzioni precedenti.
==Se viene rilevata una dipendenza, l'ID propaga delle nop agli stadi successivi mentre IF e ID continuano ad eseguire la stessa operazione.==

### Risolvere le dipendenze via software
È possibile risolvere le dipendenze senza implementare una _hazard detection unit_ questo comporta però l'inserimento manuale delle _nop_ e quindi in stalli espliciti da parte del programmatore/compialtore.