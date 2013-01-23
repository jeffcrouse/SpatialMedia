import spacebrew.*;

String server="localhost";
String name="Pinwheel";
String description ="This sketch sends a boolean true when someone is blowing into the pinwheel, and a false when someone stops";
import processing.serial.*;

Serial myPort;  // Create object from Serial class
int serialState = 0;
int lastRead    = 0;

Spacebrew spacebrew;

boolean bReading = false;

void setup() {
  frameRate(240);
  size(600, 400);
  
 // load from spacebrew.txt
  String spacebrewConfig[] = loadStrings("spacebrew.txt");
  if ( spacebrewConfig != null && spacebrewConfig.length > 0 ){
    server = spacebrewConfig[0];
  }
  
  println("connect "+server);
  
  spacebrew = new Spacebrew( this );
  
  // add each thing you publish and subscribe to
  spacebrew.addPublish( "pinwheel", false );
  
  // connect!
  spacebrew.connect("ws://"+server+":9000", name, description );
  
  // connect to serial
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[4], 57600);
  //myPort.bufferUntil('\n');
}

void draw() {
  background( 255 );
  fill(20);
  textSize(30);
  if ( bReading ){
    text("Spinning!", 20, 320);
  } else {
    text("Spin the pinwheel!", 20, 320);
  }
  
  if(myPort.available() > 0) {
    serialState = myPort.read();
    if (!bReading){
      spacebrew.send("pinwheel", true);
      bReading = true;
      println("spin");
    }
    lastRead = millis();
  }
  
  // haven't gotten a read in a 100 millis?
  if ( millis() - lastRead > 100 && bReading){
      println("stopped");
      spacebrew.send("pinwheel", false);
      bReading = false;
  }
}

void onRangeMessage( String name, int value ){
  println("got int message "+name +" : "+ value);
}

void onBooleanMessage( String name, boolean value ){
  println("got bool message "+name +" : "+ value);  
}

void onStringMessage( String name, String value ){
  println("got string message "+name +" : "+ value);  
}
