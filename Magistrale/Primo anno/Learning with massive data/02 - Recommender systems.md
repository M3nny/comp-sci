Recommending popular stuff may not be sufficient, we want to understand what a user is looking for.

Some **quality measures** we are looking after, are:
- How _expensive is to process our data_ and build the recommender system?
- How _expensive is to produce recommendations_ at run time?
- Are recommendations _novel and interesting_ (i.e. **serendipity**)?
- What when we know little about the users (i.e. **cold-start problem**)?

### Content-based recommender systems
In this type of recommendation system, we are going to <u>recommend items that are most similar to the user profile</u> (e.g. songs).

A user is the set of items he interacted with, hence we define:
- The item **representation**
- The **user profile**, by averaging the items representations
>This can be generalized to many applications, such as: movies, web-pages, ...

We define the **users** as the set $U$, and the **items** being recommended with the set $I$.

We model text by using the **vector-space model**, where:
- Each item $x\in I$ is a vector of size $N$, where normalization techniques such as [[02 - Document ingestion#Stemming and lemmatization|stemming and lemmatization]] are applied
- $x[t]=tf(t,x)\cdot idf(t)$
	- $tf(t,x)$ is the frequency of term $t$ in item $x$
	- $idf(t)$ is the [[01 - Boolean model#Inverted index|inverse document frequency]] across the corpus of documents

The **profile of a user** $u\in U$ is the average of items $I_u$ he interacted with:
$$u=\frac{1}{|I_u|}\sum_{x\in I_u}x$$
Given a user $u$ and an item $x$, their similarity is given by the **cosine similarity** of the two vectors:
$$\cos(u,x)=\frac{u\cdot x}{||u||\cdot||x||}=\frac{\sum_tu[t]\cdot x[t]}{\sqrt{\sum_tu[t]^2}\cdot\sqrt{\sum_tx[t]^2}}$$
the recommender system, then returns the **top-k most similar** items to the user profile.

Wrapping up:
- **Easy processing for the corpus** and cheap model for the user
- **Inference is not cheap** when searching the nearest neighbor among the collection of documents
- **Small serendipity**, which is tied to text similarity
- The user should **interact with at least one item** to solve the cold-start problem

Another issue is that text representation has some non trivial issues, for example: _synonymy_.

### User based collaborative filtering
We introduce the **feedback** provided by the user as the **rating** $R$, which is expressed as a matrix $|U|\times|I|$ where each entry $R[u,i]$ stores the user feedback.

The idea is to find **similar users** instead of similar items, which can lead to _greater serendipity_.

Users can rate items in many ways:
- **Explicitly**: by expressing a vote (e.g. like, stars)
- **Implicitly**: by analyzing the time spent on a page, or clicks on a result page

The **sketch of the algorithm** is:
1. Find a set of neighbors $N(u)$ of users similar to $u$
2. Exploit the rating of users $N(u)$ to build recommendations for $u$

We recall that the profile of a user $u$ is a vector of size $|I|$, where $u[i]=r$ if the user $u$ gave a rating of $r$ to the item $i$.
It is possible to see $u$ as the row $R[u,:]$ of the rating matrix.

We use **Pearson correlation** to _find similar users_, it is a normalized measure of _linear correlation_, informally it is large ($-1$ / $1$) if both users $u$ and $v$ decrease/increase similarly below/above their mean $\overline u$ and $\overline v$:
$$\rho(u,v)=\frac{cov(u,v)}{\sigma_u\sigma_v}=\frac{\sum_i(u[i]-\overline u)(v[i]-\overline v)}{\sqrt{\sum_i(u[i]-\overline u)^2}\sqrt{\sum_i(v[i]-\overline v)^2}}$$

We **avoid the cosine similarity** because it would lead to false positives, for example, let's consider two users who have rated three songs:
- User $P$: $(5.6, 6, 5.6)$
- User $Q$: $(1,2,3)$
Their cosine similarity is $\cos(P,Q)=0.92$, but they are not similar, instead the Pearson correlation is $\rho(P,Q)=0$ which is what we expected.

For **building recommendations** we predict a **ranking score** $s_{ui}$, which for each item $i\in I$ considers the ratings of users in $N(u)$ and weights those ratings by the users' similarity with $u$.
$$s_{ui}=\frac{\sum_{v\in N(u)}(v[i]-\overline v)\cdot\rho(u,v)}{\sum_{v\in N(u)} |\rho(u,v)|}$$
>Eventually $s_{ui}$ is used to rank every item in $I$ and select the top-k.

We can even predict the rating by the user $u$ as follows:
$$r_{ui}=\overline u+s_{ui}$$

Wrapping up:
- **Building the model is difficult**, since user similarity is expensive ($O(|U|^2)$) and when a user is added similarities should be recomputed
- **Inference is cheap** if neighbor search is pre-computed
- The **serendipity is great**
- We **need a sufficiently large set of ratings** for a new user/item

Most users rate only a tiny fraction of items, hence the matrix is **sparse**.

### Item-based collaborative filtering
An item $i$ is represented by a vector of size $|U|$, then $i[u]=r$ if the user $U$ gave a rating of $r$ to the item $i$.
We can see $i$ as the column $R[:,i]$ of the rating matrix.

The **rationale** is: to estimate the rating for an item $i$ for user $u$, what are the ratings that user $u$ gave to items similar to $i$?

The **sketch of the algorithm** is the following:
1. Find a set $N(i)$ of other items _rated by_ $u$ and _similar to_ $i$
2. Exploit the ratings of user $u$ for items in $N(i)$ to compute a score for $i$

In this case we return back to the _cosine similarity_, since Pearson correlation is not clear.
But this time we adjust it by the user mean rating $\overline u$ (i.e. **severity**), in this way we get the **adjusted cosine similarity**:
$$\text a-\cos(i,j)=\frac{\sum_u(i[u]-\overline u)(j[u]-\overline u)}{\sqrt{\sum_u(i[u]-\overline u)^2}\sqrt{\sum_u(j[u]-\overline u)^2}}$$
then, the predicted rating will be:
$$r_{ui}=\frac{\sum_{j\in N(i)}R[u,j]\cdot (\text a-\cos(i,j))}{\sum_{j\in N(i)} |\text a-\cos(i,j)|}$$

Wrapping up:
- $|I|$ is usually smaller than $|U|$, this **makes the computation cheaper** than the user-based method (computation is done off-line)
- **Inference is cheap** if neighbor search is pre-computed
- **Serendipity is less than user-based**, as the final ranking depends on ratings by the current user
- We **need a sufficiently large set of ratings** for a new user/item

The matrix is still sparse, but items are more likely to share common raters, so item similarity is easier to compute and more reliable than user similarity.
