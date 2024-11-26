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

---
## Riduzione basata su storie di computazioni accettanti
Sia $M$ una MdT e sia $w$ il suo input, una storia di computazione accettante per $M$ e $w$ è una sequenza di configurazioni $C_1,C_2,...,C_k$ tali che:
1. $C_1$ è la configurazione iniziale di $M$ su $w$
2. $C_k$ è una configurazione accettante
3. $\forall i,C_i$ produce $C_{i+1}$

- Se $M$ accetta $w$ ci sarà almeno una ($1$ se $M$ è deterministica) storia di computazione accettante
- Se $M$ rifiuta $w$ o va in loop, non ci saranno storie di computazioni accettanti
>Le storie di computazioni accettanti sono sequenze finite.

Per utilizzare questa tecnica serve introdurre un nuovo modello computazionale.

### Automi linearmente limitati
Un **Linear Bounded Automata (LBA)** è una MdT con lunghezza del nastro pari alla lunghezza del suo input iniziale.

#### Accettazione - LBA
Il problema di determinare se un LBA accetta un certo input è decidibile.
$$A_{LBA}=\{<M,w>|M\text{ è un LBA che accetta }w\}$$

**Lemma**: sia $M$ un LBA con $q$ stati e $g$ simboli per il nastro, se un nastro ha lunghezza $n$, il numero massimo di configurazioni del LBA è pari a $qng^n$.

Questo è vero in quanto:
- Numero di stati: $q$
- Numero di posizioni possibili della testina: $n$
- Possibili contenuti del nastro: $g$ possibili caratteri in $n$ possibili celle ($g^n$)
>Il prodotto fornisce il numero di configurazioni massime.

Costruiamo un decisore $D$ per $A_{LBA}$.
$D$ = su input $<M,w>$:
1. Simula $M$ su $w$ per $qng^n$ passi oppure fino a terminazione
2. Se $M$ ha terminato, allora ritorna il suo output
3. Altrimenti rifiuta
>L'ultimo punto indica che $M$ ha attraversato $qng^n+1$ configurazioni ($+1$ a causa della configurazione iniziale), quindi sicuramente sarà andata in loop.

#### Emptiness - LBA
Il problema di determinare se un LBA possiede un linguaggio vuoto è indecidibile.
$$E_{LBA}=\{<M>|M$\text{ è un LBA e }L(M)=\emptyset\}$$

Per dimostrarlo costruiamo una riduzione da $A_{TM}$ a $E_{LBA}$ sfruttando la tecnica delle storie di computazioni accettanti.

Assumiamo per assurdo che $E_{LBA}$ sia decidibile e che quindi esista un suo decisore $N$, costruiamo il decisore $S$ per $A_{TM}$.
$S$ = su input $<M,w>$ ($M$ è una MdT):
1. Costruisci un LBA $M'$ con la seguente caratteristica:
$$L(M')=\begin{cases}
\text{Non vuoto}&\text{se }M\text{ accetta }w\\
\text{Vuoto}&\text{altrimenti}
\end{cases}$$
2. Esegui $N$ su $<M'>$
3. Ritorna il suo output invertito

Costruiamo $M'$ in modo tale che $L(M')$ sia l'insieme delle storie di computazione accettanti di $M$ su $w$.
- Se $L(M')=\emptyset$, allora non vi sono storie di computazioni accettanti di $M$ su $w$, quindi $M$ non accetta $w$
- Se $L(M')\neq\emptyset$, allora vi è una storia di computazione accettante di $M$ su $w$, quindi $M$ accetta $w$

Per capire come costruire $M'$ forniamo una rappresentazione di una storia di computazione accettante:
$$\#C_1\#C_2\#...\#C_k\#$$

Verifichiamo nel seguente modo se una stringa è una storia di computazione accettante:
1. Controlla che $C_1$ è una configurazione iniziale di $M$ su $w$, ovvero il suo formato deve corrispondere a $C_1=q_0w$ (dove $w$ è l'input e $q_0$ è posizionata sul suo primo carattere)
2. Controlla che $C_k$ è una configurazione accettante, ovvero $C_k=uq_{accept}v$ per qualche $u,v$
3. Controlla che $\forall i$, $C_i$ produce $C_{i+1}$ secondo la funzione di transizione
$$\#abq_7ba\#aaaaq_{10}\quad\text{mossa non valida}$$
$$\#abq_7ba\#aq_{10}bca\#\quad\text{mossa valida}$$

#### ALL - CFG
Il problema di determinare se una CFG genera tutte le stringhe del suo alfabeto è indecidibile.
$$ALL_{CFG}=\{<G>|G\text{ è una CFG tale che }L(G)=\Sigma^*\}$$

Vogliamo ridurre $A_{TM}$ a $ALL_{CFG}$, assumiamo per assurdo che $ALL_{CFG}$ sia decidibile e sia $N$ il suo decisore, costruiamo un decisore $S$ per $A_{TM}$.
$S$ = su input $<M,w>$:
1. Costruisci una CFG $G$ con la seguente caratteristica:
$$L(G)=\begin{cases}
\neq\Sigma^*&\text{se }M\text{ accetta }w\\
\Sigma^*&\text{altrimenti}
\end{cases}$$
2. Esegui il decisore per $ALL_{CFG}$ su $L(G)$
3. Ritorna l'output invertito

Costruiamo $G$ tale che $L(G)$ contenga le stringhe che non sono storie di computazioni accettanti per $M$ su $w$.
- Se $L(G)=\Sigma^*$, allora nessuna stringa è una storia di computazione accettante, quindi $M$ non accetta $w$
- Se $L(G)\neq\Sigma^*$, allora qualche stringa è una storia di computazione accettante, quindi $M$ accetta $w$

Dato che specificare una CFG $G$ sarebbe complesso, definiamo un PDA $P$ tale che $L(G)=L(P)$ (vedi [[Automi a pila#Equivalenza tra CFG e PDA|equivalenza tra CFG e PDA]]).

Affinchè una stringa nel formato $\#C_1\#C_2\#...\#C_k\#$ _non_ sia una storia di computazione accettante, deve valere almeno una delle seguenti tre condizioni:
1. $C_1$ non è una configurazione iniziale ($C_1\neq q_0w$), oppure
2. $C_k$ non è una configurazione accettante ($C_k\neq uq_{accept}v$), oppure
3. Esiste un $C_i$ tale che $C_i$ non produce $C_{i+1}$

Essendo che un PDA lavora con uno _stack_, caricare una configurazione per poi confrontarla con quella successiva non è semplice, immaginiamo che legga il primo carattere di $C_1$, quando dovrà confrontarlo con il primo carattere di $C_2$ esso si troverà in fondo allo stack.

Modifichiamo quindi la rappresentazione come stringa delle configurazioni in modo da usufruire dei caratteri memorizzati in ordine corretto.
Per farlo invertiamo a due a due le configurazioni.
$$C_1\#C_2^R\#C_3\#C_4^R\#...\#C_k$$
>In base alla parità del numero di configurazioni, l'ultima configurazione sarà invertita o meno.

