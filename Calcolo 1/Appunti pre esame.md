### Appunti generali
- Una **funzione è continua** se non è definita a tratti, inoltre possiamo dire che è continua se è un composizione di funzione continue (somma, prodotto...)
- Quando valuto la continuità,**i buchi nel dominio non significano che la funzione non è continua**
- Una **funzione è derivabile** se è composta da funzioni derivabili, inoltre se è presente un valore assoluto dentro al funzione è meglio vedere per che valore si azzera e non valutare la derivabilità in quel punto, in quanto potrebbe essere non derivabile (cuspide)
- **Generare il sistema del valore assoluto**, non bisogna mettere semplicemente $\geq 0$ e $<0$, ma devo calcolare il valore per cui il val. ass. si annulla e combinarlo al dominio 
	- Se il dominio è $]0,2[$, ed il val. ass. si annulla per $1$, avrò $\begin{cases}x\in [1,2[\\x\in ]0,1[\end{cases}$ 
- Avendo un val. ass. del genere: $|1-e|$, il valore assoluto sarà: $e-1$ perchè $e > 1$, altrimenti si avrebbe in valore negativo
- **Tenere conto del range del dominio** quando si studia il segno
- **Quando si va a trovare una derivata di un valore assoluto** (di solito la seconda, quando si ha già la funzione divisa in 2 parti a causa del val. ass) non è detto che bisogna farla per entrambe le funzioni nel sistema, se il grado massimo dentro al valore assoluto è 1, allora la derivata seconda farà sparire la $x$ risultando in una derivata uguale per entrambe le funzioni
- **Una funzione senza simmetrie non può essere periodica**
- Una funzione non è invertibile se esiste un punto di massimo o di minimo all'interno della funzione
- Per ogni nuova variabile, specificare a che insieme appartiene
- Quando valuto una funzione con il valore assoluto, le condizioni da mettere a sistema sono: la prima dove non altero il segno dentro al valore assoluto e metto la condizione per cui x > 0 (anche in parte se questo dovesse essere un intervallo limitato) e nella seconda altero il segno all'interno del valore assoluto e poi come condizione metto che x < 0 (anche in parte come prima)

---
### Verificare il limite con la definizione
**Diseguaglianze che devo risolvere** per i vari casi:
1. Per $f(x)\to\ell$ uso $|f(x)-\ell|<\epsilon$
2. Per $f(x)\to +\infty$ uso $f(x)>M$
3. Per $f(x)\to - \infty$ uso $f(x)<-M$
**Il risultato dovrà essere del tipo:** (in base a dove tende la $x$)
1. Per $x\to x_0$ il risultato dovrà appartenere ad un intorno di $x_0$ ($x\in I(x_0)$), ovvero $x_0-\delta < x < x_0 +\delta$ 
2. Per $x\to +\infty$ il risultato dovrà essere $x>M$
3. Per $x\to -\infty$ il risultato dovrà essere $x<-M$ 

---
### Asintoti
Per trovare gli **asintoti verticali** devo vedere il limite dove possibile, attorno ai punti esclusi dal dominio, per quelli **orizzontali** devo fare il limite per $x$ che tende a $\pm \infty$, inoltre poi devo trovare quelli **obliqui**, che saranno rappresentati da una retta:
1.  $m: \lim\limits_{x\to\pm\infty}\frac{f(x)}{x}$, se il limite esiste ed è finito, posso passare a trovare $q$
2. $q: \lim\limits_{x\to\pm\infty} f(x)-mx$ se sono riuscito a trovare $q$, posso trovare la retta
3. $y=mx+q$

---
### Periodo di una funzione
Si può trovare solo se la funzione è pari o dispari, inoltre una funzione è periodica se il periodo ottenuto è razionale (quindi non valori come $\pi$, $e$)
| **Funzione** | **Periodo** |
| ------------ | ----------- |
| $\sin(x)$    | $2\pi$      |
| $\cos(x)$    | $2\pi$      |
| $\tan(x)$    | $\pi$       |
| $\cot(x)$    | $\pi$            |

1. **moltiplicazione**: Se la $x$ all'interno della funzione viene moltiplicata/divisa, divido il periodo per quel valore.
2. **valore assoluto**: $|f(x)|$, il periodo di $\sin(x)$ e $\cos(x)$ viene dimezzato, quello di $\tan(x)$ e $\cot(x)$ rimane invariato.
3. **potenze**: se l'esponente è pari per $\sin(x)$ e $\cos(x)$, il periodo viene dimezzato, negli altri casi il periodo è invariato
4. **radici**: non cambiano il periodo

1. **somma/differenza di funzioni**: il periodo è il mcm tra i periodi delle singole funzioni, se i periodi sono frazionari, li esprimo in modo che abbiano lo stesso denominatore, poi il periodo sarà dato dal mcm del numeratore fratto il denominatore comune.
2. **prodotto/rapporto di funzioni**: 
	- Argomento uguale, periodo uguale: il periodo risultante è il periodo uguale per tutte le funzioni diviso 2
	- Argomento diverso o periodo diverso o entrambi, si procede come somma/differenza
3. **funzioni esponenziali**: ho notato che si trova sempre con la regola del mcm, ma è da ignorare il fatto di dimezzare se hanno stesso argomento/periodo.

---
### Teorema degli zeri
Per verificare quanti zeri ha una funzione senza eseguire ulteriori calcoli, bisogna, dopo aver studiato il segno di $f'(x)$, trovare le ordinate delle $x$ che abbiamo trovato, se una è l'opposto dell'altra e precedentemente abbiamo visto che la funzione è continua, allora esiste per forza **almeno uno** zero. 

---
### Vedere se una funzione è di classe $C^1$ 
1. Vedere se il limite verso il punto non compreso nella funzione è uguale  all'altra funzione del sistema, dove invece il punto è compreso
2. Guardare se è derivabile in quel punto tramite il rapporto incrementale
3. Vedere se la derivata è continua

---
### Formule
- $\sin(-x) = -\sin(x)$
- $\cos(-x) = \cos(x)$
- $\sec(x) = \frac{1}{\cos(x)} \quad cosec(x) = \frac{1}{\sin(x)}$
- **Rapporto incrementale**: $\lim\limits_{x\to x_0}\frac{f(x)-f(x_0)}{x-x_0}$
-  **Retta tangente per un punto** $y=f'(x_0)\cdot(x-x_0)+f(x_0)$
- **Taylor**: $\frac{f^{(n)}(x_0)}{n!}(x-x_0)^n$ 

>Discutere successivamente la derivata del valore assoluto

>TENERE CONTO DEL DOMINIO E DELL'INTERVALLO DELLA FUNZIONE