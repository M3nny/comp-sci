### Linguaggi integrati
Un esempio di linguaggio integrato è PL/pgSQL.

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

---
### Librerie esterne
**Vantaggi**:
- Costo ridotto di apprendimento
- Non è richiesto alcun pre-processore
- **SQL dinamico**: possibilità di selezionare la tabella usata nel `FROM` in base all'input utente (SQLJ non lo permette in quanto altrimenti impedirebbe il type-checking statico)
**Svantaggi**:
- Differenza di tipi fra linguaggio ospite e SQL (impedance mismatch)
- Assenza di controlli a compile time

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
