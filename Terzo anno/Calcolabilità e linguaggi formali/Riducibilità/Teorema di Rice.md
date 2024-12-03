$$\text{Qualsiasi proprietà non banale del linguaggio di una MdT è indecidibile.}$$

Una **proprietà** di una MdT è un'insieme $P$ contenente una serie di descrizioni $<M_1>,<M_2>,...$ di MdT, ovvero un linguaggio.

Una **proprietà non banale** è una proprietà tale per cui esistono delle MdT $M$ e $N$ tali che $<M>\in P$ e $<N>\notin P$, ovvero $P$ è soddisfatta da certe MdT, ma non da altre.

Una **proprietà del linguaggio** è una proprietà tale che per ogni MdT $M$ e $N$ tali che $L(M)=L(N)$, allora $<M>\in P\iff <N>\in P$, ovvero se $M$ e $N$ hanno lo stesso linguaggio, o $P$ vale sia per $M$ e per $N$, oppure $P$ non vale per nessuna delle due MdT.

**Dimostrazione**
Sia $P$ una proprietà (linguaggio) _non banale_ del linguaggio di una MdT.
Assumiamo per assurdo che $P$ sia _decidibile_ e sia $H$ il suo decisore.

In tal caso riusciremo a costruire per riduzione un decisore per $A_{TM}$, il che è assurdo in quanto $A_{TM}$ è indecidibile. 
Sia $S$ il decisore per $A_{TM}$.
$S$ = su input $<M,w>$:
1. Costruisci una nuova MdT $N$ tale che:
$$L(N)=\begin{cases}
\text{Ha la proprietà }P&\text{ se }M\text{ accetta }w\\
\text{Non ha la proprietà }P&\text{ altrimenti}
\end{cases}$$
2. Esegui $H$ su input $<N>$
3. Ritorna il suo output

Vediamo come è costruita $N$.
Visto che $P$ è non banale, devono esistere almeno una MdT che soddisfa $P$ e una MdT che non soddisfa $P$.
- Assumiamo senza perdita di generalità che la MdT $V_\emptyset$ tale che $L(V_\emptyset)=\emptyset$ non soddisfi $P$, cioè $<V_\emptyset>\notin P$
- Sia invece $T$ una MdT che soddisfa $P$, cioè $<T>\in P$

Costruiamo la MdT $N$ come segue:
$N$ = su input $x$:
1. Esegui $M$ su $w$
2. Se $M$ rifiuta, _reject_
3. Se $M$ accetta, simula $T$ su $x$ e ritorna il suo output

$$L(N)=\begin{cases}
L(T)&\text{se }M\text{ accetta }w\\
L(V_\emptyset) (\text{uguale a }\emptyset)&\text{altrimenti}
\end{cases}$$

>[!Tip] Implicazioni del teorema di Rice
>Con il teorema di Rice possiamo affermare che qualsiasi proprietà ragionevole non è decidibile da un programma, i software di testing infatti eseguono solo delle approssimazioni.
