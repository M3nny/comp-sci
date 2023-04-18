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
