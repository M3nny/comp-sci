Gli spazi vettoriali sono correlati ai seguenti argomenti visti in matematica discreta: [[Aritmetica modulare#Gruppi|gruppi]], [[Aritmetica modulare#Anelli|anelli]], e [[Aritmetica modulare#Campi|campi]].

## Definizione
Sia $K$ un campo numerico dove gli elementi al suo interno sono degli scalari, uno **spazio vettoriale** su $K$ è costituito da un insieme di vettori $V$ dotati di:
- Somma vettoriale
- Prodotto scalare

Inoltre devono valere i seguenti **assiomi** con $a,b,c,d\in V$ _vettori_ mentre $m,s\in \mathbb{K}$ _scalari_: 
| **Assioma n°** | **proprietà**               | **nome proprietà**      |
| ----------- | ----------------------- | ------------------- |
| 1           | $a+(b+c) = (a+b)+c$   | prop. associativa   |
| 2           | $a+b = b+a$           | prop. commutativa   |
| 3           | $0+a = a = a+0$       | elem. neutro        |
| 4           | $a+(-a) = 0 = (-a)+a$ | inversa della somma |
| 5           | $(r+s)a = ar + as$    | prop. distributiva  |
| 6           | $(r\cdot s)a = r(sa)$ | prop. distributiva  |
| 7           | $r(a+b) = ra+rb$      | prop. distributiva  |
| 8           | $O \cdot a = O$       | O = vettore nullo   |

### Sottospazi
Un **sottospazio vettoriale** di uno _spazio vettoriale_ $V$ è un **sottoinsieme** $W$ che eredita da $V$ una struttura di spazio vettoriale, ciò è possibile se $W$ sia **non vuoto** e sia **chiuso rispetto le due operazioni** di somma e prodotto, inoltre $W$ deve contenere lo zero di $V$.

>Ogni retta passante per l'origine è sottospazio di $\mathbb{R}^2$ 
>Quelle che non passano per l'origine <u>non sono sottospazi vettoriali</u>

### Combinazione lineare
Una combinazione lineare la possiamo trovare sotto la forma di:
$$a_1v_1+...+a_nv_n$$
Dove $v$ sono **elementi dello spazio vettoriale**, mentre $a$ sono **scalari** ed il risultato sarà un nuovo elemento dello spazio.

#### Combinazione lineare banale
Si dice così se è una combinazione formata da un unico vettore nullo.

## Vettori linearmente dipendenti e indipendenti
Avendo dei **vettori** $v \in V$ e dei **coefficienti** $a\in\mathbb{K}$, imponiamo l'uguaglianza:
$$a_1v_1+a_2v_2+...+a_nv_n=0$$
I vettori si dicono:
- **linearmente indipendenti** se tutti i coefficienti sono $= 0$;
- **linearmente dipendenti** se esiste almeno un coefficienti _non nullo_.

## Base di uno spazio vettoriale
Una base è un insieme di vettori _linearmente indipendenti_ che generano l'intero spazio vettoriale attraverso le combinazioni lineari (vedi sistemi generatori).

Le basi quindi contengono il numero minimo di vettori necessari per generare uno spazio vettoriale.
Ad esempio per $\mathbb{R}^2$ saranno due i vettori: l'asse x e l'asse y, se aggiungo un terzo vettore ottengo una terna.
>[!Teorema di completamento di una base]
>Se usiamo le immagini dei vettori di una base, essi formano un sistema di generatori

### Base canonica
Una base canonica è un insieme formato da vettori i quali elementi sono:
- tutti nulli tranne l'$i$-esimo elemento

Con la base canonica formata dall'insieme $\{e_1, e_2, ..., e_n\}$ avremmo che:
$$e_1 = (1,0,0,...,0)$$
$$e_2 = (0,1,0,...,0)$$
$$e_n = (0,0,0,...,1)$$
ne deduciamo quindi che $\dim(\mathbb{R}^n) = n$.

### Base ortogonale
Una base è definita ortogonale quando il prodotto scalare tra qualsiasi coppia di elementi dello stesso vettore è uguale a zero: $v_i\cdot v_j = 0$ con $i\neq j$ .

### Base ortonormale
Una base è ortonormale se oltre ad essere _ortogonale_, la norma di ogni vettore che la compone è $1$.
