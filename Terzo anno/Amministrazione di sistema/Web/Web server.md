Il **World Wide Web** è utilizzato per scambiare documenti ipertestuali multimediali sfruttando una grande WAN.

La prima versione del protocollo [[HTTP]] consentiva ad un client di richiedere <u>una singola risorsa al server durante una sessione</u> (connessione).

Nella versione HTTP 1.1 vennero rese possibili <u>più richieste per connessione</u>, inoltre in ogni richiesta bisogna specificare l'**hostname** dal quale si vuole ottenere la risorsa, ciò permette di implementare il **virtual hosting**, ovvero un server può ospitare più siti internet usando nomi diversi, sebbene questi corrispondano allo stesso IP.

## Web server
È un'applicazione software in grado di gestire le richieste di trasferimento di pagine web verso un client, l'interpretazione del codice inviato è fatta dal browser, che riceve un semplice file di testo.

### Apache HTTP server
Fino a poco tempo fa era l'unico in grado di gestire applicazioni di tutti i tipi, dunque è uno tra i più diffusi.

Modificando `httpd.conf` è possibile gestire l'accesso a più siti, inoltre è possibile ospitare diverse estensioni per pagine dinamiche come CGI.

Presenta un'**architettura modulare**, ad ogni richiesta del client vengono svolte funzioni specifiche da ogni modulo di cui è composto, quest'ultimi sono indipendenti tra loro e sono gestiti dal **core**.

Il **core** è un daemon che esegue un **ciclo di polling** che interroga le linee logiche da cui possono arrivare richieste (e.g. porta 80 e 443).
Esso poi passa la richiesta ai moduli in modo sequenziale, usando l'output del primo come input del secondo, generando un'illusione di **comunicazione orizzontale** tra i moduli.
![[Apache core.png|500]]

Da **Apache 2.0** viene esteso il design modulare con dei **Multi-Processing Modules (MPM)**, i quali sono responsabili di:
- Connessione alle porte di rete
- Accettazione delle richieste
- Invio ai figli per la gestione delle richieste

Diversi MPM utilizzano **strategie** diverse per gestire più richieste, esse sono essenzialmente:
- Prefork
- Worker
- Event

**mpm_prefork** esegue una serie di processi figlio per soddisfare le richieste, ed i processi figlio servono <u>solo una richiesta alla volta</u>, nel caso di richieste simultanee che superano il numero di processi creati, esse saranno accodate in attesa di un processo libero.

| Vantaggi                                                                                                       | Svantaggi                 |
| -------------------------------------------------------------------------------------------------------------- | ------------------------- |
| È più veloce dei MPM threaded, in quanto non crea nuovi thread, ma sfrutta una pool di processi pre esistenti. | Può richiedere molta RAM. |
| Viene usato per moduli non thread-safe come php.                                                               |                           |

**mpm_worker** utilizza i thread per migliorare la gestione delle richieste concorrenti.
In avvio vengono creati dei processi figlio i quali restano in attesa di richieste, e per ogni richiesta che ricevono creano un thread che si occupa di gestirla.

| Vantaggi                                                                     | Svantaggi                                           |
| ---------------------------------------------------------------------------- | --------------------------------------------------- |
| Le connessioni devono solo attendere un thread libero invece di un processo. | Non adatto alla gestione di moduli non thread-safe. |
| Richiede meno RAM.                                                           |                                                     |

**mpm_event**, è simile al modulo worker, con la differenza che utilizza un thread apposito per le connessioni _keep-alive_, in questo modo non vengono tenuti occupati thread che di fatto non fanno nulla, quando arriverà una richiesta effettiva, il thread che si occupa delle connessioni keep-alive creerà un nuovo thread per gestire la richiesta.


| Vantaggi                                                                                                              | Svantaggi                                           |
| --------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------- |
| Più performante del modulo worker.                                                                                    | Non adatto alla gestione di moduli non thread-safe. |
| Occupa meno RAM del modulo prefork.                                                                                   |                                                     |
| Ottimo per la gestione di accessi concorrenti di client che non sono necessariamente tutti attivi contemporaneamente. |                                                     |

#### Configurazione
Apache normalmente va a leggere i file che compongono il sito nella cartella `/var/www/html`, questa posizione viene determinata tramite clausola **DocumentRoot**.

I file di Apache nei derivati di debian, risiedono in `/etc/apache2`:
- `apache.conf`: file con la configurazione iniziale
- `ports.conf`: file con le porte di ascolto del daemon
- `conf-available`: directory con le configurazioni aggiuntive disponibili
- `conf-enabled`: directory con le configurazioni aggiuntive attive
- `mods-available`: directory che contiene i moduli disponibili
- `mods-enabled`: directory che contiene i moduli attivi
- `sites-available`: directory che contiene i siti disponibili
- `sites-enabled`: directory che contiene i siti attivi

La **configurazione di mpm-prefork** si trova in `/etc/apache2/mods-available/mpm-prefork.conf`, tra i suoi parametri si trova il numero di istanze Apache da lanciare all'avvio.

A seconda della dotazione hardware del server, si imposta un numero prefissato di processi di avvio, ad esempio se $N=20$:
```bash
<IfModule mpm_prefork_module>
	StartServers 20 # N
	MinSpareServers 20 # N
	MaxSpareServers 40 # 2 * N
	MaxRequestWorkers 150 # lasciato stare
	MaxConnectionsPerChild 0 # lasciato stare
</IfModule>
```

Visitare la pagina `http://<iplocale>` visualizzerà la pagina `index.html` se inserita all'interno di `/var/www/html`.

Alcuni **comandi utili**:
- `a2ensite <sito>`: abilita un sito web presente in `sites-available`
- `a2sissite <sito>`: disabilita un sito web presente in `sites-enabled`
- `a2enmod <modulo>`: abilita un modulo presente in `mods-available`
- `a2dismod <modulo>`: disabilita un modulo presente in `mods-enabled`
- `ab`: apache benchmark
- `apachectl configtest`: apache configuration test
- `service apache2 <start|restart|stop>`: avvia, riavvia e ferma apache
- `systemctl <start|restart|stop> apache2`: avvia, riavvia e ferma apache

---
### SSL
Il protocollo [[TLS]] permette una comunicazione sicura **end-to-end** su reti TCP/IP, fornendo autenticazione, integrità dei dati e cifratura operando nei livelli superiori del [[Livello di trasporto|livello di trasporto]].

Un server HTTPS si può realizzare tramite il modulo **ssl** di Apache, e risponderà sulla porta 443, anche per **apache tomcat** esiste una modalità ssl che risponde sulla porta 8443 al posto che sulla 8080 (default).

Per abilitare ssl su apache si procede con:
```bash
sudo a2enmod ssl
```

### Sistemi di monitoring
I web server possono essere usati per le **applicazioni di monitoring**, le quali possono essere classificate a seconda del livello in cui operano:
- **Basso livello**: controller dello stato di salute dei dischi, sensori di temperatura
- **A livello SO**: watchdog
- **Livello applicativo**: nagios permette di monitorare hardware e software di vari host e lo stato dei servizi ospitati, mrtg e cacti raccolgono statistiche e le interpretano sotto forma di grafici per descrivere l'uso del sistema

Il **Simple Network Management Protocol (SNMP)** viene usato per il monitoring dei dispositivi.
