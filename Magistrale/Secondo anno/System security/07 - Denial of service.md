**Denial of Service (DoS)** is a popular attack that compromises the availability of a service, its formal definition is: an attack that _prevents or impairs the authorized use_ of networks, systems, or applications _by exhausting resources_.

It is particularly effective when launched from _many devices_, in this case we refer to it as **DDoS (Distributed DoS)**.

Typical **targets** are:
- _Network bandwidth_: if incoming traffic exceeds the bandwidth, packets will be discarded, thus including legitimate packets  
- _System resources_: exhausting TCP connections (for example) makes the server reject connections
- _Application resources_: required to accomplish tasks, for example excessively complex queries to a database

### Network bandwidth DoS attacks
**Flooding attacks** are used to overwhelm network capacity, between them we list:
- _ICMP flooding_
- _UDP flooding_
- _TCP flooding_

The target might either respond (increasing the load), generate a ICMP unreachable message, or reject the packet.

A **simple flooding attack** may be done using `ping -f`, however it is easily identified and the target will reflect all those requests back.

Another type of attack is **source address spoofing**, in this case the attacker uses _raw socket interface_ to change the source address, so that responses will be scattered around the Internet, and also possible error packets might be addressed toward the target itself thus contributing to DoS.

Source address spoofing makes it _hard to identify_ the attacker since TCP/IP does not ensure that the source address really corresponds to the originating host (it would be necessary to manually query the logs of traversed routers in order to identify the trajectory).

Then there are **botnets** which are a collection of _zombie devices_ under the attacker control, flooding coming from thousands of hosts easily reaches Gbps bandwidth.

### System resources DoS attacks
A popular attacks is **SYN spoofing** which _overflows_ the tables used to manage TCP connections.

Recall that TCP uses a **three-way handshake** to establish a connection, this attack consists in using spoofed source addresses in order to keep the server TCP table full.

This exploits the fact that after a SYN request, the server pre-allocates the memory for the connection, and by sending many of these requests, basically we cutoff the server from the Internet since its TCP table will always be full and it will then reject any other connection.

Notice also that the volume of SYN requests is low and far from link capacity.

### Application resources DoS attacks
In this case, the attacker floods an application protocol, for example:
- **Session initiation protocol (SIP)** used in VoIP, creates INVITE requests that go through proxies and consume system/network resources
- **HTTP requests** can be heavy, for example a download of a large file

**Slowloris** is a particular DoS attack that leverages server multi-threading:
- Start many HTTP requests without completing them
- Keep the connection alive by sending new lines, periodically
>This consumes all available web server connections.


---
### DoS techniques
**Reflection attacks**
The attacker sends packets to an _intermediary_ with a spoofed source address of the target, so the intermediary responds to the actual target.

If the response is larger than request, then the attack is also amplified, and tracing is hard if the attacker uses many intermediaries.

When the _echo service_ (port 7) is enabled, **reflection loops** are possible, for example: the attacker sends a packet to `ip-1` port 7, with spoofed source address `ip-2` port, the intermediary echoes to target and  target echoes to intermediary in a loop.

**Amplification** consists in generating multiple responses packets with a single request, for example: send a packet to the broadcast address of a network with spoofed address, then all hosts (with the service enabled) will respond to the target.

### Defenses
- **DoS cannot be fully prevented**: attackers that can flood a service with legitimate requests will limit traffic from other users
- **DoS can be "incidental"**: important news make legitimate users overload referenced web sites

**Prevention and mitigation for spoofed source addresses** (before the attack)
- _Filtering_ spoofed source address as close as possible to the originating host (e.g. where the organization connects to the Internet)
- Ensure that the _path back_ to the claimed source address is the one being used by the current packet, CISCO implemented this, but it is too strict when routing is asymmetrical, since it does not permit "multihoming" which allows connecting to many networks for reliability/performance

**Prevention of SYN spoofing**
Make the protocol _stateless_ by encoding state information directly in the SYN-ACK sequence number `y`, thus avoiding the use of TCP request tables (and their possible overflow).
![[SYN spoofing prevention.png|253]]

**Mitigation: rate limits and random drops**
Flooding attacks can be mitigated by imposing _limits on packet rates_, similarly SYN spoofing attacks can be mitigated by _limiting the connection rate_ to a certain service.

Table overflow in SYN spoofing can be mitigated by _random dropping_ connections, the idea is that: since an overflow is a probable sign of attack, then randomly dropping a connection will more likely drop and attacker's connection (could drop a legitimate connection, but it is better than full DoS).

**Other prevention techniques**:
- _Block broadcast_: prevents amplification attacks
- _Block/limit suspicious services and combinations of ports_: counters reflection attacks
- _Check human interaction_: for example with captcha, to protect application resources
- _Keep systems up-to-date and secured_: so they do not become part of a botnet
- _Monitor systems_: especially high-performance, well-connected servers, which are potential intermediaries
- _Use mirrored and replicated servers_: increases reliability and resilience to DoS attacks

**Detection, source traceback and reaction**:
- _Detection_: capturing packet flows and analyzing them, if the attack is identified:
    - Suitable filters can be activated
    - Bugs can be fixed
    - Alternate backup servers can be activated
- _Source traceback_: necessary for legal actions, requires collaborating ISPs (can be complex)
- _Reaction_: analyzing the attack and the response to gain benefit from the experience and improve future handling, which can improve the organization's security

