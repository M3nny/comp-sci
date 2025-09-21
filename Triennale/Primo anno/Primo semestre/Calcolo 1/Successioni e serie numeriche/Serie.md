Data una successione $(a_n)_{n\in\mathbb{N}}$ chiamiamo **somme parziali** la successione $(s_n)_{n\in\mathbb{N}}$ , data da:
$$\sum^{+\infty}_{n=0}a_n=\lim_{n\to +\infty}s_n \quad \text{è definita come serie}$$
### Carattere della serie
In base al risultato della sommatoria precedente possiamo determinare il _carattere della serie_:
- **convergente**: se $\sum_n a_n = \ell$;
- **divergente**: se $\sum_n a_n = \pm \infty$;
- **indeterminata**: se il limite non esiste.

### Serie geometrica
Sia $a\neq 1$ e $a_n = a^n$, allora le somme parziali sono definite da:
$$s_n=\frac{1-a^n}{1-a}$$
Se ne deduce che:
- Se $|a|<1$ allora la serie è uguale a $\frac{1}{1-a}$;
- Se $a\geq 1$ allora la serie **diverge**;
- Se $a\leq -1$ la serie è **indeterminata**.

### Serie a termini di segno costante
È una serie dove tutti i suoi termini sono **o positivi o negativi**.
Essendo monotona, crescente/decrescente che sia, il suo limite esiste sempre,  quindi **non potrà mai essere indeterminata**.

>[!Teorema]
>Se una serie converge, allora il suo termine generale $a_n$ è _infinitesimo_, cioè $\lim a_n = 0$.

>[!Teorema (criterio del confronto)]
>Siano $(a_n);(b_n)$ successioni tali che $a_n \leq b_n$:
>- Se $\sum_n b_n$ converge, allora $\sum_n a_n$ è convergente;
>- Se $\sum_n a_n$ diverge, allora $\sum_n b_n$ è divergente.

### Nozioni sull'algebra delle serie
- Se due serie **convergono**, $\sum_n a_n = l$ e $\sum_n b_n = m$ allora **le loro combinazioni lineari** (somma) **sono convergenti**:
$$\sum_n(\lambda a_n + \micro b_n) = \lambda l+\micro m \quad \forall \lambda ,\micro \in \mathbb{R}$$
- Se due serie **divergono**, $\sum_n a_n = \pm \infty$ e $\sum_n b_n = \pm \infty$ allora la loro somma **diverge**:
$$\sum_n a_n +b_n = \pm \infty$$

### Serie armonica
La serie armonica (chiede spesso) è definita come:
$$\sum^{+\infty}_{n=1} \frac{1}{n}$$
e questa serie **diverge**.
Vediamo quella generalizzata:
$$\sum^{+\infty}_{n=1} \frac{1}{n^\alpha}$$
- **converge** se $\alpha > 1$;
- **diverge** se $0<\alpha\leq 1$.

>[!Teorema (criterio del rapporto)]
>Sia $\sum_n a_n$ una serie a **termini positivi** e sia:
>$$\lim_{n\to +\infty} \frac{a_{n+1}}{a_n} = l$$
>Allora:
>- Se $l<1$ **converge**;
>- Se $l>1$ **diverge**;
>- Se $l=1$ non si può determinare il suo carattere con questo criterio.

>[!Teorema (criterio della radice)]
>Sia $\sum_n a_n$ una serie a **termini positivi** e sia:
>$$\lim_{n\to +\infty}\sqrt[n]{a_n}=l$$
>Allora:
>- Se $l<1$ **converge**;
>- Se $l>1$ **diverge**;
>- Se $l=1$ non si può determinare il suo carattere con questo criterio.

### Serie assolutamente convergente
Sia data la serie $\sum_n a_n$, se la serie di tutti i suoi elementi con il valore assoluto:
$$\sum_n |a_n|$$
è convergente, allora la serie $\sum_n a_n$ si dice **assolutamente convergente**.

>[!Teorema (criterio di Leibniz)]
>Sia $\sum_n a_n$ **una serie a termini di segno alterno**, se
>$$\lim_{n\to +\infty} a_n = 0 \quad\land\quad |a_n+1| < |a_n|$$
>Allora la serie **converge**.

