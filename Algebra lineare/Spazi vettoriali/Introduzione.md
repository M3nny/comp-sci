# Introduzione agli spazi vettoriali
Possiamo rappresentare punti in spazi con più di due dimensioni, ad esempio su tre dimensioni un punto sarà caratterizzato da $(x, y ,z)$.

Indichiamo con lettere:
- **Maiuscole**: un punto.
- **Minuscole**: un vettore.

### Proprietà somma
Per l'**addizione** di due punti valgono le proprietà generali della somma tra cui:
- **Associativa**: $(A+B)+C=A+(B+C)$
- **Commutativa**: $A+B=B+A$
- **Distributiva**: $C(A+B)=CA+CB$
- **Coordinate nulle**: $0+A=A+0=A$

Quando applichiamo un valore scalare ad un vettore lo **allunghiamo**:
$v 3(1,1)=(3,3)$
![[Scalare applicato a vettore.svg]]
Un **vettore applicato** è una coppia ordinata di punti che denoteremo come $\overrightarrow{AB}$, dove $A$ è l'origine e $B$ è la fine del vettore.
Se <u>applichiamo un vettore all'origine</u>, potremmo dire che è determinato solo dalla sua fine, è anche più facile lavorare con vettori applicati all'origine, quindi è bene traslarli fino ad essa.
![[vettore applicato a origine.svg]]

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


### Proprietà prodotto
**Commutativa**: $A\cdot B = B \cdot A$
**Distributiva**: $A\cdot (B+C)=A\cdot B + A\cdot C$
**Associativa**: $(XA)B=X(AB)$
**PS4**:$A\cdot A = 0 \text{ altrimenti }A\cdot A >0 (\text{ somme di quadrati > 0 per forza})$
>[!Info]
>Se abbiamo un prodotto di due vettori che è uguale a $0$ allora sono perpendicolari.

### Modulo o Norma o lunghezza
Può essere chiamata con uno dei tre nomi che precedono la **lunghezza** di un vettore, e si calcola tramite:
$$||v||=\sqrt{\sum^n_{i=1}(v_i)^2}$$
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