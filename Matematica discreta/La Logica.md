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
>[!Example]
>**Dimostrare che un numero naturale è un multiplo di 12 <u>se e solo se</u> esso è un multiplo di 3 e un multiplo di 4**
>La dmistrazione è divisa in 2 parti
>- ($\Rightarrow$ sufficiente): 
>Se $n$ è un multiplo di 12, allora $n=12\cdot t$ dove $t\in \mathbb{N}$, ma:
>$$12=3\cdot 4=4\cdot 3$$
> Quindi
> $$n=3\cdot (4\cdot t) = 4\cdot (3\cdot t)$$
>$$n=3\cdot S_1 = 4\cdot S_2$$
>Troviamo quindi che $n$ è un multiplo di 4
>
>- ($\Leftarrow$ necessario):
>Supponiamo che $n=3\cdot r$ e $n=4\cdot s$, dimostriamo che $n=12\cdot t$
>$$3r = 4s$$
>Quindi $4s$ è un multiplo di $3$, ma $4$ non è un multiplo di $3$, quindi deve essere che $s$ è un multiplo di $3$, cioè $s=3\cdot t$
>$$n=4s=4\cdot (3\cdot t)= 12\cdot t$$

## Connettivi logici
- Hanno un ordine di priorità, dal primo all'ultimo:
$$1°\quad \neg$$
$$2°\quad \land$$
$$3°\quad \lor$$
$$4°\quad \implies$$
$$5°\quad \iff$$

## Quantificatori

### Universale
- $\forall x \in X, P(x)$ ovvero: tutti gli elementi $x$ appartenenti a $X$ soddisfano la proprietà $P(x)$.
- $\forall$ è **falso** quando **almeno un elemento non soddisfa** $P(x)$.
- $\forall$ è una forma abbreviata di: $$P(0) \land P(1) \land P(2) \land ... \land P(n) \land ...$$
>[!Example]
>Considerando: $X = \{ n \in \mathbb{N} | 1\leq n \leq 1000\}$
>
>Dimostrare che la seguente proposizione è falsa:
>$\forall x \in X, \quad x^2+x+41$ è un numero primo.
>
>Dobbiamo quindi esibire un **contro-esempio**.
>Inizialmente potremmo andare per tentativi e quindi proviamo con $x=1$, il quale risulta $1^2+1+41=43$ che è primo, dunque $x=1$ non è un contro-esempio.
>Andiamo a fare un altro tipo di ragionamento, ovvero: per essere sicuri che $x^2+x+41$ non sia un numero primo, dobbiamo assegnare ad $x$ un valore che produce un fattore comune tra $x^2, x, 41$, quindi proviamo con $x=41$.
>$$41^2+41+41=$$
>$$=41(41+1+1)= 41\cdot 43$$
>Il prodotto $41 \cdot 43$ sicuramente non è un numero primo, quindi abbiamo trovato il contro-esempio e abbiamo dimostrato che proposizione è falsa.

### Esistenziale
- $\exists n \in  \mathbb{N}$ ovvero: esiste un numero $n$ naturale.
- $\exists$ è **falso** quando è falso per ogni elemento.

## Tautologie, contraddizioni, soddisfacibilità
Possiamo dare una definizione ai risultati di operazioni in base a quanti valori veri e falsi posseggono.
**Tautologia**: tutti veri.
**Contraddizione**: tutti falsi.
**Soddisfacibile**: possiede dei valori sia veri che falsi.


















