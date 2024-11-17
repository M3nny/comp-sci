Molti protocolli studiati in questo corso sono stati aggiornati dalla loro prima introduzione, tuttavia alcuni funzionano ancora se implementati come definiti originariamente (e.g. [[Livello di trasporto#Connection-oriented service|TCP]]), questo non funziona però per altri protocolli, come quello [[SMTP]].

Ciò è dovuto all'implementazione di nuovi protocolli utilizzati per **limitare lo spam**, quindi un server SMTP senza tali protocolli configurati non consegnerà neanche una mail.

## Combattere lo spam
Uno spammer generalmente controlla un numero importante di _computer zombie_., i quali si connetteranno ad un server SMTP per provare a mandare in modo massiccio delle e-mail.

Se **lo spammer è un MUA**, è facile da rilevare dal suo MSA, questo perchè esso si connetterà, si autenticherà e manderà un grande numero di e-mail.

Se **lo spammer è un MTA**, allora è più difficile distinguere il buon traffico da quello cattivo, in quanto è normale che un MTA inoltri molte mail, per questo infatti i buoni MTA utilizzano varie tecniche per rilevare i MTA cattivi per poi rifiutare/aggiungere ritardo/limitare le loro e-mail.

Ci concentriamo ora sulle tecniche che riducono lo spam semplicemente basandosi sui protocolli di rete.

### Chiusura dei ripetitori
Avere un ripetitore (MTA in questo caso) che tutti possono usare è una cattiva pratica, in quanto un MTA potrebbe essere utilizzato dagli spammer, in più senza autenticazione possono cambiare liberamente il campo `From` della mail.

La tecnica basilare è l'introduzione degli [[SMTP#SMTP operations|MSA]].

### Fully Qualified Domain Name (FQDN) check
Il comando `HELO` dovrà trasportare un nome di dominio se il client (MTA) ne possiede uno, oppure direttamente un indirizzo IP se non lo possiede (MUA).

Gli MTA dopo aver risolto il nome di dominio (se è presente, altrimenti usano l'IP direttamente):
- Performano una [[DNS#Reverse DNS|query DNS inversa]] per tale IP e controlleranno se combacia con il dominio originale
- Controllano se l'IP che ha cominciato la connessione è lo stesso

Se una di questa condizioni non è soddisfatta, allora il server MTA potrebbe scartare la connessione.

### DNS Black Lists (DNSBL)
Varie organizzazioni mantengono una lista aggiornata di indirizzi IP i quali sono stati incolpati di generare messaggi spam, è nato quindi il protocollo DNSBL in modo da testare gli IP delle connessioni in entrata con tali liste.

Prima di consentire l'invio di una mail, il MTA eseguirà una query su un server DNSBL per testare se l'IP in entrata è presente all'interno di tale server, se è presente la mail viene scartata (vedi [spamhaus](https://www.spamhaus.org/)).

Gli spammer potrebbero noleggiare un grande set di IP e cambiarli contemporaneamente, <u>questo sistema infatti non funziona da solo</u>.

### Strict RFC compliance
Un server SMTP che si comporta bene aderisce allo standard SMTP, mentre uno spammer tende a non rispettare la parte di standard che potrebbe rallentare la sua attività.
#### Graylisting
Quando un MTA riceve un errore del tipo `4xx` dovrebbe riprova dopo un po' di tempo, cosa che gli spammer non faranno in quanto rallenterebbe la loro attività.

Il server MTA che utilizza il **graylisting** tiene una lista di IP conosciuti, quando una nuova connessione non presente nella lista è in entrata il server risponderà con un errore `4xx` e aggiungerà l'IP nella **whitelist**.
- Il client lecito riproverà più tardi
- Lo spammer non riproverà

Il server accetterà la seconda connessione se arriva all'interno dell'intervallo
1 minuto - 24 ore.
Dopo un periodo di inattività l'indirizzo IP sarà rimosso dalla _whitelist_.
>Questa tecnica non è costosa, tuttavia introduce un ritardo nella prima mail ricevuta da un nuovo IP.

Per gli MTA molto usati (e.g. google) questo non è un problema, ma ad esempio il MTA che un web server utilizza per mandare e-mail per recuperare la password sarà usato una volta ogni tanto (dipende dalla userbase) per questo la mail di recupero potrebbe arrivare in ritardo.

### Sender Policy Framework (SPF)
- `HELO`: identifica un dominio di un MTA, ovvero il server SMTP che fa da client
- `MAIL FROM`: non è necessariamente il mittente della mail. è il posto a cui mandare gli errori
- `FROM`: mittente

Un singolo client può legittimamente mandare mail utilizzando `FROM` con diversi domini.

Solitamente il provider del dominio fornisce anche vari indirizzi mail da poter utilizzare, l'MTA del provider manderà le mail impostando `FROM` al dominio noleggiato, e tanti altri domini registrati dallo stesso provider, per cui un MTA non può scartare una mail soltanto perchè il campo `FROM` è diverso da quello utilizzato in `HELO`, in questo caso infatti:
- `HELO`: dominio del provider
- `FROM`: dominio noleggiato

Ciò è sfruttato dagli spammer in quanto una mail è più credibile se viene da un dominio noto.

Consideriamo la seguente situazione:
Supponiamo che esista il sottodominio `computer-networks.dais.unive.it`, un attaccante potrebbe sfruttare una vulnerabilità per diventare _root_, e poi sfruttare la reputazione di `unive.it` per mandare mail spam.

**SPF** cerca di evitare la situazione precedente, esso è un protocollo che impedisce ad uno spammer di utilizzare i comandi `HELO, MAIL FROM` nel caso l'attaccante non possieda il dominio in questione.
>Non protegge il campo `FROM`.

Una _entry SPF_ (testuale) è associata al dominio dell'organizzazione che specifica quali sono gli indirizzi IP che possono inviare e-mail.

Le entry testuali non hanno un formato, tuttavia solitamente sono formate come segue: `unive.it. 86400 IN TXT “v=spf1 ip4:17.18.7.120 -all”`.
- Il protocollo ha versione $1$
- Un solo indirizzo IP può inviare e-mail
- Tutti gli altri sono proibiti

Quando un MTA riceverà una connessione in entrata farà quanto segue:
- Esegue una risoluzione DNS per il dominio specificato in `HELO` e `MAIL FROM`
- Verifica se una entry SPF esiste per tali domini
- Controlla se l'indirizzo IP da cui la connessione arriva è consentito

Nel caso non fosse consentito potrebbe scartare la mail oppure applicargli qualche policy.

La flag `-all` indica che solo gli indirizzi specificati possono essere usati, ciò vuol dire che è il dominio del mittente che decide chi può inviare e non il server MTA.

>[!Attention] Assunzione di base
>Si assume che l'attaccante che prende il controllo dell'infrastruttura di una organizzazione non possa modificare i record DNS.
>Questo è un altro motivo per cui il DNS di una organizzazione è critico sotto il punto di vista di sicurezza.

### DomainKeys Identified Mail (DKIM) Signatures
Dobbiamo trovare un modo per verificare gli altri campi del formato e-mail.

Ricordiamo che i campi sono generati dal MUA e passati in seguito ad un MTA, tuttavia solo un MSA potrà controllarne la veridicità.

DKIM è un protocollo che **si concentra sull'autenticazione** dell'associazione tra alcuni degli header/body ed un MTA valido.
Esso richiede ad un MSA di possedere una coppia di chiavi (pubblica/privata) che l'amministratore deve generare e configurare.

Quando un MUA contatta un MSA, esso di identifica, questo è l'unico momento in cui la mail può essere _certificata_, in quanto il prossimo MTA non sarà in grado di fornire un meccanismo di autenticazione.

Quando si usa DKIM, il MSA selezionerà alcune campi dalla mail e creerà una firma digitale, la firma digitale è applicata all'hash della mail e allegata all'header della mail.
Il prossimo MTA che riceve la mail sarà in grado di verificare la firma (assumendo che conosca la chiave pubblica di chi firma).

Un **header DKIM** è formato come segue:
- `v`: versione
- `a`: algoritmi crittografici usati per firma e hash
- `h`: header firmati
- `bh`: hash del body
- `b`: firma
- `d,s`: dominio e selector, necessari per recuperare la chiave pubblica

L'amministratore dell'MTA firmante dovrà pubblicare la sua chiave pubblica assieme alle altre informazioni del DNS in un record DNS testuale del tipo: `selector._domainkey.domain` (`_domainkey` è costante).

**Recap**
Possediamo ora:
- **FQDN check** per controllare che l'IP di un MTA corrisponda ad un dominio
- **SPF** che limita gli indirizzi IP autorizzati a mandare mail usando un certo dominio `MAIL FROM`
- **DKIM** il quale verifica che il campo `FROM` sia allineato con un certo dominio

$$\text{IP/dominio valido}\to \text{MTA autorizzato da SPF}\to \text{DKIM-validato FROM per un certo dominio}$$

Serve ancora un modo per far combaciare il dominio con `FROM` e prendere una decisione.

### DMARC
Cosa succede se un MTA riceve una mail ma:
- I controlli SPF e DKIM falliscono
- La policy SPF è ok, ma il dominio `HELO` è diverso da quello in `FROM`
- La firma DKIM è ok, ma il dominio `FROM` differisce da `MAIL FROM` oppure dal campo `d` di DKIM

Questo tipo di controllo è chiamato **alignment check**, il controllo basilare è che il campo `FROM` combaci almeno con uno tra:
- `d` nella firma DKIM
- Dominio verificato da SPF

Nel caso l'allineamento fallisca vogliamo che tutti i MTA si comportino allo stesso modo, ovvero sarà il proprietario del dominio del mittente a decidere per tutti gli MTA.

**Domain-based Message Authentication, Reporting, and Conformance (DMARC)**, è un protocollo che consente al proprietario del dominio di scegliere una policy che tutti gli altri MTA devono rispettare attraverso un ulteriore record testuale nel DNS, il quale dovrà essere accessibile a `_dmarc.domain.com`.

I campi più importanti di DMARC sono:
- `p` (policy): è un'azione da eseguire quando l'allineamento fallisce
- `rua`: mail a cui inviare casi di allineamento falliti

## Riassunto
![[Anti-spam.png]]

1. Alice usa SMTP con il suo MSA locale, vuole mandare una mail da `alice@a.com` a `bob.b.com`
2. Il MSA autentica alice con qualche credenziale
3. Il MTA in `a.com` usa SMTP per consegnare una mail utilizzando dei campi appropriati ed una firma DKIM ,l'IP di origine e `1.2.3.4`
4. Viene controllato se `1.2.3.4` compare all'interno di Spamhaus DNSBL attraverso la query `4.3.2.1.zen.spamhaus.com`
5. Il server MTA in `b.com` esegue una query DNS inversa per l'indirizzo IP del MTA client
6. Il server MTA risolve `mail.a.com` poi controlla se entrambe le risoluzioni sono consistenti
7. Il server MTA esegue una query presso il DNS `a.com` per una entry `TXT`, controlla che la policy SPF autorizzi `1.2.3.4` a mandare mail tramite `a.com`
8. Il server MTA esegue una query presso il DNS `a.com` per un sottodominio di `_domainkey`, riceve la chiave DKIM e controlla la firma digitale della mail
9. Il server MTA esegue una query presso `a.com` per un sottodominio `_dmarc`, controlla quali policy deve essere rispettate
10. Se tutte le policy sono rispettate, allora la mail viene accettata

