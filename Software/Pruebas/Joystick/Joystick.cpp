#include <Joystick.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Joystick::Joystick(int boton, int adc1, int adc2, uint8_t adsDir):ads(dir){
  _boton = boton;
  _adc1 = adc1;
  _adc2 = adc2;
}

Joystick::readY(){
    value_boton = digitalRead(boton);
    if (value_boton == 1){
      _adcY=ads.readADC_SingleEnded(adc1);
    }
    else{
      _adcY = 13150;
    }
}
Joystick::readX(){
    value_boton = digitalRead(boton);
    if (value_boton == 1){
      _adcX=ads.readADC_SingleEnded(adc2);
    }
    else{
      _adcX = 13150;
    }
}
Joystick::readYB(){
    value_boton = digitalRead(boton);
    if (value_boton == 0){
      _adcYB=ads.readADC_SingleEnded(adc1);
    }
    else{
      _adcYB = 13150;
    }
}
Joystick::readXB(){
    value_boton = digitalRead(boton);
    if (value_boton == 0){
      _adcXB=ads.readADC_SingleEnded(adc2);
    }
    else{
      _adcXB = 13150;
    }
}

