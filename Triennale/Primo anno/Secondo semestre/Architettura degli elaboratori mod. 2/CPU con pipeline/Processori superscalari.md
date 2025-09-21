Per aumentare il livello di di ILP (Instruction level parallelism) possiamo:
- Aumentare la profondità della pipeline.
- Replicare componenti così da far entrare più istruzioni alla volta nella pipeline ed ottenere un CPI < 1, questo metodo è chiamato **multiple issue**.

#### Multiple issue
Nell'approccio **statico** è il compilatore a raggruppare le istruzioni in _issue packet_ da inserire contemporaneamente nella pipeline (evitando _hazard_ tra istruzioni).
Questo pacchetto di istruzioni è noto anche come **VLIW** (Very Long Instruction Word) il quale è un'istruzione complessa formata da sotto-operazioni.

| **Vantaggi**                                                       | **Svantaggi**                                                   |
| ------------------------------------------------------------------ | --------------------------------------------------------------- |
| Ottimizzazioni sofisticate                                         | Non tutti gli stalli sono predicibili a compile time            |
| Branch prediction non più implementato nella CPU                   | Non può speculare in modo efficace sull'outcome dei branch      |
| L'ottimizzazione effettuata dal compilatore ha un costo una tantum | Il codice prodotto dipende sia dall'ISA sia dalla specifica CPU |
 
Nell'approccio **dinamico** la CPU decide ad ogni ciclo di clock quante istruzioni immettere nella pipeline ad ogni ciclo di clock, si parla quindi di **CPU superscalari**.
 Esistono due tipi di invio:
 1. **In-order**: la CPU decide solo quante istruzioni indipendenti sequenziali, sono inviate in ogni ciclo di clock.
 2. **Out-of-order**: la CPU può cambiare l’ordine delle istruzioni prima di raggrupparle.

Con lo scheduling dinamico le uniche dipendenze che creano blocchi sono quelle RAW, mentre quelle WAW e WAR possono essere risolte eseguendo le operazioni in parallelo, avendo cura di scrivere i risultati in ordine (in-order commit).