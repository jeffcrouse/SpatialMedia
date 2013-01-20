//
//  Lights.h
//  Randomizer
//
//  Created by BRenfer on 1/20/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"

class Lights
{
private:
    vector<ofVec2f> points;     // vector of "lights"
    float   whichLight;         // which lights are lighting up
    
public:
    bool    bActive;
    
    Lights();
    Lights( int x, int y, int w, int h, int r);
    void draw();
};


