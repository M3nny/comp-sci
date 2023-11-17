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
