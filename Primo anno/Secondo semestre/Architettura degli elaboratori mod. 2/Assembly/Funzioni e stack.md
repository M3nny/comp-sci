Le funzioni (o subroutine) sono generalizzate per eseguire compiti parametrizzati.
Differenziamo le **procedure** le quali non ritornano un valore a differenza delle funzioni.

Per chiamare una procedura occorre:
1. Salvare il PC corrente
2. Modificare il PC con l'indirizzo della procedura da chiamare
3. Rispristinare il PC salvato sommandogli 4 al termine della procedura.

```armasm
proc:
	// codice procedura
	RET
// ...
BL proc
// ...
```

L'istruzione `BL` salva PC+4 nel link register (x30) e salta a `proc`.
Questo ci fa pensare che si possa usare `BR x30` per tornare al normale flusso di esecuzione; è vero, ma con `RET`:
- Indichiamo in modo esplicito l'uscita dalla procedura/funzione
- Abbiamo più possibilità che il branch predictor effettui la scelta giusta
