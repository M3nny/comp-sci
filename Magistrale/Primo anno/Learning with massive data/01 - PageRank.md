**PageRank** computes the relevance of a Web page based on the link structure of the Web itself.

We can measure the importance of a node $i$ in a graph $G$ as the **sum of the importances of its neighbors**.

Let $\pi[i]$ be the importance of node $i$, then:
$$\pi[i]=\sum_{j\to i}\frac{\pi[j]}{o(j)}$$
where $o(j)$ is the **out-degree** of node $j$ (how many links page $j$ points to).
The division by $o(j)$ prevents a page from "multiplying" importance by linking to many pages, thus it distributes its importance equally among all outgoing links.


This definition is _recursive_, since page importance depends on the importance of other pages, the solution is to treat it as an iterative process:
1. Start with a random probability distribution $\pi^0$ (all pages equally likely)
2. Repeatedly apply the update rule: $\pi^{t+1}=M\pi^t$
3. Stop when the values converge

The matrix $M$ is defined as:
$$M[i,j]=\begin{cases}\frac{1}{o(j)}&\text{if }j\to i\\0&\text{otherwise}\end{cases}$$

It converges only if $G$ is **irreducible** (any page is reachable from any other) and **aperiodic** (no cycles of fixed length).
But the Web does not satisfy this criteria since it has _dead ends_ and _cycles_.

The solution to this problem introduces a **teleportation probability** $\beta$:
$$\pi^{t+1}=\beta M\pi^t+(1-\beta)\frac{1}{n}\quad\text{with}\quad M[i,j]=\begin{cases}\frac{1}{o(j)}&\text{if }j\to i\\\frac{1}{n}&\text{if }o(j)=0\\0&\text{otherwise}\end{cases}$$
with probability $\beta$ we follow $M$, and with probability $(1-\beta)$ we jump to a random node, this removes dead ends by "linking" them to every other node.

The PageRank $\pi$ is the stable state distribution of the above when $\pi^t=\pi^{t+1}$, this usually happens after less than 50 iterations.

Since an iteration is basically a matrix-vector product, let's assume the number of pages to be $N=10^{10}$, each iteration takes $N^2$ multiplications and $N^2$ additions, in total we have $50\cdot 10^{20}$ floating point operations (FLOPS), and assuming a modern processor with $1000$ GFLOPS, the total running time is $50\cdot10^{20}/10^{12}=5\cdot 10^9$ seconds, which is more than **150 years**.

Let's store $M$ in a sparse format, for each page $i$ we store the list of page IDs of incoming links.

**Clusters** are made of multicore nodes which host GPGPU boards and several disks at the various levels of the hierarchy, however, parallel algorithms must be carefully designed in order to exploit locality.

>[!Quote] Parallel programming
>"To put it quite bluntly: as long as there were no machines, programming
>was no problem at all; when we had a few weak computers, programming
>became a mild problem, and now we have gigantic computers, programming
>has become an equally gigantic problem."
>- E. Dijkstra, 1972 Turing Award Lecture

