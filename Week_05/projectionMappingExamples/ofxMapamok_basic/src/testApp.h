#pragma once

#include "ofMain.h"

#include "ofxMapamok.h"
#include "ofxSmartViewPort.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    // create mapamok object
    ofxMapaMok      mapamoko;
    
    // grab video from your webcam
    ofVideoGrabber      video;
    
    // ofxMapamok util that allows you to do some
    // simple cropping on your video
    ofxSmartViewPort    videoViewPort;
    
    // the all-powerful canvas that you'll draw to!
    ofFbo           canvas;
    
    int             textWidth;
    int             textHeight;
    
    bool            bCanvasMode;
    bool            bShowHelp;
};
