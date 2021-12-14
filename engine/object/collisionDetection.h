#include <Arduino.h>

bool ellipseCollision(int16_t x0, int16_t y0, int16_t rx, int16_t ry, int16_t x1, int16_t y1, int32_t w1)
{
  int32_t x, y;
  int32_t rx2 = rx * rx;
  int32_t ry2 = ry * ry;
  int32_t fx2 = 4 * rx2;
  int32_t fy2 = 4 * ry2;
  int32_t s;

  for (x = 0, y = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry); ry2 * x <= rx2 * y; x++) {
    if (x0 - x <= x1 && x0 + x + 1 >= x1 + w1) {
      if (y0 - y == y1) {
        return true;
      }
      if (y0 + y == y1) {
        return true;
      }
    }

    if (s >= 0) {
      s += fx2 * (1 - y);
      y--;
    }

    s += ry2 * ((4 * x) + 6);
  }

  for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx); rx2 * y <= ry2 * x; y++) {
    if (x0 - x <= x1 && x0 + x + 1 >= x1 + w1) {
      if (y0 - y == y1) {
        return true;
      }
      if (y0 + y == y1) {
        return true;
      }
    }

    if (s >= 0) {
      s += fy2 * (1 - x);
      x--;
    }
    s += rx2 * ((4 * y) + 6);
  }

  return false;
}

bool circleCollision(int16_t x0, int16_t y0, int16_t r0, int16_t x1, int16_t y1, int16_t w1) {
  x0 += r0 + 1;
  y0 += r0 + 1;

  int16_t x = 0;
  int16_t dx = 1;
  int16_t dy = r0 + r0;
  int16_t p = -(r0 / 2);

  if (y0 == y1) {
    if (x0 - r0 >= x1 && x0 - r0 + dy + 1 <= x1 + w1) {
      return true;
    }
  }

  while (x < r0) {
    if (p >= 0) {
      if (y0 + r0 == y1 || y0 - r0 == y1) {
        if (x1 >= x0 - x && x1 <= x0 - x + dx) {
          return true;
        }
      }

      dy -= 2;
      p -= dx;
      r0--;
    }

    dx += 2;
    p += dx;
    x++;

    if (y0 + x == y1 || y0 - x == y1) {
      if (x1 >= x0 - r0 && x1 <= x0 - r0 + dy + 1) {
        return true;
      }
    }
  }

  return false;
}

bool rectCollision(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t x1, int16_t y1, int16_t w1) {
  if (y0 <= y1 && y0 + h0 >= y1) {
    for (int16_t x = x0; x <= x0 + w0; x++) {
      if (x >= x1 && x <= x1 + w1) {
        return true;
      }
    }
  }

  return false;
}

bool pointCollision(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t w1) {
  if (y0 == y1) {
    if (x0 >= x1 && x0 <= x1 + w1) {
      return true;
    }
  }

  return false;
}

/*
  Shape:  0 - point, 1 - rectangle, 2 - circle, 3 - ellipse.

  Point: w and h are ignored, therefore you could use any number there without any effect on the point itself.
  Rectangle: w and h are used to determine the width and height of the rectangle. This can also be used to check if a solid line is interfering
  with another shape by setting either w or h to 0. A width of 0 refers to a vertical line, and a height of 0 refers to a horizontal line.
  Circle: w and h refer to the diameter of the circle.
  Ellipse: w and h refer to the respective diameters, w being the horizontal diameter and h being the vertical diameter.
*/
bool collision(int16_t x0, int16_t y0, int16_t w0, int16_t h0, int16_t shape0, int16_t x1, int16_t y1, int16_t w1, int16_t h1, int16_t shape1) {
  switch (shape0) {
    case 0:
      switch (shape1) {
        case 0:
          if (pointCollision(x1, y1, x0, y0, 0)) {
            return true;
          }
          break;
        case 1:
          if (rectCollision(x1, y1, w1, h1, x0, y0, 0)) {
            return true;
          }
          break;
        case 2:
          if (circleCollision(x1, y1, w1 / 2, x0, y0, 0)) {
            return true;
          }
          break;
        case 3:
          if (ellipseCollision(x1, y1, w1, h1, x0, y0, 0)) {
            return true;
          }
        default:
          break;
      }
      break;
    default:
      break;
    case 1:
      for (int16_t y = y0; y <= y0 + h0; y++) {
        switch (shape1) {
          case 0:
            if (pointCollision(x1, y1, x0, y, w0)) {
              return true;
            }
            break;
          case 1:
            if (rectCollision(x1, y1, w1, h1, x0, y, w0)) {
              return true;
            }
            break;
          case 2:
            if (circleCollision(x1, y1, w1 / 2, x0, y, w0)) {
              return true;
            }
            break;
          case 3:
            if (ellipseCollision(x1, y1, w1, h1, x0, y, w0)) {
              return true;
            }
            break;
          default:
            break;
        }
      }
    case 2:
      {
        int16_t r0 = w0 / 2;
        x0 += r0 + 1;
        y0 += r0 + 1;

        int16_t x = 0;
        int16_t dx = 1;
        int16_t dy = r0 + r0;
        int16_t p = -(r0 / 2);

        switch (shape1) {
          case 0:
            if (pointCollision(x1, y1, x0 - r0, y0, dy + 1)) {
              return true;
            }
            break;
          case 1:
            if (rectCollision(x1, y1, w1, h1, x0 - r0, y0, dy + 1)) {
              return true;
            }
            break;
          case 2:
            if (circleCollision(x1, y1, w1 / 2, x0 - r0, y0, dy + 1)) {
              return true;
            }
            break;
          case 3:
            if (ellipseCollision(x1, y1, w1, h1, x0 - r0, y0, dy + 1)) {
              return true;
            }
            break;
          default:
            break;
        }

        while (x < r0) {
          if (p >= 0) {
            switch (shape1) {
              case 0:
                if (pointCollision(x1, y1, x0 - x, y0 + r0, dx)) {
                  return true;
                }
                if (pointCollision(x1, y1, x0 - x, y0 - r0, dx)) {
                  return true;
                }
                break;
              case 1:
                if (rectCollision(x1, y1, w1, h1, x0 - x, y0 + r0, dx)) {
                  return true;
                }
                if (rectCollision(x1, y1, w1, h1, x0 - x, y0 - r0, dx)) {
                  return true;
                }
                break;
              case 2:
                if (circleCollision(x1, y1, w1 / 2, x0 - x, y0 + r0, dx)) {
                  return true;
                }
                if (circleCollision(x1, y1, w1 / 2, x0 - x, y0 - r0, dx)) {
                  return true;
                }
                break;
              case 3:
                if (ellipseCollision(x1, y1, w1, h1, x0 - x, y0 + r0, dx)) {
                  return true;
                }
                if (ellipseCollision(x1, y1, w1, h1, x0 - x, y0 - r0, dx)) {
                  return true;
                }
                break;
              default:
                break;
            }

            dy -= 2;
            p -= dy;
            r0--;
          }

          dx += 2;
          p += dx;
          x++;

          switch (shape1) {
            case 0:
              if (pointCollision(x1, y1, x0 - r0, y0 + x, dx)) {
                return true;
              }
              if (pointCollision(x1, y1, x0 - r0, y0 - x, dx)) {
                return true;
              }
              break;
            case 1:
              if (rectCollision(x1, y1, w1, h1, x0 - r0, y0 + x, dx)) {
                return true;
              }
              if (rectCollision(x1, y1, w1, h1, x0 - r0, y0 - x, dx)) {
                return true;
              }
              break;
            case 2:
              if (circleCollision(x1, y1, w1 / 2, x0 - r0, y0 + x, dx)) {
                return true;
              }
              if (circleCollision(x1, y1, w1 / 2, x0 - r0, y0 - x, dx)) {
                return true;
              }
              break;
            case 3:
              if (ellipseCollision(x1, y1, w1, h1, x0 - r0, y0 + x, dx)) {
                return true;
              }
              if (ellipseCollision(x1, y1, w1, h1, x0 - r0, y0 - x, dx)) {
                return true;
              }
              break;
            default:
              break;
          }
        }
      }
      break;
    case 3:
      {
        int16_t rx = x0 / 2;
        int16_t ry = y0 / 2;
        int32_t x, y;
        int32_t rx2 = rx * rx;
        int32_t ry2 = ry * ry;
        int32_t fx2 = 4 * rx2;
        int32_t fy2 = 4 * ry2;
        int32_t s;

        for (x = 0, y = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry); ry2 * x <= rx2 * y; x++) {
          switch (shape1) {
            case 0:
              if (pointCollision(x1, y1, x0 - x, y0 - y, x + x + 1)) {
                return true;
              }
              if (pointCollision(x1, y1, x0 - x, y0 + y, x + x + 1)) {
                return true;
              }
              break;
            case 1:
              if (rectCollision(x1, y1, w1, h1, x0 - x, y0 - y, x + x + 1)) {
                return true;
              }
              if (rectCollision(x1, y1, w1, h1, x0 - x, y0 + y, x + x + 1)) {
                return true;
              }
              break;
            case 2:
              if (circleCollision(x1, y1, w1 / 2, x0 - x, y0 - y, x + x + 1)) {
                return true;
              }
              if (circleCollision(x1, y1, w1 / 2, x0 - x, y0 + y, x + x + 1)) {
                return true;
              }
              break;
            case 3:
              if (ellipseCollision(x1, y1, w1, h1, x0 - x, y0 - y, x + x + 1)) {
                return true;
              }
              if (ellipseCollision(x1, y1, w1, h1, x0 - x, y0 + y, x + x + 1)) {
                return true;
              }
              break;
            default:
              break;
          }

          if (s >= 0) {
            s += fx2 * (1 - y);
            y--;
          }
          s += ry2 * ((4 * x) + 6);
        }

        for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx); rx2 * y <= ry2 * x; y++) {
          switch (shape1) {
            case 0:
              if (pointCollision(x1, y1, x0 - x, y0 - y, x + x + 1)) {
                return true;
              }
              if (pointCollision(x1, y1, x0 - x, y0 + y, x + x + 1)) {
                return true;
              }
              break;
            case 1:
              if (rectCollision(x1, y1, w1, h1, x0 - x, y0 - y, x + x + 1)) {
                return true;
              }
              if (rectCollision(x1, y1, w1, h1, x0 - x, y0 + y, x + x + 1)) {
                return true;
              }
              break;
            case 2:
              if (circleCollision(x1, y1, w1 / 2, x0 - x, y0 - y, x + x + 1)) {
                return true;
              }
              if (circleCollision(x1, y1, w1 / 2, x0 - x, y0 + y, x + x + 1)) {
                return true;
              }
              break;
            case 3:
              if (ellipseCollision(x1, y1, w1, h1, x0 - x, y0 - y, x + x + 1)) {
                return true;
              }
              if (ellipseCollision(x1, y1, w1, h1, x0 - x, y0 + y, x + x + 1)) {
                return true;
              }
              break;
            default:
              break;
          }

          if (s >= 0) {
            s += fy2 * (1 - x);
            x--;
          }
          s += rx2 * ((4 * y) + 6);
        }
      }
  }

  return false;
}
