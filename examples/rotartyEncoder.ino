#include <RotaryEncoder.h>

RotaryEncoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, RotaryEncoder::LatchMode::FOUR3);

// This interrupt will do our encoder reading/checking!
void checkPosition() {
  encoder.tick(); // just call tick() to check the state.
}

int last_rotary = 0;
bool last_button = false;

void setup() {
  Serial.begin(115200);
  
  attachInterrupt(PIN_ENCODER_A, checkPosition, CHANGE);
  attachInterrupt(PIN_ENCODER_B, checkPosition, CHANGE);
  
  // set up the encoder switch, which is separate from the encoder
  pinMode(PIN_ENCODER_SWITCH, INPUT_PULLDOWN);
}

void loop() {
  // read encoder
  int curr_rotary = encoder.getPosition();
  RotaryEncoder::Direction direction = encoder.getDirection();
  // read switch
  bool curr_button = !digitalRead(PIN_ENCODER_SWITCH);
  
  if (direction != RotaryEncoder::Direction::NOROTATION) {
    Serial.print("Encoder value: ");
    Serial.print(curr_rotary);
    Serial.print(" direction: ");
    Serial.print((int)direction);

    if (direction == RotaryEncoder::Direction::CLOCKWISE) {
      Serial.println(" Rotate+");
    }
    if (direction == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
      Serial.println(" Rotate-");
    }

    last_rotary = curr_rotary;
  }

  if (curr_button && !last_button) { // switch pressed!
    Serial.println("Press");
  }
  
  if (!curr_button && last_button) { // switch released!
    Serial.println("Release");
  }
  
  last_button = curr_button;

  delay(10); // debounce
}
