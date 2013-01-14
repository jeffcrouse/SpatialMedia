
#include <SPI.h>
#include <Spacebrew.h>
#include <Ethernet.h>
#include <WebSocketClient.h>
#include "SoftwareSerial.h"
#include "Adafruit_Thermal.h"
//#include <avr/pgmspace.h>

// Make some vaaaaars
int printer_RX_Pin = 5;  // This is the green wire
int printer_TX_Pin = 6;  // This is the yellow wire
Adafruit_Thermal printer(printer_RX_Pin, printer_TX_Pin);
uint8_t mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
Spacebrew spacebrewConnection;

void setup(){
  Serial.begin(9600);
  pinMode(7, OUTPUT); 
  digitalWrite(7, LOW); // To also work w/IoTP printer
  printer.begin();

  spacebrewConnection.addSubscribe("Printer", SB_STRING);

  //connect to spacebrew library info
  spacebrewConnection.onOpen(onOpen);
  spacebrewConnection.onClose(onClose);
  spacebrewConnection.onError(onError);
  spacebrewConnection.onStringMessage(onStringMessage);

  //connect to the spacebrew server
  // http://spacebrew.cc/master/spacebrew/admin/admin.html?server=sandbox.spacebrew.cc
  Ethernet.begin(mac);
  spacebrewConnection.connect("sandbox.spacebrew.cc", "GroupPrinter", "Prints to the termal printer");
  Serial.println(Ethernet.localIP());
}

void loop() {
  spacebrewConnection.monitor();
}

void onStringMessage(char *name, char* message){
  
  String str = String(message);
  int idx = str.indexOf(';');
  int lastidx = str.lastIndexOf(';');
  
  String location = str.substring(0, idx);
  String name1 = str.substring(idx+1, lastidx);
  String name2 = str.substring(lastidx+1);
  
  
  Serial.println( "message:" );
  Serial.println( str );
  Serial.println( "location:" );
  Serial.println( location );
  Serial.println( "name1:" );
  Serial.println( name1 );
  Serial.println( "name2:" );
  Serial.println( name2 );

  
  // Test inverse on & off
  printer.justify('C');
  printer.setSize('L');     // Set type size, accepts 'S', 'M', 'L'
  printer.inverseOn();
  printer.println("Welcome to Spatial Media!");
  printer.inverseOff();

  printer.setLineHeight(50);
  printer.setSize('M');

  printer.underlineOn(); 
  printer.println( location );
  printer.underlineOff();


  printer.setSize('L');     // Set type size, accepts 'S', 'M', 'L'
  printer.inverseOn();
  printer.println("Your group is:");
  printer.inverseOff();

  printer.setLineHeight(); // Reset to default
  
  printer.setSize('M');
  printer.println( name1 );
  printer.println( name2 );
  printer.feed(1);

  printer.printBarcode("123456789123", UPC_A);
  
  printer.println("Thanks, and have a great day!");
  
  /*
  // Test character double-height on & off
   printer.doubleHeightOn();
   printer.println("Double Height ON");
   printer.doubleHeightOff();
   
   // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
   printer.justify('R');
   printer.println("Right justified");
   printer.justify('C');
   printer.println("Center justified");
   printer.justify('L');
   printer.println("Left justified");
   
   // Test more styles
   printer.boldOn();
   printer.println("Bold text");
   printer.boldOff();
   
   printer.underlineOn(); 
   printer.println("Underlined text ");
   printer.underlineOff();
   
   
   printer.println("Large"); // Print line
   printer.setSize('M');
   printer.println("Medium");
   printer.setSize('S');
   printer.println("Small");
   
   printer.justify('C');
   printer.println("normal\nline\nspacing");
   printer.setLineHeight(50);
   printer.println("Taller\nline\nspacing");
   printer.setLineHeight(); // Reset to default
   printer.justify('L');
   
   // Barcode examples
   printer.feed(1);
   // CODE39 is the most common alphanumeric barcode
   printer.printBarcode("ADAFRUT", CODE39);
   printer.setBarcodeHeight(100);
   // Print UPC line on product barcodes
   printer.printBarcode("123456789123", UPC_A);
  */


  printer.feed(3);
  printer.sleep();      // Tell printer to sleep
  printer.wake();       // MUST call wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
}


void onOpen(){
  Serial.println("onOpen");
}
void onClose(int code, char* message){
  Serial.println("onClose");
}
void onError(char* message){
  Serial.println("onError");
  Serial.println(message);
}






