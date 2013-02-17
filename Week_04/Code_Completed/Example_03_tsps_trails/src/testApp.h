#pragma once

#include "ofMain.h"

// include ofxTSPSReceiver
#include "ofxTSPSReceiver.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        // create TSPS Receiver object
        ofxTSPS::Receiver tspsReceiver;
    
        // create map of people IDs (int) to colors (ofColor)
        map<int, ofColor> colors;
};
