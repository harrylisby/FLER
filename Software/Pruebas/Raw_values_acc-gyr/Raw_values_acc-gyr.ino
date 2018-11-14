#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 posicion;

int acc_x, acc_y, acc_z; //variables para los tres ejes del acelerómetro
int gyr_x, gyr_y, gyr_z; //variables para los tres ejes del giroscópio


void setup (){
  Serial.begin (115200);
  Wire.begin();
  posicion.initialize();

  if (posicion.testConnection()){
    Serial.println("Sensor funcionando");
  }
  else {
    Serial.println("Error al iniciar sensor");
  }
}

void loop (){
  posicion.getAcceleration(&acc_x, acc_y, acc_z); //lee la aceleracion
  posicion.getRotation(gyr_x, gyr_y, gyr_z); //lee la velocidad angular

  Serial.print("ACC_X: " + String(acc_x) + "Y: " + String(acc_y) + "Z: " + String(acc_z));
  Serial.println("GYR_X: " + String(gyr_x) + "Y: " + String(gyr_y) + "Z: " + String(gyr_z));
}
