Un **database** è una collezione di dati non necessariamente omogenei tra loro, ma tra loro correlati.

Il **DBMS** viene utilizzato per la gestione di uno o più database, esso definisce gli utenti e fornisce meccanismi di sicurezza.

Gli attori che operano con i database sono:
- **DataBase Administrator (DBA)**: gestisce gli accessi, predispone le tabelle ed effettua i backup
- **Programmatori**: scrivono le applicazioni che utilizzano i dati del DB
- **Utenti finali**: utilizzano le applicazioni che sfruttano il database
- **Sistemisti**: verificano il corretto funzionamento dei sistemi hardware e software su cui gira il DBMS gestendo anch'esso il backup e la ridondanza dei dati

### Tipi di database server
#### MySQL
È un **Relational DataBase Management System (RDBMS)** adatto per applicazioni web di piccole dimensioni, diventa poco performante con grandi query.

#### PostgreSQL
È un **Object Relational DataBase Management System (ORDBMS)** che supporta un modello di database **object oriented**, ovvero permette l'estensione del modello dei dati con tipi di dato e metodi personalizzati.

È molto sicuro e più veloce di MySQL.

#### Oracle
È un **ORDBMS**, dalla versione 10g utilizza il calcolo distribuito di tipo **grid computing**, ovvero il DBMS può essere visto come un'insieme di macchine eterogenee interconnesse tra loro per garantire scalabilità e condivisione.

Ha un sistema di gestione sviluppato tramite le **servlet** di Java.

Esiste una versione **express** che può essere utilizzata a scopi di sviluppo.

#### MS SQL Server
È un **RDBMS** di Microsoft, inizialmente usato per basi dati medio-piccolo, ma dalla versione 2000 viene usato anche per la gestione di grandi basi di dati.

È stato il primo database server con interfaccia grafica, inoltre esiste una versione **compact** per piccole applicazioni e sviluppo.

Anche in questo caso esiste una versione **express** gratuita utilizzabile dagli sviluppatori.

### Configurazione
Per configurare MySQL su distribuzioni basate su debian, è possibile utilizzare:
```
mysql_secure_installation
```

La configurazione si trova in `/etc/mysql/conf.d/mysql.cnf.`, all'interno del file è possibile specificare quali reti possono provare ad accedere a MySQL.
```
bind-address = 127.0.0.1 ; ammette solo localhost
```

Per la gestione è disponibile una console da riga di comando tramite `mysql -u root -p`.

```
// mostra i database
# mysql> show databases;

// crea un database
# mysql> create database books_db;

// delega dei permessi
# mysql> GRANT ALL privileges ON books_db.* TO
'librarian'@'127.0.0.1' IDENTIFIED BY
'semprelasolita'

# mysql> FLUSH PRIVILEGES;
```

Ora `root` e `librarian` possono fare qualsiasi cosa sul database `books_db`.

È possibile amministrare MySQL tramite **phpmyadmin** la quale è una UI realizzata in php che permette di effettuare operazioni con il database.
