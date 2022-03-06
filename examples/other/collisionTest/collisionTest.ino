#include <SPI.h>
#include <TFT_eSPI.h>

#include "objectCollision.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // Setup the serial interface.
  Serial.begin(115200);

  // Select the chip used for the TFT display.
  digitalWrite(15, HIGH);

  // Setup the TFT display.
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(0);
}

void loop() {
  // TEST SHAPE 0
  rect shape0;
  shape0.x = 0;
  shape0.y = 0;
  shape0.w = 100;
  shape0.h = 100;

  // TEST SHAPE 1
  circle shape1;
  shape1.x = 100;
  shape1.y = 100;
  shape1.r = 20;

  // TEST SHAPE 2
  ellipse shape2;
  shape2.x = 50;
  shape2.y = 0;
  shape2.rx = 20;
  shape2.ry = 50;

  // TEST SHAPE 3
  circle shape3;
  shape3.x = 120;
  shape3.y = 120;
  shape3.r = 30;

  // TEST SHAPE 4
  ellipse shape4;
  shape4.x = 140;
  shape4.y = 100;
  shape4.rx = 50;
  shape4.ry = 10;

  // TEST SHAPE 5
  rect shape5;
  shape5.x = 200;
  shape5.y = 50;
  shape5.w = 30;
  shape5.h = 30;

  // TEST SHAPE 6
  circle shape6;
  shape6.x = 300;
  shape6.y = 240;
  shape6.r = 20;

  // Draw all of the test shapes so you can see a graphical representation.
  tft.fillRect(shape0.x, shape0.y, shape0.w, shape0.h, TFT_RED); // Shape 0
  tft.fillCircle(shape1.x, shape1.y, shape1.r, TFT_PURPLE); // Shape 1
  tft.fillEllipse(shape2.x, shape2.y, shape2.rx, shape2.ry, TFT_YELLOW); // Shape 2
  tft.fillCircle(shape3.x, shape3.y, shape3.r, TFT_BLUE); // Shape 3
  tft.fillEllipse(shape4.x, shape4.y, shape4.rx, shape4.ry, TFT_MAGENTA); // Shape 4
  tft.fillRect(shape5.x, shape5.y, shape5.w, shape5.h, TFT_GREEN); // Shape 5
  tft.fillCircle(shape6.x, shape6.y, shape6.r, TFT_BROWN); // Shape 6

  // Print to the serial monitor the shape type numbers. Move to new test file
  Serial.print("Rectangle: ");
  Serial.println(OBJECT_RECTANGLE);
  Serial.print("Circle: ");
  Serial.println(OBJECT_CIRCLE);
  Serial.print("Ellipse: ");
  Serial.println(OBJECT_ELLIPSE);
  Serial.println();

  // Set up  the collision class for all seven shapes.
  objectCollision colShape0(shape0);
  objectCollision colShape1(shape1);
  objectCollision colShape2(shape2);
  objectCollision colShape3(shape3);
  objectCollision colShape4(shape4);
  objectCollision colShape5(shape5);
  objectCollision colShape6(shape6);

  // All 21 combinations of pairs of the shapes.
  Serial.println("0 is false, 1 is true.");
  Serial.print("0 and 1: ");
  Serial.println(colShape0.isCollision(colShape1)); // true
  Serial.println(colShape0.isCollision(shape1));
  Serial.print("0 and 2: ");
  Serial.println(colShape0.isCollision(colShape2)); // true
  Serial.print("0 and 3: ");
  Serial.println(colShape0.isCollision(colShape3)); // true
  Serial.print("0 and 4: ");
  Serial.println(colShape0.isCollision(colShape4)); // false
  Serial.print("0 and 5: ");
  Serial.println(colShape0.isCollision(colShape5)); // false
  Serial.print("0 and 6: ");
  Serial.println(colShape0.isCollision(colShape6)); // false
  Serial.print("1 and 2: ");
  Serial.println(colShape1.isCollision(colShape2)); // false
  Serial.print("1 and 3: ");
  Serial.println(colShape1.isCollision(colShape3)); // true
  Serial.print("1 and 4: ");
  Serial.println(colShape1.isCollision(colShape4)); // true
  Serial.print("1 and 5: ");
  Serial.println(colShape1.isCollision(colShape5)); // false
  Serial.print("1 and 6: ");
  Serial.println(colShape1.isCollision(colShape6)); // false
  Serial.print("2 and 3: ");
  Serial.println(colShape2.isCollision(colShape3)); // false
  Serial.print("2 and 4: ");
  Serial.println(colShape2.isCollision(colShape4)); // false
  Serial.print("2 and 5: ");
  Serial.println(colShape2.isCollision(colShape5)); // false
  Serial.print("2 and 6: ");
  Serial.println(colShape2.isCollision(colShape6)); // false
  Serial.print("3 and 4: ");
  Serial.println(colShape3.isCollision(colShape4)); // true
  Serial.print("3 and 5: ");
  Serial.println(colShape3.isCollision(colShape5)); // false
  Serial.print("3 and 6: ");
  Serial.println(colShape3.isCollision(colShape6)); // false
  Serial.print("4 and 5: ");
  Serial.println(colShape4.isCollision(colShape5)); // false
  Serial.print("4 and 6: ");
  Serial.println(colShape4.isCollision(colShape6)); // false
  Serial.print("5 and 6: ");
  Serial.println(colShape5.isCollision(colShape6)); // false

  delay(100000);
}
