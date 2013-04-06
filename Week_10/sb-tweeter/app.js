
var Spacebrew = require('spacebrew')
	, twitter = require('ntwitter') // https://github.com/AvianFlu/ntwitter



//
// 1.  Start up the Spacebrew client
//
var keywords = "I'm listening to";

var server = "sandbox.spacebrew.cc";
var name = "Keyword Tweeter";
var description = "A stream of twets that contain the words '"+keywords+"'";
var sb = new Spacebrew.Client( server, name, description );

sb.addPublish("tweet", "string", "A single tweet");  // create the publication feed
// connect to spacbrew
sb.connect();



//
// 2. Now set up Twitter and access the Twitter Stream API
//

// Configure Twitter
var twit = new twitter({
	consumer_key: 'CuJDkgecdDtVNVa3wrvtQ',
	consumer_secret: 't9zzya77qkm7UkFmgQ0rniCziT11PoaUEQCthYGezY',
	access_token_key: '761368-NJ95le3zIfMW5XbRXZrZeaFVjFZofEPT9UeQkRTq78',
	access_token_secret: 'kW6MCgVAy9ZV0uTYTc8RDAFY8INFOQIMKYU4ZBOUTM'
});


// Start the twitter stream 
// https://dev.twitter.com/docs/api/1.1/post/statuses/filter
var filters = { 'track':keywords };
twit.stream('statuses/filter', filters, function(stream) {
	stream.on('data', function (data) {
		console.log(data.text);
		if(sb._isConnected) {
			sb.send("tweet", "string", data.text); 
		}
	});
});