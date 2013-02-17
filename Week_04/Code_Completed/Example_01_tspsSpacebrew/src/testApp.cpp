#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // create spacebrew connection + say you're listening to a range called "count"
    connection.connect();
    connection.addSubscribe("count", "range");
    
    // tell spacebrew you are listening to this connection
    Spacebrew::addListener(this, connection);
    
    countRange = 0;
    
    // set the background to black and make the circles high resolution
    ofBackground(0);
    ofSetCircleResolution(30);
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    // draw circles based on count
    for ( int i=0; i<countRange; i++){
        ofCircle( 60 + i * ofGetWidth() / countRange, ofGetHeight() / 2.0f, 60 );
    }
    
    // draw text with count
    ofDrawBitmapString(ofToString(countRange), ofGetWidth()/2.0, ofGetHeight() / 2.0 + 100);
}

//--------------------------------------------------------------
// Add Spacebrew message catcher
void testApp::onMessage( Spacebrew::Message & m ){
    // if message name is "count", set countRange variable
    if ( m.name == "count" ){
        countRange = m.valueRange();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){}

//--------------------------------------------------------------
void testApp::keyReleased(int key){}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){}