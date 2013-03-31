
/**
 * Module dependencies.
 */

var express = require('express')
  , routes = require('./routes')
  , user = require('./routes/user')
  , http = require('http')
  , path = require('path')
  , Spacebrew = require('./sb-1.0.3')
  , util = require('util')
  , exec = require('child_process').exec
  , http = require('http')
  , fs = require('fs')
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


function emptyDir(dirPath) {
	try { var files = fs.readdirSync(dirPath); }
	catch(e) { return; }
	if (files.length > 0) 
		for (var i = 0; i < files.length; i++) {
			var filePath = dirPath + '/' + files[i];
			if (fs.statSync(filePath).isFile())
				fs.unlinkSync(filePath);
			else
				rmDir(filePath);
		}
	//fs.rmdirSync(dirPath);
};

function getExtension(filename) {
    var ext = path.extname(filename||'').split('.');
    return ext[ext.length - 1];
}


//
// What do we do when we get an incoming string?
//
var work_dir = [__dirname, crypto.randomBytes(8)].join('/');
fs.mkdirSync(work_dir);
var n = 0;

function onStringMessage( name, value ){
	if(name=="image") {
		var ext = getExtension(value);
		var path = util.format('%s/%s.%s', work_dir, String('00000'+n).slice(-5), ext);
		var file = fs.createWriteStream(path);
		var request = http.get(value, function(response) {
			response.pipe(file);
		});
		n++;

		if(n>100) {
			makeMovie(work_dir);
			work_dir = [__dirname, crypto.randomBytes(8)].join('/');
			fs.mkdirSync( work_dir );
			n = 0;
		}
	}
}

function makeMovie( dirname ) {

	var cmd = 'convert *.jpg -resize 800x600^ -gravity Center -crop 800x600+0+0 +repage %05d.jpg && ffmpeg -r 25 -qscale 2  -i %05d.jpg output.mp4';
	exec(cmd, {cwd: dirname}, function(error, stdout, stderr){

	});

	// var video = youtube
	// 	.createUpload('/path/to/my/video.webm')
	// 	.user('jefftimesten')
	// 	.source('LearnBoost')
	// 	.password('rightmeow')
	// 	.key('AI39si6L-CpOoC82Kn1noxwSXbfySDW0VCpxIPPwIu2YgZthc_XKEZPLw-4mxRxZYyh-xrGhZmuIKkNfFkhvZrptwc62qbXW8Q')
	// 	.title('Testing')
	// 	.description('Some test stuff')
	// 	.category('Education')
	// 	.upload(function(err, res){
	// 		if (err) callback(err);
	// 		else {
	// 			console.log('done');
	// 			console.log(res.id);
	// 			console.log(res.url);
	// 			console.log(res.embed());
	// 			console.log(res.embed(320, 320));
	// 			console.log(require('util').inspect(res, false, 15, true));
	// 		}
	// 	});
}
