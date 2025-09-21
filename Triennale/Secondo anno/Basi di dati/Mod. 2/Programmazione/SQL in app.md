### Linguaggi integrati
Un esempio di linguaggio integrato è **PL/pgSQL**, il quale viene anche usato per le funzioni dei [[Trigger|trigger]].

**Vantaggi**:
- Stesso livello di astrazione di SQL
- Supporto di controlli statici da parte del type system
**Svantaggi**:
- Costo elevato di apprendimento
- Tecnologie non standard
- Non adatti allo sviluppo di applicazioni complesse

---
### Linguaggi che incorporano SQL
Un esempio di linguaggio integrato è  [SQLJ](https://it.wikipedia.org/wiki/SQLJ), esso consente il **typing di connessioni**, ovvero può controllare la struttura del database in fase di compilazione controllando se le query scritte hanno tabelle/campi/tipi validi per il database usato.

**Vantaggi**:
-  Costo ridotto di apprendimento
- La sintassi SQL integrata abilita controlli statici
**Svantaggi**:
- Differenza di tipi fra linguaggio ospite e SQL (impedance mismatch)
- È richiesto un opportuno pre-processore

```java
String prov = "Venezia";
String sigla = "VE";
int numeroComuni = 44;

Class.forName(DatabaseDriver); // carica il driver
#sql context MyContext;
MyContext contesto = new MyContext(urlDb, user, pwd);

// uso le variabili java nelle query con :nome_var
#sql [contesto] INSERT INTO Province VALUES (:prov, :sigla, :numeroComuni);
```

>Pre-processore $\rightarrow$ Compilatore java $\rightarrow$ Runtime Java $\rightarrow$ DBMS.

---
### Librerie esterne
Un esempio è la libreria [JDBC](https://docs.oracle.com/javase/8/docs/technotes/guides/jdbc/) per Java. 
**Vantaggi**:
- Costo ridotto di apprendimento
- Non è richiesto alcun pre-processore
- **SQL dinamico**: possibilità di selezionare la tabella usata nel `FROM` in base all'input utente (SQLJ non lo permette in quanto altrimenti impedirebbe il type-checking statico)
**Svantaggi**:
- Differenza di tipi fra linguaggio ospite e SQL (impedance mismatch)
- Assenza di controlli a compile time

```java
String db = "jdbc:oracle:oci";
String u = "stefano";
String p = "secret";
Connection con = DriverManager.getConnection(db, u, p);

Statement stmt = con.createStatement();
String val = "VALUES (Venezia, VE, 44)"
String query = "INSERT INTO Province " + val;
stmt.executeQuery(query);
```

>Compilatore java $\rightarrow$ Runtime Java $\rightarrow$ DBMS.

---
### Object Relational Mapping (ORM)
Questo approccio consiste in librerie esterne in grado di fornire una interazione con il database usando un notazione **object-oriented**, in questo modo non si scrivono realmente query, e si delega il compito al servizio di ORM.

**Vantaggi**:
- Indipendenza dallo specifico DBMS sottostante
- Non richiede conoscenza approfondita di SQL
- Miglior supporto da parte del compilatore
- Astrazione da dettagli delle query (e.g. sanitizzazione delle query)
- Soluzione moderna al problema dell'impedance mismatch
**Svantaggi**:
- Tipicamente più lento delle query scritte ad hoc
- Poco adatto all'esecuzione di query complesse

```java
// JDBC
Statement stmt = con.createStatement();
String query = "SELECT * FROM Students WHERE id = 10"
ResultSet rs = stmt.executeQuery(query);
String name = rs.next().getString("Name");

// ORM
Student stud = db.getStudent(10);
String name = stud.getName();
```

