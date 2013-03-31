
	 _____              _                                          
	(_   _)          _ (_ )  _                                     
	  | | _   _   _ (_) | | (_)   _                                
	  | |( ) ( ) ( )| | | | | | /'_`\                              
	  | || \_/ \_/ || | | | | |( (_) )                             
	  (_)`\___x___/'(_)(___)(_)`\___/'                             
	                                                               
	                                                               
	 ___           _                            _                  
	(  _`\        ( )                        _ ( )                 
	| (_(_) _   _ | |_     ___    ___  _ __ (_)| |_      __   _ __ 
	`\__ \ ( ) ( )| '_`\ /',__) /'___)( '__)| || '_`\  /'__`\( '__)
	( )_) || (_) || |_) )\__, \( (___ | |   | || |_) )(  ___/| |   
	`\____)`\___/'(_,__/'(____/`\____)(_)   (_)(_,__/'`\____)(_)   
	                                                               
                                                               

[Twilio](http://www.twilio.com/) is a web service that makes it possible to easily send SMS and voice calls. And (surprise) it has [pretty nice documentation for use within node.js](http://twilio.github.com/twilio-node/). But the first step is to [create an account](https://www.twilio.com/try-twilio).

**IMPORTANT**:  Don't read the docuemntation at [https://github.com/sjwalter/node-twilio](https://github.com/sjwalter/node-twilio)!!! It's outdated/incorrect.  Instead, read [the documentation on the twilio site]](http://twilio.github.com/twilio-node/)

### Voice Calls

You can easily tell Twilio to make a voice call from within your application.  You need to provide 3 things:
1. 

// Step 1:
// Learn about localtunnel!  http://progrium.com/localtunnel/
// localtunnel -k ~/.ssh/id_rsa.pub 3000
// http://twilio.github.com/twilio-node/#validateExpressRequest
// https://www.twilio.com/user/account
// VERBS: http://www.twilio.com/docs/api/twiml