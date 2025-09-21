La **sezione critica** è la parte di codice in cui i processi accedono a dati condivisi.

Vogliamo garantire la **mutua esclusione** a quella sezione di codice, ovvero fare in modo che un solo thread alla volta possa accedervi.

Vediamo ora vari tentativi per garantire la _mutua esclusione_.
## Soluzioni software
### Lock
Utilizziamo una variabile booleana globale `lock` inizializzata a `false`.
```
thread T {
	....
	while(lock) {}
	lock = true;
	< sezione critica >
	lock = false;
	....
}
```

In questo modo il thread non può accedere alla sezione critica se `lock = true`, ovvero: un altro thread ci è entrato prima di lui settandola a `true`.

**Problema**: più thread potrebbero superare il while contemporaneamente, portando all'esecuzione di più thread nella zona critica.

### Turno
Utilizziamo una variabile booleana globale `turno` inizializzata a `true`.
```
thread T0 {                        thread T1 { 
	....                                ....  
	while(turno != 0) {}                while(turno != 1) {}    
	< sezione critica >                 < sezione critica >   
	turno = 1;                          turno = 0; 
	....                                ....  
}                                   }
```

In questo modo, dato che turno non può valere sia $0$ che $1$ contemporaneamente, si ottiene la **mutua esclusione** in quanto uno dei due thread rimarrà fermo sul `while`.

**Problema**: se uno dei due thread volesse entrare più volte di fila nella sezione critica non potrebbe in quanto l'accesso è alternato, e per quanto ne sappiamo l'altro thread potrebbe anche non entrarci mai nella sezione critica.

Definiamo una seconda proprietà fondamentale chiamata **progresso**:
- Se nessun thread è in sezione critica, un thread che chiede di accederci, deve poterlo fare immediatamente.

### Pronto
Utilizziamo un array booleano globale `pronto[2]` inizializzato a `false`.
```
thread T0 {                        thread T1 { 
	....                                ....  
	pronto[0] = true;                   pronto[1] = true;
	while(pronto[1]) {}                 while(pronto[0]) {}    
	< sezione critica >                 < sezione critica >   
	pronto[0] = false;                  pronto[1] = false;
	....                                ....  
}                                   }
```

In questo modo un thread che vuole accedere alla sezione critica pone a `true` la sua cella nell'array e nel caso ci sia l'altro thread nella sezione critica aspetta, altrimenti ci entra e quando ha finito si rimette (sè stesso) a `false` (non pronto).

La **mutua esclusione** è garantita dal fatto che se un thread è in sezione critica, la sua cella `pronto == true`, quindi l'altro thread non ci potrà entrare.

**Problema**: anche se la _mutua esclusione_ è garantita, se entrambi i thread pongono il proprio `turno = true`, allora rimarrebbero bloccati entrambi nel ciclo `while` ad aspettarsi a vicenda (ma effettivamente non entreranno mai nella sezione critica), avviene quindi uno **stallo**.

### L'algoritmo di Peterson
Utilizziamo una combinazione tra `pronto[2]` e `turno`.
```
thread T0 {                           thread T1 { 
  ....                                  ....  
  pronto[0] = true;                     pronto[1] = true;
  turno=1;                              turno=0;
  while(pronto[1] && turno != 0) {}     while(pronto[0] && turno != 1) {} 
  < sezione critica >                   < sezione critica >   
  pronto[0] = false;                    pronto[1] = false;
  ....                                  ....  
}                                     }
```

Per evitare che `pronto` vada in stallo utilizziamo una turnazione solo nel caso problematico, ovvero quando entrambi i thread sono pronti.

In questo modo quando un thread vuole entrare, pone `pronto[i] = true`, successivamente cede il turno all'altro thread e aspetta se l'altro thread è anch'esso pronto, quando sarà arrivato il suo turno (subito se l'altro thread non è pronto) esegue il codice nella sezione critica e poi pone `pronto[i] = false`.

**Mutua esclusione**:
1. `T0` supera il `while` quando l'altro thread deve ancora settare `turno = 0`, l'altro thread imposterà `turno = 0` ed aspetterà in quanto `T0` ora potrà accedere alla sezione critica
2. `T0` supera il `while` quando l'altro thread ha già settato `turno = 0`, dato che `T0` sta superando il `while`, bisogna che `turno == 0`, quindi l'altro thread aspetta ancora

**Progresso**: se nessuno è in sezione critica, `pronto[i] == false`, chiunque voglia entrarci potrà farlo in quanto la condizione per l'altro thread sarà `false`.

**Assenza di stallo**: `turno` non può essere sia $0$ che $1$, quindi uno dei due thread uscirà necessariamente dal ciclo `while`.

>L'algoritmo di Peterson è generalizzabile per un numero arbitrario di thread.

## Soluzioni hardware
Le soluzioni software appena viste hanno problemi di performance:
1. I cicli a vuoto consumano tempo di CPU
2. Vengono utilizzate variabili globali e una sequenza precisa di istruzioni, questo potrebbe essere un problema in quanto i compilatori moderni per ottimizzare le performance rimaneggiano e riordinano le istruzioni, bisognerebbe disattivare tali ottimizzazioni per assicurarsi che l'algoritmo funzioni come vogliamo

### Disabilitare le interruzioni
Questa tecnica viene usata in sistemi embedded che solitamente hanno poca potenza di calcolo e quindi $1$ core.

Bloccare le interruzioni infatti fa monopolizzare la CPU al thread che le disabilita, infatti così facendo rimuoverà il pre-rilascio e la CPU non passerà il controllo ad altri thread dello stesso processo, in questo modo sarà l'unico ad accedere alla sezione critica, per poi riattivare le interruzioni.

>Questa soluzione non funziona con sistemi che hanno più core, in quanto i thread potrebbero essere eseguiti parallelamente.

### Istruzioni speciali
L'istruzione `test_and_set` permette di testare un valore ed assegnarlo in modo atomico, segue una implementazione in pseudo-C:
```c
boolean test_and_set(boolean* x) {
	boolean ret = *x;
    *x = true;
    return ret;
}
```

la CPU può usare l'istruzione `test_and_set` offerta da altre componenti elettroniche, oppure fornirne una propria definizione.

Il problema del [[Sezione critica#Lock|lock]] può essere risolto così:
```
thread T {
	....
	while(test_and_set(&lock)) {}
	< sezione critica >
	lock = false;
	....
}
```

1. Se `lock == false`, la funzione ritorna `false`, ma allo stesso tempo pone `lock = true` in modo atomico, facendo entrare il thread nella sezione critica
2. Se `lock == true`, la funzione ritorna `true` e lascia inalterato il valore, di conseguenza il thread rimane dentro al `while`

Questa soluzione prende il nome di [spinlock](https://it.wikipedia.org/wiki/Spinlock) e viene usata dai sistemi operativi per realizzare la sezione critica sulle proprie strutture dati.

>[!Tip]
>Nei processori Intel esiste un'istruzione atomica che permette di scambiare il valore di due variabili in modo atomico: `XCHG`:
>```c
>int main() {
>    int a = 0, b = 1;
>    printf("a: %d  b: %d\n", a,b); // a: 0  b: 1
>    
>    __asm__("xchg %0, %1" : "+q" (a), "+m" (b));
>    
>    printf("a: %d  b: %d\n", a,b); // a: 1  b: 0
>}
>```
