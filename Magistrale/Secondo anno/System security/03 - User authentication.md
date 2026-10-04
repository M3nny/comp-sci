**Identification** is the task of correctly identifying a user or entity, it is typically required for enforcing other security properties, for example when _access to a resource_ needs to be regulated.

An identification scheme should always **prevent**:
- _Impersonation_: even observing previous identifications
- _Uncontrolled transferability_: the verifier should not reuse a previous identification to impersonate the claimant with a different verifier, unless authorized

**Classes of identification schemes**
- _Something known_: check the knowledge of a secret
- _Something possessed_: check the possession of a device
- _Something inherent_: check biometric features of users

### Something known
**Preventing leakage and guess**
- The password should only be used over encrypted channels
- The service should be disabled after $n$ attempts
- Use strong passwords (avoids offline attacks e.g. bruteforce dictionary attack)
- The server should store the one-way hash digest
>Precomputation of password hashed is prevented by adding a _random salt_.

### Something possessed
**Token based authentication** works with _passive cards_ with a memory (e.g. hotel cards to open doors), _smart cards_ (e.g. telepass).
Their **interface** can be:
- _Contact based_: a conductive contact plate for commands transmission and data
- _Contactless_: both the reader and the card have an antenna, and comunicate using radio frequencies
Their **protocol** may be:
- _Static_: token provides a fixed secret (as for passive cards)
- _One time password (OTP)_: the token generates a fresh OTP that is used for authentication
- _Challenge-response_: a challenge is processed by the token that produces a response

#### OTPs
**OTPs** are _never reused_, they mitigate password leakage by allowing for a single authentication, in order to do this, the token and the computer system must be kept synchronized, so the computer knows the OTP that is current for this token.

##### Lamport's hash-based OTP
Given a secret $s$ and a one-way hash function $h$ we compute:
$$h^t(s)=h(h(...h(s)...))\space t\text{ times}$$
- The _claimant_ uses the list of passwords: $h^{t-1}(s), h^{t-2},...h(s),s$
- The _verifier_ computes $h(pwd)$ and checks if it is equal to the stored hash: $h(h^{t-1}(s))=h^t(s)$
- If the check succeds the verifier stores $h^{t-1}(s)$

- **Passwords**: $h^{t-1}(s), h^{t-2},..., h(s),s$
- **Stored hashes**: $h^{t}(s), h^{t-1},..., h^2(s), h(s)$

With this approach _only $t$ authentication are possible_, but computing next passwords from the current is equivalent to compute the preimage of $h$, which is infeasible ($h$ is one-way).

### Something inherent
**Biometrics** requires storing users personal features into a database and later comparing them.

This leads to a delicate balance between _false positives_, since this method should ensure not impersonification, and correct users should be identified most of the times, so _no false positives_.

A major issues with this system is a **breach in the biometric database** which has _high impact_ due to the biometric data being unique and cannot be changed if leaked.

