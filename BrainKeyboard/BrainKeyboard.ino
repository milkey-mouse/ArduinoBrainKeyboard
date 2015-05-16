#include <cmdline_defs.h>
#include <ProTrinketKeyboard.h>
#include <ProTrinketKeyboardC.h>
#include <usbconfig.h>

//Arduino Brain CSV_USB Keyboard
//By Milkey Mouse

#include <SoftwareSerial.h>
#include <Brain.h>


// Set up the software serial port on pins 12 (RX) and 11 (TX). We'll only actually hook up pin 12.
SoftwareSerial softSerial(12, 11);

// Set up the brain reader, pass it the software serial object you want to listen on.
Brain brain(softSerial);

void setup() {
  // Start the software serial.
  softSerial.begin(9600);
  
  // Start the hardware serial.
  Serial.begin(9600);

  //Start the keyboard.
  TrinketKeyboard.begin();
  TrinketKeyboard.println("signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma");
}

void loop() {
  TrinketKeyboard.poll();
  //Expect packets about once per second.
  //The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
  //"signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"
  if (brain.update()) {
    Serial.println(brain.readErrors());
    Serial.println(brain.readCSV());
    //type it
    TrinketKeyboard.println(brain.readCSV());
  }
}
