#include <Arduino.h>
#include <Keyboard.h>
#include "MyKey.h"

const int buttonPin = D7;
const int boardSelect = D10;

const int leftKey = 176; // Return
const int rightKey = 176; // Return
int key_code = -1;

const unsigned long key_debounce_ms = 20;

const unsigned long left_delay_ms = 0;
const unsigned long right_delay_ms = 500;

bool will_press = false;
unsigned long delay_ms = 0;
unsigned long delay_timer = 0;

int isRightBoard = false;

Key key = Key(buttonPin);

void setup() {
  key.setPressTime(key_debounce_ms);
  key.setReleaseTime(key_debounce_ms);

  // If boardSelect is HIGH, we are on the Right Board
  isRightBoard = digitalRead(boardSelect) == HIGH;

  if (isRightBoard) {
    key_code = rightKey;
    delay_ms = right_delay_ms;
  } else {
    key_code = leftKey;
    delay_ms = left_delay_ms;
  }

  // Reset Keyboard Takeover
  Keyboard.begin();
  Keyboard.end();
}

void loop() {
  key.update();

  switch (key.kstate) {
    case PRESSED:
      will_press = true;
      delay_timer = millis();
      break;
  }

  // Handle Delayed Press
  if (will_press) {
    if ((millis() - delay_timer) > delay_ms) {
      Keyboard.begin();
      Keyboard.write(key_code);
      Keyboard.end();
      will_press = false;
    }
  }
}
