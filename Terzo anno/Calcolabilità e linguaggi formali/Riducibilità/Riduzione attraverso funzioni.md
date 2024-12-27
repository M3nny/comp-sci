Una **funzione** $f:\Sigma^*\to\Sigma^*$ si dice **calcolabile** sse esiste una MdT $M$ tale che per ogni stringa $w$, $M$ su input $w$ termina lasciando $f(w)$ sul nastro.
>In pratica una funzione è calcolabile se è simulabile da una MdT.

Un linguaggio $A$ è mapping-riducibile ad un linguaggio $B$ (indicato come $A\leq_mB$) sse esiste una funzione _calcolabile_ $f$ tale che:
$$\forall w\in\Sigma^*,w\in A\iff f(w)\in B$$
![[Funzione di riduzione.svg|400]]
>**Osservazione**: $A\leq_mB\iff\bar A\leq_m\bar B$.

**Teorema**
Se $A\leq_mB$ e $B$ è decidibile, allora $A$ è decidibile.

**Dimostrazione**: dato che $A\leq_mB$, esiste una funzione calcolabile $f$ tale che per ogni stringa $w$, $w\in A$ sse $f(w)\in B$, inoltre visto che $B$ è decidibile, allora esiste un decisore $M$ tale che $L(M)=B$.
Costruiamo un decisore $N$ per $A$ come segue:
$N$ su input $w$:
1. Calcola $f(w)$
2. Esegui $M$ su input $f(w)$
3. Ritorna il suo output
$$\begin{align}
&w\in A\implies f(w)\in B\implies M\text{ accetta}\implies N\text{ accetta}\\
&w\notin A\implies f(w)\notin B\implies M\text{ rifiuta}\implies N\text{ rifiuta}
\end{align}$$

**Corollario**: se $A\leq_mB$ e $A$ è indecidibile, allora $B$ è indecidibile.
>Utile per dimostrare l'indecidibilità.

#### Problema della fermata (con riduzione attraverso funzione)
Vediamo una dimostrazione alternativa all'indecidibilità del [[Terzo anno/Calcolabilità e linguaggi formali/Riducibilità/Introduzione#Problema della fermata|problema della fermata]] $HALT_{TM}$ tramite il problema (indecidibile anch'esso) dell'[[Indecidibilità#Accettazione - macchina di Turing|accettazione]] $A_{TM}$, ovvero dimostriamo $A_{TM}\leq_mHALT_{TM}$.

Dobbiamo trovare una $f$ calcolabile tale che:
$$<M,w>\in A_{TM}\iff \underbrace{f(<M,w>)}_{<M,w>}\in HALT_{TM}$$
Costruiamo una MdT $F$ che implementa $f$:
$F$ = su input $<M,w>$:
1. Costruisci una nuova MdT $M'$ definita come segue:
	$M'$ = su input $x$:
	- Simula $M$ su $x$
	- Se $M$ accetta, allora accetta
	- Altrimenti vai in loop
2. Ritorna $<M',w>$

Controlliamo la correttezza di entrambi i versi della riduzione:
$$\begin{align}
&<M,w>\in A_{TM}\Rightarrow M\text{ accetta }w\Rightarrow M'\text{ accetta }w\Rightarrow M'\text{ termina su }w\Rightarrow <M',w>\in HALT_{TM}\\
&<M,w>\notin A_{TM}\Rightarrow M\text{ rifiuta }w \text{ o }M\text{ va in loop su }w\Rightarrow M'\text{ va in loop su }w\Rightarrow <M',w>\notin HALT_{TM}
\end{align}$$

#### Equity - Turing machine (con riduzione attraverso funzione)
Dimostriamo che il problema [[Terzo anno/Calcolabilità e linguaggi formali/Riducibilità/Introduzione#Equity - Turing machine|equity]] per MdT è indecidibile tramite il problema di [[Terzo anno/Calcolabilità e linguaggi formali/Riducibilità/Introduzione#Emptiness - Turing machine|emptiness]] per MdT con una funzione, ovvero dimostriamo $E_{TM}\leq_m EQ_{TM}$.

Dobbiamo trovare una $f$ calcolabile tale che:
$$<M>\in E_{TM}\iff \underbrace{f(<M>)}_{<M_1,M_2>}\in EQ_{TM}$$
Costruiamo una MdT $F$ che implementa $f$:
$F$ = su input $<M>$:
1. Costruisci una MdT $M'$ tale che $L(M')=\emptyset$
2. Ritorna $<M,M'>$

Controlliamo la correttezza di entrambi i versi della riduzione:
$$\begin{align}
&<M>\in E_{TM}\Rightarrow L(M)=\emptyset\Rightarrow L(M)=L(M')\Rightarrow<M,M'>\in EQ_{TM}\\
&<M>\notin E_{TM}\Rightarrow L(M)\neq\emptyset\Rightarrow L(M)\neq L(M')\Rightarrow <M,M'>\notin EQ_{TM}
\end{align}$$

#### Emptiness - Turing machine (con riduzione attraverso funzione)
Dimostriamo che il problema [[Terzo anno/Calcolabilità e linguaggi formali/Riducibilità/Introduzione#Emptiness - Turing machine|emptiness]] per MdT è indecidibile tramite il problema di [[Indecidibilità#Accettazione - macchina di Turing|accettazione]] per MdT con una funzione, ovvero dimostriamo $A_{TM}\leq_mE_{TM}$, per semplicità dimostreremo $A_{TM}\leq_m\bar E_{TM}$ il che è equivalente.
>È equivalente perchè se uno dei due linguaggio è decidibile, si potrebbe decidere il problema indecidibile invertendo l'output del decisore.

Dobbiamo trovare una $f$ calcolabile tale che:
$$<M,w>\in A_{TM}\iff \underbrace{f(<M,w>)}_{<M>}\in\bar E_{TM}$$

Costruiamo una MdT $F$ che implementa $f$:
$F$ = su input $<M,w>$:
1. Costruisci una MdT $M'$ definita come segue:
	$M'$ = su input $x$:
	- Se $x\neq w$, rifiuta
	- Altrimenti simula $M$ su $w$ e ritorna il suo output
2. Ritorna $<M'>$
>$M'$ è uguale a quella costruita nella dimostrazione di indecidibilità per _emptiness_.

Controlliamo la correttezza di entrambi i versi della riduzione:
$$\begin{align}
&<M,w>\in A_{TM}\Rightarrow M\text{ accetta }w\Rightarrow L(M')=\{w\}\Rightarrow L(M')\neq\emptyset\Rightarrow<M'>\notin E_{TM}\Rightarrow<M'>\in\bar E_{TM}\\
&<M,w>\notin A_{TM}\Rightarrow M\text{ non accetta }w\Rightarrow L(M')=\emptyset\Rightarrow<M'>\in E_{TM}\Rightarrow<M'>\notin\bar E_{TM}
\end{align}$$

### Turing-riconoscibilità
**Teorema**
Se $A\leq_mB$ e $B$ è [[Macchina di Turing#Linguaggio per una macchina di Turing|Turing-riconoscibile]], allora anche $A$ è Turing-riconoscibile.
>Si dice che $A$ è **co-Turing-riconoscibile** se $\bar A$ è Turing-riconoscibile.

**Dimostrazione** (uguale a quella fatta con i decisori ad inizio pagina): dato che $A\leq_mB$, allora esiste una $f$ calcolabile tale che per ogni stringa $w$, $w\in A$ sse $f(w)\in B$, inoltre dato che $B$ è Turing-riconoscibile, esiste una MdT $M$ tale che $L(M)=B$.
Costruiamo una MdT $N$ tale che $L(N)=A$:
$N$ = su input $w$:
1. Calcola $f(w)$
2. Esegui $M$ su $f(w)$ e ritorna il suo output

**Corollario**: se $A\leq_mB$ e $A$ _non_ è Turing-riconoscibile, allora $B$ _non_ è Turing-riconoscibile.
>La riduzione attraverso funzioni ci permette di dimostrare che alcuni problemi non sono Turing-riconoscibili, cosa che non potevamo fare prima.

#### Equity - Turing machine (non Turing-riconoscibile)
Dimostriamo che $\bar A_{TM}\leq_mEQ_{TM}$, ovvero $A_{TM}\leq_m\overline{EQ}_{TM}$.

Costruiamo una $f$ calcolabile tale che:
$$<M,w>\in A_{TM}\iff \underbrace{f(<M,w>)}_{M_1,M_2}\in\overline{EQ}_{TM}$$

Costruiamo una MdT $F$ che implementa $f$:
$F$ = su input $<M,w>$:
1. Costruisci una nuova MdT $M_1$ come segue:
	$M_1$ = su input $x$:
	- Rifiuta
2. Costruisci una nuova MdT $M_2$ come segue:
	$M_2$ = su input $x$:
	- Simula $M$ su $w$ e ritorna il suo output
3. Ritorna $<M_1,M_2>$

Controlliamo la correttezza di entrambi i versi della riduzione:
$$\begin{align}
&<M,w>\in A_{TM}\Rightarrow M\text{ accetta }w\Rightarrow L(M_2)=\Sigma^*\Rightarrow L(M_1)\neq L(M_2)\Rightarrow<M_1,M_2>\in\overline{EQ}_{TM}\\
&
<M,w>\notin A_{TM}\Rightarrow M\text{ non accetta }w\Rightarrow L(M_2)=\emptyset\Rightarrow L(M_1)=L(M_2)\Rightarrow<M_1,M_2>\notin\overline{EQ}_{TM}
\end{align}$$

>È possibile anche dimostrare che in modo analogo che $\overline{EQ}_{TM}$ non è Turing-riconoscibile, dimostriamo che $\bar A_{TM}\leq_m\overline{EQ}_{TM}$, ovvero $A_{TM}\leq_m EQ_{TM}$.

