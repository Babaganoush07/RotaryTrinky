#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include <RotaryEncoder.h>
#include "HID-Project.h"  // https://github.com/NicoHood/HID

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
int16_t neo_brightness = 20; // initialize with 20 brightness (out of 255)
uint32_t teams = strip.Color(70, 78, 184);
uint32_t youtube = strip.Color(255, 0, 0);
uint32_t yellow = strip.Color(255, 255, 0);

RotaryEncoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, RotaryEncoder::LatchMode::FOUR3);
// This interrupt will do our encoder reading/checking!
void checkPosition() {
  encoder.tick(); // just call tick() to check the state.
}

Adafruit_FreeTouch qt = Adafruit_FreeTouch(A2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

int last_rotary = 0;
bool last_button = false;
int opertaionalMode = 0;


void teamsFunctions(){
  // read touch
  int touch = qt.measure();

  // read encoder
  int curr_rotary = encoder.getPosition();
  RotaryEncoder::Direction direction = encoder.getDirection();

  // change the color
  strip.setPixelColor(0, teams);
  strip.show();

  if (direction != RotaryEncoder::Direction::NOROTATION) {
    if (direction == RotaryEncoder::Direction::CLOCKWISE) {
      Consumer.write(MEDIA_VOLUME_UP);
    }
    if (direction == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    last_rotary = curr_rotary;
  }

  if(touch >= 300){
    // un-mute in teams
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_SPACE);
    // blink red when hot mic
    strip.setPixelColor(0, youtube);
    strip.show();
    delay(1000);
    strip.clear();
    strip.show();
    
    delay(200); // debounce
  }else{
    Keyboard.releaseAll();
  }
} // END teamsFunctions()


void youtubeFunctions(){
  // read touch
  int touch = qt.measure();

  // read encoder
  int curr_rotary = encoder.getPosition();
  RotaryEncoder::Direction direction = encoder.getDirection();

  // Chenge the color
  strip.setPixelColor(0, youtube);
  strip.show();

  if (direction != RotaryEncoder::Direction::NOROTATION) {
    if (direction == RotaryEncoder::Direction::CLOCKWISE) {
      Consumer.write(MEDIA_VOLUME_UP);
    }
    if (direction == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    last_rotary = curr_rotary;
  }

  if(touch >= 300){
    Consumer.write(MEDIA_PLAY_PAUSE);
    delay(200); // debounce
  } // END touch if

  delay(10); // debounce
} // END youtubeFunctions()


void increaseBrightness(){
  // read encoder
  int curr_rotary = encoder.getPosition();
  RotaryEncoder::Direction direction = encoder.getDirection();

  // Chenge the color
  strip.setPixelColor(0, yellow);
  strip.show();

  if (direction != RotaryEncoder::Direction::NOROTATION) {
    if (direction == RotaryEncoder::Direction::CLOCKWISE) {
      neo_brightness += 10;
    }
    if (direction == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
      neo_brightness -= 10;
    }
    
    // ranges between 0 and 255
    if (neo_brightness > 255) neo_brightness = 255;
    if (neo_brightness < 0) neo_brightness = 0;
      
    last_rotary = curr_rotary;
  }
  
  strip.setBrightness(neo_brightness);
} // increaseBrightness()

void setup() {

  attachInterrupt(PIN_ENCODER_A, checkPosition, CHANGE);
  attachInterrupt(PIN_ENCODER_B, checkPosition, CHANGE);
  
  // set up the encoder switch, which is separate from the encoder
  pinMode(PIN_ENCODER_SWITCH, INPUT_PULLDOWN);

  // setup touch pad
  qt.begin();
  
  // start neopixels
  strip.begin();
  strip.setBrightness(neo_brightness);
  strip.show(); // Initialize all pixels to 'off'

  Consumer.begin(); // For media stuff
  Keyboard.begin(); // For Teams mute un mute
} // END setup()


void loop() {
  // read the button
  bool curr_button = !digitalRead(PIN_ENCODER_SWITCH);

  if (curr_button && !last_button) { // switch pressed!
    opertaionalMode ++;
  }

  if(opertaionalMode > 2){
    opertaionalMode = 0;
  }

  if(opertaionalMode == 0){
    teamsFunctions();
  }else if(opertaionalMode == 1){
    youtubeFunctions();
  }else if(opertaionalMode == 2){
    increaseBrightness();
  }
 
  last_button = curr_button;
} // END loop()
