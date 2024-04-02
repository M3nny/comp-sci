I semafori POSIX sono contatori che permettono la sincronizzazione dei thread POSIX.

- `sem_t sem_name`: dichiara un semaforo
- `int sem_init(sem_t *sem, int pshared, unsigned int value)`: inizializza `sem` a `value`, la variabile `pshared == 0` indica che il semaforo è condiviso tra thread, se `pshared > 0` allora è condiviso tra processi (noi la useremo sempre a `0`)
- `int sem_wait(sem_t *sem)`: **P(sem)**
- `int sem_post(sem_t *sem)`: **V(sem)**
- `int sem_getvalue(sem_t *sem, int *val)`: legge il valore del semaforo e lo copia in `val`
	In alcune implementazioni il semaforo rosso è sempre $0$, in altre è negativo e indica il numero di thread in coda
- `sem_destroy(sem_t *sem)`: elimina il semaforo (da usare quando non c'è più nessuno in coda)

Per creare semafori con nome si applicano le seguenti modifiche:
- `sem_init -> sem_open("mutex", O_CREAT, 0644, 1)`
- `sem_destroy -> sem_close(var_mutex)` seguito da `sem_unlink("mutex")`

### Sezione critica
Vogliamo incrementare un contatore globale $1.000.000$ volte per thread:
```c
#define MAX 1000000
int count = 0;

void * incrementa(void * a) {
    for(int i = 0; i < MAX; i++) {
        count++;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[2];
    int i,err;

    for (int i = 0;i < 2; i++) {
        if ((err=pthread_create(&tid[i], NULL, incrementa, NULL))) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE);
        }
    }
    for (i=0;i<2;i++) {
        if ((err=pthread_join(tid[i], NULL))) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE);
        }
    }
    printf("count: %d\n", count);
}
```

se eseguito senza ottimizzazioni, il risultato varierà, in quanto la sezione critica non è gestita correttamente, se è eseguito con ottimizzazioni da parte del compilatore, esso potrebbe togliere il ciclo `for` e sommare direttamente $1.000.000$.

per garantire la mutua esclusione introduciamo un semaforo `mutex` inizializzato a `1` per dare l'accesso alla sezione critica ad un thread alla volta:
```c
#define MAX 1000000
int count = 0;
sem_t mutex;

void * incrementa(void * a) {
    for(int i = 0; i < MAX; i++) {
        sem_wait(&mutex); // P
        count++;
        sem_post(&mutex); // V
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[2];
    int err;
    sem_init(&mutex,0,1);

    for (int i = 0;i < 2; i++) {
        if ((err=pthread_create(&tid[i], NULL, incrementa, NULL))) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < 2; i++) {
        if ((err=pthread_join(tid[i], NULL))) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE);
        }
    }

    sem_destroy(&mutex);
    printf("count: %d\n", count);
}
```

Usando i **semafori con nome**:
```c
#define MAX 1000000
int count = 0;
sem_t *mutex; // puntatore a sem_t

void * incrementa(void * a) {
    for(int i = 0; i < MAX; i++) {
        sem_wait(mutex); // non più &mutex
        count++;
        sem_post(mutex); // non più &mutex
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[2];
    int err;
    // mutex è un puntatore a sem_t
    mutex = sem_open("mutex", O_CREAT, 0644, 1);

    for (int i = 0; i < 2; i++) {
        if ((err=pthread_create(&tid[i], NULL, incrementa, NULL))) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < 2; i++) {
        if ((err=pthread_join(tid[i], NULL))) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE);
        }
    }

    sem_close(mutex); // non più &mutex
    sem_unlink("mutex");
    printf("count: %d\n", count);
}
```


### Attendere un thread
Implementiamo l'[[Semafori#Attendere un thread|esempio]] visto precedentemente in C:
```c
sem_t sinc;

void * T1(void * j) {
    printf("Eseguito < A >\n");

    // semaforo rosso
    sem_post(&sinc); // OK a D di T2!
    printf("Eseguito < B >\n");
}

void * T2(void * j) {
    printf("Eseguito < C >\n");
	
    // semaforo rosso
    sem_wait(&sinc); // attende A di T1
    printf("Eseguito < D >\n");
}

int main() {
    pthread_t tid[2];
    int i,err;
	
    sem_init(&sinc, 0, 0); // semaforo rosso
	
    if ((err=pthread_create(&tid[0], NULL, T1, NULL))) {
		printf("errore create [%i]\n",err);
		exit(EXIT_FAILURE);
    }
    if ((err=pthread_create(&tid[1], NULL, T2, NULL))) {
		printf("errore create [%i]\n",err);
		exit(EXIT_FAILURE);
    }
	

    for (i = 0; i < 2; i++) {
        if ((err=pthread_join(tid[i], NULL))) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE);
        }
    }

    sem_destroy(&sinc);
    printf("I thread hanno terminato l'esecuzione correttamente.\n");
}
```

In questo modo la sezione di codice `< D >` verrà sempre eseguita dopo la sezione `< A >`.

Possibili esecuzioni:
```
Eseguito < A >
Eseguito < B >
Eseguito < C >
Eseguito < D >

Eseguito < C >
Eseguito < A >
Eseguito < D >
Eseguito < B >
```

### Produttori e consumatori
Implementiamo il problema dei [[Semafori#Produttore e consumatore con semafori|produttori e consumatori]] in C:
```c
#define MAX 10
#define N_PROD 3
#define N_CONS 3

int buffer[MAX]; // buffer circolare
int inserisci = 0, preleva = 0;

sem_t piene, vuote, mutex;

void* prod(void* a) {
    while(1) {
		sem_wait(&vuote); // richiede una cella vuota
		sem_wait(&mutex); // entra in sezione critica

		if (buffer[inserisci] != 0) {
			printf("Produttore non sincronizzato\n");
            exit(1);
		}
		buffer[inserisci] = 1;
		inserisci = (inserisci + 1) % MAX;

		sem_post(&mutex); // lascia la sezione critica
		sem_post(&piene); // inrementa il numero di celle piene
	}
	pthread_exit(NULL);
}

void* cons(void* a) {
    while(1) {
		sem_wait(&piene); // richiede una cella piena
		sem_wait(&mutex); // entra in sezione critica

		if (buffer[preleva] == 0) {
			printf("Consumatore non sincronizzato\n");
            exit(1);
		}

		buffer[preleva] = 0;
		preleva = (preleva + 1) % MAX;

		sem_post(&mutex); // lascia la sezione critica
		sem_post(&vuote); // incrementa il numero di celle vuote
	}
	pthread_exit(NULL);
}

int main() {
    pthread_t tid_prod[N_PROD], tid_cons[N_CONS];
    int err;

	// conta il numero di celle piene inizialmente
    sem_init(&piene, 0, 0);
    // conta il numero di celle vuote inizialmente
    sem_init(&vuote, 0, MAX);
    // 1: garantisce mutua esclusione
    sem_init(&mutex, 0, 1);


	for (int i = 0; i < MAX; i++) {
		buffer[i] = 0;
	}

	for (int i = 0; i < N_PROD; i++) {
		if ((err = pthread_create(&tid_prod[i], NULL, prod, NULL))) {
			printf("errore create [%d]\n", err);
			exit(EXIT_FAILURE);
		}
    }

	for (int i = 0; i < N_CONS; i++) {
		if ((err = pthread_create(&tid_cons[i], NULL, cons, NULL))) {
			printf("errore create [%d]\n", err);
			exit(EXIT_FAILURE);
		}
    }


    for (int i = 0; i < N_PROD; i++) {
        if ((err = pthread_join(tid_prod[i], NULL))) {
            printf("errore join [%d]\n", err);
            exit(EXIT_FAILURE);
		}
    }

    for (int i = 0; i < N_CONS; i++) {
        if ((err = pthread_join(tid_cons[i], NULL))) {
            printf("errore join [%d]\n", err);
            exit(EXIT_FAILURE);
		}
    }

    sem_destroy(&mutex);
    sem_destroy(&piene);
    sem_destroy(&vuote);
}
```

