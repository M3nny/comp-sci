Given the set $C\subseteq\mathbb{R}^n$, we'll say that it is **convex** if:
$$\alpha x+(1-\alpha)y\in C,\quad \forall x,y,\in C,\quad\forall\alpha\in[0,1]$$

That is, given **any** pair of point in the set $C$, the segment of points (convex combination) that connects them is inside of the set.
![[Insiemi convessi.svg|500]]

We also **assume** that the empty set $\emptyset$ is convex since it does not negate the definition of a convex set.

Given the convex sets $C_1,...,C_m$, then their **intersection**:
$$C=C_1\cap...\cap C_m$$
is also convex.

**Proof**: we want to prove that the segment $[x,y]$ is inside the intersection of the sets, if this were true, then $x,y\in C_1$ which is convex, it follows that $[x,y]\subseteq C_1$, it is possible to make the same reasoning for each set.
Given that $[x,y]$ is contained in each set separately, then it is contained in the intersection, that is $[x,y]\subseteq C$.

