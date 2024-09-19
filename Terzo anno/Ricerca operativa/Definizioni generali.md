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

