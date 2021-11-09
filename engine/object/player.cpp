#include <TFT_eSPI.h>
#include <SPI.h>
#include "collisionDetection.h"
#include "player.h"

void player::createPlayer(uint16_t playerW, uint16_t playerH, uint8_t playerShape, int8_t highSpeed, int16_t borderX, int16_t borderY, uint16_t borderW, uint16_t borderH, int8_t initialSpeed) {
  // Set the borders that the player must stay in.
  xBorder = borderX;
  yBorder = borderY;
  // Subtract the player's width and height to account for the fact that the player's x and y values are the upper left corner.
  wBorder = borderW - playerW;
  hBorder = borderH - playerH;

  // Player size.
  wVal = playerW;
  hVal = playerH;
  // Player shape.
  shape = playerShape;

  // Player speed.
  baseSpeed = initialSpeed;
  speed = baseSpeed;
  // Player speed boundaries.
  maxSpeed = highSpeed;
  // The minimum speed is determined buy multiplying the max speed by -1.
  minSpeed = maxSpeed * -1;
}

void player::spawnPlayer(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite, int16_t playerX, int16_t playerY, void (*drawPlayer)(TFT_eSprite&), uint32_t backgroundColor) {
  // Set the position of the player.
  xVal = playerX;
  yVal = playerY;

  // Create the shadow sprite.
  shadowSprite.createSprite(wVal, hVal);
  // Fill the shadow with the color of the background.
  shadowSprite.fillSprite(backgroundColor);
  // Push the sprite onto the screen at the given x and y value.
  shadowSprite.pushSprite(xVal, yVal);

  // Create the player sprite.
  playerSprite.createSprite(wVal, hVal);
  // Fill the background of the sprite with the background color.
  playerSprite.fillSprite(backgroundColor);
  // Call the custom function that is used to draw a player to the screen.
  drawPlayer(playerSprite);
  // Push the player sprite onto the screen.
  playerSprite.pushSprite(xVal, yVal);
}

// PLAYER DESTRUCTION FUNCTION(S)

void player::despawnPlayer(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite) {
  // Delete the sprites to save ram when you are done using the player.
  playerSprite.deleteSprite();
  shadowSprite.pushSprite(xVal, yVal);
  shadowSprite.deleteSprite();
}

void player::destroyPlayer(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite) {
  // Delete the player's sprites and set the background to the background color.
  despawnPlayer(playerSprite, shadowSprite);

  // Reset the player's values.
  // Reset the speed to the base speed.
  speed = baseSpeed;
  // Unlock the player's movement.
  leftLocked = false;
  rightLocked = false;
  upLocked = false;
  downLocked = false;
}

// CHARACTER FUNCTION(S)

void player::changePlayerImage(TFT_eSprite &playerSprite, void (*drawPlayer)(TFT_eSprite&), uint32_t backgroundColor) {
  // Fill the background of the sprite with the background color.
  playerSprite.fillSprite(backgroundColor);
  // Call the custom function that is used to draw a player to the screen.
  drawPlayer(playerSprite);
  // Update the image.
  playerSprite.pushSprite(xVal, yVal);
}

void player::changePlayerShape(int8_t newShape) {
  // Set the players shape to the new shape type.
  shape = newShape;
}

// PLAYER MOVEMENT FUNCTION(S)

void player::setPlayerPos(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite, int16_t x, int16_t y) {
  // Push the sprite to the previous location of the player.
  shadowSprite.pushSprite(xVal, yVal);

  // Set the x and y value for the player.
  xVal = x;
  yVal = y;

  // Make sure that the player stays within the predefined borders.
  inBorderRange();

  // Push the player to that location.
  playerSprite.pushSprite(xVal, yVal);
}

void player::updatePlayerPos(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite, int8_t xChange, int8_t yChange) {
  // If xChange is not 0 and/or yChange is not 0.
  if (((xChange != 0) || (yChange != 0)) || (((xChange != 0) == true) && ((yChange != 0) == true))) {
    // Push the sprite to the previous location of the player.
    shadowSprite.pushSprite(xVal, yVal);
    // Update the x and y value.

    // Only change the x value if the left is not locked and moving left or the right is not locked and moving right.
    if (((leftLocked != true) && (xChange == -1)) || ((rightLocked != true) && (xChange == 1))) {
      xVal = xVal + (xChange * speed);
    }
    // Only change the y value if up is not locked and moving up or down is not locked and moving down.
    if (((upLocked != true) && (yChange == -1)) || ((downLocked != true) && (yChange == 1))) {
      yVal = yVal + (yChange * speed);
    }

    // Make sure that the player stays within the predefined borders.
    inBorderRange();

    // Push the player to that location.
    playerSprite.pushSprite(xVal, yVal);
  }
}

// PLAYER DIRECTION LOCK FUNCTION(S)

void player::directionLock(uint8_t direction, bool state) {
  // Determine what directions to set.
  switch (direction) {
    case 0:
      // all
      leftLocked = state;
      rightLocked = state;
      upLocked = state;
      downLocked = state;
      break;
    case 1:
      // x axis
      leftLocked = state;
      rightLocked = state;
      break;
    case 2:
      // y axis
      upLocked = state;
      downLocked = state;
      break;
    case 3:
      // left
      leftLocked = state;
      break;
    case 4:
      // right
      rightLocked = state;
      break;
    case 5:
      // up
      upLocked = state;
      break;
    case 6:
      // down
      downLocked = state;
      break;
    default:
      break;
  }
}

// PLAYER SPEED FUNCTION(S)

void player::setPlayerSpeed(int8_t newSpeed) {
  // Set the speed.
  speed = newSpeed;
  // Make sure the speed is within the specified range.
  isSpeedRange();
}

void player::increasePlayerSpeed() {
  // Increase the speed.
  if (speed < 0) {
    // If inverse Subtract
    speed--;
  } else {
    // Else, add.
    speed++;
  }
  // Make sure the speed is within the specified range.
  isSpeedRange();
}

void player::decreasePlayerSpeed() {
  // Decrease the speed.
  if (speed < 0) {
    // If inverse add
    speed++;
  } else {
    // Else, subtract.
    speed--;
  }
  // Make sure the speed is within the specified range.
  isSpeedRange();
}

void player::inversePlayerControls() {
  // Multiply the speed by -1 to get inverse controls.
  speed *= -1;
  // Make sure the speed is within the specified range.
  isSpeedRange();
}

void player::isSpeedRange() {
  // Make sure the speed is not greater or less than the minimum and maximum.
  if (speed < minSpeed) {
    speed = minSpeed;
  } else if (speed > maxSpeed) {
    speed = maxSpeed;
  }
}

// BORDER FUNCTION(S)

void player::updatePlayerBoundaries(int16_t borderX, int16_t borderY, uint16_t borderW, uint16_t borderH) {
  // Borders that the player must stay in.
  xBorder = borderX;
  yBorder = borderY;
  wBorder = borderW - wVal;
  hBorder = borderH - hVal;

  // Makes sure the player is within the new border.
  inBorderRange();
}

void player::inBorderRange() {
  // Check the x value.
  if (xVal < xBorder) {
    xVal = xBorder;
  } else if (xVal > xBorder + wBorder) {
    xVal = xBorder + wBorder;
  }
  // Check the y value.
  if (yVal < yBorder) {
    yVal = yBorder;
  } else if (yVal > yBorder + hBorder) {
    yVal = yBorder + hBorder;
  }
}

// PLAYER COLLISION FUNCTION(S)

bool player::playerCollision(int16_t x0, int16_t y0, uint16_t w0, uint16_t h0, uint8_t shape0) {
  // Return either true or false. True if the two shapes are colloiding, false if they are not.
  return collision(xVal, yVal, wVal, hVal, shape, x0, y0, w0, h0, shape0);
}

// VARIABLE RETURN FUNCTION(S)

int8_t player::returnPlayerSpeed() {
  return speed;
}

int16_t player::returnPlayerWidth() {
  return wVal;
}

int16_t player::returnPlayerHeight() {
  return hVal;
}
