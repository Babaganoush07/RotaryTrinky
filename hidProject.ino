#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  Consumer.begin();
  // or
  Keyboard.begin();
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);

    // See HID Project documentation for more Consumer keys
    Consumer.write(MEDIA_PLAY_PAUSE);
    
    // See HID Project documentation for more Keyboard layouts and keys
    Keyboard.println("Hello World!");
    // Write single keys, do not use a number here!
    //Keyboard.write(KEY_ENTER);

    // Simple debounce
    delay(300);
    digitalWrite(pinLed, LOW);
  }
}
