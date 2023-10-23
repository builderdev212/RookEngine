#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "location.h"
#include "drawHelper.h"
#include "obj.h"

TFT_eSPI *tft = new TFT_eSPI();

void testDraw(TFT_eSprite *objSprite) {
  objSprite->fillRect(0, 0, 100, 100, TFT_BLUE);
}

void setup() {
  Serial.begin(115200);
  Serial.print("yay");
  log_e("test");
  log_i("banana");

  tft->init();
  tft->setRotation(3);
  tft->fillScreen(TFT_WHITE);
}

void loop() {
  position testPos = {0, 0};
  rectangle testRect = {100, 100};
  delay(1000);

  obj<rectangle> test1(tft, testPos, testRect, TFT_BLACK, true, testDraw);
  delay(5000);
  /*
  triangle testTri = {0, 0, 100, 0, 0, 100};

  obj<triangle> test2(tft, testPos, testTri, TFT_BLACK, true, testDraw);
  delay(3000);

  circle testCirc = {50, 50};

  obj<circle> test3(tft, testPos, testCirc, TFT_BLACK, true, testDraw);
  delay(3000);
  */
}


