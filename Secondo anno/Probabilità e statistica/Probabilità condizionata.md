La probabilità di un evento è un rapporto tra l'evento stesso e $\Omega$, con $\mathbb{P}(A|B)$ ovvero la probabilità di $A$ dato per vero/non incerto/accaduto $B$ ora considero solo l'evento $B$ come mio "spazio campionario", quindi:
$$\boxed{\mathbb{P}[A|B]=\frac{\mathbb{P}[A\cap B]}{\mathbb{P}[B]}}$$
Le regole di unione e intersezione valgono allo stesso modo, quindi ad esempio potrei ritrovare:
$$\mathbb{P}[\overline{A}|B]=\frac{\mathbb{P}[\overline{A}\cap B]}{\mathbb{P}(B)}=\frac{\mathbb{P}[B]-\mathbb{P}[A\cap B]}{\mathbb{P}}=1-\mathbb{P}[A|B]$$
Da notare che se abbiamo già dati a disposizione possiamo sempre trovare **formule inverse**:
$$\mathbb{P}[A\cap B]=\mathbb{P}[A|B]\mathbb{P}[B]$$
>[!Example]
>Un urna contiene quattro palle bianche numerate da 1 a 4 e tre palle nere numerate da 1 a 3, dalla quale si estrae casualmente una palla con eventi:
>- $B$ = viene estratta una palla bianca
>- $N$ = viene estratta una palla nera
>- $C_i$ = viene estratto il numero $1 \leq i \leq 4$
>$$\mathbb[C_1|B]=\frac{\mathbb{P}[C_1\cap B]}{\mathbb{P}[B]}=\frac{1/7}{4/7}=\frac{1}{4}$$
>$$\mathbb[C_1|N]=\frac{\mathbb{P}[C_1\cap N]}{\mathbb{P}[N]}=\frac{1/7}{3/7}=\frac{1}{3}$$
>$$\mathbb[N|C_1]=\frac{\mathbb{P}[N\cap C_1]}{\mathbb{P}[C_1]}=\frac{1/7}{2/7}=\frac{1}{2}$$
>
>Da considerare anche che: $\mathbb{P}[N|C_1]=1-\mathbb{P}[B|C_1]=\frac{1}{2}$ dato che $N=\overline{B}$.
