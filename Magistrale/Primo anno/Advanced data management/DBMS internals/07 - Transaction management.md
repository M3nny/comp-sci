Concurrency control and recovery are among the most important functions provided by a DBMS.
For the programmer it is a sequential unit of work, for a DBMS it is a sequence of reads and writes bounded within a transaction context, which is terminated by either a **commit** or a **rollback**.
![[RDBMS architecture.png|500]]

It is the **transaction and recovery manager** which guarantees atomicity and durability.

- **Atomicity**: only commited transactions change the database, otherwise they rollback in case of failure, it should appear as a single read/write
- **Isolation**: when a transaction is executed concurrently with others, the final result must be the same as if it was executed alone
- **Durability**: the effect of commited transactions survive system and media failures, that is, comittment is an irrevocable act

![[Lifecycle of a transaction.png|400]]

A partial commit can be reverted by a rollback, a full commit means that the transaction is written to disk.

#### Kinds of failures
- **Transaction failure**: failure that does not damage the temporary and permanent memory
- **System failure**: crash of the system in which the contents of buffer and temporary memory are lost, but the contents of the permanent memory remain intact
- **Media failure**: a disaster in which the contents of the permanent memory are lost

### Transaction operations
The **tasks** of the transaction and recovery manager are:
- Execution of transaction operations, such as read, write, commit, abort
- Log and backup
- Execution of techniques that prevent data loss
- Execution of a restart command after a system failure

For simplicity we assume that a transaction reads/writes pages and not records.
- **Reading** requires the retrieval of the page from the disk to the buffer (if not already in the buffer)
- **Writing** only happens when the buffer manager decide to do it, until then, the changes are made in a in-memory copy, this means that if a system failure happens, the recovery manager must ensure that the effect of the operation is not lost

---
### Strategies for protection from failures
- **Database backup**: copy of the database on removable devices
- **Periodic checkpoints**: to reduce the cost of recovery
- **Undo-Redo management**: this requires logging, and ensures that the DBMS knows at which point of a transaction it were before an eventual failure

>Each log is identified through a **log sequence number**.

Periodically the DBMS creates a **checkpoint (CKP)** in order to minimize the time taken to recover in the event of a system crash.

There are three approaches to CKP:
- Commit consistent CKP: allows one transaction at a time
- Buffer consistent CKP: does not wait for transaction termination, when a page is updated, it flushes the result to disk (does not mean it is committed yet), ensuring that the disk and buffer have the same data
- Fuzzy CKP: flushes only some pages at once in order to not overwhelm the CPU, data in the buffer is not consistent with that in the disk

#### Undo and Redo procedures
Recovery algorithms differ in what, how (structure of the log) and when the log information is stored.

An **undo** is required when an update of some uncommitted transaction is recorded in the stable database.
The recovery algorithm must copy the before-image of the page from the log to the stable database.

A **redo** is required if a transaction is considered committed before all of its updates are installed in the stable database.
In case a failure occurs after the transaction commits, but before the updates are installed in the stable database, the recovery algorithm must redo updates by copying the after-image of the page from the log to the stable database.

Not every algorithm allows undo and redo.

As regard to _undo_, when an update of an active transaction is written to the DB?
- **Deferred update (NoUndo policy)**: an update cannot be written to the stable DB before the successful termination of the transaction
- **Immediate update (Undo policy)**: an update may be written to the stable DB before the transaction terminates

**Write Ahead Log**: if a new version of a page is written to the DB before the transaction terminates, then the old version of the page must be written in the log (in stable storage), before the change to the page is written to disk.

As regard to _redo_, when a transaction is considered terminated?
- **Deferred commit (NoRedo policy)**: a transaction is considered terminated with success only after the transfer of all the modified pages to the stable database
- **Immediate commit (Redo policy)**: a transaction is considered terminated with success, without the necessity of writing first all its updated to the permanent memory

**Commit rule**: the new version of the pages must be written in the log (in stable storage) before the transaction is considered committed.

A technique without undo and redo is called **shadow pages**, it works as follows: when a page is updated, a new table is created on disk, and operations are done on this table, then when a commit happens the root pointer is switched from the old original table (i.e. shadow table) to the new table, this does not need undo and redo since we are not modifying the original table directly.

To summarize:
In case of system failure, the transactions not terminated must be undone, whilst the transaction terminated must be redone.

#### Recovery
Recovery involves two phases: **rollback** and **rollforward**, we identify as $L_r$ the set of transactions to be redone, and with $L_u$ the set of transactions to be undone.

If a record is $(commit,T_i)$, $T_i$ is added to $L_r$.
If a record is an update of a transaction $T_i$, if $T_i\notin L_r$, the operation is undone and $T_i$ is added to $L_u$.

If a record is $(begin, T_i)$, $T_i$ is removed from $L_u$.
If a record is $(CKP, L)$, for each $T_i\in L, if T_i\notin L_r$, then $T_i$ is added to $L_u$, and if $L_u$ is not empty, the rollback phase continues after the checkpoint record until $L_u$ is emptied.

Rollforward from a checkpoint consists in re-doing all the operations of $T_i$ if $T_i\in L_r$.
When $(commit, T_i)$ is found, $T_i$ is removed from $L_r$, the phase terminates when $L_r$ is empty.
![[Recovery.png|700]]

---
### Concurrency
In real systems:
- Transaction granularity is at record (or field) level, not page level
- The database log does not record the entire page, but only the change itself, including before/after value (these logs are stored in memory before being written to disk)
- During the checkpoint, the pages updated in the buffer are not flushed to disk (fuzzy checkpoint)

An execution of a set of transaction is **serializable** if its effect is exactly the same as a serial execution of the committed transactions.

The **concurrency manager** establishes an order among the operations of a set of transactions in order to make them serializable.
Its correctness is proved by using the results of the _serializability theory_, which verifies the serializability of the executions generated by the concurrency manager.

_Simplification hypothesis_:
A transaction is a set of read and write operations, which terminates only with commit or abort.
We do not consider the insert and remove operations and a transaction can read of modify a single data just once.

#### Schedules
A **schedule** (or history) $H$ of a transaction $T$ is a set of operations such that:
- The operations of $H$ are those of the $T_i$
- $H$ preserves the ordering among the operations of a single transaction

Two schedules $H$ and $L$ are equivalent with respect to the conflicting operations if:
- $H$ and $L$ are defined over the same set of transactions
- They have in the same order the conflicting operations of committed transactions, also called **c-equivalent** (c stands for commit)

**Definitions**
- A schedule is serial if it represents a **serial** execution of $T$ is some order.
- A is **c-serializable** if it is c-equivalent to a serial schedule on $T$

#### Serialization graph
We can decide if a schedule is c-serializable by looking at its serialization graph.

Given a schedule $H$, its **serialization graph** $SG(H)$ is a direct graph where:
- _Nodes_ are the committed transaction of $H$
- An _arc_ from $T_i\to T_j$ is generated when:
	1. An operations from $T_i$ happens before an operation from $T_j$ in the order of the schedule
	2. These two operations **conflict**

Two operations **conflict** when:
- They're from different transactions
- They access the same data item ($x$ or $y$)
- At least once is a write
![[Serialization graph.png|500]]

A schedule is **c-serializable** iff the corresponding serialization graph is **acyclic**.
>$H2$ is serializable, whilst $H3$ isn't.

#### Concurrency control
The serialization graph is only used for checking _c-serializability_, it does not create the schedule itself (which in theory should always be c-serializable).

Concurrency control is usually done via **locking**, where if a transaction can't get the lock, it is _suspended on a wait queue_.

A popular scheduling algorithm is called **strict two-phase locking algorithm** and it involves the following rules:
1. **Lock before access**:
	- To read an object, acquire  a _shared_ lock $S$ first
	- To write/update an object, acquire and exclusive lock $X$ first
2. **No conflicting locks**: two transactions cannot hold conflicting locks simultaneously, that is, they cannot have an $X$ lock (not allowed: S+X, X+X)
3. **Hold until commit/abort**: a transaction must hold all its locks until it completes, without early releases (this is what it makes it "strict")

>The strictness of this algorithm ensures **isolation**.

A **deadlock** my happen when $(T_1)w[x]\to (T_2)w[y]\to c1\to c2$, this is because $T_1$ acquires the $X$ lock, which is needed by $T_2$ to continue the execution.

##### Deadlock detection
To avoid deadlocks, we use a **wait-for** graph:
- When $T_i$ requires a lock on an object already locked by $T_j$, then a new arc $T_i\to T_j$ is added to the graph, the arc is removed when $T_J$ releases the object needed by $T_i$

The system builds the graph and periodically checks for cycles, which indicates deadlocks, then a transaction inside the cycle is **aborted and restarted** to break the cycle.

##### Deadlock prevention
The idea in this case is to prevent cycle in the wait-for graph by aborting one transaction when a conflict occurs.

There are two strategies when a transaction $T_h$ requests a lock that conflicts with transaction $T_k$:
1. **Wait-die (non-preemptive)**:
	- If $T_h$ is older, then $T_h$ waits for $T_k$
	- If $T_h$ is younger, $T_h$ is aborted and restarted
2. **Wound-wait (preemptive)**:
	- If $T_h$ is older, then $T_k$ is aborted and restarted
	- If $T_h$ is younger, $T_h$ waits for $T_k$

When the youngest transaction is restarted, it keeps its old age timestamp in order to avoid starvation.

When a transaction releases a lock the list of locking transactions is updated, and the element at the head of the waiting list is considered.
If it can be reactivated, it is added to the list of locking transactions.
>This is repeated until there are transactions which can be reactivated.

### Concurrency in real systems
In real systems, objects are of different size and we try to reduce locks as much as possible, as well as to lock at the smallest possible level.

Lock towards the fields give more concurrency potential, but more complex lock management, whilst locks towards the db give less concurrency with simple management.

The strict 2Pl protocol has terrible performance on B-tree indexes: when updating an index a transaction should have an $X$ lock on the entire tree, hence new methods have been proposed, such as releasing the lock on the father node, when a child node is locked.
