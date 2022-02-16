#include "joystick.h"

// Initalize the joystick on pin 33 (x) and pin 32 (y).
joystick stick(33, 32);

void setup() {
  Serial.begin(115200);
  // Calculate the center of the joystick.
  stick.center();
}

void loop() {
  Serial.print("x: ");
  // Print the x value.
  Serial.print(stick.read(0));
  Serial.print(", y: ");
  // Print the y value.
  Serial.println(stick.read(1));
  delay(100);
}
