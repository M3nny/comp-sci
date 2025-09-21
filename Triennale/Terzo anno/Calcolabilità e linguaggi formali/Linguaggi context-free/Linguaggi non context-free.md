Dimostrare che un linguaggio non è context-free è difficile in quanto bisogna dimostrare che esso non è generabile da alcuna CFG (oppure non riconoscibile da un PDA).

## Pumping lemma per linguaggi context-free
Se $A$ è un linguaggio context-free, allora esiste un intero $p\geq 1$ (**pumping length**) tale che ogni stringa $w\in A$ con $|w|\geq p$ può essere suddivisa in cinque parti ($w=uvxyz$) tali che valgono le seguenti tre condizioni:
1. $\forall i\geq 0$ $uv^ixy^iz\in A$
2. $|vy|>0$
3. $|vxy|\leq p$

L'idea è quella di scegliere una $p$ "molto grande", le stringhe con lunghezza $\geq p$ saranno "molto lunghe", ed essendo molto lunghe avranno un parse tree "molto alto".
Visto che i non-terminali sono in numero finito, in tale parse tree "molto alto" ci deve essere un non-terminale $R$ che si ripete.
![[Parse tree pumping lemma.svg]]

Prendendo il più piccolo dei parse tree radicati in $R$ e mettendolo al posto del più grande, si ottiene un parse tree per $uxz$ (**pumping down**).
Prendendo il più grande dei due parse tree radicati in $R$ e mettendolo al posto del più piccolo, si ottiene un parse tree per $uv^2xy^2z$ (**pumping up**).
>È possibile eseguire pumping up/down quante volte si vuole.

**Dimostrazione**
Se $A$ è un context-free language (CFL), esiste una CFG $G$ tale che $L(G)=A$, definiamo $b$ come il numero massimo di simboli che occorrono a destra di una produzione di $G$.
>Assumiamo $b\geq 2$, altrimenti la CFG sostituirebbe i non terminali con un singolo carattere, rendendo impossibile generare infinite stringhe diverse.

Ad esempio in $S\to acd|aS$ si ha $b=3$.

Sia $V$ l'insieme di non-terminali di $G$, definiamo $p=b^{|V|+1}$.
Osserviamo che:
$$b^{|V|+1}\geq b^{|V|}+1\quad(\text{per }b\geq 2)$$

Consideriamo una stringa $w\in A$ con $|w|\geq p$, ciò implica che $|w|\geq b^{|V|}+1$.
Ragionando sull'[[Cos'è un albero#Caratteristiche di un albero|altezza del parse tree]] di $w$ notiamo che:
- Quando ha **altezza 1** la lunghezza massima di una sua stringa è $b$
- Quando ha **altezza 2** la lunghezza massima di una sua stringa è $b^2$
>Un parse tree di lunghezza $h$ genera stringhe di lunghezza massima $b^h$.

Dall'affermazione precedente abbiamo che i parse tree di $w$ hanno altezza almeno $|V|+1$, e fra tutti scegliamo quello col numero minimo di nodi, prendiamo poi il cammino più lungo di tale parse tree che ne definisce l'altezza, e noteremo che tale cammino deve contenere almeno $|V|+1$ non-terminali, ciò implica che lungo tale cammino c'è almeno un non-terminale che si ripete.
>Ci concentriamo sul non-terminale che si ripete tra i $|V|+1$ non-terminali più in basso nel cammino.

Procediamo a verificare le tre condizioni:
1. Dividiamo $s$ in $uvxyz$ come nel disegno
2. ($|vy|>0$). Assumiamo per assurdo che $|vy|=0$, allora $s=uxz$, e quindi se sostituiamo il più piccolo albero radicato in $R$ al posto di quello più grande, si ottiene un parse tree per $uxz$ che ha meno nodi del parse tree di partenza, ma ciò è assurdo perchè il parse tree di partenza è minimo
3. ($|vxy|\leq p$). Abbiamo preso un non-terminale $R$ che occorre sul cammino più lungo dell'albero e si ripete fra i $|V|+1$ non-terminali più in basso, di conseguenza l'altezza del sottoalbero più grande di $R$ è $|V|+1$, e tale sottoalbero che genera la stringa $vxy$ genera stringhe di lunghezza massima $b^{|V|+1}=p$

>[!Example]
>**Dimostriamo che $B=\{a^nb^nc^n|n\geq 0\}$ non è context-free.**
>
>Assumo per assurdo che $B$ sia context-free, allora deve valere il pumping lemma.
>Sia $p$ la sua pumping length, consideriamo la stringa $s=a^pb^pc^p$, abbiamo che $s\in B$ e $|S|\geq p$, assumiamo inoltre che $s$ si possa suddividere come $s=uvxyz$ con $|vy|>0$ e $|vxy|\leq p$, possiamo ragionare per casi:
>1. $v$ o $y$ contengono più di un tipo di carattere, in questo caso $uv^ixy^iz\notin B$ perchè l'ordine dei caratteri non è rispettato
>$$\underbrace{a}_u \underbrace{a}_v \underbrace{ab}_y \underbrace{bbccc}_z \Rightarrow \underbrace{a}_u \underbrace{aa}_{v^2} \underbrace{abab}_{y^2} \underbrace{bbcc}_z\quad(x=\epsilon)$$
>
>2. Sia $v$ che $y$ contengono un solo tipo di carattere, per esempio $v$ contiene solo delle $a$ e $y$ contiene solo delle $b$, questo vuol dire che c'è almeno un tipo di carattere che non occorre nè in $v$ nè in $y$, di conseguenza $uv^ixy^iz\notin B$ perchè eseguendo il _pumping-up_ un carattere sarà sottorappresentato.



