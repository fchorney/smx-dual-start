#ifndef _MY_KEY_H_
#define _MY_KEY_H_

#include <Arduino.h>

typedef enum {IDLE, PRESS, PRESSED, HOLD, RELEASE, RELEASED} KeyState;
#define OPEN LOW
#define CLOSED HIGH

class Key {
  public:
    int pin;
    KeyState kstate;
    bool stateChanged;
    unsigned long pressTimer;
    unsigned long releaseTimer;

    Key();
    Key(int pin);

    void update();
    void setPressTime(unsigned long);
    void setReleaseTime(unsigned long);

  private:
    unsigned long pressTime;
    unsigned long releaseTime;

    void nextKeyState(bool btn);
    void transitionTo(KeyState nextState);
};

#endif
