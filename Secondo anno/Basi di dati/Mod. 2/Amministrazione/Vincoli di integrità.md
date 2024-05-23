I **vincoli di integrità** sono applicati ai dati di una tabella e dipendono dalla semantica dei dati.

- **NOT NULL**: l'attributo non può essere vuoto o impostato a `NULL`
```sql
CREATE TABLE Movies (
	title CHAR(100) NOT NULL,
	...
)
```

- **UNIQUE**: gli attributi all'interno di questa clausola non possono essere uguali per più righe
```sql
CREATE TABLE Movies (
	title CHAR(100) NOT NULL,
	release_year INT,
	...
	UNIQUE (title, release_year)
)
```

- **PRIMARY KEY**: si comporta come `UNIQUE` ed impone il vincolo `NOT NULL` sugli attributi nella clausola
```sql
CREATE TABLE Movies (
	title CHAR(100) NOT NULL,
	release_year INT,
	...
	PRIMARY KEY (title, release_year)
)
```

- **FOREIGN KEY**: garantisce l'<u>integrità referenziale</u>, il campo fa riferimento ad un campo di un'altra tabella, il quale deve essere `PRIMARY KEY` oppure `UNIQUE`
```sql
CREATE TABLE Movies (
	title CHAR(100) NOT NULL,
	studio INT,
	...
	FOREIGN KEY (studio) REFERENCES Studio(id)
)
-- Reference alla tabella Studio con PK = id
```

Alcuni **casi problematici**:
- Viene inserito come FK un attributo che non è presente nella tabella puntata
- Viene modificato un attributo FK ad un valore che non è presente nella tabella puntata
- Nella tabella puntata viene cancellata una riga puntata
- Nella tabella puntata viene modificato l'attributo chiave di una riga puntata

SQL mette a disposizione delle **politiche di integrità** per evitare i casi sopra descritti:
1. **NO ACTION**: rifiuta la modifica (è il comportamento di default)
2. **CASCADE**: applica alla tabella con la FK la stessa modifica effettuata nella tabella padre
3. **SET NULL**: imposta la FK a `NULL`

è possibile specificare se vogliamo applicare le politiche quando la tabella padre viene modificata con `ON UPDATE` oppure quando vengono cancellate delle righe `ON DELETE`.
```sql
CREATE TABLE Movies (
	title CHAR(100) NOT NULL,
	studio INT,
	...
	FOREIGN KEY (studio) REFERENCES Studio(id)
		ON DELETE SET NULL
		ON UPDATE CASCADE
)
```

### Check
È possibile specificare **vincoli complessi** tramite **CHECK** seguita da un'espressione booleana:
- Il vincolo è controllato ad ogni `INSERT` o `UPDATE`
- In alcuni DBMS non è possibile usare delle sottoquery per i `CHECK`
```sql
CREATE TABLE Person (
	age INT CHECK (age >= 0)
)
```

È possibile imitare la FK con un `CHECK`:
```sql
CREATE TABLE Movies (
	title CHAR(100) NOT NULL,
	studio INT CHECK (studio in (SELECT id from Studio))
)
```
tuttavia non è possibile garantire _l'integrità referenziale_ in caso di modifiche all'attributo "puntato".

la clausola `CHECK` può essere anche usata su una riga intera:
```sql
CREATE TABLE Person (
	code INT PRIMARY KEY,
	age INT,
	CHECK (code >= 100 AND age >= 0)
)
```

Il `CHECK` eseguito sulle righe è necessario solo se l'espressione coinvolge più attributi che non sono indipendenti tra loro, altrimenti risulta **inefficiente** rispetto ai singoli `CHECK` sugli attributi.

>[!Tip] Equivalenze logiche
>Per garantire che **tutti** gli attributi che soddisfano $A$ soddisfino $B$, si usa:
>$\neg A\lor B$ che equivale a $A\implies B$.
>
>Per garantire che **solo** gli attributi che soddisfano $A$ soddisfino $B$, si usa:
>$\neg B\lor A$ che equivale a $B\implies A$.

### Aggiornare i vincoli
Dando un nome ai vincoli con **CONSTRAINT** permette di modificarli/cancellarli successivamente.

Sintassi:
- `CONSTRAINT nome_c [FOREIGN KEY, UNIQUE, CHECK, ...`
- `ALTER TABLE nome_t ADD [CONSTRAINT nome_c] <definizione vincolo>`
- `ALTER TABLE nome_t DROP CONSTRAINT nome_c`
```sql
CREATE TABLE Person (
	age INT
);

ALTER TABLE Person ADD CONSTRAINT age_check CHECK (age >= 0);
ALTER TABLE Person DROP CONSTRAINT age_check;
```

>Il vincolo deve già valere al momento del suo inserimento.
### Asserzioni
Le asserzioni esprimono **invarianti globali** sull'intero schema relazionale, devono essere già vere al momento della loro creazione.

Sintassi:
- `CREATE ASSERTION nome CHECK <condizione>`

```sql
CREATE ASSERTION SumLength CHECK (
	500 <= ALL(
		SELECT SUM(length)
		FROM Movies
		GROUP BY studio
	)
)
-- La durata complessiva dei film prodotti da ogni studio
-- deve essere di almeno 500 minuti
```

>I principali DBMS non supportano le asserzioni.

