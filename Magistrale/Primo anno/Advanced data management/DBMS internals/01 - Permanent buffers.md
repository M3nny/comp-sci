Among the features of DBMSs we can highlight the fact they are able to provide a language to define a database **schema** as well as describing **restrictions on data** instances, offering also **a rich set of data structures** to store and retrieve large amount of data in persistent memory, while also protecting data with **transactions**.
![[RDBMS architecture.png|600]]

### Memory types
Various memory types are managed by the **persistent memory manager** which abstracts the physical memory devices (at the hardware level), providing a logical view of them.

The managed memory is usually a 2-level memory, where the main memory is fast and volatile, whilst the other one is slower and permanent.

In **flash memories** read and write operations are much faster compared to their hard-disk counterpart, however <u>overwriting data is slower than a regular write</u>, this is due to the fact that the _flash controller_ has to first copy the data from the interested block (set of pages), erase the entire block, and write the modified data back.
>Moreover, flash memories suffer from _wearing out_, thus losing reliability.

In **hard disks** spatial locality is much more important than in flash drives, since the seek time + latency is much greater than the transfer time, for this reason it is also important to make consecutive reads on the same [[Dischi#Caratteristiche dei dischi a testina mobile|cylinder]].

The **permanent memory manager** gives an abstraction (at a software level) of permanent memory as a set of databases, each of them as a set of logical files, hiding:
- Disk characteristics
- OS abstractions

### Buffer manager
The **buffer manager** manages the transfer of pages between volatile and persistent memory, making it transparent, in practice it handles:
- Request/release of a page
- Page modification

An [[Memoria virtuale#Mapping associativo|associative table]] is used to map permanent pages addresses, identified by a page identifier (PID) to temporary RAM addresses.

On a page request, if the page is already in the buffer, we only increment the **pin counter** which represent the number of application that are using that page.
If the page is not in the buffer, we retrieve it from the secondary storage, and put it in a free buffer cell.
If there aren't any free cells, we use a substitution policy, that usually releases pages with a pin count equal to 0, or least recently used (LRU) cells.

<u>In a page we store multiple records</u> that are composed by fields, we can view a record as: **prefix + fields**.
The prefix represents the number of components, the offset indicating when fields start, deletion flag, and other information.

---
## File structures
When talking about DBMSs internals, the term **file** indicates a group of pages that is used to store records.

There are 2 main ways to organize files.

**Serial organization**
This is the simplest way to store records, we just append them to the file in the order they arrive without using any index.

This works fine for smalls tables because we don't have to adjust "extra" data structures, but searching involves a full scan every time.
>They can also be called _heap files_, and they have nothing to do with the heap data structure, it is just a name for an unordered pile of records.

**Sequential organization**
Records are kept sorted by some key in order to retrieve the data faster, however keeping things in order is expensive, because we have to re-arrange data structures.

#### Sorting files
Sorting files is a difficult task, and the one of the most used algorithm in DBMSs is the **sort-merge**, which is an external [[Merge sort|merge sort]].

By **external** we mean that most of the data involved in the operations lives on the disk, since it cannot be fully loaded into the RAM.

It works as follows:
1. **Run generation**: read $B$ pages of unsorted data from disk into RAM, sort them and write the sorted chunk (called **run**) back to disk
2. **Fusion phase**: merge the sorted runs into fewer bigger sorted runs, like in the merge sort, but this time limited by memory, in this case we load into the RAM $Z=B-1$ pages, this is done because we can only fit $B$ pages in the RAM, but a page will be used for writing the result
3. **Repeat** until sorted

![[Sort-merge.png|500]]