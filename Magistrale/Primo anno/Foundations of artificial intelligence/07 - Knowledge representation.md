Machine learning models deal with **knowledge** (i.e. data), and using the right representation is crucial.

### Expert systems
An **expert system** (or knowledge based system) is a rule based computer system which simulates a human expert in his field of expertise in an attempt to solve a problem.

- It accumulates knowledge from various sources (e.g. documentation)
- The decisions of the expert are based on the accumulated knowledge (facts)

Expertise is a large amount of knowledge in some domain, that is easily recalled, while intelligence allows to use the expertise.

If some specific information is missing, the expert system must choose an alternative route, and it also must be able to justify their decisions.

**Production systems** (or rule based systems) are programs that use sets of if-then rules, that is _production rules_, and their order is decided by the program itself with respect to a problem state.

Some **limitations** of expert systems include:
- Not able to cope with unseen information
- Not able to learn independently
- Not able to cope with noise
- Not able to adapt to new environments

---
### Logic
A **logic** is a **language** with concrete rules, that has no ambiguity in its representation.
> Logics are languages, reasoning is a process that may use logic.

**Syntax**:
- Rules for constructing legal sentences in the logic
- Allowed symbols and allowed combinations of them

**Semantics**:
- How to interpret sentences in the logic
- Assigns a meaning to each sentence

#### Propositional logic
**Syntax**:
- Propositions (e.g. it is wet)
- Connectives: $\land,\lor,\neg,\implies,\iff$
- Brackets: true, false

**Semantics**:
- Define how connectives affect truth
- Use truth tables to work out the truth of statements

#### Predicate logic
Predicates allow us to talk about objects by using atoms that do not contain propositional connectives.
- **Properties**: `is_wet(today)`
- **Relations**: `likes(john, apples)`

Each atom is a predicate (e.g. first order logic, higher order logic).

#### First order logic
More expressive than propositional logic, in this case **predicates** are properties and relations: `likes(john, apples)`.

And **functions** transform objects: `likes(john, fruit_of(apple_tree))`.

**Variables** represent any object: `likes(X, apples)`, and **quantifiers** qualify values of variables (e.g. universal, existential).

>[!Example] FOL sentences
>"Every rose has a thorn".
>$$\forall X.(rose(x)\implies\exists Y.(has(X,Y)\land thorn(Y))$$
>"On mondays and wednesdays i go to john's house for dinner".
>$$\forall .((is\_mon(X)\lor is\_wed(X)))\implies eat\_meal(me,house\_of(john),X)$$

#### Higher order logic
More expressive than first order.
In this case functions and predicates are also objects:
- Described by predicates
- Transformed by functions

They are much harder to reason with, for example "define red functions as having zero at 17":
$$\forall F.(red(F)\iff F(0)=17$$

---
### Non-logical representations
Logic representations have restrictions and can be hard to work with, we can for example use **production rules** that involves set of pairs of `<condition, action>`.

We can use **semantic networks** to represent relationships between ideas as graphs, and **frame representations** to extend the concept of a node to an object with various attributes (similar to OOP).

