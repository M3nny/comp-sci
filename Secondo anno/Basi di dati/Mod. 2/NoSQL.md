I database **NoSQL** (Not-Only SQL) consentono di rendere la rappresentazione della base di dati più flessibile, in base alle proprie esigenze, i principali modelli di NoSQL sono i seguenti:
- **Documentale**: vengono usati file JSON (e.g. [MongoDB](https://www.mongodb.com/))
- **Grafo**: i dati sono rappresentati attraverso nodi e relazioni (e.g. [Neo4j](https://neo4j.com/))
- **Key-Value**: vengono utilizzate delle semplici coppie chiave valore, solitamente come meccanismo di cache (e.g. [Redis](https://redis.io/))
- **Colonnari**: utilizzano grandi tabelle con tante colonne suddivise in famiglie chiamate anche supercolonne (e.g. [Cassandra](https://cassandra.apache.org/))

### DDBMS
Un **DDBMS** (Distributed DBMS) consente alla base dati di **scalare orizzontalmente**, ovvero alla crescita dell'utenza si utilizzano più macchine distribuite con potenza più o meno equivalente, al posto di un classico **RDBMS** che _normalmente_ scalerà solo **verticalmente**.

Inoltre il fatto di essere distribuito rende il sistema più **resiliente ai guasti**.

### Principi BaSE
A differenza delle **tre proprietà** viste per i RDBMS, in NoSQL vengono utilizzati i principi **BaSE**:
- **Ba**: Basically Available
- **S**: Soft state
- **E**: Eventually consistent

### Denormalizzazione
Utilizzare NoSQL con una forte normalizzazione lo renderà molto lento, per questo bisogna denormalizzare i dati prima di inserirli nel modello scelto (e.g. documentale con JSON).

Essere **schemaless** consente una maggiore **scalabilità** e flessibilità verso il cliente finale dell'applicazione.

---
## Neo4j
Neo4j utilizza grafi e consente di eseguire query sfruttando le connessioni fra i nodi.
Le query sono eseguite tramite **cyphers** i quali rappresentano tramite ASCII art le relazioni tra i vari nodi.

**Nodi**:
```cypher
() // nodo anonimo
(p) // variabile p, è una reference ad un nodo usato più tardi
(:Person) // nodo anonimo di tipo Person
(p:Person) // p è una reference ad un nodo di tipo Person
 
// p è una reference ad un nodo di tipo Actor e Director
(p:Actor:Director)
```

```cypher
// ritorna i nodi con label Movie con determinati attributi
MATCH (m:Movie {released: 2003, tagline: 'Free your mind'}) RETURN m
```

**Relazioni**:
```cypher
()---() // 2 nodi hanno qualche tipo di relazione
()-->() // il primo nodo ha una relazione con il secondo nodo
()<--() // il secondo nodo ha una relazione con il primo nodo

// query che sfrutta una relazione
MATCH (node1)-[:REL_TYPE]->(node2) RETURN node1, node2
```

```cypher
// ritorna le persone che seguono Arnold Schwarzenegger
MATCH (p1:Person)-[:FOLLOWS]->(p2:Person {name:'Arnold Schwarzenegger'})
RETURN p

// oppure con where
MATCH (p1:Person)-[:FOLLOWS]->(p2:Person)
WHERE p2.name =  'Arnold Schwarzenegger'
RETURN p

// ritorna le persone che hanno scritto il film
// ma non lo hanno diretto
MATCH (p:Person)-[:WROTE]->(m:Movie)
WHERE NOT exists( (p)-[:DIRECTED]->(m) )
RETURN DISTINCT p.name, m.title

// ritorna il titolo del film assieme ad una lista di persone
// che in quel film hanno: recitato, diretto, scritto
MATCH (p:Person)-[:ACTED_IN | DIRECTED | WROTE]->(m:Movie)
WHERE m.released = 2003
RETURN m.title, collect(p.name) AS credits
```

**Creazione di nodi**:
```cypher
// labels: Movie e Action
// properties: title: 'Batman Begins'
CREATE (m:Movie:Action {title: 'Batman Begins'})

MATCH (m:Movie)
WHERE m.title = 'Batman Begins'
SET m:Fantasy // nuova label

MATCH (m:Movie)
WHERE m.title = 'Batman Begins'
SET m.released = 2005, m.lengthInMinutes = 140 // nuove properties
```

**Creazione di relazioni**:
```cypher
MATCH (a:Person), (m:Movie)
WHERE a.name = 'Michael Caine' AND m.title = 'Batman Begins'
CREATE (a)-[:ACTED_IN]->(m)
RETURN a, m
```

**Cancellazione**:
Per cancellare una relazione è prima necessario cancellare tutti i nodi collegati da quella relazione, oppure usare la keyword `DETACH` al momento della cancellazione di un nodo.
```cypher
// cancellazione di un nodo
MATCH (p:Person)
WHERE p.name = 'Jane Doe'
DELETE p

// cancellazione di una relazione
MATCH (a:Person)-[rel:WROTE | DIRECTED]->(m:Movie)
WHERE a.name = 'Katie Holmes' AND m.title = 'Batman Begins'
DELETE rel

// distacco di un nodo e cancellazione
MATCH (p:Person)
WHERE p.name = 'Liam Neeson'
DETACH DELETE p
```

---
## Redis
Redis: **RE**mote **DI**ctionary **S**erver è un BBMS **chiave-valore** utilizzato come **cache** di vari servizi in quanto è veloce a recuperare i dati memorizzati al suo interno, infatti essi sono tutti memorizzati in una memoria a rapido accesso che utilizza molteplici tipi di chiavi, tra cui:
- Stringhe
- Bitmaps
- Hashes
- Lists
- Sets
- Geospatial indexes
- Hyperloglogs
- Streams
>Un valore associato ad una chiave non può essere più grande di 512 MB.

Tutte le istruzioni di redis seguono la seguente sintassi:
```
ISTRUZIONE key [args]
```

---
## Couchbase
Couchbase combina il modello **key-value** con quello **document** (json), memorizza i documenti in dei **buckets** che sono distribuiti in cluster facilmente scalabili orizzontalmente.
- **Bucket**: spazio virtuale in cui sono memorizzate le chiavi
- **Nodo**: un'istanza di couchbase server
- **Cluster**: una o più istanze di couchbase server che formano un sistema distribuito

Il sistema in caso di aggiunta di un nuovo nodo ribilancia i dati tra i vari nodi automaticamente.

Una esempio di query possibile è la seguente:
```sql
SELECT *
FROM `gamesim-sample` AS player JOIN `gamesim-sample` AS weapon
ON player.name = weapon.ownerId
WHERE player.jsonType = "player" AND weapon.jsonType = "item"
```

Couchbase inoltre utilizza un approccio **locale** assieme all'utilizzo del **cloud**, ciò vuol dire che in assenza di connessione, i dati sono salvati sul dispositivo, ed appena la connessione ad internet viene stabilita, il database locale si sincronizzerà con quello del cloud mantenendo le modifiche più recenti, ciò rappresenta una sicurezza anche in caso di smarrimento del dispositivo, in quanto i dati saranno comunque salvati nel cloud.

