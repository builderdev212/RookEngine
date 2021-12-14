#include <Arduino.h>
#include "joystick.h"

const int X_AXIS = 0;
const int Y_AXIS = 1;

void joystick::begin(int x, int y) {
  xPin = x;
  yPin = y;
};

void joystick::begin(int x, int y, int z) {
  xPin = x;
  yPin = y;
  isButton = true;
  zPin = z;
  pinMode(zPin, INPUT_PULLUP);
};

int joystick::readJoy(uint8_t axis) {
  switch (axis) {
    // x axis
    case (X_AXIS):
      {
        int16_t xVal = analogRead(xPin);
        delay(10);
        if (xVal < 1800) {
          return -1;
        } else if (xVal > 2200) {
          return 1;
        } else {
          return 0;
        }
        break;
      }
    // y axis
    case (Y_AXIS):
      {
        int16_t yVal = analogRead(yPin);
        delay(10);
        if (yVal < 1700) {
          return -1;
        } else if (yVal > 2300) {
          return 1;
        } else {
          return 0;
        }
        break;
      }
    default:
      return 0;
      break;
  }
};

int joystick::readJoy(uint8_t axis, bool orientation) {
  int orient;
  if (orientation) {
    orient = 1;
  } else {
    orient = -1;
  }

  switch (axis) {
    // x axis
    case (X_AXIS):
      {
        int16_t xVal = analogRead(xPin);
        delay(10);
        if (xVal < 1800) {
          return -1*orient;
        } else if (xVal > 2200) {
          return 1*orient;
        } else {
          return 0;
        }
        break;
      }
    // y axis
    case (Y_AXIS):
      {
        int16_t yVal = analogRead(yPin);
        delay(10);
        if (yVal < 1700) {
          return -1*orient;
        } else if (yVal > 2300) {
          return 1*orient;
        } else {
          return 0;
        }
        break;
      }
    default:
      return 0;
      break;
  }
};

bool joystick::readZ(bool singular) {
  // If there is a joystick button.
  if (isButton) {
    // Read the joysticks buttons state.
    int buttonState = digitalRead(zPin);

    // If you're only looking for a state change.
    if (singular) {
      if (buttonState != lastButtonState) {
        lastButtonState = buttonState;
        if (buttonState == 0) {
          return true;
        }
      }
      // Else if you just want the current value of the button.
    } else {
      if (buttonState == 0) {
        return true;
      }
    }

    return false;
  // Else if there isn't one, just return false.
  } else {
    return false;
  }
};
