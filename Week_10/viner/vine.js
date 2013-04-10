
var  request = require("request")
	, twitter = require("ntwitter")
	, twit = new twitter()
	, params = { include_entities: true, since_id: null };


module.exports.getVines = function(keywords, callback) {
	var query = "vine.co/v/ AND ("+keywords+")";
	var vines = [];

	twit.search(query, params, function(err, data) {
		if(err) {
			callback(err);
			return;
		} else {
			params.since_id = data.max_id;
			var remaining = data.results.length;

			data.results.forEach(function(tweet){
				var vine_url = null;
				tweet.entities.urls.forEach(function(url){
					if( url.expanded_url.split("//")[1].indexOf("vine.co/v/") > -1 ) {
						vine_url = url.expanded_url+"/card";
					}
				});
				if(!vine_url) return;

				request(vine_url, function (error, response, body) {	
					if (error) {
						console.log("Error fetching "+vine_url+": "+error);
					} else {
						var matches = body.match(/<source src="([^"]+)"/i);
						if(matches) {
							var vine = {
								user: tweet.from_user
								, link: vine_url
								, video: matches[1]
								, user_name: tweet.from_user_name
								, text: tweet.text
								, created_at: tweet.created_at
								, keywords: keywords
							};
							vines.push( vine );
						} else {
							console.log("Couldn't find video link on "+vine_url);
						}

						if(--remaining==0) {
							callback(null, vines);
						}
					}
				});
			});  // end loop through data.results
		} 
	}); // end of twit.search
}

