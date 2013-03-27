
	   _____                      _                               
	  / ____|                    | |                          _   
	 | (___  _ __   __ _  ___ ___| |__  _ __ _____      __  _| |_ 
	  \___ \| '_ \ / _` |/ __/ _ \ '_ \| '__/ _ \ \ /\ / / |_   _|
	  ____) | |_) | (_| | (_|  __/ |_) | | |  __/\ V  V /    |_|  
	 |_____/| .__/ \__,_|\___\___|_.__/|_|  \___| \_/\_/          
	  _   _ | |       _        _                                  
	 | \ | ||_|      | |      (_)        _                        
	 |  \| | ___   __| | ___   _ ___   _| |_                      
	 | . ` |/ _ \ / _` |/ _ \ | / __| |_   _|                     
	 | |\  | (_) | (_| |  __/_| \__ \   |_|                       
	 |_|_\_|\___/ \__,_|\___(_) |___/                             
	 |  ____|                _/ |                                 
	 | |__  __  ___ __  _ __|__/  ___ ___                         
	 |  __| \ \/ / '_ \| '__/ _ \/ __/ __|                        
	 | |____ >  <| |_) | | |  __/\__ \__ \                        
	 |______/_/\_\ .__/|_|  \___||___/___/                        
	             | |                                              
	             |_|                                              


This repository contains a super simple node.js application that creates a Spacebrew client with one publisher that sends a "tick" string every second. Why express and not just plain old node? That's a topic for another day.  

For learning's sake, the following instructions will re-create the app contained here.

1. Follow [the directions here](http://expressjs.com/guide.html#executable) to create a barebones Express app.  Essentially it comes down to issuing the following commands:

	```
	npm install -g express
	express --sessions --ejs spacebrew-ticker
	```
	
* Install the initial required modules by running the following command

	```
	cd spacebrew-ticker && npm install
	```

* Install the 'ws' module (it is required by spacebrew)
	
	```
	npm install ws --save
	```

* Get *sb-1.0.3.js* from the lib folder in https://github.com/Spacebrew/spacebrew.js and put it in the root folder of your app

	```
	curl -O https://raw.github.com/Spacebrew/spacebrew.js/master/library/sb-1.0.3.js
	```
	
- Open app.js in tour favorite text editor and include Spacebrew by modifying the top of your app.js so that it looks like this:

	```
	var express = require('express')
	  , routes = require('./routes')
	  , user = require('./routes/user')
	  , http = require('http')
	  , path = require('path')
	  , Spacebrew = require('./sb-1.0.3')

	```
- Create a Spacebrew client. Provide a server, name, description

	```
	var sb = new Spacebrew.Spacebrew.Client( server, name, description );
	```
	
- Add publishers and/or subscribers as described in the examples at the [Spacebrew.js repo](https://github.com/Spacebrew/spacebrew.js).
- Connect the mofo.

	```
	sb.connect();
	```
	
- Run your node app!

	```
	node app.js
	```
	
- Head over to the [Spacebrew Sandbox](http://spacebrew.github.com/spacebrew/admin/admin.html?server=sandbox.spacebrew.cc) and see your app