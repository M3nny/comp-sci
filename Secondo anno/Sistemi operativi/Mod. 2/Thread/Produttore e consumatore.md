Il modello a scambio di messaggi, lo schema produttore/consumatore utilizza una **send asincrona** (bloccante quando il buffer è pieno) ed una **receive sincrona**, ovvero:
- Il consumatore attende se non ci sono dati da consumare
- Il produttore attende se non c'è spazio nel buffer

### Memoria condivisa
Il modello a **memoria condivisa** viene usato in molti contesti, tra cui:
- Calcolo parallelo
- Applicazioni modulari
- Quando è utile condividere informazioni tra processi e thread

Nel [[Processi#Process Control Block|PCB]] di un processo troviamo la **memoria** come risorsa allocata, ed un thread (distinto da un ID) in quanto **parte di esecuzione** di un processo eredita dal processo le risorse, per cui normalmente condivide anche la memoria con gli altri thread del processo.

### Produttore e consumatore con memoria condivisa
Consideriamo di usare un ipotetico array "infinito" come canale di comunicazione tra due thread.

**Problema**: il consumatore legga memoria sporca nel caso legga più velocemente di quanto viene prodotto.
**Soluzione**: far ciclare a vuoto il consumatore (busy-waiting) finchè non ci sono elementi da consumare.

Sebbene possa funzionare, è una soluzione irrealistica a causa dell'array infinito, potremmo sostituirlo con un buffer circolare.

**Problema**: se il produttore è più veloce del consumatore, una volta raggiunta la fine del buffer circolare, comincerà a sovrascrivere i dati più vecchi, che potenzialmente potrebbero non essere stati letti.
**Soluzione**: applicare il busy-waiting anche sul consumatore
	1. Spreca una cella di memoria per distinguere buffer pieno da vuoto
	2. Spreca tempo nel busy-waiting
	3. Non scala con più attori

Per risolvere il primo punto si può usare un contatore condiviso inizializzato a $0$:

```c
data_t buffer[MAX]; // un buffer di dimensione MAX
int inserisci=0, preleva=0; // indici per l'accesso al buffer
int contatore=0; // contatore per le condizioni di attesa
 
Produttore() {
	while(1) {
	    /* produce un elemento d */
	    while (contatore == MAX) {}; // buffer pieno, attendo
	    buffer[inserisci] = d;
	    inserisci=(inserisci+1) % MAX // il buffer è circolare
	    contatore++; // aggiorno il contatore
	}
}
 
Consumatore() {
	while(1) {
	    while (contatore == 0) {}; // buffer vuoto, attendo
	    d = buffer[preleva];
	    preleva=(preleva+1) % MAX // il buffer è circolare
	    contatore--; // aggiorno il contatore
	    /* consuma d */
	}
}
```

**Problema**: i thread aggiornano la variabile `contatore` contemporaneamente, il che può creare interferenze che compromettono l'integrità dei dati.

Indicando `r1` e `r2` come registri, possiamo immaginare l'**incremento** come:
1. a) `r1 = contatore` (lettura da memoria a registro)
2. a) `r1 = r1 + 1` (incremento del registro)
3. a) `contatore = r1` (riscrittura del registro in memoria)

ed il **decremento** come:
1. b) `r2 = contatore` (lettura da memoria a registro)
2. b) `r2 = r2 - 1` (decremento del registro)
3. b) `contatore = r2` (riscrittura del registro in memoria)

Otteniamo risultati diversi a seconda di come queste istruzioni vengono schedulate, ad esempio partendo da `contatore = 5`:
- 1a, 1b, 2b, 3b, 2a, 3a $\rightarrow$ `contatore = 6`
- 1b, 1a, 2a, 3a, 2b, 3b $\rightarrow$ `contatore = 4`
- 1a, 2a, 3a, 1b, 2b, 3b $\rightarrow$ `contatore = 5`

Abbiamo una **race condition**: <u>l'output dipende dalla temporizzazione degli eventi</u>.
Accade quando c'è competizione per la stessa risorsa.

Serve un meccanismo per sincronizzare i thread in modo generale e sistematico.
