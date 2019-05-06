const express = require('express');
const webpack = require('webpack');
const webpackDevMiddleware = require('webpack-dev-middleware');

const app = express();
const config = require('./webpack.config.js');
const compiler = webpack(config);

// Tell express to use the webpack-dev-middleware and use the webpack.config.js
// configuration file as a base.
app.use(webpackDevMiddleware(compiler, {
  publicPath: config.output.publicPath
}));

function cb(x) {
    console.log("I'm the callback. Args = " + x);
}

function http_req(url, cb) {
    const http = require('http');
    http.get(url, (resp) => {
        let data = '';

        // A chunk of data has been recieved.
        resp.on('data', (chunk) => {
            data += chunk;
        });

        // The whole response has been received. Print out the result.
        resp.on('end', () => {
            //console.log(JSON.parse(data).explanation);
            cb(data);
        });

    }).on("error", (err) => {
        console.log("Error: " + err.message);
    });
}

app.get('/test2', function(req, res) { 
    console.log("GET: /test2");
    res.send({ hello: 'there - Webpack MIDDLEWARE -test2 ' })
})

app.get('/test', function(req, res) { 
    console.log("GET: /test");
    http_req("http://localhost:3000/test2", cb)
    res.send({ hello: 'there - Webpack MIDDLEWARE ' })
})

app.get('/test3', function(req, res) { 
    console.log("GET: /test3");
    http_req("http://neo4j:1234@0.0.0.0:7475", cb)
    res.send({ hello: 'there - Webpack MIDDLEWARE -test3  ' })
})


// Serve the files on port 3000.
app.listen(3000, function () {
  console.log('Example app listening on port 3000 !?\n');
});
