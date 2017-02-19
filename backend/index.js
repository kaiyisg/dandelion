var express = require('express')
var app = express()

var env = require('dotenv').config()
var assert = require('assert')

var MongoClient = require('mongodb').MongoClient;
var format = require('util').format;

var mongoStr = process.env.DB_CONNECT

var insertDocuments = function(db, callback) {
  var collection = db.collection('test_events');
  // Insert some documents
  collection.insertMany([
    {a : 1}, {a : 2}, {a : 3}
  ], function(err, result) {
    assert.equal(err, null);
    assert.equal(3, result.result.n);
    assert.equal(3, result.ops.length);
    console.log("Inserted 3 documents into the collection");
    callback(result);
  })
}

MongoClient.connect(mongoStr, function(err, db) {
  assert.equal(null, err);
  console.log("Connected successfully to server");

  insertDocuments(db, function() {
    db.close();
  });
});

app.get('/', function(req, res){
  res.sendFile(__dirname + '/public/index.html');
})

app.listen(3000, function() {
  console.log('Example app listening on port 3000!')
})
