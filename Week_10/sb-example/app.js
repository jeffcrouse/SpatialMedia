

var Spacebrew = require('spacebrew')


//
// Now start up the Spacebrew client
//

var server = "sandbox.spacebrew.cc";
var name = "Clock";
var description = "Jeff's Node test!";
var sb = new Spacebrew.Client( server, name, description );

sb.addPublish("tick", "string", "The tick of a clock!");  // create the publication feed

var i = 0;
setInterval(function(){
  var newString = "The time is now "+i;
  sb.send("tick", "string", newString);   // send string to spacebrew
  i++;
}, 1000);

// connect to spacbrew
sb.connect();

