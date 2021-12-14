#ifndef joystick_h
#define joystick_h

class joystick {
  public:
    int xPin;
    int yPin;
    int zPin;

    // Function to setup the variables needed for the class. They're overloaded so that the user can either choose to enter a buttonless joystick or a joystick with a button.
    void begin(int x, int y);
    void begin(int x, int y, int z);

    // Read the joystick. X and Y orientation can be used to flip around the orientation of the joystick. True is the default orientation, false is the opposite. If
    // you don't wish to switch the orientation at all, you don't have to.
    int readJoy(uint8_t axis);
    int readJoy(uint8_t axis, bool orientation);

    // Function to read the joystick button. Will only read if the user has defined a z pin.
    bool readZ(bool singular);

  private:
    int lastButtonState = 1;
    bool isButton = false;
};

#endif
