#ifndef MENU_H
#define MENU_H

struct buttonLayout {
  uint16_t x = 0;
  uint16_t y = 0;
  uint16_t w = 0;
  uint16_t h = 0;
};

using buttonFunc = void(*)(TFT_eSPI*, int, int);

struct button {
  uint16_t x;
  uint16_t y;
  uint16_t w;
  uint16_t h;
  bool isDisabled = false;
  bool selected = false;
  bool hovered = false;
  buttonFunc draw;
  buttonFunc select;
  buttonFunc hover;
  buttonFunc disable;
};

struct buttonsInfo {
  uint16_t rows;
  uint16_t* buttonPerRow;
  button** buttons;
};

struct pos {
  uint16_t x;
  uint16_t y;
};

class buttonSet {
  public:
    // SETUP FUNCTIONS

    buttonSet(TFT_eSPI*, buttonLayout, void (*)(TFT_eSPI*, uint16_t, uint16_t, uint16_t, uint16_t));

    buttonSet(TFT_eSPI*, buttonLayout, void (*)(TFT_eSPI*, uint16_t, uint16_t, uint16_t, uint16_t), pos);

    buttonSet(TFT_eSPI*, buttonLayout, int);

    buttonSet(TFT_eSPI*, buttonLayout, int, pos);

    // STRUCTURE SETUP

    // Function to setups the buttonsInfo array.
    buttonsInfo initButtons(buttonsInfo);

    // BUTTON FUNCTIONS

    // Function to draw all of the buttons.
    void drawButtons();

    // Function to calculate all of the x and y values.
    void calcButtonsPos();

    // This function sets up the button info.
    void setup(buttonsInfo);

    // BUTTON ADDITION FUNCTIONS

    // This function will add in a new button at the location given to it.
    void addButton(button, uint16_t, uint16_t);

    // Function to remove a button.
    void removeButton(uint16_t, uint16_t);

    // Disable a button at a given spot.
    void disableButton(uint16_t, uint16_t);

    // Enable a button at the given spot.
    void enableButton(uint16_t, uint16_t);

    // Disable an entire row.
    void disableRow(uint16_t);

    // Enable an entire row.
    void enableRow(uint16_t);

    // Disable all buttons.
    void disableAll();

    // Enable all buttons.
    void enableAll();

    // BUTTON HOVER FUNCTIONS

    // Set the position of the hover.
    void setHoveredButton(pos);

    // Turn hover on.
    void hoverOn();

    // Turn hover off.
    void hoverOff();

  private:
    // Variable to store the display library.
    TFT_eSPI *_tft = nullptr;

    // Structure that holds the button layout.
    buttonLayout layout;
    // Structure that holds the buttons.
    buttonsInfo buttons;

    // Function to draw the background.
    void (*background)(TFT_eSPI*, uint16_t, uint16_t, uint16_t, uint16_t) = nullptr;
    // Variable to store the background color.
    uint32_t bgColor;

    // Variable to store hover position.
    pos hoverPos;

    // Variable to store the status of the hover.
    bool isHoverOn = false;

    // BUTTON HOVER FUNCTIONS

    // Function used to validate if the position is within the possible position.
    bool isValidPos(pos);

    // BACKGROUND FUNCTIONS

    // Function to draw the background to the screen. It figures out if it needs to draw a user definited bacground or a color.
    void drawBackground();
};

#endif
