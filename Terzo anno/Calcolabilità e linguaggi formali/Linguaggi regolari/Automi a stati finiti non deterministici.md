Gli **automi a stati finiti non-deterministici (NFA)** si differenziano rispetto ai normali DFA per due caratteristiche principali:
- Uno stato può avere più/meno archi uscenti rispetto a quanti sono i simboli dell'alfabeto
- Può possedere delle **$\epsilon$-transizioni**, ovvero transizioni di stato che avvengono senza consumare caratteri in input

Consideriamo il seguente NFA:
![[NFA.svg]]

L'input $101$ è accettato, lo stesso vale per $11$ tramite ($1\to\epsilon\to1$), $0$ però non è accettato.
<u>Un NFA accetta una stringa se esiste un cammino verso uno stato accettante</u>.

È possibile visualizzare tutti i possibili cammini come un albero, di seguito l'**albero di computazione** per l'input $0101$:
![[Albero di computazione.svg]]

### Definizione di NFA
Un NFA $N$ è una quintupla $(Q,\Sigma, \delta, q_0, F)$ dove:
- $Q$: è un insieme finito di stati
- $\Sigma$: è un insieme finito di input, detto **alfabeto**
- $q_0\in Q$: è lo stato iniziale
- $F\subseteq Q$: è l'insieme degli stati accettanti, essi possono essere $\geq 0$
- $\delta$: è dato da $Q\times(\Sigma\lor\{\epsilon\})\rightarrow \mathcal{P}(Q)$ e rappresenta la funzione di transizione

La differenza rispetto ai DFA sta nella funzione di transizione, essa infatti potrà prendere in input $\epsilon$ per eseguire una $\epsilon$-transizione, ed al posto di ritornare un singolo stato ritornerà l'[[Gli insiemi#Insieme delle parti|insieme delle parti]].

### Linguaggio di un NFA
Sia $N=(Q,\Sigma,\delta,q_0,F)$ un NFA, e sia $w$ una stringa che utilizza un alfabeto $\Sigma$.
Diciamo che $N$ accetta $w$ sse $w=y_1y_2,...,y_m$ dove $\forall i:y_i\in\Sigma\cup\{\epsilon\}$ (vengono inserite $\epsilon$ quando opportuno) ed avente una sequenza di stati $r_0,...,r_m\in Q$ tali che:
1. $r_0=q_0$ (il primo stato è quello iniziale)
2. $r_m\in F$ (l'ultimo stato è uno stato accettante)
3. $\forall i\in[0,m-1]:r_{i+1}\in\delta(r_i,y_{i+1})$ (la funzione di transizione è rispettata)

Prendendo in considerazione il precedente esempio:
![[NFA.svg]]

Il suo linguaggio è definito come:
- $Q=\{q1,q2,q3,q4\}$
- $\Sigma=\{0,1\}$
- $q_0=q_1$
- $F=\{q_4\}$
- $\delta(q_1,0)=\{q_1\}$, $\delta(q_1,1)=\{q_1,q_2\}$, ..., $\delta(q_1,\epsilon)=\{\emptyset\}$

>[!Example]
>Generalmente un NFA è molto più espressivo di un DFA, ad esempio di seguito viene rappresentato un NFA per il linguaggio delle stringhe binarie contenenti un $1$ nella terza posizione dalla fine (e.g. $00110$):
>![[NFA 1 terzultimo.png]]
>mentre il corrispondente DFA (tenendo traccia degli ultimi $3$ bit) sarebbe:
>![[DFA 1 terzultimo.png]]

### Conversione da NFA a DFA
**Teorema**:
Per ogni NFA $N$ esiste un DFA $D$ tale che $L(D)=L(N)$.
Sia $N=(Q,\Sigma,\delta,q_0,F)$, costruiamo un DFA $D=(Q',\Sigma,\delta',q_0',F')$ introducendo il concetto di $\epsilon$-transizione tramite la funzione:
$E(R)=\{q|q\text{ può essere raggiunto da qualche }r\in R\text{ con 0 o più }\epsilon-\text{transizioni} \}$

- $Q'=\mathcal{P}(Q)$ 
	(uno stato di $D$ corrisponde ad un insieme di stati possibili di $N$)
- $q_0'=E(\{q_0\})$
	(stato iniziale + altri raggiungibili da esso tramite $\epsilon$-transizioni)
- $F'=\{R\in Q'|\exists r\in R: r\in F\}$
	(uno stato è accettante se all'interno del suo insieme di stati è presente uno stato accettante per $N$)
- $\delta'(R,a)=\bigcup\limits_{r\in R}E(\delta(r,a))$
	(Presi un insieme di stati $R$, ed in input $a$, ritorna gli stati raggiungibili attraverso $a$ a partire da ogni stato in $R$ considerando anche le $\epsilon$-transizioni)

Di seguito la conversione di un NFA in un DFA:
![[NFA to DFA.svg]]

1. Lo stato iniziale è $E(\{1\})=\{1,3\}$
2. $\delta(1,a)=\emptyset$, $\delta(3,a)=\{1\}$, $\emptyset\cup\{1\}=\{1\}$ da cui $E(\{1\})=\{1,3\}$
3. $\delta(1,b)=\{2\}$, $\delta(3,b)=\emptyset$, $\{2\}\cup\emptyset = \{2\}$ da cui $E(\{2\})=\{2\}$
4. $...$
>Notare come il grafico risultante possiede $6$ stati, mentre il numero massimo di stati che potrebbe avere è $2^3$ ($\text{\#simboli}^\text{\#stati}$), questo è dovuto al fatto che sarebbero stati isolati, dunque l'algoritmo li ha ignorati.

1. Ogni NFA è convertibile in un DFA equivalente
2. Ogni DFA è convertibile in un NFA equivalente, ciò è banale in quanto un DFA è un sottoinsieme di un NFA, in altre parole un NFA che si comporta come un DFA
**Corollario**: un linguaggio $A$ è regolare sse esiste un NFA che lo riconosce.
**Dimostrazione**:
- $\Rightarrow$ Sia $A$ regolare, per definizione esiste un DFA $D$ tale che $L(D)=A$, converto quindi $D$ in un NFA equivalente
- $\Leftarrow$ Assumiamo che esista un NFA $N$ tale che $L(N)=A$, converto $N$ in un DFA equivalente e verifico la [[Automi a stati finiti#Linguaggio regolare|regolarità]]

#### Chiusura rispetto alla concatenazione
Dimostriamo che se $A$ e $B$ sono due linguaggi regolari, allora $A\circ B$ è regolare.
Data una stringa $w=abbaa$ non è possibile sapere dove inizia la sottostringa di $A$ e quella di $B$, per cui dobbiamo costruire un NFA.

Essendo $A$ e $B$ regolari allora esistono gli NFA $N_1$ e $N_2$ tali che $L(N_1)=A$ e $L(N_2)=B$, costruiamo un nuovo NFA $N$ tale che $L(N)=A\circ B$.
$N_1=(Q_1,\Sigma,\delta_1,q_1,F_1)$
$N_2=(Q_2,\Sigma,\delta_2,q_2,F_2)$
$N=(Q,\Sigma,\delta,q_0,F)$

L'idea è: al posto di accettare in $N_1$ eseguo una $\epsilon$-transizione allo stato iniziale di $N_2$:
![[Concatenazione NFA.png]]

- $Q=Q_1\cup Q_2$ (gli stati sono l'unione di quelli di $N_1$ e $N_2$)
- $q_0=q_1$ (la prima sottostringa sarà di $A$)
- $F=F_2$ (la seconda sottostringa sarà di $B$)
- $\delta(q,a)=\begin{cases}\delta_1(q,a)&\text{se }q\in Q_1\setminus F_1\\\delta_2(q,a)&\text{se }q\in Q_2\\\delta_1(q,a)&\text{se }q\in F_1\land a\neq\epsilon\\\{q_2\}\cup\delta_1(q,a)&\text{se }q\in F_1\land a=\epsilon\end{cases}$
	dove $q\in Q$ e $a\in\Sigma\cup\{\epsilon\}$:
	1. Si comporta come la transizione di $N_1$ se siamo su uno stato di $N_1$ che non è accettante
	2. Si comporta come la transizione di $N_2$ se siamo su uno stato di $N_2$
	3. Si comporta come la transizione di $N_1$ se siamo su uno stato accettante di $N_1$ che non effettua una $\epsilon$-transizione
	4. Si comporta come la transizione di $N_1$ se siamo su uno stato accettante di $N_1$ che effettua una $\epsilon$-transizione interna ad $N_1$, altrimenti si passa all'automa $N_2$

#### Chiusura rispetto a star
Dimostriamo che se $A$ è un linguaggio regolare, allora anche $A^*$ è regolare.
Data una stringa $w=abbabb$ non è possibile sapere dove inizia quale sottostringa di $A$, per cui useremo un NFA.

L'idea è quella di sostituire lo stato iniziale con un altro (nuovo) stato accettante collegato allo stato iniziale originale tramite una $\epsilon$-transizione, in questo modo sarà possibile accettare anche la stringa vuota, inoltre colleghiamo gli stati accettanti originali allo stato iniziale tramite delle $\epsilon$-transizioni, in questo modo potremmo continuare ad accettare un'altra eventuale sottostringa.

![[Star NFA.png]]
Sia $N_1$ l'NFA che riconosce $A_1$ definito come $N_1=\{Q_1,\Sigma,\delta_1,q_1,F_1\}$, costruiamo $N=\{Q,\Sigma,\delta,q_0,F\}$ per riconoscere $A_1^*$.
1. $Q=\{q_0\}\cup Q_1$ (gli stati di $N$ sono gli stati di $N_1$ più un nuovo stato iniziale)
2. Lo stato $q_0$ è il nuovo stato iniziale
3. $F=\{q_0\}\cup F_1$ (gli stati accettanti sono i vecchi stati accettanti più il nuovo stato iniziale)
4. Definiamo $\delta$ in modo che per ogni $q\in Q$ e ogni $a\in\Sigma_\epsilon$:
$$\delta(q,a)=\begin{cases}
\delta_1(q,a)&q\in Q_1\land q\notin F_1\\
\delta_1(q,a)&q\in F_1\land a\neq\epsilon\\
\delta_1(q,a)\cup\{q_1\}&q\in F_1\land a=\epsilon\\
\{q_1\}&q=q_0\land a=\epsilon\\
\emptyset&q=q_0\land a\neq\epsilon
\end{cases}$$
