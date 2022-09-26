#include "MyKey.h"

Key::Key() {
  pin = -1;
  kstate = IDLE;
  stateChanged = false;
}

Key::Key(int btn_pin){
  pin = btn_pin;
  kstate = IDLE;
  stateChanged = false;

  pinMode(pin, INPUT);
}

void Key::update() {
  nextKeyState(digitalRead(pin));
}

void Key::nextKeyState(bool btn) {
  stateChanged = false;

  switch (kstate) {
    case IDLE:
      if (btn == CLOSED) {
        transitionTo(PRESS);
        pressTimer = millis();
      }
      break;
    case PRESS:
      if ((millis() - pressTimer) > pressTime) {
        transitionTo(PRESSED);
      } else if (btn == OPEN) {
        transitionTo(RELEASE);
        releaseTimer = millis();
      }
      break;
    case PRESSED:
      transitionTo(HOLD);
      break;
    case HOLD:
      if (btn == OPEN) {
        transitionTo(RELEASE);
        releaseTimer = millis();
      }
      break;
    case RELEASE:
      if ((millis() - releaseTimer) > releaseTime) {
        transitionTo(RELEASED);
      } else if (btn == CLOSED) {
        transitionTo(PRESS);
        pressTimer = millis();
      }
      break;
    case RELEASED:
      transitionTo(IDLE);
      break;
  }
}

void Key::transitionTo(KeyState nextState) {
  kstate = nextState;
  stateChanged = true;
}

void Key::setPressTime(unsigned long pTime) {
  pressTime = pTime;
}

void Key::setReleaseTime(unsigned long rTime) {
  releaseTime = rTime;
}
