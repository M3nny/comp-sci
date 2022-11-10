## Moltiplicazione
##### Riflessioni sul metodo "carta e penna"
Per una moltiplicazione in base $10$ procediamo come segue:
1. Considerare le cifre da moltiplicare da destra a sinistra una alla volta
2. Moltiplicare il moltiplicando per la singola cifra del moltiplicatore
3. Shiftare il prodotto intermedio di una cifra alla volta verso sinistra
4. Sommo tutti i prodotti intermedi.

Mentre per la moltiplicazione in base $2$ proseguo nello stesso modo, solo che ci sono alcune osservazioni da fare:
- Il numero di cifre prodotto è più grande rispetto al numero di cifre di ciascuno dei due numeri moltiplicati;
- Ignorando i bit di segno si avrà se i due fattori hanno $n$ bit ciascuno, un prodotto di $2n$ bit;
- Per rappresentare il risultato in generale abbiamo bisogno del doppio dei bit dei fattori;
- Quando moltiplichiamo $1$ per il moltiplicando riscriviamo il numero, quando lo moltiplichiamo per $0$, mettiamo tutto a $0$.

### Algoritmo di moltiplicazione su 32 bit
1. Controllo se la cifra del **moltiplicatore** è $0$ o $1$:
	- Se è $1$ aggiungo il _moltiplicando_ nel registro del prodotto e lo sommerò agli altri moltiplicandi li presenti.
2. **Shift a sinistra** del registro del _moltiplicando_ di 1 bit
3. **Shift a destra** del registro del **moltiplicatore** di 1 bit
4. Controllo se è la 32esima volta che itero
	- Vero: Finito
	- Falso: Vado al punto 1.
![[Moltiplicazione.png|400]]

Questo tipo di algoritmo però, utilizza un registro di 64 bit per il _moltiplicando_, questo perchè con lo shift a sinistra potrebbero essere persi bit altrimenti, di conseguenza serve una ALU a 64 bit per la somma.

### Ottimizzazione della moltiplicazione
1. Controllo se la cifra del **moltiplicatore** è $0$ o $1$:
	- Se è $1$ sommo il _moltiplicando_ alla metà sinistra (32 bit più significativi) del registro del prodotto.
2. **Shift a destra** del registro del prodotto di 1 bit
3. **Shift a destra** del registro del **moltiplicatore** di 1 bit
4. Controllo se è la 32esima volta che itero
	- Vero: Finito
	- Falso: Vado al punto 1.
![[Moltiplicazione ottimizzata.png|400]]
In questo modo sarà il registro del prodotto (sempre 64 bit) a shiftare a destra mentre il _moltiplicando_ resterà fisso, sono ora necessari solo 32 bit così da poter usare un'ALU a 32 bit.

### Evitare lo spreco del registro del prodotto
L'algoritmo ottimizzato spreca inizialmente la seconda metà del registro del prodotto (32 bit) che sarebbero giusti per memorizzare il **moltiplicatore**.
Inoltre iterando mentre lo spazio inutilizzato del registro del prodotto si riempie, il registro del **moltiplicatore** diminuisce in modo tale che potrebbe continuare a starci dentro al registro del prodotto.

Vediamo ora come eliminare il registro del **moltiplicatore** e metterlo dentro a quello del prodotto:
1. Controllo se la cifra del ==prodotto== è $0$ o $1$:
	- Se è $1$ sommo il _moltiplicando_ alla metà sinistra (32 bit più significativi) del registro del prodotto.
2. **Shift a destra** del registro del prodotto di 1 bit
3. Controllo se è la 32esima volta che itero
	- Vero: Finito
	- Falso: Vado al punto 1.

#### Considerazioni sul segno della moltiplicazione
Il modo più semplice per gestire il segno è quello di convertire i due fattori in numeri positivi per poi eseguire la moltiplicazione e stabilire il segno del prodotto sulla base del segno dei due fattori.

>[!Attention]
>Gli algoritmi visti si limitano a 31 iterazioni, lasciano quindi il segno fuori dal calcolo.

---
## Divisione
##### Riflessioni sul metodo "carta e penna"
Per una divisione in base $10$ procediamo come segue:
1. Considerare i gruppi di cifre del _divedendo_
2. Vedere quante volte il **divisore** ci sta nel gruppo di cifre del _dividendo_
3. Scrivere il quoziente parziale nel quoziente totale
4. Sottrarre il multiplo del **divisore** dal _dividendo_
5. La divisione finisce quando il resto è minore del **divisore** o è uguale a 0.


Mentre per la divisione in base $2$ proseguo nello stesso modo, solo che ci sono alcune osservazioni da fare:
- Il **divisore** ci sta 0 o 1 volta nel _dividendo_

### Algoritmo di divisione su 32 bit
- Il **divisore** è memorizzato sulla parte più significativa di un registro
- Il **dividendo** ed il **resto** sono memorizzati nello stesso registro, il resto viene inizializzato con il valore del dividendo
- Il **quoziente** è memorizzato su un registro a parte

1. Resto - **divisore** e metto il risultato nel registro del resto
2. Controllo se il resto è maggiore o minore di 0:
	- maggiore: **Shifto il quoziente a sinistra** e metto il valore meno significativo a 1
	- minore: **Shifto a sinistra il quoziente** e metto il valore meno significativo a 0, poi ripristino il valore di resto precedente.
3. Shifto a destra il registro del divisore
4. Controllo se è la 33esima volta che itero
	- Vero: Finito
	- Falso: Vado al punto 1.

![[Divisione.png|400]]
### Ottimizzazioni dell'algoritmo di divisione
Analogamente alle migliorie della moltiplicazione, anche in questo caso si passa da una ALU a 64 bit ad una ALU a 32 bit.
- Esiste un'atra ottimizzazione dove il quoziente viene memorizzato nella parte bassa del resto, eliminando così il registro del quoziente.

#### Considerazioni sul segno del quoziente e del resto
Il modo più semplice per gestire il segno è quello di rendere entrambi gli operandi positivi e stabilire il segno del quoziente in base ai segni originali dei due operandi.

Per il resto basta stabilirne il segno tramite la regola: il dividendo e resto devono avere lo stesso segno.