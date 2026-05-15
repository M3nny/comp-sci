**Graph mining** algorithms are difficult to be parallelized.
Traditional **divide et empira** is awkward since we wold have to partition the graph, and then later merge results that are themselves graphs.

The **vertex-centric model** avoids this by holding a _local state_, that is, each node exchanges messages with its neighbors and updates its state.
We repeat this until we reach **convergence** (nothing changes), this logic applies on every node simultaneously.

The tradeoff is that a node **can't see the global graph**, so algorithms may need many rounds to propagate information across the graph.

### Connected components
A **connected component** is a set of nodes where every node _can reach every other node_, the goal is to label each node with the ID of its component.

#### Pegasus algorithm
1. Each node $X$ sends its own component ID $X_\min$ to all its neighbors $N(X)$
2. Each node $X$ receives a list of component IDs and computes the minimum among them, this will be the new $X_\min$
3. Repeat until convergence

![[Label propagation.png|500]]

The **time complexity** of this algorithm is $O(d)$, where $d$ is the diameter of the graph.
>For example, node $3$ which is at the end of the $1-2-3$ chain, learns it's in component $1$ after $3$ iterations, one "hop" per round.

#### Hash-To-Min
Label propagation is slow on long chains since information travels one hop per iteration.

Instead of each node tracking just a single label, each node maintains a set of all the node IDs it currently knows about, which enables an **exponential information spreading**.

1. Each node $X$ computes $C_\min$ being the smallest node in $C(X)$
2. Each node $X$ sends $C(X)$ to node $C_\min$ and $C_\min$ to every other node in $C(X)$
3. Each node $X$ merges together all the node sets received, this is the new $C(X)$
4. Repeat until convergence
![[Hash-To-Min.png|800]]

### Counting triangles
A **triangle is a set of three nodes** that are all mutually connected, it's a measure of **how clustered** a graph is.

**Sequential algorithm**
For an undirected graph, we are going to _orient all edges_ from lower to higher ID, so the edge $<A,B>$ means that the id of $A$ is less than $B$.

Each nodes only _stores neighbors with a larger ID_, then for each edge $<U,V>$, count how many nodes appear in both $N(U)$ and $N(V)$, each such node forms a triangle with $U$ and $V$.

There are two natural choices into how we can **partition the work**:
 - Partition the input (edges)
 - Partition the output (triangles)

Input partitioning is tricky because counting a triangle requires knowing three edges that might end up on different machines, hence output partitioning is better.

#### Node hashing
We are going to partition triangles with the following approach:
1. Assign each node to one of $B$ buckets using a hash function $h$
2. Every triangle $<x,y,z>$ maps to a triple $<h(X),h(Y),h(Z)>$

This creates $B^3$ reducer slots, but _which edges does each reducer need_?
An edge $<X,Y>$ could partecipate in a triangle in three roles, $X$ could be the first, second or third vertex of the triple, so the map phase emits each edge three times, once for each role.
```python
def map(key: X, value: Y):
	for b in 0...B-1 :
		emit(<h(X), h(Y), b >, [X,Y])
		emit(<h(X), b, h(Y)>, [X,Y])
		emit(<b, h(X), h(Y)>, [X,Y])
		
def reduce(key: <b1, b2, b3>, values: [[X,Y], [U,V], ...]):
	triangles = count_triangles([[X,Y], [U,V], ...])
	emit(<b1, b2, b3>, triangles)
```

Each reducer $<b1,b2,b3>$ then has all the edges it needs to find every triangle where $h(X)=b1$, $h(Y)=b2$, $h(Z)=b3$, and it runs the sequential triangle-counting algorithm locally.

A **final aggregation** step sums the counts across all $B^3$ reducers.

