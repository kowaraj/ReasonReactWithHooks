const express = require('express')
const app = express()

app.get('/', function(req, res) { 
  res.send({ hello: 'there' })
})

app.get('/test1', function(req, res) { 
  res.send({ reply: 'requested page is /test1' })
})

app.listen(3000, () => 'Listening at http://localhost:3000')
