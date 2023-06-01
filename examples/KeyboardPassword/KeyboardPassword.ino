/* Released into the public domain */
/* Earle F. Philhower, III <earlephilhower@yahoo.com> */

#include "CH9329_Keyboard.h"

const int button = 2;

/* SoftwareSerial can also be used.
#include <SoftwareSerial.h>
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial mySerial (rxPin, txPin);
*/

void setup() {
  Serial.begin(CH9329_DEFAULT_BAUDRATE);
  CH9329_Keyboard.begin(Serial);
  /* or
  mySerial.begin(CH9329_DEFAULT_BAUDRATE);
  CH9329_Keyboard.begin(mySerial);
  */

  pinMode(button, INPUT_PULLUP);
  delay(5000);
  // Serial.printf("Arduino USB Password Typer\n");
  // Serial.printf("Press button to enter your super-secure(not!) password\n\n");
}

void loop() {
  if (digitalRead(button) == LOW) {
    CH9329_Keyboard.print("ThisPasswordIsWeakLikeABaby");
    while (digitalRead(button) == LOW);
  }
}
