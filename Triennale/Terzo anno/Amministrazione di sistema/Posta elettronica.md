Gli attori coinvolti in una comunicazione tramite email sono:
- **Mail User Agent (MUA)**: client di posta
- **Mail Submission Agent (MSA)**: passa i messaggi da MUA ad un MTA
- **Mail Transit Agent (MTA)**: riceve posta da un MSA o MTA e la inoltra verso un altro MTA oppure MDA
- **Mail Delivery Agent (MDA)** o **Local Delivery Agent (LDA)**: consegna la posta all'utente se la destinazione finale è nel sistema corrente
- **Mail Access Agent (MAA)**: permette di consultare/scaricare i messaggi
- **Mail Retrieval Agent (MRA)**: scarica la posta da un MAA e la rende disponibile in locale
>MSA è integrato nel MTA, mentre MRA è integrato nel MUA.

Ad eccezione delle interazione tra MRA e MAA, tutte le comunicazioni tra i vari attori avvengono tramite [[SMTP]].

![[Flusso di posta.png]]
1. Il mittente scrive una email usando un MUA
2. Il MUA invia la mail ad un MSA/MTA
3. Il MTA in questione controlla l'indirizzo di destinazione:
	- Se il dominio di destinazione è locale al MTA, la email viene inoltrata al LDA e la consegna termina (5)
	- Se il dominio di destinazione non è locale, e il MTA accetta ulteriori instradamenti (**relaying**), allora mette in coda di uscita il messaggio
4. Il MTA dopo aver estratto dalla coda il messaggio, controlla quale sia il record DNS [[Servizi di rete#DNS|MX]] associato al dominio e contatta l'MTA associato:
	- L'invio procede correttamente, allora l'MTA di destinazione procede dal punto (3)
	- Se l'MTA contattato non risponde, il messaggio torna in coda
	- Se l'MTA contattato rifiuta il messaggio oppure il messaggio è stato in coda troppo a lungo, viene mandato un messaggio al mittente di mancata consegna
5. Il messaggio si trova nella inbox del destinatario

Il **relay** non è sempre concesso, si accetta se la richiesta viene da un **host conosciuto** oppure da un **utente autenticato**.

>[!Attention]
>Il servizio di posta da solo non offre nessun tipo di garanzia che il messaggio arrivi e nessun tipo di autenticazione tra mittente e destinatario, per questo bisogna ricorrere a sistemi a livello applicativo.

| Attori        | Protocollo usato         |
| ------------- | ------------------------ |
| MUA $\to$ MTA | SMTP                     |
| MTA $\to$ MTA | SMTP                     |
| MTA $\to$ LDA | memoria condivisa o LMPT |
| MAA $\to$ MRA | POP o IMAP               |

- **LMPT (Local Mail Transfer Protocol)** è una versione semplificata di SMTP
- **IMAP (Internet Message Access Protocol)**: il server mantiene una copia delle mail
- **POP (Post Office Protocol)**: il server delega al dispositivo usato per la consultazione si provvedere al salvataggio, non mantiene copie delle mail

>In realtà i MRA hanno delle opzioni per POP che permettono di mantenere una copia dei messaggi sul server, IMAP rimane comunque preferibile per questo uso.

### Implementazioni di MTA
#### Sendmail
Il primo MTA a fare uso di SMTP, possiede molti bug e problemi di sicurezza, non è più usato.

#### Postfix
MTA di riferimento in ambiente Linux, permette diversi tipi di autenticazione e permette di interfacciarsi con altri sistemi di controllo della posta per evitare lo spam.

#### MS Exchange
Software studiato per agevolare la collaborazione online tra vari utenti, è stato introdotto da Microsoft ed è uno dei server mail più usati.

#### MAA Dovecot
Permette di usare i protocolli IMAP e POP, e supporta diversi formati di memorizzazione della posta (e.g. mbox e maildir), inoltra è possibile gestire la quota della posta per ogni utente e permette di autenticarsi tramite vari servizi.

---
### Formati mailbox
- **Mbox**: la casella di posta è un file di testo, i messaggi sono separati tramite dei tag uno dopo l'altro
- **Maildir**: la casella di posta è una directory, i messaggi sono singoli file contenuti al suo interno
- **D-box**: come _maildir_, ma i nomi dei file non cambiano, inoltre mantiene dei metadati (i.e. file indice di Dovecot) i quali possono essere riscostruiti automaticamente se danneggiati/persi
- **Mdbox**: messaggi multipli in un singolo file, e multipli file all'interno di una casella di posta, crash o perdita di alimentazione non possono corrompere o perdere dati

---
## SPAM
Pe **spam** si intendono messaggi non richiesti, simili tra loro, inviati da un grande sistema.

È possibile collocare le email indesiderate nelle seguenti categorie:
- **Hoax**: notizie false
- **Worm**: email mandate da virus
- **UCE (Unsolicited Commercial Email)**: spam dal contenuto commerciale
- **UBE (Unsolicited Bulk Email)**: email indesiderate inviate in grandi quantità

Lo <u>spam non è arginabile con una policy statica</u>, possiamo solo **filtrare** le email in ingresso cercando di evitare di scartare email legittime.

### Tecniche di difesa
#### Graylisting
Una email proveniente da un dominio sconosciuto viene inizialmente rifiutata per un numero preimpostato $n$ di volte, ad ogni rifiuto il mittente riprova l'invio, dopo $n$ tentativi la mail viene accettata ed il mittente viene inserito in una **whitelist**, le sue prossime mail verranno subito accettate.

Gli spammer solitamente non re-inoltrano le email se sono rifiutate, in quanto il loro scopo è mandarle a più MTA possibile nel minor tempo (vedi [[Tecniche anti-spam#Graylisting|graylisting]]).

Questa è una tecnica di base che non scarta email legittime, tuttavia questa implementazione di base non è sufficiente.

#### Realtime Blackhole List
Le **RBL** rappresentano delle [[Tecniche anti-spam#DNS Black Lists (DNSBL)|blacklist]] contenenti un elenco di IP che non sono autorizzati ad inviare email.

È difficile capire quali siano gli IP validi e quali no, sono basate su criteri personali scelti da terzi, l'unica cosa che si può fare è scegliere se usarle o meno, alcuni criteri per capire gli IP da bloccare sono:
- Tutti gli IP assegnati dinamicamente dai provider
- Tutti gli IP che inviano email senza passare da un email server ufficiale
- IP segnalati come spammer dagli utenti

Al momento solo [spamhaus](https://www.spamhaus.org/) è affidabile.

#### Sender Policy Framework
Lo standard definito come [[Tecniche anti-spam#Sender Policy Framework (SPF)|SPF]], non viene usato in senso stretto per combattere lo spam, ma viene applicato nella risoluzione dei nomi, tramite un record TXT infatti è possibile specificare quali sono gli IP o i nomi di dominio che possono inviare mail per il dominio stesso.

In pratica chi riceve una email può verificare, se il mittente è abilitato ad inviare email, tuttavia ci sono delle problematiche:
- Non tutti i domini hanno tale record TXT
- L'implementazione può essere difficoltosa per strutture complesse
- Gestione complicata del processo di forwarding delle email

#### Spamassassin
È un daemon che utilizza dei filtri basati su delle **euristiche** assegnando un punteggio di legittimità della mail in entrata sulla base di vari aspetti, tra cui:
- Linguaggio della email
- Presenza di tag html
- Presenza di parole chiave

A seconda del punteggio ottenuto e dalle soglie impostate, spamassassin può:
- Far passare la mail
- Segnalarla come spam all'utente
- Scartarla e salvarla in una directory apposita

La sua efficacia può migliorare in base alle mail ricevute in precedenza, tuttavia deve essere costantemente mantenuto ed inoltre non esistono configurazioni predefinite che vadano bene per tutti.

#### Controlli MTA
Un MTA può implementare dei controlli per ridurre lo spam sfruttando il formato del protocollo SMTP.

#### AMAVIS
È un super-daemon che filtra i contenuti delle mail interfacciandosi con altri sistemi di filtraggio di spam e virus.

In pratica è un interfaccia tra un MTA e altri sistemi come spamassassin, può essere usato per:
- Rilevare virus e spam
- Bloccare, etichettare e re-indirizzare email

Spesso viene utilizzato con **postfix** come MTA, **spamassassin** come classificatore per lo spam, **clamav** come antivirus, mentre amavis stesso li orchestra.

>[!Attention]
>Per un corretto funzionamento di un sistema di posta elettronica è necessario avere un servizio NTP, una corretta configurazione dei DNS, e dei certificati SSL, oltre alla **manutenzione costante** del database degli utenti e gruppi.

