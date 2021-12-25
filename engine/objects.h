#ifndef player_h
#define player_h

class item {
  public:
    // Item position.
    int16_t xVal;
    int16_t yVal;
    // Item size.
    uint16_t wVal;
    uint16_t hVal;
    // Item shape.
    uint8_t shape;

    // CREATION OF THE ITEM

    /*
      Initialization of the item. This gives variables that only need to be declared once their values.

      Arguments are as follow: Background color, item width, item height, and item shape.
    */
    void createItem(uint32_t bgColor, uint16_t itemW, uint16_t itemH, uint8_t itemShape);

    /*
      Spawns the item at the given location.

      Arguments are as follow: Item sprite, x value, y value, function that contains the code to draw the item to the sprite.
    */
    void spawnItem(TFT_eSprite &itemSprite, int16_t itemX, int16_t itemY, void (*drawItemShape)(TFT_eSprite&));

    // DESTRUCTION OF THE ITEM

    /*
      Destroys the item that is spawned.

      Arguments are as follow: Item sprite.
    */
    void destroyItem(TFT_eSprite &itemSprite);

    // CHANGE THE ITEM

    /*
      This function is used to update the item's image with a new one.

      Arguments are as follow: Item sprite, draw function, and background color.
    */
    void changeItemImage(TFT_eSprite &playerItem, void (*drawItem)(TFT_eSprite&), uint32_t backgroundColor);

    /*
      This function is used to change the value of the item's shape. This is VERY important for hitboxes.

      Arguments are as follow: new shape

      Shapes: 0 - point, 1 - rectangle, 2 - circle, 3 - ellipse.
    */
    void changeItemShape(int8_t newShape);

  private:
    // Background color.
    uint32_t backgroundColor;
};

#endif
