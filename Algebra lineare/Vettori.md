# Introduzione agli spazi vettoriali
Possiamo rappresentare punti in spazi con più di due dimensioni, ad esempio su tre dimensioni un punto sarà caratterizzato da $(x, y ,z)$.

Indichiamo con lettere:
- **Maiuscole**: un punto.
- **Minuscole**: un vettore.

### Somma
L'operazione somma può essere <u>rappresentata graficamente con un parallelogramma</u>:
![[Grafico somma.png]]

Per l'**addizione** di due punti valgono le proprietà generali della somma tra cui:
- **Associativa**: $(A+B)+C=A+(B+C)$
- **Commutativa**: $A+B=B+A$
- **Distributiva**: $C(A+B)=CA+CB$
- **Coordinate nulle**: $0+A=A+0=A$

Quando applichiamo un valore scalare ad un vettore (moltiplichiamo per uno scalare) lo **ridimensioniamo**:
![[Ridimensionamento.png]]
Un **vettore applicato** è una coppia ordinata di punti che denoteremo come $\overrightarrow{AB}$, dove $A$ è l'_origine_ e $B$ è la _fine_ del vettore.
Se <u>applichiamo un vettore all'origine</u>, potremmo dire che è determinato solo dalla sua fine, possiamo trovarlo tramite: $A - B$.
![[Vettore applicato.png]]

## Prodotto scalare
Siano:
- $A=(a_1, a_2, ..., a_n)$
- $B=(b_1, b_2, ..., b_n)$

Quindi aventi spazio di $n$ dimensioni.
Possiamo calcolare il loro **prodotto scalare** procedendo in questo modo:
$$a_1b_1+a_2b_2+...+a_n+b_n$$
$$\text{ovvero}$$
$$\sum^n_{i=1}{a_ib_i}$$
Quindi vado da $\mathbb{R}^n$ a $\mathbb{R}$, prima avevo molte dimensioni, ma dopo averli moltiplicati ottengo un numero scalare.
>[!Example]
>- $A=(1, 3, -2)$
>- $B=(-1, 4, -3)$
>$$A\cdot B= 1\cdot (-1)+3\cdot 4+ (-2)\cdot 3=-1+12+6=17$$

Oppure se possediamo l'angolo $\phi$ tra i due vettori possiamo usare la seguente formula:
$$v\cdot w=cos\phi||v||\cdot ||w||$$


### Proprietà
**PS 1**: $A\cdot B = B \cdot A$;
**PS 2**: $A\cdot (B+C)=A\cdot B + A\cdot C$;
**PS 3 (con $x$ che è un numero)**: $(xA)B=x(AB)$;
**PS 4**:se $A=0$ allora $A\cdot A = 0$ altrimenti; in ogni altri caso abbiamo $A\cdot A>0$.
>[!Info]
>Se abbiamo un prodotto di due vettori che è uguale a $0$ allora sono perpendicolari.

### Modulo o Norma o lunghezza
Può essere chiamata con uno dei tre nomi che precedono la **lunghezza** di un vettore, e si calcola tramite:
$$||A||=||a_1,a_2||=\sqrt{(a_1)^2+(a_2)^2}$$
### Vettore unità o normalizzato
Indichiamo con $\tilde{v}$ un vettore di lunghezza pari a $1$, che è anche chiamato **normalizzato**, e può essere calcolato tramite:

$$\tilde{v}=\frac{v}{||v||}$$
>[!Example]
>**Normalizzare il seguente vettore:**
>$$v=\begin{bmatrix} 2 \\ 3 \\\end{bmatrix}$$
>Trovo la norma
>$||v||=\sqrt{2^2+3^2}=\sqrt{13}$
>
>Normalizzo il vettore
>$\tilde{v}=\frac{v}{||v||}=(\frac{2}{\sqrt{13}}, \frac{3}{\sqrt{13}})$

### Distanza tra punti
È possibile trovare la **distanza** tra due punti facendo la <u>norma del vettore che li congiunge</u>.
$$dist(A,B)=||\overrightarrow{AB}||=\sqrt{(x_b-x_a)^2+(y_b-y_a)^2}$$
>[!Example]
>**Trova la distanza tra A e B:**
>$$A=(-2,1)\quad B=(2,1)$$
>Applico la formula
>$dist(A, B)= \sqrt{(2-(-2))^2+(1-1)^2}=\sqrt{16+0}=4$

## Vettori allineati
Per verificare che due vettori siano **allineati** bisogna che il prodotto tra i due vettori ed il prodotto tra le loro lunghezze sia uguale:
$$A\cdot B = \pm ||A||\cdot ||B||$$
![[Vettori allineati.svg]]
>[!Example]
>**Verifica se i vettori sono allineati:**
>$$A=(-2,0)\quad B=(-3,0)$$
>- $A\cdot B= (2\cdot -3) + (0\cdot 0)=-6$;
>- $||A||\cdot ||B||=2\cdot 3=6$
>I vettori sono allineati.

## Proiezioni
Possiamo calcolare la Proiezione di un vettore $A$ su un vettore $B$ tramite:
$$P=\frac{A\cdot B}{B\cdot B}\cdot B$$
Oppure se abbiamo l'angolo:
$$P=||A||\cdot cos\alpha \cdot \frac{B}{||B||}$$
