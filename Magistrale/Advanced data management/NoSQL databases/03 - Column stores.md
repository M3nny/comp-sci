On a **row store** relational database, data rows are stored consecutively, whilst on a **column store** data _columns_ are store consecutively.

| ID  | Nome  |
| --- | ----- |
| 1   | Mario |
| 2   | Peach |

- Storage order in a row store: 1, Mario, 2, Peach
- Storage order in a column store: 1, 2, Mario, Peach

**Advantages of column stores**:
- _Only attributes that are needed are read from disk into main memory_, this is because a [[Memoria virtuale#Paginazione|page]] contains only values of a column
- Values in a column have the same attribute domain and can be _compressed better_ when stored consecutively
- Iterating and _aggregating over values in a column is faster_ (e.g. summing all the values in a column)
- _Adding new columns to a table is easy_, whilst on a row store it is necessary to append a new column value to each tuple

**Disadvantages of column stores**:
- _Reconstructing a row from the combination of several columns is costly_, because we have to identify which values in the column belong to the same tuple
- _Inserting a new record is costly_, because new values have to be added to all columns of the table

## Column compression
Columns may contain lots of repetitions of values, for this reason we can compress them easily with various algorithms.

##### Run-length encoding
- Count number of consecutive repetitions
- Format: (`value`, `start-row`, `run-length`)
![[Run-length encoding.png|400]]

##### Bit vector encoding
- For each value in the column we create a bit vector with one bit for each row, similarly to [[Feature selection & engineering#One-hot encoding|one-hot encoding]]
- Good for few distinct values (this reduces bit vectors)
![[Bit vector encoding.png|400]]

##### Dictionary encoding
- Replace values (or a sequence of values) with shorter placeholder
- Maintain dictionary to map placeholders back
![[Dictionary encoding.png|400]]

##### Frame reference encoding
- Choose the median value as the reference value
- For other values store the (fixed) offset, and if the value exceeds the offset, store the value itself as an exception
![[Frame reference encoding.png|400]]

##### Differential encoding
- Use the difference from the value in the preceding row as the offset
- Handle exceptions that are outside the offset range
![[Differential encoding.png|400]]

A popular data format is the [Apache parquet](https://parquet.apache.org/) format, which implements **column stripping** in order to transform nested data into columns.

