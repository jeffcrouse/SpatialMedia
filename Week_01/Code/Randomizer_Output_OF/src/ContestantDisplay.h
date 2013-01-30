//
//  ContestantDisplay.h
//  Randomizer
//
//  Created by BRenfer on 1/27/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"

class ContestantDisplay
{
public:
    ofColor     fillColor;
    float       alpha;
    string      current;
    ofTrueTypeFont font, smallFont;
    ofRectangle dims;
    
    ContestantDisplay(){};
    ContestantDisplay( string _font, int fontSize );
    void draw();
    void activate( string _current, int delay = 0 );
    void deactivate();
    
private:
    
    int  activeDelay, activated;
    bool bActive;
};

