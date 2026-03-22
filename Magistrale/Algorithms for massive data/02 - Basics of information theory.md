Let's consider a string of length $n$ over the alphabet $\{A,C,G,T\}$ containing one occurrence of $A,C,G$ and with the remaining letters being equal to $T$.

The **IT lower bound** for encoding such string would be:$\log\binom{n}{3}\cdot3!=O(\log n)$ bits, because we only need to encode where those $3$ rare characters are placed among the $T$'s, but the [[01 - Suffix trie#The suffix array|suffix array]] still takes $n\log n$ bits, which is still an exponential gap between the compressed text and the SA.

### Worst case entropy
The IT lower bound has a formal name.
Let $\mathscr{U}$ be a universe of objects, then the **worst-case entropy** of $\mathscr{U}$ is:
$$\mathscr H_{wc}=\lceil\log_2(|\mathscr U|)\rceil$$
It represents the _minimum number of bits needed to distinguish between all objects_ in $\mathscr U$.

This is because if we have a universe of $|\mathscr U|$ distinct objects, and we want to assign each one a unique binary code in order to tell them apart, we know that with $k$ bits we can form exactly $2^k$ distinct codes, so we would need at least $2^k\geq|\mathscr U|$ bits, that is $k\geq\log_2(|\mathscr U|)$, and since $k$ must be an integer, we round it up, and that's $\mathscr H_{wc}$.

>[!Note]
>Since $\mathscr H_{wc}(\mathscr U)$ bits is a very strong requirement, we'll be happy to use a negligible amount of extra space:
>$$\mathscr H_{wc}\cdot(1+o(1))=\mathscr H_{wc}(\mathscr{U})+o(\mathscr H_{wc}(\mathscr U))$$

As an example we can take **bitvectors**, in particular the set of all length-$n$ bitvectors, with exactly $m$ ones they achive a worst-case entropy of $\log_2\binom{n}{m}\approx m\log(\frac{n}{m})$, which is the same formula as for the sets of integers, this is not a coincidence, since there's a direct bijection between them: a bitvector of length $n$ with $m$ ones is exactly a way of marking which $m$ positions out of $n$ are "inside of the set".
>So any compression scheme for bitvectors works for integer sets too.

### Empirical entropy
For a string $S$ of length $n$, let $n_c$ be the number of occurrences of character $c$, then:
$$H_0(S)=\sum_{c\in\Sigma}\frac{n_c}{n}\log_2\frac{n}{n_c}$$

This is the definition of [[00 - Information and inference#Entropy|entropy]] applied to strings with finite length (and after applying the logarithms rule to remove the '-').
It gives the **average bits per character** needed if we assign each character a code based on how often it appears.

Let's consider the set $\mathcal S(n_1,...,n_\sigma)\subseteq[\sigma]^n$ of strings of length $n$ over alphabet $[\sigma]$ such that each $s\in\mathcal S$ contains $n_c$ occurrences of each character $c\in[\sigma]$.

For example $12122132\in\mathcal S(3,4,1)$: we have $\binom{n}{n_1}$ combinations for placing character $1$, then $\binom{n-n_1}{n_2}$ combinations for placing character $2$, then $\binom{n-n_1-n_2}{n_3}$ combinations for placing character $3$,..., hence we get:
$$\begin{align}
&\binom{n}{n_1}\cdot\binom{n-n_1}{n_2}\cdot\binom{n-n_1-n_2}{n_3}\dotsi=\\
&=\frac{n!}{n_1!\cancel{(n-n_1)!}}\cdot\frac{\cancel{(n-n_1)!}}{n_2!\cancel{(n-n_1-n_2)!}}\cdot\frac{\cancel{(n-n_1-n_2)!}}{n_3!\cancel{(n-n_1-n_2-n_3)!}}\dotsi=\\
&=\frac{n!}{n_1!n_2!\dotsi n_\sigma!)}=\binom{n}{n_1,...,n_\sigma}=\\
&=\mathscr H_{wc}(\mathcal S(n_1,...,n_\sigma))
\end{align}$$

This is called **multinomial coefficient**, and by applying Stirling's approximation of the factorial, one can prove that:
$$\mathscr H_{wc}(\mathcal S(n_1,...,n_\sigma))=nH_0-O(\sigma\log n)$$
showing that worst-case entropy and zero-order empirical entropy are **essentially identical**.

Since $\mathscr H_{wc}(\mathcal S(n_1,...,n_\sigma))\approx nH_0$ and we know that $\mathscr H_{wc}(\mathcal S(n_1,...,n_\sigma))$ is a hard lower bound for encoding strings with character frequencies $n_1,...,n_\sigma$, then $H_0$ (bits) is a lower bound for encoding each character of those strings, **on average**.

>[!Info]
>There exist encodings able to compress $S$ to $nH_0$ bits, and the intuition is the following:
>- Encode frequent characters using few bits
>- Encode rare characters using many bits
>- For decodability, no code must be prefix of another code (prefix-free codes)

As an example let's take $S=abracadabra$, $n=11$, $\sigma=5$, if we pack every character in $\lceil\log\sigma\rceil=3$ bits, then $S$ is packed in $n\lceil\log\sigma\rceil=33$ bits, the _empirical entropy_ is equal to $nH_0\approx 22.4$ bits, and by suing a prefix-free code, such as:
$$a\to1,b\to010,r\to011,c\to000,d\to001$$
then the encoding takes only $23$ bits, which is very close to the optimum.
>This is literally how [[00 - Information and inference#Huffman coding|Huffman codes]] work.

### Higher-order empirical entropy
$H_0$ only looks at raw characters frequencies, but natural language has much more structure, for example the character that precedes "ompile" is almost certainly 'c', and we can **exploit** this **context**.

Let $S\in\Sigma^n$, choose $k\leq n$ and let $w\in\Sigma^k$.
We define $S_w$ as the **concatenation of all characters preceding occurrences** of $w$ in $S$, from the leftmost to rightmost occurrence (circular: $S[1]$ is preceded by $S[n]$).

>[!Example]
>Let $S=aababbabab$ and $k=2$, these represent sequences of characters that appear immediately before each occurrence of $w$ in $S$.
>- $S_{ab}=abbb$
>- $S_{bb}=a$
>- $S_{aa}=b$
>- $S_{ba}=abaa$

The idea now is to group characters by their $k$-character context (the $k$ character that follow them), for each context $w$ we collect all character that precede an occurrence of $w$ into a "bucket" $S_w$ and apply $H_0$ inside each bucket.
>$S_w$ will likely have very low $H_0$ since those characters have the same context.

Let $S\in\Sigma^n$ and $k\leq n$, then the **k-th order empirical entropy** of $S$ is:
$$H_k(S)=\sum_{w\in\Sigma^k}\frac{|S_w|}{n}H_0(S_w)$$

The goal of an **entropy compressor** is to achieve $nH_k+o(n\log\sigma)$ bits.
$$\log_2\sigma\geq H_0\geq H_1\geq H_2\geq ...$$
>The entropy decreases as we use more context.

>[!Tip] Extra: $k$ upper bound.
>We cannot use $k=n$ because the compressor has to also store the model itself (all the context statistics) which costs $\sigma^k bits$, and for $k\geq\log_\sigma(n)$ this overhead dominates and we lose the benefit, hence $k$ must stay below $\log_\sigma(n)$.

### Beyond entropy
Entropy is not always a good measure of compressibility, the theoretical perfect measure is the **Kolmogorov complexity** $\kappa(S)$, which is the length of the shortest program that generates $S$, but $\kappa(S)$ is **uncomputable**, so in other words, no algorithm can calculate it in general, which means no compressor can ever be truly optimal.

Another crucial thing to keep in mind is that worst-case entropy applies to the **worst-case** in a set of objects, **not individually** on every object in that set.

>[!Example]
>Consider the set $X_n$ of all strings of length $n$ containing $n/2$ characters equal to 'a' and $n/2$ characters equal to 'b', then:
>$$\mathscr H_{wc}(X_n)=\log\binom{n}{n/2}\approx n$$
>This means that any compressor that compresses strings of $X_n$ must use $n$ bits for _at least one_ of those strings.
>However, some strings of $X$ are more compressible than others, for example: $aaaaaabbbbbb\in X_{12}$.

Intuitively $H_k$ <u>cannot capture repetitions longer than</u> $k$ .
Let's take as an example $S=0101010101010101$ ($n=16$), this string should be extremely compressible, but $H_0(S)=16$ because $0$ and $1$ are equally frequent, in fact by _adding context_, we can see that $H_1(S)\approx0$ does better.

But even with the following pattern $H_1(0110 0110 0110 0110)=16$, we see that $H_k$ can get fooled.
>Entropy with context $k$ only sees patterns of length $k+1$, but repetitions may depend on longer structures.

A key observation is that doubling a string ($TT$) does not change its empirical entropy at all:
$$|TT|\cdot H_0(TT)=2n\cdot H_0(T)$$

even though $TT$ is obviously twice as compressible as $T$ if we just store $T$ once and say "repeat twice".

