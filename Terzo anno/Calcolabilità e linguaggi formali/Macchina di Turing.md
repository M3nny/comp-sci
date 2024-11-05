Una **macchina di Turing (MdT)** è un modello teorico di un calcolatore con memoria infinita ed utilizzabile in maniera arbitraria.

>[!Info] Memoria dei DFA e PDA
>I **DFA** possiedono memoria **finita**, mentre gli **NFA** dispongono di memoria **infinita** in forma di _stack_.

Una MdT è formata da uno **stato interno**, un **nastro infinito** ed una **testina**.

**Caratteristiche** di una MdT:
- L'input è sul nastro e può essere sia letto che scritto
- La testina può spostarsi sia a sx e sia a dx
- Memoria (nastro) infinita
- Accetta o rifiuta un input non appena entra in uno stato di accettazione o rifiuto

## Definizione di una macchina di Turing
Una MdT è una settupla $(Q,\Sigma,\Gamma,\delta,q_0,q_{accept},q_{reject})$ dove:
- $Q$: è insieme finito di stati
- $\Sigma$: è un alfabeto finito di input tale che un carattere **blank** $\sqcup\notin\Sigma$
- $\Gamma$: è un alfabeto finito per il nastro tale che $\sqcup\in\Gamma$ e $\Sigma\subseteq\Gamma$
- $q_0\in Q$: è lo stato iniziale
- $q_{accept}\in Q$: è (l'unico) stato accettante
- $q_{reject}\in Q$: è (l'unico) stato rifiutante ($q_{reject}\neq q_{accept}$)
- $\delta:Q\times\Gamma\to Q\times\Gamma\times\{L,R\}$ è la funzione di transizione

Una configurazione di una MdT <u>descrive un momento della computazione</u> tramite tre informazioni:
- Lo stato interno
- Il contenuto del nastro
- La posizione della testina

![[Configurazione MdT.svg]]
essa può essere scritta come $001q_301$.
Generalmente una configurazione ha forma $uqv$, dove $u,v\in\Gamma^*$ e $q\in Q$.

Una MdT computa passando da una configurazione a quella successiva secondo quanto definito da $\delta$, vediamo le **regole di computazione**:
- Sia $M$ nella configurazione $uaq_ibv$, e sia $\delta(q_i,b)=(q_j,c,L)$, allora la prossima configurazione sarà $uq_jacv$
- Sia $M$ nella configurazione $uaq_ibv$ e sia $\delta(q_i,b)=(q_j,c,R)$, allora la prossima configurazione sarà $uacq_jv$
- Sia $m$ nella configurazione $q_ibv$ e sia $\delta(q_i,b)=(q_j,c,L)$, allora la prossima configurazione sarà $q_jcv$
- Sia $M$ nella configurazione $q_ibv$ e sia $\delta(q_i,b)=(q_j,c,R)$, allora la prossima configurazione sarà $cq_jv$

Una MdT **accetta un input** $w$ sse esistono della configurazioni $C_1,C_2,...,C_k$ tali che:
- $C_1$ è la configurazione iniziale $q_0w$
- $C_k$ è una configurazione accettante $u_{accept}v$ per qualche $u,v\in\Gamma^*$
	(Le configurazioni accettanti possono essere più di una)
- Per ogni $i$ $C_i$ passa in $C_{i+1}$ secondo le regole di computazione date

### Linguaggio per una macchina di Turing
Un linguaggio $A$ si dice **Turing riconoscibile** sse esiste una MdT $M$ tale che $L(M)=A$.
Dato un input $w$, una MdT $M$ ha solo tre possibili comportamenti:
- $M$ accetta $w$
- $M$ rifiuta $w$
- $M$ non termina (va in loop quando eseguita su $w$)

Una macchina di Turing che non va mai in loop per nessun input si dice **decisore**.
Un linguaggio $A$ si dice **decidibile** sse esiste un _decisore_ $M$ tale che $L(M)=A$.

>[!Example]
>Creiamo una MdT per il linguaggio _non regolare_, e _non CFL_:
>$$C=\{w\#w|w\in\{0,1\}^*\}$$
>
>L'idea è quella di andare a fare il match dei simboli a sx e dx di $\#$, per prima cosa si sostituisce il primo simbolo in posizione $i$ con una $\times$, poi si controlla il simbolo a posizione $pos(\#)+i$, se combacia si marchia con una $\times$, altrimenti si rifiuta.
>
>Dopo aver sostituito i simboli con $\times$ a sx e dx di $\#$ si verifica se ci sono ancora simboli non marchiati con $\times$, in tal caso si rifiuta, altrimenti si accetta.
>![[MdT 1.png]]
>
>---
>Creiamo una MdT per il seguente linguaggio:
>$$\{0^{2^n}|n\geq 0\}$$
>
>Il linguaggio rappresenta una stringa di zeri con lunghezza pari ad una potenza di $2$.
>L'idea è quella di fare molteplici passate sul nastro, dove ogni volta vengono marchiati con $\times$ la metà degli $0$, quindi si marchia uno si ed uno no.
>Se la passata ha marchiato solo uno $0$ accetta, se ha trovato una quantità di $0$ dispari ($>1$) rifiuta, altrimenti esegue un'altra passata.

---
### Variante MdT - Stay
Cambiando la funzione di transizione è possibile introdurre una variante della macchina di Turing che oltre a muoversi verso sinistra e destra, <u>permette anche di non muovere la testina dopo aver letto un input</u>.
$$\delta:Q\times\Gamma\to Q\times\Gamma\times\{L,R,S\}$$

La mossa $S$ sta per **Stay** e permette di mantenere la testina nella posizione in cui si trovava prima di processare il carattere corrente.

Questa mossa può essere replicata da una normale MdT muovendosi prima a destra e poi a sinistra (evitiamo il caso limite di essere all'inizio del nastro).

### Variante MdT - Multinastro
Immaginiamo di avere una macchina con $k$ nastri, il primo nastro sarà usato per contenere l'input, gli altri $k-1$ come <u>area di memorizzazione aggiuntiva</u>.

Questa variante non è più espressiva di una MdT tradizionale in quanto i $k-1$ nastri aggiuntivi potrebbero essere concatenati e delimitati da un carattere speciale in una MdT normale dato che la lunghezza del nastro è infinita.
Bisogna fare attenzione a _shiftare_ correttamente tutti gli elementi del nastro unico, infine bisogna considerare la **rappresentazione delle posizioni** delle testine sui $k$ nastri (e.g. marcando tali celle con un pallino).
![[MdT - multinastro.png]]

La funzione di transizione per una MdT multinastro è la seguente:
$$\delta:Q\times\Gamma^k\to Q\times\Gamma^k\times\{L,R,S\}^k$$

**Esempio di conversione**
1. Popoliamo il nastro con $\dot w_1...w_n\#\underbrace{\dot\sqcup\#...\#\dot\sqcup}_{k-1}\#$
2. Simuliamo una mossa scorrendo tutto il nastro e segniamo nello stato i $k$ simboli marcati con $\cdot$, poi scorriamo di nuovo il nastro per aggiornare il suo contenuto secondo $\delta$
3. Se stiamo per scrivere su un $\#$ eseguiamo uno _shift_ a destra del contenuto del nastro e liberiamo una cella

### Variante MdT - Non deterministica
Similmente a quello visto con gli [[Automi a stati finiti non deterministici#Definizione di NFA|NFA]] modifichiamo la funzione di transizione per far uscire la MdT dai limiti del determinismo:
$$\delta:Q\times\Gamma\to\mathcal{P}(Q\times\Gamma\times\{L,R\}$$

**Teorema**: per ogni MdT non deterministica, esiste una MdT deterministica equivalente.

**Idea**: una computazione non-deterministica si può rappresentare come albero, dove ogni nodo ha come figli i passi successivi delle computazioni che genera.
Lo scopo della dimostrazione è quello di poter simulare tramite MdT deterministica un cammino radice-foglia che rappresenta una computazione accettante, non possiamo però effettuare una ricerca in profondità (potremmo finire in una esecuzione che entra in loop infinito), per cui eseguiremo una ricerca in ampiezza.

Utilizziamo una MdT dotata di tre nastri per completare la dimostrazione.
![[MdT - non deterministica.png|650]]

- **1° nastro**: contiene l'input originale
- **2° nastro**: su di esso avvengono le simulazioni delle esecuzioni, inizialmente sarà popolato con l'input originale
- **3° nastro**: risolve il non determinismo, esso tiene traccia del cammino corrente (cioè l'esecuzione considerata attualmente) codificato tramite una stringa di interi, tale cammino prende il nome di **indirizzo**

Dall'immagina capiamo che il percorso a sinistra è un ciclo infinito, per questo dobbiamo procedere in ampiezza, la macchina terminerà quando arriverà alla fine del cammino evidenziato in verde (assumiamo accettante).
Possiamo codificare il cammino accettante come $121$ in quanto prendiamo inizialmente il primo figlio da sx, poi il secondo ed infine il primo.

La macchina funzionerà come segue:
1. Inizialmente mette sul nastro $1$ l'input $w$, assume che il 2° nastro sia vuoto ed inizializza il 3° nastro a $\epsilon$
2. Copia il 1° nastro sul 2°
3. Simula la MdT non deterministica sul 2° nastro usando il contenuto del 3ç nastro per risolvere il non-determinismo
4. Se accetta termina con _accept_, altrimenti se rifiuta oppure il 3° nastro contiene un indirizzo invalido aggiorna il contenuto del 3° nastro con la prossima stringa e va al punto 2

>La generazione degli indirizzi è ciò che determina la visita in ampiezza dell'albero.

### Enumeratore
Un enumeratore, volgarmente, consiste in una MdT con una stampante annessa, che può usare come dispositivo di output.
![[Enumeratore.png]]

L'enumeratore non parte con un input sul nastro, ma genera stringhe su di esso _enumerandole_, con l'idea che prima o poi la stringa sul nastro venga stampata.

Il suo **linguaggio** è l'insieme delle stringhe stampate.
>Possiamo vedere una MdT come un riconoscitore di stringhe, mentre un enumeratore come un generatore di stringhe.

**Teorema**: un linguaggio è Turing-riconoscibile sse esiste un enumeratore che lo genera.

**Dimostrazione ($\Rightarrow$)**:
Assumiamo di avere una MdT $M$ tale che $L(M)=A$, costruiamo un enumeratore $E$ tale che $L(E)=A$.

$E=\forall i\in[1,2,...]$
1. Esegue $m$ per i passi di computazione su $s_1,...,s_i$
2. Se esiste $s_j$ dove $M$ termina con _accept_, stampa $s_j$

Il funzionamento dell'enumeratore è il seguente:
1. Simula $M$ su $s_1$ per $1$ passo
2. Simula $M$ su $s_1,s_2$ per $2$ passi
3. Simula $M$ su $s_1,s_2,s_3$ per $3$ passi
4. ...

In questo modo la computazione di $M$ non si blocca su una stringa che potenzialmente può mandare in ciclo infinito la macchina, ma ad ogni colpo viene dato il beneficio del dubbio alla stringa successiva per aumentare la probabilità di successo.

**Dimostrazione ($\Leftarrow$)**:
Assumiamo che esista una enumeratore $E$ tale che $L(E)=A$, costruiamo una MdT $M$ tale che $L(M)=A$ descritta come segue:

$M=$ su input $w$:
1. Esegue $E$, quando esso genera una stringa $w'$, confronta $w$ con $w'$
2. Se $w=w'$ accetta, altrimenti passa alla stringa successiva


