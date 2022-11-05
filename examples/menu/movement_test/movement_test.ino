#include <TFT_eSPI.h>
#include <SPI.h>
#include "menu.h"

// Setup display library.
TFT_eSPI *tft = new TFT_eSPI();

// Define the fonts.
#define sans &FreeSans9pt7b
#define sansBold &FreeSansBold9pt7b

void setup() {
  // Begin the serial monitor for debugging.
  Serial.begin(115200);

  // Select the chip used for the TFT display.
  digitalWrite(15, HIGH);

  // Setup the TFT display.
  tft->begin();
  tft->setRotation(1);
  tft->fillScreen(0);
}

// Custom background function.
void background(TFT_eSPI *_tft, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
  _tft->fillRect(x, y, w, h, TFT_WHITE);
}

// Custom button drawing function.
void drawTest(TFT_eSPI *_tft, int x, int y) {
  _tft->fillRect(x, y, 10, 10, TFT_BLUE);
}

// Custom button hover function.
void hoverTest(TFT_eSPI *_tft, int x, int y) {
  _tft->drawRect(x, y, 10, 10, TFT_ORANGE);
  _tft->drawRect(x + 1, y + 1, 8, 8, TFT_ORANGE);
}

// Custom button selection function.
void selectTest(TFT_eSPI *_tft, int x, int y) {
  _tft->drawRect(x, y, 10, 10, TFT_GREEN);
  _tft->drawRect(x + 1, y + 1, 8, 8, TFT_GREEN);
}

// Custom button disabled function.
void disableTest(TFT_eSPI *_tft, int x, int y) {
  _tft->fillRect(x, y, 10, 10, TFT_RED);
}

void loop() {
  // Setup the inital button layout.
  buttonLayout layout;
  layout.x = 0;
  layout.y = 0;
  layout.w = 100;
  layout.h = 100;

  // Pass the display library, the layout, and the color to make the display.
  buttonSet buttonTest(tft, layout, TFT_WHITE);
  // Uncomment the following line to see an example of a background being drawn from
  // A function. This can be used to create custom backgrounds.
  // buttonSet buttonTest(tft, layout, background);

  // Initate the button setup variable.
  buttonsInfo buttons;
  buttons.rows = 5;
  buttons.buttonPerRow = new uint16_t[buttons.rows];
  buttons.buttons = new button*[buttons.rows];
  // Set the number of rows of buttons.
  // Set the number of buttons per row.
  for (int n = 0; n < buttons.rows; n++) {
    buttons.buttonPerRow[n] = 5;
  }

  // Setup the arrays to fill.
  buttons = buttonTest.initButtons(buttons);

  // Create the button. This can be done individually for different types of buttons,
  // but in this case all of the buttons are the same.
  button singleButton;
  singleButton.w = 10;
  singleButton.h = 10;

  // Create the pointers to the functions.
  void (*draw)(TFT_eSPI*, int, int);
  void (*hover)(TFT_eSPI*, int, int);
  void (*select)(TFT_eSPI*, int, int);
  void (*disable)(TFT_eSPI*, int, int);

  // Set the pointers to be equal to the respective functions.
  draw = drawTest;
  hover = hoverTest;
  select = selectTest;
  disable = disableTest;

  singleButton.draw = draw;
  singleButton.select = select;
  singleButton.hover = hover;
  singleButton.disable = disable;

  // Fill the respective arrays with the functions. Keep in mind that each button
  // can have unique functions, however for the sake of this example, all of the
  // buttons are the same.
  for (int n = 0; n < buttons.rows; n++) {
    for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
      buttons.buttons[n][i] = singleButton;
    }
  }

  // Setup the buttons with the array of values, figure out the inital positions,
  // and draw all of the buttons to the screen.
  buttonTest.setup(buttons);

  buttonTest.hoverOn();

  pos test;

  for (int n = 0; n < 5; n++) {
    for (int m = 0; m < 5; m++) {
      test.x = m;
      test.y = n;

      buttonTest.setHoveredButton(test);
      delay(1000);
    }
  }

  delay(1000000);
}
