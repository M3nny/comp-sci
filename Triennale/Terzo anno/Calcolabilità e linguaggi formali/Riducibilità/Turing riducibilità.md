Intuitivamente possiamo immaginare che la riduzione $\bar A_{TM}\leq_m A_{TM}$ sia possibile, infatti dato un decisore per un problema, la sua variante complementata si dovrebbe poter ottenere invertendone il risultato.

Questa proprietà formalmente però non vale, infatti abbiamo visto che $A_{TM}$ [[Indecidibilità#Accettazione - macchina di Turing|è Turing-riconoscibile]], mentre il suo complemento $\bar A_{TM}$ [[Indecidibilità#Linguaggi decidibili|non lo è]], per cui dal [[Riduzione attraverso funzioni#Turing-riconoscibilità|corollario della Turing-riconoscibilità]], sappiamo che non è possibile eseguire quel tipo di riduzione tramite funzione.

Serve quindi introdurre un nuovo tipo di riducibilità più intuitiva.

## Turing-riducibilità
Per prima cosa diamo alcune definizioni.
- Un **oracolo** per un linguaggio $B$ è un dispositivo (non specificato) che per ogni stringa $w$ ritorna _accept_ se $w\in B$ e _reject_ se $w\notin B$
- Una **MdT con oracolo** per il linguaggio $B$ è una MdT estesa con la possibilità di interrogare un oracolo
- Un linguaggio $A$ è Turing-riducibile ad un linguaggio $B$, rappresentato con la notazione $A\leq_T B$, sse esiste una _MdT con oracolo_ per $B$ che decide $A$

**Osservazione**: $\bar A_{TM}\leq_T A_{TM}$.
**Dimostrazione**: costruiamo una MdT $M$ con oracolo per $A_{TM}$ che decide $\bar A_{TM}$.
$M$ = su input $w$:
1. Invoca l'oracolo per $A_{TM}$
2. Inverti il suo output

**Osservazione**: $E_{TM}\leq_T A_{TM}$
**Dimostrazione**: costruiamo una MdT $M'$ con oracolo per $A_{TM}$ che decide $E_{TM}$.
$M'$ = su input $<M>$:
1. Costruisci una nuova MdT $N$ con la seguente proprietà:
$$L(N)=\begin{cases}
\Sigma^*&\text{se }L(M)\neq\emptyset\\
\emptyset&\text{se }L(M)=\emptyset
\end{cases}$$
2. Invoca l'oracolo per $A_{TM}$ su input $<N,1>$ ($1$ è una stringa arbitraria)
3. Ritorna l'output invertito dell'oracolo

La definizione di $N$ è la seguente:
$N$ = su input $x$:
1. Per $i=1,2,3,...$
	- Esegui $M$ su $x_i$ per $i$ passi (per evitare di andare in loop)
2. Se una di tali computazioni accetta, _accept_

**Osservazione**: $\overline{EQ}_{TM}\leq_T A_{TM}$
**Dimostrazione**: costruiamo una MdT $M$ con oracolo per $A_{TM}$ che decide $\overline{EQ}_{TM}$.
$M$ = su input $<M_1,M_2>$:
1. Sia $\Sigma^* = \{w_1,w_2,w_3,\dots\}$
2. Per $i=1,2,3\dots$
	- Usa l'oracolo per $A_{TM}$ per testare se $M_1$ e $M_2$ accettano $w_i$
	- Se i risultati sono diversi, accetta
### Decidibilità con Turing-riduzione
**Teorema**
Se $A\leq_T B$ e $B$ è decidibile, allora $A$ è decidibile.

**Dimostrazione**
Sia $A\leq_T B$, allora esiste una MdT con oracolo per $B$ che decide $A$.
È quindi possibile creare un decisore per $A$ sostituendo tutte le chiamate all'oracolo per $B$ con chiamate al decisore per $B$.

**Corollario**
Se $A\leq_T B$ e $A$ è indecidibile, allora $B$ è indecidibile.

#### Relazione tra mapping riducibilità e Turing-riducibilità
$$A\leq_m B\implies A\leq_T B$$
Se $A\leq_m B$, allora esiste una $f$ calcolabile tale che $\forall w$, $w\in A\iff f(w)\in B$.
Costruiamo quindi una MdT $M$ con oracolo per $B$ che decide $A$ come segue:
$M$ = su input $w$:
1. Calcola $f(w)$
2. Esegui l'oracolo per $B$ su $f(w)$
3. Ritorna il suo output

| Mapping-riducibilità                                                                                                                     | Turing-riducibilità                                              |
| ---------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------- |
| $(+)$ Permette di dimostrare che certi problemi non sono Turing-riconoscibili.<br>Se $A\leq_m B$ e $A$ non è T.r., allora $B$ non è T.r. | $(+)$ Più intuitiva<br>E.g. $\bar A_{TM}\leq_T A_{TM}$           |
| $(-)$ Non cattura certe riduzioni "intuitive".<br>E.g. $\bar A_{TM}\cancel{\leq_m} A_{TM}$.                                              | $(+)$ Se vale $\leq_m$ allora vale anche $\leq_T$                |
|                                                                                                                                          | $(-)$ Non ci aiuta a dimostrare che certi problemi non sono T.r. |

