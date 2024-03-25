Un **indice** è una struttura dati ausiliaria che ci permette di accedere in maniera efficiente alle righe di una relazione che soddisfano una determinata proprietà.

Solitamente è memorizzato in un binary search tree ([[Alberi binari di ricerca#B_Alberi|b-albero]]) che consente di trovare velocemente i puntatori alle righe che soddisfano una determinata condizione su una tabella.

Per creare un [indice](https://www.postgresql.org/docs/current/indexes-intro.html) su postgres si procede come segue:
```sql
CREATE INDEX myIndex ON tabella(attr);
```

per eliminarlo:
```sql
DROP INDEX myIndex
```
Vengono utilizzati **automaticamente** quando ritenuti vantaggiosi dal **query planner** del DBMS.

Considerando la seguente query:
```sql
SELECT *
FROM Movies
WHERE studio = ’Disney’ AND year = 2012;
```
 applicare un _indice_ su `year` fa in modo che solo metà delle tuple siano esaminate (ricerca in BST).

applicare un indice **multiattributo** su `(studio, year)` incrementa ancora di più le performance.
>L'ordine degli attributi su cui si specifica un indice _multiattributo_ è importante.

### Costo di una query
Una metrica ottimale per misurare il costo di una query è il numero di **pagine** caricate in RAM:
- Ciascuna contiene molteplici righe
- Se viene richiesta una singola riga, comunque viene allocata una pagina
- L'accesso a tutte le righe in una pagina ha quasi lo stesso costo di accedere ad una singola riga

Il numero di righe è una metrica pessima in quanto dipende tutto da come le informazioni sono salvate in memoria ([CLUSTER](https://www.postgresql.org/docs/current/sql-cluster.html)), potrebbero essere caricate $100$ pagine come $1$ nel caso fossero salvate in memoria in un modo che favorisce la query.

L'operazione di **clustering** avviene una volta sola, questo vuol dire che con nuove modifiche alle tabelle, questa operazione non sarà eseguita automaticamente, essa modifica la disposizione delle tabelle in memoria fisica secondo gli indici definiti.
```sql
CLUSTER tabella USING myIndex
```

**Vantaggio**: un indice può accelerare di molto una query che coinvolge gli attributi appartenenti all'indice.
**Svantaggio**: le operazioni di inserimento, cancellazione e modifica sono più costose in quanto devono aggiornare la struttura dati dell'indice.

>[!Info] Quando e dove definire un indice
>- Su chiavi/chiavi esterne
>- Quando le operazioni di modifica sono rare
>
>**NON**:
>- Su tabelle piccole
>- Su attributi poco selettivi (e.g. sesso)
>- Su attributi modificati di frequente

### Analisi sugli indici
È possibile usare i seguenti comandi per ottenere delle informazioni sugli indici utilizzati in una query:
- `ANALYZE`: colleziona statistiche sulla distribuzione dei dati, il _query planner_ le utilizzerà per decidere quali indici usare
- `EXPLAIN`: per verificare quali indici sono stati usati in una query

```sql
EXPLAIN SELECT *
FROM tabella
WHERE i = 3
```

Il DBMS procederà come segue per selezionare un indice:
1. Usa i log delle query per stimare il costo delle operazioni più frequenti
2. Genera un insieme di **indici candidati** e stima i tempi di esecuzione
3. Ritorna l'insieme di indici che ottimizza i tempi di esecuzione
>Il secondo passo potrebbe essere implementato in maniera **greedy**.

### Viste e performance
Una [[DDL#Viste|vista]] viene calcolata ogni volta che viene eseguita una query su di essa, il che è inefficiente.

Postgres consente di **materializzare** una vista in memoria in modo da mantenere la tabella creata dalla vista in memoria.

La sintassi è uguale a quella usata per creare una nuova vista:
```sql
CREATE MATERIALIZED VIEW tabella AS query
```

la differenza con `CREATE TABLE AS` è che le viste materializzate ricordano la query usata per generare la tabella, inoltre possono essere aggiornate su richiesta tramite `REFRESH MATERIALIZED VIEW`.

>Modificare la vista materializzata non comporta una sua rigenerazione intera, quando verrà usato `REFRESH` però ri-eseguirà la query con cui è stata dichiarata.

- In certi DBMS sono mantenute in modo **incrementale**
- Posso essere usate automaticamente dal DBMS in una query se la materialized view contiene un'informazione già computata utile alla query in questione




