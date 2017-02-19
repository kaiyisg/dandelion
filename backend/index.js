var express = require('express')
var app = express()

app.get('/', functio(req, res){
  res.send('Waiting for Signal')
})

app.listen(3000, function() {
  console.log('Example app listening on port 3000!')
})
