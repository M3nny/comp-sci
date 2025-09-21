## Valgrind
**Definitely lost**: nessun puntatore che punta ad un'area di memoria allocata.
**Indirectly lost**: non è possibile accedere ad un'area di memoria.

`int** a -> indirizzo memoria -> altro indirizzo`:
Alla fine del programma viene svuotato lo stack, si perde `int** a`, quindi `indirizzo di memoria` è **definitely lost**, `altro indirizzo` è **indirectly lost**.

Per ogni **new** ci deve essere una **delete** (come malloc e free in C).
Quando uso la new implicitamente (e.g. vector) non devo usare una delete, in quanto verrà chiamato il distruttore automaticamente di quell'oggetto appena va fuori scope.

Opzioni utili per valgrind:
- `valgrind --leak-check=full --track-origins=yes ./hello`
	nell'error summary ci devono essere solo 0.

- ```valgrind --tool=callgrind --cache-sim=yes ./hello```
	per vedere i cache miss.

---
#### Sanitizers
A differenza di valgrind che simula una CPU, in questo caso i leaks e altri problemi vengono scoperti grazie a dei flag messi in compilazione.

Per usare i sanitizers devo avere anche il codice sorgente.
I sanitizers sono più precisi di valgrind e non rallentano il programma.   

---
#### Memory accesses
Per velocizzare il programma è suggerito pensare un accesso alla memoria sequenziale al posto di accederci in modo casuale.
In questo modo diminuiscono i **cache miss**.

Se ad esempio devo leggere i dati da un array, ==è meglio leggere più valori vicini possibili== dato che nella cache L1 **dopo un primo cache miss, viene caricata una cache line lunga circa 16 interi** quindi se accedo ad un elemento vicino a quello missed precedentemente questa volta lo troverò nella cache L1.
