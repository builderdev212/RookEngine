#ifndef countdown_h
#define countdown_h

class countdown {
  public:
    unsigned long timeLeft;
    unsigned long endTime;

    // Starts the timer.
    void start(int32_t seconds);

    // Pauses the timer.
    void pause();

    // Resumes the timer.
    void resume();

    // Stops the timer.
    void stop();

    // Checks to see if the timer is done. Returns true if finshed, else returns false.
    bool isDone();
  private:
    // Is the timer running. This ignores whether they are paused or not.
    bool isTimer = false;

    // Timer variables
    bool isRunningTimer = false;
    bool isPausedTimer = false;
};

#endif
