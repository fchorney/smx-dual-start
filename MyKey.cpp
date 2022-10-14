#include "MyKey.h"

// Default Constructor
Key::Key() {
  pin = -1;
  kstate = IDLE;
  hasFullyReleased = true;
}

// Constructor
Key::Key(int btn_pin){
  pin = btn_pin;
  kstate = IDLE;
  hasFullyReleased = true;

  // Set pin to INPUT mode
  pinMode(pin, INPUT);
}

void Key::update() {
  bool btn = digitalRead(pin);
  KeyState state = kstate;

  switch (state) {
    case IDLE:
      if (btn == CLOSED) {
        kstate = PRESS;
        pressTimer = millis();
      }
      break;
    case PRESS:
      if ((millis() - pressTimer) > pressTime) {
        if (hasFullyReleased) {
          kstate = PRESSED;
        } else {
          if (btn == CLOSED) {
            kstate = HOLD;
          } else {
            kstate = RELEASE;
          }
        }
      } else if (btn == OPEN) {
        kstate = RELEASE;
        releaseTimer = millis();
      }
      break;
    case PRESSED:
      hasFullyReleased = false;
      kstate = HOLD;
      break;
    case HOLD:
      if (btn == OPEN) {
        kstate = RELEASE;
        releaseTimer = millis();
      }
      break;
    case RELEASE:
      if ((millis() - releaseTimer) > releaseTime) {
        kstate = RELEASED;
      } else if (btn == CLOSED) {
        kstate = PRESS;
        pressTimer = millis();
      }
      break;
    case RELEASED:
      hasFullyReleased = true;
      kstate = IDLE;
      break;
  }
}

void Key::setPressTime(unsigned long pTime) {
  pressTime = pTime;
}

void Key::setReleaseTime(unsigned long rTime) {
  releaseTime = rTime;
}
