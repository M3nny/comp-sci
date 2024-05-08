Esistono problemi **intrattabili** come quello della [[Algoritmi greedy#Problema della clique massima|clique massima]] per cui è inverosimile che esista un algoritmo risolutivo con complessità polinomiale.

### Problemi
Un problema può essere rappresentato come una relazione binaria tra le sue **possibili istanze** e le sue **possibili soluzioni**:
$$\mathscr{P}\subseteq\underbrace{T}_\text{Istanze}\times\underbrace{S}_\text{Soluzioni}$$
Ad esempio per il problema della ricerca dei cammini minimi:
- Istanze: insieme di tutti i grafi orientati e pesati sugli archi
- Soluzioni: tutti i cammini minimi possibili

Esistono due macro categorie di problemi.
- **Problemi decidibili**: esiste un algoritmo che dia una soluzione in tempo finito
	- **Problemi trattabili**: possiedono algoritmi risolutivi con complessità _polinomiale_ al massimo pari a $O(n^k)$
	- **Problemi intrattabili**: possiedono algoritmi risolutivi con complessità _esponenziale_ al minimo pari a $O(k^n)$
- **Problemi indecidibili**: non esiste un algoritmo che produca una soluzione in tempo finito

>Potremmo però scoprire algoritmi che rendono problemi **intrattabili**, **trattabili**.

Possiamo distinguere  i problemi anche in base al tipo di risultato:
- **Problemi decisionali**: il cui risultato è una scelta binaria tra due opzioni
- **Problemi di ottimizzazione**: le soluzioni sono più o meno vaste e vogliamo trovare l'elemento massimo o minimo (e.g. clique massima, [problema del commesso viaggiatore](https://en.wikipedia.org/wiki/Travelling_salesman_problem))

Se qualcuno dovesse trovare un **algoritmo polinomiale** per risolvere un **problema intrattabile**, risolverebbe anche la variante decisionale in tempo polinomiale, ovvero la renderebbe **trattabile**.

## Classi di problemi decisionali
#### Classe P
La **classe P** dove P sta per polinomiale, è definita come segue:
$$\text{P}=\{\mathscr{P}|\mathscr{P}\text{ è un problema decisionale risolvibile polinomialmente}\}$$
tutti i problemi visti fino ad ora appartengono a questa classe.

### Classe NP
La **classe NP** è definita come segue:
$$\text{NP}=\{\mathscr{P}|\mathscr{P}\text{ è un problema decisionale verificabile polinomialmente}\}$$
un problema decisionale ritorna come risultato una risposta binaria, indichiamo con $\mathcal{I}_+$ le **istanze positive** (ritorna $1$), mentre con $\mathcal{I}_-$ le **istanze negative** (ritorna $0$).

Immaginando di avere un **algoritmo di verifica** $A_{VER}$ che prende in input:
- Una **istanza positiva** di un problema
- Un **certificato** (presunta soluzione del problema)
il suo compito è verificare che l'istanza passata in input sia effettivamente un'istanza positiva per il problema, attraverso il certificato, e ritornare $1$ in tal caso, $0$ altrimenti.

>[!Example]
>Prendiamo come esempio il problema del **ciclo Hamiltoniano** per cui deve esistere un ciclo che attraversa tutti i nodi di un grafo una sola volta.
>
>Sia data la seguente _istanza positiva_:
>![[Verifica ciclo Hamiltoniano.svg]]
>ed il _certificato_: $(2,4,3,1)$.
>
>Possiamo dimostrare in tempo polinomiale, addirittura lineare, che il certificato non è valido in quanto l'arco $(4,3)$ non esiste, per questo motivo il problema appartiene alla classe $\text{NP}$.
>Questo non prova che il grafo non sia Hamiltoniano, bensì che questo certificato non permette di dimostrare che il grafo dato in input sia un'istanza valida per questo problema.

### Classe Co-NP
La classe **Co-NP** è definita come segue:
$$\text{Co-NP}=\{\mathscr{P}|\mathscr{P}\text{ è un problema decisionale tale che }\overline{\mathscr{P}} \text{ è verificabile polinomialmente}\}$$

dove $\overline{\mathscr{P}}$ è il **complemento di un problema decisionale**, ovvero: le istanze positive del problema originale sono negative, e quelle negative sono positive.

Prendendo il problema del **ciclo Hamiltoniano** come esempio, se volessimo verificare che un grafo non sia Hamiltoniano, non possiamo usare lo stesso certificato usato precedentemente, infatti dovremmo testare tutte le $n!$ permutazioni dei vertici (questo sarebbe il nuovo certificato), il che non potrebbe mai risultare in un algoritmo polinomiale.
>L'appartenenza alla classe $\text{Co-NP}$ _non esclude_ l'appartenenza alla classe $\text{NP}$.

![[Classi di problemi.svg]]

### Classe NPC
Introduciamo il concetto di **riducibilità polinomiale** (già visto [[Bellman-Ford#Esercizi per riduzione|qui]]), questo metodo ci consente di ricondurci a problemi già noti, ma affinchè si possa parlare di _riducibilità polinomiale_, è necessario che anche l'operazione di riduzione sia polinomiale, ovvero:

diciamo che un problema $\mathscr{P}_1$ è riducibile polinomialmente al problema $\mathscr{P}_2$ se esiste un algoritmo polinomiale che mappi le istanze del problema $\mathscr{P}_1$ in istanze equivalenti del problema $\mathscr{P}_2$:
$$\mathscr{P}_1\leq_P\mathscr{P}_2$$
>È necessario preservare la positività e la negatività delle istanze, ovvero, istanze positive possono essere mappate solo in altre istanze positive e viceversa.

##### Proprietà della riducibilità
- $\leq_P$ è **riflessiva**: ogni problema decisionale è riducibile a se stesso
- $\leq_P$ è **transitiva**: ovvero vale: $\mathscr{P}_1\leq_P\mathscr{P}_2\leq_P\mathscr{P}_3\implies \mathscr{P}_1\leq_P\mathscr{P}_3$
	per definizione di _riducibilità_ $\mathscr{P}_1\leq_P\mathscr{P}_2$ implica che esiste un algoritmo che prende le istanze di $\mathscr{P}_1$ e le mappa in tempo polinomiale in istanze di $\mathscr{P}_2$, l'algoritmo sarà: $\mathscr{P}_2:A_{12}:\mathcal{I}_1\to\mathcal{I}_2$, discorso analogo per $\mathscr{P}_2\leq_P\mathscr{P}_3$.
	Per cui un algoritmo $A_{13}$ è sufficiente che concateni $A_{12}$ e $A_{23}$, e tale algoritmo sarà anch'esso polinomiale dato che la sua complessità è data dalla somma delle complessità di $A_{12}$ e $A_{23}$ che sono polinomiali, quindi la riducibilità è transitiva.
- $\leq_P$ **non è necessariamente simmetrica**: non è detto che se un problema $\mathscr{P}_1$ è riducibile a $\mathscr{P}_2$, allora valga anche il contrario

La definizione della classe $\text{NPC}$ è data da:
$$\text{NPC}=\begin{cases}
\mathscr{P}|\mathscr{P}\text{ è un problema decisionale tale che}\\
1) \mathscr{P}\in\text{NP}\\
2) \forall\mathscr{P}'\in\text{NP}:\mathscr{P}'\leq_P\mathscr{P}
\end{cases}$$
Un problema di classe $\text{NPC}$ si dice **NP completo**.

La **seconda condizione** di appartenenza alla classe $\text{NPC}$ dice che:
	tutti i problemi in $\text{NP}$ possono essere mappati in qualsiasi problema $\text{NPC}$ anche completamente diverso, inoltre tutti i problemi in $\text{N}$ sono riducibili a problemi $\text{NPC}$ in quanto $\text{P}\subseteq \text{NP}$; inoltre essendo $\text{NPC}\subseteq \text{NP}$, vuol dire che tutti i problemi $\text{NPC}$ possono essere ridotti tra di loro, implicando che la relazione di **riducibilità è simmetrica tra problemi di classe** $\text{NPC}$.

#### Teorema fondamentale della NP completezza
$$P\cap NPC\neq\emptyset\implies P=NP$$
Se esiste un problema risolvibile in tempo polinomiale, che è _anche_ $\text{NPC}$, allora $\text{P}$ e $\text{NP}$ sono lo stesso insieme.
>Ciò implicherebbe che tutti i problemi $\text{NPC}$ conosciuti ma non in grado di essere risolti in quanto _intrattabili_, potrebbero essere risolti in tempo polinomiale.

**Dimostrazione**: per ipotesi $\exists\mathscr{P}\in\text{NPC}\cap\text{P}$, ovvero $\mathscr{P}\in\text{NPC}\land\mathscr{P}\in\text{P}$,
bisogna dimostrare che:
1. $\text{P}\subseteq \text{NP}$: banalmente vero in quanto un problema risolvibile polinomialmente è anche verificabile polinomialmente
2. $\text{NP}\subseteq \text{P}$:
	sia $Q$ un problema $\text{NP}$, allora dovrà valere $\forall Q\in\text{NP}:Q\in\text{P}$, ed essendo che $Q\in\text{NP}$ e $\mathscr{P}\in\text{NPC}$ per ipotesi, allora:
	$$\underbrace{Q\leq_P\mathscr{P}}_\text{Def. NPC}\in\text{P}\qquad\mathscr{P}\in\text{P}\text{(per ipotesi)}$$
	dato che pe definizione di $\text{NPC}$, $Q$ è riducibile a $\mathscr{P}$ il quale appartiene a $\text{P}$, vuol dire che esiste un algoritmo polinomiale che traduce le istanze di $Q$ in istanze di $\mathscr{P}$, che può essere risolto polinomialmente.
	Quindi $Q$ si può risolvere in tempo polinomiale, ovvero $Q\in\text{P}$ che è quello che volevamo dimostrare.

Da questo teorema emerge che $\text{NPC}$ e $\text{P}$ formino l'insieme $\text{NP}$, ma non è proprio così a causa di dei **problemi** $\text{NPI}$, ovvero $\text{NP-intermedi}$ per cui è possibile verificare in tempo polinomiale, ma non risolvere in tempo polinomiale (e.g. [[Isomorfismo|isomorfismo tra grafi]])

![[NPC - NPCI.svg]]

---
### Il problema CIRCUIT-SAT
Il primo problema che è stato dimostrato appartenere alla classe $\text{NPC}$ è il problema del **CIRCUIT-SAT** (Circuit-Satisfiability) la cui NP-completezza è garantita dal **teorema di Cook**. 

Il problema si chiede se dato un circuito logico con $n$ linee in input esiste una configurazione delle linee che produca in output $1$ (attraverso varie porte logiche).

L'algoritmo di verifica prenderà in input un **circuito** e come certificato una **configurazione** che _dovrebbe_ ritornare $1$ (quindi essere soddisfacibile), e dato che il risultato di una singola porta logica ha complessità costante, la correttezza del certificato si può verificare in tempo polinomiale (da cui l'appartenenza alla classe $\text{NP}$).

<u>Per dimostrare che un problema è NP-completo</u> bisognerà dimostrare:
1. Che è verificabile in tempo polinomiale, ovvero $\mathscr{P}\in\text{NP}$
2. Che esiste un problema $Q\in\text{NPC}$ tale che $Q\leq_P\mathscr{P}$
>È infatti sufficiente dimostrare l'esistenza di un singolo problema NP-completo che soddisfi la seconda condizione per via della transitività della riducibilità polinomiale tra problemi.

Un altro problema analogo è quello **SAT**, il quale si interroga sulla **soddisfacibilità di formule logiche**, per dimostrare che esso è NP-completo bisognerà dimostrare che è polinomialmente verificabile e che il CIRCUIT-SAT (che è NP-completo) è polinomialmente riducibile al problema SAT.

#### Forma normale congiuntiva
Quando si ha a che fare con l'algebra booleana è utile utilizzare un formato particolare di formule booleane, noi useremo la **FNC (Forma Normale Congiuntiva)** ovvero una congiunzione di clausole:
$$\Phi=C_1\land C_2\land...\land C_k$$
$$C=\ell_1\lor\ell_2\lor...\lor\ell_q$$
dove ogni clausola è formata da letterali, ovvero affermazioni o negazioni di variabili booleane.
Per verificare la soddisfacibilità di $\Phi$ è necessario che almeno un letterale (per ogni clausola) sia vero.

Il **formato k-FNC** è un formato _FNC_ dove ogni clausola ha $k$ letterali, ci interessiamo al formato in cui $k=3$ parlando del problema **SAT-3FNC** il quale si occupa di verificare la soddisfacibilità di formule con clausole a $3$ letterali.

Utilizziamo questa digressione sulla FNC per dimostrare che il problema della **clique** è **NP-completo**:
1. $clique\in \text{NP}$: vero in quanto è [[Algoritmi greedy#Problema della clique massima|verificabile in tempo quadratico]]
2. Scegliamo il problema SAT-3FNC è dimostriamo che è _riducibile_ al problema della _clique_

Prendiamo una generica istanza del problema SAT-3FNC:
$$\Phi=C_1\land C_2\land C_3$$
$$C_1=x_1\lor\neg x_2\lor\neg x_3$$
$$C_2=\neg x_1\lor x_2\lor x_3$$
$$C_3=x_1\lor x_2\lor x_3$$
trasformiamo questa congiunzione in un'istanza di $clique$, costruendo gli archi secondo le seguenti condizioni:
1. Un arco (se presente) dovrà collegare letterali di gruppi diversi
2. Non può esistere un arco tra due letterali che sono uno la negazione dell'altro

![[SAT-3FNC to Clique.svg]]
Prendendo la _clique_ formata dai vertici blu nel grafo, se diamo il valore $1$ a letterali e $0$ ai letterali negati che costituiscono la _clique_, avremmo che con $x_2=0$, $x_3=1$ e $x_1$ scelto arbitrariamente, la congiunzione è verificata; infatti $x_2=0$ soddisfa la clausola $C_1$ e $x_3=1$ soddisfa le clausole $C_2$ e $C_3$ (i vertici sono stati scelti arbitrariamente).

In questo modo è possibile dimostrare la completezza di molti altri problemi tra cui quello del ciclo Hamiltoniano.

---
### Cosa fare davanti ad un problema intrattabile
1. Usare **algoritmi di approssimazione** i quali forniscono soluzioni non lontane da quelle ottimali, queste soluzioni sono dette $\epsilon$-ottimali, in quanto possiedono un margine di errore $\epsilon$
2. Sperare che il problema sia un **caso speciale**, ad esempio il problema della clique è polinomiale per _grafi planari_ (grafi con archi che non si intersecano)
3. Usare **euristiche**, che anche se non garantiscono la correttezza della soluzione costituiscono l'ultima spiaggia per problemi intrattabili

