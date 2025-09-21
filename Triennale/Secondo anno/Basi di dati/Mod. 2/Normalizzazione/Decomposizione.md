L'eliminazione di [[Dipendenze funzionali|anomalie]] è tipicamente basata sulla **decomposizione** di schemi mal definiti in schemi più piccoli equivalenti.

### Proiezione
Dato uno schema $R(T,F)$ ed un sottoinsieme di attributi $Z\in T$, la **proiezione** di $F$ su $Z$ è definita come l'insieme:
$$\pi_z(F)=\{X\to Y\in F^+ | X\cup Y\subseteq Z\}$$
ovvero: tutte le dipendenze funzionali di $F$, considerando solo il sottoinsieme di attributi $Z$.

### Decomposizione
Dato uno schema $R(T,F)$, una sua **decomposizione** è un insieme di schemi più piccoli:
$$\rho=\{R_1(T_1,F_1),...,R_n(T_n,F_n)\}$$
tale che:
- L'unione di tutti i $T_i$ copra l'insieme completo $T$ inziale
- Ciascun insieme $T_i$ non deve essere vuoto
- Per ogni $R_i(T_i,F_i)\in\rho$, $F_i$ è definito come la proiezione di $F$ su $T_i$: $\pi_{T_i}(F)$ 

Dato che i $F_i$ sono determinati da $F$ e $T_i$, scriveremo:
$$\rho=\{R_1(T_1),...,R_n(T_n)\}$$

### Perdita di informazioni
Tabella originale $R$:

| Proprietario | Telefono | Abitazione |
| ------------ | -------- | ---------- |
| Mario        | 1234     | Via Torino |
| Mario        | 4321     | Dorsoduro  |
Dopo la decomposizione:
$R_1$:

| Proprietario | Telefono |
| ------------ | -------- |
| Mario        | 1234     |
| Mario        | 4321     |
$R_2$:

| Proprietario | Abitazione |
| ------------ | ---------- |
| Mario        | Via Torino |
| Mario        | Dorsoduro  |
Andando a selezionare il numero di telefono di chi abita in Via Torino, otteniamo da:
- $R$: {1234}
- $R_1\bowtie R_2$: {1234, 4321}, vengono introdotti dati spuri

Definendo $S = R_1\bowtie R_2$, possiamo affermare che $R\subseteq S$, in quanto: o la join ritorna le stesse righe, o ci sono righe in più, ovvero **dati spuri**.

Una decomposizione $\rho=\{R_1(T_1), R_2(T_2)\}$ **preserva i dati** sse:
$$T_1\cap T_2\rightarrow T_1\in F^+\quad\text{oppure}\quad T_1\cap T_2\rightarrow T_2\in F^+$$

>[!Example]
>Si consideri $R(A,B,C,D)$ con $F=\{A\rightarrow BC\}$ .
>Verificare se $\rho=\{R_1(A,B,C), R_2(A,D)\}$ preserva i dati:
>- $T_1=\{A,B,C\}$ e $T_2=\{A,D\}$
>- $T_1\cap T_2=\{A\}$
>- $A_F^+=\{A,B,C\}=T_1$, quindi $T_1\cap T_2\rightarrow T_1\in F^+$
>
>La decomposizione preserva i dati.

### Perdita di dipendenze
Tabella originale $R$:

| Proprietario | Telefono | Macchina |
| ------------ | -------- | -------- |
| Mario        | 1234     | AAA      |
| Mario        | 1234     | BBB      |
| Mario        | 4321     | BBB      |
Dopo la decomposizione:
$R_1$:

| Proprietario | Telefono |
| ------------ | -------- |
| Mario        | 1234     |
| Mario        | 4321     |
$R_2$:

| Telefono | Macchina |
| -------- | -------- |
| 1234     | AAA      |
| 1234     | BBB      |
| 4321     | BBB      |
Volendo inserire (Luca, 6789, AAA):
- Nel primo caso verrebbe violata la dipendenza Macchina$\rightarrow$Proprietario
- Nel secondo caso non è possibile accorgersene, se non dopo la join

Una decomposizione $\rho=\{R_1(T_1),...,R_n(T_n)\}$ **preserva le dipendenze** sse:
$$\bigcup_i\pi_{T_i}(F)\equiv F$$
ovvero: sse l'unione delle dipendenze sui singoli schemi _equivale_ alle dipendenze dello schema originale.

Per verificarlo quindi, bisogna:
1. Calcolare le proiezioni
2. Calcolare l'unione delle dipendenze delle proiezioni
3. Verificare che per ogni $X\rightarrow Y\in F$ si abbia $Y\subseteq X_G^+$

>[!Example]
>Siano $R(A,B,C)$ e $F=\{A\rightarrow B, B\rightarrow C, C\rightarrow A\}$, verificare se la decomposizione $\rho = \{R_1(A,B),R_2(B,C)\}$ preserva le dipendenze.
>
>Calcoliamo $\pi_{AB}(F)$
>- $A_F^+=ABC$, quindi $A\rightarrow B\in\pi_{AB}(F)$
>- $B_F^+=BCA$, quindi $B\rightarrow A\in\pi_{AB}(F)$
>concludiamo che: $\pi_{AB}(F)=\{A\rightarrow B, B\rightarrow A\}$
>
>Calcoliamo $\pi_{BC}(F)$
>- $B_F^+=BCA$, quindi $B\rightarrow C\in\pi_{BC}(F)$
>- $C_F^+=CAB$, quindi $C\rightarrow B\in\pi_{BC}(F)$
>concludiamo che: $\pi_{BC}(F)=\{B\rightarrow C, C\rightarrow B\}$
>
>Calcoliamo l'unione:
>$$G=\pi_{AB}(F)\cup\pi_{BC}(F)=\{A\rightarrow B, B\rightarrow A, B\rightarrow C, C\rightarrow B\}$$
>Iteriamo sulle dipendenze originali $F$ e verifichiamo che siano tutte derivabili da $G$:
>- $A\rightarrow B$: abbiamo $B\in A_G^+=ABC$
>- $B\rightarrow C$: abbiamo $C\in B_G^+=BAC$
>- $C\rightarrow A$: abbiamo $A\in C_G^+=CBA$
>
>La decomposizione preserva le dipendenze.

La preservazione dei dati generalmente è **indipendente** dalla preservazione delle dipendenze, però se in una decomposizione $\rho=\{R_1(T_1),...,R_n(T_n)\}$ di $R(T,F)$ <u>che preserva le dipendenze</u> esiste almeno un insieme di attributi $T_i$ che è una _superchiave_ di $R(T,F)$, allora $\rho$ preserva anche i dati.
