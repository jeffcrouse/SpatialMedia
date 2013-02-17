#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // connect to tsps
    tspsReceiver.connect(12000);
    
    // turn off ofBackgroundAuto so it's more like processing
    ofSetBackgroundAuto(false);
    ofBackground(0);
    
    // enable alpha blending for trail effect
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    // clear background slightly
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    ofSetColor(0,10);
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // get TSPS people
    vector<ofxTSPS::Person *> people = tspsReceiver.getPeople();
    
    // loop through people
    for (int i=0; i<people.size(); i++){
        // is there a color for this person's ID (pid)?
        // maps: check for a value with count( key )
        // if map.count(key) == 0, it doesn't exist (yet)
        if ( colors.count( people[i]->pid ) == 0){
            // if not, create a new color
            // make the alpha low for the blend mode
            colors[ people[i]->pid ] = ofColor( ofRandom(255), ofRandom(255), ofRandom(255), 50);
        }
        
        // set color from map
        ofSetColor( colors[ people[i]->pid ]);
        
        // values in tsps people are normalized, so fetch them and multiply them by window size
        ofPoint centroid = people[i]->centroid;
        centroid.x *= ofGetWidth();
        centroid.y *= ofGetHeight();
        
        float width = people[i]->boundingRect.width;
        width *= ofGetWidth() / 2.0f;
        
        // draw the circle!
        ofCircle(centroid, width);
    }
}