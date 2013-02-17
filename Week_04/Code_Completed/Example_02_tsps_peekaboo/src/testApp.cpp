#include "testApp.h"

using namespace ofxTSPS;

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    
    // state state to "i've never seen a face"
    state = NEVER_SEEN;
    
    // setup TSPS receiver
    tspsReceiver.connect(12000);
    
    // load an amazing font
    font.loadFont("DINPro-Medium.otf", 30);
    ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void testApp::update(){
    // see if there any people with faces
    
    vector<Person * > people = tspsReceiver.getPeople();
    
    // store last state
    FaceState lastState = state;
    
    // reset state to "lost face"
    if ( state == SAW_FACE ) state = LOST_FACE;
    
    for (int i=0; i<people.size(); i++){
        if ( people[i]->hasHaarRect() ){
            state = SAW_FACE;
            
            // if this is a new face, randomize the background
            if ( lastState != SAW_FACE ){
                background.set(ofRandom(255), ofRandom(255), ofRandom(255));
            }
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    string toDraw = "";
    
    if ( state == SAW_FACE ){
        ofBackground(background);
        toDraw = "PEEK-A-BOO!";
    } else if ( state == LOST_FACE ){
        ofBackground(0);
        toDraw = "Where'd you go?";
    } else if ( state == NEVER_SEEN ){
        ofBackground(0);
        toDraw = "I wish I had a friend ;(";
    }
    
    // centering fonts is kind of annoying
    ofRectangle bounds = font.getStringBoundingBox(toDraw, 0, 0);
    ofPoint position( ofGetWidth() / 2.0f, ofGetHeight() / 2.0f );
    position.x -= bounds.width / 2.0f;
    
    font.drawString(toDraw, position.x, position.y);
}