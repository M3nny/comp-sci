## Key-value stores
A **key-value** pair is a tuple composed by two strings, in this way data can be retrieved with constant complexity by key.

This method is simple and good for data intensive applications, but the application is responsible for combining key-value pairs into more complex objects.
>See [DynamoDB](https://aws.amazon.com/dynamodb/), [Redis](https://redis.io/).

### MapReduce
These kind of stores are great for lookups, but are not optimized for aggregations or complex queries over large datasets, that's where **MapReduce** comes in.

MapReduce is designed to process massive amounts of data across many servers, it involves four steps:
- **Split** inputs into various servers
- Compute a **map** function on each input subset
- **Group** all intermediate values by key
- Iterate over groups and **reduce** values of each group

![[MapReduce.png|600]]

**Optimizations** that can be made to this approach are:
- Compute the **map and reduce in parallel**
- **Compute the data at the server at which it is allocated** (reduce network traffic)
- **Combine intermediate results** instead of sending them all (see image below)

![[Optimized MapReduce.png|600]]

---
## Document stores
They are related a to key-value stores, but instead of a string as a value, they store an object which _usually_ is a JSON object.

This model does not support foreign keys, but it can associate an id to each document, that can be referenced inside other documents.
>See [[02 - MongoDB|MongoDB]].

