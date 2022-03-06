#ifndef joystick_h
#define joystick_h

class joystick {
  public:
    // Initalizer. uses the x pin, y pin, and the center of the joystick.
    joystick(int x, int y, int center);
    joystick(int x, int y);

    // Figure out the center of the joystick.
    void center();

    // Read the joysticks value.
    int read(uint8_t axis);
    int read(uint8_t axis, bool orientation);
    int read(uint8_t axis, int multiplier);
    
  private:
    // Center of the joystick.
    int center;

    // Pins.
    int xPin;
    int yPin;
}

#endif
