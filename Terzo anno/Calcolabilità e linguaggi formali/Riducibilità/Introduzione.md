Utilizziamo il concetto di **riducibilità** (vedi: [[Teoria della NP completezza#Classe NPC|riducibilità polinomiale]]) per dimostrare l'[[Indecidibilità|indecidibilità]].

Intuitivamente diciamo che un linguaggio $A$ è **riducibile** a $B$ ($A\leq B$) quando una soluzione per $B$ ci consente di costruire una soluzione per $A$.
- Se $A\leq B$ e $B$ è _decidibile_, allora anche $A$ è _decidibile_
- Se $A\leq B$ e $A$ è _indecidibile_, allora anche $B$ è _indecidibile_
>Ad esempio eseguendo una riduzione da $A_{TM}$ a $B$ dimostriamo che anche $B$ è indecidibile.

#### Problema della fermata
Questo problema chiamato anche come **halting problem**, chiede di determinare se una MdT terminerà.
$$HALT_{TM}=\{<M,w>|M\text{ è una MdT che termina su input }w\}$$

**Teorema**: $HALT_{TM}$ è _indecidibile_.

Assumiamo per assurdo che esista un decisore $N$ per $HALT_{TM}$, dimostriamo che $A_{TM}$ è riducibile a $HALT_{TM}$ ($A_{TM}\leq HALT_{TM}$), ovvero risolviamo il problema $A_{TM}$ sfruttando una soluzione per $HALT_{TM}$, essendo $HALT_{TM}$ decidibile (per ipotesi assurda), concluderemo che anche $A_{TM}$ è decidibile, ma questo sarebbe assurdo in quanto $A_{TM}$ [[Indecidibilità#Accettazione - macchina di Turing|è indecidibile]], per cui $HALT_{TM}$ non può essere decidibile.

Costruiamo il decisore $S$ per $A_{TM}$.
$S$ = su input $<M,w>$:
1. Esegui il decisore per $HALT_{TM}$ ($N$) su $<M,w>$
2. Se $N$ rifiuta ($M$ non termina), allora rifiuta ($M$ non potrebbe accettare $w$)
3. Se $N$ accetta ($M$ termina), allora simula $M$ su $w$ e ritorna il suo output

#### Emptiness - Turing machine
Il problema di determinare se il linguaggio di una MdT è vuoto, è indecidibile.
$$E_{TM}=\{<M>|M\text{ è una MdT e }L(M)=\emptyset\}$$

Dimostriamo che $A_{TM}$ è riducibile ad $E_{TM}$ ($A_{TM}\leq E_{TM}$), cioè dimostriamo che se esistesse (per assurdo) un decisore $N$ per $E_{TM}$, allora $A_{TM}$ sarebbe decidibile (assurdo).

Forniamo un primo **approccio sbagliato** per capire meglio il perchè della prossima soluzione che forniremo.

Costruiamo il decisore $S$ per $A_{TM}$.
$S$ = su input $<M,w>$:
1. Esegui $N$ su $<M>$
2. Se $N$ accetta ($L(M)=\emptyset$), allora rifiuta
3. Se $N$ rifiuta ($L(M)\neq\emptyset$), simula $M$ su $w$ e ritorna il suo output

$M$ non è un decisore, per cui potrebbe andare in loop, a differenza del caso precedente, con $N$ non siamo sicuri che $M$ termini o meno.

Procediamo con un'**idea migliore**, ovvero ipotizziamo inizialmente che esista una MdT il cui linguaggio esibisca delle proprietà a noi utili, la utilizziamo per costruire il nostro decisore (assurdo) e poi diamo una spiegazione di come costruire tale MdT in modo da rendere possibile l'algoritmo.

Costruiamo quindi un decisore $S$ per $A_{TM}$.
$S$ = su input $<M,w>$
1. Costruisci una nuova MdT $M'$ tale che:
$$L(M')=\begin{cases}
\text{Non vuoto}&\text{se }M\text{ accetta }w\\
\text{Vuoto}&\text{altrimenti}
\end{cases}$$
2. Esegui $N$ su input $<M'>$
3. Se $N$ accetta ($L(M')=\emptyset$), rifiuta
4. Se $N$ rifiuta ($L(M')\neq\emptyset$), accetta

$S$ è un decisore in quanto si basa su passi di esecuzione che non vanno in loop, in particolare l'esecuzione di $N$ su $<M'>$ non può andare in loop, in quanto $N$ è un decisore (per ipotesi assurda), e questa esecuzione ci permette di capire in quale dei due casi che definiscono $L(M')$ ci troviamo.

Rimane ora da dare una definizione per $M'$, dopodichè avremmo ottenuto l'assurdo che cercavamo, ovvero abbiamo costruito un decisore per $A_{TM}$ basandoci su $E_{TM}$, il che è assurdo, per cui $E_{TM}$ dovrà essere indecidibile.

$M'$ = su input $x$:
1. Se $x\neq 123$ rifiuta
2. Altrimenti simula $M$ su $w$ e ritorna il suo output
$$L(M')=\begin{cases}
\{123\}&\text{se }M\text{ accetta } w\\
\emptyset&\text{altrimenti}
\end{cases}$$
>$123$ è una stringa arbitraria.

La MdT $M'$ rifiuta sempre qualsiasi stringa diversa da $123$, in questo modo l'unica stringa accettabile può essere $123$, nel caso $x=123$ facciamo simulare $M$ su $w$, se $M$ accetta allora facciamo accettare $123$ a $M'$, altrimenti non facciamo accettare neanche quella striga, rendendo $L(M')$ vuoto.
>Questa costruzione condiziona $M'$ in base al comportamento di $M$ su $w$. 
#### Regular - Turing machine
Il problema di determinare se il linguaggio di una MdT è regolare, è indecidibile.
$$REG_{TM}=\{<M>|M\text{ è una MdT e }L(M)\text{ è regolare}\}$$

Dimostriamo che $A_{TM}$ è riducibile a $REG_{TM}$, ciè dimostriamo che se avessimo un decisore $N$ per $REG_{TM}$, allora $A_{TM}$ sarebbe decidibile (assurdo).

Costruiamo un decisore $S$ per $A_{TM}$.
$S$ = su input $<M,w>$:
1. Costruisci una nuova MdT $M'$ tale che:
$$L(M')=\begin{cases}
\text{Regolare}&\text{se }M\text{ accetta }w\\
\text{Non regolare}&\text{altrimenti}
\end{cases}$$
2. Esegui $N$ su input $<M'>$
3. Se $N$ accetta ($L(M')$ è regolare), accetta
4. Se $N$ rifiuta ($L(M')$ non è regolare), rifiuta

Definiamo ora $M'$.
$M'$ su input $x$:
1. Se $x$ è nella forma $0^n1^n$, allora accetta
2. Altrimenti simula $M$ su $w$ e ritorna il suo output

Il suo linguaggio è definito come:
$$L(M')=\begin{cases}
\Sigma^*&\text{se }M\text{ accetta }w\\
\{0^n1^n|n\geq 0\}&\text{altrimenti}
\end{cases}$$

La MdT $M'$ è costruita in modo da accettare sempre le stringhe nella forma $0^n1^n$, per cui $L(M')$ contiene sempre almeno $0^n1^n$ il quale abbiamo dimostrato essere un linguaggio non regolare, poi condizioniamo il comportamento in base al risultato di $M$, infatti se $M$ accetta, allora $M'$ accetterà qualsiasi stringa, trasformando $L(M')$ in $\Sigma^*$, il quale è un linguaggio regolare, mentre se $M$ rifiuta, otterremo che $M$ accetterà tutte le stringhe tranne quelle in forma $0^n1^n$, rendendo $L(M')$ non regolare.

#### Equity - Turing machine
Il problema di determinare se due MdT riconoscono lo stesso linguaggio è indecidibile.
$$EQ_{TM}=\{<M_1,M_2>|M_1,M_2\text{ sono MdT e }L(M_1)=L(M_2)\}$$

Assumiamo per assurdo che $EQ_{TM}$ sia decidibile, e sia $N$ il suo decisore, costruiamo un decisore $E_{TM}$ per dimostrare la riduzione $E_{TM}\leq EQ_{TM}$ la quale porta ad un assurdo.

Costruiamo un decisore $S$ per $E_{TM}$.
$S$ = su input $<M>$:
1. Costruisci una nuova MdT $M'$ tale che $L(M')=\emptyset$
2. Esegui $N$ su $<M,M'>$
3. Ritorna il suo output
>$M'$ è una MdT che rifiuta sempre.

Ciò è assurdo perchè $E_{TM}$ è indecidibile.
