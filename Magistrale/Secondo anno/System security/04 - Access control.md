**Access control** is the protection of system resources against unauthorized access.
It is the process regulating the use of system resources according to a _security policy_.

---
**Authentication**
Verification that the credentials of a user or other system entity are valid.

**Authorization**
 The granting of a right to a system entity to access a system resource.

**Audit**
An independent review and examination of system records and activities in order to:
- _Test_ for adequacy controls
- _Ensure compliance_ with established policy and operational procedures
- _Detect breaches_ in security and recommend changes

---
The **subject** is an entity capable of accessing resources (_objects_).
Any user or application actually gains access to an object by means of a _process_.

An **object** is a resource to which access is controlled.

---
### Access rights
- **Read**: subject may view information in an object
- **Write**: subject may add, modify or delete data in an object
- **Execute**: subject may execute an object
- **Delete**: subject may delete an object
- **Create**: subject may create an object
- **Search**: subject may search into an object
>One right might imply another one (e.g. read $\implies$ search).

---
### Access control policies

#### Discretionary Access Control (DAC)
![[Access matrix.png|637]]
**Access control list (ACL)** for each object lists subjects and their permission rights.
>Decomposition by columns.
- _Easy_ to find which subjects have access to a certain subject
- _Hard_ to find the access right for a certain subject 

![[ACL.png|582]]
**Capabilities** for each subject, list objects and access rights to them.
>Decomposition by rows.
- _Easy_ to find the access rights for a certain subject
- _Hard_ to find which subjects have access to a certain object

![[Capabilities.png|589]]

An **authorization table** stores an entry for each subject, access right and object, so that querying by subject gives capabilities, and querying by object gives ACLs.
![[Authorization table.png|291]]

A subject can give access to the object it **owns**, in some systems, access rights can be given with a **copy flag** so that non-owners can pass the right to other subjects.
>Programs typically _inherit_ user's access rights.

>[!Example] Attack example
>1. A malware program executed by Alice can leak Alice's sensitive data by simply giving read access to (malicious, malevolent and nefarious) Bob
>2. Alice might erroneously give read access to her sensitive files

Discretionary Access Control is **too flexible**.

#### Mandatory Access Control (MAC)
MAC imposes rules that **subjects cannot change**, so Alice cannot allow other users to access the secret files she has access to (unless they also have this right).

MAC **prevents**:
- _Leakage due to malware_
- _Leakage due to errors_

The **Bell-LaPadula (BLP) model** defines the level of security w.r.t. a certain _confidentiality_: <u>top secret, secret, confidential, restricted, unclassified</u>.

Subjects and objects are assigned to **security levels**:
- _Clearance_: the security level of subjects
- _Classification_: the security level of objects

In this model, information should _never flow from a level to lower ones_, such that subjects _cannot read from objects at a higher level (simple security)_, and subjects _cannot write into objects classified at a lower level (*-property)_.
![[BLP.png|406]]
**Covert channels** may still be used to _indirectly transmit information_, for example a shared resource that is slowed down by a malicious program might be used to encode bits (e.g. slow = 0, fast = 1).

**Chinese wall policy** is used to _prevent conflicts of interest_, the idea is that subjects cannot access objects from different companies that belong to the same conflict of interest class.

>[!Example]
>- Bank $A$
>
>- Oil company $B$
>- Oil company $C$
>  
>>$B$ and $C$ objects are in conflict.
> 
> Subject $S$ accesses an object from $B$, it can access more $B$'s objects, but cannot access $C$'s objects, however it can access $A$'s objects since they are not in conflict.
> 

**Read access (simple security)** is granted if the object:
- Is in the same company dataset as an already accessed object
- Or belongs to an entirely different conflict interest class

**Write access (\*-property)** is granted if:
- Access is permitted by simple security policy
- And no object can be read which is in a different company dataset to the one for which write access is requested
>This rule is _very restrictive_ since read/write permission is only possible on single company datasets.


#### Role-Based Access Control (RBAC)
DAC specifies access rights for each subject and object, RBAC adds a new layer: **roles**.
![[Pasted image 20261004184825.png|258]]

Subjects are assigned to roles, and roles have access rights to objects.
>RBAC can express DAC and MAC policies.

![[Pasted image 20261004184859.png|480]]
We can have **multiple roles** per user and **multiple users** per role.
Users establish sessions with the **roles they need** to accomplish a task (least privilege principle).

Roles can be organized as a **hierarchy** and might be **mutually exclusive** to enforce separation of duties (e.g. creating vs authorizing an account).

#### Attribute-Based Access Control (ABAC)
The idea is that the access should be regulated through attributes.
- **Subject attributes** ($SA_1,...,SA_k$): name, title, age, ...
- **Object attributes** ($OA_1,...,OA_M$): author, category, ...
- **Environment attributes**($EA_1,...,EA_N$): date, setting, connection, ...

For each subject $s$, object $o$ and environment $e$:
- $ATTR(s)\in SA_1\times\dotsi\times SA_k$
- $ATTR(o)\in OA_1\times\dotsi OA_M$
- $ATTR(e)\in EA_1\times\dotsi\times EA_N$
$$\text{can\_access}(s,o,e) = f(ATTR(s),ATTR(o),ATTR(e))$$

>[!Example]
>Access to online streaming
>```
>can_access(s,o,e) =
>(
>	(Membership(s) == Premium)
>	∨
>	(Membership(s) == Regular ∧
>		Type(o) == OldRelease)
>)
>∧
>( ExpireDate(s) >= Time(e) )
>```


- ABAC is **more flexible** than RBAC
- ABAC **can express** DAC, MAC, and RBAC
- Access decision is **more complex**
>More and more popular on cloud since performance is already limited by network latency.


>[!Example] Define BLP with ABAC
>BLP is no read-up no write-down, so how can we express it?
>Use security levels: `clearance(s)` and `classification(o)` are the security levels of `s` and `o`
>
>`BLP_can_access_read(s,o,e) = clearance(s) >= classification(o)`
>`BLP_can_access_write(s,o,e) = clearance(s) <= classification(o)`


