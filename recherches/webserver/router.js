var serveStatic = require("./staticserve").serve;
var captors = require("./requestHandlers").captors;

function route(handle, pathname, resp, parameters, postData) {
	console.log("[ROUTER] Route received : " + pathname);

	if (typeof handle[pathname] === 'function') {
		handle[pathname](resp, parameters, postData);
	} else	{
		console.log("[ROUTER] No route found for " + pathname + ". Trying static serving...");
		serveStatic(pathname, resp);
	}
}

exports.route = route;
