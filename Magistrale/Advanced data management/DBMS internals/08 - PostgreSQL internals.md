As we saw in the RDBMS architecture, the relational engine contains a **catalog manager**, this is where PostgreSQL looks up information to decide how to do things, it is important to remark that _these catalogs are just tables_ that can be expanded by the user, they store:
- Table definitions
- Data types
- Functions
- Operators
- Indexes
- Access methods

PostgreSQL doesn't need to be recompiled or restarted, it just add entries and lookup those entries during query execution.

#### Query processing path
1. **Connection**: application establishes connection to PostgreSQL server
2. **Parser**: checks syntax and creates a query tree without semantic understanding
3. **Transformation**: performs semantic interpretation withing a transaction, accesses catalogs to identify tables, functions, operators, types and creates detailed query tree
4. **Rewriter**: takes the detailed query tree and looks for any rules (stored in the catalogs) to apply to the query tree, then it performs the transformations given in the rule bodies. This also inlines table views if possible, as saw in [[06 - Physical operators#Relational query optimization|relational query optimization]].
5. **Planner/Optimizer**:
	- Generates all possible execution paths
	- Estimates costs for each of them
	- Chooses the cheapest path
	- For large joins uses the _genetic query optimizer_ instead of exhaustive search
- **Executor**: recursively processes the plan tree, retrieves rows using storage system, performs joins, sorts, filtering and finally hands back the rows derived

### Key internal components
The **Genetic Query Optimizer (GQO)** handles queries with many joins using [[06 - Local search#Genetic algorithms|genetic algorithms]], thus generating random join sequences, then evaluates the fitness to choose the best join sequence.

**Index access methods** provide handler functions and specific support routines, this means that it is possible to handle heaps, b-trees and hashes.

Finally, PostgreSQL power comes from treating its own metadata as extensible data, allowing users to add functionality that integrates seamlessly with the core system.