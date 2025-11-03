We differentiate two types of scaling:
- **Vertical**: adds more power to a single database server
- **Horizontal**: adds more database servers to a network

A **distributed DBMS** is used to manage distributed and inter-related databases over a network, thus making the interaction with them **transparent** to the user.

It is possible to list the following types of _transparency_:
- **Access**: independent of the structure of the network or storage organization
- **Location**: data distribution is hidden
- **Replication**: user may access any replica
- **Fragmentation/sharding**: it is handled internally, the user can query the database as if it contained un-fragmented  data
- **Migration**: data organization does not affect data access
- **Concurrency**: operations of multiple users must not interfere
- **Failure**: continue processing requests even in the presence of failures

---
### Failures in distributed systems
There are many ways a distributed system may fail, including: **server failure**, **failure of a link** and **network partition**, that is when a network gets split in more subsystems without any communication link between them.

>[!Attention] Network partitioning and server failure
>Since a subsystem may consist of a single node, if a server fails, it is indistinguishable from network partitioning.

**Epidemic protocols** are probabilistic methods used to propagate information, other than being used for data replication and update propagation, they are also used for failure detection, in fact it is possible that every node of a network pings other groups in order to check if they're alive.

These methods give **probabilistic guarantees** that even if some nodes fail, the information will likely still reach everyone.

Nodes can be in three different states:
- **Infected**: they have received the message and will pass it to others
- **Susceptible**: they have not received the message yet
- **Removed**: they have received the message but are no longer willing to pass it on

Variants of epidemic protocols include:
- **Anti-entropy**: any server is either susceptible or infected, so the infection does not degrade over time
- **Rumor spreading**: at the arrival of a new message the node becomes infected, the infection proceeds in several rounds, and it decreases with every round as the number of removed nodes grows, it can be _probabilistic_ if after an exchange with a node, the server stops being infective with a certain probability, or it can be _counter-based_ if after a certain number of exchanges, the server stops being infective

Each node builds an **hash tree (i.e. [Merkle tree](https://en.wikipedia.org/wiki/Merkle_tree))** where leaves are the raw data of the node, and then their hashes are grouped into another hash that represent the parent of the group, this process is repeated until the tree root is created.

In this way two nodes can compare if they have the same data just by checking if their root is equal.
>It is important that the raw data is sorted in the same way in each node, otherwise it will lead to different hashes.

---
### Fragmentation
Fragmenting (or sharding) data consists into splitting the original data between nodes.

| Advantages                                                                                   | Disadvantages                                                |
| -------------------------------------------------------------------------------------------- | ------------------------------------------------------------ |
| Put frequently accessed data in the same fragment (data locality)                            | Queries over different fragments are costly                  |
| Query performance can be better on smaller fragments, and also their indexes will be smaller | Backup and recovery is more difficult in distributed systems |
| Storage and load capacity can be balanced in the network                                     |                                                              |

The allocation of distributed data can be done with **consistent hashing**:
1. Each server gets a numerical hash value
2. Each data item also gets a numerical hash value
3. Assign each data item to the next server with equal or bigger hash value

The **removal of a node** consists in assigning the data that was assigned to him, to the next server, in fact we can imagine this as an **hash ring**.

The **insertion of a node**, causes the move of data items previous to his hash value, that are smaller than his, and where the new node hash value is smaller than the node where the data was previously assigned.

In case one node is **better equipped** (more storage, better CPU,...), it is possible to create virtual copies that will appear as new nodes in order to assign more data items to it.

---
### Data replication
We identify the copies of data as **replicas*** and the number of servers as the **replication factor**.

| Advantages                               | Disadvantages                             |
| ---------------------------------------- | ----------------------------------------- |
| Reliability and higher data availability | Consistency problems (update propagation) |
| Lower latency                            | Concurrency problems (multi-user write)   |

**Master-slave** replication consists in a single master node that propagates the updates to other slave nodes, the latter's data may only be read, never update directly by the user, in this way the master node is the only point of failure.

This approach has variants like:
- _Some nodes may act as master for others, and slave for others_, in this way not all data depends on one master and improves availability and load balancing
- _Every node is a master_ and updates are automatically synchronized among all replicas, it is more complex to maintain since it requires conflict resolution, but in this way there is a better response time and increased availability

Techniques to improve consistency across distributed databases are:
- **Hinted handoff**: if a replica is unavailable, write requests are delegated to another available server, and are relayed to the replica as soon as possible
- **Read repair**: a coordinator contacts a set of replicas, and returns the majority response to the client, then sends repair (update) instructions to those replicas that are not yet synchronized

---
### Distributed concurrency control
The execution of a **distributed transaction** consists in a **2-phase commit** where a coordinator first sends a message to every other node telling them to prepare, and then it will commit the change to every node once they are ready.

Failure of a single node will lead to a global abort of the transaction, and in case the coordinator fails before sending his decision, the other nodes cannot proceed to either commit or abort the transaction.
![[2-phase commit.png|400]]

What if in a _multi-master_ system an update message is lost? And what will be the correct value and order of updates?

A **consensus algorithm** is needed in order to keep a distributed DBMS in a consistent state under certain failures, nodes have to come to a consensus on what the current state (most recent value) of the record is.

**Paxos consensus algorithm**:
1. **Prepare**
	- One proposer (or leader) selects a proposal number $n$ (that has to be higher than any proposal number used before) and sends _prepare requests_ to _acceptors_
	- Each acceptor, upon receiving the prepare request if $n$ is greater than any proposal number it has already seen, it promises not to accept any future proposals with a number less than $n$ and sends back a promise response to the proposer including the highest-numbered proposal it has already previously accepted (if any)
	
2. **Accept**
	- The proposer waits for promises, if it receives them from a majority of acceptors it now knows that no smaller-numbered proposal can succeed
	- The proposer chooses a value to propose, if any acceptor's promise contained an already accepted proposal, the proposer picks the value from the highest-numbered accepted proposal, if none had already accepted a proposal, the proposer can choose its own new value $v$
	- The proposer sends an _accept request_ to the acceptors
	- The acceptors upon receiving the request, if there weren't any new proposals with a higher number than $n$ in the meantime, accept the proposed value $v$ marking it as _accepted_ and sending an accepted message to the _learners_
	- The learners just observe the result of the voting, and once they see that the majority consensus is a certain value $v$, they update the the record with the new value $v$ and propagate it to other nodes

![[Paxos algorithm.png|500]]

>[!Attention] Failures
>- **Failure of learner**: for this to work, there must be at least one learner returning the result to the client
>- **Failure of proposer**: another proposer takes the role, starting with a higher proposal number. There could be a problem about dueling leaders, where the proposers prepare messages with increasing proposal numbers (no consensus is reached in this case)


---
### Version vectors
In order to determine the precedence of updates it is possible to use **version vectors**.

- **Union semantics**: each node gets independently updated, then they merge forming an union, no data is lost, just merged (this does not work with conflicts in setting a value)
![[Union semantics.png|500]]
- **Siblings & Reconciliation**: Instead of merging automatically, conflicting updates create _siblings_, later, clients or the system can reconcile them by merging them manually or by picking one version
![[Siblings & reconciliation.png|500]]

>[!Attention] Lost updates
>Keeping logical counter per replica, and not per client or update source can lead to lost updates.
>![[Lost update.png|500]]
>Client $A$ and $B$ start with the same base state from replica 1, each of them makes updates, when merging one overwrites the other.

---
### Consistency problems
When a server modifies a value in a replica, the value must be immediately modified in every other replica before it gets read again, this might block a read access until every replica is updated (bad for availability).

The **CAP conjecture** states that at most 2 of these 3 properties can be satisfied at the same time in a distributed system:
- **Consistency**
- **Availability**
- **Partition tolerance**

There are two types of consistency:
- **Strong**: after an update any subsequent access returns the updated value
- **Weak**: after a period named _inconsistency window_ that indicates the period between the update and the point of time when every node is updated, eventually all accesses will return the last updated value

It is possible to use **read/write quorums** to ensure consistency.
Quorums represent a set of replicas that have to be contacted when reading (all replicas must return the same value fro a successful read), and writing (every replica has to acknowledge the write request).
