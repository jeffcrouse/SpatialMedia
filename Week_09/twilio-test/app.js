
/**
 * Module dependencies.
 */

var express = require('express')
	, routes = require('./routes')
	, user = require('./routes/user')
	, http = require('http')
	, path = require('path')
	, twilio = require('twilio')

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

//Twilio request authentication
app.post('/twiml', function(req, res) {
    if (twilio.validateExpressRequest(req, 'ced5bbb0b7f9f5ffe416abe9ff6b4f0b')) {
        var resp = new twilio.TwimlResponse();
		resp.say('Welcome to Twilio!');
		resp.say('Please let us know if we can help during your development.', {
			voice:'woman',
			language:'en-gb'
		});
        res.type('text/xml');
        res.send(resp.toString());
    }
    else {
        res.send('you are not twilio.  Buzz off.');
    }
});

http.createServer(app).listen(app.get('port'), function(){
	console.log("Express server listening on port " + app.get('port'));
});






// Step 1:
// Learn about localtunnel!  http://progrium.com/localtunnel/
// localtunnel -k ~/.ssh/id_rsa.pub 3000
// http://twilio.github.com/twilio-node/#validateExpressRequest
// https://www.twilio.com/user/account
// VERBS: http://www.twilio.com/docs/api/twiml


// http://twilio.github.com/twilio-node/
// IMPORTANT:  Don't Read the docuemntation at https://github.com/sjwalter/node-twilio  !!!
var client = require('twilio')('ACcc854bb5309b0308c6f6af4aa3ececf3', 'ced5bbb0b7f9f5ffe416abe9ff6b4f0b');


// //Send an SMS text message
// client.sendSms({

//     to:'+16462465999', // Any number Twilio can deliver to
//     from: '+13473217570', // A number you bought from Twilio and can use for outbound communication
//     body: 'word to your mother.' // body of the SMS message

// }, function(err, responseData) { //this function is executed when a response is received from Twilio

//     if (!err) { // "err" is an error received during the request, if any

//         // "responseData" is a JavaScript object containing data received from Twilio.
//         // A sample response from sending an SMS message is here (click "JSON" to see how the data appears in JavaScript):
//         // http://www.twilio.com/docs/api/rest/sending-sms#example-1

//         console.log(responseData.from); // outputs "+14506667788"
//         console.log(responseData.body); // outputs "word to your mother."

//     }
// });


//Place a phone call, and respond with TwiML instructions from the given URL
client.makeCall({

    to:'+16462465999', // Any number Twilio can call
    from: '+13473217570', // A number you bought from Twilio and can use for outbound communication
    url: 'http://4qj4.localtunnel.com/twiml' // A URL that produces an XML document (TwiML) which contains instructions for the call

}, function(err, responseData) {

    //executed when the call has been initiated.
    console.log(responseData.from); 

});
