Given the friendship directed graph $G$ of a social network, we want to fin all the pairs of users $(u,v)$ such that $v$ is a friend of a friend of $u$, that is, there exists an $x$ such that $u\to x\to v$ for some user $x$.

The intuition is to label $u\to x$ and $x\to v$ with the key $x$ so that they reach the same reduce, that is, one reduce per central node.
```python
def map(u, x): # user -> friend
	emit(x, (u, x)) # for triplets u -> x -> ?
	emit(u, (u, x)) # for triplets ? -> u -> x

def reduce(x, edges): # list of edges that insist on x
	for (a,b) in values: # for each
		for (c,d) in values: # pair of edges
			if (b==c):
				emit(a,d)
```

### Documents all pairs similarity
A document is a vector $d$ of $N$ distinct words in the corpus (lexicon), where documents have ids$\in[1,N_{docs}]$.
$d[i]$ stores the frequency of the term $i$ in document $d$, then $d$ is normalized by dividing it by its $L_2$ norm.

We use cosine similarity tom measure similarity between vectors:
$$s(a,b)=\sum_{i=1}^Na[i]\cdot b[i]$$
The problem is **finding all pairs such that their similarity $s$ is at least $\tau$**.

The key observation is that documents with similarity $s>0$ share at least one term.
The idea is then to attach a key $t$ to a document $d$ for each of its terms $<t_1,d>,<t_2,d>,...$ then if two documents have the same key $t$ it would mean that they at least one term in common and we can compute their similarity.
```python
def map (doc_id, document):
	for each term t in document:
		emit (t, [doc_id,document])

def reduce (t, docs: list[ [doc_id,document] ] ):
	for id1,d1 in docs:
		for id2,d2 in docs:
			if s(d1,d2)>=tau:
				emit ([id1, id2], s(d1,d2))
```
>The full document is sent from mappers to reducers to compute similarities.

If a document has $1000$ terms, then the document is **replicated** $1000$ times, in order to handle this we could use **prefix filtering**:
- Sort terms by decreasing frequency (or score) in the corpus
- Create the maximum document $d^*$ which stores the maximum score of terms in any document: $D^*[i]=\max_dd[i]$

There are a few observations, one is that if $d(d,d^*)<\tau$, then $d$ has no similar documents in the corpus, and second, let $b(d)$ be the largest term (id) such that:
$$\sum_{0\leq t\leq b(d)}d[t]\cdot d^*[t]<\tau$$
then, a document similar to $d$ must share with $d$ at least one term $t>b(d)$, **it is sufficient to check common terms beyond $b(d)$**.
```python
def map (doc_id, document):
	for each term t in sorted(document):
		if t>b(document):
			emit (t, [doc_id,document])

def reduce (t, docs: list[[doc_id,document]]):
	for id1,d1 in docs:
		for id2,d2 in docs:
			if s(d1,d2)>=tau:
				emit ([id1, id2], s(d1,d2))
```

But if two documents share $10$ terms after filtering, their similarity is computed $10$ times.

The solution is to use only one reducer to compute the similarity, but the two documents are replicated $10$ times with $10$ different keys may end up
in $10$ different reducers, the solution is to compute the similarity at the reducer which has the **key equal to the largest common term**.
```python
def map (doc_id, document):
	for each term t in sorted(document):
		if t>b(document):
			emit (t, [doc_id,document])

def reduce (t, docs: list[ [doc_id,document]]):
	for id1,d1 in docs:
		for id2,d2 in docs:
			if (t == max( intersect(d1,d2))):
				if s(d1,d2)>=tau:
					emit ([id1, id2], s(d1,d2))
```