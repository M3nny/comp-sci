In questa sezione mostriamo le potenzialità dei [[Problemi convessi|problemi convessi]].

### Direzione ammissibile
Dato l'insieme $C\subseteq \mathbb{R}^n$ ed il punto $\overline{x}\in C$, il vettore direzione $d=y-\overline{x}$ con $y\in\mathbb{R}^n$ e $y\neq\overline{x}$ è una **direzione ammissibile** per $C$ in $\overline{x}$ se:
$$x=\overline{x}+\alpha d\in C\quad\forall\alpha\in]0,\overline{\alpha}]\space\text{ con }\overline{\alpha}>0$$
È possibile vedere $\alpha$ come un passo lungo la direzione $d$, la direzione è ammissibile se esiste un $\overline{\alpha}$ per cui ogni punto tra $0$ (non compreso) e $\overline{\alpha}$ è presente all'interno di $C$.
![[Direzioni ammissibili.svg|450]]

La direzione $\hat{\hat d}$ è ammessa in quanto si può considerare un $\overline{\alpha}$ che considera solo il primo segmento (senza attraversare il buco).
L'unica direzione non ammessa è $\stackrel{\sim}{d}$, infatti essendo sulla frontiera non esiste alcun $\overline{\alpha}>0$ per cui essa sia ammessa in quel verso.

### Direzione di discesa
Data la funzione $f(x)$ con $f:\mathbb{R}^n\to\mathbb{R}$ ed il vettore $d\in\mathbb{R}^n$, con $d\neq 0$.
Considerato il punto $\overline{x}\in\mathbb{R}^n$, si dice che $d$ è una **direzione di discesa** per $f(x)$ in $\overline{x}$ se esiste un $\alpha>0$ tale che:
$$f(\overline{x}+\alpha d)<f(\overline{x})\quad\forall\alpha\in]0,\overline{\alpha}]$$


>[!Tip] Interpretazione del significato di direzione
>Considerando il caso di $f:\mathbb{R}\to\mathbb{R}$, la direzione, non è un vettore, bensì un numero (scalare), esso è dato dalla differenza di due numeri.

Se $f\in C^1(\mathbb{R}^n)$, allora si può constatare subito se una direzione $d$ è di **discesa**, in particolare se $0<||d||<\infty$ ($d$ è limitata e non nulla) e $\nabla f(\overline{x})^Td\neq 0$ (i vettori non sono ortogonali), allora $d$ è di discesa per $f(x)$ in $\overline{x}$ sse:
$$\nabla f(\overline{x})^Td<0$$

La formulazione sta dicendo che se la derivata direzionale lungo $d$ è minore di $0$, allora la direzione è di discesa.

>L'anti-gradiente, nonchè la migliore soluzione di discesa rappresenta una direzione di discesa sicura, essa è espressa come: $d=-\frac{\nabla f(\overline{x})}{||\nabla f(\overline{x})||_2}$.
>Discorso analogo per la migliore soluzione di crescita, solamente cambiando il segno con $+$.

**Dimostrazione**
Dal [[Definizioni generali#Teorema del valor medio|teorema del valor medio]] per $\alpha\in]0,1]$ (maggiore di $0$ altrimenti si rimarrebbe sul punto $\overline{x}$) si ottiene:
$$\begin{align}
f(\overline{x}+\alpha d)&=f(\overline{x})+\nabla f(\overline{x})^T(\alpha d)+o(||\alpha d||)\\
&= f(\overline{x})+\alpha\nabla f(\overline{x})^Td+o(||\alpha d||)\frac{||d||}{||d||}\\
\frac{f(\overline{x}+\alpha d)-f(\overline{x})}{\alpha}&=\nabla f(\overline{x})^Td+\frac{o(||\alpha d||)}{\alpha ||d||}||d||
\end{align}$$

Dato che esiste almeno un limite nella somma del membro di destra, li posso calcolare separatamente, quindi applico il limite per $\alpha\to0^+$ in ambo i membri (con quello di destra diviso) ed ignoro il limite per $\nabla f(\overline{x})^Td$ in quanto non dipende da $\alpha$:
$$\begin{align}
\lim_{\alpha\to0^+}\frac{f(\overline{x}+\alpha d) -f(\overline{x})}{\alpha}&=\nabla f(\overline{x})^T d+\lim_{\alpha\to0^+}\frac{o(||\alpha d||)}{\alpha||d||}||d||\\
&=\nabla f(\overline{x})^Td
\end{align}$$

Con questo abbiamo dimostrato che la derivata direzionale lungo $d$ nel punto $\overline{x}$ è data dalla formulazione precedente.
Dobbiamo ancora dimostrare che $d$ è una direzione di discesa per $f$ sse $\nabla f(\overline{x})^Td<0$.

($\Rightarrow$)
Sia per ipotesi $d$ una direzione di discesa, allora la differenza $f(\overline{x}+\alpha d) -f(\overline{x})$ sarà negativa, essendo $\alpha$ positivo il rapporto sarà negativo, quindi secondo la catena di uguaglianze anche $\nabla f(\overline{x})^Td$ sarà minore di $0$.

($\Leftarrow$)
Sia per ipotesi $\nabla f(\overline{x})^Td<0$, ciò implica che il membro di destra è negativo, e per la catena di uguaglianze anche il membro di sinistra lo sarà.

Perchè il rapporto sia negativo dovrà valere che la differenza $f(\overline{x}+\alpha d) -f(\overline{x})$ sia negativa in quanto $\alpha$ è sempre positivo a causa del limite, tale differenza rappresenta la definizione di direzione di discesa, dimostrando così che $d$ è effettivamente di discesa.

---
### Condizione necessaria per minimo locale
Si consideri il problema $\min\limits_{x\in C}f(x)$, l'insieme $C$ convesso e la funzione  $f:\mathbb{R}^n\to\mathbb{R}$ con $f\in C^1(\mathbb{R}^n$).
$$x^*\text{ è un  minimo locale}\implies\nabla f(x^*)^T(x-x^*)\geq 0\quad\forall x\in C$$

**Dimostrazione**
Se $x^*$ è un minimo locale, allora non deve esistere alcuna direzione ammissibile di discesa in $x^*$, possono quindi solo esistere direzioni ammissibili per cui
$$\nabla f(x^*)^Td\geq 0\quad\forall d\text{ ammissibile per }C$$

Dato che $C$ è convesso, preso un qualsiasi punto $x\in C$ con $x\neq x^*$, la direzione $d=x-x^*$ sarà ammissibile, dovrà valere quindi $\nabla f(x^*)^T(x-x^*)\geq 0$.

#### Condizione necessaria e sufficiente per minimo locale
Dato il medesimo problema precedente con le stesse ipotesi, specifichiamo ora che $f(x)$ sia **convessa** su $C$.
$$x^*\text{ è un  minimo locale}\iff\nabla f(x^*)^T(x-x^*)\geq 0\quad\forall x\in C$$

**Dimostrazione**
Il primo verso ($\Rightarrow$) è già stato verificato dalla _condizione necessaria_.
Dimostriamo quindi il lato opposto ($\Leftarrow$) assumendo che $\nabla f(x^*)^T(x-x^*)\geq 0$.

Sappiamo che una funzione è convessa se rispetta la [[Problemi convessi#Differenziabilità e funzioni convesse|seguente disuguaglianza]]:
$$f(y)\geq f(x^*)+\underbrace{\nabla f(x^*)^T(x-x^*)}_{\geq 0\text{ per ipotesi}}\quad\forall x,y\in C$$
$$f(y)\geq f(x^*)$$

Dimostrando così che $x^*$ è un minimo locale, e anche globale dato che stiamo considerando una funzione convessa.
