In this course we will discuss about the internals of [[Triennale/Secondo anno/Basi di dati/Mod. 1/Introduzione#DB e DBMS|DBMS]], and how a declarative query can be converted into an **execution plan** (see: [[Indici e viste materializzate#Analisi sugli indici|indexes analysis]]).

### What's a database system?
A **database system** is required to **manage huge amount of data** atomically, using various arrangements such as: tables, trees, graphs, or text documents.

This should be done in an **efficient**, **persistent** and **reliable** way (i.e. by keeping the integrity of the data and using backups).

In addition, it must be **consistent**, and thus it should not contain any contradictory data, and verify all the constraints defined by the user.

Other than that it should store data in a **non-redundant** way for **multiple users** concurrently, while also protecting confidential data with _views_.

#### Choosing a DBMS
Between all of the possible factors that may influence this choice, we may list the following:
- **Permanence in memory**
- **Storage engine**: enables various _access methods_ to the database, we can immagine it like an API to the DB (e.g. InnoDB, ISAM)
- **Data model engine**: transforms the query into an internal representation (i.e. execution plan), this component needs to know the specifics of the storage engine to do so

Other than the things mentioned above, we may also want to consider the _buffer management_, which is useful to avoid the retrieval of the same data in a short period of time.
>It may also hold a portion of the disk-resident tree (i.e. [[Alberi binari di ricerca#B_Alberi|B-trees]]) in RAM.

---
### Relational model
We already saw in the past that a database is a set of table names (i.e. **relation symbol**), where table headers determines the column names (i.e. **attribute names**) and their domain of values.

We recall that it is a good practice to [[Forme normali|normalize]] a relational database, this will enforce a good distribution of attributes among the tables, and will get rid of the following **anomalies**:
- **Insertion anomaly**: we need every attribute value when inserting a new record, but some may sill be unknown
- **Deletion anomaly**: when deleting a record, we may lose information that was needed in the database
- **Update anomaly**: when data is stored redundantly, values have to be changed in more than one record

Before proceeding we recall a few [[Linguaggi relazionali#Algebra relazionale|relational algebra operators]] such as: $\pi$ (projection), $\sigma$ (selection with condition), $\rho$ (renaming), $\cup, \textminus,\cap$ (union, difference, intersection), $\bowtie$ (natural join).

Relational algebra expression can be converted to algebra trees, which the database will convert into a lower level manipulation.

A relational database has to **manage transactions in a concurrent** environment, ensuring the possibility to rollback if something goes wrong, and for this reason it must adhere to the [[Triennale/Secondo anno/Basi di dati/Mod. 1/Introduzione#Transazioni|ACID properties]].

#### RDBMs weaknesses
This type of model assumes **horizontal and vertical homogeneity**, this means that every record has the same attributes, and each value of an attribute is inside a specified domain.

**Recursion is difficult to express**, for example let's think about friendship in a social network, it will be a table of users related to users of the same table, where friends of friend are retrieved with a join and so on.
>We'll find out that _window aggregates_ help in solving this problem, without crunching the rows like in the group by clause, since they slide over related rows adding context.
>In this way we can easily find, for example, shared friends.

RDBMs are **not well suited to handle a lot of updates**, this is due to the fact that to form an optimal execution plan, the database needs statistics, which are hard to calculate when a lot of updates happen.

**Transactions are both a blessing and a curse** to handle concurrently since they can be rolled back.
>The last 2 weaknesses lead to a **lower throughput**.

---
### NoSQL
For the reasons listed above, new database models emerged in order to handle data that is always changing with frequent updates over a huge number of interconnected servers.

This "new" movement does not strictly adhere to the ACID properties, but can cope with **schema evolution** or handle **schemaless** data, and can also support data distribution across servers by design.
>See [[NoSQL|NoSQL databases]].

Instead of ACID properties, nosql databases, follow the **BaSE** properties:
- **Ba (Basically Available)**: the system guarantees availability, by always responding to requests even if some nodes are down or out of sync
- **S (Soft state)**: the system's state can change over time, even without input, because data is replicated across nodes
- **E (Eventually consistent)**: given enough time without updates, all nodes will converge to the same consistent state

>[!Tip] ACID vs BaSE
>- **ACID** = Always correct, even if slow
>- **BASE** = Always available, even if temporarily inconsistent

