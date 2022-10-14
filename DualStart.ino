#include <Arduino.h>
#include <Keyboard.h>
#include "MyKey.h"

// Arduino Pins
const int buttonPin = D7;
const int boardSelect = D10;

// Key Codes
const int leftKeyCode = 176; // Return
const int rightKeyCode = 176; // Return
int key_code = -1;

// Amount in milliseconds to debounce the press and release of the button
const unsigned long keyDebounce = 20;

// Set delay for both "keyboards" in Milliseconds
const unsigned long leftDelay = 0;
const unsigned long rightDelay = 100;

// Variables to handle delayed button press
bool willPress = false;
unsigned long keyDelay = 0;
unsigned long keyDelayTimer = 0;

// Determine if we are on the left or right board
int isRightBoard = false;

// The Key/Button we are using
Key key = Key(buttonPin);

void setup() {
  key.setPressTime(keyDebounce);
  key.setReleaseTime(keyDebounce);

  // If boardSelect pin is HIGH, we are on the Right Board
  isRightBoard = digitalRead(boardSelect) == HIGH;

  // Set variables depending on which "Keyboard" we are on
  if (isRightBoard) {
    key_code = rightKeyCode;
    keyDelay = rightDelay;
  } else {
    key_code = leftKeyCode;
    keyDelay = leftDelay;
  }

  // Reset Keyboard Takeover
  Keyboard.begin();
  Keyboard.end();
}

void loop() {
  // Update the status of the key
  key.update();

  switch (key.kstate) {
    case PRESSED:
      // When we detect a press, start the delay timer
      willPress = true;
      keyDelayTimer = millis();
      break;
  }

  // Handle Delayed Press
  if (willPress) {
    if ((millis() - keyDelayTimer) > keyDelay) {
      Keyboard.begin();
      Keyboard.write(key_code);
      Keyboard.end();
      willPress = false;
    }
  }
}
