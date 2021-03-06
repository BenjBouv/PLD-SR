var logger = require('../logger');
var net = require('net');

function connectClient() {
	var client = net.createConnection(1234, "localhost");
	return client;
}

/*
 * REQUEST :
 * ============================================================================
SENSOR :
{
    “id” : “111111”,
    “type” : “1ZJU928”,
    "subject" : {
		"i" : 12212,
		"g" : 0 // patient : 0, piece : 1
	}
}
ACTUATOR :
{
    “id” : “111111”,
    “type” : “1ZJU928”,
    "subject" : [
		{
			"i" : 12212,
			"g" : 0 // patient : 0, piece : 1
		},
		{
			"i" : 1452,
			"g" : 1 // patient : 0, piece : 1
		}
	]
} 
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
{
    “state” : “ok”
} ============================================================================
 */
function addDevice(param, callback) {
	// Construct the query :
	var query = {};
		query.a = 1;
		query.i = param.id;
		query.t = param.type;
		query.s = param.subject;
	logger.info("Adding device : id = " + query.i + ", type = " + query.t + ", subject = " + query.s);
		
	// Send the query :
	var client = connectClient();
	client.on("error", function() {
		logger.error("Unable to connect to client");
		var response = {};
		response.status = "ko";
		callback(response);
	});
	client.on("connect", function() {
		logger.debug("[addDevice] Connected to the server");
		client.write(JSON.stringify(query), function() {
			logger.debug("[addDevice] message sent to the server");
			logger.info("Device added !");
			// Construct json response :
			var response = {};
			response.status = "ok";
			callback(response);
			client.end();
		});
	});
}

/*
 * REQUEST :
 * ============================================================================
{
    “id” : “111111”,
    “type” : “1ZJU928”
} ============================================================================
 *
 * RESPONSE :
 * ============================================================================
{
    “state” : “ok”
} ============================================================================
 */
function removeDevice(param, callback) {
	// Construct the query :
	var query = {};
		query.a = 2;
		query.i = param.id;
	logger.info("Removing device with id = " + query.i);
		
	// Send the query :
	var client = connectClient();
	client.on("connect", function() {
		logger.debug("[removeDevice] Connected to the server");
		client.write(JSON.stringify(query), function() {
			logger.debug("[removeDevice] message sent to the server");
			logger.info("Device removed !");
			// Construct json response :
			var response = {};
			response.status = "ok";
			callback(response);
			client.end();
		});
	});
}

/*
 * REQUEST :
 * ============================================================================
{
    “id” : “11111111”,
    "type" : "12321",
    “active” : “true”,
    “value” : 1.1
} ============================================================================
 *
 * RESPONSE :
 * ============================================================================
{
    “state” : “ok”
} ============================================================================
 */
function setActuator(param, callback) {
	// Construct the query :
	var query = {};
		query.a = 3;
		query.i = param.id;
		query.t = param.type;
		query.e = param.active ? 1 : 0;
		query.v = param.value;
	logger.info("Setting actuator with id = " + query.i + ", type = " + query.t + ", active = " + query.e + ", value = " + query.v);
		
	// Send the query :
	var client = connectClient();
	client.on("error", function() {
		logger.error("Unable to connect to client");
		var response = {};
		response.status = "ko";
		callback(response);
	});
	client.on("connect", function() {
		logger.debug("[setActuator] Connected to the server");
		client.write(JSON.stringify(query), function() {
			logger.debug("[setActuator] message sent to the server");
			logger.info("Actuator set !");
			// Construct json response :
			var response = {};
			response.status = "ok";
			callback(response);
			client.end();
		});
	});
}

exports.addDevice = addDevice;
exports.removeDevice = removeDevice;
exports.setActuator = setActuator;
