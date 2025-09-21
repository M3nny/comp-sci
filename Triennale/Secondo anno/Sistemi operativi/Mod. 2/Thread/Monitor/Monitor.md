Con i [[Semafori|semafori]] abbiamo alcune difficoltà:
- Sincronizzazione gestita dai singoli thread
- Sincronizzazione complessa in caso di attesa che si verifichino certe condizioni

I **monitor** sono un costrutto linguistico che centralizzano il problema nel _monitor_ consentendo di gestire facilmente la mutua esclusione.

Dispongono dei seguenti **meccanismi di sincronizzazione**:
1. Le procedure sono eseguite in mutua esclusione
2. Mettono a disposizione delle variabili speciali, dette **conditions**, sulle quali sono possibili due operazioni:
	- **Wait**: il thread si mette in attesa sulla coda relativa alla condition, rilasciando automaticamente il _mutex_
	- **Signal o Notify**: riattiva il primo thread in attesa sulla coda relativa alla condition (se non c'è nessuno in attesa, non fa nulla)

### Signal vs notify
- **Signal**: il thread sbloccato va subito in esecuzione nel monitor, mentre chi ha chiamato la _signal_ attende che il thread sbloccato esca dal monitor
- **Notify**: il thread sbloccato si mette in coda per ri-accedere al monitor, mentre chi ha chiamato la _notify_ prosegue la sua esecuzione

In breve con la _signal_ si è sicuri che il thread verrà eseguito subito, mentre con la _notify_ dipende dallo scheduler.

### Produttore e consumatore
Risolviamo il problema dell'accesso al [[Produttore e consumatore#Produttore e consumatore con memoria condivisa|contatore condiviso]] centralizzando il problema in un monitor.

Il monitor avrà due procedure:
```c
Produttore() {
	while(1) {
		/* produce un elemento d */
		pc.scrivi(d);
	}
}

Consumatore() {
	while(1) {
		d = pc.leggi();
		/* consuma d */
	}
}
```

La sincronizzazione avviene tutta nel monitor che definiamo come segue:
```c
Monitor pc {
	dato buffer[MAX];
	int contatore=0, inserisci=0, preleva=0;
	condition piene,vuote;
	
	void scrivi(dato d) {
		if (contatore == MAX)
			vuote.wait(); // buffer pieno attendo
		
		/* scrivi sul buffer */
		buffer[inserisci] = d;
		inserisci=(inserisci+1)%MAX; // Il buffer è circolare
		
		contatore++; // aggiorno il contatore
		piene.signal();
	}
	
	dato leggi() {
		if (contatore == 0)
			piene.wait(); // buffer vuoto attendo
		
		/* leggi dal buffer */
		d = buffer[preleva];
		preleva=(preleva+1)%MAX; // Il buffer è circolare
		
		contatore--; // aggiorno il contatore
		vuote.signal();
		return d;
	}
}
```

La scrittura avverrà solo quando il contatore non è uguale a `MAX`.

Un **esempio di esecuzione** con un consumatore `C`  e due produttori `P1, P2` è la seguente:
1. `contatore = 0`
2. `C` in attesa sulla coda piene
3. `P1` invoca `pc.scrivi(d)` (scrive effettivamente dato che `contatore = 0`)
4. `P2` in attesa sull'invocazione di `pc.scrivi`

L'effetto è quello di consumare subito il dato prodotto in quanto nessun altro consumatore può aver letto tra la `signal` e l'esecuzione di `C`.

Ora lo stato è il seguente:
1. `contatore = 1`
2. `C` nel monitor subito dopo `piene.wait()`
3. `P1` in attesa sulle `piene.signal()` dentro `pc.scrivi(d)`
4. `P2` in attesa sull'invocazione di `pc.scrivi`

il consumatore legge il dato, decrementa il `contatore` ed esegue `vuote.signal()` che non farà nulla dato che non ci sono thread in attesa su quella coda, poi `C` esce dal monitor e viene eseguito `P1` in quanto è in attesa prioritaria rispetto a `P2`:
1. `contatore = 0`
2. `C` uscito dal monitor
3. `P1` nel monitor sulla `piene.signal()` dentro `pc.scrivi(d)`
4. `P2` in attesa sull'invocazione di `pc.scrivi`

poi `P1` esce immediatamente dal monitor e viene eseguito `P2` che scriverà nel buffer ed aggiornerà il `contatore`:
1. `contatore = 1`
2. `C` uscito dal monitor
3. `P1` uscito dal monitor
4. `P2` uscito dal monitor


Usare **notify al posto di signal** crea problemi in quanto, con la `notify` potrebbe accadere che sbloccando un consumatore, ne venga eseguito un altro prima di esso, si può evitare questo problema usando un `while`:
```c
// produttore
while (contatore == MAX)
	vuote.wait();

contatore++;
piene.notify();
```

### Filosofi a cena con raccolta atomica
Abbiamo visto tre modi per risolvere il problema dei [[Problemi noti#Filosofi a cena|filosofi a cena]] con i semafori, e l'approccio della raccolta atomica con i semafori non parallelizzava molto.

Vediamo come potrebbe essere risolto questo problema usando i monitor con le procedure: `raccogli(i)` e `deposita(i)` che raccolgono **entrambe** le bacchette dell'$i$-esimo filosofo:
```c
Monitor tavola {
	boolean bacchetta[5]={true,true,true,true,true};
	condition filosofo[5]; // code di attesa per i filosofi
	
	void raccogli(int i) {
		while(!bacchetta[i] || !bacchetta[(i+1)%5])
			// attende se non sono disponibili entrambe le bacchette
			  filosofo[i].wait();
		
			// raccoglie le bacchette in modo atomico
			bacchetta[i] = false;
			bacchetta[(i+1)%5] = false;
	}
	
	void deposita(int i) {
		// deposita le bacchette
		bacchetta[i] = true;
		bacchetta[(i+1)%5] = true;
		
		// notifica il filosofo a sx e quello a dx
		filosofo[(i+4)%5].notify();
		filosofo[(i+1)%5].notify();
	}
}
```

I filosofi attendono solo se non sono presenti entrambe le bacchette, la `wait` è all'interno di un `while` perchè quando un filosofo viene svegliato deve verificare la presenza di entrambe le bacchette.

>In questo caso l'uso di `signal` non altera l'esecuzione in quanto comunque bisognerà ri-verificare la condizione di bloccaggio.

