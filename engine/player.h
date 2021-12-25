#ifndef player_h
#define player_h

class player {
  public:
    // Player position.
    int16_t xVal;
    int16_t yVal;
    // Player shape.
    int8_t shape;
    // Player speed.
    int8_t speed;

    // PLAYER SPAWN FUNCTION(S)

    /*
      Initialization function. This sets up the variables needed for the player. These variables can be chnaged later.

      Arguments are as follows: Player width, player height, player shape, max speed, border x, border y, border width,
      border height, and initial speed.
      Player shape: 0 - point, 1 - rectangle, 2 - circle, 3 - ellipse.
      Max Speed: Must be a positive integer. Speed determines how many pixels the player moves at a time.
      Border x and y: The coordinates of the top left corner of the play area.
      Initial speed: the speed at which the player will initially go. The default value is one.
    */
    void createPlayer(uint16_t playerW, uint16_t playerH, uint8_t playerShape, int8_t highSpeed, int16_t borderX, int16_t borderY, uint16_t borderW, uint16_t borderH, int8_t initialSpeed);

    /*
      This function is used to spawn the player. This creates the player and its shadow and then spawns them
      on the screen at the given location. The shadow is used to destroy the trail that the player would leave behind.

      Arguments are as follow: Player sprite, shadow sprite, player x, player y, draw player function, background color.
      drawPlayer function: This is a void function with one argument. This function should contain the code to draw the
      player to the player's sprite.
    */
    void spawnPlayer(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite, int16_t playerX, int16_t playerY, void (*drawPlayer)(TFT_eSprite&), uint32_t backgroundColor);

    // PLAYER DESTRUCTION FUNCTION(S)

    /*
      Despawn function. This is used when you are finished using the player. It destroys the player's
      sprites to save ram and resets the background to the background color.

      Arguments are as follow: Player sprite, shadow sprite.
    */
    void despawnPlayer(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite);

    /*
      Destruction function. This is used when you are finished using the player. It not only removes it
      from the screen, but it resets the player's variables.

      Arguments are as follow: Player sprite, shadow sprite.
    */
    void destroyPlayer(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite);

    // CHARACTER FUNCTION(S)

    /*
      This function is used to update the player's image with a new one.

      Arguments are as follow: Player sprite, draw function, and background color.
    */
    void changePlayerImage(TFT_eSprite &playerSprite, void (*drawPlayer)(TFT_eSprite&), uint32_t backgroundColor);

    /*
      This function is used to change the value of the players shape. This is VERY important for hitboxes.

      Arguments are as follow: new shape

      Player shape: 0 - point, 1 - rectangle, 2 - circle, 3 - ellipse.
    */
    void changePlayerShape(int8_t newShape);

    // PLAYER MOVEMENT FUNCTION(S)

    /*
      Player movement function. Sets the x and y value and pushes the player to that location.

      Arguments are as follow: Player sprite, shadow sprite, x value, and y value.
    */
    void setPlayerPos(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite, int16_t x, int16_t y);

    /*
      Update the player position. Used for controls, x and y change should be either 0, 1, or -1. Speed determines how much to multiply the change by.

      Arguments are as follow: Player sprite, shadow sprite, speed, x change, and y change.
    */
    void updatePlayerPos(TFT_eSprite &playerSprite, TFT_eSprite &shadowSprite, int8_t xChange, int8_t yChange);

    // PLAYER DIRECTION LOCK FUNCTION(S)

    /*
      Disallows a player to go in a certain direction or set of directions.

      Arguments are as follow: Direction, state.
      Direction: 0 - all, 1 - x axis, 2 - y axis, 3 - left, 4 - right, 5 - up, 6 - down
      State: Either true or false, true to lock a direction and false to unlock that direction.
    */
    void directionLock(uint8_t direction, bool state);

    // PLAYER SPEED FUNCTION(S)

    /*
      Set the player's speed. Keep in mind that this speed should be within the specified
      minimum and maximum speed, otherwise it will be set to the appropriate value.

      Arguments are as follow: new speed.
    */
    void setPlayerSpeed(int8_t newSpeed);

    /*
      Increase the speed of the player by 1.
    */
    void increasePlayerSpeed();

    /*
      Decrease the speed of the player by 1.
    */
    void decreasePlayerSpeed();

    /*
      Inverse the controls of the player.
    */
    void inversePlayerControls();

    // BORDER FUNCTION(S)

    /*
      Changes the border that the player must stay in.

      Arguments are as follow: x min, y min, border width, and border height.
    */
    void updatePlayerBoundaries(int16_t borderX, int16_t borderY, uint16_t borderW, uint16_t borderH);

    // PLAYER COLLISION FUNCTION(S)

    /*
      Checks to see if the player is colliding with another object.

      Arguments are as follow: x, y, w, h, shape.
      ALL of the arguments refer to the OTHER object that you are checking to see if it's colliding with
      the player.
      shape:  0 - point, 1 - rectangle, 2 - circle, 3 - ellipse.
    */
    bool playerCollision(int16_t x0, int16_t y0, uint16_t w0, uint16_t h0, uint8_t shape0);

    // VARIABLE RETURN FUNCTION(S)

    /*
      Return the player's speed.
    */
    int8_t returnPlayerSpeed();

    /*
      Return the player's speed.
    */
    int16_t returnPlayerWidth();

    /*
      Return the player's speed.
    */
    int16_t returnPlayerHeight();

  private:
    // Player size.
    int16_t wVal;
    int16_t hVal;

    // Speed.
    int8_t baseSpeed;
    int8_t minSpeed;
    int8_t maxSpeed;

    // Border values.
    int16_t xBorder;
    int16_t yBorder;
    uint16_t wBorder;
    uint16_t hBorder;

    // Position Lock.
    bool leftLocked = false;
    bool rightLocked = false;
    bool upLocked = false;
    bool downLocked = false;

    // BORDER FUNCTION(S)

    /*
      Make sure that the player stays within the defined border.
      There are no arguments for this function, it simply changes xVal and yVal if they are not within the specified border.
    */
    void inBorderRange();

    // PLAYER SPEED FUNCTION(S)

    /*
      Make sure that the player is staying within the specified range of speeds.
    */
    void isSpeedRange();
};

#endif
