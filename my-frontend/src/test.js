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

export { http_req };
