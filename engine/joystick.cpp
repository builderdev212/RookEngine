#include <Arduino.h>
#include "joystick.h"

const int X_AXIS = 0;
const int Y_AXIS = 1;

joystick::joystick(int x, int y, int joystickCenter) {
  xPin = x;
  yPin = y;
  center = joystickCenter;
};

joystick::joystick(int x, int y) {
  xPin = x;
  yPin = y;
}

void joystick::center() {
  // Get the x center.
  int xcenter = 0;
  for (int n = 0; n < 5; n++) {
    int16_t xcenter += analogRead(xPin);
  }
  xcenter /= 5;

  // Get they y center.
  int ycenter = 0;
  for (int n = 0; n < 5; n++) {
    int16_t ycenter += analogRead(yPin);
  }
  ycenter /= 5;

  // Get the center.
  center = (xcenter + ycenter)/2;
}

int joystick::readJoy(uint8_t axis) {
  switch (axis) {
    // x axis
    case (X_AXIS):
      {
        int16_t xVal = analogRead(xPin);
        if (xVal < (center-300)) {
          return -1;
        } else if (xVal > (center+300)) {
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
        if (yVal < (center-300)) {
          return -1;
        } else if (yVal > (center+300)) {
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
  // Set the orientation.
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
        if (xVal < (center-300)) {
          return -1*orient;
        } else if (xVal > (center+300)) {
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
        if (yVal < (center-300)) {
          return -1*orient;
        } else if (yVal > (center+300)) {
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

int joystick::readJoy(uint8_t axis, int multiplier) {
  switch (axis) {
    // x axis
    case (X_AXIS):
      {
        int16_t xVal = analogRead(xPin);
        if (xVal < (center-300)) {
          for (int i = 0; i < multiplier; i++) {
            if ((xVal > ((center-300)-((center-300)/multiplier)*(i+1))) && (xVal < ((center-300)-((center-300)/multiplier)*(i)))) {
              return (-1*(i+1));
            }
          }
        } else if (xVal > (center+300)) {
          for (int i = 0; i < multiplier; i++) {
            if ((xVal > ((center+300)+((center+300)/multiplier)*(i))) && (xVal < ((center+300)+((center+300)/multiplier)*(i+1)))) {
              return (-1*(i+1));
            }
          }
        } else {
          return 0;
        }
        break;
      }
    // y axis
    case (Y_AXIS):
      {
        int16_t yVal = analogRead(yPin);
        if (yVal < (center-300)) {
          for (int i = 0; i < multiplier; i++) {
            if ((yVal > ((center-300)-((center-300)/multiplier)*(i+1))) && (yVal < ((center-300)-((center-300)/multiplier)*(i)))) {
              return (-1*(i+1));
            }
          }
        } else if (yVal > (center+300)) {
          for (int i = 0; i < multiplier; i++) {
            if ((yVal > ((center+300)+((center+300)/multiplier)*(i))) && (yVal < ((center+300)+((center+300)/multiplier)*(i+1)))) {
              return (-1*(i+1));
            }
          }
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
