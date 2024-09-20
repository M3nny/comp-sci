Un **Deterministic Finite Automata (DFA)** è un riconoscitore di stringhe, le stringhe da esso accettate formano un **linguaggio**.

Un DFA $D$ è una quintupla $(Q,\Sigma, \delta, q_0, F)$ dove:
- $Q$: è un insieme finito di stati
- $\Sigma$: è un insieme finito di input, detto **alfabeto**
- $q_0\in Q$: è lo stato iniziale
- $F\subseteq Q$: è l'insieme degli stati accettanti, essi possono essere $\geq 0$
- $\delta$: è dato da $Q\times\Sigma\rightarrow Q$ e rappresenta la funzione di transizione

![[DFA.svg]]

Il DFA sopra rappresentato è definito come:
- $Q=\{q_1,q_2,q_3\}$
- $\Sigma=\{0,1\}$
- $q_0=q_1$
- $F=\{q_2\}$
- $\delta(q_1,0)=q_1$, $\delta(q_1, 1)=q_2$ $...$ ($6$ in totale)
>Il numero di funzioni di transizione $\delta$ è dato da $|\Sigma|\cdot|Q|$.

In questo caso il _linguaggio_ di $D$ è dato da:
$$L(D)=\{w\in\{0,1\}^*|\text{ esiste almeno un 1 e dopo l'ultimo 1 è presente un numero pari di 0}\}$$
>$\{0,1\}^*$ indica tutte le stringhe (anche infinite) composte da $0$ e $1$, vedi [[Automi a stati finiti#Operazioni regolari|operatore star]].

>[!Attention]
>Non viene definito DFA una quintupla in cui non è definito uno stato iniziale e/o almeno uno stato accettante, inoltre ogni stato stato deve avere $|\Sigma|$ funzioni di transizione, ovvero una per ogni input.

## Linguaggio
Sia $M=(Q,\Sigma, \delta, q_0, F)$, e sia $w=w_1, w_2,...,w_m$ una stringa tale che $\forall i\in[1,n]:w_i\in\Sigma$, diciamo che $M$ accetta $w$ sse esistono degli stati $r_0,...,r_n\in Q$ tali che:
1. $r_0=q_0$, ovvero il primo stato è quello iniziale
2. $r_n\in F$, ovvero l'ultimo stato è uno stato accettante
3. $\forall i\in[0,n-1]:\delta(r_i,w_{i+1})=r_{i+1}$ 

Il linguaggio riconosciuto da un DFA $M$ è indicato con $L(M)$, ed esso rappresenta l'insieme delle stringhe accettate da $M$.

### Linguaggio regolare
Un linguaggio $A$ si dice regolare sse esiste un DFA $M$ tale che $L(M)=A$, ovvero esiste un DFA in grado di implementare tale linguaggio.

Per il momento ci limitiamo a costruire un DFA per dimostrare la regolarità di un linguaggio.

>[!Example]
>Dimostrare che l'insieme delle stringhe binarie che contengono la sottostringa $001$ è regolare.
>
>![[Dimostrazione regolarità.svg]]

## Operazioni regolari
Siano $A,B$ due linguaggi qualsiasi, definiamo le seguenti tre operazioni regolari:
1. **Unione**: $A\cup B=\{w|w\in A \lor w\in B\}$
2. **Concatenazione**: $A\circ B=\{w_1w_2|w_1\in A\land w_2\in B\}$
3. **Star**: $A^*=\{w_1w_2...w_k|\forall i\in[1,k]:w_i\in A\land k\geq 0\}$

>[!Example]
>$A=\{a,b\}$ $B=\{a, c\}$
>- $A\cup B=\{a,b,c\}$
>- $A\circ B=\{aa,ac,ba,bc\}$ (cardinalità pari a $|A|\cdot |B|$)
>- $B^*=\{\epsilon, a, c, aa, ac, ca, cc,...\}$ (cardinalità $\infty$)

**Teorema**:
La classe dei linguaggi regolari è chiusa rispetto alle operazioni regolari, ovvero se $A$ e $B$ sono regolari, allora $A\cup B$, $A\circ B$, $A^*$ sono tutti linguaggi regolari.

Dimostrazione per _unione_:
Siano $A,B$ linguaggi regolari, allora esistono due DFA $M_1=(Q_1,\Sigma_1, \delta_1, q_1, F_1)$ e $M_2=(Q_2,\Sigma_2, \delta_2, q_2, F_2)$ tali che $L(M_1)=A$ e $L(M_2)=B$, costruiamo un nuovo DFA $M$ tale che $L(M)=A\cup B$.

L'idea è quella di simulare $M_1$ e $M_2$ "in parallelo".
Sia $M=(Q,\Sigma, \delta, q_0, F)$ il DFA definito come segue (ricordando che stiamo usando coppie):
- Assumiamo che gli alfabeti siano uguali $\Sigma_1=\Sigma_2=\Sigma$, (funzionerebbe lo stesso anche se non lo fossero)
- $Q=Q_1\times Q_2=\{(q_1,q_2)|q_1\in Q_1 \land\ q_2\in Q_2\}$
- $q_0=(q_1,q_2)$
- $F=\{(r_1,r_2)\in Q|r_1\in F_1\lor r_2\in F_2\}$
- $\delta((r_1,r_2), a)=(\delta_1(r_1, a), \delta_2(r_2, a))$
	Dato che vengono eseguiti in parallelo, la funzione di transizione è equivalente alla funzione di transizione applicata su $M_1$ e $M_2$ in parallelo.

