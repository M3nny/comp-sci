La gestione degli utenti non fa parte dello standard SQL, noi la vedremo sull'implementazione di postgresql.

- **Autenticazione**: identificare chi sta operando
- **Autorizzazione**: determinare i permessi

Il **controllo degli accessi** è il meccanismo con cui viene verificato chi richiede un'operazione.

Gli utenti vengono creati come segue:
```sql
CREATE USER nome WITH PASSWORD pwd [OPTION]
```

Su option è possibile specificare:
- `SUPERUSER`: l'utente ignora tutti i controlli di sicurezza
- `CREATEDB`: consente la creazione di nuovi database
- `VALID UNTIL`: specifica la durata massima della password

È possibile specificare un **metodo di autenticazione** tramite il file `pg_hba.conf` specificando la quadrupla:
1. **Tipo di connessione**
2. **Database**
3. **Utente**
4. **Indirizzo IP**

Per **autenticarsi** al giorno d'oggi vengono impiegati protocolli come [SCRAM](https://en.wikipedia.org/wiki/Salted_Challenge_Response_Authentication_Mechanism) il quale prevede l'utilizzo di hashing, salt e Certificate Authorities.

Dopo la fase di autenticazione si sa con chi si sta interagendo e si possono implementare politiche di **autorizzazione**, ecco alcune regole base:
1. Quando una tabella viene creata il suo creatore ne diventa **proprietario** e può farne ciò che desidera
2. Gli altri utenti possono accedere alla tabella solo con i **permessi** concessi su di essa
3. Il privilegio di eliminare una tabella o alterarne la definizione è esclusivo al proprietario

### Permessi
Vengono messi a disposizione vari permessi il cui nome rappresenta l'operazione eseguibile con tale permesso: `SELECT, INSERT, UPDATE, DELETE, TRIGGER` e `EXECUTE` il quale consente di creare funzioni e procedure.

È possibile inoltre dare un permesso più dettagliato, ad esempio `SELECT(X)` consente di eseguire tale operazione solo su certi attributi ed è più ristretto del permesso generale `SELECT`.

Quando un **trigger** viene attivato, esso viene eseguito con i permessi del suo creatore, indipendentemente da chi ha indotto l'attivazione, questo può portare a **scalate di privilegi**.

Quando una **funzione** viene dichiarata è possibile specificarne i permessi di esecuzione tramite le opzioni:
- `SECURITY INVOKER`: eseguita con i permessi del chiamante (Default)
- `SECURITY DEFINER`: eseguita con i permessi di chi l'ha definita

Il **proprietario di uno schema** può operare su tutto quello definito al suo interno e può **concedere** permessi ad altri utenti tramite:
```sql
GRANT listaPermessi ON elemento TO listaUtenti
```
>`ALL PRIVILEGES` indica tutti i permessi, `PUBLIC` autorizza tutti.

Oltre a _concedere_ privilegi, è anche possibile **delegare** l'opzione di dare tali privilegi anche ad altri utenti, tramite:
```sql
GRANT listaPermessi ON elemento TO listaUtenti WITH GRANT OPTION
```
È sempre possibile delegare una versione **meno generale** di un privilegio che si possiede.
>Un utente che ha ricevuto il permesso `SELECT WITH GRANT OPTION` può delegare `SELECT(X)`.

È possibile rappresentare i permessi tramite un **diagramma di autorizzazione** il quale è un grafo orientato, dove ogni nodo rappresenta: utente, permesso, assegnato non delegabile | assegnato delegabile | concesso in quanto proprietario.

I permessi assegnati possono essere **revocati** tramite:
```sql
REVOKE listaPermessi ON elemento FROM listaUtenti [OPTION]
```
 dove `OPTION` _deve_ essere una di queste due opzioni:
 - `CASCADE`: il permesso viene revocato anche a quelli che lo hanno ricevuto dal target della revoca
 - `RESTRICT`: fa fallire la revoca, se comporterebbe la revoca di ulteriori permessi come in _CASCADE_.
>Un utente può revocare solo permessi assegnati **direttamente** da se stesso ad eccezione di `CASCADE`.

È anche possibile **revocare la possibilità di delegare** l'assegnazione di un permesso tramite:
```sql
REVOKE GRANT OPTION FOR listaPermessi ON elemento FROM listaUtenti
```

Quando ad un utente che possiede sia un permesso generale, ed uno ristretto per lo stesso oggetto, se gli viene revocato quello meno generale non succede nulla a quello più generale, se accade il contrario però:
- Postgres revoca automaticamente anche quello meno generale
- Lo standard SQL suggerisce di lascare quello meno generale assegnato

### Ruoli
Al posto di assegnare permessi a mano, è possibile definire **ruoli** i quali rappresentano un collettore di permessi, questo tramite:
```sql
CREATE ROLE nomeRuolo
```

per attivare il ruolo (non è attivo di default):
```sql
SET ROLE nomeRuolo (già esistente)
```

con un ruolo è possibile effettuare operazioni simili a quelle per i permessi come `GRANT` e `REVOKE`.

In postgres non c'è una vera e propria differenza tra ruolo ed utente, infatti:
```sql
CREATE USER == CREATE ROLE WITH LOGIN
```
alcune specificità:
- L'opzione `CREATE ROLE` consente al ruolo di creare altri ruoli (può condurre a scalate di privilegi)
- I ruoli assegnati con `WITH ADMIN OPTION` possono essere delegati
- È possibile assegnare ruoli ad altri ruoli, creando così **ereditarietà** dei permessi

### Prevenire SQL injection
Per prevenire l'[SQL injection](https://it.wikipedia.org/wiki/SQL_injection) vengono usati principalmente due approcci:
- **Sanitizzazione**: analisi o trasformazione degli input per garantire l'assenza di contenuti malevoli
- **Encoding**: trasformazione degli input in qualcosa di non eseguibile

L'**escaping** è una della forme più semplici di encoding, il quale chiude le stringhe date in input:
```python
userName = escape(get_parameter($u))
pwd = escape(get_parameter($p))
statement = "
	SELECT *
	FROM users
	WHERE name = ’" + userName + "’ AND password = ’" + pwd + "’;
	"

# inserendo Mario e 'OR '1' = '1 otteniamo
SELECT *
FROM users
WHERE name = ’Mario’ AND password = ’’’ OR ’’1’’ = ’’1’;
```

Un **prepared statement** consiste in un'istruzione SQL con dei buchi (?) ai quali viene associato un tipo, in questo modo il dbms sarà in grado di assicurarsi che l'input sia effettivamente di quel tipo:
```python
userName = get_parameter($u)
pwd = get_parameter($p)
statement = "SELECT * FROM users WHERE name = ? AND password = ?;"

statement.setString(1,userName);
statement.setString(2,pwd);
```

quest'ultimo metodo non è sempre applicabile, infatti se l'input ha un tipo diverso da quelli base (e.g. una tabella) bisogna **sanitizzare** l'input ricevuto:
```python
table = get_parameter($t);

if (table == "Student" || table == "Teacher") {
	statement = "SELECT * FROM " + table;
} else {
	throw new Exception("Unexpected!");
}
```

>[!Tip]
>È sconsigliato applicare queste tecniche scrivendo codice "nuovo" di propria mano in quanto si potrebbero saltare dei casi limite, per questo è meglio usare librerie apposite già testate.

