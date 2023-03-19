La memoria cache si trova tra la CPU e la RAM, ci riferiamo ad essa come sistema che sfrutta la località degli accessi.

## Cache ad accesso diretto
La funzione di mapping è la seguente: `<address> mod <# blocchi cache>.

Se **#** è il numero di blocchi di cache (potenza di 2) l'operazione modulo è equivalente a prendere i primi $\log_2$ <# blocchi cache> bits dall'indirizzo.

#### Shifting
- **Moltiplicare** per $k=2^n$ equivale a $n$ shift a **sinistra**
- **Dividere** per $k=2^n$ equivale a $n$ shift a **destra**

Gli indirizzi con gli stessi bit meno significativi finiscono nello stesso **cache block**, <u>indirizzamento al blocco invece che al bite</u>:
1. **Block address**: $\frac{\text{address}}{\text{block size}}$
2. **Block index**: $\text{block address}$ % #$\text{cache blocks}$

In pratica se la cache ha _block size_ pari a $1$, e $8$  blocchi, allora dalla memoria indirizziamo al blocco gli indirizzi con gli ultimi $3$ ($8=2^3$) bit significativi con un offset pari a $0$ (avendo _block size_ 1:  $\log_21 = 0$).

Vediamo 2 esempi con lo stesso numero di blocchi di cache, ma che si differenziano nella grandezza di quest'ultimi.

Osserviamo che nel secondo esempio sono raggruppati gli indirizzi che hanno i penultimi $3$ bit significativi, questo è dovuto ad un offset pari a $1$ dato da: $\log_22 = 1$, quindi in questo caso più blocchi di memoria finiscono nella stessa locazione nella cache.

![[Cache accesso diretto.svg]]
### Tag
Per distinguere i valori che finiscono nello stesso blocco di cache **memorizziamo** _i bit più significativi_ del **block address** insieme ai dati, chiamiamo questo tipo di dato **tag**.
- Tag = $\frac{\text{block address}}{\text{n cache blocks}}$

### Valid bit
Usiamo un **valid bit** (inizializzato a 0) per capire se le informazioni contenute nei tag hanno effettivamente significato (e.g. appena avviata la CPU ha la cache vuota con tag privi di significato)
- 0: dati _non_ validi
- 1: dati _validi_

>[!Example]
>Assumiamo una cache con:
>- 64 blocchi
>- Blocco da 16 B
>
>1. Se l'indirizzo è di 27 bit come è composto?
>2. Qual è l'indice del blocco che contiene il byte all'indirizzo 1201?
>
>L'**index** è dato da $\log_264=6$, mentre l'**offset** è dato da $\log_216=4$, otteniamo il **tag** sottraendo alla sua dimensione la dimensione dell'indice e dell'offset: $27-6-4=17$.
>
>Per trovare l'indice del blocco che contiene il byte all'indirizzo 1201 procediamo come segue:
>1. **Indirizzo blocco**: $1201/16=75$
>2. **Offset**: $1201\%16=1$
>3. **Index**: $75\%64=11\space(\text{dodicesimo blocco})$
>4. **Tag**: $75/64=1$
>
>![[Esercizio blocco cache.png]]

### Dimensione ottimale del blocco
Se aumento il _block size_ sfrutto di più la località spaziale e può diminuire il _miss rate_, ma con esso aumenterà sicuramente il _miss penalty_, il costo di un miss è dato da:
- costo miss: cicli per attivare DRAM + cicli spesi per copiare i dati (può essere abbassato organizzando la memoria in modo da trasferire blocchi più grandi).

Conclusione: è meglio aumentare il _block size_ dato che raddoppiandolo non raddoppiano i miss.
Caricare un blocco grande senza usarlo completamente è uno spreco e genera **conflitti** con altri blocchi utilizzati.

---
## Conflitti
Se il blocco da portare in memoria viene scritto sopra un altro blocco già presente in cache possono avvenire due casi:
1. Se il blocco presente in cache è stato **usato solo in lettura** possiamo rimpiazzarlo (è possibile trovarlo su un livello più basso di memoria).
2. Se **è stato scritto** bisogna stabilire **politiche di coerenza tra livelli di memoria** essendo che rappresenta una copia dei dati al livello inferiore.

### Politiche di coerenza
- **Write through**: ogni scrittura nella cache implica anche una scrittura al livello inferiore.
	- _Vantaggi_: Il blocco può essere rimpiazzato senza problemi
	- _Svantaggi_: Le scritture sono molto lente al livello inferiore e consuma centinaia di cicli di clock.
	- _Possibile soluzione_: scriviamo contemporaneamente i dati anche in un write buffer, verranno poi scritti in modo asincrono nella memoria inferiore. Se la frequenza con cui vengono generate le write è minore di quella con cui le si completa il buffer non aiuta.

- **Write back**: Solo quando un blocco deve essere rimpiazzato in cache viene scritto nella memoria inferiore.
	- _Vantaggi_: In assenza di conflitti non c'è overhead.
	- _Svantaggi_: La sostituzione di un blocco in conflitto è più lenta e complessa perchè richiede la scrittura del blocco al livello inferiore.

### Hit vs Miss
- **Read-hit**: avviene dopo `lw` o `fetch`, è l'accesso più veloce alla memoria.
- **Read-miss**: il controllo mette in stallo la CPU finchè non viene portato il blocco dal livello inferiore alla cache e viene letto. Possono avvenire due situazioni:
	1. Viene rifatto il `fetch` dell'istruzione
	2. Viene completato l'accesso al dato dell'istruzione (e.g. `lw`)

- **Write-hit**: avviene dopo una `sw`, è dipendente dalla politica di coerenza:
	1. _Write through_: i dati vengono scritti in cache e al livello inferiore.
	2. _Write back_: i dati vengono scritti solo in cache, segnalando che il blocco è stato modificato attraverso un dirty bit associato al blocco.
- **Write-miss**: il controllo mette in stallo la CPU, quello che succede dopo è dipendente dalla politica di coerenza:
	1. _Write back_: viene portato il blocco dal livello inferiore alla cache (write allocate) e poi viene completata l'istruzione di store in cache.
	2. _Write through_: la scrittura avviene direttamente al livello inferiore.

