**Intrusion** is the unauthorized act of bypassing the security mechanisms of a system. 
We can detect it by analyzing information from a computer or a network.

**Classes of intruders**:
- _Cybercriminals_: individuals or members of an organized crime group with a goal of financial reward
- _Activists (hacktivists)_: individuals or groups motivated by social and political causes
- _State-sponsored organizations_: groups of hackers sponsored by governments to conduct espionage or sabotage
- _Others_: hackers motivated by technical challenges or peer esteem, usually advancing the state of the art in hacking techniques

### Intruder behavior
The **phases of an intrusion** may be summarized as:
- _Target acquisition and information gathering_: the attacker identifies and characterizes the target by examining the corporate website, scanning with tools like DNS lookup and NMAP, identifying vulnerable services, or interacting by email
- _Initial access_: exploiting a vulnerability, guessing weak credentials, or installing malware via phishing
- _Privilege escalation_: exploiting a local vulnerability to gain more privileges
- _Information leakage and system exploit_: scanning and examining files, transferring sensitive data out, and using guessed or captured passwords to reach other systems
- _Maintaining access_: installing remote administration tools and rootkits with backdoors, using admin passwords, modifying or disabling the IDS (the goal is to hide presence)
- _Covering tracks_: using rootkits to hide installed or modified files and removing logs

### Intrusion Detection Systems (IDS)
An **IDS** is hardware or software that analyzes information from a computer or network to identify possible intrusions.

**IDS components**:
- _Sensors_: collect data that may contain evidence of intrusion (network packets, logs, syscall traces)
- _Analyzers_: receive sensor input and determine whether an intrusion occurred, offering guidance on possible actions and storing data for later analysis
- _User interface_: displays results and allows system configuration

**Why bother with IDSs?**
1. Quick detection allows the intruder to be ejected before much damage is done (or even, fully prevented)
2. An effective IDS acts as a _deterrent_, reducing attack attempts
3. It collects information about intrusion techniques that can be used to _strengthen_ system and network security

### Analysis approaches
**Anomaly detection** builds a model of legitimate user behavior from data collected in a _training phase_ (no intrusion).

<u>Observed behavior is compared to the model</u>, and flagged as an intrusion when the difference exceeds a threshold.

**Anomaly detection approaches**:

| Approach           | Description                              | Pros                   | Cons                                                                          |
| ------------------ | ---------------------------------------- | ---------------------- | ----------------------------------------------------------------------------- |
| _Statistical_      | Statistical profile of observed metrics  | Simple and efficient   | Not flexible (which metrics?)                                                 |
| _Knowledge based_  | Rules classifying legitimate behaviour   | Robust and flexible    | Difficult to develop, requires experts                                        |
| _Machine learning_ | Automatically built classification model | Flexible and automated | Training is expensive, accuracy is not yet optimal, exposed to adversarial ML |

**Signature or heuristic detection (misuse detection)** uses known malicious patterns or attack rules, so it can only identify _known attacks_ (no 0-day).

**Signature and heuristic approaches**:

|Approach|Description|Pros|Cons|
|---|---|---|---|
|_Signature-based_|Matches known malicious patterns, large enough to minimize false positives (e.g. anti-virus)|Fast and widely accepted|Needs continuous review of malware to create signatures, cannot detect 0-days|
|_Heuristic-based_|Rules identifying intrusions or suspicious behaviour, often derived from analyzing existing attack tools|Fast and widely accepted|Rules are specific to the machine and OS, attackers who know the rules can circumvent them|

**Detecting intruder behaviour**: honest and malicious behaviors differ but also _overlap_.

**Types of detection errors**:

- _False positives (false alarms)_: honest users flagged as intruders
- _False negatives (missed alarms)_: intruders classified as honest

>[!Tip] Base-rate fallacy
>People tend to ignore the base rate when given more specific information.
>
>For example, with a breathalyzer with a 5% false positive rate (no false negatives) and 1 in 1000 drivers drunk, a positive test means only about a 1.96% chance the driver is really drunk (1 / (49.95 + 1)), not 95%.
>
>The same applies to IDSs: with 1 malicious event in 10000 and a 5% false positive rate, only about 0.2% of alerts are true.
>
>**Too many false positives make an IDS useless**, and there is no trivial fix since tightening detection introduces false negatives.

### IDS classification
**Types of IDS**:
- _Host-based IDS (HIDS)_: monitors events on a single host, such as process identifiers and their system calls
- _Network-based IDS (NIDS)_: monitors traffic on particular network segments or devices and analyzes protocols to spot suspicious activity
- _Distributed or hybrid IDS_: combines sensors (often both host and network) in a central analyzer, thus summing up the advantages of multiple HIDS and NIDS

#### HIDS
A HIDS runs directly on a host to protect its applications, it detects intrusions, logs suspicious events and sends alerts, and it detects both **internal and external intrusions**.

**HIDS sensors**:
- _System call traces_: sequences of syscalls invoked by processes, giving accurate information on process interaction with the OS
- _Log files_: already produced by modern systems, they provide less overhead than syscall traces, but less information, lower detection rate
- _File checksums_: compare cryptographic checksums with stored ones to spot changes to important files
- _Registry access_: monitors access to the registry (Windows-specific)
- _Files_: signature-based HIDS looking for known signatures, as in anti-virus (file system, attachments)
- _Accesses to resources_: heuristic-based HIDS looking for known suspicious access requests

#### NIDS
A NIDS monitors traffic at selected points of a network and inspects packets directed to potentially vulnerable hosts.

**NIDS sensor deployment**:
- _External perimeter_: detects external intrusions, firewall misconfigurations, and outgoing malicious traffic (it does not detect internal attacks)
- _Before the LANs_: detects both internal and external intrusions, firewall misconfigurations and outgoing malicious traffic, and can be configured for specific resources

**Anomaly-based NIDS detection**:
- _Denial-of-service (DoS)_: anomalous increases in packet traffic or connection attempts
- _Scanning_: an attacker probes a target with different kinds of packets, detectable through atypical flow patterns
- _Worms_: propagate quickly using a lot of bandwidth, make hosts communicate that normally do not, use unusual ports, and often perform scanning

**Signature-based NIDS detection**:
- _Application layer attacks_: attack patterns targeting application protocols
- _Transport layer attacks_: unusual packet fragmentation, TCP-specific attacks such as [SYN floods](https://en.wikipedia.org/wiki/SYN_flood)
- _Network layer attacks_: spoofed IP addresses and illegal IP header values
- _Unexpected application services_: checking that activity on a transport connection is consistent with the expected application protocol
- _Policy violations_: inappropriate websites or forbidden application protocols

