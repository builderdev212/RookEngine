#ifndef obj_h
#define obj_h

#include <TFT_eSPI.h>

#include "location.h"
#include "drawHelper.h"

template <class T>
class obj {
    public:
        // Constructor
        obj(TFT_eSPI*, position, T, int, bool, void (*)(TFT_eSprite*));

        // Deconstructor
        ~obj();

    private:
        // Display
        TFT_eSPI *_tft = nullptr;

        // Object Sprite
        TFT_eSprite *shadow = nullptr;
        TFT_eSprite *object = nullptr;

        // Position/Shape Variables
        position currentPos;
        T shape;
        bool isMoveable;

        // Graphic Variables
        drawFunc defaultState;
        int bgColor;

        // Sprite Functions
        void createSprite();

        //void updateSprite();
};

#include "obj.cpp"

#endif
