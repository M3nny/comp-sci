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

- **Se tutti gli attributi compaiono a destra**, allora si deve usare un approccio "brute-force" partendo dagli attributi singoli e vedendo se essi sono chiave, poi verificare con insiemi di 2 attributi, etc.. verificando sempre che le chiavi già trovate _non_ siano dentro ad altre chiavi (questo perchè altrimenti non sarebbero minime e devono essere scartate)

>[!Tip] Attributi che non compaiono
>- L'attributo **non compare a destra**: fa parte di tutte le chiavi
>- L'attributo **non compare a sinistra**: non fa parte di nessuna chiave


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

### Forma canonica
La forma canonica rappresenta una forma più "disciplinata", equivalente all'originale delle dipendenze funzionali originali.
Di seguito sono riportati termini nuovi per comprendere cos'è una _forma canonica_.

**Equivalenza**: due insiemi di dipendenze funzionali $F$ e $G$ sono _equivalenti_ se:
$$F\equiv G\iff F^+=G^+$$
inoltre: $F=G\implies F\equiv G$.

**Attributo estraneo**: sia $(X\rightarrow Y)\in F$, l'attributo $A\in X$ è _estraneo_ sse $X\setminus\{A\}\rightarrow Y\in F^+$.

**Dipendenza ridondante**: $(X\rightarrow Y)\in F$ è _ridondante_ sse $(X\rightarrow Y)\in(F\setminus\{X\rightarrow Y\})^+$.

**Forma canonica**: $F$ è in _forma canonica_ sse per ogni $(X\rightarrow Y)\in F$:
- $|Y|=1$, ovvero la cardinalità dell'insieme $Y$ è pari a $1$
- $X$ non contiene attributi estranei
- $X\rightarrow Y$ non è ridondante
	questa operazione è da fare con gli attributi rimanenti dal passaggio precedente, quindi la chiusura non dovrà comprendere anche gli attributi che sono spariti del tutto.

$G$ è una copertura canonica di $F$ sse $F\equiv G$ e $G$ è in forma canonica.
I passaggi per trovarne una sono i seguenti:
1. Suddivido gli insiemi con cardinalità > 1 che dipendono da altri attributi
2. Elimino gli attributi estranei (presenti solo in insiemi con cardinalità > 1 a sx della freccia), ovvero quelli che se rimossi consentono comunque a $X$ di possedere $Y$ nella propria chiusura $X_F^+$ (uno vale l'altro, questo porterà a differenti coperture, ma non è detto che ce ne debba essere solo una)
	Questo passaggio è da ripetere se dopo l'eliminazione di un estraneo rimangono $|X|>1$ elementi.
3. Trovo le chiusure dell'elemento a sx per ogni dipendenza funzionale, togliendo a $F$ la dipendenza funzionale stessa, se come risultato danno l'insieme di tutti gli elementi in $T$, allora quella dipendenza può essere rimossa

>Per ogni insieme di dipendenze $F$ esiste una copertura canonica.
>Può esistere più di una copertura canonica per insieme di dipendenze.

>[!Example]
>Trovare una copertura canonica per:
>$G=\{A\rightarrow BC, B\rightarrow C, A\rightarrow B, AB\rightarrow C\}$.
>1. $G=\{A\rightarrow B, A\rightarrow C, B\rightarrow C, A\rightarrow B, AB\rightarrow C\}$
>	- L'unica dipendenza che può contenere attributi estranei è $AB\rightarrow C$, $A$ è estraneo perchè non compare in $B_G^+=BC$, per cui va eliminato e si ottiene $B\rightarrow C$
>	- Elimino i doppioni
>2. $G=\{A\rightarrow B,A\rightarrow C, B\rightarrow C, \cancel{A\rightarrow B}, \cancel{B\rightarrow C}\}$
>	- $A_{G\setminus\{A\rightarrow B\}}^+=AC$
>	- $A_{G\setminus\{A\rightarrow C\}}^+=ABC$ elimino $A\rightarrow C$ perchè comunque senza di esso posso derivare tutti gli elementi
>	- $B_{G\setminus\{B\rightarrow C\}}^+=B$
>3. $G=\{B\rightarrow C, A\rightarrow B\}$






