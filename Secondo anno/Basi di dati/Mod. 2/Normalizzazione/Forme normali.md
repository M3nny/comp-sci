L'obiettivo delle forme normali è garantire che uno schema sia di buona qualità, e viene spesso ottenuto tramite un processo di **normalizzazione** basato su una [[Secondo anno/Basi di dati/Mod. 2/Normalizzazione/Decomposizione|decomposizione]] dello schema di partenza.

**Proprietà desiderabili**:
- Lo schema non deve contenere anomalie
- Il processo di normalizzazione deve preservare i dati e le dipendenze

vedremo che non sarà possibile garantirle tutte.
## Boyce-Codd
Uno schema di relazione $R(T,F)$ è in **BCNF** (Boyce-Codd Normal Form) sse per ogni dipendenza funzionale $X\rightarrow Y\in F^+$ tale che $Y\nsubseteq X$ si ha che:
- $X$ è una _superchiave_.

>$F^+$ è sostituibile con $F$, la verifica di BCNF ha costo **polinomiale**.

>[!Example]
>**Verifica forma BCNF**
>
>$\text{Prodotti({Articolo, Magazzino, Quantità, Indirizzo}, F)}$ con $F=\{\text{Articolo Magazzino}\rightarrow\text{Quantità}, \text{Magazzino}\rightarrow\text{Indirizzo}\}$.
>
>Verifichiamo che ogni $X\in F$ sia una superchiave:
>- $\{\text{Magazzino}\}_F^+=\{\text{Magazzino, Indirizzo}\}$, non è superchiave
>- Non serve verificare le altre $X$ in quanto ne abbiamo già trovata una che non è superchiave
>
>Lo schema NON è in BCNF in quanto $\{\text{Magazzino, Indirizzo}\}$ non rappresenta una [[Chiavi e coperture canoniche#Verifica superchiave|superchiave]].

### Algoritmo di analisi
Questo algoritmo di conversione in BCNF è detto di **analisi** perchè decompone lo schema originale fino alla normalizzazione, ha costo **esponenziale**.

Sia $R(T,F)$ lo schema di partenza:
1. Seleziona $X\rightarrow Y\in F$ che viola BCNF, calcola gli insiemi di attributi $T_1=X_F^+$ e $T_2=X\cup(T\setminus T_1)$ 
2. Calcola le [[Secondo anno/Basi di dati/Mod. 2/Normalizzazione/Decomposizione#Proiezione|proiezioni]] $F_1=\pi_{T_1}(F)$ e $F_2=\pi_{T_2}(F)$
3. Controlla se $R_1(T_1,F_1)$ e $R_2(T_2,F_2)$ sono in BCNF, altrimenti applica lo stesso procedimento sullo schema che non rispetta la condizione

>[!Example]
>**Conversione in BCNF**
>
>Si consideri $\text{R(\{A, B, C\}, }\{\text{A B}\rightarrow\text{C},\space\text{C}\rightarrow\text{A}\})$ con:
>
>La dipendenza $\text{C}\rightarrow\text{A}$ viola BCNF, perchè:
>$$\{\text{C}\}_F^+=\{\text{C,A}\}$$
>
>**Algoritmo di analisi:**
>Calcoliamo $T_1$ e $T_2$
>$$T_1=\{\text{C}\}_F^+=\{\text{C,A}\}$$
>
>$$\begin{flalign}
>T_2&=\{\text{C}\}\cup(\text{\{A, B, C\}}\setminus\{\text{C,A}\})\\
>&=\{\text{C,B}\}
>\end{flalign}$$
>
>Calcoliamo $F_1$
>- $\{\text{C}\}_F^+=\{\text{C,A}\}$, le dipendenze funzionali in $T$ che riguardano gli attributi di $T_1$ sono: $\text{C}\rightarrow\text{A}\in F_1$
>- $\{\text{A}\}_F^+=\{\text{A}\}$, è un singolo attributo non ha dipendenze
>
>Calcoliamo $F_2$:
>$\{\text{C}\}_F^+=\{\text{C,A}\}$, da cui nessuna nuova dipendenza
>$\{\text{B}\}_F^+=\{\text{B}\}$, è un singolo attributo non ha dipendenze
>
>Abbiamo quindi $F_1=\{\text{C}\rightarrow\text{A}\}$ e $F_2=\emptyset$
>
>Lo schema iniziale è stato decomposto in:
>- $R_1(\{\text{C,A}\},\{\text{C}\rightarrow\text{A}\})$
>- $R_2(\{\text{C,B}\},\emptyset)$
>
>La dipendenza $\text{A B}\rightarrow\text{C}$ è andata persa.

**Vantaggi**:
- Garantisce l'assenza di anomalie
- Preserva i dati
- La verifica ha costo polinomiale
**Svantaggi**:
- La conversione ha costo esponenziale
- Non preserva le dipendenze

---
## Terza forma normale
Uno schema di relazione $R(T,F)$ è in **3NF** (Third Normal Form) sse per ogni dipendenza funzionale $X\rightarrow Y\in F^+$ tale che $Y\nsubseteq X$ si ha che:
- $X$ è una _superchiave_
- _Oppure_ tutti gli attributi di $Y\setminus X$ sono _primi_ (appartengono ad almeno una chiave).

>$F^+$ è sostituibile con $F$, la verifica di 3NF ha comunque costo **esponenziale** a causa della generazione delle chiavi.

>[!Attention]
>Ogni schema in BCNF è anche in 3NF, ma non viceversa.

>[!Example]
>**Verifica forma 3NF**
>
>Si consideri $\text{Telefoni(\{Prefisso, Numero, Località\}, F)}$ con:
>$$F=\{\text{Prefisso Numero}\rightarrow\text{Località},\space\text{Località}\rightarrow\text{Prefisso}\}$$
>
>Calcoliamo le chiavi partendo da $\text{Numero}$ il quale non dipende da altri attributi, in questo caso gli attributi in $T$ sono pochi, quindi possiamo direttamente verificare se le combinazioni che contengono $\text{Numero}$ sono chiavi.
>- $\{\text{Numero}\}_F^+=\{\text{Numero}\}$, non è chiave
>- $\{\text{Numero, Prefisso}\}_F^+=\{\text{Numero, Prefisso, Località}\}$, {Numero, Prefisso} è chiave
>- $\{\text{Numero, Località}\}_F^+=\{\text{Numero, Località, Prefisso}\}$, {Numero, Località} è chiave
>
>Abbiamo: 
>- $\{\text{Località}\}\setminus\{\text{Prefisso, Numero}\} = \text{Località}$
>- $\{\text{Prefisso}\}\setminus\{\text{Località}\} = \text{Prefisso}$
>
>Ogni attributo risultante da $Y\setminus X$ è primo in quanto compare in almeno una chiave, quindi lo schema è in 3NF.

### Algoritmo di sintesi
Questo algoritmo di conversione in BCNF è detto di **sintesi** perchè è basato sulla generazione di nuovi schemi più piccoli.

Sia $R(T,F)$ lo schema di partenza:
1. Costruisce una copertura canonica di $F$ chiamata $G$
2. Sostituisce in $G$ ciascun insieme di dipendenze $X\rightarrow A_1,..., X\rightarrow A_n$ con una singola dipendenza $X\rightarrow A_1...A_n$
3. Per ogni $X\rightarrow Y\in G$ crea un nuovo schema $S_i(XY)$
4. Elimina ogni schema contenuto in un altro schema
5. Se la decomposizione non contiene alcuno schema i cui attributi costituiscano una superchiave per $R$, aggiunge un nuovo schema $S(W)$ dove $W$ è una chiave di $R$ (garantisce la preservazione dei dati)
6. Le dipendenze di ogni schema sono quelle presenti in $F$ tali che la dipendenza in questione in $F$ usi un sottoinsieme degli attributi dello schema creato

>[!Example]
>Sia $R(\{A,B,C,D\},\{AB\rightarrow C,C\rightarrow D, D\rightarrow B\})$.
>
>Troviamo una copertura canonica:
>- Tutti gli $Y$ sono attributi singoli
>- L'unica dipendenza che può contenere attributi estranei è $AB\rightarrow C$, però non esistono $X$ che contengano solo $A$ o $B$ da cui dipendono altri attributi, per cui non sono ridondanti (nè $A$ nè $B$ sono estranei in $AB$)
>Lo schema è già in forma canonica
>
>Creiamo i nuovi schemi:
>- $R_1(\{A,B,C\})$ tramite $A\rightarrow C$
>- $R_2(\{C,D\})$ tramite $C\rightarrow D$
>- $R_3(\{B,D\})$ tramite $D\rightarrow B$
>
>Nessuno schema è contenuto in un altro
>
>Verifico se è presente uno schema i cui attributi costituiscano una superchiave per $R$:
>- $ABC_R^+=ABCD$, è superchiave
>- $CD_R^+=CDB$, non è superchiave
>- $BD_R^+=BD$, non è superchiave
>
>Gli attributi di $R_1$ costituiscono una superchiave per $R$, non è necessario aggiungere altri schemi, nel caso contrario bisognerebbe partire dall'attributo $A_R$ per trovare una chiave e aggiungere un eventuale $R_4$ che abbia come attributi la chiave trovata.

**Vantaggi**:
- Preserva i dati e le dipendenze
- La conversione ha costo polinomiale
**Svantaggi**:
- La verifica ha costo esponenziale
- Uno schema in 3NF può ancora contenere anomalie

---
### Strategie
Possiamo applicare due strategie in caso di uno schema di scarsa qualità:
- **Strategia 1**: convertirlo in BCNF per eliminare le anomalie, se notiamo che non ha preservato le dipendenze ci si accontenta di una conversione in 3NF
- **Strategia 2**: convertirlo in 3NF in modo da preservare dati e dipendenze, sperando di rimuovere tutte le anomalie (si verifica se la conversione produce in realtà una BCNF)

### Dipendenze multivalore
Esiste una anomalia non considerata neanche dalla BCNF, ovvero le **dipendenze multivalore**, le quali comportano una forte ridondanza nelle tabelle, risolvibile con la [4NF](https://en.wikipedia.org/wiki/Fourth_normal_form).
