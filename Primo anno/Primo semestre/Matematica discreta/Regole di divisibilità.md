Qualsiasi numero $a$ può essere espresso tramite:
$$a=c_0+\sum_{i=1}^nc_i\cdot 10^i$$
Dove $c_0$ è l'ultima cifra a destra del numero.
$b$ è un divisore esatto di $a$ $\land$ $a$ è un multiplo di $b$ $\iff$ $a \equiv_b 0$.

Dalla formula precedente abbiamo che $b$ è un divisore esatto di $a$ **se e solo se**:
$$c_0+\sum_{i=1}^nc_i\cdot 10^i\equiv_b0$$
Criteri di divisibilità per:
- **2**: l'ultima cifra è pari;
- **3**: la somma delle cifre di $a$ ritorna un multiplo di 3;
- **4**: l'ultima cifra sommata al doppio della penultima ritorna un multiplo di 4:
	$c_0+2c_1$ è multiplo di 4;
- **5**: l'ultima cifra è 5 oppure 0;
- **6**: la somma delle cifre che compongono $a$ ritorna un multiplo sia di 2 sia di 3, inoltre l'ultima cifra di $a$ deve essere pari;
- **8**: l'ultima cifra sommata al doppio della penultima sommata al quadruplo della terzultima ritorna un multiplo di 8:
	$c_0+2c_1+4c_2$ è multiplo di 8;
- **9**: la somma della cifre di $a$ ritorna un multiplo di 9;
- **10**: l'ultima cifra è 0.

>[!Teorema divisibilità]
>Siano $a,b,c,r \in \mathbb{Z}$
>$$a=b\cdot q +r$$
>Se $c|a$ e $c|b$ allora $c|r$

