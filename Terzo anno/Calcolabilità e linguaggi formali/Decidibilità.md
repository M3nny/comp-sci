D'ora in poi ci concentreremo sulla decidibilità dei problemi, e nel caso non lo fossero scopriremo che si farà uso di _approssimazioni_.

#### Accettazione - DFA
Determinare se un [[Automi a stati finiti#Definizione DFA|DFA]] $D$ accetta una stringa $w$.
$$A_{DFA}=\{<M,w>|M\text{ è un DFA e }w\in L(M)\}$$
Costruiamo un decisore $N$ tale che $L(N)=A_{DFA}$.
$N$ = su input $<M,w>$:
1. Simula il DFA $M$ su input $w$
2. Se $M$ termina in uno stato di accettazione, accetta, altrimenti rifiuta

Questa macchina termina sempre in quanto un DFA terminerà quando avrà consumato il suo input.
È importante notare che la MdT può imitare un DFA in quanto possiede una espressività uguale (o maggiore in questo caso).
>Sebbene si sta fornendo una descrizione ad alto livello è importante descrivere cose fattibili da una MdT.

#### Accettazione - NFA e Regex
Determinare se un [[Automi a stati finiti non deterministici#Definizione di NFA|NFA]] $N$ accetta una stringa $w$.
$$A_{NFA}=\{<N,w>|N\text{ è un NFA e }w\in L(N)\}$$
Costruiamo un decisore $M$ tale che $L(M)=A_{NFA}$.
$M$ = su input $<N,w>$:
1. Converte $N$ in un DFA $D$ ad esso equivalente
2. Simula il decisore per $A_{DFA}$ su input $<D,w>$
3. Ritorna il suo output

Questo problema era risolvibile anche simulando $N$ non deterministicamente su $w$, tuttavia in questo modo sfruttiamo il decisore definito precedentemente come una chiamata a funzione.

In modo analogo data una [[Espressioni regolari#Regolarità tramite regex|regex]] è possibile costruire un decisore per $A_{rex}$ convertendo la regex in un NFA.

#### Emptiness - DFA
Determinare se un DFA $D$ non accetta nessuna stringa (linguaggio vuoto).
$$E_{DFA}=\{<D>|D\text{ è un DFA e }L(D)=\emptyset\}$$

Utilizzare una tecnica di brute-force provando a generare tutte le stringhe possibili non funziona in quanto non sarebbe un decisore.

Riformuliamo il problema in un problema su [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione|grafi]] sfruttando la struttura di un DFA, andiamo quindi a marcare i nodi raggiungibili da ogni nodo, partendo da quello iniziale, se viene marcato uno stato accettante allora si rifiuta in quanto esisterà un input $w$ per cui tale DFA accetterà.

Costruiamo un decisore $M$ tale che $L(M)=E_{DFA}$.
$M$ = su input $<D>$:
1. Marca lo stato iniziale di $D$
2. Finchè è possibile marcare nuovi stati:
	- Marca gli stati con una transizione in entrata da stati già marcati
3. Se ha marcato almeno uno stato accettante allora rifiuta, altrimenti accetta

#### Equity - DFA
Determinare se due DFA $D_1$ e $D_2$ riconoscono lo stesso linguaggio.
$$EQ_{DFA}=\{<D_1,D_2>|D_1,D_2\text{ sono DFA e }L(D_1)=L(D_2)\}$$

Osserviamo che $L(D_1)=L(D_2)$ sse:
- Tutte le stringhe di $L(D_1)$ stanno anche in $L(D_2)$
- Tutte le stringhe di $L(D_2)$ stanno anche in $L(D_1)$
ovvero:
- Non esiste alcuna stringa di $L(D_1)$ tale che essa non stia in $L(D_2)$
- Non esiste alcuna stringa di $L(D_2)$ tale che essa non stia in $L(D_1)$
ovvero:
$$L(D_1)=L(D_2)\iff \underbrace{\underbrace{\left(L(D_1)\cap\overline{L(D_2)}\right)}_{\text{Str. che stanno in }L(D_1)\text{ ma non in }L(D_2)}\cup\underbrace{\left(\overline{L(D_1)}\cap L(D_2)\right)}_{\text{Str. che stanno in }L(D_2)\text{ ma non in }L(D_1)}}_{\text{Vuoto se entrambi gli insiemi sono vuoti}}$$

Costruiamo un decisore $M$ tale che $L(M)=EQ_{DFA}$.
$M$ = su input $<D_1,D_2>$:
1. Costruisce un nuovo DFA $D$ tale che $L(D)=\left(L(D_1)\cap\overline{L(D_2)}\right)\cup\left(\overline{L(D_1)}\cap L(D_2)\right)$
	Ciò è possibile in quanto la classe dei linguaggi regolari è chiusa rispetto al complemento, intersezione ed unione.
2. Simula il decisore per $E_{DFA}$ su input $<D>$
3. Ritorna il suo output, in quanto $E_{DFA}$ ritorna _accept_ se il linguaggio è vuoto, ovvero vorrà dire (per come è stato trattato il problema) che $L(D_1)=L(D_2)$

#### Accettazione - CFG
Determinare se una [[Context-free grammar|CFG]] $G$ genera una certa stringa $w$.
$$A_{CFG}=\{<G,w>|G\text{ è una CFG e }w\in L(G)\}$$

Utilizzare una tecnica di brute-force provando a generare derivazioni può causare cicli infiniti in quanto da una grammatica possono essere generate potenzialmente infinite derivazioni.

Come nel caso del [[Macchina di Turing#Decimo problema di Hilbert|problema di Hilbert]] per costruire un decisore andiamo ad applicare dei vincoli in modo da evitare i cicli infiniti.

**Lemma**: se $H$ è una CFG in [[Context-free grammar#Forma normale di Chomsky|forma normale di Chomsky]] e $w$ è una stringa di lunghezza $n$, allora se $w\in L(H)$ è possibile trovare una derivazione di $w$ costituita da $2n-1$ passi.

Questo lemma vale perchè se $H$ è nella forma normale di Chomsky vorrà dire che può avere solo tre tipi di produzioni, dove in particolare se $|w|=0$, si avrà $S\to\epsilon$, e quindi è possibile trovare una derivazione anche dopo un solo passo.

Nel caso in cui si avessero i rimanenti due tipi di produzioni, indichiamoli come:
- $A\to BC$: 1° tipo
- $A\to a$: 2° tipo
si noti come verranno utilizzate inizialmente $n-1$ produzioni del 1° tipo, e poi $n$ produzioni del 2° tipo.
Se per esempio volessimo generare $aaab$ potremmo usare la seguente derivazione: $S\Rightarrow AB\Rightarrow AAB\Rightarrow AAAB\Rightarrow aAAB\Rightarrow aaAB\Rightarrow aaaB\Rightarrow aaab$.

Costruiamo un decisore $M$ tale che $L(M)=A_{CFG}$.
$M$ = su input $<G,w>$:
1. Converte $F$ in forma normale di Chomsky, chiamiamo il suo output $H$
2. Prova tutte le derivazioni di $2n-1$ passi dove $n=|w|$, se $n=0$ prova solo le derivazioni di un passo
3. Se una di esse genera $w$ allora accetta, altrimenti rifiuta

#### Emptiness - CFG
Determinare se una CFG $G$ non genera alcuna stringa (linguaggio vuoto).
$$E_{CFG}=\{<G>|G\text{ è una CFG e }L(G)=\emptyset\}$$

Similmente al caso di emptiness visto per i DFA in questo caso marchiamo i terminali (in quanto già stringhe), poi marchiamo i non-terminali la cui parte destra è già stata marcata.

Costruiamo un decisore $M$ tale che $L(M)=E_{CFG}$.
$M$ = su input $<G>$:
1. Marca tutti i terminali di $G$ nelle sue produzioni
2. Finchè è possibile marcare non-terminali:
	- Marca i non-terminali $A$ tali che esista una produzione nella forma $A\to w_1,...,w_n$ dove tutti i $w_i$ sono marcati
3. Se ha marcato lo start-symbol $S$ rifiuta, altrimenti accetta

### Decidibilità delle CFG
Sia $A$ un linguaggio context-free, allora esiste una CFG $G$ tale che $L(G)=A$.

Dimostriamo quindi che esiste un decisore $M$ tale che $L(M)=A$:
$M$ = su input $w$:
1. Simula il decisore per il problema $A_{CFG}$ su input $<G,w>$
2. Ritorna il suo output

La grammatica $G$ nel nostro caso è "hard-coded" nella macchina $M$, in quanto non viene fornita come input, siamo sicuri che esista una grammatica $G$ per definizione di linguaggio context-free, e questo è sufficiente per la dimostrazione.

Con questa dimostrazione possiamo vedere i linguaggi nel seguente modo:
![[Gerarchia linguaggi.svg]]
