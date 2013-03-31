
/**
 * Module dependencies.
 */

var express = require('express')
	, routes = require('./routes')
	, user = require('./routes/user')
	, http = require('http')
	, path = require('path')
	, util = require('util')
	, spotify = require('spotify')
	, spotify_app = require('spotify-node-applescript')
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

var server = "sandbox.spacebrew.cc";
var name = "Jeff's Spotify";
var description = "This app controls the Spotify app on Jeff's laptop.  Send strings to influence the next song.";
var sb = new Spacebrew.Spacebrew.Client( server, name, description );
sb.addSubscribe("words", "string");
sb.onStringMessage = onStringMessage;

sb.connect();

var now = new Date().getTime()
var nextSongChange = now + (1000 * 10);

function onStringMessage( name, value ){
	//console.log("[onStringMessage] string message received %s = %s", name, value);
	var now = new Date().getTime();
	if(name=="words" && now > nextSongChange) {
		
		var matches = value.match(/"([^"]+)"/i);
	    if(matches && matches.length>0) 
	    {
	    	console.log( "QUOTE:  " + matches[1] );
			spotify.search({ type: 'track', query: matches[1] }, function(err, data) {
				if ( err ) {
					console.log('Error occurred: ' + err);
				} else {
					var track = null;
					for(var i=0; i<data.tracks.length; i++) {
						track = data.tracks[i];
						if( track.album.availability.territories.indexOf('US') > -1) break;
					}

					if(track!=null) {
						console.log(track);
						console.log( util.format('PLAYING: %s - %s %s %s', track.name, track.href, track.artists[0].name, track.popularity) );
						spotify_app.playTrack(track.href, function(){
							console.log("PLAYING!");
							nextSongChange = now + (1000 * 10);
						});
					} else {
						console.log("Couldn't find a song!");
					}
				}
			});
	    } else console.log("No quoted string found in "+value);
	}
}




