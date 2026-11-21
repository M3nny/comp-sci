The best **best defense** against software vulnerabilities is to prevent them occurring, **software security** refers to writing safe code and correctly handling program I/O so to prevent vulnerabilities.

- _Prevention_: improved methods for specifying and building software
- _Detection_: better and more efficient testing techniques
- _Mitigation_: more resilient architectures, defense in depth

The definition of **defensive programming** is "designing software so it continues to function even when under attack", for this reason software should _detect_ erroneous conditions results from attack, and:
- Continue executing safely, or
- Fail gracefully

The key rule is to _never assume anything_, always handle any possible error states, since vulnerabilities are often triggered by inputs that differ dramatically from what is usually expected.

Security is hardly achieved if not a design goal from the beginning, defensive programming requires awareness of _consequences of failures_ and _attacker techniques_.

### Handling program input
**Assuming input is valid is dangerous**, Heartbleed (OpenSSL) is a perfect example: the requested data size was never checked against the available data, causing _buffer over-read_.

**Interpretation** is a second source of trouble, through _charset confusion_ (bypassing blacklists with alternate encodings) and _type confusion_ (input treated as a different type than intended).

**Injection attacks**
The attacker injects a payload that changes the program's flow of execution, typically in scripting languages that pass input to helper programs.

- _Command injection_: a Perl CGI script runs `finger -sh $user`, input like `Alice; echo Attack!` runs extra commands with the server's privileges, a whitelist regex (`/^\w+$/`) helps, but the better fix is not invoking the shell at all
- _Code injection_: a PHP script does `include($_GET["p"])` with `allow_url_include` enabled, the attacker passes a URL and arbitrary remote code is included and executed
- _Cross-site scripting (XSS)_: the attacker injects a script (e.g. in a comment) that runs in the honest site's context with full privileges, bypassing the same-origin restriction (e.g. steal cookies by redirecting to the attacker's server)

**Validating input syntax**
- _Whitelisting_ compares input against what is wanted (e.g. alphanumeric usernames), it is hard to bypass if strict enough
- _Blacklisting_ rejects or escapes known-dangerous values (e.g. `mysql_real_escape_string`, now deprecated), it can be bypassed, for instance with encodings

### Writing safe code
Buggy implementations break security even when the design is sound, as an example we pick a poor random number generator that in early Netscape allowed session keys to be broken.

**Data must be interpreted consistently**: strongly typed languages enforce this, while _loosely typed_ ones like C allow liberal casting and pointer manipulation that can crash a program or subvert execution.

**Correct use of memory**: heap memory must be released once a task is done, a _memory leak_ gradually exhausts memory, which an attacker can exploit for a DoS.

### Handling interaction with the environment
**Environment variables** are strings inherited from the parent process that affect behavior, such as `PATH`, `IFS` and `LD_LIBRARY_PATH`.

>[!Example]
>An ISP shell script, SUID root, strips the domain from a user identity using `sed` and `grep`.
>- _Attack:_ the attacker puts a directory of her own first in `PATH`, containing malicious `sed` and `grep`, so her code runs as root
>- _Naive fix:_ hardcode `PATH="/sbin:/bin:/usr/sbin:/usr/bin"` in the script
>- _Why it fails:_ the attacker sets `IFS` to include `=`, so the assignment is parsed as running a command named `PATH` with the path string as its argument

**Securing shell scripts** is very hard, but there are some recommendations:
- SUID on shell scripts is ignored on recent Unix systems
- Use a compiled _wrapper_ that sets the user and environment before invoking the script (e.g. Apache suEXEC)
- For programs, a similar attack uses `LD_LIBRARY_PATH` to load malicious libraries, modern systems ignore it for SUID programs, so the library path must be fixed at compile time

Custom environment variables should always be treated as **untrusted input**.
