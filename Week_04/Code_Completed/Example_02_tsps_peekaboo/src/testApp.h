#pragma once

#include "ofMain.h"

#include "ofxTSPSReceiver.h"

// enumerate possible face states

enum FaceState {
    NEVER_SEEN,
    SAW_FACE,
    LOST_FACE
};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        // set up TSPS Receiver
        ofxTSPS::Receiver tspsReceiver;
    
        // declare current FaceState
        FaceState state;
    
        // load a font for displaying feedback
        ofTrueTypeFont font;
    
        // ofColor for randomizing background
        ofColor     background;
};
