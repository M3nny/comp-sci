## Salti non condizionati
Supportano un offset di $\pm$ 128MB.
- Il registro `x30` è noto anche come **link register** (`lr`) 
| `B label`                             | `BL label`                                                                                              | `RET`                                            | `BR x<m>`                                        | `BLR x<m>`                                                                                                          |
| ------------------------------------- | ------------------------------------------------------------------------------------------------------- | ------------------------------------------------ | ------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------- |
| salta all'indirizzo indicato da label | salta all'indirizzo indicato da label e salva l'indirizzo dell'istruzione successiva nel registro `x30` | salta all'indirizzo contenuto nel registro `x30` | Salta all'indirizzo contenuto nel registro `x<m>` | Salta all'indirizzo contenuto nel registro `x<m>` e salva l'indirizzo dell'istruzione successiva nel registro `x30` |

## Branch condizionati
Il registro (**reg**.) usato per il branch può essere di tipo `w<n>` oppure `x<n>`, inoltre **label** deve trovarsi a $\pm$ 1MB dal PC.
| `CBZ reg, label` | `CBNZ reg, label`|
| -------------------------- | ----------- | 
| Salta a label se reg. = 0  | Salta a label se reg. $\neq$ 0            |       

Esistono branch che saltano sulla base di una condizione `<COND>` e quindi non controllano solo se reg. è uguale o meno a 0.
La condizione si basa anche sul modo in cui stiamo interpretando il numero (signed/unsigned).
Il <u>risultato del branch dipende dai flag del registro APSR</u>.

![[Conditional branch.png]]

Le condizioni sono ottenute tramite l'istruzione `CMP` (eseguita automaticamente) la quale funziona nel seguente modo:
`CMP reg1, reg2` la quale è un _alias_ di `SUBS xzr, reg1, reg2` ovvero esegue la sottrazione impostando i _conditional codes_ e poi butta via il risultato dato che ci interessa solo il valore di `N` e/o `Z` nel registro [[Registri#Application Program Status Register (APSR)|APSR]].
Dopo aver impostato i valori del registro APSR posso eseguire un `B.<COND>` sulla base del suo valore.
```armasm
CMP x20, x11
B.NE label // salto a label se x20 e x11 sono diversi
```

## Conditional select & increment
`CSEL reg1, reg2, reg3, <COND>` equivale a:
```c
if (COND) {
	reg1 = reg2;
} else {
	reg1 = reg3;
}
```

`CINC reg1, reg2, reg3, <COND>` equivale a:
```c
if (COND) {
	reg1 = reg2 + 1;
} else {
	reg1 = reg3;
}
```

In generale queste due istruzioni sono più efficienti dei branch e andrebbero usate sempre se possibile, in quanto:
- Richiedono meno istruzioni
- Non influenzano il PC