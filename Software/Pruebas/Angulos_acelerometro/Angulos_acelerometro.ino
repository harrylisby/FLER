#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 sensor;


int16_t ax, ay, az;

void setup() {
  Serial.begin(57600);    
  Wire.begin();             
  sensor.initialize();    

 
  // wait for ready
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available()){
    Serial.println(F("Send any character to start sketch.\n"));
    delay(1500);
  }                
  while (Serial.available() && Serial.read()); // empty buffer again
 
  // start message
  Serial.println("\nMPU6050 Calibration Sketch");
  delay(2000);
  Serial.println("\nYour MPU6050 should be placed in horizontal position, with package letters facing up. \nDon't touch it until you see a finish message.\n");
  delay(5000);
  // verify connection
  Serial.println(sensor.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
 
  delay(1000);
  
  /*if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");*/

  sensor.setXAccelOffset(-5659);
  sensor.setYAccelOffset(6569);
  sensor.setZAccelOffset(8754);
  sensor.setXGyroOffset(-48);
  sensor.setYGyroOffset(-9);
  sensor.setZGyroOffset(43);

}

void loop() {
 
  sensor.getAcceleration(&ax, &ay, &az);

  float accel_ang_x=atan(ax/sqrt(pow(ay,2) + pow(az,2)))*(180.0/3.14);
  float accel_ang_y=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(180.0/3.14);

  Serial.print("Inclinacion en X: ");
  Serial.print(accel_ang_x); 
  Serial.print(" Inclinacion en Y:");
  Serial.println(accel_ang_y);
  delay(100);
}

