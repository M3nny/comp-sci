In many cases, data arrives as a continuous **stream** (e.g. network packets, logs), and we **cannot store the entire stream** in memory, so we see each element once, and use it to update a compact summary that is a **sketch**, and then discard the element.

At any point in time, we must be able to answer a query about what we've seen so far.

Key **performance metrics** for a streaming algorithm are:
- **Working space**: how much memory it uses
- **Delay per element**: how long it takes to process each new item as it arrives
- **Probability of correctness**: many streaming algorithms are _randomized_, they are _correct with high probability_ but not always with certainty
- **Approximation ratio**: some problems can only be solved approximately, this measures how close the answer is to exact

### Pattern matching on strings
The classical problem is that we have a fixed text, we index it first and then query it efficiently.

The streaming variant of this problem is that now the stream contains the pattern first, then the text:
- $y=y_1,...,y_n$: **pattern** of length $n$
- $x=x_1,...,x_n$: **text** of length $m\geq n$

Every time a new text character $x_i$ arrives, we must immediately report whether the pattern $y$ matches the last $n$ characters of the text so far (i.e. if $y$ is a suffix of $x_1,...,x_i$).

The **naive solution** takes $O(n)$ space, we just keep a sliding window of the last $n$ text characters.

### Polynomial hashing
Recall [[10 - Hashing#Polynomial hashing|polynomial hashing]], which is used to **fingerprint** a string $A$ of length $n$ into a single number using:
$$\kappa_{q,z}=\left(\sum_{i=1}^nA[i]\cdot z^{n-1}\mod q\right)$$
This compresses the entire pattern into one integer, using $O(1)$ space, and to checker whether the pattern matches the last $n$ text characters, we just compare $\kappa(y)$ with $\kappa(x_{i-n+1},...,x_i)$.
![[Polynomial hashing pattern matching.png|500]]
But, there's a problem: to **update** the sliding window hash when a new character $x_{i+1}$ arrives, we need to drop the oldest character $x_{i-n+1}$ from the hash, the formula to do so is:
$$\kappa(x_{i-n+2},...,x_{i+1})=\kappa(x_{i-n+1},...,x_i)\cdot z-x_{i-n+1}\cdot z^n+x_{i+1}\mod q$$
![[Polynomial hashing pattern match update.png|600]]
This requires knowing $x_{i-n+1}$, which is the character that entered the window $n$ steps ago.

Since we've already discarded it, we'd have to keep all $n$ recent characters, putting us back at $O(n)$ space.

>[!Example]
>When a new character $x_{i+1}$ arrives, the window shifts:
>- Old window: $x_{i-n+1}, ..., x_i$
>- New window: $x_{i-n+2}, ..., x_{i+1}$
>
>Let's call the old hash
>
>$$H_{\text{old}} = k(x_{i-n+1}, ..., x_i)$$
>
>In the polynomial form:
>$$H_{\text{old}}=x_{i-n+1} z^{n-1}+x_{i-n+2} z^{n-2}+\cdots+x_i z^0$$
>
>To get the new hash, we want to:
>1. Remove the contribution of $x_{i-n+1}$ (the character leaving the window)
>2. Shift all remaining terms up by one power of $z$
>3. Add the new character $x_{i+1}$ at power $z^0$
>
>Step 2 is the problem, since it is achieved by multiplying $H_{\text{old}}$ by $z$:
>
>$$H_{\text{old}} \cdot z=x_{i-n+1} z^n+x_{i-n+2} z^{n-1}+\cdots+x_i z^1$$
>
>Now subtract the outgoing character term and add the incoming one:
>
>$$H_{\text{new}}=H_{\text{old}} \cdot z-x_{i-n+1} z^n+x_{i+1}\mod q$$
>Which is the formula the we described above.

### Porat & Porat's algorithm
We don't need to store the last $n$ characters, instead, **maintain a collection of $O(\log n)$ hashes** that together let us reconstruct any needed window hash on demand.

Assume $n=16$, the algorithm maintains $\log n+1=5$ sets, named $W_0,...,W_4$.
The set $W_i$ stores the positions where the **prefix of the pattern of length $2^i$ occurs within the last $2^{i+1}$ characters of the text**, in other words:
- $W_0$: tracks where the $1$-character pattern prefix $y_1$ appears in the last $2$ text characters
- $W_1$: tracks where the $2$-character prefix $(y_1,y_2)$ appears in the last $4$ text characters
- $W_2$: tracks where the $4$-character prefix appears in the last $8$ text characters
- $W_3$: tracks the $8$-character prefix in the last $16$ characters
- $W_4(=W_{\log n})$: tracks the full $16$-character pattern in the last $32$ characters, a non empty $W_4$ means a match was found

**Initializing the sets**
As the pattern arrives, the algorithm computes and stores the hashes of the pattern prefixes of lengths $2^0,...,2^{\log n}$, that's $\log n+1$ hashes, which is easy to do in $O(\log n)$ space.
![[Porat & Porat sets.png|700]]


**Updating the sets**
When a new text character $x_{i+1}$ arrives, three things happen for each set $W_i$:
1. _Delete expired occurrences_: the window for $W_i$ covers only the most recent $w^{i+1}$ text characters, if the oldest occurrence in $W_i$ has fallen outside this window, it is removed
2. _Insert new occurrence (for $W_0$)_: check whether $x_{i+1}$ equals $y_1$ (the first character of the pattern), if yes, add position $i+1$ to $W_0$
3. _Promote occurrences up the hierarchy_: an occurrence at position $r$ in $W_i$ can be "promoted" to $W_{i+1}$ if the text substring of length $2^{i+1}$ starting at $r$ matches the corresponding pattern prefix, this requires comparing their hashes, if the check passes, $r$ is added to $W_{i+1}$

Continuing the previous example, suppose that after $16$ text characters, the state is:
$$W_0=\{16\}, w_1=\{14\}, w_2=\{11\}, w_3=\{3,7\}$$
Character $x_{17}=\text b$ arrives, so $W_0$ gains $17$ since $b=y_1$, but no promotions yet.
![[Porat & Porat update 1.png|7000]]

Character $x_{18}=\text a$ arrives:
- Position $16$ exists its window, as well as position $14$
- $a\neq y_1$, so $17$ is not added to $W_0$ again
- $17$ is promoted to $W_1$ since $text[17,...,18]=\text{"ba"}$ matches $y_1,y_2$
- $11$ is not promoted from $W_2$ to $W_3$ since $text[11,...,18]\neq y_1,...,y_8$
- $3$ is checked in $W_3$: $text[3,18]$ matches the full pattern, with pattern occurrence found at position $3$
![[Porat & Porat update 2.png|700]]
$$\downarrow$$
![[Porat & Porat update 3.png|700]]

### Representing sets in constant space
How can $W_i$ occupy only $O(1)$ space if it could contain up to $2^{i+1}$ integers?

The key insight is that **occurrences are periodic**.
If a string $A$ of length $2^i$ occurs three or more times inside a string $B$ of length $2^{i+1}$, then $B$ _must_ be periodic (with the period equal to the gap between occurrences).

>[!Tip] Non-regular occurrences
>A consequence of the Fine and Wilf periodicity lemma is that if occurrences aren't evenly spaced, additional forced occurrences arise that fill in the gaps and make the pattern regular.

Any arithmetic progression $\{r_1,r_1+p,r_1+2p,...\}$ with $t$ elements, can be stored as just the triple $(r_1,t,p)$, which is constant space regardless of $t$.
- **Delete front**: $\{r_1+p,...\}\to(r_1+p,t-1,p)$
- **Append to end**: $\{...,r_t,r_{t+1}\}\to(r_1,t+1,p)$

These are the only two operations needed on each $W_i$, so in total all sets together use $O(\log n)$ words of space.

### Computing the hash of the text window
When performing a promotion check (e.g., does $text[11..18]$ match $y_1…y_8$?), we need the hash of that specific text window, but we don't have the text anymore.

The trick is to **store three auxiliary hashes**, where for each level $i$ we maintain:
- $A$: the _hash of the entire stream_ so far $\kappa(x_1,...,x_i)$, easy to update with each new character, just multiply by $z$ and add $x_i$
- $B$: for each $W_i$ with at least two occurrences, store $\kappa(x_{r_1},...,x_{r_2-1})$, which is the _hash of the segment between the first and second occurrence_, this is used to update $C$ when the leftmost occurrence disappears
- $C$: for each $W_i$ with at least one occurrence, store $\kappa(x_1,...,x_{r_1-1})$, which is the _hash of all text before the first occurrence_ $r_1$, this lets us peel off the prefix

![[Porat & Porat hashes.png|700]]

To get the window hash we use $A$ and $C$ hashes.
To get $\kappa(x_{11},...,x_{18})$ given $\kappa(x_1,...,x_{18})$ and $\kappa(x_1,...,x_{10})$:
$$\kappa(x_{11},...,x_{18})=\kappa(x_1,...,x_{18}k)-\kappa(x_1,...,x_{10})\cdot z^8\mod q$$

![[Porat & Porat hashes 2.png|700]]

This is a property of polynomial hashing, we can subtract a prefix hash (scaled appropriately) to isolate any suffix/window.

All hashes $A,B,C$ can be updated in $O(1)$ per character per level, for a total of $O(\log n)$ update time per character across all levels.

#### Summary
Exact pattern matching on streams can be solved with:
- $O(\log n)$ words of working space
- $O(\log n)$ update time per character
- Correctness with high probability (due to randomized hashing)

