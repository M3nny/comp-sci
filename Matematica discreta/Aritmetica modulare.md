## Le operazioni
Un'operazione in un insieme $A$ è una applicazione:
$$*: A \times A \to A$$
$$(a,b)\mapsto a*b$$
Un'operazione si dice:
- **Associativa** se: $(a*b)*c=a*(b*c)$;
- **Commutativa** se: $(a*b)=b*a$.

Un elemento si dice:
- **Neutro** se: $a*e=e*a=a$;
- **Inverso** se: $a*a^{-1}=a^{-1}*a=e$.

Definiamo quindi **monoide** un insieme dotato di una operazione tale che l'operazione sia:
- Associativa;
- Dotata di elemento neutro.

>[!Example]
>$(\mathbb{N},+)$ è un monoide con elemento neutro $0$.

### Gruppi
Un **gruppo** $(G,*)$ è un monoide dove l'insieme è dotato di un'operazione che consente:
- Proprietà Associativa;
- Esistenza dell'elemento neutro;
- Ogni $x$ ammette l'inverso.

Inoltre un gruppo si dice **abeliano** (o commutativo) <u>se consente anche</u> la proprietà:
- Commutativa.

### Anelli
Un **anello** $(A,+,\cdot )$ è un insieme in cui sono definite due operazioni tali che:
- $(A,+)$ è un gruppo abeliano;
- $\cdot$ è associativa;
- Valgono le leggi distributive di $\cdot$ ;
Si dice **commutativo** se l'operazione $\cdot$ è commutativa.
Si dice con **identità** se esiste l'elemento neutro per ogni elemento dell'insieme.

### Campi
Un **campo** $(C, + , \cdot )$ è un insieme in cui sono definite due operazione tali che:
- $(C, + , \cdot )$ è un anello commutativo con identità;
- Ogni elemento $\neq 0$ è invertibile.

---
## La divisione euclidea
Per ogni coppia di numeri interi $a$ e $b$ con $b\neq 0$ esiste un'unica coppia di interi $q$ e $r$ tali che:
$$a=bq+r$$
con $0\leq r < |b|$.

## Modulo
Definiamo la somma $+_n$ ed il prodotto $*_n$ sui numeri interi come segue:
$$a+_n b = (a+b) \mod n$$
$$a*_n b = (ab)\mod n$$
Il risultato del modulo della somma e del prodotto è sempre un valore
compreso tra $0$ e $n-1$.

>[!Tip] Proprietà del modulo
>$$(a+b)\text{ mod } n = ((a\text{ mod } n)+(b\text{ mod } n)) \text{ mod } n$$
>$$(ab)\text{ mod } n = ((a\text{ mod } n)(b\text{ mod } n)) \text{ mod } n$$

### Gruppi ciclici
$\mathbb{Z} = \{0,1,2,3\}$ con l'operazione $+_4$ e $*_4$ è un **gruppo ciclico** perchè esiste un elemento generatore ($g=1$ ) che è in grado di generare tutti gli elementi di $\mathbb{Z}_4$.
$$1^1=1$$
$$1^2 = 2$$
$$1^3 = 3$$
$$1^4 = 0$$
Il **periodo** dell'elemento $1$ è pari a $4$ (perchè sono necessarie $4$ ripetizioni per tornare allo $0$ che è elemento neutro).
Il **sottogruppo** $<1>=\{0,1,2,3\}$ coincide con l'insieme $\mathbb{Z}_4$.

>[!Example]
>Sia $n=9$, calcolare $(95\cdot 37)\text{ mod }9 =$
>$$=((95 \text{ mod }9)(37\text{ mod }9)\text{ mod } 9$$
>$$=(5\cdot 1) \text{ mod } 9$$
>$$=5 \text{ mod }9$$
>$$=5$$

### Congruenze
Sia $n>0,\space n\in \mathbb{N}$.
Diciamo che $a,b\in \mathbb{Z}$ son congruenti in modulo $n$ ($a\equiv_n b$) se e solo se:
$$a \text{ mod }n = b \text{ mod }n$$

>[!Example]
>- $12\equiv_{10}2$ perchè $12=10\cdot 1+2$ e $2=10\cdot 0 +2$ (resto 2)

