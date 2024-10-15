Un esempio di **grammatica context-free (CFG)** è:
- $A \to 0A1 | B$
- $B \to \#$ 
Queste sono dette **produzioni (o regole)**, e indicano che $A$ può riscriversi come $0A1$ oppure come $B$, il quale si può riscrivere come $\#$.

Indichiamo $A,B$ come **non-terminali (o variabili)**, mentre $0,1,\#$ come **terminali**.
Le stringhe generate sono le stringhe di terminali ottenibili a partire dallo **start symbol** (non terminale) il quale solitamente è il _non terminale_ della prima produzione.

Sviluppando la grammatica otteniamo una **derivazione**:
$$A\Rightarrow 0A1 \Rightarrow 00A11 \Rightarrow 00A11 \Rightarrow 00B11 \Rightarrow 00\#11$$
>La quale rappresenta il linguaggio $L(G)=\{0^n\#1^n|n\geq 0\}$

Le derivazioni possono essere anche scritte come **parse tree**, dove la frontiera dell'albero costituisce la stringa in questione:
![[Parse tree.svg|200]]

Un **linguaggio** $A$ si dice _context-free_ sse esiste una CFG tale che $L(G)=A$, ovvero sse esiste una CFG che lo genera.

Una **CFG** $G$ è una **quadrupla** $(V,\Sigma,R,S)$, dove:
1. $V$ è un insieme finito di non terminali
2. $\Sigma$ è un insieme finito di terminali tali che $V\cap\Sigma=\emptyset$
3. $R$ è un insieme finito di produzioni della forma $A\to w$, dove $A\in V$ e $w\in(V\cup\Sigma)^*$ (stringhe di terminali e non terminali includendo anche $\epsilon$)
4. $S\in V$ è lo start symbol

Riprendendo l'esempio iniziale:
- $A\to 0A1|B$
- $B\to \#$
$V=\{A,B\}$, $\Sigma=\{0,1\#\}$, $R=\{A\to0A1, A\to B, B\to\#\}$, $S=A$.

>[!Info] Significato di context-free
>Il significato di **context-free** deriva dal fatto che i non-terminali si possono riscrivere nella loro parte a destra indipendentemente dal contesto.
>Una grammatica dipendente dal contesto invece è: $aA\to aa$.

Siano ora $u,v\in(V\cup\Sigma)^*$ e una $A\to w\in R$, diciamo che $uAv\underbrace{\Rightarrow}_\text{produce} uwv$, ovvero è sempre possibile scrivere un non terminale in base alle produzioni possibili.

Diciamo che $u\underbrace{\Rightarrow^*}_\text{deriva}v$ sse $u=v$ oppure $u\Rightarrow w_1\Rightarrow...\Rightarrow v$ per qualche $w_1,...$
>Utilizzando l'esempio precedente abbiamo che $A\Rightarrow^* 00\#11$.

Sia $G=(V,\Sigma,R,S)$, una CFG, definiamo il suo linguaggio come $L(G)=\{w\in\Sigma^*|S\Rightarrow^* w\}$.

>[!Example]
>Sia $\Sigma=\{0,1\}$ fornire una CFG per i seguenti linguaggi:
>1. Stringhe che comprendono almeno tre $1$
>	- $S\to A1A1A1A$
>	- $A\to 0A|1A|\epsilon$, oppure $A\to 0|1|AA|\epsilon$
>2. Stringhe che iniziano e finiscono con lo stesso simbolo
>	- $S\to 0A0|1A1|0|1$
>	- $A\to 0A|1A|\epsilon$
>3. Stringhe di lunghezza dispari
>	- $S\to CP$
>	- $C\to 0|1$
>	- $P\to 00P|01P|10P|11P|\epsilon$
>4. Stringhe palindrome
>	- $S\to 0S0|1S1|0|1|\epsilon$
>5. Nessuna stringa
>	- $S\to S$

### Correttezza di una CFG
Si considerino le seguenti produzioni:
- $A\to 0A1|B$
- $B\to \#$

si consideri inoltre il seguente linguaggio $L(G)=\{0^n\#1^n|n\geq 0\}$.
Dimostriamo che $w\in L(G)$ sse $w=0^n\#1^n$ per qualche $n\geq 0$.
- $(\Rightarrow)$ Sia $w\in L(G)$, allora $A\Rightarrow^*w$, eseguiamo una induzione sulla lunghezza della derivazione distinguendo due casi:
	1. $A\Rightarrow 0A1\Rightarrow^* w$, allora $w=0v1$ con $A\Rightarrow v$, per ipotesi induttiva $v=0^m\#1^m$ con $m\geq 0$, ma allora $w=0^{m+1}\#1^{m+1}$
	2. $A\Rightarrow B\Rightarrow^* w$, in questo caso $w=\#$, quindi $w$ ha la forma giusta

- $(\Leftarrow)$ Sia $w=0^n\#1^n$ con $\geq 0$, dimostro che $w\in L(G)$, eseguiamo una induzione su $n$ distinguendo due casi:
	1. Se $n=0$, $w=\#$ e $A\Rightarrow B\Rightarrow \#$
	2. Se $n> 0$, $w=O^{m+1}\#1^{m+1}$ con $m\geq 0$, per ipotesi induttiva $A\Rightarrow^*0^m\# 1^m$ ma allora: $A\Rightarrow 0A1\Rightarrow^* 00^m\#1^m1$

### Ambiguità
Una CFG è ambigua sse esiste $w\in L(G)$ tale che $w$ possiede almeno due parse tree differenti.

Ad esempio: $E\to E+E|E\cdot E|a$ può generare $a+a\cdot a$, ma esistono vari parse tree per questa stringa, infatti $E$ potrebbe produrre prima una somma oppure un prodotto.

L'ambiguità è un problema poichè non si sa come interpretare la stringa, in un compilatore è preferibile la derivazione che produce $E\cdot E$ per secondo in modo da valutarlo per primo ricorsivamente: $E\Rightarrow E+E\Rightarrow a+E\Rightarrow a+E\cdot E\Rightarrow a+a\cdot a$.

### Forma normale di Chomsky
Una CFG è in forma normale di **Chomsky** sse ognuna delle sue produzioni è in uno dei seguenti formati:
1. $A\to BC$, dove $B,C\neq S$
2. $A\to a$
3. $S\to \epsilon$

Ad esempio la seguente CFG è in forma normale di Chomsky:
	$S\to AB|\epsilon$
	$A\to 0$
	$B\to CD$
	$C\to 1$
	$d\to 1$

**Teorema**: ogni CFG può essere riscritta in forma normale di Chomsky.
**Dimostrazione**: definiamo un algoritmo che converte una CFG in un'altra CFG equivalente che soddisfa la forma normale di Chomsky.
1. Generiamo un nuovo start symbol $S'$ ed aggiungiamo la produzione $S'\to S$, in questo modo tale trasformazione preserva il linguaggio e assicura per costruzione che lo start symbol non occorre a destra di una produzione.

2. Eliminiamo le produzioni della forma $A\to\epsilon$ (con $A\neq S$). Per tutte le regole della forma $R\to uAv$ introduciamo una nuova regola $R\to uv$ (questo va fatto per tutte le occorrenze di $A$):

$$R\to uAvAw\quad\text{diventa}\quad R\to uvAw|uAvw|uvw$$

3. Eliminiamo le produzioni della forma $A\to B$ (dette _unitarie_). Per tutte le regole della forma $B\to u$, introduciamo una nuova regola $A\to u$.

4. Sostituiamo ogni regola della forma $A\to u_1,u_2,...,u_k$ con $k\geq 3$ con nuove regole $A\to u_1A_1$, $A_1\to u_2A_2$, ..., $A_{k-2}\to u_{k-1}u_k$.

>[!Attention]
>L'ordine dei passaggi è importante.
>Nel secondo e terzo punto bisogna tenere traccia delle produzioni eliminate, se si dovessero ripresentare non bisogna reinserirle, altrimenti verrebbe a crearsi un ciclo.

>[!Example]
>Sia data la seguente grammatica:
>- $S\to ASA|aB$
>- $A\to B|S$
>- $B\to b|\epsilon$
>
>La sua conversione in forma normale di Chomsky è la seguente:
>- $S\to AA_1|UB|a|SA|AS$
>- $A\to b|AA_1|UB|a|SA|AS$
>- $B\to b$
>- $S'\to AA_1|UB|a|SA|AS$
>- $A_1\to SA$
>- $U\to a$

---
## Automi a pila
Gli **automi a pila** o **PushDown Automata (PDA)** possono essere descritti informalmente come un [[Automi a stati finiti non deterministici#Definizione di NFA|NFA]] + Stack, ovvero legge l'input sequenzialmente come un NFA, ha uno stato interno che può cambiare, e ha a disposizione uno stack _infinito_ dove può leggere e scrivere.

Consideriamo il linguaggio [[Linguaggi non regolari|non regolare]] $\{0^n1^n|n\geq 0\}$, il PDA ogni volta che leggerà uno $0$ eseguirà il push di uno $0$ sullo stack, mentre quando arriverà un $1$ cambierà stato e continuerà a fare pop finchè arrivano $1$, alla fine dell'input se lo stack è vuoto il linguaggio sarà riconosciuto.
Può rifiutare in nel caso in cui l'input è finito e lo stack non è vuoto, quando arriva uno $0$ dopo un $1$.
>NFA+Stack $\neq$ DFA+Stack anche se DFA e NFA sono convertibili tra loro.

### Definizione di PDA
Un PDA è una sestupla $(Q,\Sigma, \Gamma, \delta, q_0, F)$, dove:
- $Q$ è un insieme finito di stati
- $\Sigma$ è l'alfabeto
- $\Gamma$ è l'alfabeto dello stack (si può leggere un carattere e eseguire il push di qualcosa di diverso)
- $\delta:Q\times\Sigma_\epsilon\times\Gamma_\epsilon\to\mathscr{P}(Q\times\Gamma)$ è la funzione di transizione
	dove $\Sigma_\epsilon=\Sigma\cup\{\epsilon\}$ e $\Gamma_\epsilon=\Gamma\cup\{\epsilon\}$.


