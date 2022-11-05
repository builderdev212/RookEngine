#include "joystick.h"
#include "button.h"

// This is the pinout for the controls of the RookConsole.
const int X_PIN = 39;
const int Y_PIN = 36;
const int JOY_B = 12;
const int TOP_B = 32;
const int BOT_B = 33;
const int LEFT_B = 13;
const int RIGHT_B = 14;

joystick stick(X_PIN, Y_PIN);
button joy(JOY_B);
button top(TOP_B);
button bot(BOT_B);
button left(LEFT_B);
button right(RIGHT_B);

void setup() {
    Serial.begin(115200);

    // Calculate the center of the joystick.
    stick.center();
}


void loop() {
  while (true) {
    // BUTTON STATES
    Serial.print("Top: ");
    // Get the current state of the button.
    Serial.print(top.read());
    // Do the same for all the buttons.
    Serial.print(" Bottom: ");
    Serial.print(bot.read());
    Serial.print(" Left: ");
    Serial.print(left.read());
    Serial.print(" Right: ");
    Serial.print(right.read());
    Serial.print(" Joy: ");
    Serial.println(joy.read());

    // JOYSTICK STATES
    Serial.print("x: ");
    // Print the x value.
    Serial.print(stick.read(0));
    Serial.print(", y: ");
    // Print the y value.
    Serial.println(stick.read(1));

    delay(100);
  }
}
