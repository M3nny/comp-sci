In many optimization problems, **the goal state itself is the solution**, and not the path taken to reach it.

In **constraint satisfaction problems (CSPs)**, we can use search algorithms to keep a single current state, and try to improve it.

We can define them in terms of:
- **Variables**: entities that can have different values assigned to them, the set of assignments constitutes the search space
- **Domains**: set of values that can be assigned to a single variable
- **Constraints**: conditions of the valid assignments of values to variables, using also the context of other current assignments

>[!Example] N-queens
>Place $n$ queens on a $n\times n$ chessboard so that none can attack any other.
>This means that two queens cannot stay in the same row, column or diagonal.
>- **Variables**: every board position in the chessboard
>- **Domains**: occupied by queen (Q) or blank (B)
>- **Constraints**: two positions on a line (vertical, horizontal and diagonal) cannot be both Q

CSP problems are very general, and since they can be [[Teoria della NP completezza#Classe NPC|NP-Hard]], we cannot hope to find an optimal solution, but instead use local approaches.

Solving them involves some combination of:
- **Constraint propagation**: to eliminate values that cannot be part of the solution
- **Search**: to explore valid assignments

### Arc consistency
**Arc consistency** eliminates values from the domain of a variable, that can never be part of a consistent solution.

An **arc** represents a directed relationship between two variables that share a constraint.
For a constraint between $v_i$ and $v_j$, the arc $v_i\to v_j$, is _consistent_ if:
$$\forall x\in D_i, \exists y\in D_j:(x,y)\text{ satisfies }v_i\to v_j$$
We can achieve consistency on arc by deleting values from $D_i$ that fails this condition.

>[!Example] Graph coloring
>We want each node to have a different color from its neighbors.
>We check for each value in $D(v_i)$ if there is at least one value $D(v_j)$ that satisfies the constraint.
>![[Constraint satisfaction.svg|600]]

Note that constraint propagation alone does not guarantee a solution.
![[Arc consistent but no solutions.svg|200]]
>Arc consistent but no solution.

#### Backtracking and constraint propagation
We could also use backtracking to find states that satisfy the constraints.
![[Backtracking.png]]

A better solution would prune immediately the domains of unassigned variables connected by a constraint, removing values that are inconsistent with the current assignment.

**Forward checking** can be summarized as:
1. Assign $V_1=R$
2. For each unassigned variable connected $V_1$, remove $R$ from its domain
3. Continue untile all variables are assigned (found solution), or a domain becomes empty (backtrack)

In this approach we can also add a few heuristics:
- **Minimum Remaining Variable (MRV)**: pick the variable with the fewest legal values left in its domain, this variable is the hardest to satisfy, if it fails we find out early
- **Least Constraining Value (LCV)**: after picking the variable we need to decide which value try first, in this case we pick the value that rules out the fewest options for neighboring variables, in this way we give more flexibility for future assignments

