#ifndef button_h
#define button_h

class button {
  public:
    // Initalizer functions.
    button(int pin);
    button(int pin, byte inputType);

    // Return the current button state.
    bool read();

    // Look for a state change in the button.
    bool uniqueRead();

  private:
    // Button pin
    int buttonPin;

    // State of the button
    int currentState = LOW;
    int previousState = currentState;

    // Debounce vairables
    unsigned long lastDebounce = millis();
    unsigned long debounceDelay = 5;

    // Function to read the button.
    void readButton();
};

#endif
