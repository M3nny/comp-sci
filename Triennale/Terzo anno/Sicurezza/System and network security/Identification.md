La fase di **identificazione** consiste nel identificare _correttamente_ un utente o entità, è richiesta per applicare altre policy di sicurezza.

Uno schema di identificazione deve evitare l'**impersonificazione**, anche osservando identificazioni precedenti.
Il _verificatore_ **non deve riutilizzare una identificazione precedente** per impersonare il _richiedente_ con un altro verificatore a meno che non sia stato autorizzato.
>Le password appunto non devono essere uguali tra vari servizi.

Esistono varie **classi** di schemi di identificazione, si distinguono in base a cosa verificano:
- **Qualcosa di conosciuto**: controlla la conoscenza di un secreto
	Password, passphrase, PIN, chiave crittografica
- **Qualcosa di posseduto**: controlla il possesso di un dispositivo
	Carte di credito, OTP, smartphone
- **Qualcosa di inerente**: controlla le caratteristiche biometriche di un utente
	Firma cartacea, impronta digitale, riconoscimento facciale

---
## Password
L'identità affermata nella fase di login è controllata richiedendo una password segreta.

| Problema                                         | Soluzioni                                                                                          |
| ------------------------------------------------ | -------------------------------------------------------------------------------------------------- |
| La password viene intercettata (sniffed)         | Usare la password solo su canali criptati (e.g. https)                                             |
| La password viene indovinata da chi non dovrebbe | Disabilitare il servizio di autenticazione dopo _max_ tentativi.<br><br>Usare password complicate. |
| L'attaccante ha accesso alle password nel server | Usare funzioni di hashing unidirezionali                                                           |

### Funzioni hash unidirezionali
Una [[Funzioni hash|funzione hash]] computa efficientemente un valore di lunghezza fissa $h(x)=z$ chiamato **digest** da un valore $x$ di dimensione arbitraria.
>Collisioni sono possibili: $h(x1)=h(x2)$.

Trovare una pre-immagine di un digest ha un grande costo computazionale (infattibile in tempi accettabili).

Esistono varie funzioni di hashing, le più usate sono: **md5** (message-digest algorithm 5), e la famiglia degli **sha** (secure hash algorithm).
>È possibile trovare più collisioni in md5, e sha-1 in quanto producono un digest più corto rispetto ad altri algoritmi.

È possibile usare le funzioni hash per controllare l'integrità dei file:
```bash
sha256sum Assembly/* > checksum.txt
sha256sum -c checksum.txt
Assembly/checkPassword: OK
Assembly/count: OK
Assembly/count.c: OK
```

### Dictionary attacks
Immaginiamo che l'attaccante abbia recuperato un file con tutti gli hash delle password in un database, ora non è più vincolato al numero massimo di tentativi.

È possibile procedere con un attacco **brute force** computando hash digest di password semplici e vedere se qualcuno combacia, oppure usare una [rainbow table](https://en.wikipedia.org/wiki/Rainbow_table) e cercare semplicemente qualche $z$ contenuto nel file.

La precomputazione degli hash può essere evitata aggiungendo un **random salt** assieme all'hash il quale sarà diverso per ogni utente.
Al login verrà computato $h(x, s)$ al posto della singola password $x$ inserita dall'utente, dove $s$ è il salt salvato nel database.

Dato che il salt è salvato nell'ipotetico file ottenuto dall'attaccante, è sempre possibile usare un attacco brute-force contro password molto semplici (lento, ma fattibile).

### "Slow" hashes
Al posto di usare un singolo hash, gli hash vengono iterati più volte in modo da rallentare gli attacchi brute force.
```bash
mkpasswd cat -m sha-256 -S Lc5mF7Mm -R 5000
$5$rounds=5000$Lc5mF7Mm$5C1z.RDJY8wsRdxcjYq6HX8uWbk6clNf6xL99J4.uT2
```
- `$5`: indica che viene usato lo sha-256
- `$rounds=5000`: quante volte è stato iterato l'hash
- `$Lc5mF7Mm`: salt
- `$5C1z.RDJY8wsRdxcjYq6HX8uWbk6clNf6xL99J4.uT2`: digest

---

### Token-based authentication
In questa modalità di autenticazione si va a verificare qualcosa di **posseduto**.

Le **memory card** sono carte _passive_ con una memoria, e accoppiandole con un PIN le rendono difficili da duplicare.

Le **smart card** sono dei smart token con un chip integrato (e.g. usb token, piccoli oggetti portabili come il  telepass)

### Biometrics
1. Le caratteristiche dell'utente durante la fase di iscrizione sono estratte e salvate nel database
2. Le caratteristiche sono estratte e comparate con quelle memorizzate

Deve esserci un bilanciamento delicato tra falsi positivi e falsi negativi nel riconoscimento di dati biometrici in quanto non si vuole identificare una persona come un'altra, ma non si vuole nemmeno far fallire la verifica quando la persona è quella giusta.

Una violazione di un database biometrico ha un alto impatto in quanto i dati biometrici sono unici, appartengono ad un utente e non possono essere cambiati.

Negli ultimi anni si è sviluppata una nuova branca di studi per quanto riguarda la sicurezza: **adversarial machine learning**, la quale studia attacchi sugli algoritmi di machine learning, in particolare [questa ricerca](https://users.ece.cmu.edu/~lbauer/proj/advml.php) mostra come cambiando delle caratteristiche facciali di un utente, esso riesca ad essere identificato come un altro.