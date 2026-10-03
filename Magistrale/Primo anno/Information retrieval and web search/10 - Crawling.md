Programs called **crawlers**, **spiders** or **harvesters** navigate the web automatically by _following hyperlinks_, fetching and storing content as they go.
The web can be seen as a directed graph where **pages are nodes** and **hyperlinks are edges**.

The simplest crawling algorithm starts with a few known **seed URLs**, then it  fetches and parses those pages, extracts any links they contain, and adds those links to a **queue**, this is then repeated with the URLs in the queue.

The **URL frontier** is the _name for this queue_ of discovered but not yet fetched URLs. The **unseen web** is everything that hasn't been reached yet.

### Crawl pipeline
A general crawl pipeline will have the following steps.
![[Crawl pipeline.png|400]]

**Fetch**
The crawler issues an HTTP request to retrieve the page, this is typically _multithreaded_ since many requests are being made at once.

**DNS lookup**
Before fetching, the crawler must resolve the URL's hostname to an IP address.
DNS lookups can have high latency, and standard OS DNS calls block, since only one can be in flight at a time.
Solutions include _caching recent DNS results_ and batching requests into a single resolver.

**Parse and URL normalization**
The fetched HTML is parsed to extract links, and _relative URLs are expanded_ into absolute URLs before they can be used.

**Seen content**
Since the web ha many _duplicated content_, before adding a page to the index, the crawler checks whether it has already seen the same content using a [[13 - MinHash#Jaccard similarity and MinHash|fingerprint]].

**URL filter**
Extracted URLs are checked against rules, for example obey to `robots.txt` restrictions, or ignore certain file types.

**Robots filter**
The `robots.txt` file is put at the root of the website and it's used to restrict access by the crawlers.

**Duplicated URL elimination**
Even if the content is new, the URL itself might already be queued or visited, this step removes redundant URLs before they enter the queue.

### Complications
Web crawling runs into many problems, between them, we have:
- **Malicious pages**: _spam pages_ can pollute the index, whilst _spider traps_ are dynamically generated infinite link sequences designed to keep a crawler busy forever
- **Scale**: everything must be distributed and parallelized
- **Politeness**: hammering a single server repeatedly can overload it, hence crawlers must space out requests to the same host
- **Variance**: network latency and bandwidth to remote servers is unpredictable
- **Depth**: how far into a site's URL hierarchy should we go?
- **Freshness**: pages change over time, so previously crawled pages need to be recrawled

Most importantly, every crawler **must** be **robust** (i.e. immune to traps and malicious behavior) and be **polite** (don't overload server).

Additional goals are scalability, efficiency, quality-first crawling, continuous operation, and extensibility to new protocols and formats.

And by politeness we distinguish, **explicit politeness** by respecting the `robots.txt` and **implicit politeness** by avoid hammering the website with requests.

>[!Example]
>No robot should visit any URL starting with `/site/temp/` except the robot called "searchengine":
>
>```
>User-agent: *
>Disallow: /site/temp/
>
>User-agent: searchengine
>Disallow:
>```

### Distributed crawling
Because a single machine can't handle the web, real crawlers run as a **cluster of nodes**, each responsible for a **partition of the URL space**.

URLs are typically assigned to nodes via **hash of the hostname**, so all pages of a site go to the same node, avoiding politeness coordination issues.

When a **node dies**, its **URLs are redistributed**.

![[Distributed crawling.png|400]]

There are three **communication strategies** between nodes:
- **Firewall mode**: each node only crawls its own partition and never sends links to other nodes, this is simple and with low overhead, but some pages may never be discovered if the only link to them crosses partition boundaries
- **Crossover mode**: like firewall mode, but nodes follow links even if they fall into another node's partition, leading to duplicate crawling (the same page gets fetched by multiple nodes)
- **Exchange mode**: nodes forward links to whichever node owns that partition, this ensures full coverage but adds communication overhead, and raises a coordination challenge for the distributed document fingerprint store (since content deduplication must now work across nodes)

### The URL frontier
The frontier has two competing goals:
- **Politeness**: don't flood a single server
- **Freshness**: prioritize pages that change often, like news sites

These conflict, since we might want to recrawl a news page every hour, but doing so too aggressively violates politeness.

For this reason there are two separate queues within the frontier:
- **Discovery queue**: for newly found pages not yet crawled, focused on expanding coverage
- **Refreshing queue**: for re-downloading already seen pages, focused on keeping the index current

### Revisit policy and freshness
Because the web is constantly changing, a crawler needs a strategy for **how often to revisit each page**, the two main metrics are:
- **Freshness** (boolean): is the local copy currently up to date?
- **Age** (continuous): how long has the local copy been out of date? $0$ if fresh, otherwise the time since the last modification

Intuitively one might think that we should revisit frequently changing pages more often (**proportional policy**).

But, a research (Cho and Garcia-Molina, SIGMOD 2000) found that a **uniform revisit schedule** that revisits all pages at the same rate regardless of how often they change, actually performs better at maximizing overall freshness.

The reason is that if a page changes every hour, visiting it every hour still misses most changes, so we better spread the crawl budget evenly.
<u>Pages that change too often should effectively be penalized</u> because they'll **always be stale anyway**.

In practice, search engines use **multiple refresh queues** with _different cadences_, in this way some sites are refreshed multiple times a day, others daily, weekly, or monthly.

### Hidden web crawling
Standard crawlers can only reach pages they find through links.

The **hidden web** (also called the deep web) includes pages that are **unlinked, private, or dynamically generated** in response to a form query.

For example, a flight search site only returns results when you submit an origin, destination, and date.
A specialized **hidden web crawler** addresses this by iteratively submitting domain specific queries to web forms and storing the result pages.

