import spacebrew.*;

String server="sandbox.spacebrew.cc";
String name="FlashScreen";
String description ="This example flashes the screen white after a random delay when it receives any message.";

Spacebrew spacebrewConnection;

int messageReceived = 0;
int delay           = 0;
boolean bNeedToFlash = false;

void setup() {
  size(1920, 1080);
  
  spacebrewConnection = new Spacebrew( this );
  
  // add each thing you subscribe to
  spacebrewConnection.addSubscribe( "flash", "boolean" );
  
  // connect!
  spacebrewConnection.connect("ws://"+server+":9000", name, description );
  
}

void draw() {
  background(0);
  if ( millis() - messageReceived > delay && bNeedToFlash ){
    background(255);
    bNeedToFlash = false;
  }
}

void onBooleanMessage( String name, boolean value ){
  bNeedToFlash = true;
  messageReceived = millis();
  delay = (int) random(0,1000);
}
