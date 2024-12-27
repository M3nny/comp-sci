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
	2. Se $n> 0$, $w=0^{m+1}\#1^{m+1}$ con $m\geq 0$, per ipotesi induttiva $A\Rightarrow^*0^m\# 1^m$ ma allora: $A\Rightarrow 0A1\Rightarrow^* 00^m\#1^m1$

### Ambiguità
Una CFG è ambigua sse esiste $w\in L(G)$ tale che $w$ possiede almeno due parse tree differenti.

Ad esempio: $E\to E+E|E\cdot E|a$ può generare $a+a\cdot a$, ma esistono vari parse tree per questa stringa, infatti $E$ potrebbe produrre prima una somma oppure un prodotto.

L'ambiguità è un problema poichè non si sa come interpretare la stringa, in un compilatore è preferibile la derivazione che produce $E\cdot E$ per secondo in modo da valutarlo per primo ricorsivamente: $E\Rightarrow E+E\Rightarrow a+E\Rightarrow a+E\cdot E\Rightarrow a+a\cdot a$.

### Chiusura delle grammatiche context-free
Consideriamo i due start symbol $S_1$ e $S_2$, per i linguaggi $L_1$ e $L_2$, vediamo come generare delle grammatiche per dimostrare la chiusura rispetto ai seguenti operatori:
- **Unione**: $S\to S_1|S_2$
- **Concatenazione**: $S\to S_1S_2$
- **Star**: $S\to S_1S|\epsilon$

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

2. Eliminiamo le produzioni della forma $A\to\epsilon$ (con $A\neq S$), di seguito per tutte le regole che hanno $A$ nella parte destra introduciamo una nuova regola considerando $A$ cancellato, ripetendo per ogni $A$ a destra

$$R\to uAvAw\quad\text{diventa}\quad R\to uvAw|uAvw|uvw$$

3. Eliminiamo le produzioni della forma $A\to B$ (dette _unitarie_). Per tutte le regole della forma $B\to u$, introduciamo una nuova regola $A\to u$.

4. Sostituiamo ogni regola della forma $A\to u_1,u_2,...,u_k$ con $k\geq 3$ con nuove regole $A\to u_1A_1$, $A_1\to u_2A_2$, ..., $A_{k-2}\to u_{k-1}u_k$.

Alla fine la grammatica sarà composta da derivazioni da **1 terminale**, oppure **2 non terminali**.

>[!Attention]
>L'ordine dei passaggi è importante.
>Nel secondo e terzo punto bisogna tenere traccia delle produzioni eliminate, se si dovessero ripresentare non bisogna reinserirle, altrimenti verrebbe a crearsi un ciclo.

>[!Example]
>Sia data la seguente grammatica:
>$$\begin{align}
>&S\to ASA|aB\\
>&A\to B|S\\
>&B\to b|\epsilon
>\end{align}$$
>---
>**Creazione del nuovo starting symbol**
>- $S'\to S$
>- $S\to ASA|aB$
>- $A\to B|S$
>- $B\to b|\epsilon$
>---
>**Rimozione delle $\epsilon$**
>- $S'\to S$
>- $S\to ASA|aB|a|SA|AS|S$
>- $A\to B|S$
>- $B\to b$
>---
>**Rimozione delle produzioni unitarie**
>- $S'\to ASA|aB|a|SA|AS$
>- $S\to ASA|aB|a|SA|AS$
>- $A\to b|ASA|aB|a|SA|AS$
>- $B\to b$
>---
>**Rimozione delle produzioni con più di due non terminali, con "rinominazione" dei terminali extra e successiva "rinominazione" dei terminali nelle produzioni miste**
>$$\begin{align}
>&S'\to AA_1|UB|a|SA|AS\\
>&S\to AA_1|UB|a|SA|AS\\
>&A\to b|AA_1|UB|a|SA|AS\\
>&B\to b\\
>&A_1\to SA\\
>&U\to a
>\end{align}


a