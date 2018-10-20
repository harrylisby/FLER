#include "joysticRead.h"

joystickReader joy(A0,A1,2);

uint32_t actualMillis=0;
uint32_t prevMillis=0;


void setup() {
  Serial.begin(9600);
  Serial.print("Started");

}

void loop() {
  
  actualMillis=millis();
  if((prevMillis-actualMillis)>=20){  //Ejecutar código cada 20ms
    prevMillis=actualMillis;
    Serial.println(joy.readCoords());    //Para obtener los valores se ejecuta joy.readCoords();
  }
}
