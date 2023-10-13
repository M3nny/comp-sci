I meccanismi per definire una base di dati con il modello relazionale sono l'**ennupla** (lista di attributi) e la **relazione** (tabella).

Rappresentiamo la seguente tabella:

|  Nome   | Cognome | Matricola | Anno |
|:-------:|:-------:|:---------:|:----:|
|  Paolo  |  Verdi  |   1234    | 2000 |
|  Anna   |  Rossi  |   4321    | 2006 |
| Giorgio |  Zeri   |   1243    | 2005 |

**Studenti**(Nome:string, Cognome:string, Matricola:string, Anno:Date)
- Cardinalità: 3
- Grado: 4

La **relazione** è quindi un insieme finito di ennuple, dove:
- La **cardinalità** è il numero delle righe della tabella
- Il **grado** è il numero di attributi della tabella

## Vincoli di integrità
Una istanza (riga) si dice **valida** se rispetta tutti i vincoli  definiti nel suo schema di appartenenza.
### Chiavi
Sono attributi che identificano univocamente l'ennupla di cui fanno parte, dovranno quindi essere diversi per ogni ennupla.

- **Superchiave**: è un sottoinsieme di attributi che identifica univocamente ogni ennupla
- **Chiave**: è una _superchiave_ che contiene solo attributi che discriminano facilmente ogni ennupla
- **Chiave primaria (Primary Key - PK)**: solitamente è una _chiave_, ce ne deve essere una per ogni tabella

Posso porre anche il vincolo **unique** su un attributo rendendolo diverso per ogni riga, esso di default potrà essere **null** mentre la PK _non_ può essere null.

Una colonna di una tabella può anche rappresentare la PK di un'altra tabella, in questo caso si parla di **chiave esterna (Foreign Key - FK)**, esse garantiscono l'**integrità referenziale** tra tabelle.

>[!Example]
>Studenti:
>
>|  Nome   | Cognome | Matricola | Anno |
>| :-------: | :-------: | :---------: | :----: |
>| Paolo     | Verdi     | 1234        | 2000   |
>| Anna      | Rossi     | 4321        | 2006   |
>| Giorgio   | Zeri      | 1243        | 2005   |
>Esami:
>
>| Codice | Materia | Candidato |    Data    | Voto | Lode |
>|:------:|:-------:|:---------:|:----------:|:----:|:----:|
>|   A1   |   M1    |   1234    | 01-01-2006 |  27  |  N   |
>|   B2   |   M2    |   1243    | 02-02-2006 |  26  |  N   |
>|   C3   |   M3    |   4321    | 03-02-2006 |  30  |  S   |
>
>**Studenti**(Nome:string, Cognome:string, <u>Matricola</u>:string, Anno:Date)
>**Esami**(<u>Codice</u>:string, Materia:string, _Candidato*_:string, Data:Date, Voto:int, Lode:char)
>

### Valori null
Viene posto **null** quando non si conosce o non è applicabile il valore di un attributo.
Il vincolo **not null** impone che quell'attributo non deve assumere valore null (not null è di default nelle PK).
Una FK può avere un valore null se rappresenta una associazione parziale.

## Dal modello a oggetti al modello relazionale
**Associazioni N:1 (totali)**
![[N_to_1_totale.png]]
La FK va messa nella parte che punta a 1 della relazione, se dovesse esserci un attributo della relazione, metto anch'esso con la FK.

**Associazioni N:1 (parziali)**:
![[N_to_1_parziale.png]]
Se la relazione è parziale, la FK la posso mettere nella parte che punta alla tabella parziale, in questo caso FK può essere null.
Se non voglio che la FK sia null devo creare una terza tabella dove la PK è la FK che punta alla tabella che prima era totale e poi aggiungere un'altra FK che punta all'altra tabella.

Anche qui se esiste un attributo di relazione lo metto dove c'è la FK oppure, nel caso, la metto nella terza tabella creata.

**Associazioni N:1 (ricorsive)**:
![[N_to_1_ricorsiva.png]]
Anche qui il ragionamento è analogo ai casi precedenti, solo che le FK si riferiscono sempre alla stessa tabella.

**Associazioni 1:1**:
![[1_to_1.png]]
Se una parte di relazione è parziale, metto la FK dove punta verso la tabella con associazione totale, se sono entrambe parziali o totali la metto dove voglio.
Come nei casi precedenti se non voglio FK null in caso di associazioni parziali, devo creare una terza tabella.

**Associazioni N:M**:
![[N_to_M.png]]
In caso di associazioni N:M devo aggiungere di default una nuova tabella dove le FK sono anche PK, non si pongono problemi riguardo a dove mettere gli attributi di relazione dato che ho sempre la terza tabella in cui dovranno stare.

## Sottoclassi
Considerando la seguente gerarchia:
![[Gerarchia.png]]

Possiamo risolvere l'ereditarietà in tre modi.

- **Relazione unica**: accorpo gli attributi dei figli nel padre aggiungendo un attributo che discrimina la tabella figlio di cui facevano parte.
![[Relazione unica.png]]

- **Partizionamento verticale**: copio la PK del padre nei figli mettendola anche come FK (nei figli).
![[Partizionamento verticale.png]]

- **Partizionamento orizzontale**: se il padre non ha associazioni verso di lui, posso eliminare il padre e copiare i suoi attributi compresa PK e FK nei figli.
![[Partizionamento orizzontale.png]]
