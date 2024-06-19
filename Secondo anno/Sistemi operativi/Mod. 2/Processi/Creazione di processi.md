La creazione di un processo richiede:
- Creazione di un nuovo PID (Process ID)
- Allocazione memoria (dati) e altre risorse (I/O)
- Gestione informazioni sul nuovo processo (e.g. priorità)
- Creazione [[Processi#Process Control Block|PCB]]

Un processo, a macchina avviata, è sempre creato da un altro processo tranne `init` (pid=1) che viene creato al momento del boot.

Vediamo cosa accade dopo la creazione di un processo, generando dei processi figli della **shell**.

- Di default il processo genitore attende il processo figlio:
```shell
~ sleep 5 
```

- Facendo eseguire il processo in background (`&`) i due processi procedono in modo _concorrente_:
```shell
~ sleep 5 &
[1] 26

~ ps -o pid,ppid,comm
  PID  PPID COMMAND
   10     9 bash
   26    10 sleep
   27    10 ps
```

Può essere utile che un processo si dissoci dal processo genitore in modo da non essere terminato alla chiusura della shell (supponendo che sia stato avviato dalla shell), per poi diventare figlio di `init` (e.g. _deamon_).

**Relazioni di contenuto**:
- Il figlio è un duplicato del genitore ([[Memoria virtuale#Strategie di gestione della memoria|copy-on-write]])
- Il figlio esegue un programma differente

Di default nei sistemi Unix avviene il primo caso, mentre in Windows il secondo caso, è comunque possibile l'altra modalità in entrambi i sistemi.

## System call "fork"
La chiamata a sistema `fork` permette di creare un processo duplicato del processo genitore.

>[!Tip] Posix
>Come la maggior parte delle chiamate a sistema che discuteremo, `fork` appartiene allo standard **POSIX** (Portable Operating System Interface).

In particolare, crea un nuovo processo che:
- Condivide l'area codice del processo genitore
- Utilizza una copia dell'area dati del processo genitore

```c
pid_t pid = fork();
if ( pid < 0 ) {
	perror("fork error");
} else if (pid == 0) {
	// codice figlio
} else { // pid > 0
	// codice genitore
}

// codice del genitore e del figlio
```

>Una regola non scritta è che porre `_t` dopo un tipo indica che esso è definito dal sistema su cui si esegue il programma.
>Normalmente `pid_t` è un `int` ([libc](https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_554.html)).

Valore di ritorno di `fork()`:
**Successo**:
- Al padre viene ritornato il pid del figlio
- Al figlio viene ritornato $0$
**Insuccesso**:
- Al padre viene ritornato $-1$, e nessun figlio viene creato

È possibile ottenere il pid del processo attuale con `getpid()`, oppure il pid del padre con `getppid()`.

>[!Attention]
>I pid sono valori univoci incrementali, il contatore viene resettato ad ogni boot.

Una `fork` può **fallire** quando non c'è memoria per il processo o per il kernel.

Una "fork-bomb" consiste nella creazione indefinita di processi figlio per saturare le risorse del sistema:
```c
int main() {
  while(1)
    if (fork() < 0) 
      perror ("errore fork");
}
```

`ulimit` mostra i limiti di risorse per utente per la sessione shell corrente, è possibile modificare il numero di processi utenti creabili (come figli della shell attuale) con `ulimit -u <num>` tuttavia è solamente possibile abbassare i limiti, ma non aumentarli.

### Processi orfani e zombie
Se un processo genitore finisce prima del figlio, il figlio diventerà **orfano** e verrà adottato da `init`.
```c
// ...
else if (pid == 0) { // figlio
	sleep(5);
} else {
	// genitore
}
```

Se un processo figlio è terminato, ma è in attesa che il genitore lo riconosca come tale, esso sarà uno **zombie**.
```c
// ...
else if (pid == 0) {
	// figlio
} else { // genitore
	sleep(5);
}
```
