It is easy to think about relations as graphs, the example that stands out is social networks.

A **property graph** is a directed _multigraph_ (i.e. a graph that has a pair of nodes that is connected by more than one edge) that stores information (properties) in vertices and edges.

**Properties** are key-values pairs, and each node and edge has a predefined unique **id**.
In general the properties are _not typed_, _but they can be_ in order to give semantics to the stored data.

Edges have a predefined property key called **label**, it is possible to have multiple edges from node $A$ to $B$ only if they have a different label.
![[Graph properties.svg|500]]

### Storing graphs
We can store graphs as an [[Triennale/Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Matrice di adiacenza|adjacency matrix]], where rows and columns denote nodes, and the values in the matrix are binary, where $1$ indicates the presence of an edge between the nodes.

For undirected graphs, the matrix will be _symmetric_.

If it is a multigraph, then we would use integers (not only booleans) to store the number of edges from a node to the other.

| Advantages                      | Disadvantages                                                    |
| ------------------------------- | ---------------------------------------------------------------- |
| Quick lookup/insertion of edges | Storage intensive                                                |
|                                 | Determining adjacent nodes requires the lookup of the entire row |
|                                 | Insertion of new nodes is costly                                 |


Another approach is to use an [[Triennale/Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Matrice di incidenza|incidence matrix]], where rows represent nodes, and columns represent the existent edges.
In this case the values of the matrix are structured as follows:
$$a_{ij}=\begin{cases}-1&\text{outgoing arch}\\0&\text{missing arch}\\1&\text{incoming arch}\end{cases}$$

| Advantages                     | Disadvantages                                                                                       |
| ------------------------------ | --------------------------------------------------------------------------------------------------- |
| Only existing edges are stored | Storage intensive                                                                                   |
|                                | Determining adjacent nodes requires the lookup of the entire row and columns where row entry is $1$ |
|                                | Insertion of new nodes and edges is costly                                                          |


We can also store neighboring nodes in a [[Triennale/Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Lista di adiacenza|adjacency list]].

| Advantages                     | Disadvantages                                                      |
| ------------------------------ | ------------------------------------------------------------------ |
| Quick lookup                   | Checking the existence of a single edge requires traversal of list |
| No storage overhead            |                                                                    |
| Quick insertion of nodes/edges |                                                                    |

Or in a **incidence list**, that for each node stores its outgoing edges.

A popular database that uses graphs is [Neo4j](https://neo4j.com/).