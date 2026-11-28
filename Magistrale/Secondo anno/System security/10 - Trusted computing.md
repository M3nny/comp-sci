**Formal models of security** can be used to "prove" that a design meets a set of security requirements and that an implementation conforms to the design.

### The Bell-La Padula (BLP) model
Information must never flow from a level to lower ones, which is enforced by **mandatory access control** plus standard DAC:
- _Simple security_: subjects cannot read objects at a higher level
- _*-property_: subjects cannot write into objects at a lower level

The effect is "write up, read down", even a malicious subject at a high level cannot leak secrets to a lower level, nor can a low-level subject read secrets.

**Formal model**
There are _subjects_ $S_1,..., S_m$, _objects_ $O_1,...,O_n$ and _access modes_ $A_1,...,A_w$ (read, write, append, …), and a _state_ is a triple $(b, M, f)$:
- $b$: the current access set, with triples $(S_i, O_j, A_x)$
- $M$: the access matrix of permitted modes, where $M_{ij}$ holds the modes of subject $i$ on object $j$
- $f$: the level function assigning security levels to subjects and objects

**Secure state** means that a state is secure iff:
- _Simple security_: every $(S_i, O_j, read)$ in $b$ has $f(S_i) \geq f(O_j)$
- _*-property_: every $(S_i, O_j, write)$ in $b$ has $f(S_i) \leq f(O_j)$
- _ds-property (DAC)_: every $(S_i, O_j, A_x)$ in $b$ has $A_x \in M_{ij}$

**Operations**
The model defines get/release access, change object or subject level, give/revoke permission, and create/delete object, each must preserve the three properties, for example:
- Get-read requires $f(S_i) \geq f(O_j)$ and read $∈ M_{ij}$
- Get-write requires $f(S_i) \leq f(O_j)$ and write $\in M_{ij}$
- Changing a level must not break existing accesses
- Revoking a permission requires that no matching access is currently active

When an action would violate a condition, it is either _forbidden (error)_ or the state is _updated to restore security_ (e.g. by releasing the offending accesses).

**Security proof**
The _security Theorem_ states that a system starting in a secure state stays secure iff every operation preserves the three properties.

In theory one can prove an implementation or design secure by checking that every state-changing action satisfies them.

For complex systems such a proof can hardly cover all cases, but _formal proof still leads to more secure designs and implementations_.

**BLP in RBAC**
Each subject gets a clearance $L(s)$ and each object a classification $L(o)$.

For a role r:
- _r-level(r)_ is the least upper bound of the levels of objects the role can read
- _w-level(r)_ is the greatest lower bound of the levels of objects the role can write

A subject may be assigned to a role only if $L(S) \geq r-level(r)$ (simple security) and $L(S) \leq w-level(r)$ (\*-property).

### Trusted systems and the TPM
**Trusted systems**
_Trust_ is confidence that a system meets its specifications (e.g. through formal analysis or code review).

The _trusted computing base (TCB)_ is the part of the system enforcing a policy, small enough to be analyzed.

_Evaluation_ assesses whether the system has its claimed security properties.

**Trusted Platform Module (TPM)**
A tamper-resistant hardware TCB standardized by the Trusted Computing Group, integrated in the CPU, the motherboard or smartcards.

It works with TC-enabled software (OS and applications), so that software can trust the data it receives and the system can trust the software, and it offers three services: _authenticated boot_, _certification_ and _encryption_.

**Authenticated boot**
The TPM makes sure the OS booted is an approved version, then boot proceeds in stages (Boot ROM, boot block, larger blocks, full OS), and at each stage the TPM checks that valid software is loaded (e.g. by verifying a digital signature).

The TPM keeps a _tamper-evident log_ of the loading process, protected by a cryptographic hash, recording exactly which OS version and modules are running.

The trust boundary can be extended to hardware, applications and utilities through an _approved list_. A new component must be on the list, digitally signed, and have a serial number that has not been revoked.

**Certification**
The TPM certifies the trusted configuration to other local or remote parties by _signing a description of the configuration with its private key_.

The TPM is trusted itself, only it holds the private key, and its public key verifies the signature

Trust is _hierarchical_: the TPM certifies hardware and OS, the OS can certify applications, and so on.

**Preventing replay attacks**
An attacker could intercept a certification, compromise the system, then replay the old certification to look trustworthy, the fix is a _random challenge $R$_ from the requester, included in the signature as $Sign(R, config)$, so a replayed signature carries a different $R′$, so the requester sees $R \neq R'$ and _rejects_ it.

**Encryption service**
Data is encrypted so that it can be decrypted only by a specific machine _in a specific trusted configuration_.

One master secret key derives a separate encryption key for each trusted configuration, so decryption works only in the same configuration.

Trust is hierarchical here too: a certified application can be given a key, and only the desired version of the desired application, on the desired OS version, can decrypt. 
>This works even remotely if TPMs share master keys.

>[!Example] Protected storage
A file is encrypted and saved locally, and its encryption key is encrypted by the TPM under the master key and stored with the file, tied to the authorized hardware/software configuration.
>
>To decrypt, the application asks the TPM, which _verifies the configuration matches_, decrypts the key and passes it to the application.
>
>The application decrypts the file and is trusted to discard the key.


