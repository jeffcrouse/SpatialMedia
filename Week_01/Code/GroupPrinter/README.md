# Group Printer




### Description

This code is meant to be run on a Arduino Uno with an Ethernet shield connected to a [thermal printer](http://www.adafruit.com/products/597).  

![Mini Thermal Printer](http://www.adafruit.com/images/medium/thermalprinter_MED.jpg)

It accepts string (from Spacebrew) that look like this:

    One;Two;Three

and prints 

![receipt](http://4u.jeffcrouse.info/spatialmedia/receipt.png)


### Spacebrew info

- **Name**: GroupPrinter
- **Server**: sandbox.spacebrew.cc
- **Subscriptions**: 
  - Printer
- **Publishers**
  - none


### Setup
  
- green = 5
- yellow = 6
- red = gnd



### Required Libraries

Put into ~/Documents/Arduino/libraries

- Adafruit_Thermal: [Adafruit-Thermal-Printer-Library](https://github.com/adafruit/Adafruit-Thermal-Printer-Library)
- WebsocketClient: [ArduinoWebsocketClient](https://github.com/labatrockwell/ArduinoWebsocketClient)
- Spacebrew: [spacebrew-arduino-library](https://github.com/labatrockwell/spacebrew-arduino-library)