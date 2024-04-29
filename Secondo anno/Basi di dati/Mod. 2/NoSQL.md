I database **NoSQL** (Not-Only SQL) consentono di rendere la rappresentazione della base di dati più flessibile, in base alle proprie esigenze, i principali modelli di NoSQL sono i seguenti:
- **Documentale**: vengono usati file JSON (e.g. [MongoDB](https://www.mongodb.com/))
- **Grafo**: i dati sono rappresentati attraverso nodi e relazioni (e.g. [Neo4j](https://neo4j.com/))
- **Key-Value**: vengono utilizzate delle semplici coppie chiave valore, solitamente come meccanismo di cache (e.g. [Redis](https://redis.io/))
- **Colonnari**: utilizzano grandi tabelle con tante colonne suddivise in famiglie chiamate anche supercolonne (e.g. [Cassandra](https://cassandra.apache.org/))

### DDBMS
Un **DDBMS** (Distributed DBMS) consente alla base dati di **scalare orizzontalmente**, ovvero alla crescita dell'utenza si utilizzano più macchine distribuite con potenza più o meno equivalente, al posto di un classico **RDBMS** che _normalmente_ scalerà solo **verticalmente**.

Inoltre il fatto di essere distribuito rende il sistema più **resiliente ai guasti**.

### Principi BaSE
A differenza dei principi [[Transazioni|ACID]] visti per i RDBMS, in NoSQL vengono utilizzati i principi **BaSE**:
- **Ba**: Basically Available
- **S**: Soft state
- **E**: Eventually consistent

### Denormalizzazione
Utilizzare NoSQL con una forte normalizzazione lo renderà molto lento, per questo bisogna denormalizzare i dati prima di inserirli nel modello scelto (e.g. documentale con JSON).

Essere **schemaless** consente una maggiore **scalabilità** e flessibilità verso il cliente finale dell'applicazione.
