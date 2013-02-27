#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);
    
    // width of your canvas
    textWidth = 1024;
    textHeight = 768;
    
    //  Load mapamok model + settings
    string model = "model.dae";
    
    // this loads the settings, which includes position + dimension info
    mapamoko.loadSettings("mapamok.xml");
    mapamoko.loadMesh(model, textWidth, textHeight);
    mapamoko.drawMode = DRAW_FACES;
    
    // is there a calibration file? mapamok stores it inside of the model
    if (mapamoko.loadCalibration(model)){
        mapamoko.setupMode = SETUP_NONE;
        bShowHelp = false;
    } else {
        mapamoko.setupMode = SETUP_SELECT;
        bShowHelp = true;
    }
    
    //  Setup the canvas
    canvas.allocate(textWidth, textHeight);
    canvas.begin();
    ofClear(0);
    canvas.end();
    
    //  Init WebCam texture
    video.initGrabber(640,480);
    videoViewPort.loadSettings("video.xml");
    
    bCanvasMode = false;
}

//--------------------------------------------------------------
void testApp::update(){
    video.update();
    
    //  Render the canvas
    //
    canvas.begin();
    ofClear(0);
    video.draw(videoViewPort);
    canvas.end();
    
    if (!bCanvasMode){
        mapamoko.update();
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (bCanvasMode){
        ofSetColor(255);
        canvas.draw(0, 0);
        ofDrawBitmapString("CANVAS MODE ( press 'e' to drag )", 15,15);
        
    } else {
        mapamoko.draw( &canvas.getTextureReference() );
    }
    
    // draw some instructions to the screen
    if ( mapamoko.setupMode == SETUP_SELECT || bShowHelp ){
        string toDraw = "KEY COMMANDS:\n'h' to show/hide this menu\n's' to save crop settings\n'S' to save Mapamok calibration\n'f' to toggle fullscreen\n";
        toDraw+="'c' to toggle editing the canvas cropping";
        ofDrawBitmapString(toDraw, 20, 40);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if ( key == 'h' ){
        // toggle help menu
        bShowHelp = !bShowHelp;
    } else if(key == 'f'){
        
        //  Toggle Fullscreen
        //
        ofToggleFullscreen();
    } else if(key == 'c'){
        
        //  Canvas Mode to edit what is projected over the surface
        //
        bCanvasMode = !bCanvasMode;
    } else if (key == 's'){
        
        //  Save All View Ports positions
        //
        videoViewPort.saveSettings();
        mapamoko.saveSettings();
    } else if (key == 'S'){
        
        //  Save Calibrations
        //
        mapamoko.saveCalibration();
    }
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}