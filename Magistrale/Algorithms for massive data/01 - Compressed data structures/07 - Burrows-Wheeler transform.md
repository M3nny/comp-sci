The **Burrow-Wheeler Transform (BWT)** has a simple idea with powerful consequences.

Let's take as an example: $S=mississippi\$$.

**Step 1: compute all string rotations**
![[BWT rotate.png|400]]

**Step 2: sort the strings lexicographically**
In this step we move the rows in order for them to be sorted lexicographically (not by sorting each string internally, otherwise it would lead to every string to be equal).
![[BWT sort.png|400]]

and that's it, the **BWT** is the **last column** of this matrix.
$$\text{BWT(mississippi\$)=ipssm\$pissii}$$
![[BWT column.png|400]]

### Relation between BWT and the suffix array
Because `$` is smaller than all other characters, **sorting rotations is equivalent to sorting the suffixes of the string**.
The BWT is therefore **deeply connected to the [[01 - Suffix trie#The suffix array|suffix array]]**.

Characters in the BWT are **sorted according to the lexicographic order of the suffix that follows them**, this means that characters that **appear in similar contexts** get grouped together (e.g. all `i`'s that are followed by `ssi` appear consecutively).

This is essentially [[02 - Basics of information theory#Higher-order empirical entropy|high-order entropy]] since BWT **clusters characters** by their $k$-character context, which is why it compresses so well.

Since sorting rotations equals to sorting suffixes (thanks to `$`), then the text position of the $i$-th matrix row is precisely $SA[i]$, which gives us:
$$BWT[i]=S[SA[i]-1]$$

![[BWT-SA.png|400]]

**BWT is a compressed SA**, instead of storing $SA[i]$ (which costs $\log n$ bits each), we store the single character $S[SA[i]-1]$ which costs only $H_k$ bits (will be proved).
>BWT can be computed via SA.

### The LF property
We don't want to store the full $n\times n$ matrix (which would be quadratic space), we are going to **store instead the first $F$ column and the last column** $L=BWT$.

Moreover, **$F$ can be retrieved from $L$ by simply sorting $L$** (since $F$ is just the sorted version of all characters).

**Lemma**: the $i$-th occurrence of character $c$ in $L$ corresponds to the same text position as the $i$-th occurrence of $c$ in $F$.
This is because both $L$ and $F$ contain occurrences of each character $c$, and in both cases those occurrences are sorted by the suffix that follows them.
>This is the same reason why [[05 - Compressed suffix array#The core idea|the psi function]] works.

As an example: the first $i$ in $L$ is in the same text position of the first $i$ in $F$, that is, the last $i$ of `mississipp[i]$`.

**The LF property defines a function** $LF:[n]\to[n]$ mapping each row of the sorted matrix to another row, it makes us move **backwards** in the text.

>[!Example]
>Starting from row 1, applying $LF$ moves to the row corresponding to the character before `$` in the text:
>- `mississippi[$] -> F=$ -> L=i`
>- `mississipp[i]$ -> F=i -> L=p`
>- `mississip[p]i$ -> F=p -> L=p`
>- `mississi[p]pi$ -> F=p -> L=i`
>- `...`

Conversely, $FL=LF^{-1}$ moves forward in the text, and it turn out that:
$$FL=\psi$$
which enables us to re-use a lot of operations from the [[05 - Compressed suffix array|CSA]].

### Compression boosting
We know that a [[06 - Wavelet trees|wavelet tree]] over a string $S$ uses $nH_0+o(n\log \sigma)$ bits (zero-order compression).

**Claim**: $WT(BWT(S))$ uses $nH_k+o(n\log\sigma)$ bits, for a small (logarithmic in $n$) context length $k$.
>We are able to achieve **high-order compression** by just permuting $S$.

**Proof**
As noted earlier, the BWT clusters characters of $S$ according to the contexts of length $k$  following them, for any $k\geq0$.

For context word $w$ of length $k$, define $S_w$ as the substring of $BWT(S)$ corresponding to all rows whose first $k$ characters are $w$.
The BWT is literally the concatenation of all these context-grouped substrings:
$$BWT(S)=S_{w_1}S_{w_2}...S_{wt}$$
![[BWT of a string.png|400]]

For example with $k=2$:
$$BWT(S)=\underbrace{S_{$m}}_{i}\underbrace{S_{i$}}_{p}\underbrace{S_{ip}}_{s}\underbrace{S_{is}}_{sm}\underbrace{S_{mi}}_{$}\underbrace{S_{pi}}_{p}\underbrace{S_{pp}}_{i}\underbrace{S_{si}}_{ss}\underbrace{S_{ss}}_{ii}$$

We recall the definition of [[02 - Basics of information theory#Higher-order empirical entropy|k-th order entropy]]:
$$H_k(S)=\sum_{w\in\Sigma^k}\frac{|S_w|}{n}H_0(S_w)$$
Each $S_w$ is a group of characters that share the same $k$-length context, so $H_0(S_w)$ is small withing each group.

Then we recall the [[06 - Wavelet trees#Final result|final theorem of wavelet trees]]:
$$\begin{align}
WT\_size(S_1,...,S_t)&\leq\left(\sum_{i=1}^tn_iH_0(S_i)\right)+o(\log\sigma)+O(t\sigma\log n)\\
&=nH_K+o(n\log\sigma)+O(\sigma^{k+1}\log n)
\end{align}$$
to eliminate the $\sigma^{k+1}\log n$ term, we pick the largest $k$ such that $\sigma^{k+1}\log n=o(n)$, which gives:
$$k=\lfloor\max\{0,\alpha\log_\sigma n-1\}\rfloor=\Theta(\log_\sigma n)\quad\forall \alpha\in]0,1[$$
**Final theorem**
$WT(BWT(S))$ uses $nH_k+o(n\log\sigma)+O(\sigma\log n)$ bits, simultaneously for all $k\geq0$, where $k=\Theta(\log_\sigma n)$.
>On constant sized alphabets (e.g. DNA uses $\sigma=4$), this simplifies to $nH_k+o(n)$ bits.

### Searching the BWT
Since $FL=\psi$ and we can compute $\psi$ in $O(\log\sigma)$ time from $F$ and $L$, we can solve **count queries** via binary search on the SA in:
- Time: $O(m\log n\cdot\log\sigma)$
- Space: $nH_k+o(n\log\sigma)+O(\sigma\log n)$

This is **better space than CSA**, but **slower** than the CSA $O(m\log n)$ time.
