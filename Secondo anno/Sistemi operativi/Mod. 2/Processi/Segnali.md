I segnali sono **interruzioni software** causate da svarianti eventi.
Quando arriva un segnale possiamo:
- **Ignorarlo**
- **Gestirlo**
- **Lasciare il compito al gestore di sistema**

Vediamo in quale caso alcuni segnali vengono inviati ad un processo:
- `SIGHUP`: il terminale a cui è associato viene chiuso
- `SIGINT`: interrompe il processo con Ctrl-C
- `SIGQUIT`: termina il processo con Ctrl-\\
- `SIGILL` (istruzione illegale), `SIGABRT` (invocazione di _abort_), `SIGFPE` (errore aritmetico), `SIGSEGV` (riferimento a memoria illegale): corrispondono ad azioni del processo stesso
- `SIGKILL`, `SIGTERM`: inviati da un processo a un altro, vengono utilizzati per terminare un processo
- `SIGPIPE`: scrittura su una pipe che non ha lettori
- `SIGALRM`: è un timer che “sveglia” un processo, simile al timer usato dallo scheduler per implementare il time-sharing
- `SIGCHLD`: viene inviato a un processo quando un suo processo figlio termina (il segnale viene utilizzato per svegliare un processo che ha invocato la `wait`, altrimenti viene ignorato)

**Azioni** possibili in seguito al ricevimento di un segnale:
- `Term`: termina il processo
- `Ign`: ignora il segnale
- `Core`: termina il processo e salva lo stato della memoria in modo da poter essere esaminato da un debugger (e.g. segmentation fault, core dumped)
- `Stop`: ferma il processo
- `Cont`: fa continuare il processo se era fermato

### Impostare il gestore dei segnali
Tramite la syscall `signal()` è possibile cambiare il gestore dei segnali.

```c
void alarmHandler() {
	printf("questo me lo gestisco io!\n");
    alarm(3); // ri-setta il timer a 3 secondi
}

int main() { 
    signal(SIGALRM, alarmHandler);
    alarm(3);
    while(1){}
}
```

In questo esempio il ciclo while viene interrotto da `alarm` il quale lancia un segnale `SIGALARM` che verrà gestito da `alarmHandler`, il quale però rilancia lo stesso segnale causando una stampa ogni 3 secondi.
>Compilando con `--ansi`, una volta catturato il segnale non è possibile rilanciarlo.

Al posto di passare la funzione di gestione del segnale, è possibile passare a `signal` le seguenti costanti:
- `SIG_IGN`: ignora il segnale
- `SIG_DFL`: usa l'handler di default del sistema

`signal` in caso di errore, ritornerà `SIG_ERR`, altrimenti ritornerà l'handler usato precedentemente, nel seguente esempio memorizziamo l'handler precedente (`SIG_DFL`) all'interno di `sig_t old` (è un [puntatore a funzione](https://en.wikipedia.org/wiki/Function_pointer) di tipo `void (*)(int)`) vedi esempio:

```c
int main() {
    sig_t old = signal(SIGINT, SIG_IGN);
    printf("Sono protetto!\n");
    sleep(3);
	
    signal(SIGINT, old);
    printf("Non sono più protetto!\n");
    sleep(3);
}
```

>Per garantire la portabilità tra sistemi, si consiglia di usare `sigaction`.

### Sospensione e ripristino dei processi
Tramite la syscall `kill()` è possibile mandare un segnale ad un processo.
Il segnale di default è `SIGTERM` il quale implica la terminazione del processo con il pid specificato.

È possibile anche mandare altri segnali come quello di sospensione e di ripresa:
- `kill(pid, SIGSTOP)` sospende pid
- `kill(pid, SIGCONT)` risveglia pid

### Mascherare i segnali
È possibile bloccare temporaneamente i segnali tramite le **maschere**, le quali **posticipano** i segnali in questione, utile se si sta eseguendo un'operazione delicata.

>Tipicamente se più segnali uguali vengono generati, solo uno verrà "recapitato" quando il blocco viene tolto.

Per mascherare i segnali è possibile usare la syscall
`sigprocmask(int action, sigset_t* newmask, sigset_t* oldmask)`, la quale prende in input due _set_ di segnali (newmask e oldmask) e specifica una azione:
- `SIG_BLOCK`: **unisce** `newmask` a `oldmask`
- `SIG_UNBLOCK`: **sottrae** `newmask` a `oldmask`
- `SIG_SETMASK`: **sostituisce** `oldmask` con `newmask`

>`sigprocmask()` ritorna un valore $<0$ nel caso NON fosse andata a buon fine.

Per gestire i _set_ di tipo `sigset_t`, si utilizzano:
- `sigemptyset(sigset_t* set)`: inizializza un set vuoto
- `sigaddset(sigset_t* set, int signum)`: aggiunge il segnale `signum` a `set`

Nel seguente esempio viene mascherato inizialmente `SIGINT` per evitare di essere bloccato dal Ctrl-C, dopo 3 secondi la maschera viene tolta ed il programma terminerà immediatamente se prima aveva ricevuto quel tipo di segnale, altrimenti aspetterà altri 3 secondi prima di terminare naturalmente:
```c
int main() {
	sigset_t newmask, oldmask;

	sigemptyset(&newmask); // insieme vuoto
	sigaddset(&newmask, SIGINT); // aggiunge SIGINT alla "maschera"
	
	// setta la nuova maschera e memorizza la vecchia
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		perror("errore settaggio maschera");
		exit(1);
	}
	
	printf("Sono protetto!\n");
	sleep(3);
	
	// reimposta la vecchia maschera
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		perror("errore settaggio maschera");
		exit(1);
	}
	
	printf("Non sono piu' protetto!\n");
	sleep(3);
}
```

>[!Attention]
>I segnali: `SIGKILL` e `SIGSTOP`, NON possono essere catturati, mascherati o ignoranti, fanno terminare il processo senza alcuna eccezione.

### Attendere segnali
Nel primo esempio in questo file abbiamo usato un ciclo infinito (busy-waiting) per aspettare il segnale, tuttavia la syscall `pause()` **attende un segnale qualsiasi**  senza consumare tempo di CPU:

```c
void alarmHandler() {
    printf("questo me lo gestisco io!\n");
}

int main() {
    signal(SIGALRM, alarmHandler);
    alarm(3);
    
    pause();
    printf("segnale ricevuto, termino!\n");
}
```