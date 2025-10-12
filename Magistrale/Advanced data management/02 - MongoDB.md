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

#### Example case
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
```json
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

