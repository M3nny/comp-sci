**MongoDB** is a nosql database, which is **document oriented**, it scales well horizontally over standardized hardware, and it provides ad hoc queries and **indexes** as well as **secondary indexes**.

While _RDBMSs allow for long running multi-row transactions_, this distributes poorly, because it requires locking and coordination, MongoDB also does't work well with multi document transaction, but the fact is that it is easy to atomically update a document in a distributed system.

While in SQL we have **joins**, in MongoDB we have **embedded documents**, to store related data in the same document.

| RDBMS       | MongoDB           |
| ----------- | ----------------- |
| Table       | Collection        |
| Row         | Document          |
| Column      | Field             |
| Join        | Embedded document |
| Foreign key | Reference         |
| Partition   | Shard             |
>RDBMSs objects mapped to MongoDB.

Stored data is in the **BSON** format representing an extended JSON with additional datatypes, which is **binary encoded** to be _lightweight_ and easily _navigable_.

Unlike RDBMSs, MongoDB **stores data together** (by having nested documents), this improves data locality, and frequently read documents are stored inside a **in-memory cache**, this means that "hot data" has a faster retrieval time.

### CRUD operations
Below are some basic [mongoose](https://www.mongodb.com/docs/drivers/node/current/integrations/mongoose-get-started/) operations.
**Create**
- `db.collection.insert({...document})`: saves a new document
- `db.collection.save({...document})`: upserts a document
**Read**
- `db.collection.find(<query>, {...document})`: returns a cursor, which is a pointer to data that matches the query
- `db.collection.findOne(<query>, {...document})`: returns the first document that matches the query
**Update**
- `db.collection.update(<query>, {...document}, <options>)`: updates a new document
**Delete**
- `db.collection.remove(<query>, {...document})`: removes the documents that match the query

##### Example case
We want to store locations, users, manage users logins into these locations and be able to check-in users in the locations.

A location may be structured as:
```json
location_1 = {
	name: "10gen HQ”,
	address: "17 West 18th Street 8th Floor”,
	city: "New York”,
	zip: "10011”,
	latlong: [40.0,72.0],
	tags: [“business”, “cool place”],
	tips: [
		{
			user:"nosh",
			time:6/26/2010,
			tip:"stop by for office hours on Wednesdays from 4-6pm"
		},
		{.....},
	]
}
```

We may also want to find nearby locations, so we **set an index** in the `latlong` coordinates, specifying that it is a 2D-geospatial index:
```ts
db.locations.ensureIndex({latlong:"2d"})
db.locations.find({latlong:{$near:[40,70]}})
```

We can create other indexes such as:
```ts
// Data sorted in ascending order (1) or descending (-1)
db.locations.ensureIndex({tags:1})
db.locations.ensureIndex({name:1})
```

We add users' tips with:
```ts
db.locations.update(
	{name:"10gen HQ"}, // Query
	{
		$push: { // Insert a nested document
			tips: {
				user:"nosh",
				time:6/26/2010,
				tip:"stop by for office hours onWednesdays from 4-6"
			}
		}
	}
}
```

We can model users as:
```ts
user1 = {
	name: "nosh"
	email: "nosh@10gen.com",
	// ObjectId reference to locations collection
	checkins: [4b97e62bf1d8c7152c9ccb74, 5a20e62bf1d8c736ab]
}
```

To find where a user checked in:
```ts
checkin_array = db.users.findOne(
	{...}, // Query
	{checkins: true} // Fields to return
).checkins;

db.location.find({_id:{$in: checkin_array}}) 
```

---
### Aggregation pipelines
An **aggregation pipeline** in MongoDB is a series of operations to analyze data within a collection, we can think of it as the equivalent for the `join` and `goup by` operator in SQL, but more flexible.

Common aggregation stages are:
- **Match**: filters documents (like `where` in SQL)
- **Project**: selects specific fields or computes new ones
- **Group**: groups documents and performs aggregation (i.e. `sum`, `avg`)
- **Lookup**: performs joins with another collection
- **Unwind**: deconstructs arrays into individual documents
```ts
db.orders.aggregate([
	{$match: { status: "A" }},
	{$group: { _id: "$cust_id", total: { $sum: "$amount" }}}
])
```

#### Window aggregation
In **window aggregates** we can perform calculation over a sliding range of documents.

Let's consider the following example:
```ts
db.cakeSales.aggregate([
    {
        $setWindowFields: {
            partitionBy: "$state",
            sortBy: { orderDate: 1 },
    		output: {
                cumulativeQuantityForState: {
    			  $sum: "$quantity",
    			  window: { documents: ["unbounded", "current"] }
    			}
            }
        }
	}
])
```
- `$setWindowFields`: adds a new computed field based on window functions
- `$partitionBy`: splits data into groups by state
- `sortBy`: within each state, documents are sorted chronologically by `orderDate`
- `output`: defines the new field that we are creating, inside that we are summing the quantity field, and the window starts from the first document, and goes up to the current document that we are processing

Visually the operation is computed as it follows:
```json
// Input data
[
	{ state: "CA", orderDate: ISODate("2023-01-01"), quantity: 5 },
	{ state: "CA", orderDate: ISODate("2023-01-02"), quantity: 7 },
	{ state: "CA", orderDate: ISODate("2023-01-03"), quantity: 3 },
	{ state: "NY", orderDate: ISODate("2023-01-01"), quantity: 10 },
	{ state: "NY", orderDate: ISODate("2023-01-03"), quantity: 2 }
]

// Processed data
[
	{ state: "CA", orderDate: "2023-01-01", quantity: 5, cumulativeQuantityForState: 5 },
	{ state: "CA", orderDate: "2023-01-02", quantity: 7, cumulativeQuantityForState: 12 },
	{ state: "CA", orderDate: "2023-01-03", quantity: 3, cumulativeQuantityForState: 15 },
	{ state: "NY", orderDate: "2023-01-01", quantity: 10, cumulativeQuantityForState: 10 },
	{ state: "NY", orderDate: "2023-01-03", quantity: 2, cumulativeQuantityForState: 12 }
]
```

#### Bucket aggregation
Unlike the window aggregation, which computes values based on a sliding window, in a **bucket aggregate** we can specify the boundaries of the aggregated computation.

We can briefly say that bucket aggregates have _static ranges_, whilst window aggregates have a _dynamic range_.

```ts
db.people.aggregate([
	{
		$bucket: {
			groupBy: "$age", // field to bucket
			boundaries: [0, 18, 30, 50, 100], // bucket edges
			default: "Unknown", // bucket for out-of-range ages
			output: {
				count: { $sum: 1 }, // count how many docs in each bucket
				names: { $push: "$name" } // collect names in each bucket
			}
		}
	}
])
```

We can apply this query to the following data:
```json
// Input data
[
	{ name: "Alice", age: 17 },
	{ name: "Bob", age: 22 },
	{ name: "Charlie", age: 35 },
	{ name: "Diana", age: 42 },
	{ name: "Eve", age: 68 },
	{ name: "Frank", age: 75 }
]

// Output data
[
	{ _id: 0,  count: 1, names: ["Alice"] },
	{ _id: 18, count: 1, names: ["Bob"] },
	{ _id: 30, count: 2, names: ["Charlie", "Diana"] },
	{ _id: 50, count: 2, names: ["Eve", "Frank"] }
]
```

---
### Sharding
In a normal database, when the requests exceed the database read capacity, it is possible to make replicas of the same database in order to scale horizontally.

With **sharded deployment** it is possible to split a large dataset across multiple servers, called **shards**, in this way the data can be processed in parallel.

In MongoDB it is possible to specify a **shard key**, which is a field that determines how MongoDB splits data (i.e. split by the field "region").

This approach is transparent to the applications and allows to better balance incoming traffic.