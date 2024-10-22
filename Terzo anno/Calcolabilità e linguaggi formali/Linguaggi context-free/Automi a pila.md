Gli **automi a pila** o **PushDown Automata (PDA)** possono essere descritti informalmente come un [[Automi a stati finiti non deterministici#Definizione di NFA|NFA]] + Stack, ovvero legge l'input sequenzialmente come un NFA, ha uno stato interno che può cambiare, e ha a disposizione uno stack _infinito_ dove può leggere e scrivere.

Consideriamo il linguaggio [[Linguaggi non regolari|non regolare]] $\{0^n1^n|n\geq 0\}$, il PDA ogni volta che leggerà uno $0$ eseguirà il push di uno $0$ sullo stack, mentre quando arriverà un $1$ cambierà stato e continuerà a fare pop finchè arrivano $1$, alla fine dell'input se lo stack è vuoto il linguaggio sarà riconosciuto.
Può rifiutare in nel caso in cui l'input è finito e lo stack non è vuoto, quando arriva uno $0$ dopo un $1$.
>NFA+Stack $\neq$ DFA+Stack anche se DFA e NFA sono convertibili tra loro.

### Definizione di PDA
Un PDA è una sestupla $(Q,\Sigma, \Gamma, \delta, q_0, F)$, dove:
- $Q$ è un insieme finito di stati
- $\Sigma$ è l'alfabeto
- $\Gamma$ è l'alfabeto dello stack (si può leggere un carattere e eseguire il push di qualcosa di diverso)
- $\delta:Q\times\Sigma_\epsilon\times\Gamma_\epsilon\to\mathscr{P}(Q\times\Gamma_\epsilon)$ è la funzione di transizione
	dove $\Sigma_\epsilon=\Sigma\cup\{\epsilon\}$ e $\Gamma_\epsilon=\Gamma\cup\{\epsilon\}$.
- $q_0\in Q$ è lo stato iniziale
- $F\subseteq Q$ è l'insieme degli stati accettanti

Sia $M$ un PDA, diciamo che $M$ accetta la stringa $w$ sse $w=w_1w_2...w_m$ dove $\forall i\in[1,m]:w_i\in\Sigma_\epsilon$ ed esistono una sequenza di stati $r_0,r_1,...,r_m\in Q$ e una sequenza di stack $s_0,s_1,...,s_m\in\Gamma^*$ tali che valgono le seguenti condizioni:
1. $r_0=q_0$ e $s_0=\epsilon$
2. Per $i=0,...,m-1$ abbiamo $(r_{i+1},b)\in\delta(r_i,w_{i+1},a)$ dove $s_i=at$ e $s_{i+1}=bt$ per qualche $a,b\in\Gamma_\epsilon$ e $t\in\Gamma^*$
3. $r_m\in F$

>Il secondo punto dice che si è nello stato $r_i$, si legge $w_{i+1}$ e si va in $r_{i+1}$.
>$a$ è la head dello stack, $b$ è il nuovo simbolo inserito nelle head, mentre $t$ indica il resto dello stack.
>$a$ e $b$ possono essere caratteri da mettere nello stack, oppure $\epsilon$.

Nel secondo punto possono avvenire i seguenti casi:
- $a\neq\epsilon\quad b\neq\epsilon\implies\text{pop e push (assieme)}$ quindi uno swap di head
- $a=\epsilon\quad b\neq\epsilon\implies\text{push}$ perchè $a=\epsilon$ quindi $s_i=t$
- $a\neq\epsilon\quad b=\epsilon\implies\text{pop}$
- $a=\epsilon\quad b=\epsilon\implies$ lo stack non viene alterato

La **notazione grafica** di un PDA è la seguente:
![[Notazione PDA.svg|300]]
L'automa passa da $q_i$ a $q_j$ leggendo l'input $w$ quando $a$ è in cima allo stack;
$b$ è la nuova cima dello stack.

>[!Tip] Accettazione per stack vuoto
>Molti PDA vogliono accettare solo quando lo stack è vuoto, ma ciò non è richiesto dalla definizione formale.

Seguono alcuni esempi di PDA.
>[!Example]
>$$\{0^n1^n|n\geq 0\}$$
>![[PDA 1.png|300]]
>
>---
>
>$$\{ww^R|w\in\{0,1\}\}\text{ dove }w^R\text{ è }w\text{ letta da destra a sinistra}$$
>![[PDA 2.png|300]]
>
>È da notare come in entrambi gli esempi venga sfruttato il non determinismo, inoltre per capire quando lo stack è vuoto viene utilizzato il carattere $\$$ il quale viene pushato ad inizio computazione.

---
## Equivalenza tra CFG e PDA
**Teorema**: un linguaggio $A$ è context-free se e solo se esiste un PDA $P$ tale che $L(P)=A$.

**Corollario**: qualsiasi linguaggio regolare è anche context-free.
**Dimostrazione corollario**: sia $A$ un [[Automi a stati finiti#Linguaggio regolare|linguaggio regolare]], allora esiste un [[Automi a stati finiti non deterministici#Definizione di NFA|NFA]] $N$ tale che $L(N)=A$. Dato che un NFA è un PDA che non tocca lo stack si può dire che $N$ è anche un PDA, concludo pertanto che $A$ è context-free.
![[Linguaggi context-free e regolari.svg]]

**Dimostrazione teorema ($\Rightarrow$)**
Se $A$ è context-free, allora esiste un PDA $P$ tale che $L(P)=A$.

L'**idea** è, dato che $A$ è context-free, esiste una CFG $G$ tale che $L(G)=A$, converto quindi $G$ in un PDA equivalente.

Immaginiamo la seguente CFG:
- $S\to|AB|C$
- $A\to a$
- $B\to b|bB$

e consideriamo la stringa $w=abb$, essa può essere derivata come:
$$S\Rightarrow AB\Rightarrow aB\Rightarrow abB\Rightarrow abb$$
![[CFG to PDA.svg]]

>Questo metodo è chiamato **parsing top-down**, non è efficiente, ma è sufficiente per la dimostrazione.

Costruiamo  il seguente PDA a partire da $G$:
1. Metti sullo stack $\$$ e poi lo start symbol $S$
2. Ripeti i seguenti passi fino a terminazione in base a cosa è presente sulla cima dello stack:
	- C'è un _non terminale_ $A$, scegli non deterministicamente una produzione $A\to u_1,...,u_k$ e fai push di $u_k,...,u_1$ dopo aver fatto pop di $A$
	- C'è un _terminale_ $a$, confrontalo con il prossimo carattere di input, se sono uguali fai pop, altrimenti rifiuta
	- C'è $\$$, passa allo stato di accettazione, ciò comporta accettazione se ho consumato tutto l'input

La rappresentazione grafica del precedente algoritmo è la seguente:
![[CFG to PDA rappresentazione grafica.svg|500]]

**Dimostrazione teorema ($\Leftarrow$)**
Sia $A$ un linguaggio tale che esiste un PDA $P$ tale che $L(P)=A$, allora $A$ è context-free.

L'**idea** è quella di convertire $P$ in una CFG $G$ tale che $L(P)=L(G)$.

**Disciplinare il PDA**: il PDA in questione deve avere le seguenti tre proprietà.
1. $P$ ha un solo stato accettante $q_{accept}$
	È possibile eseguire una $\epsilon$-transizione dagli stati accettanti ad un nuovo stato accettante.

2. $P$ accetta solo con lo stack vuoto
	Dagli (ex) stati accettanti eseguiamo il pop di tutti gli elementi nello stack prima di andare nel nuovo stato accettante tramite la $\epsilon$-transizione.

3. Ogni mossa di $P$ è una push oppure una pop
	Questa condizione può essere violata da $\epsilon\to\epsilon$ (risolto eseguendo prima push e poi pop di un simbolo _dummy_) e da $a\to b$ (risolto aggiungendo uno stato intermedio e trasformando tale operazione in $a\to\epsilon$ e poi $\epsilon\to b$).

>Tali proprietà non hanno perdita di generalità.

**Generare la CFG**
Definiamo una nuova CFG che contiene un non-terminale $A_{pq}$ per ogni coppia di stati $p,q$ del PDA, la CFG inoltre conterrà delle operazioni opportune che hanno l'obiettivo di simulare le transizioni del PDA.

Tale CFG ci assicura che $A_{pq}$ deriva una stringa $x$ sse il PDA passa da $p$ con stack vuoto a $q$ con stack vuoto leggendo $x$.
Definiamo quindi come start symbol della CFG il non-terminale $A_{q_0, q_{accept}}$, dove $q_0$ è lo stato iniziale del PDA e $q_{accept}$ è il suo stato accettante.

Per realizzare tale CFG le produzioni potranno avere tre possibili formati:
1. $A_{pp}\to\epsilon$ per ogni stato $p$ del PDA
2. $A_{pq}\to A_{pr}A_{rq}$ per ogni tripla di stati $p,q,r$ del PDA
3. Se $(r,u)\in\delta(p,a,\epsilon)$ e $(q,\epsilon)\in\delta(s,b,u)$ allora produco $A_{pq}\to aA_{rs}b$

>$p$ = stato di partenza, $q$ = stato di arrivo, $a$ = primo simbolo letto, $b$ = ultimo simbolo letto, $r$ = secondo stato, $s$ = penultimo stato, $u$ = primo simbolo che metto sullo stack e anche ultimo simbolo di cui si esegue il pop dallo stack.

**Condizione critica**
$A_{pq}\Rightarrow^* x$ se e solo se $P$ parte da $p$ con stack vuoto ed arriva in $q$ con stack vuoto processando $x$.

**Dimostrazione condizione critica ($\Rightarrow$)**
Se $A_{pq}\Rightarrow^* x$, allora $x$ porta $P$ da $p$ con lo stack vuoto a $q$ con lo stack vuoto.

**Caso base**: in questo caso la derivazione deve essere di lunghezza pari a $1$, l'unica produzione applicabile che non contiene non-terminali nella parte destra è $A_{pp}\to\epsilon$, ovvero $A_{pp}\Rightarrow\epsilon$, abbiamo quindi che l'input $\epsilon$ porta $P$ da $p$ con lo stack vuoto a $p$ con lo stack vuoto.

**Passo induttivo**: consideriamo derivazioni di lunghezza $>1$