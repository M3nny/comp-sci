Il **World Wide Web** è formato da vari componenti, tra cui:
- Uno schema per creare referenze a locazioni
- Un linguaggio per costruire pagine
- Un layer applicativo per recuperare pagine

Vediamo come un'applicazione funziona.
![[Applicazione web.png]]
1. Al browser ed al web server viene assegnata una porta dal layer TCP
2. Il browser esegue un comando HTTP, il quale incapsulato in un segmento TCP
3. Il segmento TCP viene incapsulato in un segmento IP
4. Il layer IP e TCP del server lo decapsulano
5. Il comando è ricevuto dal server web, esso lo elabora e risponde

## Universal Resource Identifiers (URI)
Un **URI** è una stringa che identifica una risorsa nel world wide web.
Un **Uniform Resource Locator (URL)** è un URI che provvede una locazione in cui recuperare una risorsa, contrariamente ad un **Uniform Resource Name (URN)** il quale indica solo il nome della risorsa.

Il formato di un URI/URL è il seguente:
$$\text{scheme://authority/path[?query][\#fragment]}$$
- **Scheme**: indica il significato dei campi che lo seguono, in partica indica il protocollo applicativo usato per recuperare il documento (e.g. `http, https, ftp, mailto`)
- **Authority**: indica il nome di dominio o IP del server presso cui recuperare il documento; prima del nome, separato da `@`, può essere specificato un nome utente ed eventualmente una password di chi sta richiedendo il documento; dopo il nome, separato da `:`, può essere specificato il numero di porta
- **Path**: percorso per il documento, se non viene specificato il server provvederà un documento di default
- **Query (opzionale)**: verrà analizzato dal server web
- **Fragment (opzionale)**: indica un punto specifico del documento

## HTML
Utilizziamo HTML per arricchire i documenti, essi infatti potranno contenere oltre a **header** e **body**, dei riferimenti ad altri documenti (tramite URL).
>Nel tag `<a>` viene espresso un URI tramite il parametro `href`.

#### Pagine dinamiche server-side
L'URL può puntare anche a file di linguaggi specifici, i quali sono eseguiti nel server, essi ritorneranno un file HTML al browser se interrogati, ciò è definito come **Common Gateway Interface (CGI)**.

I file **PHP** possono essere referenziati direttamente nell'URL, oppure incorporati all'interno di file HTML, il server potrà poi utilizzare le variabili fornite nell'URL, dopo il simbolo `?` per fornire una risposta personalizzata.

#### Pagine dinamiche client-side
Il codice per rendere le pagine dinamiche in questo caso è inoltrato assieme ai file HTML al browser, solitamente il linguaggio in questione è **Javascript**.

Le pagine dinamiche _server-side_ solitamente sono usate per eseguire un qualche tipo di query ad un database, per cui il server deve prestare attenzione a ciò che espone verso gli utenti, mentre le pagine dinamiche _client-side_ solitamente non necessitano neanche della connessione, e servono solo per fornire un'esperienza migliore.

#### Formattazione del documento
Il linguaggio **CSS** consente di applicare degli stili al documento HTML, esso può essere incorporato nei file HTML oppure in un file apposito e successivamente referenziato dal file HTML.

## HTTP
L'**Hyper Text Transfer Protocol (HTTP)** è un protocollo testuale il quale utilizza il servizio TCP, e opera sulla porta `80` di default.

Ogni **richiesta HTTP** è composta da tre parti:
- Un **metodo** che indica il tipo di richiesta, un **URI** e la versione del protocollo HTTP usata
- Un **header** usato per specificare parametri opzionali per la richiesta
- Un documento **MIME** opzionale allegato alla richiesta

La **risposta HTTP** mandata dal server contiene anch'essa tre parti:
- Una **status line**, che indica se la richiesta ha avuto successo o meno
- Un **header** che contiene informazioni aggiuntive riguardanti la risposta
- Un documento **MIME**

>Una linea vuota è usata per segnare la fine dell'header.

I **metodi HTTP** più usati sono:
- `GET`: recupera un documento dal server indicato da un URI
- `HEAD`: recupera solo l'header per un dato URI senza recuperarne il documento
- `POST`: usato dal client per inoltrare un documento al server come documento MIME

Gli **header HTTP** più usati sono:
- `User-agent`: identifica il browser
- `Referrer`: il sito precedente visitato dal client
- `Host`: il dominio del server richiesto
- `Server`: informazioni riguardanti il software utilizzato dal server

Gli **status code HTTP** possono essere interpretati come:
- `2xx`: risposta valida
- `3xx`: il documento non è più disponibile nel server
- `4xx`: errore del client
- `5xx`: errore del server

Inizialmente poteva essere impiegata una sola connessione TCP, per richiesta HTTP, oggi però una pagina web può comprendere varie parti, ognuna delle quali necessità una richiesta HTTP, è stato aggiunto il campo `Keep-Alive` all'header in modo da poter eseguire più di una richiesta in una sola connessione.

#### Stateless
È importante sapere che ogni richiesta HTTP è scorrelata dalle precedente, ovvero **stateless**, infatti il protocollo non mantiene alcuno stato tra le richieste, ciò però è diverso da dire che il software in esecuzione nel server non mantenga uno stato, infatti lo fa.

Il modo più semplice per mantenere uno stato è attraverso i **cookie**, essi sono un'informazione generata dal server ed inoltrata al client, il quale dovrà poi allegare i cookie impostati da tale server ad ogni richiesta verso esso.
I cookie possono essere gestiti tra client e server tramite gli header `Set-cookie` e `Cookie`.

I cookie possono essere distinti in base a come sono usati, ovvero:
- Gestione della sessione
- Personalizzazione
- Tracciamento

>[!Attention]
>Un cookie rubato o indovinato può portare all'**impersonificazione**.

#### Server proxy
Un **server proxy è una cache** che salva le pagine visitate per un certo tempo, esso risiede nella rete dell'utente.

I server si connetteranno al proxy, il quale poi richiederà le pagine al server e le memorizzerà per un po' di tempo, in questo modo se l'utente richiede la stessa pagina web, il proxy potrà fornirgliela subito in quanto l'aveva memorizzata.

Questo ha due benefici:
- Velocizza l'accesso alle pagine
- Salva banda di rete in download

Il proxy è configurato dall'amministratore e può essere acceduto dai terminali nella rete locale, esso rappresenta un vero e proprio MiTM, quindi deve essere maneggiato con cautela.

Introduciamo due nuovi header:
- `Cache-Control`: usata dal server per notificare che una pagina non può essere memorizzata (`no-store`), può essere memorizzata per un periodo di tempo (`max-age=10`), oppure può essere memorizzata per un tempo indefinito
- `If-Modified-Since`: se un client invia una richiesta con questo header, la pagina è ritornata dal server solo se è stata modificata, altrimenti si usa la cache

Un **reverse proxy** è un proxy locato in prossimità del server al posto che del client, in questo modo può **nascondere** il server reale, limitarne il suo uso di CPU e limitare il numero di query ai database.

### HTTP 2.0
Da questa versione, il protocollo **non è più testuale**, ora le richieste e risposte sono codificate in formato binario, questo perchè i protocolli testuali sono veloci da capire e debuggare, ma sono lenti, infatti il testo può essere compresso molto volendo.

Il contenuto della pagina è diviso in **frame**, i quali possono essere inoltrati parallelamente dal server al client, in questo modo non c'è più una sequenza precisa di richieste da fare da parte del client.
>Il server inoltrerà le pagine piccole prima di quelle grandi.

Con **Head-of-Line (HoL)** blocking ci si riferisce ad una situazione in cui dei task piccoli sono rallentati da task grandi.

- Da **HTML 2.0** è il server a decidere quali elementi renderizzare per primi, in questo modo può dare la priorità ai testi al posto di grandi immagini
- Da **HTTP 2.0** il server è autorizzato ad inoltrare contenuto al client ancora prima che esso lo richieda, in questo modo il server può risparmiare tempo se sa che un contenuto dovrà essere richiesto in un futuro prossimo




