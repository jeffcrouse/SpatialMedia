#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    
    // state state to "i've never seen a face"
    
    // setup TSPS receiver
    
    // load an amazing font
}

//--------------------------------------------------------------
void testApp::update(){
    // see if there any people with faces
    // first, get the vector of current people
    
    // store last state for reference below
    
    // reset state to "lost face" IF it's on "saw face"
    // why? makes it easy: if not set to "saw face" below, it will
    // automatically say "we lost the face!"
    
    // loop through people
    
        // if they have a haar rectangle, we saw a face!
        
            // if this is a new face, randomize the background variable
}

//--------------------------------------------------------------
void testApp::draw(){
    // check what state we're in, and set a variable for what text
    // we want to draw
    
    // if we saw a face, set the background to our background variable,
    // and say "peek-a-boo!"
    
    // if we lost the face, say "where did you go??"

    // say something if we have never seen a face
    
    // figure out where we want to draw our text (centered seems good)
    
    // draw our text
}