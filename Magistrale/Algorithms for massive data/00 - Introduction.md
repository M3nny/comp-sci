Why yet another course on [[Strutture dati|algorithms and data structures]]?
This is because we've discussed big-O notation, but what if $O(n)$ has a really big $n$, which is bigger than the memory size?

In this course we'll see algorithms and compressed data structures used to handle bigger than memory data.

In the **traditional approach** we store all the data on the memory/disk and build a data structure over it, and then query it later.

In the **massive data paradigm** we are dealing with _streams of data_, we cannot fully store all of it.
- On-the-fly **lossless** compressed data structure
- On-the-fly **lossy** _sketch_ of the data

### The information-theoretic lower bound
Suppose having a set $S$ of $m$ integers drawn from a universe of size $n$, for example:
$$S=\{3,5,6,7\}\quad m=4\quad n=8$$
The number of such sets is equal to the [[Probabilità elementare#Combinazioni|binomial coefficient]] $\binom{n}{m}$, and if we want a binary encoding that is _injective_ (i.e. every set maps to a unique code), we need at least $\log_2\binom{n}{m}$.

This is because with $k$ bits we only have $2^k$ possible [[00 - Information and inference#Source coding|codewords]], and if there are more sets than codewords, we'll end up having two sets mapping to the same code, making decoding impossible.

To **losslessly encode** objects from a universe $U$, we need at least $\log_2(|U|)$ bits per object.

### Measuring space
In a typical algorithms course, space is measured in **words**, but since one word is equal to $\Theta(\log n)$ bits, $O(n)$ words actually means $\Theta (n\log n)$ _bits_.

Since this course is about compression, it measures space in _bits_ to be precise and avoid hiding constants behind big-O.
