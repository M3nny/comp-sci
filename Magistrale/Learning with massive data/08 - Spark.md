[Apache Spark](https://spark.apache.org/) is a multi-language engine for executing data engineering, data science, and machine learning on single-node machines or clusters.
![[Spark architecture.png|500]]

### Core
Every Spark application has two kinds of actors:
- **Driver**: the orchestrator in which the main entrypoint lives, driver programs access Spark through a _SparkContext_ object which represents a connection to a computing cluster
- **Workers** (also called Executors): machines in the cluster that actually do the computation

The driver talks to the **cluster manager**, which talks to worker nodes, each of which has an executor running tasks and a cache for storing intermediate data.

#### Resilient Distributed Dataset
The RDD is the central concept in Spark:
- It looks like a list which is actually **spread across many machines**
- Each machine holds and processes only its **slice of the data**
- It's **fault tolerant**, which means that if one machine crashes, Spark can reconstruct the lost portion by replaying the operations that created it (it keeps a log of transformations rather than storing extra copies)
- It's **read-only**, so it is not possible to edit an RDD in place, instead we create new RDDs from old ones

>[!Info]
>We're going to use **PySpark** for the examples.

It is possible to create a basic RDD like this:
```python
data = list(range(20))
myrdd = sc.parallelize(data, numSlices=8)
```

We can specify how many slices to divide the data into, remembering that each partition maps to one task.

Spark operations come in two flavors:
- **Transformations** (e.g. `map`, `filter`) take an RDD and return a new RDD 
- **Actions** (e.g. `collect`, `count`, `reduce`) are what actually trigger computation

When we call an action, Spark looks at all the **queued transformations** (which are not executed immediately), optimizes them into an efficient **execution plan**, and runs everything in parallel.

This **lazy evaluation** lets Spark combine steps and avoid unnecessary computation.

### Transformations
These are all lazy operations that return a new RDD.

`map(func)`: applies a function to every element.
```python
# Squares every number
myrdd.map(lambda x: x * x)
# [0, 1, 4, 9, 16, 25, 36, 49, 64, ...]
```

`flatMap(func)`: like `map`, but the function can return _multiple_ values per input, and those are all flattened into a single RDD.
```python
# Each line -> list of words -> all merged
divina = [ "Nel mezzo del cammin di nostra vita",
		   "mi ritrovai per una selva oscura",
		   "ché la diritta via era smarrita."]
divinardd = sc.parallelize(divina)
divinardd.flatMap(lambda line: line.split())

print(words.collect())
# ['Nel', 'mezzo', 'del', 'cammin', 'di', 'nostra', 'vita', 'mi', 'ritrovai', 'per', 'una', 'selva', 'oscura', 'ch\xc3\xa9', 'la', 'diritta', 'via', 'era', 'smarrita.']
```

`filter(func)`: keeps only elements where the function returns True.
```python
# Keeps only even numbers
myrdd.filter(lambda x: x % 2 == 0)

print(even.collect())
# [0, 2, 4, 6, 8, 10, 12, 14, 16, 18]
```

`sample(withReplacement, fraction)`: randomly samples a fraction of the data, optionally allowing the same element to be picked more than once.
```python
# Sample 20% of the data without replacement
sample = myrdd.sample(False, 0.20)

print(sample.collect())
# [5, 11, 15, 19]
```

`distinct()`: removes duplicate elements (the result may not be in original order).
```python
distinct = sc.parallelize([1, 2, 2, 3, 3, 3, 4, 4, 4, 4]).distinct()

print(distinct.collect())
# [2, 4, 1, 3]
```

`union(other)`: combines both RDDs, keeping all duplicates.
```python
myrdd = sc.parallelize(range(20))
myrdd2 = sc.parallelize(range(10, 30))
union = myrdd.union(myrdd2)

print(union.collect())
# [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29]
```

`intersection(other)`: keeps only elements present in both.
```python
myrdd = sc.parallelize(range(20))
myrdd2 = sc.parallelize(range(10, 30))
intersection = myrdd.intersection(myrdd2)

print(intersection.collect())
# [10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
```

`subtract(other)`: keeps elements in the first RDD that are not in the second.
```python
myrdd = sc.parallelize(range(20))
myrdd2 = sc.parallelize(range(10, 30))
subtraction = myrdd.subtract(myrdd2)

print(subtraction.collect())
# [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
```

`cartesian(other)`: produces every possible pair between the two RDDs, if each has $N$ and $M$ elements, the result has $N\times M$ pairs.
```python
myrdd = sc.parallelize(range(20))
myrdd2 = sc.parallelize(range(10, 30))
cartesian = myrdd.cartesian(myrdd2)

print(cartesian.collect())
# [(0, 10), (0, 11), (0, 12), ..., (0, 28), (0, 29), (1, 10), (1, 11), (1, 12), ...
```

### Actions
We recall that **actions trigger actual computation** and return results to the driver (or write to storage).

`collect()`: pulls the entire RDD back to the driver as a list.

If the RDD is huge (which it often is), this means transferring all that data back to one machine.

`count()`: returns how many elements are in the RDD (computed in parallel)
```python
myrdd = sc.parallelize(range(20))
myrdd2 = sc.parallelize(range(10, 30))
print(myrdd.cartesian(myrdd2).count())

# 400
```

`countByValue()`: returns a dictionary of `{element: count}` for each distinct value.
```python
myrdd = sc.parallelize(range(20))
withflatmap = myrdd.flatMap(lambda x: (x * x, x * x * x))

print(withflatmap.countByValue()
# defaultdict(<class 'int'>, {0: 2, 1: 2, 4: 1, 8: 1, 9: 1, 27: 1, 16: 1, 64: 2, 25: 1, 125: 1, 36: 1, 216: 1, 49: 1, 343: 1, 512: 1, 81: 1, 729: 1, 100: 1, 1000: 1, 121: 1, 1331: 1, 144: 1, 1728: 1, 169: 1, 2197: 1, 196: 1, 2744: 1, 225: 1, 3375: 1, 256: 1, 4096: 1, 289: 1, 4913: 1, 324: 1, 5832: 1, 361: 1, 6859: 1})
```

`take(n)`: returns the first $n$ elements, this is not sorted, not random,  just whatever Spark happens to find first.
```python
myrdd = sc.parallelize(range(20))

print(myrdd.take(3))
# [0, 1, 2]
```

`top(n)`: returns the $n$ largest elements in descending order.
```python
myrdd = sc.parallelize(range(20))

print(myrdd.top(3))
# [19, 18, 17]
```

`reduce(func)`: aggregates the entire RDD into a single value using a combining function, which must be _associative and commutative_ (order-independent, e.g. summing all elements), because Spark computes partial results on each machine in parallel and then merges them.
```python
def sum(x, y): return x + y

print (myrdd.reduce(sum))
# 190
```

`aggregate(initialValue, mergeWithValue, mergeTwoAccumulators)`: a more powerful version of reduce for cases where the output type differs from the input type.

For example, computing an average (which requires tracking both a sum and a count) from an RDD of numbers:
- Start with `(0.0, 0.0)` as the accumulator `(sum, count)`
- Merge each element into the accumulator by adding the value and incrementing the count
- Merge two accumulators by adding both their sums and counts together
- At the end, divide sum by count
```python
# Empty accumulator (partial_sum, partial_count)
empty_acc = (0.0, 0.0)

# Merge by summing partial_sum and adding 1 to partial_count
def mergeValue(acc, value): return (acc[0] + value, acc[1] + 1)

# Merge by summing partial_sums and partial_counts
def mergeAccum(acc1, acc2): return (acc1[0] + acc2[0], acc1[1] + acc2[1])

# Spark aggregate
sum_and_count = myrdd.aggregate(empty_acc, mergeValue, mergeAccum)

print ("Average is", sum_and_count[0] / sum_and_count[1])
# Average is 9.5
```

`foreach(func)`: applies a function to each element, but unlike `map`, it doesn't produce a new RDD, it's used for side effects like printing, writing to a database, or updating counters.
```python
def f(x): print("This is x:", x)
myrdd.foreach(f)

# This is x: 10
# This is x: 0
# This is x: 6
# ...
```

### Working with key-value pairs RDD
Many real-world problems involve grouping data by some key.
Spark has special support for RDDs where each element is a `(key, value)` tuple.

```python
poems = sc.textFile("./poems.txt")
```

This creates an RDD where each element is one line of text from the file. Spark can also read from distributed file systems like HDFS.

A classic example would be to count how many times each word appears in a large text file.
```python
words = (
    poems.flatMap(lambda line: line.split()) # split lines into words
         .map(lambda word: (word, 1)) # tag each word with count 1
         .reduceByKey(lambda a, b: a + b) # sum counts per word
         .filter(lambda wc: wc[1] >= 600) # keep only frequent words
         .map(lambda wc: (wc[1], wc[0])) # flip to (count, word) for sorting
)

words.top(10)
# [(1246, 'the'), (920, 'to'), (826, 'and'), (812, 'of'), (742, 'in')]
```

`reduceByKey` is the main operation here, it grouped all values that shared the same key, then applied the reduce function to them.
>It's basically a parallel group-by-aggregate.

**Other key/value transformations**:
- `keys()` / `values()`: extract just keys or just values
- `mapValues(func)`: apply a function to values only, leaving keys unchanged
- `sortByKey()`: sort the RDD by key
- `groupByKey()`: group all values with the same key into a list (less efficient than `reduceByKey` when we just need aggregation)
- `join(other)` / `leftOuterJoin` / `rightOuterJoin`: database-style joins on matching keys
- `zipWithIndex()`: attach a sequential index `(0, 1, 2, …)` to each element

**Key/value actions:**
- `countByKey()`: count how many values are associated with each key
- `lookup(key)`: retrieve all values for a specific key
- `collectAsMap()`: pull the RDD to the driver as a dictionary

### RDD persistence
By default, every time we trigger an action, Spark **recomputes the entire lineage of transformations from scratch**, this means that if we call the same action multiple times on the same RDD, we're recomputing everything every time.

`persist()` tells Spark to save the results of that RDD after its first computation, so subsequent actions can reuse it directly.

```python
import math

numbers = sc.parallelize(range(10000000))    # a large vector
ss      = numbers.map(lambda x: math.sin(x)) # compute sin
aass    = ss.map(lambda x: math.asin(x))     # compute asin

aass.persist() # save intermediate results

aass.top(10) # take largest
aass.top(10) # take largest again
aass.top(10) # take largest again
```

In this case, at the first invocation of top, all the RDDs are computed from scratch.
At the second invocation, the `aass` RDD is cached, it doesn't need to be recomputed.

### Sharing variables between driver and workers
When Spark runs tasks on workers, each task gets its own copy of any variables it references, this is usually fine, but some scenarios need special handling.

**Accumulators**
Used when _workers need to write back_ to a shared counter or variable that the driver can read.

_Workers can only add to accumulators_ (never read them), while the driver can read the final value.

Let’s simulate a programs that sometimes fails, and we want to count the number of
failures.
```python
lines  = sc.parallelize(range(1000)) # some input lines
errors = sc.accumulator(0)           # 0 errors so far

def f(x):           # process x
	global errors   # errors are defined globally
	if x % 2 == 0:  # if something happens
		errors += 1 # one more error

lines.foreach(f)    # apply x to each input
print(errors.value) # print the number of errors
```

**Broadcast Variables**
Used when the driver has a large data structure (e.g. a lookup table) that every worker task needs a copy of.

Without broadcasting, Spark would send a separate copy for every single task.
Broadcast variables ensure _only one copy per machine_ is sent, then shared among all tasks on that machine.
```python
shared = sc.broadcast(range(1000, 2000)) # large shared data
tasks  = sc.parallelize([1, 2, 3, 4])    # four tasks

def f(x): # process x
	print("Element of shared data", shared.value[x])

tasks.foreach(f) # apply x to each input
```

Finally, the method `saveAsTextFile(path)` takes a directory path and Spark will output the content of an RDD into multiple files underneath that directory.

```python
words.saveAsTextFile("./out")
```
```bash
$ ls ./out
part-00000 part-00001

$ cat ./out/part*
(1246, u'the')
(826, u'and')
(742, u'in')
(920, u'to')
(812, u'of')
```
