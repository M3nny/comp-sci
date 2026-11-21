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
**Biometrics** requires storing users personal features into a database and later comparing them, this is called **enrollment**.

This leads to a delicate balance between _false positives_, since this method should ensure not impersonification, and correct users should be identified most of the times, so _no false positives_.

A major issues with this system is a **breach in the biometric database** which has _high impact_ due to the biometric data being unique and cannot be changed if leaked.

Enrollment produces a **protected feature template** $T$, then at verification, a fresh sample gives features $x$, and the user is accepted when $score(x,T)\geq\tau$ (a threshold).

Since noisy measurements _can't directly reproduce a key_, biometrics are used to authorize key use rather than act as the key.
>The challenge is: protect the template and matcher, prevent sample injection or replay and securely bind a successful verification to key use.

---
### Passkeys and the keystore model
A **passkey** is a public-private key credential for signing in to a site or app, the **relying party (RP)** stores the public key and account; the authenticator holds the private key.

We can differentiate:
- _Local authorization_: a PIN or biometric unlocks the key
- _Remote authorization_: a signature proves possession of the key (the website never receives any biometric)

**Registration**
1. The server sends a fresh challenge, RP ID and user ID
2. The browser validates the RP ID against the origin
3. The authenticator verifies the users, generates (sk, pk) and binds it to the RP and account
4. The server validates and stores the credential ID and pk
>Secure enrollment determines whose key the account will trust.

**Authentication**
1. The server sends a fresh challenge $c$
2. The authenticator signs `authenticatorData` plush the hash of `clientDataJSON`
3. The server checks $c$, origin RP ID, flags, account mapping and the signature

A phishing page can _relay the genuine challenge_, but the browser rejects a request whose RP ID doesn't match its origin, so the genuine passkey is out of scope for the phishing domain.

| |Device-bound|Synced|
|---|---|---|
|Availability|Original authenticator|Authorized provider devices|
|Key mobility|No sync/export by design|Encrypted transfer/recovery|
|Device loss|Register another credential or recover the account|Provider recovery or another device|
|Local key protection|Depends on authenticator|Depends on provider and device|

>[!Example] Scenarios
>1. A leaked database of public keys and credential IDs doesn't let an attacker log in as Alice, because the private key is missing.
>2. A stolen session cookie after passkey login still allows hijacking, because biometrics only protect the login step.
>3. A response with Bob's user ID but Alice's signature must be rejected by the server's account-mapping check (the credential must belong to the claimed account).

>[!Example] Passkey authenticators:
>- **Synced passkeys** (e.g. Bitwarden): store the private key and sync it between our devices via the provider
>- **Device-bound passkeys** (e.g. YubiKey): a hardware key such keeps the private key on the device and never exports it

>[!Example] Biometric/platform authenticators
>_Face ID/Touch ID (Apple Secure Enclave)_ and _Android fingerprint/face unlock (TEE plus KeyMint)_ don't act as the key, they authorize use of a key stored in secure hardware.