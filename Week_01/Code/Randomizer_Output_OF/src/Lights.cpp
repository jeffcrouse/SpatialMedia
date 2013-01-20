//
//  Lights.cpp
//  Randomizer
//
//  Created by BRenfer on 1/20/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Lights.h"

Lights::Lights(){
}

Lights::Lights( int x, int y, int w, int h, int r){
    bActive = false;
    whichLight = 1;
    ofSetCircleResolution(100);
    
    int index=0;
    // top
    for (int i=0; i < 10; i++ ){
        ofVec2f p = ofVec2f(ofLerp( (float) x + r*2, (float)x + r + (w-r),(float)i/10.0f), y);
        points.push_back(p);
        index++;
    }
    
    // right
    for (int i=0; i < 8; i++ ){
        ofVec2f p = ofVec2f(x + w, ofLerp( (float) y + r*2, (float) y + r + (h-r),(float)i/8.0f) );
        points.push_back(p);
        index++;
    }
    
    // bottom
    for (int i=0; i < 11; i++ ){
        ofVec2f p = ofVec2f(ofLerp( (float)x + r + (w-r), (float) x + r*2, (float)i/10.0f), y + h);
        points.push_back(p);
        index++;
    }
    
    // left
    for (int i=0; i < 8; i++ ){
        ofVec2f p = ofVec2f(x, ofLerp((float) y + r + (h-r), (float) y + r *2, (float)i/8.0f));
        points.push_back(p);
        index++;
    }
}

void Lights::draw(){
    // draw lights
    for (int i=0; i<points.size(); i++){
        if ( (i+1) % (int) whichLight == 0 && bActive ){
            ofSetColor(255);
        } else {
            ofSetColor(150);
        }
        ofEllipse(points[i], 20, 20 );
    }
    whichLight += .5;
    if ( whichLight >= 4 ) whichLight = 1;
}
