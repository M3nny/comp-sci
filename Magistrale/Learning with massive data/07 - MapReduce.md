When dealing with massive data computations, we need **clusters**, and since nodes can fail, we must use a **distributed file system**.

### Hadoop Distributed File System (HDFS)
HDFS splits files into **chunks** (16-64 MB each), each one of them is replicated (2x-3x) across different machines, called **chunk servers**.

A **master node**, called _Name Node_ in HDFS tracks where everything lives (metadata) and it also might be replicated.

The **client** talks to the master node first, then it goes to talk directly with the machines holding the data after knowing where the data is stored.

**File operations** involve:
- Concurrent reads
- Single writer
- Write can only append

**Sequence files** are a persistent data structure for binary key-value pairs, where we can only write by using the `append()` method, and we can only read by using the `next()` method.
 
**Map files** are _sorted sequence files_ with an index to permit **lookup by key** so we can also use the `get()` method for reading.

### MapReduce programming model
The idea is to let the user define only two functions, that is `map` and `reduce`, where keys and values are user defined, and can be anything, the system will handle parallelism, failures and data movement by itself.

`map(key, value) -> list(key2, value2)`
Takes one piece of input and emits intermediate key-value pairs, there is one map function call for each key-value pair in the input.

`reduce(key2, list(values)) -> list(key3, value3)`
Takes all values sharing the same key and aggregates them into output, there is one reduce function call for each distinct key2.

|    Phase    |                                                                     What happens                                                                      |
| :---------: | :---------------------------------------------------------------------------------------------------------------------------------------------------: |
|   **Map**   |                                      Input is split across many mappers, each processing its chunk independently                                      |
| **Shuffle** |                                The system automatically groups all values by key and routes them to the right reducer                                 |
| **Reduce**  | Each reducer receives all values for its assigned keys and produces a portion of the final output (typically each reducer writes to a different file) |

As an introductory example, we count words in a corpus of documents:
```python
map(doc_name, text):
	for word in text:
		emit(word, 1)
		
reduce(word, [1, 1, 1, ...]):
    emit(word, sum of counts)
```

![[Magistrale/Learning with massive data/Images/MapReduce.png|600]]

The **master node** takes care of _coordination_:
- Schedules tasks as workers become available
- When a map task completes, it sends to the master, the location of its intermediate files, this info is pushed to the reducers by the master
- Pings workers periodically to detect failures

#### Failures
When a **map worker fails**, its tasks are reset to idle and reduce workers are notified when the task is rescheduled on another worker.

If a **reduce worker fails**, only in-progress tasks are reset to idle, and a different reducer takes the idle task over.

Finally, if the **master fails**, the task is aborted and the client is notified.

#### Optimizations
A rule of thumb is to make the <u>number of mapper much larger than the number of nodes in the cluster</u>, hence the number of reducers is smaller than the number of mappers.
This is because the system has a maximum capacity of parallel reducers, which are executed in waves.

**Combiners** act as a mini-reducer on the mapper machine before sending data over the network, in the case of word count, instead of sending ("the", 1) many times, we can directly send ("the", 1000), which reduces network traffic.

The **shuffle is purely automatic** we never write it, in fact the system uses a **partition function** (typically `hash(key) mod R`) to decide which reducer handles which key.

Slow machines, called **stragglers** can delay the whole job, near the end of a phase, the master spawns duplicate copies of slow tasks and uses whichever finishes first.

### Limitations of MapReduce
MapReduce is great for a lot of things, since we only have to override two functions generally speaking, and we get parallelism and fault tolerance for free.

But it is not great for everything:
- Every mapper writes to disk, which creates I/O overhead
- The shuffle is a bottleneck for data-heavy tasks
- Graph mining problems such as [[01 - PageRank|PageRank]] require to share a state, in this case the adjacency matrix, but it is not possible to broadcast it in this paradigm

### The ecosystem
- **Hadoop**: Java implementation of MapReduce + HDFS
- **Pig**: scripting language that compiles to MapReduce jobs
- **Hive**: SQL-like queries (HiveQL) compiled to MapReduce
- **Spark**: Keeps data in memory between steps using RDDs (Resilient Distributed Dataset), this is much faster for iterative jobs