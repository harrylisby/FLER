#include <Joystick.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Joystick::Joystick(int boton, int adc1, int adc2):ads(dir){
  _boton = boton;
  _adc1 = adc1;
  _adc2 = adc2;
}

Joystick::readY(){
    value_boton = digitalRead(boton);
   \\ if (value_boton == 
    adcI=ads.readADC_SingleEnded(0);
    adcR=ads.readADC_SingleEnded(1);
}
Joystick::readX(){
  
}
Joystick::readYB(){
  
}
Joystick::readYX(){
   
}

