#ifndef objectCollision_h
#define objectCollision_h

const uint8_t OBJECT_RECTANGLE = 0;
const uint8_t OBJECT_CIRCLE = 1;
const uint8_t OBJECT_ELLIPSE = 2;

struct rect {
  uint32_t x = 0;
  uint32_t y = 0;
  uint32_t w = 0;
  uint32_t h = 0;
};

struct circle {
  uint32_t x = 0;
  uint32_t y = 0;
  uint32_t r = 0;
};

struct ellipse {
  uint32_t x = 0;
  uint32_t y = 0;
  uint32_t rx = 0;
  uint32_t ry = 0;
};

class objectCollision {
  public:
    // Variable to store the object's shape.
    uint8_t shape; // 0 - rectangle, 1 - circle, 2 - ellipse.
    // Variables to store the object's size.
    int h0;
    int w0;
    int r0;
    int rx0;
    int ry0;
    // Variables to store the object's location.
    int x0;
    int y0;

    // Object initalizer.
    objectCollision(rect objshape); // line/rectange/square.
    objectCollision(circle objshape); // circle.
    objectCollision(ellipse objshape); // ellipse.

    // Check for collision with another object.
    bool isCollision(objectCollision otherObject);
    // Check for collision with the respective shapes.
    bool isCollision(rect objShape);
    bool isCollision(circle objShape);
    bool isCollision(ellipse objShape);

  private:
    // Check for collision between a line and the shape of the initalized object.
    bool collision(int x, int y, int w);

    // Functions to check collison betweent the different types of shapes.
    bool rectLineCollision(int x, int y, int w);
    bool circleLineCollision(int x, int y, int w);
    bool ellipseLineCollision(int x, int y, int w);

};

#endif
