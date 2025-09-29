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

