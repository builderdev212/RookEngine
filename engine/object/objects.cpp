#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "collisionDetection.h"

// CHARACTER CREATION FUNCTION(S)

void item::createItem(uint32_t bgColor, uint16_t itemW, uint16_t itemH, uint8_t itemShape) {
  // Item size.
  wVal = itemW;
  hVal = itemH;
  // Item shape.
  shape = itemShape;
  // Background color.
  backgroundColor = bgColor;
}

void item::spawnItem(TFT_eSprite &itemSprite, int16_t itemX, int16_t itemY, void (*drawItemShape)(TFT_eSprite&)) {
  // Item location.
  xVal = itemX;
  yVal = itemY;

  // Create the item sprite.
  itemSprite.createSprite(wVal, hVal);
  // Fill the background of the sprite.
  itemSprite.fillSprite(backgroundColor);
  // Draw the item to the sprite.
  drawItemShape(itemSprite);
  // Push the sprite to the screen at the given location.
  itemSprite.pushSprite(xVal, yVal);
}

// CHARACTER DESTRUCTION FUNCTION(S)

void item::destroyItem(TFT_eSprite &itemSprite) {
  // Clear the sprite.
  itemSprite.fillSprite(backgroundColor);
  // Push the cleared sprite to the screen.
  itemSprite.pushSprite(xVal, yVal);
  // Delete the sprite to save ram.
  itemSprite.deleteSprite();
}

// CHARACTER FUNCTION(S)

void item::changeItemImage(TFT_eSprite &itemSprite, void (*drawItem)(TFT_eSprite&), uint32_t backgroundColor) {
  // Fill the background of the sprite with the background color.
  itemSprite.fillSprite(backgroundColor);
  // Call the custom function that is used to draw a player to the screen.
  drawItem(itemSprite);
  // Update the image.
  itemSprite.pushSprite(xVal, yVal);
}

void item::changeItemShape(int8_t newShape) {
  // Set the players shape to the new shape type.
  shape = newShape;
}
