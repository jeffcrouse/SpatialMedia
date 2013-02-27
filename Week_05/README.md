Week 5 Examples
===========

Setting up
----------
* Make sure you have the following repositories inside of openFrameworks/addons
	* [ofxSpacebrew](https://github.com/labatrockwell/ofxSpacebrew)
	* [ofxLibwebsockets](https://github.com/labatrockwell/ofxLibwebsockets)
	* [ofxCv](https://github.com/kylemcdonald/ofxCv)
	* [ofxMapamok](https://github.com/natxopedreira/ofxMapamok)
	* [ofxSimpleProjectionMapper](https://github.com/robotconscience/ofxSimpleProjectionMapper.git)
* Create a Spatial Media folder inside openFrameworks/ if you haven't already
* Copy the folder "projectionMappingExamples" into openFrameworks/SpatialMedia

The Examples
----------
* ofxSPM_basic
	* Very basic quad-warping projection mapping
	* Deceptively simple: this is often all you need to do! 
	* Example shows how to draw to an ofFbo and render it to an ofxSimpleProjectionMapper instance
* ofxSPM_box
	* This example shows how to set up multiple ofxSPM instances (and multiple FBOs) to map onto a primitive ( a box in this case)
* ofxMapamok_basic
	* This is almost exactly the same as the example that comes with ofxMapamok (just a few more comments + on-screen help).
	* Allows you to map a video camera feed onto a Sketchup-generated model
* ofxMapamok_spacebrew
	* This is a more advanced example that connects a gradient and 3D light to Spacebrew
	* This example also includes ofxGui, which is included with the dev version of openFrameworks
		* ofxGui allows you to create simple user interfaces to control variables
