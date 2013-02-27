#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    // this changes our drawing rate to match our screen's refresh rate
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    // allocate your FBO
    // you MUST do this before drawing to it!
    // we'll make ours the same res as our mapper (see below)
    canvas.allocate(800, 600);
    
    // you also need to clear out your FBO (we'll clear it to black)
    canvas.begin();
    ofClear(0);
    canvas.end();
    
    // initialize ofxSPM at a specific res (we'll say 800x600)
    mapper.initialize(800, 600);
    
    // try loading some settings
    mapper.load("mapsettings.txt");
    
    // start off not drawing bounds; press 'd' for debug to show them
    bDrawBounds = false;
}

//--------------------------------------------------------------
void testApp::update(){
    // update your mapper
    mapper.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    // draw something to your canvas
    canvas.begin();
    // fade out the bg a little
    ofSetColor(0,2);
    ofRect(0,0,canvas.getWidth(), canvas.getHeight());
    ofSetColor(255);
    
    // we'll draw some little circles
    ofCircle(mouseX, mouseY, ofRandom(5,10));
    canvas.end();
    
    mapper.startMapping();
    canvas.draw(0,0);
    mapper.stopMapping();
    
    if ( bDrawBounds ){
        mapper.drawBoundingBox();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == 's' ){
        // save to a file
        mapper.save("mapsettings.txt");
    } else if ( key == 'd' ){
        bDrawBounds = !bDrawBounds;
    } else if ( key == 'f' ) {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    // pass along mouse events to mapper
    mapper.mouseDragged(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    mapper.mousePressed(x, y);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    mapper.mouseReleased(x, y);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ }