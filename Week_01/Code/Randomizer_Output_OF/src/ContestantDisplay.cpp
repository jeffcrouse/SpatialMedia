//
//  ContestantDisplay.cpp
//  Randomizer
//
//  Created by BRenfer on 1/27/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "ContestantDisplay.h"

ContestantDisplay::ContestantDisplay( string _font, int fontSize ){
    smallFont.loadFont( _font, fontSize );
    font.loadFont( _font, 70 );
    dims.set( ofGetWidth()/2, ofGetHeight()/2, ofGetWidth() * 3/4, 160);    
    alpha     = 0;
    bActive = false;
};

void ContestantDisplay::draw(){
    if ( bActive && ofGetElapsedTimeMillis() - activated > activeDelay ){
        alpha += 10;
        if ( alpha > 255 ){
            alpha = 255;
        }
    } else {
        alpha *= .75;
        if ( alpha < 0 ) alpha = 0;
    }
    ofPushStyle();{
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(0, alpha * .5);
        ofRect(dims.x, dims.y, ofGetWidth(), ofGetHeight());
        ofSetColor(fillColor, alpha);
        ofRect(dims);
        ofSetColor(0, alpha);
        
        float fontY = (dims.y - dims.height/2) + 10 + smallFont.getSize();
        smallFont.drawString("Next Up:", dims.x - dims.width/2 + 10, fontY );
        fontY += font.getSize() + 20;
        font.drawString(current, dims.x - dims.width/2 + 10, fontY );
    }; ofPopStyle();
};

void ContestantDisplay::activate( string _current, int delay ){
    activated = ofGetElapsedTimeMillis();
    activeDelay     = delay;
    bActive = true;
    current = _current;
}

void ContestantDisplay::deactivate(){
    bActive = false;
}
