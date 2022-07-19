#include "Adafruit_FreeTouch.h"

Adafruit_FreeTouch qt = Adafruit_FreeTouch(A2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);


void setup() {
  Serial.begin(115200);
  
  qt.begin();
}



void loop() {
  int counter, result = 0;
  
  // DIY
  Serial.println("\n*************************************");

  counter = millis();
  result = qt.measure(); 
  Serial.print("QT: "); Serial.print(result);
  Serial.print(" (");  Serial.print(millis() - counter); Serial.println(" ms)");
  
  delay(200);
}
