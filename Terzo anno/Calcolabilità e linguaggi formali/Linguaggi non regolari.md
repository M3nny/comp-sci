Se vogliamo dimostrare la regolarità di un linguaggio $A$ possiamo sfruttare un [[Automi a stati finiti#Definizione DFA|DFA]], un [[Automi a stati finiti non deterministici#Definizione di NFA|NFA]] oppure una [[Espressioni regolari|espressione regolare]], ma per dimostrare che $A$ non è regolare è più difficile.

Un linguaggio non regolare è il seguente: $\{0^n1^n|n\geq 0\}=\{\epsilon,01,0011,...\}$, un automa infatti non potrà riconoscerlo, bisognerebbe tener traccia degli $0$ e degli $1$, ma non è possibile con stati finiti.

## Pumping lemma
Sia $A$ un linguaggio regolare, allora esiste un intero $p\geq 1$ (lunghezza del pumping) tale che per ogni stringa $s\in A$ con lunghezza $|s|\geq p$, si ha $s=xyz$ per qualche $x,y,z$ tali che:
1. $\forall i\geq 0:xy^iz\in A$
2. $|y|>0$
3. $|xy|\leq p$

>$y^i$ indica $i$ copie di $y$ concatenate, $y^0=\epsilon$.

>[!Info]
>Notare che senza la seconda condizione, ovvero $y\neq \epsilon$, il lemma sarebbe sempre vero.
>
>La condizione tre afferma che le parti $x$ e $y$ insieme hanno lunghezza al massimo $p$.

**Dimostrazione**:
Sia il linguaggio $A$ regolare, allora esiste un DFA $D$ tale che $L(D)=A$.

Poniamo $p$ pari al numero di stati di $D$ considerando una stringa $s=w_1w_2...w_n$, con lunghezza $n\geq p$ e tale che $D$ accetta $s$, visto che $D$ accetta $s$, esiste una sequenza di stati $q_0,q_1,...,q_n$ tali che $q_0$ è iniziale, $q_n$ è accettante, e ogni stato passa in un altro usando la funzione di transizione, riassumendo si ha:
- $p$ = numero di stati del DFA
- $s=w_1...w_n$ con $n\geq p$
- $\underbrace{q_0,q_1,...,q_n}_\text{n+1 stati }$ con $n\geq p$

Abbiamo detto che $n$ è la lunghezza della stringa $s$, mentre la lunghezza della sequenza di stati usata per rappresentare $s$ sarà pari a $n+1$ (a causa dello stato iniziale), poichè $n$ è almeno $p$ (numero di stati di $D$) e $n+1$ è il numero di stati usati per rappresentare $s$, si avrà che almeno uno stato viene ripetuto, chiamiamo questo stato $q_i$.

Rappresentando graficamente l'attraversamento del DFA:
![[Pumping lemma attraversamento.svg|400]]
Gli archi inclusi nel cammino sono etichettati con i caratteri di $s$ (essendo un DFA), definiamo le parti di stringa come:
- $x: q_0\to q_i$
- $y:q_i\to q_i$
- $z:q_i\to q_n$

Questa rappresentazione **soddisfa le tre condizioni del pumping lemma** in quanto:
1. È vero che $\forall i\geq 0$ (qualsiasi **pumping length**) ovvero ripetizione della parte $y$, la stringa $s$ appartiene al linguaggio $A$
2. È vero che $|y|>0$ in quanto abbiamo almeno uno stato che si ripete, e quindi esiste almeno un carattere che etichetta l'arco tra $q_i$ e $q_i$ stesso
3. Ci assicuriamo che $q_i$ rappresenti la prima ripetizione nella sequenza e poichè i primi $p+1$ stati nella sequenza conterranno una ripetizione si deduce che $|xy|\leq p$

#### Utilizzare il pumping lemma
Sia $A$ il linguaggio di cui si vuole dimostrare la <u>non</u> regolarità: si assume per assurdo che $A$ sia regolare, visto che $A$ è regolare deve valere il pumping lemma, si contraddice il pumping lemma (controesempio), si conclude infine che $A$ <u>non</u> è regolare.

Quindi si va a verificare l'opposto del pumping lemma, ovvero:
**Esiste** una stringa $s\in A$ con $|s|\geq p$ tale che **per ogni** $xyz$ tali che $s=xyz$ si abbia:
1. $\exists i\geq 0, xy^iz\notin A$, **oppure**
2. $|y|=0$, **oppure**
3. $|xy|>p$

>[!Example]
>**Dimostriamo che $A=\{0^n1^n\}$ non è regolare.**
>Assumiamo per assurdo che $A$ sia regolare, allora deve valere il pumping lemma.
>
>Prendiamo come esempio la stringa $s=0^p1^p$ (lunga $2p$ caratteri), essa deve essere parametrica rispetto a $p$ in quanto non sappiamo quanto valga $p$.
>
>Scriviamo $s$ nella forma $s=xyz$ con $|y|>0$ e $|xy|\leq p$, dimostriamo poi che esiste $i\geq 0$ tale che $xy^iz\notin A$.
>
>Una soluzione può sfruttare il fatto di ragionare sui caratteri che stanno in $y$, ovvero:
>1. $y$ contiene solo $0$
>	Allora $xy^2z$ ha forma $0^{p+k}1^p$ con $k>0$ (perchè $|y|>0$), tale stringa non sta in $A$ perchè ha più $0$ che $1$.
>2. $y$ contiene solo $1$
>	Allora $xy^2z$ ha forma $0^p1^{p+k}$ (sempre con $k>0$) tale stringa non sta in $A$ perchè ha più $1$ che $0$.
>3. $y$ contiene sia $0$ che $1$
>	Allora $xy^2z$ avrà degli $1$ prima degli $0$ (in disordine quindi), ad esempio: $00\underbrace{0101}_{yy}11$ non è accettata. 
>
>>Nota che $xy^2z=xyyz$.
>
>Un'altra soluzione (più efficace) sfrutta la terza condizione, ovvero $|xy|\leq p$:
>
>Essendo che la stringa usata come controesempio è $s=0^p1^p$, e dato che $y$ sta nei primi $p$ caratteri (a causa di $|xy|\leq p$), si avrà che $y$ comprende solo $0$, di conseguenza $xy^2z\notin A$ perchè avrebbe forma $0^{p+k}1^p$ con $k>0$.
>
>---
>
>**Dimostriamo che $F=\{ww|w\in\{0,1\}^*\}$ non è regolare.**
>Assumiamo per assurdo che $F$ sia regolare e prendiamo come controesempio la stringa $s=0^p10^p1$.
>
>Sia $s=xyz$ con $|y|>0$ e $|xy|\leq p$, applicando $|xy|\leq p$ sappiamo che $y$ sta nei primi $p$ $0$, quindi $xy^2z$ ha forma $0^{p+k}10^p1$ (con $k>0$), in questo caso la prima parte è più lunga dell'altra per cui $xy^2z\notin F$.
>>Notare come la stringa $s=0^p10^p1$ esibisce la non regolarità di $F$, a differenza di un'altra possibile stringa come $0^p0^p$ la quale non riesce a dar luogo a una contraddizione.
>














