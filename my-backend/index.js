const express = require('express')
const app = express()

app.get('/', function(req, res) { 
    console.log("GET: /");
    res.send({ hello: 'there' })
})


app.get('/test', 
	function(req, res) {
	    console.log("GET: /test");
	    
	    // Set CORS headers
	    res.setHeader('Access-Control-Allow-Origin', '*');
	    res.setHeader('Access-Control-Request-Method', '*');
	    res.setHeader('Access-Control-Allow-Methods', 'OPTIONS, GET');
	    res.setHeader('Access-Control-Allow-Headers', '*');
	    if ( req.method === 'OPTIONS' ) {
		res.writeHead(200);
		res.end();
		return;
	    }

	    res.send({ reply: 'requested page is /test1' })
	})

app.get('/test1', function(req, res) {
    console.log("GET: /test1");
    res.send({ reply: 'requested page is /test1' })
})

app.listen(3000, () => 'Listening at http://localhost:3000')
