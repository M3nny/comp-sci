Dynamic organizations avoid the re-computation of every value in case of overflow.

### Dynamic hashing
Dynamic hashing allows a hash file to **grow and shrink gracefully** as more records are inserted or deleted, avoiding full rehashing.

#### Virtual hashing
The main idea behind **virtual hashing** is that we have a **directory** that is like an index and tells us in which **bucket** the value is stored.

The following example has a _global depth (GD)_ of $2$, since $2$ bits are used to index directory.
```
Index   ->   Points to bucket
00      ->   B0
01      ->   B1
10      ->   B2
11      ->   B3
```

Each hashed value is **converted into a binary string**, and its last GD bits are taken and used to find the corresponding bucket using the directory indexes.

Each bucket has a _local depth (LD)_ which also uses bits, and at the beginning, LD=GD, but this changes as soon as there are not enough slots in the same bucket.

In fact when a bucket overflows, we **split the bucket**, this means increasing LD, so if LD was $1$ it could previously store $2^1$ records, but now after the split that bucket can store $2^2$ records, this also means that the last 2 bits are looked in order to assign the bucket.

For this reason when a bucket LD equals to the directory GD, we **double the directory size** in order to make indexing decisions based on "more last bits".
```
Directory (1 bit)
-----------------
0 -> B0[4, 12]
1 -> B1

Insert 20 -> B0 is full -> double the directory size

Directory (2 bit)
-----------------
00 -> B0[4, 12, 20]
01 -> B1
10 -> B0
11 -> B1
```

#### Linear hashing
This algorithm uses **two hashes**:
- $h(k)=k\mod n$
- $h'(k)=k\mod 2n$

The result of the hash indicates the number of the bucket that will store that record.
Moreover we use a **split pointer** $p$ which cycles linearly the buckets, in this case buckets have a specified capacity.

The hashing logic is:
1. Hash the key $k$ and retrieve result $r$
2. $r<p$? No -> use the $r$-th bucket, Yes -> hash using $h'(k)$
3. Overflow? (i.e. the bucket contains for items than its capacity)
	- Yes -> Add a bucket, re-hash every key in the bucket pointed by $p$ and move $p$ forward by one bucket

Let's say that the capacity of each bucket is $2$, they can exceed it temporarily.
```
Insert 3, 7:
B0[ ]   B1[3, 7]
p = 0

Insert 11 -> Overflow (nothing to re-hash):
B0[ ]   B1[3, 7, 11]   B2[ ]
p = 1

Insert 1 -> Overflow (re-hash):
B0[ ]    B1[1]    B2[ ]    B3[3,7,11]
p = 2
```

We have a **nominal max capacity**, but the idea is that records are eventually distributed linearly as overflows occurs.

>[!Attention] Hash methods issues
>Both of these approaches are difficult to evaluate in the worst case, and it is impossible to make range search.

---
## B-trees
A **B-tree** is a _balanced multi-way search tree_ designed for disk-based storage.
Each node contains:
- Up to $m-1$ sorted keys
- Up to $m$ children pointers

```
| k1 | k2 | k3 |
 /     |     \
c0    c1     c2
```
The keys separate ranges of child substrees, this means that values < $k1$ are in $c0$, whilst values between $k1$ and $k2$ are in $c1$.

Another key property is that all **leaves are at the same depth**, and generally speaking the height is small, thus all the major operations on the tree have a cost of $O(\log n)$ with small constants.

### B+ trees
Unlike the normal implementation, in **B+ trees** the **data is only stored in the leaves** and the internal nodes contain keys that are used for "routing" to the correct leaf.

In addition **leaves are linked in a linked list**, which is good for **range queries**, since we recall that entries in each node are sorted.

**Search**:
_Follow the pointers_ in the internal nodes until a leaf is reached, then look for the key in the leaf, this operation is done in $height$ time since the records are all in the leaves and we have to traverse all the tree levels.

**Insertion**:
_Search for the leaf_ where the key belongs and _insert it in sorted order_.

_If it overflows_ the number of keys in the leaf:
1. _Split the leaf in two leaves_, where the first one contains the first half, and the second leaf, the second half
2. _Copy the first key_ of the right leaf to the parent
If the parent overflows, repeat the same logic upward.
```
        [10]
       /    \
 [5 | 6]   [10 | 20]


Insert 12:
      [10 | 12]
    /     |      \
[5 | 6] [10 | 12] [20]
```

**Deletion**:
_Search the leaf_ containing the key and delete it.

_If the leaf has too few keys_ (i.e. $\lceil m/2\rceil$ where $m$ is the number of children of each node):
- _Rotate (borrow):_ borrow a key from a sibling and update the parent separator key
```
			[10 | 20]
		/       |       \
[3 | 5]        [10]     [20 | 30]


Delete 10 (borrow from right sibling):
	       [10 | 30]
		/      |    \
[3 | 5]       [20]   [30]

```

- _Merge_: there is no leaf to borrow from, since they all have the minimum keys inside, then merge the leaf with a sibling, this never causes an overflow since there wasn't a leaf that could lend a key
```
			[10 | 15 | 20]
	   /        |       |        \
 [5|6]     [10|12]   [15|18]   [20|25]
 
 Delete 12:
			 [10 | 20]
	   /        |        \
 [5|6]     [10|15|18]   [20|25]
```

>It is possible for the tree to shrink if the merge logic gets propagated up to the root, and the root is the only key to delete.

---
## Indexes
Indexes can be **clustered** (e.g. table itself) if they determine the physical order of data in the table, or **unclustered** if they are stored separately from the table and contain pointers to the actual rows that are not in order in the actual table.

We can further differentiate them in:
- **Dense**: if the index contains a reference to each specific record in the table (e.g. index on primary key)
- **Sparse**: if the index contains a reference to a block of records (e.g. index to an hypothetical age column)

**Inverted indexes** are a special kind of index that maps data to the records, this is particularly useful for text searches, for example we could have the following table:

| DocID | Content             |
| ----- | ------------------- |
| 1     | "Alice likes math"  |
| 2     | "Bob likes physics" |

The inverted index would be the following:

| Word    | DocID |
| ------- | ----- |
| Alice   | 1     |
| Bob     | 2     |
| likes   | 1,2   |
| math    | 1     |
| physics | 2     |

This is very efficient for text searches and "count" queries.

**Bitmap indexes** on the other hand are like the one-hot-encoding, in the sense that for a particular attribute of the table, another table is stored which has as many columns as the possible entries of the given attribute.

For this reason, bitmaps indexes are particularly useful when the cardinality (i.e. number of distinct values) of the attribute is low, for example:

| ID  | Gender |
| --- | ------ |
| 1   | M      |
| 2   | F      |

| Gender=M | Gender=F |
| -------- | -------- |
| 1        | 0        |
| 0        | 1        |
