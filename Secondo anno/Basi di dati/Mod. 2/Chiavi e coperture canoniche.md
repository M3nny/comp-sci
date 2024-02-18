Dato uno schema di relazione $R(T,F)$, un insieme di attributi $X\subseteq T$:
- **Superchiave** (di $R$): sse $(X\rightarrow T)\in F^+$  
- **Chiave**: superchiave minimale, ovvero all'interno non contiene sottoinsiemi (più piccoli) che possono essere superchiave
- **Attributo primo**: sse appartiene ad almeno una chiave

### Verifica superchiave
Dato $R(T,F)$, per verificare se $X\subseteq T$ è una _superchiave_ è possibile:
1. Calcolare la chiusura $X_F^+$
	Si parte dalla superchiave data e si aggiungono (Augm) ad essa gli attributi presenti in $F$ che dipendono da un sottoinsieme di attributi della superchiave.
2. Verificare se $X_F^+=T$ 

>[!Example]
>Si consideri lo schema di relazione $R(T,G)$ con $T=ABCDEF$ e $G=\{AB\rightarrow C, E\rightarrow A, A\rightarrow E, B\rightarrow F\}$.
>Verificare se $ABD$ è superchiave.
>1. $ABD_0^+ = ABD$
>2. $ABD_1^+ = ABCD$ (tramite $AB\rightarrow C$)
>3. $ABD_2^+ = ABCDE$ (tramite $A\rightarrow E$)
>4. $ABD_3^+ = ABCDEF$ (tramite $B\rightarrow F$)
>$$ABD_3^+ = T\quad\text{(ABD è superchiave)}$$

### Verifica chiave
Dato $R(T,F)$, per verificare se $X\subseteq T$ è una _chiave_ è possibile:
1. Verificare se $X$ è superchiave
2. Verificare che per ogni attributo di $X$ sia vero che: togliendolo e trovando la chiusura dell'insieme di attributi rimanenti si ha che la chiusura trovata è diversa dall'insieme di attributi $T$, questo vuol dire che l'attributo tolto è indispensabile e deve far parte della chiave minima (chiave)

>[!Example]
>Continuando l'esempio precedente, si vuole vedere se $ABD$ è anche chiave.
>1. $A$ non può essere rimosso, perchè senza: $BD_G^+=BDF$
>	- (tramite $B\rightarrow F$)
>2. $B$ non può essere rimosso, perchè senza: $AD_G^+=ADE$
>	- (tramite $A\rightarrow E$)
>3. $D$ non può essere rimosso, perchè senza: $AB_G^+=ABCEF$
>	- $ABC$ (tramite $AB\rightarrow C$)
>	- $ABCE$ (tramite $A\rightarrow E$)
>	- $ABCEF$ (tramite $B\rightarrow F$)

### Trovare una chiave
1. Si inizializza $K_0$ come la chiave che contiene tutti gli attributi (superchiave banale)
2. Si rimuove un attributo alla volta e si verifica che la chiusura dell'insieme di attributi sia:
	- Uguale a $K_i$: si rimuove l'attributo dall'insieme e si forma $K_{i+1}$
	- Diverso da $K_i$: si mantiene l'attributo
3. Ripetere il punto 2. con l'eventuale nuovo insieme finchè non si è provato a togliere ciascun attributo

>[!Example]
>Sia $G=\{AB\rightarrow C, E\rightarrow A, A\rightarrow E, B\rightarrow F\}$.
>1. $K_0=ABCDEF$
>2. Rimuoviamo $A$ da $K_0$: $BCDEF_G^+=ABCDEF$, $A$ non è indispensabile, va rimosso, $K_1=BCDEF$
>3. Rimuoviamo $B$ da $K_1$: $CDEF_G^+=ACDEF$, $B$ è essenziale, va tenuto
>4. Rimuoviamo $C$ da $K_1$: $BDEF_G^+=ABCDEF$, $C$ non è indispensabile, va rimosso, $K_2=BDEF$
>5. Rimuoviamo $D$ da $K_2$: $BEF_G^+=ABCEF$, $D$ è essenziale, va tenuto
>6. Rimuoviamo $E$ da $K_2$: $BDF_G^+=BDF$, $E$ è essenziale, va tenuto
>7. Rimuoviamo $F$ da $K_2$: $BDE_G^+=ABCDEF$, $F$ non è indispensabile, va rimosso, $K_3=BDE$
>
>Abbiamo trovato la chiave $BDE$.

Ogni sottoinsieme di $T$ però potrebbe essere una chiave.

### Trovare tutte le chiavi
1. Inizialmente viene scelto l'insieme di attributi $X$ che non dipendono da altri, ovvero non sono presenti alla destra di ($X_1\rightarrow X_2$), e l'insieme di attributi $Y$ (attributi restanti) da confrontare con $X$. Questi saranno i candidati, scritti come $X::(Y)$
2. Si calcola la chiusura di $X$:
	- Se è uguale $T$, allora $X$ è chiave:
		1. Si toglie dai candidati
	- Se è diversa da $T$, allora $X$ non è chiave:
		1. Si toglie dai candidati
		2. Si sottrae da $Y$ la chiusura di $X$ 
		3. Si aggiungono ai candidati: $[X\cup(Y\setminus X^+)_0::((Y\setminus X^+)_1,...,(Y\setminus X^+)_n)],...,[X\cup(Y\setminus X^+)_n::()]$
3. L'algoritmo termina quando non ci sono più candidati

>Partiamo dall'insieme di attributi che non dipende da nessun'altro, perchè esso farà parte di tutte le chiavi.

>[!Example]
>Sia $G=\{AB\rightarrow C, E\rightarrow A, A\rightarrow E, B\rightarrow F\}$.
>- 1
>	$X=BD$
>	$Y=ACEF$
>	$X_G^+=BDF\neq T$, $X$ non è una chiave
>	$Y\setminus X_G^+=ACE$
>	$\text{Cand}=[BDA::(CE),BDC::(E),BDE::()]$
>	$\text{Keys}=[]$
>- 2
>	$X=BDA$
>	$Y=CE$
>	$X_G^+=BDACEF=T$, $X$ è una chiave
>	$\text{Cand}=[BDC::(E),BDE::()]$
>	$\text{Keys}=[BDA]$
>- 3
>	$X=BDC$
>	$Y=E$
>	$X_G^+=BDCF\neq T$, $X$ non è una chiave
>	$Y\setminus X_G^+=E$
>	$\text{Cand}=[BDE::(),BDCE::()]$
>	$\text{Keys}=[BDA]$
>- 4
>	$X=BDE$
>	$Y=\emptyset$
>	$X_G^+BDEACF=T$, $X$ è una chiave
>	$\text{Cand}=[BDCE::()]$
>	$\text{Keys}=[BDA,BDE]$
>- 5
>	$X=BDCE$
>	$Y=\emptyset$
>	$X$ contiene la chiave $BDE$, per cui non può essere una chiave minimale, viene quindi scartato
>	$\text{Cand}=[]$
>	$\text{Keys}=[BDA,BDE]$
>
>Le chiavi sono: $BDA$ e $BDE$.


















