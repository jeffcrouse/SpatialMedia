
/**
 * Module dependencies.
 */

var express = require('express')
	, routes = require('./routes')
	, user = require('./routes/user')
	, http = require('http')
	, path = require('path')
	, util = require('util')
	, fs = require('fs')
	, exec = require('child_process').exec
	, Spacebrew = require('./sb-1.0.3')
	, youtube = require('youtube')
	, crypto = require('crypto')

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
var name = "Youtube Uploader";
var description = "Accepts URLS of images.  Generates a video and eventually uploads it to YouTube";
var sb = new Spacebrew.Spacebrew.Client( server, name, description );
sb.addSubscribe("image", "string");
sb.onStringMessage = onStringMessage;
sb.connect();


function getExtension(filename) {
    var ext = path.extname(filename||'').split('.');
    return ext[ext.length - 1];
}


//
// What do we do when we get an incoming string?
//
var work_dir = [__dirname, crypto.randomBytes(8).toString('hex')].join('/');
fs.mkdirSync(work_dir);
var n = 0;

function onStringMessage( name, value ){
	if(name=="image" && getExtension(value)=="jpg") {

		var path = util.format('%s/%s.jpg', work_dir, String('00000'+n).slice(-5));
		var file = fs.createWriteStream(path);
		var request = http.get(value, function(response) { 
			response.pipe(file); 

			if(n>30) {
				makeMovie(work_dir);
				work_dir = [__dirname, crypto.randomBytes(8).toString('hex')].join('/');
				fs.mkdirSync( work_dir );
				n = 0;
			}
		});
		n++;
	}
}


function makeMovie( dirname ) {

	var cmd = 'convert *.jpg -resize 800x600^ -gravity Center -crop 800x600+0+0 +repage %05d.jpg && ffmpeg -r 25 -qscale 2  -i %05d.jpg output.mp4';
	exec(cmd, {cwd: dirname}, function(error, stdout, stderr){
		var path = dirname+"/output.mp4";

		if(error) {
			console.log(error);
		} else if(!fs.existsSync(path)) {
			console.log(path+" not generated!");
		} else {
			
			var title = 'Spacebrew Output '+new Date().toJSON();
			var description = "Some images sent through Spacebrew";
			var category = 'Education';
			var dev_key = 'AI39si6wKltoN5L83T7NOHPOhJ5rXkfe3fAA8jVfqhc3Fhf9Nlw2k8_WGAFlmnxPjj5YdGYQ7hnXW_7LE4tbJFliNSQ--yGQfA';

			var video = youtube
				.createUpload(path)
				.user('jefftimesten@gmail.com')
				.source('jefftimesten')
				.password('FullHouse99!')
				.key(dev_key)
				.title(title)
				.description(title)
				.category(category)
				.upload(function(err, res){
					if (err) console.log(err);
					else {
						console.log('done');
						console.log(res.id);
						console.log(res.url);
						console.log(res.embed());
						console.log(res.embed(320, 320));
						console.log(require('util').inspect(res, false, 15, true));
					}
				});
		}
	});
}


