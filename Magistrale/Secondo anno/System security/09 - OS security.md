Programs will always contains vulnerabilities and weaknesses, so OS security is about providing adequate guarantees even in their presence, it is in fact treated as a **hardening process**.

We can list four key measures, which together build a **defence-in-depth system**:
- White-list approved applications
- Patch third-party applications
- Patch OS vulnerabilities and use the latest versions
- Restrict administrative privileges

The whole system can be seen as **three layers**:
- _User applications and utilities_: user programs interacting with the operating system APIs and services
- _Operating system_: privileged kernel code, APIs, services, interacting with the physical hardware
- _Physical hardware_: the actual device
>Attacks can come from "below" if lower layers are not hardened to provide proper security services.

### OS hardening steps
**System security planning**
The aim is to balance _security, usability, operational needs and cost_, planning must start at deployment, since _retrofitting is difficult and expensive_.

It is based on the system's purpose and information type, user categories and authentication, how access is managed (to this and other hosts), who administers the system and how (local or remote), and which extra mechanisms are needed (firewalls, anti-virus, logging).

**Installation**
Ideally done in an _isolated environment with no incoming connections_, since the system is vulnerable during this phase and hardening comes after.

Outgoing connections should go only to necessary, verified sites, other than this we can use further measures such as:
- _Secure boot_: prevents BIOS changes and limits boot media to trusted ones, blocking malicious hypervisors and trivial access-control bypass (e.g. booting from an external drive)
- _Cryptographic file systems_: add a protection layer to stored data

**Trusted code and patching**
Third-party _device drivers_ run with kernel privileges and can install malware.
>See: [Blue Pill rootkit](https://en.wikipedia.org/wiki/Blue_Pill_(software)), [Stuxnet](https://it.wikipedia.org/wiki/Stuxnet).

Systems should be patched, but updates can cause instability, so critical-availability systems often disable automatic updates, for these, patches must be _tested and applied promptly_.

**Unnecessary services and access control**
- _Remove unnecessary software_: fewer packages means less risk, not installing is better than removing or disabling, because removal is incomplete and attackers can re-enable disabled software
- All modern systems implement _DAC_, and sometimes _RBAC_ or _MAC_
- Administrative privileges should go to few users, be used only when necessary, and every administrative action should be logged

**Additional security controls**
- _Anti-malware_ uses signatures and behavioural analysis
- _Host-based firewalls and IDS_ filter connections, block ports used by malicious processes, and monitor traffic and file integrity
- _Application whitelisting_ prevents malware execution, though not every organization is predictable enough for it
- _Security testing_ tools scan for vulnerabilities and weak configurations

**Application security**
Review default data, scripts and accounts, and keep them only if required and secured (e.g. web servers' insecure example scripts).

Apply _minimum privilege_: a web server should not have write access to most web application files, so a vulnerability cannot be used to deface the site.

**Logging**
Logs report bad things that _already happened_ and are crucial for remediation and recovery.

What to log is decided during planning, based on security requirements and information sensitivity.

_Log rotation_ (compress, archive, delete) is needed as logs grow, in addition, _automated analysis_, such as IDSs, is preferred over unreliable manual review.

**Backup**
_Backup_ means regular copies for recovery over short periods, while _archive_ means long-term retention for legal and operational needs, and the two are often managed together.

Two trade-offs apply:
- _Online vs offline_: online is easier and cheaper but can be destroyed in an attack
- _Local vs remote_: local backups are lost in a calamity such as fire or flood

### Case studies

| Area                          | Linux/Unix                                     | Windows                                            |
| ----------------------------- | ---------------------------------------------- | -------------------------------------------------- |
| Updates and configuration     | Package managers, `/etc` and user config files | Windows Update, Registry and Group Policy          |
| Identity and authentication   | passwd, shadow, groups, PAM                    | Local accounts/SAM, Active Directory               |
| Access control                | rwx, ACLs, capabilities; SELinux/AppArmor      | ACLs, SIDs, privileges, mandatory integrity levels |
| Privilege management          | Limit root, SUID/SGID, prefer capabilities     | UAC, restricted administration, service accounts   |
| Network and host protection   | nftables, application control via MAC          | Windows Firewall, Defender, application control    |
| Logging and monitoring        | journald/syslog, log rotation and auditing     | Windows Event Log, auditing                        |
| Isolation and data protection | chroot, namespaces, MAC, encrypted filesystems | Service isolation, BitLocker/EFS                   |

### Virtualization
The **hypervisor** is the software between the hardware and the virtual machines (VMs) that acts as a _resource broker_, it abstracts the physical resources (processor, memory, network, storage) and lets multiple VMs run on one host.

**Types of virtualization (hypervisors)**
- _Type 1 (native)_: the hypervisor is loaded directly on the physical server and controls the hardware, with VMs as guest OSs
- _Type 2 (hosted)_: the hypervisor runs on a host OS and relies on it to access hardware
- _Containers (application virtualization)_: a container engine on a host OS gives applications isolated environments that _share the same kernel_, with smaller overhead

**Native vs hosted**
_Native_ usually performs better (no extra host OS) and is usually more secure: fewer layers to protect, no vulnerable host OS, and no host users able to access VM images.

_Hosted_ is convenient on clients because the machine need not be dedicated to VMs (e.g. developers running Unix, Linux and Windows on one host).

**Virtualization security**
- _VM escape_: a hypervisor vulnerability could let VMs or virtualized applications reach the hypervisor, other VMs or the host OS
- _Host OS attack_: a host OS vulnerability could expose guest OS images
- _Upside_: separating services into different VMs or containers confines vulnerabilities to that VM or container
- _Downside_: flaws in the virtualization layers could give full control of the physical server or host OS

**Hypervisor and infrastructure security**
Secure the hypervisor like an OS: isolated installation, clean media, regular (automatic) patching, no unused services, unused hardware disconnected.
>Only administrators should access it, locally or from a separate network.

_Management traffic_ (administration) and _application traffic_ (VMs and their applications) should ideally be separated using different physical interfaces, VLANs or SDNs.

**Virtual firewalls**
- _VM bastion host_: a separate VM running firewall, IDS and IPS services that monitors the VMs' virtual network interfaces
- _VM host-based firewall_: the guest OS uses host-based protection as on physical hardware
- _Hypervisor firewall_: built into the hypervisor. It is more efficient (no competition with VMs for resources) and in principle more secure (invisible to other VMs), but it adds complexity to the hypervisor

