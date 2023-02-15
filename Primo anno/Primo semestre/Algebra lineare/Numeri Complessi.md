# I numeri complessi
I numeri complessi ci vengono in aiuto dato che i numeri reali negativi hanno delle limitazioni come $\sqrt{-1}$ .
- $a,b$ sono numeri reali arbitrari
- $a+bi$ ha una parte immaginaria, ovvero $i$
$$i=\sqrt{-1}$$$$i^2=-1$$
Possiamo rappresentare numeri immaginari del tipo $z=a+bi$ in un **piano complesso**
ad esempio $3+2i$ dove avrà coordinate $(3,2)$.

### Somma
$$(a+bi) + (c+di) = a+c+i(b+d)$$
### Prodotto
$$(a+bi)\cdot(c+di)=$$
$$= ac+adi+bci+bidi =$$
$$= ac+adi+bci-bd =$$
$$= ac-bd+i(ad+bc)$$
### Coniugato:
$$\overline{z} = a -bi$$
### Modulo:
$$|z| = \sqrt{a^2+b^2}$$
### Inverso: 
$$z^{-1} = \frac{\overline z}{|z|^2} = \frac{a - bi}{a^2+b^2}$$
### Divisione
$$\frac{z}{w}=\frac{1}{|w|^2}\cdot z\overline{w}$$

## Il piano complesso
Un numero complesso $z = a+bi$ è <u>rappresentabile graficamente</u> tramite il **piano complesso** (o di Gauss), dove nelle **ascisse** troveremo la sua **parte reale**: $Re(z) = a$ mentre nelle **ordinate** la sua **parte immaginaria**: $Im(z)=b$.
![[Piano complesso.svg]]
Possiamo quindi identificare:
- $|z|$ che è equivalente alla diagonale che parte dall'origine e arriva a $z$
- È possibile ricavare il numero complesso utilizzando come raggio $r$ la diagonale
- Per cui $a=r\cdot cos(\alpha)$ e $b=r\cdot sin(\alpha)i$ 

Otteniamo così le **coordinate polari**:
$$z = a+bi =$$
$$= r\cdot cos(\alpha) + r\cdot sin(\alpha)i =$$
$$|z|(cos(\alpha)+isin(\alpha))$$
### Moltiplicazione con coordinate polari
Sia $z=|z|(cos(\alpha)+isin(\alpha))$ e $w=|w|(cos(\beta)+isin(\beta))$, allora
$$z\cdot w=|z\cdot w|(cos(\alpha +\beta)+isin(\alpha +\beta))$$

>[!Example]
>**Trovare le coordinate polari d**i $z=2-3i$
>
>1. Trovare $r=|z|$
>$$|z|=\sqrt{a^2+b^2}=\sqrt{4+9}=\sqrt{13}$$
>Sapendo che $z=|z|\cdot \frac{z}{|z|}$ possiamo riscrivere z in un modo diverso così da trovare anche seno e coseno.
>$$z=\sqrt{13}\cdot (\frac{2-3i}{\sqrt{13}})=$$
>$$=\sqrt{13}(\frac{2}{\sqrt{13}}-\frac{3i}{\sqrt{13}})$$
>Dove:
>- Il **coseno** sarà la parte **reale**, quindi $cos(\alpha)=\frac{2}{\sqrt{13}}$
>- Il **seno** sarà la parte **immaginaria**, quindi $sin(\alpha)=-\frac{3}{\sqrt{13}}$

## Forma esponenziale
>[!Teorema]
>**Prima formula di Eulero**
$e^{i\alpha}=cos(\alpha)+isin(\alpha)$

Grazie a questa formula possiamo scrivere $z$ in un modo più corto, ovvero:
$$z=|z|\cdot e^{i\alpha}$$
e dato che $|z| = r$ possiamo anche scriverlo così:
$$z=r\cdot e^{i\alpha}$$
In questa forma sarà molto più semplice eseguire le moltiplicazioni:
- $z=r_1\cdot e^{i\alpha}$
- $w=r_2\cdot e^{i\beta}$
- $z\cdot w=(r_1\cdot r_2)e^{i(\alpha + \beta)}$

## Recap forme
**Forma standard** (o cartesiana): $z=a+bi$
**Forma polare** (o trigonometrica): $z=r(cos(\alpha)+isin(\alpha))$
	$r=|z|=\sqrt{a^2+b^2}$
	$a=r\cdot cos(\alpha)$
	$b=r\cdot sin(\alpha)$	
**Forma esponenziale**: $z=r\cdot e^{i\alpha}$























