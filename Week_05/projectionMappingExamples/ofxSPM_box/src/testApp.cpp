#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    // this changes our drawing rate to match our screen's refresh rate
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    // allocate your FBOs
    // you MUST do this before drawing to it!
    // we'll make ours the same res as our mapper (see below)
    for (int i=0; i<3; i++){
        canvas[i].allocate(800, 600);
        
        // you also need to clear out your FBO (we'll clear it to black)
        canvas[i].begin();
        ofClear(0);
        canvas[i].end();
    }
    
    // initialize your mappers; you can also pass in an x and y,
    // which we'll do until we have them set up into a cube
    
    for (int i=0; i<3; i++){
        // initialize ofxSPM at a specific res (we'll say 800x600)
        // we will also offset the x + y positions a bit
        mappers[i].initialize(800, 600, i * 20, i * 20);
    
        // each mapper will have a unique settings file
        string settingsfile = "mapsettings" + ofToString(i) + ".txt";
        // try loading some settings
        mappers[i].load(settingsfile);
    }
    
    // start off not drawing bounds; press 'd' for debug to show them
    bDrawBounds = false;
    
    // use -1 as "false" for forceSelect
    forceSelect = -1;
}

//--------------------------------------------------------------
void testApp::update(){
    // update your mappers
    for (int i=0; i<3; i++){
        mappers[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    // draw mouse circles to front canvas
    canvas[0].begin();
    // fade out the bg a little
    ofSetColor(0,2);
    ofRect(0,0, canvas[0].getWidth(),  canvas[0].getHeight());
    ofSetColor(255);
    // draw a box outline
    ofNoFill();
    ofSetLineWidth(5);
    ofRect(5,5, canvas[0].getWidth()-10,  canvas[0].getHeight()-10);
    ofFill();
    
    // draw some little circles
    ofCircle(mouseX, mouseY, ofRandom(5,10));
    canvas[0].end();
    
    // have the top of the box show random colors
    canvas[1].begin();
    ofSetColor(ofNoise(ofGetElapsedTimef()) * 255.0f, ofNoise(ofGetElapsedTimef() * .5) * 255.0f, ofNoise(ofGetElapsedTimef() * .25) * 255.0f);
    ofRect(0,0, canvas[1].getWidth(),  canvas[0].getHeight());
    canvas[1].end();
    
    // have the side of the box combine the two
    canvas[2].begin();
    // draw somewhat transparent
    ofSetColor(255, 150);
    canvas[0].draw(0,0);
    canvas[1].draw(0,0);
    canvas[2].end();
    
    // draw your mappers and canvases
    for (int i=0; i<3; i++){
        mappers[i].startMapping();
        canvas[i].draw(0,0);
        mappers[i].stopMapping();
        
        if ( bDrawBounds ){
            mappers[i].drawBoundingBox();
            
            // some instructions!
            ofDrawBitmapString("press '1', '2', or '3' to just select one box at a time!\npress 's' to save", 20,20);
        }
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == 's' ){
        // save each a file
        for (int i=0; i<3; i++){
            // each mapper will have a unique settings file
            string settingsfile = "mapsettings" + ofToString(i) + ".txt";
            // try loading some settings
            mappers[i].save(settingsfile);
        }
    } else if ( key == 'd' ){
        bDrawBounds = !bDrawBounds;
    } else if ( key == 'f' ) {
        ofToggleFullscreen();
    }
    
    // force select stuff
    if ( key == '1'){
        forceSelect = 0;
    } else if ( key == '2' ){
        forceSelect = 1;
    } else if ( key == '3' ){
        forceSelect = 2;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    // always reset forceSelect when you release keys
    forceSelect = -1;
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    // are we trying to select juse one?
    if ( forceSelect != -1 ){
        mappers[forceSelect].mouseDragged(x, y);
        return;
    }
    // pass along mouse events to mappers
    for (int i=0; i<3; i++){
        mappers[i].mouseDragged(x, y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    // are we trying to select juse one?
    if ( forceSelect != -1 ){
        mappers[forceSelect].mousePressed(x, y);
        return;
    }
    for (int i=0; i<3; i++){
        mappers[i].mousePressed(x, y);
    }

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    // are we trying to select juse one?
    if ( forceSelect != -1 ){
        mappers[forceSelect].mouseReleased(x, y);
        return;
    }
    for (int i=0; i<3; i++){
        mappers[i].mouseReleased(x, y);
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ }