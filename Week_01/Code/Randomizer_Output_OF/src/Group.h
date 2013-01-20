//
//  Group.h
//  Randomizer
//
//  Created by BRenfer on 1/20/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"

class Group
{
    
private:
    int drawX,drawY,w,h;
    ofTrueTypeFont *    font;
    
public:
    
    string   studentOne;
    string   studentTwo;
    string   assignment;
    bool    studentOneSelected;
    bool    studentTwoSelected;
    
    Group( int _x, int _y, int _w, int _h );
    void setFont( ofTrueTypeFont * font );
    void draw();
};

