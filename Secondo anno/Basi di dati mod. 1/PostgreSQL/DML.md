**SQL (Structured Query Language)** è un linguaggio dichiarativo basato su calcolo relazionale su ennuple e algebra relazionale, dove:
- Relazioni = tabelle
- Ennuple = record/righe
- Attributi = campi/colonne

In questa sezione vedremo come effettuare query usando la parte di **DML (Data Manipulation Language)** in sql.

### Select
Viene usato per selezionare gli attributi da mostrare dopo una serie di operazioni, o anche per una semplice visione di come è fatta la tabella.
```sql
SELECT *
FROM Studenti
-- Mostra tutti i campi della tabella studenti

SELECT DISTINCT Provincia
FROM Studenti
-- Mostra le province degli studenti senza ripetizioni
```

### Where
Viene usato per restringere gli attributi da mostrare, applicando delle condizioni.
```sql
SELECT *
FROM Studenti
WHERE Provincia = "VE"
-- Mostra tutti gli studenti che fanno parte della provincia 'VE'
```

Si usa la **notazione puntata** quando si opera su tabelle diverse che hanno attributi con lo stesso nome, in questo modo si evita di creare ambiguità per il DMBS.
Si possono concatenare più condizioni con `AND | OR | BETWEEN`.

Utile anche per **query ricorsive**:
```sql
SELECT n.Nome, n.Cognome, f.Nome, f.Cognome
FROM Persone n, Persone p, Persone f
WHERE f.IdPadre = p.Id AND p.IdPadre = n.Id AND n.Lavoro = f.Lavoro
/*
	Nome e cognome delle persone (e dei nonni) che fanno lo stesso lavoro
	dei nonni
*/
```

### Alias
Al posto di usare la _notazione puntata_ si possono usare gli **alias** per definire degli attributi, utile anche quando si usa la `SELECT` con funzioni di aggregazione.
```sql
SELECT COUNT(*) AS Totale_studenti
FROM Studenti
```

### Funzioni di aggregazione
Le **funzioni di aggregazione** sono: `SUM | COUNT | AVG | MAX | MIN`
esse non possono essere usate nella clausola `WHERE`.
```sql
SELECT MIN(Nascita), MAX(Nascita), AVG(Nascita)
FROM Studenti
-- Anno di nascita minimo, massimo e medio degli studenti
```

### From
La clausola `FROM` specifica da che tabella selezionare gli attributi, è possibile specificare più di una tabella, così da eseguire il _prodotto cartesiano_.
```sql
SELECT Esami.Nome, Studenti.Nome
FROM Esami, Studenti
WHERE Studenti.Nome = "Mario"
-- Mostra gli esami fatti da Mario
```

Oppure si possono usare le **giunzioni** (tutti i tipi di `JOIN`) per creare una tabella mettendone in relazione altre.
Le giunzioni possibili sono: `[CROSS | NATURAL] [LEFT | RIGHT | FULL] JOIN`.
> Usare il `CROSS JOIN` equivale ad usare `FROM` su più tabelle.
> `JOIN` e `INNER JOIN` hanno lo stesso effetto.
> Si può usare `USING` per specificare le colonne su cui effettuare la natural join.

```sql
SELECT Nome, Cognome, Matricola, Data, Materia
FROM Studenti s LEFT JOIN Esami e ON s.Matricola=e.Candidato
/*
	Esami di tutti gli studenti con gli attributi nella SELECT,
	elencando anche gli studenti che non hanno fatto esami
*/
```

### Order by
La clausola `ORDER BY attributo [DESC | ASC]` fa in modo che la tabella risultante si ordinata in modo _lessicografico_ secondo gli attributi indicati.
```sql
SELECT Nome, Cognome
FROM Studenti
WHERE Provincia = "VE"
ORDER BY Cognome DESC, Nome DESC
-- La tabella sarà ordinata in modo decrescente rispetto al nome completo
```

### Operatori insiemistici
Le clausole `[UNION | INTERSECT | EXCEPT] [ALL]` vengono usate per combinare i risultati di tabelle con colonne che hanno lo stesso nome e tipo.
Con l'opzione `ALL` vengono inclusi anche i duplicati nella tabella risultante.
```sql
SELECT Matricola
FROM Studenti
EXCEPT
SELECT Tutor AS Matricola
FROM Studenti
-- Le matricole che non sono tutor
```

### Il valore NULL
Viene assegnato il valore `NULL` ai campi su cui un attributo non è applicabile o non è disponibile (i motivi potrebbero essere anche altri).
Le condizioni usano una logica a $3$ valori: TRUE, FALSE, UNKNOWN.

|  p  |  q  | p `AND` q | p `OR` q |
|:---:|:---:|:---------:|:--------:|
|  T  |  T  |     T     |    T     |
|  T  |  F  |     F     |    T     |
|  T  |  U  |     U     |    T     |
|  F  |  T  |     F     |    T     |
|  F  |  F  |     F     |    F     |
|  F  |  U  |     F     |    U     |
|  U  |  T  |     U     |    T     |
|  U  |  F  |     F     |    U     |
|  U  |  U  |     U     |    U     |

Le clausole restituiscono solo le righe che rendono **vere** le condizioni.
```sql
SELECT *
FROM Studenti
WHERE Tutor IS NULL
-- Ritorna tutte le righe complete della tabella studenti, dove Tutor è NULL
```

è possibile usare l'operatore `COALESCE(expr)` per ritornare il primo valore diverso da `NULL` (funzione da sinistra a destra).
```sql
SELECT COALESCE(NULL, "Mario", NULL, "Luigi")
-- Ritorna "Mario"
```

### Pattern matching
Sulle stringhe è possibile usare la clausola `LIKE` per usare _regex_.
```sql
SELECT *
FROM Studenti
WHERE Nome LIKE "A%a" OR Nome LIKE "A%i"
-- Studenti che iniziano con 'A' e terminano per 'a' oppure 'i'
```

### Sottoselect
La clausola `WHERE` usa una combinazione booleana di predicati sotto forma di: `Expr Comp Expr`, è possibile inserire nel campo `WHERE` una condizione che usa una select annidata, dove si può:
- Eseguire **confronti** con la tabella di ritorno della sottoselect
- Verificare la **presenza di valori** all'interno della tabella ritornata dalla sottoselect
- Verificare se l'insieme di valori ritornato dalla sottoselect è **vuoto**
```sql
SELECT *
FROM Studenti
WHERE (Matricola <> "1234") AND
	Provincia = (SELECT Provincia
				 FROM Studenti
				 Where Matricola = "1234")

-- Oppure, senza sottoselect
SELECT altri.*
FROM Studenti altri JOIN Studenti s USING (Provincia)
WHERE altri.Matricola <> "1234" AND s.Matricola = "1234"

/*
* Studenti che vivono nella stessa provincia dello studente con la matricola 
* 1234, escluso lo studente stesso
*/
```

## Quantificazione
Esistono quantificazioni **esistenziali** ed **universali**.
- Esistenziale negata = universale
- Universale negata = esistenziale

Nella clausola `WHERE`, possiamo specificare varie quantificazioni:

#### Esistenziale

**EXISTS**:
`WHERE [NOT] EXISTS (Sottoselect)`, verifica se la sottoselect ritorna una tabella non vuota.
```sql
SELECT *
FROM Studenti s
WHERE EXISTS (SELECT *
			  FROM Esami e
			  WHERE e.Candidato = s.Matricola AND e.Voto > 27)
-- Studenti con almeno un voto > 27
```

**ANY**:
`WHERE Expr Comp ANY (Sottoselect)`.
- TRUE se esiste un valore `v` restituito dalla sottoselect che è in relazione `Comp` con `Expr`, cioè `Expr Comp v` è vera
- FALSE se nella sottoselect tutti i valori sono diversi da `NULL` e non esiste un valore `v` tale che `Expr Comp v` è vera, quindi se la sottoselect è vuota è false
- UNKNOWN se nella sottoselect ci sono valori `NULL` e per tutti i valori diversi da `NULL` si ha che `Expr Comp v` è falsa
```sql
SELECT *
FROM Studenti s
WHERE s.Matricola = ANY (SELECT e.Candidato
						 FROM Esami e
						 WHERE e.Voto > 27)
-- Studenti con almeno un voto > 27
```

**IN**:
```sql
SELECT *
FROM Studenti s
WHERE s.Matricola IN (SELECT e.Candidato
					  FROM Esami e
					  WHERE e.Voto > 27)
-- Studenti con almeno un voto > 27
```

#### Universale
Non disponendo di un operatore del tipo "forall" in sql, dobbiamo trasformare la quantificazione universale in una esistenziale negata.
```sql
SELECT *
FROM Studenti s
WHERE NOT EXISTS (SELECT *
				  FROM Esami e
				  WHERE e.Candidato = s.Matricola AND e.Voto <> 30)
-- Gli studenti che hanno preso solo 30
-- ATTENZIONE: con questa query si prendono anche gli studenti che devono ancora superare qualche esame, quindi con valore NULL

SELECT *
FROM Studenti s
WHERE NOT EXISTS (SELECT *
				  FROM Esami e
				  WHERE e.Candidato = s.Matricola AND e.Voto <> 30)
	  AND EXISTS (SELECT *
				  FROM Esami e
				  WHERE e.Candidato = s.Matricola)
-- Studenti che hanno preso solo trenta e hanno superato qualche esame
```

**ALL**:
`WHERE Expr Comp ALL (Sottoselect)`
Forma specchiata di `ANY`.
- TRUE se tutti i valori della sottoselect sono diversi da `NULL`, e per ogni `v` del risultato della sottoselect, `Expr Comp v` è vera
- FALSE se esiste un `v` risultato della sottoselect tale che `Expr Comp v` è false
- UNKNOWN se nella sottoselect ci sono valori `NULL` e per tutti i valori `v` diversi da `NULL`, si ha che `Expr Comp v` è vera
```sql
SELECT *
FROM Studenti s
WHERE s.Matricola <> ALL (SELECT e.Candidato
						  FROM Esami e
						  WHERE e.Voto <> 30)
-- Gli studenti che hanno preso solo 30
```

>[!Tip] ANY vs ALL
>- `ANY` = `OR` generalizzato
>- `ALL` = `AND` generalizzato
### Group by
Partiziona la tabella risultante (dalle operazioni di select, from, where) rispetto all'uguaglianza su tutti i campi ed elimina i gruppi che non rispettano la clausola `HAVING`, da ogni gruppo poi viene estratta una riga tramite la `SELECT`.

```sql
SELECT Candidato, COUNT(*) AS NEsami, MIN(Voto), MAX(Voto), AVG(Voto)
FROM Esami
GROUP BY Candidato
HAVING AVG(Voto) > 23
-- Mostra delle statistiche solo per candidati con media superiore a 23
```
![[GROUP BY.svg|600]]

>[!Attention]
>- Gli attributi non aggregati nella `SELECT` e `HAVING` devono essere presenti nel `GROUP BY`.
>- La clausola `HAVING` presenta solo attributi raggruppati oppure funzioni di aggregazione applicate ad attributi non raggruppati.

Nel raggruppamento si assume `NULL = NULL`.
```sql
SELECT Tutor, COUNT(*), AS NStud
FROM Studenti
GROUP BY Tutor
-- Matricole dei tutor e relativo numero di studenti di cui sono tutor
```

#### Cases
La clausola `CASE` crea varie condizioni e ritorna la prima query che rispetta una di esse, se nessuna è rispettata verrà eseguito il ramo `ELSE`, oppure verrà ritornato `NULL` in assenza di `ELSE`.
```sql
CASE
	WHEN cond1 THEN result1
	WHEN cond2 THEN result2
	ELSE result
END
```

---
## Modifica dei dati

**INSERT**
Vengono specificati in ordine gli attributi da inserire in una nuova riga di una tabella, se non si specificano tutti, quelli rimanenti prenderanno valore `NULL` oppure `default`.
```sql
INSERT INTO Studenti (Matricola, Nome, Cognome)
VALUES ("1234", "Mario", "Rossi")

INSERT INTO StNomeCognome AS
	SELECT Nome, Cognome FROM Studenti

/*
* Insert di righe prodotte da una SELECT
* StNomeCognome(Nome, Cognome) è una tabella valida per questo tipo
* di inserimento
**

```
I valori `NOT NULL` e senza valore di `default` devono essere specificati.

**DELETE**:
Simile alla `SELECT`, a differenza che cancella righe intere.
```sql
DELETE FROM Studenti
WHERE Matricola NOT IN (SELECT Candidato FROM Esami)
-- Cancella gli studenti che non hanno sostenuto esami
```

>`DELETE FROM Tabella` cancella tutte le righe.

**UPDATE**:
Aggiorna i valori presenti in una tabella.
```sql
UPDATE Esami
SET Voto = Voto + 1
WHERE Voto > 23 AND Voto < 30
-- Aumenta di 1 punto il voto a tutti gli esami con voto > 23
```

Anche qui è possibile usare delle sottoselect.