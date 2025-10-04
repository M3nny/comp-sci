One general approach to solve a problem in the AI field is to reduce the given problem to one of _searching a graph_.
In order to use this approach, we must specify: **states**, **actions** and a **goal**, the objective is to find the correct actions that take us from an initial state to a goal state.

The search can be:
- **Uninformed (blind)**: we know only the neighbors of the current state
- **Informed (heuristic)**: we have the means to measure the progress towards the goal

It is possible to image the states as positions of trucks, an action can be "move a truck to a new position", and the goal might be to deliver every package in the given locations.
>We can turn graph problems into tree problems, by creating a [[Minimum Spanning Tree|MST]] to make it easier.

We can evaluate a search algorithm with the following criteria:
- **Completeness**: will it find a solution if one exists?
- **Optimality**: will it fin the "best" solution when more than one exist?
- **Temporal complexity**: how long will it take to find the solution?
- **Spatial complexity**: how much memory will it require?

Generally speaking, we can say that nodes are **visited**, when encountered for the first time and placed in the neighbors list, and **expanded** when subjected to the goal test, and its neighbors are inserted into the list.
>The type of search depends on how we extract and insert from the list.

### Breadth-First search
Considering a **[[Cos'è un albero#Alberi binari|full k-ary tree]]**, where the first goal is at depth $d$, the number of nodes to examine to reach depth $d$ is:
$$1+b+b^2+...+b^{d-1}=\frac{b^d-1}{b-1}$$
>Which is the result of a _geometric progression_.

The **average** number of nodes to explore at depth $d$  (considering that we visit at least a node at that depth):
$$\frac{1+b^d}{2}$$
![[Average nodes to explore BFS.png|500]]

Unlike a full tree search, which has a complexity of $\Theta(n)$, if we know from the start that the goal is at level $d$, the _time and memory complexity_ is $O(b^d)$.

### Depth-First search
Unlike the BFS that we previously saw, the DFS algorithm is **not complete** since it can get stuck in an infinite branch, and it is **not optimal**, since if the problem has more than one solution, it may find the deepest instead of the one at minimum depth.

Let's consider again a _full tree_, with a [[Visite#Ordine di visita nella DFS|pre-order]] search, in the best case the goal is at the far left, hence the number of nodes to visit is $d+1$, while in worst case (far right) it is:
$$1+...+b^d=\frac{b^{d+1}-1}{b-1}$$
So, in **average** it is:
$$\frac{b^{d+1}+bd+b-d-2}{2(b-1)}$$
Then the _time complexity_ is $O(b^d)$, and the _memory complexity_ to reach the goal node at level $d$ is $O(db)$.

### Iterative deepening search
This approach is used to fill the defects of the DFS, while also keeping a low memory usage.

In fact we can imagine this algorithm as a **iterative limited DFS**, this means that for each iteration $i$ we start from the root, make a DFS search until depth $i$, and repeat.

In this way this algorithm is **complete and optimal**, while not allocating a lot of memory, and we have a _time complexity_ of $O(b^d)$ while maintaining a _memory complexity_ of $O(db)$.

### Uniform cost search
Until now we evaluated the optimality in terms of steps (actions) taken to reach the goal, but there might be cases where we don't want to pick the best path based on the number of steps that it contains to reach the goal.

For example we may want to search in a weighted graph, in this case we can change the extraction strategy, and pick the path with the lowest cost from the root.

This algorithm can explore large trees of small steps before exploring path with large and potentially useful steps.

When all step costs are equal, it is similar to a BFS.
>Here by "step" we indicate the weighted edges of a graph.

