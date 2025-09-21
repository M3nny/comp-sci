Con la chiamata a sistema `exec` è possibile **sostituire** _codice e dati_ di un processo con quelli di un programma differente.

### Copy-on-write
Potrebbe sembrare inefficiente chiamare una `exec` subito dopo una `fork`, a causa dei dati copiati e scartati subito, ma con il meccanismo di **copy-on-write** al momento della `fork` viene <u>copiata solo la page table</u>, e le pagine (condivise) vengono settate come read-only, alla prima scrittura del padre o del figlio:
1. Si copia la pagina fisica e si fa puntare la page table in questione (duplicata precedentemente) alla nuova copia
2. Viene impostata la modalità read-write e da questo momento le due copie sono indipendenti

Quindi se viene eseguita una `exec` subito dopo una `fork`, dato che non avviene nessuna scrittura, nessuna pagina viene effettivamente copiata.

### Sintassi "exec"
Le varianti di `exec<...>` di differenziano per _formato degli argomenti_, _utilizzo del path_.

Per convenzione il primo argomento contiene il nome dell'eseguibile, inoltre, indipendentemente da come sono passati gli argomenti, devono essere terminati da `NULL`.

- `l`: formato degli argomenti in forma di lista
- `v`: formato degli argomenti in forma di array
- `p`: risolve il comando usando il path di sistema

```c
execl("/bin/ls", "/bin/ls", "-a", NULL);
execlp("ls", "ls", "-a", NULL);


char* argv[] = {"/bin/ls", "-a", NULL};
execv("/bin/ls", argv);

char* argv[] = {"ls", "-a", NULL};
execvp("ls", argv);
```

Valori di ritorno di `exec()`:
- **Successo**: non ritorna nulla, il vecchio codice è completamente sostituito da quello nuovo
- **Insuccesso**: ritorna $-1$ e continua l'esecuzione del programma che l'ha chiamata

**Nota**: se l'eseguibile esiste ma gli argomenti a lui passati sono errati, l'errore sarà sollevato dall'eseguibile, `exec`non fallisce.
```c
execlp("ls", "ls", "--huh", NULL); // errore di ls
perror("errore"); // non viene stampato

// ---

execlp("sl", "ls", "--huh", NULL);
perror("errore"); // viene stampato
```

>`perror()` esegue la stampa solo se ci sono stati degli errori prima di lui.
>(Nel primo caso dell'esempio precedente, neanche `printf` verrebbe eseguito).

### Terminazione di un processo
La terminazione di un processo rilascia le risorse allocate dal SO e segnala la terminazione al genitore, alcune informazioni di stato (presenti nel [[Processi#Process Control Block|PCB]]) vengono messe a disposizione del genitore finchè non vengono processate.

Il sistema mantiene almeno:
- PID
- Stato di terminazione
- Tempo di CPU usato dal processo

`exit(int stato)` termina il processo corrente ritornando lo stato al genitore, solitamente si usano le costanti `EXIT_SUCCESS == 0` e `EXIT_FAILURE == 1`.

`wait(int &stato)` attende la terminazione di **un** figlio, ritorna il pid e lo stato del figlio che ha terminato, se non interessa lo stato si invoca `wait(NULL)`, se non ci sono figli ritorna $-1$.

È possibile usare altre varianti di `wait`, come `waitpid` il quale prende come argomenti:
- PID da aspettare
- Status da modificare
- Un intero che specifica come deve aspettare

Valori di ritorno di `wait` (gestiti dalle macro):
- `WEXITSTATUS(status)` ritorna il bit di stato con cui è uscito il processo
- `WIFEXITED(status) == true` se il figlio è uscito normalmente con una `exit`
- `WIFSIGNALED(status) == true` se il figlio è stato terminato in maniera anomala

```c
int main() {
    int status;
	
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("errore");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        exit(EXIT_SUCCESS);
    }
	
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("errore");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        int* tmp = 0;
        int a = *tmp; // segfault
    }
	
    pid1 = waitpid(pid1, &status, 0);
    if (WIFEXITED(status))
        printf("[%d] graceful shutdown with status %d\n", pid1, status);
	
    pid2 = waitpid(pid2, &status, 0);
    if (WIFSIGNALED(status))
        printf("[%d] ERROR: terminated with status %d\n", pid2, status);
}
```

```shell
~ ./exec
[1700] graceful shutdown: with status 0
[1701] ERROR: terminated with status 11
```