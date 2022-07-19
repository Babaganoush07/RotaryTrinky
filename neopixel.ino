#include <Adafruit_NeoPixel.h>

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
int16_t neo_brightness = 20; // initialize with 20 brightness (out of 255)

void setup() {
  Serial.begin(115200);
  
  // start neopixels
  strip.begin();
  strip.setBrightness(neo_brightness);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
  // update pixels!
  strip.setBrightness(neo_brightness);
  // Red
  strip.setPixelColor(0, 255, 0, 0);
  strip.show();
  
  delay(1000);
  
  // Green
  strip.setPixelColor(0, 0, 255, 0);
  strip.show();
  
  delay(1000);
  
  // Blue
  strip.setPixelColor(0, 0, 0, 255);
  strip.show();
  
  delay(1000);
  
}
