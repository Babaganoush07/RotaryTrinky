# Adafruit Rotary Trinkey


## Table of Contents
* [General Info](#general-information)
* [Setup](#setup)


![image](https://user-images.githubusercontent.com/94538153/179838341-eba4838a-379d-4bac-a83f-2ec5c1eabfc5.png)


## General Information
- It's half USB Key, half Adafruit Trinket, half rotary encoder...it's Rotary Trinkey.
- Please note this board DOES NOT come with a rotary encoder.
- The PCB is designed to slip into any USB A port on a computer or laptop. There's an ATSAMD21 microcontroller on board with just enough circuitry to keep it happy. Three pins of the microcontroller connects to a rotary encoder with built-in push switch. Another connects to a NeoPixel LED. Finally, one pin can be used as a capacitive touch input.


## Setup
- Purchasing a Rotary Trinkey: [Adafruit Rotary Trinkey - USB NeoPixel Rotary Encoder](https://www.adafruit.com/product/4964)
- Get a rotary encoder: [Rotary Encoder + Extras](https://www.adafruit.com/product/377)
- Getting Started: [Overview](https://learn.adafruit.com/adafruit-rotary-trinkey/overview)
- In Arduino IDE Preferences, in the Additional Boards Manager URLs textbox enter:

`https://adafruit.github.io/arduino-board-index/package_adafruit_index.json`

- Install `Arduino SAMD` and `Adafruit SAMD` in the boards manager.

**LIBRARIES**
- `RotaryEncoder` [(RotaryEncoder)](https://github.com/mathertel/RotaryEncoder)
- `Adafruit NeoPixel` [(Adafruit NeoPixel)](https://github.com/adafruit/Adafruit_NeoPixel)
- `Adafruit FreeTouch` [(Adafruit FreeTouch)](https://github.com/adafruit/Adafruit_FreeTouch)
- `HID-Project` [(HID-Project)](https://github.com/NicoHood/HID)

Got a return error from the samd.cpp file in the HID-Project, found the fix [here](https://github.com/NicoHood/HID/pull/342/commits/ea0c514d9129506700cb6a1df5dbc518f48c5031)
