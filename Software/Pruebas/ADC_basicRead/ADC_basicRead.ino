#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  ads.begin();
  
}

void loop() {
  int16_t adc0=ads.readADC_SingleEnded(0);
  int16_t adc1=ads.readADC_SingleEnded(1);
  int16_t adc2=ads.readADC_SingleEnded(2);
  int16_t adc3=ads.readADC_SingleEnded(3);

}
