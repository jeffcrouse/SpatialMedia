#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetFrameRate(60);
    ofSetFullscreen(true);

    
    string host = "sandbox.spacebrew.cc"; // change to localhost to test Spacebrew local server
    string name = "Falling Words";
    string description = "Feed me strings!";
    spacebrew.addSubscribe("words", "string");
    spacebrew.connect( host, name, description );
    Spacebrew::addListener(this, spacebrew);


    bool bAntiAliased=false;
    bool bFullCharacterSet=true;
    bool makeContours=true;
    font.loadFont("Serif Neu.ttf", 24, bAntiAliased, bFullCharacterSet, makeContours);

    ofxExtrudedText word;
    word.setup("Hello!", 5, font);
    ofLogNotice() << "Adding " << word.text << " with " << word.verts << " verts";
    
    fallingWords.push_back( word );
    
    nextTweetInterval = 0.5;
    nextTweetAt = ofGetElapsedTimef()+nextTweetInterval;
}

//--------------------------------------------------------------
void testApp::onMessage( Spacebrew::Message & msg ){
    float now = ofGetElapsedTimef();
    if ( now > nextTweetAt && msg.name == "words") {
        
        vector<string> words = ofSplitString(msg.value, " ");
        for(int i=0; i<words.size(); i++) {
            if(ofInRange(words[i].length(), 6, 15)) {
                queue.push_back(words[i]);
            }
        }
        nextTweetAt = now + nextTweetInterval;
    }
}


//--------------------------------------------------------------
void testApp::update(){

    for(int i=0; i<queue.size(); i++) {
        ofxExtrudedText word;
        word.setup(queue[i], 5, font);
        ofLogNotice() << "Adding " << word.text << " with " << word.verts << " verts";
        fallingWords.push_back( word );
    }
    queue.clear();
    
    float now = ofGetElapsedTimef();
    float elapsed = now-lastFrame;
    lastFrame = now;
    
    for(int i=fallingWords.size()-1; i>-1; i--) {
        fallingWords[i].update(elapsed);
        
        if(fallingWords[i].getY() > ofGetHeight()+fallingWords[i].bb.width) {
            fallingWords.erase(fallingWords.begin()+i);
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::black);
    
    ofEnableLighting();
    light.enable();
    
    int verts = 0;
    glEnable(GL_DEPTH_TEST);
    for(int i=0; i<fallingWords.size(); i++) {
        fallingWords[i].draw();
        verts += fallingWords[i].verts;
    }
    glDisable(GL_DEPTH_TEST);
    light.disable();
    ofDisableLighting();
    
    ofSetColor(255);
    stringstream msg;
    msg << "fps=" << ofGetFrameRate() << " #words=" << fallingWords.size() << " verts=" << verts;
    ofDrawBitmapString(msg.str(), 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}