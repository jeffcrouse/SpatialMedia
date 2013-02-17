#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // connect to tsps
    
    // turn off ofBackgroundAuto so it's more like processing
    
    // enable alpha blending for trail effect, set framerate, and make circles high res
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    // clear background slightly
    
    // get TSPS people vector
    
    // loop through people
    
        // is there a color for this person's ID (pid)?
        // maps: check for a value with count( key )
        // if map.count(key) == 0, it doesn't exist (yet)
        
            // if not, create a new color
            
        // set color from map
        
        // values in tsps people are normalized, so fetch them and multiply them by window size
        // use the centroid (center) and bounding box to draw
        
        // draw the circle!
        
}