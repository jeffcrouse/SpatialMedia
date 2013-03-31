
/**
 * Module dependencies.
 */

var express = require('express')
	, routes = require('./routes')
	, user = require('./routes/user')
	, http = require('http')
	, path = require('path')
	, Spacebrew = require('./sb-1.0.3')
	, util = require('util')
	, exec = require('child_process').exec

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
// Set up Spacebrew to accept strings ont he "words" channel
//
var server = "sandbox.spacebrew.cc";
var name = "Simple 'say' Subscriber";
var description = "";
var sb = new Spacebrew.Spacebrew.Client( server, name, description );
sb.addSubscribe("words", "string");
sb.onStringMessage = onStringMessage;
sb.connect();


//
// What do we do when we get an incoming string?
//
var voices = ["Agnes", "Kathy", "Princess", "Vicki", "Victoria", "Bruce", "Fred", "Junior", "Ralph", "Zarvox", "Cellos"];
var speaking = false;
function onStringMessage( name, value ){
	if(name=="words" && !speaking) {
		
		var matches = value.match(/"([^"]+)"/i);
		if(matches) {
			var quote = matches[1];
			console.log( quote );
			var voice = voices[Math.floor(Math.random()*voices.length)];
			var cmd = util.format('say -v %s -r 200 "%s"', voice, quote);
			
			speaking = true;
			exec(cmd, function(err, stdout, stderr){
				speaking = false;
			}); // exec
		}
	}
}

