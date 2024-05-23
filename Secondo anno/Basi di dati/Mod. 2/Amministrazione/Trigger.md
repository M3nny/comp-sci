I **trigger** sono lo standard per il mantenimento di **invarianti globali**.
1. Un trigger è associato ad un **evento** (`INSERT, DELETE, UPDATE`)
2. Quando attivato può controllare una certa **condizione**
3. Se la _condizione_ è vera esegue l'**azione** associata al trigger

- **Trigger per riga**: eseguiti per ogni _riga_ coinvolta nell'evento scatenante, per riferirsi alle righe prima e dopo la loro modifica si usa `OLD ROW` e `NEW ROW`
- **Trigger per statement**: eseguiti per ogni _tabella_ coinvolta nell'evento scatenante, per riferirsi alle righe prima e dopo la loro modifica si usa `OLD TABLE` e `NEW TABLE`

Nella definizione di un trigger è possibile specificare se l'azione sarà eseguita prima o dopo dell'evento scatenante:
- **BEFORE trigger**: attivati prima dell'evento, impediscono l'esecuzione di un'operazione o ne cambiano il comportamento
- **AFTER trigger**: attivati dopo l'evento, possono agire sia con lo stato vecchio del database e sia con quello nuovo

>Un AFTER trigger può simulare l'annullamento di un'operazione, ma è più costoso ed in genere se possibile è meglio usare i BEFORE triggers, tuttavia in alcuni casi è necessaria l'espressività fornita da un AFTER trigger.

Possiamo scegliere un trigger in base a questi punti:
1. Quali eventi possono violare l'invariante?
2. Il mantenimento dell'invariante deve essere controllato per ogni riga?
3. Cosa bisogna fare prima o dopo l'evento per garantire l'invariante?

>[!Example]
>**Garantire che non sia mai possibile abbassare uno stipendio.**
>1. Violato da `UPDATE`
>2. L'informazione è contestuale alla riga modificata
>3. Impedire l'aggiornamento (BEFORE), fare un rollback (AFTER)
>
>**Garantire che la media degli stipendi non scenda mai sotto 500.000**
>1. Violato da `INSERT, DELETE, UPDATE`
>2. L'informazione riguarda l'intera tabella
>3. Impedire l'aggiornamento (BEFORE), fare un rollback (AFTER)
>
>**Garantire che la data di uscita di un film non possa essere `NULL`, usando un valore di default 2000 in tal caso**
>1. Violato da `INSERT, UPDATE`
>2. L'informazione è contestuale alla riga modificata
>3. Correggere il valore della data nella riga prima che venga scritta o dopo

- **Trigger passivi**: provocano il fallimento di un'operazione sotto determinate condizioni
- **Trigger attivi**: modificano anche in modo complesso lo stato del database in corrispondenza di certi eventi

È possibile usare i trigger per garantire vincoli come chiavi primarie o esterne, ma anche dipendenze funzionali, tuttavia ogni DBMS implementa i trigger a proprio modo, quindi, dove possibile, è meglio usare i vincoli standard SQL supportati da tutti i DBMS.

Postgres offre un sistema di trigger fedele allo standard SQL:
```
CREATE TRIGGER name { BEFORE | AFTER } { evt [ OR ... ] } ON table_name
[ REFERENCING { { OLD | NEW } TABLE AS tab } [ ... ] ]
[ FOR EACH { ROW | STATEMENT } ]
[ WHEN ( condition ) ]
EXECUTE FUNCTION func ( args )
```

il corpo del trigger deve essere definito in una funzione separata.
## Funzioni
Postgres supporta la definizione di funzioni scritte in vari linguaggi, il suo nativo è **PL/pgSQL**, esse possono avere _trigger_ come tipo di ritorno.

```
CREATE FUNCTION my_trigger() RETURNS trigger as $$
BEGIN
	IF
		statement
	END IF;
END
$$ LANGUAGE plpgsql;
```

Ogni statement è una istruzione SQL.

### Variabili speciali
Quando una funzione viene invocata, vengono create nel suo scope alcune variabili speciali, tra cui:
- `NEW`: la nuova riga per operazioni di `INSERT/UPDATE` all'interno di un trigger per riga (`NULL` in caso di `DELETE`)
- `OLD`: la vecchia riga per operazioni di `DELETE/UPDATE` all'interno di un trigger per riga (`NULL` in caso di `INSERT`)
- `TG_OP`: l'operazione che ha fatto scaturire il trigger (e.g. insert)
- `TG_TABLE_NAME`: la tabella che ha fatto scaturire il trigger

### Valore di ritorno
Una funzione associata ad un **BEFORE trigger per riga**, può:
- Ritornare `NULL` per indicare che l'operazione sulla riga deve essere abortita
- Ritornare una riga che diventerà la nuova riga in caso di `INSERT, UPDATE`
- Ritornare `NEW` nel caso di `INSERT, UPDATE` oppure `OLD` nel caso di `DELETE` se non si vuole interferire con l'operazione

Nel caso di una funzione associata ad un **AFTER trigger per riga**, oppure per **statement**, la funzione deve ritornare `NULL`.

#### Trigger per riga
- Un BEFORE trigger per riga può prevenire operazioni o modificarle
- La clausola `WHEN` può fare riferimento a `OLD` e `NEW`, ma non può far uso di sotto-query
- È possibile usare `REFERENCING` per vedere i cambiamenti complessivi nell'intera tabella (solo per AFTER trigger)

#### Trigger per statement
- Un trigger per statement viene eseguito almeno una volta anche se nessuna riga è coinvolta nell'operazione scatenante
- La clausola `WHEN` può essere usata ma è inutile in quanto non è possibile accedere a `OLD` e `NEW`
- È possibile usare `REFERENCING` per vedere i cambiamenti complessivi nell'intera tabella (solo per AFTER trigger)

### Ordine di esecuzione
I trigger vengono eseguiti nel seguente ordine:
1. BEFORE trigger per statement
2. BEFORE trigger per riga
3. AFTER trigger per riga
4. AFTER trigger per statement

>[!Attention]
>- Se più trigger dello stesso tipo per lo stesso evento vengono definiti, allora verranno eseguiti in ordine alfabetico fino alla terminazione o finchè uno di essi _non_ ritorna `NULL`.
>
>- Un trigger può chiamare ricorsivamente altri trigger, e potrebbero generare ricorsioni infinite se gestiti male.

---
Avendo il seguente schema logico:
- **Product**(maker, <u>model</u>, type)
- **PC**(<u>model</u>_*_, speed, ram, hd, price)
- **Laptop**(<u>model</u>_*_, speed, ram, hd, screen, price)
- **Printer**(<u>model</u>_*_, color, type, price)

Garantire che nessun produttore di PC possa anche produrre laptop.
1. Violato da `INSERT, UPDATE` su Product
2. L'informazione è contestuale alla riga modificata
3. Bloccare l'operazione (BEFORE)

```sql
CREATE TRIGGER NoPCLaptop
BEFORE INSERT OR UPDATE
ON Product
FOR EACH ROW
EXECUTE FUNCTION no_pc_laptop();

CREATE FUNCTION no_pc_laptop() RETURNS trigger AS $$
BEGIN
	IF (NEW.type = ’pc’ AND NEW.maker IN (
		SELECT maker
		FROM Product
		WHERE type = ’laptop’)
	) THEN RETURN NULL;
	END IF;
	
	IF (NEW.type = ’laptop’ AND NEW.maker IN (
		SELECT maker
		FROM Product
		WHERE type = ’pc’)
	) THEN RETURN NULL;
	END IF;
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;
```

---
## Constraint vs Trigger
I **constraint** possono essere usati solo se la condizione da verificare è sulla riga stessa.

I **trigger** vanno usati quando:
- È necessaria una sotto-query per verificare una condizione trasversale a più tabelle che **non richiede aggregazione** :`for each row`
- È **necessario un calcolo aggregato**: `for each statement`

La keyword `WHEN` può essere **usata solo nei trigger per riga** per discriminare quando chiamare la funzione associata o meno, in base alla
riga modificata.
>Non è possibile usare sotto-query nel `WHEN`.

#### Righe modificate
- **Trigger per statement**: non possono accedere ai valori di ogni riga direttamente, il trigger dovrà referenziare `OLD table | NEW table` (possibile solo su `AFTER` trigger) se si vuole osservare la differenza tra righe prima e dopo l'operazione
- **Trigger per riga**: possono accedere per ogni riga al cambiamento ad esempio su una condizione è possibile fare `if campo = NEW.campo`, inoltre possono anche referenziare `OLD table | NEW table` (possibile solo su `AFTER` trigger)

>[!Attention]
>Le tabelle di transizione `OLD table` e `NEW table` possono essere referenziate solo se il trigger risponde ad un solo tipo evento.

`REFERENCING [OLD TABLE | NEW TABLE]` è **specificabile solo con trigger AFTER**, consente di avere delle tabelle di transizione che contengono tutte le righe che sono state prese in considerazione dall'evento e non solo una riga per volta come quando si accede ai campi con `NEW.campo | OLD.campo`.

|            | BEFORE                                                                                                                  | AFTER                                                                                      |
| ---------- | ----------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| **INSERT** | **OLD**: non disponibile<br>**NEW**: contiene la riga che sta per essere inserita                                       | **OLD**: non disponibile<br>**NEW**: contiene la nuova riga                                |
| **UPDATE** | **OLD**: contiene la riga prima dell'aggiornamento<br>**NEW**: contiene la riga con l'aggiornamento che verrà applicato | **OLD**: contiene la riga prima dell'aggiornamento<br>**NEW**: contiene la riga aggiornata |
| **DELETE** | **OLD**: contiene la riga che sta per essere cancellata<br>**NEW**: non disponibile                                     | **OLD**: contiene la riga che è stata cancellata<br>**NEW**: non disponibile               |

Eseguire una **query sulla tabella attuale** cambia in base al tipo di trigger:
- **BEFORE trigger**: la query viene eseguita sulla tabella prima della modifica
- **AFTER trigger**: la query viene eseguita sulla tabella modificata

- `OLD` non è disponibile nei trigger `INSERT` perché non esiste una riga vecchia prima dell'inserimento.
- `NEW` non è disponibile nei trigger `DELETE` perché non esiste una nuova riga dopo la cancellazione.