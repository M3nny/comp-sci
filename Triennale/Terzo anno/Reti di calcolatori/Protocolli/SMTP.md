Ci sono vari componenti coinvolti durante l'invio di una **e-mail**, tra cui:
- Il **client** di Alice che si occupa di formattare correttamente una mail
- Il **server** mail di Alice al quale arriverà la mail inviata dal client
- Il **server** mail di Bob al quale arriverà la mail inviata dal server mail di Alice
- Il **client** di Bob al quale arriverà la mail inviata dal suo server mail

>La lista di server intermediari può essere più lunga.

#### Formato delle e-mail
Le e-mail possiedono delle righe iniziali le quali compongono gli **header** come: `From, To, Date, CC, BCC, Subject`.

Altri header rilevanti sono:
- `Message-Id` rappresentante un ID univoco per una mail
- `In-reply-to` si riferisce ad un ID quando si risponde ad una mail
- `Received` utilizzato per il debugging dato che una mail può passare per più server, e ognuno di essi può aggiungere una riga in questo campo

Inizialmente per **body** del messaggio veniva utilizzato il codice ASCII, successivamente venne introdotto il **Multipurpose Internet Mail Extensions (MIME)** il quale specifica  come suddividere il body in modo da poter inviare molteplici file binari.

I campi principali di MIME sono:
- `MIME-Version` il quale indica la versione
- `Content-Type` (e.g. text/plain, image)
- `Content-Transfer-Encoding` (e.g. ASCII, UTF-8)

## SMTP
Il formato delle e-mail è rilevante in maggior parte solo agli estremi delle comunicazione, chiamati **Mail User Agent (MUA)**, tuttavia dobbiamo sapere come la comunicazione avviene tra i server intermedi, chiamati **Mail Transfer Agents (MTA)**, per questo abbiamo bisogno di due protocolli:
- **SMTP (Simple Mail Transfer Protocol)**
- **POP** e **IMAP**
![[SMTP.png]]

SMTP è un protocollo basato sul testo **connection-oriented (TCP)** con numero di porta predefinito **25**.

I **client invia comandi** composti da righe di caratteri ASCII terminati da `CLRF`, mentre il server **risponde con un codice** di errore/successo.

I **comandi del client** più usati sono:
- `EHLO`: usato per iniziare una comunicazione
- `MAIL FROM`: mittente
- `RCPT TO`: destinatario
- `DATA`: inizio del messaggio
- `QUIT`: fine del messaggio

I **codici del server** sono composti da tre cifre ed un commento:
- `2XX`: esito positivo
- `3XX`: esito positivo ma è stato richiesto più input
- `4XX`: esito negativo, ma il problema è temporaneo, riprova più tardi
- `5XX`: esito negativo, il problema è permanente, non riprovare

#### SMTP operations
Le seguenti non sono regole, ma configurazioni comuni.

Il MUA deve essere configurato con il nome di dominio di un server SMTP, successivamente esso utilizzerà dei comandi speciali per _autenticarsi_.

Inizialmente non esisteva l'**autenticazione** nel protocollo, poi sono state aggiunte delle estensioni per supportarla.
Un server che supporta l'autenticazione aggiungerà righe al campo `EHLO` della risposta, con una lista di metodi di autenticazione supportati (e.g. [[HMAC#CRAM-MD5|CRAM-MD5]]).

Quando un server SMTP riceverà una mail dal MUA, dovrà inoltrarla al SMTP server della destinazione con il dominio specificato nella sezione destinatario (supponiamo `gmail.com`), esso però non conosce il suo indirizzo IP, dovrà quindi eseguire una risoluzione DNS (usando `MX` type) per poi ottenere dei non-terminali, la risposta infatti potrebbe essere simile alla seguente:
```
dig gmail.com MX
;; ANSWER SECTION :
gmail.com. 2696 IN MX 5 gmail-smtp-in.l.google.com.
gmail.com. 2696 IN MX 20 alt2.gmail-smtp-in.l.google.com.
gmail.com. 2696 IN MX 30 alt3.gmail-smtp-in.l.google.com.
```

successivamente eseguirà un'altra query per ottenere l'indirizzo di `mail.b.com` tramite `gmail-smtp-in.l.google.com`.

Quando un MUA si **autentica** presso un MTA, il MTA consentirà il **relaying** (rilancio), ovvero esso potrà inoltrare le mail a qualsiasi dominio.

Senza autenticazione il MTA non consentirà il _relaying_, il client (MUA) potrà inviare mail solo se il dominio di destinazione è quello configurato nel MTA.

Chiamiamo un MTA che esegue l'autenticazione **Mail Submission Agent (MSA)**.

## POP
Una volta che la mail è arrivata all'ultimo MTA, essa è inviata ad un'altra entità chiamata **Mail Delivery Agent (MDA)**, la quale rende la mail disponibile a Bob con un protocollo dedicato.

Il protocollo **Post Office Protocol (POP)** viene utilizzato per inviare la mail dal MDA al MUA del destinatario.
Esso è un altro protocollo testuale con i suoi comandi, tra i più rilevanti troviamo:
- `USER`: username
- `PASS`: password
- `STAT`: chiede lo status della mailbox
- `LIST`: lista i nuovi messaggi
- `RETR i`: recupera l'i-esimo messaggio

Il server risponderà con `+OK` oppure con codici di errore simili a quelli di SMTP.
>Al giorno d'oggi anche POP supporta l'autenticazione.
