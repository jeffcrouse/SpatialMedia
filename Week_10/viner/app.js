
var  vine = require("./vine")
	, Spacebrew = require('spacebrew')


// Connect to the database
var dburl = "mongodb://spatial_media:LogicalDebateN64@ds035127.mongolab.com:35127/spatial_media";
var collections = ["vines"]
var db = require("mongojs").connect(dburl, collections);


var keywords = "NYU"
var getVines = function() {
	// Use the vine module to get vines
	vine.getVines(keywords, function(err, vines){
		// Loop through all of the vines we get back
		vines.forEach(function(vine) {

			// Search the database for the vine link
			console.log("Searching for "+vine.link);
			db.vines.find({link: vine.link}, function(err, vines) {
				if( err ) console.log(err);
				else if(vines.length==0) {
					// If it's not already in the database, save it.
					console.log("Saving "+vine.link);
					db.vines.save(vine, function(err, saved) {
						if( err || !saved ) console.log("Vine not saved");
						else console.log("Vine saved");
					});
				} 
			});
		});
	});
}

setInterval(getVines, 5000);




var server = "sandbox.spacebrew.cc";
var name = "Viner";
var description = "Sends out vines that have been posted on Twitter";
var sb = new Spacebrew.Client( server, name, description );
sb.addPublish("vineVideo", "string", "The URL of a single vine video.");
sb.addPublish("vineTweet", "string", "A tweet that accompanied a vine post.")


var sendVines = function() {
	db.vines.count(function(error, nbDocs) {
		var skip = Math.random() * nbDocs;
	    db.vines.find({keywords: keywords}).limit(1).skip(skip, function(err, docs) { 
	    	if(err) {

	    	} else if(docs.length > 0) {
	    		var doc = docs[0];
	    		console.log(doc);
	    		sb.send("vineVideo", "string", doc.link);
	    		sb.send("vineTweet", "string", doc.text);
	    	}
	    });
	});
}
setInterval(sendVines, 1000);

sb.connect();

