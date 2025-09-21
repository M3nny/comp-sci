**Sintassi generale:**
Load reg <- MEM:
`LDR<S><size> reg, [<addr>]`

Store reg -> MEM:
`STR<S><size> reg, [<addr>]`

## Size
- **Sign (S)** indica se stiamo caricando/leggendo un valore _signed_.
- **Size** può essere implicita allora si caricherà/leggerà la grandezza del registro (w/r -> 32/64 bit) altrimenti in base ad esso andremo a memorizzare solo alcuni byte.

| `LDR reg [<addr>]`  | `STRB reg [<addr>]`                                           | `STRH reg [<addr>]`                                            | `STRW reg [<addr>]` |
| ------------------- | ------------------------------------------------------------- | -------------------------------------------------------------- | ------------------- |
| Memorizza 32/64 bit | Memorizza **il byte** meno significativo di `reg` dentro `<addr>` | Memorizza i **2 byte** meno significativi di `reg` dentro `<addr>` | Memorizza i **4 byte** meno significativi di `reg` dentro `<addr>`                    |

Con le **load** le istruzioni funzionano analogamente, ma quando andiamo a caricare in un registro solo alcuni byte estendiamo il valore caricato con:
- **Zeri** (_zero-extend_) se trattiamo il valore come <u>unsigned</u>.
- Il suo **segno** (_sign-extend_) se trattiamo il valore come <u>signed</u>.

## Addressing modes
Vediamo cosa mettere nel campo `[<addr>]`.

Abbiamo 4 modi di indirizzamento:
- **Base register**: l'indirizzo da usare è contenuto dentro a `reg2`.
	`LDR reg1, [reg2]`
- **Offset**: l'indirizzo da usare è ottenuto sommando un immediato al valore dentro un registro (`LDR` prende l'alias di `LDUR` (load unscaled-offset register).
	`LDR reg1, [reg2, #3]`
- **Pre-indexed (++c)**: l'indirizzo da usare è ottenuto dall'operazione di _offset_, ma esso viene calcolato prima di accedere alla memoria e viene scritto nel registro contenete l'indirizzo, dopo questa operazione quindi troveremo `reg2` cambiato.
	`LDR reg1, [reg2, #3]!`
- **Post-indexed (c++)**: l'indirizzo da usare è contenuto dentro a `reg2`, dopo l'accesso alla memoria l'_offset_ è aggiunto a `reg2`.
	`LDR reg1, [reg2], #3`

---
## Altre istruzioni
- `SVC #0`: supervisor call, la CPU passa il controllo al kernel, il valore immediato indica il servizio richiesto.
- `FMOV reg1, reg2`: copia bit-a-bit valori da un registro FP ad un registro intero o FP.
- `FCVTNS reg1, reg2`: copia arrotondando all'intero più vicino da un registro FP ad un registro intero o FP
