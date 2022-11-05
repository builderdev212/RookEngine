#include <Arduino.h>
#include "countdown.h"

void countdown::start(int32_t seconds) {
  // If no clock is running...
  if ((isTimer == false)) {
    // Set the timer to be equal to true.
    isTimer = true;
    // If the timer is running and/or the timer is paused...
    if (((isRunningTimer == true) || (isPausedTimer == true)) || ((isRunningTimer == true) && (isPausedTimer == true))) {
      // Don't start the timer.
      return;
      // Else if the timer is not running and is not paused...
    } else {
      // Start the timer.
      isRunningTimer = true;
      // Make sure that the paused value is equal to false.
      isPausedTimer = false;
      // Set the end time to the current time plus however many seconds the timer is. Since millis() returns the milliseconds
      // since the microcontroller was turned on, the seconds are multiplied by 1000 to turn them into milliseconds.
      endTime = millis() + (seconds * 1000);
      // Set the time left to be equal to the initial amount of time.
      timeLeft = seconds * 1000;
    }
  }
}

void countdown::pause() {
  // If the timer is running...
  if ((isTimer == true)) {
    // If the timer is already paused...
    if (isPausedTimer == true) {
      // Don't pause the timer.
      return;
      // Else if the timer is not paused...
    } else {
      // Pause the timer.
      isPausedTimer = true;
      isRunningTimer = false;
      // Figure out the time left on the timer. This is used to figure out what time the timer should end when
      // the timer is unpaused.
      timeLeft = endTime - millis();
    }
  }
}

void countdown::resume() {
  // If the timer is running...
  if ((isTimer == true)) {
    // If the timer is already unpaused...
    if (isPausedTimer == false) {
      // Don't unpause the timer.
      return;
      // Else if the timer is paused...
    } else {
      // Unpause the timer.
      isPausedTimer = false;
      isRunningTimer = true;
      // Set the end time to be equal to the current time plus the time left on the timer.
      endTime = millis() + timeLeft;
    }
  }
}

void countdown::stop() {
  // If the timer is running...
  if ((isTimer == true)) {
    // Stop the timer.
    isPausedTimer = false;
    isRunningTimer = false;
    // Set the end time to the current time.
    endTime = millis();
    // Set the time left to be equal to 0.
    timeLeft = 0;
  }
}

bool countdown::isDone() {
  // If the timer is running...
  if ((isTimer == true)) {
    // If the timer is running and is not paused, and the end time is less than or equal to the current time...
    if (((isRunningTimer == true) && (isPausedTimer == false)) && (endTime <= millis())) {
      // Reset the timer variables to stop the timer.
      isRunningTimer = false;
      isPausedTimer = false;
      // Turn the timer off.
      isTimer = false;
      // Return true.
      return true;
      // Else if the timer is still running...
    } else {
      // Return false.
      return false;
    }
  } else {
    return false;
  }
}
