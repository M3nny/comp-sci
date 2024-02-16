La **normalizzazione** fornisce degli strumenti/algoritmi per stabilire in modo rigoroso la bontà di uno schema relazionale e nel caso migliorarlo (normalizzazione).

Prendiamo come esempio il seguente schema **non normalizzato**:

| NomeUtente       | Telefono | <u>CodiceLibro</u> | Titolo     | Data  |
|:---------------- |:-------- |:------------------ |:---------- |:----- |
| Rossi Carlo      | 75444    | XY188A             | Decameron  | 07-07 |
| Pastine Maurizio | 66133    | XY090C             | Canzoniere | 01-08 |
| Paolicchi Laura  | 59729    | XY101A             | Vita Nova  | 05-08 |
| Paolicchi Luca   | 59729    | XY701B             | Adelchi    | 14-01 |
| Paolicchi Luca   | 59729    | XY008C             | Amleto     | 17-08 |

I problemi principali sono:
- **Ridondanza dei dati**
- **Scarsa espressività**: possono essere rappresentati solo utenti che hanno preso libri in prestito
- **Anomalie di aggiornamento**: potrebbero essere aggiornati solo una parte di dati
- **Anomalie di inserimento/cancellazione**: Una cattiva progettazione può rendere impossibile rappresentare certe informazioni, conducendo ad anomalie in presenza di operazioni di inserimento e cancellazione.

### Dipendenze funzionali
Sia $R(T)$ uno schema di relazione, $r$ una sua istanza (tabella) e siano $X, Y$ due insiemi di attributi non vuoti della tabella $r$,  una **dipendenza funzionale** è un qualsiasi vincolo della forma:
$$X\rightarrow Y\quad (Y\text{ dipende da }X)$$
Si dice **soddisfatta** sse per ogni coppia di tuple $t_1$ e $t_2$ di $r$ aventi gli stessi valori sui campi $X$, $t_1$ e $t_2$ hanno gli stessi valori anche sui campi $Y$.

>$R(T, F)$ indica uno schema di relazione $R(T)$ con tutte le dipendenze funzionali $F$ soddisfatte.

>[!Example]
>- ✔️ NomeUtente $\rightarrow$ Telefono
>- ✔️ CodiceLibro $\rightarrow$ Titolo, NomeUtente, Data
>- ❌ Telefono $\rightarrow$ NomeUtente

$F$ implica logicamente la dipendenza funzionale $X\rightarrow Y$ indicato con $X\models Y$ sse ogni istanza di $R(T, F)$ soddisfa (almeno) $X\rightarrow Y$.

>[!Example]
>Sia $F$ = {CodiceLibro $\rightarrow$ TItolo, CodiceLibro $\rightarrow$ NomeUtente}
>- $F\models$ CodiceLibro $\rightarrow$ Titolo, NomeUtente
>- $F\models$ CodiceLibro

### Assiomi di Armstrong
- **Riflessione** (Refl):
$$\frac{Y\subseteq X}{F\vdash X\rightarrow Y}$$
Se $Y$ è un sottoinsieme di $X$, allora $Y$ dipende da $X$.

- **Aumento** (Augm):
$$\frac{F\vdash X\rightarrow Y}{F\vdash XZ\rightarrow YZ}$$
Se $Y$ dipende da $X$ e $Z$ è un insieme di attributi, allora $YZ$ dipende da $XZ$, questo vuol dire che aggiungendo attributi alla dipendenza di base, essa non cambia.

- **Transitività** (Trans):
$$\frac{F\vdash X\rightarrow Y\qquad F\vdash Y\rightarrow Z}{F\vdash X\rightarrow Z}$$
Se $Y$ dipende da $X$ e $Z$ dipende da $Y$, allora $Z$ dipende da $X$.

>La linea di frazione si legge come: _"tale che"_ o _"allora"_.
>Lo spazio tra due implicazioni si legge come: _"e"_.

>[!Attention]
>Dati gli assiomi di Armstrong, $\models$ e $\vdash$ sono equivalenti, perchè vale quanto segue: $F\vdash X\rightarrow Y \iff F\models X\rightarrow Y$.

**Regole derivate**:
- **Unione**: se $X\rightarrow Y$ e $X\rightarrow Z$, allora $X\rightarrow YZ$
- **Decomposizione**: se $X\rightarrow YZ$, allora $X\rightarrow Y$
- **Indebolimento**: se $X\rightarrow Y$, allora $XZ\rightarrow Y$

### Chiusura
Dato un insieme di dipendenze funzionali $F$, la sua chiusura $F^+$ rappresenta l'insieme di dipendenze funzionali di $F$ più le sue dipendenze funzionali derivate.
$$F^+=\{X\rightarrow Y\space|\space F\vdash X\rightarrow Y\}$$
ovvero: $F^+=\{\text{dipendenze funzionali } | \text{ dipendenze derivate}\}$.

Sia $R(T, F)$ lo schema di relazione, la chiusura di un attributo $X\subseteq T$ rispetto ad $F$ è definita come l'insieme di dipendenze funzionali di $F^+$ le quali hanno attributi che dipendono da $X$.
$$X_F^+=\{A\in T\space|\space F\vdash X\rightarrow A\}$$
dove $A$ è un attributo che dipende da $X$, infatti:
$$F\vdash X\rightarrow A\iff A\subseteq X_F^+$$


