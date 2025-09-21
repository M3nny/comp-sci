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

## Passaggio di parametri e valori di ritorno
Usiamo le **Procedure Call Standard (PCS)** per definire dove mettere i parametri ed i valori di ritorno:
1. I <u>parametri sono passati nei registri</u> `x0,...,x7` (o `w0,...,w7` se usa interi a 32 bit), se la funzione usa più di 8 parametri occorre usare lo stack.
2. Il <u>valore di ritorno</u> è passato nel registro `x0`.
3. L'<u>indirizzo della prossima istruzione del chiamante </u> è contenuto nel link register (`x30`).

**Side effects**: una funzione può modificare i valori di registri di cui si vuole invece mantenere il valore.

4. La <u>funzione chiamata può usare i registri</u> `x0,...,x15` senza preoccuparsi di preservare il loro valore.
5. La <u>funzione chiamata deve preservare il valore dei registri</u> `x19,...,x27`, volendo può modificarli, ma alla fine della funzione devono contenere i valori originali.
6. Generalmente i registri `x8,x16-x18` sono <u>riservati</u>, meglio non usarli se non necessario.

## Stack
Lo stack (politica LIFO) viene usato per salvare i registri da preservare, in questo modo anche con una funzione ricorsiva non è necessario sapere quante variabili verranno usate in quanto lo stack crescerà rispettivamente al numero di registri da salvare.

- Lo stack è inizializzato su un'indirizzo "alto" e cresce verso il basso

Idealmente le operazioni di **push** e **pop** corrispondono rispettivamente a:
- Calcolare l'indirizzo dello stack pointer - 16 (cresce verso il basso) e salvare il registro nell'indirizzo calcolato
- Caricare il valore puntato da sp e spostare sp verso su con sp + 16
```armasm
str w0, [sp, #-16]! // push
ldr w0, [sp], #16 // pop
```

>[!attention]
>In AArch64 operiamo nel modo appena descritto in quanto gli accessi in memoria mediante il registro sp devono essere multipli di 16 (allineati a 16 byte).

Al termine dell'esecuzione la funzione deve riportare lo stack pointer al valore che aveva prima che essa venisse invocata (deve rimuovere gli elementi che ha aggiunto), altrimenti si avrebbero memory leak i quali possono portare ad un consumo dello stack prematuro, portando all'eccezione **stack overflow**.

Se una funzione ne chiama un'altra a sua volta, bisogna salvare il link register dato che verrà sovrascritto.