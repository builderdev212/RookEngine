#ifndef POSITION_H
#define POSITION_H

struct position {
    // Top left corner
    int x;
    int y;

};

#endif

#ifndef RECTANGLE_H
#define RECTANGLE_H

struct rectangle {
    int w;
    int h;
};

#endif

#ifndef CIRCLE_H
#define CIRCLE_H

struct circle {
    int rw;
    int rh;

    // Set by calcSize function.
    int w;
    int h;
};

#endif

#ifndef TRIANGLE_H
#define TRIANGLE_H

struct triangle {
    // Point 1
    int x1;
    int y1;

    // Point 2
    int x2;
    int y2;

    // Point 3
    int x3;
    int y3;

    // Set by calcSize function.
    int w;
    int h;
};

#endif

#ifndef CALCSIZE_H
#define CALCSIZE_H

rectangle calcSize(rectangle);
circle calcSize(circle);
triangle calcSize(triangle);

#include "location.cpp"

#endif