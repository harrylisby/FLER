#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);

int16_t adcY;
int16_t adcX;
int16_t adcZ;
int16_t adcG;

//Joystick derecho con boton
const int boton = 0;
int value_boton;

uint32_t prevMillis;
uint32_t actMillis;

void setup() {
  Wire.begin();
 	Serial.begin(115200); // Ignored by Maple. But needed by boards using Hardware serial via a USB to Serial Adaptor
  ads.begin();
  ads.setGain(GAIN_ONE);
  pinMode(boton, INPUT_PULLUP);
}

void loop() {
  actMillis = millis();
  if((actMillis-prevMillis)>20){
    prevMillis=actMillis;
    //su codigo aqui
    // Read the analog input into a variable:
    value_boton = digitalRead(boton);
    //Se lee el valor del eje I y R
    int16_t adcI=ads.readADC_SingleEnded(0);
    int16_t adcR=ads.readADC_SingleEnded(1);
    
    if(value_boton == 1){
      //Leer eje Y y X
      adcY=ads.readADC_SingleEnded(2);
      adcX=ads.readADC_SingleEnded(3);
      adcZ = 13150;
      adcG = 13150;
    }
    else{
      //Leer eje Z y G
      adcZ=ads.readADC_SingleEnded(2);
      adcG=ads.readADC_SingleEnded(3);
      adcY = 13150;
      adcX = 13150;
    }

    Serial.print("X: ");
    Serial.print(adcX);
    Serial.print(" ");
    Serial.print("Y: ");
    Serial.print(adcY);
    Serial.print(" ");
    Serial.print("Z: ");
    Serial.print(adcZ);
    Serial.print(" ");
    Serial.print("G: ");
    Serial.print(adcG);
    Serial.print(" ");
    Serial.print("I: ");
    Serial.print(adcI);
    Serial.print(" ");
    Serial.print("R: ");
    Serial.print(adcR);
    Serial.println();
  }
}
