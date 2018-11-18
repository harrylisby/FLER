#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <Joystick.h>
//Adafruit_ADS1115 ads(0x48);

Joystick js(0, 0, 1, 0x48);

void setup() {
  Wire.begin();
 	Serial.begin(115200); // Ignored by Maple. But needed by boards using Hardware serial via a USB to Serial Adaptor
  ads.begin();
  ads.setGain(GAIN_ONE);
}

void loop() {
  actMillis = millis();
  if((actMillis-prevMillis)>20){
    prevMillis=actMillis;
    //su codigo aqui
    int16_t adcY = readY();
    int16_t adcX = readX();
    int16_t adcZ = readYB();
    int16_t adcG = readXB;
//    int16_t adcI;
//    int16_t adcR;
    

    Serial.print("X: ");
    Serial.print(adcX);
    Serial.print(" ");
    Serial.print("Y: ");
    Serial.print(adcY);
    Serial.print(" ");
    Serial.print("Z: ");
    Serial.print(adcZ);
//    Serial.print(" ");
//    Serial.print("G: ");
//    Serial.print(adcG);
//    Serial.print(" ");
//    Serial.print("I: ");
//    Serial.print(adcI);
//    Serial.print(" ");
//    Serial.print("R: ");
//    Serial.print(adcR);
    Serial.println();
  }
}
