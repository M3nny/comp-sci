Le istruzioni logico-aritmetiche, si presentano come segue:
```armasm
<op>{S} Rd, Rn, <op2>, <shift>
```
- <**op**>: istruzione
- **S**(opzionale): esegue l'operazione e imposta i [[Registri#Application Program Status Register (ASPR)|codici di controllo]]
- **Rd**: registro di destinazione
- **Rn**: primo operando
- <**op2**>: Rm (registro) | Rm, <_shift_> _#n_ | Rm, <_shift_> Rs (shift del valore dentro al reg. Rs)
- <**shift**>: LSL | LSR | ASR

e.g.
```armasm
ADDS X0, X1, X0 // X0 = X1 + X0 (set cond. codes)
ADD W0, W0, W0, LSL #2 // W0 = W0 + (W0<<2)
ADD W0, W0, #3 // W0 = W0 + 3
```

### Barrel shifter
La possibilità di shiftare (o ruotare, utile per operazioni di cybersecurity) il secondo operando è una prerogativa di ARM, utile per:
- Moltiplicare e dividere per potenze di 2 prima di effettuare altre operazioni
- Accedere ad elementi di array avendo un registro R1 che punta al suo inizio ed un'altro registro R2 che contiene l'indice da accedere: `addr = R1 + R2 << 2`

- **LSL** (Logical Left Shift) inserisce degli _zeri_ nei bit _meno_ significativi, compromette il risultato se di verifica _overflow_.
- **LSR** (Logical Right Shift) inserisce degli _zeri_ nei bit _più_ significativi, nel caso il numero avesse segno, lo comprometterebbe aggiungendo uno _zero_ davanti.
- **ARS** (Arithmetic Right Shift) inserisce 0 oppure 1 in base al segno.

![[Barrel shifter.svg]]
### Operazioni logico-aritmetiche immediate
La notazione **#n** è usata per indicare valori immediati (decimali), l'operazione ADDI non è presente in ARM (a differenza di MIPS).
Un valore immediato è grande _12 bit_ questo significa che possiamo inserire un numero decimale senza segno da 0 a 4096 mentre con segno da -2046 a 2047.

>[!Info]
>- L'istruzione non è R-type, il compilatore la traduce automaticamente a I-type.
>- XZR non può essere usato come secondo operando
>```armasm
>ADD X0, XZR, #3 // non funziona
>MOV X0, #3 // sposto 3 dentro al registro X0
>```

Per **caricare immediati più grandi** usiamo l'istruzione `MOVZ` la quale permette di caricare un immediato da _16 bit_ (0 - 65535) shiftato di 0, 16, 32 o 48 bit in un registro ponendo tutti gli altri bit a _zero_.
```armasm
MOVZ X9, #255, LSL #16
```

`MOVK` esegue la stessa operazione lasciando inalterati gli altri bit.

Con l'istruzione `MOV` in generale è quindi possibile far muovere un valore da un registro (o valore immediato) ad un altro registro.
- `SXT`: sign extend
- `UXT`: zero extend (aggiunge _zeri_ a sinistra)

È anche possibile **caricare indirizzi nei registri**:
- `ADR Rd, label`: carica nel registro destinazione l'indirizzo di label, il quale deve trovarsi entro $\pm$ 1MB dal PC.
- `ADRP Rd, label`: carica nel registro destinazione l'indice della pagina che contiene l'indirizzo di label, il quale deve trovarsi entro $\pm$ 4GB dal PC.
