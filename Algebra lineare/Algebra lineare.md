## Rette e piani
- **Retta passante per 2 punti o passante per un punto parallelo a vettore**:
![[Retta passante per 2 punti.png|500]]
	Dopo si isola t e si sostituisce ad una equazione, in questo modo nell'equazione dove abbiamo sostituito t avremmo tutte le variabili, quella è l'equazione cartesiana della retta, il procedimento è lo stesso per una retta che passa per un punto parallelo ad un vettore, solo che qui andiamo direttamente a scrivere l'equazione parametrica.

- **Retta passante per 3 punti**:
	Al posto di trovare un singolo vettore $\overrightarrow{AB}=(t_0, t_1, t_2)$ troveremo anche un vettore $\overrightarrow{AC} = (s_0,s_1,s_2)$, dopo useremo un sistema del tipo $\begin{cases}x=x_0+t_0+s_0\\y=y_0+t_1+s_1\\z=z_0+t_2+s_2\end{cases}$ 

- **Retta dello spazio di equazioni cartesiane** $\begin{cases}y=...\\y=...\end{cases}$ 
	Qui pongo una variabile che è uguale a t (x=t) e poi vado a sostituire finchè non mi ritrovo in una situazione del tipo $\begin{cases}x=t\\y=...+t\\z=...+t\end{cases}$ 

- **Punto appartenente ad una retta**:
	Sostituisco un valore a piacere dentro all'equazione parametrica o cartesiana e metto i valori del punto qua: P(0,0,0). Inoltre per verificare se un punto fa parte del piano, vado a sostituire i valori del punto dentro all'equazione cartesiana (più facile) e dovrei ottenere 0, altrimenti sostituendo a quella parametrica dovrei ottenere le variabili con valori uguali nelle varie equazioni.

- **Retta passante per un punto e ortogonale/perpendicolare al piano**:
	Dato un generico piano $ax+by+cz = k$ il vettore $(a,b,c)$ è sempre ortogonale al piano, quindi dobbiamo trovare l'equazione cartesiana del piano e conoscendo che il piano passa per $(l,m,n)$ la retta parametrica passante per un punto e ortogonale al piano la ottengo così $\begin{cases}x=l+at\\y=m+bt\\z=n+ct\end{cases}$ 

- **Si determini l’equazione LINEARE del piano ortogonale a $r_1$ passante per C**:
	1. Trovare vettore direzione $r_1$
	2. Applicare $r_1$ all'origine (se $v=(1,1,1)$ allora $r_1 = x+y+z=0$)
	3. Sostituisco su $r_1$ applicata all'origine i valori di $C$
	4. Il piano è uguale a <retta applicata all'origine> = <valori di $C$ sostituiti su $r_1$>

- **Trovare se le rette sono parallele, incidenti o sghembe**:
	Avendo 2 rette $r:\begin{cases}x=x_0+t_0\\y=y_0+t_1\\z=z_0+t_2\end{cases}$ e $s:\begin{cases}x=x_0+h_0\\y=y_0+h_1\\z=z_0+h_2\end{cases}$
	1. Sono _parallele_ se i loro vettori direzioni sono proporzionali uno rispetto all'altro.
	2. Sono _incidenti_ se le equazioni di $r\cap s$ non si contraddicono $\begin{cases}x_0+t_0 = x_0+h_0\\...=...\\...=...\end{cases}$ , troviamo il punto in cui incidono sostituendo il valore di $t$ o $h$ determinato in una delle due equazioni.
	3. Sono _sghembe_ altrimenti.

- **Trovare l'angolo tra 2 rette**:
	Usando il loro vettore direzione uso $\frac{A\cdot B}{|A|\cdot |B|} = \frac{A\cdot B}{\sqrt{(A\cdot A)} \cdot \sqrt{(B\cdot B)}}$ e poi faccio il coseno di quello che trovo.

- _Posso trovare il punto di intersezione tra 2 rette/piani sostituendo uno nell'altro nel caso uno dovesse essere in forma parametrica e l'altro in forma cartesiana_: $r:\begin{cases}x=t\\y=2t\\z=3t\end{cases}$  $s: x+y+z-1=0$ ora sostituisco -> $t+2t+3t-1=0$ dopo aver trovato il valore di $t$ lo sostituisco e trovo il punto di incidenza

- **Trovare il piano che contiene 2 rette**: 
	_Nota: nel caso le 2 rette fossero parallele, devo prima trovare la retta tra 2 punti, il primo appartenente alla prima retta ed il secondo appartenente alla seconda retta, successivamente svolgo i normali passaggi usando la retta che ho appena trovato ed una delle altre due (una di quelle parallele)_
	
	1. Trovo il punto di intersezione delle rette
	2. Trovo i vettori delle direzioni delle rette
	3. Ora possiedo $P=(a,b,c)$ $\overrightarrow{v} = (x_0, y_o, z_0)$ e $\overrightarrow{w} = (x_1, y_1, z_1)$, rappresento il piano in forma parametrica, ovvero $\pi: \begin{cases}x=a+x_0t+x_1u\\y=b+y_0t+y_1u\\z=c+z_0t+z_1u\end{cases}$ 
	4. Mi ricavo l'equazione lineare del piano isolando prima $t$, sostituisco, isolo $u$, sostituisco, la funzione che non ha parametri è l'equazione lineare del piano.

- **Due vettori sono**:
	1. _Perpendicolari_ se il loro prodotto è 0 
		$v=(P_1,p_2)\space w=(1,2)\quad |\quad p_1+2p_2=0\quad | \quad p_1=-2p_2$ 
	2. _Allineati_ se il coseno dell'angolo da essi formato è $\pm 1$ 


## Valori per cui il sistema ammette soluzioni
1. Calcolo il determinante della matrice incompleta, se è diverso da 0 per ogni $t$ dico che la soluzione esiste ed è unica per ciascun valore reale di $t$ altrimenti trovo quando è 0 e valuto quel caso alla fine *
2. Trasformo la matrice completa in forma triangolare superiore
3. Ricavo le soluzioni dalla matrice partendo col trovare l'incognita dell'ultima riga
4. Ripeto l'ultimo passaggio andando verso su e sostituendo le incognite già trovate
5. Alla fine devo ritrovarmi tutte le incognite espresse in funzione di $t$
* * Nel caso $t$ fosse 0 per qualche valore, lo sostituisco nella matrice a scala che ho determinato e se trovo qualche incongruenza del tipo 0 = 5 dico che non esiste soluzione per il valore per cui il $det \neq 0$.
	Se invece non ci sono incongruenze vado a determinare i valori di $x,y,z$, nel caso non fosse possibile trovare il valore di nessuna delle 3 inizialmente, assegno un parametro a una delle 3 incognite, se fossero necessari 2 o più parametri il sistema avrebbe infinite soluzioni.

## Autovettori
- **Determinare gli autovalori di una matrice**:
	1. Sottraggo $\lambda$ alla diagonale principale
	2. Calcolo il determinante delle matrice e quindi ottengo il polinomio caratteristico
	3. Trovo $\lambda_1, \lambda_2...$ per cui il loro valore si annulla, questi sono gli autovalori

- **Determinare la dimensione degli autospazi associati agli autovalori**:
	Trovare la base di ogni autovettore associato a ogni autovalore, la dimensione dell'autospazio sarà data da quanti vettori contiene al suo interno. _Ogni autovalore ha almeno un autovettore_.
	Se mi ritrovo uno sottospazio del tipo $\begin{bmatrix}0&0&0\\1&1&1\\0&0&0\end{bmatrix}$ dove ho solo $x+y+z=0$, sapendo che non possono essere tutti a 0 dato che  _ogni autovalore ha almeno un autovettore_, allora per forza 2 variabili si negano tra loro mentre 1 avrà un valore, posso fare degli esempi dicendo: "due autovalori linearmente indipendenti sono: $P=(1,-1,0)$ e $Q=(0,1,-1)$"
	
	==_è data dalla molteplicità geometrica==

- **Una matrice è diagonalizzabile quando**:
	1. Gli autovalori appartengono all'insieme in cui la matrice deve essere diagonalizzata (Se un autovalore mi risulta essere $i$ ma deve essere diagonlizzabile in $\mathbb{R}$ allora non può essere diagonalizzata in $\mathbb{R}$ ma solo in $\mathbb{K}$).
	2. La somma delle molteplicità algebriche (quante volte abbiamo ottenuto lo stesso autovalore) coincide con la somma delle molteplicità geometriche (dimensione dell'autospazio associato all'autovalore).
	3. La molteplicità algebrica deve corrispondere con la dimensione di una eventuale della matrice, nel caso $f: \mathbb{R}^3 \to \mathbb{R}^3$ allora la molteplicità algebrica deve essere 3.

**Calcolare la molteplicità geometrica**:
	1. Se la molteplicità algebrica è 1 allora anche la geometrica è 1, altrimenti calcolo la geometrica tramite: **n° righe - rango(A-$\lambda \cdot$ID)**.
	1 $\leq$  m_geometrica $\leq$ m_algebrica

- **Verificare che i vettori $v$ sono autovettori di $f$ e determinare i rispettivi autovalori**:
	Sostituisco dentro a $f$ i valori del vettore $v$, ora che ho trovato la sua immagine, se $v$ fosse stato $v=(0,3,1)$ e avessi trovato mettendolo dentro alla funzione $f(0,3,1)=(0,6,2)$, devo trovare quel valore $\lambda$ (autovalore) per cui $(0\lambda, 3\lambda, 1\lambda) = (0,6,2)$, se non esiste, allora il vettore $v$ non è autovettore di $f$.

- **Verificare che i vettori costituiscono una base di $\mathbb{R}^3$**
	Se gli autovalori che ho trovato da essi sono distinti allora sono linearmente indipendenti e costituiscono una base di $\mathbb{R}^3$

- **La matrice diagonalizzata si ottiene** mettendo gli autovalori trovati nella diagonale principale della matrice, mettendo 0 al resto dei valori.

- **Trovare la matrice diagonalizzante**:
	Una matrice diagonalizzate è detta tale se $D=P^{-1}\cdot A \cdot P$.
	Dove $D$ è la matrice diagonalizzata, $P$ la matrice diagonalizzabile e $A$ la matrice di partenza.
	
	Per trovare la matrice diagonalizzante:
	1. Creo la matrice diagonalizzata facendo attenzione a dove metto gli autovalori
	2. Trovo gli autovettori sostituendo $\lambda$, se ad esempio ottengo $\begin{bmatrix}0\\t\\-t\end{bmatrix}$  vado a raccogliere $t$  e ottengo $\begin{bmatrix}0\\1\\-1\end{bmatrix}$. Un altro esempio con 2 parametri liberi diversi (in questo caso l'autovalore aveva m algebrica pari a 2) potrebbe essere che mi ritrovo $\begin{bmatrix}0\\t\\r\end{bmatrix}$ da cui prima raccolgo $t$ e poi $r$ o viceversa ottenendo così $\begin{bmatrix}0\\1\\0\end{bmatrix}$ e $\begin{bmatrix}0\\0\\1\end{bmatrix}$
	3. Ripeto il passaggio 2 per tutti gli autovalori, alla fine posso comporre la matrice diagonalizzante creando una nuova matrice tenendo conto che se nella prima colonna della matrice diagonalizzata avevo messo $\lambda_1$ dovrò mettere in quella colonna l'autovettore di $\lambda_1$. 
		Nel caso ci fosse un autovalore con m algebrica pari a 2, i 2 autovettori che ne derivo li posso mettere su una colonna che voglio (basta che sia sempre di quel autovalore in questione)

## Trasformazioni (o applicazioni) lineari
- **La dimensione del nucleo $ker$ si ottiene tramite**: numero di colonne - rango
- **La dimensione dell'immagine**: è uguale al rango della matrice associata
- **Iniettiva quando**: $dim(ker) = 0$
- **Suriettiva quando**: $dim(Im(f))$ è uguale alla dimensione dello spazio vettoriale di destinazione, ad esempio se la funzione è $f: \mathbb{R}^3 \to \mathbb{R}^3$, se la dimensione dell'immagine è 3 allora è suriettiva.
- **Trovare _una_ base del nucleo**: 
	1. Devo trovare un vettore non nullo del nucleo
	2. Trovo i valori di $x,y,z$ in funzione di $t$
	3. Raccolgo $t$ e ottengo una base del nucleo

- **Trovare una base dell'immagine**:
	Devo trasformare la matrice in scala e poi guardando le righe possiedono un pivot, se ad esempio lo possiedono la _riga_ $1$ e $2$, dirò che una basse di $Im(f)$ è data dai vettori _colonna_ $1$ e $2$ 
- Il rango rappresenta anche la dimensione del sottospazio vettoriale generato dai vettori che ne compongono la matrice

## Linearità di una applicazione lineare
- **Una applicazione è lineare se**:
	1. La somma delle immagini è uguale all'immagine della somma (_additività_)
		$f((x_1,y_1,z_1) + (x_2+y_2+z_2)) = f((x_1,y_1,z_1)) + f((x_2+y_2+z_2))$
	2. il prodotto per uno scalare qualsiasi $\lambda$ delle somme delle immagini è uguale al al prodotto per $\lambda$ delle immagini (_omogeneità_)
		$f(\lambda(x,y,z)) = \lambda f(x,y,z)$

- **Vedere quali vettori colonna sono linearmente indipendenti**:
	1. Trasformo la matrice in scala
	2. La trasformo in sistema
	3. Isolo variabili diverse per ogni equazione
	4. Sono linearmente indipendenti le colonne che non compaiono nell'equazione delle altre variabili isolate
	$A=\begin{bmatrix}1&-1&0\\0&1&3\\0&0&0\end{bmatrix}$  da cui otteniamo $\begin{cases}A_1-A_2=0\\A_2+3A_3=0\end{cases} \to \begin{cases}A_1=A_2\\A_3=-\frac{A_2}{3}\end{cases}$   

- **Stabilire se esiste una applicazione lineare** $T : \mathbb{R}^2 \to \mathbb{R}^2$ tale che $T(1, 2) = (3, 0),\space T(2, 7) = (4, 5), \space T(1, 5) = (1, 4)$
	1. Trovo quale vettore è combinazione lineare dell'altro (molte semplice di solito si vede ad occhio), qui c'è $(1,2)+(1,5)=(2,7)$
	2. Ora devo vedere se anche $T(v)$ corrisponde, quindi $(3,0)+(1,4) = (4,4)$ ma $(4,4) \neq (4,5)$ per questo l'applicazione lineare non esiste.

## Dipendenza lineare
- **Vettori linearmente dipendenti**: sono tali se oltre alla n-upla di scalari pari a $0$ esiste almeno una n-upla per cui gli scalari _non sono_ tutti nulli. 
- **Un vettore linearmente dipendente dal vettore** $(x,y,z)$ è dato da $\lambda(x,y,z)$
- **Studiare la dipendenza lineare**:
	1. Metto i vettori in una matrice e risolvo il "sistema"
		Nota: $\begin{bmatrix}1&2\\3&4\end{bmatrix}$ lo scrivo come $\begin{bmatrix}1\\2\\3\\4\end{bmatrix}$ e procedo normalmente.
	1. Ora che ho ottenuto le soluzioni $(\lambda, \micro, v)$ guardo in che modo le posso combinare tra loro per ottenere il vettore desiderato 
- Non è una combinazione lineare se ottengo soluzioni diverse per lo stesso parametro.

## Sottospazi
Per dimostrare che un insieme di uno spazio vettoriale è un sottospazio devo mostrare che è chiuso rispetto alla somma di due elementi e chiuso rispetto al prodotto per uno scalare.
$V=\{\begin{bmatrix}x&2y\\y&x-y\end{bmatrix}\in M_2(\mathbb{R}):x,y\in \mathbb{R}\}$ 

_Chiusura rispetto la somma_
$v_1=\begin{bmatrix}x_1&2y_1\\y&x_1-y_1\end{bmatrix}$ $v_2=\begin{bmatrix}x_2&2y_2\\y_2&x-y_2\end{bmatrix}$ 

$v_1+v_2=\begin{bmatrix}x_1+x_2&2(y_1+y_2)\\y_1+y_2&x_1-y_1+x_2-y_2\end{bmatrix}$ la somma appartiene ancora ad $\mathbb{R}$? per vederlo meglio poniamo $x=x_1+x_2$ e $y=y_1+y_2$ e otteniamo $v_1+v_2=\begin{bmatrix}x&2y\\y&x-y\end{bmatrix}$ per cui è evidente che appartiene all'insieme.

_Chiusura rispetto al prodotto per uno scalare_
$v_1=\begin{bmatrix}x&2y\\y&x-y\end{bmatrix}$

$\lambda v_1=\begin{bmatrix}\lambda x&\lambda 2y\\\lambda y&\lambda (x-y)\end{bmatrix}$ $\lambda v_1$ appartiene ancora a $\mathbb{R}$? beh si ma per vederlo meglio poniamo $x=\lambda x_1$ e $y=\lambda y_1$ la matrice diventa $\begin{bmatrix}x&2y\\y&x-y\end{bmatrix}$
Per cui dato che rispetta entrambi i requisiti, è un sottospazio.

Altro esempio
_Appartenenza dell'elemento nullo_
$S =\{v = (x1, x2, x3) \in \mathbb{R}^3 | x1 + x2 + x3 = 1\}$
Non è un sottospazio dato che $0v=0\neq 1$

## Domande
- **Sia $f : V → W$ una trasformazione lineare di spazi vettoriali. Dimostrare che sia il nucleo di $f$ che l’immagine di $f$ sono sottospazi vettoriali**:
	Dimostriamo che il nucleo è un sottospazio. Siano $v,t\in V$ vettori ed $r$ uno scalare. Se $f(v)=f(t)=0$ allora $f(v+t)=f(v)+f(t)=0+0=0$ e $f(rv)=rf(v)=r0=0$.
	Dimostriamo che l'immagine è un sottospazio. Siano $w_1,w_2\in Im(f)$ allora esistono $v_1,v_2\in V$ tali che $w_i=f(v_i)\space (i=1,2)$ . Allora $w_1+w_2=f(v_1)+f(v_2)=f(v_1+v_2)$ e $rw_1=rf(v_1)=f(rv_1)$. In conclusione $w_1+w_2\in Im(f)$ e $rw_1 \in Im(f)$ 

- **Sia $f : V → V$ un endomorfismo lineare e $v_1, . . . , v_n$ una base di $V$ . Spiegare in quali casi la matrice di $f$ rispetto alla data base è diagonale**:
	Sia $A=(a_{ij})$ allora gli scalari della colonna $A^j$ sono le coordinate del vettore $f(v_j)$. Allorala matrice è diagonale se e solo se $a_{jj}$ è un autovalore di autovettore $v_j$ quindi $A$ è diagonale se e solo se $v_1,...v_n$ è una base di autovettori.

- **Sia $f : V → V$ un endomorfismo lineare e $\lambda$ un autovalore di $f$. Verificare che l’insieme degli autovettori di $\lambda$ è un sottospazio di $V$**:
	Siano $v,w$ due autovettori tali che $f(v)=\lambda v$ e $f(w)=\lambda w$, allora per ogni scalare $r,s$ si ha che $f(rv+sw)=\lambda(rv+sw)$

- **Consideriamo un sistema lineare omogeneo di $m$ equazioni in $n$ incognite: $Ax = 0$ con $A$ matrice di tipo $m × n$. Supponendo $n > m$, spiegare il motivo per cui il sistema ammette sicuramente una soluzione non banale**:
	$\ker(f_a)=n-dim(f_a)\geq n-m\geq 1$ quindi $Ax=0$ ha soluzioni non banali.

- 
1. **Scrivere la definizione di trasformazione lineare.** 
2. **Siano $V$ uno spazio vettoriale di dimensione $n$ e $W$ uno spazio vettoriale di dimensione $m$. Data una trasformazione lineare $f : V → W$, determinare una matrice associata ad $f$.**
	1. è una funzione che preserva le operazioni di somma di vettori e moltiplicazioni per uno scalare.
	2. La colonna $A^j$ è costituita dalle coordinate del vettore $f(v_j)$ di $W$: $\begin{bmatrix}a_{1j}\\...\\a_{mj}\end{bmatrix}$ 

- **Scrivere la definizione di base di uno spazio vettoriale. Lo spazio vettoriale dei polinomi reali in una variabile ha una base finita?**
	è un insieme di vettori linearmente indipendenti che generano tutto lo spazio. Lo spazio vettoriale dei polinomi reali in una variabile ha base infinita, una possibile base è $1,x,x^2,x^3,...,x^n,...$

- **Quali sono le tre proprietà che univocamente definiscono il determinante di una matrice quadrata di ordine $n$?**
	1. Il determinante come funzione di una colonna è lineare
	2. Se due colonne sono uguali, allora $det(A)=0$
	3. Il determinante della matrice identica è uguale a 1

- **Quali sono gli assiomi (espressi in termini di equazioni) che definiscono gli spazi vettoriali?**
	1. $a+(b+c)=(a+b)+c$
	2. $a + b = b + a$
	3. $0 + a = a = a + 0$
	4. $a + (−a) = 0 = (−a) + a$
	5. $(r + s)a = ra + sa$
	6. $(rs)a = r(sa)$
	7. $r(a + b) = ra + rb$
	8. $0a = 0; 1a = a; (−1)a = −a$

## Tips
- Se una matrice ha $det\neq 0$ allora tutte le sue colonne sono linearmente indipendenti e formano una base di $Im(f)$.
- Se una matrice è triangolare superiore, i suoi autovalori, sono i valori appartenenti alla diagonale
- Provare che l'insieme $\{(2,0,−1),(2, −3,0),(−1,2,1)\}$ è una base dello spazio vettoriale $\mathbb{R}^3$ sul campo $\mathbb{R}$ significa provare che il determinante della matrice $\begin{bmatrix}2&2&-1\\0&-3&2\\-1&0&1\end{bmatrix}$ sia diverso da $0$, ovvero bisogna dimostrare che le colonne siano linearmente indipendenti. Se viene chiesto poi di determinare le coordinate di un vettore $P=(1,2,1)$ rispetto ad una base come quella precedente, andiamo semplicemente ad aggiungere una colonna alla fine della matrice e risolviamo il sistema considerando la colonna aggiunta come i termini noti, le coordinate del punto $P$ rispetto alla base sono i valori di $x,y,z$ trovati dopo aver risolto il sistema.