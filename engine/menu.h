#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

struct buttonLayout {
  uint16_t x = 0;
  uint16_t y = 0;
  uint16_t w = 0;
  uint16_t h = 0;
  
};

struct buttonSize {
  uint16_t w = 0;
  uint16_t h = 0;
};

using disableB = void(*)(TFT_eSPI*, int, int);
using drawButton = void(*)(TFT_eSPI*, int, int);
using selectButton = void(*)(TFT_eSPI*, int, int);
using hoverButton = void(*)(TFT_eSPI*, int, int);

struct buttonSetup {
  uint16_t rows = 1;
  uint16_t* buttonPerRow = new uint16_t[rows];
  drawButton** drawFuncs = new drawButton*[rows];
  buttonSize** sizes = new buttonSize*[rows];
  selectButton** selectFuncs = new selectButton*[rows];
  hoverButton** hoverFuncs = new hoverButton*[rows];
  disableB** disableFuncs = new disableB*[rows];
};

struct button {
  uint16_t x;
  uint16_t y;
  uint16_t w;
  uint16_t h;
  bool isDisabled = false;
  drawButton draw;
  selectButton select;
  hoverButton hover;
  disableB disable;
};

struct buttonInfo {
  uint16_t cols = 1;
  uint16_t rows = 1;
  uint16_t* buttonPerRow = new uint16_t[rows];
  button** buttons = new button*[rows];
};

class buttonSet {
  public:
    // SETUP FUNCTIONS

    buttonSet(TFT_eSPI* tft, buttonLayout initialLayout, void (*drawBg)(TFT_eSPI*, uint16_t, uint16_t, uint16_t, uint16_t)) {
      // Set the inital layout variables.
      layout = initialLayout;
      // Store the tft library to draw to the screen.
      _tft = tft;
      // Store the function to display the background.
      background = drawBg;
      // Draw the background to the screen.
      drawBackground();
    }

    buttonSet(TFT_eSPI* tft, buttonLayout initialLayout, uint32_t backgroundColor) {
      // Set the inital layout variables.
      layout = initialLayout;
      // Store the tft library to draw to the screen.
      _tft = tft;
      // Store the background color.
      bgColor = backgroundColor;
      // Draw the background to the screen.
      drawBackground();
    }

    // STRUCTURE SETUP

    // setup the arrays so the user can input values.
    buttonSetup initButtons(buttonSetup buttonToSetup) {
      for (int n = 0; n < buttonToSetup.rows; n++) {
        buttonToSetup.drawFuncs[n] = new drawButton[buttonToSetup.buttonPerRow[n]];
        buttonToSetup.selectFuncs[n] = new selectButton[buttonToSetup.buttonPerRow[n]];
        buttonToSetup.hoverFuncs[n] = new hoverButton[buttonToSetup.buttonPerRow[n]];
        buttonToSetup.disableFuncs[n] = new disableB[buttonToSetup.buttonPerRow[n]];
        buttonToSetup.sizes[n] = new buttonSize[buttonToSetup.buttonPerRow[n]];
      }

      return buttonToSetup;
    }

    // Function to setups the buttonInfo array.
    buttonInfo initButtons(buttonInfo buttonToSetup) {
      for (int n = 0; n < buttonToSetup.rows; n++) {
        buttonToSetup.buttons[n] = new button[buttonToSetup.buttonPerRow[n]];
      }

      return buttonToSetup;
    }

    // BUTTON FUNCTIONS

    // Function to draw all of the buttons.
    void drawButtons() {
      for (int n = 0; n < buttons.rows; n++) {
        for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
          buttons.buttons[n][i].draw(_tft, buttons.buttons[n][i].x, buttons.buttons[n][i].y);
        }
      }
    }

    // Function to calculate all of the x and y values.
    void calcButtonsPos() {
      int16_t totalHeight = 0;
      int16_t largestButton;
      for (int n = 0; n < buttons.rows; n++) {
        largestButton = 0;
        for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
          if (buttons.buttons[n][i].h > largestButton) {
            largestButton = buttons.buttons[n][i].h;
          }
        }
        totalHeight += largestButton;
      }

      // Calculate the y-margin
      int16_t buttonYMargin = (layout.h-totalHeight)/(buttons.rows+1);
      if (buttonYMargin < 0) {
        buttonYMargin = 0;
      }

      // Solve all of the y values.
      int16_t prevSizes;
      for (int n = 0; n < buttons.rows; n++) {
        for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
          buttons.buttons[n][i].y = layout.y + buttonYMargin;
        }
        if (n != 0) {
          prevSizes = 0;
          for (int a = 0; a < n; a++) {
            largestButton = 0;
            for (int i = 0; i < buttons.buttonPerRow[a]; i++) {
              if (buttons.buttons[a][i].h > largestButton) {
                largestButton = buttons.buttons[a][i].h;
              }
            }
            prevSizes += largestButton + buttonYMargin;
          }

          for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
            buttons.buttons[n][i].y += prevSizes;
          }
        }
      }

      int16_t buttonXMargin;
      int16_t totalWidth;

      // Solve for all of the x values.
      for (int n = 0; n < buttons.rows; n++) {
        // Find the x-margin.
        totalWidth = 0;
        buttonXMargin = 0;

        for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
          totalWidth += buttons.buttons[n][i].w;
        }

        buttonXMargin = (layout.w-totalWidth)/(buttons.buttonPerRow[n]+1);
        if (buttonXMargin < 0) {
          buttonXMargin = 0;
        }

        // Solve the x values for the current row.
        for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
          buttons.buttons[n][i].x = layout.x+buttonXMargin;
          if (i != 0) {
            for (int a = 0; a < i; a++) {
              buttons.buttons[n][i].x += buttons.buttons[n][a].w+buttonXMargin;
            }
          }
        }
      }
    }

    // This function sets up the button info.
    void setup(buttonSetup initButtons) {
      // Copy over the basic information.
      buttons.rows = initButtons.rows;
      buttons.buttonPerRow = initButtons.buttonPerRow;

      // Fill the array of buttons.
      for (int n = 0; n < buttons.rows; n++) {
        buttons.buttons[n] = new button[buttons.buttonPerRow[n]];
        for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
          buttons.buttons[n][i].draw = initButtons.drawFuncs[n][i];
          buttons.buttons[n][i].select = initButtons.selectFuncs[n][i];
          buttons.buttons[n][i].hover = initButtons.hoverFuncs[n][i];
          buttons.buttons[n][i].disable = initButtons.disableFuncs[n][i];
          buttons.buttons[n][i].w = initButtons.sizes[n][i].w;
          buttons.buttons[n][i].h = initButtons.sizes[n][i].h;
        }
      }

      // Calculate the buttons' positions.
      calcButtonsPos();
      // Draw all of the buttons.
      drawButtons();
    }

    // BUTTON ADDITION FUNCTIONS

    // This function will add in a new button at the location given to it.
    void addButton(button newButton, uint16_t row, uint16_t col) {
      buttonInfo newButtonInfo;

      // Calculate the amount of rows.
      if ((row+1) > buttons.rows) {
        newButtonInfo.rows = row+1;
      } else {
        newButtonInfo.rows = buttons.rows;
      }

      // Calculate the number of buttons per row.
      for (int i = 0; i < newButtonInfo.rows; i++) {
        if (i < buttons.rows) {
          newButtonInfo.buttonPerRow[i] = buttons.buttonPerRow[i];
        } else {
          newButtonInfo.buttonPerRow[i] = 0;
        }
      }

      newButtonInfo.buttonPerRow[row]++;

      // Initiate the array.
      newButtonInfo = initButtons(newButtonInfo);

      // Fill in the new array of buttons.
      for (int n = 0; n < newButtonInfo.rows; n++) {
        if (n != row) {
          newButtonInfo.buttons[n] = buttons.buttons[n];
        } else {
          for (int i = 0; i < newButtonInfo.buttonPerRow[n]; i++) {
            if (i < col) {
              newButtonInfo.buttons[n][i] = buttons.buttons[n][i];
            } else if (i == col) {
              newButtonInfo.buttons[n][i] = newButton;
            } else {
              newButtonInfo.buttons[n][i] = buttons.buttons[n][i-1];
            }
          }
        }
      }

      // Set the button array to the new array.
      buttons = newButtonInfo;

      // Redraw the background.
      drawBackground();
      // Calculate the buttons' positions.
      calcButtonsPos();
      // Draw all of the buttons.
      drawButtons();
    }

    // Function to remove a button.
    void removeButton(uint16_t row, uint16_t col) {
      buttonInfo newButtonInfo;

      // Calculate the number of rows.
      if (buttons.buttonPerRow[row] == 1) {
        newButtonInfo.rows = buttons.rows - 1;
      } else {
        newButtonInfo.rows = buttons.rows;
      }

      // Calculate the number of buttons per row.
      int isZero = 0;
      for (int n = 0; n < newButtonInfo.rows; n++) {
        if (n == row) {
          if (buttons.buttonPerRow[n]-1 == 0) {
            isZero = 1;
          } else {
            newButtonInfo.buttonPerRow[n] = buttons.buttonPerRow[n] - 1;
          }
        } else {
          newButtonInfo.buttonPerRow[n - isZero] = buttons.buttonPerRow[n];
        }
      }

      // Setup the array to store the buttons.
      newButtonInfo = initButtons(newButtonInfo);

      // Fill in the new array.
      for (int n = 0; n < newButtonInfo.rows; n++) {
        if (isZero == 1) {
          if (n < row) {
            newButtonInfo.buttons[n] = buttons.buttons[n];
          } else if (n >= row) {
            newButtonInfo.buttons[n] = buttons.buttons[n+1];
          }
        } else {
          if (n == row) {
            for (int i = 0; i < newButtonInfo.buttonPerRow[n]; i++) {
              if (i < col) {
                newButtonInfo.buttons[n][i] = buttons.buttons[n][i];
              } else {
                newButtonInfo.buttons[n][i] = buttons.buttons[n][i+1];
              }
            }
          } else {
            newButtonInfo.buttons[n] = buttons.buttons[n];
          }
        }
      }

      buttons = newButtonInfo;

      drawBackground();
      // Calculate the buttons' positions.
      calcButtonsPos();
      // Draw all of the buttons.
      drawButtons();
    }

    // BUTTON STATE FUNCTIONS

    // Disable a button at the given spot.
    void disableButton(uint16_t row, uint16_t col) {
      if (buttons.buttons[row][col].isDisabled == false) {
        if (row < buttons.rows) {
          if (col < buttons.buttonPerRow[row]) {
            buttons.buttons[row][col].disable(_tft, buttons.buttons[row][col].x, buttons.buttons[row][col].y);
            buttons.buttons[row][col].isDisabled = true;
          }
        }
      }
    }

    // Enable a button at the given spot.
    void enableButton(uint16_t row, uint16_t col) {
      if (buttons.buttons[row][col].isDisabled == true) {
        if (row < buttons.rows) {
          if (col < buttons.buttonPerRow[row]) {
            buttons.buttons[row][col].draw(_tft, buttons.buttons[row][col].x, buttons.buttons[row][col].y);
            buttons.buttons[row][col].isDisabled = false;
          }
        }
      }
    }

    // Disable all buttons.
    void disableAll() {
      for (int n = 0; n < buttons.rows; n++) {
        for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
          buttons.buttons[n][i].disable(_tft, buttons.buttons[n][i].x, buttons.buttons[n][i].y);
          buttons.buttons[n][i].isDisabled = true;
        }
      }
    }

    // Enable all buttons.
    void enableAll() {
      for (int n = 0; n < buttons.rows; n++) {
        for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
          buttons.buttons[n][i].draw(_tft, buttons.buttons[n][i].x, buttons.buttons[n][i].y);
          buttons.buttons[n][i].isDisabled = false;
        }
      }
    }

  private:
    // Variable to store the display library.
    TFT_eSPI *_tft = nullptr;

    // Structure that holds the button layout.
    buttonLayout layout;
    // Structure that holds the buttons.
    buttonInfo buttons;

    // Function to draw the background.
    void (*background)(TFT_eSPI*, uint16_t, uint16_t, uint16_t, uint16_t) = nullptr;
    // Variable to store the background color.
    uint32_t bgColor;

    // SETUP FUNCTIONS

    // BACKGROUND FUNCTIONS

    // Draw the background color to the screen.
    void bgColorDraw() {
      _tft->fillRect(layout.x, layout.y, layout.w, layout.h, bgColor);
    }

    // Function to draw the background to the screen. It figures out if it needs to draw a user definited bacground or a color.
    void drawBackground() {
      if (background != nullptr) {
        background(_tft, layout.x, layout.y, layout.w, layout.h);
      } else {
        bgColorDraw();
      }
    }
};
