**Economy of mechanism (simple vs complex)**
The design of security measures should be as _simple and small_ as possible, since complex mechanisms are more vulnerable and harder to maintain and configure.

**Fail-safe default (permission vs exclusion)**
Access decisions should be _deny as default_, since a mistake in the configuration will tend to refuse a permission, which is better than an hard to notice unauthorized access.

**Complete mediation (optimizations)**
Every access must be _checked against the access control mechanism_.
Caching this mechanism would ignore changes in access policy (or the system should mark the cache as dirty).

**Open design (open vs closed design)**
The design of a security mechanism should be _open rather than secret_, thus allowing for expert reviews, only the keys are secret.

**Separation of privilege (single vs separated privileges)**
_Multiple privilege attributes_ are required to achieve a sensitive task.

**Least privilege (min vs max privileges)**
Every process and every user of the system should operate at the _least set of privileges_ necessary to perform the task.

**Layering (single vs multiple protections)**
Use of _multiple, overlapping protection_ approaches, so that a failure of one protection will note leave the system unprotected.

**Psychological acceptability (usability)**
The _security mechanisms should not interfere with the work_ of users, since low usability might lead users to turn off mechanisms.

**Isolation (isolated vs connected)**
_Physical or logical isolation_ of critical information/resources.

**Modularity (modular vs monolithic)**
Use of a _modular architecture_ for mechanism design and implementation, so that common security modules shared by applications can be checked once and easily maintained, also they should be _isolated_.

### Compute security strategy
**Specification/policy**: what is the security scheme supposed to do?

Security involves _penalties in usability_, for example: access control requires users to remember passwords, firewalls reduce transmission capacity and virus checking reduces the available processing power.

_Security is not free_, cost of failure and recovery should be considered.

_Attack trees_ are a methodical way of describing the security of systems, based on varying attacks, nodes are OR/AND:
- OR is possible if one child is possible
- AND is possible if all children are possible


Values can be associated to nodes (e.g. cost), as well as extra information (e.g. special equipment required).
![[Attack tree.png]]

**Implementation/mechanisms**: how does it do it?
- _Prevention_: ideal security scheme in which no attack is successful (not always practical)
- _Detection_: when absolute protection is not feasible, it is still practical/useful to detect security attacks
- _Response_: the system responds in such a way as to halt the attack and prevent further damage
- _Recovery_: recover the system prior to the attack

**Correctness/assurance**: does it really work?
- _Assurance_: confidence that the system operates such that the system's security policy is enforced (formal analysis can help)
- _Evaluation_: process of examining a computer product or system with respect to certain criteria

