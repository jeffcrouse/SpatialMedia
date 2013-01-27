import spacebrew.*;
import java.util.Collections;
import java.util.Arrays;

String server="localhost";
String name="Randomizer";
String description ="This sketch will randomly assign students (from students.txt) and assigns them to something (assign.txt)";

Spacebrew spacebrewConnection;

// array of students
String   students[];
Group    groups[];

boolean  bGroupsPicked = false;
int      groupSize;
int      numGroups = 0;

// array of assignments
String   assignments[];

// visual stuff
ContestantDisplay contestant;
PFont   arial;
int     fontSize = 18;
int     squareWidth;
int     squareHeight = (fontSize + 10)*2;
int     padding      = 15;

// randomize!
boolean bRandomizing = false;
int     currentIndex = 0;
float   floatIndex   = 0;
float   speed        = 0;
PVector pos          = new PVector(150,150);
Lights  lights;

//---------------------------------------------------------------
void setup() {
  size(1024, 768);
  frameRate(60);
  
  // load from spacebrew.txt
  String spacebrewConfig[] = loadStrings("spacebrew.txt");
  if ( spacebrewConfig != null && spacebrewConfig.length > 0 ){
    server = spacebrewConfig[0];
  }
  
  spacebrewConnection = new Spacebrew( this );
  
  // add each thing you publish to
  spacebrewConnection.addPublish( "selectedGroup", "" ); 

  // add each thing you subscribe to
  spacebrewConnection.addSubscribe( "randomize", "boolean" );
  
  // connect!
  spacebrewConnection.connect("ws://"+server+":9000", name, description );
  
  // load students
  String tempStudents[] = loadStrings("students.txt");
  
  // null = file doesn't exist :(
  if ( tempStudents != null ){
    println(tempStudents[0]);
    groupSize = int(tempStudents[0]); // # of people in group is first line
    
    // need to make students an array that is length-1 (so we don't include that first line)
    students = new String[tempStudents.length - 1];
    for (int i=1; i<tempStudents.length; i++){
      students[i-1] = tempStudents[i];
    }
    numGroups = ceil(students.length / groupSize);
  }
  
  // load assignments
  assignments = loadStrings("assign.txt");
  
  // nifty way to randomize array
  Collections.shuffle(Arrays.asList(assignments));
  
  // visual stuff
  arial = createFont("Arial", fontSize);
  lights = new Lights(90,90, width-180, height-180, 0);
  textFont(arial);
  squareWidth = (width-((int)pos.x * 2) - padding*3)/2;
  
  // setup contestant display
  contestant = new ContestantDisplay( "Arial", 30 );
  
  // setup groups!
  groups   = new Group[numGroups];
  int x = (int) pos.x;
  int y = (int) pos.y + fontSize;
  
  for (int i=0; i<numGroups; i++){
    groups[i] = new Group( x, y, squareWidth, squareHeight );
    groups[i].assignment = assignments[i];
    
    y += 10;
    y += squareHeight/2;
    y += squareHeight + padding * 1.5;
    
    if ( y + squareHeight + padding > height - pos.y ){
      y = (int) pos.y + fontSize;; 
      x += squareWidth + padding;
    }
  }
  
  // get started!
  String upNext = selectContestant();
  contestant.activate( upNext );
}

//---------------------------------------------------------------
void draw() {
  drawBackground();
  // update randomizer
  randomize();
  
  // turn lights on if we're randomizing!
  if ( speed != 0 ) lights.bActive = true;
  else lights.bActive = false;
   
  textFont(arial);
  for (int i=0; i<numGroups; i++){
    groups[i].draw();
    
    // deselect
    groups[i].studentOneSelected = groups[i].studentTwoSelected = false;
  }
  
  // draw "up next"
  contestant.draw();
}

/**
  Draws Price Is Right style background + lights
*/
void drawBackground(){
  // draw background
  background(31,104,41);
  noStroke();
  fill(195,0,71);
  rect(60,60, width-120, height-120, 40);
  fill(207,196,38);
  rect(120,120, width-240, height-240, 30);
  
  lights.draw();
}

/**
  Select next available contestant
*/
String selectContestant(){
  int random = int(random(students.length));
  while ( students[random].equals("") ){
    random = int(random(students.length));
  }
  String toReturn = students[random];
  students[random] = "";
  return toReturn;
}

/**
  Randomize: if bRandomizing is true, select next available spot,
  accelerate chooser. If done, connect contestant with group + check
  to see if we're all done.
*/
void randomize(){
  if ( bGroupsPicked) return;
  
  if ( (bRandomizing || speed > 0 ) ){
    
    floatIndex += speed;
    currentIndex = floor(floatIndex);
    
    while ( currentIndex >= students.length ){
      currentIndex -= students.length;
    }
    
    // try to pick the next empty spot
    int whichGroup = floor( currentIndex / 2);
    boolean bStudentOne = currentIndex % 2 == 0;
    boolean bNotPickedYet = (bStudentOne ? groups[whichGroup].studentOne == "" : groups[whichGroup].studentTwo == "");
    
    while ( !bNotPickedYet ){
      currentIndex++;
      while ( currentIndex >= students.length ){
        currentIndex -= students.length;
      }
      whichGroup = floor( currentIndex / 2);
      bStudentOne = currentIndex % 2 == 0;
      bNotPickedYet = (bStudentOne ? groups[whichGroup].studentOne == "" : groups[whichGroup].studentTwo == "");
    }
    
    // set groups selected for drawing
    if ( bStudentOne ){
      groups[whichGroup].studentOneSelected = true;
      groups[whichGroup].studentTwoSelected = false;
    } else {
      groups[whichGroup].studentOneSelected = false;
      groups[whichGroup].studentTwoSelected = true;
    } 
    
    // slow to stop if done randomizing
    if ( bRandomizing && speed < 10 ){
      speed += .1;
    } else if ( !bRandomizing ){
      speed *= .95;
      
      // stopped, time to select!
      if ( speed < .1 ){
        speed = 0;
        if ( bStudentOne ){
          groups[whichGroup].studentOne = contestant.current;
        } else {
          groups[whichGroup].studentTwo  = contestant.current;
        } 
        
        // should we send to spacebrew now?
        if ( !groups[whichGroup].studentOne.equals("") && !groups[whichGroup].studentTwo.equals("") ){
          spacebrewConnection.send("selectedGroup", groups[whichGroup].assignment +";" + groups[whichGroup].studentOne+";"+ groups[whichGroup].studentTwo );
        }
        
        // see if we have picked all the groups
        int numPicked = 0;
        for (int i=0; i<groups.length; i++){
          if ( !groups[i].studentOne.equals("") ) numPicked++;
          if ( !groups[i].studentTwo.equals("") ) numPicked++;
        }
        
        if ( numPicked == students.length) bGroupsPicked = true;
        
        if ( !bGroupsPicked ){
          String upNext = selectContestant();
          contestant.activate( upNext );
        }
      }
    }
  }
}

//---------------------------------------------------------------
void mousePressed(){
  bRandomizing = true;
  contestant.deactivate();
}

//---------------------------------------------------------------
void mouseReleased(){
  bRandomizing = false;
}

//---------------------------------------------------------------
void onBooleanMessage( String name, boolean value ){
  if ( name.equals("randomize") ){
    bRandomizing = value;
    contestant.deactivate();
  }
}

//---------------------------------------------------------------
void onRangeMessage( String name, int value ){}

//---------------------------------------------------------------
void onStringMessage( String name, String value ){}
