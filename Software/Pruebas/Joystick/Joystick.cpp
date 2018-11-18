#include <Joystick.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Joystick::Joystick(int boton, int adc1, int adc2, uint8_t adsDir):ads(dir){
  _boton = boton;
  _adc1 = adc1;
  _adc2 = adc2;
  _adsDir = dir;
}

uint16_t Joystick::readY(){
    _value_boton = digitalRead(boton);
    if (_value_boton == 1){
      _adcY=ads.readADC_SingleEnded(adc1);
    }
    else{
      _adcY = 13150;
    }
    return _adcY;
}
uint16_t Joystick::readX(){
    _value_boton = digitalRead(boton);
    if (_value_boton == 1){
      _adcX=ads.readADC_SingleEnded(adc2);
    }
    else{
      _adcX = 13150;
    }
    return _adcX;
}
uint16_t Joystick::readYB(){
    value_boton = digitalRead(boton);
    if (value_boton == 0){
      _adcYB=ads.readADC_SingleEnded(adc1);
    }
    else{
      _adcYB = 13150;
    }
    return _adcYB;
}
uint16_t Joystick::readXB(){
    value_boton = digitalRead(boton);
    if (value_boton == 0){
      _adcXB=ads.readADC_SingleEnded(adc2);
    }
    else{
      _adcXB = 13150;
    }
    return _adcXB;
}

