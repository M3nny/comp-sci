### Filosofi a cena con monitor
Nei [[Semafori#Regolare l'accesso a risorse|semafori]] abbiamo visto come usarli sotto la forma di contatori, vediamo come risolvere il problema dei [[Problemi noti#Filosofi a cena|filosofi a cena]] utilizzando un monitor contatore che limita il numero di filosofi a tavola a $4$ (ce ne sarebbero $5$ nel problema).

```c
Filosofo(i) {
	while(1) {
		< pensa >
		
		tavola.siediti(); // attende una delle 4 sedie disponibili
		tavola.raccogli(i);
		
		< mangia >
		
		tavola.deposita(i);
		tavola.alzati(); // libera la sedia
	}
}
```

il monitor sarà implementato idealmente come segue:
```c
Monitor tavola {
	int sedie=4;
	condition sedia;
	...
	void siediti() {
		while(sedie==0)
			sedia.wait(); // attende una sedia libera
			
			// occupa una sedia
			sedie--;
		}
		
		void alzati() {
		sedie++; // libera una sedia
		sedia.notify(); // sblocca un thread in attesa di un sedia
	}
}
```

la procedura `siediti` in questo modo potrà essere invocata $4$ volte prima di diventare bloccante, inoltre lo stallo viene evitato.


### Lettori e scrittori con monitor
Vediamo ora come risolvere il problema dei [[Problemi noti#Lettori e scrittori|lettori e scrittori]]:
```c
Lettore {
	while(1) {
	...
	rw.ini_leggi();
	
	< legge i dati >
	
	rw.end_leggi();
	...
	}
}

Scrittore {
	while(1) {
	...
	rw.ini_scrivi();
	
	< modifica i dati >
	
	rw.end_scrivi();
	...
	}
}
```

Per realizzare il monitor `rw` dobbiamo sapere se c'è uno scrittore in sezione critica oppure il numero esatto di lettori in sezione critica.
>I lettori entrano se non c'è uno scrittore, lo scrittore entra se non c'è nessuno in sezione critica.

```c
Monitor rw {
	int n_lettori=0; // n. lettori in sezione critica
	boolean scrittore=false; // scrittore in sezione critica
	condition c; // coda di attesa
	
	void ini_leggi() {
		while(scrittore)
			c.wait(); // attende se c'è uno scrittore
		n_lettori++; // il lettore entra
	}
	
	void end_leggi() {
		n_lettori--; // il lettore esce
		if (n_lettori==0)
		  // l'ultimo lettore sblocca eventuali scrittori in attesa
		  c.notify();
	}
	
	void ini_scrivi() {
		while(scrittore || n_lettori > 0)
			// attende se c'è uno scrittore o qualche lettore
			c.wait();
		scrittore=true; // lo scrittore entra
	}
	
	void end_scrivi() {
		scrittore=false; // lo scrittore esce
		c.notifyAll(); // lo scrittore sblocca tutti i thread in attesa
	}
}
```

i monitor permettono di programmare la sincronizzazione tramite variabili senza preoccuparsi della mutua esclusione che viene garantita automaticamente.

In `end_scrivi()` usiamo `notifyAll()` sulla condition `c`, essa sblocca tutti i thread in coda (ovvero tutti i lettori), da notare che tutti i thread ri-verificheranno la condizione di attesa prima di proseguire.
>La `notifyAll()` affida allo scheduler la scelta del prossimo thread che entrerà in sezione critica evitando _starvation_.

Per **rispettare l'ordine di arrivo** dei thread è possibile passare l'id del thread alle funzioni del monitor, ed implementare una `queue` interna al monitor che tenga conto del loro ordine di arrivo:
```c
Monitor rw {
	...
	queue q;
	
	void ini_leggi(id) {
		q.add(id); // si accoda
		// attende se non e' il primo della coda
		// o se c'è uno scrittore
		while(q.top()!=id || scrittore)
			c.wait(); 
		q.remove(); // si toglie dalla coda (e' il primo!)
		n_lettori++; // il lettore entra
		c.notifyAll(); // notifica eventuali altri lettori in attesa
	}
	
	void end_leggi(id) {
		n_lettori--; // il lettore esce
		if (n_lettori==0)
			c.notifyAll(); // l'ultimo lettore sblocca tutti i thread
	}
	
	void ini_scrivi(id) {
		q.add(id); // si accoda
		// attende se non e' il primo della coda
		// o se c'è uno scrittore o qualche lettore
		while(q.top()!=id || scrittore || n_lettori > 0)
			c.wait(); 
		q.remove(); // si toglie dalla coda (e' il primo!)
		scrittore=true; // lo scrittore entra
	}
		
	void end_scrivi(id) {
		scrittore=false; // lo scrittore esce
		// lo scrittore sblocca tutti i thread in attesa
		c.notifyAll();
	}
}
```

Oltre alla coda abbiamo:
- Aggiunto `notifyAll()` alla fine di `ini_leggi` per sbloccare altri lettori in attesa che potrebbero essersi ribloccati in quanto non erano i primi della coda
- Sostituito la `notify()` con `notifyAll()` in `end_legg()` in quanto i thread sulla coda potrebbero non essere nello stesso ordine dei thread sulla condition, per questo li sblocchiamo tutti e lasciamo che loro stessi si riblocchino.
	Se sbloccassimo un solo thread ed esso non fosse il primo della coda, si ribloccherebbe e nessun altro thread verrebbe eseguito

