#include "testApp.h"

string server="localhost";
string name="Randomizer";
string description ="This sketch will randomly assign students (from students.txt) and assigns them to something (assign.txt)";

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    bGroupsPicked   = false;
    numGroups       = 0;
    fontSize        = 18;
    squareHeight    = (fontSize + 10)*2;
    padding         = 15;
    
    // randomize!
    bRandomizing    = false;
    currentIndex    = 0;
    floatIndex      = 0;
    speed           = 0;
    pos.set(150,150);
    
    vector<string> spacebrewConfig = loadStrings("spacebrew.txt");
    if ( spacebrewConfig.size() > 0 ){
        server = spacebrewConfig[0];
    }
    
    // listen to spacebrew events
    ofAddListener(spacebrewConnection.onMessageEvent, this, &testApp::onMessage);
    
    // add each thing you publish to
    spacebrewConnection.addPublish( "selectedGroup", "string" );
    
    // add each thing you subscribe to
    spacebrewConnection.addSubscribe( "randomize", "boolean" );
    
    // connect!
    spacebrewConnection.connect(server, name, description );
    
    // load students
    vector<string> tempStudents = loadStrings( "students.txt" );
    
    // null = file doesn't exist :(
    if ( tempStudents.size() > 0 ){
        groupSize = ofToInt(tempStudents[0]); // # of people in group is first line
        
        // need to make students an array that is length-1 (so we don't include that first line)
        tempStudents.erase(tempStudents.begin());
        students = tempStudents;
        numGroups = ceil(students.size() / groupSize);
    }
    
    // load assignments
    assignments = loadStrings("assign.txt");
    
    // nifty way to randomize array
    ofRandomize(assignments);
    
    // visual stuff
    arial.loadFont("Arial.ttf", fontSize);
    lights = Lights(90,90, ofGetWidth()-180, ofGetHeight()-180, 0);
    squareWidth = (ofGetWidth()-((int)pos.x * 2) - padding*3)/2;
    
    // setup groups!
    int x = (int) pos.x;
    int y = (int) pos.y + fontSize;
    
    for (int i=0; i<numGroups; i++){
        groups.push_back( Group( x, y, squareWidth, squareHeight ));
        groups.back().assignment = assignments[i];
        groups.back().setFont( &arial );
        
        y += 10;
        y += squareHeight/2;
        y += squareHeight + padding * 1.5;
        
        if ( y + squareHeight + padding > ofGetHeight() - pos.y ){
            y = (int) pos.y + fontSize;; 
            x += squareWidth + padding;
        }
    }
}

//--------------------------------------------------------------
vector<string> testApp::loadStrings( string file ){
    vector<string> ret;
    ofBuffer temp = ofFile( file ).readToBuffer();
    while ( !temp.isLastLine() ){
        ret.push_back( temp.getNextLine() );
        cout<<ret.back()<<endl;
    }
    return ret;
}

//--------------------------------------------------------------
void testApp::update(){
    // update randomizer
    if ( (bRandomizing || speed > 0 ) && !bGroupsPicked ){
        
        floatIndex += speed;
        currentIndex = floor(floatIndex);
        
        while ( currentIndex >= students.size() ){
            currentIndex -= students.size();
        }
        
        int whichGroup = floor( currentIndex / 2);
        bool bStudentOne = currentIndex % 2 == 0;
        bool bNotPickedYet = (bStudentOne ? groups[whichGroup].studentOne == "" : groups[whichGroup].studentTwo == "");
        
        while ( !bNotPickedYet ){
            currentIndex++;
            while ( currentIndex >= students.size() ){
                currentIndex -= students.size();
            }
            whichGroup = floor( currentIndex / 2);
            bStudentOne = currentIndex % 2 == 0;
            bNotPickedYet = (bStudentOne ? groups[whichGroup].studentOne == "" : groups[whichGroup].studentTwo == "");
        }
        
        if ( bStudentOne ){
            groups[whichGroup].studentOneSelected = true;
            groups[whichGroup].studentTwoSelected = false;
        } else {
            groups[whichGroup].studentOneSelected = false;
            groups[whichGroup].studentTwoSelected = true;
        }
        
        if ( bRandomizing && speed < 10 ){
            speed += .1;
        } else if ( !bRandomizing ){
            speed *= .95;
            if ( speed < .1 ){
                speed = 0;
                selectRandom();
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    drawBackground();
    // turn lights on if we're randomizing!
    if ( speed != 0 ) lights.bActive = true;
    else lights.bActive = false;
    
    int x = (int) pos.x;
    int y = (int) pos.y + fontSize;
    
    for (int i=0; i<numGroups; i++){
        groups[i].draw();
        
        // deselect
        groups[i].studentOneSelected = groups[i].studentTwoSelected = false;
    }
}

//--------------------------------------------------------------
void testApp::drawBackground(){
    // draw background
    ofBackground(31,104,41);
    ofSetColor(195,0,71);
    ofRectRounded(60,60, ofGetWidth()-120, ofGetHeight()-120, 40);
    ofSetColor(207,196,38);
    ofRectRounded(120,120, ofGetWidth()-240, ofGetHeight()-240, 30);
    
    lights.draw();
}

//--------------------------------------------------------------
void testApp::selectRandom(){
    if ( bGroupsPicked) return;
    
    int whichGroup = floor( currentIndex / 2);
    bool bStudentOne = currentIndex % 2 == 0;
    bool bNotPickedYet = (bStudentOne ? groups[whichGroup].studentOne == "" : groups[whichGroup].studentTwo == "");
    
    while ( !bNotPickedYet ){
        currentIndex++;
        if ( currentIndex >= students.size() ){
            currentIndex = 0;
        }
        whichGroup = floor( currentIndex / 2);
        bStudentOne = currentIndex % 2 == 0;
        bNotPickedYet = (bStudentOne ? groups[whichGroup].studentOne == "" : groups[whichGroup].studentTwo == "");
    }
    
    int random = int(ofRandom(students.size()));
    while ( students[random] == "" ){
        random = int(ofRandom(students.size()));
    }
    
    if ( bStudentOne ){
        groups[whichGroup].studentOne = students[random];
    } else {
        groups[whichGroup].studentTwo  = students[random];
    }
    
    // should we send to spacebrew now?
    
    if ( !(groups[whichGroup].studentOne == "") && !(groups[whichGroup].studentTwo  == "") ){
        spacebrewConnection.send("selectedGroup", "string", groups[whichGroup].studentOne+";"+ groups[whichGroup].studentTwo );
    }
    
    students[random] = "";
    
    // see if we have picked all the groups
    int numPicked = 0;
    for (int i=0; i<groups.size(); i++){
        if ( !(groups[i].studentOne == "") ) numPicked++;
        if ( !(groups[i].studentTwo == "") ) numPicked++;
    }
    
    if ( numPicked == students.size()) bGroupsPicked = true;
}

//--------------------------------------------------------------
void testApp::onMessage( Spacebrew::Message & m ){
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){}

//--------------------------------------------------------------
void testApp::keyReleased(int key){}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    bRandomizing = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    bRandomizing = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){}