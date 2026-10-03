The goal is to locate a record with a given key quickly.

A file organization is called a **primary organization** if it determines the way the records are physically stored, otherwise it is called a **secondary organization**.

Usually hash or tree structures are primary, whilst indexes are secondary, although they can also be **static** or **dynamic** if the data structure adjusts gracefully under inserts and deletes.

### Hash methods
Keys are mapped into a page address by an [[Funzioni hash|hash function]], and if the key is a string, then it is first mapped into a number.

The set of all possible keys is larger than the records that will be actually stored, therefore **collisions** may happen.
![[Static organization.png|400]]

The hash function $H$ is **uniform** if its results are uniformly distributed in a given interval.

If the same result is produced for different keys $k_1,k_2$, then we have a **collision** and $k_1,k_2$ are **synonyms**.

Overflows increase the cost of the search operation, when well designed ($80\%$ page occupancy), we can assume that there are no overflows and so a record is retrieved with one page access.

There are two main ways to manage collisions:
- [[Indirizzamento aperto|Open addressing]]: the same hash table is used, if some key generates a collision, then it is re-hashed together with its fail count, if every cell of the table is filled (or most of them are), we need to re-hash everything into a bigger table
- [[Concatenamento|Chained overflow]]: every cell of the table maintains a pointer to a linked list used to store collisions

The **loading factor** $d$ influences the cost of operations, and mostly the _search time_, it is calculated as:
$$d=\frac{N}{M\cdot c}$$
- $N$: number of stored records
- $M$: number of addressable slots in the hash table
- $c$: number of records that can be stored in the same slot (with linked list)

For good results (i.e. search in one access) it is suggested to use have $d<0.7$ and $c>>10$.

Generally if we want to **import an hash table**, we build it in two phases:
1. Load the records which do not overflow
2. Load the records which overflow