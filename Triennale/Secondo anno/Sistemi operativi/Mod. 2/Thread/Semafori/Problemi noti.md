### Sincronizzazione molti a uno
Considerando la variante del [[Semafori#Produttore e consumatore con semafori|produttore e consumatore]] in cui ci sono $n$ produttori che generano $n$ dati, i quali verranno computati simultaneamente da un singolo consumatore quando sono stati tutti prodotti.

In questo caso ci serviranno:
- $n$ semafori `piene`
- $n$ semafori `vuote`
>Due semafori per produttore in pratica.

- $n$ `mutex`
>Uno per ogni coda.

```
queue dato_produttore[N]; 
semaphore vuote[N]={MAX, ..., MAX}; 
semaphore piene[N]={0, ..., 0};
semaphore mutex[N]={1, ..., 1};

Produttore(i) {
	while(1) {
		< produce d >
		
		P(vuote[i]);
		P(mutex[i]);
		dato_produttore[i].add(d);
		V(mutex[i]);
		V(piene[i]);
	}
}
 
Consumatore {
	while(1) {
		for (i=0;i<N;i++) { // si sincronizza con ogni produttore
			P(piene[i]);
			P(mutex[i]);
			d[i] = dato_produttore[i].remove();
			V(mutex[i]);
			V(vuote[i]);
		}
		< consuma d[0], ..., d[N-1] >
	}
}
```

In questo modo otteniamo $n$ sincronizzazioni distinte consentendo quindi ai produttori di eseguire in parallelo, al posto che sequenzialmente.

### Lettori e scrittori
Il problema è il seguente:
- Più lettori possono leggere indisturbati il dato senza causare incoerenze
- Uno scrittore potrà scrivere solo se è l'unico ad accedere al dato

L'accesso viene quindi regolato secondo il seguente principio: **uno scrittore oppure tanti lettori**.

Utilizziamo:
- Un mutex per la scrittura inizializzato a $1$ `scrittura`
- Una variabile `num_lettori` inizializzata a $0$, terrà traccia dei lettori attivi
- Un mutex per i lettori `mutex` inizializzato a $1$, proteggerà la variabile condivisa dai lettori `num_lettori` 

Dopo che un lettore ha acquisito la mutua esclusione per la sezione critica, anche gli altri potranno entrare direttamente, l'ultimo lettore rilascerà il `mutex`.

```
semaphore scrittura=1;
semaphore mutex=1;
int num_lettori=0;

Scrittore {
	while(1) {
		...
		P(scrittura);
		
		< modifica i dati >
		
		V(scrittura);
		...
	}
}

Lettore {
	while(1) {
		...
		P(mutex); // protegge num_lettori e accoda i lettori
		num_lettori++;
		if (num_lettori == 1)  // primo lettore
			P(scrittura); // prende mutua esclusione in scrittura
		V(mutex);
		
		< legge i dati >
		
		P(mutex);              // protegge num_lettori
		num_lettori--;
		if (num_lettori == 0)  // ultimo lettore 
			V(scrittura); // rilascia mutua esclusione in scrittura
		V(mutex);
		...
	}
}
```

Se i lettori continuano ad arrivare, si potrebbe verificare il fenomeno della **starvation**.

### Filosofi a cena
Ci sono $5$ filosofi seduti su una tavola rotonda, tra ogni piatto c'è una bacchetta, per mangiare un filosofo ha bisogno di $2$ bacchette, se ne deduce che due filosofi vicini non potranno mai mangiare contemporaneamente.

Quando non mangiano, pensano, riassumendo, un filosofo può essere rappresentato come segue:
```
Filosofo(i) {
	while(1) {
		< pensa >
		
		< raccoglie le bacchette sx e dx > 
		< mangia >
		< deposita le bacchette sx e dx >
	}
}
```

Utilizziamo $5$ semafori per indicare le bacchette, essi saranno inizializzati tutti a $1$ per indicare che inizialmente sono posate sul tavolo (libere).
- `P`: raccoglie la bacchetta
- `V`: rilascia la bacchetta

```
semaphore bacchette[5]={1,1,1,1,1};

Filosofo(i) {
	while(1) {
		< pensa >
		
		P(bacchette[i]);
		P(bacchette[(i+1)%5]);
		< mangia >
		V(bacchette[i]);
		V(bacchette[(i+1)%5]);
	}
}
```

Potrebbe però verificarsi un **deadlock** (i thread si aspettano a vicenda per sempre) nel caso tutti i filosofi prendessero la bacchetta a sinistra in quanto rimarrebbero tutti in attesa della bacchetta destra.

##### Limitare il numero di posti
Utilizzando un numero di posti inferiore a $5$, una bacchetta sarebbe sempre libera nel tavolo, in questo modo se arriva un altro filosofo, dovrà accodarsi al tavolo.
```
semaphore bacchette[5]={1,1,1,1,1};
semaphore posti=4;

Filosofo(i) {
	while(1) {
		< pensa >
		
		P(posti);
		P(bacchette[i]);
		P(bacchette[(i+1)%5]);
		< mangia >
		V(bacchette[i]);
		V(bacchette[(i+1)%5]);
		V(posti);
	}
}
```

##### Raccolta atomica
Si può usare un mutex in più per garantire che le bacchette vengano raccolte da un filosofo alla volta.

Tuttavia questa soluzione sincronizza troppo in quanto un filosofo che è in attesa della bacchetta destra farà aspettare anche gli altri che possono già mangiare, riducendo il parallelismo.
```
semaphore bacchette[5]={1,1,1,1,1};
semaphore mutex=1;

Filosofo(i) {
	while(1) {
		< pensa >
		
		P(mutex);
		P(bacchette[i]);
		P(bacchette[(i+1)%5]);
		V(mutex);
		< mangia >
		V(bacchette[i]);
		V(bacchette[(i+1)%5]);
	}
}
```

##### Filosofo mancino
Forzando un filosofo a raccogliere per prima la bacchetta di destra si evita la situazione di _deadlock_.

Non è più possibile che tutti raccolgano la bacchetta di sinistra mettendosi in attesa su quella di destra, dato che almeno uno cercherà di raccogliere prima quella di destra.

Selezioniamo il quinto filosofo come mancino.
```
Filosofo(i) {
	while(1) {
		< pensa >
		
		if (i == 4) {
			  P(bacchette[0]);       // destra
			  P(bacchette[4]);       // sinistra
		} else {
			  P(bacchette[i]);       // sinistra
			  P(bacchette[(i+1)%5]); // destra
		}
		
		< mangia >
		
		// rilascia le bacchette
		// non importa l'ordine in quanto la V non è bloccante
		V(bacchette[i]);
		V(bacchette[(i+1)%5]);
	}
}
```

