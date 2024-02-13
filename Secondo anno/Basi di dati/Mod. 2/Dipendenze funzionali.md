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
Sia $R(T)$ uno schema di relazione, $r$ una sua istanza (tabella) e siano $X, Y$ due insiemi di attributi non vuoti della tabella $r$,  una **dipendenza funzionale** è un qualsiasi vincolo della forma $X\rightarrow Y$ (e.g. Titolo dipende da CodiceLibro).

Si dice **soddisfatta** sse per ogni coppia di tuple $t_1$ e $t_2$ di $r$ aventi gli stessi valori sui campi $X$, $t_1$ e $t_2$ hanno gli stessi valori anche sui campi $Y$.

>$R(T, F)$ indica uno schema di relazione $R(T)$ con tutte le dipendenze funzionali $F$ soddisfatte.

>[!Example]
>- ✔️NomeUtente $\rightarrow$ Telefono
>- ✔️CodiceLibro $\rightarrow$ Titolo, NomeUtente, Data
>- ❌ Telefono $\rightarrow$ NomeUtente

$F$ implica logicamente la dipendenza funzionale $X\rightarrow Y$ indicato con $X\models Y$ sse ogni istanza di $R(T, F)$ soddisfa (almeno) $X\rightarrow Y$.

>[!Example]
>Sia $F$ = {CodiceLibro $\rightarrow$ TItolo, CodiceLibro $\rightarrow$ NomeUtente}
>- $F\models$ CodiceLibro $\rightarrow$ Titolo, NomeUtente
>- $F\models$ CodiceLibro

