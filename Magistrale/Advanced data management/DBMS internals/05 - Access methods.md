Access methods are an _API that let's us ask the storage engine to perform certain operations_ (which depends on the storage we are using).

![[RDBMS architecture.png|600]]

We recall the architectural diagram of a DBMS, which is composed by **two main layers**.

The **relational engine**, used to understand SQL:
- **Query manager**: entry point for SQL commands
- **DDL manager**: handler data definition language (e.g. create table)
- **Catalog manager**: manager metadata (e.g. information about types)
- **Query optimizer**: finds the most efficient way to execute queries
- **Access plan manager**: creates the execution strategy
- **Transaction manager**: ensures ACID properties
- **Concurrency manager**: handles multiple users accessing data simultaneously

The **storage engine** used to actually work on data stored on disk:
- **Access method manager**: provides ways to read/write data (e.g. scans, index lookups)
- **Storage structures manager**: manages physical structures (e.g. heap files indexes)
- **Buffer manager**: manages memory cache for frequently accessed data
- **Permanent memory manager**: handles reading/writing to disk

#### Physical machine operators
Here we list some operators used to create and delete database structures along with their parameters.
- `create_db(path, db_name, trans_id)`
- `create_heap_file(path, db_name, heapfile_name, trans_id)`
- `create_index(path, db_name, index_name, heapfile_name, attribute, ord, unique, trans_id)`
- `drop_db(path, db_name, trans_id)`
- `drop_index(path, db_name, index_name, trans_id)`
- `drop_heap_file(path, db_name, heapfile_name, trans_id)`

#### Heap file operations
Operations that we can perform on heap files.
- `hf_open(path, db_name, hf_name, trans_id) -> heap_file*`
- `hf_close()`
- `hf_get_record(RID) -> record`
	Record IDentifier (RID): unique address for a record
- `hf_update_record(RID, field_num, new_field_val)`
- `hf_insert_record(record) -> RID`
- `hf_get_n_of_pages() -> int`
- `hf_get_n_of_records() -> int`

Access times are fast when the RID is known, otherwise a scan is needed.

#### Index operations
List of operations that we can perform on fast-lookup structures.
- `i_open(path, db_name, index_name, trans_id) -> index*`
- `i_close()`
- `i_is_key(value) -> bool`
- `i_delete_entry(entry)`
	An entry is defined as a (value, RID) pair
- `i_insert_entry(entry)`
- `i_get_n_key() -> int` returns the number of distinct key values
- `i_get_n_leaf() -> int` returns number of leaf nodes (useful for tree structures)
- `i_get_min() -> value` returns the smallest value in the index
- `i_get_max() -> value` returns the largest value in the index

An index maps values to record locations, for example it could map the value _Florence_ from the attribute _city_ to `[(page1, slot1), (page 2, slot 1))`.
In this case the value is used in more than one record.

Indexes need to stay synchronized with the heap file, this means that a insert/update/delete operation has to be done also in the index other than the heap file.

#### Heap file scan operations
These operations are used to iterate through all records in a heap file sequentially.
- `hfs_open(heapfile) -> scan_heap_file*` returns an handle that starts at the first record for the heap file
- `hfs_id_done() -> bool` returns true if you've seen all records
- `hfs_get_current() -> RID` returns the RID of the current record, does not move forward
- `hfs_next()` advances the iterator to the next record
- `hfs_close()` releases resources

The performance cost is $O(N)$, not ideal when there are indexes.

#### Index scan operations
These are the same operations that we saw for the heap scan (but done in the index), with the difference of the open operation:
- `is_open(index, first_key, last_key) -> scan_index*`
	Returns all records between first and last key (e.g. age 20 - 30)

#### Usage
Consider the following query.
```sql
SELECT Name
FROM Students
WHERE City = 'Pisa'
```

Without indexes we could execute the query in this way:
```java
HeapFile Students = hf_open("path", "db", "Students", trans_id);
ScanHeapFile iteratorHF = hfs_open(students);
while (!iterator.hfs_is_done()) {
	Rid rid = iteratorHF.hfs_get_current();
	Record theRecord = Students.hf_get_record(rid);
	if (theRecord.getField(4).("Pisa")) {
		System.out.println(theRecord.getField(1));
	}
	iteratorHF.hfs_next();
}
Students.hs_close();
iteratorHF.hfs_close();
```

instead, with indexes we would have:
```java
HeapFile Students = hf_open("path", "db", "Students", trans_id);
Index indexCity = i_open("path", "bd", "idxCity", trans_id);
ScanIndex iteratorIndex = is_open(indexCity, "Pisa", "Pisa");
while (!iteratorIndex.is_is_done()) {
	Rid rid = iteratorIndex.is_get_current().get_rid();
	Record theRecord = Students.hf_get_record(rid);
	System.out.println(theRecord.getField(1));
	iteratorIndex.is_next();
}
iteratorIndex.is_close();
Students.hs_close();
indexCity.i_close();
```

### Execution plan
Considering the following query.
```sql
SELECT PkEmp, EName
FROM EMployee, Department
WHERE FkDept = PkDept AND DLocation = 'Pisa' AND ESalary = 2000;
```
![[Execution plan.png]]

From left to right we have:
- **Logical tree**: straightforward translation of SQL
- **Logical transformation**: the optimizer applies rules to improve the query:
	1. Push selections down in order to filter as early as possible
	2. Push projections down in order to carry needed columns
	3. Reorder operations in order to do cheaper ones first
- **Access plan**: actual algorithm the database will executes