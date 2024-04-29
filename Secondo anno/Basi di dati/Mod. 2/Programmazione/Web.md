Il protocollo **HTTP** (Hyper Text Transfer Protocol) consente ad un **client** di richiedere risorse presenti su un **server**.

HTTP è **senza stato**, ovvero le richieste inviate sono **scorrelate** agli occhi del server, scelta fatta per assicurare **scalabilità**, questo comporta che non è possibile gestire la seconda richiesta con le conoscenze della prima richiesta e non è possibile capire che due richieste provengono dallo stesso client, **rendendo impossibile la sua autenticazione**, infatti **non fornisce nessuna forma di sicurezza**.

Distinguiamo tre principali **strati** di una applicazione web:
- **Presentation**: interfaccia grafica
	- **HTML**: per strutturare i contenuti all'interno di una pagina
	- **CSS**: per descrivere la presentazione dei contenuti strutturati
	- **JavaScript**: per rendere interattive le pagine
- **Logic**: processa comandi, e fa da cuscinetto tra presentation e lo strato _data_
- **Data**: contiene la base di dati, questo strato risponderà alle query fatte dallo strato _logic_

Una risorsa web è identificata da un **URL** (Uniform Resource Locator) formato da:
$$\underbrace{\text{schema://}}_\text{http/https}\overbrace{\text{hostname}}^\text{server ospitante}\underbrace{\text{[:port]}}_\text{servizio}\overbrace{\text{/path}}^\text{percorso}\underbrace{\text{[?query]}}_\text{lega parametri a valori}\overbrace{\text{[\#fragment]}}^\text{parte di pagina}$$

Tramite il **DNS** (Domain Name System) è possibile tradurre un **nome di dominio** in un indirizzo IP.

### HTTP
Una **richiesta HTTP** è strutturata come segue:
- **Metodo** e **risorsa** richiesta seguiti dalla versione del protocollo
- **Request headers**
- Linea vuota come separatore
- **Corpo** (opzionale)

Metodi comuni:
- **GET**: legge informazioni dal server
- **HEAD**: come GET, ma richiede solo header della risposta
- **POST**: invia una informazione al server
- **PUT**: carica un file sul server
- **DELETE**: rimuove un file dal server
- **OPTIONS**: richiede la lista dei metodi supportati

Una **risposta HTTP** è strutturata come segue:
- **Status code** e **messaggio**
- **Response headers**
- Linea vuota come separatore
- **Corpo** (opzionale)


| **Status code** | **Category** | **Example**                |
| --------------- | ------------ | -------------------------- |
| 2XX             | Success      | 200 OK                     |
| 3XX             | Redirection  | 301 Moved Permanently      |
| 4XX             | Client error | 404 Not Found              |
| 5XX             | Server error | 500 Internal Server Errror |

### Cookie
La **gestione dello stato** è delegata al **client** attraverso i **cookie** nella forma:
- `key = value`

Essi sono **generati dal server** ed **impostati nel client** attraverso una risposta HTTP con header `Set-Cookie`.
Saranno poi allegati dal client in ogni richiesta HTTP verso il server che li ha impostati.

I cookie si dicono **opachi** in quanto possono salvare un dato arbitrario la cui interpretazione è a carico dello sviluppatore che li ha concepiti.

### HTTPS
Variante **cifrata** di HTTP tramite l'utilizzo di **TLS** (Transport Layer Security), assicura la **confidenzialità** e **integrità** dei messaggi, inoltre consente l'**autorizzazione** del server attraverso dei **certificati**.
>HTTPS è _necessario_, ma _non sufficiente_ per la sicurezza di una applicazione web.

