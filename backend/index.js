var express = require('express')
var app = express()

var env = require('dotenv').config()
var assert = require('assert')

var MongoClient = require('mongodb').MongoClient;
var format = require('util').format;

var mongoStr = process.env.DB_CONNECT

// MongoClient.connect(mongoStr, function(err, db) {
//   var records = db.collection('events').find().sort({published_at:-1}).limit(2);
//   records.toArray(function(err, docs) {
//     console.log(docs);
//     db.close();
//   })
// });

app.get('/latest', function(req, res) {
  var latestRecord = {};
  MongoClient.connect(mongoStr, function(err, db) {
    var records = db.collection('events').find().sort({published_at:-1}).limit(2);
    records.toArray(function(err, docs) {
      latestRecord = docs[0];
      console.log(latestRecord);
      res.send(latestRecord);
      db.close();
    })
  });
})


app.get('/', function(req, res){
  res.sendFile(__dirname + '/public/index.html');
})

app.listen(3000, function() {
  console.log('Example app listening on port 3000!')
})
