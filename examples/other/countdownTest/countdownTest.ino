#include "countdown.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  countdown timer;
  // Set a countdown for 30 seconds.
  timer.start(30);
  // Wait 15 seconds.
  delay(15000);
  timer.pause();
  // Print the time left in milliseconds.
  Serial.println(timer.timeLeft);
  // Resume the timer.
  timer.resume();
  // Wait until the timer is finished.
  while(timer.isDone() != true) {

  }
  Serial.println("Your 30 second timer is finished!");
}
