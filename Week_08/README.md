	  ______   __                          __                                                     
	 /      \ /  |                        /  |                                                    
	/$$$$$$  |$$/  _____  ____    ______  $$ |  ______                                            
	$$ \__$$/ /  |/     \/    \  /      \ $$ | /      \                                           
	$$      \ $$ |$$$$$$ $$$$  |/$$$$$$  |$$ |/$$$$$$  |                                          
	 $$$$$$  |$$ |$$ | $$ | $$ |$$ |  $$ |$$ |$$    $$ |                                          
	/  \__$$ |$$ |$$ | $$ | $$ |$$ |__$$ |$$ |$$$$$$$$/                                           
	$$    $$/ $$ |$$ | $$ | $$ |$$    $$/ $$ |$$       |                                          
	 $$$$$$/  $$/ $$/  $$/  $$/ $$$$$$$/  $$/  $$$$$$$/                                           
	                            $$ |                                                              
	                            $$ |                                                              
	                            $$/                                                               
	  ______                                           __                                         
	 /      \                                         /  |                                        
	/$$$$$$  |  ______    ______    _______   ______  $$ |____    ______    ______   __   __   __ 
	$$ \__$$/  /      \  /      \  /       | /      \ $$      \  /      \  /      \ /  | /  | /  |
	$$      \ /$$$$$$  | $$$$$$  |/$$$$$$$/ /$$$$$$  |$$$$$$$  |/$$$$$$  |/$$$$$$  |$$ | $$ | $$ |
	 $$$$$$  |$$ |  $$ | /    $$ |$$ |      $$    $$ |$$ |  $$ |$$ |  $$/ $$    $$ |$$ | $$ | $$ |
	/  \__$$ |$$ |__$$ |/$$$$$$$ |$$ \_____ $$$$$$$$/ $$ |__$$ |$$ |      $$$$$$$$/ $$ \_$$ \_$$ |
	$$    $$/ $$    $$/ $$    $$ |$$       |$$       |$$    $$/ $$ |      $$       |$$   $$   $$/ 
	 $$$$$$/  $$$$$$$/   $$$$$$$/  $$$$$$$/  $$$$$$$/ $$$$$$$/  $$/        $$$$$$$/  $$$$$/$$$$/  
	          $$ |                                                                                
	          $$ |                                                                                
	          $$/                                                                                 
	 _______             __        __  __            __                                           
	/       \           /  |      /  |/  |          /  |                                          
	$$$$$$$  | __    __ $$ |____  $$ |$$/   _______ $$ |____    ______    ______    _______       
	$$ |__$$ |/  |  /  |$$      \ $$ |/  | /       |$$      \  /      \  /      \  /       |      
	$$    $$/ $$ |  $$ |$$$$$$$  |$$ |$$ |/$$$$$$$/ $$$$$$$  |/$$$$$$  |/$$$$$$  |/$$$$$$$/       
	$$$$$$$/  $$ |  $$ |$$ |  $$ |$$ |$$ |$$      \ $$ |  $$ |$$    $$ |$$ |  $$/ $$      \       
	$$ |      $$ \__$$ |$$ |__$$ |$$ |$$ | $$$$$$  |$$ |  $$ |$$$$$$$$/ $$ |       $$$$$$  |      
	$$ |      $$    $$/ $$    $$/ $$ |$$ |/     $$/ $$ |  $$ |$$       |$$ |      /     $$/       
	$$/        $$$$$$/  $$$$$$$/  $$/ $$/ $$$$$$$/  $$/   $$/  $$$$$$$/ $$/       $$$$$$$/        
	                                                                                              
                                                                                              
### Oveview
This set of examples deals with using the web as Input (in the Spatial Media sense). This can be a super broad subject since the web encompasses so many different methods of communication, but here we will focus on just a few, and hopefully you will see something that interests you.  

Keep in mind that the web can most definitely also be used as Output also -- posting videos you YouTube, tweets to Twitter, publishing data in real time about a space -- but here we are focusing on Input.

Communicating with the web can be very important in Spatial Media for a variety of reasons:

* allow offsite people to communicate with onsite people and vice versa
* incorporate data (political, geographic, humorous) about a space that isn't readily available onsite due to technological or temporal limitations, thus giving users a wider view of the space
* create a general sense of connected-ness in the space and generally expand the reach of possible Input reagh to global
* what else?


####Nuts & Bolts
                                                                                        
As we said on the first day of class, one important feature of Spacebrew is that it allows you to easily use tools for what they do best.  In the case of communicating with the web, while it's definitlely possible to use a graphics-focused language like Processing or openFrameworks to communicate with the web (see [this chapter](https://github.com/jefftimesten/CodeForArt/tree/master/Chapter011-web) of my openFrameworks examples), it's often much easier to use a scripting language like Python or Node. While skeptics may say that this makes your system more prone to problems by introducing additional working parts, I prefer to think of it as conforming to the *Rule of Modularity* in [UNIX philosophy](http://en.wikipedia.org/wiki/Unix_philosophy):

	Developers should build a program out of simple parts connected by well defined interfaces, so problems are local, and parts of the program can be replaced in future versions to support new features. This rule aims to save time on debugging complex code that is complex, long, and unreadable.

PS: Brett and I were initally excited about using the "meta-api" [Temboo](https://temboo.com/) in this class.  It offers a common interface to a variety of popular APIs and is supposed to save you a bit of trouble researching individual APIs (in practice, not really). I tried to make an example or two using a few of the Temboo services for these examples, but I found the interfaces they provided to be limited in functionality (ie: they didn't implement all of the methods of an API, and didn't seem to encourage extending/hacking their interface) and sometimes just plain broken (Netflix). Instead, I encourage you to check out modules/packages in your language of choice.  Or, if you are still interested in Temboo, the [spacebrew-twitter example](https://github.com/labatrockwell/spacebrew-twitter) uses it.



