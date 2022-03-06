#include <Arduino.h>
#include "objectCollision.h"

objectCollision::objectCollision(rect objShape) {
  // Position
  x0 = objShape.x;
  y0 = objShape.y;
  // Width and height.
  w0 = objShape.h;
  h0 = objShape.w;
  // Shape type.
  shape = OBJECT_RECTANGLE;
}

objectCollision::objectCollision(circle objShape) {
  // Center Point.
  x0 = objShape.x;
  y0 = objShape.y;
  // Radius.
  r0 = objShape.r;
  // Shape type.
  shape = OBJECT_CIRCLE;
}

objectCollision::objectCollision(ellipse objShape) {
  // Center Point.
  x0 = objShape.x;
  y0 = objShape.y;
  // Radius for the width.
  rx0 = objShape.rx;
  // Radius for the height.
  ry0 = objShape.ry;
  // Shape type.
  shape = OBJECT_ELLIPSE;
}

bool objectCollision::isCollision(objectCollision otherObject) {
  rect rectShape;
  circle circleShape;
  ellipse ellipseShape;
  
  switch (otherObject.shape) {
    case OBJECT_RECTANGLE:
      rectShape.x = otherObject.x0;
      rectShape.y = otherObject.y0;
      rectShape.w = otherObject.w0;
      rectShape.h = otherObject.h0;
      return isCollision(rectShape);

    case OBJECT_CIRCLE:
      circleShape.x = otherObject.x0;
      circleShape.y = otherObject.y0;
      circleShape.r = otherObject.r0;
      return isCollision(circleShape);
      
    case OBJECT_ELLIPSE:
      ellipseShape.x = otherObject.x0;
      ellipseShape.y = otherObject.y0;
      ellipseShape.rx = otherObject.rx0;
      ellipseShape.ry = otherObject.ry0;
      return isCollision(ellipseShape);

    default:
      return false;
  }
}

bool objectCollision::isCollision(rect objShape) {
  for (int i = objShape.y; i < (objShape.y + objShape.h); i++) {
    if (collision(objShape.x, i, objShape.w) == true) {
      return true;
    }
  }

  return false;
}

bool objectCollision::isCollision(circle objShape) {
  // This formula is taken from the TFT_eSPI library,
  // though of course has been modified to detect overlap.
  int32_t  xC  = 0;
  int32_t  dxC = 1;
  int32_t  dyC = objShape.r + objShape.r;
  int32_t  pC  = -(objShape.r >> 1);

  if (collision(objShape.x, objShape.y, dyC + 1) == true) {
    return true;
  }

  while (xC < objShape.r) {
    if (pC >= 0) {
      // If the y values match the y value of the line,
      if ((collision(objShape.x - xC, objShape.y + objShape.r, dxC) == true) || (collision(objShape.x - xC, objShape.y - objShape.r, dxC) == true)) {
        return true;
      }

      dyC -= 2;
      pC -= dyC;
      objShape.r--;
    }

    dxC += 2;
    pC += dxC;
    xC++;

    if ((collision(objShape.x - objShape.r, objShape.y + xC, dyC + 1) == true) || (collision(objShape.x - objShape.r, objShape.y - xC, dyC + 1) == true)) {
      return true;
    }
  }

  return false;
}

bool objectCollision::isCollision(ellipse objShape) {
  // This formula is taken from the TFT_eSPI library,
  // though of course has been modified to detect overlap.
  if (objShape.rx < 2) return false;
  if (objShape.ry < 2) return false;

  int32_t xE, yE;
  int32_t rx2 = objShape.rx * objShape.rx;
  int32_t ry2 = objShape.ry * objShape.ry;
  int32_t fx2 = 4 * rx2;
  int32_t fy2 = 4 * ry2;
  int32_t s;

  for (xE = 0, yE = objShape.ry, s = 2 * ry2 + rx2 * (1 - 2 * objShape.ry); ry2 * xE <= rx2 * yE; xE++) {
    if ((collision((objShape.x - xE), (objShape.y - yE), (xE + xE + 1)) == true) || (collision((objShape.x - xE), (objShape.y + yE), (xE + xE + 1)) == true)) {
      return true;
    }

    if (s >= 0) {
      s += fx2 * (1 - yE);
      yE--;
    }
    s += ry2 * ((4 * xE) + 6);
  }

  for (xE = objShape.rx, yE = 0, s = 2 * rx2 + ry2 * (1 - 2 * objShape.rx); rx2 * yE <= ry2 * xE; yE++) {
    if ((collision((objShape.x - xE), (objShape.y - yE), (xE + xE + 1)) == true) || (collision((objShape.x - xE), (objShape.y + yE), (xE + xE + 1)) == true)) {
      return true;
    }

    if (s >= 0) {
      s += fy2 * (1 - xE);
      xE--;
    }
    s += rx2 * ((4 * yE) + 6);
  }

  return false;
}

bool objectCollision::collision(int x, int y, int w) {
  switch (shape) {
    case OBJECT_RECTANGLE:
      return rectLineCollision(x, y, w);

    case OBJECT_CIRCLE:
      return circleLineCollision(x, y, w);

    case OBJECT_ELLIPSE:
      return ellipseLineCollision(x, y, w);

    default:
      return false;
  }
}

bool objectCollision::rectLineCollision(int x, int y, int w) {
  // If the width is below zero,
  if (w < 0) {
    return false;
  }

  // If the y values match the y value of the line,
  if ((y >= y0) && (y <= (y0 + h0))) {
    // If the x values share an overlapping point,
    if ((w + w0 + 1) > (max(x + w, x0 + w0) - min(x, x0))) {
      return true;
    }
  }

  // If the lines didn't share a common point.
  return false;
}

bool objectCollision::circleLineCollision(int x, int y, int w) {
  // This formula is taken from the TFT_eSPI library,
  // though of course has been modified to detect overlap.
  int32_t  r   = r0;
  int32_t  xC  = 0;
  int32_t  dxC = 1;
  int32_t  dyC = r + r;
  int32_t  pC  = -(r >> 1);

  // If the y values match the y value of the line,
  if (y == y0) {
    // If the x values share an overlapping point,
    if ((w + (dyC + 1) + 1) > (max(x + w, x0 + (dyC + 1)) - min(x, x0))) {
      return true;
    }
  }

  while (xC < r) {
    if (pC >= 0) {
      // If the y values match the y value of the line,
      if ((y == (y0 + r)) || (y == (y0 - r))) {
        // If the x values share an overlapping point,
        if ((w + dxC + 1) > (max(x + w, (x0 - xC) + dxC) - min(x, (x0 - xC)))) {
          return true;
        }
      }

      dyC -= 2;
      pC -= dyC;
      r--;
    }

    dxC += 2;
    pC += dxC;
    xC++;

    // If the y values match the y value of the line,
    if ((y == (y0 + xC)) || (y == (y0 - xC))) {
      // If the x values share an overlapping point,
      if ((w + (dyC + 1) + 1) > (max(x + w, (x0 - r) + (dyC + 1)) - min(x, (x0 - r)))) {
        return true;
      }
    }
  }

  return false;
}

bool objectCollision::ellipseLineCollision(int x, int y, int w) {
  // This formula is taken from the TFT_eSPI library,
  // though of course has been modified to detect overlap.
  if (rx0 < 2) return false;
  if (ry0 < 2) return false;

  int32_t xE, yE;
  int32_t rx2 = rx0 * rx0;
  int32_t ry2 = ry0 * ry0;
  int32_t fx2 = 4 * rx2;
  int32_t fy2 = 4 * ry2;
  int32_t s;

  for (xE = 0, yE = ry0, s = 2 * ry2 + rx2 * (1 - 2 * ry0); ry2 * xE <= rx2 * yE; xE++) {
    // If the y values match the y value of the line,
    if ((y == (y0 - yE)) || (y == (y0 + yE))) {
      // If the x values share an overlapping point,
      if ((w + (xE + xE + 1) + 1) > (max(x + w, (x0 - xE) + (xE + xE + 1)) - min(x, (x0 - xE)))) {
        return true;
      }
    }

    if (s >= 0) {
      s += fx2 * (1 - yE);
      yE--;
    }
    s += ry2 * ((4 * xE) + 6);
  }

  for (xE = rx0, yE = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx0); rx2 * yE <= ry2 * xE; yE++) {
    // If the y values match the y value of the line,
    if ((y == (y0 - yE)) || (y == (y0 + yE))) {
      // If the x values share an overlapping point,
      if ((w + (xE + xE + 1) + 1) > (max(x + w, (x0 - xE) + (xE + xE + 1))) - min(x, (x0 - xE))) {
        return true;
      }
      break;
    }

    if (s >= 0) {
      s += fy2 * (1 - xE);
      xE--;
    }
    s += rx2 * ((4 * yE) + 6);
  }

  return false;
};
