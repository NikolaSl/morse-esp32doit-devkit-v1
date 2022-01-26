#include "Arduino.h"
#include "BleKeyboard.h"

BleKeyboard bleKeyboard("MorseManiaKey", "LZ1NKL", 100);

struct Key {
  const uint8_t PIN;
  const char KEY;
  const uint8_t TONE_PIN;
  const int TONE_FREQ;
  bool isPressed;
};

Key keys[] = {{12,'a', 0, 0, false}, {13,'s', 0, 0, false}, {14,KEY_RETURN, 27, 600, false}};
int keysCount = sizeof(keys)/sizeof(*keys);

void setup() {
  for (int key = 0; key<keysCount; key++) {
    pinMode(keys[key].PIN, INPUT_PULLUP);
    if (keys[key].TONE_PIN) {
      ledcSetup(key, keys[key].TONE_FREQ, 10);
      ledcAttachPin(keys[key].TONE_PIN, key);
    }
  }
  bleKeyboard.begin();
}

void loop() {
  for (int key = 0; key<keysCount; key++) {
    if (HIGH == digitalRead(keys[key].PIN)) {
      if (keys[key].isPressed) {
        bleKeyboard.release(keys[key].KEY);
        keys[key].isPressed = false;
        if (keys[key].TONE_PIN) {
          ledcWriteTone(key, 0);
        }
        delay(2);
      }
    } else {
      if (!keys[key].isPressed) {
        bleKeyboard.press(keys[key].KEY);
        keys[key].isPressed = true;
        if (keys[key].TONE_PIN) {
          ledcWriteTone(key, keys[key].TONE_FREQ);
        }
        delay(2);
      }
    }
  }
}
