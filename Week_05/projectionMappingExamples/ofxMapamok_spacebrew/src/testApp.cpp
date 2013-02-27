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
    
    mapamoko.drawMode = DRAW_FACES;
    mapamoko.slowLerpRate = .1;
    
    //  Setup the canvas
    //
    canvas.allocate(textWidth, textHeight);
    canvas.begin();
    ofClear(0);
    canvas.end();
    
    bCanvasMode = false;
    
    // setup light that follows mouse
    mouseLight.enable();
    mouseLight.setSpotlight();
    
    // setup ofxGui
    bGuiHidden = true;
    gui.setup();
    
    // ofxGui - slider that adjusts model scale
    gui.add(scale.setup("Scale", 1.0f, .1f, 10.0f));
    
    // gradient ofColors for background
    start.set(ofRandom(255),ofRandom(255),ofRandom(255));
    end.set(ofRandom(255),ofRandom(255),ofRandom(255));
    
    //setup spacebrew
    spacebrew.connect();
    spacebrew.addSubscribe("red", Spacebrew::TYPE_RANGE);
    spacebrew.addSubscribe("green", Spacebrew::TYPE_RANGE);
    spacebrew.addSubscribe("blue", Spacebrew::TYPE_RANGE);
    spacebrew.addSubscribe("lightX", Spacebrew::TYPE_RANGE);
    spacebrew.addSubscribe("lightY", Spacebrew::TYPE_RANGE);
    Spacebrew::addListener(this, spacebrew);
}

//--------------------------------------------------------------
void testApp::update(){
    
    //  Render the canvas
    canvas.begin();
    ofEnableAlphaBlending();
    ofClear(0);
    ofBackgroundGradient(start, end);
    canvas.end();
    
    if (!bCanvasMode){
        mapamoko.update();
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    // update from gui gui
    mapamoko.scale = scale;
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
    
    // draw gui?
    if ( !bGuiHidden ){
        gui.draw();
    }
    
    // draw some instructions to the screen
    if ( mapamoko.setupMode == SETUP_SELECT || bShowHelp ){
        string toDraw = "KEY COMMANDS:\n'h' to show/hide this menu\n's' to save crop settings\n";
        toDraw+="'g' to show/hide the gui\n'S' to save Mapamok calibration\n'f' to toggle fullscreen\n";
        toDraw+="'c' to toggle editing the canvas cropping";
        ofDrawBitmapString(toDraw, 20, 100);
    }
}

//--------------------------------------------------------------
void testApp::onMessage(Spacebrew::Message & m ){
    if ( m.name == "red" ){
        start.r = m.valueRange() * 255.0f / 1024.0;
    } else if ( m.name == "green" ){
        start.g = m.valueRange() * 255.0f / 1024.0;
    } else if ( m.name == "blue" ){
        start.b = m.valueRange() * 255.0f / 1024.0;
    } else if ( m.name == "lightX" ){
        ofVec3f oldPosition = mouseLight.getPosition();
        // map range input to y
        oldPosition.y = ofMap(m.valueRange(), 0.0, 1.0, 0.0, ofGetWidth());
        mouseLight.setPosition(oldPosition);
    } else if ( m.name == "lightY" ){
        ofVec3f oldPosition = mouseLight.getPosition();
        // map range input to x
        oldPosition.x = ofMap(m.valueRange(), 0.0, 1.0, 0.0, ofGetWidth());
        mouseLight.setPosition(oldPosition);
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
        
        //  Canvas Mode to edit what is proyected over the surface
        //
        bCanvasMode = !bCanvasMode;
    } else if (key == 's'){
        
        //  Save All View Ports positions
        mapamoko.saveSettings();
    } else if (key == 'S'){
        
        //  Save Calibration
        mapamoko.saveCalibration();
        
    // show the gui
    } else if ( key == 'g' ){
        bGuiHidden = !bGuiHidden;
    }
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseDragged( int x, int y, int button){
    // set the light to move via the mouse
    mouseLight.setPosition(x, y, 1200);
}