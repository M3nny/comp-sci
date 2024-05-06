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

### Classi di problemi decisionali
#### Classe P
La **classe P** dove P sta per polinomiale, è definita come segue:
$$\text{P}=\{\mathscr{P}|\mathscr{P}\text{ è un problema decisionale risolvibile polinomialmente}\}$$
tutti i problemi visti fino ad ora appartengono a questa classe.

#### Classe NP
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

#### Classe NPC
Introduciamo il concetto di **riducibilità polinomiale** (già visto [[Bellman-Ford#Esercizi per riduzione|qui]]), questo metodo ci consente di ricondurci a problemi già noti, ma affinchè si possa parlare di _riducibilità polinomiale_, è necessario che anche l'operazione di riduzione sia polinomiale, ovvero:

diciamo che un problema $\mathscr{P}_1$ è riducibile polinomialmente al problema $\mathscr{P}_2$ se esiste un algoritmo polinomiale che mappi le istanze del problema $\mathscr{P}_1$ in istanze equivalente del problema $\mathscr{P}_2$:
$$\mathscr{P}_1\leq_P\mathscr{P}_2$$
>È necessario preservare la positività e la negatività delle istanze, ovvero, istanze positive possono essere mappate solo in altre istanze positive e viceversa.

