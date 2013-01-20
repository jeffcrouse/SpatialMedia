#pragma once

#include "ofMain.h"

// include custom classes
#include "Group.h"
#include "Lights.h"

// include ofxSpacebrew
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
		
        // catcher for Spacebrew events
        void onMessage( Spacebrew::Message & m );
    
        // helper shim for quickly porting from P5
        vector<string> loadStrings( string file );
    
        void drawBackground();
        void selectRandom();
    
        Spacebrew::Connection spacebrewConnection;
    
        // array of students
        vector<string>   students;
        vector<Group>    groups;
        
        bool             bGroupsPicked;
        int              groupSize;
        int              numGroups = 0;
        
        // array of assignments
        vector<string>   assignments;
        
        // visual stuff
        ofTrueTypeFont   arial;
    
        int     fontSize;
        int     squareWidth;
        int     squareHeight;
        int     padding;
        
        // randomize!
        bool    bRandomizing;
        int     currentIndex;
        float   floatIndex;
        float   speed;
        ofVec2f pos;
        Lights  lights;

};
