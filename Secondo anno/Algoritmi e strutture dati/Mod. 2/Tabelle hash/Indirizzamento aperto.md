Questo metodo non necessità di strutture dati ausiliarie, tutti gli elementi sono memorizzati nella tabella hash stessa, ogni cella contiene un elemento dell'insieme dinamico oppure `NIL`.

Per cercare un elemento con chiave $k$:
1. Calcolo $h(k)$ ed esamino il contenuto (**ispezione**)
2. Se la cella $h(k)$ contiene $k$ o `NIL`, la ricerca ha _successo_
3. La cella $h(k)$ potrebbe essere diversa da $k$ o `NIL`, allora calcoliamo l'indice di un'altra cella in base alla chiave $k$ ed al numero di ispezioni eseguite finora
4. Si continua la scansione della tabella finchè non si trova $k$ o `NIL` oppure ho eseguito $m$ ispezioni senza successo (_insuccesso_)

La funzione hash diventa:
$$h:U\times\underbrace{\{0,...,m-1\}}_\text{Numero di ispezione}\rightarrow\{0,...,m-1\}$$
$h(k,i)$ rappresenta la posizione della chiave $k$ dopo $i$ ispezioni fallite.

Si richiede che per ogni chiave, la sequenza di ispezioni: $<h(k,0),...,h(k,m-1)>$ sia una permutazione di $<0,...,m-1>$ in modo che ogni posizione della tabella hash possa essere considerata come possibile cella in cui inserire una nuova chiave mentre la tabella si riempie.

**Ipotesi**: per semplicità si assuma che gli elementi della tabella hash siano chiavi senza dati satellite, ovvero che contengano solo la chiave.

### Inserimento
- **Post**: restituisce l'indice della tabella dove ha memorizzato la chiave $k$ oppure segnala un errore se la tabella è piena
```
hashInsert(T, k)
	i = 0
	found = false
	repeat
		j = h(k, i)
		if T[j] == NIL or T[j] == DELETED
			T[j] = k
			found = true
		else
			i++
	until found or i == m
	if found
		return j
	else
		error "Overflow della tabella hash"
```

### Ricerca
- **Post**: restituisce $j$ se la cella $j$ contiene $k$, oppure restituisce `NIL` se la chiave $k$ si trova nella tabella $T$
```
hashSearch(T, k)
	i = 0
	found = false
	repeat
		j = h(k, i)
		if T[j] == k
			found = true
		else
			i++
	until found or T[j] == NIL or i== m
	if found
		return j
	else
		return NIL
```

### Cancellazione
Considerando la seguente tabella hash:
![[Cancellazione indirizzamento aperto.svg]]
Vogliamo inserire la chiave $12$:
1. Al primo tentativo $h(12,0) = 4$, si verifica una collisione, al secondo tentativo $h(12,1)=1$, si verifica una collisione, al terzo tentativo $h(12,2)=3$, la cella è libera, quindi l'elemento con chiave $12$ viene inserito in posizione $3$
2. Vogliamo eliminare l'elemento con chiave $101$, ora in posizione $1$ sarà presente $\text{NIL}$, se volessimo ricercare l'elemento avente chiave $12$ dovremmo compiere tutte le ispezioni fatte per l'inserimento, quindi: $h(12,0)=4$, $h(12,1)=1$, ma in posizione $1$ troviamo il valore $\text{NIL}$

Nella nostra implementazione $\text{NIL}$ segnala che l'elemento con chiave $12$ non è presente in $T$, per risolvere questo problema utilizzeremo il valore arbitrario $\text{DELETED}$ che ci consente di proseguire l'ispezione anche se un elemento "facente parte del percorso di inserimento" è stato eliminato.

Per questo motivo `hashInsert` inserirà anche nelle celle $\text{DELETED}$.

**Svantaggio**: con l'impiego di $\text{DELETED}$, il tempo di ricerca non dipende più dal fattore di carico $\alpha =\frac{n}{m}$, portando ad un calo di prestazioni, se sappiamo che delle chiavi dovranno essere cancellate è meglio la strategia del [[Concatenamento|concatenamento]].

## Metodi di scansione/ispezione
Nella realtà è difficile ottenere un _hashing uniforme_ ad ogni iterazione di collisione, per questo nella realtà sono usate delle approssimazioni di questa tecnica.

### Ispezione lineare
Viene usata una **funzione hash ausiliaria**:
$$h(k,i)=(h'(k)+i)\text{ mod } m$$
![[Ispezione lineare.svg]]
Ispeziona $T$ sequenzialmente a partire da $T[h'(k)]$, quando raggiunge $m-1$ riparte da $0$ per arrivare a $T[h'(k)-1]$.

>[!Example]
>Vogliamo inserire le seguenti chiavi: $69,4,31,43$ in una tabella con $m=13$ posizioni, le funzioni di hashing sono definite di seguito:
>- $h_1(k)=k\text{ mod }m$
>- $h(k,i)=(h'(k)+i)\text{ mod }m$
>
>1. $h(69,0)=(h'(69)+0)\text{ mod }13=4\text{ mod }13=4$
>	- Non c'è collisione: $T[4]=69$
>2. $h(4,0)=(h'(4)+0)\text{ mod }13=4\text{ mod }13=4$
>	- $h(4,1)=(h'(4)+1)\text{ mod }13=5\text{ mod }13=5$
>	- Non c'è collisione: $T[5]=4$
>3. $h(31,0)=(h'(31)+0)\text{ mod }13=5\text{ mod }13=5$
>	- $h(31,1)=(h'(31)+1)\text{ mod }13=6\text{ mod }13=6$
>	- Non c'è collisione: $T[6]=31$
>4. $h(43,0)=(h'(43)+0)\text{ mod }13=4\text{ mod }13=4$
>	- $h(43,1)=(h'(43)+1)\text{ mod }13=5\text{ mod }13=5$
>	- $h(43,2)=(h'(43)+2)\text{ mod }13=6\text{ mod }13=6$
>	- $h(43,3)=(h'(43)+3)\text{ mod }13=7\text{ mod }13=7$
>	- Non c'è collisione: $T[7]=43$


**Vantaggio**: facile da implementare

**Svantaggio**: si vanno  a formare file di celle adiacenti occupate che aumentano il tempo delle operazioni (e.g. inserire il quarto elemento nell'esempio precedente è stato molto più complesso del primo).

### Ispezione quadratica
Una variante dell'ispezione lineare è la seguente:
$$h(k,i)=(h'(k)+c_1\cdot i+c_2\cdot i^2)\text{ mod }m$$
- $h'(k)$ è una funzione hash ausiliaria
- $c_1,c_2\in\mathbb{R}^+\land c_1,c_2\neq 0$
- $i\in[0,m-1]$.

Ad esempio possiamo scegliere: $c_1=c_2=\frac{1}{2}$, $m=2^p$ ($m$ è una potenza di $2$).

Comunque l'hashing quadratico soffre dello stesso problema di quello lineare, ovvero se due chiavi vengono mappate nella stessa cella, allora le due chiavi generano la stessa sequenza di ispezioni (formazione di celle adiacenti occupate).

Anche in questo caso la prima posizione determina l'intera sequenza di ispezioni.

### Doppio hashing
$$h(k,i)=(h_1(k)+i\cdot h_2(k))\text{ mod }m$$
- $h_1$ viene usata per determinare il punto di partenza (non cambia mai in funzione di $i$)
- $h_2$ serve per determinare il passo delle ispezioni
- $i\in[0,m-1]$

>[!Example]
>Vogliamo inserire le seguenti chiavi: $69,4,31,43$ in una tabella con $m=13$ posizioni, le funzioni di hashing sono definite di seguito:
>- $h_1(k)=k\text{ mod }m$
>- $h(k,i)=(h_1(k)+i\cdot h_2(k))\text{ mod }m$
>
>1. $h(69,0)=(h_1(69)+0)\text{ mod }13=4\text{ mod }13=4$
>	- Non c'è collisione: $T[4]=69$
>2. $h(4,0)=(h_1(4)+0)\text{ mod }13=4\text{ mod }13=4$
>	- $h(4,1)=(h_1(4)+h_2(4))\text{ mod }13=9\text{ mod }13=9$
>	- Non c'è collisione: $T[9]=4$
>3. $h(31,0)=(h_1(31)+0)\text{ mod }13=5\text{ mod }13=5$
>	- Non c'è collisione: $T[5]=31$
>4. $h(43,0)=(h_1(43)+0)\text{ mod }13=4\text{ mod }13=4$
>	- $h(43,0)=(h_1(43)+h_2(43))\text{ mod }13=15\text{ mod }13=2$
>	- Non c'è collisione: $T[2]=43$

Il doppio hashing a differenza dell'hashing lineare, usa $m^2$ sequenze di ispezioni (a differenza delle $m$ sequenze per l'hashing lineare) perchè ogni coppia $h_1(k),h_2(k)$ produce una distinta sequenza di ispezioni.
In questa strategia le celle occupate non sono adiacenti.

>Il doppio hashing viene molto usato nel mondo reale in quanto si avvicina molto alla strategia dell'hashing uniforme indipendente.

**Come costruire la funzione hash**: di seguito sono riportate due opzioni
1. $m=2^p$ (sempre pari), definisco $h_2(k)$ in modo che produca sempre numeri dispari, in questo modo $m$ e $h_2(k)$ saranno sempre relativamente primi.
	- e.g. $m=2^p$, $h_2(k)=2h'(k)+1$
2. Si sceglie $m$ com numero primo, e si definisce $h_2(k)$ in modo che generi sempre un intero $m' < m$.
	- e.g. $m$ primo, $h_1(k)=k\text{ mod }m$ e $h_2(k)=1+(k\text{ mod }m')$

## Analisi dell'hashing a indirizzamento aperto
**Ipotesi**:
- Si assuma H.U.I.
- Si assuma che non venga compiuta l'operazione di cancellazione (necessario se vogliamo fare l'analisi in termini del fattore di carico $\alpha$)

A differenza del concatenamento che poteva memorizzare più di $m$ chiavi date le sue doubly-linked-list, ora il fattore di carico: $0\leq \alpha=\frac{n}{m}\leq 1$, infatti ora il numero massimo di chiavi che possiamo memorizzare è $m$, dunque quando $n=m$ , $\alpha=1$.

#### Teorema
Nell'ipotesi di H.U.I., data una tabella hash a indirizzamento aperto con fattore di carico $\alpha < 1$, il numero di ispezioni in una _ricerca senza successo_ (caso peggiore) risulta essere al massimo $\frac{1}{1-\alpha}$.

**Dimostrazione**: Se $\alpha < 1$, allora esistono delle celle vuote, per cui ci si può fermare alla prima cella vuota durante una ricerca:
1. Una prima ispezione è sempre compiuta: $\mathbb{P}[\mathrm{I}]=1$
2. La probabilità che venga compiuta la seconda ispezione equivale alla probabilità che la prima cella sia occupata: $\mathbb{P}[\mathrm{II}]=\frac{n}{m}$
3. la probabilità che venga compiuta anche la terza ispezione equivale alla probabilità che anche la seconda cella sia occupata: $\mathbb{P}[\mathrm{III}]=\frac{n}{m}\cdot\frac{n-1}{m-1}$
4. la probabilità che venga computa la quarta ispezione equivale alla probabilità che anche la terza cella sia occupata: $\mathbb{P}[\mathrm{IV}]=\frac{n}{m}\cdot\frac{n-1}{m-1}\cdot\frac{n-2}{m-2}$

Dato che $\alpha = \frac{n}{m}$ possiamo approssimare i termini come segue:
$$\mathbb{P}[\mathrm{I}]=1,\quad\mathbb{P}[\mathrm{II}]=\alpha,\quad\mathbb{P}[\mathrm{III}]\simeq\alpha^2,\quad\mathbb{P}[\mathrm{IV}]\simeq\alpha^3$$
$$1+\alpha+\alpha^2+...\leq\sum_{i=0}^\infty a^i=\frac{1}{1-\alpha}$$

**Interpretazione**: se $\alpha$ è costante, una _ricerca senza successo_ viene eseguita in tempo medio $O(1)$.
- Se $\alpha=0.5$ (tabella piena a metà), il numero medio di ispezioni è al massimo $\frac{1}{1-\frac{1}{2}}=2$.

Più la tabella è piena, più è costosa la ricerca.

**Corollario**: nell'ipotesi di H.U.I., l'inserimento di un elemento in una tabella hash a indirizzamento aperto con un fattore di carico $\alpha$ richiede al massimo $\frac{1}{1-\alpha}$ ispezioni, questo perchè per inserire un elemento dobbiamo prima eseguire una _ricerca senza successo_ per trovare una posizione vuota.

#### Teorema
Nell'ipotesi di H.U.I., data una tabella hash a indirizzamento aperto con fattore di carico $\alpha < 1$, il numero di ispezioni in una _ricerca con successo_ risulta essere al massimo $\frac{1}{\alpha}\log\Big(\frac{1}{1-\alpha}\Big)$.

**Interpretazione**: se $\alpha$ è costante, una _ricerca con successo_ viene eseguita in tempo medio $O(1)$.
- Se $\alpha=0.5$ (tabella metà piena), il numero medio di ispezioni è al massimo $\frac{1}{0.5}\log\Big(\frac{1}{1-0.5}\Big)=1.3863$

