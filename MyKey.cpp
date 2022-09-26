#include "MyKey.h"

// Default Constructor
Key::Key() {
  pin = -1;
  kstate = IDLE;
}

// Constructor
Key::Key(int btn_pin){
  pin = btn_pin;
  kstate = IDLE;

  // Set pin to INPUT mode
  pinMode(pin, INPUT);
}

void Key::update() {
  btn = (digitalRead(pin));
  state = kstate;

  switch (state) {
    case IDLE:
      if (btn == CLOSED) {
        kstate = PRESS;
        pressTimer = millis();
      }
      break;
    case PRESS:
      if ((millis() - pressTimer) > pressTime) {
        kstate = PRESSED;
      } else if (btn == OPEN) {
        kstate = RELEASE;
        releaseTimer = millis();
      }
      break;
    case PRESSED:
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
