/**
 * Module dependencies.
 */

var express = require('express')
  , routes = require('./routes')
  , user = require('./routes/user')
  , http = require('http')
  , path = require('path')
  , Spacebrew = require('./sb-1.0.3')


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
// Now start up the Spacebrew client
//

var server = "sandbox.spacebrew.cc";
var name = "Clock";
var description = "Jeff's Node test!";
var sb = new Spacebrew.Spacebrew.Client( server, name, description );

sb.addPublish("tick", "string", "The tick of a clock!");  // create the publication feed

var i = 0;
setInterval(function(){
  var newString = "The time is now "+i;
  sb.send("tick", "string", newString);   // send string to spacebrew
  i++;
}, 1000);

// connect to spacbrew
sb.connect();




