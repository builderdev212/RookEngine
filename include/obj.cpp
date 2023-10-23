#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

// Important helper functions and structures
#include "location.h"
#include "drawHelper.h"

// Constructor
template <class T>
obj<T>::obj(TFT_eSPI *tft, position initialPosition, T newShape, int bg, bool moveable, void (*initialDraw)(TFT_eSprite*)) {
    // Display
    _tft = tft;
    shadow = new TFT_eSprite(_tft);
    object = new TFT_eSprite(_tft);

    // Position/Shape
    currentPos = initialPosition;
    shape = calcSize(newShape);
    isMoveable = moveable;

    // Graphics
    defaultState = initialDraw;
    bgColor = bg;
}

template <class T>
void obj<T>::createSprite() {
    // Only create the shadow if the object is moveable.
    if (isMoveable) {
        shadow->createSprite(shape.w, shape.h);
        shadow->fillRect(0, 0, shape.w, shape.h, bgColor);
        shadow->pushSprite(currentPos.x, currentPos.y);
    }

    // Create the object sprite.
    object->createSprite(shape.w, shape.h);
    defaultState(object);
    object->pushSprite(currentPos.x, currentPos.y);
}

/*
// Sprite Functions
template < >
void obj<rectangle>::createSprite() {
    // Only create the shadow if the object is moveable.
    if (isMoveable) {
        shadow.createSprite(shape.w, shape.h);
        shadow.fillRect(0, 0, shape.w, shape.h, bgColor);
    }

    // Create the object sprite.
    object.createSprite(shape.w, shape.h);
    defaultState(object);
}

template < >
void obj<circle>::createSprite() {
    // Only create the shadow if the object is moveable.
    if (isMoveable) {
        shadow.createSprite(shape.w, shape.h);
        shadow.fillRect(0, 0, shape.w, shape.h, bgColor);
    }

    // Create the object sprite.
    object.createSprite(shape.w, shape.h);
    defaultState(object);
}

template < >
void obj<triangle>::createSprite() {
    // Only create the shadow if the object is moveable.
    if (isMoveable) {
        shadow.createSprite(shape.w, shape.h);
        shadow.fillTriangle(shape.x1, shape.y1, shape.x2, shape.y2, shape.x3, shape.y3, bgColor);
    }

    // Create the object sprite.
    object.createSprite(shape.w, shape.h);
    defaultState(object);
}
*/

// Deconstructor
template <class T>
obj<T>::~obj() {
    _tft = nullptr;
    defaultState = nullptr;
}
