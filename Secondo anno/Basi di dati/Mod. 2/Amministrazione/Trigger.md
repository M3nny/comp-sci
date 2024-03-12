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