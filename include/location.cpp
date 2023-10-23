#include <Arduino.h>
#include "location.h"

// Calculate the width and height of shapes in rectangle form.
rectangle calcSize(rectangle shape) {
    return shape;
}

circle calcSize(circle shape) {
    // Solve for the width/height.
    shape.w = shape.rw * 2;
    shape.h = shape.rh * 2;

    return shape;
}

triangle calcSize(triangle shape) {
    // Solve the top left corner.
    int topLeftX = min(shape.x1, min(shape.x2, shape.x3));
    int topLeftY = min(shape.y1, min(shape.y2, shape.y3));

    // Solve for the width/height.
    shape.w = max(shape.x1, max(shape.x2, shape.x3)) - topLeftX;
    shape.h = max(shape.y1, max(shape.y2, shape.y3)) - topLeftY;

    return shape;
}