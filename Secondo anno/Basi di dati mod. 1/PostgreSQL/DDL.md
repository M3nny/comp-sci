In questa sezione vedremo come creare e modificare tabelle tramite il **DDL (Data Definition Language)**.

## Schemi
La **tabelle** sono racchiuse in uno **schema** con diverse autorizzazioni, i quali sono racchiusi in **cataloghi**.
- `CREATE SCHEMA Nome AUTHORIZATION Utente` per creare uno schema
- `DROP SCHEMA Università CASCADE` per eliminare uno schema, di default userà `RESTRICT`, ovvero non sarà possibile la cancellazione dello schema finchè ci sono tabelle al suo interno, con `CASCADE` invece si cancellano anche le tabelle.

Uno schema può contenere:
- **Tabelle base**: fisicamente memorizzate
- **Viste**: i dati non sono fisicamente memorizzati, ma prodotti dalla valutazione di una query

---
## Tabelle
Quando si crea una tabella, per ogni colonna si specifica il nome, tipo di dato ed eventuali vincoli.
Possono essere: vuote, già inizializzate o viste.

#### Tipi di dato
Oltre ai normali tipi di dato, `BLOB` (Binary Large Object) e `CLOB` (Character Large Object) vengono usati per memorizzare file binari e testi di dimensioni grandi, non è possibile eseguire confronti su questi tipi di dato.

Per creare un tipo personalizzato è possibile usare `DOMAIN`:
```sql
CREATE DOMAIN Voto AS SMALLINT
	CHECK (VALUE <= 30 AND VALUE >= 18)
```

Il tipo `SERIAL` viene usato per indicare un valore auto-incrementale, durante la fase di inserimento dati, per questa colonna particolare abbiamo due opzioni:
- Ignorare la colonna ed inserire gli altri dati
- Inserire `DEFAULT`
```sql
CREATE TABLE name (
	colname SERIAL,
	name VARCHAR(10)
);
```
#### Vincoli
Il DBMS oltre a verificare la correttezza del tipo di dato inserito, verifica anche i vincoli:
**Intra-relazionali**:
- `PRIMARY KEY`: designa un insieme di attributi come chiave primaria
- `UNIQUE`: designa un insieme di attributi come chiave
- `CHECK`: valuta un'espressione che produce un valore booleano
**Inter-relazionali**:
- `FOREIGN KEY`: designa un insieme di attributi come chiave esterna ed un'eventuale azione (`NO ACTION, SET NULL, SET DEFAULT, CASCADE`) da eseguire nel caso di `UPDATE` o `DELETE` della riga puntata.

```sql
CREATE TABLE Studenti (
	Nome VARCHAR(10) NOT NULL,
	Cognome VARCHAR(10) NOT NULL,
	Matricola CHAR(6) PRIMARY KEY,
	Nascita YEAR,
	Provincia CHAR(2) DEFAULT "VE"
	Tutor CHAR(6)
	FOREIGN KEY (Tutor) REFERENCES Studenti(Matricola)
		ON UPDATE CASCADE
		ON DELETE SET NULL
);

CREATE TABLE Docenti (
	CodDoc CHAR(3) PRIMARY KEY,
	Nome VARCHAR(8),
	Cognome VARCHAR(8)
);

CREATE TABLE Esami (
	Codice CHAR(4) PRIMARY KEY,
	Materia CHAR(3),
	Candidato CHAR(6) NOT NULL,
	Data DATE,
	Voto INTEGER CHECK(Voto >= 18 AND Voto <= 30),
	Lode CHAR(1),
	CodDoc CHAR(3) NOT NULL,
	UNIQUE (Materia, Candidato),
	FOREIGN KEY (Candidato) REFERENCES Studenti(Matricola)
		ON UPDATE CASCADE,
	FOREIGN KEY (CodDoc) REFERENCES Docenti(CodDoc)
		ON UPDATE CASCADE
);
```

>Ai vincoli può essere dato un nome così da poter essere aggiornati/modificati.

#### Alterazione delle tabelle
Le tabelle possono essere modificate con `ALTER`
```sql
ALTER TABLE Studenti
	ADD COLUMN Nazionalita VARCHAR(10) DEFAULT "Italiana";
-- Aggiunge una nuova colonna

ALTER TABLE Studenti
	DROP COLUMN Provincia;
-- Elimina una colonna

ALTER TABLE Studenti
	ALTER COLUMN Nazionalita TYPE VARCHAR(15);
-- Modifica il tipo di una colonna

ALTER TABLE Docenti
	ADD UNIQUE(RecapitoTel);
-- Aggiunge un vincolo

ALTER TABLE Studenti
	DROP CONSTRAINT nome_vincolo;
-- Elimina un vincolo
```

#### Eliminare tabelle
Le tabelle possono essere eliminate con il comando `DROP TABLE` seguito da:
- `RESTRICT` (default): non viene rimossa la tabella (o vista) se è usata in altre viste
- `CASCADE`: rimuove la tabella (o vista) e tutte le viste che la usano

#### Tabelle inizializzate
Si può inizializzare una tabella con una query.
```sql
CREATE TABLE EsamiFino2006 AS
	SELECT *
	FROM Esami e
	WHERE e.Data <= "31/12/2006";

DELETE FROM Esami
	WHERE e.Data <= "31/12/2006";
-- Rimuovo i dati duplicati dalla tabella appena creata
```

#### Viste
È possibile creare tabelle virtuali che vengono calcolate ad ogni interrogazione chiamate viste.

Le viste non possono essere modificate, inoltre devono essere corrispondenze biunivoche fra le righe della vista ed un sottoinsieme della tabella di base, ovvero:
- La `SELECT` per la vista contiene solo attributi non calcolati o ristretti
- `FROM` usa solo una tabella base
- Non è possibile usare `GROUP BY` e `HAVING` assieme
- Non deve contenere operatori insiemistici

Sono utili per:
- Dare accesso ad una parte limitata dei dati ad utenti
- Offrire visioni diverse senza duplicazione di dati 
- Rendere possibili o più semplici alcune query
>Non è possibile usare una funzione di aggregazione dentro ad un'altra


```sql
CREATE VIEW ProvMax(Provincia, Max) AS
	SELECT s.Provincia, MAX(e.Voto)
	FROM Studenti s JOIN Esami e ON s.Matricola = e.Candidato
	GROUP BY s.Provincia;

SELECT AVG(Max) FROM ProvMax;
-- Trova la media dei voti massimi ottenuti nelle varie province
```

---
