Utilizziamo funzioni per centralizzare lato server una sequenza di operazioni di cui non ci interessano i risultati intermedi.

Una funzione si dichiara come segue:
```sql
CREATE FUNCTION my_fun ( args ) RETURNS type AS
$$ DECLARE
	num INT;
	name TEXT;
BEGIN
	...
END; 
$$ LANGUAGE plpgsql;
```

Postgres richiede che il corpo della funzione sia una stringa, per creare una stringa multi-riga utilizziamo `$$` prima e dopo il corpo della funzione.

### Dichiarazione
La **dichiarazione di variabili** segue il seguente formato:
```sql
DECLARE
name [ CONSTANT ] type [ NOT NULL ] [ = expr ];
```

il tipo può essere qualsiasi tipo SQL, inoltre ce ne sono altri particolari tra cui:
- `var%TYPE`: il tipo della variabile o colonna chiamata `var`
- `tab%ROWTYPE`: il tipo record delle righe della tabella `tab`
- `RECORD`: un qualsiasi tipo record
- `SETOF t`: un insieme di elementi di tipo `t` (solo per valori di ritorno)

```sql
CREATE FUNCTION my_concat(a text, b text, uppercase boolean = false)
RETURNS text AS $$
BEGIN
	IF uppercase
		THEN RETURN UPPER(a || ’ ’ || b);
	END IF;
	RETURN LOWER(a || ’ ’ || b);
END;
$$ LANGUAGE plpgsql;

-- Concatena due stringhe
```

### Assegnamento
L'**assegnamento** avviene tramite l'operatore `:=`
```sql
DECLARE
	price INT := 10; -- binding
```

è anche possibile usare delle query come valore di una variabile:
```sql
DECLARE
	my_id INT;
BEGIN
	SELECT id INTO my_id FROM table_name WHERE name = 'example';
	-- my_id contiene il valore ID della riga selezionata
END
```

se la query ritorna più di una riga, la variabile assumerà il valore della prima riga, è possibile usare `STRICT` per sollevare un'eccezione nel caso la query ritornasse più di una riga.

### Valore di ritorno

**Ritorno singolo**:
```sql
CREATE OR FUNCTION sum(x INT, y INT) RETURNS INT AS $$
DECLARE
    result INT;
BEGIN
    result := x + y;
    RETURN result;
END;
$$ LANGUAGE plpgsql;

-- Ritorna x + y
SELECT sum(10, 5);
```

**Ritorno multiplo**: viene utilizzato `OUT` nella firma
```sql
CREATE OR FUNCTION
sum_prod(x INT, y INT, OUT sum_result INT, OUT product_result INT)
AS $$
BEGIN
    sum_result := x + y;
    product_result := x * y;
END;
$$ LANGUAGE plpgsql;

-- Ritorna x + y, e x * y
SELECT * FROM sum_prod(10, 5);
```


È anche possibile ritornare un **insieme di valori** (`SETOF`), però per farlo bisogna aggiungere i valori al set in maniera incrementale tramite:
```sql
RETURN NEXT expr; -- aggiunge un record al risultato
RETURN QUERY query; -- aggiunge un insieme al risultato
```

**Ritorno di un insieme**:
`SETOF:
- Non specifica esplicitamente i tipi di dati restituiti
- Quando viene chiamata bisogna specificarli
```sql
CREATE FUNCTION set_foo() RETURNS SETOF RECORD AS $$
BEGIN
	RETURN QUERY SELECT model, price FROM pc;
END;
$$ LANGUAGE plpgsql;

-- Restituisce i modelli ed i prezzi della tabella pc
SELECT m, p FROM set_foo() AS (m character(20), p real);
```

`RETURNS TABLE`:
- Specifica i dati restituiti
- Quando viene chiamata non bisogna specificarli
```sql
CREATE FUNCTION table_foo() RETURNS TABLE(m integer, p real) AS $$
BEGIN
	RETURN QUERY SELECT model, price FROM pc;
END;
$$ LANGUAGE plpgsql;

-- Restituisce i modelli ed i prezzi della tabella pc
SELECT * FROM table_foo();
```

**Costruzione del tipo di ritorno**: utile quando si vuole tener traccia di più stadi del valore di una variabile
```sql
CREATE FUNCTION generate_up_to(n INT) RETURNS SETOF INT AS $$
DECLARE
    i INT := 0;
BEGIN
    WHILE i < n LOOP
        i := i + 1;
        RETURN NEXT i; -- Restituisce il numero corrente
    END LOOP;
END;
$$ LANGUAGE plpgsql;

-- Genera i primi 10 numeri interi
SELECT * FROM generate_up_to(10);
```

### Control flow
**If-else**:
```
IF boolean-expr THEN
	statements
ELSIF boolean-expr THEN
	statements
ELSE
	statements
END IF;
```

**While**:
```
WHILE boolean-expr LOOP
	statements
END LOOP;
```

**For**:
```
FOR i IN 1..n LOOP -- i non deve essere dichiarata, è locale al for
	statements
END LOOP;
```

**FOUND**: è una variabile (non dichiarata) che viene impostata a `true` o `false` in base all'ultima operazione effettuata, viene impostata a `true` quando:
- Viene assegnata una riga alla variabile corrispondente in `SELECT INTO`
- `UPDATE, INSERT, DELETE` modificano almeno una riga
- Il ciclo `FOR` ha iterato almeno una volta
- `RETURN QUERY` ritorna almeno una riga

### Eccezioni
La clausola `RAISE` permette di stampare messaggi informativi oppure di sollevare un'eccezione:
```
RAISE [ level ] 'stringa formattata'
```

`level` può essere: DEBUG, LOG, NOTICE,... oppure **EXCEPTION** il quale genera un'eccezione.

Oltre a sollevare un'eccezione manualmente è possibile definire un blocco "try-catch" come segue:
```sql
BEGIN
	UPDATE ...
	x := x + 1;
	y := x / 0;
EXCEPTION
	WHEN division_by_zero THEN
		RAISE NOTICE ’caught division_by_zero’;
		RETURN x;
END;

-- division_by_zero è un'eccezione di default di postgres
```

in questo caso l'operazione di `UPDATE` che è all'interno del blocco `EXCEPTION` viene annullata, però le variabili mantengono il loro valore modificato, (e.g. se `x` inizialmente era 0 e poi è stata incrementata a 1, dopo l'eccezione sarà comunque a 1).

### Procedure
Le procedure per definizione non ritornano valori, in plpgsql, si creano con `PROCEDURE` e vengono chiamate con `CALL`:
```sql
CREATE PROCEDURE calculate_sum(x INT, y INT) AS $$
DECLARE
    result INT;
BEGIN
    result := x + y;
    RAISE NOTICE '% + % = %', x, y, result;
END;
$$ LANGUAGE plpgsql;

-- Stampa la somma tra x e y
CALL sum(5, 10);
```

