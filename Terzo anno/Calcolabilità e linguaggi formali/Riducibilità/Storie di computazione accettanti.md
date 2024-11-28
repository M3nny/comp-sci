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
$$E_{LBA}=\{<M>|M\text{ è un LBA e }L(M)=\emptyset\}$$

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

