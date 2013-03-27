
/**
 * Module dependencies.
 */

var express = require('express')
  , routes = require('./routes')
  , user = require('./routes/user')
  , http = require('http')
  , path = require('path')
  , Spacebrew = require('./sb-1.0.3')
  , twitter = require('ntwitter') // https://github.com/AvianFlu/ntwitter

var app = express();

app.configure(function(){
  app.set('port', process.env.PORT || 3000);
  app.set('views', __dirname + '/views');
  app.set('view engine', 'ejs');
  app.use(express.favicon());
  app.use(express.logger('dev'));
  app.use(express.bodyParser());
  app.use(express.methodOverride());
  app.use(express.cookieParser('your secret here'));
  app.use(express.session());
  app.use(app.router);
  app.use(express.static(path.join(__dirname, 'public')));
});

app.configure('development', function(){
  app.use(express.errorHandler());
});

app.get('/', routes.index);
app.get('/users', user.list);

http.createServer(app).listen(app.get('port'), function(){
  console.log("Express server listening on port " + app.get('port'));
});


//
// 1.  Start up the Spacebrew client
//

var server = "sandbox.spacebrew.cc";
var name = "Spatial Media Tweeter";
var description = "A stream of twets that contain the words spatial, media, nyu, or ITP.";
var sb = new Spacebrew.Spacebrew.Client( server, name, description );

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
var filters = {'track':'spatial,media,nyu,itp'};
twit.stream('statuses/filter', filters, function(stream) {
	stream.on('data', function (data) {
		console.log(data.text);
		if(sb._isConnected) {
			sb.send("tweet", "string", data.text); 
		}
	});
});


/*
// https://dev.twitter.com/docs/api/1.1/get/statuses/sample
twit.stream('statuses/sample', function(stream) {
  stream.on('data', function (data) {
    console.log(data.text);
    console.log("\n\n\n------------------\n\n\n");
  });
});
*/

