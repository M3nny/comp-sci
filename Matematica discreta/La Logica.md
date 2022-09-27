# La logica matematica
La logica matematica <u>studia il ragionamento matematico e le proposizioni</u>, che possono avere **valori di verità** per cui le proposizioni, più specificatamente, i **predicati** <u>sono veri o falsi</u>.

- $x+1$ non è un predicato perchè non ha un valore che può essere vero o falso.
- x > 9 è un predicato perchè può essere vero o falso.

La logica inoltre è un tipo di **algebra booleana**, dove tale algebra è definita su un insieme di due soli elementi: vero o falso.

## Tipi di predicato
### Predicati atomici
Esprimono una <u>relazione tra oggetti</u>.
|    3 < 5    | V |
|:-----------:|:-:|
|   5+7 = 13  | F |
|  3 = 5 + 6  | F |
| 5 è dispari | V |

### Predicati atomici con con variabili
Dove le <u>variabili devono essere espresse in un dominio</u> (o universo).
- $x$ divide $22 \quad x\in \mathbb{N}$
- $x+y = y+x \quad x,y \in \mathbb{R}$
- $x$ è primo $\quad x\in \mathbb{Z}$
- $P(x)$ significa: $x$ soddisfa la proprietà $P$

### Predicati composti
Creati con <u>predicati semplici assieme a connettivi logici e quantificatori</u>.
- $5$ è un numero primo **e** $8$ è un numero pari
- $5$ **non** è un numero pari
- Un numero è pari **se e solo se** è divisibile per 2
- **Ogni** numero naturale è somma di 2 numeri primi
- **Per ogni** $x$ esiste $y$ tale che $P(x,y)$

## Connettivi logici
- $\lor$ congiunzione
- $\land$ disgiunzione
- $\neg$ negazione

I valori di verità possono essere riassunti nelle **tabelle di verità**:

![[tabella verità and or not.png]]

## Leggi di De Morgan
>[!Teorema]
>$$\neg(P\lor Q) \quad = \quad (\neg P) \land (\neg Q)$$
>$$\neg(P\land Q) \quad = \quad (\neg P) \lor (\neg Q)$$


## Implicazione
- $P \implies Q$, ovvero: Tutte le volte in cui $P$ è vero, allora anche $Q$ è vero.
- In questo è indicata con $P$ la **precondizione** e con $Q$ la **conclusione**.
- <u><b>L'unico</b> caso in cui un'implicazione è falsa</u>, è quando: la <u>precondizione è vera</u> e la <u>conclusione</u> è falsa.
>[!Example]
>$$P(x) x \geq 10$$
>$$Q(x) x > 5$$
>Allora $\forall n \in \mathbb{N}$
>$$P(n)\implies Q(n)$$
>$$n \geq 10 \implies n > 5$$
>Se $n \geq 10$ allora $n>5$

>[!Info]
>$$P \implies Q \equiv \neg(P\land (\neg Q))$$
>Per le leggi di De Morgan:
>$$\neg(P\land (\neg Q)) = (\neg P) \lor Q$$
>Allora possiamo dedurre:
>$$P \implies Q = (\neg P) \lor Q$$


Per cui la tabella di verità di $P \implies Q$ sarà la seguente:

![[tabella verità implica.png]]

## Doppia implicazione
- $P \iff Q \quad \equiv \quad (P\implies Q)\land (Q\implies P)$
- $P \implies Q$ condizione **sufficiente**
- $Q\implies P$ condizione **necessaria**
- É falsa solo se $P$ è vera e $Q$ è falsa
![[tabella verità se e solo se.png]]
