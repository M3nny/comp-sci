Un dizionario rappresenta il concetto matematico di una **relazione univoca**$R:D\to C$ fra gli elementi di un insieme $D$ (dominio) e gli elementi di un insieme $C$ (codominio).
Gli elementi del dominio sono detti **chiavi** e gli elementi del codominio sono detti **valori**.

- **Dati**: un insieme di coppie (chiave-valore)
- **Operazioni**:
	- `search(Dizionario S, Chiave K) -> elem or {NIL}`
		**Post**: restituisce il valore associato alla chiave $K$ se presente in $S$, altrimenti restituisce NIL.
	- `insert(Dizionario S, Elem v, Chiave K)`
		**Post**: associa il valore $v$ alla chiave $K$ 
	- `delete(Dizionario S, Chiave K)`
		**Pre**: $K$ deve essere presente in $S$
		**Post**: cancella da $S$ la coppia con chiave $K$

---
### Implementazione con array ordinati
In questa implementazione vedremo un array $A$ contenente $n$ record formati da due campi **(key, info)**, i quali saranno ordinati in base a _key_, per poter così effettuare una ricerca binaria.
La dimensione dell'array è data da `A.length`, e lo spazio richiesto per memorizzare un dizionario così implementato è:
$$S(n)=\Theta(n)$$
dato che cresce linearmente con il numero di elementi al suo interno.
#### Search
```
search(Dizionario A, Chiave K)
	i = search_index(A, k, 1, A.length) // 1 sarebbe 0
	if i == -1
		return NIL
	else
		return A[i].info
```

```
search_index(Dizionario A, Key, K, int p, int r) -> int
	if p > r // quando un array è vuoto
		return -1
	else
		med = (p+r)/2
		if A[med].Key > K
			return search_index(A, K, p, med-1)
		else
			return search_index(A, K, med+1, r)
```

La funzione `search` è semplicemente un wrapper di `search_index`, la quale è una funzione _divide et impera_ dove i parametri `p` ed `r` sono rispettivamente inizio e fine di dove cercare.
##### Complessità
$$T(n)=\begin{cases}\Theta(1)&\text{se }n=0\\T(\frac{n}{2})+\Theta(1)&\text{se }n>0\end{cases}$$
La ricorrenza $T(\frac{n}{2})$ corrisponde alle chiamate ricorsive da eseguire nel caso la chiave non fosse ancora trovata, mentre $\Theta(1)$ corrisponde alle operazioni costanti come i controlli, return e assegnamenti.

Posso applicare il teorema master:
$$a=1\quad b=2\quad d=\log_21=0\quad f(n)=1\quad g(n)=n^0=1$$
siamo nel secondo caso quindi:
$$T(n)=\Theta(n^d\log n)=\Theta(n^0\log n)=\Theta(\log n)$$
La complessità di `search()` si trova sommando le operazioni di tempo costante, le quali però non modificano la complessità generale, per cui anche questa funzione sarà: $T(n)=\Theta(\log n)$.
#### Insert
```
insert(Dizionario A, Info v, Key K)
	i = 1
	while i <= A.length and A[i].Key < K
		i = i + 1
	if i <= A.length and A[i].Key == K // se ho trovato la chiave
		A[i].info = v
	else // aggiungo la coppia chiave-valore
		reallocate(A, A.length + 1)
		A.length = A.length + 1
		for j = A.length down to i + 1
			A[j] = A[j - 1]
		A[i].Key = K
		A[i].Info = v
```
Aggiorna la chiave se presente, altrimenti aggiunge una nuova coppia chiave-valore.
Nel for, dopo aver allocato un posto in più in memoria eseguo lo shift di tutti gli elementi a destra dell'elemento appena minore di `K` , quando arrivo nella posizione subito dopo il valore appena minore di `K`, lo sovrascrivo mettendo la nuova coppia chiave valore.
##### Complessità
L'algoritmo non essendo ricorsivo permette di rappresentare la propria complessità tramite la somma delle complessità delle operazioni che lo compongono.
- Il `while` viene eseguito $i$ volte ed il suo corpo $d$ volte, per un costo totale di $i\cdot d$
- La `reallocate()` ha un costo di $O(n)$
- Il `for` viene eseguito $(n+1)-(i+1)+1=n-i+1$ volte ed il suo corpo $d$ volte, per un costo totale di $(n-i+1)\cdot d$
- Le altre operazioni hanno complessità $\Theta(1)$
$$\begin{flalign}
T(n)&=\\
&=\Theta(1)+i\cdot d+O(n)+(n-i+1)\cdot d\\
&= O(n)
\end{flalign}$$
Ovviamente con $O(n)$ stiamo tenendo conto del caso peggiore, nel caso la chiave si trovasse subito allora il tempo sarebbe molto minore.
#### Delete
```
delete(Dizionario A, Key K)
	i = search_index(A, K, 1, A.length)
	for j = i to A.length - 1
		A[j] = A[j + 1]
	reallocate(A, A.length - 1)
	A.length = A.length - 1
```
Trovo l'elemento da cancellare (esiste per precondizione), shifto a sinistra dalla fine dell'array fino all'elemento (sovrascrivendolo quindi), ridimensiono l'array togliendo l'ultimo elemento il quale è stato precedentemente scritto nella cella a lui precedente.
##### Complessità
Non è ricorsivo, quindi basta sommare le complessità delle operazioni.
- `search_index()` ha costo $\Theta(\log n)$ come visto precedentemente
- Il `for` viene eseguito $(n-1)-i+1=n-i$ volte, il corpo ha costo $d$, per un costo totale di $(n-i)\cdot d$
- `reallocate()` ha costo $O(n)$
$$\begin{flalign}
T(n)&=\\
&=\Theta(\log n)+(n-1)\cdot d+O(n)\\
&= O(n)
\end{flalign}
$$
>[!Tip] Approfondimento su Reallocate()
>Questa funzione avviene con la tecnica del **raddoppiamento e dimezzamento**, si mantiene un array di dimensione $h$, dove per ogni $n>0$ $h$ soddisfa il seguente invariante: $n\leq h\leq 4n$.
>Le prime celle dell'array contengono gli elementi della mia collezione, nel nostro caso il dizionario, mentre il contenuto delle altre è indefinito,
>- Inizialmente quando $n=0$ poniamo $h=1$
>- Quando $n$ supera $h$, l'array viene riallocato raddoppiando la dimensione ($h=2h$)
>- Ogni volta che $n$ scende a $\frac{h}{4}$, l'array viene riallocato dimezzando la dimensione ($h=\frac{h}{2}$)
>Lo spazio occupato dall'algoritmo sarà:
>$$S(n)=\Theta(h)=\Theta(n)$$

---
## Analisi ammortizzata
L'analisi ammortizzata è l'**analisi del costo medio**, non di una singola istruzione, ma di un blocco di $m$ istruzioni su una struttura dati.
Eseguiamo questo tipo di analisi perchè in casi come l'`insert()` visto precedentemente non deve sempre riallocare la lunghezza dell'array, molte volte troverà anche la chiave già pronta per modificarne il valore.

Assumiamo di partire da un vettore di dimensione $1$ su cui vogliamo eseguire $n$ `insert()`.
Sia $C_i$ il costo dell'i-esimo inserimento:
$$C_i=\begin{cases}i&\text{se }\exists k:i=2^k+1\\1&\text{altrimenti}\end{cases}$$
Rientra nel primo caso $C_i$ quando lo spazio precedentemente allocato dovrà essere raddoppiato.
Indicando con $C(n)$ il costo di $n$ inserimenti e [[Le sommatorie#Scambio degli indici|risolvendo le sommatorie]], otteniamo:
$$\begin{flalign}
C(n) &=\sum_{i=1}^{k}C_{i}=n\text{ (inserimenti puri) }+\sum_{k=0}^{\log_{2}n}2^{k}\text{ (copiatura)}\\
&=n+\frac{2^{\log_{2}n+1}-1}{2-1}=n+2n-1\leq 3n
\end{flalign}
$$
Quindi $C(n)\leq 3n$.
**Costo ammortizzato**: $\frac{C(n)}{n}\leq\frac{3n}{n}=3=\Theta(1)$

---
### Implementazione con liste doppiamente concatenate
In questa implementazione useremo una collezione $L$ di $n$ record contenenti: (**Key, Info, next, prev**), dove **prev** e **next** sono rispettivamente puntatori al record precedente e successivo.
Un attributo `L.head` punta al primo elemento della lista, se la lista è vuota, allora `L.head == NIL`.
Anche in questo caso lo spazio per memorizzare un dizionario così implementato è:
$$S(n)=\Theta(n)$$
#### Search
```
search(Dizionario L, Key K)
	x = L.head
	while x != NIL and x.Key != K
		x = x.next
	if x != NIL
		return x.Info
	else
		return NIL
```
Scorro la lista finchè non trovo `K`, se non è presente ritorno `NIL`.
##### Complessità
Nel caso peggiore deve scorrere tutta lista, quindi ha complessità lineare.
$$T(n)=O(n)$$
##### Analisi della correttezza dell'algoritmo
Per verificare che questo algoritmo sia corretto, bisogna che alla fine del ciclo `while`, `x` sia la chiave cercata oppure `NIL`.
Dobbiamo quindi verificare la correttezza del ciclo.

>[!Invariante del ciclo]
>Un **invariante** è un'asserzione che deve essere vera prima e dopo ogni iterazione del ciclo.
>Per un invariante si deve dimostrare:
>- **Inizializzazione**: è vero dalla prima iterazione
>- **Conservazione**: se è vero prima di un'iterazione , allora rimane vero anche prima dell'iterazione successiva
>	$$\text{INV}\land\text{Guardia}\implies\text{INV[dopo iterazione]}$$
>- **Conclusione**: quando il ciclo termina, l'invariante fornisce un utile proprietà che aiuta a dimostrare che l'algoritmo è corretto.
>	$$\text{INV}\land\neg\text{Guardia}\implies\text{Asserzione finale}$$
>- **Funzione di terminazione**: è una funzione a valori naturali che decresce dopo ogni iterazione. Ad un certo punto arriva allo $0$ dove il ciclo necessariamente termina.

La funzione nel nostro caso è il numero di elementi non ancora visitati, e $\text{INV}\equiv$ gli elementi da `L.head` ad `x` escluso hanno chiave diversa da `K`.

- **Inizializzazione**: `x` e `L.head` sono lo stesso elemento, quindi non hanno elementi in mezzo che possono essere uguali a `K`.
- **Conservazione**: 
	Per ipotesi, sappiamo che:
		1. Invariante vero: gli elementi da `L.head` ad `x` escluso hanno chiave diversa da `K`
		2. Guardia vera: `x != NIL and x.Key != K`
	
	Per ipotesi (1.) e (2.) `x` punta ad un elemento con chiave diversa da `K`, dimostrando quindi che tutti gli elementi da `L.head` a `x` _compreso_ hanno chiave diversa da `K`.
- **Conclusione**: 
	Il ciclo può terminare in due modi:
	1. `x == NIL`: tutta la lista è stata visitata mantenendo l'invariante vero, per cui non ci sono chiavi uguali a `K`
	2. `x.Key == K`: dato che l'invariante dice che `K` non è presente prima di `x`, `x` sarà dunque la _prima_ occorrenza della chiave `K`

Abbiamo così dimostrato la correttezza dell'algoritmo di ricerca.
#### Insert
```
insert(Dizionario L, Info v, Key K)
	creo un record p
	p.next = L.head
	if L.head != NIL
		L.head.prev = p
	p.prev = NIL
	L.head = p
```
Questa volta eseguo una **prepend()**, da notare che l'algoritmo non va a cercare se esiste una chiave con lo stesso valore, per poi modificarlo.
##### Complessità
L'algoritmo consiste in sole operazioni di assegnamento, per cui la complessità è costante.
$$T(n)=\Theta(1)$$
#### Delete
```
delete(Dizionario L, Key K)
	x = L.head
	while x != NIL
		if x.Key == K
			if x.next != NIL
				x.next.prev = x.prev
			if x.prev != NIL
				x.prev.next = x.next
			else
				L.head = x.next
			temp = x
			x = x.next
			rimuovi temp
		else
			x = x.next
```
Per compensare il fatto che `insert()` aggiunge una nuova coppia chiave-valore senza verificare se esiste già un elemento con la chiave passata come argomento, con questo algoritmo eliminiamo tutte le occorrenze della chiave `K`.
##### Complessità
L'algoritmo consiste in semplici assegnamenti, però il fatto che l'ultima occorrenza della chiave `K` possa essere alla fine, rende la complessità lineare, dato che bisognerebbe scorrere tutta la lista.
$$T(n)=\Theta(n)$$
