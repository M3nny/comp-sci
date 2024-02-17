Dato uno schema di relazione $R(T,F)$, un insieme di attributi $X\subseteq T$:
- **Superchiave** (di $R$): sse $(X\rightarrow T)\in F^+$  
- **Chiave**: superchiave minimale, ovvero all'interno non contiene sottoinsiemi (più piccoli) che possono essere superchiave
- **Attributo primo**: sse appartiene ad almeno una chiave

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

Dato $R(T,F)$, per verificare se $X\subseteq T$ è una _chiave_ è possibile:
1. Verificare se $X$ è superchiave
2. Verificare che per ogni attributo di $X$ sia vero che: togliendolo e trovando la chiusura dell'insieme di attributi rimanenti (verificando se è superchiave) si ha che la chiusura trovata è diversa dall'insieme di attributi $T$, questo vuol dire che l'attributo tolto è indispensabile e deve far parte della chiave minima (chiave)

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











