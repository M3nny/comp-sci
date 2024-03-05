Le **pipe** sono una forma di comunicazione tra processi con [[Comunicazione tra processi e thread#Nominazione indiretta|nominazione indiretta]] con _send_ asincrona e _receive_ sincrona, rispettivamente `write()` e `read()`.

## Pipe senza nome
le pipe senza nome vengono <u>usate solo da processi con antenati comuni</u>, in quanto sono risorse che vengono ereditate dai genitori.

L'operazione di pipe nella shell è effettuata "al volo" con `|`, mentre in C viene implementata usando la syscall `pipe(fd[2])` la quale prende in input un array di interi lungo 2, per poi restituire due descrittori in `fd`:
- `fd[0]`: lettura
- `fd[1]`: scrittura

Le pipe sono **half-duplex** (monodirezionali), se un processo volesse sia leggere che scrivere sarebbe meglio utilizzare 2 pipe distinte in quanto, altrimenti, non si saprebbe se il messaggio letto sia di un altro processo oppure il suo stesso messaggio appena scritto.

```c
int main() {
    int fd[2];
    pipe(fd); // crea la pipe
	
    if (fork() == 0) {
        char *phrase = "Ciao da tuo figlio";
		
        close(fd[0]); // chiudo in lettura
        write(fd[1], phrase, strlen(phrase)+1); // aggiungo \0
        close(fd[1]); // chiudo in scrittura quando ho finito di scrivere
    } else {
        char message[100];
        memset(message, 0, 100); // metto a 0 l'array
		
        close(fd[1]); // chiudo in scrittura
        // leggo al massimo 99 byte
        int bytesread = read(fd[0], message, 99);
        printf("Ho letto %d bytes:\n%s\n", bytesread, message);
        close(fd[0]); // chiudo la lettura finito di leggere
    }
}
```

<u>Ogni processo tiene aperte solo le risorse che gli servono</u>, quindi o legge o scrive, la porta che non intende usare la chiude subito, e dopo aver letto o scritto chiude anche l'altra rispettiva porta, in questo modo è possibile capire quando buttare via dalla memoria la pipe.

Il _valore di ritorno_ di `read()` sarà il numero di bytes letti, quindi se la pipe è vuota ritornerà 0.

>Se non sono più presenti lettori, verrà lanciato il segnale `SIGPIPE` che di default terminerà l'esecuzione del programma.

### Imitazione pipe da shell
Nel seguente programma imiteremo l'esecuzione di due programmi senza parametri aggiuntivi, dove il primo è il produttore ed il secondo il consumatore.

Ad esempio:
```shell
~ ls | wc
```

equivale a mettere l'output di `ls` all'interno del file `out.txt` ed eseguire:
```shell
~ wc out.txt
```

quindi vogliamo prendere l'output del primo programma ed usarlo come input per il secondo, in particolare vogliamo una pipe condivisa tra due processi, il primo che ci scriverà il suo output, ed il secondo che userà il contenuto della pipe come input.

```c
int main(int argc, char* argv[]) {
    int fd[2];
    pipe(fd);
	
    if (fork() == 0)  {
        close(fd[0]); // chiude in lettura
        dup2(fd[1], 1); // redirige stdout (1) in fd[1]
        close(fd[1]); // questo processo non scriverà più nella pipe
        execlp(argv[1], argv[1], NULL);
        perror("errore esecuzione primo comando");
    } else {
        close(fd[1]); // chiude in scrittura
        dup2(fd[0], 0); // usa fd[0] come stdin (0)
        close(fd[0]); // questo processo non leggerà più dalla pipe
        execlp(argv[2], argv[2], NULL);
        perror("errore esecuzione secondo comando");
    }
}
```

la syscall `dup2(int oldfd, int newfd)` crea una copia di `oldfd` chiudendo prima `newfd` se necessario, entrambi i file descriptor devono essere validi.

Esempio di utilizzo:
```shell
~ ./home_made_pipe ls wc
```


Le `write` sulle pipe sono **atomiche** se inferiori alla dimensione di `PIPE_BUF` (presente in `limits.h`), questo vuol dire che sono eseguite in una sola operazione, sopra quella soglia potrebbero volerci più operazioni da parte del sistema, portando quindi a dalle stringhe disordinate se più processi provassero a scrivere oltre a quella soglia contemporaneamente.

## Pipe con nome
le pipe con nome consentono a processi non in relazione tra loro di scambiarsi informazioni, per creare una pipe con nome bisogna usare il comando `mkfifo` il quale creerà un file speciale che svolgerà la funzione di pipe.

- `mkfifo(mypipe, 0666)`: crea una pipe con nome in lettura e scrittura
- `int fd = open(mypipe, O_RDONLY)`: apre la pipe `mypipe` in modalità readonly
- `int fd = open(mypipe, O_WRONLY)`: apre la pipe `mypipe` in modalità writeonly
- `unlink(mypipe)`: rimuove la pipe dal file system


scrittore.c
```c
int main() {
    mkfifo("mypipe", 0666); // crea la pipe se non esiste
	
    int fd = open("mypipe", O_WRONLY); // apre la pipe in scrittura
    if ( fd < 0 ) {
        perror("errore apertura pipe");
        exit(1);
    }
	
    char* message = "Ciao da un'altro processo\0";
    write (fd, message, strlen(message));
	
    close(fd); // chiude il descrittore
}
```

lettore.c
```c
int main() {
    mkfifo("mypipe", 0666); // crea la pipe se non esiste
	
    int fd = open("mypipe", O_RDONLY); // apre la pipe in scrittura
    if ( fd < 0 ) {
        perror("errore apertura pipe");
        exit(1);
    }
	
    char char_iter;
    while(read(fd, &char_iter, 1)) { // legge un carattere alla volta
        if (char_iter == '\0'){
            printf("\n");
        } else {
            printf("%c", char_iter);
        }
    }
	
    close(fd); // chiude il descrittore
    unlink("mypipe"); // rimuove la pipe
}
```

Eseguendo i due programmi in parallelo:
```shell
~ ./scrittore & ./lettore
"Ciao da un'altro processo"
```

>[!Attention]
>Una open in scrittura di una pipe non ancora aperta in lettura è **bloccante**.

Le pipe con nome sebbene possono essere aperte con l'opzione `O_RDWR` (read-write) non hanno senso di essere read-write, per lo stesso motivo delle pipe senza nome, ovvero non si può discriminare se un processo sta leggendo quello che lui stesso ha scritto.
