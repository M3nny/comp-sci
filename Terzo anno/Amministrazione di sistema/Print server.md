Un **server di stampa** permette la gestione centralizzata di una o più stampanti, in pratica è un host che gestisce le code di stampa delle stampanti ad esso collegate.

Ogni stampante ormai è un <u>print server per sè stessa</u>, con più stampanti però è consigliabile un print server, il quale è collegato alle stampanti:
- **Direttamente**: se la stampante è a meno di due metri dal server
- **Via rete**: se la stampante è in una zona lontana dal print server
### Print server in Windows
In Windows esiste:
- **Windows client**: sistema di condivisione file e stampanti
- **Windows server**: comprende un print server che gestisce le varie stampanti connesse
>È necessario installare la regola **print service** da **service manager**.

### Print server in Linux
In **Linux** il server di stampa è gestito dal sistema **Common UNIX Printing System (CUPS)**, successore di **lpd**.

Il comportamento del server CUPS è gestito dal file `/etc/cups/cupsd.conf`, inoltre può essere configurato e monitorato dall'interfaccia web disponibile all'indirizzo `http://localhost:631/admin`.
>È necessario essere root o nel gruppo lpadmin.

L'interfaccia grafica mantiene le modifiche fatte in memoria per farne il push allo stop del servizio.

Alcuni comandi utili:
- `lpstat`: visualizza diverse informazioni sulle stampanti installate
- `lpq`: restituisce un elenco dei job (id) accodati in una stampante
- `lprm`: rimuove dei job tramite il loro id
- `lpr`: invia un job ad una coda di stampa
