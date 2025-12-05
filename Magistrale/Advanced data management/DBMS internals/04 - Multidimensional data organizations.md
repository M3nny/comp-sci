The main goal when thinking about the **primary data organization** is how to make the position of where we store data, related to the content of the data itself, in other words, how to structure the data in order to make it easy to find for a specific query.

Whilst for **secondary data organization** we are thinking about how index entries go together in order to be able to answer queries efficiently.

In **multidimensional data** we may have queries that involve checking if a point/region is present, or if they are present inside a given region, the latter is called _spatial range query_.
>This is the equivalent of equality and range queries.

Other than these queries we also have **k-Nearest Neighbors** queries that find the $k$ points that are the closest ones with respect with another point.

### Linear order based organizations
Linear order based organizations try to **map multidimensional data into a one-dimensional order** in order to store it in a standard structure like a [[03 - Dynamic organizations#B+ trees|B+ tree]].

It works by defining a **total order** on the data, which may be:
- **Lexicographical order**: sort by $x$ coordinate, then by $y$ coordinate
- **Diagonal order**: sort by $x+y$
- **Space filling curves**: curves whose range reaches every point in a higher dimensional region while preserving spatial locality (e.g. [Peano curve](https://en.wikipedia.org/wiki/Peano_curve))
![[Peano curve.png|300]]

| Pros                                                              | Cons                                                                                                                       |
| ----------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- |
| Easy to implement, since it is possible to use a standard B+ tree | Poor performance for range or k-NN queries since nearby points in a multidimensional space may not be near when linearized |
| Efficient for checking if a specific point exists                 |                                                                                                                            |

### Space partitioning base organizations
In this case, instead of forcing data into a one-dimensional order, we **divide the space** itself into smaller **non-overlapping partitions**, and store each of them in a different page.

This has the major advantage of not having to scan (potentially) the whole space for a range search nearby a point.

It works by splitting recursively the space into regions, and as stated before, each region corresponds to a page of data in storage.
![[Space partitioning.png|300]]

Common structures are [quadtrees and octrees](https://en.wikipedia.org/wiki/Quadtree), both of them split the space with a fixed size recursively, the difference between them is that that first one is for 2D data (splits a rectangle in 4 regions), whilst the latter is for 3D data (splits a cube in 8 smaller cubes).
![[Quadtree.png|500]]
>Quadtree.

![[Octree.png|400]]
>Octree.

Another useful implementation is the **KDB-tree** which instead of having fixed splits, it maintains a balanced tree by splitting based on data location.

| Pros                                                                             | Cons                                         |
| -------------------------------------------------------------------------------- | -------------------------------------------- |
| Works well for range and spatial queries                                         | Can become unbalanced if data is skewed      |
| Partitions don't overlap, in this way there is no duplicate checking for queries | Complex to maintain with inserts and deletes |

### Generalized search tree based organizations
A **Generalized Search Tree (GiST)** such as an **R*-tree** is the _multidimensional_ equivalent of a [[03 - Dynamic organizations#B+ trees|B+ tree]], but instead of keys, **each node stores a bounding region**.

As we previously saw, linearization is bad for spatial queries, whilst space partitioning is not ideal for unbalanced data since they split the space in non-overlapping regions, this type of tree address these issues by:
- Grouping nearby objects dynamically
- Allowing overlapping bounding regions
- Staying balanced (like a B+ tree)

- **Internal nodes**: (`Ri`, `pointer_to_child_i`)
	`Ri` is the minimum bounding rectangle covering all objects below that child.
- **Leaf nodes**: (`data_region`, `pointer_to_record`)
![[R-star tree.png|400]]

**Search**:
If we want to find objects overlapping a query region `R`, we start from the root and for each entry (`Ri`, `pi`), if `Ri OVERLAPS R` we follow the pointer and at leaves report every data region that overlaps `R`.

**Insertion**:
Since nodes overlaps, we must choose which leaf to descend into, the heuristic is picking the child whose bounding region needs the least enlargement to include the new region.

If the region fits into the leaf then it's done, otherwise we split the leaf, but unlike quadtrees we do not split the space, instead we split the entries in order to:
- Minimize overlap between new bounding rectangles
- Minimize dead space (empty but included area) inside the new rectangles

After splitting a leaf the parent bounding regions are updated, and eventually it also gets split up until (potentially) the root, where the tree will grow in height by creating a new root with 2 children.

**Deletion**:
We first find the leaf containing the region to delete, then we remove it.
If the leaf now has too few entries, we do not borrow (as seen in B+ trees), instead we remove the node entirely and reinsert all of its entries back into the tree in order to let the tree reorganize itself.

| Pros                     | Cons                                                         |
| ------------------------ | ------------------------------------------------------------ |
| Good for spatial queries | Since nodes overlap, sometime multiple paths must be checked |
| Dynamically balanced     | Complicated insertion/deletion.                              |
