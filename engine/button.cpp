#include <Arduino.h>
#include "button.h"

button::button(int pin) {
  // Set the pin.
  buttonPin = pin;
  // Setup the pin for pullup.
  pinMode(buttonPin, INPUT_PULLUP);
}

button::button(int pin, byte inputType) {
  // Set the pin.
  buttonPin = pin;
  // Setup the pin to the given mode.
  pinMode(buttonPin, inputType);
}

bool button::read() {
  // Read the button state.
  readButton();

  // Return that state.
  if (currentState == HIGH) {
    return true;
  } else {
    return false;
  }
}

bool button::uniqueRead() {
  // Read the button state.
  readButton();

  // If there has been a change in state, return true, else return false.
  if (previousState != currentState) {
    previousState = currentState;
    if (previousState == HIGH) {
      return true;
    }
  }
  return false;
}

void button::readButton() {
  // Store the current button state.
  int state = digitalRead(buttonPin);

  // Only store the new state if it has been more than five milliseconds since the last one.
  if ((millis() - lastDebounce) > debounceDelay) {
    lastDebounce = millis();
    currentState = state;
  }
}
