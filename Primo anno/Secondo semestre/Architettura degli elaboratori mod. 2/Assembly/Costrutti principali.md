## Branches
### If-else
Non avendo un **if** vero e proprio, bisogna eseguire un salto alla label **else** se la condizione è _falsa_, altrimenti continuare l'esecuzione (then) fino al salto che ci farà superare l'else.

```
B.<!cond> else-label
	// then
	B exit-label
else-label:
	// else
exit-label:
```

### Do-while
Si ignora la label inizialmente, poi alla fine del ciclo si ritorna alla label di inizio se necessario.

```
init-do:
	// ...
	B.<cond> init-do
```

### While
Abbiamo due condizioni: quella che ci fa uscire dal ciclo e quella ci fa restare dentro.
La prima se è vero l'opposto di quello che vogliamo non ci fa entrare nel ciclo, la seconda (dopo aver eseguito almeno una volta il corpo del ciclo) ci fa ritornare all'inizio del corpo del ciclo.

```
B.<!cond> exit-while
init-while:
	// ...
	B.<cond> init-while
exit-while:
```

### For
Definito come `for(<init>; <cond>; <incr>) {...}` possiamo esprimerlo come un while dove:
- **init**: è un'assegnazione che avviene sempre, vero o falso che sia la condizione iniziale
- **cond**: inizialmente deve essere negata così da saltare il ciclo se è vero quello che non vogliamo, poi dovrà essere espressa normalmente in quanto se è vero quello che vogliamo dovrà ripetere il corpo del ciclo
- **incr**: affettua l'incremento della "variabile" prima di ri-eseguire il corpo del ciclo

```
<init>
B.<!cond> exit-for
init-for:
	// ...
	<incr>
	B.<cond> init-for
exit-for:
```

## Array
Gli array sono un modo compatto per dichiarare $n$ variabili dello stesso tipo.
L'indirizzo in memoria di `A[x]` è `&A[0] + sizeof(int)*x`.
Quindi se `x0` contiene l'indirizzo di `A[0]` e `x1` contiene l'indice dell'array, possiamo ottenere `x3 = &(A[x1])` nel seguente modo:
```armasm
add x3, x0, x1, LSL #2 // moltiplico per 4 (grandezza int)
```

Per offset piccoli noti in fase di compilazione è possibile usare [[Load&Store#Addressing modes|l'addressing mode offset]]
```armasm
ldr w4, [x0, #12] // x4 = A[3]
```

## Stringhe
Finora abbiamo agito solo con `words` o `dwords` (4 - 8 byte), però si sono istruzioni come:
- `strb w0, <addr>` memorizza il byte meno significativo di `w0` all'indirizzo `<addr>`
- `ldrb w0, <addr>`carica il byte all'indirizzo `<addr>` nel byte meno significativo di `w0` e imposta il resto a 0

Queste istruzioni tornano utili per manipolare **stringhe** codificate con lo standard **ASCII** dove ogni byte rappresenta un carattere, ed il carattere finale è uno 0 (come in C).
Vediamo due modi per caricare una stringa in memoria:

```armasm
.byte 67, 73, 65, 79, 0 // carico i decimali ASCII
.asciz <<ciao>> // carico la parola direttamente
```

<u>Esistono però molti più caratteri nella realtà di quelli rappresentabili dalla tabella ASCII</u> (come le lingue asiatiche ed europee).
Per questo <u>nascono altri ISO appositi per rappresentarle</u>, ma in base al dispositivo in cui queste codifiche vengono visualizzate, potrebbero avere delle variazioni rendendo incompatibile ad esempio un testo scritto su MacOs e uno su Windows.

Nasce quindi l'**unicode** che contiene ogni possibile simbolo, usando pochi byte per i caratteri frequenti e più byte per quelli meno frequenti (multi-byte character encoding), lo standard più comune è l'**utf-8**:
- **Primi 128** caratteri usano 1 byte (un testo ASCII è un testo UTF-8 valido)
- **Successivi 1920** caratteri usano 2 byte (latino, greco...)
- **Restanti caratteri** 3 byte (lingue asiatiche)
- **Emoji, simboli matematici...**  4 byte