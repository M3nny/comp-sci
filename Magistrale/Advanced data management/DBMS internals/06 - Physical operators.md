In this chapter we will assume:
- That relations are stored as heap files, or with B+ tree based primary organizations
- Indexes can be: unique/non-unique, clustered/unclustered

Everything that follows assumes these storage structures.

### Operators as iterators
A **physical query plan** is composed of operators where each operator is an iterator and returns a collection of records.
Each operator has a certain type and can return records in a certain order (or not).

For each operator, we estimate:
- $C$: cost
- $E_{rec}$: cardinality of the result

An iterator has these methods:
- `open`: initialize the process of getting data
- `isDone`: tests if the iterator has more data
- `next`: returns the next result record
- `reset`: re-initializes the iterator already opened
- `close`: performs cleanup operations

The following tree of operators can be represented using iterators.
![[Operators tree.png|400]]
```
Project({Name})
	NestedLoop(StudentNumber = Candidate)
		Project({Name, StudentNumber})
		    Filter(Province = 'PI')
			    TableScan(Students)
    Project({Candidate})
	    Filter(Course = 'BD' AND Voto = 30)
		    TableScan(Exams)
```

---
## Physical operators
Other than the already known [[Linguaggi relazionali#Algebra relazionale|relational algebra]], we recall the [[Linguaggi relazionali#Operazioni su multinsiemi|multiset operators]] which will be useful in this chapter.

### Tables
- $TableScan(R)$: returns records of $R$ in storage order
- $SortScan(R,\{A_i\})$: returns records of $R$ sorted in ascending order on attributes $\{A_i\}$
- $IndexScan(R,I)$: returns records of $R$ sorted in ascending order on index $I$'s attributes
- $IndexSequentialScan(R,I)$: for records stored with index sequential (B+ tree primary organization)

For all table operators, the cardinality is $E_{rec}=N_{rec}(R)$.

### Projection
- $Project(O, \{A_i\})$: projects records from $O$ over attributes $\{A_i\}$ without duplicate elimination
- $Distinct(O)$ returns records sorted without duplicates from sorted records of $O$
- $HashDistinct(O)$: returns de-duplicated records from $O$ (not sorted)
- $IndexOnlyScan(R, I, \{A_i\})$: returns records of the selected attributes using index $I$ on those attributes, avoiding scanning $R$

### Selection
- $Filter(O,\psi)$: returns records of $O$ matching condition $\psi$
- $IndexFilter(R,I,\psi)$: returns records of $R$ matching condition $\psi$ using index $I$ defined on attributes of $\psi$
- $IndexSequentialFIlter(R,O,\psi)$: for records stored with index sequential primary organization
- $IndexOnlyFilter(R,I,\{A_i\},\psi)$: returns sorted records using index $I$ avoiding access to $R$
- $OrIndexFilter(R,\{I_i,\psi_i\})$: uses indexes to find set _union_ of RID lists for each $\psi_i$ then retrieves records of $R$
- $AndIndexFilter(R,\{I_i,\psi_i\})$: uses indexes to find set _intersection_ of RID lists for each $\psi_i$ then retrieves records of $R$

### Grouping
- $GroupBy(O,\{A_i\},\{f_i\})$: groups records of $O$ on $\{A_i\}$ using aggregation functions $\{f_i\}$
	Returns records with the specified attributes and the aggregation functions used, also, records of $O$ must be sorted so group members are adjacent
- $HashGroupBy(O,\{A_i\},\{f_i\})$: partitions records using hash functions on $\{A_i\}$, results are not sorted
	After creating the partitions using an hash function, for each partition group records with a second hash function on grouping attributes, then when two records with the same grouping attributes are found, compute the aggregation function

### Join
Let's consider the following join query:
```sql
SELECT *
FROM Students S, Exams E
WHERE S.StudCode=E.Candidate
```

It is simple, but it must be carefully optimized, since the cartesian product between the sets might me large, we can't just filter its result.

The general join pattern with restrictions can be seen as it follows:
```
foreach r in R where CR do
	foreach s in S wher eCS do
		if r_i = s_j then
			add <r, s> to result
```

There are three main strategies for optimizing joins.

- $NestedLoop(O_E, O_I, \psi_j)$: works regardless of join condition
```
foreach r in O_E do
	foreach s in O_I do
		if ψ_j then add <r, s> to result
```

The **order of loops** matters as outer relation is more convenient the one with the longest tuples.

- $PageNestedLoop(O_E, O_I, \psi_j)$: same thing as the nested loop with the difference that we access alle the results in page before moving to the next one
```
foreach page p_r of O_E fo
	foreach page p_s of O_I do
		foreach r in p_r do
			foreach s in p_s fo
				if ψ_j then add <r, s> to result
```

- $IndexNestedLoop(O_E, O_I, \psi_j)$: if there is an index on the join column, exploit it in the inner loop
```
foreach r in O_E do
	foreach s in IndexFilter(S, I, S.A_j = r.A_i) do
		add <r, s> to result
```

- $MergeJoin(O_E, O_I, \psi_j)$: combines records from two sorted tables by reading though them simultaneously
- $HashJoin(O_E, O_I, \psi_j)$: choose the smaller table as the build input, then build a hash table on the join key, then scan the larger (probe) table and hash its join key to find matches (this only works in equi-join)

### Set and multiset
- $Union(O_E, O_I)$: requires the operands sorted and without duplicates
	Same for $Except, Intersection$

There is a union variant, that is $UnionAll$, which is simple and fast since it does not eliminate duplicates.

---
### Relational query optimization
The **goal of optimization** is to find an efficient plan to execute a query, where by **plan** we mean the tree of physical operators.

**Query analysis** involves type checking and user's access rights.
Other than that we have the **simplification of conditions (i.e. where clause)** with the elimination of contradictions and the use of De Morgan rules to eliminate the `not` clause before simple expressions.

Then we have query transformation, say for example the selection cascade:
$$\sigma_{\psi X}(\sigma_{\psi Y}(E))=\sigma_{\psi X\land\psi Y}(E)$$
In general _selection and projection are pushed below join_ if possible, and projections are grouped.
![[Query transformation.png|600]]

The `distinct` clause if possible is deleted, since it requires sorting, which is costly.
For this reason we use functional dependencies theory to discover if an interesting functional dependency can be inferred into the result of a query, in order to prove that the query result is already unique.


Same thing with the `group by` clause, it can be deleted if there is only a single group, since the DBMS can prove that all rows belong to a single group, hence that clause is not useful, since it would require sorting.

All the different kinds of subqueries (e.g. `ANY, ALL, IN`) can be transformed into `EXISTS` and `NOT EXISTS` clauses, furthermore, the latter clauses can be eliminated with the introduction of `JOIN`.

Another optimizations technique is called **view merging** which in other words, _inlines_ the view into the outer query instead of evaluating it separately, in this way the query can be globally optimized.
>Some views cannot be inlined, for example views that contains aggregates.

One last optimization technique is to **aggregate before joining**, since aggregation first may reduce by a lot, the number of rows after the join.

### Generation of the physical plan
For each query multiple alternatives of physical plans are generated, then after and **estimation of the costs**, the one with the lowest cost is chosen.

To estimate the cost it is necessary to calculate:
- Cost of the physical operator
- Size of the result
- The (possible) order of the result

In the case of single relation queries, the problem is quite simple, but the real problem arises with multiple relations, for this reason, heuristics and dynamic programming is used to explore the state space of possible sub-expression for the query.

Basically, this is an optimization problem, where we want to minimize the cost of the execution plan.
>PostgreSQL for example uses [[06 - Local search#Genetic algorithms|genetic algorithms]].


Heuristics are used because we don't want to spend more time optimizing the query than executing it directly without optimizations.