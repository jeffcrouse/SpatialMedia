
/**
 * Module dependencies.
 */

var  util = require('util')
	, spotify = require('spotify')
	, spotify_app = require('spotify-node-applescript')
  	, Spacebrew = require('spacebrew')

var now = new Date().getTime()
var nextSongChange = now + (1000 * 10);


var server = "sandbox.spacebrew.cc";
var name = "Jeff's Spotify";
var description = "This app controls the Spotify app the machine on which it is running. Send strings to influence the next song.";
var sb = new Spacebrew.Client( server, name, description );
sb.addSubscribe("words", "string");
sb.onStringMessage = function( name, value ){

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

sb.connect();



