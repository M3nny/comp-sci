Neo4j is a graph database used to model relationships, its main building blocks are:
- **Nodes**: represent the objects in the graph and can be labeled
- **Relationships**: relate nodes by type and direction
- **Properties**: name-value pairs that can go on nodes and relationships

![[Neo4j graph.png|250]]

For querying the graph we use **cypher** which is a pattern matching language made for graphs.

| Semantic                                    | Syntax                  |
| ------------------------------------------- | ----------------------- |
| Node                                        | `()`                    |
| Relationships                               | `-->`, `-[:LIKES]->`    |
| Patterns (connects nodes and relationships) | `()-[]-()`, `()-[]->()` |

```cypher
// Returns people that acted in movies
MATCH path = (:Person)-[:ACTED_IN]->(:Movie)
RETURN path
```

Things defined by the user, such as node labels are **case sensitive**, while cypher keywords are **case insensitive**.

#### Constraints
We can create constraints in order to ensure **uniqueness** and allow **fast lookup** of nodes which match label-property pairs.

**Unique node property**
```cypher
CREATE CONSTRAINT ON (label:Label)
ASSERT label.property IS UNIQUE
```

**Node property existence**
```cypher
CREATE CONSTRAINT ON (label:Label)
ASSERT EXISTS (label.name)
```

**Relationship property existence**
```cypher
CREATE CONSTRAINT ON ()-[rel:REL_TYPE]->()
ASSERT EXISTS (rel.name)
```

#### Indexes
We can also create indexes to allow fast lookup of nodes which match label-property pairs.
```cypher
CREATE INDEX ON :Label(property)
```

They can be used with the following predicates: `equality`, `starts with`, `contains`, `ends with`.

<u>Indexes are only used to find the starting points for queries</u>.

### Queries
**CREATE**
```cypher
CREATE (m:Movie {title:'Mystic River', released:2003})
RETURN m
```

**SET**
```cypher
MATCH (m:Movie {title: 'Mystic River'})
SET m.tagline = 'We bury our sins here, Dave. We wash them
clean.'
RETURN m
```

**MERGE**
This clause is the same as `MATCH`, but if the matched value does not exist, it gets created.
```cypher
MERGE (p:Person {name: 'Tom Hanks'})-[:ACTED_IN]
->(m:Movie {title: 'The Terminal'})
RETURN p, m
```

**ON CREATE**
Simile ad un trigger SQL, definisce delle operazioni da fare quando la clausola specificata viene eseguita (in questo caso create) su un certo match.
```cypher
MERGE (p:Person {name: 'Your Name'})
ON CREATE SET p.created = timestamp(), p.updated = 0
ON MATCH SET p.updated = p.updated + 1
RETURN p.created, p.updated;
```

