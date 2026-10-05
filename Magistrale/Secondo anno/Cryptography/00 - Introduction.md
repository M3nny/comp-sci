**Security properties** we are interested in (also seen in [[Magistrale/Secondo anno/System security/00 - Introduction|system security]]) are:
- **Authenticity**: an entity should be correctly identified
- **Confidentiality (secrecy)**: information should only be accessed (read) by authorized entities
- **Integrity**: information should be modified by authorized entities
- **Availability**: information should be available/usable by authorized users
- **Non-repudiation**: an entity should not be able to deny an event

### Cryptography
Cryptography (hidden writing) is a way to protect the information when the environment is insecure.

- **Encryption**: a _plaintext_ is transformed using some rules (encryption algorithm) in a _ciphertext_
- **Decryption**: the _plaintext_ is reconstructed starting from a _ciphertext_
>The decryption has to be simple for the receiver and unfeasible for an attacker.


There are two possible solutions for **encryption**:
1. Only the sender and the receiver know the encryption algorithm
2. The encryption algorithm is public and the actors share some information (the key) non accessible by the attacker

**Encryption keys** is the best solution, since it is simpler to distribute only one key and if case of an attack it will be easier to just change the key (rather than the whole algorithm).

A **symmetric key** is the same for both actors in a communication channel, and it must be sent in a secure channel, they will use it to encrypt and decrypt messages.

**Caesar cipher** is an example of this, since it consisted in shifting each letter by the one 3 positions ahead in the alphabet (cycling), in this case the key was the number of shifts (3).