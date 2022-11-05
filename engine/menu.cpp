#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "menu.h"

// SETUP FUNCTIONS

buttonSet::buttonSet(TFT_eSPI* tft, buttonLayout initialLayout, void (*drawBg)(TFT_eSPI*, uint16_t, uint16_t, uint16_t, uint16_t)) {
  // Set the inital layout variables.
  layout = initialLayout;
  // Store the tft library to draw to the screen.
  _tft = tft;
  // Store the function to display the background.
  background = drawBg;
  // Draw the background to the screen.
  drawBackground();
}

buttonSet::buttonSet(TFT_eSPI* tft, buttonLayout initialLayout, int backgroundColor) {
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

// Function to setups the buttonsInfo array.
buttonsInfo buttonSet::initButtons(buttonsInfo buttonToSetup) {
  for (int n = 0; n < buttonToSetup.rows; n++) {
    buttonToSetup.buttons[n] = new button[buttonToSetup.buttonPerRow[n]];
  }

  return buttonToSetup;
}

// BUTTON FUNCTIONS

// Function to draw all of the buttons.
void buttonSet::drawButtons() {
  for (int n = 0; n < buttons.rows; n++) {
    for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
      if (buttons.buttons[n][i].isDisabled) {
        buttons.buttons[n][i].disable(_tft, buttons.buttons[n][i].x, buttons.buttons[n][i].y);
      } else {
        buttons.buttons[n][i].draw(_tft, buttons.buttons[n][i].x, buttons.buttons[n][i].y);
      }
    }
  }
}

// Function to calculate all of the x and y values.
void buttonSet::calcButtonsPos() {
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
  int16_t buttonYMargin = (layout.h - totalHeight) / (buttons.rows + 1);
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

    buttonXMargin = (layout.w - totalWidth) / (buttons.buttonPerRow[n] + 1);
    if (buttonXMargin < 0) {
      buttonXMargin = 0;
    }

    // Solve the x values for the current row.
    for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
      buttons.buttons[n][i].x = layout.x + buttonXMargin;
      if (i != 0) {
        for (int a = 0; a < i; a++) {
          buttons.buttons[n][i].x += buttons.buttons[n][a].w + buttonXMargin;
        }
      }
    }
  }
}

// This function sets up the button info.
void buttonSet::setup(buttonsInfo initalButtons) {
  buttons = initalButtons;

  // Calculate the buttons' positions.
  calcButtonsPos();
  // Draw all of the buttons.
  drawButtons();
}

// BUTTON ADDITION FUNCTIONS

// This function will add in a new button at the location given to it.
void buttonSet::addButton(button newButton, uint16_t row, uint16_t col) {
  buttonsInfo newbuttonsInfo;

  // Calculate the amount of rows.
  if ((row + 1) > buttons.rows) {
    newbuttonsInfo.rows = row + 1;
  } else {
    newbuttonsInfo.rows = buttons.rows;
  }

  newbuttonsInfo.buttonPerRow = new uint16_t[newbuttonsInfo.rows];
  newbuttonsInfo.buttons = new button*[newbuttonsInfo.rows];

  // Calculate the number of buttons per row.
  for (int i = 0; i < newbuttonsInfo.rows; i++) {
    if (i < buttons.rows) {
      newbuttonsInfo.buttonPerRow[i] = buttons.buttonPerRow[i];
    } else {
      newbuttonsInfo.buttonPerRow[i] = 0;
    }
  }

  newbuttonsInfo.buttonPerRow[row]++;

  // Initiate the array.
  newbuttonsInfo = initButtons(newbuttonsInfo);

  // Fill in the new array of buttons.
  for (int n = 0; n < newbuttonsInfo.rows; n++) {
    if (n != row) {
      newbuttonsInfo.buttons[n] = buttons.buttons[n];
    } else {
      for (int i = 0; i < newbuttonsInfo.buttonPerRow[n]; i++) {
        if (i < col) {
          newbuttonsInfo.buttons[n][i] = buttons.buttons[n][i];
        } else if (i == col) {
          newbuttonsInfo.buttons[n][i] = newButton;
        } else {
          newbuttonsInfo.buttons[n][i] = buttons.buttons[n][i - 1];
        }
      }
    }
  }

  // Set the button array to the new array.
  buttons = newbuttonsInfo;

  // Redraw the background.
  drawBackground();
  // Calculate the buttons' positions.
  calcButtonsPos();
  // Draw all of the buttons.
  drawButtons();
}

// Function to remove a button.
void buttonSet::removeButton(uint16_t row, uint16_t col) {
  // Make sure the row is within boundries. If not, do nothing.
  if (row > buttons.rows) return;
  // Make sure the column is within boundries. If not, do nothing.
  if (col > buttons.buttonPerRow[row]) return;

  buttonsInfo newbuttonsInfo;

  // Calculate the number of rows.
  if (buttons.buttonPerRow[row] == 1) {
    newbuttonsInfo.rows = buttons.rows - 1;
  } else {
    newbuttonsInfo.rows = buttons.rows;
  }

  newbuttonsInfo.buttonPerRow = new uint16_t[newbuttonsInfo.rows];
  newbuttonsInfo.buttons = new button*[newbuttonsInfo.rows];

  // Calculate the number of buttons per row.
  int isZero = 0;
  for (int n = 0; n < newbuttonsInfo.rows; n++) {
    if (n == row) {
      if (buttons.buttonPerRow[n] - 1 == 0) {
        isZero = 1;
      } else {
        newbuttonsInfo.buttonPerRow[n] = buttons.buttonPerRow[n] - 1;
      }
    } else {
      newbuttonsInfo.buttonPerRow[n - isZero] = buttons.buttonPerRow[n];
    }
  }

  // Setup the array to store the buttons.
  newbuttonsInfo = initButtons(newbuttonsInfo);

  // Fill in the new array.
  for (int n = 0; n < newbuttonsInfo.rows; n++) {
    if (isZero == 1) {
      if (n < row) {
        newbuttonsInfo.buttons[n] = buttons.buttons[n];
      } else if (n >= row) {
        newbuttonsInfo.buttons[n] = buttons.buttons[n + 1];
      }
    } else {
      if (n == row) {
        for (int i = 0; i < newbuttonsInfo.buttonPerRow[n]; i++) {
          if (i < col) {
            newbuttonsInfo.buttons[n][i] = buttons.buttons[n][i];
          } else {
            newbuttonsInfo.buttons[n][i] = buttons.buttons[n][i + 1];
          }
        }
      } else {
        newbuttonsInfo.buttons[n] = buttons.buttons[n];
      }
    }
  }

  buttons = newbuttonsInfo;

  drawBackground();
  // Calculate the buttons' positions.
  calcButtonsPos();
  // Draw all of the buttons.
  drawButtons();
}

// BUTTON STATE FUNCTIONS

// Disable a button at the given spot.
void buttonSet::disableButton(uint16_t row, uint16_t col) {
  // Make sure the row is within boundries. If not, do nothing.
  if (row > buttons.rows) return;
  // Make sure the column is within boundries. If not, do nothing.
  if (col > buttons.buttonPerRow[row]) return;

  // Disable the button as long as it isn't already disabled.
  if (buttons.buttons[row][col].isDisabled == false) {
    buttons.buttons[row][col].disable(_tft, buttons.buttons[row][col].x, buttons.buttons[row][col].y);
    buttons.buttons[row][col].isDisabled = true;
  }
}

// Enable a button at the given spot.
void buttonSet::enableButton(uint16_t row, uint16_t col) {
  // Make sure the row is within boundries. If not, do nothing.
  if (row > buttons.rows) return;
  // Make sure the column is within boundries. If not, do nothing.
  if (col > buttons.buttonPerRow[row]) return;

  // Enable the button as long as it isn't already enabled.
  if (buttons.buttons[row][col].isDisabled == true) {
    buttons.buttons[row][col].draw(_tft, buttons.buttons[row][col].x, buttons.buttons[row][col].y);
    buttons.buttons[row][col].isDisabled = false;
  }
}

// Disable an entire row.
void buttonSet::disableRow(uint16_t row) {
  // Make sure the row is within boundries. If not, do nothing.
  if (row > buttons.rows) return;

  // Disable the row as long as it isn't already disabled.
  for (int col = 0; col < buttons.buttonPerRow[row]; col++) {
    if (buttons.buttons[row][col].isDisabled == false) {
      buttons.buttons[row][col].disable(_tft, buttons.buttons[row][col].x, buttons.buttons[row][col].y);
      buttons.buttons[row][col].isDisabled = true;
    }
  }
}

// Enable an entire row.
void buttonSet::enableRow(uint16_t row) {
  // Make sure the row is within boundries. If not, do nothing.
  if (row > buttons.rows) return;

  // Enable the row as long as it isn't already enabled.
  for (int col = 0; col < buttons.buttonPerRow[row]; col++) {
    if (buttons.buttons[row][col].isDisabled == true) {
      buttons.buttons[row][col].draw(_tft, buttons.buttons[row][col].x, buttons.buttons[row][col].y);
      buttons.buttons[row][col].isDisabled = false;
    }
  }
}

// Disable all buttons.
void buttonSet::disableAll() {
  // Disable all of the buttons as long as they're not already disabled.
  for (int n = 0; n < buttons.rows; n++) {
    for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
      if (buttons.buttons[n][i].isDisabled == false) {
        buttons.buttons[n][i].disable(_tft, buttons.buttons[n][i].x, buttons.buttons[n][i].y);
        buttons.buttons[n][i].isDisabled = true;
      }
    }
  }
}

// Enable all buttons.
void buttonSet::enableAll() {
  // Enable all of the buttons as long as they're not already enabled.
  for (int n = 0; n < buttons.rows; n++) {
    for (int i = 0; i < buttons.buttonPerRow[n]; i++) {
      if (buttons.buttons[n][i].isDisabled == true) {
        buttons.buttons[n][i].draw(_tft, buttons.buttons[n][i].x, buttons.buttons[n][i].y);
        buttons.buttons[n][i].isDisabled = false;
      }
    }
  }
}

// Function to draw the background to the screen. It figures out if it needs to draw a user definited bacground or a color.
void buttonSet::drawBackground() {
  if (background != nullptr) {
    background(_tft, layout.x, layout.y, layout.w, layout.h);
  } else {
    _tft->fillRect(layout.x, layout.y, layout.w, layout.h, bgColor);
  }
}
