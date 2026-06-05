So far we've seen sketches with basic operations such as membership, frequency estimation and frequency moment.

But **modern databases use more complex queries**, such as joins and aggregations.
In this model, the database is a set of tables.

In standard [[Linguaggi relazionali#Algebra relazionale|relational algebra]], a table is modeled as a **set of tuples**, however our sketches will naturally handle tables as **multisets of tuples** (we allow duplicate rows).

$$\text{Table R}$$

| matriculation | course_code | module | evaluation |
| :-----------: | :---------: | :----: | :--------: |
|     12345     |     664     |   1    |     28     |
|     23315     |     664     |   2    |     18     |
|     10123     |     622     |   1    |     25     |
|     12345     |     622     |   1    |     25     |
|     12345     |     622     |   2    |     27     |
|     10123     |     664     |   1    |     25     |

$$\text{Table P}$$

| course_code | active |
| :---------: | :----: |
|     664     |   0    |
|     622     |   1    |
|     123     |   1    |

### Operators
**Projection**
Unary operator which _filters columns_ of the table.
- $\pi_{\text{matriculation,module}}(R)$: select two columns from $R$
- $\pi_\text{sum(evaluation)}(R)$: this will return us the aggregate value of the `evaluation` column

**Selection**
Unary operator which _filters rows_ of the table.
- $\sigma_\text{evaluation>25}(R)$ selects rows where `evaluation` is greater than $25$

**Cartesian product**
Binary relation that "glues" all $n\times m$ combinations of rows of two tables with $n$ and $m$ rows, respectively.

When combined together, these operators allow us to express complex queries, for example the average of the evaluations of a student on active courses is given by:
$$\pi_\text{average(evaluation)}(\sigma_\text{matriculation=12345, active=1, R.course\_code=P.course\_code}(R\times P))$$

In this chapter we'll see how to estimate the results of aggregations like this one.

### Estimating join sizes
Estimating the size of a join is crucial to a DBMS since it will select the appropriate optimization path based on the join size.

For an **equal join**, its size is given by counting every value $x$ that appears in both tables join column, in practice (frequency in R) $\times$ (frequency in $P$):
$$\text{join size}=\sum_{x\in R.course\_code,y\in P.course\_code, x=y}f_{x,R}f_{y,P}$$
where $f_{x,R}$ is the number of times value $x$ appears in the `course_code` column of $R$.

This is a **dot product** of two frequency vectors, and the [[20 - Second order frequency moments#Tug-of-war sketch|ToW sketch]] is exactly designed to estimate dot products efficiently.

We then build a ToW sketch for the `course_code` column of $R$:
$$sk(R)=\sum_{(x_1,x_2,x_3,x_4)\in R}h(x_2)=\sum_{x\in R.course\_code}f_{x,R}\cdot h(x)$$
>Here $x_2$ is the `course_code` value of a given row, and summing over all rows is the same as summing $f_{x,R}\cdot h(x)$ over distinct values.

We then build the same sketch for $P$, and the **estimator for the join** becomes $sk(R)\cdot sk(P)$.

**Proof of unbiasedness** (the expected value of the estimator is the true join size):
$$\begin{align}
&E\left[\left(\sum_{x\in R.\text{course\_code}} f_{x,R} \cdot h(x)\right) \cdot \left(\sum_{x\in P.\text{course\_code}} f_{x,P} \cdot h(x)\right)\right]\\
&= \left(\sum_{\substack{x\in R.\text{course\_code} \\ y\in P.\text{course\_code} \\ x=y}} f_{x,R}f_{y,P} \cdot \underset{1}{\boxed{E[h(x)\cdot h(y)]}}\right) + \left(\sum_{\substack{x\in R.\text{course\_code} \\ y\in P.\text{course\_code} \\ x\neq y}} f_{x,R}f_{x,P} \cdot \underset{0}{\boxed{E[h(x)\cdot h(y)]}}\right)\\
&= \sum_{\substack{x\in R.\text{course\_code} \\ y\in P.\text{course\_code} \\ x=y}} f_{x,R}f_{y,P}
\end{align}$$The expected value of the estimator is exactly the join size, hence it is unbiased, by repeating it many times and averaging, we can achieve an $(\epsilon,\delta)$-approximation.

If we build **ToW sketch of every column** of every table in the database, then we can **estimate the join size** between any two tables.

This sketch can easily be updated when new rows are added/deleted.
>This technique is used in real DBMS to understand which join algorithm to run.

### Estimating aggregations
Now we want to compute aggregate values over filtered rows, more generally we want to estimate:
$$\sum_{(x_1,x_2,x_3,x_4)\in R:x_1=x}x_4$$
That is, the sum of the `evaluatiuon` column ($4$th column $x_4$) for all rows where the `matriculation` value ($1$st column $x_1$) equals a given query value $x$.

The sketch is:
$$Q_1(R)=\sum_{(x_1,x_2,x_3,x_4)\in R}h(x_1)\cdot x_4$$
For each row, we multiply the hash of its `matriculation` value by its `evaluation` score, and sum everything up.

The sketch $Q_1(R)$ doesn't depend on the query value $x$, it's built from the table structure alone, so we can build it once and then query it for any student ID just by multiplying by $h(x)$.

**Proof of unbiasedness**
$$\begin{align}
&E[Q_1(R) \cdot h(x)] \\
&= E\left[\sum_{(x_1,\dots,x_4)\in R} h(x_1)h(x) \cdot x_4\right] \\
&= \sum_{\substack{(x_1,\dots,x_4)\in R \\ x_1=x}} \underset{1}{\boxed{E[h(x_1)h(x)]}} \cdot x_4 + \sum_{\substack{(x_1,\dots,x_4)\in R \\ x_1\neq x}} \underset{0}{\boxed{E[h(x_1)h(x)]}} \cdot x_4 \\
&= \sum_{\substack{(x_1,\dots,x_4)\in R \\ x_1=x}} x_4
\end{align}$$
The expected value is $\sum_{(x_1,\dots,x_4)\in R:x_1=x}x_4$, which is the true answer, hence the estimator is unbiased.

### Combining joins and aggregations
Now we merge the two estimates for the join and the aggregate using the following example: "what is the total evaluation score of student 12345, counting only active courses?"

We need one sketch per table, each hashing the relevant join/filter columns:
$$Q_2(R) = \sum_{(x_1,\dots,x_4)\in R} h(x_1)h(x_2) \cdot x_4$$
$$Q_2(P) = \sum_{(x_1,x_2)\in P} h(x_1) \cdot h(x_2)$$
- In $Q_2(R)$ we hash both the filter column $x_1$ and the join column $x_2$, and weight by the aggregated value $x_4$
- In $Q_2(P)$ we hash both $x_1$ and $x_2$

The estimator is the given by:
$$Q_2(R)\cdot Q_2(P)\cdot h(12345)\cdot h(1)$$
The two extra factors $h(12345)$ and $h(1)$ correspond to the specific filter values in the query.

The **intuition** is: when we expand the product of the two sketches, we get a sum over all pairs of rows $(r\in R,p\in P)$.
The hash functions cause cancellations, by the same logic as before, only pairs where $x_1^R=12345$ and $x_2^P=1$ and $x_2^R=x_1^P$ (the join condition) contribute in expectation.
All mismatches pairs cancel out, and what survives is exactly the sum of $x_4$ (`evaluation`) over the rows satisfying all conditions.

