Le web app sono complesse e possiedono una grande superfice attaccabile, illustriamo di seguito comuni vulnerabilità di PHP.

## String comparison attacks
- **Type juggling**: in PHP il tipo di una variabile è determinato dal contesto nella quale viene usata
- **Strict comparison `===`**: ritorna `true` solo con valori identici (stesso tipo e valore)
- **Loose comparison `==`**: ritorna `true` anche se i valori (uguali) hanno tipo diverso (e.g. `"10" == 10`)

La loose comparison tuttavia [equipara troppo](https://www.php.net/manual/en/types.comparisons.php), potrebbero essere usate delle conversioni sottili che modificano il control-flow in modo non previsto.

Quando stringhe e interi vengono comparati, le stringhe vengono convertite in interi, se al loro interno non contengono cifre allora vengono convertite in `0`, da cui: `"php" == 0`.

### Vulnerabilità della loose comparison
Immaginiamo di avere un token di autenticazione salvato sul server, se usassimo `==` per confrontarlo con quello in input dall'utente l'autenticazione potrebbe essere bypassata facilmente:
```php
<?php
	// token stored on the server
	$token = "0e392847" ;
	// User input, e.g. coming from a cookie
	$input = $_COOKIE['user_token']
	if ($input == $token) {
		// access to privileged area
		echo "Authenticated!";
	} else {
		// login required ...
		echo "Please authenticate";
	}
?>
```

L'attaccante può bypassare l'autenticazione semplicemente passando `"0"` o usando brute-force finchè il valore convertito non è uguale.

Oppure in una situazione più "realistica" si userebbe un formato json:
```php
<?php
	// token stored on the server
	$token = ".....";
	// from the user
	$jsonInput = $_COOKIE['user_json_token']
	// parse json input from user
	$input = json_decode($jsonInput,true);
	// $input["token"] should be a string!
	
	if ($input["token"] == $token) {
		// access to privilege area
		echo "Authenticated!";
	} else {
		// login required ...
		echo "Please authenticate";
	}
?>

// json forged by the attacker
{
	"token": 0, // integer
	"username": "admin"
}
```

L'input potrebbe essere convertito in stringa prima di essere confrontato con `strcmp()`, ma ciò da un falso senso di sicurezza in quanto passare un array bypassa l'autenticazione, questo perchè quando `strcmp()` fallisce (non si aspetta un array) ritorna `NULL`, ma `NULL` è uguale a `0`:
```php
echo strcmp(array(), "4222412412") == 0;
1
```

## File inclusion attacks
Immaginiamo che il server carichi una pagina passata come parametro per cambiare dinamicamente il contenuto quando un bottone è premuto:
```php
<?php
	if(isset($_GET["p"])) {
		 include($_GET["p"]);
	} else {
		 include("home.html");
	}
?>
```

Il problema è che l'attaccante sceglie cosa è "incluso" (`include`):

Può includere un file sensibile:
```
...?p=/etc/passwd
```

Può usare `php://filter` [wrapper](https://www.php.net/manual/en/wrappers.php.php#wrappers.php.filter) per eseguire un <u>leak</u> dei file php:
```
...?p=php://filter/convert.base64-encode/resource=index.php
```

Può usare un [data wrapper](https://www.php.net/manual/en/wrappers.data.php) per <u>eseguire codice</u> (`allow_url_include` richiesto):
```
...?p=data:text/plain,<?php phpinfo();?>
```

## Deserialization attacks
L'**URL encoding** converte i caratteri in modo che possano essere trasmessi (e.g. `" "` diventa `%20`), alcuni caratteri sono **riservati** (e.g. `/ ? : + =`).

Gli oggetti in PHP possono essere **serializati** (oggetto a memoria) e **deserializati** (memoria ad oggetto) come in molti altri linguaggi ad oggetti.
Solitamente la **deserializazione** porta ad esecuzione di codice (input non fidato).

PHP riserva i metodi che cominciano con `__` per i [magic methods](https://www.php.net/manual/en/language.oop5.magic.php), ad esempio `__wakeup()` viene usato dopo la _deserializzazione_ ed è usato per eseguire codice che ripristina l'oggetto.

```php
class Example2 {
	private $hook;
		function __construct() {
		echo "ciao";
	}
	// some PHP code...
	function __wakeup() {
		// After deserialization
		// executes the code stored into $hook
		if (isset ($this->hook)) eval ($this->hook);
	}
}
// simulating the attack.
$user_data = unserialize(urldecode('O%3A8%3A%22Example2%22%3A1%3A%7Bs%3A14%3A%22%00Example2%00h
ook%22%3Bs%3A10%3A%22phpinfo%28%29%3B%22%3B%7D'));

// output
phpinfo()
PHP Version => 7.1.19
System => ...
Build Date => Aug 17 2018 18:02:33 ...
```

`phpinfo()` passato in `urldecode` può essere sostituito con codice arbitrario.

## SQL injection
Se l'input utente viene messo all'interno di una query senza alcun tipo di controllo esso verrà eseguito nella query finale:
```php
$query = "SELECT name, lastname, url FROM people WHERE lastname = '"
. $_POST['lastname']
. "'";
```

È possibile effettuare un leak dei dati presenti in tabella chiudendo `''` e aggiungendo codice SQL:
```sql
... WHERE lastname = '' OR 1 -- '

SELECT name, lastname, url FROM people WHERE lastname = '' OR 1 -- '
```
