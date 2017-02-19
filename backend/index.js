var express = require('express')
var app = express()

var env = require('dotenv').config()
var assert = require('assert')

var MongoClient = require('mongodb').MongoClient;
var format = require('util').format;

var mongoStr = process.env.DB_CONNECT

app.get('/latest', function(req, res) {
  MongoClient.connect(mongoStr, function(err, db) {
    var records = db.collection('events').find().sort({published_at:-1}).limit(10);
    records.toArray(function(err, docs) {
      res.send(uniqueDeviceIds(docs));
      db.close();
    })
  });
})

app.get('/', function(req, res){
  res.sendFile(__dirname + '/public/index.html');
})

app.listen(3000, function() {
  console.log('Backend listening on port 3000!')
})

function uniqueDeviceIds(events) {
  var resultArray = {};
  events.forEach(function(event) {
    if (!(event.device_id in resultArray)) {
      resultArray[event.device_id] = event;
    }
  })
  return resultArray;
}
