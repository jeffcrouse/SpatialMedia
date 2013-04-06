
/**
 * Module dependencies.
 */

var express = require('express')
	, http = require('http')
	, path = require('path')
	, twilio = require('twilio')
	, Spacebrew = require('spacebrew')
	, WordPOS = require('wordpos')
    , wordpos = new WordPOS()


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

//Twilio request authentication
app.post('/twiml', function(req, res) {
    if (twilio.validateExpressRequest(req, 'ced5bbb0b7f9f5ffe416abe9ff6b4f0b')) {
        res.type('text/xml');
        var twilioResponse = new twilio.TwimlResponse();
        twilioResponse.say(phoneMessage, {voice:'woman', language:'en-gb'});
        res.send(twilioResponse.toString());
    } else {
        res.send('you are not twilio.  Buzz off.');
    }
});

http.createServer(app).listen(app.get('port'), function(){
	console.log("Express server listening on port " + app.get('port'));
});



//
// Set up Spacebrew to accept strings ont he "words" channel
//
var server = "sandbox.spacebrew.cc";
var name = "Twilio Voice Caller";
var description = "";
var sb = new Spacebrew.Client( server, name, description );
sb.addSubscribe("words", "string");
sb.onStringMessage = onStringMessage;
sb.connect();



var client = require('twilio')('ACcc854bb5309b0308c6f6af4aa3ececf3', 'ced5bbb0b7f9f5ffe416abe9ff6b4f0b');
var adjectives = [];
var phoneMessage = "";
function onStringMessage(name, value) {
	if(name=="words") {
		wordpos.getAdjectives(value, function(result){
			
			result.forEach(function(word){
				if(word.length > 5) adjectives.push( word )
			});
		    console.log( adjectives );

			if(adjectives.length > 15) {
				//Place a phone call, and respond with TwiML instructions from the given URL
				client.makeCall({
				    to:'+16462465999', // Any number Twilio can call
				    from: '+13473217570', // A number you bought from Twilio and can use for outbound communication
				    url: 'http://4zsw.localtunnel.com/twiml' // A URL that produces an XML document (TwiML) which contains instructions for the call
				}, function(err, responseData) {
				    console.log(responseData.from); 
				});
				phoneMessage = adjectives.join(' ');
				adjectives = [];
			}
		});
	}
}



