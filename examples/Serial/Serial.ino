/*
  Keyboard test

  For the Arduino Leonardo, Micro or Due

  Reads a byte from the serial port, sends a keystroke back.
  The sent keystroke is one higher than what's received, e.g. if you send a,
  you get b, send A you get B, and so forth.

  The circuit:
  - none

  created 21 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/KeyboardSerial
*/

#include "CH9329_Keyboard.h"

/* SoftwareSerial can also be used.
#include <SoftwareSerial.h>
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial mySerial (rxPin, txPin);
*/

void setup() {
  // initialize control over the keyboard:
  Serial.begin(CH9329_DEFAULT_BAUDRATE);
  CH9329_Keyboard.begin(Serial);
  /* or
  mySerial.begin(9600);
  CH9329_Keyboard.begin(mySerial);
  */
}

void loop() {
  // check for incoming serial data:
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    // Type the next ASCII value from what you received:
    CH9329_Keyboard.write(inChar + 1);
  }
}
