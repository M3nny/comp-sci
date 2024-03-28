Gli spinlock utilizzati solo dai sistemi operativi, ma quasi mai nelle applicazioni, vediamo ora uno dei metodi più semplici ed efficaci.

Un **semaforo** è un contatore (intero) con una coda di attesa:
```c
struct semaphore {
	int val;
	thread* queue; 
}
```

Immaginando di avere un semaforo `S`:
- `S.val > 0`: il semaforo è <span style="color:#32CD32">verde</span>
	`val` indica il numero di accessi consentiti prima che diventi rosso
- `S.val <= 0`: il semaforo è <span style="color:#ff0000">rosso</span>
	Il valore assoluto di `val` indica il numero di thread in coda al semaforo

>In alcune implementazioni i semafori non assumono mai un valore negativo, un semaforo rosso avrà quindi sempre valore $0$.

I semafori vengono incrementati/decrementati tramite funzioni che gestiscono la sincronizzazione dei thread:
- `P(S)` o `wait(S)`: decrementa `S.val`, se era già rosso, il thread si mette in coda
- `V(S)` o `post(S)`: incrementa `S.val`, se ci sono thread in attesa, viene sbloccato il primo della coda

```c
P(semaphore S) {
	S.valore--;
	if (S.valore<0)
	    // Metti il thread corrente in attesa su S.queue
}

V(semaphore S) {
	S.valore++;
	if (S.valore<=0)
	    // Sblocca il primo thread in attesa su S.queue
}
```

### Sezione critica con i semafori
Il valore del semaforo indica il numero di accessi consentiti prima di diventare rosso.

Inizializziamo il semaforo `mutex` al valore $1$, poi eseguiamo `P(mutex)` per accedere alla zona critica, ed alla fine rispristiniamo il semaforo con `V(mutex)`:
```c
thread T {
	P(mutex);
	// sezione critica
	V(mutex);
}
```

vediamo una rappresentazione grafica di tre thread che cercano di accedere alla sezione critica:
```
T1 -----------P====V----P==============V--------------

T2 --------------------------P         +====V---------

T3 -------------------------------P         +====V----

mutex
 valore: 1    0    1    0   -1   -2   -1    0    1  
 queue:  _    _    _    _    |    |    |    _    _  
                             T2   T2   T3  
                                  |  
                                  T3 
```

Indici:
- `P`: `P(mutex)`
- `V`: `V(mutex)`
- `----`: esecuzione fuori dalla sezione critica
- `====`: esecuzione nella sezione critica

1. `T1` entra ed esce dalla sezione critica senza che nulla di speciale accada, in quanto è l'unico a volerci accedere, alla fine riporta il semaforo allo stato iniziale
2. `T1` rientra nella sezione critica, questa volta però non è l'unico che ci vuole accedere, infatti, anche `T2` e `T3` vogliono accederci, però questi arrivano dopo, quindi decrementano il semaforo e si mettono in coda
3. `T1` finisce, incrementa il semaforo e da il turno al prossimo thread in coda, quando anch'esso finirà farà la stessa cosa
4. Quando tutti i thread hanno finito di accedere alla sezione critica, il valore del semaforo sarà di nuovo $1$

### Attendere un thread
Supponiamo che `T2` debba aspettare che `T1` esegua `< A >` prima di eseguire la sua porzione di codice `< D >`, possiamo procedere come segue:
```
semaphore S=0;

  T1 {                    T2 {
    < A >                    < C >
    V(S) ------------------> P(S)
    < B >                    < D >
  }                       }
```

Dato che `S` è inizializzato a $0$ (rosso), la `P(S)` di `T2` sarà bloccante (mette `T2` in coda), e di conseguenza il codice `< D >` sarà eseguito dopo `< A >`, ovvero dopo che `T1` avrà sbloccato `T2`.

### Regolare l'accesso a risorse
Un semaforo inizializzato ad $1$ può essere utilizzato per regolare l'accesso ad una sezione critica, mentre se inizializzato a $0$ può essere usato per aspettare un altro thread.

Se inizializziamo `S.val` a `MAX`, esso consentirà `MAX` accessi prima di diventare bloccante, possiamo quindi vedere il semaforo sotto un'altra ottica:
- `P(S)` richiesta di risorsa: se ce ne è una disponibile viene assegnata, altrimenti si attende
- `V(S)` rilascio di risorsa: se ci sono thread in attesa, il primo viene sbloccato

### Produttore e consumatore con semafori
Quando il buffer è pieno il produttore deve attendere, quando è vuoto, il consumatore deve attendere (per evitare di leggere celle ancora non scritte).

Usiamo due semafori che regolano l'accesso a risorse:
- `vuote`: inizializzato a `MAX = <n. celle inizialmente vuote>`
- `piene`: inizializzato a $0$, in quanto inizialmente non abbiamo celle piene

```c
semaphore piene=0, vuote=MAX;

Produttore {
	while(1) {
	    < produce d >
	    P(vuote); // richiede una cella vuota
	    buffer[inserisci] = d;
	    inserisci = (inserisci+1) % MAX;
	    V(piene); // rilascia una cella piena
	}
}
 
Consumatore {
	while(1) {
		P(piene); // richiede una cella piena
	    d = buffer[preleva];
	    preleva = (preleva+1) % MAX:
	    V(vuote); // rilascia una cella vuota
	    < consuma d >
	}
}
```

con **tanti produttori e consumatori** si potrebbero creare interferenze in scrittura e lettura sul buffer, introduciamo quindi un nuovo semaforo `mutex` (inizializzato a $1$) per creare una sezione critica:
```c
semaphore piene=0, vuote=MAX, mutex=1;

Produttore() {
	while(1) {
	    < produce d >
	    P(vuote); // richiede una cella vuota
	    P(mutex); // entra in sezione critica
	    buffer[inserisci] = d;
	    inserisci = (inserisci+1) % MAX;
	    V(mutex); // esce dalla sezione critica
	    V(piene); // rilascia una cella piena
	}
}
 
Consumatore() {
	while(1) {
	    P(piene); // richiede una cella piena
	    P(mutex); // entra in sezione critica
	    d = buffer[preleva];
	    preleva = (preleva+1) % MAX:
	    V(mutex); // esce dalla sezione critica
	    V(vuote); // rilascia una cella vuota
	    < consuma d >
	}
}
```

>[!Attention]
>Quando si inseriscono sezioni critiche bisogna fare attenzione che non ci siano semafori bloccanti al loro interno.
>
>Se un `consumatore` fosse schedulato per primo, creerebbe uno stallo, in quanto verrebbe bloccato su `P(piene)`.

