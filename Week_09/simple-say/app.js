
/**
 * Module dependencies.
 */

var Spacebrew = require('spacebrew')
	, util = require('util')
	, exec = require('child_process').exec

//
// Set up Spacebrew to accept strings ont he "words" channel
//
var server = "sandbox.spacebrew.cc";
var name = "Simple 'say' Subscriber";
var description = "";
var sb = new Spacebrew.Client( server, name, description );
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
			//var cmd = util.format('say -v %s -r 200 "%s"', voice, quote);
			var cmd = "say -v "+voice+" -r 200 "+'"'+quote+'"';
 			console.log( cmd );

			speaking = true;
			exec(cmd, function(err, stdout, stderr){
				speaking = false;
			}); // exec
		}
	}
}

