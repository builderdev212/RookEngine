#include <Arduino.h>

int16_t xVal;
int16_t yVal;

int8_t readJoy(int8_t axis) {
  switch (axis) {
    // x axis
    case 0:
      xVal = analogRead(36);
      if (xVal < 1800) {
        return 1;
      } else if (xVal > 2200) {
        return -1;
      } else {
        return 0;
      }
      break;
    // y axis
    case 1:
      yVal = analogRead(39);
      if (yVal < 1800) {
        return -1;
      } else if (yVal > 2200) {
        return 1;
      } else {
        return 0;
      }
      break;
  }
}
