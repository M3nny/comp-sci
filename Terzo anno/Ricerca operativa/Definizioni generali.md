## Spazi vettoriali
Uno **spazio vettoriale** è un insieme $V^n(K)$ di elementi (vettori) con **campo** $K$ che soddisfano $8+1$ proprietà, in cui i simboli $+,\oplus, \cdot, \bullet$ rappresentano quattro operazioni binarie arbitrarie.

0. $\forall u,v\in V^n(K),\quad u+v\in V^n(K)$
	**Chiusura** rispetto a l'operatore $+$, ovvero l'operatore applicato a due elementi dello stesso tipo ritorna un valore dello stesso tipo.
	
1. $\forall u,v,z\in V^n(K),\quad (u+v)+z = u+(v+z)$
	Proprietà **associativa**.
	
2. $\exists w\in V^n(K): \forall v\in V^n(K),\quad w+v = v$
	Elemento **neutro (o nullo)**.
	
3. $\forall v\in V^n(K),\quad\exists \overline{v}\in V^n(K): v+\overline{v}=w$
	Elemento **opposto (o inverso)**.
	
4. $\forall u,v\in V^n(K),\quad u+v=v+u$
	Proprietà **commutativa**.
	
5. $\forall a,b\in K, \forall v\in V^n(K), a \bullet v\in V^n(K),\quad (a\cdot b)\bullet v=a\bullet (b\bullet v)$
6. $\exists\sigma\in K:\forall v\in V^n(K),\quad \sigma\bullet v = v$
7. $\forall a,b\in K, \forall v\in V^n(K),\quad (a\oplus b)\bullet v=a\bullet v+b\bullet v$
8. $\forall a\in K, \forall u,v\in V^n(K),\quad a\bullet (u+v)=a\bullet u + a\bullet v$

>[!Example]
>**Dimostriamo come il prodotto tra due numeri negativi è positivo**.
>$$(-2)\cdot (-3)$$
>Il nostro spazio vettoriale avrà $n=1$, e sarà quindi rappresentato da $\mathbb{R}(\mathbb{R})$.
>$$\begin{flalign}(-2)[+3+(-3)]&=0\\&=(-2)\cdot(+3)+(-2)\cdot(-3)=0\\&=-6+(-2)\cdot(-3)=0\\&=6-6+(-2)\cdot(-3)=6\\&=(-2)\cdot(-3)=6\end{flalign}$$

### Indipendenza lineare
L'apice $n$ in $\mathbb{R}^n$ rappresenta la **dimensione** dello spazio vettoriale, ovvero il numero massimo di vettori _linearmente indipendenti_ usati per rappresentare lo spazio vettoriale.
>D'ora in poi $\mathbb{R}^n=\mathbb{R}^n(\mathbb{R})$

Nelle matrici è possibile trovare come pedice il numero di righe $n$ ed il numero di colonne $m$, la dimensione è data da $n\cdot m$ (e.g. $M_{n,m}(\mathbb{R})$).

Un vettore $z=z_1,...,z_m\in \mathbb{R}^n(\mathbb{R})$ si dice **linearmente indipendente** quando:
$$z=0\iff a_1=...=a_m=0$$
ovvero: il vettore è nullo sse la _combinazione lineare_ (una qualsiasi) avente coefficienti nulli ritorna un vettore nullo.

Ad esempio nella matrice $M_{2,3}(\mathbb{R})$ i vettori linearmente indipendenti sono:
$$
\begin{pmatrix}1&0&0\\0&0&0\end{pmatrix}
\begin{pmatrix}0&0&0\\1&0&0\end{pmatrix}
\begin{pmatrix}0&1&0\\0&0&0\end{pmatrix}
\begin{pmatrix}0&0&0\\0&1&0\end{pmatrix}
\begin{pmatrix}0&0&1\\0&0&0\end{pmatrix}
\begin{pmatrix}0&0&0\\0&0&1\end{pmatrix}
$$
infatti tramite le loro combinazioni è possibile qualsiasi tipo di matrice $M_{2,3}(\mathbb{R})$.

Dati gli $n$ vettori $v_1,...,v_n\in\mathbb{R}^n$, essi risultano _linearmente indipendenti_ (su $\mathbb{R}$) sse il determinante della matrice da essi formata è non nullo:
$$\left(v_1\space\vdots\space...\space\vdots\space v_n\right)\in\mathbb{R}^{n\times n}$$
dove la prima colonna è data da: $v_i^1=\begin{pmatrix}v_1^1\\\vdots\\v_n^1\end{pmatrix}$.

Per indicare le **funzioni continue** nell'intervallo $[a,b]$ usiamo la seguente notazione (nel nostro caso $a=-\infty, b=\infty$):
$$C^0[a,b]=\{\sin(x),\cos(x),...\}$$
>$C^0$ rappresenta le funzioni continue, $C^1$ le funzioni derivabili almeno una volta, dove la derivata è anch'essa continua (vedi [[Funzioni vettoriali#Continuità/Derivabilità/Integrabilità|continuità]]).


### Combinazioni lineari
Una **combinazione lineare** dati $z_1,...,z_m\in\mathbb{R}^n$ e $a_1,...,a_m\in\mathbb{R}$ è definita come:
$$z=a_1z_1+...+a_mz_m$$

Una **combinazione affine** è una _combinazione lineare_ in cui:
$$z=a_1z_1+...+a_mz_m\quad\text{con}\quad\sum_{i=1}^ma_i=1$$
geometricamente appare come una retta passante passante per due punti specifici dei vettori:
![[Combinazione affine.svg|250]]
in tre dimensioni crea un _piano_.

Una **combinazione conica** è una _combinazione lineare_ in cui:
$$z=a_1z_1+...+a_mz_m\quad\text{con}\quad a_i\geq 0,\space i=1,...,m$$
geometricamente appare come l'area della superficie infinita generata dai due vettori:
![[Combinazioni coniche.svg|400]]
in tre dimensioni è il volume di una piramide senza base.

Una **combinazione convessa** è allo stesso tempo una _combinazione affine_ ed una _combinazione conica_:
$$z=a_1z_1+...+a_mz_m\quad\text{con}\quad \sum_{i=1}^ma_i=1\quad\land \quad a_i\geq 0,\space i=1,...,m$$
geometricamente appare come un segmento delimitato da due punti specifici dei vettori:
![[Combinazione convessa.svg]]
in tre dimensioni è un taglio (base) di una piramide.
In questo caso la combinazione convessa $z$ dei vettori $z_1$ e $z_2$ si ottiene tramite la relazione: $z=a_1z_1+a_2z_2$, dove $a_1+a_2=1$ e $a_1,a_2\geq 0$.
