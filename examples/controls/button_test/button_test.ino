#include "button.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Initalize a button on pin 27 as input pullup. This is the default.
  button test(27);

  while (true) {
    Serial.print("State: ");
    // Get the current state of the button.
    Serial.print(test.read());

    Serial.print(" Unique: ");
    // See if there has been a unique button press.
    Serial.println(test.uniqueRead());
    delay(10);
  }
}
