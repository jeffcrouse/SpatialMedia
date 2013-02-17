#pragma once

#include "ofMain.h"

// include spacebrew addon
#include "ofxSpacebrew.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        // add spacebrew connection object + message catcher
        Spacebrew::Connection connection;
        void onMessage( Spacebrew::Message & m );
    
        // add variable that will be updated by spacebrew
        int countRange;
};
