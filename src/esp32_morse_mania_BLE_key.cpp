#include "Arduino.h"
#include "BleKeyboard.h"

BleKeyboard bleKeyboard("MorseManiaKey", "LZ1NKL", 100);

struct Key {
  const uint8_t PIN;
  const char KEY;
  bool isPressed;
};

Key keys[] = {{12,'a',false}, {13,'s',false}, {14,KEY_RETURN,false}};

void setup() {
  for (int key = 0; key<3; key++) {
    pinMode(keys[key].PIN, INPUT_PULLUP);
  }
  bleKeyboard.begin();
}

void loop() {
  for (int key = 0; key<3; key++) {
    if (HIGH == digitalRead(keys[key].PIN)) {
      if (keys[key].isPressed) {
        bleKeyboard.release(keys[key].KEY);
        keys[key].isPressed = false;
        delay(2);
      }
    } else {
      if (!keys[key].isPressed) {
        bleKeyboard.press(keys[key].KEY);
        keys[key].isPressed = true;
        delay(2);
      }
    }
  }

}
