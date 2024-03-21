Un thread è un'unità di esecuzione all'interno di un processo, [POSIX](https://pubs.opengroup.org/onlinepubs/9699919799/) definisce un'insieme di funzioni per la creazione e sincronizzazione dei thread.

- `pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)`:
	1. `thread`: puntatore a `pthread_t` (e.g. `pid_t`)
	2. `attr`: attributi del nuovo thread, ne modificano l'esecuzione (`NULL` se non si vogliono modificare)
	3. `start_routine`: puntatore alla funzione da eseguire
	4. `arg`: eventuali argomenti da passare (`NULL` se non si passa nulla)
- `pthread_exit(void *retval)`: fa terminare il thread che la chiama, ritorna `retval` (nota che `exit` fa uscire il processo intero)
- `pthread_join(pthread_t th, void **thread_return)`: attende la terminazione di `th`, se ha successo ritorna $0$ ed un puntatore al valore ritornato dal thread all'interno del secondo argomento (`NULL` passato come secondo parametro evita che si riceva il valore di ritorno)
- `pthread_detach(pthread_t th)`: evita che un thread possa essere aspettato con la join, in questo modo quando finisce il thread specificato, le sue risorse verranno automaticamente rilasciate
- `pthread_t pthread_self()`: ritorna il proprio thread ID, non è quello visualizzato dal sistema, ma dipende dalla libreria usata

Segue un esempio in cui due thread calcolano il quadrato di due numeri passati da riga di comando e poi il thread principale li somma:
```c
void* quadrato(void* n) {
    *(int*) n *= *(int*) n;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t tid[2];
    int num[2];
    int err;
	
    num[0] = atoi(argv[1]);
    num[1] = atoi(argv[2]);
	
    // crea i thread (ritorna 0 quando ha successo)
    for (int i = 0; i < 2; i++) {
        if ((err=pthread_create(&tid[i], NULL, quadrato, &num[i]))) {
            printf("errore create [%i]\n", err);
            exit(EXIT_FAILURE);
        }
    }
	
    // Attende i thread.
    // Non legge il valore di ritorno (secondo parametro NULL)
    for (int i = 0; i < 2; i++) {
        if ((err=pthread_join(tid[i], NULL))) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE);
        }
    }
	
    printf("quadrati: %d %d\n", num[0], num[1]);
    printf("somma: %d\n", num[0]+num[1]);
    printf("I thread hanno terminato l'esecuzione correttamente\n");
}
```

Se `pthread_detach` fosse stata chiamata prima della join, quest'ultima avrebbe ritornato un errore:

```c
    pthread_detach(tid[0]);
    for (int i = 0; i < 2; i++) {
        if ((err=pthread_join(tid[i], NULL))) {
            printf("errore join [%i]\n",err); // 22
            exit(EXIT_FAILURE);
        }
    }
```

gli errori ritornati sono visibili in `/usr/include/asm-generic/errno-base.h`.