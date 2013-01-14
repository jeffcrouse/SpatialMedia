import spacebrew.*;

String server="sandbox.spacebrew.cc";
String name="givemeabettername";
String description ="This is an example client which .... It also listens to...";

Spacebrew c;

void setup() {
  size(600, 400);
  
  c = new Spacebrew( this );
  
  // add each thing you publish to
  c.addPublish( "sendGroup", "foo" ); 

  // add each thing you subscribe to
  // spacebrewConnection.addSubscribe( "color", "range" );
  
  // connect!
  c.connect("ws://"+server+":9000", name, description );
  
}

void draw() {

}

void mousePressed() {
  c.send( "sendGroup", "one;two;three");
}



void onRangeMessage( String name, int value ){
  println("got int message "+name +" : "+ value);
  //  // check name by using equals
  //  if (name.equals("color") == true) {
  //      currentColor = value;
  //  }
}

void onBooleanMessage( String name, boolean value ){
  println("got bool message "+name +" : "+ value);  
}

void onStringMessage( String name, String value ){
  println("got string message "+name +" : "+ value);  
}
