import spacebrew.*;
import java.util.Collections;
import java.util.Arrays;

String server="localhost";
String name="Randomizer";
String description ="This sketch will randomly assign students (from students.txt) and assigns them to something (assign.txt)";

Spacebrew spacebrewConnection;

// array of students
String students[];
String groups[];
boolean bGroupsPicked = false;
int    groupSize;
int    numGroups = 0;

// array of assignments
String assignments[];

// visual stuff
PFont arial;
int   fontSize = 18;
int   squareWidth;
int   squareHeight = (fontSize + 10)*2;
int   padding = 20;

// randomize!
boolean bRandomizing = false;
int     currentIndex = 0;
float   floatIndex   = 0;
float   speed        = 0;

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
  textFont(arial);
  squareWidth = (width-padding*3)/2;
}

void draw() {
  background(0);
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
    
    if ( bRandomizing && speed < 5 ){
      speed += .1;
    } else if ( !bRandomizing ){
      speed *= .95;
      if ( speed < .1 ){
        speed = 0;
        selectRandom();
      }
    }
  }
  
  int x = padding;
  int y = padding + fontSize;
   
  for (int i=0; i<numGroups; i++){
    fill(255);
    text( assignments[i], x,y);
    y += 10;
    
    
    if ( currentIndex == i*2 ) fill(200);
    else fill(150);
    rect(x,y,squareWidth,squareHeight/2);
  
    fill(0);
    text(groups[i*2], x + 4, y+fontSize+ 2);
    
    y += squareHeight/2;
    
    if ( currentIndex == i*2 + 1 ) fill(200);
    else fill(150);
    rect(x,y,squareWidth,squareHeight/2);
    
    fill(0);
    text(groups[i*2 + 1], x+ 4, y+fontSize+ 2);
    y += squareHeight + padding * 1.5;
    
    if ( y + squareHeight + padding * 1.5 >= height ){
      y = padding + fontSize;; 
      x += squareWidth + padding;
    }
  }
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
