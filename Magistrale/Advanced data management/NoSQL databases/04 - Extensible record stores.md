Extensible record stores, also knows as **column data stores**, group columns into **column families**, which should behave as follows:
- Group columns that are often accessed together
- Must be created before using them (like the `create table` in sql)
- Inside them, arbitrary columns can be added at runtime
- Theoretically we may have an unbounded number of columns
- Each row can have a different set of columns

A **column family** is a group of columns, like a relational table, but with the difference that each row is not predefined, and _each cell_ is composed of:
- **Column qualifier**: specifies the column in a column family (e.g. `Title`, `Author`), this can be seen as an attribute of a record in a relational table, since it can hold only one value, but with the difference that <u>it will store previous version of the value for a specified time</u>
- **Values**: the value inside a column qualifier
- **Row key**: identifies the row of the cell

![[Column family.png|500]]

The full key used to access a value is: `rowkey:columnFamily:columnQualifier`.

Most recent writes are collected in a main memory table, called **memtable** of fixed size, usually it is one per column family, this data is later flushed to the disk sorted by key, and these files once written are **read-only**, this means that the modification of a record must be simulated by appending a new record to the store.

The fact that the previous written data, will, at some point, be **immutable** is a core aspect of these databases, in this way it is possible to keep previous version of the data, and the concurrent reads/writes will be easier.
>Updating data in fact, is just an append operation specifying a new timestamp.

**Deleting data** consists in appending a **tombstone** value instead of the value that we wanted to delete, for example if we wanted to delete `Miller` (from the example above), we would have a new record `1002:BookInfo:Author->Tombstone` that indicates that the record has been deleted.

After a period of time the database runs a **compaction process** in order to remove from disk old and unwanted data, and cleanup space.
>If the value inside every column qualifier in a cell is set to tombstone, then the entire cell will be erased.

### File structure
The **downside** of this approach is that reading is complicated because the database has to identify the most recent records according to the timestamp.

The file is composed as follows:
- **Index**: small structure that allows to quickly locate which block contains a given row key
- **Trailer**: stores metadata (e.g. where the index is located, the bloom filter location)
- **Data**: contains one or more key-value pairs, each of them describes a cell

A **bloom filter** is stored in each file in order to determine the membership of a given record.

>[!Tip] Bloom filters
>A bloom filter uses a fixed array of bits set to $0$ or $1$, an input undergoes multiple hash function, each of them will write $1$ in a position in the array.
If we want to check the membership of an input, we just hash with the predefined hash function, if _not every_ mapped location in the array returns $1$ then the element is _surely_ not a member of the set.
>
>It is possible to have false positives because of [[Tabelle ad indirizzamento diretto#Tabelle hash|collisions]], but never false negatives.
>
>The bigger the fixed array is, less is the probability of collisions, but as elements are added to the set, the probability of collisions increases.
>
>This approach saves a lot of space, since we only store a binary array.


