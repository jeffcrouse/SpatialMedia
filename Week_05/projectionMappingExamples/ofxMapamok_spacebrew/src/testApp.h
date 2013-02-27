#pragma once

#include "ofMain.h"

#include "ofxMapamok.h"
#include "ofxSmartViewPort.h"

#include "ofxSpacebrew.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged( int x, int y, int button);
    
    // spacebrew stuff
    Spacebrew::Connection spacebrew;
    void onMessage( Spacebrew::Message & m );
    
    // mapamok stuff
    ofxMapaMok          mapamoko;
    
    // light that will follow your mouse
    ofLight             mouseLight;
    
    // the all-powerful canvas that you'll draw to!
    ofFbo               canvas;
    
    int                 textWidth;
    int                 textHeight;
    
    bool                bCanvasMode;
    bool                bShowHelp;
    
    // vars to use with ofxGui
    bool                bGuiHidden;
    ofxPanel            gui;
    ofxFloatSlider      scale, lerpSpeed;
    
    bool                bCursorHidden;
    ofColor             start,end;
    
};
