var http = require("http");
var url = require("url");
var staticserve = require("./staticserve");

function routeBasic(handlers, pathname, query, postData, resp, defaultHandler) {
	if (typeof handlers[pathname] === 'function') {
		console.log("Route received for : " + pathname);
		handlers[pathname](query, postData, resp);
	} else	{
		console.log("No route found for : " + pathname + ". Trying default handler...");
		//staticserve.serve(pathname, resp);
		if (defaultHandler !== undefined) {
			defaultHandler(pathname, resp);
		}
	}
}

function routeService(handlers, pathname, query, postData, resp) {
	routeBasic(handlers, pathname, query, postData, resp, function() {
		resp.writeHead(403); // forbidden access when you try to access services
		resp.end();	
	});
}

function routeHttp(handlers, pathname, query, postData, resp) {
	routeBasic(handlers, pathname, query, postData, resp, staticserve.serve);
}

function httpStart(port, handlers, routeFunction) {
	function onRequest(req, resp) {
		var method = req.method;		// GET;POST;PUT;DELETE
		var urlObj = url.parse(req.url, true);	// Parse the url AND the query
		var pathname = urlObj.pathname;
		var query = urlObj.query;
		
		console.log("Request received for " + pathname);
		req.setEncoding("utf8");

		var postData = "";
		req.addListener("data", function(chunk) {
			postData += chunk;
		});

		req.addListener("end", function() {
			routeFunction(handlers, pathname, query, postData, resp);
		});
	}
	
	http.createServer(onRequest).listen(port);
	console.log("Webserver launched on port "+port);
}

exports.start = httpStart;
exports.routeService = routeService;
exports.routeHttp = routeHttp;
