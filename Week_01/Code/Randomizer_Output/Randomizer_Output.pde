import spacebrew.*;
import java.util.Collections;
import java.util.Arrays;

String server="localhost";
String name="Randomizer";
String description ="This sketch will randomly assign students (from students.txt) and assigns them to something (assign.txt)";

Spacebrew spacebrewConnection;

// array of students
String   students[];
String   groups[];
boolean  bGroupsPicked = false;
int      groupSize;
int      numGroups = 0;

// array of assignments
String   assignments[];

// visual stuff
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

void setup() {
  size(1024, 768);
  
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
    groups   = new String[tempStudents.length - 1];
    for (int i=1; i<tempStudents.length; i++){
      students[i-1] = tempStudents[i];
      groups[i-1]   = ""; // fill in group array with empty strings
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
}

void draw() {
  drawBackground();
  
  // update randomizer
  if ( (bRandomizing || speed > 0 ) && !bGroupsPicked ){
    floatIndex += speed;
    currentIndex = floor(floatIndex);
    
    while ( currentIndex >= students.length ){
      currentIndex -= students.length;
    }
    
    while ( !groups[currentIndex].equals("") ){
      currentIndex++;
      while ( currentIndex >= students.length ){
        currentIndex -= students.length;
      }
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
  
  // turn lights on if we're randomizing!
  if ( speed != 0 ) lights.bActive = true;
  else lights.bActive = false;
  
  int x = (int) pos.x;
  int y = (int) pos.y + fontSize;
   
  for (int i=0; i<numGroups; i++){
    fill(10,50,11);
    text( assignments[i], x,y);
    y += 10;
    
    if ( currentIndex == i*2 ) fill(255);
    else fill(130,159,180);
    rect(x,y,squareWidth,squareHeight/2);
  
    fill(0);
    text(groups[i*2], x + 4, y+fontSize+ 2);
    
    y += squareHeight/2;
    
    if ( currentIndex == i*2 + 1 ) fill(255);
    else fill(45,86,117);
    rect(x,y,squareWidth,squareHeight/2);
    
    fill(0);
    text(groups[i*2 + 1], x+ 4, y+fontSize+ 2);
    y += squareHeight + padding * 1.5;
    
    if ( y + squareHeight + padding > height - pos.y ){
      y = (int) pos.y + fontSize;; 
      x += squareWidth + padding;
    }
  }
}

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

void selectRandom(){
  if ( bGroupsPicked) return;
  
  while ( !groups[currentIndex].equals("") ){
    currentIndex++;
    if ( currentIndex >= students.length ){
      currentIndex = 0;
    }
  }
  
  int random = int(random(students.length));
   println( "select "+students[random] );
   while ( students[random].equals("") ){
    random = int(random(students.length));
    println( "select "+students[random] );
  }
  
  println( "select "+students[random] );
  
  groups[currentIndex] = students[random];
  students[random] = "";
  
  int numPicked = 0;
  for (int i=0; i<groups.length; i++){
    if (!groups[i].equals("")) numPicked++;
  }
  
  if ( numPicked == groups.length) bGroupsPicked = true;
}

void mousePressed(){
  bRandomizing = true;
}

void mouseReleased(){
  bRandomizing = false;
}


void onRangeMessage( String name, int value ){
  println("got int message "+name +" : "+ value);
}

void onBooleanMessage( String name, boolean value ){
  if ( name.equals("randomize") ){
    bRandomizing = value;
  }
}

void onStringMessage( String name, String value ){
  println("got string message "+name +" : "+ value);  
}
