La probabilità di un evento è un rapporto tra l'evento stesso e $\Omega$, con $\mathbb{P}(A|B)$ ovvero la probabilità di $A$ dato per vero/non incerto/accaduto $B$ ora considero solo l'evento $B$ come mio "spazio campionario", quindi:
$$\boxed{\mathbb{P}[A|B]=\frac{\mathbb{P}[A\cap B]}{\mathbb{P}[B]}}$$
Le regole di unione e intersezione valgono allo stesso modo, quindi ad esempio potrei ritrovare:
$$\mathbb{P}[\overline{A}|B]=\frac{\mathbb{P}[\overline{A}\cap B]}{\mathbb{P}(B)}=\frac{\mathbb{P}[B]-\mathbb{P}[A\cap B]}{\mathbb{P}}=1-\mathbb{P}[A|B]$$
Da notare che se abbiamo già dati a disposizione possiamo sempre trovare **formule inverse**:
$$\mathbb{P}[A\cap B]=\mathbb{P}[A|B]\mathbb{P}[B]$$
>[!Example]
>Un urna contiene quattro palle bianche numerate da 1 a 4 e tre palle nere numerate da 1 a 3, dalla quale si estrae casualmente una palla con eventi:
>- $B$ = viene estratta una palla bianca
>- $N$ = viene estratta una palla nera
>- $C_i$ = viene estratto il numero $1 \leq i \leq 4$
>$$\mathbb[C_1|B]=\frac{\mathbb{P}[C_1\cap B]}{\mathbb{P}[B]}=\frac{1/7}{4/7}=\frac{1}{4}$$
>$$\mathbb[C_1|N]=\frac{\mathbb{P}[C_1\cap N]}{\mathbb{P}[N]}=\frac{1/7}{3/7}=\frac{1}{3}$$
>$$\mathbb[N|C_1]=\frac{\mathbb{P}[N\cap C_1]}{\mathbb{P}[C_1]}=\frac{1/7}{2/7}=\frac{1}{2}$$
>
>Da considerare anche che: $\mathbb{P}[N|C_1]=1-\mathbb{P}[B|C_1]=\frac{1}{2}$ dato che $N=\overline{B}$.

Dalla probabilità condizionata possiamo trovare anche la **formula delle probabilità composte**:
$$\mathbb{P}[A_1\cap A_2\cap ... \cap A_n]=\mathbb{P}[A_1]\cdot\mathbb{P}[A_2|A_1]\cdot\mathbb{P}[A_3|A_1\cap A_2]\cdot...\cdot\mathbb{P}[A_n|A_1\cap ...\cap A_{n-1}]$$

>[!Example]
>Si lancia _tre_ volte una moneta, quante sono le probabilità che le prime _due_ volte esca croce e la _terza_ volta testa?
>![[Probabilità composta.png|450]]
>$$\mathbb{P}[C_1\cap C_2\cap T_3]=\mathbb{P}[C_1]\mathbb{P}[C_2|C_1]\mathbb{P}[T_3|C_1\cap C_2]=$$
>$$=\frac{1}{2}\cdot\frac{1}{2}\cdot\frac{1}{2}=\frac{1}{8}$$

## Eventi indipendenti
Due eventi si dicono **indipendenti** se: $\mathbb{P}[A|B]=\mathbb{P}[A]$
ed in questo caso vale anche $\mathbb{P}[A|\overline{B}]=\mathbb{P}[A]$.
La **definizione di eventi indipendenti** è quindi data da:
$$\boxed{\mathbb{P}[A\cap B]=\mathbb{P}[A]\mathbb{P}[B]}$$
la definizione si può estendere ad una collezione infinita di eventi, i quali saranno indipendenti se ogni sottoinsieme finito di essi è formato da eventi indipendenti.


>[!Attention]
>Eventi indipendenti e disgiunti sono cose diverse, due eventi disgiunti possono essere indipendenti solo se uno di essi ha probabilità $0$.

Sotto l'**ipotesi di indipendenza** possiamo eseguire calcoli semplici, ad esempio:
- **Sistemi in serie**: dove il sistema $A$ funziona se tutti gli $n$ componenti funzionano e $p_i$ è la probabilità che si guasti l'elemento $i$, se si guastano in modo indipendente allora la probabilità che il sistema funzioni è data da: $$\mathbb{P}[A]=\mathbb{P}\left[\bigcap_{i=1}^n A_i\right]=\prod_{i=1}^n\mathbb{P}[A_i]=\prod_{i=1}^n(1-p_i)$$
- **Sistemi in parallelo**: funziona quando almeno uno degli $n$ elementi funziona, usando sempre le stesse variabili di prima, se i componenti si guastano in modo indipendente:
$$\mathbb{P}[A]=1-\mathbb{P}[\overline{A}]=1-\mathbb{P}\left[\bigcap_{i=1}^n\overline{A}_i\right]=1-\prod_{i=1}^n\mathbb{P}[\overline{A}_i]=1-\prod_{i=1}^np_i$$
---
## Teorema di Bayes
A volte, è più semplice calcolare la probabilità di un evento $B$ che dipende da un altro evento $A$, rispetto a calcolare direttamente la probabilità di $A$.

Eseguendo il test di una malattia, abbiamo due esiti:
- Malato $M$
- Non malato $\overline{M}$
Però ci possono essere sia **falsi positivi** $\mathbb{P}\Big[+|\overline{M}\Big]$, sia **falsi negativi** $\mathbb{P}\Big[-|M\Big]$.
$$\mathbb{P}\Big[M\Big]=\text{prevalenza}\quad\mathbb{P}\Big[+|M\Big]=\text{sensitività}\quad\mathbb{P}\Big[-|\overline{M}\Big]=\text{specificità}$$
```mermaid
---
title: Distribuzione di probabilità della malattia
---
stateDiagram-v2
	direction LR
    [*] --> M: P(M)
    [*] --> ¬M: P(¬M)
    M --> pos(sensitività): P(+|M)
    M --> neg(falso_negativo): P(-|M)
    ¬M --> pos(falso_positivo): P(+|¬M)
    ¬M --> neg(specificità): P(-|¬M)
```
Avendo inizialmente i seguenti dati:
- $\mathbb{P}[M]=0.001$
- $\mathbb{P}[+|M]=0.95$
- $\mathbb{P}[-|\overline{M}] = 0.98$
è facile ricavare la probabilità di un falso positivo e falso negativo:
$$\mathbb{P}\Big[+, \overline{M}\Big]=\mathbb{P}\Big[\overline{M}\Big]\mathbb{P}\Big[+|\overline{M}\Big] \approx 0.01998\quad\quad\quad\mathbb{P}\Big[-,M\Big]=\mathbb{P}\Big[M\Big]\mathbb{P}\Big[-|M\Big] \approx 0.00005$$
possiamo ricavare anche la probabilità che una persona sia positiva dopo aver fatto il test:
$$\mathbb{P}\Big[+\Big]=\mathbb{P}\Big[M\Big]\mathbb{P}\Big[+|M\Big]+\mathbb{P}\Big[\overline{M}\Big]\mathbb{P}\Big[+|\overline{M}\Big] \approx 0.02093$$
>[!Tip]
>$\mathbb{P}[A, B] = \mathbb{P}[A\cap B]$

Non è banale invece ricavare quale è la probabilità $M$ e $\overline{M}$, possiamo quindi usare la **formula di Bayes**:
$$\boxed{\mathbb{P}[C_m|A]=\frac{\mathbb{P}[A|C_m]\mathbb{P}[C_m]}{\sum_i(\mathbb{P}[A|C_i]\mathbb{P}[C_i])}}$$
quindi:
$$\mathbb{P}[M|+]=\frac{\mathbb{P}[M\cap +]}{\mathbb{P}[+]}=\frac{\mathbb{P}[+|M]\mathbb{P}[M]}{\mathbb{P}[+|M]\mathbb{P}[M]+\mathbb{P}[+|\overline{M}]\mathbb{P}[\overline{M}]}\approx 0.045$$

---
