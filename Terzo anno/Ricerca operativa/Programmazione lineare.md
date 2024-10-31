In questa sezione mostriamo le potenzialità dei [[Problemi convessi|problemi convessi]].

### Direzione ammissibile
Dato l'insieme $C\subseteq \mathbb{R}^n$ ed il punto $\overline{x}\in C$, il vettore direzione $d=y-\overline{x}$ con $y\in\mathbb{R}^n$ e $y\neq\overline{x}$ è una **direzione ammissibile** per $C$ in $\overline{x}$ se:
$$x=\overline{x}+\alpha d\in C\quad\forall\alpha\in]0,\overline{\alpha}]\space\text{ con }\overline{\alpha}>0$$
È possibile vedere $\alpha$ come un passo lungo la direzione $d$, la direzione è ammissibile se esiste un $\overline{\alpha}$ per cui ogni punto tra $0$ (non compreso) e $\overline{\alpha}$ è presente all'interno di $C$.
![[Direzioni ammissibili.svg|450]]

La direzione $\hat{\hat d}$ è ammessa in quanto si può considerare un $\overline{\alpha}$ che considera solo il primo segmento (senza attraversare il buco).
L'unica direzione non ammessa è $\stackrel{\sim}{d}$, infatti essendo sulla frontiera non esiste alcun $\overline{\alpha}>0$ per cui essa sia ammessa.

### Direzione di discesa
Data la funzione $f(x)$ con $f:\mathbb{R}^n\to\mathbb{R}$ ed il vettore $d\in\mathbb{R}^n$, con $d\neq 0$.
Considerato il punto $\overline{x}\in\mathbb{R}^n$, si dice che $d$ è una **direzione di discesa** per $f(x)$ in $\overline{x}$ se esiste una $\alpha>0$ tale che:
$$f(\overline{x}+\alpha d)<f(\overline{x})\quad\forall\alpha\in]0,\overline{\alpha}]$$


>[!Tip] Interpretazione del significato di direzione
>Considerando il caso di $f:\mathbb{R}\to\mathbb{R}$, la direzione, non è un vettore, bensì un numero (scalare), esso è dato dalla differenza di altri due numeri.

Se la funzione appartiene alla classe $C^1(\mathbb{R}^n)$, allora si può constatare subito se una direzione $d$ è di discesa, in particolare se $0<||d||<\infty$ e $\nabla f(\overline{x})^Td\neq 0$, allora $d$ è di discesa sse:
$$\nabla f(x)^Td<0$$

