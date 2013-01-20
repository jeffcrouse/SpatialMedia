//
//  Group.cpp
//  Randomizer
//
//  Created by BRenfer on 1/20/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Group.h"


Group::Group( int _x, int _y, int _w, int _h ){
    studentOne = "";
    studentTwo = "";
    assignment = "";
    studentOneSelected = false;
    studentTwoSelected = false;
    
    drawX = _x;
    drawY = _y;
    w = _w;
    h = _h;
    
    font = NULL;
}

void Group::setFont( ofTrueTypeFont * _font ){
    font = _font;
}

void Group::draw(){
    int x = drawX;
    int y = drawY;
    
    ofSetColor(10,50,11);
    font->drawString( assignment, x,y);
    y += 10;
    
    if ( studentOneSelected ) ofSetColor(255);
    else ofSetColor(130,159,180);
    ofRect(x,y,w,h/2);
    
    ofSetColor(0);
    font->drawString(studentOne, x + 4, y+font->getSize()+ 2);
    
    y += h/2;
    
    if ( studentTwoSelected ) ofSetColor(255);
    else ofSetColor(45,86,117);
    ofRect(x,y,w,h/2);
    
    ofSetColor(0);
    font->drawString(studentTwo, x+ 4, y+font->getSize()+ 2);
};